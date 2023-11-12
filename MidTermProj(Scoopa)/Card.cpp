#include <string>

class Card {
private:
	static bool isgold;
	static int number;
	static int cardId;
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
};