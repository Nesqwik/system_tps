#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "pizza.h"


/* IMPLEMENTATION DES FONCTIONS A FAIRE ICI */

/* Stoppe un producteur */
/* Cette fonction NE DOIT PAS être modifiée */
void stop_producer(int pid)
{
    kill(pid, SIGKILL);
}


int main(int argc, char *argv[])
{
	int n = 3;
	int i;
	int fd[2];
	int pid_producers[4];
	pipe(fd);
	
	for(i = 0 ; i < n ; i++)
	{
		create_consumer(fd);
	}
	init_producers(fd, pid_producers);
	
	for(i = 0 ; i < n ; i++)
	{
		wait(0);
	}
	
	for(i = 0 ; i < 4 ; i++)
	{
		stop_producer(pid_producers[i]);
	}
	
	return 0;
}


int init_producers(int fd[2], int pid_producers[4])
{
	int i;
	for(i = 0 ; i < 4 ; i++)
	{
		int pid = create_producer(fd, i, ((i+3)%4)+1);
		
		if(pid == -1)
			return -1;
		else
			pid_producers[i] = pid;
	}
	
	return 0;
}


int create_producer(int fd[2], int ingredient, int delay)
{
	int pid = fork();
	
	if(pid == -1)
		return -1;
	if(pid != 0)
		return pid;
	
	close(fd[0]);
	
	while(1)
	{
		printf("prod : %d\n", ingredient);
		write(fd[1], &ingredient, sizeof(int));
		sleep(delay);
	}
}

int create_consumer(int fd[2])
{
	int pid = fork();
	struct stock s = {0, 0, 0, 0};
	
	int ingredient;
	
	if(pid == -1)
		return -1;
	if(pid != 0)
		return 0;
	
	close(fd[1]);
	
	
	while(1)
	{
		if(pizza_ready(&s) == 0)
		{
			s.bread -= 1;
			s.tomato -= 3;
			s.cheese -= 2;
			s.ham -= 2;
			
			free_stock(fd, &s);
			printf("Kowabunga !\n");
			close(fd[0]);
			exit(0);
		}
		else 
		{
			read(fd[0], &ingredient, sizeof(int));
			if(ingredient == BREAD) {
				s.bread++;
				printf("%d -> bread : %d\n", getpid(), s.bread);
			}
			else if(ingredient == TOMATO) {
				s.tomato++;
				printf("%d -> tomato : %d\n", getpid(), s.tomato);
			}
			else if(ingredient == CHEESE) {
				s.cheese++;
				printf("%d -> cheese : %d\n", getpid(), s.cheese);
			}
			else if(ingredient == HAM) {
				s.ham++;
				printf("%d -> ham : %d\n", getpid(), s.ham);
			}
			
			sleep(1);
		}
	}
}

void free_stock(int fd[2], struct stock *s)
{
	int i;
	int j;
	for(i = 0 ; i < 4 ; i++)
	{
		for(j = 0 ; j < ((int*)s)[i] ; j++)
		{
			write(fd[1], &i, sizeof(int));
		}
	}
}

int pizza_ready(struct stock * s)
{
	if(s->bread >= 1 && s->tomato >= 3 && s->cheese >= 2 && s->ham >= 2)
		return 0;
	return -1;
}
