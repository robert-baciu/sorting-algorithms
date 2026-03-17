#pragma once

#include <vector>

template <typename T>
void merge(std::vector<T> &src, std::vector<T> &dest, size_t l, size_t r)
{
    size_t mid = l + (r - l) / 2;

    size_t i = l;
    size_t j = mid + 1;
    size_t k = l;
    while (i <= mid && j <= r)
    {
        if (src[i] <= src[j])
        {
            dest[k] = src[i];
            i++;
        }
        else
        {
            dest[k] = src[j];
            j++;
        }
        k++;
    }

    while (i <= mid)
    {
        dest[k] = src[i];
        i++;
        k++;
    }

    while (j <= r)
    {
        dest[k] = src[j];
        j++;
        k++;
    }
}

template <typename T>
void merge_sort(std::vector<T> &src, std::vector<T> &dest, size_t l, size_t r)
{
    if (l >= r)
        return;

    size_t mid = l + (r - l) / 2;
    merge_sort(dest, src, l, mid);
    merge_sort(dest, src, mid + 1, r);
    merge(src, dest, l, r);
}

template <typename T> void merge_sort(std::vector<T> &vec)
{
    if (vec.size() <= 1)
        return;

    std::vector<T> aux_vec = vec;
    merge_sort(aux_vec, vec, 0, vec.size() - 1);
}
