#ifndef lauxlib51_h
#define lauxlib51_h

#include "lua.h"

namespace lua51
{
	LUA51_API void (luaI_openlib) (lua_State *L, const char *libname, const luaL_Reg *l, int nup);
	LUA51_API void (luaL_register) (lua_State *L, const char *libname, const luaL_Reg *l);
	LUA51_API int (luaL_getmetafield) (lua_State *L, int obj, const char *e);
	LUA51_API int (luaL_callmeta) (lua_State *L, int obj, const char *e);
	LUA51_API int (luaL_typerror) (lua_State *L, int narg, const char *tname);
	LUA51_API int (luaL_argerror) (lua_State *L, int numarg, const char *extramsg);
	LUA51_API const char *(luaL_checklstring) (lua_State *L, int numArg, size_t *l);
	LUA51_API const char *(luaL_optlstring) (lua_State *L, int numArg, const char *def, size_t *l);
	LUA51_API lua_Number (luaL_checknumber) (lua_State *L, int numArg);
	LUA51_API lua_Number (luaL_optnumber) (lua_State *L, int nArg, lua_Number def);

	LUA51_API lua_Integer (luaL_checkinteger) (lua_State *L, int numArg);
	LUA51_API lua_Integer (luaL_optinteger) (lua_State *L, int nArg, lua_Integer def);

	LUA51_API void (luaL_checkstack) (lua_State *L, int sz, const char *msg);
	LUA51_API void (luaL_checktype) (lua_State *L, int narg, int t);
	LUA51_API void (luaL_checkany) (lua_State *L, int narg);

	LUA51_API int   (luaL_newmetatable) (lua_State *L, const char *tname);
	LUA51_API void *(luaL_checkudata) (lua_State *L, int ud, const char *tname);

	LUA51_API void (luaL_where) (lua_State *L, int lvl);
	LUA51_API int (luaL_error) (lua_State *L, const char *fmt, ...);

	LUA51_API int (luaL_checkoption) (lua_State *L, int narg, const char *def, const char *const lst[]);

	LUA51_API int (luaL_ref) (lua_State *L, int t);
	LUA51_API void (luaL_unref) (lua_State *L, int t, int ref);

	LUA51_API int (luaL_loadfile) (lua_State *L, const char *filename);
	LUA51_API int (luaL_loadbuffer) (lua_State *L, const char *buff, size_t sz, const char *name);
	LUA51_API int (luaL_loadstring) (lua_State *L, const char *s);

	LUA51_API lua_State *(luaL_newstate) (void);


	LUA51_API const char *(luaL_gsub) (lua_State *L, const char *s, const char *p, const char *r);

	LUA51_API const char *(luaL_findtable) (lua_State *L, int idx, const char *fname, int szhint);

	typedef struct luaL_Buffer {
	  char *p;			/* current position in buffer */
	  int lvl;  /* number of strings in the stack (level) */
	  lua_State *L;
	  char buffer[LUAL_BUFFERSIZE];
	} luaL_Buffer;

	LUA51_API void (luaL_buffinit) (lua_State *L, luaL_Buffer *B);
	LUA51_API char *(luaL_prepbuffer) (luaL_Buffer *B);
	LUA51_API void (luaL_addlstring) (luaL_Buffer *B, const char *s, size_t l);
	LUA51_API void (luaL_addstring) (luaL_Buffer *B, const char *s);
	LUA51_API void (luaL_addvalue) (luaL_Buffer *B);
	LUA51_API void (luaL_pushresult) (luaL_Buffer *B);
}

#endif
