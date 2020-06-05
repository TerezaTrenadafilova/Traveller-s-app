#ifndef __MANAGER_HPP
#define __MANAGER_HPP

#include "User.hpp"
#include "Destination.hpp"

//Класът ще има списък с потребители на приложението.
class Manager {
private:
	User * m_users;
	unsigned m_numberOfUsers;
	unsigned m_capacityOfUsers;

	//Списък с всички дестинации
	Destination* m_destinations;
	unsigned m_numberOfDestinations;
	unsigned m_capacityOfDestinations;

	static unsigned const startCapacity = 8;
	static unsigned const MAX_LEN = 50;

public:
	//Дали има вписан потребител.
	bool isLoggedIn = false;

	//Дали има успешно отворен файл.
	bool isSuccessfullyOpen = false;

	//Голяма четворка
	Manager();
	Manager(User*, unsigned, unsigned, Destination*, unsigned, unsigned);
	Manager(const Manager&) = delete;//Няма да може да правим копие на вече съществуващо приложение.
	Manager& operator=(const Manager&) = delete;
	~Manager();

	std::ifstream* ptrIfs = nullptr;

	void open(char*);
	void closeFile();
	void save();
	void saveas(char*);
	void help()const;

	//Вписване на потребител.
	void login();
	void logout();
	void registrerNewUser();
	void exit();

	//Извеждане на всички потребители на програмата.
	void printUser()const;

	//Извеждане на всички дестинации в програмата.
	void printDestinations()const;

	//Влезлият потребител проверява дали негов приятел е посетил дадена дестинация.
	void checkFriendDestination(char* friendName, char* destinationName);

	//Извеждане на всички дестинации, които е посетил приятел на влезлия потербител.
	void allDesinationOfFriend(char* friendName);

	//Проверка за дадена дестинация.
	void checkDestination(char*);

	//Добавяне на приятел по въведено име.
	void  addNewFriend( char*);

	//Премахване на приятел по въведено име.
	void removeFriend(char*);

	//Добавяне на дестинация.
	void addDestination(const TravelInformation&);

	//Преглед на пътуванията на влезлия потребител.
	void viewLoggedInUserTravels()const;

	//Стратиране на програмата.
	void runProgram();


private:
	const int defaultPos = -1;

	//Променлива, която ще пази името на файла, който е бил последно отворен.
	char* m_nameFile = nullptr;
	void setM_NameFile(char*);

	//Променлива, която пази името на последния влязъл потребител.
	char* nameLastLoggedUser = nullptr;
	void setNameLastLoggedUser(char*);

	//Променлива, която пази позицията в списъка с потребителите, на влезлия потребител.
	int posLoggedUser = defaultPos;
	

	void cleanMemory();
	void resizeUserList();
	void resizeDestinationList();

	//Функция, която проверява дали потеребител с дадено име и парола съществува.
	bool isUserExist(char*, char*);

	//Функция, която връща позицията на потребител с дадени име и парола.
	int posOfUser(char*, char*);

	//Функция, която връща позицията на потребител с дадено име.
	//Трябва ми за функцията checkFriendDestination(char* friendName, char* destinationName);
	int posOfUserByName(char*);

	//Функция, която проверавя дали дадено потребителско име не е заето.
	bool isUsed(char*);

	//Фукция, която проверява дали името на въведената снимка е валидно или не.
	bool isValidPhoto(char*);


};

#endif






//void setUsers(User* users);
	//void setNumberOfUsers(unsigned);
	//void setCapacityOfUsers(unsigned);
	//void setDestination(Destination*);
	//void setNumberOfDestinations(unsigned);
	//void setCapacityOfDestinations(unsigned);