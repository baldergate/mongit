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
	char *url;
	char tok [1024];
	char message_client [1024];
	const char *message_bienvenue="Eh bien, c'est l'histoire d'un petit ourson qui s'appelle… Arthur. Et y'a une fée, un jour, qui vient voir le petit ourson et qui lui dit : Arthur tu vas partir à la recherche du Vase Magique. Et elle lui donne une épée hmm… magique (ouais, parce qu'y a plein de trucs magiques dans l'histoire, bref) alors le petit ourson il se dit : \"Heu, chercher le Vase Magique ça doit être drôlement difficile, alors il faut que je parte dans la forêt pour trouver des amis pour m'aider.\" Alors il va voir son ami Lancelot… le cerf (parce que le cerf c'est majestueux comme ça), heu, Bohort le faisan et puis Léodagan… heu… l'ours, ouais c'est un ours aussi, c'est pas tout à fait le même ours mais bon. Donc Léodagan qui est le père de la femme du petit ourson, qui s'appelle Guenièvre la truite… non, non, parce que c'est la fille de… non c'est un ours aussi puisque c'est la fille de l'autre ours, non parce qu'après ça fait des machins mixtes, en fait un ours et une truite… non en fait ça va pas. Bref, sinon y'a Gauvain le neveu du petit ourson qui est le fils de sa sœur Anna, qui est restée à Tintagel avec sa mère Igerne la… bah non, ouais du coup je suis obligé de foutre des ours de partout sinon on pige plus rien dans la famille… Donc c'est des ours, en gros, enfin bref… Ils sont tous là et donc Petit Ourson il part avec sa troupe à la recherche du Vase Magique. Mais il le trouve pas, il le trouve pas parce qu'en fait pour la plupart d'entre eux c'est… c'est des nazes : ils sont hyper mous, ils sont bêtes, en plus y'en a qu'ont la trouille. Donc il décide de les faire bruler dans une grange pour s'en débarrasser… Donc la fée revient pour lui dire : \"Attention petit ourson, il faut être gentil avec ses amis de la forêt\" quand même c'est vrai, et du coup Petit Ourson il lui met un taquet dans la tête à la fée, comme ça : \"BAH !\". Alors la fée elle est comme ça et elle s'en va… et voilà et en fait il trouve pas le vase. En fait il est… il trouve pas… et Petit Ourson il fait de la dépression et tous les jours il se demande s'il va se tuer ou… pas…Eh bien, c'est l'histoire d'un petit ourson qui s'appelle… Arthur. Et y'a une fée, un jour, qui vient voir le petit ourson et qui lui dit : Arthur tu vas partir à la recherche du Vase Magique. Et elle lui donne une épée hmm… magique (ouais, parce qu'y a plein de trucs magiques dans l'histoire, bref) alors le petit ourson il se dit :\"Heu, chercher le Vase Magique ça doit être drôlement difficile, alors il faut que je parte dans la forêt pour trouver des amis pour m'aider.\" Alors il va voir son ami Lancelot… le cerf (parce que le cerf c'est majestueux comme ça), heu, Bohort le faisan et puis Léodagan… heu… l'ours, ouais c'est un ours aussi, c'est pas tout à fait le même ours mais bon. Donc Léodagan qui est le père de la femme du petit ourson, qui s'appelle Guenièvre la truite… non, non, parce que c'est la fille de… non c'est un ours aussi puisque c'est la fille de l'autre ours, non parce qu'après ça fait des machins mixtes, en fait un ours et une truite… non en fait ça va pas. Bref, sinon y'a Gauvain le neveu du petit ourson qui est le fils de sa sœur Anna, qui est restée à Tintagel avec sa mère Igerne la… bah non, ouais du coup je suis obligé de foutre des ours de partout sinon on pige plus rien dans la famille… Donc c'est des ours, en gros, enfin bref… Ils sont tous là et donc Petit Ourson il part avec sa troupe à la recherche du Vase Magique. Mais il le trouve pas, il le trouve pas parce qu'en fait pour la plupart d'entre eux c'est… c'est des nazes : ils sont hyper mous, ils sont bêtes, en plus y'en a qu'ont la trouille. Donc il décide de les faire bruler dans une grange pour s'en débarrasser… Donc la fée revient pour lui dire : \"Attention petit ourson, il faut être gentil avec ses amis de la forêt\" quand même c'est vrai, et du coup Petit Ourson il lui met un taquet dans la tête à la fée, comme ça : \"BAH !\". Alors la fée elle est comme ça et elle s'en va… et voilà et en fait il trouve pas le vase. En fait il est… il trouve pas… et Petit Ourson il fait de la dépression et tous les jours il se demande s'il va se tuer ou… pas…";
	const char *erreur = "HTTP/1.1 400 Bad Request\r\nConnection: Close\r\nContent-Length: 17 \r\n\n400 Bad request";
	const char *bon = "HTTP/1.1 200 OK\r\nContent-Length: ";
	const char *pastrouve =  "404 NOT FOUND\r\n";
	
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
	    url=strtok(NULL," ");
	    resource = strtok(NULL," ");
	    strtok(resource,"/");
	    if(strcmp(url,"/")){
	      
	      fprintf(f,"%s", pastrouve);
	      fclose(f);
	    }
	    version = strtok(NULL,"/");
	    if (!strcmp(methode,"GET")){
	      
	      if(!strcmp(version,"1.1\r\n")){
		printf("1.1\n");
	      }
	      
	      if(!strcmp(version,"1.0\r\n")){
		printf("1.0\n");
	      }
	      
	      fprintf(f,"<mongit> %s %s : %d \n %s\n",message_client, bon,(int)strlen(message_bienvenue),message_bienvenue);
	      fclose(f);
	    }
	    else {
	      fprintf(f,"%s",erreur);
	      fflush(f);
	    }
	  }
	  else {
	    close(socket_client);
	    
	    
	    
	  }
	}
	return 0;
	
}

	
	
