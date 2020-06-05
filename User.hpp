#ifndef __USER_HPP
#define __USER_HPP

#include<fstream>
#include<cstring>
#include"TravelInformation.hpp"

class TravelInformation;

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

	static const unsigned startCapacity = 8;
	static const unsigned MAX = 1024;
	
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
	void setNumberOfTravels(unsigned);

	//��������������� �� ������� � ��������.
	void resizeFriendList();
	void resizeTravelInfo();

public:
	void memoryAllocFriendsList();
	void memoryAllocTravelInfo();

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
	unsigned getNumberOfTravels()const;

	//��������� �� ���������� � ���� ������� � ����������.
	void serializeUsersDatabase(std::ofstream &)const;
	
	//������ �� ���������� �� ���� ������� � �����������.
	void deserializeUsersDatabase(std::ifstream&);

	//��������� � ������� ���� �����.
	void serializePersonalDataBase(std::ofstream&) const;

	//������ �� ������� ���� �����.
	void deserializePersonalDataBase(std::ifstream&);

	//�������� ���� ���������� � ������ ��� � �������.
	bool isFriend(char*);

	//������� ������������ �� �����������.
	void printInformation()const;

	//������� ������������ �� ����������� �� �����������.
	void printTravelInformation()const;

	//��������� ���� ���������� � ������ ��� � �������� �� �����������.
	bool isVisitDestination(char*);

	//�������� ���������� �� ���������� � ������ ���.
	void printDestinationInfoByName(char*)const;

	//������� �������� �� ����������� �� ���������� � ������ ���.
	void prinDestinationEvaluation(char*) const;

	//������� �� �������� �� �������.
	void addFriend(const User &);

	//������� �� ���������� �� �������.
	void removeFriend(const User&);

	//�������� �� ���� ����������.
	void addNewTravel(const TravelInformation&);

};

#endif
