#pragma once

#include <Vector2.h>
#include <assert.h>
#define _USE_MATH_DEFINES
#include <cmath>

//3x3行列
struct Matrix3x3 {
	float matrix[3][3];
};

//Vector to Matrix
Matrix3x3 MakeVectorToMatrix(const Vec2<float>& V) {
	Matrix3x3 result;
	result.matrix[0][0] = 1;
	result.matrix[0][1] = 0;
	result.matrix[0][2] = 0;
	result.matrix[1][0] = 0;
	result.matrix[1][1] = 1;
	result.matrix[1][2] = 0;
	result.matrix[2][0] = V.x;
	result.matrix[2][1] = V.y;
	result.matrix[2][2] = 1;
	return result;
}
//正射影行列
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	Matrix3x3 result;
	result.matrix[0][0] = float(2.0 / (right - left));
	result.matrix[0][1] = 0;
	result.matrix[0][2] = 0;
	result.matrix[1][0] = 0;
	result.matrix[1][1] = float(2.0 / (top - bottom));
	result.matrix[1][2] = 0;
	result.matrix[2][0] = float((left + right) / (left - right));
	result.matrix[2][1] = float((top + bottom) / (bottom - top));
	result.matrix[2][2] = 1;
	return result;
};
//ビューボード行列
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	Matrix3x3 result;
	result.matrix[0][0] = width / 2;
	result.matrix[0][1] = 0;
	result.matrix[0][2] = 0;
	result.matrix[1][0] = 0;
	result.matrix[1][1] = -(height / 2);
	result.matrix[1][2] = 0;
	result.matrix[2][0] = left + width / 2;
	result.matrix[2][1] = top + height / 2;
	result.matrix[2][2] = 1;
	return result;
};
//逆行列
Matrix3x3 Inverse(const Matrix3x3& A) {
	Matrix3x3 result;
	float det = A.matrix[0][0] * A.matrix[1][1] * A.matrix[2][2] + A.matrix[0][1] * A.matrix[1][2] * A.matrix[2][0] + A.matrix[0][2] * A.matrix[1][0] * A.matrix[2][1] - A.matrix[0][2] * A.matrix[1][1] * A.matrix[2][1] - A.matrix[0][1] * A.matrix[1][0] * A.matrix[2][2] - A.matrix[0][0] * A.matrix[1][2] * A.matrix[2][1];
	result.matrix[0][0] = 1 / det * (A.matrix[1][1] * A.matrix[2][2] - A.matrix[1][2] * A.matrix[2][1]);
	result.matrix[0][1] = 1 / det * -(A.matrix[0][1] * A.matrix[2][2] - A.matrix[0][2] * A.matrix[2][1]);
	result.matrix[0][2] = 1 / det * (A.matrix[0][1] * A.matrix[1][2] - A.matrix[0][2] * A.matrix[1][1]);
	result.matrix[1][0] = 1 / det * -(A.matrix[1][0] * A.matrix[2][2] - A.matrix[1][2] * A.matrix[2][0]);
	result.matrix[1][1] = 1 / det * (A.matrix[0][0] * A.matrix[2][2] - A.matrix[0][2] * A.matrix[2][1]);
	result.matrix[1][2] = 1 / det * -(A.matrix[0][0] * A.matrix[1][2] - A.matrix[0][2] * A.matrix[1][0]);
	result.matrix[2][0] = 1 / det * (A.matrix[1][0] * A.matrix[2][1] - A.matrix[1][1] * A.matrix[2][0]);
	result.matrix[2][1] = 1 / det * -(A.matrix[0][0] * A.matrix[2][1] - A.matrix[0][1] * A.matrix[2][0]);
	result.matrix[2][2] = 1 / det * (A.matrix[0][0] * A.matrix[1][1] - A.matrix[0][1] * A.matrix[1][0]);
	return result;
};
//アフィン変換行列
Matrix3x3 MakeAffineMatrix(const Vec2<float>& scale, float theta, const Vec2<float>& translate) {
	Matrix3x3 result;
	result.matrix[0][0] = scale.x * cosf(theta);
	result.matrix[0][1] = scale.x * sinf(theta);
	result.matrix[0][2] = 0;
	result.matrix[1][0] = scale.y * -sinf(theta);
	result.matrix[1][1] = scale.y * cosf(theta);
	result.matrix[1][2] = 0;
	result.matrix[2][0] = translate.x;
	result.matrix[2][1] = translate.y;
	result.matrix[2][2] = 1;
	return result;
}
//Matrix積
Matrix3x3 Multiply(const Matrix3x3& matrix1, const Matrix3x3& matrix2) {
	Matrix3x3 result = {};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				result.matrix[i][j] += matrix1.matrix[i][k] * matrix2.matrix[k][j];
			}
		}
	}
	return result;
}
//Vector積
Vec2<float> Transform(const Vec2<float>& vector, const Matrix3x3& matrix) {
	Vec2<float> result;
	result.x = vector.x * matrix.matrix[0][0] + vector.y * matrix.matrix[1][0] + 1.0f * matrix.matrix[2][0];
	result.y = vector.x * matrix.matrix[0][1] + vector.y * matrix.matrix[1][1] + 1.0f * matrix.matrix[2][1];
	float w = vector.x * matrix.matrix[0][2] + vector.y * matrix.matrix[1][2] + 1.0f * matrix.matrix[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}