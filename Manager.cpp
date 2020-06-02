#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include"Manager.hpp"

//unsigned startCapacity = 8;

//unsigned const MAX_LEN_COMMAND = 11;
unsigned const MAX_LEN = 50;

//Разширението на файла с личната база данни.
const char* extDataBase = ".db";

Manager::Manager()
	:m_users(nullptr)
	, m_numberOfUsers(0)
	, m_capacityOfUsers(startCapacity)
	, m_destinations(nullptr)
	, m_numberOfDestinations(0)
	, m_capacityOfDestinations(startCapacity)
{
	// Заделяне на памет за потребителите на приложението.
		m_users = new(std::nothrow) User[m_capacityOfUsers];
	if (m_users == nullptr) {
		std::cout << "Not enought memory for users in Manager class. Error!" << std::endl;
		return;
	}

	//Заделяна не памет за всички дестниации, които са посетили потребителите.
	m_destinations = new(std::nothrow) Destination[m_capacityOfDestinations];
	if (m_destinations == nullptr) {
		std::cout << "Not enought memory for destinations in Manager class. Error!" << std::endl;
		return;
	}

}

Manager::Manager(User * users, unsigned numberOfUsers, unsigned capacityOfUsers, Destination * destinations, unsigned numberOfDestinations, unsigned capacityOfDestinations)
	:m_users(nullptr)
	, m_numberOfUsers(numberOfUsers)
	, m_capacityOfUsers(capacityOfUsers)
	,m_destinations(nullptr)
	,m_numberOfDestinations(numberOfDestinations)
	,m_capacityOfDestinations(capacityOfDestinations)
{
	//Заделяна на памет за потребителите.
	m_users = new(std::nothrow) User[m_capacityOfUsers];
	if (m_users == nullptr) {
		std::cout << "Not enought memory for users in Manager class. Error!" << std::endl;
		return;
	}

	for (int i = 0; i < m_numberOfUsers; ++i) {
		m_users[i] = users[i];
	}


	//Заделяне на памет за всички дестинации, които са посетени от потребителите на приложението.
	m_destinations = new(std::nothrow) Destination[m_capacityOfDestinations];
	if (m_destinations == nullptr) {
		std::cout << "Not enought memory for destinations in Manager class. Error!" << std::endl;
		return;
	}

	for (int i = 0; i < m_numberOfDestinations; ++i) {
		m_destinations[i] = destinations[i];
	}
}

Manager::~Manager()
{
	cleanMemory();
}

void Manager::open(char * fileName) 
{
	//Може да се отварят само база данните за потребителите и дестниациите на приложението.
	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}

	ptrIfs = &ifs;

	//Ако трябва да се отвори база данните с потребителите на приложението.
	if (strcmp(fileName, "User.db") == 0) {
		/*m_nameFile = new(std::nothrow) char[strlen(fileName) + 1];
		if (m_nameFile == nullptr) {
			std::cout << "Not enought memory fo m_nameFile in open(). Error!" << std::endl << std::endl;
			return;
		}
		strcpy(m_nameFile, fileName);*/
		setM_NameFile(fileName);

		ifs.read((char*)&m_numberOfUsers, sizeof(m_numberOfUsers));
		ifs.read((char*)&m_capacityOfUsers, sizeof(m_capacityOfUsers));

		m_users = new(std::nothrow) User[m_capacityOfUsers];
		if (m_users == nullptr) {
			std::cout << "Not enought  memory for users in open(). Error!" << std::endl << std::endl;
			return;
		}
		for (int i = 0; i < m_numberOfUsers; ++i) {
			m_users[i].deserializeUsersDatabase(ifs);
			m_users[i].memoryAllocFriendsList();
			m_users[i].memoryAllocTravelInfo();
		}

		std::cout << "open: " << std::endl;
		std::cout << m_numberOfUsers << ", " << m_capacityOfUsers << std::endl;

		for (int i = 0; i < m_numberOfUsers; ++i) {
			std::cout << m_users[i].getUserName() << ", " << m_users[i].getPassword() << ", " << m_users[i].getEmail() << std::endl;
		}

		/*if (ifs.good()) {
			std::cout << "Successfully opened " << fileName << std::endl << std::endl;
			printUser();
		}
		else {
			std::cout << fileName << " is not open." << std::endl << std::endl;
		}
		ifs.*/
	}
	if (strcmp(fileName, "Destinations.db") == 0) {
		
		setM_NameFile(fileName);

		ifs.read((char*)& m_numberOfDestinations, sizeof(m_numberOfDestinations));
		ifs.read((char*)& m_capacityOfDestinations, sizeof(m_capacityOfDestinations));

		m_destinations = new(std::nothrow) Destination[m_capacityOfDestinations];
		if (m_destinations == nullptr) {
			std::cout << "Not enought memorty for destinations in open(). Error!" << std::endl << std::endl;
			return;
		}
		for (int i = 0; i < m_numberOfDestinations; ++i) {
			m_destinations[i].deserialize(ifs);
		}
	}

	if (ifs.good()) {
		std::cout << std::endl << "Successfully opened file " << fileName << std::endl << std::endl;
		isSuccessfullyOpen = true;
	}
	else {
		std::cout << "File is not readen." << std::endl;
	}

	ifs.close();
}

void Manager::closeFile()
{
	if (ptrIfs == nullptr) {
		std::cout << std::endl << "Unvalid operation!" << std::endl << std::endl;
		return;
	}

	cleanMemory();
	isSuccessfullyOpen = false;
	m_nameFile = nullptr;
	m_numberOfUsers = 0;//Текущият брой на потребителите се нулира.
	std::cout << std::endl << "Successfully closed file." << std::endl << std::endl;
}

void Manager::save()
{
	std::ofstream ofs(m_nameFile, std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << std::endl << "The file is not saved." << std::endl << std::endl;
		return;
	}

	//За потребителите
	if (strcmp(m_nameFile, "User.db") == 0) {
		ofs.write((const char*)& m_numberOfUsers, sizeof(m_numberOfUsers));
		ofs.write((const char*)& m_capacityOfUsers, sizeof(m_capacityOfUsers));

		for (int i = 0; i < m_numberOfUsers; ++i) {
			m_users[i].serializeUsersDatabase(ofs);
		}
	}

	//За дестинациите
	if (strcmp(m_nameFile, "Destinations.db") == 0) {
		ofs.write((const char*)& m_numberOfDestinations, sizeof(m_numberOfDestinations));
		ofs.write((const char*)& m_capacityOfDestinations, sizeof(m_capacityOfDestinations));

		for (int i = 0; i < m_numberOfDestinations; ++i) {
			m_destinations[i].serialize(ofs);
		}
	}
	/*else {
		//За личната база данни
		m_users[posLoggedUser].serializePersonalDataBase(ofs);
	}*/

	if (ofs.good()) {
		std::cout << std::endl << "Successfully saved " << m_nameFile << std::endl << std::endl;
	}
	else {
		std::cout << std::endl << "Save has failed. " << std::endl << std::endl;
	}
	ofs.close();
}

void Manager::saveas(char * newFileName) 
{
	std::ofstream ofs(newFileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		std::cout << "File is not open! Error";
		return;
	}

	//Ако сме отворили и работили последно с потребителите на приложението.
	if (strcmp(m_nameFile, "User.db") ==0 ) {
		ofs.write((const char*)& m_numberOfUsers, sizeof(m_numberOfUsers));
		ofs.write((const char*)& m_capacityOfUsers, sizeof(m_capacityOfUsers));

		for (int i = 0; i < m_numberOfUsers; ++i) {
			m_users[i].serializeUsersDatabase(ofs);
		}
	}

	//Ако сме отворили и работили последно с дестинациите на приложението.
	if (strcmp(m_nameFile, "Destinations.db") == 0) {
		ofs.write((const char*)& m_numberOfDestinations, sizeof(m_numberOfDestinations));
		ofs.write((const char*)& m_capacityOfDestinations, sizeof(m_capacityOfDestinations));

		for (int i = 0; i < m_numberOfDestinations; ++i) {
			m_destinations[i].serialize(ofs);
		}
	}

	

	if (ofs.good()) {
		std::cout << std::endl << "Successfully saved another file " << newFileName << std::endl;
	}
	else {
		std::cout << std::endl << "Unsuccessfully saved another file " << newFileName << std::endl;
	}

	ofs.close();
}

void Manager::setM_NameFile(char *name)
{
	m_nameFile = new(std::nothrow) char[strlen(name) + 1];
	if (m_nameFile == nullptr) {
		std::cout << "Not enought memory fo m_nameFile. Error!" << std::endl << std::endl;
		return;
	}
	strcpy(m_nameFile, name);
}

void Manager::setNameLastLoggedUser(char * name)
{
	if (nameLastLoggedUser != nullptr) {
		delete[]nameLastLoggedUser;
		nameLastLoggedUser = nullptr;
	}

	nameLastLoggedUser = new(std::nothrow) char[strlen(name) + 1];
	if (nameLastLoggedUser == nullptr) {
		std::cout << "Not enought memory for set nameLastLoggedUser. Error!" << std::endl << std::endl;
		return;
	}
	strcpy(nameLastLoggedUser, name);
}

void Manager::cleanMemory()
{
	delete[] m_users;
	m_users = nullptr;

	delete[] m_destinations;
	m_destinations = nullptr;

	delete[] m_nameFile;
	m_nameFile = nullptr;
	
	delete[] nameLastLoggedUser;
	nameLastLoggedUser = nullptr;
}

void Manager::resizeUserList()
{
	unsigned newCapacity = m_capacityOfUsers * 2;
	User* newUsers = new (std::nothrow) User[newCapacity];

	if (newUsers == nullptr) {
		std::cout << "Not enought memory for resize! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacityOfUsers; ++i) {
		newUsers[i] = m_users[i];
	}
	m_capacityOfUsers = newCapacity;
	delete[] m_users;
	m_users = newUsers;
}

void Manager::resizeDestinationList()
{
	unsigned newCapacity = m_capacityOfDestinations * 2;
	Destination* newDest = new (std::nothrow) Destination[newCapacity];

	if (newDest == nullptr) {
		std::cout << "Not enought memory for resize destinations list! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacityOfDestinations; ++i) {
		newDest[i] = m_destinations[i];
	}
	m_capacityOfDestinations = newCapacity;
	delete[] m_destinations;
	m_destinations = newDest;
}

bool Manager::isUserExist(char * userName, char * password)
{
	for (int i = 0; i < m_numberOfUsers; ++i) {
		if (strcmp(m_users[i].getUserName(), userName) == 0 && strcmp(m_users[i].getPassword(), password) == 0) {
			return true;
		}
	}
	return false;
}

int Manager::posOfUser(char *username, char * password)
{
	int pos = -1;
	for (int i = 0; i < m_numberOfUsers; ++i) {
		if (strcmp(m_users[i].getUserName(), username) == 0 && strcmp(m_users[i].getPassword(), password) == 0) {
			pos = i;
			break;
		}
	}
	return pos;
}

int Manager::posOfUserByName(char *username)
{
	int pos = -1;
	for (int i = 0; i < m_numberOfUsers; ++i) {
		if (strcmp(m_users[i].getUserName(), username) == 0) {
			pos = i;
			break;
		}
	}
	return pos;
}

bool Manager::isUsed(char *name)
{
	for (int i = 0; i < m_numberOfUsers; ++i) {
		if (strcmp(m_users[i].getUserName(), name) == 0 ) {
			return true;
		}
	}
	return false;
}

void Manager::help() const
{
	std::cout << "The following commands are supported:" << std::endl
		<< "open<file> " << '\t' << "opens<file>";
	std::cout << "close" << '\t' << "close currently opened file" << std::endl
		<< "save" << '\t' << "saves the currently opened file" << std::endl
		<< "saveas<file>" << '\t' << "saves the currently open file in <file>" << std::endl
		<< "help" << '\t' << "prints this information" << std::endl
		<< "exit" << '\t' << "exit the program" << std::endl;
}

void Manager::login()
{
	//Ако няма вписан потребител
	if (isLoggedIn == false) {
		char name[MAX_LEN];
		char password[MAX_LEN];
		//char email[MAX_LEN];

		std::cout << "Username: ";
		std::cin.getline(name, MAX_LEN);

		std::cout << "Password: ";
		std::cin.getline(password, MAX_LEN);

		/*std::cout << "Email: ";
		std::cin.getline(email, MAX_LEN);*/

		//std::ifstream ifs("User.db", std::ios::in | std::ios::binary);
		//if (!ifs.is_open()) {
		//	std::cout << "File is not open in login. Error." << std::endl;
		//	return;
		//}
		//unsigned count = 0;
		//
		////Прочитане на всички потретбители на приложението.
		//ifs.read((char*)& count, sizeof(count));
		//User *usersList = new(std::nothrow) User[count];
		//if (usersList == nullptr) {
		//	std::cout << "Error!" << std::endl;
		//	return;
		//}

		//for (int i = 0; i < count; ++i) {
		//	usersList[i].deserializeUsersDatabase(ifs);
		//}

		//ifs.close();

		//for (int i = 0; i < count; ++i) {
		//	//Търсене дали съществува такъв потребител.
		//	if (strcmp(usersList[i].getUserName(), name) == 0 && strcmp(usersList[i].getPassword(), password) == 0 )
		//	{
		//		isLoggedIn = true;
		//		std::cout << "Welcome " << name << " !" << std::endl;
		//		
		//		char* userDataBase = new(std::nothrow)char[strlen(name) + strlen(extDataBase) + 1];
		//		if (userDataBase == nullptr) {
		//			std::cout << std::endl << "Not enought memory for userDataBase in login(). Error!" << std::endl;
		//			return;
		//		}
		//		strcpy(userDataBase, name);
		//		strcat(userDataBase, extDataBase);
		//		std::cout << " user data base is: " << userDataBase << std::endl;

		//		//Отваряне на личната база данни на потребителя. Тя ще бъде празна, защото потребителят е нов.
		//		ifs.open(userDataBase, std::ios::binary | std::ios::in);
		//		if (!ifs.is_open()) {
		//			std::cout << userDataBase << " is not opened. Error!" << std::endl << std::endl;
		//		}

		//		//Прочитане на личната база данни на потребителя.
		//		usersList[i].deserializePersonalDataBase(ifs);
		//		ifs.close();

		//	}
		//}

		if (isUserExist(name, password) == true) {
			isLoggedIn = true;
			 posLoggedUser = posOfUser(name, password);

			std::cout <<std::endl<< "Welcome " << name << " !" << std::endl<<std::endl;
					
			char* userDataBase = new(std::nothrow)char[strlen(name) + strlen(extDataBase) + 1];
			if (userDataBase == nullptr) {
				std::cout << std::endl << "Not enought memory for userDataBase in login(). Error!" << std::endl;
				return;
			}
			strcpy(userDataBase, name);
			strcat(userDataBase, extDataBase);
			std::cout << " user data base is: " << userDataBase << std::endl;

			//Отваряне на личната база данни на потребителя. Тя ще бъде празна, защото потребителят е нов.
			std::ifstream ifs;
			
			ifs.open(userDataBase, std::ios::binary | std::ios::in|std::ios::app);
			if (!ifs.is_open()) {
				std::cout << userDataBase << " is not opened. Error!" << std::endl << std::endl;
			}

			//Проверка дали личната база данни не е прадзна.
			ifs.seekg(0, std::ios::end);
			if (ifs.tellg()) {
				//Прочитане на личната база данни на потребителя.
				m_users[posLoggedUser].deserializePersonalDataBase(ifs);
				ifs.close();
			}
			else {
				std::cout << "Private database is empty." << std::endl << std::endl;
				std::cout << "Pos logged user: " << posLoggedUser << std::endl
					<< m_users[posLoggedUser].getNumberOfFriends() << ", " << m_users[posLoggedUser].getNumberOfTravels() << std::endl;
			}

			//Работа с m_nameFile
			setM_NameFile(userDataBase);

			//Променяне на името на последния влязъл потребител.
			setNameLastLoggedUser(name);
			
		}
		if (isLoggedIn == false) {
			std::cout << "Uncorrect username/password." << std::endl;
		}
	}
	else {
		std::cout << "You are already logged in!" << std::endl;
	}
}

void Manager::logout()
{
	if (isLoggedIn == true) {
		isLoggedIn = false;
		posLoggedUser = defaultPos;
	}
	else {
		std::cout << "No user logged in." << std::endl;
	}
}

void Manager::registrerNewUser()
{
	char name[MAX_LEN];
	char password[MAX_LEN];
	char email[MAX_LEN];

	std::cout << "Username: ";
	std::cin.getline(name, MAX_LEN);

	std::cout << "Password: ";
	std::cin.getline(password, MAX_LEN);

	std::cout << "Email: ";
	std::cin.getline(email, MAX_LEN);

	if (isUsed(name)) {
		std::cout << std::endl << "The name " << name << " is already in use. Please try another name." << std::endl << std::endl;
		return;
	}

	//Добавяне на новия потребител.
	User newUser(name, password, email);
	if (m_numberOfUsers >= m_capacityOfUsers) {
		resizeUserList();
	}
	m_users[m_numberOfUsers] = newUser;
	++m_numberOfUsers;

	char* userDataBase = new(std::nothrow) char[strlen(name) + strlen(extDataBase) + 1];
	if (userDataBase == nullptr) {
		std::cout << "Not enought memory for userDataBase in registrerNewUser(). Error!" << std::endl;
		return;
	}
	strcpy(userDataBase, name);
	strcat(userDataBase, extDataBase);
	std::cout << "User data base is: " << userDataBase << std::endl;

	//Личната база данни се отваря, когато потребетелят се впише (в login()).
	/*std::ifstream ifs(userDataBase, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) {
		std::cout << userDataBase << " is not open. Error!" << std::endl << std::endl;
		return;
	}

	setM_NameFile(userDataBase);*/

}

void Manager::exit()
{
	std::cout << "Exit the program." << std::endl;
}

void Manager::printUser() const
{
	
	if (m_numberOfUsers == 0) {
		std::cout << "There are no registered users." << std::endl << std::endl;
		return;
	}
	std::cout << std::endl << "Users in traveller's app: " << std::endl;
	for (int i = 0; i < m_numberOfUsers; ++i) {
		std::cout << m_users[i].getUserName() << ", " << m_users[i].getEmail()<<std::endl;
	}
	std::cout << std::endl;
}

void Manager::printDestinations() const
{
	std::cout << std::endl << "Destinations in app: " << std::endl;
	for (int i = 0; i < m_numberOfDestinations; ++i) {
		std::cout << m_destinations[i].getDestination() << std::endl;
	}
	std::cout << std::endl;
}

void Manager::checkFriendDestination(char * friendName, char * destinationName)
{
	//Проверка дали първо потребител с име friendName съществува.
	if (isUsed(friendName) == true) {
		std::cout << std::endl << "Check if " << friendName << " has visited " << destinationName << "." << std::endl;

		//Проверка дали първо потребител с име friendName e приятел на влезлият потребител.
		if (m_users[posLoggedUser].isFriend(friendName) == true) {
			
			//Намиране на позицията на приятеля в списъка с потребители на приложението.
			int pos = posOfUserByName(friendName);

			////Извеждане на информацията за всички пътуания на потребителя.
			//std::cout << std::endl << friendName << " travels information: " << std::endl;
			//m_users[pos].printTravelInformation();

			//Проверка дали потребителя е посетил дестинацията.
			if (m_users[pos].isVisitDestination(destinationName) == true) {
				m_users[pos].printDestinationInfoByName(destinationName);
				std::cout << std::endl;
			}
			else {
				std::cout << std::endl << friendName << " has no visited " << destinationName << "."
					<< "The destinations that " << friendName << " has visited is: " << std::endl;
				m_users[pos].printTravelInformation();
				std::cout << std::endl;
			}
		}
		else {
			std::cout << std::endl <<friendName <<" is not your friend." << std::endl << std::endl;
		}
	}
	else {
		std::cout <<std::endl<< friendName << " is not exist. Please, try again." << std::endl << std::endl;
	}
}

void Manager::allDesinationOfFriend(char * friendName)
{
	//Проверка дали първо потребител с име friendName съществува.
	if (isUsed(friendName) == true) {
		//Проверка дали първо потребител с име friendName e приятел на влезлият потребител.
		if (m_users[posLoggedUser].isFriend(friendName) == true) {

			//Намиране на позицията на приятеля в списъка с потребители на приложението.
			int pos = posOfUserByName(friendName);

			//Извеждане на информацията за всички пътуания на потребителя.
			std::cout << std::endl << friendName << " travels information: " << std::endl;
			m_users[pos].printTravelInformation();
			std::cout << std::endl;

		}
		else {
			std::cout << std::endl << friendName << " is not your friend." << std::endl << std::endl;
		}
	}
	else {
		std::cout << std::endl << friendName << " is not exist. Please, try again." << std::endl << std::endl;
	}
}

void Manager::checkDestination(char * dest)
{
	int pos = -1;
	for (int i = 0; i < m_numberOfDestinations; ++i) {
		if (strcmp(dest, m_destinations[i].getDestination()) == 0) {
			pos = i;
			break;
		}
	}

	//Проверка дали такава дестинация съществува.
	if (pos == -1) {
		std::cout << std::endl << "No one has visited " << dest << "." << std::endl << std::endl;
		return;
	}

	m_destinations[pos].printUserWhoVisitedDestination();
}

void Manager::addNewFriend(/*const User & newFriend*/char* nameFriend)
{	
	if (isUsed(nameFriend) == true) {
		//Проверка дали името не е на текущо влезлият потребител.
		if (strcmp(nameFriend, m_users[posLoggedUser].getUserName()) == 0) {
			std::cout << std::endl << "Impossible operation. The name you entered matches your own." << std::endl << std::endl;
			return;
		}
		//Намиране на позицията на проителя с даденото име.
		unsigned posFriend = posOfUserByName(nameFriend);
		
		User friendUser=m_users[posFriend];
		std::cout << friendUser.getUserName() << ", " << friendUser.getEmail() << std::endl;

		//На потребителя, който е влязъл се добавя нов приятел.
		m_users[posLoggedUser].addFriend(friendUser);

		//Приятелството е симетрична релация.
		m_users[posFriend].addFriend(m_users[posLoggedUser]);

		std::cout << std::endl << "You are friends with " << friendUser.getUserName() << "." << std::endl << std::endl;
	}
	else {
		std::cout << nameFriend<< " is not exist." << std::endl << std::endl;
	}
}

void Manager::removeFriend(/*const User & adversary*/char*  nameFriend)
{
	if (isUsed(nameFriend) == true) {
		//Намиране на позицията на проителя с даденото име.
		unsigned posFriend = posOfUserByName(nameFriend);

		//На потребителя, който е влязъл се премахва приятел.
		m_users[posLoggedUser].removeFriend(m_users[posFriend]);
		m_users[posFriend].removeFriend(m_users[posLoggedUser]);//Защото приятелството е симетрична релация.

		std::cout << std::endl << "You bloked " << m_users[posFriend].getUserName() << ". You are no longer friends." << std::endl << std::endl;
	}
	else {
		std::cout << nameFriend << " is not exist." << std::endl << std::endl;
	}
}

void Manager::addDestination(const TravelInformation & newTravel)
{
	m_users[posLoggedUser].addNewTravel(newTravel);
	std::cout << std::endl << "You added new travel. " << std::endl << std::endl;

	for (int i = 0; i < m_numberOfDestinations; ++i) {
		if (strcmp(newTravel.getDestination(), m_destinations[i].getDestination()) == 0) {
			//Увеличавене броя на посещениеята с 1.
			unsigned numberVisit = m_destinations[i].getNumberOfVisits() + 1;
			m_destinations[i].setNumberOfVisits(numberVisit);
	
			//Промяна на сумата от всички оценки на дестинацията.
			unsigned sumAll = m_destinations[i].getSumOfALL() + newTravel.getEvaluation();
			m_destinations[i].setSumOfAll(sumAll);

			return;
		}
	}

	if (m_numberOfDestinations >= m_capacityOfDestinations) {
		resizeDestinationList();
	}
	char* name = new(std::nothrow) char[strlen(newTravel.getDestination()) + 1];
	if (name == nullptr) {
		std::cout << "Error in addDestination() in Manager class." << std::endl << std::endl;
		return;
	}
	strcpy(name, newTravel.getDestination());
	
	unsigned countVisit = 1; //тоест само посещението на потребителя

	Destination newDest(name, countVisit);
	newDest.addUser(m_users[posLoggedUser]);
	newDest.setSumOfAll(newTravel.getEvaluation());

	m_destinations[m_numberOfDestinations] = newDest;
	++m_numberOfDestinations;
}

void Manager::runProgram()
{
	const unsigned MAX_COMMAND = 35;
	char command[MAX_COMMAND];

	for (;;) {
		std::cout << "Command: ";
		std::cin.getline(command, MAX_COMMAND);

		//Отваряне на нов файл.
		if (strcmp(command, "open") == 0) {
			char fileName[MAX_LEN * 10];//Умножавам по 10, защото е възможно да има по-дълго име на файл с над 50 елемента.
			std::cin.getline(fileName, MAX_LEN * 10);

			open(fileName);

		}

		//Затваряне на файл.
		if (strcmp(command, "close") == 0) {
			closeFile();
		}

		//Запазване на текущо отворения файл.
		if (strcmp(command, "save") == 0) {
			save();
		}

		//Запазване в нов файл.
		if (strcmp(command, "saveas") == 0) {
			char fileName[MAX_LEN * 10];
			std::cin.getline(fileName, MAX_LEN * 10);

			saveas(fileName);
		}

		//Помощ.
		if (strcmp(command, "help") == 0) {
			help();
		}

		//Вписване на потребител.
		if (strcmp(command, "log in") == 0) {
			login();
		}

		//Отписване на потребител.
		if (strcmp(command, "log out") == 0) {
			logout();
		}

		//Регистриране на нов потребител.
		if (strcmp(command, "registration") == 0) {
			registrerNewUser();
		}

		//Изход.
		if (strcmp(command, "exit") == 0) {
			exit();
			break;
		}

		//Извеждане на всички потребители.
		if (strcmp(command, "print users") == 0) {
			printUser();
		}

		//Изваеждане на всички дестинации.
		if (strcmp(command, "print destinations") == 0) {
			printDestinations();
		}

		//Проверка дали приятел е посетил дадена дестниация.
		if (strcmp(command, "check friend destination") == 0) {
			char nameFriend[MAX_LEN];
			char nameDestination[MAX_LEN];

			std::cout << "Friend's name: ";
			std::cin.getline(nameFriend, MAX_LEN);

			std::cout << "Destination: ";
			std::cin.getline(nameDestination, MAX_LEN);

			checkFriendDestination(nameFriend, nameDestination);
		}

		//Извеждане на всички дестинации, които е посетил приятел.
		if (strcmp(command, "print all freind's destinations") == 0) {
			char nameFriend[MAX_LEN];
			
			std::cout << "Friend's name: ";
			std::cin.getline(nameFriend, MAX_LEN);

			allDesinationOfFriend(nameFriend);
		}

		//Проверка за дадена дестинация.
		if (strcmp(command, "check destination") == 0) {
			char nameDestination[MAX_LEN];

			std::cout << "Destination: ";
			std::cin.getline(nameDestination, MAX_LEN);

			checkDestination(nameDestination);
		}

		//Добавяне на приятел.
		if (strcmp(command, "add friend") == 0) {
			char nameFriend[MAX_LEN];

			std::cout << "Friend's name: ";
			std::cin.getline(nameFriend, MAX_LEN);

			addNewFriend(nameFriend);
		}

		//Премахване на приятел.
		if (strcmp(command, "block friend") == 0) {
			char nameFriend[MAX_LEN];

			std::cout << "Friend's name: ";
			std::cin.getline(nameFriend, MAX_LEN);

			removeFriend(nameFriend);
		}

		if(m_nameFile!= nullptr)
			std::cout << std::endl << "Last opened file name: " << m_nameFile << std::endl << std::endl;

		//Добавяне на дестинация.
	}
}
