#include <iostream>
#include <string>
#include <vector>

#include "cxxopts.hpp"
#include "fill.hpp"

#include "bubble.hpp"
#include "heap.hpp"
#include "hybrid.hpp"
#include "insertion.hpp"
#include "merge.hpp"
#include "quick.hpp"
#include "selection.hpp"
#include "stl.hpp"

template <typename T> auto str_to_sort_func(std::string const &str)
{
    using sort_func = void (*)(std::vector<T> &);

    if (str == "bubble")
        return (sort_func)bubble_sort<T>;
    if (str == "heap")
        return (sort_func)heap_sort<T>;

    if (str == "hybrid-insertion-4")
        return (sort_func)hybrid_sort_insertion<4, T>;
    if (str == "hybrid-insertion-8")
        return (sort_func)hybrid_sort_insertion<8, T>;
    if (str == "hybrid-insertion-12")
        return (sort_func)hybrid_sort_insertion<12, T>;
    if (str == "hybrid-insertion-16")
        return (sort_func)hybrid_sort_insertion<16, T>;
    if (str == "hybrid-insertion-20")
        return (sort_func)hybrid_sort_insertion<20, T>;

    if (str == "hybrid-selection-4")
        return (sort_func)hybrid_sort_selection<4, T>;
    if (str == "hybrid-selection-8" || str == "hybrid")
        return (sort_func)hybrid_sort_selection<8, T>;
    if (str == "hybrid-selection-12")
        return (sort_func)hybrid_sort_selection<12, T>;
    if (str == "hybrid-selection-16")
        return (sort_func)hybrid_sort_selection<16, T>;
    if (str == "hybrid-selection-20")
        return (sort_func)hybrid_sort_selection<20, T>;

    if (str == "insertion")
        return (sort_func)insertion_sort<T>;
    if (str == "intro")
        return (sort_func)stl_sort<T>;
    if (str == "merge")
        return (sort_func)merge_sort<T>;

    if (str == "quick-left")
        return (sort_func)quick_sort<QuickPivotLeft, T>;
    if (str == "quick-middle" || str == "quick")
        return (sort_func)quick_sort<QuickPivotMiddle, T>;
    if (str == "quick-right")
        return (sort_func)quick_sort<QuickPivotRight, T>;
    if (str == "quick-median")
        return (sort_func)quick_sort<QuickPivotMedian, T>;
    if (str == "quick-random")
        return (sort_func)quick_sort<QuickPivotRandom, T>;

    if (str == "selection")
        return (sort_func)selection_sort<T>;

    throw std::runtime_error("Invalid algorithm: " + str);
}

template <typename T>
void fill_vector(std::vector<T> &vec, cxxopts::ParseResult const &args)
{
    std::string fill = args["fill"].as<std::string>();

    enum class Fill
    {
        Constant,
        Random,
        Sorted,
        ReverseSorted
    };

    Fill strategy;
    if (fill == "constant")
        strategy = Fill::Constant;
    else if (fill == "random")
        strategy = Fill::Random;
    else if (fill == "sorted")
        strategy = Fill::Sorted;
    else if (fill == "reverse-sorted")
        strategy = Fill::ReverseSorted;
    else
        throw std::runtime_error("Invalid fill strategy: " + fill);

    if (strategy == Fill::Constant)
    {
        for (T &elem : vec)
            elem = 0;
    }
    else
    {
        uint32_t seed = args["rseed"].as<uint32_t>();

        std::string raw_min = args["rmin"].as<std::string>();
        std::string raw_max = args["rmax"].as<std::string>();
        T min, max;

        cxxopts::value(min)->parse(raw_min);
        cxxopts::value(max)->parse(raw_max);
        fill_random(vec, seed, min, max);

        if (strategy == Fill::Sorted)
            std::sort(vec.begin(), vec.end());

        if (strategy == Fill::ReverseSorted)
        {
            std::sort(vec.begin(), vec.end());
            std::reverse(vec.begin(), vec.end());
        }
    }
}

template <typename T> void run_benchmark(cxxopts::ParseResult const &args)
{
    std::string sort_str = args["sort"].as<std::string>();
    auto sort = str_to_sort_func<T>(sort_str);
    auto size = args["size"].as<size_t>();

    std::vector<T> vec(size);
    fill_vector(vec, args);

    auto startTime = std::chrono::high_resolution_clock::now();
    sort(vec);
    auto finishTime = std::chrono::high_resolution_clock::now();

    bool sorted = std::is_sorted(vec.begin(), vec.end());
    if (!sorted)
    {
        throw std::runtime_error("Vector is not sorted");
    }

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
        finishTime - startTime);
    std::cout << duration.count() << std::endl;
}

int main(int argc, char **argv)
{
    cxxopts::Options options("benchmark", "Sorting benchmarking tool");

    // clang-format off
    options.add_options()
        ("sort", "Algorithm", cxxopts::value<std::string>())
        ("size", "Vector size", cxxopts::value<size_t>())
        ("type", "Data type", cxxopts::value<std::string>())
        ("fill", "Fill strategy", cxxopts::value<std::string>())
        ("rseed", "Random seed", cxxopts::value<uint32_t>())
        ("rmin", "Random min value", cxxopts::value<std::string>())
        ("rmax", "Random max value", cxxopts::value<std::string>())
        ("help", "Print usage");
    // clang-format on

    auto result = options.parse(argc, argv);
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    std::string data_type = result["type"].as<std::string>();

    if (data_type == "byte")
        run_benchmark<unsigned char>(result);
    else if (data_type == "int")
        run_benchmark<int>(result);
    else if (data_type == "double")
        run_benchmark<double>(result);
    else
        throw std::runtime_error("Invalid data type: " + data_type);

    return 0;
}
