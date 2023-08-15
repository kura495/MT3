#pragma once
#include <Novice.h>
#include<Vector3.h>
#include"Sphere.h"
#include"Line.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<Matrix4x4.h>
#include<cmath>
#include<cassert>
#include<algorithm>
Vector3 Add(const Vector3& v1, const Vector3& v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
float Length(const Vector3& v);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Vector3 Multiply(float scalar, const Vector3& v);
Matrix4x4 Inverse(const Matrix4x4& m);
float det(const Matrix4x4& m);
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float FovY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
//cotangent関数
float cot(float top);
Vector3 Cross(const Vector3& v1, const Vector3& v2);
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* Tag);
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* Tag);
void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix); 
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, unsigned int color);
float Dot(const Vector3& v1, const Vector3& v2);
Vector3 Normalize(const Vector3& v1);
Vector3 Project(const Vector3& v1, const Vector3& v2);
Vector3 ClosestPoint(const Vector3& point, const Segment& segment);
bool IsCollision(const Sphere& s1, const Sphere& s2);