#ifndef _HASHTABLE_
#define _HASHTABLE_
#include<string>
#include<iostream>

#include"List.h"
#include"Constants.h"
#include"Guest.h"

class HashTable {
private:
	int _size;
	List<Guest>* _arr;
	int hash_func(std::string str) {
		unsigned long long int multiply = 1;
		int sum = 0;
		for (int i = 0; i < Constants::PASSPORT_FORMAT.length(); i++)
		{
			multiply *= int(str[i]);
			sum += int(str[i]) * int(str[i]);
		}
		int result = (multiply / sum) % _size;
		return result;
	}
	void clear() {
		delete[] _arr;
		_arr = nullptr;
	}
public:
	HashTable(int size) {
		_size = size;
		_arr = new List <Guest>[_size];
	}
	Guest& operator[](std::string passport) {
		try {
			int hash = hash_func(passport);
			return _arr[hash].getBy([passport](Guest guest) {
				return passport == guest.getPassport();
				});
		}
		catch (std::string error) {
			throw passport + std::string(" doesn't exist!");
		}
	}

	bool find(Guest guest) {
		int hash = hash_func(guest.getPassport());
		return _arr[hash].findBy([&](Guest g) {
			return guest.getPassport() == g.getPassport();
			});
	}
	bool find(std::string passport) {
		int hash = hash_func(passport);
		return _arr[hash].findBy([&](Guest g) {
			return passport == g.getPassport();
			});
	}

	bool insert(Guest guest) {
		if (!(this->find(guest))) {
			int hash = hash_func(guest.getPassport());
			_arr[hash].pushBack(guest);
			return true;
		}
		return false;
	}

	bool remove(Guest guest) {
		try {
			int hash = hash_func(guest.getPassport());
			_arr[hash].removeBy([&guest](Guest g) {
				return guest.getPassport() == g.getPassport();
				});
			return true;
		}
		catch (std::string error) {
			std::cerr << guest.getPassport() + std::string(" is not found.");
		}
		return false;
	}

	bool remove(std::string passport) {
		try {
			int hash = hash_func(passport);
			_arr[hash].removeBy([&passport](Guest g) {
				return passport == g.getPassport();
				});
			return true;
		}
		catch (std::string error) {
			//std::cerr << passport + std::string(" is not found.");
		}
		return false;
	}

	void printEdgeLine(int maxLengthPassport, int maxLengthFullname,int maxLengthBirthYear,int maxLengthAddress,int maxLengthPurpose) {
		std::cout << "+-";
		for (int i = 0; i < maxLengthPassport; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthFullname; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthBirthYear; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthAddress; i++)
			std::cout << "-";
		std::cout << "-+-";
		for (int i = 0; i < maxLengthPurpose; i++)
			std::cout << "-";
		std::cout << "-+" << std::endl;
	}

	void printElementByMaxWidth(std::string str, int maxLength) {
		int diff = maxLength - str.length();
		std::cout << str;
		for (int i = 0; i < diff; i++)
			std::cout << " ";
	}

	void printLine(Guest guest, int maxLengthPassport, int maxLengthFullname, int maxLengthBirthYear, int maxLengthAddress, int maxLengthPurpose) {
		std::cout << "| ";
		printElementByMaxWidth(guest.getPassport(), maxLengthPassport);
		std::cout << " | ";
		printElementByMaxWidth(guest.getFullName(), maxLengthFullname);
		std::cout << " | ";
		printElementByMaxWidth(std::to_string(guest.getBirthYear()), maxLengthBirthYear);
		std::cout << " | ";
		printElementByMaxWidth(guest.getAddress(), maxLengthAddress);
		std::cout << " | ";
		printElementByMaxWidth(guest.getPurpose(), maxLengthPurpose);
		std::cout << " |" << std::endl;
	}

	void print(std::function<bool(Guest)> predicat) {
		if (!isEmpty()) {
			int maxLengthFullname = 9;
			int maxLengthBirthYear = 10;
			int maxLengthAddress = 7;
			int maxLengthPurpose = 7;

			for (int i = 0; i < _size; i++) {
				for (int j = 0; j < _arr[i].getSize(); j++) {
					if (_arr[i][j].getFullName().length() > maxLengthFullname) maxLengthFullname = _arr[i][j].getFullName().length();
					if (std::to_string(_arr[i][j].getBirthYear()).length() > maxLengthBirthYear) maxLengthBirthYear = std::to_string(_arr[i][j].getBirthYear()).length();
					if (_arr[i][j].getAddress().length() > maxLengthAddress) maxLengthAddress = _arr[i][j].getAddress().length();
					if (_arr[i][j].getPurpose().length() > maxLengthPurpose) maxLengthPurpose = _arr[i][j].getPurpose().length();
				}
			}

			printEdgeLine(Constants::PASSPORT_FORMAT.length(), maxLengthFullname, maxLengthBirthYear, maxLengthAddress, maxLengthPurpose);
			std::cout << "| ";
			printElementByMaxWidth("Passport", Constants::PASSPORT_FORMAT.length());
			std::cout << " | ";
			printElementByMaxWidth("Full name", maxLengthFullname);
			std::cout << " | ";
			printElementByMaxWidth("Birth year", maxLengthBirthYear);
			std::cout << " | ";
			printElementByMaxWidth("Address", maxLengthAddress);
			std::cout << " | ";
			printElementByMaxWidth("Purpose", maxLengthPurpose);
			std::cout << " |" << std::endl;
			printEdgeLine(Constants::PASSPORT_FORMAT.length(), maxLengthFullname, maxLengthBirthYear, maxLengthAddress, maxLengthPurpose);
			for (int i = 0; i < _size; i++) {
				for (int j = 0; j < _arr[i].getSize(); j++) {
					if(predicat(_arr[i][j]))
						printLine(_arr[i][j], Constants::PASSPORT_FORMAT.length(), maxLengthFullname, maxLengthBirthYear, maxLengthAddress, maxLengthPurpose);
				}
			}
			printEdgeLine(Constants::PASSPORT_FORMAT.length(), maxLengthFullname, maxLengthBirthYear, maxLengthAddress, maxLengthPurpose);

		}
		else
			std::cout << "Empty" << std::endl;
	}

	bool isEmpty() {
		for (int i = 0; i < _size; i++)
		{
			if (!_arr[i].isEmpty()) return false;
		}
		return true;
	}

	void clearAllGuests() {
		clear();
		_arr = new List <Guest>[_size];
	}

	~HashTable() {
		clear();
	}
};

#endif
