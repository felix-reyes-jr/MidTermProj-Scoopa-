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
		cout << "what card would you like to match: " << endl;
		cin >> cId;
		Card tableCard = table.getCardFromTable(cId);
		list<Card> cardsToMatch;
		cardsToMatch.emplace_front(tableCard);
		list<Card> matched = match(cardsToMatch, handCard);
		if (!matched.empty()) {
			matchedHappened = true;
			player.removefromHand(handCard);
			player.addToEarned(handCard);
			cout << "you matched: " << handCard.getNumber() << " from your hand" << endl;
			cout << "With cards: " << endl;
			for (Card card : matched) {
				cout << "card: " << card.getNumber() << " ";
				table.pickupFromTable(card);
				player.addToEarned(card);
			}
			cout << endl;
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
		list<Card> matched = match(cardsToSumMatch, handCard);
		if (!matched.empty()) {
			matchedHappened = true;
			cout << "you matched: " << handCard.getNumber() << " from your hand" << endl;
			cout << "With cards: " << endl;
			for (Card card : matched) { 
				cout << "card: " << card.getNumber() << " "; 
				table.pickupFromTable(card); 
				player.addToEarned(card); 
			}
			cout << endl;
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
		player.removefromHand(handCard);
		table.addCardToTable(handCard);
		cout << "Card: ";
		handCard.displayCard();
		cout << " put down";
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
				<< "One point awarded to you!";
			player.addPoints(1);
		}
	}

	void endRound() {
		table.resetTable();
		for (Player player : Players) {
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
			player.resetHand();
			player.resetEarned();
		}
		dealCards();
	}

	void round() {
		bool roundEnd = false;
		bool emptyHand = false;
		while(!roundEnd ){
			for (Player player : Players) {
				cout << "Player" << player.getPlayerId() << " it's your turn! \n";
				turn(player);
				//at the end of each turn we'll check to see if there are anymore cards in the deck
				if (table.getDeck().empty()) {
					//if there are no cards in the deck then we'll look at each player to see if they have a hand left
					for (Player player : Players) {
						//the player doesnt have a hand we'll track that with a boolean
						if (player.getHand().empty()) {
							emptyHand = true;
						}
						else {
							//if atleast one player has a hand them\n the round contiues
							emptyHand = false;
						}
					}
					//all player have no hand then all remaining cards on the table go to the last player who picked up 
					//and the round ends
					if (emptyHand == true) {
						for (Card card : table.getCardsOnTable()) {
							player.addToEarned(card);
							table.pickupFromTable(card);
							roundEnd = true;
							//call endRound function(it'll reset player hand, table, and deck, reshuffle(if needed), then deal 
							break;
						}
					}
					else {
						for (Player player : Players) {
							//the player doesnt have a hand we'll track that with a boolean
							if (player.getHand().empty()) {
								emptyHand = true;
							}
							else {
								//if atleast one player has a hand them\n the round contiues
								emptyHand = false;
							}
						}
						//all players have no hand but the deck is not empty, deal 3 more cards to players
						if (emptyHand == true) {
							//dealToPlayers();
						}
					}
				}
			}
		}

	}

	void turnHelper(Player player, list<Card> playerHand) {
		int handCId;
		string input;
		list<Card> useableHand = playerHand;
		if (useableHand.empty()) {
			noMatch(player);
			return;
		}
		cout << "table cards: ";
		table.displayCardsonTable();
		cout << endl;
		cout << "Your usable hand: ";
		for (Card card : useableHand) {
			card.displayCard();
		}
		cout << endl;
		cout << "What card in your hand would you like to choose pick the number in the {}:";
		cin >> handCId;
		Card handCard = player.getCard(handCId);
		cout << "\n would you like to pick one [o] or more cards[m]: ";
		cin >> input;
		if (input == "o") {
			if (matchOneCard(player, handCard) == true) {
				isScoopa(player);
				return;
			}
			else {
				cout << "Lets try multiple cards to sum up and match!";
				if (matchMultipleCards(player, handCard) == true) {
					isScoopa(player);
					return;
				}
				else {
					useableHand.remove(handCard);
					turnHelper(player, useableHand);
				}
			}
		}
		else if (input == "m") {
			if (matchMultipleCards(player, handCard) == true) {
				isScoopa(player);
				return;
			}
			else {
				cout << "Lets try one card to match!";
				if (matchOneCard(player, handCard) == true) {
					isScoopa(player);
					return;
				}
				else {
					useableHand.remove(handCard);
					turnHelper(player, useableHand);
				}
			}

		}
		else {
			turnHelper(player, useableHand);
		}
	}

	void turn(Player player) {
		list<Card>cardsToMatch = {};
		string input;
		int handCId;
		cout << "Remeber, to match you must choose either a card with the same number as one in your hand from the table \n"
			<< "or you must pick a number of cards " 
			<< "that are less than and add up to a card in your hand" << endl;
		player.DisplayHand();
		cout << "Would you like to match [y/n]";
		cin >> input;
		if (player.getHand().empty()) {
			cout << "No cards in hand, cannot play!" << endl;
			return;
		}
		if (input == "y") {
			if (table.getCardsOnTable().empty()) {
				noMatch(player);
				return;
			}
			turnHelper(player, player.getHand());
		}
		else {
			player.DisplayHand();
			cout << "What card in your hand would you like to choose to put down, type the number in the {}:";
			cin >> handCId;
			Card handCard = player.getCard(handCId);
			player.removefromHand(handCard);
			table.addCardToTable(handCard);
			return;
		}
	}

	void start() {
		displayPlayers();
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