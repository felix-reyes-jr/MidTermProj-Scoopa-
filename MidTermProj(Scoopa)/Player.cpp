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

	//constructor for player class
	Player(string nm = " ", int Id = -1, int point = 0, list<Card>hnd = {}, list<Card>earned = {}) {
		name = nm;

		points = point;

		hand = hnd;

		earnedCards = earned;

		playerId = Id;
	}

	//adds a given card to the player's hand
	void addtoHand(Card card) {
		hand.emplace_front(card);
	}

	//removes a card from the player's hand
	void removefromHand(int cardId) {
		list<Card>::iterator itr;
		for (itr = hand.begin(); itr != hand.end(); ++itr) { 
			if (itr->getCardId() == cardId) { 
				hand.erase(itr); break; 
			} 
		}
	}

	//adds a card to the player's list of earned cards
	void addToEarned(Card card) {
		earnedCards.push_back(card);
	}

	//resets a player's hand to empty
	void resetHand() {
		hand.clear();
	}

	//resets a player's earned cards to empty
	void resetEarned() {
		earnedCards.clear();
	}

	//adds a point to the player's point total
	void addPoints(int pointstoAdd) {
		points += pointstoAdd;
	}
	
	//returns the player's hand list
	list<Card> getHand(){
		return hand;
	}

	//returns the player's earned cards list
	list<Card> getEarnedCards() {
		return earnedCards;
	}

	//displays the player's hand
	void DisplayHand() {
		cout << "Your Hand: \n";
		for (Card card : hand) {
			card.displayCard();
		}
		cout << endl;
	}

	//displays the player's earned cards
	void displayEarned() {
		cout << "Earned cards: " << endl;
		for (Card card : earnedCards) {
			card.displayCard();
		}
		cout << endl;
	}

	//returns a specific card from the player's hand with the given card ID
	Card getCard(int cID) {
		Card desiredCard;
		list<Card>::iterator itr;
		for (itr = hand.begin(); itr != hand.end(); ++itr) {
			if (itr->getCardId() == cID) {
				return *itr;
			}
		}
		return *itr;
	}

	//returns the player's point total
	int getPoints() { return points; }

	//returns the player's ID
	int getPlayerId() { return playerId; }

	//returns the amount of sevens a player has in their earned cards
	int getSevens() {
		int sevens = 0;
		for (Card card : earnedCards) {
			if (card.getNumber() == 7) {
				sevens++;
			}
		}
		return sevens;
	}

	//returns the amount of cards a player has in their earned cards
	int getNumberOfCards() {
		return static_cast<int>(earnedCards.size());
	}

	//returns the amount of gold a player has in their earned cards
	int getGold() {
		int golds = 0;
		for (Card card : earnedCards) {
			if (card.isGold()) {
				golds++;
			}
		}
		return golds;
	}

	//returns the amount of sixes a player has in their earned cards
	int getSixes() {
		int sixes = 0;
		for (Card card : earnedCards) {
			if (card.getNumber() == 6) {
				sixes++;
			}
		}
		return sixes;
	}

	//returns a bool whether a player has the gold seven in their earned cards
	bool hasGoldSeven() {
		for (Card card : earnedCards) {
			if (card.getNumber() == 7 && card.isGold()) {
				return true;
			}
		}
		return false;
	}

	//returns the player's name
	string getName() {
		return name;
	}

	//returns a bool whether a player's hand is empty
	bool isHandEmpty() {
		return hand.empty();
	}
};
#endif