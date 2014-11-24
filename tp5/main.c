#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "tag.h"


void tests()
{
	int fd;


	// test read 32
	if((fd = open("music/00000.mp3", O_RDONLY)) == -1)
	{
		perror("open");
	}
    u32 val;
    read_u32(fd, &val);
    if(val == 0x49443303)
		printf("%x : ok !\n", val);
	else
		printf("%x : fail\n", val);

	// test convert size
    val = 0x6D776E6E;
    if(val == 0x0DBDF76E)
		printf("%x : ok !\n", convert_size(val));
	else
		printf("%x : ok !\n", convert_size(val));

	// test read_string;
	if((fd = open("music/00000.mp3", O_RDONLY)) == -1)
	{
		perror("open");
	}
    char* str = NULL;
    lseek(fd, 21, SEEK_CUR);
    str = read_string(fd, str, 34, 1);
    printf("%s\n", str);


	// test read header
	if((fd = open("music/00000.mp3", O_RDONLY)) == -1)
	{
		perror("open");
	}
    id3v2_header_t header;
    int error = tag_read_id3_header(fd, &header);
    printf("erreur : %d\n", error);
	printf("ID3 : %s\n", header.ID3);
	printf("version : %0x\n", header.version);
	printf("flags : %0x\n", header.flags);
	printf("size : %d\n\n\n", header.size);


	// test read frame 1
	id3v2_frame_t frame;
	error = tag_read_one_frame(fd, &frame);
    printf("erreur : %d\n", error);
	printf("id : %s\n", frame.id);
	printf("size : %d\n", frame.size);
	printf("flags : %0x\n", frame.flags);
	printf("text : %s\n\n\n", frame.text);


	// test read al frames
	id3v2_frame_t *frames = NULL;
	int frame_array_size;
	int i;
	const char *file = "music/00015.mp3";
	frames = tag_get_frames(file, &frame_array_size);
	printf("nombre frames : %d\n", frame_array_size);
	for(i = 0 ; i < frame_array_size ; i++)
	{
		printf("Frame %d : \n", i+1);
		printf("id : %s\n", frames[i].id);
		printf("size : %d\n", frames[i].size);
		printf("flags : %0x\n", frames[i].flags);
		printf("text : %s\n\n\n", frames[i].text);
	}

	tag_free(frames, frame_array_size);
}

void print_file(char *file)
{
	id3v2_frame_t *frames = NULL;
	int frame_array_size;
	int i;

	frames = tag_get_frames(file, &frame_array_size);

	printf("Fichier : %s\n", file);
	for(i = 0 ; i < frame_array_size ; i++)
	{
		printf("%s\n", frames[i].text);
	}

	tag_free(frames, frame_array_size);
	printf("\n");
}


int main(int argc, char **argv)
{
	int i;
	for(i = 1 ; i < argc ; i++)
	{
		print_file(argv[i]);
	}
    return 0;
}


