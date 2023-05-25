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

enum Rank {
    Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};

enum Suit {
    Clubs, Diamonds, Hearts, Spades
};



void initializeDeck(Card deck[]) {
    int i, j, index = 0;
    for (i = 0; i < NUM_RANKS; i++) {
        for (j = 0; j < NUM_SUITS; j++) {
            deck[index].rank = i + 1;
            deck[index].suit = j;
            index++;
        }
    }
}

void shuffleDeck(Card deck[]) {
    int i, j;
    Card temp;
    for (i = 0; i < NUM_RANKS * NUM_SUITS; i++) {
        j = rand() % (NUM_RANKS * NUM_SUITS);
        temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }
}

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

void printHand(Card hand[]) {
    int i;
    for (i = 0; i < HAND_SIZE; i++) {
        printCard(hand[i]);
        printf("\t");
    }
}

void drawCards(Card deck[], Card hand[]) {
    int i;
    for (i = 0; i < HAND_SIZE; i++) {
        hand[i] = deck[i];
    }
}



int isPair(Card hand[]) {
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

int isTwoPair(Card hand[]) {
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

int isThreeOfAKind(Card hand[]) {
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

int isStraight(Card hand[]) {
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

    // Special case: Ten Jack Queen King Ace
    if (ranks[Ten - 1] && ranks[Jack - 1] && ranks[Queen - 1] && ranks[King - 1] && ranks[Ace - 1]) {
        return 1;
    }

    return 0;
}

int isFlush(Card hand[]) {
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

int isFullHouse(Card hand[]) {
    return isThreeOfAKind(hand) && isPair(hand);
}

int isFourOfAKind(Card hand[]) {
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

int isStraightFlush(Card hand[]) {
    return isStraight(hand) && isFlush(hand);
}

int isRoyalFlush(Card hand[]) {
    int ranks[NUM_RANKS] = { 0 };
    int i;

    for (i = 0; i < HAND_SIZE; i++) {
        ranks[hand[i].rank - 1]++;
    }

    return ranks[Ten - 1] && ranks[Jack - 1] && ranks[Queen - 1] && ranks[King - 1] && ranks[Ace - 1] && isFlush(hand);
}

int evaluateHand(PLAYER* player,Card hand[]) {
    if (isRoyalFlush(hand)) {
        printf("ROYAL FLUSH");
        dobitak = player->ulog * 300;
        return 250;
    }
    else if (isStraightFlush(hand)) {
        printf("STRAIGHT FLUSH");
        dobitak = player->ulog * 80;
        return 50;
    }
    else if (isFourOfAKind(hand)) {
        printf("FOUR OF KIND");
        dobitak = player->ulog * 40;
        return 25;
    }
    else if (isFullHouse(hand)) {
        printf("FULL HOUSE");
        dobitak = player->ulog * 12;
        return 9;
    }
    else if (isFlush(hand)) {
        printf("BOJA");
        dobitak = player->ulog * 9;
        return 6;
    }
    else if (isStraight(hand)) {
        printf("SKALA");
        dobitak = player->ulog * 7;
        return 4;
    }
    else if (isThreeOfAKind(hand)) {
        printf("TRIS");
        dobitak = player->ulog * 5;
        return 3;
    }
    else if (isTwoPair(hand)) {
        printf("DVA PARA");
        dobitak = player->ulog * 3;
        return 2;
    }
    else if (isPair(hand)) {
        printf("JEDAN PAR");
        dobitak = player->ulog * 1;
        return 1;
    }
    else return 0;
}

void start(PLAYER* player) {

   

    Card deck[NUM_RANKS * NUM_SUITS];
    Card hand[HAND_SIZE];

    if (player->status < player->ulog) {
        printf("Nedovoljno kredita!\n");
        return;
    }

    initializeDeck(deck);
    shuffleDeck(deck);


        printf("Nova ruka:\n");
        drawCards(deck, hand);
        printHand(hand);
        int score = evaluateHand(player,hand);
        printf("\nRezultat: %d\n\n", score);

        player->status = player->status - player->ulog;
        player->status = player->status + dobitak;
        player->dobitak = dobitak;
        dobitak = 0;
        
    
}