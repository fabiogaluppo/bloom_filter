/* -------------------------------------------------------------------------------------------------
*
* BLOOM FILTER
* ============
*
* This file:
*    bloom_filter test driver for C++ as header-only
*
* Authors:
*    Fabio Galuppo
*
* Releases: September 18 2022 - v0.1
*    v0.1 - September 2022 - initial release
*
* The MIT License (MIT)
* Copyright © 2022 Fabio Galuppo
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the “Software”), to deal in the Software without
* restriction, including without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or
* substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
* 
------------------------------------------------------------------------------------------------- */

#include "bloom_filter.hpp"

#include <string>
#include <memory>
#include <array>
#include <iostream>

namespace bloom_filter
{
    namespace internal
    {
        template<>
        struct default_hasher_adapter<std::array<int, 3>>
        {
            inline static const void* key(const std::array<int, 3>& value) { return &value[0]; }
            inline static int len(const std::array<int, 3>& value) { return static_cast<int>(sizeof(int) * value.size()); }
        };
    }
}

int main()
{
    using bloom_filter::make_bloom_filter;
    using bloom_filter::bloom_filter;
    
    bool x;

    auto bf = make_bloom_filter<std::string>(100, 0.01);
    x = bf.add("hello");    std::cout << x << ' ';
    x = bf.add("world");    std::cout << x << ' ';
    x = bf.add("hello");    std::cout << x << ' ';
    x = bf.exists("hello"); std::cout << x << ' ';
    x = bf.exists("C++");   std::cout << x << ' ';

    std::cout << '\n';

    auto bf2 = make_bloom_filter<int>(100, 0.01);
    x = bf2.add(111);    std::cout << x << ' ';
    x = bf2.add(222);    std::cout << x << ' ';
    x = bf2.add(111);    std::cout << x << ' ';
    x = bf2.exists(111); std::cout << x << ' ';
    x = bf2.exists(333); std::cout << x << ' ';

    std::cout << '\n';

    bloom_filter<std::string> bf3 = bf;
    x = bf3.add("hello");    std::cout << x << ' ';
    x = bf3.add("world");    std::cout << x << ' ';
    x = bf3.add("hello");    std::cout << x << ' ';
    x = bf3.exists("hello"); std::cout << x << ' ';
    x = bf3.exists("C++");   std::cout << x << ' ';

    std::cout << '\n';
    
    bloom_filter<int> bf4 = std::move(bf2);
    x = bf4.add(111);    std::cout << x << ' ';
    x = bf4.add(222);    std::cout << x << ' ';
    x = bf4.add(111);    std::cout << x << ' ';
    x = bf4.exists(111); std::cout << x << ' ';
    x = bf4.exists(333); std::cout << x << ' ';

    std::cout << '\n';

    auto bf5 = make_bloom_filter<std::array<int, 3>>(100, 0.01);
    x = bf5.add({ 1, 2, 3 });    std::cout << x << ' ';
    x = bf5.add({ 4, 5, 6 });    std::cout << x << ' ';
    x = bf5.add({ 1, 2, 3 });    std::cout << x << ' ';
    x = bf5.exists({ 1, 2, 3 }); std::cout << x << ' ';
    x = bf5.exists({ 6, 7, 8 }); std::cout << x << ' ';

    std::cout << '\n';

    return 0;
}