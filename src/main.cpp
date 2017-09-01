#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "EGUtils.h"
#include "EGConfig.h"

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "ABE_ADCPi.h"

using namespace std;
using namespace ABElectronics_CPP_Libraries;
using namespace EGUtils;

struct sockaddr_in clientAddr;
socklen_t clientAddrLen;

int openSocket (int port) {
	int sockfd, newsockfd, n, recv_len;
	char buffer[BUFFER_LEN];
	struct sockaddr_in serv_addr;

	socklen_t slen;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
		 error("ERROR opening socket");
	
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}

	return sockfd;
}

bool waitForConnection (int sockfd, char* buffer, int bufferlength) {
	int recv_len;
	cout << "Waiting for new connection..." << endl;
	if ((recv_len = recvfrom(sockfd, buffer, bufferlength, 0, (struct sockaddr *) &clientAddr, &clientAddrLen)) == -1){
		error("recvfrom()");
	}
	string input(buffer);
	return input.compare("HELLO") == 0;
}

int main (int argc, char **argv) {
	int port, sockfd;
	char buffer[BUFFER_LEN];
	if (argc > 1) {
		port = atoi(argv[1]);
	} else {
		port = DEFAULT_PORT;
	}
	sockfd = openSocket(port);
	while (true) {
		if (waitForConnection(sockfd, buffer, BUFFER_LEN)) {
			cout << "ready!!" << endl;
		}
	}

	return 0;
}