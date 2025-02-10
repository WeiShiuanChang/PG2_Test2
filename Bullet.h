#pragma once
#include <Vector2.h>
#include <cmath>
#include <Novice.h>
#include "Object.h"

class Bullet : public Object {
public:
	Bullet(const Vec2<float>& position_, const Vec2<float>& size_, const Vec2<float>& velocity_, const float position_x_max_) :
		Object(position_, size_, velocity_), position_x_max(position_x_max_) {}
	~Bullet() {};

	std::vector<Object*> update(const std::vector<Object*>& current_objects, char* key, char* preKeys) override {
		auto ret = Object::update(current_objects, key, preKeys);

		if (this->position.x - this->size.x > this->position_x_max) {
			this->retired = true;
		}

		return ret;
	}

	void draw(const Matrix3x3& vpVpMatrix) override {
		const auto screen_position = this->transform_to_draw(vpVpMatrix).to<int>();
		const auto size_int = this->size.to<int>();
		Novice::DrawEllipse(screen_position.x, screen_position.y, size_int.x, size_int.y, 0.0, RED, kFillModeSolid);
	}

	friend class Enemy;
private:
	float position_x_max;
};
