#ifndef __USER_HPP
#define __USER_HPP

#include<fstream>
#include<cstring>
#include"TravelInformation.hpp"

class User {
private:
	//Данните, които се пазят в базата данни за потребителите.
	char* m_userName;
	char* m_password;
	char* m_email;

	//Допълнителни данни за всеки потребител.
	User* m_friendsList;
	unsigned m_numberOfFriends;
	unsigned m_capacityFriends;
	
	//Списък с пътувания.
	TravelInformation* m_travels;
	unsigned m_countTravels;
	unsigned m_capacityTravels;
	
public:
	//Може би няма да ми трябва, но за сега ще го оставя.
	User();
	
	//Констректор за създаване на нов потребител.
	User(char*, char*, char*);

	//Конструктор, който инициализира всички полета на класа.
	User(char*, char*, char*, User*, unsigned, unsigned, TravelInformation*, unsigned, unsigned);

	//Констректор за копиране.
	User(const User&); //Ще ми трябва при промяна на списъка с приятели. 
	
	//Консструктор за присвояване.
	User& operator=(const User&);
	
	//Деструктор.
	~User();

private:

	void copy(const User&);
	void cleanMemory();

	//Ще направя сетъррите private, за да не може да се променят данните на потребителя.
	void setName(char*);
	void setPassword(char*);
	void setEmail(char*);


public:
	//void freeMemory(User& );

	//Мутатори за промяна на приятелите.
	void setFriendsList(User*);
	void setNumberOfFriends(unsigned);

//	void setTravels(TravelInformation*);
//	void setCountTravels(unsigned);

	//Селектори.
	char* getUserName() const;
	char* getPassword() const;
	char* getEmail() const;
	unsigned getNumberOfFriends() const;
	unsigned getCapacityOfFriends()const;

	//Записване на потребител в база данните с потребител.
	void serializeUsersDatabase(std::ofstream &)const;
	
	//Четене на потребител от база данните с потребители.
	void deserializeUsersDatabase(std::ifstream&);

	//Записване в личната база данни.
	void serializePersonalDataBase(std::ofstream&) const;

	//Четене от личната база данни.
	void deserializePersonalDataBase(std::ifstream&);

	void printInformation()const;
};

#endif
