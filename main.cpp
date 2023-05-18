#include <Novice.h>
#include<Vector3.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"Matrix4x4.h"
#include<cmath>
const char kWindowTitle[] = "LE2B_11_クラモト_アツシ_MT3";

//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top,float right, float bottom, float nearClip, float farClip);
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float FovY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
//cotangent関数
float cot(float top);
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* Tag);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 orthographicMatrix = MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);
		Matrix4x4 perspectiveFovMatrix = MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");
		MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix, "viewportMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip)
{
	Matrix4x4 result = {
	2 / (right - left),0,0,0,
	0,2 / (top - bottom),0,0,
	0,0,1 / (farClip - nearClip),0,
	(left + right) / (left - right),(top + bottom) / (bottom - top),nearClip / (nearClip - farClip),1
	};
	return	result;
}

Matrix4x4 MakePerspectiveFovMatrix(float FovY, float aspectRatio, float nearClip, float farClip)
{
	Matrix4x4 result = {
	(1 / aspectRatio) * cot(FovY /2),0,0,0,
	0,cot(FovY /2),0,0,
	0,0,farClip / (farClip - nearClip),1,
	0,0,(-nearClip * farClip) / (farClip - nearClip),0
	};
	return result;
}



Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth)
{
	Matrix4x4 result = {
	width / 2,0,0,0,
	0,-(height / 2),0,0,
	0,0,maxDepth - minDepth,0,
	left + (width / 2),top + (height / 2),minDepth,1
	};
	return result;
}

float cot(float top)
{
	float result= 1/tan(top);
	return result;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* Tag)
{
	Novice::ScreenPrintf(x, y, Tag);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight + 24, "%6.02f", matrix.m[row][column]);
		}
	}
}