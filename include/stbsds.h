#pragma once

#include <stdarg.h>

#ifdef __SDS_H
#define __SDS sds
#else
#define __SDS char *
#endif

#if defined(__has_attribute)
#if __has_attribute(format)
#define __FORMAT(fmt, va) __attribute__((format(printf, fmt, va)))
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

__SDS sdsstbcatprintf(__SDS s, const char *fmt, ...) __FORMAT(2, 3);
__SDS sdsstbcatvprintf(__SDS s, const char *fmt, va_list va);

#ifdef __cplusplus
}
#endif
