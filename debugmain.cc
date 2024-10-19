#include <iostream>
#include <vector>
#include "multisubsetGenerator.cc"

int main() {
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
    testGenerator = MultisetGenerator(test2, 4);
    cout<<testGenerator.allMultisets().size()<<endl;
}