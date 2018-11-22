#include <chrono>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef uint32_t Value;

int main(int argc, char const* argv[])
{
    std::vector<Value> myArray(16 * 1024 * 1024);
    const size_t steps = 32;
    size_t counter = 0;
    vector<size_t> strides{ 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 };
    for (auto stride : strides) {
        std::cout << stride;

        for (size_t sample = 0; sample < 100; ++sample) {
            auto start = high_resolution_clock::now();

            for (size_t i = 0; i < steps; ++i) {
                ++myArray[counter + i * stride];
            }

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start).count();

            counter += stride * steps;
            std::cout << ',' << duration;
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
    return 0;
}
