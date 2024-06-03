//TODO
/*
 * Quickselect/Hoare's algorithm:
 * Find kth largest element in unordered list
 * N = size of list
 * Time complexity : O(N) avg, O(N^2) worst
 * Space complexity : O(1)
 *
 * 1) Choose (random if you want really want to avoid O(N^2)) pivot in array
 * 2) Partition relative to pivot into greater, mid, less.
 * 3)
 */

/*
 * Tutorial: https://www.geeksforgeeks.org/quickselect-algorithm/
 * Problem: https://leetcode.com/problems/kth-largest-element-in-an-array
 */

#include <vector>
#include <iostream>

using namespace std;

int kthSmallest(int arr[], int lo, int hi, int k) {
    if (hi == lo) return arr[lo];
    int pivot = (lo + rand() % (hi - lo + 1));
    int midNum = arr[pivot];

    //Partitioning
    for (int i = lo; i <= hi; i++) {
        for (int j = lo; j <= hi; j++) {
            cout << arr[j] << " ";
        }
        cout << endl;
        if (i <= pivot && arr[i] > midNum) {
            swap(arr[i], arr[pivot]);
            pivot = i;
        } else if (i > pivot && arr[i] <= midNum) {
            swap(arr[pivot], arr[pivot + 1]);
            if (i != pivot + 1) swap(arr[i], arr[pivot]);
            pivot++;
        }

    }

    int left = pivot - lo + 1;
    if (k == left) return arr[pivot];
    if (left >= k) {
        return kthSmallest(arr, lo, pivot, k);
    } else {
        return kthSmallest(arr, pivot + 1, hi, k - left);
    }
}

int main() {
    int arr[] = {10, 4, 5, 8, 6, 11, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    cout << "K-th smallest element is "
         << kthSmallest(arr, 0, n - 1, k);
    return 0;
}