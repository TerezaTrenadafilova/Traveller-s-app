#ifndef __DESTINATION_HPP
#define __DESTINATION_HPP

#include<fstream>

class Destination {
private:
	char* m_name;
	unsigned m_numberOfVisits;
	unsigned m_sumOfAllEstimates;
	//double m_average;

public:
	//Голяма четворка.
	Destination();
	Destination(char*, unsigned, unsigned/*, double*/);
	Destination(const Destination&);
	Destination& operator=(const Destination&);
	~Destination();

	//Сетъри и гетъри
	void setName(char*);
//	void setAverage(double);
	void setNumberOfVisits(unsigned);
	void setSumOfAll(unsigned);

	char* getDestination()const;
	double getAverage() const;
	unsigned getSumOfALL()const;
	unsigned getNumberOfVisits()const;

	//Записване на информация в двойчен файл.
	void serialize(std::ofstream&) const;

	//Четене на информация от двоичен файл.
	void deserialize(std::ifstream&);
private:
	//Функция за копиране
	void copy(const Destination&);
};

#endif
