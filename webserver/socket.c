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

int creer_serveur(int port){
	int socket_serveur;
	int socket_client;
	struct sockaddr_in saddr;

	socket_serveur = socket(AF_INET,SOCK_STREAM,0);
	if (socket_serveur ==-1){
	  
	  perror("socket_serveur");		/*traitement de l'erreur*/
	  
	}/* Utilisation de la socket*/
	

	saddr.sin_family = AF_INET;		/* Socket ipv4 */
	saddr.sin_port = htons(port);	/* Port d’écoute */
	saddr.sin_addr.s_addr = INADDR_ANY;	/* écoute sur toutes les interfaces */
	
	if (bind(socket_serveur , (struct sockaddr *)&saddr , sizeof(saddr)) == -1)
	{
		perror("bind socker_serveur");	/* traitement de l’erreur */
	}

	if (listen(socket_serveur , 10) == -1)
	{
		perror("listen socket_serveur");	/* traitement d’erreur */
	}


	while((socket_client = accept(socket_serveur , NULL , NULL))!=-1){
	  if (socket_client == -1)
	    {
	      perror("accept");	/* traitement d’erreur */
	    }
	  
	  /* On peut maintenant dialoguer avec le client */
	  const char *message_bienvenue = "Eh bien, c'est l'histoire d'un petit ourson qui s'appelle… Arthur. Et y'a une fée, un jour, qui vient voir le petit ourson et qui lui dit : Arthur tu vas partir à la recherche du Vase Magique. Et elle lui donne une épée hmm… magique (ouais, parce qu'y a plein de trucs magiques dans l'histoire, bref) alors le petit ourson il se dit : \"Heu, chercher le Vase Magique ça doit être drôlement difficile, alors il faut que je parte dans la forêt pour trouver des amis pour m'aider.\" Alors il va voir son ami Lancelot… le cerf (parce que le cerf c'est majestueux comme ça), heu, Bohort le faisan et puis Léodagan… heu… l'ours, ouais c'est un ours aussi, c'est pas tout à fait le même ours mais bon. Donc Léodagan qui est le père de la femme du petit ourson, qui s'appelle Guenièvre la truite… non, non, parce que c'est la fille de… non c'est un ours aussi puisque c'est la fille de l'autre ours, non parce qu'après ça fait des machins mixtes, en fait un ours et une truite… non en fait ça va pas. Bref, sinon y'a Gauvain le neveu du petit ourson qui est le fils de sa sœur Anna, qui est restée à Tintagel avec sa mère Igerne la… bah non, ouais du coup je suis obligé de foutre des ours de partout sinon on pige plus rien dans la famille… Donc c'est des ours, en gros, enfin bref… Ils sont tous là et donc Petit Ourson il part avec sa troupe à la recherche du Vase Magique. Mais il le trouve pas, il le trouve pas parce qu'en fait pour la plupart d'entre eux c'est… c'est des nazes : ils sont hyper mous, ils sont bêtes, en plus y'en a qu'ont la trouille. Donc il décide de les faire bruler dans une grange pour s'en débarrasser… Donc la fée revient pour lui dire : \"Attention petit ourson, il faut être gentil avec ses amis de la forêt\" quand même c'est vrai, et du coup Petit Ourson il lui met un taquet dans la tête à la fée, comme ça : \"BAH !\". Alors la fée elle est comme ça et elle s'en va… et voilà et en fait il trouve pas le vase. En fait il est… il trouve pas… et Petit Ourson il fait de la dépression et tous les jours il se demande s'il va se tuer ou… pas…\n";
	  
	  if(fork()==0){
	    write(socket_client , message_bienvenue , strlen(message_bienvenue));
	    exit(0);
	  }
	}
	return 0;
}
