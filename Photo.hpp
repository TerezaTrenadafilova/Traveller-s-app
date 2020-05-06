#ifndef __PHOTO_HPP
#define __PHOTO_HPP

#include <cstring>
#include <fstream>

class Photo {
private:
	char* m_name;

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

	//Записване в бинарен файл.
	void serialize(std::ofstream &)const;

	//Четене от бинарен файл.
	void deserialize(std::ifstream&);

private:
	void copyFrom(const Photo&);
};

#endif
