#include "Header.h"
#include "image.h"


BMP_img::BMP_img(string path)
/*
Called on instantiation, simply loads the image and outputs
the path with dimensions for clarity.

parameters
----------
string path: path to the image to be loaded into memory
*/
{
	this->filename = path;

		// open the file
	FILE *p_file;
	FILE **pp = &p_file;
	int a = fopen_s(pp, path.c_str(), "rb");

	//////////////////////////////////////////
	//cout << "file load successful (0 == yes): " << a << '\n';
	assert(a == 0);

	// read in the header (54 bytes)
	const int char_size = sizeof(unsigned char);
	fread_s(this->meta_data, 54 * char_size, char_size, 54, *pp);

	// extract the file dimensions
	this->dim_x = *(int*)&meta_data[18];
	this->dim_y = *(int*)&meta_data[22];
	this->bit_depth = *(uint8_t*)&meta_data[28]; // Read bit depth for conditional indexing

	// pad readline to be multiple of 4
	if ((this->dim_x % 4) != 0)
		this->dim_x += 4 - (dim_x % 4);

	// load in the pixel data as charaters
	this->size = 3 * dim_x * dim_y;

	// u8int method
	uint8_t * raw_data = new uint8_t[this->size];
	fread_s(raw_data, char_size * this->size, char_size, this->size, *pp);
	this->data_pointer = raw_data;

	// close the file
	fclose(p_file);
	cout << "Loaded from " << path << " BMP with dimensions "
		<< dim_x << " " << dim_y << "\n";
	cout << "Image is " << (int)this->bit_depth << " bit-depth BMP." << "\n";
}


/*
Loads BMP files, reading the memory and separating the meta-data
(54 bytes) and the pixel values, storing the relevant information
and creating an easy to use array for pixel values.

parameters
----------
string path: path to the image to be loaded into memory
*/


void BMP_img::save(string name)
/*
Saves a pixel array as a BMP image, appending the correct
meta-data to the start of the image and writing to a file
in the correct order. If the extension is .dcm, then
conversion also takes place.

parameters
----------
string name: file name to save the image as (target path)

string ext: file extension to append to image file
*/
{
		// get the file extension
	string ext = name.substr(name.length() - 4, name.length());

	if (ext == ".bmp")
	{
			// create output file
		ofstream save_file(name, ios::binary);

			// write the header
		save_file.write((char *)this->meta_data, 54);

			// write the data
		save_file.write((char *)this->data_pointer, this->size);

			// close the stream
		save_file.close();

			// update the filename property
		this->filename = name;
		cout << "\nFile" + name + " created\n";
	}

	else if (ext == ".dcm")
	{
			// temporary bmp save
		this->save("tmp.bmp");

			// path to execultable
		string const converter_path = "\"" + this->abs_direct + "dcmtk\\img2dcm.exe\"";
		string const source_path = "\"" + this->filename + "\"";
		string const target_path = "\"" + name + "\"";

			// Constructing command
		string convert_command = "\"" + converter_path + " -i BMP " + source_path + " " + target_path + "\"";

			// Using system (no pipes needed)
		system(convert_command.c_str());
			
			// delete the temporary save
		remove("tmp.bmp");
		
			// update the filename property
		this->filename = name;
		cout << "\nFile" + name + " created\n";
	}
	else
	{
		cerr << "Extension not recognised";
		_RAISE();
	}
}


int BMP_img::i(int row, int col, int rgb)
/*
Returns the index in memory of the colour channel of
the pixel required, keeping in mind how RGB values 
are conventionally stored in 1-dimension.

parameters
----------
int row: row number of the pixel needed

int col: collumn number of the pixel needed

int rgb: which of the 3 channels needed

returns
-------
int : index of the pixel colour value required
*/
{
		// check pixel exists
	assert(3 > rgb && rgb >= 0);
	assert(this->dim_y > row && row >= 0);
	assert(this->dim_x > col && col >= 0);

	int index;

	// Indexing appropriately for 8 bit vs 24 bit depth images.
	if (this->bit_depth == 8) 
	{
		index = ((row + 3) * this->dim_x) + col;
	}
	else {
		index = ((row * this->dim_x + col) * 3) + rgb;
	}

	return index;

}


	// calls the different filter methods
void BMP_img::filter(string method, uint8_t val)
/*
Wrapper function to decide which filter to apply to the image.

parameters
----------
string method: which method (filter name) to apply and which 
	sub method to apply. 

uint8_t val: 8-bit integer parameter passed to some filters
*/
{
	if (method == "inv")
		this->color_inversion();
	else if (method == "NTSC")
		this->grey_scale("NTSC");
	else if (method == "SA")
		this->grey_scale("SA");
	else if (method == "omni")
		this->convolution_filter("omni");
	else if (method == "di")
		this->convolution_filter("di");
	else if (method == "thresh")
		this->threshold(val);
	else
	{
		cerr << "Method Unknown";
		_RAISE();
	}
}


void BMP_img::color_inversion()
/*
Filter to invert the colour channels of the image. 
Find the modulo-inverse.
*/
{
	for (int i = 0; i < this->dim_y; i++)
		for (int j = 0; j < this->dim_x; j++)
			for (int n = 0; n < 3; n++)
			{
				this->data_pointer[this->i(i, j, n)] = (uint8_t)255 - this->data_pointer[this->i(i, j, n)];
			}
}


void BMP_img::grey_scale(string method)
/*
Finds the weighted average of each colour channel per pixel
and outputs into one channel, simulating a monochrome image.

parameters
----------
string method: which weighting method to use
*/
{
		// set color weights for the method
	float weights[3];

	double rc, bc, gc;
	if (method == "NTSC")
	{
			// NTSC_luminence method
		weights[0] = 0.2989;
		weights[1] = 0.5870;
		weights[2] = 0.1140;
	}
	else if (method == "SA")
	{
			// spectral_average method
		weights[0] = 0.3333;
		weights[1] = 0.3333;
		weights[2] = 0.3333;
	}

	float grey_val;

		// set the new color value
	for (int i = 0; i < this->dim_y; i++) { // row i
		for (int j = 0; j < this->dim_x; j++) {// col j
			grey_val = 0.0f;
			// accumulate the sum of weightings
			for (int n = 0; n < 3; n++)
			{
				grey_val = grey_val + (weights[n] * (int)data_pointer[this->i(i, j, n)]);
			}

			// apply with casting
			grey_val = ceil(grey_val);
			for (int n = 0; n < 3; n++)
			{
				data_pointer[this->i(i, j, n)] = (uint8_t)grey_val;
			}
		}
	}

}


void BMP_img::threshold(uint8_t limit)
/*
Applies a binary threshold to the image, based on the integer
limit provided. Fills in either 255 or 0 to each pixel.

parameters
----------
uint8_t limit: Pixel value to compare other pixels to. The threshold
*/
{
	
	uint8_t pixel_intensity;
	
	for (int i = 0; i < this->dim_y; i++) // row i
		for (int j = 0; j < this->dim_x; j++) //row j
		{
			
			pixel_intensity = this->data_pointer[this->i(i, j, 0)];
			
			// simple binary decision, case by case for pixel
			for (int n = 0; n < 3; n++)
			{
				if (pixel_intensity > limit)
				{
					this->data_pointer[this->i(i, j, n)] = 255;
				}
				else {
					this->data_pointer[this->i(i, j, n)] = 0;
				}
			}
		}

}


void BMP_img::convolution_filter(string method)
/*
Applies a 3x3 convolutional filter to the image, using an 
intermediate array for storing calculated values and then 
scaling back down to 0-255 range into the final array, 
reassining the BMP_img class pointer to the new data.

parameters
----------
string method: which variant of the laplace filter to apply
*/
{
	int * raw_filtered = new int[this->size];

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
				}

	}

	for (int i = 1; i < (this->dim_y - 1); i++) // row i
		for (int j = 1; j < (this->dim_x - 1); j++)  // col j
			for (int n = 0; n < 3; n++)  // color n
			{
				this->data_pointer[this->i(i, j, n)] = (uint8_t)raw_filtered[this->i(i, j, n)];
			}

	//////////////////////// NOTE i removed scaling cuz it just dosent seem to help us over various experiments. two pixels  with 5 bits of colour difference will always have 5 bits of colour difference regardless of how many times they are wrapped aroung in mod 256 space.

}


DICOM_img::DICOM_img(string path)
/* 
Called on instantiation, checks the extension and existence
of the DICOM file, and stores the filename.
*/
{
		// check the file extension is correct
		/////////////// make me better :)
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


void DICOM_img::save(string name)
{
		// path to execultable
	string const converter_path = "\"" + this->abs_direct + "dcmtk\\dcm2pnm.exe\"";
	string const source_path = "\"" + this->filename + "\""; ////////////////// fix me
	string const target_path = "\"" + name + "\"";

		// Constructing command
	string convert_command = "\"" + converter_path + " --write-bmp " + source_path + " " + target_path + "\"";

		// Using system (no pipes needed)
	system(convert_command.c_str());

	cout << "\nFile " + name + " created\n";
}

	// create a BMP_img object (by saving then deleting a file)
void DICOM_img::convert_bmp(BMP_img *&pointer)
{
		// create bmp file
	//const string name = "tmp.bmp";
	//this->save_bmp(name);
	//	
	//	// load as object
	//	// note this has to be deleted later EXTERNALLY!
	//pointer = new BMP_img(name);

	//	// delete file and reset name
	//(*pointer).filename = "";
	//remove(name.c_str());

	//for (int i = 0; i < 12; i++)
	//{
	//	if (i % 3 == 0) cout << '\n';
	//	cout << +(*pointer).data_pointer[i] << "\t";
	//}
	//cout << "daata pointer " << (*pointer).data_pointer << "\n";
}
