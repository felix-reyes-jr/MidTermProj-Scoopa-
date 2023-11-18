#include <string>
#include "Card.cpp"
#include <list>
#include <iostream>
using namespace std;
#ifndef Player_class
#define Player_class
class Player {
private:
	string name; //name if player

	int points; //total points a player has

	list<Card> hand; //the players hand

	list<Card> earnedCards; //the total cards the player has gotten during the round

	int playerId; //an id to keep track of player, more secure than using name

public:

	Player(string nm = " ", int Id = -1, int point = 0, list<Card>hnd = {}, list<Card>earned = {}) {
		name = nm;

		points = point;

		hand = hnd;

		earnedCards = earned;

		playerId = Id;
	}

	void addtoHand(Card card) {
		hand.emplace_back(card);
	}

	void removefromHand(Card card) {
		hand.remove(card);
	}


	void addToEarned(Card card) {
		hand.emplace_back(card);
	}

	void resetHand() {
		hand.clear();
	}

	void resetEarned() {
		earnedCards.clear();
	}

	void addPoints(int pointstoAdd) {
		points += pointstoAdd;
	}
	
	list<Card> getHand(){
		return hand;
	}

	list<Card> getEarnedCards() {
		return earnedCards;
	}

	void DisplayHand() {
		cout << "Your Hand: \n";
		for (Card card : hand) {
			cout << "{ID:" << card.getCardId() << "}|Number: ";
			card.displayCard();
		}
		cout << endl;
	}

	Card getCard(int cID) {
		Card desiredCard;
		for (Card card : hand) {
			if (card.getCardId() == cID) {
				desiredCard = card;
			}
		}
		return desiredCard;
	}

	int getPoints() { return points; }

	int getPlayerId() { return playerId; }

	int getSevens() {
		int sevens = 0;
		for (Card card : earnedCards) {
			if (card.getNumber() == 7) {
				sevens++;
			}
		}
		return sevens;
	}

	int getNumberOfCards() {
		return earnedCards.size();
	}

	int getGold() {
		int golds = 0;
		for (Card card : earnedCards) {
			if (card.isGold()) {
				golds++;
			}
		}
		return golds;
	}

	int getSixes() {
		int sixes = 0;
		for (Card card : earnedCards) {
			if (card.getNumber() == 6) {
				sixes++;
			}
		}
		return sixes;
	}

	bool hasGoldSeven() {
		for (Card card : earnedCards) {
			if (card.getNumber() == 7 && card.isGold()) {
				return true;
			}
		}
		return false;
	}

	string getName() {
		return name;
	}
};
#endif