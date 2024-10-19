#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include "utils.cc"

using namespace std;
class MultisetGenerator {
    /*
    1,3,3,4,5,5,7; size 4

    1,3,3,4 -> 1,3,3,5 -> 1,3,3,7 -> 1,3,4,5 ... 1,5,5,7 -> 3,3,4,5 ... 3,5,5,7 -> 4,5,5,7


    1,5,5,5,5,5,5,5,5,5,5,5,5,6; size 4

    1,5,5,5 -> 1,5,5,6 -> 5,5,5,5 -> 5,5,5,6
    */
    private:
        vector<int> multiset;
        vector<int> curPermutation;
        // contains the next bigger number of every number in multiset except for the largest
        unordered_map<int, int> nextBiggerNumber;
        // contains the first index of every number in multiset
        unordered_map<int, int> firstIndex;
        int length;
        void nextPermutation() {
            int multisetIndex = multiset.size() - 1;
            int permutationIndex = length - 1;
            while(permutationIndex >= 0 && curPermutation[permutationIndex] == multiset[multisetIndex]) {
                //cout<<"Index: "<<permutationIndex<<endl;
                permutationIndex--;
                multisetIndex--;
            }
            if (permutationIndex == -1) {
                return;
            }

            int pivot = curPermutation[permutationIndex];
            // 1. find next number bigger than curValue
            // At this point pivot is guaranteed to not be the biggest number,
            // this can only occur if the entirity of curPermutation is the biggest number, which would return above
            int nextNum = nextBiggerNumber[pivot];

            // 2. find index of first occurence of next number
            int newIndex = firstIndex[nextNum];

            // 3. replace tail with subarray starting at that index
            for (int i = permutationIndex; i < length; i++, newIndex++) {
                curPermutation[i] = multiset[newIndex];
            }
        }

    public:
        MultisetGenerator(vector<int> _multiset, int _length) : multiset(_multiset), length(_length) {
            assert(length <= multiset.size());
            sort(_multiset.begin(), _multiset.end());
            curPermutation = vector<int>(_multiset.begin(), _multiset.begin() + length);
            for (int i = 0; i < multiset.size(); i++) {
                int curNum = multiset[i];
                if (firstIndex.find(curNum) == firstIndex.end()) {
                    firstIndex[curNum] = i;
                }
                if (i + 1 < multiset.size() && curNum != multiset[i+1]) {
                    nextBiggerNumber[curNum] = multiset[i+1];
                }
            }
        }

        vector<vector<int>> allMultisets() {
            // 1,2,2,2,3; 3
            // 2,2,2; 2,2,3
            vector<vector<int>> result;
            vector<int> lastPermutation = vector<int>(multiset.end() - length, multiset.end());
            while (curPermutation != lastPermutation) {
                result.push_back(curPermutation);
                nextPermutation();
            }
            // ensure we push back last permuttaion
            result.push_back(curPermutation);
            return result;
        }

        vector<int> getCurPermuation() {
            return curPermutation;
        }
};