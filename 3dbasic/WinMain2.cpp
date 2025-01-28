#if false
#include < DxLib.h>

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	int model1;
	
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
	
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		DrawBox(0, 0, 600, 400, GetColor(255, 255, 0), TRUE);
		
		MV1DrawModel(model1);
		
		ScreenFlip();
		
	}
	DxLib_End();
	
	return 0;
}
#endif