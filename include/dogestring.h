#ifndef DOGESTRING_H
#define DOGESTRING_H

#include <stddef.h>

size_t stirng_strlen(const char* str);
bool string_isempty(const char* str);
char* string_strcpy(char* dest, const char* src);
char* string_strncpy(char* dest, const char* src, size_t n);
void* string_memcpy(void* dest, const void* src, size_t n);
void* string_memmove(void* dest, const void* src, size_t n);
char* string_combine(char* dest, const char* src);
char* string_commbinelimit(char* dest, const char* src, size_t n);
char* string_strcat(char* dest, const char* src);
char* string_strncat(char* dest, const char* src, size_t n);
bool string_strcmp(const char* string1, const char* string2);
bool string_startsWtih(const char* str, const char* prefix);

#endif
