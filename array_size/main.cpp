#include <chrono>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef uint32_t Value;

int main(int argc, char const* argv[])
{
    std::vector<size_t> sizes(15);
    for (size_t i = 1; i <= sizes.size(); i++) {
        sizes[i - 1] = pow(2, i) * 1024;
    }

    constexpr size_t STEPS = 1024 * 1024;
    constexpr size_t CACHE_LINE_SIZE = 64 / sizeof(Value);
    for (auto size : sizes) {
        const size_t lenMod = size - 1;
        std::vector<Value> myArray(size);

        std::cout << myArray.size();

        for (size_t sample = 0; sample < 100; ++sample) {
            auto start = high_resolution_clock::now();

            for (size_t i = 0; i < STEPS; ++i) {
                ++myArray[(i * CACHE_LINE_SIZE) & lenMod];
            }

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start).count();
            std::cout << ',' << duration;
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
    return 0;
}
