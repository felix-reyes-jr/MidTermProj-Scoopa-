#include "Player.cpp"
#include "Table.cpp"
#include "Matcher.cpp"
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
	Matcher matcher;

public:
	Game() {
		table = Table();
		matcher = Matcher(table);
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
				//at the end of each turn we'll check to see if there are anymore cards in the deck
				if (table.getDeck().empty()) {
					//if there are no cards in the deck then we'll look at each player to see if they have a hand left
					bool emptyHand = true;
					for (auto it2 = Players.begin(); it2 != Players.end(); ++it2) {
						//the player doesnt have a hand we'll track that with a boolean
						if (it2->getHand().empty()) {
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
							it->addToEarned(card);
							table.pickupFromTable(card.getCardId());
							roundEnd = true;
							//call endRound function(it'll reset player hand, table, and deck, reshuffle(if needed), then deal 
							break;
						}
					}
					else {
						dealToPlayers();
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
			matcher.noMatch(player);
			return;
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
			if (matcher.matchOneCard(player, handCard) == true) {
				player.removefromHand(handCId);
				isScoopa(player);
				return;
			}
			else {
				cout << "Lets try multiple cards to sum up and match!";
				if (matcher.matchMultipleCards(player, handCard) == true) {
					player.removefromHand(handCId);
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
			if (matcher.matchMultipleCards(player, handCard) == true) {
				player.removefromHand(handCId);
				isScoopa(player);
				return;
			}
			else {
				cout << "Lets try one card to match!";
				if (matcher.matchOneCard(player, handCard) == true) {
					isScoopa(player);
					player.removefromHand(handCId);
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

	Player turn(Player player) {
		list<Card>cardsToMatch = {};
		string input;
		int handCId;
		cout << "\n" << "Remeber, to match you must choose either a card with the same number as one in your hand from the table \n"
			<< "or you must pick a number of cards " 
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
				noMatch(player);
				return player;
			}
			turnHelper(player, player.getHand());
		}
		else {
			player.DisplayHand();
			cout << "What card in your hand would you like to choose to put down, type the number in the {}:";
			cin >> handCId;
			Card handCard = player.getCard(handCId);
			player.removefromHand(handCId);
			table.addCardToTable(handCard);
			cout << "You put down ";
			handCard.displayCard(); 
			cout << endl;
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