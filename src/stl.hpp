#pragma once

#include <algorithm>
#include <vector>

template <typename T> void stl_sort(std::vector<T> &vec)
{
    std::sort(vec.begin(), vec.end());
}
