#define _CRT_SECURE_NO_WARNINGS

#include "player.h"

#include <stdio.h>
#include <stdlib.h>


int izbornik(PLAYER* player) {

	
	printf("Odaberite opciju :\n");
	printf("\t\t\tOpcija 1: Provjera statusa.\n");
	printf("\t\t\tOpcija 2: Promjenite uloge.\n");
	printf("\t\t\tOpcija 3: START!\n");
	printf("\t\t\tOpcija 4: Informacije mogucih dobitaka. \n");
	printf("\t\t\tOpcija 5: Cash out!\n");
	printf("Ulog: %d kredita\n", player->ulog);



	int uvijet = 1;



	scanf("%d", &uvijet);
	switch (uvijet) {
	case 1:
		provjeraStanja(player); //Provjera stanja igraca
		break;
	case 2:
		promjenaUloga(player);//promjena uloga
		break;
	case 3:
		upis(player);
		break;
	case 4:
		info(); //Info o isplati
		break;
	case 5:
		uvijet = izlazIzPrograma(); //Exit
		break;
	default:
		uvijet = 0;
	}
	return uvijet;
}