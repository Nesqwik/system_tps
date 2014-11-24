#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "ligne_commande.h"
#include "iut_shell.h"


void affiche_prompt()
{
	printf("iutshell$");
	fflush(stdout);
}

void execute_ligne_commande()
{
	int flag, nb, i, pid;

	char ***argv = ligne_commande(&flag, &nb);

	for(i = 0 ; i < nb ; i++)
	{
		pid = fork();
		if(pid == 0) {
			execvp(argv[i][0], argv[i]);
		}
		else
		{
			waitpid(pid, NULL, 0);
		}
	}
}

