#include "Header.h"
#include "image.h"

	// test loading an image file
int main()
{
	
	string filename;
	cout << "gimme a file name bruh: ";
	cin >> filename;

	BMP_img img(filename);

	for (int i = 0; i < 99; i++)
	{
		if (i % 3 == 0) cout << '\n';
		cout << +img.data_pointer[i] << "\t";
	}

	img.grey_scale("NTSC");
	img.convolution_filter("omni");

	for (int i = 0; i < 99; i++)
	{
		if (i % 3 == 0) cout << '\n';
		cout << +img.data_pointer[i] << "\t";
	}

	img.save("test_conv.bmp");

	system("pause");
}
