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
/*8.2 = 20 git tag stats*/



char *fgets_or_exit(char *buffer, int size, FILE *stream) {
  if(fgets(buffer, size, stream) == NULL){ 
    printf("Erreur!\n");
    exit(1); 
  }
  return buffer;
}

int parse_http_request(const char *request_line, http_request *request){
  char *methode;
  char *resource;
  char *toto=" " ;
  char *url;
  toto =strdup(request_line);
  methode = strtok(toto," ");
  url=strtok(NULL," ");

  resource = strtok(NULL," ");
    request->url=rewrite_url(url);
  printf("[%s][%s][%s]\n",methode,request->url,resource);
  if(strncmp(resource,"HTTP/1.0\r\n",10)){
    request->major_version =1;
    request->minor_version =0;
  }
  else if(strncmp(resource,"HTTP/1.1\r\n",10)){
    request->major_version =1;
    request->minor_version =1;
  }
  if (!strcmp(methode,"GET")){
    request->method=HTTP_GET;
  }
  else{
    request->method=HTTP_UNSUPPORTED;
    return 0;
  }
  return 1;
  
}

void skip_headers(FILE *client){
  char tok [1024];
  while(fgets(tok,sizeof(tok),client)!=NULL && tok[0] != '\r' && tok[1]!= '\n' );
}

void send_status(FILE *client, int code, const char *reason_phrase){
  fprintf(client,"HTTP/1.1 %d %s\r\n",code, reason_phrase);
  fflush(client);
}

void send_response(FILE *client, int code, const char *reason_phrase, const char * message_body){
  send_status(client,code,reason_phrase);
  fprintf(client,"Content-Length: %d\r\n\r\n%s",(int)strlen(message_body)+2,message_body);
  fflush(client);
}

char *rewrite_url(char *url){
  char *url1;
  url1 = strtok(url,"?");
  return url1;
  
}

int check_and_open(const char *url, const char *document_root){
  char *toto ="";
  char *tata ="";
  char titi [512]="";
  int fd;
  toto=strdup(url);
  tata=strdup(document_root);
  strcat(titi,tata);
  strcat(titi,toto);
  fd=open(titi,O_RDONLY);
  if(fd!=-1){
    printf("1\n");
    return fd;
  }
  else{
        printf("2\n");
    return -1;
  } 
}

int get_file_size(int fd){ 
  struct stat s;
  if(fstat(fd,&s)==0){
    return s.st_size;
  }
  return 0;
  
}

int copy(int in, int out){
  char buff [1024];
  int ok;
  ok=read(in, buff, strlen(buff));
  if(ok!=-1){
    write(out, buff, strlen(buff));
  }
  return 0;
}


int creer_serveur(int port){
  int socket_serveur;
  
  struct sockaddr_in saddr;
  
  socket_serveur = socket(AF_INET,SOCK_STREAM,0);
  if (socket_serveur ==-1){
    
    perror("socket_serveur");		/*traitement de l'erreur*/
    
  }/* Utilisation de la socket*/
  
  
  saddr.sin_family = AF_INET;		/* Socket ipv4 */
  saddr.sin_port = htons(port);	/* Port d’écoute */
  saddr.sin_addr.s_addr = INADDR_ANY;	/* écoute sur toutes les interfaces */

  int optval = 1;
  if (setsockopt(socket_serveur, SOL_SOCKET , SO_REUSEADDR , &optval , sizeof(int)) == -1)
    perror("Can not set SO_REUSEADDR option");

  if (bind(socket_serveur , (struct sockaddr *)&saddr , sizeof(saddr)) == -1)
    {
      perror("bind socker_serveur");	/* traitement de l’erreur */
    }
  
  if (listen(socket_serveur , 10) == -1)
    {
      perror("listen socket_serveur");	/* traitement d’erreur */
    }	
  return socket_serveur;
}


void traitement_signal(int sig)
{
  printf("Signal %d reçu\n", sig);
  waitpid(-1, &sig, WNOHANG);
}

void initialiser_signaux(void)
{
  struct sigaction sa;
  sa.sa_handler = traitement_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGCHLD , &sa, NULL) == -1)
    {
      perror("sigaction(SIGCHLD)");
    }
  if(signal(SIGPIPE,SIG_IGN)==SIG_ERR){
    perror("signal");
  }
}
