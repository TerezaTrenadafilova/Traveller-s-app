#ifndef __TRAVEL_INFORMATION_HPP
#define __TRAVEL_INFORMATION_HPP

#include <cstring>
#include <fstream>

#include "Destination.hpp"
#include "Date.hpp"
#include "Photo.hpp"


class Destination;
class TravelInformation {
private:
	Destination* m_destination;

	Date m_dateOfArrival;
	Date m_dateOfDeparture;

	unsigned m_evaluation;
	
	char* m_comment;
	
	Photo* m_photos;
	unsigned m_countPhoto;
	unsigned m_capacityPhoto;
	//Помисли дали ти трабва списък с потребители, които са посетили дадена дестинация.

	//Променлива, която пази дали коректо е съзадено пътуване, т.е дали датите са валидни и дали имената на снимките също.
	bool isCorrectTravel = false;

	static const unsigned startCapacity = 8;//беше глобална константа преди класа

public:
	//Голяма четворка
	TravelInformation();
	TravelInformation(Destination*,Date,Date, unsigned, char* , Photo* =nullptr, unsigned=0,unsigned=startCapacity);

	//Конструктор за капиране.
	TravelInformation(const TravelInformation&);
	
	//Конструктор за присвояване.
	TravelInformation& operator=(const TravelInformation&);
	
	//Деструктор.
	~TravelInformation();

private:
	//Функция за копиране.
	void copy(const TravelInformation&);

	//Функция за изтриване.
	void clean();

	//Функция за преоразмеряване.
	void resize(unsigned);

public:
	//Мутатори.
	//void setDestination(char*);
	void setEvaluation(unsigned);
	void setComment(char*);
	//void setDateOfArrival(const Date&);
//	void setDeteOfDeparture(const Date&);
	void setDates(const Date&, const Date&);
	void setPhotos(Photo* );

	//Селектори.
	char* getDestination()const;
	unsigned getEvaluation() const;
	char* getComment() const;
	//char** getPhotos() const;

	//Записване в бинарен файл.
	void serialize(std::ofstream&) const;

	//Четене на информация от бинарен файл.
	void deserialize(std::ifstream&);

	//Добавяне на нова снимка.
	void addPhoto(const Photo&);

	void print()const;

	//Функция, която връща исктина, ако коректно е съзададено пътуване.
	bool isCorrectTravelInfo()const;

};

#endif
