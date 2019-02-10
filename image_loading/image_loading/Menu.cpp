#include "Header.h"
#include "image.h"

	// Basic input validation
string validate_name(bool bmp = true, bool dcm = true)
/*
Makes sure the input filepaths are valid - i.e if the has the correct
extension and does not contain space (we dont like spaces in windows)

parameters
----------
bmp, dcm: boolians for the allowed extensions for the string to be input

returns
-------
sting: valid filepath from the user
*/
{
	string s;
	while (true)
	{
		getline(cin, s);

			// if string has correct extension
		if ((s.find(".bmp") != string::npos) && bmp ||
			(s.find(".dcm") != string::npos) && dcm)
			return s;
		else
			cout << "\ninput invalid (check file extesion is correct)\n try again: ";
	}
}

	// lets the user enter a command to do something
int menu()
/*
The Menu the user sees when running the code, creates a map between
available inputs and integers, allowing switch-case to take care of 
the actions carried out.
*/
{
		// setup
	string input;
	Image * master_pointer = nullptr;
	map<const string, int> command_map;
	command_map["quit"] = 0;
	command_map["restart"] = 1;
	command_map["load bmp"] = 2;
	command_map["load dcm"] = 3;
	command_map["save"] = 4;
	//command_map["convert"] = 5;
	command_map["filter NTSC"] = 6; 
	command_map["filter SA"] = 7;
	command_map["filter omni"] = 8;
	command_map["filter di"] = 9;
	command_map["filter inv"] = 10;
	command_map["filter thresh"] = 11;


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
				input = validate_name(true, false);
				master_pointer = new BMP_img(input);
				break;

			case 3:  // load dcm
				cout << "Absolute path to (.dcm) file: ";
				input = validate_name(false, true);
				master_pointer = new DICOM_img(input);
				break;

			case 4:  // save bmp
				cout << "Absolute path to save with: ";
				input = validate_name(true, true);
				master_pointer->save(input);
				break;

			//case 5:  // convert to bmp
			//	cout << typeid(*master_pointer).name();
			//	if (typeid(*master_pointer).name() == "class BMP_img")
			//	{
			//		cout << "Image is already a bmp file\n";
			//	}
			//	else
			//	{
			//		cout << "do something ******************";
			//	}
			//	break;

			case 6:  // filter 1
				master_pointer->filter("NTSC");
				break;

			case 7:  // filter 2
				master_pointer->filter("SA");
				break;

			case 8:  // filter 3
				master_pointer->filter("omni");
				break;

			case 9:  // filter 4
				master_pointer->filter("bi");
				break;

			case 10:  // filter 5
				master_pointer->filter("inv");
				break;

			case 11:  // filter 6
				cout << "color threshold: ";
				int val;
				cin >> val;
				master_pointer->filter("thresh", val);
				break;
			}
		else  // ignore unknown commands
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
		cout << "===============================\n\t\tMenu\n=============================== \n"
			<< "Command \t\tDescription \n"
			<< " load bmp \t\t create a bmp object and load into it an image \n"
			<< " load dcm \t\t create a dicom object \n"
			<< " save \t\t\t save the current object as a bmp \n"
			//<< " convert \t\t change the current object to be of bmp type \n"
			<< " filter NTSC \t\t apply National Television System Committee filter \n"
			<< " filter SA \t\t apply averaging grey filter \n"
			<< " filter omni \t\t apply omni-directonal convolution filter (diagonals included) \n"
			<< " filter bi \t\t apply bi-directonal convolution filter (diagonals excluded) \n"
			<< " filter inv \t\t apply a color inversion \n"
			<< " filter thresh \t\t partition image pixels into black and white\n"
			<< " quit  \t\t\t exit the program \n"
			<< " restart \t\t restart the programm \n";

		if (menu() == 0) return 0;
	}
}