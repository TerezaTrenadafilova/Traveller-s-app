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
	//������� ���� �� ������ ������ � �����������, ����� �� �������� ������ ����������.

public:
	//������ ��������
	TravelInformation();
	TravelInformation(Destination*,Date,Date, unsigned, char* , Photo* , unsigned,unsigned);

	//����������� �� ��������.
	TravelInformation(const TravelInformation&);
	
	//����������� �� �����������.
	TravelInformation& operator=(const TravelInformation&);
	
	//����������.
	~TravelInformation();

private:
	//������� �� ��������.
	void copy(const TravelInformation&);

	//������� �� ���������.
	void clean();

	//������� �� ���������������.
	void resize(unsigned);

public:
	//��������.
	//void setDestination(char*);
	void setEvaluation(unsigned);
	void setComment(char*);
	void setDateOfArrival(const Date&);
	void setDeteOfDeparture(const Date&);
	void setPhotos(Photo* );

	//���������.
	char* getDestination()const;
	unsigned getEvaluation() const;
	char* getComment() const;
	//char** getPhotos() const;

	//��������� � ������� ����.
	void serialize(std::ofstream&) const;

	//������ �� ���������� �� ������� ����.
	void deserialize(std::ifstream&);

	//�������� �� ���� ������.
	void addPhoto(const Photo&);

	void print()const;


};

#endif
