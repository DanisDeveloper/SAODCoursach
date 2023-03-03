#ifndef _RECORD_
#define _RECORD_


#include<string>
#include<iomanip>

int numberToInt(std::string number);

class Record {
private:
	std::string _passport; // NNNN-NNNNNN
	std::string _number;   // ANNN
	std::string _dateIn;   // dd.MM.yyyy
	std::string _dateOut;  // dd.MM.yyyy

public:
	Record(std::string passport = "", std::string number = "", std::string dateIn = "", std::string dateOut = "") {
		_passport = passport; // NNNN-NNNNNN
		_number = number;   // ANNN
		_dateIn = dateIn;   // dd.MM.yyyy
		_dateOut = dateOut;  // dd.MM.yyyy
	}

	std::string getPassport() { return _passport; }
	std::string getNumber() { return _number; }
	int getIntNumber() { return numberToInt(_number); }
	std::string getDateIn() { return _dateIn; }
	std::string getDateOut() { return _dateOut; }

	void setPassport(std::string passport) {  _passport = passport; }
	void setNumber(std::string number) {  _number = number; }
	void setDateIn(std::string dateIn) {  _dateIn = dateIn; }
	void setDateOut(std::string dateOut) {  _dateOut = dateOut; }
};

std::ostream& operator<<(std::ostream& out, Record& rec) {
	out << "Passport: " << rec.getPassport() << '\n';
	out << "Number:   " << rec.getNumber() << '\n';
	out << "Date in:  " << rec.getDateIn() << '\n';
	out << "Date out: " << rec.getDateOut() << '\n';
	return out;
}

#endif