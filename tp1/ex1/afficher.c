#include <stdio.h>

void afficher(int liste[], int taille) {
	int i;
	for(i = 0 ; i < taille ; i++) {
		printf("%d, ", liste[i]);
	}
	printf("\n");
}
