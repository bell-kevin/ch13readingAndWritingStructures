// ch13readingAndWritingStructures.cpp
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype> // for toUpper()
#include <string>
#include <iomanip>
using namespace std;

const int ITEM_SIZE = 15;
struct Inventory
{
	char item[ITEM_SIZE];
	int quantity;
	double price;
};

int main()
{
    cout << "Chapter 13 Inventory by Kevin Bell\n\n";
	Inventory inventory; // Store information about an inventory
	char response; // User's response to a question
	string input; // used to read strings
	
	//create file object and open file
	fstream items("items.dat", ios::out | ios::binary);
	if (!items)
	{
		cout << "Error opening file. Program terminated.";
		return 1;
	}
	
	//keep getting information from user and writing to file in binary mode
	do
	{
		//get item name
		cout << "Enter name of inventory object: ";
		getline(cin, input);
		strcpy_s(inventory.item, input.c_str());
		
		//get price of item
		cout << "Enter price of inventory object: $";
		cin >> inventory.price;

		//get quantity
		cout << "Quantity of that object: ";
		cin >> inventory.quantity;

		//write the record to the file
		items.write(reinterpret_cast<char*>(&inventory), sizeof(inventory));

		//ask user if they want to enter another record
		cout << "Do you want to enter another record? (Y/N): ";
		cin >> response;
		cin.ignore();
		response = toupper(response);
	} while (response == 'Y');
	//close the file
	items.close();
	
	//open the file for reading
	items.open("items.dat", ios::in | ios::binary);
	if (!items)
	{
		cout << "Error opening file. Program terminated.";
		return 1;
	}
	
	//read the first record from the file
	items.read(reinterpret_cast<char*>(&inventory), sizeof(inventory));
	
	
	//display the records as a table
	//use setw to format the output
	
	cout << setw(ITEM_SIZE) << left << "Item" << setw(10) << right << "Quantity" << setw(14) << right << "Price" << endl;
	cout << "------------------------------------------" << endl;
	
	//while not at the end of the file, read the record from the file
	while (!items.eof())
	{
		//display the record with set precision 2 for price and dollar sign for price
		cout << setw(ITEM_SIZE) << left << inventory.item << setw(10) << right << inventory.quantity << setw(10) << right << setprecision(2) << fixed << "$" << inventory.price << endl;
		
		//read the next record from the file
		items.read(reinterpret_cast<char*>(&inventory), sizeof(inventory));
	} //end while loop
	
	//close the file
	items.close();
	cout << "Complete" << endl;
	system("pause");
	return 0;
} //end main
