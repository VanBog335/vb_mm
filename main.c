#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define VB_MM_IMPLEMENTATION
#include "vb_mm.h"

int main()
{
	vb_da_ptr_init();
	
	char *a1, *a2, *a3;
	a1 = a2 = a3 = NULL;
	
	puts("ut 1");
	vb_printPoints();
	a1 = vb_alloc(16);
	vb_printPoints();
	vb_free(a1);
	vb_printPoints();
	a1 = a2 = a3 = NULL;

	puts("\nut 2");
	a1 = vb_alloc(16);
	a2 = vb_alloc(32);
	vb_printPoints();
	vb_freeall();
	vb_printPoints();
	a1 = a2 = a3 = NULL;

	puts("\nut 3");
	a1 = vb_alloc(16);
	a2 = vb_alloc(32);
	a3 = vb_alloc(32);
	vb_printPoints();
	vb_free(a2);
	vb_printPoints();
	vb_freeall();
	vb_printPoints();
	a1 = a2 = a3 = NULL;
	
	puts("\nut 4");
	a1 = vb_alloc(16);
	strncpy(a1, "smthn2281234567890", 15);
	puts(a1);
	vb_printPoints();
	a1 = vb_realloc(a1, 8);
	a1[7] = 0;
	vb_printPoints();
	puts(a1);
	a1 = a2 = a3 = NULL;
	vb_freeall();
	vb_printPoints();


	vb_freeall();
	vb_da_ptr_destroy();
}
