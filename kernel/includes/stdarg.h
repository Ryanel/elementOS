#ifndef STDARG_H
#define STDARG_H
#if 0
// Credit Solar for PCDLIB source code
typedef __builtin_va_list va_list;
#define va_arg( ap, type ) ( __builtin_va_arg( ap, type ) )
#define va_copy( dest, src ) ( __builtin_va_copy( dest, src ) )
#define va_end( ap ) ( __builtin_va_end( ap ) )
#define va_start( ap, parmN ) ( __builtin_va_start( ap, parmN ) )
#else
#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;
#endif
#endif