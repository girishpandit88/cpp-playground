#include <iostream>
#include <vector>
#include <string>
#include <ranges> // For std::views
#include <algorithm> // For std::for_each
#include <numeric> // For std::accumulate
#include "Functors.h"

using namespace std;

int main() {
    // Test MultiplyByFunctor
    vector<int> testVec = {1, 2, 3, 4, 5};
    MultiplyByFunctor multiplyBy2(2);

    // Apply MultiplyByFunctor
    for_each(testVec.begin(), testVec.end(), multiplyBy2);

    cout << "After multiplication by 2: ";
    for (int x : testVec) {
        cout << x << " ";
    }
    cout << endl;

    // Test ProductReducingFunctor
    ProductReducingFunctor productFunctor;
    int result = accumulate(testVec.begin(), testVec.end(), 1, productFunctor);

    cout << "Product of elements: " << result << endl;

    return 0;
}
