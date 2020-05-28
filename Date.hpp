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

	//������� �� ����.
	void setDay(unsigned);
	void setMonth(unsigned);
	void setYear(unsigned);

	//������ �� ������������ �� ������.
	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	//��������� �� ����.
	void printDate()const;

	//��������� � ������� ����.
	void serialize(std::ofstream&) const;

	//������ �� ������� ����.
	void deserialize(std::ifstream&)const;
};

#endif
