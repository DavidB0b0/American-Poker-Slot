#define _CRT_SECURE_NO_WARNINGS

#include "player.h"
#include "poker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int brojac = 0;


//funkcija za promjenu uloga
void promjeniUlog(PLAYER* player) {

	int NoviUlog;

	printf("Unesite zeljeni ulog: ");
	scanf("%d", &NoviUlog);


	//provjera dali ne prekoracava stanje na racunu
	while (NoviUlog > player->status) {
		printf("Nemate dovoljno kredita za igranje.\n");
		printf("Unesite zeljeni ulog: ");
		scanf("%d", &NoviUlog);
	}

	player->ulog = NoviUlog;

}


//upis rezultata u datoteku
void upis(PLAYER* player) {

	
	FILE* fp = fopen("rezultati.txt", "a");
	if (fp == NULL) {
		printf("Nije moguce otvoriti datoteku za pisanje.\n");
		return;
	}
	brojac++;
	fprintf(fp, "%d\t%d\t%d\t%d\n", brojac, player->status, player->ulog, player->dobitak);


	fclose(fp);

}


//funkcija za informaciju o dobitcima
void info() {
	printf("Royal flush : x300\n");
	printf("Str flush   : x80\n");
	printf("4 of kinds  : x40\n");
	printf("Full house  : x12\n");
	printf("Flush       : x9\n");
	printf("Straight    : x7\n");
	printf("3 of kinds  : x5\n");
	printf("2 pairs     : x3\n");
	printf("pairs       : x1\n");
}


//funkcija zavrsetka programa
int izlazIzPrograma(PLAYER* player) {
	char c[10] = "";
	char s[] = "da";

	printf("Jeste li sigurni da zelite zatvoriti porgram ?\nda\nne\n");;
	scanf("%s", c);
	if (!strcmp(c, s)) {

		FILE* fp = fopen("rezultati.txt", "a");
		if (fp == NULL) {
			printf("Nije moguce otvoriti datoteku za pisanje.\n");
			return;
		}
		fprintf(fp, "ISPLACENO:%d", player->status);
		return 0;
	}
	else {
		return 1;
	}

}

