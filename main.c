#define _CRT_SECURE_NO_WARNINGS

#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

	srand((unsigned)time(NULL));

	FILE* fp = fopen("rezultati.txt", "w");
	fclose(fp);

	int uvijet = 1;

	//kreiranje igraca

	PLAYER* player = (PLAYER*)calloc(1, sizeof(PLAYER));
	if (player == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}


	return 0;
}