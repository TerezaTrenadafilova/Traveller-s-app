#pragma warning(disable:4996)
#include<iostream>
#include "TravelInformation.hpp"

const unsigned MAX_EVALUATION = 5;
const unsigned MIN_EVALUATION = 1;

TravelInformation::TravelInformation()
	/*:m_destination(nullptr)
	, m_dateOfArrival(nullptr)
	, m_dateOfDeparture(nullptr)
	, m_evaluation(MIN_EVALUATION)
	,m_comment(nullptr)*/
	:m_destination(Destination::Destination())
	, m_dateOfArrival(Date::Date())
	, m_dateOfDeparture(Date::Date())
	,m_evaluation(MIN_EVALUATION)
	, m_comment(nullptr)
	,m_photos(nullptr)
	,m_countPhoto(0)
	,m_capacityPhoto(8)
{
	std::cout << "Default travelInfo cnst:" << std::endl;
	setComment("no comment");
}

TravelInformation::TravelInformation(Destination destination, Date arrival, Date departure ,unsigned evaluation, char *comment, Photo* photos, unsigned count, unsigned capacity)
	//:m_destination(destination)//����� ��������� � ������ �� ������������
	//,m_dateOfArrival(arrival)
	//,m_dateOfDeparture(departure)
	/*: m_destination(nullptr)
	,m_dateOfArrival(nullptr)
	,m_dateOfDeparture(nullptr)*/
	:m_evaluation(evaluation)
	, m_comment(nullptr) 
	,m_photos(nullptr)
	,m_countPhoto(count)
	,m_capacityPhoto(capacity)
{
	m_destination = destination;
	m_dateOfArrival = arrival;
	m_dateOfDeparture = departure;
	
	//����������� ���� �� ����������� �� ������ ����������.
	destination.setNumberOfVisits(destination.getNumberOfVisits() + 1);

	//������� �� ����� ���� ���������.
	unsigned numberVisit = destination.getNumberOfVisits() + 1;
	destination.setNumberOfVisits(numberVisit);

	//������� �� ������ �� ������ ������ �� ������������.
	unsigned sumAll = destination.getSumOfALL() + m_evaluation;
	destination.setSumOfAll(sumAll);
	
	setComment(comment);
	setPhotos(photos);


}

TravelInformation::TravelInformation(const TravelInformation & other)
{
	if (this != &other) {
		copy(other);
	}
}

TravelInformation & TravelInformation::operator=(const TravelInformation &other)
{
	if (this != &other) {
		clean();
		copy(other);
	}
	return *this;
}

TravelInformation::~TravelInformation()
{
	clean();
}

void TravelInformation::copy(const TravelInformation & other)
{
//	setDestination(other.m_destination);

	setEvaluation(other.m_evaluation);
	setComment(other.m_comment);
	setDateOfArrival(other.m_dateOfArrival);
	setDeteOfDeparture(other.m_dateOfDeparture);

	m_photos = new(std::nothrow) Photo[other.m_capacityPhoto];
	if (m_photos == nullptr) {
		std::cout << "Not enought memory for set photos." << std::endl;
		return;
	}
	for (int i = 0; i < other.m_countPhoto; ++i) {
		m_photos[i] = other.m_photos[i];
	}

}

void TravelInformation::clean()
{


	delete[] m_comment;
	m_comment = nullptr;

	delete[] m_photos;
	m_photos = nullptr;

	//��������� �� ������� �� ��������.
}

void TravelInformation::resize(unsigned newCapacity)
{
	if (m_countPhoto <= m_capacityPhoto) {
		return;
	}

	Photo* tempPhotos = new(std::nothrow) Photo[newCapacity];
	if (tempPhotos == nullptr) {
		std::cout << "Error in resize function. " << std::endl;
		return;
	}

	for (int i = 0; i < m_countPhoto; ++i) {
		tempPhotos[i] = m_photos[i];
	}

	delete[] m_photos;
	m_photos = tempPhotos;
	m_capacityPhoto = newCapacity;
}

//void TravelInformation::setDestination(char * destination)
//{
//	if (m_destination != nullptr) {
//		delete[] m_destination;
//	}
//
//	m_destination = new(std::nothrow) char[strlen(destination) + 1];
//	if (m_destination == nullptr) {
//		std::cout << "Not enought memory for destination! Error!" << std::endl;
//		return;
//	}
//
//	strcpy(m_destination, destination);
//}

void TravelInformation::setEvaluation(unsigned evaluation)
{
	
	if (evaluation >= MIN_EVALUATION && evaluation <= MAX_EVALUATION) {
		m_evaluation = evaluation;
		
		//������� �� ������ �� ������ ������ �� ������ ����������.
		unsigned change = m_destination.getSumOfALL() + m_evaluation;
		m_destination.setSumOfAll(change);
	}
	else {
		std::cout << "Ivavalid evaluation. The evaluation will not be changed" << std::endl;
		return;
	}
}

void TravelInformation::setComment(char * comment)
{
	if (m_comment != nullptr) {
		delete[] m_comment;
	}

	m_comment = new(std::nothrow) char[strlen(comment) + 1];
	if (m_comment == nullptr) {
		std::cout << "Not enought memory for comment. Error!" << std::endl;
		return;
	}
	strcpy(m_comment, comment);
}

void TravelInformation::setDateOfArrival( const Date& date)
{
	/*m_dateOfArrival = new(std::nothrow) Date;
	if (m_dateOfArrival == nullptr) {
		std::cout << "Not enought memory for date of arrival. Error!" << std::endl;
		return;
	}*/

	if (date.getYear() <= m_dateOfDeparture.getYear() && date.getMonth() <= m_dateOfDeparture.getMonth()&& date.getDay() <= m_dateOfDeparture.getDay()) {
		m_dateOfArrival = date;
	}
	else {
		std::cout << "Invalid date of arrival! " << std::endl;
		return;
	}

	
}

void TravelInformation::setDeteOfDeparture(const Date& date)
{
	/*m_dateOfDeparture = new(std::nothrow) Date;
	if (m_dateOfDeparture == nullptr) {
		std::cout << "Not enought memory for date of departure. Error!" << std::endl;
		return;
	}*/

	if (date.getYear() >= m_dateOfArrival.getYear() && date.getMonth() >= m_dateOfArrival.getMonth() && date.getDay() >= m_dateOfArrival.getDay()) {
		m_dateOfDeparture = date;
	}
	else {
		std::cout << "Invalid date of arrival! " << std::endl;
		return;
	}
}

void TravelInformation::setPhotos(Photo * photo)
{
	m_photos = new(std::nothrow) Photo[m_capacityPhoto];
	if (m_photos == nullptr) {
		std::cout << "Not enought memory." << std::endl;
		return;
	}
	for (int i = 0; i < m_countPhoto; ++i) {
		m_photos[i] = photo[i];
	}
}

//void TravelInformation::setPhotos(char ** photos)
//{
//	//TODO work;
//}

//char * TravelInformation::getDestination() const
//{
//	return m_destination;
//}

unsigned TravelInformation::getEvaluation() const
{
	return m_evaluation;
}

char * TravelInformation::getComment() const
{
	return m_comment;
}

void TravelInformation::serialize(std::ofstream &ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}
	m_destination.serialize(ofs);
	m_dateOfArrival.serialize(ofs);
	m_dateOfDeparture.serialize(ofs);

	ofs.write((const char*)& m_evaluation, sizeof(m_evaluation));

	unsigned lenComment = strlen(m_comment);
	ofs.write((const char*)& lenComment, sizeof(lenComment));
	ofs.write(m_comment, lenComment);

	ofs.write((const char*)& m_countPhoto, sizeof(m_countPhoto));
	ofs.write((const char*)& m_capacityPhoto, sizeof(m_capacityPhoto));
	for (int i = 0; i < m_countPhoto; ++i) {
		m_photos[i].serialize(ofs);
	}

	if (ofs.good()) {
		std::cout << "Successffuly serialize of travel information." << std::endl;
	}
	else {
		std::cout << "Serialize of travel information failed. " << std::endl;
	}
}

void TravelInformation::deserialize(std::ifstream & ifs)
{
	if (!ifs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	m_destination.deserialize(ifs);
	m_dateOfArrival.deserialize(ifs);
	m_dateOfDeparture.deserialize(ifs);

	ifs.read((char*)& m_evaluation, sizeof(m_evaluation));

	unsigned lenComment = 0;
	ifs.read((char*)& lenComment, sizeof(lenComment));
	m_comment = new(std::nothrow) char[lenComment + 1];
	if (m_comment ) {
		ifs.read(m_comment, lenComment);
		m_comment[lenComment] = '\0';
	}
	else {
		std::cout << "Not enought memory in deserialize method. Error!" << std::endl;
		return;
	}

	ifs.read((char*)& m_countPhoto, sizeof(m_countPhoto));
	ifs.read((char*)& m_capacityPhoto, sizeof(m_capacityPhoto));

	m_photos = new(std::nothrow) Photo[m_capacityPhoto];
	if (m_photos == nullptr) {
		std::cout << "Not enought memory for photos in deserialize method." << std::endl;
		return;
	}
	for (int i = 0; i < m_countPhoto; ++i) {
		m_photos[i].deserialize(ifs);
	}

	if (ifs.good()) {
		std::cout << "Successffuly deserialize." << std::endl;
	}
	else {
		std::cout << "Deserialize failed." << std::endl;
	}
}

void TravelInformation::addPhoto(const Photo & photo)
{
	if (m_countPhoto >= m_capacityPhoto) {
		unsigned newCapacity = m_capacityPhoto * 2;
		resize(newCapacity);
	}
	m_photos[m_countPhoto] = photo;
	++m_countPhoto;
}

void TravelInformation::print() const
{
	//������� ������ �� � ��-�����.
	std::cout << m_destination.getDestination() << ", ";
	m_dateOfArrival.printDate();
	std::cout << ", ";
	m_dateOfDeparture.printDate();
	std::cout << ", " << m_evaluation << ", " << m_comment << std::endl;
}

//char ** TravelInformation::getPhotos() const
//{
//	return m_photos;
//}

