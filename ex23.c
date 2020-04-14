// Example 22. Simple stand-alone Lua interpreter
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(int argc, char **argv) {
  int status = 0;
  // Create a new embedded Lua interpreter.
  lua_State *L = luaL_newstate();
  // Load all of Lua's standard library modules.
  luaL_openlibs(L);
  // Execute the Lua script specified on the command
  // line. If there is an error, report it.
  if (argc > 1 && luaL_dofile(L, argv[1]) != LUA_OK) {
    const char *errmsg = lua_tostring(L, -1);
    fprintf(stderr, "Lua error: %s\n", errmsg);
    status = 1;
  }
  // Close the Lua interpreter.
  lua_close(L);
  return status;
}
