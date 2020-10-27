#ifndef lconfig51_h
#define lconfig51_h

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef __GNUC__
#define LUA51_API extern "C" __attribute__ ((dllexport))
#else
#define LUA51_API extern "C" __declspec(dllexport)
#endif
#else
#if __GNUC__ >= 4
#define LUA51_API extern "C"  __attribute__ ((visibility ("default")))
#else
#define LUA51_API extern "C" 
#endif
#endif

#endif
