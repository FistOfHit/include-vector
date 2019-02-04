#include "Header.h"
#include "image.h"

	// test loading an image file
int main()
{
	
	string filename;
	cout << "gimme a file name bruh: ";
	cin >> filename;

	BMP_img img(filename);

	for (int i = 0; i < 999; i++)
	{
		if (i % 3 == 0) cout << '\n';
		cout << +img.data_pointer[i] << "\t";
	}

	img.color_inversion();

	img.save("test.bmp");

	system("pause");
}