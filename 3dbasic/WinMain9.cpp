#if 0
#include < DxLib.h>

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int model1;
	int anim_nutral;
	int anim_run;
	int attachidx;
	int rootflm;            // ★★追加
	bool running = FALSE;   
	float anim_totaltime;
	float playtime = 0.0f;
	VECTOR pos = VGet(600.0f, 300.0f, -400.0f);
	int key;
	enum Direction {
		DOWN,
		LEFT,
		UP,
		RIGHT
	} direction = DOWN;
	MATRIX mat1, mat2;

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
	anim_nutral = MV1LoadModel("Player/Anim_Neutral.mv1");
	if (anim_nutral == -1) {
		return -1;
	}
	anim_run = MV1LoadModel("Player/Anim_Run.mv1");
	if (anim_run == -1) {
		return -1;
	}
	attachidx = MV1AttachAnim(model1, 0, anim_nutral);
	anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);
	rootflm = MV1SearchFrame(model1, "root");                 // ★★追加
	MV1SetFrameUserLocalMatrix(model1, rootflm, MGetIdent()); // ★★追加

	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		//アニメーション進行  
		playtime += 0.5f;
		if (playtime > anim_totaltime) playtime = 0.0f;
		MV1SetAttachAnimTime(model1, attachidx, playtime);

		//キー操作
		key = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		if (key & PAD_INPUT_DOWN) { pos.z -= 4.0f; direction = DOWN; }
		if (key & PAD_INPUT_UP) { pos.z += 4.0f; direction = UP; }
		if (key & PAD_INPUT_LEFT) { pos.x -= 4.0f; direction = LEFT; }
		if (key & PAD_INPUT_RIGHT) { pos.x += 4.0f; direction = RIGHT; }
		if (key == 0) {
			if (running == true) {
				running = false;
				MV1DetachAnim(model1, attachidx);
				attachidx = MV1AttachAnim(model1, 0, anim_nutral);
				anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);
			}
		}
		else {
			if (running == false) {
				running = true;
				MV1DetachAnim(model1, attachidx);
				attachidx = MV1AttachAnim(model1, 0, anim_run);
				anim_totaltime = MV1GetAttachAnimTotalTime(model1, attachidx);
			}
		}

		ClearDrawScreen();
		DrawBox(0, 0, 1200, 800, GetColor(255, 255, 255), TRUE);

		MV1SetRotationXYZ(model1, VGet(0.0f, 1.57f * direction, 0.0f));
		MV1SetPosition(model1, pos);
		// mat1 = MGetRotY(1.57f * direction);
		// mat2 = MGetTranslate(pos);
		// MV1SetMatrix(model1, MMult(mat1, mat2));
		MV1DrawModel(model1);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}
#endif
