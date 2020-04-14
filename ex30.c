// Example 29. Call Lua's string.find

//8<----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  const char *s = "foobar", *pattern = "b..";
//8<----------------------------------------------------------------------------

// Record initial stack size due to LUA_MULTRET.
int n = lua_gettop(L);
// Push the global function string.find().
lua_getglobal(L, "string");
lua_getfield(L, -1, "find");
lua_replace(L, -2);
// Push two arguments.
lua_pushstring(L, s);
lua_pushstring(L, pattern);
// Call the function with those two arguments,
// expecting a variable number of results.
if (lua_pcall(L, 2, LUA_MULTRET, 0) == LUA_OK &&
    lua_gettop(L) > n) {
  int start = lua_tointeger(L, n + 1);
  int end = lua_tointeger(L, n + 2);
  /* process returned positions and any captures */
  //8<--------------------------------------------------------------------------
  printf("%i %i\n", start, end);
  //8<--------------------------------------------------------------------------
  lua_settop(L, n); // pop all returned values
}

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
