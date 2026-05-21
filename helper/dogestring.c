// include files
#include "../include/dogestring.h"
#include <dogebool.h>
#include <stddef.h>
#include <stdint.h>

size_t string_strlen(const char* str) {
	const char* string = str;
	while (*string) string++;
	return (size_t)(string - str);
}

// check if the string is completely empty, the null terminator (\0) doesn't
// count
bool string_isempty(const char* str) {
	return (!str || !*str) ? true : false;
}

// copy a string
char* string_strcpy(char* dest, const char* src) {
	char* d = dest;
	while ((*d++ = *src++));
	return dest;
}

// copy a string with a limit of n
char* string_strncpy(char* dest, const char* src, size_t n) {
	size_t i;
	
	for (i = 0; i < n && src[i] != '\0'; i++) {
		dest[i] = src[i];
	}
	for (; i < n; i++) {
		dest[i] = '\0';
	}
	
	return dest;
}


// copy pure memory
void* string_memcopy(void* dest, const void* src, size_t n) {
	char* d = (char*)dest;
	const char* s = (const char*)src;
	while (n--) *d++ = *s++;
	return dest;
}

// move pure memory
void* string_memmove(void* dest, const void* src, size_t n) {
	char* d = (char*)dest;
	const char* s = (const char*)src;
	if (d < s) { 
		while (n--) *d++ = *s++;
	} else {
		d += n;
		s+= n;
		while (n--) *--d = *--s;
	}
	return dest;
}

// combine strings
char* string_combine(char* dest, const char* src) {
	char* d = dest;
	while (*d) d++;
	while ((*d++ = *src++));
	return dest;
}

// combine strings with a limit on n
char* string_combinelimit(char* dest, const char* src, size_t n) {
	char* d = dest;
	while (*d) d++;
	while (n-- && *src) *d++ = *src++;
	*d = '\0';
	return dest;
}

// alias so other people wont go insane
char* string_strcat(char* dest, const char* src) {
	char* d = dest;
	while (*d) d++;
	while ((*d++ = *src++));
	return dest;
}

// compare strings
bool string_strcmp(const char* string1, const char* string2) {
	while (*string1 && (*string1 == *string2)) {
		string1++;
		string2++;
	}
	int return_value = *(unsigned char*)string1 - *(unsigned char*)string2;
	if (return_value == 0) { return true; }
	else { return false; }
}

bool string_startsWith(const char* str, const char* prefix) {
    while (*prefix && *str == *prefix) ++str, ++prefix;
    return *prefix == 0;
}
