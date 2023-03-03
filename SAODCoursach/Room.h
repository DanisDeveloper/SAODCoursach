#ifndef _ROOM_
#define _ROOM_

#include<string>
#include<iomanip>
#include"Constants.h"
#include"Common.h"


class Room {
private:
	std::string _number;
	int _places;
	int _rooms;
	bool _bathroom;
	std::string _equipment;
public:
	Room(std::string number = "", int places = 0, int rooms = 0, bool bathroom = 0, std::string equipment = "") {
		_number = number;
		_places = places;
		_rooms = rooms;
		_bathroom = bathroom;
		_equipment = equipment;
	}

	std::string getNumber() { return _number; }
	int getPlaces() { return _places; }
	int getRooms() { return _rooms; }
	bool getBathroom() { return _bathroom; }
	std::string getEquipment() { return _equipment; }

	void setNumber(std::string number) {  _number = number; }
	void setPlaces(int places) {  _places = places; }
	void setRooms(int rooms) {  _rooms = rooms; }
	void setBathroom(bool bathroom) {  _bathroom = bathroom; }
	void setEquipment(std::string equipment) {  _equipment = equipment; }

	bool operator<(Room& room) {
		return numberToInt(_number) < numberToInt(room._number);
	}
	bool operator>(Room& room) {
		return numberToInt(_number) > numberToInt(room._number);
	}
	bool operator<=(Room& room) {
		return numberToInt(_number) <= numberToInt(room._number);
	}
	bool operator>=(Room& room) {
		return numberToInt(_number) >= numberToInt(room._number);
	}
	bool operator==(Room& room) {
		return numberToInt(_number) == numberToInt(room._number);
	}
	bool operator!=(Room& room) {
		return numberToInt(_number) != numberToInt(room._number);
	}
};

std::ostream& operator<<(std::ostream& out, Room& room) {
	out << "Number:    " << room.getNumber() << '\n';
	out << "Places:    " << room.getPlaces() << '\n';
	out << "Rooms:     " << room.getRooms() << '\n';
	out << "Bathroom:  " << std::boolalpha << room.getBathroom() << '\n';
	out << "Equipment: " << room.getEquipment() << '\n';
	return out;
}

#endif