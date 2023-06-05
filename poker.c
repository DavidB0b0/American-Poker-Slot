#define _CRT_SECURE_NO_WARNINGS

#include "player.h"
#include "hand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define HAND_SIZE 5
#define NUM_RANKS 13
#define NUM_SUITS 4

static int dobitak = 0;

//brojevi karata
enum Rank {
	Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};

//simboli karata
enum Suit {
	Clubs, Diamonds, Hearts, Spades
};


//inicijalizacija deka
void stvaranjeDeka(Card deck[]) {
	int i, j, index = 0;
	for (i = 0; i < NUM_RANKS; i++) {
		for (j = 0; j < NUM_SUITS; j++) {
			deck[index].rank = i + 1;
			deck[index].suit = j;
			index++;
		}
	}
}

//funkcija za mjesanje deka

void mjesanjeDeka(Card deck[]) {
	int i, j;
	Card temp;
	for (i = 0; i < NUM_RANKS * NUM_SUITS; i++) {
		j = rand() % (NUM_RANKS * NUM_SUITS);
		temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}

//ispis karte

void printCard(Card card) {
	switch (card.rank) {
	case Ace:
		printf("Ace");
		break;
	case Two:
		printf("2");
		break;
	case Three:
		printf("3");
		break;
	case Four:
		printf("4");
		break;
	case Five:
		printf("5");
		break;
	case Six:
		printf("6");
		break;
	case Seven:
		printf("7");
		break;
	case Eight:
		printf("8");
		break;
	case Nine:
		printf("9");
		break;
	case Ten:
		printf("10");
		break;
	case Jack:
		printf("J");
		break;
	case Queen:
		printf("Q");
		break;
	case King:
		printf("K");
		break;
	}

	switch (card.suit) {
	case Clubs:
		printf("C");
		break;
	case Diamonds:
		printf("D");
		break;
	case Hearts:
		printf("H");
		break;
	case Spades:
		printf("S");
		break;
	}
}

//ispis ruke

void printHand(Card hand[]) {
	int i;
	printf("\n");
	for (i = 0; i < HAND_SIZE; i++) {
		printCard(hand[i]);
		printf("\t");
	}

}

//izvlacenje karte

void drawCards(Card deck[], Card hand[]) {
	int i;
	for (i = 0; i < HAND_SIZE; i++) {
		hand[i] = deck[i];
	}
}

//funkcija za provjeru parova

int Pairs(Card hand[]) {
	int ranks[NUM_RANKS] = { 0 };
	int i;

	for (i = 0; i < HAND_SIZE; i++) {
		ranks[hand[i].rank - 1]++;
	}

	for (i = 0; i < NUM_RANKS; i++) {
		if (ranks[i] == 2) {
			return 1;
		}
	}

	return 0;
}

//funkcija za provjeru 2 para

int TwoPairs(Card hand[]) {
	int ranks[NUM_RANKS] = { 0 };
	int i, pairs = 0;

	for (i = 0; i < HAND_SIZE; i++) {
		ranks[hand[i].rank - 1]++;
	}

	for (i = 0; i < NUM_RANKS; i++) {
		if (ranks[i] == 2) {
			pairs++;
		}
	}

	return pairs == 2;
}

//funkcija za provjeru trisa

int ThreeOfAKind(Card hand[]) {
	int ranks[NUM_RANKS] = { 0 };
	int i;

	for (i = 0; i < HAND_SIZE; i++) {
		ranks[hand[i].rank - 1]++;
	}

	for (i = 0; i < NUM_RANKS; i++) {
		if (ranks[i] == 3) {
			return 1;
		}
	}

	return 0;
}

//funkcija za provjeru skale

int Straight(Card hand[]) {
	int ranks[NUM_RANKS] = { 0 };
	int i;

	for (i = 0; i < HAND_SIZE; i++) {
		ranks[hand[i].rank - 1]++;
	}

	for (i = 0; i < NUM_RANKS - 4; i++) {
		if (ranks[i] && ranks[i + 1] && ranks[i + 2] && ranks[i + 3] && ranks[i + 4]) {
			return 1;
		}
	}

	// Slucaj 10-Jack-Queen-King-Ace

	if (ranks[Ten - 1] && ranks[Jack - 1] && ranks[Queen - 1] && ranks[King - 1] && ranks[Ace - 1]) {
		return 1;
	}

	return 0;
}

//funkcija za provjeru boje

int Flush(Card hand[]) {
	int suits[NUM_SUITS] = { 0 };
	int i;

	for (i = 0; i < HAND_SIZE; i++) {
		suits[hand[i].suit]++;
	}

	for (i = 0; i < NUM_SUITS; i++) {
		if (suits[i] == HAND_SIZE) {
			return 1;
		}
	}

	return 0;
}

//funkcija za provjeru full housa

int FullHouse(Card hand[]) {
	return ThreeOfAKind(hand) && Pairs(hand);
}

//funkcija za provjeru 4 ista

int FourOfAKind(Card hand[]) {
	int ranks[NUM_RANKS] = { 0 };
	int i;

	for (i = 0; i < HAND_SIZE; i++) {
		ranks[hand[i].rank - 1]++;
	}

	for (i = 0; i < NUM_RANKS; i++) {
		if (ranks[i] == 4) {
			return 1;
		}
	}

	return 0;
}
//funkcija za provjeru skale u boji
int StrFlush(Card hand[]) {
	return Straight(hand) && Flush(hand);
}

//funkcija za provjeru royal flusha
int RoyalFlush(Card hand[]) {
	int ranks[NUM_RANKS] = { 0 };
	int i;

	for (i = 0; i < HAND_SIZE; i++) {
		ranks[hand[i].rank - 1]++;
	}

	return ranks[Ten - 1] && ranks[Jack - 1] && ranks[Queen - 1] && ranks[King - 1] && ranks[Ace - 1] && Flush(hand);
}

//izracun dobitka
int izracunajHand(PLAYER* player, Card hand[]) {
	if (RoyalFlush(hand)) {
		printf("ROYAL FLUSH");
		dobitak = player->ulog * 300;
		return dobitak;
	}
	else if (StrFlush(hand)) {
		printf("STRAIGHT FLUSH");
		dobitak = player->ulog * 80;
		return dobitak;
	}
	else if (FourOfAKind(hand)) {
		printf("FOUR OF KIND");
		dobitak = player->ulog * 40;
		return dobitak;
	}
	else if (FullHouse(hand)) {
		printf("FULL HOUSE");
		dobitak = player->ulog * 12;
		return dobitak;
	}
	else if (Flush(hand)) {
		printf("BOJA");
		dobitak = player->ulog * 9;
		return dobitak;
	}
	else if (Straight(hand)) {
		printf("SKALA");
		dobitak = player->ulog * 7;
		return dobitak;
	}
	else if (ThreeOfAKind(hand)) {
		printf("TRIS");
		dobitak = player->ulog * 5;
		return dobitak;
	}
	else if (TwoPairs(hand)) {
		printf("DVA PARA");
		dobitak = player->ulog * 3;
		return dobitak;
	}
	else if (Pairs(hand)) {
		printf("JEDAN PAR");
		dobitak = player->ulog * 1;
		return dobitak;;
	}
	else return 0;
}

//pretrazivanje najveceg dobitka

void pretragNajDobitka(PLAYER* player) {

	if (player->najDobitak < player->dobitak) {

		player->najDobitak = player->dobitak;

	}

}


void start(PLAYER* player) {

	int najUlog = 0;

	Card deck[NUM_RANKS * NUM_SUITS];
	Card hand[HAND_SIZE];

	if (player->status < player->ulog) {
		printf("Nedovoljno kredita!\n");
		return;
	}

	stvaranjeDeka(deck);
	mjesanjeDeka(deck);


	printf("\nVasa Ruka:\n");
	drawCards(deck, hand);
	printHand(hand);
	int score = izracunajHand(player, hand);
	printf("\nRezultat: %d\n\n", score);

	pretragNajDobitka(player);

	player->status = player->status - player->ulog;
	player->status = player->status + dobitak;
	player->dobitak = dobitak;
	dobitak = 0;



}