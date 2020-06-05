#ifndef __PHOTO_HPP
#define __PHOTO_HPP

#include <cstring>
#include <fstream>

class Photo {
private:
	char* m_name;

	//променлива, която ще пази дали правилно  е създадена снимка.
	bool isCorrectPhotoCreate = false;

public:
	//Голяма четворка.
	Photo();
	Photo(char*);
	Photo(const Photo&);
	Photo& operator=(const Photo&);
	~Photo();

	//Сетър.
	void setPhoto(char*);

	//Гетър.
	char* getPhoto()const;

	//Проверка дали името на файла е коректно.
	bool isValidName(char*);

	//Записване в бинарен файл.
	void serialize(std::ofstream &)const;

	//Четене от бинарен файл.
	void deserialize(std::ifstream&);

	//Функция, която връща дали е създадена снимка с валидно име.
	bool isValidPhotoCreated()const;


private:
	void copyFrom(const Photo&);
};

#endif
