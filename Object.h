#pragma once
#include <vector>
#include "Matrix.h"
#include "Vector2.h"

class Object {
public:
	Object() {}

	Object(const Vec2<float>& position_, const Vec2<float>& size_) : position(position_), size(size_) {}

	Object(const Vec2<float>& position_, const Vec2<float>& size_, const Vec2<float>& velocity_) :
		position(position_), size(size_), velocity(velocity_) {}

	virtual ~Object() {}

	virtual std::vector<Object*> update(const std::vector<Object*>& /*current_objects*/, char* /*key*/, char* /*preKeys*/) {
		this->position += this->velocity;
		return {};
	}

	virtual void draw(const Matrix3x3& vpVpMatrix) = 0;

	bool is_retired() const {
		return retired;
	}
	
	void set_retired() {
		this->retired = true;
	}

protected:
	Vec2<float> transform_to_draw(const Matrix3x3& vpVpMatrix) const {
		return Transform(this->position, vpVpMatrix);
	}

	Vec2<float> position{};
	Vec2<float> size{};
	Vec2<float> velocity{};
	bool retired = false;
};

class ObjectSet {
public:
	ObjectSet() = default;
	~ObjectSet() = default;

	void update(char* keys, char* preKeys) {
		std::vector<Object*> new_objects{};

		for (auto obj : objects) {
			const auto current_new_objects = obj->update(objects, keys, preKeys);
			new_objects.insert(new_objects.end(), current_new_objects.begin(), current_new_objects.end());
		}

		// Remove everything retired
		this->objects.erase(std::remove_if(
			this->objects.begin(),
			this->objects.end(),
			[](const auto obj) {
				const auto retired = obj->is_retired();
				if (retired) {
					delete obj;
				}
				return retired;
			}), this->objects.end());

		// Push in the new objects
		objects.insert(objects.end(), new_objects.begin(), new_objects.end());
	}

	void draw(const Matrix3x3& vpVpMatrix) {
		for (auto obj : objects) {
			obj->draw(vpVpMatrix);
		}
	}

	std::vector<Object*> objects{};
};