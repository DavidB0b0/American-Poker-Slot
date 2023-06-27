#define _CRT_SECURE_NO_WARNINGS



#include "player.h"
#include "funkcije.h"
#include "poker.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int brojac = 0;

int main(void) {

	int izbor;
	int brojPlayera = 0;
    int br = 0;
	PLAYER* player = NULL;

	srand((unsigned)time(NULL));

	FILE* fp = fopen("rezultati.txt", "w");
	fclose(fp);

    char c[10] = "";
    char s[] = "da";
	//kreiranje igraca

	PLAYER noviPlayer;
	printf("Unesite ime igraca: ");
	scanf("%s", noviPlayer.ime);
    noviPlayer.status = 1000;
    noviPlayer.ulog = 10;
    noviPlayer.dobitak = 0;
    noviPlayer.najDobitak = 0;

	player = realloc(player, (brojPlayera + 1) * sizeof(PLAYER));
	player[brojPlayera++] = noviPlayer;

	printf("Igrac je uspjesno kreiran.\n");



	//zapisivanje pocetnog stanja



	fp = fopen("rezultati.txt", "a");
	if (fp == NULL) {
		printf("Nije moguce otvoriti datoteku za pisanje.\n");
		return;
	}
	fprintf(fp, "VRTNJA\tPLAYER\tSTATUS\tULOG\tDOBITAK\n");
    fprintf(fp, "%d\t%s\t%d\t%d\t%d\n",brojac,player->ime, player->status, player->ulog, player->dobitak);

	fclose(fp);

    FILE* Fp = fopen("highscore.txt", "w");
    fclose(Fp);


    do {
        printf("----------------------------------------------------------------\n");
        printf("\nOdaberite opciju :\n");
        printf("\t\t\tOpcija 1: START!\n");
        printf("\t\t\tOpcija 2: Promjenite uloge.\n");
        printf("\t\t\tOpcija 3: Novi player.\n");
        printf("\t\t\tOpcija 4: Informacije mogucih dobitaka. \n");
        printf("\t\t\tOpcija 5: Pretrazite playera.\n");
        printf("\t\t\tOpcija 6: Cash out!\n");
        int i = brojPlayera - 1;
        provjeriStanje(&player[i]);
        printf("----------------------------------------------------------------\n");

        scanf("%d", &izbor);

        switch (izbor) {
        case 1: {
            int indeks = brojPlayera - 1;
            br++;
            start(&player[indeks]);
            upis(&player[indeks], brojPlayera,br);
            break;
        }
        case 2: {
            // Promjena uloga igraca

            promjeniUlog(&player[brojPlayera - 1]);

            break;
        }
        case 3: {
            // Kreiranje novog igraca

            PLAYER noviPlayer;
            printf("Unesite ime igraca: ");
            scanf("%s", noviPlayer.ime);
            noviPlayer.status = 1000;
            noviPlayer.ulog = 10;
            noviPlayer.dobitak = 0;
            noviPlayer.najDobitak = 0;

            player = realloc(player, (brojPlayera + 1) * sizeof(PLAYER));
            player[brojPlayera++] = noviPlayer;
            
            printf("Igrac je uspjesno kreiran.\n");

            br = 0;
            int indeks = brojPlayera - 1;
            upis(&player[indeks], brojPlayera, br);

            break;
        }
        case 4: {
            printf("Royal flush : x300\n");
            printf("Str flush   : x80\n");
            printf("4 of kinds  : x40\n");
            printf("Full house  : x12\n");
            printf("Flush       : x9\n");
            printf("Straight    : x7\n");
            printf("3 of kinds  : x5\n");
            printf("2 pairs     : x3\n");
            printf("pairs       : x1\n");
            break;
        }
        case 5:
            pretraziIgraca(player, brojPlayera);
            break;
        case 6:

            printf("Jeste li sigurni da zelite zatvoriti porgram ?\nda\nne\n");;
            scanf("%s", c);
            if (!strcmp(c, s)) {

                sortiranje(player, brojPlayera);
                izbor = 0;
                break;
               
            }
            else {
                break;
            }
        default:
            printf("Neispravan odabir. Molimo odaberite ponovno.\n");
        }

        printf("\n");

    } while (izbor != 0);

    free(player);
	return 0;
}