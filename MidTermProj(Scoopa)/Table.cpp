#include <string>
#include "Card.cpp"
#include <list>
#include <stack>
#include <vector>
#include <iostream>
#include <random>
using namespace std;
#ifndef Table_class
#define Table_class
class Table {
private:
	list<Card> cardsOnTable;
	stack<Card> deck;

	stack<Card> populateDeck() {
		vector<string> suits = { "hearts", "Diamonds", "Clubs", "Spades" };
		stack<Card>dck = {};
		int idCounter = 0;

		for (string suit : suits) {
			for (int i = 1; i <= 10; i++) {
				if (suit == "Diamonds") {
					Card card = Card(true, i, idCounter);
					dck.push(card);
				}
				else {
					Card card = Card(false, i, idCounter);
					dck.push(card);
				}
				idCounter++;
			}
		}
		return dck;
	}

public:
	Table() {
		deck = populateDeck();
		shuffleDeck();
		cardsOnTable = {};
	}

	~Table() {
		deck = {};
		cardsOnTable = {};
	}

	stack<Card> getDeck() {
		return deck;
	}

	void displayCardsonTable() {
		cout << "Cards on the table: ";
		for (Card card : cardsOnTable) {
			card.displayCard();
		}
		cout << endl;
	 }

	Card getCardFromTable(int cardID) {
		Card desiredCard = Card();
		for (Card card : cardsOnTable) {
			if (card.getCardId() == cardID) {
				desiredCard = card;
			}
		}
		return desiredCard;
	}

	list<Card> getCardsOnTable() { return cardsOnTable; }

	void setCardsOnTable(list<Card>cards) {
		cardsOnTable = cards;
	}

	void addCardToTable(Card card) {
		cardsOnTable.emplace_front(card);
	}

	/* Returns the specifed card on the table
	* precondition: the card must be in the cardsOnTable List
	*/
	Card pickupFromTable(Card card) {
		cardsOnTable.remove(card);
		return card;
	}

	void shuffleDeck() {
		vector<Card> cards;

		while (!deck.empty()) {
			cards.push_back(deck.top());
			deck.pop();
		}

		random_device rand;
		random_shuffle(cards.begin(), cards.end());

		for (Card card : cards) {
			deck.push(card);
		}
	}

	Card pickupFromDeck() {
		Card topCard = deck.top();
		deck.pop();
		return topCard;
	}

	void resetTable() {
		cardsOnTable.clear();
		deck = {};
		deck = populateDeck();
		shuffleDeck();
	}
};
#endif