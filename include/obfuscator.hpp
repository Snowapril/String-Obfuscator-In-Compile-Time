#ifndef CRYPTOSYSTEM_HPP
#define CRYPTOSYSTEM_HPP

#include <array>
#include "meta_random.hpp"

namespace snowapril {

	template <int A, int B>
	struct ExtendedEuclidian { enum { 
		d = ExtendedEuclidian<B, A % B>::d,
		x = ExtendedEuclidian<B, A % B>::y,
		y = ExtendedEuclidian<B, A % B>::x - (A/B) * ExtendedEuclidian<B, A % B>::y
	}; };

	template <int A>
	struct ExtendedEuclidian<A, 0> { enum { 
		d = A,
		x = 1,
		y = 0
	}; };

	constexpr std::array<int, 30> PrimeNumbers = {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 
		31, 37, 41, 43, 47, 53, 59, 61, 67,
		71, 73, 79, 83, 89, 97, 101, 103, 
		107, 109, 113
	};

	constexpr int positive_modulo(int a, int n) {
		return (a % n + n) % n;
	}

	template <typename Indexes, int A, int B>
	class MetaString;

	template <size_t... I, int A, int B>
	class MetaString<std::index_sequence<I...>, A, B> {
	public:
		constexpr MetaString(char const* str)
			: encrypted_buffer{ encrypt(str[I])... } {};
	public:
		inline const char* decrypt(void) {
			for (size_t i = 0; i < sizeof...(I); ++i) {
				buffer[i] = decrypt(encrypted_buffer[i]);
			}
			buffer[sizeof...(I)] = 0;
			return buffer;
		}
	private:
		constexpr int  encrypt(char c) const { return (A * c + B) % 127; } ;
		constexpr char decrypt(int c) const { return positive_modulo(ExtendedEuclidian<127, A>::y * (c - B), 127); } ;
	private:
		char buffer[sizeof...(I) + 1] {};
		int  encrypted_buffer[sizeof...(I)] {};
	};
}

#define TEST(str) (snowapril::MetaString<std::make_index_sequence<sizeof(str) - 1>, \
					      std::get<snowapril::MetaRandom<__COUNTER__, 30>::value>(snowapril::PrimeNumbers), \
					      snowapril::MetaRandom<__COUNTER__, 126>::value>(str))

#define OBFUSCATE(str) (snowapril::MetaString<std::make_index_sequence<sizeof(str) - 1>, \
					      std::get<snowapril::MetaRandom<__COUNTER__, 30>::value>(snowapril::PrimeNumbers), \
					      snowapril::MetaRandom<__COUNTER__, 126>::value>(str).decrypt())

#endif
