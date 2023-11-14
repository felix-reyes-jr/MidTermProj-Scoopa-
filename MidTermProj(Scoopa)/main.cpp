#include "Card.cpp"
#include "Player.cpp"
#include "Table.cpp"
#include <string>
#include <iostream>

using namespace std;

int main() {
	Table table = Table();

	table.addCardToTable(table.pickupFromDeck());
	table.addCardToTable(table.pickupFromDeck());
	table.addCardToTable(table.pickupFromDeck());
	table.addCardToTable(table.pickupFromDeck());

	table.displayCardsonTable();
}