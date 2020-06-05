#ifndef __PHOTO_HPP
#define __PHOTO_HPP

#include <cstring>
#include <fstream>

class Photo {
private:
	char* m_name;

	//����������, ����� �� ���� ���� ��������  � ��������� ������.
	bool isCorrectPhotoCreate = false;

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

	//�������� ���� ����� �� ����� � ��������.
	bool isValidName(char*);

	//��������� � ������� ����.
	void serialize(std::ofstream &)const;

	//������ �� ������� ����.
	void deserialize(std::ifstream&);

	//�������, ����� ����� ���� � ��������� ������ � ������� ���.
	bool isValidPhotoCreated()const;


private:
	void copyFrom(const Photo&);
};

#endif
