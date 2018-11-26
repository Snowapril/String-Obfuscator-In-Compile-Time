#ifndef META_RANDOM_HPP
#define META_RANDOM_HPP

#include <limits>

namespace snowapril {

    constexpr int DigitToInt(char c) {
		return c - '0';
	};

	constexpr int RandomSeed(void) {
		constexpr char time[] = __TIME__;

		constexpr int seed = DigitToInt(time[7]) 			+
 							 DigitToInt(time[6]) * 10 		+
 							 DigitToInt(time[4]) * 60 		+
 							 DigitToInt(time[3]) * 600 		+
 							 DigitToInt(time[1]) * 3600 	+
 							 DigitToInt(time[0]) * 36000;

		return seed;
	};

    template <int N>
    struct MetaRandomEngine {
    private:
        static constexpr unsigned int MAX_VALUE = std::numeric_limits<unsigned int>::max();
    public:
        static constexpr unsigned int value = MAX_VALUE * MetaRandomEngine<N - 1>::value;
    };

    template <>
    struct MetaRandomEngine<0> {
        static constexpr unsigned int value = RandomSeed();
    };

    template <int N, int Limit> 
    struct MetaRandom {
        static constexpr unsigned int value = MetaRandomEngine<N>::value % Limit;
    };
}

#endif