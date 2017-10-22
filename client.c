// The header file that includes the socket basic functions for socket communication
// in unix type environment
#include<stdio.h>
// The header file to include the basic c functions like scanf printf etc

# define MAXLINE 1024
// MAXLINE to be used in the program to specify the maximum output for the buffer

#include <string.h>
// to use the bzero function

#include<unistd.h>
// to use the read and write function

#include<arpa/inet.h>

// to use the exit function in c
#include<stdlib.h>

// to use the power function used in the diffie-hellmen
#include"diffie.h"	

// declaration for the error function
void error(char* msg);


int 
main(int argc, char *argv[]) {

	// variables for the socket file descriptor
	// port_no and the error number;
	int sockfd, port_no, n;

	// declaration for the server address part
	// which will contain the information about 
	// the family and the port_number and the
	// address to which we will communicate
	struct sockaddr_in serv_addr;

	// a temporary buffer for the storage of the
	// temporary data during the transfer
	char buffer[MAXLINE];
	
	if(argc < 3) {
		// the argument for the client program will be of like
		// ./client.out localhost 4566
		// $(program) (machine_on_which_pgm_will_run) (port_no)
		// If the argument is less than 3 then there is something
		// missing the program cannot proceed forward
		// so exiting the program
		fprintf(stderr, "usage %s hostname port \n", argv[0]);
		exit(1);
	}

	printf("\n\n\t\t\t\t CLIENT \n\n");
	
	printf("Please enter your secret key : \n\n");

	fflush(stdout);

	int mySecretKey = 0;

	// clearning the socket_structure using the berkeley-derived
	// function bzero(void* , size_t);
	bzero(&serv_addr, sizeof(serv_addr));

	// converting the port number with the help of atoi function
	// which is given at the begining of the program 
	port_no = atoi(argv[2]);
	

	// creating the socket needed for the tcp connection
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(sockfd < 0) {
		// If something went wrong during the connection of the 
		// of the program then exit the program
		printf("error creating socket");
		exit(1);
	}
	
	// filling the server structure with the help of the port_no
	serv_addr.sin_port = htons(port_no);

	// filling the server_structure family with AF_INET for the
	// tcp connection family
	serv_addr.sin_family = AF_INET;
	
	// connecting to the socket with the help of the structrure of 
	// the socket if it fails then just return
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR connecting ");

	/* UPTO NOW IF EVERYTHING IS GONE RIGHT THEN A CONNECTION WILL GOT 
	   ESTABLISHED WITH THE SERVER AND DIFFIE-HELLMEN PROCESS WILL GO ON
	   AFTER THIS*/
	
	// clearing the buffer to be zero
	bzero(buffer, sizeof(buffer));

	// declaring variables for the PKP, PKG, PKX
	int PKP = 0, PKG = 0, keyExchanged = 0;
	
	// receiving the PKP public Key PrimeNumber
	n = read(sockfd, &PKP, sizeof(PKP));
	if(n < 0) error("Error reading from the socket");

	// receiving the PKG public key PrimitiveRootG
	n = read(sockfd, &PKG, sizeof(PKG));
	if(n < 0) error("Error reading from the socket");

	// receiving the key sent by the sender
	n = read(sockfd, &keyExchanged, sizeof(keyExchanged));
	if(n < 0) error("Error reading from the socket");

	// converting them to the various formats due to the
	// little-endian and big-endian formats
	int pkp = ntohl(PKP);
	int pkg = ntohl(PKG);
	int keyexchanged = ntohl(keyExchanged);

	// getting your secret key 
	scanf("%d",&mySecretKey);

	int keyToBeSent = power(pkg, mySecretKey, pkp);

	// sending the keygenerated from the private key and
	// the global public keys
	// again conversion because of the format in various pc
	int converted_number = htonl(keyToBeSent);
	write(sockfd, &converted_number, sizeof(converted_number));

	// calculation of the shared key
	int sharedKey = power(keyexchanged, mySecretKey, pkp);

	// printing the various keys and shared keys during the process
	printf("\nPublic Key used in the process (Prime Number) : %d\n", pkp);
	printf("Public Key used in the process (Primitive Root): %d\n", pkg);
	printf("Public Key sent by me (Client) in the process : %d\n\n", keyToBeSent);
	printf("Shared Key with the server in the process : %d\n", sharedKey);
	
	close(sockfd);
	return 0;
}

void error(char *msg) {
	perror(msg);
	exit(1);
}
