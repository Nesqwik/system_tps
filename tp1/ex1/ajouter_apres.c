void ajouter_apres(int dest[], int taille_dest, int src[], int taille_src) {
	int i;
	for(i = 0 ; i < taille_src ; i++) {
		dest[i + taille_dest] = src[i];
	}
}
