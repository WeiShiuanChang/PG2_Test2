#include <Novice.h>
#include "Enemy.h"
#include "Player.h"
#include "Scene.h"

const char kWindowTitle[] = "GC1B_09_チョウ_イ_セン_PG2_評価課題2";

enum Scene {
	TITLE,
	INGAME,
	OVER
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	unsigned int currentTime = int(time(nullptr));
	srand(currentTime);

	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	Matrix3x3 cameraMatrix = MakeAffineMatrix(Vec2<float>{ 1.0f, 1.0f }, 0.0f, Vec2<float>{ 640.0f, 360.0f });
	Matrix3x3 viewMatrix = Inverse(cameraMatrix);
	Matrix3x3 orthoMatrix = MakeOrthographicMatrix(-640.0f, 360.0f, 640.0f, -360.0f);
	Matrix3x3 viewportMatrix = MakeViewportMatrix(0, 0, 1280.0f, 720.0f);

	Matrix3x3 vpVpMatrix = Multiply(viewMatrix, orthoMatrix);
	vpVpMatrix = Multiply(vpVpMatrix, viewportMatrix);

	Background* bg = new Background(Vec2<float>{}, Vec2<float>{kWindowWidth, kWindowHeight}, 0x000000ff);
	Background* title = new Background(Vec2<float>{}, Vec2<float>{kWindowWidth, kWindowHeight}, 0x191970ff);
	
	int currentGameState = TITLE;
	bool gamestart = 0;

	Player* player = new Player(Vec2<float>{ 70.0f, 600.0f }, Vec2<float>{ 40.0f, 40.0f }, Vec2<float>{}, 0.0f, (kWindowWidth -100.0f), 90.0f, kWindowHeight, kWindowWidth);
	EnemyManager* enemy_manager = nullptr;

	ObjectSet objects;
	objects.objects = { bg, player };

	int titleGraph = Novice::LoadTexture("./Resources/title.png");
	int gameoverGraph = Novice::LoadTexture("./Resources/gameover.png");

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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
		switch (currentGameState)
		{
		case TITLE:
			if (gamestart != 1 && keys[DIK_RETURN]) {
				gamestart = 1;
				enemy_manager = new EnemyManager(30);
				objects.objects.push_back(enemy_manager);
				player->reset();
				currentGameState = INGAME;
			}
			break;

		case INGAME:
			if (gamestart == 1 && player->hp == 0) {
				gamestart = 0;
				enemy_manager->set_retired();
				enemy_manager = nullptr;

				for (auto obj : objects.objects) {
					Enemy* enemy = dynamic_cast<Enemy*>(obj);
					if (enemy != nullptr) {
						enemy->set_retired();
					}
				}
			}
			if (gamestart == 0) {
				currentGameState = OVER;
			}
			objects.update(keys, preKeys);
			break;

		case OVER:
			if (gamestart != 1 && keys[DIK_R]) {
				currentGameState = TITLE;
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		objects.draw(vpVpMatrix);

		switch (currentGameState)
		{
		case TITLE:
			title->draw(vpVpMatrix);
			Novice::DrawSprite(kWindowWidth /4, kWindowHeight/3, titleGraph, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::ScreenPrintf(kWindowWidth / 4 + 200, kWindowHeight / 3 + 200, "Press [ENTER] key to start");
			break;
		case INGAME:
			for (int i = 0; i < player->hp; i++) {
				Novice::DrawBox(15 + i * 40, 20, 20, 20, 0.0f, 0xff8c00ff, kFillModeSolid);
			}
			//information
			Vec2 line = Transform({ 50,50 }, vpVpMatrix);
			Novice::DrawLine(0, static_cast<int>(line.y), kWindowWidth, static_cast<int>(line.y), WHITE);

			Vec2 scorePos = Transform({ 80,45 }, vpVpMatrix);
			Novice::ScreenPrintf(static_cast<int>(scorePos.x), static_cast<int>(scorePos.y), "Score:%d", player->score);
			break;
		case OVER:
			title->draw(vpVpMatrix);
			Novice::DrawSprite(400, kWindowHeight / 3, gameoverGraph, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::ScreenPrintf(kWindowWidth / 2-10 , kWindowHeight / 3 + 150, "Score:%d", player->score);
			Novice::ScreenPrintf(kWindowWidth / 4 + 220, kWindowHeight / 3 + 200, "Press [R] key to return");
			break;
		}
		

		
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
