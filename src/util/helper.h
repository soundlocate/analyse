#ifndef _HELPER_H
#define _HELPER_H

#include <cstddef>
#include <functional>

template<class T>
inline void hash_combine(std::size_t& seed, const T& v) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

#endif
