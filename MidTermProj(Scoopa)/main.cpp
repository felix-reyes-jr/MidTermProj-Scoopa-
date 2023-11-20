#include "Card.cpp"
#include "Player.cpp"
#include "Table.cpp"
#include "Game.cpp"
#include <string>
#include <iostream>

using namespace std;

int main() {
	Game game = Game();
	game.start();

	
	/*Player player = Player("Felix", 1, 0, {}, {});
	Card card1 = Card(false, 1, 1);
	Card card2 = Card(false, 2, 2);
	Card card3 = Card(false, 3, 3);

	player.addtoHand(card1);
	player.addtoHand(card2);
	player.addtoHand(card3);

	int handCId;
	player.DisplayHand();
	cout << "What card in your hand would you like to choose to put down, type the number in the {}:";
	cin >> handCId;
	Card handCard = player.getCard(handCId);
	player.removefromHand(handCard.getCardId());
	player.DisplayHand();

	Player p1 = player;

	cout << "p1" << endl;
	p1.DisplayHand();
	cout << "What card in your hand would you like to choose to put down, type the number in the {}:";
	cin >> handCId;
	handCard = p1.getCard(handCId);
	p1.removefromHand(handCard.getCardId());
	cout << "p1 hand" << endl;
	p1.DisplayHand();

	player.DisplayHand();*/
}