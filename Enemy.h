#pragma once
#include <algorithm>
#define  _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>
#include "Object.h"
#include "Player.h"
#include "Bullet.h"
#include <stdlib.h> 
#include <time.h>

float pi = float(M_PI);

class Enemy : public Object
{
public:
	Enemy(const float position_x_min_, const float radius_, const float velocity_) :
		Object({ 1280, float(rand() % 600 + 100) }, { radius_,  radius_ }, { velocity_, 0 }), position_x_min(position_x_min_){};
	~Enemy(){};

	std::vector<Object*> update(const std::vector<Object*>& current_objects, char* key, char* preKeys) override {
	
		this->position.x += this->velocity.x;

		auto ret = Object::update(current_objects, key, preKeys);
		
		if (this->position.x <= this->position_x_min) {
			this->retired = true;
		}
	
	    // Find player 
		Player* player = nullptr;
		for (auto obj : current_objects) {
			if (dynamic_cast<Player*>(obj) != nullptr) {
				player = dynamic_cast<Player*>(obj);
				if (isConflictPlayer(player)) {
					this->retired = true;
					player->score += 100;
					player->hp -= 1;
				}
			}
		}

		for (auto obj : current_objects) {
			Bullet* bullet = dynamic_cast<Bullet*>(obj);
			if (bullet != nullptr) {
				if (isConflictBullet(bullet)) {
					if (player != nullptr) {
						player->score += 200;
					}
					bullet->retired = true;
					this->retired = true;
				}
			}
		}

		return ret;
	};

	void draw(const Matrix3x3& vpVpMatrix) override {
		const auto screen_position = this->transform_to_draw(vpVpMatrix).to<int>();
		const auto size_int = this->size.to<int>();
		Novice::DrawEllipse(screen_position.x, screen_position.y, size_int.x, size_int.y, 0.0, WHITE, kFillModeSolid);
	}
private:
	float position_x_min;

	bool isConflictPlayer(const Player* player) {
		const float pPlusE = player->getSize().x/2 + this->size.x;
		const auto p2eDelta = player->getPosition() - this->position;
		return (hypotf(p2eDelta.x, p2eDelta.y) <= pPlusE);
	}

	bool isConflictBullet(const Bullet* bullet) {
		const float bPlusE = bullet->size.x + this->size.x; 
		const auto b2eDelta = bullet->position - this->position;
		return (hypotf(b2eDelta.x, b2eDelta.y) <= bPlusE);
	}
};

class EnemyA: public Enemy
{
public:
	EnemyA(const float position_x_min_) :
		Enemy(position_x_min_, 25.0f, -5.0f) {};
	~EnemyA() {};
};

class EnemyB : public Enemy
{
public:
	EnemyB( const float position_x_min_) :
		Enemy(position_x_min_, 20.0f, -7.0f) {};
	~EnemyB() {};
};

class EnemyC : public Enemy
{
public:
	EnemyC(const float position_x_min_) :
		Enemy(position_x_min_, 13.0f, -10.0f) {};
	~EnemyC() {};
};

class EnemyManager : public Object {
public:
	EnemyManager(const int respawn_time_) : respawn_time(respawn_time_), Object({}, {}) {};
	~EnemyManager() {};

	std::vector<Object*> update(const std::vector<Object*>& current_objects, char* key, char* preKeys) override {
		auto ret = Object::update(current_objects, key, preKeys);
		this->counter--;
		if (this->counter <= 0) {
			this->counter = this->respawn_time;
			
			int new_enemy = rand() % 3;
			if (new_enemy == 0) {
				ret.push_back(new EnemyA(0));
			} else if (new_enemy == 1) {
				ret.push_back(new EnemyB(0));
			} else {
				ret.push_back(new EnemyC(0));
			}
			
		}
		return ret;
	};

	void draw(const Matrix3x3& /*vpVpMatrix*/) override {}

private:
	int respawn_time;
	int counter{ respawn_time };
};

