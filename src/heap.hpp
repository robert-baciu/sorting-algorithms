#pragma once

#include <vector>

template <typename T>
void heapify(std::vector<T> &heap, size_t max_node, size_t node)
{
    size_t lsubtree = node * 2 + 1;
    size_t rsubtree = node * 2 + 2;

    size_t largest = node;
    if (lsubtree <= max_node && heap[lsubtree] > heap[largest])
    {
        largest = lsubtree;
    }

    if (rsubtree <= max_node && heap[rsubtree] > heap[largest])
    {
        largest = rsubtree;
    }

    if (largest != node)
    {
        std::swap(heap[node], heap[largest]);
        heapify(heap, max_node, largest);
    }
}

template <typename T> size_t build_heap(std::vector<T> &vec, size_t max_node)
{
    for (size_t i = (max_node - 1) / 2; i >= 1; i--)
    {
        heapify(vec, max_node, i);
    }
    heapify(vec, max_node, 0);
    return max_node;
}

template <typename T> void heap_sort(std::vector<T> &vec)
{
    if (vec.size() <= 1)
        return;

    size_t max_node = vec.size() - 1;
    build_heap(vec, max_node);
    for (size_t i = max_node; i >= 1; i--)
    {
        std::swap(vec[0], vec[i]);
        max_node--;
        heapify(vec, max_node, 0);
    }
}
