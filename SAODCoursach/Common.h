#ifndef _COMMON_
#define _COMMON_

#include<string>
#include<vector>
#include<iostream>
#include<random>

#include"Record.h"
#include"CyclicList.h"
#include"Constants.h"
#include"Calendar.h"

void getBackToMainMenu() {
	std::cout << "Press any key to get back to main menu";
	_getch();
}

std::string clearEdgeSpaces(std::string str) { // delete spaces,tabs and \n around the edges of string
	if (str.length() != 0)
		while (str[0] == ' ' || str[0] == '\t' || str[0] == '\n') {

			str.erase(0, 1);
		}
	if (str.length() != 0)
		while (str[str.length() - 1] == ' ' || str[str.length() - 1] == '\t' || str[str.length() - 1] == '\n') {
			str.erase(str.length() - 1, 1);
		}
	return str;

}

bool isDigit(char symbol) {
	return (int(symbol) >= 48 && int(symbol) <= 57);
}
bool isLowLetter(char symbol) {
	return (int(symbol) >= 97 && int(symbol) <= 122);
}
bool isHighLetter(char symbol) {
	return (int(symbol) >= 65 && int(symbol) <= 90);
}

std::string toLower(std::string str) {
	for (int i = 0; i < str.length(); i++)
		if (isHighLetter(str[i])) str[i] += 32;
	return str;
}

std::string toUpper(std::string str) {
	for (int i = 0; i < str.length(); i++)
		if (isLowLetter(str[i])) str[i] -= 32;
	return str;
}

bool isRightPassport(std::string passport) {
	if (passport.length() != Constants::PASSPORT_FORMAT.length()) return false;
	if (passport[4] != '-') return false;
	for (int i = 0; i < Constants::PASSPORT_FORMAT.length(); i++) {
		if (i != 4) {
			if (!isDigit(passport[i])) return false;
		}
	}
	return true;
}


bool isRightFullname(std::string fullname) {
	for (int i = 0; i < fullname.length(); i++) {
		if (!(isLowLetter(fullname[i]) || isHighLetter(fullname[i]) || fullname[i] == ' ')) return false;
	}
	return true;
}

bool isRightNumber(std::string number) // number ~ ANNN (A - type of number)
{
	if (number.length() != Constants::NUMBER_FORMAT.length()) return false;
	if (number[0] != Constants::LUX && number[0] != Constants::HALF_LUX && number[0] != Constants::SINGLE && number[0] != Constants::MANY) return false;
	for (int i = 1; i <= 3; i++) {
		if (!isDigit(number[i])) return false;
	}
}



int validInput(std::string errorMessage = "input error")
{
	int value;
	while (true)
	{
		std::cin >> value;

		if (std::cin.fail())
		{
			std::cerr << errorMessage;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return value;
	}
}

std::string randomPassport() {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<> random(0, 9);
	std::string str = "";
	for (int i = 0; i < Constants::PASSPORT_FORMAT.length(); i++) {
		if (i == 4) {
			str += '-';
			continue;
		}
		str += std::to_string(random(mt));
	}
	return str;
}

int numberToInt(std::string number) { // number ~ "ANNN"
	int result = 0;
	for (int i = 1; i < number.length(); i++)
	{
		result += (int(number[i]) - Constants::ASCII_COEFF) * pow(10, number.length() - i - 1);
	}
	return result;
}

void sortByNumber(CyclicList<Record>& list) {
	std::vector <std::vector<Record>> buffer(Constants::MAX_NUMBER);
	for (int i = 0; i < list.getSize(); i++) {
		buffer[numberToInt(list[i].getNumber())].push_back(list[i]);
	}
	list.clear();
	for (int i = 0; i < buffer.size(); i++) {
		for (int j = 0; j < buffer[i].size(); j++) {
			list.pushBack(buffer[i][j]);
		}
	}
}

int goodSuffix(int j, std::string& sample) {
	int last = sample.length() - 1;
	int index = -1;
	j--;
	while (j >= 0) {
		if (sample[j] == sample[last]) {
			index = j;
			break;
		}
		else j--;
	}
	return last - index;
}

int badSymbol(int j, char symbol, std::string sample)
{
	int index = -1;
	for (int i = j - 1; i >= 0; --i)
	{
		if (sample[i] == symbol)
		{
			index = i;
			break;
		}
	}
	return j - index;
}

int findSubstring(std::string str, std::string sample)
{
	if (str.length() < sample.length()) return -1;

	int i = sample.length() - 1;
	int	j = sample.length() - 1;

	while (i < str.length()) {
		if (str[i] == sample[j]) {
			if (j == 0) return i;
			i--;
			j--;
		}
		else {
			int bad = badSymbol(j, str[i], sample);
			if (j == sample.length() - 1) {
				i = i + bad;
				j = sample.length() - 1;
			}
			else {
				if (bad == -1)
					bad = sample.length();
				int good = goodSuffix(j, sample);
				int difference = bad > good ? bad : good;
				i = i + sample.length() - 1 - j + difference;
				j = sample.length() - 1;
			}
		}
	}
	return -1;
}



#endif