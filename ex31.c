// Example 30. Complex number module

//8<----------------------------------------------------------------------------
#include "lualib.h"
//8<----------------------------------------------------------------------------

#include <complex.h>
#include "lua.h"
#include "lauxlib.h"
typedef double complex Complex;

// Pushes a complex number as userdata.
static int l_pushcomplex(lua_State *L, Complex z) {
  Complex *p = lua_newuserdata(L, sizeof(Complex));
  *p = z;
  luaL_setmetatable(L, "complex_mt");
  return 1;
}

// Creates and pushes a new complex number.
static int l_cnew(lua_State *L) {
  double x = luaL_optnumber(L, 1, 0);
  double y = luaL_optnumber(L, 2, 0);
  l_pushcomplex(L, x + y * I);
  return 1;
}

// Asserts and returns a complex number function
// argument.
static Complex lL_checkcomplex(lua_State *L, int arg) {
  if (lua_isuserdata(L, 1))
    return *((Complex *)luaL_checkudata(L, arg, "complex_mt"));
  else
    return luaL_checknumber(L, arg);
}

// Defines a binary complex number operation.
#define binop(name, op) \
  static int l_c##name(lua_State *L) { \
    Complex z1 = lL_checkcomplex(L, 1); \
    Complex z2 = lL_checkcomplex(L, 2); \
    return l_pushcomplex(L, z1 op z2); \
  }

// Defines a unary complex number operation.
#define unop(name, op) \
  static int l_c##name(lua_State *L) { \
    Complex z = lL_checkcomplex(L, 1); \
    return l_pushcomplex(L, op(z)); \
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
static int l_ctostring(lua_State *L) {
  Complex z = lL_checkcomplex(L, 1);
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
  {"new", l_cnew},
  {"abs", l_cabs},
  {"real", l_creal},
  {"imag", l_cimag},
  {"arg", l_carg},
  {"conj", l_cconj},
  {NULL, NULL}
};

// Complex number metamethods.
static const luaL_Reg complex_metamethods[] = {
  {"__add", l_cadd},
  {"__sub", l_csub},
  {"__mul", l_cmul},
  {"__div", l_cdiv},
  {"__unm", l_cunm},
  {"__eq", l_ceq},
  {"__tostring", l_ctostring},
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
