#ifndef __USER_HPP
#define __USER_HPP

#include<fstream>
#include<cstring>
#include"TravelInformation.hpp"

class User {
private:
	//�������, ����� �� ����� � ������ ����� �� �������������.
	char* m_userName;
	char* m_password;
	char* m_email;

	//������������ ����� �� ����� ����������.
	User* m_friendsList;
	unsigned m_numberOfFriends;
	unsigned m_capacityFriends;
	
	//������ � ���������.
	TravelInformation* m_travels;
	unsigned m_countTravels;
	unsigned m_capacityTravels;
	
public:
	//���� �� ���� �� �� ������, �� �� ���� �� �� ������.
	User();
	
	//����������� �� ��������� �� ��� ����������.
	User(char*, char*, char*);

	//�����������, ����� ������������ ������ ������ �� �����.
	User(char*, char*, char*, User*, unsigned, unsigned, TravelInformation*, unsigned, unsigned);

	//����������� �� ��������.
	User(const User&); //�� �� ������ ��� ������� �� ������� � ��������. 
	
	//������������ �� �����������.
	User& operator=(const User&);
	
	//����������.
	~User();

private:

	void copy(const User&);
	void cleanMemory();

	//�� ������� ��������� private, �� �� �� ���� �� �� �������� ������� �� �����������.
	void setName(char*);
	void setPassword(char*);
	void setEmail(char*);


public:
	//void freeMemory(User& );

	//�������� �� ������� �� ����������.
	void setFriendsList(User*);
	void setNumberOfFriends(unsigned);

//	void setTravels(TravelInformation*);
//	void setCountTravels(unsigned);

	//���������.
	char* getUserName() const;
	char* getPassword() const;
	char* getEmail() const;
	unsigned getNumberOfFriends() const;
	unsigned getCapacityOfFriends()const;

	//��������� �� ���������� � ���� ������� � ����������.
	void serializeUsersDatabase(std::ofstream &)const;
	
	//������ �� ���������� �� ���� ������� � �����������.
	void deserializeUsersDatabase(std::ifstream&);

	//��������� � ������� ���� �����.
	void serializePersonalDataBase(std::ofstream&) const;

	//������ �� ������� ���� �����.
	void deserializePersonalDataBase(std::ifstream&);

	void printInformation()const;
};

#endif
