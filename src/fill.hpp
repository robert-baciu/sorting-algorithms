#include <algorithm>
#include <random>
#include <vector>

template <typename T>
void fill_random(std::vector<T> &vec, uint32_t const seed, T const minVal,
                 T const maxVal)
{
    std::mt19937 generator(seed);

    if constexpr (std::is_integral_v<T>)
    {
        std::uniform_int_distribution<T> distr(minVal, maxVal);

        for (T &elem : vec)
        {
            elem = distr(generator);
        }
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        std::uniform_real_distribution<T> distr(minVal, maxVal);

        for (T &elem : vec)
        {
            elem = distr(generator);
        }
    }
}

template <typename T>
void fillSorted(std::vector<T> &vec, T const minVal, T const maxVal,
                uint32_t const seed)
{
    fill_random(vec, minVal, maxVal, seed);
    std::sort(vec.begin(), vec.end());
}

template <typename T>
void fillSortedReversed(std::vector<T> &vec, T const minVal, T const maxVal,
                        uint32_t const seed)
{
    fillSorted(vec, minVal, maxVal, seed);
    std::reverse(vec.begin(), vec.end());
}
