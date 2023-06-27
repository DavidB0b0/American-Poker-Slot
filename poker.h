#pragma once
#include "player.h"
#include "hand.h"
void start(PLAYER* player);
void stvaranjeDeka(Card deck[]);
void mjesanjeDeka(Card deck[]);
void printCard(Card card);
void printHand(Card hand[]);
void drawCards(Card deck[], Card hand[]);
int Pairs(Card hand[]);
int TwoPairs(Card hand[]);
int ThreeOfAKind(Card hand[]);
int Straight(Card hand[]);
int Flush(Card hand[]);
int FullHouse(Card hand[]);
int FourOfAKind(Card hand[]);
int StrFlush(Card hand[]);
int RoyalFlush(Card hand[]);
int izracunajHand(PLAYER* player, Card hand[]);
