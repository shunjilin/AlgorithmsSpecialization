#ifndef KARATSUBA_HPP
#define KARATSUBA_HPP

#include <deque>
#include <algorithm>
#include <string>

// assumptions:
// - positive inputs TODO: handle negatives

namespace Karatsuba {

    std::deque<char> encode(std::string number) {
        auto encoded = std::deque<char>();
        for (auto digit : number) encoded.push_front(digit - '0');
        return encoded;
    }

    std::string decode(std::deque<char> encoded) {
        std::reverse(std::begin(encoded), std::end(encoded));
        std::for_each(std::begin(encoded), std::end(encoded),
                      [](char &digit){ digit += '0'; });
        return std::string(std::begin(encoded), std::end(encoded));
    }

    void truncate(std::deque<char>&x) {
        int i = x.size() - 1;
        for (; i >=0; --i) {
            if (x[i] != 0) break;
        }
        x.resize(i + 1);
    }

    void makeEvenSize(std::deque<char>& x) {
        if (x.size() % 2 != 0) x.push_back(0);
    }

    void makeSameSize(std::deque<char>&x, std::deque<char>&y) {
        x.size() > y.size() ? y.resize(x.size(), 0) : x.resize(y.size(), 0);   
    }

    std::deque<char> multiplyByTenToPower(std::deque<char> x, int power) {
        for (int i = 0; i < power; ++i) x.push_front(0);
        return x;
    }
    
    std::deque<char> add(std::deque<char>x, std::deque<char>y) {
        makeSameSize(x, y);
        auto output = std::deque<char>(x.size());
        char carry = 0;
        for (std::size_t i = 0; i < x.size(); ++ i) {
            output[i] = x[i] + y[i] + carry;
            carry = 0;
            if (output[i] >= 10) {
                carry = output[i] / 10;
                output[i] %= 10;
            }
        }
        if (carry != 0) output.push_back(carry);
        return output;
    }

    std::deque<char> subtract(std::deque<char>x, std::deque<char>y) { // x-y
        makeSameSize(x,y);
        auto output = std::deque<char>(x.size());
        for (std::size_t i = 0; i < x.size(); ++i) {
            if (x[i] < y[i]) {
                x[i] += 10;
                x[i+1] -= 1;
            }
            output[i] = x[i] - y[i];
        }
        truncate(output);
        return output;
    }
    
    std::deque<char> multiplySingleDigits(std::deque<char>x,
                                             std::deque<char>y) {
        auto output = std::deque<char>(1, x[0] * y[0]);
        if (output[0] >= 10) {
            output.push_back(output[0] / 10);
            output[0] %= 10;
        }
        return output;
    }    

    // least significant integer is at 0-index
    std::deque<char> multiplyHelper(std::deque<char>x, std::deque<char>y) {
        if (x.size() == 1 && y.size() == 1) return multiplySingleDigits(x, y);
        if (x.size() % 2 != 0) x.push_back(0);
        if (y.size() % 2 != 0) y.push_back(0);
        if (x.size() != y.size()) makeSameSize(x, y);
        int mid_idx = x.size() / 2;
        auto b = std::deque<char>(std::begin(x), std::begin(x) + mid_idx);
        auto a = std::deque<char>(std::begin(x) + mid_idx, std::end(x));
        auto d = std::deque<char>(std::begin(y), std::begin(y) + mid_idx);
        auto c = std::deque<char>(std::begin(y) + mid_idx, std::end(y));

        auto ac = multiplyHelper(a, c);
        auto bd = multiplyHelper(b, d);
        auto intermediate = multiplyHelper(add(a,b), add(c,d));
        
        auto ad_plus_bc
            = subtract(subtract(multiplyHelper(add(a, b), add(c, d)),ac), bd);
        
        auto result = add(add(multiplyByTenToPower(ac, x.size()),
                              multiplyByTenToPower(ad_plus_bc, x.size()/2)),
                          bd);
        truncate(result);
        return result;
    }
    
    std::string multiply(std::string x, std::string y) {
        return decode(multiplyHelper(encode(x), encode(y)));
    }
};
#endif
