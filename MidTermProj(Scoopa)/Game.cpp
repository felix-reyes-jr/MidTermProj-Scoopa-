#include "Player.cpp"
#include "Table.cpp"
#include <string>
#include <list>
#include <stack>
#include <iostream>

using namespace std;
class Game {
private:
	int playerCount;
	Table table;
	list<Player> Players;

public:
	Game() {
		cout << "How many Players:";
		cin >> playerCount;
		cout << '\n';
		for (int i = 1; i <= playerCount; i++) {
			string playerName;
			cout << "player" << i << " What is your name: ";
			cin >> playerName;
			cout << '\n';
			Player player = Player(playerName, i);
			Players.emplace_back(player);
		}
	}
	void startGame() {
		table = Table();
		table.shuffleDeck();
	}

	void dealCards() {
		table.addCardToTable(table.pickupFromDeck());
		table.addCardToTable(table.pickupFromDeck());
		table.addCardToTable(table.pickupFromDeck());
		table.addCardToTable(table.pickupFromDeck());
			for (int i = 1; i <= 3; i++) {
				for (Player player : Players) {
					player.addtoHand(table.pickupFromDeck());
				}
			}
	}

	list<Card> match(list<Card> cardsToMatch, Card card) {
		list<Card>matchedCards = {};
		int mSum = 0;
		for (Card c : cardsToMatch) {
			mSum += c.getNumber();
		}
		if (mSum == card.getNumber()) {
			matchedCards = cardsToMatch;
		}
		return matchedCards;
	}

	/*void Round() {
		bool roundEnd;
		for (Player player : Players) {
			cout << "Player" << player.getPlayerId() << " it's your turn! \n";

		}

	}*/

	void turn(Player player) {
		string input;
		cout << "Remeber to match, you must choose either a card with the same number as on in your hand from the table \n"
			<< "or you must pick a number of cards" 
			<< "that are less than and add up to a card in your hand";
		cout << "Would you like to match [y/n]";
		cin >> input;
		if (input == "y") {
			table.displayCardsonTable();

		}
	}

};