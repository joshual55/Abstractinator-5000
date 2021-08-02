// Code for this file by: Michael Kruse & Joshua Lamb

#include <iostream>
#include <fstream>
#include <chrono>
#include "Image.h"
#include "TimSort.h"
#include "BucketSort.h"

int main() {

    cout << "\n---------- Welcome to the Abstractinator 5000! ----------\n";
    cout << "Make sure you move any images to the images folder.\n\n";
    cout << "Note: Using this program with jpgs requires ImageMagick. The windows download is found at . . .\n";
    cout << "https://download.imagemagick.org/ImageMagick/download/binaries/ImageMagick-7.1.0-4-Q16-HDRI-x64-dll.exe\n\n";

    string option = "-1";
    while (option != "0") {

        cout << "\nWould you like to exit (0) or sort an image via timsort (1) or bucket sort (2)?\n";
        cin >> option;

        // Error prevention for wrong option inputs
	    while (option != "0" && option != "1" && option != "2") {
		    cout << "\nOption does not exist. Please input a valid integer.\n";
		    cin >> option;
	    }

        if (option != "0") {
            cout << "\nWhat is the name of the file you want to sort (no extensions)?\n";
            string filename;
            cin >> filename;
            filename = "images/" + filename + ".jpg";

            // Error prevention for wrong file inputs
            fstream file(filename);
	        while (file.fail()) {
		        cout << "\nFile does not exist. Please input a valid file name.\n";
		        cin >> filename;
		        filename = "images/" + filename + ".jpg";
		        file.open(filename.c_str());
	        }
	        file.close();

            // Constructor that sets input/output images & creates HSL (color) or RGB (greyscale) pixel vector
	        Image img(filename);

            // Times & calls correct sorting function
            auto startTime = chrono::high_resolution_clock::now();
            if (option == "1")
                ImageTimSort::masterTimSort(img.GetPixels(), img.GetHeight(), img.GetGreyscale());
            else 
                BucketSort::masterBucketSort(img.GetPixels(), img.GetHeight(), img.GetGreyscale());
            auto endTime = chrono::high_resolution_clock::now();
	        auto timeElapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);

            cout << "\nSorting complete in " << timeElapsed.count() << "ms.\n\n";
            img.DisplayImage();
        }
    }

    return 0;
}
