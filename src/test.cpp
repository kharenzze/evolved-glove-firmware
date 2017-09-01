//tests

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
#include<arpa/inet.h>

#include "ABE_ADCPi.h"

#define BUFLEN 512

using namespace std;
using namespace ABElectronics_CPP_Libraries;
using namespace EGUtils;

void testADCPI() {
	ADCPi adc(0x68, 0x69, 18);
	adc.set_conversion_mode(1);
	adc.set_pga(4);

	while (1) {
		clearscreen();
		printf("Pin 1: %G \n", adc.read_voltage(1)); // read from channel 1
		//printf("Pin 1: %d \n", adc.read_raw(1)); // read from channel 1
		usleep(200000); // sleep 0.2 seconds
	}
}

void error (string s) {
  throw runtime_error (s);
}

int main (int argc, char **argv) {

	int sockfd, newsockfd, portno, n, recv_len;
	char buffer[BUFLEN];
	struct sockaddr_in serv_addr, cli_addr;

	socklen_t slen;

	if (argc > 1) {
		portno = atoi(argv[1]);
	} else {
		portno = DEFAULT_PORT;
	}
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
		 error("ERROR opening socket");
	memset((char *) &serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}

	while (1) {
			cout << "Waiting for data..." << endl;
			 
			//try to receive some data, this is a blocking call
			
			if ((recv_len = recvfrom(sockfd, buffer, BUFLEN, 0, (struct sockaddr *) &cli_addr, &slen)) == -1)
			{
					error("recvfrom()");
			}
			 
			//print details of the client/peer and the data received
			printf("Received packet from %s:%d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
			printf("Data: %s\n" , buffer);
			 
			//now reply the client with the same data
			// if (sendto(sockfd, buffer, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
			// {
			// 		die("sendto()");
			// }
	}
	return 0;

	// listen(sockfd,5);
	// clilen = sizeof(cli_addr);
	// newsockfd = accept(sockfd, 
	// 						(struct sockaddr *) &cli_addr, 
	// 						&clilen);
	// if (newsockfd < 0) 
	// 		 error("ERROR on accept");
	// bzero(buffer,256);
	// n = read(newsockfd,buffer,255);
	// if (n < 0) error("ERROR reading from socket");
	// printf("Here is the message: %s\n",buffer);
	// n = write(newsockfd,"I got your message",18);
	// if (n < 0) error("ERROR writing to socket");
	// close(newsockfd);
	// close(sockfd);
	// return 0; 

	testADCPI();
	return 0;
}
