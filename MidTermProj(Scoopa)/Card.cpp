#include <string>

class Card {
public:
	static bool isGold;
	static int number;
	static int possibleCardPoints;

	Card() {
		isGold = false;
		number = NULL;
		possibleCardPoints = 0;
	}
	Card(bool gold, int num, int points) {
		isGold = gold;
		number = num;
		possibleCardPoints = points;
	}
	
	bool isGold() { return isGold; }

	int getNumber() { return number; }

	int getPoints() { return possibleCardPoints; }
};