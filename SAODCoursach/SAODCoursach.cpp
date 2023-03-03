#include<conio.h>

#include"Constants.h"
#include"Common.h"
#include"Guest.h"
#include"Room.h"
#include"Record.h"
#include"Tree.h"
#include"CyclicList.h"
#include"HashTable.h"
#include"Actions.h"

const std::vector<std::string> operations
{   ("Registration guest"),
	("Delete guest"),
	("Print all guests"),
	("Delete all guests"),
	("Find guest by passport"),
	("Find guest by full name"),

	("Add new room"),
	("Delete room"),
	("Print all rooms"),
	("Delete all rooms"),
	("Find room by number"),
	("Find room by equipment"),

	("Registration move in"),
	("Registration move out") };

void action(int index, HashTable& guests, Tree& rooms, CyclicList<Record>& records) {
	switch (index) {
		case 0: { // Registration guest
			registrationGuest(guests);
			break;
		}
		case 1: { // Delete guest
			deleteGuest(guests, records);
			break;
		}
		case 2: { // Print all guests
			system("cls");
			guests.print([](Guest guest) { return true; });
			getBackToMainMenu();
			
			break;
		}
		case 3: { // Delete all guests
			deleteAllGuests(guests, records);
			break;
		}
		case 4: { // Find guest by passport
			findGuestByPassport(guests, records);
			break;
		}
		case 5: { // Find guest by full name
			findGuestByFullname(guests);
			break;
		}
		case 6: { // Add new room
			addRoom(rooms);
			break;
		}
		case 7: { // Delete room
			deleteRoom(rooms, records,guests);
			break;
		}
		case 8: { // Print all rooms
			system("cls");
			rooms.print([](Room room) {return true; });
			getBackToMainMenu();
			break;
		}
		case 9: { // Delete all rooms
			deleteAllRooms(rooms, records);
			
			break;
		}
		case 10: { // Find room by number
			findRoomByNumber(rooms, records,guests);
			break;
		}
		case 11: { // Find room by equipment
			findRoomByEquipment(rooms);
			break;
		}
		case 12: { // Registration move in
			registraionMoveIn(records,guests,rooms);
			break;
		}
		case 13: { // Registration move out
			registraionMoveOut(records, guests, rooms);
			break;
		}
	}
}

void printMenu(int index) {
	system("cls");
	std::cout << "===========MENU===========" << std::endl;
	for (int i = 0; i < operations.size(); i++){
		std::cout << "|";
		if (i == index) std::cout << "*";
		else std::cout << " ";
		std::cout << "|";
		std::cout << operations[i] << std::endl;
	}
	std::cout << "==========================" << std::endl;

	std::cout << std::endl << "Up arrow - up" << std::endl;
	std::cout << "Down arrow - down" << std::endl;
	std::cout << "Enter - select action" << std::endl;
}

void menu(HashTable& guests, Tree& rooms, CyclicList<Record>& records) {
	int index = 0;
	printMenu(index);
	while (true) {
		switch (_getch()) {
			case 72: { //up
				index--;
				if (index == -1) index = operations.size()-1;
				printMenu(index);
				break;
			}
			case 80: { //down
				index++;
				if (index == operations.size()) 
					index = 0;
				printMenu(index);
				break;
			}
			case 13: { // enter
				action(index, guests, rooms, records);
				index = 0;
				printMenu(index);
				break;
			}
		}
	}
}

int main()
{
	HashTable guests(Constants::HASH_TABLE_SIZE);
	Tree rooms;
	CyclicList<Record> records;
	menu(guests,rooms,records);
	
}
