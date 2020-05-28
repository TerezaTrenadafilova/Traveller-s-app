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
	//Валидация на името на снимката.
	unsigned lenNamePhoto = strlen(namePhoto);
	unsigned pointPosition = 0;
	unsigned counter = 0;

	//Запазване името на снимката в променлива, защото след while цикъла няма да работи.
	char* photo = new(std::nothrow) char[lenNamePhoto + 1];
	if (photo == nullptr) {
		std::cout << "Not enought memory for photo. Error!" << std::endl;
		return;
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
		return;
	}
	for (int i = 0; i < lenExtention;++i) {
		ext[i] = namePhoto[i + pointPosition+1];
	}

	//Проверка дали името е коректно.

	//ПРоверка дали разширението на файла е от разрешените.
	if (strcmp(ext, EXTENSION_1) == 0 || strcmp(ext, EXTENSION_2) == 0) {
		m_name = new(std::nothrow) char[lenNamePhoto + 1];
		if (m_name == nullptr) {
			std::cout << "Not enought memory for set name of photo. Error!" << std::endl;
			return;
		}
		strcpy(m_name, namePhoto);
	}
	else {
		std::cout << "Invalid extesion." << std::endl;
		m_name = nullptr;
	}
	//delete[] photo;
	

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
