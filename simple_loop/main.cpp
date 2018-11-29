#include <chrono>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
using namespace std::chrono;

typedef uint32_t Value;

int main(int argc, char const* argv[])
{
    std::vector<Value> myArray(64 * 1024 * 1024);
    const size_t size = myArray.size();
    const size_t STEPS = 32;
    
    vector<size_t> strides{ 1, 2, 3, 4, 6, 8, 12, 16, 32, 64, 96, 128, 192, 256, 512, 1024, 2048 };

    for (auto stride : strides) {
        std::cout << stride * sizeof(Value) << ", " << STEPS << ", ";

        auto start = high_resolution_clock::now();

        for (size_t i = 0; i < STEPS * stride; i += stride) {
            myArray[stride + i] += i;
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end - start).count();

        std::cout << duration << '\n';
    }
    std::cout << std::endl;
    return 0;
}
