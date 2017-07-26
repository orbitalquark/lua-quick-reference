// Example 31. Run user-defined Lua code in a sandbox

//8<----------------------------------------------------------------------------
#include <stdio.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  const char *user_script = "/tmp/foo.lua";
//8<----------------------------------------------------------------------------

// Define and store the sandbox for subsequent use.
const char *safe[] = {
  "assert", "error", "ipairs", "math", "next", "pairs",
  "pcall", "select", "string", "table", "tonumber",
  "tostring", "type", "xpcall", NULL
};
lua_newtable(L); // the sandbox environment
for (const char **p = safe; *p; p++)
  lua_getglobal(L, *p), lua_setfield(L, -2, *p);
/* add other safe host functions to sandbox */
int sandbox_ref = luaL_ref(L, LUA_REGISTRYINDEX);

//8<----------------------------------------------------------------------------
lua_rawgeti(L, LUA_REGISTRYINDEX, sandbox_ref), lua_setglobal(L, "sandbox");
//8<----------------------------------------------------------------------------

// Attempt to load the user-defined Lua script
// (text-only) as an anonymous function.
if (luaL_loadfilex(L, user_script, "t") == LUA_OK) {
  // Make the sandbox the function's environment.
  lua_rawgeti(L, LUA_REGISTRYINDEX, sandbox_ref);
  lua_setupvalue(L, -2, 1);
  // Execute the script.
  if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
    /* process and pop error message at index -1 */
  }
}
/* ... */
// Finished with the sandbox; delete it.
luaL_unref(L, LUA_REGISTRYINDEX, sandbox_ref);

//8<----------------------------------------------------------------------------
  luaL_dostring(L, "for k,v in pairs(sandbox) do print(k,v) end");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
