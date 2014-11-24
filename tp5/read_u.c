#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tag.h"

/**
 * Reads an u8 from a file descriptor
 *
 * @param fd file descriptor
 * @param val where the value should be stored
 *
 * @return 0 on error, 1 otherwise
 */
int read_u8(int fd, u8 *val)
{
    if(read(fd, val, U8_SIZE) == -1)
    {
        perror("read");
        return 0;
    }
    return 1;
}

/**
 * Reads an u16 from a file descriptor
 *
 * @param fd file descriptor
 * @param val where the value should be stored
 *
 * @return 0 on error, 1 otherwise
 */
int read_u16(int fd, u16 *val)
{
    u8 low;
    u8 high;
    if(!read_u8(fd, &high)) return 0;
    if(!read_u8(fd, &low)) return 0;

    *val = (high << 8) | low;
    return 1;
}

/**
 * Reads an u32 from a file descriptor
 *
 * @param fd file descriptor
 * @param val where the value should be stored
 *
 * @return 0 on error, 1 otherwise
 */
int read_u32(int fd, u32 *val)
{
    u16 low;
    u16 high;
    if(!read_u16(fd, &high)) return 0;
    if(!read_u16(fd, &low)) return 0;

    *val = (high << 16) | low;
    return 1;
}


/**
 * Converts ID3 size
 *
 * @param size initial size
 *
 * @return the converted size (every 7th bit of each byte has been removed)
 */
u32 convert_size(u32 size)
{
    size = ((size & 0xFFFFFF00) >> 1) | (size & 0x0000007F);
    size = ((size & 0xFFFF8000) >> 1) | (size & 0x0000BFFF);
    size = ((size & 0xFFC00000) >> 1) | (size & 0x003FFFFF);

    return size;
}



char *read_ascii(int fd, char *to, int size)
{
	if(to == NULL)
		to = malloc(size + 1);

	if(read(fd, to, size) == -1)
	{
		perror("ascii_read");
		return NULL;
	}
	to[size] = 0;
	return to;
}

char *read_unicode(int fd, char *to, int size)
{
	int i, bom = 0;
	char buf[2];

	// Alloc memory
	if(to == NULL)
		to = malloc(size/2);

	// Read BOF
	if(read(fd, buf, 2) == -1)
	{
		perror("unicode_read");
		return NULL;
	}

	// if BOM = FEFF
	if(buf[0] == 0xFE)
		bom = 1;

	// read all size
	for(i = 0 ; i < (size / 2) - 1 ; i++)
	{
		if(read(fd, buf, 2)== -1)
		{
			perror("read");
			return NULL;
		}
		to[i] = buf[bom];
	}
	to[i] = 0;
	return to;
}


/**
 * Reads a string from a file descriptor
 *
 * @param fd the file descriptor
 * @param to where to store the string
 * @param size how many bytes
 * @param encoding how to read chars
 *
 * if "to" is NULL, malloc memory space
 * else use "to" pointer to store the string
 *
 * @return the readed string
 */
char * read_string(int fd, char *to, int size, int encoding)
{
    if(encoding == 0)
		return read_ascii(fd, to, size);

    if(encoding == 1)
		return read_unicode(fd, to, size);

	return NULL;
}
