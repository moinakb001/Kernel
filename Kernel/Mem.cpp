#include "kmem.h"

namespace Kernel{
#define mem_magic 0x4F
#pragma pack(1)
	typedef struct{
		void * next;
		void * prev;
		uint8_t used;
		uint8_t magic;
	} memptr_t;

#pragma section("end",read,write);
	__declspec(allocate("end")) memptr_t initPtrMem;
	void initMem(){

		initPtrMem.used = 0;
		initPtrMem.magic = mem_magic;
		memptr_t * en = (memptr_t *)0xA00000;
		en->next = &initPtrMem;
		en->used = 1;
		en->magic = mem_magic;
		en->prev = &initPtrMem;
		initPtrMem.next = en;
		initPtrMem.prev = en;
	}
	int Num(){
		int res = 0;
		memptr_t * curr = &initPtrMem;
		do{
			res++;
			curr =(memptr_t *) curr->next;
		} while (((size_t)curr != (size_t)&initPtrMem));
		return res;
}
	char * ras = "1234567890abcdefghij";
	int a = 0;
	void * malloc(size_t size){
		unsigned short *vidmem = (unsigned short *)0xB8000;
		memptr_t * curr = &initPtrMem;
		char t[11];
		do
		{
			
			
			if (curr->used == 0&&curr->magic==mem_magic){
				
			if ((size_t)curr < (size_t)curr->next){
					//vidmem[2] = 'a';
					if ((size_t)curr->next - (size_t)curr >= size + sizeof(memptr_t)){
						curr->used = 1;
						//vidmem[7] = ras[a] | (ras[a] << 8);
						if ((size_t)curr->next - (size_t)curr >= size + 2 * sizeof(memptr_t) + 1){
							memptr_t * eme = (memptr_t *)((size_t)curr + sizeof(memptr_t) + size);
							eme->magic = mem_magic;
							eme->used = 0;
							eme->next = curr->next;
							eme->prev = curr;
							curr->next = eme;
						}

						a = (a + 1) % 20;
						return (void *)(&curr[1]);
					}
				}
			}
			curr = (memptr_t *)curr->next;
		} while ((size_t)curr != (size_t)&initPtrMem);
		
		
		return 0;
	}

	//NOT USED UNTIL FIXED
	char merge(memptr_t * ptr){
		char num = 0;
		if (((memptr_t *)ptr->next)->used == 0 && ptr->used == 0){
			ptr->next = ((memptr_t *)ptr->next)->next;
			((memptr_t *)(((memptr_t *)ptr->next)->next))->prev = ptr;
			((memptr_t *)ptr->next)->magic = 0;
			num += 1;
		}
		if (((memptr_t *)ptr->prev)->used == 0 && ptr->used == 0){
			((memptr_t *)ptr->prev)->next = ((memptr_t *)ptr->next);
			((memptr_t *)(((memptr_t *)ptr->next)))->prev = ((memptr_t *)ptr->prev);
			((memptr_t *)ptr)->magic = 0;
			num += 2;
		}
		return "0123"[num];
	}
	//NOP FOR NOW
	//DONT CHANGE UNTIL KNOW WHATS WRONG
	void free(void * loc){
		unsigned short *vidmem = (unsigned short *)0xB8000;
		char aa[2];
		memptr_t * ptr = (memptr_t *)(((size_t)loc) - sizeof(memptr_t));
		if (ptr->magic == mem_magic){
			ptr->used = 0;
			//aa[1]=merge(ptr);
			//merge((memptr_t *)(ptr->prev));
			vidmem[7] = aa[1]| (ras[a] << 8);
		}
		a = (a + 1) % 20;

	}
}