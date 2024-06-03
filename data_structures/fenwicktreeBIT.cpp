/*
 * Fenwick Tree/Binary Index Tree/BIT
 * Given f, a binary, associative operation (e.g +, |, ^)
 * - calculates value of f over [l, r] in O(logN)
 * - updates an element of A in O(logN)
 * Space Complexity:
 * O(N)
 *
 * Basic Principle given f = +
 * Give an array of integers A[0...N-1], the Fenwick Tree is T[0...N-1]
 * T[i] = sum of elements in A[g[i], i] where 0 <= g(i) <= i
 *
 * pseudo code is as follows x (0-indexed)
 *
 * //sums A[0..r]
 * def sum(int r):
 *     res = 0
 *     while r >= 0:
 *          res += T[r]
 *          r = g(r) - 1
 *
 * //increases A[r] by delta
 * def inc(int r, int delta):
 *     for all j such that g(j) <= i <= j < n
 *        T[j] += delta
 *
 * The clever O(logN) sum query and update comes from the choice of g(i), which we choose to be
 * g(i) = i if LSB (bit most to the right) is 0
 * g(i) = i with all trailing other trailing 1s set to 0 if LSB is 1
 * for example, g(0b110100101) = 0b110100100
 *              g(0b110001111) = 0b110001111
 *              g(0b110000000) = 0b100000000
 *
 *  Define h(i) to be the least (next) number such that i < h(i) such that g(h(i)) <= i.
 *  Through lots of math, we see
 *      for sum, g(i) = i & (i+1) -> sets all trailing 1's to 0.
 *      for inc, h(i) = i || i + 1 -> sets the least unset bit to 1 (repeatedly doing this
 *          guarantees ALL the numbers that satisfy the condition g(h(i)) <= i < h(i) < n
 */

/*
 * Tutorial: https://cp-algorithms.com/data_structures/fenwick.html
 * Problem: https://leetcode.com/problems/range-sum-query-mutable/description/
 */

#include <iostream>
#include <vector>

using namespace std;

struct FenwickTree {
    vector<int> tree;
    int n;
    const int DEFAULT = 0;

    FenwickTree(int n) {
        tree.assign(n, DEFAULT);
    }

    FenwickTree(vector<int> &a) : FenwickTree(a.size()) {
        for (int i = 0; i < a.size(); i++) {
            update(i, a[i]);
        }
    }

    int getsum(int l, int r) {
        return getsum(r) - getsum(l - 1);
    }

    //1. point update, range query
    //only considers entries below r
    int getsum(int r) {
        int res = 0;
        for (; r >= 0; r = r & (r + 1) - 1) {
            res += tree[r];
        }
        return res;
    }

    //only edits entries after idx
    void update(int idx, int delta) {
        for (; idx < n; idx |= idx + 1)
            tree[idx] += delta;
    }

    //2. ONLY WORKS for range update, point query (A[0, i])
    //(if you update [11, 100] with +5, then A[11, 100] should inc by 450 but actually doing sum gives same
    //result. basically A[j] + delta - A[i] - delta = A[j] - A[i] (unchanged!!)
    void update_range(int l, int r, int delta) {
        //This works because sum(l) = A[0] + A[1] + ... A[i], so
        //if i < l, then sum A[0, i] remains unchanged because sum(int l) is unchanged
        //if l <= i <= r, then sum[0,i] is updated by delta (first change modifies, second does nothing)
        //if r < i, then first change undone by second change
        update(l, delta);
        update(r + 1, -delta);
    }
};

//For range query and range updates
struct FenwickTreeRURQ {
    FenwickTree b1;
    FenwickTree b2;

    FenwickTreeRURQ(int n) : b1(n), b2(n) {}

    /*
     * We show that sum[0, i] = sum(B1[0...i]) * i - sum(B2[0...i])
     * Let's say a range update (l, r, x) occurs. Then
     * Condition : formula above = mathmathematical reasoning
     * i < l : d sum[0,i] = d (sum(B1[0...i]) * i - sum(B2[0...i]) = 0 (correct!)
     * l <= i <= r : d sum[0, i] = x * i - x * (l - 1) = x * (i - l + 1) (correct!)
     * r < i : d sum[0, i] = 0 * i - (x * (l - 1) - x * r) = x * (r - l + 1) (correct!)
     */
    void range_add(int l, int r, int delta) {
        b1.update(l, delta);
        b1.update(r + 1, -delta);
        b2.update(l, delta * (l - 1));
        b2.update(r + 1, -delta * r);
    }
};

