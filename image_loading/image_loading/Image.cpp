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

		// pad readline to be multiple of 4
	if ((this->dim_x % 4) != 0)
		this->dim_x += 4 - (dim_x % 4);

		// load in the pixel data as charaters
	this->size = 3 * dim_x * dim_y;

		// u8int method
	uint8_t * raw_data = new uint8_t[this->size];
	fread_s(raw_data, char_size * this->size, char_size, this->size, *pp);
	this->data_pointer = raw_data;

}


void BMP_img::save_bmp(string name)
{
		// create output file
	ofstream save_file(name, ios::binary);

		// write the header
	save_file.write((char *)this->meta_data, 54);

		// write the data
	save_file.write((char *)this->data_pointer, this->size);

		// update the filename property
	this->filename = name;
}


int BMP_img::i(int row, int col, int rgb)
	// get pixle 1D value
{
		// check pixle exists
	assert(3 > rgb && rgb >= 0);
	assert(this->dim_y > row && row >= 0);
	assert(this->dim_x > col && col >= 0);

	return (int)(((row * this->dim_x + col) * 3) + rgb);
}


void BMP_img::color_inversion()
{
	for (int i = 0; i < this->size; i++)
		this->data_pointer[i] = (uint8_t)255 - this->data_pointer[i];
}


void BMP_img::grey_scale(string method)
{
		// set color constants for the method
	double rc, bc, gc;
	if (method == "NTSC")
	{
			// NTSC_luminence method
		rc = 0.2989;
		bc = 0.5870;
		gc = 0.1140;
	}
	else if (method == "SA")
	{
			// spectral_average method
		rc = 0.3333;
		bc = 0.3333;
		gc = 0.3333;
	}
	else
	{	
		cerr << "Greyscaling method Unknown";
		_RAISE();
	}

		// set the new color value
	for (int i = 0; i < this->dim_y; i++) // row i
		for (int j = 0; j < this->dim_x; j++) // col j
		{
				// find the new value
			int index  = this->i(i, j, 0);
			const int grey_val = (uint8_t)ceil(rc * data_pointer[index] + // red
												gc * data_pointer[index + 1] + // green
												bc * data_pointer[index + 2]); // blue
				// set it for all colors
			this->data_pointer[index] = grey_val;
			this->data_pointer[index + 1] = grey_val;
			this->data_pointer[index + 2] = grey_val;
		}
}


void BMP_img::convolution_filter(string method)
{
	float * raw_filtered = new float[this->size];
	uint8_t * scaled_filtered = new uint8_t[this->size];

	float min_intensity = 0;
	float max_intensity = 0;

		// omni-directional method
	if (method == "omni") {

		for (int i = 1; i < (this->dim_y - 1); i++) // row i
			for (int j = 1; j < (this->dim_x - 1); j++)  // col j
				for (int n = 0; n < 3; n++)  // color n
				{
					// Apply filter to each pixel (in new memory)
					raw_filtered[this->i(i, j, n)] = -1 * this->data_pointer[this->i(i-1, j-1, n)] +
												 	 -1 * this->data_pointer[this->i(i-1, j,   n)] +
													 -1 * this->data_pointer[this->i(i-1, j+1, n)] +
													 -1 * this->data_pointer[this->i(i  , j-1, n)] +
													  8 * this->data_pointer[this->i(i  , j  , n)] +
													 -1 * this->data_pointer[this->i(i  , j+1, n)] +
													 -1 * this->data_pointer[this->i(i+1, j-1, n)] +
													 -1 * this->data_pointer[this->i(i+1, j  , n)] +
													 -1 * this->data_pointer[this->i(i+1, j+1, n)];

					// find min and max intensities after raw filtered data
					min_intensity= min(raw_filtered[this->i(i, j, n)], min_intensity);
					max_intensity = max(raw_filtered[this->i(i, j, n)], max_intensity);

				}

	} else if (method == "bi") {

		for (int i = 1; i < (this->dim_y - 1); i++) // row i
			for (int j = 1; j < (this->dim_x - 1); j++)  // col j
				for (int n = 0; n < 3; n++)  // color n
				{
					// Apply filter to each pixel (in new memory)
					raw_filtered[this->i(i, j, n)] = -1 * this->data_pointer[this->i(i-1, j,   n)] +
													 -1 * this->data_pointer[this->i(i  , j-1, n)] +
													  4 * this->data_pointer[this->i(i  , j,   n)] +
													 -1 * this->data_pointer[this->i(i  , j+1, n)] +
													 -1 * this->data_pointer[this->i(i+1, j,   n)];

					// find min and max intensities after raw filtered data
					min_intensity = min(raw_filtered[this->i(i, j, n)], min_intensity);
					max_intensity = max(raw_filtered[this->i(i, j, n)], max_intensity);

				}

	} else {

		cerr << "Filtering method Unknown";
		_RAISE();

	}

	// Scaling intensities onto an 8-bit unsigned data-type 
	for (int i = 1; i < (this->dim_y - 1); i++) // row i
		for (int j = 1; j < (this->dim_x - 1); j++)  // col j
			for (int n = 0; n < 3; n++)  // color n
			{
				raw_filtered[this->i(i, j, n)] = (raw_filtered[this->i(i, j, n)] - min_intensity) *
					(255.0f / max_intensity);
				scaled_filtered[this->i(i, j, n)] = (uint8_t)raw_filtered[this->i(i, j, n)];
			}

	delete[] this->data_pointer;
	this->data_pointer = scaled_filtered;
	
}


	// create a .dcm file
void BMP_img::save_dcm(string name)
{

	// Read single line from file created by setup.bat
	ifstream path_file("current_path.txt");
	string current_path;
	if (path_file.is_open())
	{
		getline(path_file, current_path);
		path_file.close();
		cout << current_path;
	}
	else {
		cerr << "Please run setup.bat before proceeding.";
		_RAISE();
	}


	// path to execultable
	string const converter_path = current_path + "/dcmtk/img2dcm.exe ";

	// Constructing command
	string convert_command = converter_path + "-i BMP " + this->filename + " " + name;

	// Using system (no pipes needed)
	system(convert_command.c_str());

	cout << "\nFile" + name + " created\n";
}


DICOM_img::DICOM_img(string path)
{
		// check the file extension is correct
	char * ptr = &path.back();
	if (*(ptr - 2) != 'd' || *(ptr - 1) != 'c' || *(ptr) != 'm')
	{
		cerr << "file extenion must be '.dcm'";
		_RAISE();
	}

		// check the file exists
	ifstream f(path.c_str());
	if (!f.good())
	{
		cerr << "could not find file: " + path;
		_RAISE();
	}

		// save the file name for function call
	this->filename = path;
}

	// create a .bmp file
void DICOM_img::save_bmp(string name)
{

		// Read single line from file created by setup.bat
	ifstream path_file("current_path.txt");
	string current_path;
	if (path_file.is_open()) 
	{
		getline(path_file, current_path);
		path_file.close();
		cout << current_path;
	} else { 
		cerr << "Please run setup.bat before proceeding.";
		_RAISE();
	}


		// path to execultable
	string const converter_path = current_path + "/dcmtk/dcmj2pnm.exe ";

		// Constructing command
	string convert_command = converter_path + "--write-bmp " + this->filename + " " + name;

		// Using system (no pipes needed)
	system(convert_command.c_str());

	cout << "\nFile" + name + " created\n";
}

	// create a BMP_img object (by saving then deleting a file)
void DICOM_img::convert_bmp(BMP_img *&pointer)
{
		// create bmp file
	const string name = "tmp.bmp";
	this->save_bmp(name);
		
		// load as object
		// note this has to be deleted later EXTERNALLY!
	pointer = new BMP_img(name);

		// delete file and reset name
	(*pointer).filename = "";
	remove(name.c_str());

	for (int i = 0; i < 12; i++)
	{
		if (i % 3 == 0) cout << '\n';
		cout << +(*pointer).data_pointer[i] << "\t";
	}
	cout << "daata pointer " << (*pointer).data_pointer << "\n";
}
