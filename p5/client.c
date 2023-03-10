#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

void str_cli(FILE *fp, int sockfd)
{
  int n = 1024, cont;
  char *buf = malloc(n);
  while (fgets(buf, n, fp) != NULL)
  {
    printf("\nEnter the string:\n");
    send(sockfd, buf, n, 0);
    while ((n = recv(sockfd, buf, n, 0)) < 0)
      ;
    fputs(buf, stdout);
  }
  printf("\nEOF\n");
}
int main(int argc, char *argv[])
{
  int sockfd;
  struct sockaddr_in servaddr;
  printf("%s\n", argv[1]);
  if (sockfd = socket(AF_INET, SOCK_STREAM, 0))
    printf("\nSocket created\n");
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(15001);
  servaddr.sin_addr.s_addr = inet_addr(argv[1]);
  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  str_cli(stdin, sockfd);
  close(sockfd);
}