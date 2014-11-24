#include <stdio.h>

#include "hello.h"
#include "afficher.h"
#include "somme.h"
#include "copie_dans.h"
#include "ajouter_apres.h"

int main(void)
{
	int liste[5] = {0, 1, 2, 3, 4};
	int liste2[7] = {5, 6, 0, 0, 0, 0, 0}; 
	ajouter_apres(liste2, 2,  liste, 5);
	afficher(liste2, 7);
	return 0;
}
