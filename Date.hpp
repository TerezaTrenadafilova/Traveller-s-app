#ifndef __DATE_HPP
#define __DATE_HPP

#include<fstream>

class Date {
private:
	unsigned m_day;
	unsigned m_month;
	unsigned m_year;

	bool isLeapYear(unsigned);

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
