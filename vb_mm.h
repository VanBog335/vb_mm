/*
	vanbog_memory_manager -- v0.8.0 -- https://github.com/VanBog335
	to use, do this:
	```c
	#define VB_MM_IMPLEMENTATION
	#include "vb_mm.h"
	```
	yes, like in stb libs

	example:
	```c
	#define VB_MM_IMPLEMENTATION
	#include "vb_mm.h"

	int main()
	{
		char *a = vb_alloc(16);
		a = vb_realloc(a, 8);
		vb_free(a);

		vb_da_ptr_destroy();
		return 0;
	}
	```
*/
#ifndef VB_MM_H_
#define VB_MM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifndef VB_MEMALLOC
#include <stdlib.h>
#define VB_MEMALLOC malloc
#endif /* VB_MEMALLOC */

#ifndef VB_MEMREALLOC
#include <stdlib.h>
#define VB_MEMREALLOC realloc
#endif /* VB_MEMREALLOC */

#ifndef VB_MEMFREE
#include <stdlib.h>
#define VB_MEMFREE free
#endif /* VB_MEMFREE */

void *vb_alloc(size_t size);
void *vb_realloc(void *p, size_t newsize);
void vb_free(void *p);
void vb_freeall();
void vb_da_ptr_destroy();
void vb_printPoints();

#endif /* VB_MM_H_ */


#ifdef VB_MM_IMPLEMENTATION

#define vbmm_da_append(xs, x)\
	do {\
		if ((xs)->count >= (xs)->cap) {\
			(xs)->cap = (xs)->cap == 0 ? 4 : (xs)->cap*2;\
			(xs)->items = realloc((xs)->items, (xs)->cap*sizeof(*(xs)->items));\
		}\
		(xs)->items[(xs)->count++] = (x);\
	} while (0)

typedef struct {
    void **items;
    size_t count;
    size_t cap;
} vb_da_ptrptr_t;

vb_da_ptrptr_t vb_PtrArray = (vb_da_ptrptr_t){0};

void *vb_alloc(size_t size)
{
	void *p = VB_MEMALLOC(size);
	if (!p) return 0;
	vbmm_da_append(&vb_PtrArray, p);
	return p;
}

void *vb_realloc(void *p, size_t newsize)
{
	void *oldp = p;
	void *newp = VB_MEMREALLOC(p, newsize);

	for (size_t i = 0; i < vb_PtrArray.count; i++){
		if (vb_PtrArray.items[i] == oldp){
			vb_PtrArray.items[i] = newp;
			break;
		}
	}

	return newp;
}

void vb_free(void *p)
{
	for (size_t i = 0; i < vb_PtrArray.count; i++) {
		if (vb_PtrArray.items[i] == p) {
			vb_PtrArray.count--;
			vb_PtrArray.items[i] = vb_PtrArray.items[vb_PtrArray.count]; // Replace with last element
			vb_PtrArray.items[vb_PtrArray.count] = NULL;
			break;
		}
	}
	VB_MEMFREE(p);
}

void vb_freeall()
{
	for (size_t i = 0; i < vb_PtrArray.count; i++){
		if (vb_PtrArray.items[i] != 0){
			VB_MEMFREE(vb_PtrArray.items[i]);
			vb_PtrArray.items[i] = NULL;
		}
	}
	vb_PtrArray.count = 0;
}

void vb_da_ptr_destroy() {
	vb_freeall();
	VB_MEMFREE(vb_PtrArray.items);
	vb_PtrArray = (vb_da_ptrptr_t){0};
}

void vb_printPoints()
{
	printf("-------DEBUG-------\n");
	for (size_t i = 0; i < vb_PtrArray.cap; i++){
		printf("%zX. %p\n", i, vb_PtrArray.items[i]);
	}
	printf("-------DEBUG--------\n");
}

#endif /* VB_MM_IMPLEMENTATION */
