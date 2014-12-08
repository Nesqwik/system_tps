#ifndef MP3LIB_H_INCLUDED
#define MP3LIB_H_INCLUDED


typedef struct {
	char* artiste;
	char* album;
	char* genre;
	char* titre;
	char* numero;
} sort_info_t;


const char *get_file_extension(const char *file);
void clean_string(char *s);
int get_file_info(const char *source_file, sort_info_t *info);


#endif // MP3LIB_H_INCLUDED
