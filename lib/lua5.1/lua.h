#ifndef lua51_h
#define lua51_h

#include "luaconf.h"

namespace lua51
{
	LUA51_API lua_State *(lua_newstate)(lua_Alloc f, void *ud);
	LUA51_API void       (lua_close)(lua_State *L);
	LUA51_API lua_State *(lua_newthread)(lua_State *L);

	LUA51_API lua_CFunction(lua_atpanic) (lua_State *L, lua_CFunction panicf);

	LUA51_API int   (lua_gettop)(lua_State *L);
	LUA51_API void  (lua_settop)(lua_State *L, int idx);
	LUA51_API void  (lua_pushvalue)(lua_State *L, int idx);
	LUA51_API void  (lua_remove)(lua_State *L, int idx);
	LUA51_API void  (lua_insert)(lua_State *L, int idx);
	LUA51_API void  (lua_replace)(lua_State *L, int idx);
	LUA51_API int   (lua_checkstack)(lua_State *L, int sz);

	LUA51_API void  (lua_xmove)(lua_State *from, lua_State *to, int n);

	LUA51_API int             (lua_isnumber)(lua_State *L, int idx);
	LUA51_API int             (lua_isstring)(lua_State *L, int idx);
	LUA51_API int             (lua_iscfunction)(lua_State *L, int idx);
	LUA51_API int             (lua_isuserdata)(lua_State *L, int idx);
	LUA51_API int             (lua_type)(lua_State *L, int idx);
	LUA51_API const char     *(lua_typename)(lua_State *L, int tp);

	LUA51_API int            (lua_equal)(lua_State *L, int idx1, int idx2);
	LUA51_API int            (lua_rawequal)(lua_State *L, int idx1, int idx2);
	LUA51_API int            (lua_lessthan)(lua_State *L, int idx1, int idx2);

	LUA51_API lua_Number(lua_tonumber) (lua_State *L, int idx);
	LUA51_API lua_Integer(lua_tointeger) (lua_State *L, int idx);
	LUA51_API int             (lua_toboolean)(lua_State *L, int idx);
	LUA51_API const char     *(lua_tolstring)(lua_State *L, int idx, size_t *len);
	LUA51_API size_t(lua_objlen) (lua_State *L, int idx);
	LUA51_API lua_CFunction(lua_tocfunction) (lua_State *L, int idx);
	LUA51_API void	       *(lua_touserdata)(lua_State *L, int idx);
	LUA51_API lua_State      *(lua_tothread)(lua_State *L, int idx);
	LUA51_API const void     *(lua_topointer)(lua_State *L, int idx);

	LUA51_API void  (lua_pushnil)(lua_State *L);
	LUA51_API void  (lua_pushnumber)(lua_State *L, lua_Number n);
	LUA51_API void  (lua_pushinteger)(lua_State *L, lua_Integer n);
	LUA51_API void  (lua_pushlstring)(lua_State *L, const char *s, size_t l);
	LUA51_API void  (lua_pushstring)(lua_State *L, const char *s);
	LUA51_API const char *(lua_pushvfstring)(lua_State *L, const char *fmt, va_list argp);
	LUA51_API const char *(lua_pushfstring)(lua_State *L, const char *fmt, ...);
	LUA51_API void  (lua_pushcclosure)(lua_State *L, lua_CFunction fn, int n);
	LUA51_API void  (lua_pushboolean)(lua_State *L, int b);
	LUA51_API void  (lua_pushlightuserdata)(lua_State *L, void *p);
	LUA51_API int   (lua_pushthread)(lua_State *L);

	LUA51_API void  (lua_gettable)(lua_State *L, int idx);
	LUA51_API void  (lua_getfield)(lua_State *L, int idx, const char *k);
	LUA51_API void  (lua_rawget)(lua_State *L, int idx);
	LUA51_API void  (lua_rawgeti)(lua_State *L, int idx, int n);
	LUA51_API void  (lua_createtable)(lua_State *L, int narr, int nrec);
	LUA51_API void *(lua_newuserdata)(lua_State *L, size_t sz);
	LUA51_API int   (lua_getmetatable)(lua_State *L, int objindex);
	LUA51_API void  (lua_getfenv)(lua_State *L, int idx);

	LUA51_API void  (lua_settable)(lua_State *L, int idx);
	LUA51_API void  (lua_setfield)(lua_State *L, int idx, const char *k);
	LUA51_API void  (lua_rawset)(lua_State *L, int idx);
	LUA51_API void  (lua_rawseti)(lua_State *L, int idx, int n);
	LUA51_API int   (lua_setmetatable)(lua_State *L, int objindex);
	LUA51_API int   (lua_setfenv)(lua_State *L, int idx);

	LUA51_API void  (lua_call)(lua_State *L, int nargs, int nresults);
	LUA51_API int   (lua_pcall)(lua_State *L, int nargs, int nresults, int errfunc);
	LUA51_API int   (lua_cpcall)(lua_State *L, lua_CFunction func, void *ud);
	LUA51_API int   (lua_load)(lua_State *L, lua_Reader reader, void *dt, const char *chunkname);

	LUA51_API int (lua_dump)(lua_State *L, lua_Writer writer, void *data);

	LUA51_API int  (lua_yield)(lua_State *L, int nresults);
	LUA51_API int  (lua_resume)(lua_State *L, int narg);
	LUA51_API int  (lua_status)(lua_State *L);

	LUA51_API int (lua_gc)(lua_State *L, int what, int data);

	LUA51_API int   (lua_error)(lua_State *L);

	LUA51_API int   (lua_next)(lua_State *L, int idx);

	LUA51_API void  (lua_concat)(lua_State *L, int n);

	LUA51_API lua_Alloc(lua_getallocf) (lua_State *L, void **ud);
	LUA51_API void lua_setallocf(lua_State *L, lua_Alloc f, void *ud);

	/* hack */
	LUA51_API void lua_setlevel(lua_State *from, lua_State *to);

	typedef struct lua_Debug lua_Debug;  /* activation record */


	/* Functions to be called by the debuger in specific events */
	typedef void(*lua_Hook) (lua_State *L, lua_Debug *ar);


	LUA51_API int lua_getstack(lua_State *L, int level, lua_Debug *ar);
	LUA51_API int lua_getinfo(lua_State *L, const char *what, lua_Debug *ar);
	LUA51_API const char *lua_getlocal(lua_State *L, const lua_Debug *ar, int n);
	LUA51_API const char *lua_setlocal(lua_State *L, const lua_Debug *ar, int n);
	LUA51_API const char *lua_getupvalue(lua_State *L, int funcindex, int n);
	LUA51_API const char *lua_setupvalue(lua_State *L, int funcindex, int n);

	LUA51_API int lua_sethook(lua_State *L, lua_Hook func, int mask, int count);
	LUA51_API lua_Hook lua_gethook(lua_State *L);
	LUA51_API int lua_gethookmask(lua_State *L);
	LUA51_API int lua_gethookcount(lua_State *L);


	struct lua_Debug {
		int event;
		const char *name;	/* (n) */
		const char *namewhat;	/* (n) `global', `local', `field', `method' */
		const char *what;	/* (S) `Lua', `C', `main', `tail' */
		const char *source;	/* (S) */
		int currentline;	/* (l) */
		int nups;		/* (u) number of upvalues */
		int linedefined;	/* (S) */
		int lastlinedefined;	/* (S) */
		char short_src[LUA_IDSIZE]; /* (S) */
		/* private part */
		int i_ci;  /* active function */
	};
}

#endif
