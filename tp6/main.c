#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "mp3lib.h"

int main(int argc, char** argv)
{
	int i;
	for(i = 1 ; i < argc ; i++) {
		/*printf("ext : %s\n", get_file_extension(argv[i]));
		char *cleared = malloc(strlen(argv[i]));
		strcpy(cleared, argv[i]);
		clean_string(cleared);
		printf("clean : %s\n", cleared);*/

		printf("file : %s\n", argv[i]);
		sort_info_t info;
		get_file_info(argv[i], &info);
		printf("artiste : %s\n", info.artiste);
		printf("album : %s\n", info.album);
		printf("titre : %s\n", info.titre);
		printf("genre : %s\n", info.genre);
		printf("numero : %s\n\n", info.numero);
	}
    return 0;
}
