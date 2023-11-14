#include <string>
#include "Card.cpp"
#include <list>
#include <iostream>
using namespace std;
class Player {
private:
	string name; //name if player

	int points; //total points a player has

	list<Card> hand; //the players hand

	list<Card> earnedCards; //the total cards the player has gotten during the round

	int playerId; //an id to keep track of player, more secure than using name

public:

	Player() {
		name = "";

		points = 0;
		
		hand = {};

		earnedCards = {};

		playerId = -1;

	}

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
		cout << "Your Hnd: \n";
		for (Card card : hand) {
			if (card.isGold() == true) {
				cout << "|Gold " << card.getNumber() << "|, ";
			}
			else {
				cout << "|" << card.getNumber() << "|, ";
			}
		}
	}

	int getPlayerId() { return playerId; }
};