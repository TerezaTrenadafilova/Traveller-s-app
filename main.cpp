#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>

//#include"User.hpp"
//#include"TravelInformation.hpp"
//#include"Destination.hpp"
//#include"Date.hpp"
//#include"Photo.hpp"
#include"Manager.hpp"


void testDate() {
	std::ofstream ofs("date.bin", std::ios::out | std::ios::binary);

	Date date1(3, 2, 2020);
	Date date2(1, 3, 2020);

	std::cout << "date1: ";
	date1.printDate();
	date1.serialize(ofs);
	ofs.close();
	std::cout << std::endl << "date2: ";
	date2.printDate();

	Date date3;
	std::ifstream ifs("date.bin", std::ios::in | std::ios::binary);
	date3.deserialize(ifs);

	std::cout << "Date 3: ";
	date3.printDate();

	ifs.close();

	Date d1(29, 2, 2019);
	std::cout << d1.getDay() << "/" << d1.getMonth() << "/" << d1.getYear() << std::endl;
}

void testDestination() {
	Destination d("Berkovica", 7, 25);
	std::cout << "Average evaluation of destination is: " << std::setprecision(2) << d.getAverage() << std::endl;

	
	std::ofstream dest("destination.bin", std::ios::out | std::ios::binary);
	d.serialize(dest);
	dest.close();

	std::ifstream des("destination.bin", std::ios::in | std::ios::binary);
	Destination d2;
	d2.deserialize(des);
	std::cout << d2.getDestination() << ", " << d2.getNumberOfVisits() << std::endl;
	des.close();

}

void testTravelInfo() {
	//Проверка на валидацията.
	/*TravelInformation t1;
	t1.setEvaluation(3);
	std::cout << "Evaluation: " << t1.getEvaluation() << std::endl;*/

	Date d1(1, 7, 2019);
	Date d2(7, 7, 2019);
	Destination destination("Nesebar", 100, 321);
	unsigned eval = 3;;
	char comment[100];
	std::cout << "enter a coment: ";
	std::cin.getline(comment, 100);

	Photo* p1 = new(std::nothrow) Photo[1];
	p1->setPhoto("myPhoto.jpeg");
	//TravelInformation t1(destination, d1, d2, eval, comment, p1, 1, 2);
	destination.setNumberOfVisits(destination.getNumberOfVisits() + 1);
	destination.setSumOfAll(destination.getSumOfALL() + eval);
	std::cout << "Print info: " << std::endl;
	//t1.print();
	std::cout << "Destination: " << destination.getAverage() << ", " << destination.getNumberOfVisits() << ", " << destination.getSumOfALL() << std::endl;
	std::cout << std::endl;
	
	std::ofstream ofs("travelInfo.bin", std::ios::out | std::ios::binary);
	//t1.serialize(ofs);
	ofs.close();

	std::ifstream ifs("travelInfo.bin", std::ios::in | std::ios::binary);
	TravelInformation t2;
	t2.deserialize(ifs);
	std::cout << t2.getComment() << std::endl;
	ifs.close();

	
}

void testPhoto() {
	Photo p("myFristPhoto.jpeg");
	std::ofstream ofs("photos.bin", std::ios::out | std::ios::binary);
	p.serialize(ofs);
	ofs.close();

	Photo p1;
	std::ifstream ifs("photos.bin", std::ios::in | std::ios::binary);
	p1.deserialize(ifs);
	std::cout << "Photo name is: " << p1.getPhoto() << std::endl;

	Photo p2("img.jpeg");
	std::cout << p2.getPhoto() << std::endl;

	Photo p3("error.txt");
	std::cout << p3.getPhoto() << std::endl;

}

void testMenagerClass() {

	Manager m;
	m.registrerNewUser();
	m.registrerNewUser();
	m.login();
	Destination* dest = new Destination("Melnik");
	Date a(1, 3, 2020);
	Date b(2, 3, 2020);
	unsigned eval = 4;
	char comment[3];
	std::cin.getline(comment, 3);

	TravelInformation t1(dest, a, b, eval, comment);
	m.addDestination(t1);

	m.printUser();

	m.printDestinations();
}

int main() {

	//std::ofstream ofs("users.bin", std::ios::binary| std::ios::out|std::ios::trunc);

	//if (!ofs.is_open()) {
	//	std::cout << "File can not to open!" << std::endl;
	//	return 1;
	//}

	//unsigned countUser = 2;
	//
	////В началото на файла файла, който пази иформацията за потребителите, записваме брой на потребителите.
	//ofs.write((const char*)& countUser, sizeof(countUser));

	//const unsigned MAX_LEN = 100;
	//char name[MAX_LEN];
	//char pass[MAX_LEN];
	//char email[MAX_LEN];

	//std::cout << "Name: ";
	//std::cin.getline(name, MAX_LEN);

	//std::cout << "Password: ";//<< std::endl;
	//std::cin.getline(pass, MAX_LEN);

	//std::cout << "Email: ";//<< std::endl;
	//std::cin.getline(email, MAX_LEN);

	//User u(name, pass, email);
	//u.serializeUsersDatabase(ofs);
	//User u1("Ana Simeonova", "12345", "an@abv.bg");
	//u1.serializeUsersDatabase(ofs);
	//ofs.close();

	//std::ifstream ifs("users.bin", std::ios::binary);
	////Първо прочита броят на потребителите.
	//unsigned sizeOfArr;
	//ifs.read((char*)& sizeOfArr, sizeof(sizeOfArr));

	//User *usersInfo= new (std::nothrow) User[sizeOfArr];
	//if (usersInfo == nullptr) {
	//	std::cout << "Not enought memory for usersInfo! Error!" << std::endl;
	//	return 1;
	//}
	//for (int i = 0; i < sizeOfArr; ++i) {
	//	usersInfo[i].deserializeUsersDatabase(ifs);
	//}
	//ifs.close();

	//std::cout << "Do you have registration?[y/n]" << std::endl;
	//char userAnswer;
	//std::cin >> userAnswer;

	////Ако потребителят има вече регистрация.
	//if (userAnswer == 'y' || userAnswer == 'Y') {//Работи успешно, без направената лична база данни.
	//	std::cout << "User name: ";
	//	
	//	//За да работи правилно cin.getline()
	//	char c;
	//	std::cin.get(c);

	//	std::cin.getline(name, MAX_LEN);

	//	std::cout << "Password: ";
	//	std::cin.getline(pass, MAX_LEN);

	//	bool isUser=false;
	//	for (int i = 0; i < sizeOfArr; ++i) {
	//		if (strcmp(usersInfo[i].getUserName(), name) == 0) {
	//			if (strcmp(usersInfo[i].getPassword(), pass) == 0) {
	//				//Отвaране на личната база данни за този потребител.
	//				std::cout << "You log in as " << name << std::endl;
	//				isUser = true;
	//			
	//			}
	//		}
	//	}
	//	if (isUser == false) {
	//		std::cout << "Invalid user name/ password." << std::endl;
	//	}

	//}

	////Ако потребителя иска да се регистрира
	//if (userAnswer == 'n' || userAnswer == 'N') {
	//	std::cout << "User name: ";

	//	//За да работи правилно cin.getline()
	//	char c;
	//	std::cin.get(c);

	//	std::cin.getline(name, MAX_LEN);

	//	std::cout << "Password: ";
	//	std::cin.getline(pass, MAX_LEN);

	//	std::cout << "Email: ";
	//	std::cin.getline(email, MAX_LEN);

	//	//Създаване на нов потребител в системата.
	//	User newUser(name, pass, email);
	//	ofs.open("users.bin", std::ios::binary | std::ios::out | std::ios::app);
	//	
	//	sizeOfArr += 1;//Увеличаваме броят на потребителите.
	//	ofs.write((const char*)& sizeOfArr, sizeof(sizeOfArr));
	//	
	//	//Тук не работи правилно. Трябва да го поправя. Помисли как!
	//	for (int i = 0; i < sizeOfArr; ++i) {
	//		usersInfo[i].deserializeUsersDatabase(ifs);//Записваме наново всички потребители до сега.
	//	}
	//	newUser.serializeUsersDatabase(ofs);//в края добавяме новият регистриран потребител.

	//	ofs.close();
	//	char nameFile[MAX_LEN];
	//	strcpy(nameFile, name);
	//	strcat(nameFile, ".db");

	//	//Отваряне на личната база данни.
	//	//std::ifstream ifs(nameFile, std::ios::in | std::ios::binary);
	//	//Работа с информацията, която потребителя ни подава.
	//}



	////Трябва да прочетем отново информацията от файла.
	//ifs.open("users.bin", std::ios::binary);
	//unsigned size = 0;
	////Прочитаме броя на потребителите.
	//ifs.read((char*)&size, sizeof(size));
	//User* newUsers = new(std::nothrow) User[size];
	//if (newUsers == nullptr) {
	//	std::cout << "Error" << std::endl;
	//	return 1;
	//}
	//
	//for (int i = 0; i < size; ++i) {
	//	newUsers[i].deserializeUsersDatabase(ifs);
	//}
	//ifs.close();

	//std::cout << "Print users information: " << size<< std::endl;
	//for (int i = 0; i < size; ++i) {
	//	newUsers[i].printInformation();
	//}

	//ifs.close();

	////Изтриване на заделената памет.
	//for (int i = 0; i < size; ++i) {
	//	delete[] newUsers;
	//}
	//delete[] newUsers;
	//
	//

	//testTravelInfo();
	
	unsigned count = 1;
	unsigned capacity = 8;

	Destination dest("Melnik");
	std::cout << dest.getDestination() << ", " << dest.getNumberOfVisits() << std::endl;
	std::ofstream ofs("Destinations.db", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "In main error." << std::endl;
		return 1;
	}

	ofs.write((const char*)& count, sizeof(count));
	ofs.write((const char*)& capacity, sizeof(capacity));
	dest.serialize(ofs);

	if (ofs.good()) {
		std::cout << "Success." << std::endl;
	}
	else {
		std::cout << "Error in file." << std::endl;
	}
	ofs.close();


	User u1("Teri", "13245", "teri@abv.bg");
	ofs.open("User.db", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "In main error." << std::endl;
		return 1;

	}

	
	ofs.write((const char*)& count, sizeof(count));
	ofs.write((const char*)& capacity, sizeof(capacity));
	u1.serializeUsersDatabase(ofs);

	if (ofs.good()) {
		std::cout << "Success." << std::endl;
	}
	else {
		std::cout << "Error in file." << std::endl;
	}
	ofs.close();


 //testPhoto();

	Manager m;
	m.runProgram();

	system("pause");

	return 0;
}