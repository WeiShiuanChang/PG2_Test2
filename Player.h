#pragma once
#include<algorithm>
#include "Bullet.h"
#include "Object.h"

class Player : public Object {
public:
	Player(
		const Vec2<float>& position_,
		const Vec2<float>& size_,
		const Vec2<float>& velocity_,
		const float position_x_min_, const float position_x_max_,
		const float position_y_min_, const float position_y_max_,
		const float bullet_reach_) :
		Object(position_, size_, velocity_), position_x_min(position_x_min_), position_x_max(position_x_max_), position_y_min(position_y_min_), position_y_max(position_y_max_), bullet_reach(bullet_reach_) {}
	~Player() {};

	void reset() {
		this->hp = 5;
		this->score = 0;
	}

	std::vector<Object*> update(const std::vector<Object*>& current_objects, char* key, char* preKeys) override {
		if (key == nullptr) {
			return {};
		}

		this->velocity = Vec2<float>{};
		if (key[DIK_W] || key[DIK_UP]) {
			this->velocity.y = +speed;
		}
		if (key[DIK_S] || key[DIK_DOWN]) {
			this->velocity.y = -speed;
		}
		if (key[DIK_A] || key[DIK_LEFT]) {
			this->velocity.x = -speed;
		}
		if (key[DIK_D] || key[DIK_RIGHT]) {
			this->velocity.x = +speed;
		}

		auto ret = Object::update(current_objects, key, preKeys);

		this->position.x = std::clamp(this->position.x, this->position_x_min, this->position_x_max);
		this->position.y = std::clamp(this->position.y, this->position_y_min, this->position_y_max);

		if (!preKeys[DIK_SPACE] && key[DIK_SPACE]) {
			const auto adjustment = Vec2<float>{ this->size.x, -this->size.y / 2 };
			Bullet* bullet = new Bullet(this->position + adjustment, Vec2<float>{10, 10}, Vec2<float>{20, 0}, bullet_reach);
			ret.push_back(bullet);
		}

		return ret;
	}

	void draw(const Matrix3x3& vpVpMatrix) override {
		const auto screen_position = this->transform_to_draw(vpVpMatrix).to<int>();
		const auto size_int = this->size.to<int>();
		Novice::DrawBox(screen_position.x, screen_position.y, size_int.x, size_int.y, 0.0, 0xff8c00ff, kFillModeSolid);
	}
	const Vec2<float>& getPosition() const { return position; }
	const Vec2<float>& getSize() const { return size; }

	int hp = 5;
	int score = 0;
	static constexpr auto speed = 10;

private:
	float position_x_min;
	float position_x_max;
	float position_y_min;
	float position_y_max;
	float bullet_reach;
};