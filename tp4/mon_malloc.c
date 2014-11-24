#include <stdio.h>
#include "mon_malloc.h"

static int init = 0;


unsigned int get_int(void *ptr) 
{
	return (*((unsigned int*) ptr));
}


void set_int(void *ptr, unsigned int val)
{
	(*((unsigned int*) ptr)) = val;
}

void set_chunk(chunk *c, unsigned char *ptr)
{
	set_int(ptr, c->free);
	set_int(ptr + sizeof(unsigned int), c->size);
	set_int(ptr + c->size - sizeof(unsigned int), c->size);
}

void get_chunk(chunk *c, unsigned char *ptr) 
{
	
	
	c->free = get_int(ptr);
	c->size = get_int(ptr + sizeof(unsigned int));
	c->addr = ptr;
	
	c->next_chunk = c->addr + c->size;
	c->previous_chunk = (c->addr -  get_int(c->addr - sizeof(unsigned int)));
	
	if(ptr == heap) {
		c->previous_chunk = NULL;
	}
	
	if(c->addr + c->size == heap + HEAP_SIZE) {
		c->next_chunk = NULL;
	}
}

void init_alloc() 
{
	if(init != 0) return;
	init = 1;
	chunk c;
	c.free = 1;
	c.size = HEAP_SIZE;
	set_chunk(&c, heap);
	
	printf("Init_alloc()\n");
	
}

void *my_malloc(size_t size) 
{
	chunk current_c;
	chunk c;
	int chunk_size;
	int min_size ;
	init_alloc();
	
	get_chunk(&current_c, heap);
	min_size = size + 3*sizeof(unsigned int);
	
	while(current_c.free != 1 || current_c.size < min_size) 
	{
		/******************************/
		/******************************/
		/* Boucle infini !!!                   */
		/*gcc -shared -fPIC -o exec.so mon_malloc.c*/
		/*LD_PRELOAD=./exec.so ls*/
		/******************************/
		/******************************/
		
		if(current_c.next_chunk == NULL) 
		{
			printf("pas de place\n");
			return NULL;
		}
		get_chunk(&current_c, current_c.next_chunk);
	}
	
	
	/* le reste est trop petit */
	if(current_c.size - min_size < 3*sizeof(unsigned int)) 
	{
		/* on prend tout le chunk actuel */
		current_c.free = 0;
		set_chunk(&current_c, current_c.addr);
	}
	else
	{
		/* on découpe le chunk. */
		chunk_size = current_c.size;
		current_c.free = 0;
		current_c.size = min_size;
		set_chunk(&current_c, current_c.addr);
		
		/* reste */
		c.free = 1;
		c.size = chunk_size - min_size;
		set_chunk(&c, current_c.addr + current_c.size);
	}
	
	//printf("malloc(%ld)\n", size);
	//printf("nb chunk : %d\n", get_chunk_number());
	
	return (current_c.addr + (2*sizeof(unsigned int)));
}


void my_free(void *ptr)
{
	init_alloc();
	chunk c;

	if(ptr == NULL) return;
	
	chunk c_next;
	chunk c_previous;
	
	get_chunk(&c, ptr - (2*sizeof(unsigned int)));
	
	if(c.next_chunk != NULL) 
		get_chunk(&c_next, c.next_chunk);
	if(c.previous_chunk != NULL) 
		get_chunk(&c_previous, c.previous_chunk);
	
	if (c_next.free == 1)
	{
		c.size += c_next.size;
	}
	if (c_previous.free == 1)
	{
		c.addr -= c_previous.size;
		c.size += c_previous.size;
	}
	
	c.free = 1;
	set_chunk(&c, c.addr);
	
	//printf("free(%p)\n", ptr);
	//printf("nb chunk : %d\n", get_chunk_number());
	
}


void *my_realloc(void *ptr, size_t size)
{
	init_alloc();
	if(ptr == NULL) return malloc(size);
	unsigned char *p = malloc(size);
	if(p == NULL) return NULL;
	
	int i;
	for(i = 0 ; i < size ; i++) 
	{
		p[i] = ((unsigned char*)ptr)[i];
	}
	
	free(ptr);
	
	return p;
}

int get_chunk_number() {
	chunk c;
	int nb = 1;
	get_chunk(&c, heap);
	while(c.next_chunk != NULL) {
		get_chunk(&c, c.next_chunk);
		nb++;
	}
	return nb;
}















