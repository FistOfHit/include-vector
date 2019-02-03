#include <iostream>
#include <string>
#include <vector>
#include "image_creator.h"


using namespace std;

/* 


*/
int **decolorise(int **red_array, int **green_array, int **blue_array,
				 int width, int height, string method = "NTSC_luminence") {


	// Initialise empty image storage
	int **empty_image = create_image<int>(width, height);


	// Official NTSC scaling to convert RGB to effective luminence
	if (method == "NTSC_luminence") {

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				empty_image[i][j] = (int)ceil(0.2989f * red_array[i][j] +
											  0.5870f * blue_array[i][j] +
											  0.1140f * green_array[i][j]);
			};
		};

		return empty_image;

	};


	// Assign each pixel's RGB as the average of R, G and B channels
	if (method == "spectral_average") {

		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				empty_image[i][j] = (int)ceil(0.3333f * red_array[i][j] +
											  0.3333f * blue_array[i][j] +
											  0.3333f * green_array[i][j]);
			};
		};

		return empty_image;

	};


};


int **invert_greyscale(int **greyscale_image, int width, int height) {







};



int main() {





};