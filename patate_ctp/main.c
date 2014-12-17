#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "patate.h"

int main(void)
{
	int nbJoueur = 3;
	int tubes[nbJoueur][2];
	int nbDepart = obtenir_valeur_aleatoire(30); 
	int i;
	
	for(i = 0 ; i < nbJoueur ; i++)
	{
		pipe(tubes[i]);
	}
	
	
	int lastPid = 0;
	for(i = 0 ; i < nbJoueur ; i++)
	{
		if(lastPid == 0) {
			lastPid = fork();
		}
		if(lastPid != 0) {
			// TODO : suite
			demarrer_recepteur_patate(tubes[i][0], tubes [i-1][1]);
		}
	}
	
	lancer_patate(fds[1], 10);
	//recevoir_patate(fds[0]);
	
	demarrer_recepteur_patate(fds[0], fds[1]);
	return 0;
}
