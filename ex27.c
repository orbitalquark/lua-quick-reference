// Example 27. Mathematical gamma function

//8<----------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

//8<----------------------------------------------------------------------------
static int l_gamma(lua_State *L) {
  double z = luaL_checknumber(L, 1); // fetch argument
  lua_pushnumber(L, tgamma(z)); // push value to return
  return 1; // number of stack values to return
}

//8<----------------------------------------------------------------------------
int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
//8<----------------------------------------------------------------------------

// Add gamma to Lua's math module.
lua_getglobal(L, "math");
lua_pushcfunction(L, l_gamma);
lua_setfield(L, -2, "gamma");
lua_pop(L, 1); // global "math"

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  luaL_dostring(L, "return math.gamma(3)");
  printf("%f\n", lua_tonumber(L, -1));
  lua_pop(L, 1);
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
