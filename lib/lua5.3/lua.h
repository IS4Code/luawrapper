#ifndef lua53_h
#define lua53_h

#include "luaconf.h"

namespace lua53
{
	typedef LUA_KCONTEXT lua_KContext;

	typedef int(*lua_KFunction) (lua_State *L, int status, lua_KContext ctx);

	extern const char lua_ident[];

	LUA53_API lua_State *(lua_newstate)(lua_Alloc f, void *ud);
	LUA53_API void       (lua_close)(lua_State *L);
	LUA53_API lua_State *(lua_newthread)(lua_State *L);

	LUA53_API lua_CFunction(lua_atpanic) (lua_State *L, lua_CFunction panicf);


	LUA53_API const lua_Number *(lua_version)(lua_State *L);

	LUA53_API int   (lua_absindex)(lua_State *L, int idx);
	LUA53_API int   (lua_gettop)(lua_State *L);
	LUA53_API void  (lua_settop)(lua_State *L, int idx);
	LUA53_API void  (lua_pushvalue)(lua_State *L, int idx);
	LUA53_API void  (lua_rotate)(lua_State *L, int idx, int n);
	LUA53_API void  (lua_copy)(lua_State *L, int fromidx, int toidx);
	LUA53_API int   (lua_checkstack)(lua_State *L, int n);

	LUA53_API void  (lua_xmove)(lua_State *from, lua_State *to, int n);

	LUA53_API int             (lua_isnumber)(lua_State *L, int idx);
	LUA53_API int             (lua_isstring)(lua_State *L, int idx);
	LUA53_API int             (lua_iscfunction)(lua_State *L, int idx);
	LUA53_API int             (lua_isinteger)(lua_State *L, int idx);
	LUA53_API int             (lua_isuserdata)(lua_State *L, int idx);
	LUA53_API int             (lua_type)(lua_State *L, int idx);
	LUA53_API const char     *(lua_typename)(lua_State *L, int tp);

	LUA53_API lua_Number(lua_tonumberx) (lua_State *L, int idx, int *isnum);
	LUA53_API lua_Integer(lua_tointegerx) (lua_State *L, int idx, int *isnum);
	LUA53_API int             (lua_toboolean)(lua_State *L, int idx);
	LUA53_API const char     *(lua_tolstring)(lua_State *L, int idx, size_t *len);
	LUA53_API size_t(lua_rawlen) (lua_State *L, int idx);
	LUA53_API lua_CFunction(lua_tocfunction) (lua_State *L, int idx);
	LUA53_API void	       *(lua_touserdata)(lua_State *L, int idx);
	LUA53_API lua_State      *(lua_tothread)(lua_State *L, int idx);
	LUA53_API const void     *(lua_topointer)(lua_State *L, int idx);

	LUA53_API void  (lua_arith)(lua_State *L, int op);

	LUA53_API int   (lua_rawequal)(lua_State *L, int idx1, int idx2);
	LUA53_API int   (lua_compare)(lua_State *L, int idx1, int idx2, int op);

	LUA53_API void        (lua_pushnil)(lua_State *L);
	LUA53_API void        (lua_pushnumber)(lua_State *L, lua_Number n);
	LUA53_API void        (lua_pushinteger)(lua_State *L, lua_Integer n);
	LUA53_API const char *(lua_pushlstring)(lua_State *L, const char *s, size_t len);
	LUA53_API const char *(lua_pushstring)(lua_State *L, const char *s);
	LUA53_API const char *(lua_pushvfstring)(lua_State *L, const char *fmt,
		va_list argp);
	LUA53_API const char *(lua_pushfstring)(lua_State *L, const char *fmt, ...);
	LUA53_API void  (lua_pushcclosure)(lua_State *L, lua_CFunction fn, int n);
	LUA53_API void  (lua_pushboolean)(lua_State *L, int b);
	LUA53_API void  (lua_pushlightuserdata)(lua_State *L, void *p);
	LUA53_API int   (lua_pushthread)(lua_State *L);

	LUA53_API int (lua_getglobal)(lua_State *L, const char *name);
	LUA53_API int (lua_gettable)(lua_State *L, int idx);
	LUA53_API int (lua_getfield)(lua_State *L, int idx, const char *k);
	LUA53_API int (lua_geti)(lua_State *L, int idx, lua_Integer n);
	LUA53_API int (lua_rawget)(lua_State *L, int idx);
	LUA53_API int (lua_rawgeti)(lua_State *L, int idx, lua_Integer n);
	LUA53_API int (lua_rawgetp)(lua_State *L, int idx, const void *p);

	LUA53_API void  (lua_createtable)(lua_State *L, int narr, int nrec);
	LUA53_API void *(lua_newuserdata)(lua_State *L, size_t sz);
	LUA53_API int   (lua_getmetatable)(lua_State *L, int objindex);
	LUA53_API int  (lua_getuservalue)(lua_State *L, int idx);

	LUA53_API void  (lua_setglobal)(lua_State *L, const char *name);
	LUA53_API void  (lua_settable)(lua_State *L, int idx);
	LUA53_API void  (lua_setfield)(lua_State *L, int idx, const char *k);
	LUA53_API void  (lua_seti)(lua_State *L, int idx, lua_Integer n);
	LUA53_API void  (lua_rawset)(lua_State *L, int idx);
	LUA53_API void  (lua_rawseti)(lua_State *L, int idx, lua_Integer n);
	LUA53_API void  (lua_rawsetp)(lua_State *L, int idx, const void *p);
	LUA53_API int   (lua_setmetatable)(lua_State *L, int objindex);
	LUA53_API void  (lua_setuservalue)(lua_State *L, int idx);

	LUA53_API void  (lua_callk)(lua_State *L, int nargs, int nresults,
		lua_KContext ctx, lua_KFunction k);

	LUA53_API int   (lua_pcallk)(lua_State *L, int nargs, int nresults, int errfunc,
		lua_KContext ctx, lua_KFunction k);

	LUA53_API int   (lua_load)(lua_State *L, lua_Reader reader, void *dt,
		const char *chunkname, const char *mode);

	LUA53_API int (lua_dump)(lua_State *L, lua_Writer writer, void *data, int strip);

	LUA53_API int  (lua_yieldk)(lua_State *L, int nresults, lua_KContext ctx,
		lua_KFunction k);
	LUA53_API int  (lua_resume)(lua_State *L, lua_State *from, int narg);
	LUA53_API int  (lua_status)(lua_State *L);
	LUA53_API int (lua_isyieldable)(lua_State *L);

	LUA53_API int (lua_gc)(lua_State *L, int what, int data);

	LUA53_API int   (lua_error)(lua_State *L);

	LUA53_API int   (lua_next)(lua_State *L, int idx);

	LUA53_API void  (lua_concat)(lua_State *L, int n);
	LUA53_API void  (lua_len)(lua_State *L, int idx);

	LUA53_API size_t(lua_stringtonumber) (lua_State *L, const char *s);

	LUA53_API lua_Alloc(lua_getallocf) (lua_State *L, void **ud);
	LUA53_API void      (lua_setallocf)(lua_State *L, lua_Alloc f, void *ud);

	typedef struct lua_Debug lua_Debug;  /* activation record */


	/* Functions to be called by the debugger in specific events */
	typedef void(*lua_Hook) (lua_State *L, lua_Debug *ar);


	LUA53_API int (lua_getstack)(lua_State *L, int level, lua_Debug *ar);
	LUA53_API int (lua_getinfo)(lua_State *L, const char *what, lua_Debug *ar);
	LUA53_API const char *(lua_getlocal)(lua_State *L, const lua_Debug *ar, int n);
	LUA53_API const char *(lua_setlocal)(lua_State *L, const lua_Debug *ar, int n);
	LUA53_API const char *(lua_getupvalue)(lua_State *L, int funcindex, int n);
	LUA53_API const char *(lua_setupvalue)(lua_State *L, int funcindex, int n);

	LUA53_API void *(lua_upvalueid)(lua_State *L, int fidx, int n);
	LUA53_API void  (lua_upvaluejoin)(lua_State *L, int fidx1, int n1,
		int fidx2, int n2);

	LUA53_API void (lua_sethook)(lua_State *L, lua_Hook func, int mask, int count);
	LUA53_API lua_Hook(lua_gethook) (lua_State *L);
	LUA53_API int (lua_gethookmask)(lua_State *L);
	LUA53_API int (lua_gethookcount)(lua_State *L);


	struct lua_Debug {
		int event;
		const char *name;	/* (n) */
		const char *namewhat;	/* (n) 'global', 'local', 'field', 'method' */
		const char *what;	/* (S) 'Lua', 'C', 'main', 'tail' */
		const char *source;	/* (S) */
		int currentline;	/* (l) */
		int linedefined;	/* (S) */
		int lastlinedefined;	/* (S) */
		unsigned char nups;	/* (u) number of upvalues */
		unsigned char nparams;/* (u) number of parameters */
		char isvararg;        /* (u) */
		char istailcall;	/* (t) */
		char short_src[LUA_IDSIZE]; /* (S) */
		/* private part */
		struct CallInfo *i_ci;  /* active function */
	};

}

#endif
