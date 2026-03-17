#pragma once

#include <vector>

template <typename T> void bubble_sort(std::vector<T> &vec)
{
    if (vec.size() <= 1)
        return;

    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (size_t i = 0; i < vec.size() - 1; i++)
        {
            if (vec[i] > vec[i + 1])
            {
                std::swap(vec[i], vec[i + 1]);
                sorted = false;
            }
        }
    }
}
