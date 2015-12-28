#ifndef STRING_H
#define STRING_H
#include <stdint.h>

extern "C" void * memcpy( void  * destination,  void * source, uint32_t num );
extern "C" void * memmove ( void * destination,  void * source, uint32_t num );
extern "C" uint8_t * strcpy ( uint8_t * destination,  uint8_t * source );
extern "C" uint8_t * strncpy ( uint8_t * destination,  uint8_t * source, uint32_t num );

extern "C" uint8_t * strcat ( uint8_t * destination,  uint8_t * source );
extern "C" uint8_t * strncat ( uint8_t * destination,  uint8_t * source, uint32_t num );

extern "C" int32_t memcmp (  void * ptr1,  void * ptr2, uint32_t num );
extern "C" int32_t strcmp (  uint8_t * str1,  uint8_t * str2 );
extern "C" int32_t strcoll (  uint8_t * str1,  uint8_t * str2 );
extern "C" int32_t strncmp (  uint8_t * str1,  uint8_t * str2, uint32_t num );
extern "C" uint32_t strxfrm ( uint8_t * destination,  uint8_t * source, uint32_t num );

extern "C" void * memchr ( void * ptr, int32_t value, uint32_t num );
extern "C" uint8_t * strchr ( uint8_t * str, int32_t character );
extern "C" uint32_t strcspn (  uint8_t * str1,  uint8_t * str2 );
extern "C" uint8_t * strpbrk ( uint8_t * str1,  uint8_t * str2 );
extern "C" uint8_t * strrchr ( uint8_t * str, int32_t character );
extern "C" uint32_t strspn (  uint8_t * str1,  uint8_t * str2 );
extern "C" uint8_t * strstr ( uint8_t * str1,  uint8_t * str2 );
extern "C" uint8_t * strtok ( uint8_t * str,  uint8_t * delimiters );

extern "C" void * memset ( void * ptr, int32_t value, uint32_t num );
extern "C" uint8_t * strerror ( int32_t errnum );
extern "C" uint32_t strlen (  uint8_t * str );

#endif