int somme(int liste[], int taille) {
	int i;
	int somme = 0;
	for(i = 0 ; i < taille ; i++) {
		somme += liste[i];
	}
	return somme;
}
