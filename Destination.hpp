#ifndef __DESTINATION_HPP
#define __DESTINATION_HPP

#include<fstream>
#include "User.hpp"

class Destination {
private:
	char* m_name;
	unsigned m_numberOfVisits;
	unsigned m_sumOfAllEstimates;
	//double m_average;

	//����� ���������� �� ��� ������ � �����������, ����� �� � ��������
	User* m_users;
	unsigned m_numberOfUsers;
	unsigned m_capacityOfUsers;

public:
	//������ ��������.
	Destination();
	Destination(char*, unsigned, unsigned, User*, unsigned, unsigned);
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
private:
	//������� �� ��������
	void copy(const Destination&);

	//������� �� ���������������
	void resize();
};

#endif
