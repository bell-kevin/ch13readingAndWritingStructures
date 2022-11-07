// ch13readingAndWritingStructures.cpp
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype> // for toUpper()
#include <string>
using namespace std;

const int NAME_SIZE = 51, ADDRESS_SIZE = 51, PHONE_SIZE = 14;
struct Info
{
	char name[NAME_SIZE];
	int age;
	char address1[ADDRESS_SIZE];
	char address2[ADDRESS_SIZE];
	char phone[PHONE_SIZE];
};

int main()
{
    cout << "Chapter 13 Inventory by Kevin Bell\n\n";
	Info person; // Store information about a person
	char response; // User's response to a question
	
	string input; // used to read strings
	
	//create file object and open file
	fstream people("people.dat", ios::out | ios::binary);
	if (!people)
	{
		cout << "Error opening file. Program terminated.";
		return 1;
	}
	
	//keep getting information from user and writing to file in binary mode
	do
	{
		//get name
		cout << "Enter the person's name: ";
		getline(cin, input);
		strcpy_s(person.name, input.c_str());

		//get age
		cout << "Enter the person's age: ";
		cin >> person.age;

		//get address
		cout << "Enter the person's address: ";
		cin.ignore();
		getline(cin, input);
		strcpy_s(person.address1, input.c_str());

		//get address
		cout << "Enter the person's address: ";
		getline(cin, input);
		strcpy_s(person.address2, input.c_str());

		//get phone number
		cout << "Enter the person's phone number: ";
		getline(cin, input);
		strcpy_s(person.phone, input.c_str());

		//write the record to the file
		people.write(reinterpret_cast<char*>(&person), sizeof(person));

		//ask user if they want to enter another record
		cout << "Do you want to enter another record? (Y/N): ";
		cin >> response;
		cin.ignore();
		response = toupper(response);
	} while (response == 'Y');
	//close the file
	people.close();	
	
	//open the file for reading
	people.open("people.dat", ios::in | ios::binary);
	if (!people)
	{
		cout << "Error opening file. Program terminated.";
		return 1;
	}
	
	//read the first record from the file
	people.read(reinterpret_cast<char*>(&person), sizeof(person));
	
	//display the records
	while (!people.eof()) {
		cout << "Name: " << person.name << endl
			<< "Age: " << person.age << endl
			<< "Address: " << person.address1 << endl
			<< "Address: " << person.address2 << endl
			<< "Phone: " << person.phone << endl << endl;
		people.read(reinterpret_cast<char*>(&person), sizeof(person));
	} //end while
	
	//close the file
	people.close();
	system("pause");
	return 0;
} //end main
