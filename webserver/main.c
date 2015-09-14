#include <stdio.h>
#include <string.h>
#include "socket.h"

int main(int argc , char **argv){
	
	if (argc > 1 && strcmp(argv[1], "-advice") == 0) {
		
	
		return 42;
	}
	creer_serveur(8080);
	return 0;
	

	



}


