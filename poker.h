#pragma once
#include "player.h"
#include "hand.h"
void start(PLAYER* player);
void initializeDeck(Card deck[]);
void shuffleDeck(Card deck[]);
void printCard(Card card);
void printHand(Card hand[]);
void drawCards(Card deck[], Card hand[]);
int isPair(Card hand[]);
int isTwoPair(Card hand[]);
int isThreeOfAKind(Card hand[]);
int isStraight(Card hand[]);
int isFlush(Card hand[]);
int isFullHouse(Card hand[]);
int isFourOfAKind(Card hand[]);
int isStraightFlush(Card hand[]);
int isRoyalFlush(Card hand[]);
int evaluateHand(Card hand[]);