#include "Card.cpp"
#include "Table.cpp"
#include "Player.cpp"

class Matcher {
private:
	Table table;

public:
	Matcher(Table t) {
		table = t;
	}

	Matcher() {
		table = Table();
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

	bool matchOneCard(Player player, Card handCard) {
		bool matchedHappened = false;
		int cId;
		table.displayCardsonTable();
		cout << "what card would you like to match: ";
		cin >> cId;
		cout << endl << endl;
		Card tableCard = table.getCardFromTable(cId);
		list<Card> cardsToMatch;
		cardsToMatch.emplace_front(tableCard);
		list<Card> matched = match(cardsToMatch, handCard);
		if (!matched.empty()) {
			matchedHappened = true;
			player.addToEarned(handCard);
			cout << "you matched: " << handCard.getNumber() << " from your hand" << endl;
			cout << "With cards: ";
			for (Card card : matched) {
				card.displayCard();
				table.pickupFromTable(card.getCardId());
				player.addToEarned(card);
			}
			cout << endl << endl;
		}
		return matchedHappened;
	}

	bool matchMultipleCards(Player player, Card handCard) {
		bool matchedHappened = false;
		int cId;
		int cardCount;
		list<Card> cardsToSumMatch;
		table.displayCardsonTable();
		cout << "What total cards are you trying to sum up to match: ";
		cin >> cardCount;
		for (int i = 1; i <= cardCount; i++) {
			cout << "Please enter the number in {} for card " << i << ": ";
			cin >> cId;
			Card tableCard = table.getCardFromTable(cId);
			if (tableCard.getNumber() != NULL) {
				cardsToSumMatch.emplace_back(tableCard);
			}
		}
		cout << "\n" << endl;
		list<Card> matched = match(cardsToSumMatch, handCard);
		if (!matched.empty()) {
			matchedHappened = true;
			player.addToEarned(handCard);
			cout << "you matched: " << handCard.getNumber() << " from your hand" << endl;
			cout << "With cards: " << endl;
			for (Card card : matched) {
				cout << "card: " << card.getNumber() << " ";
				table.pickupFromTable(card.getCardId());
				player.addToEarned(card);
			}
			cout << endl << endl;;
		}
		return matchedHappened;
	}

	void noMatch(Player player) {
		int handCId;
		cout << "No matches possible" << endl;
		player.DisplayHand();
		cout << "pick a card to put down on the table : ";
		cin >> handCId;
		Card handCard = player.getCard(handCId);
		player.removefromHand(handCId);
		table.addCardToTable(handCard);
		cout << "Card: ";
		handCard.displayCard();
		cout << " put down" << endl << endl;
	}
};