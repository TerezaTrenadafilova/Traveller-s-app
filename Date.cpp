#include<iostream>

#include"Date.hpp"



bool Date::isLeapYear(unsigned year)
{
	if (year % 4 == 0 && year%100!=0) {
		return true;
	}
	else {
		return false;
	}
}

Date::Date(unsigned day, unsigned month, unsigned year)
{
	//Първо инициялизираме годината, след това месеца и накрая деня, за да може да направим валидация за деня.
	setYear(year);
	setMonth(month);
	setDay(day);
	
}

void Date::setDay(unsigned day)
{
	if (m_month == 1 || m_month == 3 || m_month == 5 || m_month == 7 || m_month == 8 || m_month == 10 || m_month == 12) {
		if (day == 0 || day > NUMBER_DAYS_FULL_MONTH) {
			std::cout << "Invalid date. " ;
			std::cout << "Program will set date of 31th. If you not agree, try again." << std::endl;
			m_day = NUMBER_DAYS_FULL_MONTH;
			return;
		}
		else {
			m_day = day;
		}
	}

	//Ако месецът е февруари.
	if (m_month == 2) {
		
		//Проверка дали годината е високосна.
		if (isLeapYear(m_year) == true) {
			if (day == 0 || day > NUMBER_OF_DAYS_FEBR + 1) {
				std::cout << "Invalid date. " ;
				std::cout << "Program will set date of 29th. If you not agree, try again." << std::endl;
				m_day = NUMBER_OF_DAYS_FEBR + 1;
				return;
			}
			else {
				m_day = day;
			}
		}
		else {
			if (day == 0 || day > NUMBER_OF_DAYS_FEBR) {
				std::cout << "Invalid date. ";
				std::cout << "Program will set date of 28th. If you not agree, try again." << std::endl;
				m_day = NUMBER_OF_DAYS_FEBR;
				return;
			}
			else {
				m_day = day;
			}
		}
	}

	if (m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11) {
		if (day == 0 || day > NUMBER_OF_DAYS_ANOTHER_MONTH) {
			std::cout << "Invalid date. ";
			std::cout<< "Program will set date of 30th. If you not agree, try again." << std::endl;
			m_day = NUMBER_OF_DAYS_ANOTHER_MONTH;
			return;
		}
		else {
			m_day = day;
		}
	}
	/*m_day = day;*/

}

void Date::setMonth(unsigned month) 
{
	if (month > 0 || month <= NUMBER_OF_MONTHS) {
		m_month = month;
	}
	else {
		std::cout << "Invalid date." << std::endl;
		return;
	}
}

void Date::setYear(unsigned year)
{
	if (year >= MIN_YEAR && year <= TEMP_YEAR) {
		m_year = year;
	}
	else {
		std::cout << "Invalid date." << std::endl;
		return;
	}
}

unsigned Date::getDay() const
{
	return m_day;
}

unsigned Date::getMonth() const
{
	return m_month;
}

unsigned Date::getYear() const
{
	return m_year;
}

void Date::printDate() const
{
	std::cout << getYear() << '.' << getMonth() << '.' <<getDay();

}

void Date::serialize(std::ofstream & ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	ofs.write((const char*)& m_day, sizeof(m_day));
	ofs.write((const char*)& m_month, sizeof(m_month));
	ofs.write((const char*)& m_year, sizeof(m_year));

	/*if (ofs.good()) {
		std::cout << "Successfully serialize of date." << std::endl;
	}
	else {
		std::cout << "Serialize failed. Error! " << std::endl;
	}*/

}

void Date::deserialize(std::ifstream & ifs) const
{
	if (!ifs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}
	ifs.read((char*)& m_day, sizeof(m_day));
	ifs.read((char*)& m_month, sizeof(m_month));
	ifs.read((char*)& m_year, sizeof(m_year));

	/*if (ifs.good()) {
		std::cout << "Successfully deserialization!" << std::endl;
	}
	else {
		std::cout << "Deserialize failed! Error!" << std::endl;
	}*/
}
