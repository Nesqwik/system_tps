#include<stdio.h>
#include "mon_string.h"

int main() {
	char s[] = "toto";
	printf("%d\n", mon_strlen(s));
	
	char s1[20] = "abce";
	char s2[] = "abcd";
	printf("%d\n", mon_strcmp(s1, s2));
	printf("%d\n", mon_strncmp(s1, s2, 3));
	printf("%s + %s = %s \n", s1, s2, mon_strcat(s1, s2));
	printf("%c\n", *mon_strchr(s, 'o'));
	
	char str[] = "abcdef";
	char substr[] = "cd";
	printf("%s\n", mon_strstr(str, substr));
	
	return 0;
}