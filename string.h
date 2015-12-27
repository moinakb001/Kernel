#ifndef STRING_H
#define STRING_H
#include <stdint.h>
namespace std{
void * memcpy( void  * destination, const void * source, uint32_t num );
void * memmove ( void * destination, const void * source, uint32_t num );
uint8_t * strcpy ( uint8_t * destination, const uint8_t * source );
uint8_t * strncpy ( uint8_t * destination, const uint8_t * source, uint32_t num );

uint8_t * strcat ( uint8_t * destination, const uint8_t * source );
uint8_t * strncat ( uint8_t * destination, const uint8_t * source, uint32_t num );

int32_t memcmp ( const void * ptr1, const void * ptr2, uint32_t num );
int32_t strcmp ( const uint8_t * str1, const uint8_t * str2 );
int32_t strcoll ( const uint8_t * str1, const uint8_t * str2 );
int32_t strncmp ( const uint8_t * str1, const uint8_t * str2, uint32_t num );
uint32_t strxfrm ( uint8_t * destination, const uint8_t * source, uint32_t num );

void * memchr ( void * ptr, int32_t value, uint32_t num );
uint8_t * strchr ( uint8_t * str, int32_t character );
uint32_t strcspn ( const uint8_t * str1, const uint8_t * str2 );
uint8_t * strpbrk ( uint8_t * str1, const uint8_t * str2 );
uint8_t * strrchr ( uint8_t * str, int32_t character );
uint32_t strspn ( const uint8_t * str1, const uint8_t * str2 );
uint8_t * strstr ( uint8_t * str1, const uint8_t * str2 );
uint8_t * strtok ( uint8_t * str, const uint8_t * delimiters );

void * memset ( void * ptr, int32_t value, uint32_t num );
uint8_t * strerror ( int32_t errnum );
uint32_t strlen ( const uint8_t * str );
}
#endif