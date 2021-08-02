// Code for this file by: David Lawson

#include <vector>
using namespace std;

class BucketSort {

private:

    // Insertion sorts a bucket
    static void insertionSortBucket(vector<vector<float>>& data, bool sortL);

    // Moves pixels into buckets, insertion sorts buckets, & combines them
    static void bucketSort(vector<vector<float>>& pixels, bool sortL);

public:

    // Bucketsorts full img &, for a non-greyscale img, the img columns based on L
    static void masterBucketSort(vector<vector<float>>& pixels, int imgHeight, bool greyscale);

};