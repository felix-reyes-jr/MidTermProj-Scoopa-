#include "Player.cpp"
#include "Table.cpp"
#include <string>
#include <list>
#include <stack>
#include <iostream>

using namespace std;
#ifndef Game_class
#define Game_class
class Game {
private:
	int playerCount;
	Table table;
	list<Player> Players;

public:
	Game() {
		table = Table();
		cout << "How many Players:";
		cin >> playerCount;
		cout << '\n';
		for (int i = 1; i <= playerCount; i++) {
			string playerName;
			cout << "Player" << i << " what is your name: ";
			cin >> playerName;
			cout << '\n';
			Player player = Player(playerName, i);
			Players.emplace_back(player);
		}
	}

	list<Player> getPlayers() {
		return Players;
	}

	int getPlayerCount() {
		return playerCount;
	}

	Table getTable() {
		return table;
	}

	void displayPlayers() {
		cout << "All Players: ";
		for (Player player : Players) {
			cout << "Player" << player.getPlayerId() << ":" << player.getName() << "\t";
		}
		cout << endl;
	}

	void dealToPlayers() {
		for (int i = 1; i <= 3; i++) {
			for (list<Player>::iterator it = Players.begin(); it != Players.end(); ++it) {
				it->addtoHand(table.pickupFromDeck());
			}
		}
	}

	void dealCards() {
		table.addCardToTable(table.pickupFromDeck());
		table.shuffleDeck();
		table.addCardToTable(table.pickupFromDeck());
		table.shuffleDeck();
		table.addCardToTable(table.pickupFromDeck());
		table.shuffleDeck();
		table.addCardToTable(table.pickupFromDeck());
		table.shuffleDeck();
		dealToPlayers();
	}

	bool emptyHands() {
		bool emptyHand = false;
		for (Player player : Players) {
			if (player.isHandEmpty()) {
				emptyHand = true;
			}
			else {
				emptyHand = false;
			}
		}
		return emptyHand;
	}

	bool isDeckandHandsEmpty() {
		return emptyHands() && table.isDeckEmpty();
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
		cout << "what card would you like to match, type the number in the {}: ";
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

	void noMatch(Player player, Card handCard) {
		table.addCardToTable(handCard);
		cout << "Card: ";
		handCard.displayCard();
		cout << "put down" << endl << endl;
	}

	Player checkTieForSevensOrSizes(Player player, list<Player> players) {
		int sevensCount = 0;

		for (Player otherPlayer : players) {
			if (otherPlayer.getSevens() == player.getSevens()) {
				if (otherPlayer.getSixes() == player.getSixes()) {
					Player p = Player();
					return p;
				}
				else if (otherPlayer.getSixes() > player.getSixes()) {
					return otherPlayer;
				}
				else {
					return player;
				}
				
			}
			else if (otherPlayer.getSevens() > player.getSevens()) {
				return otherPlayer;
			}
			else {
				return player;
			}
		}
	}

	bool hasMostGold(Player player, list<Player> players) {
		int maxGold = 0;
		for (Player otherPlayer : players) {
			if (otherPlayer.getGold() > maxGold) {
				maxGold = otherPlayer.getGold();
			}
		}
		return player.getGold() == maxGold;
	}

	bool hasMostCards(Player player, list<Player> players) {
		int maxCards = 0;
		for (Player otherPlayer : players) {
			if (otherPlayer.getNumberOfCards() > maxCards) {
				maxCards = otherPlayer.getNumberOfCards();
			}
		}
		return player.getNumberOfCards() == maxCards;
	}

	void isScoopa(Player player) {
		if (table.getCardsOnTable().empty()) {
			cout << "Player" << player.getPlayerId() << ": " << player.getName() << " you got scoopa!!!" << endl
				<< "One point awarded to you!" << endl;
			player.addPoints(1);
		}
	}

	void pickedUpLast(Player player) {
		if (isDeckandHandsEmpty()) {
			for (Card card : table.getCardsOnTable()) {
				player.addToEarned(card);
			}
		}
	}

	void endRound() {
		table.resetTable();
		for (auto it = Players.begin(); it != Players.end(); ++it) {
			Player player = *it;
			Player p = checkTieForSevensOrSizes(player, Players);
			if (p.getPlayerId() != -1 && p.getPlayerId() == player.getPlayerId()) {
				cout << "Player" << p.getPlayerId() << ": " << p.getName() << "has the most Sevens/Sixes!";
				player.addPoints(1);
			}
			else {
				cout << "Sevens and sixes tied! No points";
			}

			if (hasMostGold(player, Players)) {
				cout << "player" << player.getPlayerId() << ": " << player.getName() << " has the most gold!" << endl;
				player.addPoints(1);
			}

			if (hasMostCards(player, Players)) {
				cout << "player" << player.getPlayerId() << ": " << player.getName() << " has the most cards!" << endl;
				player.addPoints(1);
			}

			if (player.hasGoldSeven()) {
				cout << "player" << player.getPlayerId() << ": " << player.getName() << " has the Golden Seven!" << endl;
				player.addPoints(1);
			}
			cout << "Player has " << player.getPoints() << "points" << endl;
			player.resetHand();
			player.resetEarned();
		}
		dealCards();
	}

	void round() {
		bool roundEnd = false;
		bool emptyHand = false;
		while(!roundEnd ){
			for (auto it = Players.begin(); it != Players.end(); ++it) {
				cout << "Player" << it->getPlayerId() << " it's your turn! \n";
				*it = turn(*it);
			}
			if (isDeckandHandsEmpty()) {
				cout << "\n Round Over!" << endl;
				endRound();
			}
			else if (emptyHands()) {
				cout << "\n dealing new hands to players!" << endl;
				dealToPlayers();
			}

		}

	}

	Player turnHelper(Player player, list<Card> playerHand) {
		int handCId;
		string input;
		list<Card> useableHand = playerHand;
		if (useableHand.empty()) {
			cout << "No matches possible" << endl;
			player.DisplayHand();
			cout << "pick a card to put down on the table, type the number in the {}: ";
			cin >> handCId;
			Card handCard = player.getCard(handCId);
			player.removefromHand(handCId);
			table.addCardToTable(handCard);
			cout << "You put down ";
			handCard.displayCard();
			cout << endl;
			return player;
		}
		table.displayCardsonTable();
		cout << endl;
		cout << "Your usable hand: \n";
		for (Card card : useableHand) {
			card.displayCard();
		}
		cout << endl;
		cout << "What card in your hand would you like to choose, type the number in the {}:";
		cin >> handCId;
		Card handCard = player.getCard(handCId);
		cout << "\n would you like to pick one[o] or more cards[m] from the table: ";
		cin >> input;
		cout << "\n";
		if (input == "o") {
			if (matchOneCard(player, handCard) == true) {
				isScoopa(player);
				player.removefromHand(handCId);
				pickedUpLast(player);
				return player;
			}
			else {
				cout << "A one card match was not possible!" << endl;
				cout << "Lets try multiple cards to sum up and match!";
				if (matchMultipleCards(player, handCard) == true) {
					isScoopa(player);
					player.removefromHand(handCId);
					pickedUpLast(player);
					return player;
				}
				else {
					Card card = player.getCard(handCId);
					useableHand.remove(card);
					return turnHelper(player, useableHand);
				}
			}
		}
		else if (input == "m") {
			if (matchMultipleCards(player, handCard) == true) {
				isScoopa(player);
				player.removefromHand(handCId);
				pickedUpLast(player);
				return player;
			}
			else {
				cout << "A multiple card match was not possible!" << endl;
				cout << "Lets try one card to match!" << endl;;
				if (matchOneCard(player, handCard) == true) {
					isScoopa(player);
					player.removefromHand(handCId);
					pickedUpLast(player);
					return player;
				}
				else {
					Card card = player.getCard(handCId);
					useableHand.remove(card);
					return turnHelper(player, useableHand);
				}
			}

		}
		else {
			return turnHelper(player, useableHand);
		}
		return player;
	}

	Player turn(Player player) {
		list<Card>cardsToMatch = {};
		string input;
		int handCId;
		cout << "\n" << "Remeber, to match you must choose either a card on the table with the same number as one in your hand \n"
			<< "or you must pick a number of cards on the table that sum up to equal a card in your hand" 
			<< "that are less than and add up to a card in your hand" << endl;
		table.displayCardsonTable();
		player.DisplayHand();
		cout << "Would you like to match [y/n]";
		cin >> input;
		cout << "\n" << endl;
		if (player.getHand().empty()) {
			cout << "No cards in hand, cannot play!" << endl;
			return player;
		}
		if (input == "y") {
			if (table.getCardsOnTable().empty()) {
				cout << "No matches possible" << endl;
				player.DisplayHand();
				cout << "pick a card to put down on the table  type the number in the {}: ";
				cin >> handCId;
				Card handCard = player.getCard(handCId);
				player.removefromHand(handCId);
				table.addCardToTable(handCard);
				cout << "You put down ";
				handCard.displayCard();
				cout << endl;
				return player;
			}
			player = turnHelper(player, player.getHand());
		}
		else {
			player.DisplayHand();
			cout << "pick a card to put down on the table, type the number in the{}: ";
			cin >> handCId;
			Card handCard = player.getCard(handCId);
			player.removefromHand(handCId);
			table.addCardToTable(handCard);
			cout << "You put down ";
			handCard.displayCard(); 
			cout << endl << endl;
				;
			return player;
		}
		return player;
	}

	void start() {
		displayPlayers();
		cout << "\n";
		bool gameEnd = false;
		dealCards();
		while (!gameEnd) {
			for (Player player : Players) {
				if (player.getPoints() >= 11) {
					gameEnd = true;
					//call gameEnd Function here
					break;
				}

			}
			round();
		}
	}
};
#endif