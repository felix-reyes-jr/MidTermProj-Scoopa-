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
		cout << "Cards on the table: \n";
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
	void pickupFromTable(int cardId) {
		list<Card>::iterator itr;
		for (itr = cardsOnTable.begin(); itr != cardsOnTable.end(); ++itr) {
			if (itr->getCardId() == cardId) {
				cardsOnTable.erase(itr); 
				break;
			}
		}

	}

	void shuffleDeck() {
		vector<Card> cards;

		while (!deck.empty()) {
			cards.push_back(deck.top());
			deck.pop();
		}

		// Generate a sequence of shuffled indices
		vector<int> indices(cards.size());
		for (int i = 0; i < indices.size(); i++) {
			indices[i] = i;
		}
		std::random_device rand;
		std::mt19937 g(rand());
		std::shuffle(indices.begin(), indices.end(), g);

		// Reorder the cards according to the shuffled indices
		vector<Card> shuffledCards(cards.size());
		for (int i = 0; i < cards.size(); i++) {
			shuffledCards[i] = cards[indices[i]];
		}

		// Put the shuffled cards back into the deck
		for (Card card : shuffledCards) {
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