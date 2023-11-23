#include "Card.cpp"
#include "Player.cpp"
#include "Table.cpp"
#include "Game.cpp"
#include <string>
#include <iostream>

using namespace std;

int main() {
	cout << "Welcome to Scoopa!\n"
		<< "heres how to play!:\n"
		<< "At the start of the round, four cards are dealt in the middle of the table. Then three cards are dealt to each player.\n\n"
		<< "On your turn, play a card from your hand:\n"
		<< "If theres a card on the table with the same number, you can pick up that card and put that card and the one in your hand in a pile to the side\n(the side pile will already be made for you and added to as you play).\n"
		<< "If not, choose cards on the table that add up to the card you played and put all of them in your pile\n"
		<< "If you can’t add up cards to make your card’s number, place your card face up on the table with the others.\n"
		<< "If you take the last card off the table, Scopa!, you score 1 point. The next player will have to put a card on the table.\n\n"
		<< "When everyone has run out of cards in their hand, three new cards are dealt to each player.\n"
		<< "The round ends when everyone has played all the cards in their hands and there are no more cards to deal.\n"
		<< "The player who last took cards from the table gets any cards remaining on the table and adds them to their pile.\n\n"
		<< "At the end of the round, points are given based on the cards collected:\n"
		<< "1 point for the 7 of diamonds or the gold 7 \n"
		<< "1 point for having the most Gold\n"
		<< "1 point for the most cards.\n"
		<< "1 point for the most seven, if sevens are tied, then it goes to sixes, if sixes are tied then no point is awarded\n"
		<< "\n Now you know how to play Scoopa. So let's start playing!! \n" << endl;
	Game game = Game();
	game.start(); 
}