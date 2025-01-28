#if 0 
#include < DxLib.h>

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int model1;
	VECTOR pos = VGet(600.0f, 300.0f, -400.0f);
	int key;
	enum Direction { DOWN, LEFT, UP, RIGHT } direction = DOWN;  // ★★追加

	ChangeWindowMode(TRUE);
	SetGraphMode(1200, 800, 32);
	if (DxLib_Init() == -1) {
		return -1;
	}
	//モデル読み込み
	model1 = MV1LoadModel("Player/PC.mv1");
	if (model1 == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//キー操作
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (key & PAD_INPUT_DOWN) { pos.z -= 4.0f; direction = DOWN; } // ★★修正
		if (key & PAD_INPUT_UP) { pos.z += 4.0f; direction = UP; }     // ★★修正
		if (key & PAD_INPUT_LEFT) { pos.x -= 4.0f; direction = LEFT; } // ★★修正
		if (key & PAD_INPUT_RIGHT) { pos.x += 4.0f; direction = RIGHT; } // ★★修正

		ClearDrawScreen();
		DrawBox(0, 0, 1200, 800, GetColor(255, 255, 255), TRUE);

		MV1SetRotationXYZ(model1, VGet(0.0f, 1.57f * direction, 0.0f));  // ★★追加

		MV1SetPosition(model1, pos);
		MV1DrawModel(model1);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
#endif
