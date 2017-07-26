// Example 25. Use a C structure as a Lua value

//8<----------------------------------------------------------------------------
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

//8<----------------------------------------------------------------------------

// C struct for using FILE* as a Lua value.
typedef struct {
  FILE *f;
  int closed; // cannot fclose(f) twice
} lFile;

// Metamethod for closing files prior to deletion.
static int l_filegc(lua_State *L) {
  lFile *f = (lFile *)luaL_checkudata(L, 1, "file_mt");
  if (!f->closed)
    fclose(f->f);
  //8<--------------------------------------------------------------------------
  printf("file closed\n");
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
// file with it, and assign a metatable that ensures
// the file is eventually closed.
lFile *f = (lFile *)lua_newuserdata(L, sizeof(lFile));
f->f = fopen(filename, "r");
f->closed = 0;
if (luaL_newmetatable(L, "file_mt")) {
  lua_pushcfunction(L, l_filegc);
  lua_setfield(L, -2, "__gc");
  /* define additional metamethods */
}
lua_setmetatable(L, -2);
/* do something with the file */
lua_pop(L, 1); // invokes __gc()

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
