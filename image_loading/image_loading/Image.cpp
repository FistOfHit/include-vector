#include "Header.h"
#include "image.h"

BMP_img::BMP_img(string path)
{
	this->filename = path;
	load(path);
	cout << "Loaded from " << path << " BMP with dimensions "
		 << dim_x << " " << dim_y << "\n";
}

void BMP_img::load(string path)
{
		// open the file
	FILE *p_file;
	FILE **pp = &p_file;
	int a = fopen_s(pp, path.c_str(), "rb");
	//cout << "file load successful (0 == yes): " << a << '\n';
	assert(a == 0);

		// read in the header (54 bytes)
	const int char_size = sizeof(unsigned char);
	fread_s(this->meta_data, 54 * char_size, char_size, 54, *pp);

		// extract the file dimensions
	this->dim_x = *(int*)&meta_data[18];
	this->dim_y = *(int*)&meta_data[22];

		// pad dat shit
	if ((this->dim_x % 4) != 0)
	{
		this->dim_x += 4 - (dim_x % 4);
	}

		// load in the pixel data as charaters
	this->size = 3 * dim_x * dim_y;

		// int method
	//unsigned int* raw_ints = new unsigned int[size];
	//fread_s(raw_ints, char_size * size, char_size, size, *pp);
	//for (int i = 0; i < size; i++)
	//	data.push_back(raw_ints[i]);
			// one delete for every new
	//delete[] raw_ints;



		// char method
	//int8_t * raw_int = new int8_t[size];
	uint8_t * raw_data = new uint8_t[this->size];
	fread_s(raw_data, char_size * this->size, char_size, this->size, *pp);
	this->data_pointer = raw_data;

		// his shit actually works
	/*vector<uint8_t> d;
	d.reserve(size);
	for (int i = 0; i < size; i++)
		d.push_back(raw_data[i]);

	for (int i = 0; i < 1000; i++)
	{
		if (i % 3 == 0) cout << '\n';
		assert(d[i] < 256);
		cout << d[i] << "\t";
	}*/

		// save the data as integers in the array
	//data.reserve(size);
	//for (int i = 0; i < size; i++)
	//	data.push_back(raw_data[i]);
		// one delete for every new
	//delete[] raw_data;
}


void BMP_img::save(string name)
{
		// create output file
	ofstream save_file(name, ios::binary);

		// write the header
	save_file.write((char *)this->meta_data, 54);

		// write the data
	save_file.write((char *)this->data_pointer, this->size);
}

void BMP_img::color_inversion()
{
	for (int i = 0; i < this->size; i++)
	{
		this->data_pointer[i] = (uint8_t)255 - this->data_pointer[i];
	}
}