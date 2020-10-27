#ifndef lauxlib53_h
#define lauxlib53_h

#include "lua.h"

namespace lua53
{
	LUA53_API void (luaL_checkversion_)(lua_State *L, lua_Number ver, size_t sz);
	LUA53_API int (luaL_getmetafield)(lua_State *L, int obj, const char *e);
	LUA53_API int (luaL_callmeta)(lua_State *L, int obj, const char *e);
	LUA53_API const char *(luaL_tolstring)(lua_State *L, int idx, size_t *len);
	LUA53_API int (luaL_argerror)(lua_State *L, int arg, const char *extramsg);
	LUA53_API const char *(luaL_checklstring)(lua_State *L, int arg,
															  size_t *l);
	LUA53_API const char *(luaL_optlstring)(lua_State *L, int arg,
											  const char *def, size_t *l);
	LUA53_API lua_Number(luaL_checknumber) (lua_State *L, int arg);
	LUA53_API lua_Number(luaL_optnumber) (lua_State *L, int arg, lua_Number def);

	LUA53_API lua_Integer(luaL_checkinteger) (lua_State *L, int arg);
	LUA53_API lua_Integer(luaL_optinteger) (lua_State *L, int arg,
											  lua_Integer def);

	LUA53_API void (luaL_checkstack)(lua_State *L, int sz, const char *msg);
	LUA53_API void (luaL_checktype)(lua_State *L, int arg, int t);
	LUA53_API void (luaL_checkany)(lua_State *L, int arg);

	LUA53_API int   (luaL_newmetatable)(lua_State *L, const char *tname);
	LUA53_API void  (luaL_setmetatable)(lua_State *L, const char *tname);
	LUA53_API void *(luaL_testudata)(lua_State *L, int ud, const char *tname);
	LUA53_API void *(luaL_checkudata)(lua_State *L, int ud, const char *tname);

	LUA53_API void (luaL_where)(lua_State *L, int lvl);
	LUA53_API int (luaL_error)(lua_State *L, const char *fmt, ...);

	LUA53_API int (luaL_checkoption)(lua_State *L, int arg, const char *def,
									   const char *const lst[]);

	LUA53_API int (luaL_fileresult)(lua_State *L, int stat, const char *fname);
	LUA53_API int (luaL_execresult)(lua_State *L, int stat);

	LUA53_API int (luaL_ref)(lua_State *L, int t);
	LUA53_API void (luaL_unref)(lua_State *L, int t, int ref);

	LUA53_API int (luaL_loadfilex)(lua_State *L, const char *filename,
												   const char *mode);

	LUA53_API int (luaL_loadbufferx)(lua_State *L, const char *buff, size_t sz,
									   const char *name, const char *mode);
	LUA53_API int (luaL_loadstring)(lua_State *L, const char *s);

	LUA53_API lua_State *(luaL_newstate)(void);

	LUA53_API lua_Integer(luaL_len) (lua_State *L, int idx);

	LUA53_API const char *(luaL_gsub)(lua_State *L, const char *s, const char *p,
													  const char *r);

	LUA53_API void (luaL_setfuncs)(lua_State *L, const luaL_Reg *l, int nup);

	LUA53_API int (luaL_getsubtable)(lua_State *L, int idx, const char *fname);

	LUA53_API void (luaL_traceback)(lua_State *L, lua_State *L1,
									  const char *msg, int level);

	LUA53_API void (luaL_requiref)(lua_State *L, const char *modname,
									 lua_CFunction openf, int glb);

	typedef struct luaL_Buffer {
	  char *b;  /* buffer address */
	  size_t size;  /* buffer size */
	  size_t n;  /* number of characters in buffer */
	  lua_State *L;
	  char initb[LUAL_BUFFERSIZE];  /* initial buffer */
	} luaL_Buffer;

	LUA53_API void (luaL_buffinit)(lua_State *L, luaL_Buffer *B);
	LUA53_API char *(luaL_prepbuffsize)(luaL_Buffer *B, size_t sz);
	LUA53_API void (luaL_addlstring)(luaL_Buffer *B, const char *s, size_t l);
	LUA53_API void (luaL_addstring)(luaL_Buffer *B, const char *s);
	LUA53_API void (luaL_addvalue)(luaL_Buffer *B);
	LUA53_API void (luaL_pushresult)(luaL_Buffer *B);
	LUA53_API void (luaL_pushresultsize)(luaL_Buffer *B, size_t sz);
	LUA53_API char *(luaL_buffinitsize)(lua_State *L, luaL_Buffer *B, size_t sz);
}

#endif


