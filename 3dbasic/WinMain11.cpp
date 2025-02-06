#include < DxLib.h>
#include <assert.h>

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1200, 800, 32);
	if (DxLib_Init() == -1) {
		return -1;
	}

	// モデルの読み込み
	int model1 = MV1LoadModel("Player/PC.mv1");
	int stage = MV1LoadModel("Stage/Stage00.mv1");
	int obj1 = MV1LoadModel("stage/Stage_Obj015.mv1");
	// シャドウマップの作成
	int smap = MakeShadowMap(1024, 1024);                // ★★
	SetShadowMapLightDirection(smap, VGet(1, -1, 0));    // ★★
	SetShadowMapDrawArea(smap, VGet(-1000, -1, -1000), VGet(1000, 1000, 1000)); // ★★
	assert(model1 != -1);
	assert(stage != -1);
	assert(obj1 != -1);
	assert(smap != -1);

	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		DrawBox(0, 0, 1200, 800, GetColor(255, 255, 255), TRUE);
		// 位置設定
		MV1SetPosition(model1, VGet(600, 300, -400));
		MV1SetPosition(stage, VGet(600, 255, -400));
		MV1SetPosition(obj1, VGet(500, 255, -400));
		MV1SetRotationXYZ(obj1, VGet(0, 1.57f, 0));
		// シャドウマップに書き込み
		ShadowMap_DrawSetup(smap); // ★★
		MV1DrawModel(stage);       // ★★
		MV1DrawModel(obj1);        // ★★
		MV1DrawModel(model1);      // ★★
		ShadowMap_DrawEnd();       // ★★
		SetUseShadowMap(0, smap);  // ★★
		// モデル描画
		MV1DrawModel(stage);
		MV1DrawModel(obj1);
		MV1DrawModel(model1);
		SetUseShadowMap(0, -1);    // ★★

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}