#include <string>
#include <iostream>
using namespace std;

#ifndef Card_class
#define Card_class
class Card{
private:
	bool isgold;
	int number;
	int cardId;
public:

	//Default Constructor for the card class
	Card() {
		isgold = false;
		number = NULL;
		cardId = -1;
	}

	//Constructor for Card class
	Card(bool gold, int num, int id) {
		isgold = gold;
		number = num;
		cardId = id;
	}
	
	//returns whether the card is gold or not
	bool isGold() { return isgold; }

	//returns the number of the card
	int getNumber() { return number; }

	//returns the card unique ID
	int getCardId() { return cardId; }

	//displays the card ID, number, and if it's gold
	void displayCard() {
		if (isgold) {
			cout << "|{ID:" << cardId << "}->Gold:" << number << "| ";
		}
		else {
			cout << "|{ID:" << cardId << "}->" << number << "| ";
		}
	}

	//a == operatore overide to compare two cards
	bool operator== (const Card &other) const {
		if ((this->cardId == other.cardId) && (this->number == other.number) && (this->isgold == other.isgold)) {
			return true;
		}
		return false;
	}
};
#endif