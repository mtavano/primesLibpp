/*
 * main.cpp Copyrights Jorge Aguirre (c) 2015
 * primes.hpp Copyrights Marcello Tavano (c) 2015
 */

#include <iostream>
#include <fstream>
#include <chrono>

#include "primes.hpp"

using namespace std;

template <class PrimeTest>
void test_algorithm(const char* test_name, uint32_t hi, uint32_t lo,
                    PrimeTest is_prime) {
  using namespace std::chrono;

  size_t cnt = 0;
  auto start = steady_clock::now();
  for (uint32_t i = lo; i < hi; ++i) cnt += is_prime(i);
  auto end = steady_clock::now();
  duration<double, std::milli> elapsed = end - start;

  cout << test_name << '\n';
  cout << "  High: " << hi << '\n';
  cout << "  Low: " << lo << '\n';
  cout << "  Primes: " << cnt << '\n';
  cout << "  Elapsed: " << elapsed.count() << " ms\n";
  cout << std::endl;
}

int main(int argc, const char** argv) {
  if (argc != 4) {
    std::clog << "Usage :" << *argv << " <range> <step> <limit>\n";
    return -1;
  }
  uint32_t range = std::stoul(argv[1]);
  uint32_t step = std::stoul(argv[2]);
  uint32_t limit = std::stoul(argv[3]);
  for (size_t hi = range; hi < limit; hi += step) {
    size_t lo = hi - range;
    test_algorithm("Test numbers: ", hi, lo,
                   [&](const uint32_t n) { return linearModeChecker(n); });
    test_algorithm("Test primes: ", hi, lo,
                   [&](const uint32_t n) { return linearChecker(n); });
    test_algorithm("Using sieve: ", hi, lo,
                   [&](const uint32_t n) { return tableChecker(n); });
    test_algorithm("Miller-Rabin: ", hi, lo,
                   [&](const uint32_t n) { return millerRabinChecker(n); });
  }
}
