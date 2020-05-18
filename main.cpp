#include <bits/stdc++.h>

#include "Vector.h"

int main() {
    unsigned int sz = 100000000;

    std::vector<int> v1;

    int re1 = 0;
    auto v1Begin = std::chrono::steady_clock::now();
    for (int i = 1; i <= sz; ++i) {
        if (v1.capacity() == v1.size()) {
            re1++;
        }
        v1.push_back(i);
    }
    auto v1End = std::chrono::steady_clock::now();

    std::cout << "std::vector laikas su " << sz << ": "
              << (double)std::chrono::duration_cast<std::chrono::milliseconds>(
                     v1End - v1Begin)
                         .count() /
                     1000
              << '\n';
    std::cout << "std::vector atminties perskirstymai: " << re1 << '\n';

    Vector<int> v2;

    int re2 = 0;
    auto v2Begin = std::chrono::steady_clock::now();
    for (int i = 1; i <= sz; ++i) {
        if (v2.capacity() == v2.size()) {
            re2++;
        }
        v2.push_back(i);
    };
    auto v2End = std::chrono::steady_clock::now();

    std::cout << "Vector laikas su 10000: "
              << (double)std::chrono::duration_cast<std::chrono::milliseconds>(
                     v2End - v2Begin)
                         .count() /
                     1000
              << '\n';
    std::cout << "Vector atminties perskirstymai: " << re2 << '\n';

    return 0;
}