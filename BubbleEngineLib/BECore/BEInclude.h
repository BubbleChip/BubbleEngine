#pragma once

#include <assert.h>
#include <stdint.h>
#include <math.h>

#ifdef BEL_DYNAMIC
#   ifdef DLL_EXPORTS
#       define BEL_API __declspec(dllexport)
#   else
#       define BEL_API __declspec(dllimport)
#   endif
#else
#    define BEL_API
#endif

#define BE_NOOP								(void)0;
#define BEASSERT(expr)						assert(expr)
#define BEASSERT_DESC(expr, desc)			assert(((void)desc, expr))

#if defined(_DEBUG)
#	define BEASSERT_DEBUG(expr)				BEASSERT(expr)
#	define BEASSERT_DESC_DEBUG(expr, desc)	BEASSERT_DESC(expr, desc)
#else
#	define BEASSERT_DEBUG(expr)				BE_NOOP
#	define BEASSERT_DESC_DEBUG(expr, desc)	BE_NOOP
#endif