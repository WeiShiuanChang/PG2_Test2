#pragma once
#include <Vector2.h>
#include <Novice.h>
#include <string>

struct Matrix5x5 {
	int m[5][5];
};
struct Rank {
	int M, S;
};
inline void Draw_alphabet(Vector2 pos, int size, unsigned int color, const char Alpha) {
	Matrix5x5 alphabet;
	switch (Alpha) {
	case ' ':
		alphabet = {
			0,0,0,0,0,
			0,0,0,0,0,
			0,0,0,0,0,
			0,0,0,0,0,
			0,0,0,0,0
		};
		break;
	case ':':
		alphabet = {
			0,0,0,0,0,
			0,0,1,0,0,
			0,0,0,0,0,
			0,0,1,0,0,
			0,0,0,0,0
		};
		break;
	case 'A':
		alphabet = {
		0,1,1,1,0,
		1,0,0,0,1,
		1,1,1,1,1,
		1,0,0,0,1,
		1,0,0,0,1
		};
		break;
	case 'B':
		alphabet = {
		1,1,1,1,0,
		1,0,0,0,1,
		1,1,1,1,0,
		1,0,0,0,1,
		1,1,1,1,0
		};
		break;
	case 'C':
		alphabet = {
		0,1,1,1,0,
		1,0,0,0,1,
		1,0,0,0,0,
		1,0,0,0,1,
		0,1,1,1,0,
		};
		break;
	case 'D':
		alphabet = {
		1,1,1,1,0,
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		1,1,1,1,0
		};
		break;
	case 'E':
		alphabet = {
		1,1,1,1,1,
		1,0,0,0,0,
		1,1,1,1,1,
		1,0,0,0,0,
		1,1,1,1,1,
		};
		break;
	case 'F':
		alphabet = {
		1,1,1,1,1,
		1,0,0,0,0,
		1,1,1,1,1,
		1,0,0,0,0,
		1,0,0,0,0,
		};
		break;
	case 'G':
		alphabet = {
		0,1,1,1,0,
		1,0,0,0,0,
		1,0,0,1,1,
		1,0,0,0,1,
		0,1,1,1,0,
		};
		break;
	case 'H':
		alphabet = {
		1,0,0,0,1,
		1,0,0,0,1,
		1,1,1,1,1,
		1,0,0,0,1,
		1,0,0,0,1
		};
		break;
	case 'I':
		alphabet = {
		0,1,1,1,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,1,1,1,0
		};
		break;
	case 'J':
		alphabet = {
		0,1,1,1,0,
		0,0,1,0,0,
		0,0,1,0,0,
		1,0,1,0,0,
		0,1,0,0,0
		};
		break;
	case 'K':
		alphabet = {
		1,0,0,0,1,
		1,0,0,1,0,
		1,0,1,0,0,
		1,1,0,1,0,
		1,0,0,0,1,
		};
		break;
	case 'L':
		alphabet = {
		1,0,0,0,0,
		1,0,0,0,0,
		1,0,0,0,0,
		1,0,0,0,0,
		1,1,1,1,1
		};
		break;
	case 'M':
		alphabet = {
		1,1,1,1,1,
		1,0,1,0,1,
		1,0,1,0,1,
		1,0,1,0,1,
		1,0,1,0,1
		};
		break;
	case 'N':
		alphabet = {
		1,0,0,0,1,
		1,1,0,0,1,
		1,0,1,0,1,
		1,0,0,1,1,
		1,0,0,0,1
		};
		break;
	case 'O':
		alphabet = {
		0,1,1,1,0,
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		0,1,1,1,0
		};
		break;
	case 'P':
		alphabet = {
		1,1,1,1,0,
		1,0,0,0,1,
		1,1,1,1,0,
		1,0,0,0,0,
		1,0,0,0,0,
		};
		break;
	case 'Q':
		alphabet = {
		0,1,1,1,0,
		1,0,0,0,1,
		1,0,1,0,1,
		1,0,0,1,0,
		0,1,1,0,1
		};
		break;
	case 'R':
		alphabet = {
		1,1,1,1,0,
		1,0,0,0,1,
		1,1,1,1,0,
		1,0,0,1,0,
		1,0,0,0,1
		};
		break;
	case 'S':
		alphabet = {
		0,1,1,1,1,
		1,0,0,0,0,
		0,1,1,1,0,
		0,0,0,0,1,
		1,1,1,1,0,
		};
		break;
	case 'T':
		alphabet = {
		1,1,1,1,1,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0
		};
		break;
	case 'U':
		alphabet = {
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		1,1,1,1,1
		};
		break;
	case 'V':
		alphabet = {
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		0,1,0,1,0,
		0,0,1,0,0
		};
		break;
	case 'W':
		alphabet = {
		1,0,1,0,1,
		1,0,1,0,1,
		1,0,1,0,1,
		1,0,1,0,1,
		0,1,0,1,0
		};
		break;
	case 'X':
		alphabet = {
		1,0,0,0,1,
		0,1,0,1,0,
		0,0,1,0,0,
		0,1,0,1,0,
		1,0,0,0,1
		};
		break;
	case 'Y':
		alphabet = {
		1,0,0,0,1,
		0,1,0,1,0,
		0,0,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		};
		break;
	case 'Z':
		alphabet = {
		1,1,1,1,1,
		0,0,0,1,0,
		0,0,1,0,0,
		0,1,0,0,0,
		1,1,1,1,1,
		};
		break;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int X = int(pos.x) + i * size;
			int Y = int(pos.y) + j * size;
			if (alphabet.m[j][i] == 1) {
				Novice::DrawBox(X, Y, size, size, 0.0f, color, kFillModeSolid);
			}
		}
	}
};

inline void Draw_string(const std::string& str, Vector2 pos, int size, int color, float interval) {
	auto i = 0;
	for (const char c : str) {
		Draw_alphabet(Vector2(pos.x + interval * 6 * i, pos.y), size, color, c);
		i++;
	}
}
inline void Draw_Numbers(Vector2 pos, int size, unsigned int color, int number) {
	Matrix5x5 alphabet;
	switch (number) {
	case 0:
		alphabet = {
		0,1,1,1,0,
		1,1,0,0,1,
		1,0,1,0,1,
		1,0,0,1,1,
		0,1,1,1,0
		};
		break;
	case 1:
		alphabet = {
		0,0,1,0,0,
		1,1,1,0,0,
		0,0,1,0,0,
		0,0,1,0,0,
		1,1,1,1,1
		};
		break;
	case 2:
		alphabet = {
		1,1,1,1,1,
		0,0,0,0,1,
		1,1,1,1,1,
		1,0,0,0,0,
		1,1,1,1,1
		};
		break;
	case 3:
		alphabet = {
		1,1,1,1,1,
		0,0,0,0,1,
		1,1,1,1,1,
		0,0,0,0,1,
		1,1,1,1,1
		};
		break;
	case 4:
		alphabet = {
		1,0,0,0,1,
		1,0,0,0,1,
		1,1,1,1,1,
		0,0,0,0,1,
		0,0,0,0,1
		};
		break;
	case 5:
		alphabet = {
		1,1,1,1,1,
		1,0,0,0,0,
		1,1,1,1,1,
		0,0,0,0,1,
		1,1,1,1,1
		};
		break;
	case 6:
		alphabet = {
		1,1,1,1,1,
		1,0,0,0,0,
		1,1,1,1,1,
		1,0,0,0,1,
		1,1,1,1,1
		};
		break;
	case 7:
		alphabet = {
		1,1,1,1,1,
		0,0,0,0,1,
		0,0,0,0,1,
		0,0,0,0,1,
		0,0,0,0,1
		};
		break;
	case 8:
		alphabet = {
		1,1,1,1,1,
		1,0,0,0,1,
		1,1,1,1,1,
		1,0,0,0,1,
		1,1,1,1,1
		};
		break;
	case 9:
		alphabet = {
		1,1,1,1,1,
		1,0,0,0,1,
		1,1,1,1,1,
		0,0,0,0,1,
		1,1,1,1,1
		};
		break;

	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int X = int(pos.x) + i * size;
			int Y = int(pos.y) + j * size;
			if (alphabet.m[j][i] == 1) {
				Novice::DrawBox(X, Y, size, size, 0.0f, color, kFillModeSolid);
			}
		}
	}
}
inline void Draw_string_number(int& Minutes, int& Seconds, int& Millisecond, Vector2 pos, int size, int color, bool flage) {
	if (flage)
	{
		Millisecond++;
		if (Millisecond >= 60)
		{
			Seconds++;
			Millisecond = 0;

		}if (Seconds >= 60)
		{
			Minutes++;
			Seconds = 0;
		}
	}

	Matrix5x5 alphabet = {
	0,0,0,0,0,
	0,0,1,0,0,
	0,0,0,0,0,
	0,0,1,0,0
	};
	Draw_Numbers({ pos.x, pos.y }, size, color, Minutes / 10);
	Draw_Numbers({ pos.x + size * 6, pos.y }, size, color, Minutes % 10);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int X = int(pos.x + size * 11) + i * size;
			int Y = int(pos.y) + j * size;
			if (alphabet.m[j][i] == 1) {
				Novice::DrawBox(X, Y, size, size, 0.0f, color, kFillModeSolid);
			}
		}
	}
	Draw_Numbers({ pos.x + size * 15, pos.y }, size, color, Seconds / 10);
	Draw_Numbers({ pos.x + size * 21, pos.y }, size, color, Seconds % 10);
}

