#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "patate.h"

int main(void)
{
	int nbJoueur = 3;
	int tubes[nbJoueur][2];
	int nbDepart = obtenir_valeur_aleatoire(30); 
	int i;
	int j;
	
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
			int in = (i == 0 ? tubes[nbJoueur - 1][0] : tubes[i-1][0]);
			int out = tubes[i][1];
			
			for(j = 0 ; j < nbJoueur ; j++)
			{
				if(tubes[i][0] != in) 
					close(tubes[i][0]);
				
				if(tubes[i][1] != out) 
					close(tubes[i][1]);
			}
			
			demarrer_recepteur_patate(in, out);
			break;
		}
	}
	
	if(lastPid == 0) {
		lancer_patate(tubes[0][1], nbDepart);
		
		for(j = 0 ; j < nbJoueur ; j++)
		{
			close(tubes[i][0]);
			close(tubes[i][1]);
		}

		for(i = 0 ; i < nbJoueur ; i++) {
			wait(0);
		}
	}
	return 0;
}
