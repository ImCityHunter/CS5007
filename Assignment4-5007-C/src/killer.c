/*
 *	kill.c
 *
 *  Created on: Apr 2, 2018
 *      Author: HoKang Yu
 */
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
static pid_t otherID;

#include <signal.h>
#include <stdio.h>
/**
 * print options
 */
void print_message(){
	printf("1 = SIGTSTP \n");
	printf("2 = SIGCONT \n");
	printf("3 = SIGTERM \n");
	printf("4 = SIGUSR1 \n");
	printf("5 = SIGUSR2 \n");
	printf("0 = quit\n");
	printf("Enter Signal: ");
}

/** Handler for SIGTSTP signal */
void SIGTSTP_handler(int sig){
	printf("\nreceived SIGTSTP: Pausing..... \n");
	pause();
}

/** Handler for SIGCONT signal */
void SIGCONT_handler(int sig){
	printf("\nreceived SIGCONT\n");
	print_message();
}

/** Handler for SIGTERM signal */
void SIGTERM_handler(int sig){
	printf("\nreceived SIGTERM\n");
	exit( EXIT_SUCCESS);
}

/** Handler for SIGUSR1 signal */
void SIGUSR1_handler(int sig) {
	printf("\nreceived SIGUSR1\n");
	printf("my id is: %d\n",getpid());
}

/** Handler for SIGUSR2 signal */
void SIGUSR2_handler(int sig) {
	printf("\nreceived SIGUSR2\n");
	printf("otherId is: %d\n",otherID);
}


int main() {
	// register handlers
	signal(SIGUSR1, SIGUSR1_handler);
	signal(SIGUSR2, SIGUSR2_handler);
	signal(SIGTERM, SIGTERM_handler);
	signal(SIGCONT, SIGCONT_handler);
	signal(SIGTSTP, SIGTSTP_handler);

	// get id of this process
	pid_t pid = getpid();

	printf("this process id: %d\n",pid);
	printf("other process id:");
	scanf("%d",&otherID);
	int input;

	print_message();
	scanf("%d",&input);
	bool run = true;
	int killer = -1;
	while(run){
		switch(input){
		case 1:
				killer = kill(otherID,SIGTSTP);
				break;
		case 2:
				killer = kill(otherID,SIGCONT);
				break;
		case 3:
				killer = kill(otherID,SIGTERM);
				break;
		case 4:
				killer = kill(otherID,SIGUSR1);
				break;
		case 5:
				killer = kill(otherID,SIGUSR2);
				break;
		case 0:
				printf("0 = quit\n");
				run = false;
				return EXIT_SUCCESS;
		default:
				printf("Enter valid Value\n");
				break;
			}

		if(killer == -1) {
			printf("Process %d no longer available\n",otherID);
			exit(EXIT_FAILURE);
		}

		print_message();
		scanf("%d",&input);

	}


	return EXIT_SUCCESS;
}
