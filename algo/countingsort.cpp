/*
 * Counting sort:
 * Sort range quickly at cost of space
 * N elements, range of M
 * Time complexity : O(N+M) (avg, best, worst)
 * Space complexity : O(N+M)
 *
 * 1) create array with size M+1 and compute a prefix sum of number of occurences
 * 2) iterate backwards through input array and place in appropriate location in output array
 */

/*
 * Tutorial: https://www.geeksforgeeks.org/counting-sort/
 * Problem: https://leetcode.com/problems/kth-largest-element-in-an-array
 */

/*
 * MISC
 * Advantages:
 * - Stable
 * - Faster than merge
 *
 * Disadvantages:
 * - Doesn't work for decimal vals/strings
 * - Slow for large ranges
 */
#include <vector>
#include <iostream>

using namespace std;

vector<int> countSort(vector<int> &inputArray) {

    int N = inputArray.size();

    // Finding the maximum element of array inputArray[].
    int M = 0;

    for (int i = 0; i < N; i++)
        M = max(M, inputArray[i]);

    // Initializing countArray[] with 0
    vector<int> countArray(M + 1, 0);

    // Mapping each element of inputArray[] as an index
    // of countArray[] array

    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;

    // Calculating prefix sum at every index
    // of array countArray[]
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];

    // Creating outputArray[] from countArray[] array
    vector<int> outputArray(N);

    for (int i = N - 1; i >= 0; i--) {
        outputArray[countArray[inputArray[i]] - 1]
                = inputArray[i];

        countArray[inputArray[i]]--;
    }

    return outputArray;
}

// Driver code
int main() {

    // Input array
    vector<int> inputArray = {4, 3, 12, 1, 5, 5, 3, 9};

    // Output array
    vector<int> outputArray = countSort(inputArray);

    for (int i = 0; i < inputArray.size(); i++)
        cout << outputArray[i] << " ";

    return 0;
}

