#ifndef _GUEST_
#define _GUEST_

#include<string>
#include<iomanip>

class Guest {
private:
	std::string _passport; // "NNNN-NNNNNN"
	std::string _fullName;
	int _birthYear;
	std::string _address;
	std::string _purpose;
public:
	Guest(std::string passport="", std::string fullName="", int birthYear=0, std::string address="", std::string purpose="") {
		_passport = passport;
		_fullName = fullName;
		_birthYear = birthYear;
		_address = address;
		_purpose = purpose;
	}

	std::string getPassport() { return _passport; }
	std::string getFullName() { return _fullName; }
	int getBirthYear() { return _birthYear; }
	std::string getAddress() { return _address; }
	std::string getPurpose() { return _purpose; }

	void setPassport(std::string passport) {  _passport = passport; }
	void setFullName(std::string fullName) {  _fullName = fullName; }
	void setBirthYear(int birthYear) {  _birthYear = birthYear; }
	void setAddress(std::string address) {  _address = address; }
	void setPurpose(std::string purpose) {  _purpose = purpose; }
};

std::ostream& operator<<(std::ostream& out, Guest& guest) {
	out << "Passport:   " << guest.getPassport() << '\n';
	out << "Full name:  " << guest.getFullName() << '\n';
	out << "Birth year: " << guest.getBirthYear() << '\n';
	out << "Address:    " << std::boolalpha << guest.getAddress() << '\n';
	out << "Purpose:    " << guest.getPurpose() << '\n';
	return out;
}

#endif
