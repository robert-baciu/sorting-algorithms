#pragma once

#include <vector>

template <typename T> void selection_sort(std::vector<T> &vec)
{
    if (vec.size() <= 1)
        return;

    for (size_t i = 0; i < vec.size(); i++)
    {
        size_t min_index = i;
        for (size_t j = i + 1; j < vec.size(); j++)
        {
            if (vec[j] < vec[min_index])
            {
                min_index = j;
            }
        }
        std::swap(vec[i], vec[min_index]);
    }
}
