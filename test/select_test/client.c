#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include "errwrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

int main(int argc, char *argv[])
{
		if(argc<2)
		{
			err_exit("参数过少");
		}
		struct sockaddr_in servaddr;
		char buf[MAXLINE];
		int sockfd, n;
		sockfd = Socket(AF_INET, SOCK_STREAM, 0);
		bzero(&servaddr, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
		servaddr.sin_port = htons(SERV_PORT);
		Connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
		while (fgets(buf, MAXLINE, stdin) != NULL) 
		{
				Write(sockfd, buf, strlen(buf));
				n = Read(sockfd, buf, MAXLINE);
				if (n == 0)
						printf("the other side has been closed.\n");
				else
						Write(STDOUT_FILENO, buf, n);
		}
		Close(sockfd);
		return 0;
}

