#ifndef __DESTINATION_HPP
#define __DESTINATION_HPP

#include<fstream>
#include"User.hpp"


class User;//�� �� ���� �� �� ������� �������� class Destination.

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
	//������ ��������.
	Destination();
	Destination(char*, unsigned=0, unsigned=Capacity, User* =nullptr, unsigned = 0, unsigned = Capacity);
	//Destination(char*, unsigned, unsigned, User*, unsigned, unsigned);
	Destination(const Destination&);
	Destination& operator=(const Destination&);
	~Destination();

	//������ � ������
	void setName(char*);
//	void setAverage(double);
	void setNumberOfVisits(unsigned);
	void setSumOfAll(unsigned);

	char* getDestination()const;
	double getAverage() const;
	unsigned getSumOfALL()const;
	unsigned getNumberOfVisits()const;

	//��������� �� ���������� � ������� ����.
	void serialize(std::ofstream&) const;

	//������ �� ���������� �� ������� ����.
	void deserialize(std::ifstream&);

	//�������� �� ��� ����������
	void addUser(const User&);

	//������� �������������, ����� �� �������� �����������.
	void printUserWhoVisitedDestination() const;

private:
	//������� �� ��������
	void copy(const Destination&);

	//������� �� ��������� �� �������.
	void cleanMemory();

	//������� �� ���������������
	void resize();
};

#endif
