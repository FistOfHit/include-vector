#include <iostream>
#include <string>
#include <vector>
#include "image_creator.h"


using namespace std;


/* Converts RGB image to greyscale via two methods.

	Notes
	-----
	Creates array using template, dynamically assigns memory but be 
	sure to delete it later! 

	Uses two methods, each just mapping the RGB channels into 
	one (A^3 -> A where A = {x in N: 0 <= x <= 255}), then 
	the image can be created by writing this one new channel
	into all 3 of the R, G and B channels in a BMP, PNG, JPG etc.

	Takes pointer-pointers to 2D arrays and returns a 
	pointer-pointer.

	Parameters
	----------
	int **red_array: pointer-pointer to red channel from original image
		Limits = 0 to 255

	int **green_array: pointer-pointer to green channel from original image
		Limits = 0 to 255

	int **blue_array: pointer-pointer to blue channel from original image
		Limits = 0 to 255

	int width: Horizontal number of pixels in image
		Limits = 0 and greater

	int height: Vertical number of pixels in image
		Limits = 0 and greater

	string method: Method to be used for conversion
		Default = "NTSC_luminence"
		Limits = "NTSC_luminence", "spectral_average"

	Returns
	-------
	int **greyscale_image: output 2D array of intensity values,
		to be used as all 3 channels in final output image.
		Limits = 0 and greater
*/
int **decolorise_image(int **red_array, int **green_array, int **blue_array,
				 int width, int height, string method = "NTSC_luminence") {


	// Error handling
	if (width <= 0 || height <= 0) {

		cerr << "Invalid values for dimensions,";
		cerr << "width and height must be greater than 0" << endl;

	};
	if (method != "NTSC_luminence" && method != "spectral_average") {

		cerr << "Invalid value for method,";
		cerr << "method must be either NTSC_luminence or";
		cerr << "spectral_average" << endl;

	};


	// Initialise empty image storage
	int **greyscale_image = create_image<int>(width, height);


	// Official NTSC scaling to convert RGB to effective luminence
	if (method == "NTSC_luminence") {

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {

				greyscale_image[i][j] = (int)ceil(0.2989f * red_array[i][j] +
												  0.5870f * blue_array[i][j] +
												  0.1140f * green_array[i][j]);

			};
		};

		return greyscale_image;


	// Assign each pixel's RGB as the average of R, G and B channels
	} else if (method == "spectral_average") {

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {

				greyscale_image[i][j] = (int)ceil(0.3333f * red_array[i][j] +
												  0.3333f * blue_array[i][j] +
												  0.3333f * green_array[i][j]);

			};
		};

		return greyscale_image;

	};


};


/* Inverts intensity values of greyscale image, in-place.

	Notes
	-----
	Performs in place inversion of intensity pixel-by-pixel.
	Image in memory will be inverted, but can just call twice
	to perfectly restore original image.

	Parameters
	----------
	int **greyscale_image: pointer-pointer to 2D array of 
		intensity values
		Limits = 0 <= x <= 255

	int width: Horizontal number of pixels in image
		Limits = 0 and greater

	int height: Vertical number of pixels in image
		Limits = 0 and greater

	Returns
	-------
	None
*/
void **invert_greyscale(int **greyscale_image, int width, int height) {


	// Error handling
	if (width <= 0 || height <= 0) {

		cerr << "Invalid values for dimensions,";
		cerr << "width and height must be greater than 0" << endl;

	};


	// Subtract intensity from 255, reversing it
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			greyscale_image[i][j] = 255 - greyscale_image[i][j];
		};
	};


};


/* Applies variants of the Laplace filter to single
	colour-channel image

	Notes
	-----
	Applies one of two filters: 
	- Omni-directional filter, which enhances edges
	in all orientations, and possibly more strongly,
	but takes roughly twice the time to run with twice
	as many calculations.
	- Bi-directional fitler, which enhances edges
	mostly horizontal+vertical orientations, with
	limited performance for edges oriented off these
	directions, but has only half as many calculations.

	Parameters
	----------
	int **image: pointer-pointer to 2D array of
		intensity values
		Limits = 0 <= x <= 255

	int width: Horizontal number of pixels in image
		Limits = 0 or greater

	int height: Vertical number of pixels in image
		Limits = 0 or greater

	string method: Type of filter to be used
		Default = "omni-directional"
		Limits = "omni-directional" or "bi-directional"

	Returns
	-------
	int **filtered_image: pointer-pointer to 2D array
		representing single_channel of greyscale,
		filtered image.
		Limits = 0 <= x <= 255
*/
int **apply_filter(int **image, int width, int height,
				   string filter_type = "omni-directional") {


	// Error handling
	if (width <= 0 || height <= 0) {

		cerr << "Invalid values for dimensions,";
		cerr << "width and height must be greater than 0" << endl;
		return;

	};


	// Initialise empty image storage
	int **filtered_image = create_image<int>(width, height);


	// Applying filter and error handling
	// For edge-enhancement in all directions
	if (filter_type == "omni-directional") {

		for (int i = 0; i < (width - 1); i++) {
			for (int j = 0; j < (height - 1); j++) {

				filtered_image[i][j] = -1 * image[0][0] +
									   -1 * image[0][1] + 
									   -1 * image[0][2] +
									   -1 * image[1][0] +
										8 * image[1][1] +
									   -1 * image[1][2] +
									   -1 * image[2][0] +
									   -1 * image[2][1] +
									   -1 * image[2][2];

			};
		};
	

	// For edge-enchancement in 2 directions:
	// (left-right + up-down)
	} else if (filter_type == "bi-directional") {
		
		for (int i = 0; i < (width - 1); i++) {
			for (int j = 0; j < (height - 1); j++) {

				filtered_image[i][j] = -1 * image[0][1] +
									   -1 * image[1][0] +
										4 * image[1][1] +
									   -1 * image[1][2] +
									   -1 * image[2][1];

			};
		};


	// Error handling
	} else {

		cerr << "Invalid value for method,";
		cerr << "method must be either omni-directional or";
		cerr << "bi-directional" << endl;
		return;

	};
	

	return filtered_image;


}


int main() {





};