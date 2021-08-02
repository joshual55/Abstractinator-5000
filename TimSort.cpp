// Code for this file by: Joshua Lamb

#include "TimSort.h"

// Insertion sort over subgroup of timsort
void ImageTimSort::insertionSort(vector<vector<float>>& pixels, int start, int end, bool greyscale, bool sortL) {

    // For each pixel in the bounds
    for (int i = start + 1; i < end + 1; i++) {

        // Current pixel vector
        vector<float> curPixel = pixels[i];

        // Index to traverse sorted portion
        int j = i - 1;

        // Index for which pixel val to compare based on sortL
        int k = 0;
        if (sortL)
            k = 2;

        // While sorted pixel is greater than cur pixel
        while (j >= start && pixels[j][k] > curPixel[k]) {
            
            // Shift sorted pixel vals over
            pixels[j + 1][k] = pixels[j][k];
            if (!greyscale) {
                pixels[j + 1][1] = pixels[j][1];
                if (k == 0)
                    pixels[j + 1][2] = pixels[j][2];
                else
                    pixels[j + 1][0] = pixels[j][0];
            }

            // Move to smaller sorted pixel
            j--;
        }

        // Add cur pixel to sorted pixels
        pixels[j + 1][k] = curPixel[k];
        if (!greyscale) {
            pixels[j + 1][1] = curPixel[1];
            if (k == 0)
                pixels[j + 1][2] = curPixel[2];
            else
                pixels[j + 1][0] = curPixel[0];
            
        }
    }
}





// Merge sort over subgroups of timsort
void ImageTimSort::mergeSort(vector<vector<float>>& pixels, int start, int mid, int end, bool greyscale, bool sortL) {

    // Length of left and right groups
    int lGroupSize = mid - start + 1;
    int rGroupSize = end - mid;

    // Two containers to split the groups
    vector<vector<float>> lGroup(lGroupSize, vector<float>(3, 0));
    vector<vector<float>> rGroup(rGroupSize, vector<float>(3, 0));

    // Fill the containers
    for (int i = 0; i < lGroupSize; i++)
        lGroup[i] = pixels[start + i];
    for (int i = 0; i < rGroupSize; i++)
        rGroup[i] = pixels[mid + 1 + i];

    // Indices for traversing the split groups & original pixels vector
    int lGroupIndex = 0;
    int rGroupIndex = 0;
    int pixelsIndex = start;

    // Index for which pixel val to compare based on sortL
    int k = 0;
    if (sortL)
        k = 2;

    // Traverse until one group hits the end
    while (lGroupIndex < lGroupSize && rGroupIndex < rGroupSize) {

        // If left group val is smaller than right group val
        if (lGroup[lGroupIndex][k] <= rGroup[rGroupIndex][k]) {

            // Add left group pixel vals to sorted pixels & iterate lGroupIndex
            pixels[pixelsIndex][k] = lGroup[lGroupIndex][k];
            if (!greyscale) {
                pixels[pixelsIndex][1] = lGroup[lGroupIndex][1];
                if (k == 0) 
                    pixels[pixelsIndex][2] = lGroup[lGroupIndex][2];
                else 
                    pixels[pixelsIndex][0] = lGroup[lGroupIndex][0];
            }
            lGroupIndex++;
        // Else (right group val is smaller than left group val)
        } else {

            // Add right group pixel to sorted pixels & iterate rGroupIndex
            pixels[pixelsIndex][k] = rGroup[rGroupIndex][k];
            if (!greyscale) {
                pixels[pixelsIndex][1] = rGroup[rGroupIndex][1];
                if (k == 0) 
                    pixels[pixelsIndex][2] = rGroup[rGroupIndex][2];
                else 
                    pixels[pixelsIndex][0] = rGroup[rGroupIndex][0];
            }
            rGroupIndex++;
        }
        pixelsIndex++;
    }


    // Copy the rest of the values from the untraversed group
    while (lGroupIndex < lGroupSize || rGroupIndex < rGroupSize) {
        
        // If it is left group, copy left group pixel vals over & iterate lGroupIndex
        if (lGroupIndex < lGroupSize) {
            pixels[pixelsIndex][k] = lGroup[lGroupIndex][k];
            if (!greyscale) {
                pixels[pixelsIndex][1] = lGroup[lGroupIndex][1];
                if (k == 0) 
                    pixels[pixelsIndex][2] = lGroup[lGroupIndex][2];
                else 
                    pixels[pixelsIndex][0] = lGroup[lGroupIndex][0];
            }
            lGroupIndex++;
        // Else (it is right group) copy right group pixel vals over & iterate rGroupIndex
        } else {
            pixels[pixelsIndex][k] = rGroup[rGroupIndex][k];
            if (!greyscale) {
                pixels[pixelsIndex][1] = rGroup[rGroupIndex][1];
                if (k == 0) 
                    pixels[pixelsIndex][2] = rGroup[rGroupIndex][2];
                else 
                    pixels[pixelsIndex][0] = rGroup[rGroupIndex][0];
            }
            rGroupIndex++;
        }
        pixelsIndex++;
    }
}





// Timsort over specific pixel vector region, combining insertion & merge sort
void ImageTimSort::timSort(vector<vector<float>>& pixels, int start, int end, bool greyscale, bool sortL) {

    // Arbitrary starting group size (SHOULD BE SMALLER THAN NUM OF PIXELS IN THE REGION)
    int SIZE = 32;

    // For each group of SIZE pixels (or up to last pixel in region), insertion sort the group
    for (int i = start; i < end; i += SIZE)
        insertionSort(pixels, i, min((SIZE + i - 1), end), greyscale, sortL);

    // Start merging groups of SIZE, then 2*SIZE, up to a merge of all pixels in region
    for (int mergeSize = SIZE; mergeSize < (end - start + 1); mergeSize *= 2) {

        // For each pair of groups to be merged
        for (int mStart = start; mStart < end; mStart += 2 * mergeSize) {

            // Get middle of groups & last index of right group (or last pixel in region)
            int mMid = min((mStart + mergeSize - 1), end);
            int mEnd = min((mStart + 2 * mergeSize - 1), end);

            // Merge the groups
            mergeSort(pixels, mStart, mMid, mEnd, greyscale, sortL);
        }
    }
}





// Timsorts the full img &, for a non-greysale img, the img columns based on L
void ImageTimSort::masterTimSort(vector<vector<float>>& pixels, int imgHeight, bool greyscale) {
    int numPixels = pixels.size();

    // Call timSort on the whole image
    timSort(pixels, 0, (numPixels - 1), greyscale, false);

    // If img isn't greyscale, call timSort on each column w/ sortL as true
    if (!greyscale) {
        for (int i = 0; i < numPixels; i += imgHeight)
            timSort(pixels, i, (i + imgHeight - 1), greyscale, true);
    }
}
