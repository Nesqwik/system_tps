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
	int i, nb, flag;

	int in = 0, out = 1;
	int fds[2];

	int sout = dup(1);
	int sin = dup(0);

	char ***argv = ligne_commande(&flag, &nb);

	if (flag == -1)
		return;

	for(i = 0 ; i < nb ; i++)
	{
		in = sin;
		out = sout;

		if(i != 0)
		{
			in = fds[0];
		}

		if(nb > 1 && i != nb-1)
		{
			pipe(fds);
		}

		if(i != nb-1)
		{
			out = fds[1];
		}

		//printf("nb:%d, in:%d, out:%d, pipe:%d->%d\n",i, in, out, fds[1], fds[0]);

		lance_commande(in, out, argv[i][0], argv[i]);

	}

	if (flag == 0)
	{
		for(i = 0 ; i < nb ; i++)
		{
			wait(0);
		}
	}
}



int lance_commande(int in, int out, char *com, char ** argv)
{
	int pid = fork();
	if(pid == 0) {

		if(in != 0)
		{
			if(close(0) == -1 || dup(in) == -1) return -1;
		}
		if(out != 1)
		{
			if(close(1) == -1 || dup(out) == -1) return -1;
		}

		execvp(com, argv);
		printf("iutshell: %s: commande introuvable\n", argv[0]);
		exit(1);
	}
	else
	{
		if(in != 0)
			close(in);
		if(out != 1)
			close(out);
	}

	return pid;
}
