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

void testUser() {
	User u1("Ivan", "123", "ivan@abv.bg");
	User u2;
	u2 = u1;;
	u2.printInformation();

	User user1("User1", "123", "user1mail");
	User user2("User2", "123", "user2mail");
	User user3("User3", "123", "user3mail");

	user1.addFriend(user2);
	user1.addFriend(user3);
	user1.removeFriend(user2);

	std::cout << user1.isFriend("User1") << std::endl;
	std::cout << user1.isFriend("User2") << std::endl;
	std::cout << user1.isFriend("User3") << std::endl;

	user1.printInformation();
	user2.printInformation();
	user3.printInformation();


	Destination* dest = new Destination("Rome");
	Date a(1, 3, 2020);
	Date b(10, 3, 2020);
	unsigned eval = 4;

	char comment[5];//Магическо число!
	std::cin.getline(comment, 3);

	TravelInformation t1(dest, a, b, eval, comment);
	user1.addNewTravel(t1);

	user1.printTravelInformation();
	user1.printDestinationInfoByName("Rome");
	user1.printDestinationInfoByName("Ibisa");
	user1.prinDestinationEvaluation("Rome");
}

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
	Destination*destination=new Destination("Nesebar", 100, 321);
	unsigned eval = 3;;
	char comment[100];
	std::cout << "enter a coment: ";
	std::cin.getline(comment, 100);

	Photo* p1 = new(std::nothrow) Photo[1];
	p1->setPhoto("myPhoto.jpeg");
	TravelInformation t1(destination, d1, d2, eval, comment, p1, 1, 2);
	destination->setNumberOfVisits(destination->getNumberOfVisits() + 1);
	destination->setSumOfAll(destination->getSumOfALL() + eval);
	std::cout << "Print info: " << std::endl;
	t1.print();
	std::cout << "Destination: " << destination->getAverage() << ", " << destination->getNumberOfVisits() << ", " << destination->getSumOfALL() << std::endl;
	std::cout << std::endl;
	
	//Тестване дали правилно е добавено ново пътуване.
	User u1("Ivan", "123", "ivan@abv.bg");
	std::cout << "User1: " << u1.getNumberOfFriends() << "," << u1.getCapacityOfFriends()
		<< '/' << u1.getNumberOfTravels();
	u1.addNewTravel(t1);  //Успешно преминат

	std::cout << "Add new travel for u1: " << std::endl;
	u1.printTravelInformation();

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

	/*if (ofs.good()) {
		std::cout << "Success." << std::endl;
	}
	else {
		std::cout << "Error in file." << std::endl;
	}*/
	ofs.close();


	User u1("User1", "13245", "user1@abv.bg");
	ofs.open("User.db", std::ios::out | std::ios::binary);
	if (!ofs.is_open()) {
		std::cout << "In main error." << std::endl;
		return 1;

	}

	
	ofs.write((const char*)& count, sizeof(count));
	ofs.write((const char*)& capacity, sizeof(capacity));
	u1.serializeUsersDatabase(ofs);

	//if (ofs.good()) {
	//	std::cout << "Success." << std::endl;
	//}
	//else {
	//	std::cout << "Error in file." << std::endl;
	//}
	ofs.close();

	Manager m;
	m.runProgram();

	
	//testDate();

	//std::cout << std::endl << std::endl;

	//testPhoto();

	//std::cout << std::endl << std::endl;
	//
	//testTravelInfo();

	//std::cout << std::endl << std::endl;

	//testMenagerClass();

	return 0;
}