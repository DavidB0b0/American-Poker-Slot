#define _CRT_SECURE_NO_WARNINGS



#include "player.h"
#include "izbornik.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int brojac = 0;

int main(void) {

	srand((unsigned)time(NULL));

	FILE* fp = fopen("rezultati.txt", "w");
	fclose(fp);

	int uvijet = 1;

	//stvaranje igraca

	PLAYER* player = (PLAYER*)calloc(1, sizeof(PLAYER));
	if (player == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}

	player->status = 1000;
	player->ulog = 5;
	player->dobitak = 0;



	//zapis pocetnog stanja

	fp = fopen("rezultati.txt", "a");
	if (fp == NULL) {
		printf("Nije moguce otvoriti datoteku za pisanje.\n");
		return;
	}
	fprintf(fp, "VRTNJA\tSTANJE\tULOG\tDOBITAK\n");
	fprintf(fp, "%d\t%d\t%d\t%d\n", brojac, player->status, player->ulog, player->dobitak);
	
	fclose(fp);


	//izbornik
	while (uvijet) {
		uvijet = izbornik(player);
	}


	free(player);

	printf("Hvala vam na igranju!\n");
	return 0;
}