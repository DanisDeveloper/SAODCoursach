#ifndef _CALENDAR_
#define _CALENDAR_

#include<iostream>

bool isDigit(char symbol);

class Calendar {
private:
	int month_array[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int day;
	int month;
	int year;
public:
	Calendar();
	Calendar(std::string date);
	Calendar(int day, int month, int year);
	Calendar(const Calendar& calendar);
	void set_day(int day);
	void set_month(int month);
	void set_year(int year);
	void set_date(int day, int month, int year);
	int get_day();
	int get_month();
	int get_year();

	bool operator> (Calendar& c1);
	bool operator< (Calendar& c1);
	bool operator>= (Calendar& c1);
	bool operator<= (Calendar& c1);
	bool operator==(Calendar& c1);
	bool operator!=(Calendar& c1);

};

Calendar::Calendar() {
	this->set_date(1, 1, 1970);
}
Calendar::Calendar(std::string date)
{
	if (date.length() != Constants::DATE_FORMAT.length()) throw std::string("Incorrect date");
	if (date[2] != '.' || date[5] != '.') throw std::string("Incorrect date");
	for (int i = 0; i < date.length(); i++) {
		if (i == 2 || i == 5) continue;
		if (!isDigit(date[i])) throw std::string("Incorrect date");
	}
	int day = (int(date[0]) - Constants::ASCII_COEFF) * 10 + (int(date[1]) - Constants::ASCII_COEFF);
	int month = (int(date[3]) - Constants::ASCII_COEFF) * 10 + (int(date[4]) - Constants::ASCII_COEFF);
	int year = (int(date[6]) - Constants::ASCII_COEFF) * 1000 +
		(int(date[7]) - Constants::ASCII_COEFF) * 100 +
		(int(date[8]) - Constants::ASCII_COEFF) * 10 +
		(int(date[9]) - Constants::ASCII_COEFF);
	this->set_date(day, month, year);
}
Calendar::Calendar(int day, int month, int year) {
	this->set_date(day, month, year);
}
Calendar::Calendar(const Calendar& calendar) {
	this->set_date(calendar.day, calendar.month, calendar.year);
}
void Calendar::set_day(int day) {
	if (year % 4 == 0) {
		month_array[1] = 29;
		if (year % 100 == 0 && year % 400 != 0) {
			month_array[1] = 28;
		}
	}
	else {
		month_array[1] = 28;
	}
	if (day < 1 || day > this->month_array[month - 1]) {
		throw std::string("Incorrect date");
	}
	else {
		this->day = day;
	}
}

void Calendar::set_month(int month) {
	if (month < 1 || month > 12) {
		throw std::string("Incorrect date");
	}
	else {
		this->month = month;
	}
}

void Calendar::set_year(int year) {
	this->year = year;
}

void Calendar::set_date(int day, int month, int year) {
	this->set_year(year);
	this->set_month(month);
	this->set_day(day);

}
int Calendar::get_day() {
	return this->day;
}
int Calendar::get_month() {
	return (this->month);
}
int Calendar::get_year() {
	return this->year;
}

bool Calendar::operator> (Calendar& c1) {
	if (c1.year > this->year) return true;
	else if (c1.year < this->year) return false;
	else if (c1.month > this->month) return true;
	else if (c1.month < this->month) return false;
	else if (c1.day > this->day) return true;
	else if (c1.day < this->day) return false;
	else return false;
}
bool Calendar::operator< (Calendar& c1) {
	if (c1.year < this->year) return true;
	else if (c1.year > this->year) return false;
	else if (c1.month < this->month) return true;
	else if (c1.month > this->month) return false;
	else if (c1.day < this->day) return true;
	else if (c1.day > this->day) return false;
	else return false;
}
bool Calendar::operator>= (Calendar& c1) {
	if (c1 == (*this)) return true;
	if (c1 > (*this)) return true;
	return false;
}
bool Calendar::operator<= (Calendar& c1) {
	if (c1 == (*this)) return true;
	if (c1 < (*this)) return true;
	return false;
}
bool Calendar::operator==(Calendar& c1) {
	if (c1.year == this->year && c1.month == this->month && c1.day == this->day) return true;
	return false;
}
bool Calendar::operator!=(Calendar& c1) {
	if (c1.year != this->year || c1.month != this->month || c1.day != this->day) return true;
	return false;
}


#endif // !_CALENDAR_
