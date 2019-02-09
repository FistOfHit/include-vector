#pragma once
#include "Header.h"

class Image
/*
The main class of any image object here, intialises and contains basic
information about the image such as size, location in memory,
absolute path etc.
*/
{
public:

		// properties of the image
	string filename = "null_path";
	uint8_t * data_pointer = nullptr;
	int dim_x = -1;
	int dim_y = -1;
	int size = -1;
	string abs_direct = "";

		// all images must be able to save to bmp
		// as from bmp the dcmtk package can convert to and
		// from all other types from there
	virtual void save(string path) = 0;
		// calls the different filter methods
	virtual void filter(string method, uint8_t val = 0)
	{
		cout << "Image must be of type bmp to apply filters\n";
		cout << "try convert or save bmp -> restart -> load bmp\n";
	}

	Image()
	{
		// display information
		cerr << "Image instance at " << this << " constructed\n";

			// find the path to this program
		char path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH);
			// truncate to current working directory
		int last_slash = 0;
		for (int i = 0; i < MAX_PATH; i++)
			if (path[i] == '\\')
				last_slash = i + 1;  // +1 to include the final slash
		this->abs_direct = string(&path[0], &path[0] + last_slash);

	}

	~Image()
	{
		// display information
		cerr << "\nImage instance at " << this << " deconstructed";
		// if data has been loaded delete it
		if (this->data_pointer != nullptr)
			delete[] this->data_pointer;
	}
};

class BMP_img : public Image
/*
The child class of an image object, the BMP class separates
meta-data from pixel arrays on instantiation, and has all the 
methods to manipulate the image as well as save and load as a 
BMP image.
*/
{
public:
		// file meta data
	char unsigned meta_data[54];

		// requiered functions
	BMP_img(string path);
	void save(string name);
		
		// index a pixle
	int i(int row, int col, int rgb);

		// apply different filters
	void filter(string method, uint8_t val = 0);
	void color_inversion();
	void grey_scale(string method);
	void convolution_filter(string method);
	void threshold(uint8_t limit);

};

class DICOM_img : public Image
/*
The child class of an image object, the DICOM class simply
stores the path and has functions to save as a .dcm file or 
convert to a BMP for manipulation.
*/
{
public:
		// requiered functions
	DICOM_img(string path);
	void save(string name);

		// create BMP_img object (save bmp -> load bmp -> delete file)
	void convert_bmp(BMP_img *&pointer);
};