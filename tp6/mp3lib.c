#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

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
	int frame_array_size = 0;
	int i;

	info->artiste = info->album = info->genre = info->numero = info->titre = NULL;
	frames = tag_get_frames(source_file, &frame_array_size);
	for(i = 0 ; i < frame_array_size ; i++)
	{
		if(strcmp(frames[i].id, "TALB") == 0)
		{
			info->album = malloc(strlen(frames[i].text)+1);
			strcpy(info->album, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TCON") == 0)
		{
			info->genre = malloc(strlen(frames[i].text)+1);
			strcpy(info->genre, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TPE1") == 0)
		{
			info->artiste = malloc(strlen(frames[i].text)+1);
			strcpy(info->artiste, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TRCK") == 0)
		{
			info->numero = malloc(strlen(frames[i].text)+1);
			strcpy(info->numero, frames[i].text);
		}
		else if(strcmp(frames[i].id, "TIT2") == 0)
		{
			info->titre = malloc(strlen(frames[i].text)+1);
			strcpy(info->titre, frames[i].text);
		}
	}


	tag_free(frames, frame_array_size);

	return 0;
}


const char *get_artist_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info)
{
	snprintf(buffer, size, "%s/By Artist/%c/%s/%s - %s/", root_folder, info->artiste[0], info->artiste, info->artiste, info->album);
	return buffer;
}

const char *get_genre_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info)
{
	snprintf(buffer, size, "%s/By Genre/%s/%s/%s - %s/", root_folder, info->genre, info->artiste, info->artiste, info->album);
	return buffer;
}

int check_and_create_folder(const char *path)
{
	struct stat stats;

	if(mkdir(path, 0777) == -1)
	{
		if(stat(path, &stats) != 0) return -1;
		if(S_ISDIR(stats.st_mode))
		{
			return access(path, R_OK | W_OK | X_OK);
		}
		else
		{
			return -1;
		}
	}

	return 0;
}

int create_tree(const char *fullpath)
{
	int i;
	int size = strlen(fullpath);
	char *path = malloc(size+1);

	for(i = 0 ; i < size ; i++)
	{
		path[i] = fullpath[i];
		if(fullpath[i] == '/' || fullpath[i] == '\0') {
			path[i + 1] = '\0';
			check_and_create_folder(path);
		}
	}

	return check_and_create_folder(path);
}


const char *get_file_name(char *buffer, int size, const sort_info_t *info, const char *ext)
{
	snprintf(buffer, size, "%s - %s - %02d.%s%s", info->artiste, info->album, atoi(info->numero), info->titre, ext);
	return buffer;
}


int sort_file(const char *root_folder, const char *source_file)
{
	int size = 255;
	char *new_path = malloc(size);
	char *folder_path = malloc(size);
	char *file_name = malloc(size);
	sort_info_t info;

	get_file_info(source_file, &info);

	if(info.artiste == NULL ||
		info.album == NULL ||
		info.genre == NULL ||
		info.titre == NULL ||
		info.numero == NULL )
	{
		return -1;
	}

	get_file_name(file_name, size, &info, get_file_extension(source_file));

	get_artist_folder(folder_path, size, root_folder, &info);

	create_tree(folder_path);
	snprintf(new_path, size, strcat(folder_path, file_name));
	printf("%s \n %s\n\n", get_artist_folder(folder_path, size, root_folder, &info), file_name);
	printf("link(%s \n, %s)\n\n", source_file, new_path);
	link(source_file, new_path);

	get_genre_folder(folder_path, size, root_folder, &info);
	create_tree(folder_path);
	snprintf(new_path, size, strcat(folder_path, file_name));
	link(source_file, new_path);

	return 0;
}

