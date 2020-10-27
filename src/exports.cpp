#include <stddef.h>
#include <stdarg.h>
#include <limits.h>
#include <stdio.h>

// Platform-specific

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dlfcn.h>
#endif

// Common shared Lua types

#define LUA_NUMBER double
#define LUA_INTEGER long long
#define LUA_UNSIGNED unsigned long long
#define LUA_KCONTEXT ptrdiff_t
#define LUA_IDSIZE 60
#define LUAL_BUFFERSIZE ((int)(0x80 * sizeof(void*) * sizeof(long long)))

typedef struct lua_State lua_State;
typedef LUA_NUMBER lua_Number;
typedef LUA_INTEGER lua_Integer;
typedef LUA_UNSIGNED lua_Unsigned;
typedef int(*lua_CFunction) (lua_State *L);
typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);
typedef int(*lua_Writer) (lua_State *L, const void* p, size_t sz, void* ud);
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);

typedef struct luaL_Reg {
	const char *name;
	lua_CFunction func;
} luaL_Reg;

// Lua API

#include "lua5.1/lua.h"
#include "lua5.1/lualib.h"
#include "lua5.1/lauxlib.h"

#include "lua5.3/lua.h"
#include "lua5.3/lualib.h"
#include "lua5.3/lauxlib.h"

#ifdef _WIN32
#define LIBNAME(s) #s".dll"
#else
#define LIBNAME(s) #s".so"
#endif

#ifndef LUA_MODULE
#define LUA_MODULE lua5.3
#endif

constexpr const char *not_supported = "Lua API function %s is not supported";

LUA51_API int __error_func(lua_State *L)
{
	return lua51::luaL_error(L, "Lua API function is missing");
}

#ifdef _WIN32
struct lib_loader
{
	HMODULE handle;

	lib_loader(const char *name)
	{
		handle = LoadLibrary(name);
	}

	~lib_loader()
	{
		FreeLibrary(handle);
		handle = nullptr;
	}
};

static HMODULE GetModule()
{
	static lib_loader loader(LIBNAME(LUA_MODULE));
	return loader.handle;
}

template <class FPtr, FPtr Func>
static FPtr GetFunction(const char *name)
{
	static FPtr ptr = reinterpret_cast<FPtr>(GetProcAddress(GetModule(), name));
	if(!ptr) return reinterpret_cast<FPtr>(&__error_func);
	return ptr;
}
#else
struct lib_loader
{
	void *handle;

	lib_loader(const char *name)
	{
		handle = dlopen(name, RTLD_NOW | RTLD_GLOBAL);
	}

	~lib_loader()
	{
		dlclose(handle);
		handle = nullptr;
	}
};

static void *GetModule()
{
	static lib_loader loader(LIBNAME(LUA_MODULE));
	return loader.handle;
}

template <class FPtr, FPtr Func>
static FPtr GetFunction(const char *name)
{
	static FPtr ptr = reinterpret_cast<FPtr>(dlsym(GetModule(), name));
	if(!ptr) return reinterpret_cast<FPtr>(&__error_func);
	return ptr;
}
#endif

#define lua53(func, ...) GetFunction<decltype(&lua53::func), &lua53::func>(#func)(__VA_ARGS__)

namespace lua51
{
	LUA51_API lua_State *(lua_newstate)(lua_Alloc f, void *ud)
	{
		return lua53(lua_newstate, f, ud);
	}

	LUA51_API void (lua_close)(lua_State *L)
	{
		return lua53(lua_close, L);
	}

	LUA51_API lua_State *(lua_newthread)(lua_State *L)
	{
		return lua53(lua_newthread, L);
	}

	LUA51_API lua_CFunction(lua_atpanic) (lua_State *L, lua_CFunction panicf)
	{
		return lua53(lua_atpanic, L, panicf);
	}

	LUA51_API int (lua_gettop)(lua_State *L)
	{
		return lua53(lua_gettop, L);
	}

	LUA51_API void (lua_settop)(lua_State *L, int idx)
	{
		return lua53(lua_settop, L, idx);
	}

	LUA51_API void (lua_pushvalue)(lua_State *L, int idx)
	{
		return lua53(lua_pushvalue, L, idx);
	}

	LUA51_API void (lua_remove)(lua_State *L, int idx)
	{
		return (lua53(lua_rotate, L, (idx), -1), lua53(lua_settop, L, -2));
	}

	LUA51_API void (lua_insert)(lua_State *L, int idx)
	{
		return lua53(lua_rotate, L, (idx), 1);
	}

	LUA51_API void (lua_replace)(lua_State *L, int idx)
	{
		return (lua53(lua_copy, L, -1, (idx)), lua53(lua_settop, L, -2));
	}

	LUA51_API int (lua_checkstack)(lua_State *L, int sz)
	{
		return lua53(lua_checkstack, L, sz);
	}

	LUA51_API void (lua_xmove)(lua_State *from, lua_State *to, int n)
	{
		return lua53(lua_xmove, from, to, n);
	}

	LUA51_API int (lua_isnumber)(lua_State *L, int idx)
	{
		return lua53(lua_isnumber, L, idx);
	}

	LUA51_API int (lua_isstring)(lua_State *L, int idx)
	{
		return lua53(lua_isstring, L, idx);
	}

	LUA51_API int (lua_iscfunction)(lua_State *L, int idx)
	{
		return lua53(lua_iscfunction, L, idx);
	}

	LUA51_API int (lua_isuserdata)(lua_State *L, int idx)
	{
		return lua53(lua_isuserdata, L, idx);
	}

	LUA51_API int (lua_type)(lua_State *L, int idx)
	{
		return lua53(lua_type, L, idx);
	}

	LUA51_API const char *(lua_typename)(lua_State *L, int tp)
	{
		return lua53(lua_typename, L, tp);
	}

	LUA51_API int (lua_equal)(lua_State *L, int idx1, int idx2)
	{
		return lua53(lua_compare, L, (idx1), (idx2), 0);
	}

	LUA51_API int (lua_rawequal)(lua_State *L, int idx1, int idx2)
	{
		return lua53(lua_rawequal, L, idx1, idx2);
	}

	LUA51_API int (lua_lessthan)(lua_State *L, int idx1, int idx2)
	{
		return lua53(lua_compare, L, (idx1), (idx2), 1);
	}

	LUA51_API lua_Number(lua_tonumber) (lua_State *L, int idx)
	{
		return lua53(lua_tonumberx, L, (idx), nullptr);
	}

	LUA51_API lua_Integer(lua_tointeger) (lua_State *L, int idx)
	{
		return lua53(lua_tointegerx, L, (idx), nullptr);
	}

	LUA51_API int (lua_toboolean)(lua_State *L, int idx)
	{
		return lua53(lua_toboolean, L, idx);
	}

	LUA51_API const char *(lua_tolstring)(lua_State *L, int idx, size_t *len)
	{
		return lua53(lua_tolstring, L, idx, len);
	}

	LUA51_API size_t(lua_objlen) (lua_State *L, int idx)
	{
		return lua53(lua_rawlen, L, idx);
	}

	LUA51_API lua_CFunction(lua_tocfunction) (lua_State *L, int idx)
	{
		return lua53(lua_tocfunction, L, idx);
	}

	LUA51_API void	 *(lua_touserdata)(lua_State *L, int idx)
	{
		return lua53(lua_touserdata, L, idx);
	}

	LUA51_API lua_State *(lua_tothread)(lua_State *L, int idx)
	{
		return lua53(lua_tothread, L, idx);
	}

	LUA51_API const void *(lua_topointer)(lua_State *L, int idx)
	{
		return lua53(lua_topointer, L, idx);
	}

	LUA51_API void (lua_pushnil)(lua_State *L)
	{
		return lua53(lua_pushnil, L);
	}

	LUA51_API void (lua_pushnumber)(lua_State *L, lua_Number n)
	{
		return lua53(lua_pushnumber, L, n);
	}

	LUA51_API void (lua_pushinteger)(lua_State *L, lua_Integer n)
	{
		return lua53(lua_pushinteger, L, n);
	}

	LUA51_API void (lua_pushlstring)(lua_State *L, const char *s, size_t l)
	{
		lua53(lua_pushlstring, L, s, l);
	}

	LUA51_API void (lua_pushstring)(lua_State *L, const char *s)
	{
		lua53(lua_pushstring, L, s);
	}

	LUA51_API const char *(lua_pushvfstring)(lua_State *L, const char *fmt, va_list argp)
	{
		return lua53(lua_pushvfstring, L, fmt, argp);
	}

	LUA51_API const char *(lua_pushfstring)(lua_State *L, const char *fmt, ...)
	{
		va_list argp;
		va_start(argp, fmt);
		auto ret = lua_pushvfstring(L, fmt, argp);
		va_end(argp);
		return ret;
	}

	LUA51_API void (lua_pushcclosure)(lua_State *L, lua_CFunction fn, int n)
	{
		return lua53(lua_pushcclosure, L, fn, n);
	}

	LUA51_API void (lua_pushboolean)(lua_State *L, int b)
	{
		return lua53(lua_pushboolean, L, b);
	}

	LUA51_API void (lua_pushlightuserdata)(lua_State *L, void *p)
	{
		return lua53(lua_pushlightuserdata, L, p);
	}

	LUA51_API int (lua_pushthread)(lua_State *L)
	{
		return lua53(lua_pushthread, L);
	}

	LUA51_API void (lua_gettable)(lua_State *L, int idx)
	{
		lua53(lua_gettable, L, idx);
	}

	LUA51_API void (lua_getfield)(lua_State *L, int idx, const char *k)
	{
		lua53(lua_getfield, L, idx, k);
	}

	LUA51_API void (lua_rawget)(lua_State *L, int idx)
	{
		lua53(lua_rawget, L, idx);
	}

	LUA51_API void (lua_rawgeti)(lua_State *L, int idx, int n)
	{
		lua53(lua_rawgeti, L, idx, n);
	}

	LUA51_API void (lua_createtable)(lua_State *L, int narr, int nrec)
	{
		return lua53(lua_createtable, L, narr, nrec);
	}

	LUA51_API void *(lua_newuserdata)(lua_State *L, size_t sz)
	{
		return lua53(lua_newuserdata, L, sz);
	}

	LUA51_API int (lua_getmetatable)(lua_State *L, int objindex)
	{
		return lua53(lua_getmetatable, L, objindex);
	}

	LUA51_API void (lua_getfenv)(lua_State *L, int idx)
	{
		lua53(luaL_error, L, not_supported, "lua_getfenv");
		//return lua53(lua_getfenv, L, idx);
	}

	LUA51_API void (lua_settable)(lua_State *L, int idx)
	{
		return lua53(lua_settable, L, idx);
	}

	LUA51_API void (lua_setfield)(lua_State *L, int idx, const char *k)
	{
		return lua53(lua_setfield, L, idx, k);
	}

	LUA51_API void (lua_rawset)(lua_State *L, int idx)
	{
		return lua53(lua_rawset, L, idx);
	}

	LUA51_API void (lua_rawseti)(lua_State *L, int idx, int n)
	{
		return lua53(lua_rawseti, L, idx, n);
	}

	LUA51_API int (lua_setmetatable)(lua_State *L, int objindex)
	{
		return lua53(lua_setmetatable, L, objindex);
	}

	LUA51_API int (lua_setfenv)(lua_State *L, int idx)
	{
		return lua53(luaL_error, L, not_supported, "lua_setfenv");
		//return lua53(lua_setfenv, L, idx);
	}

	LUA51_API void (lua_call)(lua_State *L, int nargs, int nresults)
	{
		return lua53(lua_callk, L, nargs, nresults, 0, nullptr);
	}

	LUA51_API int (lua_pcall)(lua_State *L, int nargs, int nresults, int errfunc)
	{
		return lua53(lua_pcallk, L, nargs, nresults, errfunc, 0, nullptr);
	}

	LUA51_API int (lua_cpcall)(lua_State *L, lua_CFunction func, void *ud)
	{
		return (lua53(lua_pushcclosure, L, (func), 0),
			lua53(lua_pushlightuserdata, L, (ud)),
			lua53(lua_pcallk, L, 1, 0, 0, 0, nullptr));
	}

	LUA51_API int (lua_load)(lua_State *L, lua_Reader reader, void *dt, const char *chunkname)
	{
		return lua53(lua_load, L, reader, dt, chunkname, nullptr);
	}

	LUA51_API int (lua_dump)(lua_State *L, lua_Writer writer, void *data)
	{
		return lua53(lua_dump, L, writer, data, 0);
	}

	LUA51_API int (lua_yield)(lua_State *L, int nresults)
	{
		return lua53(lua_yieldk, L, nresults, 0, nullptr);
	}

	LUA51_API int (lua_resume)(lua_State *L, int narg)
	{
		return lua53(lua_resume, L, nullptr, narg);
	}

	LUA51_API int (lua_status)(lua_State *L)
	{
		return lua53(lua_status, L);
	}

	LUA51_API int (lua_gc)(lua_State *L, int what, int data)
	{
		return lua53(lua_gc, L, what, data);
	}

	LUA51_API int (lua_error)(lua_State *L)
	{
		return lua53(lua_error, L);
	}

	LUA51_API int (lua_next)(lua_State *L, int idx)
	{
		return lua53(lua_next, L, idx);
	}

	LUA51_API void (lua_concat)(lua_State *L, int n)
	{
		return lua53(lua_concat, L, n);
	}

	LUA51_API lua_Alloc(lua_getallocf) (lua_State *L, void **ud)
	{
		return lua53(lua_getallocf, L, ud);
	}

	LUA51_API void lua_setallocf(lua_State *L, lua_Alloc f, void *ud)
	{
		return lua53(lua_setallocf, L, f, ud);
	}

	/*LUA51_API void lua_setlevel(lua_State *from, lua_State *to)
	{
		
	}*/

	LUA51_API int lua_getstack(lua_State *L, int level, lua_Debug *ar)
	{
		return lua53(luaL_error, L, not_supported, "lua_getstack");
		//return lua53(lua_getstack, L, level, ar);
	}

	LUA51_API int lua_getinfo(lua_State *L, const char *what, lua_Debug *ar)
	{
		return lua53(luaL_error, L, not_supported, "lua_getinfo");
		//return lua53(lua_getinfo, L, what, ar);
	}

	LUA51_API const char *lua_getlocal(lua_State *L, const lua_Debug *ar, int n)
	{
		return lua53(luaL_error, L, not_supported, "lua_getlocal"), nullptr;
		//return lua53(lua_getlocal, L, ar, n);
	}

	LUA51_API const char *lua_setlocal(lua_State *L, const lua_Debug *ar, int n)
	{
		return lua53(luaL_error, L, not_supported, "lua_setlocal"), nullptr;
		//return lua53(lua_setlocal, L, ar, n);
	}

	LUA51_API const char *lua_getupvalue(lua_State *L, int funcindex, int n)
	{
		return lua53(lua_getupvalue, L, funcindex, n);
	}

	LUA51_API const char *lua_setupvalue(lua_State *L, int funcindex, int n)
	{
		return lua53(lua_setupvalue, L, funcindex, n);
	}

	LUA51_API int lua_sethook(lua_State *L, lua_Hook func, int mask, int count)
	{
		return lua53(luaL_error, L, not_supported, "lua_sethook");
		//return lua53(lua_sethook, L, func, mask, count);
	}

	LUA51_API lua_Hook lua_gethook(lua_State *L)
	{
		return lua53(luaL_error, L, not_supported, "lua_gethook"), nullptr;
		//return lua53(lua_gethook, L);
	}

	LUA51_API int lua_gethookmask(lua_State *L)
	{
		return lua53(lua_gethookmask, L);
	}

	LUA51_API int lua_gethookcount(lua_State *L)
	{
		return lua53(lua_gethookcount, L);
	}

	LUA51_API int (luaopen_base)(lua_State *L)
	{
		return lua53(luaopen_base, L);
	}

	LUA51_API int (luaopen_table)(lua_State *L)
	{
		return lua53(luaopen_table, L);
	}

	LUA51_API int (luaopen_io)(lua_State *L)
	{
		return lua53(luaopen_io, L);
	}

	LUA51_API int (luaopen_os)(lua_State *L)
	{
		return lua53(luaopen_os, L);
	}

	LUA51_API int (luaopen_string)(lua_State *L)
	{
		return lua53(luaopen_string, L);
	}

	LUA51_API int (luaopen_math)(lua_State *L)
	{
		return lua53(luaopen_math, L);
	}

	LUA51_API int (luaopen_debug)(lua_State *L)
	{
		return lua53(luaopen_debug, L);
	}

	LUA51_API int (luaopen_package)(lua_State *L)
	{
		return lua53(luaopen_package, L);
	}

	LUA51_API void (luaL_openlibs)(lua_State *L)
	{
		return lua53(luaL_openlibs, L);
	}

	static int libsize(const luaL_Reg *l) {
		int size = 0;
		for(; l && l->name; l++) size++;
		return size;
	}

	static void luaL_pushmodule(lua_State *L, const char *modname, int sizehint)
	{
		luaL_findtable(L, (-1000000 - 1000), "_LOADED", 1);
		if(lua53(lua_getfield, L, -1, modname) != 5)
		{
			lua_remove(L, -2);
			lua_rawgeti(L, (-1000000 - 1000), 2);
			if(luaL_findtable(L, 0, modname, sizehint) != NULL)
			{
				luaL_error(L, "name conflict for module '%s'", modname);
			}
			lua_pushvalue(L, -1);
			lua_setfield(L, -3, modname);
		}
		lua_remove(L, -2);
	}

	LUA51_API void (luaL_openlib)(lua_State *L, const char *libname, const luaL_Reg *l, int nup)
	{
		if(libname)
		{
			luaL_pushmodule(L, libname, libsize(l));
			lua_insert(L, -(nup + 1));
		}
		if(l)
		{
			lua53(luaL_setfuncs, L, l, nup);
		}else{
			lua53(lua_settop, L, -nup-1);
		}
	}

	LUA51_API void (luaI_openlib)(lua_State *L, const char *libname, const luaL_Reg *l, int nup)
	{
		return luaL_openlib(L, libname, l, nup);
	}

	LUA51_API void (luaL_register)(lua_State *L, const char *libname, const luaL_Reg *l)
	{
		return luaL_openlib(L, libname, l, 0);
	}

	LUA51_API int (luaL_getmetafield)(lua_State *L, int obj, const char *e)
	{
		return lua53(luaL_getmetafield, L, obj, e);
	}

	LUA51_API int (luaL_callmeta)(lua_State *L, int obj, const char *e)
	{
		return lua53(luaL_callmeta, L, obj, e);
	}

	LUA51_API int (luaL_typerror)(lua_State *L, int narg, const char *tname)
	{
		const char *msg = lua53(lua_pushfstring, L, "%s expected, got %s",
			tname, lua53(lua_typename, L, lua53(lua_type, L, narg)));

		return luaL_argerror(L, narg, msg);
	}

	LUA51_API int (luaL_argerror)(lua_State *L, int numarg, const char *extramsg)
	{
		return lua53(luaL_argerror, L, numarg, extramsg);
	}

	LUA51_API const char *(luaL_checklstring)(lua_State *L, int numArg, size_t *l)
	{
		return lua53(luaL_checklstring, L, numArg, l);
	}

	LUA51_API const char *(luaL_optlstring)(lua_State *L, int numArg, const char *def, size_t *l)
	{
		return lua53(luaL_optlstring, L, numArg, def, l);
	}

	LUA51_API lua_Number(luaL_checknumber) (lua_State *L, int numArg)
	{
		return lua53(luaL_checknumber, L, numArg);
	}

	LUA51_API lua_Number(luaL_optnumber) (lua_State *L, int nArg, lua_Number def)
	{
		return lua53(luaL_optnumber, L, nArg, def);
	}

	LUA51_API lua_Integer(luaL_checkinteger) (lua_State *L, int numArg)
	{
		return lua53(luaL_checkinteger, L, numArg);
	}

	LUA51_API lua_Integer(luaL_optinteger) (lua_State *L, int nArg, lua_Integer def)
	{
		return lua53(luaL_optinteger, L, nArg, def);
	}

	LUA51_API void (luaL_checkstack)(lua_State *L, int sz, const char *msg)
	{
		return lua53(luaL_checkstack, L, sz, msg);
	}

	LUA51_API void (luaL_checktype)(lua_State *L, int narg, int t)
	{
		return lua53(luaL_checktype, L, narg, t);
	}

	LUA51_API void (luaL_checkany)(lua_State *L, int narg)
	{
		return lua53(luaL_checkany, L, narg);
	}

	LUA51_API int (luaL_newmetatable)(lua_State *L, const char *tname)
	{
		return lua53(luaL_newmetatable, L, tname);
	}

	LUA51_API void *(luaL_checkudata)(lua_State *L, int ud, const char *tname)
	{
		return lua53(luaL_checkudata, L, ud, tname);
	}

	LUA51_API void (luaL_where)(lua_State *L, int lvl)
	{
		return lua53(luaL_where, L, lvl);
	}

	LUA51_API int (luaL_error)(lua_State *L, const char *fmt, ...)
	{
		va_list argp;
		va_start(argp, fmt);
		luaL_where(L, 1);
		lua_pushvfstring(L, fmt, argp);
		va_end(argp);
		lua_concat(L, 2);
		return lua_error(L);
	}

	LUA51_API int (luaL_checkoption)(lua_State *L, int narg, const char *def, const char *const lst[])
	{
		return lua53(luaL_checkoption, L, narg, def, lst);
	}

	LUA51_API int (luaL_ref)(lua_State *L, int t)
	{
		return lua53(luaL_ref, L, t);
	}

	LUA51_API void (luaL_unref)(lua_State *L, int t, int ref)
	{
		return lua53(luaL_unref, L, t, ref);
	}

	LUA51_API int (luaL_loadfile)(lua_State *L, const char *filename)
	{
		return lua53(luaL_loadfilex, L, filename, nullptr);
	}

	LUA51_API int (luaL_loadbuffer)(lua_State *L, const char *buff, size_t sz, const char *name)
	{
		return lua53(luaL_loadbufferx, L, buff, sz, name, nullptr);
	}

	LUA51_API int (luaL_loadstring)(lua_State *L, const char *s)
	{
		return lua53(luaL_loadstring, L, s);
	}

	LUA51_API lua_State *(luaL_newstate)(void)
	{
		return lua53(luaL_newstate);
	}

	LUA51_API const char *(luaL_gsub)(lua_State *L, const char *s, const char *p, const char *r)
	{
		return lua53(luaL_gsub, L, s, p, r);
	}

	LUA51_API const char *(luaL_findtable)(lua_State *L, int idx, const char *fname, int szhint)
	{
		const char *e;
		if(idx) lua_pushvalue(L, idx);
		do {
			e = strchr(fname, '.');
			if(e == NULL) e = fname + strlen(fname);
			lua_pushlstring(L, fname, e - fname);
			if(lua53(lua_rawget, L, -2) == 0) {  /* no such field? */
				lua53(lua_settop, L, -2);  /* remove this nil */
				lua_createtable(L, 0, (*e == '.' ? 1 : szhint)); /* new table for field */
				lua_pushlstring(L, fname, e - fname);
				lua_pushvalue(L, -2);
				lua_settable(L, -4);  /* set new table into field */
			} else if(lua_type(L, -1) != 5) {  /* field has a non-table value? */
				lua53(lua_settop, L, -3);  /* remove table and value */
				return fname;  /* return problematic part of the name */
			}
			lua_remove(L, -2);  /* remove previous table */
			fname = e + 1;
		} while(*e == '.');
		return NULL;
	}

	LUA51_API void (luaL_buffinit)(lua_State *L, luaL_Buffer *B)
	{
		lua53(luaL_error, L, not_supported, "luaL_buffinit");
		//return lua53(luaL_buffinit, L, B);
	}

	LUA51_API char *(luaL_prepbuffer)(luaL_Buffer *B)
	{
		return lua53(luaL_error, B->L, not_supported, "luaL_prepbuffer"), nullptr;
		//return lua53(luaL_prepbuffer, B);
	}

	LUA51_API void (luaL_addlstring)(luaL_Buffer *B, const char *s, size_t l)
	{
		lua53(luaL_error, B->L, not_supported, "luaL_addlstring");
		//return lua53(luaL_addlstring, B, s, l);
	}

	LUA51_API void (luaL_addstring)(luaL_Buffer *B, const char *s)
	{
		lua53(luaL_error, B->L, not_supported, "luaL_addstring");
		//return lua53(luaL_addstring, B, s);
	}

	LUA51_API void (luaL_addvalue)(luaL_Buffer *B)
	{
		lua53(luaL_error, B->L, not_supported, "luaL_addvalue");
		//return lua53(luaL_addvalue, B);
	}

	LUA51_API void (luaL_pushresult)(luaL_Buffer *B)
	{
		lua53(luaL_error, B->L, not_supported, "luaL_pushresult");
		//return lua53(luaL_pushresult, B);
	}
}