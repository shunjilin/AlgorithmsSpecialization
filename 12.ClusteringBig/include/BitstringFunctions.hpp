#ifndef BITSTRING_FUNCTIONS_HPP
#define BITSTRING_FUNCTIONS_HPP

namespace BitstringFunctions {

    unsigned nOnes(int bitstring) {
        unsigned count = 0;
        while (bitstring != 0) {
            bitstring = bitstring & (bitstring - 1); // changes least significant 1 to 0
            ++count;
        }
        return count;
    }

    unsigned hammingDistance(int u, int v) {
        return nOnes(u ^ v);
    }

    int flipBit(int bitstring, unsigned index) {
        int mask = 1 << index;
        return bitstring ^ mask;
    }

    struct DistanceOneGenerator {
        int bitstring;
        unsigned n_bits;
        bool done = false;
        unsigned index = 0;
        DistanceOneGenerator(int bitstring, unsigned n_bits) :
            bitstring(bitstring), n_bits(n_bits) {}
        int generate() {
            auto generated_bitstring = flipBit(bitstring, index);
            ++index;
            if (index == n_bits) done = true;
            return generated_bitstring;
        }
    };

    struct DistanceTwoGenerator {
        int bitstring;
        unsigned n_bits;
        bool done = false;
        unsigned index1 = 0;
        unsigned index2 = 1;
        DistanceTwoGenerator(int bitstring, unsigned n_bits) :
            bitstring(bitstring), n_bits(n_bits) {}
        int generate() {
            auto generated_bitstring = flipBit(bitstring, index1);
            generated_bitstring = flipBit(generated_bitstring, index2);
            ++index2;
            if (index2 == n_bits) {
                ++index1;
                index2 = index1 + 1;
            }
            if (index2 == n_bits) done = true;
            return generated_bitstring;
        }
    };

}

#endif
