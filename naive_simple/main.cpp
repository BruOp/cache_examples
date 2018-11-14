#include <chrono>
#include <iostream>
#include <limits>
#include <stdlib.h>

#include "matrix.h"

int charToInt(char const* arg);

using namespace std;
using namespace std::chrono;

int main(int argc, char const* argv[])
{
    // All in bytes
    size_t lineSize = 64;
    size_t sizeOfL1 = 128 * 1024;
    size_t sizeOfL2 = 1 * 1024 * 1024;
    size_t sizeOfL3 = 6 * 1024 * 1024;

    size_t sizeOfValue = sizeof(Matrix::Value);

    vector<size_t> barriers{ 0, 500 };

    size_t N = 5;
    for (int i = 1; i < barriers.size(); i++) {
        size_t step = (barriers[i] - barriers[i - 1]) / 100;
        for (size_t M = barriers[i - 1]; M < barriers[i]; M += step) {
            Matrix matA{ N, M }, matB{ M, N };
            matA.fill();
            matB.fill();

            auto start = high_resolution_clock::now();
            multiplySimple(matA, matB);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(end - start).count();

            std::cout << M << ',' << duration << '\n';
        }
    }
    return 0;
}

int charToInt(char const* arg)
{
    char* msg = nullptr;
    long conv = strtol(arg, &msg, 10);
    // Check for errors: e.g., the string does not represent an integer
    // or the integer is larger than int
    if (errno != 0 || *msg != '\0' || conv > numeric_limits<int>::max()) {
        throw runtime_error("Couldn't turn the provided arg into an int");
    } else {
        return conv;
    }
}
