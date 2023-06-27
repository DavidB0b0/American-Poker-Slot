#define _CRT_SECURE_NO_WARNINGS

#include "player.h"
#include "poker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>





//funkcija promjene uloga
void promjeniUlog(PLAYER* player) {

	int NoviUlog;

	printf("Unesite zeljeni ulog: ");
	scanf("%d", &NoviUlog);


	//provjera je li je ulog veci nego status
	while (NoviUlog > player->status) {
		printf("Nemate dovoljno kredita za igranje.\n");
		printf("Unesite zeljeni ulog: ");
		scanf("%d", &NoviUlog);
	}

	player->ulog = NoviUlog;

}

void provjeriStanje(PLAYER* player) {
	printf("Status: %d\n", player->status);
	printf("Ulog: %d\n", player->ulog);
}


//upis rezultata u datoteku
void upis(PLAYER* player, int brojPlayera,int br) {

	
	FILE* fp = fopen("rezultati.txt", "a");
	if (fp == NULL) {
		printf("Nije moguce otvoriti datoteku za pisanje.\n");
		return;
	}
	
	fprintf(fp, "%d\t%s\t%d\t%d\t%d\n", br, player->ime, player->status, player->ulog, player->dobitak);

	
	fclose(fp);

}
  //funkcija za pretrazivanje igraca
void pretraziIgraca(PLAYER* player, int brojPlayera) {
	char trazenoIme[50];
	printf("Unesite ime : ");
	scanf("%s", trazenoIme);

	int pronaden = 0;
	int i;

	for (i = 0; i < brojPlayera; i++) {
		if (strcmp(player[i].ime, trazenoIme) == 0) {
			
			printf("Ime: %s\n", player[i].ime);
			printf("Stanje: %d\n", player[i].status);
			printf("Najveci dobitak: %d\n", player[i].najDobitak);
			pronaden = 1;
			break;
		}
	}

	if (!pronaden) {
		printf("Igrac ne postoji.\n");
	}
}

// funkcija za sortiranje igraca

void sortiranje(PLAYER* player, int brojPlayera) {
	int i, j;
	PLAYER temp;

	
	for (i = 0; i < brojPlayera - 1; i++) {
		for (j = 0; j < brojPlayera - i - 1; j++) {
			if (player[j].najDobitak < player[j + 1].najDobitak) {
				temp = player[j];
				player[j] = player[j + 1];
				player[j + 1] = temp;
			}
		}
	}

	FILE* Fp = fopen("highscore.txt", "w");


	for (i = 0; i < brojPlayera; i++) {
		fprintf(Fp, "PLAYER: %s - NAJVECI DOBITAK: %d\n", player[i].ime, player[i].najDobitak);
	}

	fclose(Fp);
}
