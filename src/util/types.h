#ifndef _TYPES_H
#define _TYPES_H

#include <cinttypes>
#include <cmath>
#include <ostream>

#include "helper.h"

typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

template<typename valueType>
union Vector2D {
	valueType comp[2];
	struct {
		valueType x;
		valueType y;
	};

	Vector2D() : x(), y() {}
	Vector2D(valueType a, valueType b) : x(a), y(b) {}
	Vector2D(const Vector2D& other) {
		this->x = other.x;
		this->y = other.y;
	}

	template<typename VT>
	friend std::ostream& operator<<(std::ostream &output, const Vector2D<VT>& vec) {
		return output << "[" << vec.x << ", " << vec.y << "]";
	}

	Vector2D<valueType> operator+(const Vector2D<valueType>& rhs) const {
		Vector2D<valueType> vec(*this);
		vec += rhs;
		return vec;
	}

	Vector2D<valueType> operator-(const Vector2D<valueType>& rhs) const {
		Vector2D<valueType> vec(*this);
		vec -= rhs;
		return vec;
	}

	Vector2D<valueType> operator-() const {
		Vector2D<valueType> vec(*this);
		vec -= Vector2D<valueType>();
		return vec;
	}

	Vector2D<valueType>& operator+=(const Vector2D<valueType>& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}

	Vector2D<valueType>& operator-=(const Vector2D<valueType>& rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}

	template<typename scalaType>
	Vector2D<valueType>& operator/=(const scalaType& rhs) {
		this->x /= rhs;
		this->y /= rhs;

		return *this;
	}

	bool operator==(const Vector2D<valueType>& rhs) const {
		return (this->x == rhs.x) && (this->y == rhs.y);
	}

	auto norm() -> decltype(x * x + y * y) {
		return std::sqrt(x * x + y * y);
	}
};

template<typename valueType>
union Vector3D {
	valueType comp[3];
	struct {
		valueType x;
		valueType y;
		valueType z;
	};

	Vector3D() : x(), y(), z() {}
	Vector3D(valueType a, valueType b, valueType c) : x(a), y(b), z(c) {}
	Vector3D(const Vector3D& other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	template<typename VT>
	friend std::ostream& operator<<(std::ostream &output, const Vector3D<VT>& vec) {
		return output << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]";
	}

	Vector3D<valueType> operator+(const Vector3D<valueType>& rhs) const {
		Vector3D<valueType> vec(*this);
		vec += rhs;
		return vec;
	}

	Vector3D<valueType> operator-(const Vector3D<valueType>& rhs) const {
		Vector3D<valueType> vec(*this);
		vec -= rhs;
		return vec;
	}

	Vector3D<valueType> operator-() const {
		Vector3D<valueType> vec(*this);
		vec -= Vector3D<valueType>();
		return vec;
	}


	Vector3D<valueType>& operator+=(const Vector3D<valueType>& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}

	Vector3D<valueType>& operator-=(const Vector3D<valueType>& rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}

	template<typename scalaType>
	Vector3D<valueType>& operator/=(const scalaType& rhs) {
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;

		return *this;
	}

	bool operator==(const Vector3D<valueType>& rhs) const {
		return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z);
	}

	auto norm() -> decltype(x * x + y * y + z * z) {
		return std::sqrt(x * x + y * y + z * z);
	}

	template<typename otherType>
	auto dotP(const Vector3D<otherType>& rhs) -> decltype(x * rhs.x + y * rhs.y + z * rhs.z) {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
};

template<typename valueType>
union Vector4D {
	valueType comp[4];
	struct {
		valueType x;
		valueType y;
		valueType z;
		valueType w;
	};

	Vector4D() : x(), y(), z(), w() {}
	Vector4D(valueType a, valueType b, valueType c, valueType d) : x(a), y(b), z(c), w(d) {}
	Vector4D(const Vector4D& other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
	}

	template<typename VT>
	friend std::ostream& operator<<(std::ostream &output, const Vector4D<VT>& vec) {
		return output << "[" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << "]";
	}

	Vector4D<valueType> operator+(const Vector4D<valueType>& rhs) const{
		Vector4D<valueType> vec(*this);
		vec += rhs;
		return vec;
	}

	Vector4D<valueType> operator-(const Vector4D<valueType>& rhs) const{
		Vector4D<valueType> vec(*this);
		vec -= rhs;
		return vec;
	}

	Vector4D<valueType> operator-() const {
		Vector4D<valueType> vec(*this);
		vec -= Vector4D<valueType>();
		return vec;
	}

	Vector4D<valueType>& operator+=(const Vector4D<valueType>& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->w += rhs.w;

		return *this;
	}

	Vector4D<valueType>& operator-=(const Vector4D<valueType>& rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->w -= rhs.w;

		return *this;
	}

	template<typename scalaType>
	Vector4D<valueType>& operator/=(const scalaType& rhs) {
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		this->w /= rhs;

		return *this;
	}


	bool operator==(const Vector4D<valueType>& rhs) const {
		return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z) && (this->w == rhs.w);
	}

	auto norm() -> decltype(x * x + y * y + z * z + w * w) {
		return std::sqrt(x * x + y * y + z * z + w * w);
	}
};

typedef Vector2D<double> v2;
typedef Vector3D<double> v3;
typedef Vector4D<double> v4;

namespace std {
	template<typename valueType>
	struct hash<Vector2D<valueType>> : public std::unary_function<const Vector2D<valueType>&, std::size_t> {
		inline std::size_t operator()(const Vector2D<valueType>& vec) const {
			std::size_t seed = 0;
			hash_combine(seed, vec.x);
			hash_combine(seed, vec.y);

			return seed;
		}
	};

	template<typename valueType>
	struct hash<Vector3D<valueType>> : public std::unary_function<const Vector3D<valueType>&, std::size_t> {
		inline std::size_t operator()(const Vector3D<valueType>& vec) const {
			std::size_t seed = 0;
			hash_combine(seed, vec.x);
			hash_combine(seed, vec.y);
			hash_combine(seed, vec.z);

			return seed;
		}
	};

	template<typename valueType>
	struct hash<Vector4D<valueType>> : public std::unary_function<const Vector4D<valueType>&, std::size_t> {
		inline std::size_t operator()(const Vector4D<valueType>& vec) const {
			std::size_t seed = 0;
			hash_combine(seed, vec.x);
			hash_combine(seed, vec.y);
			hash_combine(seed, vec.z);
			hash_combine(seed, vec.w);

			return seed;
		}
	};
}


#endif
