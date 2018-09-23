#ifndef _UTIL_H_
#define _UTIL_H_

#define ARRAY_COUNT(a) (sizeof((a))/sizeof((a)[0]))

static const char* read_entire_file(const char* file, bool binary = false);

#endif
