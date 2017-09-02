#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	int sockfd;
	struct sockaddr_in serv_addr;

	socklen_t slen;
	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
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
	struct sockaddr_in _clientAddr;
	socklen_t _clientAddrLen;
	int recv_len;
	cout << "Waiting for new connection..." << endl;
	if ((recv_len = recvfrom(sockfd, buffer, bufferlength, 0, (struct sockaddr *) &_clientAddr, &_clientAddrLen)) == -1){
		error("recvfrom()");
	}
	buffer[recv_len] = '\0';
	string input(buffer);
	clientAddr = _clientAddr;
	clientAddrLen = _clientAddrLen;
	return input.compare("HELLO") == 0;
}

bool sendData (int sockfd, char* data, int len) {
	bool error = false;
	if (error = sendto(sockfd, data, len, 0, (struct sockaddr*) &clientAddr, clientAddrLen) == -1) {
		cout << "Error sending" << endl;
	}
	return !error;
}

int main (int argc, char **argv) {
	int port, sockfd, status;
	char buffer[BUFFER_LEN];
	if (argc > 1) {
		port = atoi(argv[1]);
	} else {
		port = DEFAULT_PORT;
	}
	sockfd = openSocket(port);
	while (true) {
		if (status = waitForConnection(sockfd, buffer, BUFFER_LEN)) {
			cout << "ready!!" << endl;
			while (status) {
				string data = "sending";
				sendData(sockfd, &(data[0]), data.length());
				sleep(1);
			}
		}
	}

	return 0;
}