#ifndef _ACTIONS_
#define _ACTIONS_

#include"Constants.h"
#include"Common.h"
#include"Guest.h"
#include"Room.h"
#include"Record.h"
#include"Tree.h"
#include"CyclicList.h"
#include"HashTable.h"

void registrationGuest(HashTable& guests) {
	system("cls");
	Guest guest;
	std::string str;

	std::cout << "=====Registraion new guest=====" << std::endl;
	while (true) {

		std::cout << "Enter passport: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (isRightPassport(str)) {
			if (guests.find(str)) {
				std::cout << std::endl << "This guest already registered" << std::endl;
				getBackToMainMenu();
				return;
			}
			
			guest.setPassport(str);
			break;
		}
		else {
			std::cout << "Passport must be like \"NNNN-NNNNNN\"." << std::endl;
		}
	}
	while (true) {
		std::cout << "Enter full name: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (isRightFullname(str) && str.length() >= Constants::MIN_LENGTH_STRING) {
			guest.setFullName(str);
			break;
		}
		else {
			std::cout << "Full name cannot contain anything except letters" << std::endl;
		}
	}
	while (true) {
		std::cout << "Enter birth year: ";
		int birthYear = validInput("Input error\nEnter birth year: ");
		if (birthYear >= 0) {
			guest.setBirthYear(birthYear);
			break;
		}
		else
			std::cout << "Birth year cannot be less than 0" << std::endl;
	}
	while (true) {
		std::cout << "Enter address: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (str.length() >= Constants::MIN_LENGTH_STRING) {
			guest.setAddress(str);
			break;
		}
		else {
			std::cout << "Address cannot be less than 2 letters" << std::endl;
		}
	}

	while (true) {
		std::cout << "Enter purpose: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (str.length() >= Constants::MIN_LENGTH_STRING) {
			guest.setPurpose(str);
			break;
		}
		else {
			std::cout << "Purpose cannot be less than 2 letters" << std::endl;
		}
	}
	if (guests.insert(guest)) {
		std::cout << std::endl << "Successfully registered" << std::endl;
		getBackToMainMenu();
	}
	else {
		std::cout << std::endl << "This person already registered" << std::endl;
		getBackToMainMenu();
	}
}

void deleteGuest(HashTable& guests, CyclicList<Record>& records) { 
	system("cls");
	std::string str;
	std::cout << "=====Deleting guest=====" << std::endl;
	while (true) {
		std::cout << "Enter passport of guest:";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (isRightPassport(str)) break;
		else std::cout << "Passport must be like \"NNNN-NNNNNN\"." << std::endl;
	}
	try {
		Record& rec = records.getBy([&](Record record) { return record.getPassport() == str && record.getDateOut() == "-"; });
		std::cout << "This guest lives in room \""<<rec.getNumber()<<"\", move him out first" << std::endl;
	}
	catch (...) {
		if (guests.remove(str))
			std::cout << "Successfully deleted" << std::endl;
		else
			std::cout << "Guest is not found" << std::endl;
	}
	getBackToMainMenu();
}

void deleteAllGuests(HashTable& guests, CyclicList<Record>& records) {
	system("cls");
	if (records.findBy([](Record rec) {
		return rec.getDateOut() == "-";
		})) {
		std::cout << "There is guests that lives in hotel. Move them out first." << std::endl;
		getBackToMainMenu();
		return;
	}
	std::cout << "You sure you want to delete all guests?(y/n)" << std::endl;
	if (_getch() == 'y') {
		guests.clearAllGuests();
		std::cout << "All guests were deleted" << std::endl;
	}
	getBackToMainMenu();
}

void findGuestByPassport(HashTable& guests, CyclicList<Record>& records) {
	system("cls");
	std::string str;
	std::cout << "=====Finding guest by passport=====" << std::endl;
	while (true) {
		std::cout << "Enter passport: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (isRightPassport(str)) {
			if (!guests.find(str)) {
				std::cout << std::endl << "This guest is not registered" << std::endl;
				getBackToMainMenu();
				return;
			}
			break;
		}
		else {
			std::cout << "Passport must be like \"NNNN-NNNNNN\"." << std::endl;
		}
	}
	try {
		Record& rec = records.getBy([&](Record record) { return record.getPassport() == str && record.getDateOut() == "-"; });
		std::cout << guests[str];
		std::cout << "Room:       " << rec.getNumber()<< std::endl;
	}
	catch (...) {
		std::cout << guests[str] << std::endl;
	}
	getBackToMainMenu();
}

void findGuestByFullname(HashTable& guests) {
	system("cls");
	std::string str;
	std::cout << "=====Finding guest by full name=====" << std::endl;
	while (true) {
		std::cout << "Enter full name: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (isRightFullname(str) && str.length() >= Constants::MIN_LENGTH_STRING) {
			break;
		}
		else {
			std::cout << "Full name cannot contain anything except letters and cannot be less than 2 letters" << std::endl;
		}
	}
	guests.print([&](Guest guest) { return findSubstring(toLower(guest.getFullName()),toLower(str))!=-1; });
	getBackToMainMenu();
}

void addRoom(Tree& rooms) {
	system("cls");
	Room room;
	std::string str;
	std::cout << "=====Registration new room=====" << std::endl;

	while (true) {
		std::cout << "Enter number of room: ";
		std::getline(std::cin, str);
		str = toUpper(clearEdgeSpaces(str));
		
		if (isRightNumber(str)) {
			if (!rooms.find(Room(str))) {
				room.setNumber(str);
				break;
			}else {
				std::cout << std::endl << "Room with number \"" << str << "\" already exists" << std::endl;
				getBackToMainMenu();
				return;
			}
		}else {
			std::cout << "Number must be like \"ANNN\"" << std::endl;
			std::cout << "Available types = {S,M,L,H}" << std::endl;
		}
	}
	while (true) {
		std::cout << "Enter number of places: ";
		int places = validInput("Input error\nEnter number of places: ");
		if (places <= Constants::MAX_PLACES && places>0) {
			if (room.getNumber()[0] == Constants::SINGLE && places != 1) {
				std::cout << "Single number cannot contain more than 1 place" << std::endl;
				continue;
			}
			room.setPlaces(places);
			break;
		}
		else
			std::cout << "Number of places must be less than " << Constants::MAX_PLACES << " and more than 0" << std::endl;
	}

	while (true) {
		std::cout << "Enter number of rooms: ";
		int rooms = validInput("Input error\nEnter number of rooms: ");
		if (rooms <= Constants::MAX_ROOMS&& rooms>0) {
			if (room.getNumber()[0] == Constants::SINGLE && rooms != 1) {
				std::cout << "Single number cannot contain more than 1 rooms" << std::endl;
				continue;
			}
			room.setRooms(rooms);
			break;
		}
		else
			std::cout << "Number of rooms must be less than " <<Constants::MAX_ROOMS << " and more than 0" << std::endl;
	}

	while (true) {
		std::cout << "Have bathroom? (y/n): ";
		char bathroom = _getch();
		std::cout << bathroom << std::endl;
		if (bathroom == 'y') {
			room.setBathroom(true);
			break;
		}
		else if (bathroom == 'n') {
			room.setBathroom(false);
			break;
		}
		else
			continue;
	}
	std::cout << "Enter equipment using anyone delimiter (press \"enter\" if there is no equipment): ";
	std::getline(std::cin, str);
	str = clearEdgeSpaces(str);
	room.setEquipment(str);

	if (rooms.add(room)) 
		std::cout << "Successfully added new room" << std::endl;

	getBackToMainMenu();
}

void deleteRoom(Tree& rooms, CyclicList<Record>& records, HashTable& guests) {
	system("cls");
	std::string str;
	std::cout << "=====Deleting room=====" << std::endl;
	while (true) {
		std::cout << "Enter number of room: ";
		std::getline(std::cin, str);
		str = toUpper(clearEdgeSpaces(str));

		if (isRightNumber(str)) {
			if (!rooms.find(Room(str))) {
				std::cout << std::endl << "Room with number \"" << str << "\" does not exist" << std::endl;
				getBackToMainMenu();
				return;
			}
			else {
				try {
					rooms.get(str);
				}
				catch (std::string error) {
					std::cout << std::endl << "Room with number \"" << str << "\" does not exist" << std::endl;
					getBackToMainMenu();
					return;
				}
			}
			break;
		}
		else
			std::cout << "Number must be like \"ANNN\"" << std::endl;

		if (str[0] != Constants::LUX && str[0] != Constants::HALF_LUX && str[0] != Constants::SINGLE && str[0] != Constants::MANY) {
			std::cout << "Available types = {S,M,L,H}" << std::endl;
			continue;
		}
	}
	try {
		records.getBy([&](Record record) { return record.getNumber() == str && record.getDateOut() == "-"; });
		std::cout << std::endl << "Guests that lives in this room, move them out first" << std::endl;
		guests.print([&](Guest guest) {
			return records.findBy([&](Record rec) { return rec.getPassport()==guest.getPassport()&&rec.getNumber() == str && rec.getDateOut() == "-"; });
			});
	}
	catch (std::string error) {
		try {
			rooms.remove(Room(str));
			std::cout << "Successfully deleted" << std::endl;
		}
		catch (...) {
			std::cout << "Room with number \"" << str << "\" does not exist" << std::endl;
		}
	}
	
	getBackToMainMenu();
}

void deleteAllRooms(Tree& rooms, CyclicList<Record>& records) {
	system("cls");
	if (records.findBy([](Record rec) {
		return rec.getDateOut() == "-";
		})) {
		std::cout << "There is guests that lives in hotel. Move them out first." << std::endl;
		getBackToMainMenu();
		return;
	}
	std::cout << "You sure you want to delete all rooms?(y/n)" << std::endl;
	if (_getch() == 'y') {
		rooms.clear();
		std::cout << "All rooms were deleted" << std::endl;
	}
	getBackToMainMenu();
}

void findRoomByNumber(Tree& rooms, CyclicList<Record>& records, HashTable& guests) {
	system("cls");
	std::string str;
	std::cout << "=====Finding room by number=====" << std::endl;


	while (true) {
		std::cout << "Enter number of room: ";
		std::getline(std::cin, str);
		str = toUpper(clearEdgeSpaces(str));

		if (isRightNumber(str)) {
			try {
				rooms.get(str);
			}
			catch (std::string error) {
				std::cout << std::endl << "Room with number \"" << str << "\" does not exist" << std::endl;
				getBackToMainMenu();
				return;
			}
			break;
		}
		else {
			std::cout << "Number must be like \"ANNN\"" << std::endl;
			std::cout << "Available types = {S,M,L,H}" << std::endl;
		}
	}
	try {
		Room& room = rooms.get(str);
		std::cout << room << std::endl;
	}
	catch (std::string error) {
		std::cout << std::endl << "Room with number \"" << str << "\" does not exist" << std::endl;
		getBackToMainMenu();
		return;
	}


	std::cout <<std::endl << "Guests that lives in this room" << std::endl;
	guests.print([&](Guest guest) {
		return records.findBy([&](Record rec) { return rec.getPassport() == guest.getPassport() && rec.getNumber() == str && rec.getDateOut() == "-"; });
		});

	getBackToMainMenu();
}

void findRoomByEquipment(Tree& rooms)	 {
	system("cls");
	std::string str;
	std::cout << "=====Finding room by equipment=====" << std::endl;
	std::cout << "Enter equipment: ";
	std::getline(std::cin, str);
	str = clearEdgeSpaces(str);
	if(str!="")
		rooms.print([&](Room room) {
			return findSubstring(toLower(room.getEquipment()), toLower(str)) != -1;
			});
	else
		rooms.print([&](Room room) {
			return true;
			});
	getBackToMainMenu();
}

void registraionMoveIn(CyclicList<Record>& records, HashTable& guests,Tree& rooms) {
	system("cls");
	Record record;
	std::string str;
	std::cout << "=====Registration move in=====" << std::endl;

	while (true) {
		std::cout << "Enter passport: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (isRightPassport(str)) {
			if (!guests.find(str)) {
				std::cout << std::endl << "Person is not registered" << std::endl;
				getBackToMainMenu();
				return;
			}
			if (records.findBy([&](Record record) { return record.getPassport() == str && record.getDateOut() == "-"; })) {
				std::cout << std::endl << "Person already lives in hotel" << std::endl;
				getBackToMainMenu();
				return;
			}
			record.setPassport(str);
			break;
		}
		else {
			std::cout << "Passport must be like \"NNNN-NNNNNN\"." << std::endl;
		}
	}

	while (true) {
		std::cout << "Enter number of room: ";
		std::getline(std::cin, str);
		str = toUpper(clearEdgeSpaces(str));

		if (isRightNumber(str)) {
			if (!rooms.find(Room(str))) {
				try {
					rooms.get(str);
				}
				catch (std::string error) {
					std::cout << std::endl << "Room with number \"" << str << "\" does not exist" << std::endl;
					getBackToMainMenu();
					return;
				}
			}
			try {
				if (records.countBy([&](Record record) { return record.getNumber() == str && record.getDateOut() == "-"; }) >= rooms.get(str).getPlaces()) {
					std::cout << std::endl << "Room is already full" << std::endl;
					getBackToMainMenu();
					return;
				}
			}
			catch (std::string error) {
				std::cout << std::endl << "Room with number \"" << str << "\" does not exist" << std::endl;
				getBackToMainMenu();
				return;
			}
			
			record.setNumber(str);
			break;
		}
		else
			std::cout << "Number must be like \"ANNN\"" << std::endl;

		if (str[0] != Constants::LUX && str[0] != Constants::HALF_LUX && str[0] != Constants::SINGLE && str[0] != Constants::MANY) {
			std::cout << "Available types = {S,M,L,H}" << std::endl;
			continue;
		}
	}

	while (true) {
		std::cout << "Enter date in(dd.MM.yyyy):";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		try {
			Calendar c(str);
			record.setDateIn(str);
			break;
		}
		catch (std::string error) {
			std::cout << error << std::endl;
		}
	}
	record.setDateOut("-");
	records.pushBack(record);
	sortByNumber(records);
	std::cout << "Successfully moved in" << std::endl;
	getBackToMainMenu();
}

void registraionMoveOut(CyclicList<Record>& records, HashTable& guests, Tree& rooms) {
	system("cls");
	Record record;
	std::string str;
	std::cout << "=====Registration move out=====" << std::endl;

	while (true) {
		std::cout << "Enter passport: ";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		if (isRightPassport(str)) {
			if (!guests.find(str)) {
				std::cout << std::endl << "Person is not registered" << std::endl;
				getBackToMainMenu();
				return;
			}
			if (!records.findBy([&](Record record) { return record.getPassport() == str && record.getDateOut() == "-"; })) {
				std::cout << std::endl << "Person does not live in hotel" << std::endl;
				getBackToMainMenu();
				return;
			}
			record.setPassport(str);
			break;
		}
		else {
			std::cout << "Passport must be like \"NNNN-NNNNNN\"." << std::endl;
		}
	}

	//while (true) {
	//	std::cout << "Enter number of room: ";
	//	std::getline(std::cin, str);
	//	str = toUpper(clearEdgeSpaces(str));

	//	if (isRightNumber(str)) {
	//		if (!rooms.find(Room(str))) {
	//			try {
	//				rooms.get(str);
	//			}
	//			catch (std::string error) {
	//				std::cout << std::endl << "Room with number \"" << str << "\" does not exist" << std::endl;
	//				getBackToMainMenu();
	//				return;
	//			}
	//		}
	//		if (!records.findBy([&](Record rec) { return rec.getNumber() == str && rec.getPassport() == record.getPassport() && rec.getDateOut() == "-"; })) {
	//			std::cout << std::endl << "Person does not live in room with number \"" << str << "\"" << std::endl;
	//			getBackToMainMenu();
	//			return;
	//		}
	//		record.setNumber(str);
	//		break;
	//	}
	//	else
	//		std::cout << "Number must be like \"ANNN\"" << std::endl;

	//	if (str[0] != Constants::LUX && str[0] != Constants::HALF_LUX && str[0] != Constants::SINGLE && str[0] != Constants::MANY) {
	//		std::cout << "Available types = {S,M,L,H}" << std::endl;
	//		continue;
	//	}
	//}

	Record& recordIn = records.getBy([&](Record rec) { return rec.getPassport() == record.getPassport() && rec.getDateOut() == "-"; });
	while (true) {
		std::cout << "Enter date out(dd.MM.yyyy):";
		std::getline(std::cin, str);
		str = clearEdgeSpaces(str);
		try {
			Calendar in(recordIn.getDateIn());
			Calendar out(str);
			if (out <= in) {
				std::cout << "Date out cannot be less or equal than date in" << std::endl;
				continue;
			}
			recordIn.setDateOut(str);
			break;
		}
		catch (std::string error) {
			std::cout << error << std::endl;
		}
	}
	std::cout << "Successfully moved out from \""<<recordIn.getNumber()<<"\"" << std::endl;
	getBackToMainMenu();
}
#endif