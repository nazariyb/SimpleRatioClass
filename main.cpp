#include <iostream>
#include <cassert>

#include "Ratio.h"

using std::cout;
using std::cin;
using std::endl;

using ratio::Ratio;
using RatioInt = Ratio<int>;
using RatioDouble = Ratio<double>;

int main ()
{
    RatioInt r1i{1, 2};
    RatioInt r2i{2, 4};
    RatioInt r3i{4, 2};
    cout << "r1i: " << r1i << endl;
    cout << "r2i: " << r2i << endl;
    cout << "r3i: " << r3i << endl;

    cout << "r1i == r1i: " << (r1i == r1i) << " (true)" << endl;
    cout << "r1i == r2i: " << (r1i == r2i) << " (true)" << endl;
    cout << "r1i != r2i: " << (r1i != r2i) << " (false)" << endl;
    cout << "r1i == 2: " << (r1i == 2) << " (false)" << endl;
    cout << "r1i != 3: " << (r1i != 3) << " (true)" << endl;
    cout << "r3i == 2: " << (r3i == 2) << " (true)" << endl;
    cout << "r3i != 3: " << (r3i != 3) << " (true)" << endl;
    cout << endl;
    cout << "r1i > r2i: " << (r1i > r2i) << " (false)" << endl;
    cout << "r1i > 2: " << (r1i > 2) << " (false)" << endl;
    cout << "2 > r1i: " << (2 > r1i) << " (true)" << endl;
    cout << "r1i >= r2i: " << (r1i >= r2i) << " (true)" << endl;
    cout << "r1i >= 0: " << (r1i >= 0) << " (true)" << endl;
    cout << "1 >= r1i: " << (1 >= r1i) << " (true)" << endl;
    cout << "r1i < r2i: " << (r1i < r2i) << " (false)" << endl;
    cout << "r1i < 2: " << (r1i < 2) << " (true)" << endl;
    cout << "2 < r3i: " << (2 < r3i) << " (false)" << endl;
    cout << "r1i <= r3i: " << (r1i <= r3i) << " (true)" << endl;
    cout << "r1i <= 2: " << (r1i <= 2) << " (true)" << endl;
    cout << "2 <= r1i: " << (2 <= r1i) << " (false)" << endl;
    cout << endl;
    cout << "r1i + r2i: " << r1i + r2i << " (1/1)" << endl; // 1/1
    cout << "r1i + 2: " << r1i + 2 << " (5/2)" << endl; // 5/2
    cout << "1 + r1i: " << 1 + r1i << " (3/2)" << endl; // 3/2
    cout << endl;
    cout << "r1i - r2i: " << r1i - r2i << " (0/1)" << endl; // 0/1
    cout << "r1i - 1: " << r1i - 1 << " (-1/2)" << endl; // -1/2
    cout << "1 - r1i: " << 1 - r1i << " (1/2)" << endl; // 1/2
    cout << endl;
    cout << "r1i * r2i: " << r1i * r2i << " (1/4)" << endl;
    cout << "r1i * 2: " << r1i * 2 << " (1)" << endl;
    cout << "1 * r1i: " << 1 * r1i << " (1/2)" << endl;
    cout << endl;
    cout << "r1i / r2i: " << r1i / r2i << " (1)" << endl;
    cout << "r1i / 1: " << r1i / 1 << " (1/2)" << endl;
    cout << "1 / r1i: " << 1 / r1i << " (2)" << endl;
    cout << endl;

    //    cout << "Enter ratio in form a/b:" << endl;
    //    RatioInt a{};
    //    cin >> a;
    //    cout << "You entered: " << a << endl;

    cout << "1/2 ** 2 = " << pow(RatioInt{1, 2}, 2) << endl;
    cout << "trunc(1/2) = " << trunc(RatioInt{1, 2}) << endl;
    cout << "ceil(1/2) = " << ceil(RatioInt{1, 2}) << endl;
    cout << "floor(1/2) = " << floor(RatioInt{1, 2}) << endl;
    cout << endl;

    cout << "3.0/2.0 ** 2 = " << pow(RatioDouble{3., 2.}, 2) << endl;
    cout << "trunc(3.0/2.0) = " << trunc(RatioDouble{3., 2.}) << endl;
    cout << "ceil(3.0/2.0) = " << ceil(RatioDouble{3., 2.}) << endl;
    cout << "floor(3.0/2.0) = " << floor(RatioDouble{3., 2.}) << endl;
    cout << endl;

    RatioDouble r1d{3.2, 2.4};
    RatioDouble r2d{3.1, 2.5};
    cout << "r1d: " << r1d << endl;
    cout << "r2d: " << r2d << endl;


    std::cout << "Hello, World!" << std::endl;
    return 0;
}