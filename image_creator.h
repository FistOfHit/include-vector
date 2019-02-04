#pragma once


/* Template for pointer to a pointer to a 2D array of 
	specified width (rows) and height (collumns). 

	Notes:
	------
	REMEMBER TO DEALLOCATE (DELETE).

	Parameters:
	-----------
	int width: width of image (number of rows)

	int height: height of image (number of collumns)

	Returns:
	--------
	int	*image: (pointer to) 2D array filled with 0's
*/
template<typename T>
T **create_image(int width, int height) {

	// allocate 2D array
	T **image = new T[width][height];

	// Fill with 0s in both dimensions
	for (int i = 0; i < width; i++) {
		fill(image[i], image[i] + height, 0);
	}

	return image;

}
