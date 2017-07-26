// Example 32. Monitor output from a set of files

//8<----------------------------------------------------------------------------
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
//8<----------------------------------------------------------------------------

// Filenames to monitor.
const char *filenames[32]; // will have NULL sentinel

// Thread body continuation function for monitoring a
// file.
static int l_monitork(lua_State *thread, int status,
                      lua_KContext ctx) {
  FILE *f = (FILE*)ctx;
  // Stop monitoring file if requested to.
  if (status == LUA_YIELD &&
      !lua_toboolean(thread, 1)) {
    fclose(f);
    return 0;
  }
  // Check for data to be read.
  int c = getc(f);
  if (c != EOF) {
    // Read and yield a line of data.
    ungetc(c, f);
    char buf[BUFSIZ];
    fgets(buf, BUFSIZ, f);
    lua_pushstring(thread, buf);
    return lua_yieldk(thread, 1, ctx, l_monitork);
  } else {
    // No data to read; yield nothing.
    return lua_yieldk(thread, 0, ctx, l_monitork);
  }
}

// Thread body function for monitoring a file.
static int l_monitorfile(lua_State *thread) {
  const char *filename = luaL_checkstring(thread, 1);
  FILE *f = fopen(filename, "r");
  if (!f)
    return luaL_error(thread, "file '%s' not found",
                      filename);
  return l_monitork(thread, LUA_OK, (lua_KContext)f);
}

//8<----------------------------------------------------------------------------
int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  filenames[0] = "/tmp/output"; filenames[1] = "/tmp/output2"; filenames[2] = NULL;
//8<----------------------------------------------------------------------------

// Create and start threads.
lua_createtable(L, 32, 0); // active threads table
for (int i = 0; i < 32; i++) {
  if (!filenames[i]) break;
  lua_State *thread = lua_newthread(L);
  lua_pushcfunction(thread, l_monitorfile);
  lua_pushstring(thread, filenames[i]);
  if (lua_resume(thread, L, 1) == LUA_YIELD)
    // Store thread for monitoring.
    lua_rawseti(L, -2, lua_rawlen(L, -2) + 1);
  else {
    /* handle error starting thread */
    //8<------------------------------------------------------------------------
    printf("%s\n", lua_tostring(thread, -1));
    //8<------------------------------------------------------------------------
    lua_pop(L, 1);
  }
}
// Monitor active threads.
int i = 1;
while (lua_rawlen(L, -1) > 0) {
  lua_rawgeti(L, -1, i);
  lua_State *thread = lua_tothread(L, -1);
  if (lua_gettop(thread) > 0) {
    // Thread has output from its monitored file.
    const char *line = lua_tostring(thread, 1);
    /* process line and possibly stop monitoring */
    //8<------------------------------------------------------------------------
    printf("%s", line);
    int keep_monitoring = 0;
    //8<------------------------------------------------------------------------
    lua_pushboolean(thread, keep_monitoring);
    lua_replace(thread, 1);
    lua_resume(thread, L, 1);
    if (!keep_monitoring) {
      // Stop monitoring the now-dead thread.
      lua_getglobal(L, "table");
      lua_getfield(L, -1, "remove");
      lua_replace(L, -2);
      lua_pushvalue(L, -3); // active threads table
      lua_pushnumber(L, i);
      lua_call(L, 2, 0); // table.remove(threads, i)
      lua_pop(L, 1); // dead thread
      continue; // monitor next thread
    }
  }
  lua_pop(L, 1); // thread
  if (++i > lua_rawlen(L, -1)) i = 1; // start again
}
lua_pop(L, 1); // active threads table

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
