#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <cmath> // For std::pow
#include <numeric> // For std::accumulate

// Functor for multiplying a value
struct MultiplyByFunctor {
    int factor_;

    MultiplyByFunctor(int factor) : factor_(factor) {}

    void operator()(int& x) const {
        x *= factor_;
    }
};

// Functor for raising a value to a power
struct PowerOfFunctor {
    int exponent_;

    PowerOfFunctor(int exponent) : exponent_(exponent) {}

    double operator()(double base) const {
        return std::pow(base, exponent_);
    }
};

// Functor for reducing multiplication
struct ProductReducingFunctor {
    long long operator()(long long a, long long b) const {
        return a * b;
    }
};

// Functor for reducing sum
struct AccumulatorReducingFunctor {
    long long operator()(long long a, long long b) const {
        return a + b;
    }
};

// Generic Transformer Functor
template <typename Functor>
struct TransformerFunctor {
    Functor functor_;

    TransformerFunctor(Functor functor) : functor_(functor) {}

    void operator()(std::vector<int>& data) const {
        for (auto& elem : data) {
            functor_(elem);
        }
    }

    void applyToVector(std::vector<int>& data) const {
        for (auto& elem : data) {
            elem = functor_(elem); // Assuming functor returns the transformed value
        }
    }
};

// Generic Reducer Functor
template <typename Reducer>
struct ReducerFunctor {
    Reducer reducer_;
    long long initial_value_;

    ReducerFunctor(Reducer reducer, long long initial_value)
        : reducer_(reducer), initial_value_(initial_value) {}

    long long operator()(const std::vector<int>& data) const {
        return std::accumulate(data.begin(), data.end(), initial_value_, reducer_);
    }
};

#endif // FUNCTORS_H