#include "luamath.h"

int lualn(lua_State* L)
{
	double x = lua_tonumber(L, 1);
	lua_pushnumber(L, log(x));
	return 1;
}

int lualog2(lua_State* L)
{
	double x = lua_tonumber(L, 1);
	lua_pushnumber(L, log(x) / M_LN2);
	return 1;
}

int lualog10(lua_State* L)
{
	double x = lua_tonumber(L, 1);
	lua_pushnumber(L, log(x) / M_LN10);
	return 1;
}

// Base, x
int lualogn(lua_State* L)
{
	double x = lua_tonumber(L, 2);
	double b = lua_tonumber(L, 1);
	lua_pushnumber(L, log(x) / log(b));
	return 1;
}

int luasin(lua_State* L)
{
	double x = lua_tonumber(L, 1);
	lua_pushnumber(L, sin(x));
	return 1;
}

int luacos(lua_State* L)
{
	double x = lua_tonumber(L, 1);
	lua_pushnumber(L, cos(x));
	return 1;
}

int luatan(lua_State* L)
{
	double x = lua_tonumber(L, 1);
	lua_pushnumber(L, tan(x));
	return 1;
}

void luamath_load(lua_State* L)
{
	// Push constants
	lua_pushnumber(L, M_PI);
	lua_setglobal(L, "pi");

	lua_pushnumber(L, M_E);
	lua_setglobal(L, "e");

	lua_pushcfunction(L, lualn);
	lua_setglobal(L, "ln");

	lua_pushcfunction(L, lualog2);
	lua_setglobal(L, "log2");

	lua_pushcfunction(L, lualog10);
	lua_setglobal(L, "log10");

	lua_pushcfunction(L, lualogn);
	lua_setglobal(L, "logn");

	lua_pushcfunction(L, luasin);
	lua_setglobal(L, "sin");
	lua_pushcfunction(L, luacos);
	lua_setglobal(L, "cos");
	lua_pushcfunction(L, luatan);
	lua_setglobal(L, "tan");
}