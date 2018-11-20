#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

int main(int argc, char const* argv[])
{
    // Sizes are in KB
    std::vector<size_t> sizes{ 16, 128, 1024, 10 * 1024 };
    size_t steps = 10;

    for (size_t i = 1; i < sizes.size(); ++i) {
        size_t diff = sizes[i] - sizes[i - 1];
        size_t step = diff / 8;

        for (size_t size = sizes[i - 1]; size < sizes[i]; size += step) {
            // Convert kilobytes into bytes, divide by sizeof elements (in bytes)
            std::vector<uint16_t> myArray(size * 1024 / sizeof(uint16_t));

            auto start = high_resolution_clock::now();

            for (size_t i = 0; i < myArray.size(); ++i) {
                myArray[i];
            }

            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start).count();

            std::cout << size << ',' << duration << '\n';
        }
    }
    std::cout << std::endl;
    return 0;
}
