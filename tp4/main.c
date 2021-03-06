#include <stdio.h>
//#include <stdlib.h>
#include "mon_malloc.h"
#include <string.h>
#include <ctype.h>

#define S_FLAG 1
#define M_FLAG 2
#define ERROR_FLAG -1


void *dis_realloc(void *ptr, size_t size) {
	return my_realloc(ptr, size);
}
void *dis_malloc(size_t size) {
	return my_malloc(size);
}
void dis_free(void *ptr) {
	my_free(ptr);
}


char *miroir(char *s)
{
	int i, n;
	n = strlen(s);
	char* miroir = dis_malloc(n);
	for(i = 0 ; i < n ; i++) {
		miroir[i] = s[n - i - 1];
	}
	dis_free(s);
	return miroir;
}

char *saisie () {
	char c;
	int size = 0;
	int i = 0;
	char* word = NULL;
	
	 do {
		c = getchar();
		if(c == EOF) break;
		if(i >= size) {
			size = size + 128;
			word = dis_realloc(word, size);
		}
		word[i] = c;
		i++;
	} while(!isspace(c));
	word = dis_realloc(word, i + 1);
	word[i] = '\0';
	return word;
}


char getflag(int argc, char **argv, char* string) {
	if(argc == 1) {
		dis_free(string);
		return -1;
	}
	
	int i, j, str = 0;
	char flag = 0;
	
	for(i = 1 ; i < argc ; i++) 
	{
		//is an option
		if(argv[i][0] == '-') 
		{
			int l = strlen(argv[i]);
			for(j = 1 ; j < l ; j++)
			{
				if(argv[i][j] == 's')
					flag |= S_FLAG;
				else if(argv[i][j] == 'm')
					flag |= M_FLAG;
				else {
					dis_free(string);
					return -1;
				}
			}
		}
		else if(str == 0) 
		{
			int len = strlen(argv[i]);
			string = dis_realloc(string, len);
			for(j = 0 ; j < len ; j++) {
				string[j] = argv[i][j];
			}
			str = 1;
		}
		else
		{
			dis_free(string);
			return -1;
		}
	}
	
	if(str == 1 && flag & S_FLAG) {
		dis_free(string);
		return -1;
	}
	if(str == 0 && flag & M_FLAG && (flag & S_FLAG) == 0) {
		dis_free(string);
		return -1;
	}
	
	dis_free(string);
	return flag;
}

int main2(int argc, char **argv)
{
	char *string = dis_malloc(0);
	char flags = getflag(argc, argv, string);
	if(flags == ERROR_FLAG)
	{
		printf("Le(s) option(s) de la commande sont incorrect\n");
		return 0;
	}
	if(flags & S_FLAG)
	{			
		string = saisie();
	}
	if(flags & M_FLAG) 
	{
		string = miroir(string);
	}
	printf("%s\n", string);
	dis_free(string);
	return 0;
}


 int main(int argc, char **argv)
{
	int i = 0;
	for(i = 0 ; i < 1000 ; i++) {
	//while(1) {
		main2(argc, argv);
	}
	return 0;
}






