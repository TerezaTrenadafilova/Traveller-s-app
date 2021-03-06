#ifndef __MANAGER_HPP
#define __MANAGER_HPP

#include "User.hpp"
#include "Destination.hpp"

//������ �� ��� ������ � ����������� �� ������������.
class Manager {
private:
	User * m_users;
	unsigned m_numberOfUsers;
	unsigned m_capacityOfUsers;

	//������ � ������ ����������
	Destination* m_destinations;
	unsigned m_numberOfDestinations;
	unsigned m_capacityOfDestinations;

	static unsigned const startCapacity = 8;
	static unsigned const MAX_LEN = 50;

public:
	//���� ��� ������ ����������.
	bool isLoggedIn = false;

	//���� ��� ������� ������� ����.
	bool isSuccessfullyOpen = false;

	//������ ��������
	Manager();
	Manager(User*, unsigned, unsigned, Destination*, unsigned, unsigned);
	Manager(const Manager&) = delete;//���� �� ���� �� ������ ����� �� ���� ������������ ����������.
	Manager& operator=(const Manager&) = delete;
	~Manager();

	std::ifstream* ptrIfs = nullptr;

	void open(char*);
	void closeFile();
	void save();
	void saveas(char*);
	void help()const;

	//�������� �� ����������.
	void login();
	void logout();
	void registrerNewUser();
	void exit();

	//��������� �� ������ ����������� �� ����������.
	void printUser()const;

	//��������� �� ������ ���������� � ����������.
	void printDestinations()const;

	//�������� ���������� ��������� ���� ����� ������� � ������� ������ ����������.
	void checkFriendDestination(char* friendName, char* destinationName);

	//��������� �� ������ ����������, ����� � ������� ������� �� ������� ����������.
	void allDesinationOfFriend(char* friendName);

	//�������� �� ������ ����������.
	void checkDestination(char*);

	//�������� �� ������� �� �������� ���.
	void  addNewFriend( char*);

	//���������� �� ������� �� �������� ���.
	void removeFriend(char*);

	//�������� �� ����������.
	void addDestination(const TravelInformation&);

	//������� �� ����������� �� ������� ����������.
	void viewLoggedInUserTravels()const;

	//���������� �� ����������.
	void runProgram();


private:
	const int defaultPos = -1;

	//����������, ����� �� ���� ����� �� �����, ����� � ��� �������� �������.
	char* m_nameFile = nullptr;
	void setM_NameFile(char*);

	//����������, ����� ���� ����� �� ��������� ������ ����������.
	char* nameLastLoggedUser = nullptr;
	void setNameLastLoggedUser(char*);

	//����������, ����� ���� ��������� � ������� � �������������, �� ������� ����������.
	int posLoggedUser = defaultPos;
	

	void cleanMemory();
	void resizeUserList();
	void resizeDestinationList();

	//�������, ����� ��������� ���� ����������� � ������ ��� � ������ ����������.
	bool isUserExist(char*, char*);

	//�������, ����� ����� ��������� �� ���������� � ������ ��� � ������.
	int posOfUser(char*, char*);

	//�������, ����� ����� ��������� �� ���������� � ������ ���.
	//������ �� �� ��������� checkFriendDestination(char* friendName, char* destinationName);
	int posOfUserByName(char*);

	//�������, ����� ��������� ���� ������ ������������� ��� �� � �����.
	bool isUsed(char*);

	//������, ����� ��������� ���� ����� �� ���������� ������ � ������� ��� ��.
	bool isValidPhoto(char*);


};

#endif






//void setUsers(User* users);
	//void setNumberOfUsers(unsigned);
	//void setCapacityOfUsers(unsigned);
	//void setDestination(Destination*);
	//void setNumberOfDestinations(unsigned);
	//void setCapacityOfDestinations(unsigned);