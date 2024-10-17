#include <vector>
#include <iostream>

using namespace std;
class CardGenerator {
    private:
        vector<int> curPermutation;
        int min;
        int max;
        void nextPermutation() {
            int length = curPermutation.size();
            int index = length - 1;
            while(index >= 0 && curPermutation[index] == max) {
                index--;
            }
            if (index == -1) {
                return;
            }
            int curValue = curPermutation[index];
            //cout<<"Index of curValue: "<<index<<endl;
            for (int i = index; i < length; i++) {
                curPermutation[i] = curValue + 1;
            }
        }

    public:
        CardGenerator(int _min, int _max, int length) : min(_min), max(_max) {
            curPermutation = vector<int>(length, _min);
        }
        vector<vector<int>> allSets() {
            // index = 3: 1 1 1 1 -> 1 1 1 2 ... 1 1 1 13 -> 1 1 2 2 ... 1 1 2 13 -> 1 1 3 3 .... 1 1 12 12 -> 1 1 12 13 -> 1 1 13 13
            // index = 2: 1 2 2 2 -> 1 2 2 3 ... 1 2 2 13 -> 1 2 3 3 ... 
            vector<vector<int>> result;
            while (curPermutation[0] != max) {
                result.push_back(curPermutation);
                nextPermutation();
            }
            // ensure we push back 13 13 13 13
            result.push_back(curPermutation);
            return result;
        }
};