// Code for this file by: Joshua Lamb

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ImageTimSort {

private:

    // Insertion sort over subgroup of timsort
    static void insertionSort(vector<vector<float>>& pixels, int start, int end, bool greyscale, bool sortL);

    // Merge sort over 2 subgroups of timsort
    static void mergeSort(vector<vector<float>>& pixels, int start, int mid, int end, bool greyscale, bool sortL);

    // Timsort over specific pixel vector region, combining insertion & merge sort
    static void timSort(vector<vector<float>>& pixels, int start, int end, bool greyscale, bool sortL);

public:

    // Timsorts the full img &, for a non-greysale img, the img columns based on L
    static void masterTimSort(vector<vector<float>>& pixels, int imgHeight, bool greyscale);

};