#include "Header.h"
#include "image.h"


	// test dicom convert
//int main()
void test_convert()
{
		// take user input to load a file
	string filename;
	cout << "gimme a .dmc file name bruh: ";
	cin >> filename;

		// load dmc image
	DICOM_img dmc(filename);
		// convert to bmp
	BMP_img * img = nullptr;
	dmc.convert_bmp(img);

		// print first 33 pixles
	for (int i = 0; i < 12; i++)
	{
		if (i % 3 == 0) cout << '\n';
		cout << +(*img).data_pointer[i] << "\t";
	}

		// apply filters
	(*img).grey_scale("SA");
	//(*img).convolution_filter("omni");

		// print first 33 pixles
	//for (int i = 0; i < 99; i++)
	//{
	//	if (i % 3 == 0) cout << '\n';
	//	cout << +img.data_pointer[i] << "\t";
	//}

		// save & pause
	(*img).save_bmp("test_new_class.bmp");

	delete img;
	system("pause");
}



	// test bmp load and filter
void test_bmp()
{
		// take user input to load a file
	string filename;
	cout << "gimme a .bmp file name bruh: ";
	cin >> filename;

		// create the bmp image
	BMP_img img(filename);

		// apply the filters
	img.grey_scale("NTSC");
	img.convolution_filter("omni");

		// save the file
	cout << "gimme a target file name bruh: ";
	cin >> filename;
	img.save_bmp(filename);
}


	// test loading a DICOM and saving a BMP
void test_dicom()
{
		// take user input to load a file
	string filename;
	cout << "gimme a .dmc file name bruh: ";
	cin >> filename;

		// load dmc image
	DICOM_img dmc(filename);

		// take user input to load a file
	cout << "gimme a target bruh: ";
	cin >> filename;

		// save as bmp
	dmc.save_bmp(filename);
}