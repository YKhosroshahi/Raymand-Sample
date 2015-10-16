#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>   
#include <errno.h>   
#include <termios.h> 



void error(const char *msg)
{
    perror(msg);
    exit(1);
}


int open_port(void)
{
	int sPortFileDesc; 
	sPortFileDesc = open("/dev/pts/6", O_RDWR| O_NONBLOCK | O_NDELAY);
	if (sPortFileDesc < 0)
	{
		error("Unable to open /dev/pts/6 ");
	}
	else
	fcntl(sPortFileDesc, F_SETFL, 0);

	return (sPortFileDesc);
}


int main(int argc, char *argv[])
{
	int socketFileDesc, newsocketFileDesc, sPortFileDesc, portNumber;
	socklen_t clientLength;
	char buffer[256];
	struct sockaddr_in serverAddr
			, clientAddr;
	int n;
	if (argc < 2)
		error("ERROR 1: Please Provide Port Number\n");

	socketFileDesc = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFileDesc < 0) 
		error("ERROR 2: Can not Open Socket");

	bzero((char *) &serverAddr, sizeof(serverAddr));

	portNumber = atoi(argv[1]);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(portNumber);

	if (bind(socketFileDesc, (struct sockaddr *) &serverAddr,
		  sizeof(serverAddr)) < 0) 
		  error("ERROR 3: Can not Bind");

	listen(socketFileDesc,5);

	clientLength = sizeof(clientAddr);

	newsocketFileDesc = accept(socketFileDesc, 
		     (struct sockaddr *) &clientAddr, 
		     &clientLength);
	if (newsocketFileDesc < 0) 
	  error("ERROR 4: Can not Accept Connection");

	bzero(buffer,256);

	//Read Data from Client
	n = read(newsocketFileDesc,buffer,256);
	if (n < 0) 
		error("ERROR 5: Can not Read from Socket");
	
	printf("The Client Message Is: %s\n",buffer);
	
	// Send The Message to Serial Port
	sPortFileDesc = open_port();
	n = write(sPortFileDesc, buffer, 256);
	if (n < 0)
		fputs("Error 6: Can not Write to Serial Port!\n", stderr);

	printf("The Client Message Has Been Sent to Serial Port\n");

	
	// Read The Serial Port Response
	int bytes;

    char spBuffer[10];
    char *spBufptr;
	spBufptr = spBuffer;
	
	fcntl(sPortFileDesc, F_SETFL, FNDELAY);
	bytes = read(sPortFileDesc, spBufptr, sizeof(spBuffer));

	/*printf("Read byte %d\n", bytes);
	int x,c;
	for (x = 0; x < 10 ; x++)
    {
        c = spbuffer[x];
        printf("%d  ",c);
    }*/	
	
	printf("The Serial Port Response Has Been Received\n");

	// Send Serial Port Response To Client
	n = write(newsocketFileDesc,spBuffer,sizeof(spBuffer));
	if (n < 0)
		error("ERROR 7: Can not Write to Socket");

	printf("The Serial Port Response Has Been Sent To Client\n");

	close(newsocketFileDesc);
	close(socketFileDesc);
	close(sPortFileDesc);
	return 0; 
	}
