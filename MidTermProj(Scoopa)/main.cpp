#include "Card.cpp"
#include "Player.cpp"
#include "Table.cpp"
#include "Game.cpp"
#include <string>
#include <iostream>

using namespace std;

int main() {
	Game game = Game();
	game.displayPlayers();
	game.dealCards();
	game.getTable().displayCardsonTable();
	list<Player> players = game.getPlayers();

	for (Player player : players) {
		cout << "PLayer" << player.getPlayerId() << " ";
		player.DisplayHand();
	}
	//game.start();
}