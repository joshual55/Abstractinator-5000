// Code for this file by: Michael Kruse

#include "CImg.h"
#include <string>
#include <vector>
using namespace cimg_library;
using namespace std;

class Image {

private:

	int width;
	int height;
	bool greyscale;
	CImg<float> src;
	CImg<float> result; 
	CImg<float> output;
	vector<vector<float>> pixels;

	// Called by constructor to initialize & fill pixels vector & convert vals to HSL if img is in color
	void SetPixels();

	// Called by SetPixels to check greyscale for potentially converting to HSL
	bool CheckIfGrey();

public:

	// Constructor for setting height, width, src, reuslt, output, & calling setPixels
	Image(string filename);

	int GetHeight();
	int GetWidth();
	bool GetGreyscale();
	vector<vector<float>>& GetPixels();

	// Converts img (NOT PIXELS VECTOR, BUT CIMG OBJECT) to RGB, "src" to convert inputted img, "result" to convert outputted img
	void toRGB(string img);
	// Same as above
	void toHSL(string img);

	// Displays img in window
	void DisplayImage();

};