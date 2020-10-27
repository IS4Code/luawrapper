#ifndef lualib53_h
#define lualib53_h

#include "lua.h"

namespace lua53
{
	LUA53_API int (luaopen_base)(lua_State *L);
	LUA53_API int (luaopen_coroutine)(lua_State *L);
	LUA53_API int (luaopen_table)(lua_State *L);
	LUA53_API int (luaopen_io)(lua_State *L);
	LUA53_API int (luaopen_os)(lua_State *L);
	LUA53_API int (luaopen_string)(lua_State *L);
	LUA53_API int (luaopen_utf8)(lua_State *L);
	LUA53_API int (luaopen_bit32)(lua_State *L);
	LUA53_API int (luaopen_math)(lua_State *L);
	LUA53_API int (luaopen_debug)(lua_State *L);
	LUA53_API int (luaopen_package)(lua_State *L);
	LUA53_API void (luaL_openlibs)(lua_State *L);
}

#endif
