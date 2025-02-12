#pragma once

/// <summary>
/// 2次元ベクトル
/// </summary>

template<typename T> 
struct Vec2 final {
	T x;
	T y;

	Vec2<T> operator-(const Vec2<T>& rhs) const { return Vec2{this->x - rhs.x, this->y - rhs.y}; }

	Vec2<T> operator+(const Vec2<T>& rhs) const { return Vec2{this->x + rhs.x, this->y + rhs.y}; }

	Vec2<T> operator+=(const Vec2<T>& rhs) {
		*this = *this + rhs;
		return *this;
	}

	template<typename R> Vec2<R> to() { return Vec2<R>{static_cast<R>(this->x), static_cast<R>(this->y)}; }
};

// For Novice
struct Vector2 final {
	float x;
	float y;
};