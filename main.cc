#include <iostream>
#include "solver.cc"
#include "cardGenerator.cc"
#include <unordered_set>


int main() {
    DoubleSolver solver = DoubleSolver();
    CardGenerator generator = CardGenerator(1,13,4);
    auto result = generator.allSets();
    cout<<result.size()<<endl;
    int totalSuccess = 0;
    for (auto & vec : result) {
        if (solver.judgePoint24(vec)) {
            totalSuccess++;
        }
    }
    cout<<totalSuccess<<endl;
    /*
    result = generator.allSets(1, 5, 4);
    cout<<result.size()<<endl;
    result = generator.allSets(9, 13, 4);
    cout<<result.size()<<endl;*/
}