#include <chrono>
#include <iostream>
#include <limits>

#include "matrix.h"

int charToInt(char const* arg);

using namespace std;
using namespace std::chrono;

int main(int argc, char const* argv[])
{
    std::vector<size_t> sizes{ 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 3072 };

    for (auto N : sizes) {
        Matrix matA{ N, N }, matB{ N, N };
        matA.fill();
        matB.fill();

        auto start = high_resolution_clock::now();
        multiplySimple(matA, matB);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        multiplyTranspose(matA, matB);
        end = high_resolution_clock::now();
        auto durationTranspose = duration_cast<microseconds>(end - start).count();

        std::cout << N << ',' << duration << ',' << durationTranspose << '\n';
    }
    std::cout << std::endl;
    return 0;
}
