#ifndef META_RANDOM_HPP
#define META_RANDOM_HPP

#include <limits>

namespace snowapril {

    constexpr int DigitToInt(char c) {
		return c - '0';
	};

	constexpr int RandomSeed(void) {
		constexpr char time[] = __TIME__;

		constexpr int seed = DigitToInt(time[7]) 		+
 				     DigitToInt(time[6]) * 10 		+
				     DigitToInt(time[4]) * 60 		+
				     DigitToInt(time[3]) * 600 		+
				     DigitToInt(time[1]) * 3600 	+
				     DigitToInt(time[0]) * 36000;

		return seed;
	};

    template <unsigned int a,
              unsigned int c,
              unsigned int seed,
              unsigned int Limit>
    struct LinearCongruentialEngine {
        enum { value = (a * LinearCongruentialEngine<a, c - 1, seed, Limit>::value + c) % Limit };
    };

    template <unsigned int a,
              unsigned int seed,
              unsigned int Limit>
    struct LinearCongruentialEngine<a, 0, seed, Limit> {
        enum { value = (a * seed) % Limit };
    };

    template <int N, int Limit> 
    struct MetaRandom {
        enum { value = LinearCongruentialEngine<16807, N, RandomSeed(), Limit>::value };
    };

}

#endif
