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

	Game(int count, list<Player>& player) {
		table = Table();
		playerCount = count;
		Players = player;
	}

	void setPlayers(list<Player> players) {
		Players = players;
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

	void resetPlayers() {
		for (auto it = Players.begin(); it != Players.end(); ++it) { 
			Player player = *it;
			player.resetHand(); 
			player.resetEarned(); 
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

	bool matchMultipleCards(Player *player, Card handCard) {
		bool matchedHappened = false;
		int cId;
		int cardCount;
		list<Card> cardsToSumMatch;
		cout << "Card from hand: ";
		handCard.displayCard();
		cout << endl;
		table.displayCardsonTable();
		cout << "How many cards are you trying to sum up to match: ";
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
			player->addToEarned(handCard);
			cout << "you matched: " << handCard.getNumber() << " from your hand" << endl;
			cout << "With cards: " << endl;
			for (Card card : matched) { 
				cout << "card: " << card.getNumber() << " "; 
				table.pickupFromTable(card.getCardId()); 
				player->addToEarned(card); 
			}
			cout << endl << endl;
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

	bool hasMostGold(Player& player) {
		int maxGold = 0;
		for (auto it = Players.begin(); it != Players.end(); ++it) {
			if (it->getGold() > maxGold) {
				maxGold = it->getGold();
			}
		}
		return player.getGold() == maxGold;
	}

	bool hasMostCards(Player& player) {
		int mostCards = 0;
		for (auto it = Players.begin(); it != Players.end(); ++it) {
			if (it->getGold() > mostCards) {
				mostCards = it->getNumberOfCards();
			}
		}
		return player.getNumberOfCards() == mostCards;
	}

	bool tiedForSevens(Player& player) {
		int maxSevens = 0;
		for (auto it = Players.begin(); it != Players.end(); ++it) {
			if (it->getSevens() > maxSevens) {
				maxSevens = it->getSevens();
			}
		}
		int tieCounter = 0;
		for (auto it = Players.begin(); it != Players.end(); ++it) {
			if (it->getSevens() == maxSevens) {
				tieCounter++;
			}
		}
		return tieCounter > 1;
	}

	bool hasMostSixes(Player& player) {
		int maxSixes = 0;
		for (auto it = Players.begin(); it != Players.end(); ++it) {
			if (it->getSixes() > maxSixes) {
				maxSixes = it->getSixes();
			}
		}
		return player.getNumberOfCards() == maxSixes;
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

	void rewardPlayers() {

		for (list<Player>::iterator it = Players.begin(); it != Players.end(); ++it) {
			if (hasMostGold(*it)) {
				it->addPoints(1);
			}
			if (!tiedForSevens(*it)) {
				it->addPoints(1);
			}
			else if (hasMostSixes(*it)) {
				it->addPoints(1);
			}
			if (it->hasGoldSeven()) {
				it->addPoints(1);
			}
		}
	}

	void endRound() {

		rewardPlayers();
		for (Player player : Players) {
			cout << player.getName() << " has " << player.getPoints() << " points" << endl;
		}
		table.resetTable();
		resetPlayers();
		dealCards();
	}

	void round() {
		bool roundEnd = false;
		int i = 0;
		while(!roundEnd){
			for (auto it = Players.begin(); it != Players.end(); ++it) {
				cout << "PLAYER:" << it->getPlayerId() << " IT'S YOUR TURN \n";
				*it = turn(*it);
			}
			i += 2;
			if (i >= 2) {
				roundEnd = true;
			}
			if (isDeckandHandsEmpty()) {
				cout << "\n Round Over!" << endl;
				roundEnd = true;
			}
			else if (emptyHands()) {
				cout << "\ndealing new hands to players!\n" << endl;
				dealToPlayers();
			}
		}
		endRound();
	}

	Player turnHelper(Player *player, list<Card> playerHand) {
		int handCId;
		string input;
		list<Card> useableHand = playerHand;
		if (useableHand.empty()) {
			cout << "No matches possible" << endl;
			player->DisplayHand();
			cout << "pick a card to put down on the table, type the number in the {}: ";
			cin >> handCId;
			Card handCard = player->getCard(handCId);
			player->removefromHand(handCId);
			table.addCardToTable(handCard);
			cout << "You put down ";
			handCard.displayCard();
			cout << endl;
			return *player;
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
		Card handCard = player->getCard(handCId);
		cout << "\n";
			if (matchMultipleCards(player, handCard) == true) {
				isScoopa(*player);
				player->removefromHand(handCId);
				pickedUpLast(*player);
				return *player;
			}
			else {
				cout << "match failed!" << endl;
				cout << "Lets try again!" << endl;;
				if (matchMultipleCards(player, handCard) == true) {
					isScoopa(*player);
					player->removefromHand(handCId);
					pickedUpLast(*player);
					return *player;
				}
				else {
					Card card = player->getCard(handCId);
					useableHand.remove(card);
					return turnHelper(player, useableHand);
				}
			}
		return *player;
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
			player = turnHelper(&player, player.getHand());
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
			cout << "\n \n" << endl;
				;
			return player;
		}
		return player;
	}

	void start() {
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