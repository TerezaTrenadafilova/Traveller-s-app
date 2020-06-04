#pragma warning(disable:4996)//За да няма грешки с функцията strcpy().
#include<iostream>
#include<cstring>


#include"Destination.hpp"


Destination::Destination()
	:m_name(nullptr), m_numberOfVisits(0), m_sumOfAllEstimates(0)
	,m_users(nullptr), m_numberOfUsers(0), m_capacityOfUsers(Capacity)
{
	m_users = new(std::nothrow) User[m_capacityOfUsers];
	//m_users->memoryAllocFriendsList();//За конструктора по подразбиране: заделяне на памет за списъка с приятели
	//m_users->memoryAllocTravelInfo();//За конструктора по подразбиране: заделяне на памет за списъка с пътувания
	if (m_users == nullptr) {
		std::cout << "Not enought memory for users in destination constructor." << std::endl;
		return;
	}

}

Destination::Destination(char *name, unsigned number, unsigned sum, User* users, unsigned numberOfUsers, unsigned capacityOfUsers)
	:m_name(nullptr), m_numberOfVisits(number), m_sumOfAllEstimates(sum)
	,m_users(nullptr), m_numberOfUsers(numberOfUsers), m_capacityOfUsers(capacityOfUsers)
{
	setName(name);

	m_users = new(std::nothrow) User[m_capacityOfUsers];
	//m_users->memoryAllocFriendsList();//За конструктора по подразбиране: заделяне на памет за списъка с приятели
	//m_users->memoryAllocTravelInfo();//За конструктора по подразбиране: заделяне на памет за списъка с пътувания
	if (m_users == nullptr) {
		std::cout << "Not enought memory for users.Error!" << std::endl;
		return;
	}
	
	for (int i = 0; i < m_numberOfUsers; ++i) {
		m_users[i] = users[i];
	}
}

Destination::Destination(const Destination &other)
{
	if (this != &other) {
		copy(other);
	}
	
}

Destination & Destination::operator=(const Destination &other)
{
	if (this != &other) {
		cleanMemory();
		copy(other);
	}
	return *this;
}

Destination::~Destination()
{
	cleanMemory();
}

void Destination::setName(char *name)
{
	
	/*if (m_name != nullptr) {
		delete[] m_name;
	}*/
	

	m_name = new(std::nothrow) char[strlen(name) + 1];
	if (m_name == nullptr) {
		std::cout << "Not enought memory! Error!" << std::endl;
		return;
	}

	strcpy(m_name, name);
}

void Destination::setNumberOfVisits(unsigned number)
{
	m_numberOfVisits = number;
}

void Destination::setSumOfAll(unsigned sum)
{
	m_sumOfAllEstimates = sum;
}

char * Destination::getDestination() const
{
	return m_name;
}

double Destination::getAverage() const
{
	 double m_average = (double)m_sumOfAllEstimates / (double) m_numberOfVisits;
	return m_average;
}

unsigned Destination::getSumOfALL() const
{
	return m_sumOfAllEstimates;
}

unsigned Destination::getNumberOfVisits() const
{
	return m_numberOfVisits;
}

void Destination::serialize(std::ofstream & ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenName = strlen(m_name);
	ofs.write((const char*)& lenName, sizeof(lenName));
	ofs.write(m_name, lenName);



	/*if (ofs.good()) {
		std::cout << "Successfully serialize" << std::endl;
	}
	else {
		std::cout << "Serialize is filed!" << std::endl;
	}*/
	
}

void Destination::deserialize(std::ifstream & ifs) 
{
	if (!ifs.is_open()) {
		std::cout << "File is not open. Error!" << std::endl;
		return;
	}
	
	unsigned lenName = 0;
	ifs.read((char*)& lenName, sizeof(lenName));
	m_name = new(std::nothrow) char [lenName + 1];
	if (m_name) {
		ifs.read(m_name, lenName);
		m_name[lenName] = '\0';
	}
	else {
		std::cout << "Not enought memory for deserialize destination!" << std::endl;
		return;
	}

	/*if (ifs.good()) {
		std::cout << "Successffuly deserialize." << std::endl;
	}
	else {
		std::cout << "Deserialize failed." << std::endl;
	}*/
}

void Destination::addUser(const User & newUser)
{
	if (m_numberOfUsers >= m_capacityOfUsers) {
		resize();
	}
	m_users[m_numberOfUsers] = newUser;
	++m_numberOfUsers;
}

void Destination::printUserWhoVisitedDestination() const
{
	std::cout << std::endl << "List of users who have visited " << m_name << ": " << std::endl;
	for (int i = 0; i < m_numberOfUsers; ++i) {
		std::cout << m_users[i].getUserName() << ",  ";
		m_users[i].prinDestinationEvaluation(m_name);
	}
	std::cout << "Average evaluation: " << getAverage() << std::endl << std::endl;
}

void Destination::copy(const Destination &other)
{
	setName(other.m_name);
	setNumberOfVisits(other.m_numberOfVisits);
	setSumOfAll(other.m_sumOfAllEstimates);

	delete[]m_users;
	m_users = new(std::nothrow) User[other.m_capacityOfUsers];
	if (m_users = nullptr) {
		std::cout << "Not enought memory for set user list. Error!" << std::endl;
		return;
	}

	for (int i = 0; i < other.m_numberOfUsers; ++i) {
		m_users[i] = other.m_users[i];
	}
	m_capacityOfUsers = other.m_capacityOfUsers;
	m_numberOfUsers = other.m_numberOfUsers;
	//setAverage(other.m_average);
}

void Destination::cleanMemory()
{
	delete[]m_name;
	m_name = nullptr;

	delete[] m_users;
	m_users = nullptr;
}

void Destination::resize()
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
