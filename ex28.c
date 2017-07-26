// Example 28. C function that translates string characters

//8<----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

//8<----------------------------------------------------------------------------

static int translate_chars(lua_State *L) {
  // Fetch arguments. The first should be a string. The
  // second should be a table, if given. Otherwise, use
  // a default table stored as an upvalue.
  const char *s = luaL_checkstring(L, 1);
  if (lua_gettop(L) > 1)
    luaL_checktype(L, 2, LUA_TTABLE);
  else
    lua_pushvalue(L, lua_upvalueindex(1));
  // Allocate and fill a copy of the string argument,
  // translate its characters according to the table
  // argument, and push the result.
  char *o = strcpy(malloc(strlen(s) + 1), s);
  for (char *p = o; *p; p++) {
    lua_pushlstring(L, p, 1); // table key
    lua_gettable(L, 2); // fetch value assigned to key
    if (lua_isstring(L, -1))
      *p = *lua_tostring(L, -1); // translate char
    lua_pop(L, 1); // table value
  }
  lua_pushstring(L, o); // push the value to return
  free(o);
  return 1; // the number of stack values to return
}

//8<----------------------------------------------------------------------------

int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
//8<----------------------------------------------------------------------------

// Create the default translation table, assign it as
// an upvalue to translate_chars, and register that
// function as the global function "tr".
lua_createtable(L, 0, 1);
lua_pushliteral(L, "_");
lua_setfield(L, -2, " "); // translate ' ' to '_'
lua_pushcclosure(L, translate_chars, 1);
lua_setglobal(L, "tr");

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  luaL_dostring(L, "return tr('hello world!')");
  printf("%s\n", lua_tostring(L, -1));
  lua_pop(L, 1);
  luaL_dostring(L, "return tr('hello!', {['!'] = '?'})");
  printf("%s\n", lua_tostring(L, -1));
  lua_pop(L, 1);
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
