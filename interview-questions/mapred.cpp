#include <iostream>
#include <vector>
#include <ranges> // For std::views
#include <algorithm> // For std::for_each and std::transform
#include <numeric> // For std::accumulate
#include "Functors.h"

using namespace std;

template <typename Transformer, typename Reducer>
void processVector(const vector<int>& original, Transformer transformer, Reducer reducer, long long initial_value, const string& label) {
    vector<int> temp(original.begin(), original.end());

    // Apply the transformation to the vector
    transformer(temp);

    // Perform reduction operation
    long long result = reducer(temp);

    // Output the result
    cout << label << ": " << result << std::endl;

    // Print the modified vector
    for_each(temp.begin(), temp.end(), [](int x) {
        cout << x << " ";
    });
    cout << endl;
}

int main(int argc, char const *argv[])
{
    // Define functors
    vector<MultiplyByFunctor> multiplyBys = {MultiplyByFunctor(2), MultiplyByFunctor(3), MultiplyByFunctor(5)};
    vector<PowerOfFunctor> powerOfs = {PowerOfFunctor(1), PowerOfFunctor(2), PowerOfFunctor(3)};

    // Create a sequence of numbers from 1 to 9 using std::views::iota
    auto original = std::views::iota(1, 10);

    // Process multiplication and product reduction
    for (const auto& mb : multiplyBys) {
        TransformerFunctor<MultiplyByFunctor> transformer(mb);
        ReducerFunctor<ProductReducingFunctor> reducer(ProductReducingFunctor(), 1LL);
        processVector(vector<int>(original.begin(), original.end()), transformer, reducer, 1LL, "Product with ProductReducingFunctor");
    }

    // Process power transformation and sum reduction
    for (const auto& pof : powerOfs) {
        auto powerTransformer = [&](vector<int>& data) {
            transform(data.begin(), data.end(), data.begin(), pof);
        };
        ReducerFunctor<AccumulatorReducingFunctor> reducer(AccumulatorReducingFunctor(), 0LL);
        processVector(vector<int>(original.begin(), original.end()), powerTransformer, reducer, 0LL, "Sum with AccumulatorReducingFunctor");
    }

    return 0;
}
