#pragma once

#include <enoki/jit.h>
#include <cstdarg>

/// Print a log message with the specified log level and message
extern void jit_log(LogLevel level, const char* fmt, ...);

/// Print a log message with the specified log level and message
extern void jit_vlog(LogLevel level, const char* fmt, va_list args);

/// Raise a std::runtime_error with the given message
[[noreturn]] extern void jit_raise(const char* fmt, ...);

/// Raise a std::runtime_error with the given message
[[noreturn]] extern void jit_vraise(const char* fmt, va_list args);

/// Immediately terminate the application due to a fatal internal error
[[noreturn]] extern void jit_fail(const char* fmt, ...);

/// Immediately terminate the application due to a fatal internal error
[[noreturn]] extern void jit_vfail(const char* fmt, va_list args);

/// Return and clear the log buffer
extern char *jit_log_buffer();

/// Convert a number of bytes into a human-readable string (returns static buffer!)
extern const char *jit_mem_string(size_t size);

/// Convert a time in microseconds into a human-readable string (returns static buffer!)
extern const char *jit_time_string(float us);

/// Return the number of microseconds since the previous timer() call
extern float timer();