#pragma warning(disable:4996)
#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>

#include"Manager.hpp"
#include "Tests.hpp"


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