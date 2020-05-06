#ifndef __PHOTO_HPP
#define __PHOTO_HPP

#include <cstring>
#include <fstream>

class Photo {
private:
	char* m_name;

public:
	//������ ��������.
	Photo();
	Photo(char*);
	Photo(const Photo&);
	Photo& operator=(const Photo&);
	~Photo();

	//�����.
	void setPhoto(char*);

	//�����.
	char* getPhoto()const;

	//��������� � ������� ����.
	void serialize(std::ofstream &)const;

	//������ �� ������� ����.
	void deserialize(std::ifstream&);

private:
	void copyFrom(const Photo&);
};

#endif
