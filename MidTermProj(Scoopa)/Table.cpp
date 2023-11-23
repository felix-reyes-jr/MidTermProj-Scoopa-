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

	//a private function to create the deck cards, used for the constructor
	stack<Card> populateDeck() {
		vector<string> suits = { "hearts", "Diamonds", "Clubs", "Spades" };
		int idCounter = 1;

		for (string suit : suits) {
			for (int i = 1; i <= 10; i++) {
				if (suit == "Diamonds") {
					Card card = Card(true, i, idCounter);
					deck.push(card);
				}
				else {
					Card card = Card(false, i, idCounter);
					deck.push(card);
				}
				idCounter++;
			}
		}
		return deck;
	}

public:
	//constructor for the table class
	Table() {
		deck = populateDeck();
		shuffleDeck();
		cardsOnTable = {};
	}

	//deconstructor for the table class
	~Table() {
		deck = {};
		cardsOnTable = {};
	}

	//returns the deck stack
	stack<Card> getDeck() {
		return deck;
	}

	//displays all the cards on the table
	void displayCardsonTable() {
		cout << "Cards on the table: \n";
		for (Card card : cardsOnTable) {
			card.displayCard();
		}
		cout << endl;
	 }

	//reuturns a card from the table with the given card ID
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

	//sets the cards on the table list to a given list
	void setCardsOnTable(list<Card>cards) {
		cardsOnTable = cards;
	}

	//adds the given card to the cards on the table list
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

	//shuffles the deck stack
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

	//returns the first card of the deck stack and removes it
	Card pickupFromDeck() {
		Card topCard = deck.top();
		deck.pop();
		return topCard;
	}

	//clears the table of cards, resets the deck and shuffles it
	void resetTable() {
		cardsOnTable.clear();
		deck = {};
		deck = populateDeck();
		shuffleDeck();
	}

	//checks whether the deck is empty
	bool isDeckEmpty() {
		return deck.empty();
	}
};
#endif