#ifndef __DATE_HPP
#define __DATE_HPP

#include<fstream>

class Date {
private:
	//Член-данни
	unsigned m_day;
	unsigned m_month;
	unsigned m_year;

	bool isLeapYear(unsigned);

	//Константи
	static const unsigned NUMBER_DAYS_FULL_MONTH = 31;
	static const unsigned NUMBER_OF_DAYS_FEBR = 28;
	static const unsigned NUMBER_OF_DAYS_ANOTHER_MONTH = 30;
	static const unsigned NUMBER_OF_MONTHS = 12;
	static const unsigned MIN_YEAR = 1900;
	static const unsigned TEMP_YEAR = 2020;

public:
	Date(unsigned = 1, unsigned = 1, unsigned = 1900);

	//Промяна на дата.
	void setDay(unsigned);
	void setMonth(unsigned);
	void setYear(unsigned);

	//достъп до компонентите на датата.
	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	//Извеждане на дата.
	void printDate()const;

	//Записване в бинарен файл.
	void serialize(std::ofstream&) const;

	//Четене от бинарен файл.
	void deserialize(std::ifstream&)const;

};

#endif
