#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "patate.h"

int obtenir_valeur_aleatoire(int borne_superieure) 
{
	int fd = open("/dev/urandom", O_RDONLY);
	unsigned char buff[sizeof(int)];
	read(fd, buff, sizeof(int));
	close(fd);
	return ((int) buff[0]) % borne_superieure + 1;
}

void lancer_patate(int out, int valeur)
{
	write(out, (void*) &valeur, sizeof(int));
	printf("%d lancé à %d\n", valeur, out);
}

int recevoir_patate(int in)
{
	char buf[sizeof(int)];
	
	if(read(in, &buf, sizeof(int)) == 0)
		return -1;
	
	printf("%d recu de %d\n", (int) buf[0], in);
	
	return (int) buf[0];
}

void demarrer_recepteur_patate(int in, int out)
{
	int nb;
	while((nb = recevoir_patate(in)) != -1)
	{
		nb--;
		if(nb == 0)
		{
			printf("explosion !");
			exit(0);
		}
		lancer_patate(out, nb);
	}
	
}