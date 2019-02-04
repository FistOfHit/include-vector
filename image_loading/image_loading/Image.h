#pragma once
#include "Header.h"

class Image
{
public:

	string filename = "null_path";
	char unsigned meta_data[54];
	//int8_t * data_pointer = nullptr;
	//unsigned char * data_pointer = nullptr;
	uint8_t * data_pointer = nullptr;
	int dim_x = -1;
	int dim_y = -1;
	int size = -1;

	virtual void load(string path) = 0;
	virtual void save(string path) = 0;

	~Image()
	{
			// if data has been loaded delete it
		if (data_pointer != nullptr)
			delete[] data_pointer;
	}
};

class BMP_img : public Image
{
public:

	BMP_img(string path);

	void save(string name);

	void load(string path);

	void color_inversion();
};
