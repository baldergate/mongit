#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "socket.h"
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc , char **argv){
  int socket_client;
  int socket_serveur;
  int oui;
  int fd;
  FILE * f;
  char message_client [1024];
 
  http_request essai = {HTTP_GET,0,0,NULL};
  if (argc > 1 && strcmp(argv[1], "-advice") == 0) {
    return 42;
  }
  socket_serveur=creer_serveur(8080);
  initialiser_signaux();
  while((socket_client = accept(socket_serveur , NULL , NULL))!=-1){
    if (socket_client == -1)
      {
	perror("accept");	/* traitement d'erreur */
      }
    if(fork()==0) {
      
      f = fdopen(socket_client,"w+");
      fgets_or_exit(message_client,sizeof(message_client),f);
      skip_headers(f);
      oui=parse_http_request(message_client,&essai);
      fd=check_and_open(essai.url,"/home/infoetu/bonnardm/mongit/webserver");
      if(oui==0){
	send_response(f,400,"Bad Request","Bad Request\r\n");
      }
      else if(essai.method==HTTP_UNSUPPORTED){
	send_response(f,405,"Method not Allowed","Method not Allowed\r\n");
      }
      else if(fd!=-1){
	
	fprintf(f,"HTTP/1.1 200 OK\r\nContent-Length: %d\r\nContent-Type: text\r\n\r\n",get_file_size(fd) );
	copy(fd,socket_client);

      }
      else send_response(f,404,"Not Found","Not Found\r\n");
      exit(0);
    }
    else {
      close(socket_client);     
    }
  }
  return 0;  
}

