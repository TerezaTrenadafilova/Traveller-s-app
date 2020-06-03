#ifndef __DESTINATION_HPP
#define __DESTINATION_HPP

#include<fstream>
#include"User.hpp"


class User;//За да може да се създаде правилно class Destination.

class Destination {
private:
	char* m_name;
	unsigned m_numberOfVisits;
	unsigned m_sumOfAllEstimates;
	
	User* m_users;  // C4430
	unsigned m_numberOfUsers;
	unsigned m_capacityOfUsers;

	static const unsigned Capacity = 8;
public:
	//Голяма четворка.
	Destination();
	Destination(char*, unsigned=0, unsigned=Capacity, User* =nullptr, unsigned = 0, unsigned = Capacity);
	//Destination(char*, unsigned, unsigned, User*, unsigned, unsigned);
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

	//Добавяне на нов потребител
	void addUser(const User&);

	//Извежда потребителите, които са посетели дестницията.
	void printUserWhoVisitedDestination() const;

private:
	//Функция за копиране
	void copy(const Destination&);

	//Функция за изтриване на паметта.
	void cleanMemory();

	//Функция за преоразмеряване
	void resize();
};

#endif
