#define HEAP_SIZE 20000000
unsigned char heap[HEAP_SIZE];

typedef struct
{
	unsigned int free ;
	unsigned int size ;
	unsigned char * addr ;
	unsigned char * next_chunk ;
	unsigned char * previous_chunk ;
} chunk ;

unsigned int get_int(void *ptr);
void set_int(void *ptr, unsigned int val);
void set_chunk(chunk *c, unsigned char *ptr);
void get_chunk(chunk *c, unsigned char *ptr);
void init_alloc();
void *my_malloc(size_t size);
void my_free(void *ptr);
int get_chunk_number();
void *my_realloc(void *ptr, size_t size);
