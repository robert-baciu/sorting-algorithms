#!/usr/bin/env python

import math
import subprocess

def power(power, min, max):
    return [int(power ** x) for x in range(min, max + 1)]

def get_csv_filename(basename, suffix):
    return f'results/{basename}-{suffix}.csv'

def write_csv(sorts, sizes, results, filename):
    with open(filename, 'w') as f:
        f.write(f"size,{','.join(sorts)}\n")
        for i in range(len(sizes)):
            f.write(f"{sizes[i]},{','.join([str(results[sort][i]) for sort in sorts])}\n")
    print(f'{filename} written')

def main():
    # sorts = [
    #     'bubble',
    #     'insertion',
    #     'selection',
    #     'merge',
    #     'heap',
    #     'quick',
    #     'hybrid',
    #     'intro'
    #     'hybrid-insertion-4',
    #     'hybrid-insertion-8',
    #     'hybrid-insertion-12',
    #     'hybrid-insertion-16',
    #     'hybrid-insertion-20',
    #     'hybrid-selection-4',
    #     'hybrid-selection-8',
    #     'hybrid-selection-12',
    #     'hybrid-selection-16',
    #     'hybrid-selection-20',
    #     'quick-left',
    #     'quick-middle',
    #     'quick-right',
    #     'quick-median',
    #     'quick-random',
    # ]
    # sizes = power(2, 1, 20)
    data_type = 'double'
    fill = 'random'
    density = 'wide'
    run_count = 25
    optimization = 'O3'
    rseed = 123456

    basename = f'{fill}-{density}-{data_type}'

    # Test 1: All in 2^[1, 8]
    sorts_all = [
        'bubble', 'insertion', 'selection',
        'merge', 'heap', 'quick',
        'hybrid', 'intro'
    ]
    sizes_all = power(2, 1, 8)

    # Test 2: O(N^2) in 2^[1, 14]
    sorts_nsq = [
        'bubble', 'insertion', 'selection', 'intro'
    ]
    sizes_nsq = power(2, 1, 14)

    # Test 3: O(NlogN) in 2^[1, 20]
    sorts_nlogn = [
        'merge', 'heap', 'quick', 'hybrid', 'intro'
    ]
    sizes_nlogn = power(2, 1, 20)

    def run(sorts, sizes):
        return run_benchmark(
            sorts=sorts,
            sizes=sizes,
            data_type=data_type, fill=fill,
            density=density, run_count=run_count,
            optimization=optimization, rseed=rseed
        )

    results_all = run(sorts_all, sizes_all)
    results_nsq = run(sorts_nsq, sizes_nsq)
    results_nlogn = run(sorts_nlogn, sizes_nlogn)

    write_csv(sorts_all, sizes_all, results_all, get_csv_filename(basename, 'all'))
    write_csv(sorts_nsq, sizes_nsq, results_nsq,  get_csv_filename(basename, 'nsq'))
    write_csv(sorts_nlogn, sizes_nlogn, results_nlogn, get_csv_filename(basename, 'nlogn'))

def run_benchmark(*, sorts, sizes, data_type, fill, density, run_count, optimization, rseed):
    benchmarks = {}

    for sort in sorts:
        print(f'Algorithm: {sort}')
        min_times = []
        for size in sizes:
            print(f'  Size: {size}')
            times = []

            def run_wrapper():
                rmin = rmax = 0
                if fill in ['random', 'sorted', 'reverse-sorted']:
                    if density == 'wide':
                        rmin, rmax = 0, size
                    elif density == 'dense':
                        rmin, rmax = 0, size // 32
                    elif density == 'log':
                        rmin, rmax = 0, int(math.log2(size))
                    else:
                        raise ValueError('Invalid density: ' + density)

                    if data_type == 'byte':
                        rmax = min(rmax, 255)

                return run_and_time(
                    sort=sort, size=size, data_type=data_type,
                    fill=fill, rmin=rmin, rmax=rmax, rseed=rseed,
                    optimization=optimization
                )


            for _ in range(3):
                run_wrapper()

            for _ in range(run_count):
                time = run_wrapper()
                times.append(time)

            min_time = min(times)
            min_times.append(min_time)

        benchmarks[sort] = min_times

    return benchmarks

def run_and_time(*, sort, size, data_type, fill, rmin, rmax, rseed, optimization):
    args = [
        f'./bin/benchmark-{optimization}',
        '--sort', sort,
        '--size', str(size),
        '--type', data_type,
        '--fill', fill,
        '--rmin', str(rmin),
        '--rmax', str(rmax),
        '--rseed', str(rseed)
    ]

    try:
        result = subprocess.run(args, capture_output=True, check=True, text=True)
        return int(result.stdout.strip())
    except subprocess.CalledProcessError as e:
        print('Benchmark subprocess error')
        print('  Command: ' + ' '.join([str(arg) for arg in e.cmd]))
        return None

main()
