#pragma once

#if _WIN32 || _WIN64
#define PLATFORM_WINDOWS
#else
#if __linux__
#define PLATFORM_LINUX
#elif __APPLE__
#define PLATFORM_MAC
#else
#error "Unable to determine platform!"
#endif
#endif

#ifdef PLATFORM_WINDOWS
#define FORCEINLINE __forceinline
#define FORCENOINLINE _declspec(noinline)
#ifdef REGEN_BUILD_LIB
#define REGEN_API __declspec(dllexport)
#else
#define REGEN_API __declspec(dllimport)
#endif
#elif defined PLATFORM_LINUX || defined PLATFORM_MAC
#define FORCEINLINE inline
// TODO: Define REGEN_API for these platforms
#endif


#ifndef U32_MAX
#ifdef PLATFORM_WINDOWS
#define U32_MAX 0xffffffffui32
#elif defined PLATFORM_MAC || defined PLATFORM_LINUX
#define U32_MAX 0xffffffff
#endif
#endif

#ifndef U64_MAX
#ifdef PLATFORM_WINDOWS
#define U64_MAX 0xffffffffffffffffui64
#elif defined PLATFORM_MAC || defined PLATFORM_LINUX
#define U64_MAX 0xffffffffffffffff
#endif
#endif

// Assertions
#define ASSERTIONS_ENABLED
#ifdef ASSERTIONS_ENABLED
#include <iostream>

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak();
#else
#define debugBreak() __asm { int 3 }
#endif

#define ASSERT(expr) { \
    if( expr ) { \
    } else { \
        reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
        debugBreak(); \
    } \
}

#define ASSERT_MSG(expr, message) { \
    if( expr ) { \
    } else { \
        reportAssertionFailure(#expr, message, __FILE__, __LINE__); \
        debugBreak(); \
    } \
}

#ifdef _DEBUG
#define ASSERT_DEBUG(expr) { \
    if( expr ) { \
    } else { \
        reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
        debugBreak(); \
    } \
}
#else
#define ASSERT_DEBUG(expr) // Does nothing at all
#endif

FORCEINLINE void reportAssertionFailure( const char* expression, const char* message, const char* file, int line ) {
    std::cerr << "Assertion Failure: " << expression << ", message: '" << message << "', in file: " << file << ", line: " << line << "\n";
}

#else
#define ASSERT(expr) // Does nothing at all
#define ASSERT_MSG(expr, message) // Does nothing at all
#define ASSERT_DEBUG(expr) // Does nothing at all
#endif
