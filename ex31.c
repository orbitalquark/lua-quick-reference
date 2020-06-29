// Example 31. Complex number module

//8<----------------------------------------------------------------------------
#include "lualib.h"
//8<----------------------------------------------------------------------------

#include <complex.h>
#include "lua.h"
#include "lauxlib.h"

typedef double complex Complex;

// Pushes a complex number as userdata.
static int pushcomplex(lua_State *L, Complex z) {
  Complex *p = lua_newuserdatauv(L, sizeof(Complex),
                                 0);
  *p = z;
  luaL_setmetatable(L, "complex_mt");
  return 1;
}

// Creates and pushes a new complex number.
static int complex_new(lua_State *L) {
  double x = luaL_optnumber(L, 1, 0);
  double y = luaL_optnumber(L, 2, 0);
  pushcomplex(L, x + y * I);
  return 1;
}

// Asserts and returns a complex number function
// argument.
static Complex checkcomplex(lua_State *L, int arg) {
  return lua_isuserdata(L, 1) ?
    *((Complex *)luaL_checkudata(L, arg, "complex_mt"))
    : luaL_checknumber(L, arg);
}

// Defines a binary complex number operation.
#define binop(name, op) \
  static int complex_##name(lua_State *L) { \
    Complex z1 = checkcomplex(L, 1); \
    Complex z2 = checkcomplex(L, 2); \
    return pushcomplex(L, z1 op z2); \
  }

// Defines a unary complex number operation.
#define unop(name, op) \
  static int complex_##name(lua_State *L) { \
    Complex z = checkcomplex(L, 1); \
    return pushcomplex(L, op(z)); \
  }

// Complex number operations.
unop(abs, cabs)
unop(real, creal)
unop(imag, cimag)
unop(arg, carg)
unop(conj, conj)
binop(add, +)
binop(sub, -)
binop(mul, *)
binop(div, /)
unop(unm, -)
binop(eq, ==)

// String representation of a complex number.
static int complex_tostring(lua_State *L) {
  Complex z = checkcomplex(L, 1);
  double x = creal(z), y = cimag(z);
  if (x != 0 && y > 0)
    lua_pushfstring(L, "%f+%fi", x, y);
  else if (x != 0 && y < 0)
    lua_pushfstring(L, "%f%fi", x, y);
  else if (x == 0)
    lua_pushfstring(L, "%fi", y);
  else
    lua_pushfstring(L, "%f", x);
  return 1;
}

// Complex module functions.
static const luaL_Reg complex_functions[] = {
  {"new", complex_new},
  {"abs", complex_abs},
  {"real", complex_real},
  {"imag", complex_imag},
  {"arg", complex_arg},
  {"conj", complex_conj},
  {NULL, NULL}
};

// Complex number metamethods.
static const luaL_Reg complex_metamethods[] = {
  {"__add", complex_add},
  {"__sub", complex_sub},
  {"__mul", complex_mul},
  {"__div", complex_div},
  {"__unm", complex_unm},
  {"__eq", complex_eq},
  {"__tostring", complex_tostring},
  {NULL, NULL}
};

// Complex number module entry point.
int luaopen_complex(lua_State *L) {
  // Create and push the module table.
  luaL_newlib(L, complex_functions);
  // Create the complex number metatable, fill it,
  // link it with the module table, then pop it.
  luaL_newmetatable(L, "complex_mt");
  luaL_setfuncs(L, complex_metamethods, 0);
  lua_pushvalue(L, -2); // the module table
  lua_setfield(L, -2, "__index");
  lua_pop(L, 1); // metatable
  return 1; // return the module table
}

//8<----------------------------------------------------------------------------
int main() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  luaL_requiref(L, "complex", luaopen_complex, 0);
  lua_pop(L, 1);

  // Lua code.
  luaL_dostring(L, "complex = require('complex')");
  luaL_dostring(L, "print(complex.new(3, 4))");
  luaL_dostring(L, "print(complex.new(-3, 4))");
  luaL_dostring(L, "print(complex.new(3, -4))");
  luaL_dostring(L, "print(complex.new(-3, -4))");
  luaL_dostring(L, "print(complex.new(3, 0))");
  luaL_dostring(L, "print(complex.new(0, 4))");
  luaL_dostring(L, "print(complex.new(-3, 0))");
  luaL_dostring(L, "print(complex.new(0, -4))");
  luaL_dostring(L, "print(complex.new(-1, 1):conj())");

  if (lua_gettop(L) > 0) printf("stack size != 0\n");
  lua_close(L);
  return 0;
}
//8<----------------------------------------------------------------------------
