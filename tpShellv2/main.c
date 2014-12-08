#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "iut_shell.h"

int main()
{
	while(1)
	{
		affiche_prompt();
		execute_ligne_commande();
	}
	printf("\n");


	/*int fd = open("toto.txt", O_RDONLY | O_WRONLY | O_CREAT);
	char *argv[] = {
		"grep",
		"main",
		NULL
	};
	lance_commande(fd, 1, "grep", argv);
    return 0;*/
}
