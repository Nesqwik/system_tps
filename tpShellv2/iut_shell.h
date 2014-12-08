#ifndef IUT_SHELL_H_INCLUDED
#define IUT_SHELL_H_INCLUDED

void affiche_prompt();
void execute_ligne_commande();
int lance_commande( int in, int out, char *com, char ** argv);


#endif // IUT_SHELL_H_INCLUDED
