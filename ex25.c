// Example 24. Push a lower-case copy of a string

//8<----------------------------------------------------------------------------
#include <ctype.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  const char *s = "TEST";
//8<----------------------------------------------------------------------------

luaL_Buffer b;
size_t len = strlen(s);
char *p = luaL_buffinitsize(L, &b, len);
for (int i = 0; i < len; i++)
  p[i] = tolower((unsigned char)s[i]);
luaL_pushresultsize(&b, len);

//8<----------------------------------------------------------------------------
  printf("%s\n", lua_tostring(L, -1));
  if (lua_gettop(L) > 1) printf("stack size != 1\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
