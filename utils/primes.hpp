/*
 * primes.hpp Copyrights Marcello Tavano (c) 20015
 */

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <limits>
#include <vector>

#ifndef PRIMES_HPP
#define PRIMES_HPP

// =============================================================================
// =============================Monkey Mode checker=============================
// =============================================================================

bool monkeyModeChecker(const std::uint32_t tol) {
  if (tol == 2 || tol == 3) return true;
  for (std::uint32_t i = 2; i <= std::sqrt(tol); ++i) {
    if (tol % i == 0) return false;
  }
  return true;
}

// =============================================================================
// =============================Eratosthenes Sieve==============================
// =============================================================================

void markDown(const std::uint32_t &base, std::vector<bool> &v) {
  int i = 2;
  int component = base;
  while (component <= v.size()) {
    if (v[component] == true)
      if (base != component) v[component] = false;
    component = base * i;
    ++i;
  }
}

void nextIndexTrue(std::uint32_t &start, const std::vector<bool> &v) {
  for (std::uint32_t i = start + 1; i < v.size(); ++i) {
    if (v[i] == true) {
      start = i;
      break;
    }
  }
}

std::vector<bool> eratosthenesSieve(const std::uint32_t &tol) {
  std::vector<bool> sieve(tol + 1, true);
  sieve[0] = false;
  sieve[1] = false;
  std::uint32_t i = 2;
  while (i <= std::sqrt(sieve.size())) {
    if (sieve[i] == true) markDown(i, sieve);
    nextIndexTrue(i, sieve);
  }
  return sieve;
}

std::vector<std::uint32_t> makePrimeTable(const std::uint32_t &tol) {
  auto pt = eratosthenesSieve(tol);
  std::vector<std::uint32_t> v;
  for (int i = 0; i < pt.size(); ++i) {
    if (pt[i]) v.push_back(i);
  }
  return v;
}

bool linearChecker(const std::uint32_t &tol) {
  auto primes = makePrimeTable(tol);
  for (std::uint32_t i = 0; i < primes.size(); ++i) {
    if (primes[i] > std::sqrt(tol))
      break;
    else if (tol % primes[i] == 0)
      return false;
  }
  return true;
}

bool tableChecker(const std::uint32_t &tol) {
  if (tol < 66000) {
    auto primes = makePrimeTable(66000);
    return std::binary_search(primes.begin(), primes.end(), tol);
  }
  return linearChecker(tol);
}

// =============================================================================
// =========================Miller Rabin Primality test=========================
// =============================================================================

std::uint32_t makeMod(const std::uint32_t &fst, std::uint32_t scd,
                      const std::uint32_t &mod) {
  std::uint32_t modGen = 0;
  std::uint32_t modGen2 = fst % mod;
  while (scd > 0) {
    if (scd % 2 == 1) {
      modGen = (modGen + modGen2) % mod;
    }
    modGen2 = (modGen2 * 2) % mod;
    scd /= 2;
  }
  return modGen % mod;
}

std::uint32_t makeMod2(const std::uint32_t &base, std::uint32_t expP,
                       const std::uint32_t &mod) {
  std::uint32_t x = 1;
  std::uint32_t y = base;
  while (expP > 0) {
    if (expP % 2 == 1) x = (x * y) % mod;
    y = (y * y) % mod;
    expP = expP / 2;
  }
  return x % mod;
}

bool millerRabinChecker(const std::uint32_t &numb) {
  if (numb < 2) return false;
  if (numb != 2 && numb % 2 == 0) return false;
  std::uint32_t sth = numb - 1;
  while (sth % 2 == 0) {
    sth /= 2;
  }
  for (int i = 0; i < 5; i++) {
    std::uint32_t fst = rand() % (numb - 1) + 1, temp = sth;
    std::uint32_t mod = makeMod2(fst, temp, numb);
    while (temp != numb - 1 && mod != 1 && mod != numb - 1) {
      mod = makeMod(mod, mod, numb);
      temp *= 2;
    }
    if (mod != numb - 1 && temp % 2 == 0) {
      return false;
    }
  }
  return true;
}

#endif
