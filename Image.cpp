// Code for this file by: Michael Kruse

#include "Image.h"

// Called by constructor to initialize & fill pixels vector & convert vals to HSL if img is in color
void Image::SetPixels() {
	pixels = vector<vector<float>>(GetWidth() * GetHeight(), vector<float>(3, 0));
	greyscale = CheckIfGrey();

	if (!GetGreyscale())
		toHSL("src");

	int k = 0;
	for (int i = 0; i < GetWidth(); i++) {
		for (int j = 0; j < GetHeight(); j++) {
			pixels[k][0] = src(i, j, 0);
			if (!GetGreyscale()) {
				pixels[k][1] = src(i, j, 1);
				pixels[k][2] = src(i, j, 2);
			}
			k++;
		}
	}
	
	if (!GetGreyscale())
		toRGB("src");
}





// Called by SetPixels to check greyscale for potentially converting to HSL
bool Image::CheckIfGrey() {
	if (src.spectrum() == 1)
		return true;
	return false;
} 





// Constructor for setting height, width, src, reuslt, output, & calling setPixels
Image::Image(string filename) {
	src = CImg<float>(filename.c_str());
	height = src.height();
	width = src.width();
	result.assign(src);
	output = CImg<float>(width * 2, height, 1, 3);
	SetPixels();
}





int Image::GetHeight() {
	return height;
}

int Image::GetWidth() {
	return width;
}

bool Image::GetGreyscale() {
	return greyscale;
}

vector<vector<float>>& Image::GetPixels() {
    return pixels;
}




// Converts img (NOT PIXELS VECTOR, BUT CIMG OBJECT) to RGB, "src" to convert inputted img, "result" to convert outputted img
void Image::toRGB(string img) {
	if (img == "src")
		src.HSLtoRGB();
	else if (img == "result")
		result.HSLtoRGB();
}
// Same as above
void Image::toHSL(string img) {
	if (img == "src")
		src.RGBtoHSL();
	else if (img == "result")
		result.RGBtoHSL();
}





// Displays img in window
void Image::DisplayImage() {

	// Put pixels vector into resultant image
	int k = 0;
	for (int i = 0; i < GetWidth(); i++) {
		for (int j = 0; j < GetHeight(); j++) {
			result(i, j, 0) = pixels[k][0];
			if (!GetGreyscale()) {
				result(i, j, 1) = pixels[k][1];
				result(i, j, 2) = pixels[k][2];
			}
			k++;
		}
	}

	// Convert non-greyscale img from HSL back to RGB
	if (!GetGreyscale())
		toRGB("result");

	// Dislay img
	output = src.append(result, 'x');
	output.display("Image");
}