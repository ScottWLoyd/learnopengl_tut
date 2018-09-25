#ifndef _UTIL_H_
#define _UTIL_H_

#define ARRAY_COUNT(a) (sizeof((a))/sizeof((a)[0]))

static const char* read_entire_file(const char* file, bool binary = false);

#define CHECK_ERROR check_gl_error(__FILE__, __LINE__)
static void check_gl_error(const char* file, int line);

#endif
