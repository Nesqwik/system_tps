#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "tag.h"

/**
 * Reads the ID3v2 header. After reading the header, position the file at the
 * start of the frames
 *
 * @param fd file descriptor
 * @param header pointer to a valid header structure
 *
 * @return -1 on error, 0 otherwise
 */

int tag_read_id3_header(int fd, id3v2_header_t *header)
{
	if(strcmp("ID3", read_string(fd, header->ID3, 3, 0)) != 0)
	{
		printf("titi1");
		return -1;
	}


	if(!read_u16(fd, &(header->version)))
	{
		printf("titi2");
		return -1;
	}

	// version valide
	if(header->version > 0x0300)
	{
		printf("titi3");
		return -1;
	}

	if(!read_u8(fd, &(header->flags)))
	{
		printf("titi4");
		return -1;
	}

	if(!read_u32(fd, &(header->size)))
	{
		printf("titi5");
		return -1;
	}

	header->size = convert_size(header->size);
	return 0;
}



/**
 * Reads a frame, stores data into the structure
 *
 * @param fd file descriptor
 * @param frame structure pointer
 *
 * @return -1 on error, 0 otherwise
 */
int tag_read_one_frame(int fd, id3v2_frame_t *frame)
{
    u8 encoding;
	int i = 0;

    if(read_string(fd, frame->id, ID3V2_FRAME_ID_LENGTH, 0) == NULL)
		return -1;

    if(!read_u32(fd, &(frame->size)))
		return -1;
    if(!read_u16(fd, &(frame->flags)))
		return -1;

	if(frame->id[0] != 'T' || !strcmp(frame->id, "TXXX"))
	{
		lseek(fd, frame->size, SEEK_CUR);
		frame->text = NULL;
		return -1;
	}

	for(i = 0 ; i < ID3V2_FRAME_ID_LENGTH ; i++)
	{
		if(!isupper(frame->id[i]) && !isdigit(frame->id[i])) {
			lseek(fd, frame->size, SEEK_CUR);
			frame->text = NULL;
			return -1;
		}
	}


    if(!read_u8(fd, &(encoding)))
		return -1;

    frame->text = read_string(fd, NULL, frame->size - 1, (int) encoding);
	if(frame->text == NULL)
		return -1;


    return 0;
}


/**
 * @brief Returns the list of frames of the file
 *
 * @param file the path to the file to parse
 * @param frame_array_size pointer to a valid integer where the function will
 * store the number of read frames
 *
 * @return NULL if error, an array of frames if successful
 */
id3v2_frame_t *tag_get_frames(const char *file, int *frame_array_size)
{
	id3v2_header_t header;
	id3v2_frame_t *frames = malloc(sizeof(id3v2_frame_t));
	int i = 0;
	int fd;

	if((fd = open(file, O_RDONLY)) == -1)
	{
		perror("open");
		return NULL;
	}

	if(tag_read_id3_header(fd, &header) == -1)
	{
		printf("header invalide");
		return NULL;
	}

	while(tag_read_one_frame(fd, &(frames[i])) == 0)
	{
		i++;
		frames = realloc(frames, sizeof(id3v2_frame_t) * (i + 1));
	}

	*frame_array_size = i;

	if(i == 0){
		return NULL;
	}

	return frames;

}


/**
 * @brief frees a frames buffer and all that has been allocated to hold frame values
 *
 * @param frames
 * @param frame_count
 */
void tag_free(id3v2_frame_t *frames, int frame_count)
{
	int i;
	for(i = 0 ; i < frame_count ; i++)
	{
		free(frames[i].text);
	}
	free(frames);
}

