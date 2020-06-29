// Example 26. Use a C structure as a Lua value

//8<----------------------------------------------------------------------------
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

//8<----------------------------------------------------------------------------

// C struct for using FILE* as a Lua value.
typedef struct {FILE *f;} File;

// Metamethod for closing to-be-closed files.
static int close_file(lua_State *L) {
  File *lf = (File *)luaL_checkudata(L, 1, "file_mt");
  lua_getiuservalue(L, 1, 1); // f closed?
  if (!lua_toboolean(L, -1)) {
    fclose(lf->f);
    lua_pushboolean(L, 1);
    lua_setiuservalue(L, 1, 1); // f closed now
    //8<------------------------------------------------------------------------
    printf("file closed\n");
    //8<------------------------------------------------------------------------
  }
  //8<--------------------------------------------------------------------------
  else printf("file already closed\n");
  //8<--------------------------------------------------------------------------
  return 0;
}

//8<----------------------------------------------------------------------------
int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  const char *filename = "/home/mitchell/code/textadept/init.lua";
//8<----------------------------------------------------------------------------

// Create a new file userdata, open and associate a
// file with it, assign a metatable that helps
// automatically close the file, and mark the userdata
// as a to-be-closed variable.
File *lf = lua_newuserdatauv(L, sizeof(FILE), 1);
lf->f = fopen(filename, "r");
lua_pushboolean(L, 0);
lua_setiuservalue(L, -2, 1); // f not closed yet
if (luaL_newmetatable(L, "file_mt")) {
  lua_pushcfunction(L, close_file);
  lua_setfield(L, -2, "__close");
//8<----------------------------------------------------------------------------
  lua_pushcfunction(L, close_file);
  lua_setfield(L, -2, "__gc");
//8<----------------------------------------------------------------------------
}
lua_setmetatable(L, -2);
lua_toclose(L, -1);
/* do something with the file */
lua_pop(L, 1); // invokes __close()

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
