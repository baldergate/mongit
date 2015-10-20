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
  FILE * f;
  char message_client [1024];
  const char *message_bienvenue="Eh bien, c'est l'histoire d'un petit ourson qui s'appelle… Arthur. Et y'a une fée, un jour, qui vient voir le petit ourson et qui lui d it : Arthur tu vas partir à la recherche du Vase Magique. Et elle lui donne une épée hmm… magique (ouais, parce qu'y a plein de trucs magiques dans l'histoire, bref) alors le petit ourson il se dit : \"Heu, chercher le Vase Magique ça doit être drôlement difficile, alors il faut que je parte dans forêt pour trouver des amis pour m'aider.\" Alors il va voir son ami Lancelot… le cerf (parce que le cerf c'est majestueux comme ça), heu, Bohort le faisan et puis Léodagan… heu… l'ours, ouais c'est un ours aussi, c'est pas tout à fait le même ours mais bon. Donc Léodagan qui est le père de la femme du petit ourson, qui s'appelle Guenièvre la truite… non, non, parce que c'est la fille de… non c'est un ours aussi puisque c'est la fille de l'autre ours, non parce qu'après ça fait des machins mixtes, en fait un ours et une truite… non en fait ça va pas. Bref, sinon y'a Gauvain le neveu du petit ourson qui est le fils de sa sœur Anna, qui est restée à Tintagel avec sa mère Igerne la… bah non, ouais du coup je suis obligé de foutre des ours de partout sinon on pige plus rien dans la famille… Donc c'est des ours, en gros, enfin bref… Ils sont tous là et donc Petit Ourson il part avec sa troupe à la recherche du Vase Magique. Mais il le trouve pas, il le trouve pas parce qu'en fait pour la plupart d'entre eux c'est… c'est des nazes : ils sont hyper mous, ils sont bêtes, en plus y'en a qu'ont la trouille. Donc il décide de les faire bruler dans une grange pour s'en débarrasser… Donc la fée revient pour lui dire : \"Attention petit ourson, il faut être gentil avec ses amis de la forêt\" quand même c'est vrai, et du coup Petit Ourson il lui met un taquet dans la tête à la fée, comme ça : \"BAH !\". Alors la fée elle est comme ça et elle s'en va… et voilà et en fait il trouve pas le vase. En fait il est… il trouve pas… et Petit Ourson il fait de la dépression et tous les jours il se demande s'il va se tuer ou… pas…Eh bien, c'est l'histoire d'un petit ourson qui s'appelle… Arthur. Et y'a une fée, un jour, qui vient voir le petit ourson et qui lui dit : Arthur tu vas partir à la recherche du Vase Magique. Et elle lui donne une épée hmm… magique (ouais, parce qu'y a plein de trucs magiques dans l'histoire, bref) alors le petit ourson il se dit :\"Heu, chercher le Vase Magique ça doit être drôlement difficile, alors il faut que je parte dans la forêt pour trouver des amis pour m'aider.\" Alors il va voir son ami Lancelot… le cerf (parce que le cerf c'est majestueux comme ça), heu, Bohort le faisan et puis Léodagan… heu… l'ours, ouais c'est un ours aussi, c'est pas tout à fait le même ours mais bon. Donc Léodagan qui est le père de la femme du petit ourson, qui s'appelle Guenièvre la truite… non, non, parce que c'est la fille de… non c'est un ours aussi puisque c'est la fille de l'autre ours, non parce qu'après ça fait des machins mixtes, en fait un ours et une truite… non en fait ça va pas. Bref, sinon y'a Gauvain le neveu du petit ourson qui est le fils de sa sœur Anna, qui est restée à Tintagel avec sa mère Igerne la… bah non, ouais du coup je suis obligé de foutre des ours de partout sinon on pige plus rien dans la famille… Donc c'est des ours, en gros, enfin bref… Ils sont tous là et donc Petit Ourson il part avec sa troupe à la recherche du Vase Magique. Mais il le trouve pas, il le trouve pas parce qu'en fait pour la plupart d'entre eux c'est… c'est des nazes : ils sont hyper mous, ils sont bêtes, en plus y'en a qu'ont la trouille. Donc il décide de les faire bruler dans une grange pour s'en débarrasser… Donc la fée revient pour lui dire : \"Attention petit ourson, il faut être gentil avec ses amis de la forêt\" quand même c'est vrai, et du coup Petit Ourson il lui met un taquet dans la tête à la fée, comme ça : \"BAH !\". Alors la fée elle est comme ça et elle s'en va… et voilà et en fait il trouve pas le vase. En fait il est… il trouve pas… et Petit Ourson il fait de la dépression et tous les jours il se demande s'il va se tuer ou… pas…";
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
      if(oui==0){
	send_response(f,400,"Bad Request","Bad Request\r\n");
      }
      else if(essai.method==HTTP_UNSUPPORTED){
	send_response(f,405,"Method not Allowed","Method not Allowed\r\n");
      }
      else if(strcmp(essai.url,"/")==0){
	send_response(f,200,"OK",message_bienvenue);
      }
      else send_response(f,404,"Not Found","Not Found\r\n");  
    }
    else {
      close(socket_client);     
    }
  }
  return 0;  
}

