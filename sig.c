#define _POSIX_SOURCE
#include <makestuff.h>
#include <signal.h>

static bool m_sigint = false;

bool sigIsRaised(void) {
	return m_sigint;
}

static void sigHandler(int signum) {
	(void)signum;
	m_sigint = true;
}

void sigRegisterHandler(void) {
	struct sigaction newAction, oldAction;
	newAction.sa_handler = sigHandler;
	sigemptyset(&newAction.sa_mask);
	newAction.sa_flags = 0;
	sigaction(SIGINT, NULL, &oldAction);
	if ( oldAction.sa_handler != SIG_IGN ) {
		sigaction (SIGINT, &newAction, NULL);
	}
}
