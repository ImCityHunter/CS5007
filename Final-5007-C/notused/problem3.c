/*
 * problem3.c
 *
 * Problem 3:
 * This program uses signals to control the state of the program.
 * NOTE: On Windows, this requires CygWin.
 *
 * The loop in the main method loops forever. For each iteration,
 * it sleeps for 2 seconds, then sends a signal to its own signal
 * handler for the value of nextSignal, initially SIGUSR1.
 *
 * Before entering the loop, the main program sets an alarm that
 * will send an SIGALRM signal after 15 seconds.
 *
 * This problem is to create and install handlers for the following
 * signals that will enable the program to operate correctly.
 *
 * SIGUSR1: This handler prints the message "Received SIGUSR1:
 * setting next signal to SIGUSR2" and sets nextSignal to SIGUSR2.
 *
 * SIGUSR2: This handler prints the message "Received SIGUSR2:
 * setting next signal to SIGUSR1" and sets nextSignal to SIGUSR1.
 *
 * SIGALRM: This handler prints "Received SIGALRM: setting next
 * signal to SIGTERM" and sets nextSignal to SIGTERM.
 *
 * SIGTERM: This handler prints "Received SIGTERM: exiting" and
 * sets running to false.
 */

#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/** next signal to be sent */
int nextSignal = SIGUSR1;

/** set false to exit */
bool running = true;

/**
 * Handle SIGALRM: termination signal.
 * @param sig the received signal
 */
void SIGALRM_handler(int sig) {
	printf("\nReceived SIGALRM: setting next signal to SIGTERM\n");
	nextSignal = SIGTERM;
	// your code here
}

/**
 * Handle SIGUSR1: application specific signal.
 * @param sig the received signal
 */
void SIGUSR1_handler(int sig) {
	printf("\nReceived SIGUSR1: setting next signal to SIGUSR2\n");
	nextSignal = SIGUSR2;

	// your code here
}

/**
 * Handle SIGUSR2: application specific signal.
 * @param sig the received signal
 */
void SIGUSR2_handler(int sig) {
	printf("\nReceived SIGUSR2: setting next signal to SIGUSR1\n");
	// your code here
	nextSignal = SIGUSR1;
}

/**
 * Handle SIGTERM: termination signal.
 */
void SIGTERM_handler(int sig) {
	printf("\nReceived SIGTERM: exiting\n");
	running = false;
	// your code here
}

/**
 * Register the required signal handlers.
 */
void registerSignalHandlers() {
	printf("\nreceived register\n");

	signal(SIGUSR1, SIGUSR1_handler);
	signal(SIGUSR2, SIGUSR2_handler);
	signal(SIGTERM, SIGTERM_handler);
	signal(SIGALRM, SIGALRM_handler);
}

/**
 * Main method sends the next signal to the current process.
 */
int main() {
	setlinebuf(stdout); // buffer lines
	printf("Start problem 3\n");

	const unsigned int ALARM_SECONDS = 15;  // alarm period
	const unsigned int SLEEP_SECONDS = 2;   // sleep period

	// register the required signal handlers
	registerSignalHandlers();

	printf("Setting alarm for %d seconds\n", ALARM_SECONDS);
	alarm(ALARM_SECONDS);  // sends SIGALRM after ALARM_SECONDS

	// run until alarm goes off
	while (running) {
		sleep(SLEEP_SECONDS);
		raise(nextSignal); // sends signal to current process
	}

	printf("End problem 3\n");
}
