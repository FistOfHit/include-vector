#include "Header.h"
#include "image.h"

// Basic input validation
// does not really work
//template <class T>
//void validate_input(T &input)
//{
//	while (true)
//	{
//		cin >> input;
//
//		if (!cin)
//		{
//			cout << "\nUn-recognised input, try again: ";
//			continue;
//		}
//		for (char &c : input)
//			if (c == ' ')
//			{
//				cout << "\ninput must not have spaces, try again: ";
//				continue;
//			}
//		return;
//	}
//}

	// lets the user enter a command to do something
int menu()
{
	// setup
	string command, buffer;
	map<const string, int> command_map;
	command_map["quit"] = 0;
	command_map["restart"] = 1;
	command_map["load-bmp"] = 2;
	command_map["load-dcm"] = 3;
	command_map["save-bmp"] = 4;
	command_map["convert"] = 5;
	command_map["filter-NTSC"] = 6;
	command_map["filter-SA"] = 7;
	command_map["filter-omni"] = 8;
	command_map["filter-di"] = 9;
	command_map["filter-inv"] = 10;

	// command loop
	while (true)
	{
		cout << "\nCommand: ";
		cin >> command;

		switch (command_map[command])
		{
		case 0:
			return 0;
		case 1:
			return 1;

		case 2:
			cout << "\ncommand 2\n";
			break;
		case 3:
			cout << "\ncommand 3\n";
			break;
		case 4:
			cout << "\ncommand 4\n";
			break;
		case 5:
			cout << "\ncommand 5\n";
			break;
		case 6:
			cout << "\ncommand 6\n";
			break;
		case 7:
			cout << "\ncommand 7\n";
			break;
		case 8:
			cout << "\ncommand 8\n";
			break;
		case 9:
			cout << "\ncommand 9\n";
			break;
		case 10:
			cout << "\ncommand 10\n";
			break;
		default:
			cout << "\n Command not recognised";
		}
	}
}


	// release main
int main()
{
	while (true)
	{
		cout << "Medical Image Filter written by Hitesh Kumar and Richard Boyne\n"
			<< "for ACSE 5.2 coursework - Imperial College London\n\n";
		cout << "==========================\n\tMenu\n========================== \n"
			<< "\tCommand \t\tDescription \n"
			<< "\t 'load-bmp' \t\t create an object and load into it an image \n"
			<< "\t 'load-dmc' \n"
			<< "\t 'save-bmp' \t\t save the current object as a bmp \n"
			<< "\t 'convert' \t\t change the current object to be of bmp type \n"
			<< "\t 'filter-NTSC' \t\t apply National Television System Committee filter \n"
			<< "\t 'filter-SA' \t\t apply averaging grey filter \n"
			<< "\t 'filter-omni' \t\t apply omni-directonal convolution filter (diagonals included) \n"
			<< "\t 'filter-di' \t\t apply omni-directonal convolution filter (diagonals excluded) \n"
			<< "\t 'filter-inv' \t\t apply a color inversion \n"
			<< "\t 'quit' \t\t exit the program \n"
			<< "\t 'restart' \t\t restart the programm \n";

		if (menu() == 0) return 0;
	}
}

