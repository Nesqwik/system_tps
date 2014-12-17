#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct toto {
	int v1;
	int v2;
	int v3;
	int v4;
};

int main(int argc, char *argv[])
{
	/*int fd[2];
	int readv;
	int writev = 1000;
	
	pipe(fd);
	
	
	write(fd[1], &writev, sizeof(int));
	read(fd[0], &readv, sizeof(int));
	
	printf("nb : %d\n", readv);*/
	
	int i;
	struct toto s = {1, 2, 3, 4};
	for(i = 0 ; i < 4 ; i++)
	{
		printf("v%d = %d\n", i, ((int*)&s)[i]);
	}
	
	return 0;
}
