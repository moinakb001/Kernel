#include "string.h"
namespace{
	uint8_t * message="FUCK OFF NOT IMPLEMENTED";
}
namespace std{
	void * memcpy( void  * destination, const void * source, uint32_t num ){
		uint8_t * destArr=(uint8_t * )destination;
		uint8_t * srcArr=(uint8_t * )source;
		for(uint32_t i=0;i<num;i++){
			destArr[i]=srcArr[i];
		}
		return destination;
	}
	
	void * memmove ( void * destination, const void * source, uint32_t num ){
		uint8_t * destArr=(uint8_t * )destination;
		uint8_t * srcArr=(uint8_t * )source;
		uint8_t buffer[num];
		for(uint32_t i=0;i<num;i++){
			buffer[i]=srcArr[i];
		}
		for(uint32_t i=0;i<num;i++){
			destArr[i]=buffer[i];
		}
		return destination;
	}
	
	uint8_t * strcpy ( uint8_t * destination, const uint8_t * source ){
		uint8_t * destArr=(uint8_t * )destination;
		uint8_t * srcArr=(uint8_t * )source;
		for(uint32_t i=0;srcArr[i]!=0;i++){
			destArr[i]=srcArr[i];
		}
		return destination;
	}
	
	uint8_t * strncpy ( uint8_t * destination, const uint8_t * source, uint32_t num ){
		uint8_t * destArr=(uint8_t * )destination;
		uint8_t * srcArr=(uint8_t * )source;
		for(uint32_t i=0;srcArr[i]!=0&&i<num;i++){
			destArr[i]=srcArr[i];
		}
		return destination;
	}

	
	
	uint8_t * strcat ( uint8_t * destination, const uint8_t * source ){
		uint8_t * destArr=(uint8_t * )destination;
		uint8_t * srcArr=(uint8_t * )source;
		uint32_t len=strlen(destination);
		for(uint32_t i=len;srcArr[i-len]!=0;i++){
			destArr[i]=srcArr[i-len];
		}
		return destination;
	}
	
	uint8_t * strncat ( uint8_t * destination, const uint8_t * source, uint32_t num ){
		uint8_t * destArr=(uint8_t * )destination;
		uint8_t * srcArr=(uint8_t * )source;
		uint32_t len=strlen(destination);
		for(uint32_t i=len;srcArr[i-len]!=0&&i<num+len;i++){
			destArr[i]=srcArr[i-len];
		}
		return destination;
	}

	
	
	int32_t memcmp ( const void * ptr1, const void * ptr2, uint32_t num ){
		uint32_t i=0;
		uint8_t * ptr1Arr=(uint8_t *)ptr1;
		uint8_t * ptr2Arr=(uint8_t *)ptr2;
		while(ptr1Arr[i]==ptr2Arr[i]&&i<num-1){
			i++;
		}
		return (int32_t)(ptr1Arr[i]-ptr2Arr[i]);
		
	}
	int32_t strcmp ( const uint8_t * str1, const uint8_t * str2 ){
		uint32_t i=0;
		uint8_t * ptr1Arr=str1;
		uint8_t * ptr2Arr=str1;
		while(ptr1Arr[i]==ptr2Arr[i]&&ptr1Arr[i]!=0&&ptr2Arr[i]!=0){
			i++;
		}
		return (int32_t)(ptr1Arr[i]-ptr2Arr[i]);
	}
	int32_t strcoll ( const uint8_t * str1, const uint8_t * str2 ){
		return strcmp(str1,str2);
	}
	int32_t strncmp ( const uint8_t * str1, const uint8_t * str2, uint32_t num ){
		uint32_t i=0;
		uint8_t * ptr1Arr=str1;
		uint8_t * ptr2Arr=str1;
		while(ptr1Arr[i]==ptr2Arr[i]&&i<num-1&&ptr1Arr[i]!=0&&ptr2Arr[i]!=0){
			i++;
		}
		return (int32_t)(ptr1Arr[i]-ptr2Arr[i]);
	}
	uint32_t strxfrm ( uint8_t * destination, const uint8_t * source, uint32_t num ){
		strncpy(destination,source, num);
		return strlen(destination);
	}

	
	
	void * memchr ( void * ptr, int32_t value, uint32_t num ){
		
	}
	uint8_t * strchr ( uint8_t * str, int32_t character ){
		
	}
	uint32_t strcspn ( const uint8_t * str1, const uint8_t * str2 ){
		
	}
	uint8_t * strpbrk ( uint8_t * str1, const uint8_t * str2 ){
		
	}
	uint8_t * strrchr ( uint8_t * str, int32_t character ){
		
	}
	uint32_t strspn ( const uint8_t * str1, const uint8_t * str2 ){
		
	}
	uint8_t * strstr ( uint8_t * str1, const uint8_t * str2 ){
		
	}
	uint8_t * strtok ( uint8_t * str, const uint8_t * delimiters ){
		
	}

	
	
	void * memset ( void * ptr, int32_t value, uint32_t num ){
		uint8_t act=(uint8_t)value;
		uint8_t * block=(uint8_t *)ptr;
		for(uint32_t i=0;i<num;i++){
			block[i]=act;
		}
		return ptr;
	}
	uint8_t * strerror ( int32_t errnum ){
		return message;
	}
	uint32_t strlen ( const uint8_t * str ){
		uint32_t i=0;
		while(str[i]!=0){
			i++;
		}
		return i;
	}
}