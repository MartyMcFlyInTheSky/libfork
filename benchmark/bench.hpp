#pragma once

#include <chrono>
#include <fstream>
#include <functional>
#include <string_view>
#include <thread>
#include <type_traits>

#include <nanobench.h>

template <typename F>
auto benchmark(std::string name, F const& fun) -> void {
  //
  ankerl::nanobench::Bench bench;

  bench.title(name);
  bench.warmup(100);
  bench.relative(true);
  bench.performanceCounters(true);

  // bench.minEpochIterations(100);
  // bench.epochs(100);
  // bench.minEpochTime(std::chrono::milliseconds(100));
  // bench.minEpochTime(std::chrono::milliseconds(100));
  // bench.maxEpochTime(std::chrono::milliseconds(1000));

  for (std::size_t i = 1; i <= std::thread::hardware_concurrency(); ++i) {
    //
    std::string iname = std::string{name} + " " + std::to_string(i) + " threads";

    auto x = std::invoke(fun, i, [&]<typename B>(B const& to_bench) {
      bench.run(iname, [&]() {
        std::invoke(to_bench);
      });
    });

    ankerl::nanobench::doNotOptimizeAway(x);
  }

  std::ofstream render("build/" + name + ".json");

  ankerl::nanobench::render(ankerl::nanobench::templates::json(), bench, render);
}