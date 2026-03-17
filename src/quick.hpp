#pragma once

#include <cstdlib>
#include <utility>
#include <vector>

struct QuickPivotLeft
{
    template <typename T>
    static size_t select(std::vector<T> &vec, size_t l, size_t r)
    {
        return l;
    }
};

struct QuickPivotMiddle
{
    template <typename T>
    static size_t select(std::vector<T> &vec, size_t l, size_t r)
    {
        return l + (r - l) / 2;
    }
};

struct QuickPivotRight
{
    template <typename T>
    static size_t select(std::vector<T> &vec, size_t l, size_t r)
    {
        return r;
    }
};

struct QuickPivotMedian
{
    template <typename T>
    static size_t select(std::vector<T> &vec, size_t l, size_t r)
    {
        size_t mid = l + (r - l) / 2;

        if (vec[l] > vec[mid])
            std::swap(vec[l], vec[mid]);
        if (vec[l] > vec[r])
            std::swap(vec[l], vec[r]);
        if (vec[mid] > vec[r])
            std::swap(vec[mid], vec[r]);

        return mid;
    }
};

struct QuickPivotRandom
{
    template <typename T>
    static size_t select(std::vector<T> &vec, size_t l, size_t r)
    {
        return l + rand() % (r - l + 1);
    }
};

template <typename PivotStrategy, typename T>
size_t quick_partition(std::vector<T> &vec, size_t l, size_t r)
{
    size_t pivot = l;
    size_t desired_pivot = PivotStrategy::select(vec, l, r);
    std::swap(vec[pivot], vec[desired_pivot]);
    T pivot_value = vec[pivot];

    size_t i = l;
    size_t j = r;
    while (true)
    {
        while (vec[i] < pivot_value)
        {
            i++;
        }

        while (vec[j] > pivot_value)
        {
            j--;
        }

        if (i >= j)
        {
            return j;
        }

        std::swap(vec[i], vec[j]);
        i++;
        j--;
    }
}

template <typename PivotStrategy, typename T>
void quick_sort(std::vector<T> &vec, size_t l, size_t r)
{
    if (l >= r)
    {
        return;
    }

    size_t pivot_index = quick_partition<PivotStrategy>(vec, l, r);
    quick_sort<PivotStrategy>(vec, l, pivot_index);
    quick_sort<PivotStrategy>(vec, pivot_index + 1, r);
}

template <typename PivotStrategy, typename T>
void quick_sort(std::vector<T> &vec)
{
    if (vec.size() <= 1)
        return;

    quick_sort<PivotStrategy>(vec, 0, vec.size() - 1);
}
