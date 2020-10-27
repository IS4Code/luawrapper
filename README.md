luawrapper
==========

This is a small dynamically-linked library that exports functions for the Lua 5.1 API but uses the Lua 5.3 API to execute the calls. Simply said, placing this module alongside Lua 5.3 library will allow using modules compiled for Lua 5.1.

## Features
All documented Lua 5.1 API functions are supported, with three exceptions:

* `lua_getfenv` and `lua_setfenv`. Since 5.2, environment is only a syntactical thing and functions have no dedicated environment.
* Functions that use `lua_Debug`. This structure is larger in 5.3 and cannot fit in the old one.
* Functions that use `luaL_Buffer`, for the same reason.

## Building
Use Visual Studio to build the project on Windows, or `make` on Linux.
