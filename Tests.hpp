#ifndef __TESTS_HPP
#define __TESTS_HPP

#include<iostream>
#include"Manager.hpp"

void testUser() {
	User u1("Ivan", "123", "ivan@abv.bg");
	User u2;
	u2.memoryAllocFriendsList();//Защото в конструктора по подразбиране не се заделя памет за приятелите и пътуванията.
	u2.memoryAllocTravelInfo();
	u2 = u1;//Тест конструктор за присвояване.
	u2.printInformation();

	User user1("User1", "123", "user1mail");
	User user2("User2", "123", "user2mail");
	User user3("User3", "123", "user3mail");

	//Различни тестове за добавяне на приятел.
	user1.addFriend(user1);
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

	unsigned const m = 5;
	char comment[m];
	std::cin.getline(comment, m);

	TravelInformation t1(dest, a, b, eval, comment);
	user1.addNewTravel(t1);

	user1.printTravelInformation();
	user1.printDestinationInfoByName("Rome");
	user1.printDestinationInfoByName("Ibisa");//Извеждане на съобщение, че не е посетена тази дестинация.
	user1.prinDestinationEvaluation("Rome");
}

void testDate() {
	std::ofstream ofs("date.bin", std::ios::out | std::ios::binary);

	Date date1(3, 2, 2020);//Тестване на конструкторите
	Date date2(1, 3, 2020);
	Date invalidDate(29, 2, 2018);//Съобщение за невалидна дата.

	std::cout << "date1: ";
	date1.printDate();//Извеждане на дата
	date1.serialize(ofs);//Сериализиране.
	ofs.close();
	std::cout << std::endl << "date2: ";
	date2.printDate();

	Date date3;
	std::ifstream ifs("date.bin", std::ios::in | std::ios::binary);
	date3.deserialize(ifs);//Десериализиране.

	std::cout << "Date 3: ";
	date3.printDate();

	ifs.close();

	Date d1(29, 2, 2019);
	std::cout << d1.getDay() << "/" << d1.getMonth() << "/" << d1.getYear() << std::endl;
}

void testDestination() {
	Destination d("Sofia", 7, 25);

	//Извеждане на общата оценка за дестинацията.
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
	
	Date d1(1, 7, 2019);
	Date d2(7, 7, 2019);
	Destination*destination = new Destination("Nesebar", 100, 321);
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

	Photo p3 = p2;
	std::cout << p3.getPhoto() << std::endl;

	Photo p4;
	p4 = p1;
	std::cout << p4.getPhoto() << std::endl;

	Photo p5("error.txt");
	std::cout << p5.getPhoto() << std::endl;

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

#endif