#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int socketFileDesc, portNumber, n;
    struct sockaddr_in serverAddr;

	/*
	struct  hostent
	{
		char    *h_name;        //official name of host
		char    **h_aliases;    // alias list
		int     h_addrtype;     // host address type
		int     h_length;       // length of address
		char    **h_addr_list;  // list of addresses from name server
		#define h_addr  h_addr_list[0]  // address, for backward compatiblity
	};
	*/

    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"The Usage is: %s Hostname Port\n", argv[0]);
       exit(0);
    }
    portNumber = atoi(argv[2]);
    socketFileDesc = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFileDesc < 0) 
        error("ERROR 1: Can not Open Socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR 2: Host Name is not Valid\n");
        exit(0);
    }
    bzero((char *) &serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serverAddr.sin_addr.s_addr,
         server->h_length);
    serverAddr.sin_port = htons(portNumber);
    if (connect(socketFileDesc,(struct sockaddr *) &serverAddr,sizeof(serverAddr)) < 0) 
        error("ERROR 3: Can not Connect to Server");
    printf("Please Enter The Message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    n = write(socketFileDesc,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR 4: Can not Write to Socket");
    bzero(buffer,256);
    n = read(socketFileDesc,buffer,255);
    if (n < 0) 
         error("ERROR 5: Can not Read from Socket");
    printf("%s\n",buffer);
    close(socketFileDesc);
    return 0;
}
