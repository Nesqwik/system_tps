#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ligne_commande.h"
#include "iut_shell.h"


void affiche_prompt()
{
	char* user = NULL;
	char* directory = NULL;
	char hostname[20];
	gethostname(hostname, 20);
	user = getenv("USER");
	directory = getcwd(NULL, 128);

	printf("%s@%s%s$ ", user, hostname, directory);
	fflush(stdout);

	free(directory);
}

void execute_ligne_commande()
{
	int flag, nb, i, pid;

	char ***argv = ligne_commande(&flag, &nb);

	if (flag == -1)
		return;

	for(i = 0 ; i < nb ; i++)
	{
		pid = fork();
		if(pid == 0) {
			execvp(argv[i][0], argv[i]);
			printf("iutshell: %s: commande introuvable\n", argv[i][0]);
			exit(1);
		}
		else
		{
			if (flag == 0)
				waitpid(pid, NULL, 0);
		}
	}
}

