#pragma once
#include "Header.h"

class Image
{
public:

		// properties of the image
	string filename = "null_path";
	char unsigned meta_data[54];
	uint8_t * data_pointer = nullptr;
	int dim_x = -1;
	int dim_y = -1;
	int size = -1;

		// save and load funciton
	virtual void save_bmp(string path) = 0;

	Image()
	{
			// display information
		cerr << "\nImage instance at " << this << " constructed\n";
	}

	~Image()
	{
			// display information
		cerr << "\nImage instance at " << this << " deconstructed";
			// if data has been loaded delete it
		if (this->data_pointer != nullptr)
		{
			cerr << "(data at " << this->data_pointer << " deleted)\n";
			delete[] this->data_pointer;
		}
	}
};

class BMP_img : public Image
{
public:
		// requiered functions
	BMP_img(string path);
	void load(string path);
	void save_bmp(string name);

		// index a pixle
	int i(int row, int col, int rgb);

		// different filters
	void color_inversion();

	void grey_scale(string method);

	void convolution_filter(string method);

		// save as other file formats
	//void dicom_to_bmp(string dicom_filename, string target_filename);

	void save_dcm(string name);

};

class DICOM_img : public Image
{
public:
		// requiered functions
	DICOM_img(string path);
	void save_bmp(string name);

		// create BMP_img object
	void convert_bmp(BMP_img *&pointer);
};