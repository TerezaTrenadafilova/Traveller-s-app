#pragma warning(disable:4996)
#include<iostream>
#include<cstring>
#include"Manager.hpp"

//unsigned startCapacity = 8;

//unsigned const MAX_LEN_COMMAND = 11;
//unsigned const MAX_LEN = 50;

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
		if (m_nameFile != nullptr) {
			delete[]m_nameFile;
			m_nameFile = nullptr;
		}
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

	}
	if (strcmp(fileName, "Destinations.db") == 0) {
		if (m_nameFile != nullptr) {
			delete[]m_nameFile;
			m_nameFile = nullptr;
		}
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

	if (strcmp(m_nameFile, "User.db") == 0 || strcmp(m_nameFile, "Destinations.db") == 0) {
		cleanMemory();
	}
	
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

bool Manager::isValidPhoto(char * namePhoto)
{
	const char* EXT_1= "jpeg";
	const char* EXT_2 = "png";

	//Валидация на името на снимката.
	unsigned lenNamePhoto = strlen(namePhoto);
	unsigned pointPosition = 0;
	unsigned counter = 0;

	//Запазване името на снимката в променлива, защото след while цикъла няма да работи.
	char* photo = new(std::nothrow) char[lenNamePhoto + 1];
	if (photo == nullptr) {
		std::cout << "Not enought memory for photo. Error!" << std::endl;
		return false;
	}
	strcpy(photo, namePhoto);

	//Намиране позицията на точката в името на файла, за да проверим дали разширението е едно от двете позволени.
	while (*photo != '\0') {
		if (*photo == '.') {
			pointPosition = counter;
		}
		++counter;
		++photo;
	}

	//Намиране дължината на разширението.
	unsigned lenExtention = lenNamePhoto - pointPosition;

	char* ext = new(std::nothrow) char[lenExtention];
	if (ext == nullptr) {
		std::cout << "Not enought memory for extention. Error!" << std::endl;
		return false;
	}
	for (int i = 0; i < lenExtention; ++i) {
		ext[i] = namePhoto[i + pointPosition + 1];
	}

	std::cout << "Extension is: " << ext << std::endl;
	//Проверка дали името е коректно.

	//Запазване името на снимката в променлива, защото след while цикъла няма да работи.
	char* photo1 = new(std::nothrow) char[lenNamePhoto + 1];
	if (photo == nullptr) {
		std::cout << "Not enought memory for photo. Error!" << std::endl;
		return false;
	}
	strcpy(photo1, namePhoto);

	//ПРоверка дали разширението на файла е от разрешените.
	if (strcmp(ext, EXT_1) == 0 || strcmp(ext, EXT_2) == 0) {
		while (photo1!='\0') {
			if (!((*photo1 >= 'A' && *photo1 <= 'Z') ||
				(*photo1 >= 'a'&& *photo1 <= 'z') ||
				*photo1 == '.' || *photo1 == '_')) {
				return false;
			}
		}
		return true;
	}
	else {
		std::cout << "Invalid extesion." << std::endl;
		return false;
	}
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

		if (isUserExist(name, password) == true) {
			isLoggedIn = true;
			 posLoggedUser = posOfUser(name, password);

			std::cout <<std::endl<< "Welcome " << name << " !" << std::endl<<std::endl;
			
			//Създавене на името за лчната база данни.
			char* userDataBase = new(std::nothrow)char[strlen(name) + strlen(extDataBase) + 1];
			if (userDataBase == nullptr) {
				std::cout << std::endl << "Not enought memory for userDataBase in login(). Error!" << std::endl;
				return;
			}
			strcpy(userDataBase, name);
			strcat(userDataBase, extDataBase);
			//std::cout << " user data base is: " << userDataBase << std::endl;

			//Отваряне на личната база данни на потребителя. Тя ще бъде празна, защото потребителят е нов.
			std::ifstream ifs;
			
			ifs.open(userDataBase, std::ios::binary | std::ios::in|std::ios::app);
			if (!ifs.is_open()) {
				std::cout << userDataBase << " is not opened. Error!" << std::endl << std::endl;
			}

			//Проверка дали личната база данни не е празна.
			ifs.seekg(0, std::ios::end);
			if (ifs.tellg()) {
				//Прочитане на личната база данни на потребителя.
				m_users[posLoggedUser].deserializePersonalDataBase(ifs);
				ifs.close();
			}
			else {
				std::cout << "Private database is empty." << std::endl << std::endl;
			}

			//Работа с m_nameFile
			setM_NameFile(userDataBase);

			//Промяна на името на последния влязъл потребител.
			setNameLastLoggedUser(name);
			
		}
		if (isLoggedIn == false) {
			std::cout << "Uncorrect username/password or or the user database is not open (User.db). Try again." << std::endl;
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

void Manager::addNewFriend(char* nameFriend)
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

void Manager::removeFriend(char*  nameFriend)
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
	
//	std::cout << "Number of destination: " << m_numberOfDestinations << std::endl;

	for (int i = 0; i < m_numberOfDestinations; ++i) {
		
	//	std::cout << "In for cycle in  addDestinations()" << std::endl;
		
		//Ако вече съществува такава дестинация в програмата.
		if (strcmp( m_destinations[i].getDestination(), newTravel.getDestination()) == 0) {
			//std::cout << "In if in for: " << std::endl;
			//Увеличавене броя на посещениеята с 1.
			unsigned numberVisit = m_destinations[i].getNumberOfVisits() + 1;
			m_destinations[i].setNumberOfVisits(numberVisit);
	
			//Промяна на сумата от всички оценки на дестинацията.
			unsigned sumAll = m_destinations[i].getSumOfALL() + newTravel.getEvaluation();
			m_destinations[i].setSumOfAll(sumAll);
			m_destinations[i].addUser(m_users[posLoggedUser]);

			return;
		}
		
	}

	//Създаване на нова дестинация.

	if (m_numberOfDestinations >= m_capacityOfDestinations) {
		resizeDestinationList();
	}
	unsigned countVisit = 1;//Първото посещение е направено от текущия потребител.
	m_destinations[m_numberOfDestinations] = Destination(newTravel.getDestination(), countVisit, startCapacity);
	
	m_destinations[m_numberOfDestinations].setNumberOfVisits(countVisit);
	m_destinations[m_numberOfDestinations].setSumOfAll(newTravel.getEvaluation());
	//m_destinations[m_numberOfDestinations].addUser(m_users[posLoggedUser]); //не работи.
	++m_numberOfDestinations;

}

void Manager::viewLoggedInUserTravels() const
{
	m_users[posLoggedUser].printTravelInformation();
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
			std::cout << "File name: ";
			std::cin.getline(fileName, MAX_LEN * 10);

			open(fileName);
		
		}

		//Затваряне на файл.
		if (strcmp(command, "close") == 0) {
			if (isSuccessfullyOpen == true) {
				closeFile();
			}
			else {
				std::cout << std::endl << "There is no open file to close." << std::endl << std::endl;
			}
			
		}

		//Запазване на текущо отворения файл.
		if (strcmp(command, "save") == 0) {
			if (isSuccessfullyOpen == true) {
				save();
			}
			else {
				std::cout << std::endl << "There is no open file to save." << std::endl << std::endl;
			}
			
		}

		//Запазване в нов файл.
		if (strcmp(command, "saveas") == 0) {
			if (isSuccessfullyOpen == true) {
				char fileName[MAX_LEN * 10];
				std::cin.getline(fileName, MAX_LEN * 10);

				saveas(fileName);
			}
			else {
				std::cout << std::endl << "There is no open file to save as." << std::endl << std::endl;
			}
			
		}

		//Помощ.
		if (strcmp(command, "help") == 0) {
			help();
		}

		//Вписване на потребител.
		if (strcmp(command, "log in") == 0) {
			if (isLoggedIn == false) {
				login();
			}
			else {
				std::cout << std::endl << m_users[posLoggedUser].getUserName() << ", you are logged in." << std::endl << std::endl;
			}
			
		}

		//Отписване на потребител.
		if (strcmp(command, "log out") == 0) {
			if (isLoggedIn == true) {
				logout();
			}
			else {
				std::cout << std::endl << "No user logged in. Invalid operation." << std:: endl << std::endl;
			}
			
		}

		//Регистриране на нов потребител.
		if (strcmp(command, "registration") == 0) {
			if (isLoggedIn == false) {
				registrerNewUser();
			}
			else {
				std::cout << std::endl << "There is already a registered user. Invalid operation. " << std::endl << std::endl;
			}
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

		//Извеждане на всички дестинации на влезлия потребител.
		if (strcmp(command, "view my destinations") == 0) {
			if (isLoggedIn == true || isSuccessfullyOpen == true) {
				viewLoggedInUserTravels();
			}
			else {
				std::cout << std::endl << "No user logged in or there is no open file in the program." << std::endl << std::endl;

			}
		}

		//Проверка дали приятел е посетил дадена дестниация.
		if (strcmp(command, "check friend destination") == 0) {
			if (isSuccessfullyOpen == true && isLoggedIn == true) {
				char nameFriend[MAX_LEN];
				char nameDestination[MAX_LEN];

				std::cout << "Friend's name: ";
				std::cin.getline(nameFriend, MAX_LEN);

				std::cout << "Destination: ";
				std::cin.getline(nameDestination, MAX_LEN);

				checkFriendDestination(nameFriend, nameDestination);
			}
			else {
				std::cout << std::endl << "No user logged in or there is no open file in the program." << std::endl << std::endl;
			}
			
		}

		//Извеждане на всички дестинации, които е посетил приятел.
		if (strcmp(command, "print all friend's destinations") == 0) {
			if (isSuccessfullyOpen == true && isLoggedIn == true) {
				char nameFriend[MAX_LEN];

				std::cout << "Friend's name: ";
				std::cin.getline(nameFriend, MAX_LEN);

				allDesinationOfFriend(nameFriend);
			}
			else {
				std::cout << std::endl << "No user logged in or there is no open file in the program." << std::endl << std::endl;
			}
			
		}

		//Проверка за дадена дестинация.
		if (strcmp(command, "check destination") == 0) {
			if (isSuccessfullyOpen == true || isLoggedIn == true) {
				char nameDestination[MAX_LEN];

				std::cout << "Destination: ";
				std::cin.getline(nameDestination, MAX_LEN);

				checkDestination(nameDestination);
			}
			else {
				std::cout << std::endl << "No user logged in or there is no open file in the program." << std::endl << std::endl;

			}
			
		}

		//Добавяне на приятел.
		if (strcmp(command, "add friend") == 0) {
			if (isSuccessfullyOpen == true && isLoggedIn) {
				char nameFriend[MAX_LEN];

				std::cout << "Friend's name: ";
				std::cin.getline(nameFriend, MAX_LEN);

				addNewFriend(nameFriend);
			}
			else {
				std::cout << std::endl << "No user logged in." << std::endl << std:: endl;
			}
			
		}

		//Премахване на приятел.
		if (strcmp(command, "block friend") == 0) {
			if (isSuccessfullyOpen == true || isLoggedIn == true) {
				char nameFriend[MAX_LEN];

				std::cout << "Friend's name: ";
				std::cin.getline(nameFriend, MAX_LEN);

				removeFriend(nameFriend);
			}
			else {
				std::cout << "No user logged in." << std::endl << std::endl;
			}
			
		}

		//Добавяне на дестинация.
		if (strcmp(command, "add destination") == 0) {
			if (isSuccessfullyOpen == true || isLoggedIn == true) {
				char nameDestination[MAX_LEN];
				std::cout << "Please enter the name of the destination you visited: ";
				std::cin.getline(nameDestination, MAX_LEN);
				Destination *dest = new (std::nothrow)Destination(nameDestination);

				unsigned dayOfArrival, monthOfArrival, yearOfArrival;
				std::cout << "Please enter arrival date in ISO 8601 form  (year / month / day): ";
				std::cin >> yearOfArrival >> monthOfArrival >> dayOfArrival;
				Date dateArrival(dayOfArrival, monthOfArrival, yearOfArrival);

				unsigned dayOfDeparture, monthOfDeparture, yearOfDeparture;
				std::cout << "Please enter deperture date in ISO 8601 form  (year / month / day): ";
				std::cin >>  yearOfDeparture >> monthOfDeparture >>dayOfDeparture;
				Date dateDeparture(dayOfDeparture, monthOfDeparture, yearOfDeparture);

				unsigned evaluation;
				do {
					std::cout << "Please enter your evaluation: ";
					std::cin >> evaluation;
				} while (evaluation == 0 || evaluation > 5);


				const unsigned lenComment = MAX_LEN * 10;
				char comment[lenComment];
				char c;
				std::cin.get(c);//За да работи правилно cin.getline()
				std::cout << "Please enter your comment for this destination: ";
				std::cin.getline(comment, lenComment);

				unsigned countOfPicture;
				std::cout << "How many photos will you upload?: ";
				std::cin >> countOfPicture;


				Photo* photosFromDestination = new(std::nothrow) Photo[countOfPicture];
				if (photosFromDestination == nullptr) {
					std::cout << "Not enought memory for photos in add destination body. Error!" << std::endl;
					return;
				}

				//Според http://www-it.fmi.uni-sofia.bg/ReDisInfo/courses/modules/module1/parts/module2/part1/lesson2.html
				//името на файл не може да е по-дълго от 255 символа.
				unsigned const lenNameFile = 256;//255+1 за '\0'
				char namePhoto[lenNameFile];
				int i = 0;
				while (i < countOfPicture){
					std::cout << "Please enter the name of the photo file: ";
					char buffer;
					std::cin.get(buffer);
					std::cin.getline(namePhoto, lenNameFile);
					Photo tempPhoto(namePhoto);
					if (tempPhoto.isValidPhotoCreated()) {
						photosFromDestination[i] = tempPhoto;
						++i;
					}
				} 

				//Това е невалдно пътуване потправи го. Намери грешката къде е. Най-вероятоно е в датата.
				TravelInformation travelInfo(dest, dateArrival, dateDeparture, evaluation, comment, photosFromDestination);
				if (travelInfo.isCorrectTravelInfo() == true) {
					std::cout << "New travel is correct. AddDestinations():" << std::endl;
					addDestination(travelInfo);
				}
				else {
					std::cout << "Invalid travel." << std::endl << std::endl;
				}

			}
			else {
				std::cout << std::endl << "No user logged in. Inavalid operation." << std::endl << std::endl;
			}
			
		}

		/*if(m_nameFile!= nullptr)
			std::cout << std::endl << "Last opened file name: " << m_nameFile << std::endl << std::endl;*/

		
	}
}
