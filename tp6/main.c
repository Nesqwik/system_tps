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
		printf("numero : %s\n", info.numero);
		char* buffer = malloc(255);
		printf("%s\n", get_artist_folder(buffer, 255, "/home/toto/", &info));
		printf("%s\n", get_genre_folder(buffer, 255, "/home/toto/", &info));
		printf("%s\n\n", get_file_name(buffer, 255, &info, ".mp3"));
	}
	sort_file("/home/infoetu/guilberl/Documents/S3/systeme/tp6/toto/", argv[1]);

	//printf("create_tree : %d\n\n", create_tree("/home/infoetu/guilberl/Documents/S3/systeme/tp6/toto/titi/"));

    return 0;
}
