#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HAND_SIZE 5
#define NUM_RANKS 13
#define NUM_SUITS 4

enum Rank {
    Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King
};

enum Suit {
    Clubs, Diamonds, Hearts, Spades
};

typedef struct {
    enum Rank rank;
    enum Suit suit;
} Card;

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

int evaluateHand(Card hand[]) {
    if (isRoyalFlush(hand)) {
        printf("ROYAL FLUSH");
        return 250;
    }
    else if (isStraightFlush(hand)) {
        printf("STRAIGHT FLUSH");
        return 50;
    }
    else if (isFourOfAKind(hand)) {
        printf("FOUR OF KIND");
        return 25;
    }
    else if (isFullHouse(hand)) {
        printf("FULL HOUSE");
        return 9;
    }
    else if (isFlush(hand)) {
        printf("BOJA");
        return 6;
    }
    else if (isStraight(hand)) {
        printf("SKALA");
        return 4;
    }
    else if (isThreeOfAKind(hand)) {
        printf("TRIS");
        return 3;
    }
    else if (isTwoPair(hand)) {
        printf("DVA PARA");
        return 2;
    }
    else if (isPair(hand)) {
        printf("JEDAN PAR");
        return 1;
    }
    else return 0;
}

int main() {
    srand(time(NULL));

    Card deck[NUM_RANKS * NUM_SUITS];
    Card hand[HAND_SIZE];

    initializeDeck(deck);
    shuffleDeck(deck);

    printf("Dobrodosli na American Poker!\n\n");

    while (1) {
        printf("Nova ruka:\n");
        drawCards(deck, hand);
        printHand(hand);

        int score = evaluateHand(hand);
        printf("\nRezultat: %d\n\n", score);

        printf("Zelite li igrati ponovo? (1 - da, 0 - ne): ");
        int again;
        scanf("%d", &again);
        if (again = 1) {
            shuffleDeck(deck);
        }

        if (!1) {
            break;
        }

        printf("\n---------------------------------\n\n");
    }

    printf("Hvala što ste igrali American Poker!\n");

    return 0;
}
