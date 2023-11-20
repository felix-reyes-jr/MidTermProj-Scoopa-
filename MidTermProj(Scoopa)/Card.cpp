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

	Card() {
		isgold = false;
		number = NULL;
		cardId = -1;
	}
	Card(bool gold, int num, int id) {
		isgold = gold;
		number = num;
		cardId = id;
	}
	
	bool isGold() { return isgold; }

	int getNumber() { return number; }

	int getCardId() { return cardId; }

	void displayCard() {
		if (isgold) {
			cout << "|{ID:" << cardId << "}->Gold:" << number << "| ";
		}
		else {
			cout << "|{ID:" << cardId << "}->" << number << "| ";
		}
	}

	bool operator== (const Card &other) const {
		if ((this->cardId == other.cardId) && (this->number == other.number) && (this->isgold == other.isgold)) {
			return true;
		}
		return false;
	}
};
#endif