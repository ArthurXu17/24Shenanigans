#include <iostream>
#include <vector>
#include "multisubsetGenerator.cc"

void distinguish(vector<vector<int>>& result) {
    for (auto & vec: result) {

    }
}

int main() {
    /*
    vector<int> test = {1,3,3,4,5,5,7};
    MultisetGenerator testGenerator = MultisetGenerator(test, 4);
    testGenerator.allMultisets();
    vector<int> test2;
    for (int i = 1; i <= 13; i++) {
        for (int j = 1; j <= 4; j++) {
            test2.push_back(i);
        }
    }
    test2.push_back(14);
    test2.push_back(14);
    testGenerator = MultisetGenerator(test2, 8);
    vector<vector<int>> result = testGenerator.allMultisets();
    cout<<result.size()<<endl;*/

    vector<int> set = {0,1,2,3,4,5,6,7};
    MultisetGenerator permGen = MultisetGenerator(set, 4);
    auto result = permGen.allMultisets();
    cout<<result.size()<<endl;
}