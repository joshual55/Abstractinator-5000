// Code for this file by: David Lawson

#include "BucketSort.h"	

// Insertion sorts a bucket
void BucketSort::insertionSortBucket(vector<vector<float>>& data, bool sortL) {
    int k = 0;
    if (sortL)
        k = 2;
    
    // Cur pixel
    vector<float> key;

    // Index to traverse sorted portion
    int j;

    // For each pixel to be sorted
    for (int i = 1; i < data.size(); i++) {
        key = data[i];
        j = i - 1;

        // While sorted pixel is greater than cur pixel
        while (j >= 0 && data[j][k] > key[k])
        {
            // Shift cur pixel over & move to smaller sorted pixel
            data[j + 1] = data[j];
            j--;
        }

        // Add cur pixel to sorted pixels
        data[j + 1] = key;
    }
}





// Moves pixels into buckets, insertion sorts buckets, & combines them
void BucketSort::bucketSort(vector<vector<float>>& pixels, bool sortL) {
    int k = 0;
    if (sortL)
        k = 2;

    // Creates n buckets to put the pixels into
    int n = pixels.size();
    vector<vector<vector<float>>> buckets(n);

    // Finds max pixel val
    float max = pixels[0][k];
    for (int i = 0; i < n; i++) {
        if (pixels[i][k] > max)
            max = pixels[i][k];
    }

    // Puts each pixel into a bucket
    for (int i = 0; i < n; i++) {
        int index = (n - 1) * pixels[i][k] / max;
        buckets[index].push_back(pixels[i]);
    }

    // Insertion sorts each bucket
    for (int i = 0; i < n; i++)
        insertionSortBucket(buckets[i], sortL);

    // Combines the sorted buckets
    int ind = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            pixels[ind] = buckets[i][j];
            ind++;
        }
    }
}





// Bucketsorts full img &, for a non-greyscale img, the img columns based on L
void BucketSort::masterBucketSort(vector<vector<float>>& pixels, int imgHeight, bool greyscale) {
    
    // Call bucketSort on whole image
    bucketSort(pixels, false);

    // If image is not greyscale
    if (!greyscale) {
        vector<vector<float>> column(imgHeight, vector<float>(3,(float)0));

        // For each column
        for (int i = 0; i < pixels.size() - 1; i+= imgHeight) {

            // Pull column out, call bucketSort, push new column back in
            for (int j = i; j < i + imgHeight; j++) {
                column[j-i] = pixels[j];
            }
            bucketSort(column, true);
            for (int j = i; j < i + imgHeight; j++) {
                pixels[j] = column[j-i];
            }
        }
    }
}