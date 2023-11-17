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
		}
		return matchedHappened;
	}

	bool hasMostSevens(Player player, list<Player> players) {
		int maxSevens = 0;
		for (Player otherPlayer : players) {
			if (otherPlayer.getSevens() > maxSevens) {
				maxSevens = otherPlayer.getSevens();
			}
		}
		return player.getSevens() == maxSevens;
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

	bool checkTieForSixes(Player player, list<Player> players) {
		int sixesCount = 0;

		for (Player otherPlayer : players) {
			if (otherPlayer.getSixes() == player.getSixes()) {
				sixesCount++;
			}
		}

		return sixesCount > 1;
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

	void endRound() {
		table.resetTable();
		for (Player player : Players) {

			if (checkTieForSevens == false) {
				cout << "player" << player.getPlayerId() << ": " << player.getName() << " has the most sevens!" << endl;
			}
			else {

			}
			if (hasMostSevens(player, Players)) {
				cout << "player" << player.getPlayerId() << ": " << player.getName() <<  " has the most sevens!" << endl;
				player.addPoints(1);
			}

			if (hasMostGold(player, Players)) {
				cout << "player" << player.getPlayerId() << ": " << player.getName() << " has the most gold!" << endl;
				player.addPoints(1);
			}

			if (hasMostCards(player, Players)) {
				cout << "player" << player.getPlayerId() << ": " << player.getName() << " has the most cards!" << endl;
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
					if (emptyHand == false) {
						for (Card card : table.getCardsOnTable()) {
							player.addToEarned(card);
							table.pickupFromTable(card);
							roundEnd = true;
							//call endRound function(it'll reset player hand, table, and deck, reshuffle(if needed), then deal 
							break;
						}
					}
				}
			}
		}

	}

	void turnHelper(Player player, string input, list<Card> playerHand) {
		int handCId;
		list<Card> useableHand = playerHand;
		if (useableHand.empty()) {
			cout << "No possible matches" << endl;
			player.DisplayHand();
			cout << "pick a card to put down on the table : ";
			cin >> handCId;
			Card handCard = player.getCard(handCId);
			player.removefromHand(handCard);
			table.addCardToTable(handCard);
			cout << "Card: ";  
			handCard.displayCard();
		}
		cout << "Your hand: ";
		for (Card card : useableHand) {
			cout << "{ID:" << card.getCardId() << "}|Number: ";
			if (card.isGold() == true) {
				cout << "Gold " << card.getNumber() << "|, ";
			}
			else {
				cout << card.getNumber() << "|, ";
			}
		}
		cout << "What card in your hand would you like to choose pick the number in the {}:";
		cin >> handCId;
		Card handCard = player.getCard(handCId);
		cout << "\n would you like to pick one [o] or more cards[m]: ";
		cin >> input;
		if (input == "o") {
			if (matchOneCard(player, handCard) == true) {
				return;
			}
			else {
				cout << "Lets try multiple cards to sum up and match!";
				if (matchMultipleCards(player, handCard) == true) {
					return;
				}
				else {

				}
			}
		}
		if (input == "m") {
			if (matchMultipleCards(player, handCard) == true) {
				return;
			}
			else {
				cout << "Lets try one card to match!";

			}

		}
	}

	void turn(Player player) {
		list<Card>cardsToMatch = {};
		string input;
		int handCId;
		cout << "Remeber to match, you must choose either a card with the same number as on in your hand from the table \n"
			<< "or you must pick a number of cards " 
			<< "that are less than and add up to a card in your hand" << endl;
		cout << "Would you like to match [y/n]";
		cin >> input;
		if (input == "y") {
			table.displayCardsonTable();
			player.DisplayHand();
			cout << "What card in your hand would you like to choose pick the number in the {}:";
			cin >> handCId;
			Card handCard = player.getCard(handCId);
			cout << "/n would you like to pick one [o] or more cards[m]: ";
			cin >> input;
			if (input == "o") {
				if (matchOneCard(player, handCard) == true) {
					return;
				}
			}
			if (input == "m") {
				if (matchMultipleCards(player, handCard) == true) {
					return;
				}
				
			}
		}
	}

	void startGame() {
		bool gameEnd;
		table = Table();
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