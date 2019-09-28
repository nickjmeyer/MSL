#include <benchmark/benchmark.h>

#include "src/algorithm/Partition.hh"

#include <random>
#include <algorithm>

void njm_algorithm_benchmark(benchmark::State& state)
{
  auto num_values = state.range(0);
  std::vector<int32_t> values;
  values.reserve(num_values);
  std::mt19937 rng{0};
  std::uniform_int_distribution<int32_t> dist{-100, 100};
  size_t max_evals{0U};
  size_t min_evals{0U};
  --min_evals;
  for (auto _ : state)
  {
    state.PauseTiming();
    values.clear();
    for (int32_t i = 0; i < num_values; ++i)
    {
      values.push_back(dist(rng));
    }
    state.ResumeTiming();
    size_t num_evals{0U};
    njm::algorithm::partition(std::begin(values), std::end(values),
                              [&num_evals] (auto x)
                              {
                                ++num_evals;
                                return x < 20;
                              });
    max_evals = std::max(max_evals, num_evals);
    min_evals = std::min(min_evals, num_evals);
  }
  state.counters["max_evals"] = max_evals;
  state.counters["min_evals"] = min_evals;
}

void std_algorithm_benchmark(benchmark::State& state)
{
  auto num_values = state.range(0);
  std::vector<int32_t> values;
  values.reserve(num_values);
  std::mt19937 rng{0};
  std::uniform_int_distribution<int32_t> dist{-100, 100};
  size_t max_evals{0U};
  size_t min_evals{0U};
  --min_evals;
  for (auto _ : state)
  {
    state.PauseTiming();
    values.clear();
    for (int32_t i = 0; i < num_values; ++i)
    {
      values.push_back(dist(rng));
    }
    size_t num_evals{0U};
    state.ResumeTiming();
    std::partition(std::begin(values), std::end(values),
                   [&num_evals] (auto x)
                   {
                     ++num_evals;
                     return x < 20;
                   });
    max_evals = std::max(max_evals, num_evals);
    min_evals = std::min(min_evals, num_evals);
  }
  state.counters["max_evals"] = max_evals;
  state.counters["min_evals"] = min_evals;
}

double compute_max(const std::vector<double>&v)
{
  return *std::max_element(std::begin(v), std::end(v));
}

BENCHMARK(njm_algorithm_benchmark)
->Range(8, 1 << 24)
// ->Repetitions(10)
// ->ReportAggregatesOnly(true)
->ComputeStatistics("max", compute_max);

BENCHMARK(std_algorithm_benchmark)
->Range(8, 1 << 24)
// ->Repetitions(10)
// ->ReportAggregatesOnly(true)
->ComputeStatistics("max", compute_max);

BENCHMARK_MAIN();
