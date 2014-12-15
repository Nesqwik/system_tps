#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>



int main(void)
{
	int fd = open("/dev/urandom", O_RDONLY);
	char buff[128];
	read(fd, buff, 128);
	
	int i, nb;
	for(i = 0 ; i < strlen(buff) ; i++)
	{
		nb += (int) buff[i];
	}
	
	printf("nb : %d\n", (nb%10)+1);

	return 0;
}
