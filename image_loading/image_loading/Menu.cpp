#include "Header.h"
#include "image.h"

// Basic input validation
string validate_string(string must_have)
{
	string s;
	while (true)
	{
		getline(cin, s);

			// if string has must have and does not have spaces
		if ((s.find(must_have) != string::npos) && (s.find(" ") == string::npos))
			return s;
		else
			cout << "\ninput invalid (check file extesion and ensure no spaces)\n try again: ";
	}
}

	// lets the user enter a command to do something
int menu()
{
		// setup
	string input;
	Image * master_pointer = nullptr;
	map<const string, int> command_map;
	command_map["quit"] = 0;
	command_map["restart"] = 1;
	command_map["load bmp"] = 2;
	command_map["load dcm"] = 3;
	command_map["save bmp"] = 4;
	command_map["convert"] = 5;
	command_map["filter NTSC"] = 6;
	command_map["filter SA"] = 7;
	command_map["filter omni"] = 8;
	command_map["filter di"] = 9;
	command_map["filter inv"] = 10;


		// command loop
	while (true)
	{
		cout << "\nCommand: ";
		getline(cin, input);

		if (command_map.count(input))
			switch (command_map[input])
			{
			case 0:  // quit
				delete master_pointer;
				return 0;
			case 1:  // restart
				delete master_pointer;
				return 1;

			case 2:  // load bmp
				cout << "Absolute path to (.bmp) file: ";
				input = validate_string(".bmp");
				master_pointer = new BMP_img(input);
				break;

			case 3:
				cout << " command 3";
				break;

			case 4:  // save bmp
				cout << "Absolute path to save with: ";
				input = validate_string(".bmp");
				master_pointer->save_bmp(input);
				break;

			case 5:
				cout << typeid(*master_pointer).name();
				break;

			case 6:
				if (typeid(*master_pointer).name() != "class BMP_img")
				{
					cout << "Current Image must be a bmp type to apply filters";
					cout << "try save bmp -> restart -> load bmp or convert";
					break;
				}
				else
				{
					//master_pointer->grey_scale("NTSC");
					// will create a filter function that has options for all different filter types
					//(rather than the current outspread)
				}
				break;

			case 7:
				cout << " command 7";
				break;

			case 8:
				cout << " command 8";
				break;

			case 9:
				cout << " command 9";
				break;

			case 10:
				cout << " command 10";
				break;
			}
		else
			cout << " Command not recognised";
		cout << '\n';
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
			<< "Command \t\tDescription \n"
			<< " load bmp \t\t create a bmp object and load into it an image \n"
			<< " load dmc \t\t create a dicom object \n"
			<< " save bmp \t\t save the current object as a bmp \n"
			<< " convert \t\t change the current object to be of bmp type \n"
			<< " filter NTSC \t\t apply National Television System Committee filter \n"
			<< " filter SA \t\t apply averaging grey filter \n"
			<< " filter omni \t\t apply omni-directonal convolution filter (diagonals included) \n"
			<< " filter di \t\t apply omni-directonal convolution filter (diagonals excluded) \n"
			<< " filter inv \t\t apply a color inversion \n"
			<< " quit  \t\t exit the program \n"
			<< " restart \t\t restart the programm \n";

		if (menu() == 0) return 0;
	}
}