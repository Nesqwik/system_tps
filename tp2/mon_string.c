#include<stdio.h>

/*int mon_strlen(char s[])
{
	int i = 0;
	while(s[i] != '\0') i++;
	return i;
}*/



int mon_strcmp(const char * s1, const char * s2)
{
	int i = 0;
	while(s1[i] == s2[i] && s1[i] != '\0') i++;
	return s1[i] - s2[i];
}

int mon_strncmp(const char * s1, const char * s2, int n) {
	int i = 0;
	while(s1[i] == s2[i] && s1[i] != '\0' && i < n - 1) i++;
	return s1[i] - s2[i];
}

int mon_strlen(const char *s) {
	int i = 0;
	while(s[i] != '\0') i++;
	return i;
}

char *mon_strcat(char *s1, const char *s2)
{
	int i;
	int start = mon_strlen(s1) ;
	int end = mon_strlen(s1)  + mon_strlen(s2) ;
	for(i = start ; i < end ; i++) {
		s1[i] = s2[i - start];
	}
	s1[i] = '\0';
	return s1;
}

char *mon_strchr(char *s, int c) 
{
	int i;
	while(s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return  s[i] == '\0' ? NULL : &s[i];
}

char *mon_strstr(char *haystack, char *needle) 
{
	int i;
	int t1 = mon_strlen(haystack);
	int t2 = mon_strlen(needle);
	
	for(i = 0 ; i < t1 - t2 ; i++) {
		if(mon_strncmp(&haystack[i], needle, t2) == 0) {
			return &haystack[i];
		}
	}
	
	return NULL;
}




