#include <Novice.h>
#include<Vector3.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<Matrix4x4.h>
#include<cmath>
#include<cassert>
#include"Function.h"
#include<imGui.h>
const char kWindowTitle[] = "LE2B_11_クラモト_アツシ_MT3";
int kWindowWidth = 1280;
int kWindowHeight = 720;


Vector3 vector1{ 1.2f,-3.9f,2.5f };
Vector3 vector2{ 2.8f,0.4f,-1.3f };
Vector3 cross = Cross(vector1, vector2);

Vector3 screenVertices[3];

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	
	Vector3 rotate{ 0.0f,0.0f,0.0f };
	Vector3 translate{ 0.0f,0.0f,0.0f };
	Vector3 cameraRotate{ 0.1f,0.0f,0.0f };
	Vector3 cameraTranslate{ 0.0f,1.0f,-6.49f };

	Sphere sphere1 = { 0.0f,0.0f, 0.0f, 0.5f };
	int sphereColor = WHITE;
	Sphere sphere2 = { 2.0f,0.0f, 0.0f, 0.5f };

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
		//カメラ
		Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f,1.0f,1.0f}, rotate,translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f,1.0f,1.0f}, cameraRotate, cameraTranslate);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 WorldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		ImGui::Begin("window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		//スフィアのImGui
		ImGui::DragFloat3("Sphere1Center", &sphere1.center.x, 0.01f);
		ImGui::DragFloat("Sphere1Radius", &sphere1.radius, 0.01f);
		ImGui::DragFloat3("Sphere2Center", &sphere2.center.x, 0.01f);
		ImGui::DragFloat("Sphere2Radius", &sphere2.radius, 0.01f);

		if (IsCollision(sphere1,sphere2)==true) {
			sphereColor = RED;
		}
		else {
			sphereColor = WHITE;
		}
		ImGui::End();
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(WorldViewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere1, WorldViewProjectionMatrix, viewportMatrix, sphereColor);
		DrawSphere(sphere2, WorldViewProjectionMatrix, viewportMatrix, WHITE);

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

