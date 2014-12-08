#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "mp3lib.h"
#include "tag.h"
#include "read_u.h"

const char *get_file_extension(const char *file)
{
	int i = 0;
	while(file[i] != 0)
	{
		if(file[i] == '.')
			return &file[i];
		i++;
	}
	return NULL;
}


void clean_string(char *s)
{
	int length = strlen(s);
	int i;
	for(i = 0 ; i < length ; i++)
	{
		if(s[i] == '/')
			s[i] = '-';
		else
			s[i] = tolower(s[i]);
	}
	s[0] = toupper(s[0]);
}

int get_file_info(const char *source_file, sort_info_t *info)
{

	id3v2_frame_t *frames = NULL;
	int frame_array_size;
	int i;

	frames = tag_get_frames(source_file, &frame_array_size);
	for(i = 0 ; i < frame_array_size ; i++)
	{
		if(strcmp(frames[i].id, "TALB") == 0)
		{
			info->album = malloc(strlen(frames[i].text));
			strcpy(info->album, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TCON") == 0)
		{
			info->genre = malloc(strlen(frames[i].text));
			strcpy(info->genre, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TPE1") == 0)
		{
			info->artiste = malloc(strlen(frames[i].text));
			strcpy(info->artiste, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TRCK") == 0)
		{
			info->numero = malloc(strlen(frames[i].text));
			strcpy(info->numero, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TIT2") == 0)
		{
			info->titre = malloc(strlen(frames[i].text));
			strcpy(info->titre, frames[i].text);
		}
	}


	tag_free(frames, frame_array_size);

	return 0;
}

