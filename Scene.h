#pragma once
#include <Vector2.h>
#include <Novice.h>
#include <string>
#include "Object.h"
#include "Print.h"

class Background : public Object {
public:
	Background(const Vec2<float>& position_, const Vec2<float>& size_, const unsigned int color_) : Object(position_, size_), color(color_) {}
	~Background() {};

	std::vector<Object*> update(const std::vector<Object*>& /*current_objects*/, char* /*key*/, char* /*preKeys*/) override { return {}; }

	void draw(const Matrix3x3& /*vpVpMatrix*/) override {
		const auto position_int = this->position.to<int>();
		const auto size_int = this->size.to<int>();
		Novice::DrawBox(position_int.x, position_int.y, size_int.x, size_int.y, 0.0f, color, kFillModeSolid);
	}
private:
	unsigned int color;
};

inline void Draw_padded_string(const std::string& str, Vector2 pos, int size, int color) {
	const Vector2 padded = { pos.x + size * 2, pos.y + size * 2 };
	auto i = 0;
	for (const char c : str) {
		Draw_alphabet(Vector2(padded.x + size * 6 * i, padded.y), size, color, c);
		i++;
	}
}

class FlashingButton {
public:
	FlashingButton(const std::string& text_, const Vector2& pos_, const int size_) : pos(pos_), size(float(size_)), text(text_) {
		// Do nothing
	}

	static constexpr auto char_blocks = 5;
	static constexpr auto max_chars = 5;
	static constexpr auto border_pad = 2;
	static constexpr auto inter_char_pad = 1;

	inline void draw() {
		this->t += 1;
		if (this->t % 50 == 0) {
			if (this->bar == bar::text) {
				this->bar = bar::space;
			}
			else {
				this->bar = bar::text;
			}
		}

		const auto largeBoxSize = Vector2{ char_blocks * max_chars + inter_char_pad * (max_chars - 1) + border_pad * 2, char_blocks + border_pad * 2 };
		const auto smallBoxSize = Vector2{ char_blocks * max_chars + inter_char_pad * (max_chars - 1) + border_pad * 2 - 2, char_blocks + border_pad * 2 - 2 };

		const auto max_len_pixel = (max_chars * char_blocks + (max_chars - 1) * 1) * size;
		const auto str_len_pixel = (text.length() * char_blocks + (text.length() - 1) * 1) * size;
		const auto padding = (max_len_pixel - str_len_pixel) / 2;

		const auto strPos = Vector2{ pos.x + padding, pos.y };

		if (this->bar == bar::text) {
			Novice::DrawBox(static_cast <int>(pos.x), static_cast <int>(pos.y), static_cast <int>(largeBoxSize.x * size), static_cast <int>(largeBoxSize.y * size), 0.0, 0xbecbe4ff, kFillModeSolid);
			Novice::DrawBox(static_cast <int>(pos.x + (size * 1)), static_cast <int>(pos.y + (size * 1)), static_cast <int>(smallBoxSize.x * size), static_cast <int>(smallBoxSize.y * size), 0.0, 0xdee9feff, kFillModeSolid);
			Draw_padded_string(this->text, strPos, int(this->size), BLACK);
		}
		if (this->bar == bar::space) {
			Novice::DrawBox(static_cast <int>(pos.x), static_cast <int>(pos.y), static_cast <int>(largeBoxSize.x * size), static_cast <int>(largeBoxSize.y * size), 0.0, 0xa6b0c2ff, kFillModeSolid);
			Novice::DrawBox(static_cast <int>(pos.x + (size * 1)), static_cast <int>(pos.y + (size * 1)), static_cast <int>(smallBoxSize.x * size), static_cast <int>(smallBoxSize.y * size), 0.0, 0xbecbe4ff, kFillModeSolid);
			Draw_padded_string("SPACE", this->pos, int(this->size), BLACK);
		}
	};

private:
	Vector2 pos;
	float size;

	enum class bar {
		text, space
	};
	bar bar = bar::text;

	std::string text;
	int t = 1;
};


////title
//
//const float titleSize = 20;
//const Vector2 titlePos = { (1280 - titleSize * (6 * 7)) / 2, 720 / 10 };
//
//inline void Draw_title() {
//	int ran = rand() % 100 + 55; ;
//	int titleColor = 0XffffffFF;
//	Draw_string("TURN", titlePos, static_cast <int>(titleSize), titleColor, titleSize + 1);
//	Draw_string("ON", { titlePos.x + (titleSize * (6 * 4 + 5 + 1)), titlePos.y }, static_cast <int>(titleSize), titleColor, titleSize);
//	Draw_string("THE", { titlePos.x + titleSize * (6 * 2), titlePos.y + titleSize * 6 }, static_cast <int>(titleSize), titleColor, titleSize);
//	Draw_string("LIGHT", { titlePos.x + titleSize * 6, titlePos.y + titleSize * 6 * 2 }, static_cast <int>(titleSize), titleColor, titleSize);
//
//}
//
////gameover
//
//const float overSize = 25;
//const Vector2 overPos = { (640 - overSize * 11.5), 720 / 6 };
//inline void Draw_gameover() {
//	int ran = rand() % 100 + 55; ;
//	int overColor = 0xffffffFF;
//	float secondLine = static_cast <float>(std::fma(overSize, 7, overPos.y));
//	Draw_string("GAME", overPos, static_cast <int>(overSize), overColor, overSize);
//	Draw_string("OVER", { overPos.x,secondLine }, static_cast <int>(overSize), overColor, overSize);
//};
//
