#define _CRT_SECURE_NO_WARNINGS

#include "player.h"

#include <stdio.h>
#include <stdlib.h>

extern int brojac;

//funkcija za provjeru stanja
void provjeraStatusa(PLAYER* player) {

	printf("Stanje: %d kredita\n\n", player->status);

}


//funkcija za promjenu uloga
void promjeniUlog(PLAYER* player) {
	int NoviUlog;

	printf("Unesite novi zeljeni ulog: ");
	scanf("%d", &NoviUlog);


	//provjera dali ne prekoracava stanje na racunu
	while (NoviUlog > player->status) {
		printf("Nemate dovoljno kredita.\n");
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
}


//funkcija zavrsetka programa
int izlazIzPrograma() {
	char c[10] = "";
	char s[] = "ne";

	printf("Da li ste sigurni kako zelite zavrsiti program?\nda/ne\n");
	scanf("%s", c);
	if (!strcmp(c, s)) {

		return 1;
	}
	else {

		return 0;
	}

}