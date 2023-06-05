#define _CRT_SECURE_NO_WARNINGS

#include "player.h"
#include "funkcije.h"
#include "poker.h"
#include <stdio.h>
#include <stdlib.h>


int izbornik(PLAYER* player) {

	printf("----------------------------------------------------------------\n");
	printf("\nOdaberite opciju :\n");
	printf("\t\t\tOpcija 1: START!\n");
	printf("\t\t\tOpcija 2: Promjenite uloge.\n");
	printf("\t\t\tOpcija 3: Informacije mogucih dobitaka. \n");
	printf("\t\t\tOpcija 4: Cash out!\n");
	printf("Status: %d kredita\n\n", player->status);
	printf("Ulog: %d kredita\n", player->ulog);
	printf("----------------------------------------------------------------\n");


	int uvijet = 1;



	scanf("%d", &uvijet);
	switch (uvijet) {
	case 1:
		start(player);
		upis(player);
		break;
	case 2:
		promjeniUlog(player);  //promjena uloga
		break;
	case 3:
		info(); //Informacije o dobitcima
		break;
	case 4:
		uvijet = izlazIzPrograma(player); //Kraj
		break;
	default:
		uvijet = 0;
	}
	return uvijet;
}