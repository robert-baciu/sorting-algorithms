#pragma once

#include <vector>

template <typename T>
size_t hybrid_partition(std::vector<T> &vec, size_t l, size_t r)
{
    size_t pivot = l;
    size_t desired_pivot = l + (r - l) / 2;
    std::swap(vec[pivot], vec[desired_pivot]);
    T pivot_value = vec[pivot];

    size_t i = l;
    size_t j = r;
    while (true)
    {
        while (vec[i] < pivot_value)
            i++;

        while (vec[j] > pivot_value)
            j--;

        if (i >= j)
            return j;

        std::swap(vec[i], vec[j]);
        i++;
        j--;
    }
}

template <size_t Threshold, typename T>
void hybrid_sort_insertion(std::vector<T> &vec, size_t l, size_t r)
{
    if (l >= r)
        return;

    size_t size = r - l + 1;
    if (size <= Threshold)
    {
        // Insertion sort
        for (size_t i = l + 1; i <= r; i++)
        {
            for (size_t j = i; j > l; j--)
            {
                if (vec[j] < vec[j - 1])
                {
                    std::swap(vec[j], vec[j - 1]);
                }
            }
        }
    }
    else
    {
        // Quick sort
        size_t pivot_index = hybrid_partition(vec, l, r);
        hybrid_sort_insertion<Threshold>(vec, l, pivot_index);
        hybrid_sort_insertion<Threshold>(vec, pivot_index + 1, r);
    }
}

template <size_t Threshold, typename T>
void hybrid_sort_selection(std::vector<T> &vec, size_t l, size_t r)
{
    if (l >= r)
        return;

    size_t size = r - l + 1;
    if (size <= Threshold)
    {
        // Selection sort
        for (size_t i = l; i < r; i++)
        {
            size_t min_index = i;
            for (size_t j = i + 1; j <= r; j++)
            {
                if (vec[j] < vec[min_index])
                {
                    min_index = j;
                }
            }
            std::swap(vec[i], vec[min_index]);
        }
    }
    else
    {
        // Quick sort
        size_t pivot_index = hybrid_partition(vec, l, r);
        hybrid_sort_selection<Threshold>(vec, l, pivot_index);
        hybrid_sort_selection<Threshold>(vec, pivot_index + 1, r);
    }
}

template <size_t Threshold, typename T>
void hybrid_sort_insertion(std::vector<T> &vec)
{
    if (vec.size() <= 1)
        return;

    hybrid_sort_insertion<Threshold>(vec, 0, vec.size() - 1);
}

template <size_t Threshold, typename T>
void hybrid_sort_selection(std::vector<T> &vec)
{
    if (vec.size() <= 1)
        return;

    hybrid_sort_selection<Threshold>(vec, 0, vec.size() - 1);
}
