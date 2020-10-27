#ifndef lualib51_h
#define lualib51_h

#include "lua.h"

namespace lua51
{
	LUA51_API int (luaopen_base) (lua_State *L);
	LUA51_API int (luaopen_table) (lua_State *L);
	LUA51_API int (luaopen_io) (lua_State *L);
	LUA51_API int (luaopen_os) (lua_State *L);
	LUA51_API int (luaopen_string) (lua_State *L);
	LUA51_API int (luaopen_math) (lua_State *L);
	LUA51_API int (luaopen_debug) (lua_State *L);
	LUA51_API int (luaopen_package) (lua_State *L);
	LUA51_API void (luaL_openlibs) (lua_State *L); 
}

#endif
