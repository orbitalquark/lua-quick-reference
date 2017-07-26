// Example 23. Push the entire contents of a file as a string

//8<----------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

int main(int argc, char **argv) {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  const char *filename = "/home/mitchell/code/textadept/src/textadept.c";
//8<----------------------------------------------------------------------------

FILE *f = fopen(filename, "r");
luaL_Buffer b;
luaL_buffinit(L, &b);
char buf[BUFSIZ];
while (fgets(buf, BUFSIZ, f) != NULL)
  luaL_addlstring(&b, buf, strlen(buf));
luaL_pushresult(&b);
fclose(f);

//8<----------------------------------------------------------------------------
  printf("%s\n", lua_tostring(L, -1));
  if (lua_gettop(L) > 1) printf("stack size != 1\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
