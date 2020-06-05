#pragma warning(disable:4996)
#include "User.hpp"
#include <iostream>
//#include <fstream>

//const unsigned MAX = 1024;

User::User()
	:m_userName(nullptr), m_password(nullptr),m_email(nullptr)
	, m_friendsList(nullptr),m_numberOfFriends(0),m_capacityFriends(startCapacity)
	,m_travels(nullptr), m_countTravels(0), m_capacityTravels(startCapacity)
{
	/*m_friendsList = new(std::nothrow) User[m_capacityFriends];
	if (m_friendsList == nullptr) {
		std::cout << "Not enought memory for friendsList in User(). Error!" << std::endl;
		return;
	}*/

	//m_travels = new(std::nothrow) TravelInformation[m_capacityTravels];
	//if (m_travels == nullptr) {
	//	std::cout << "Not enought memory for travels in User(). Error!" << std::endl;
	//	return;
	//}

	
}

User::User(char *name , char *password, char *email)
	:m_userName(nullptr), m_password(nullptr), m_email(nullptr)
	,m_friendsList(nullptr), m_numberOfFriends(0), m_capacityFriends(startCapacity)
	,m_travels(nullptr), m_countTravels(0), m_capacityTravels(startCapacity)
{
	setName(name);
	setPassword(password);
	setEmail(email);
	
	memoryAllocFriendsList();
	memoryAllocTravelInfo();
}

User::User(char * name, char *password, char *email
	, User * friends, unsigned numberFriends, unsigned capacity
	, TravelInformation* travels, unsigned countTravels, unsigned capacityTravels)
	:m_userName(nullptr), m_password(nullptr), m_email(nullptr)
	 ,m_friendsList(nullptr), m_numberOfFriends(numberFriends), m_capacityFriends(capacity)
	 ,m_travels(nullptr), m_countTravels(countTravels), m_capacityTravels(capacityTravels)
{
	setName(name);
	setPassword(password);
	setEmail(email);
	//setFriendsList(friends);

	/*m_friendsList = new(std::nothrow) User[capacity];
	if (m_friendsList == nullptr) {
		std::cout << "Not enought memory for friendsList in void User:: copy(...). Error!" << std::endl << std::endl;
		return;
	}*/
	memoryAllocFriendsList();
	for (int i = 0; i < m_numberOfFriends; ++i) {
		m_friendsList[i] = friends[i];
	}
	
	/*m_travels = new(std::nothrow) TravelInformation[capacityTravels];
	if (m_travels == nullptr) {
		std::cout << "Not enought memory for travels. " << std::endl;
		return;
	}*/
	memoryAllocTravelInfo();
	for (int i = 0; i < countTravels; ++i) {
		m_travels[i] = travels[i];
	}
}

User::User(const User & other)
{
	if (this != &other) {
		copy(other);
	}
	
}

User & User::operator=(const User & other)
{
	if (this != &other) {
		cleanMemory();
		copy(other);
	}
	return *this;
}

User::~User()
{
	cleanMemory();
}

void User::copy(const User & other)
{
	setName(other.m_userName);
	setPassword(other.m_password);
	setEmail(other.m_email);
	m_capacityFriends = other.m_capacityFriends;
	m_numberOfFriends = other.m_numberOfFriends;

	if (m_friendsList != nullptr) {
		delete[]m_friendsList;
		m_friendsList = nullptr;
	}

	/*m_friendsList = new(std::nothrow) User[other.m_capacityFriends];
	if (m_friendsList == nullptr) {
		std::cout << "Not enought memory for friendsList in void User:: copy(...). Error!" << std::endl << std::endl;
		return;
	}*/
	memoryAllocFriendsList();

	for (int i = 0; i < m_numberOfFriends; ++i) {
		m_friendsList[i] = other.m_friendsList[i];
	}

	if (m_travels != nullptr) {
		delete[] m_travels;
		m_travels = nullptr;
	}
	m_countTravels = other.m_countTravels;
	m_capacityTravels = other.m_capacityTravels;

	/*m_travels = new(std::nothrow) TravelInformation[other.m_capacityTravels];
	if (m_travels == nullptr) {
		std::cout << "Not enought memory in user's copy method." << std::endl;
		return;
	}*/
	memoryAllocTravelInfo();
	
	for (int i = 0; i < other.m_countTravels; ++i) {
		m_travels[i] = other.m_travels[i];
	}
	
}

void User::cleanMemory()
{
	if (this != nullptr) {//Хвърля изключение, че this e nullptr. За това правя тази проверка. (add friend, когато приятелат е прочетен от файла)
		delete[] m_userName;
		m_userName = nullptr;

		delete[] m_password;
		m_password = nullptr;

		delete[] m_email;
		m_email = nullptr;

		delete[] m_friendsList;
		m_friendsList = nullptr;

		delete[] m_travels;
		m_travels = nullptr;
	}
	
	
		

	/*
	if (m_email != nullptr) {
		
	}
	
	if (m_friendsList != nullptr) {
		
	}
	
	if (m_travels != nullptr) {
		
	}*/
 }

void User::setName(char *name)
{
	if (m_userName != nullptr) {
		delete[]m_userName;
		m_userName = nullptr;
	}
	m_userName = new(std::nothrow) char[strlen(name) + 1];
	if (m_userName == nullptr) {
		std::cout << "Error! No user created!" << std::endl;
		return;
	}

	strcpy(m_userName, name);

}

void User::setPassword(char * password)
{
	if (m_password != nullptr) {
		delete[]m_password;
		m_password = nullptr;
	}
	m_password = new(std::nothrow) char[strlen(password) + 1];
	if (m_password == nullptr) {
		std::cout << "Error! No user created!" << std::endl;
		return;
	}
	
	strcpy(m_password, password);
}

void User::setEmail(char * email)
{
	if (m_email != nullptr) {
		delete[]m_email;
		m_email = nullptr;
	}
	m_email = new(std::nothrow) char[strlen(email) + 1];
	if (m_email == nullptr) {
		std::cout << "Error! No user created!" << std::endl;
		return;
	}

	strcpy(m_email, email);
}

void User::setNumberOfTravels(unsigned number)
{
	m_countTravels = number;
}

void User::resizeFriendList()
{
	unsigned newCapacity = m_capacityFriends* 2;
	User* newFr = new (std::nothrow) User[newCapacity];
	std::cout << " in resize: " << m_capacityFriends << ", " << newCapacity << std::endl;

	if (newFr == nullptr) {
		std::cout << "Not enought memory for resize friends list! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacityFriends; ++i) {
		newFr[i] = m_friendsList[i];
	}

	m_capacityFriends = newCapacity;
	delete[] m_friendsList;
	m_friendsList = newFr;
}

void User::resizeTravelInfo()
{
	unsigned newCapacity = m_capacityTravels * 2;
	TravelInformation* newTravels = new (std::nothrow) TravelInformation[newCapacity];

	if (newTravels == nullptr) {
		std::cout << "Not enought memory for resize travels list! Error!" << std::endl;
		return;
	}

	for (unsigned i = 0; i < m_capacityTravels; ++i) {
		newTravels[i] = m_travels[i];
	}
	m_capacityTravels = newCapacity;
	delete[] m_travels;
	m_travels = newTravels;
}

void User::memoryAllocFriendsList()
{
	m_friendsList = new(std::nothrow) User[m_capacityFriends];
	if (m_friendsList == nullptr) {
		std::cout << "Error in memoryAllocFriendsList()." << std::endl;
		return;
	}
}

void User::memoryAllocTravelInfo()
{
	m_travels = new(std::nothrow) TravelInformation[m_capacityTravels];
	if (m_travels == nullptr) {
		std::cout << "Not enought memory for travels in memoryAllocTravelInfo(). Error!" << std::endl;
		return;
	}
}

void User::setFriendsList(User* friends)
{
	if (m_friendsList != nullptr) {
		delete[] m_friendsList;
	}

	unsigned capacity = friends->getCapacityOfFriends();
	unsigned size = friends->getNumberOfFriends();
	m_friendsList = new(std::nothrow) User[size];

	//Проверка дали е заделена паметта.
	if (m_friendsList == nullptr) {
		std::cout << "Not enought memory for set friendsList. Error!" << std::endl;
		return;
	}

	for (int i = 0; i < size; ++i) {
		m_friendsList[i] = friends[i];
	}

}

void User::setNumberOfFriends(unsigned number)
{
	m_numberOfFriends = number;
}

char * User::getUserName() const
{
	return m_userName;
}

char * User::getPassword() const
{
	return m_password;
}

char * User::getEmail() const
{
	return m_email;
}

unsigned User::getNumberOfFriends() const
{
	return m_numberOfFriends;
}

unsigned User::getCapacityOfFriends() const
{
	return m_capacityFriends;
}

unsigned User::getNumberOfTravels() const
{
	return m_countTravels;
}

void User::serializeUsersDatabase(std::ofstream & ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenName = strlen(m_userName);
	ofs.write((const char*)& lenName, sizeof(unsigned));
	ofs.write(m_userName, lenName);

	unsigned lenPassword = strlen(m_password);
	ofs.write((const char*)& lenPassword, sizeof(unsigned));
	ofs.write(m_password, lenPassword);

	unsigned lenEmail = strlen(m_email);
	ofs.write((const char*)& lenEmail, sizeof(unsigned));
	ofs.write(m_email, lenEmail);

	/*if (ofs.good()) {
		std::cout << "Successfully serialize." << std::endl;
	}
	else {
		std::cout << "Serialize failed. Error!" << std::endl;
	}*/

}

 
void User::deserializeUsersDatabase(std::ifstream & ifs)
{
	if (!ifs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenName = 0;
	ifs.read((char*)& lenName, sizeof(unsigned));
	m_userName = new(std::nothrow) char[lenName + 1];
	if (m_userName) {
		ifs.read(m_userName, lenName);
		m_userName[lenName] = '\0';
	}
	else {
		std::cout << "Not enought memory for name in deserialization function!" << std::endl;
		return;
	}

	unsigned lenPassword = 0;
	ifs.read((char*)& lenPassword, sizeof(unsigned));
	m_password = new (std::nothrow) char[lenPassword + 1];
	if (m_password) {
		ifs.read(m_password, lenPassword);
		m_password[lenPassword] = '\0';
	}
	else {
		std::cout << "Not enought memory for password in deserialization function!" << std::endl;
		return;
	}

	unsigned lenEmail = 0;
	ifs.read((char*)& lenEmail, sizeof(unsigned));
	m_email = new (std::nothrow) char[lenEmail + 1];
	if (m_email) {
		ifs.read(m_email, lenEmail);
		m_email[lenEmail] = '\0';
	}
	else {
		std::cout << "Not enought memory for email in deserialization function!" << std::endl;
		return;
	}

	/*if (ifs.good()) {
		std::cout << "Successfully desrializatiion!" << std::endl;
	}
	else {
		std::cout << "Deserialization failed. Error!" << std::endl;
	}*/
}

void User::serializePersonalDataBase(std::ofstream & ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	ofs.write((const char*)& m_countTravels, sizeof(m_countTravels));
	ofs.write((const char*)& m_capacityTravels, sizeof(m_capacityTravels));

	for (int i = 0; i < m_countTravels; ++i) {
		m_travels[i].serialize(ofs);
	}

	if (ofs.good()) {
		std::cout << "Successffuly serialize personal data base." << std::endl;
	}
	else {
		std::cout << "Failed serialize personal data base." << std::endl;
	}
}

void User::deserializePersonalDataBase(std::ifstream & ifs)
{
	if (!ifs.good()) {
		std::cout << "File is not open!" << std::endl;
	}

	ifs.read((char*)& m_countTravels, sizeof(m_countTravels));
	ifs.read((char*)& m_capacityTravels, sizeof(m_capacityTravels));

	for (int i = 0; i < m_countTravels; ++i) {
		m_travels[i].deserialize(ifs);
	}

	if (ifs.good()) {
		std::cout << "Successffuly deserialize personal database." << std::endl;
	}
	else {
		std::cout << "Deserialize personal database failed." << std::endl;
	}
}

bool User::isFriend(char * nameFriend)
{
	for (int i = 0; i < m_numberOfFriends; ++i) {
		if (strcmp(m_friendsList[i].getUserName(), nameFriend) == 0) {
			return true;
		}
	}
	return false;
}

void User::printInformation() const
{
	std::cout << "User name: " << m_userName << std::endl
		<< "Email: " << m_email << std::endl;
}

void User::printTravelInformation() const
{
	for (int i = 0; i < m_countTravels; ++i) {
		m_travels[i].print();
	}
}

bool User::isVisitDestination(char * dest)
{
	for (int i = 0; i < m_countTravels; ++i) {
		if (strcmp(dest, m_travels[i].getDestination()) == 0) {
			return true;
		}
	}
	return false;
}

void User::printDestinationInfoByName(char * name) const
{
	for (int i = 0; i < m_countTravels; ++i) {
		if (strcmp(name, m_travels[i].getDestination()) == 0) {
			m_travels[i].print();
			return;
		}
	}
	std::cout << "The user " << m_userName << " has not visited " << name << ". " << std::endl;
}

void User::prinDestinationEvaluation(char *destinationName) const
{
	for (int i = 0; i < m_countTravels; ++i) {
		if (strcmp( m_travels[i].getDestination(), destinationName) == 0) {
			std::cout << m_travels[i].getEvaluation() << std::endl;
		}
	}
}

void User::addFriend(const User & newFriend)
{
	//Проверка дали вече не са приятели.
	if (isFriend(newFriend.getUserName()) == true) {
		std::cout << "You are friends." << std::endl << std::endl;
		return;
	}
	if (m_numberOfFriends >= m_capacityFriends) {
		resizeFriendList();
	}

	m_friendsList[m_numberOfFriends] = newFriend;
	setNumberOfFriends(m_numberOfFriends + 1);
}

void User::removeFriend(const User & adversary)
{
	int pos = -1;
	for (int i = 0; i < m_numberOfFriends; ++i) {
		if (strcmp(adversary.getUserName(), m_friendsList[i].getUserName()) == 0) {
			pos = i;
			break;
		}
	}

	if (pos == -1) {
		std::cout<<std::endl << adversary.getUserName() << " is not your friend." << std::endl << std::endl;
		return;
	}
	m_friendsList[pos] = m_friendsList[m_numberOfFriends - 1];
	--m_numberOfFriends;
}

void User::addNewTravel(const TravelInformation & newTravel)
{
	//std::cout << "In User:: addNewTravel()." << std::endl;
	if (m_countTravels >= m_capacityTravels) {
		//std::cout << "In if" << std::endl;
		resizeTravelInfo();
	}

	m_travels[m_countTravels] = newTravel;
	
	m_travels[m_countTravels].print();

	if (m_travels == nullptr) {
		std::cout << "m_travels is nullptr. Error" << std::endl;
		return;
	}

	setNumberOfTravels(m_countTravels + 1);	
}
