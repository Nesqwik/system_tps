#include <stdio.h>
#include <stdlib.h>

#include "iut_shell.h"

int main()
{
	while(1)
	{
		affiche_prompt();
		execute_ligne_commande();
	}
	printf("\n");
    return 0;
}
