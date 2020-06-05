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
{	if(m_name!=nullptr){
		delete[]m_name;
		m_name = nullptr;
	}

	if (isValidName(namePhoto) == true) {
		strcpy(m_name, namePhoto);
		isCorrectPhotoCreate = true;
	}
	else {
		m_name = nullptr;
	}
	//delete[] photo;
}

 char * Photo::getPhoto() const
{
	if (m_name!=nullptr) {
		return m_name;
	}
	else {
		std::cout << "The photo file name is not specified." << std::endl;
	}
}

bool Photo::isValidName(char * namePhoto)
{
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
		if (!((*photo >= 'A' &&*photo <= 'Z') || (*photo >= 'a' &&*photo <= 'z') || *photo == '_' || *photo=='.')) {
			std::cout << "Invalid name of picture file." << std::endl;
			return false;
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

	//ПРоверка дали разширението на файла е от разрешените.
	if (strcmp(ext, EXTENSION_1) == 0 || strcmp(ext, EXTENSION_2) == 0) {
		m_name = new(std::nothrow) char[lenNamePhoto + 1];
		if (m_name == nullptr) {
			std::cout << "Not enought memory for set name of photo. Error!" << std::endl;
			return false;
		}
		return true;
	}
	else {
		std::cout << "Invalid extesion." << std::endl;
		return false;
	}
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

bool Photo::isValidPhotoCreated() const
{
	return isCorrectPhotoCreate;
}

void Photo::copyFrom(const Photo & other)
{
	setPhoto(other.m_name);
}
