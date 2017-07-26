// Example 26. Delete all string keys from a table

//8<----------------------------------------------------------------------------
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_dostring(L, "t={1,2,3,a=1,b=2,c=3}");
  lua_getglobal(L, "t");
//8<----------------------------------------------------------------------------

lua_pushnil(L);
while (lua_next(L, -2) != 0) {
  if (lua_type(L, -2) == LUA_TSTRING) {
    // Delete values assigned to string keys (fields).
    const char *key = lua_tostring(L, -2);
    lua_pushnil(L);
    lua_setfield(L, -4, key);
  }
  lua_pop(L, 1); // value
}
lua_pop(L, 1); // table iterated over

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  luaL_dostring(L, "for k,v in pairs(t) do print(k,v) end");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
