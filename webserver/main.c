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
#include "socket.h"

int main(int argc , char **argv){
  	int socket_client;
	int socket_serveur;
	FILE * f;
	char *methode;
	char *version;
	char *resource;
	char tok [1024];
	char message_client [1024];
	const char *erreur = "HTTP/1.1 400 Bad Request\r\nConnection: Close\r\nContent-Length: 17 \r\n\n400 Bad request";
	/*	const char *bon = "HTTP/1.1 200 Bad Request\r\nConnection: Close\r\nContent-Length: ";*/

	
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
	  
	  /* On peut maintenant dialoguer avec le client */
	  
	  if(fork()==0) {
	    f = fdopen(socket_client,"w+");
	    
	    fgets(message_client,sizeof(message_client),f);
	    while(fgets(tok,sizeof(tok),f)!=NULL && tok[0] != '\r' && tok[0]!= '\n' );
	    printf("%s",message_client);
	    
	    methode = strtok(message_client," ");
	    strtok(NULL," ");
	    resource = strtok(NULL," ");
	    strtok(resource,"/");
	    version = strtok(NULL,"/");
	    
	    printf("fin requete\n");
	    if (!strcmp(methode,"GET")){
	      
	      
	      
	      if(!strcmp(version,"1.1\r\n")){
		printf("1.1\n");
	      }
	      
	      if(!strcmp(version,"1.0\r\n")){
			printf("1.0\n");
	      }
	      
	      fprintf(f,"<mongit> %s\n",message_client);
	      fclose(f);
	    }
	    
	    
	    
	    else {
	      fprintf(f,"%s",erreur);
	    }
	  }
	  else {
	    close(socket_client);
	    
	    
	    
	  }
	}
	return 0;
	
}

	
	
