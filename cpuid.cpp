
#include "fecpp.h"

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace fecpp {

bool has_sse2()
{
#if defined(_MSC_VER)
   // MSVC on x64 always has SSE2 support
   #if defined(_M_X64) || defined(_M_AMD64)
   return true;
   #else
   // For 32-bit MSVC, assume no SSE2 for now
   return false;
   #endif
#else
   // GCC/Clang: use runtime CPU detection
   #if defined(__builtin_cpu_supports)
   return __builtin_cpu_supports("sse2");
   #else
   // Fallback for older compilers: assume SSE2 on x86_64
   #if defined(__x86_64__) || defined(__amd64__) || defined(_AMD64__) || defined(_M_X64)
   return true;
   #else
   return false;
   #endif
   #endif
#endif
}

bool has_ssse3()
{
#if defined(_MSC_VER)
   // MSVC: check if SSSE3 is enabled via compiler defines
   #if defined(__SSSE3__)
   return true;
   #else
   return false;
   #endif
#else
   // GCC/Clang: use runtime CPU detection
   #if defined(__builtin_cpu_supports)
   return __builtin_cpu_supports("ssse3");
   #else
   // Fallback for older compilers: check if SSSE3 is enabled
   #if defined(__SSSE3__)
   return true;
   #else
   return false;
   #endif
   #endif
#endif
}

}
