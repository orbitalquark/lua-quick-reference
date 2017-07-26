// Example 33. Call a function for each table key-value pair

//8<----------------------------------------------------------------------------
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
//8<----------------------------------------------------------------------------

// Thread body continuation function for iterating over
// a table's key-value pairs and calling a function
// with each pair as that function's arguments.
static int l_iteratek(lua_State *thread, int status,
                      lua_KContext ctx) {
  if (status == LUA_OK)
    lua_pushnil(thread); // start iteration
  else
    lua_pop(thread, 1); // previous value
  while (lua_next(thread, 1) != 0) {
    lua_pushvalue(thread, lua_upvalueindex(1));
    lua_pushvalue(thread, -3); // key
    lua_pushvalue(thread, -3); // value
    lua_callk(thread, 2, 0, 0, l_iteratek);
    lua_pop(thread, 1); // value
  }
  return 0;
}

// Initial thread body function.
static int l_iterate(lua_State *thread) {
  return l_iteratek(thread, LUA_OK, 0);
}

//8<----------------------------------------------------------------------------
int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
//8<----------------------------------------------------------------------------

lua_State *thread = lua_newthread(L);
/* push function to be called each iteration */
  //8<--------------------------------------------------------------------------
  lua_getglobal(thread, "coroutine");
  lua_getfield(thread, -1, "yield");
  lua_replace(thread, -2);
  //8<--------------------------------------------------------------------------
lua_pushcclosure(thread, l_iterate, 1);
/* push table to be iterated over */
  //8<--------------------------------------------------------------------------
  lua_pushglobaltable(thread);
  //8<--------------------------------------------------------------------------
while (lua_resume(thread, L, 1) == LUA_YIELD) {
  /* work to do in-between yields */
  //8<--------------------------------------------------------------------------
  printf("%s\t%s\n", lua_tostring(thread, -2), luaL_typename(thread, -1));
  //8<--------------------------------------------------------------------------
}
lua_pop(L, 1); // dead thread

//8<----------------------------------------------------------------------------
  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
