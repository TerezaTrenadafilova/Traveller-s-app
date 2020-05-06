#pragma warning(disable:4996)//За да няма грешки с функцията strcpy().
#include<iostream>
#include "Photo.hpp"

const char* EXTENSION_1 = "jpeg";
const char* EXTENSION_2 = "png";

Photo::Photo()
	:m_name(nullptr)
{
}

Photo::Photo(char * name)
	:m_name(nullptr)
{
	setPhoto(name);
}

Photo::Photo(const Photo & other)
{
	if (this != &other) {
		copyFrom(other);
	}
}

Photo & Photo::operator=(const Photo & other)
{
	if (this != &other) {
		delete[] m_name;
		copyFrom(other);
	}
	return *this;
}

Photo::~Photo()
{
	delete[] m_name;
}

void Photo::setPhoto(char * namePhoto)
{
	//Направи валидация на името на снимката.
	unsigned lenNamePhoto = strlen(namePhoto);
	m_name = new(std::nothrow) char[lenNamePhoto + 1];
	if (m_name == nullptr) {
		std::cout << "Not enought memory for set name of photo. Error!" << std::endl;
		return;
	}
	strcpy(m_name, namePhoto);

}

char * Photo::getPhoto() const
{
	return m_name;
}

void Photo::serialize(std::ofstream & ofs) const
{
	if (!ofs.is_open()) {
		std::cout << "File is not open!" << std::endl;
		return;
	}

	unsigned lenName = strlen(m_name);
	ofs.write((const char*)& lenName, sizeof(lenName));
	ofs.write(m_name, lenName);

	if (ofs.good()) {
		std::cout << "Successffuly serialize." << std::endl;
	}
	else {
		std::cout << "Serialize failed!" << std::endl;
	}
}

void Photo::deserialize(std::ifstream & ifs)
{
	if (!ifs.is_open()) {
		std::cout << "File is not open." << std::endl;
		return;
	}

	unsigned lenName = 0;
	ifs.read((char*)& lenName, sizeof(lenName));
	m_name = new(std::nothrow) char[lenName + 1];
	if (m_name) {
		ifs.read(m_name, lenName);
		m_name[lenName] = '\0';
	}
	else {
		std::cout << "Not enought memory for deserialize. " << std::endl;
		return;
	}

}

void Photo::copyFrom(const Photo & other)
{
	/*unsigned lenName = strlen(other.m_name);
	m_name = new (std::nothrow) char[lenName + 1];
	if (m_name == nullptr) {
		std::cout << "Not enought memory for set photo's name." << std::endl;
		return;
	}
	strcpy(m_name, other.m_name);*/
	setPhoto(other.m_name);
}
