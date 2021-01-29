//########## ヘッダーファイル読み込み ##########
#include "DxLib.h"
#include "resource.h"

//########## マクロ定義 ##########
#define GAME_WIDTH			960	//画面の横の大きさ
#define GAME_HEIGHT			640	//画面の縦の大きさ
#define GAME_COLOR			32	//画面のカラービット

#define GAME_WINDOW_BAR		0	//タイトルバーはデフォルトにする
#define GAME_WINDOW_NAME	"GAME TITLE"	//ウィンドウのタイトル

#define GAME_FPS			60	//FPSの数値	

//マウスのボタン
#define MOUSE_BUTTON_CODE	129		//0x0000〜0x0080まで

//パスの長さ
#define PATH_MAX			255	//255文字まで
#define NAME_MAX			255	//255文字まで


//エラーメッセージ
#define IMAGE_LOAD_ERR_TITLE	TEXT("画像読み込みエラー")

//画像のパス
#define IMAGE_BACK_PATH			TEXT(".\\IMAGE\\プレイ.png")	//背景の画像
#define IMAGE_PLAYER_PATH		TEXT(".\\IMAGE\\プレイヤー.png")	//プレイヤーの画像
//#define IMAGE_TEKI_PATH		TEXT(".\\IMAGE\\teki.png")	//敵の画像


#define IMAGE_TITLE_BK_PATH			TEXT(".\\IMAGE\\タイトル.png")		//タイトル背景の画像
#define IMAGE_TITLE_ROGO_PATH		TEXT(".\\IMAGE\\ゲームタイトル.png")	//タイトルロゴの画像
#define IMAGE_TITLE_ROGO_ROTA		0.005		//拡大率
#define IMAGE_TITLE_ROGO_ROTA_MAX	1.0			//拡大率MAX
#define IMAGE_TITLE_ROGO_X_SPEED	1			//X移動速度
#define IMAGE_TITLE_START_PATH		TEXT(".\\IMAGE\\title_start.png")	//タイトルスタートの画像
#define IMAGE_TITLE_START_CNT		1			//点滅カウンタ
#define IMAGE_TITLE_START_CNT_MAX	30			//点滅カウンタMAX

#define IMAGE_END_COMP_PATH		TEXT(".\\IMAGE\\エンド.png")	//エンドコンプ画像
#define IMAGE_END_COMP_CNT		1			//点滅カウンタ
#define IMAGE_END_COMP_CNT_MAX	30			//点滅カウンタMAX

#define IMAGE_END_FAIL_PATH		TEXT(".\\IMAGE\\エンド.png")	//エンドフォール画像
#define IMAGE_END_FAIL_CNT		1			//点滅カウンタ
#define IMAGE_END_FAIL_CNT_MAX	30			//点滅カウンタMAX

//エラーメッセージ
#define MUSIC_LOAD_ERR_TITLE	TEXT("音楽読み込みエラー")

//音楽のパス

#define MUSIC_BGM_TITLE_PATH		TEXT(".\\MUSIC\\タイトル.mp3")	//タイトルのBGM
#define MUSIC_BGM_PATH				TEXT(".\\MUSIC\\プレイ.mp3")	//プレイBGM		
#define MUSIC_BGM_COMP_PATH			TEXT(".\\MUSIC\\エンド.mp3")	//コンプリートBGM
#define MUSIC_BGM_FAIL_PATH			TEXT(".\\MUSIC\\エンド.mp3")	//フォールトBGM

#define MAP_PATH		TEXT(".\\IMAGE\\mapchip1.png")			//マップの画像
#define MAP_PATH_CSV	TEXT(".\\IMAGE\\mapchip1.csv")	

#define GAME_MAP_TATE_MAX	8	//マップの縦の数
#define GAME_MAP_YOKO_MAX	15	//マップの横の数
#define GAME_MAP_KIND_MAX	2	//マップの種類の数

#define GAME_MAP_PATH		TEXT(".\\IMAGE\\mapchip1.png")	//マップの画像

#define MAP_DIV_WIDTH		32	//画像を分割する幅サイズ
#define MAP_DIV_HEIGHT		32	//画像を分割する高さサイズ
#define MAP_DIV_TATE		32	//画像を縦に分割する数
#define MAP_DIV_YOKO		41	//画像を横に分割する数
#define MAP_DIV_NUM	MAP_DIV_TATE * MAP_DIV_YOKO	//画像を分割する総数

//エラーメッセージ
#define START_ERR_TITLE		TEXT("スタート位置エラー")
#define START_ERR_CAPTION	TEXT("スタート位置が決まっていません")

#define GOAL_ERR_TITLE		TEXT("ゴール位置エラー")
#define GOAL_ERR_CAPTION	TEXT("ゴール位置が決まっていません")

#define MOUSE_R_CLICK_TITLE   TEXT("ゲーム中断")
#define MOUSE_R_CLICK_CAPTION   TEXT("ゲームを中断し、タイトル画面に戻りますか？")

enum GAME_MAP_KIND{
	n = -1,	//(NONE)未定
	k = 14,	//壁
	t = 9,	//通路
	s = 5,	//スタート
	g = 3	//ゴール
};	//マップの種類


enum GAME_SCENE {
	GAME_SCENE_START,
	GAME_SCENE_PLAY,
	GAME_SCENE_END,
};	//ゲームのシーン

enum GAME_END {
	GAME_END_COMP,	//コンプリート
	GAME_END_FAIL	//フォールト
};	//ゲームの終了状態

enum CHARA_SPEED {
	CHARA_SPEED_LOW = 1,
	CHARA_SPEED_MIDI = 2,
	CHARA_SPEED_HIGH = 3
};	//キャラクターのスピード

enum CHARA_RELOAD {
	CHARA_RELOAD_LOW = 60,
	CHARA_RELOAD_MIDI = 30,
	CHARA_RELOAD_HIGH = 15
};	//キャラクターのリロード

//int型のPOINT構造体
typedef struct STRUCT_I_POINT
{
	int x = -1;	//座標を初期化
	int y = -1;	//座標を初期化
}iPOINT;

//マウス構造体
typedef struct STRUCT_MOUSE
{
	int InputValue = 0;	//GetMouseInputの値を入れる
	int WheelValue = 0;	//マウスホイールの回転量(奥はプラス値 / 手前はマイナス値)
	iPOINT Point;		//マウスの座標が入る
	iPOINT OldPoint;	//マウスの座標(直前)が入る
	int OldButton[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力(直前)が入る
	int Button[MOUSE_BUTTON_CODE] = { 0 };	//マウスのボタン入力が入る
}MOUSE;

//フォント構造体
typedef struct STRUCT_FONT
{
	char path[PATH_MAX];		//パス
	char name[NAME_MAX];		//フォント名
	int handle;					//ハンドル
	int size;					//大きさ
	int bold;					//太さ
	int type;					//タイプ
	//※タイプは、https://dxlib.xsrv.jp/function/dxfunc_graph2.html#R17N10　を参照

}FONT;

typedef struct STRUCT_IMAGE
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}IMAGE;	//画像構造体

typedef struct STRUCT_MUSIC
{
	char path[PATH_MAX];		//パス
	int handle;					//ハンドル
}MUSIC;	//音楽構造体

typedef struct STRUCT_CHARA
{
	IMAGE image;				//IMAGE構造体
	int speed;					//速さ
	int CenterX;				//中心X
	int CenterY;				//中心Y

	MUSIC musicShot;			//プレイヤーの発射音

	BOOL CanShot;				//ショットできるか
	int ShotReLoadCnt;			//ショットリロード時間
	int ShotReLoadCntMAX;		//ショットリロード時間(MAX)

	RECT coll;					//当たり判定
	iPOINT collBeforePt;		//当たる前の座標

}CHARA;	//キャラクター構造体

typedef struct STRUCT_IMAGE_BACK
{
	IMAGE image;		//IMAGE構造体
	BOOL IsDraw;		//弾を表示できるか
}IMAGE_BACK;	//背景画像の構造体

typedef struct STRUCT_IMAGE_ROTA
{
	IMAGE image;		//IMAGE構造体
	double angle;		//回転率
	double angleMAX;	//回転率MAX
	double rate;		//拡大率
	double rateMAX;		//拡大率MAX

}IMAGE_ROTA;	//回転拡大する画像の構造体

typedef struct STRUCT_IMAGE_BLINK
{
	IMAGE image;		//IMAGE構造体
	int Cnt;			//点滅カウンタ
	int CntMAX;			//点滅する時間MAX
	BOOL IsDraw;		//描画できるか？

}IMAGE_BLINK;	//点滅する画像の構造体

typedef struct STRUCT_MAP_IMAGE
{
	char path[PATH_MAX];				//パス
	int handle[MAP_DIV_NUM];			//分割したの弾の画像ハンドルを取得
	int kind[MAP_DIV_NUM];				//マップの種類
	int width;							//幅
	int height;							//高さ
}MAPCHIP;	//MAP_IMAGE構造体

typedef struct STRUCT_MAP
{
	GAME_MAP_KIND kind;			//マップの種類
	int x;						//X位置
	int y;						//Y位置
	int width;					//幅
	int height;					//高さ
}MAP;	//MAP構造体


//########## グローバル変数 ##########
//FPS関連
int StartTimeFps;				//測定開始時刻
int CountFps;					//カウンタ
float CalcFps;					//計算結果
int SampleNumFps = GAME_FPS;	//平均を取るサンプル数

//キーボードの入力を取得
char AllKeyState[256] = { '\0' };			//すべてのキーの状態が入る
char OldAllKeyState[256] = { '\0' };	//すべてのキーの状態(直前)が入る

//マウスの座標を取得
MOUSE mouse;


int GameScene;		//ゲームシーンを管理

int GameEndKind;					//ゲームの終了状態
RECT GoalRect = { -1,-1, -1, -1 };	//ゴールの当たり判定

IMAGE_BACK ImageBack;	//ゲームの背景

IMAGE ImageTitleBK;						//タイトル背景の画像
IMAGE_ROTA ImageTitleROGO;				//タイトルロゴの画像
IMAGE_BLINK ImageTitleSTART;			//タイトルスタートの画像

IMAGE_BLINK ImageEndCOMP;				//エンドコンプの画像
IMAGE_BLINK ImageEndFAIL;				//エンドフォールの画像

CHARA player;		//ゲームのキャラ

//音楽関連
MUSIC BGM;			//ゲームのBGM

MUSIC BGM_TITLE;	//タイトルのBGM
MUSIC BGM_COMP;		//コンプリートのBGM
MUSIC BGM_FAIL;		//フォールトのBGM

GAME_MAP_KIND mapData[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX]{
	//  0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,
		k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,	// 0
		k,t,t,k,k,t,t,t,k,t,t,t,k,t,g,	// 1
		k,t,k,t,t,t,k,t,k,t,k,k,k,t,k,	// 2
		k,t,k,t,k,t,k,t,k,t,k,k,t,t,k,	// 3
		k,t,k,t,k,t,k,t,k,t,k,k,t,t,k,	// 4
		k,t,t,t,k,t,k,k,k,t,k,k,k,t,k,	// 5
		k,t,k,k,k,t,t,t,t,t,t,t,t,t,k,	// 6
		k,s,k,k,k,k,k,k,k,k,k,k,k,k,k,	// 7
};	//ゲームのマップ

//ゲームマップの初期化
GAME_MAP_KIND mapDataInit[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//マップチップの画像を管理
MAPCHIP mapChip;

//マップの場所を管理
MAP map[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];

//スタートの位置
iPOINT startPt{ -1,-1 };

//マップの当たり判定
RECT mapColl[GAME_MAP_TATE_MAX][GAME_MAP_YOKO_MAX];


//########## プロトタイプ宣言 ##########
VOID MY_FPS_UPDATE(VOID);			//FPS値を計測、更新する
VOID MY_FPS_DRAW(VOID);				//FPS値を描画する
VOID MY_FPS_WAIT(VOID);				//FPS値を計測し、待つ

VOID MY_ALL_KEYDOWN_UPDATE(VOID);	//キーの入力状態を更新する
BOOL MY_KEY_DOWN(int);				//キーを押しているか、キーコードで判断する
BOOL MY_KEY_UP(int);				//キーを押し上げたか、キーコードで判断する
BOOL MY_KEYDOWN_KEEP(int, int);		//キーを押し続けているか、キーコードで判断する

VOID MY_MOUSE_UPDATE(VOID);			//マウスの入力情報を更新する
BOOL MY_MOUSE_DOWN(int);			//ボタンを押しているか、マウスコードで判断する
BOOL MY_MOUSE_UP(int);				//ボタンを押し上げたか、マウスコードで判断する
BOOL MY_MOUSEDOWN_KEEP(int, int);	//ボタンを押し続けているか、マウスコードで判断する

BOOL MY_FONT_INSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にインストール
VOID MY_FONT_UNINSTALL_ONCE(VOID);	//フォントをこのソフト用に、一時的にアンインストール
BOOL MY_FONT_CREATE(VOID);			//フォントを作成する
VOID MY_FONT_DELETE(VOID);			//フォントを削除する

VOID MY_START(VOID);		//スタート画面
VOID MY_START_PROC(VOID);	//スタート画面の処理
VOID MY_START_DRAW(VOID);	//スタート画面の描画

VOID MY_PLAY(VOID);			//プレイ画面
VOID MY_PLAY_PROC(VOID);	//プレイ画面の処理
VOID MY_PLAY_DRAW(VOID);	//プレイ画面の描画

VOID MY_END(VOID);			//エンド画面
VOID MY_END_PROC(VOID);		//エンド画面の処理
VOID MY_END_DRAW(VOID);		//エンド画面の描画

BOOL MY_LOAD_IMAGE(VOID);		//画像をまとめて読み込む関数
VOID MY_DELETE_IMAGE(VOID);		//画像をまとめて削除する関数

BOOL MY_LOAD_MUSIC(VOID);		//音楽をまとめて読み込む関数
VOID MY_DELETE_MUSIC(VOID);		//音楽をまとめて削除する関数

BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT);	//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT, RECT);	//領域の当たり判定をする関数

//########## プログラムで最初に実行される関数 ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);								//ウィンドウモードに設定
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//指定の数値でウィンドウを表示する
	SetWindowStyleMode(GAME_WINDOW_BAR);				//タイトルバーはデフォルトにする
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//ウィンドウのタイトルの文字
	SetAlwaysRunFlag(TRUE);								//非アクティブでも実行する
	//SetWindowIconID(IDI_ICON1);							//アイコンファイルを読込

	if (DxLib_Init() == -1) { return -1; }	//ＤＸライブラリ初期化処理

	//画像を読み込む
	if (MY_LOAD_IMAGE() == FALSE) { return -1; }

	////音楽を読み込む
	//if (MY_LOAD_MUSIC() == FALSE) { return -1; }

	//プレイヤーの設定
	player.CanShot = TRUE;
	player.ShotReLoadCnt = 0;
	player.ShotReLoadCntMAX = CHARA_RELOAD_LOW;

	SetMouseDispFlag(TRUE);			//マウスカーソルを表示

	GameScene = GAME_SCENE_START;	//ゲームシーンはスタート画面から

	SetDrawScreen(DX_SCREEN_BACK);	//Draw系関数は裏画面に描画


	//プレイヤーの最初の位置を、スタート位置にする
	//ゴールの位置もついでに検索する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//スタート位置を探す
			if (mapData[tate][yoko] == s)
			{
				//スタート位置を計算
				startPt.x = mapChip.width * yoko + mapChip.width / 2;	//中心X座標を取得
				startPt.y = mapChip.height * tate + mapChip.height / 2;	//中心Y座標を取得
			}

			//ゴール位置を探す
			if (mapData[tate][yoko] == g)
			{
				GoalRect.left = mapChip.width * yoko;
				GoalRect.top = mapChip.height * tate;
				GoalRect.right = mapChip.width * (yoko + 1);
				GoalRect.bottom = mapChip.height * (tate + 1);
			}
		}
	}

	//スタートが決まっていなければ
	if (startPt.x == -1 && startPt.y == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), START_ERR_CAPTION, START_ERR_TITLE, MB_OK);	return -1;
	}

	//ゴールが決まっていなければ
	if (GoalRect.left == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), GOAL_ERR_CAPTION, GOAL_ERR_TITLE, MB_OK);	return -1;
	}

	//無限ループ
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//メッセージ処理の結果がエラーのとき、強制終了
		if (ClearDrawScreen() != 0) { break; }	//画面を消去できなかったとき、強制終了

		MY_ALL_KEYDOWN_UPDATE();				//押しているキー状態を取得

		MY_MOUSE_UPDATE();						//マウスの状態を取得

		MY_FPS_UPDATE();	//FPSの処理[更新]

		//シーンごとに処理を行う
		switch (GameScene)
		{
		case GAME_SCENE_START:
			MY_START();	//スタート画面
			break;
		case GAME_SCENE_PLAY:
			MY_PLAY();	//プレイ画面
			break;
		case GAME_SCENE_END:
			MY_END();	//エンド画面
			break;
		}

		MY_FPS_DRAW();		//FPSの処理[描画]

		ScreenFlip();		//モニタのリフレッシュレートの速さで裏画面を再描画

		MY_FPS_WAIT();		//FPSの処理[待つ]
	}

	//画像ハンドルを破棄
	MY_DELETE_IMAGE();

	////音楽ハンドルを破棄
	//MY_DELETE_MUSIC();

	DxLib_End();	//ＤＸライブラリ使用の終了処理

	return 0;
}

//########## FPS値を計測、更新する関数 ##########
VOID MY_FPS_UPDATE(VOID)
{
	if (CountFps == 0) //1フレーム目なら時刻を記憶
	{
		StartTimeFps = GetNowCount();
	}

	if (CountFps == SampleNumFps) //60フレーム目なら平均を計算
	{
		int now = GetNowCount();
		//現在の時間から、0フレーム目の時間を引き、FPSの数値で割る＝1FPS辺りの平均時間が計算される
		CalcFps = 1000.f / ((now - StartTimeFps) / (float)SampleNumFps);
		CountFps = 0;
		StartTimeFps = now;
	}
	CountFps++;
	return;
}

//########## FPS値を描画する関数 ##########
VOID MY_FPS_DRAW(VOID)
{
	//文字列を描画
	DrawFormatString(0, GAME_HEIGHT - 20, GetColor(255, 255, 255), "FPS:%.1f", CalcFps);
	return;
}

//########## FPS値を計測し、待つ関数 ##########
VOID MY_FPS_WAIT(VOID)
{
	int resultTime = GetNowCount() - StartTimeFps;					//かかった時間
	int waitTime = CountFps * 1000 / GAME_FPS - resultTime;	//待つべき時間

	if (waitTime > 0)		//指定のFPS値よりも早い場合
	{
		WaitTimer(waitTime);	//待つ
	}
	return;
}

//########## キーの入力状態を更新する関数 ##########
VOID MY_ALL_KEYDOWN_UPDATE(VOID)
{
	//参考：https://dxlib.xsrv.jp/function/dxfunc_input.html

	char TempKey[256];

	//直前のキー入力をとっておく
	for (int i = 0; i < 256; i++)
	{
		OldAllKeyState[i] = AllKeyState[i];
	}

	GetHitKeyStateAll(TempKey); // 全てのキーの入力状態を得る

	for (int i = 0; i < 256; i++)
	{
		if (TempKey[i] != 0)	//押されているキーのキーコードを押しているとき
		{
			AllKeyState[i]++;	//押されている
		}
		else
		{
			AllKeyState[i] = 0;	//押されていない
		}
	}
	return;
}

//キーを押しているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_DOWN(int KEY_INPUT_)
{
	//キーコードのキーを押している時
	if (AllKeyState[KEY_INPUT_] != 0)
	{
		return TRUE;	//キーを押している
	}
	else
	{
		return FALSE;	//キーを押していない
	}
}

//キーを押し上げたか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
BOOL MY_KEY_UP(int KEY_INPUT_)
{
	if (OldAllKeyState[KEY_INPUT_] >= 1	//直前は押していて
		&& AllKeyState[KEY_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//キーを押し上げている
	}
	else
	{
		return FALSE;	//キーを押し上げていない
	}
}

//キーを押し続けているか、キーコードで判断する
//引　数：int：キーコード：KEY_INPUT_???
//引　数：int：キーを押し続ける時間
BOOL MY_KEYDOWN_KEEP(int KEY_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (AllKeyState[KEY_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//マウスの入力情報を更新する
VOID MY_MOUSE_UPDATE(VOID)
{
	//マウスの以前の座標を取得
	mouse.OldPoint = mouse.Point;

	//マウスの以前のボタン入力を取得
	for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { mouse.OldButton[i] = mouse.Button[i]; }

	//マウスの座標を取得
	GetMousePoint(&mouse.Point.x, &mouse.Point.y);

	//マウスの押しているボタンを取得
	mouse.InputValue = GetMouseInput();

	//左ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) == MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_LEFT) != MOUSE_INPUT_LEFT) { mouse.Button[MOUSE_INPUT_LEFT] = 0; }		//押していない

	//中ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) == MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE]++; }	//押している
	if ((mouse.InputValue & MOUSE_INPUT_MIDDLE) != MOUSE_INPUT_MIDDLE) { mouse.Button[MOUSE_INPUT_MIDDLE] = 0; }	//押していない

	//右ボタンを押しているかチェック(TRUEは0以外なので、2も4もTRUE)
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) == MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT]++; }		//押している
	if ((mouse.InputValue & MOUSE_INPUT_RIGHT) != MOUSE_INPUT_RIGHT) { mouse.Button[MOUSE_INPUT_RIGHT] = 0; }	//押していない

	//ホイールの回転量を取得
	mouse.WheelValue = GetMouseWheelRotVol();

	return;
}

//ボタンを押しているか、マウスーコードで判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_DOWN(int MOUSE_INPUT_)
{
	//マウスコードのボタンを押している時
	if (mouse.Button[MOUSE_INPUT_] != 0)
	{
		return TRUE;	//ボタンを押している
	}
	else
	{
		return FALSE;	//ボタンを押していない
	}
}

//ボタンを押し上げたか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
BOOL MY_MOUSE_UP(int MOUSE_INPUT_)
{
	if (mouse.OldButton[MOUSE_INPUT_] >= 1	//直前は押していて
		&& mouse.Button[MOUSE_INPUT_] == 0)	//今は押していないとき
	{
		return TRUE;	//ボタンを押し上げている
	}
	else
	{
		return FALSE;	//ボタンを押し上げていない
	}
}

//ボタンを押し続けているか、マウスコード判断する
//引　数：int：マウスコード：MOUSE_INPUT_???
//引　数：int：ボタンを押し続ける時間
BOOL MY_MOUSEDOWN_KEEP(int MOUSE_INPUT_, int DownTime)
{
	//押し続ける時間=秒数×FPS値
	//例）60FPSのゲームで、1秒間押し続けるなら、1秒×60FPS
	int UpdateTime = DownTime * GAME_FPS;

	if (mouse.Button[MOUSE_INPUT_] > UpdateTime)
	{
		return TRUE;	//押し続けている
	}
	else
	{
		return FALSE;	//押し続けていない
	}
}

//スタート画面
VOID MY_START(VOID)
{
	MY_START_PROC();	//スタート画面の処理
	MY_START_DRAW();	//スタート画面の描画

	return;
}

//スタート画面の処理
VOID MY_START_PROC(VOID)
{
	//BGMが流れていないなら
	if (CheckSoundMem(BGM_TITLE.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM_TITLE.handle);	//50%の音量にする
		PlaySoundMem(BGM_TITLE.handle, DX_PLAYTYPE_LOOP);
	}

	//エンターキーを押したら、プレイシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_RETURN) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM_TITLE.handle) != 0)
		{
			StopSoundMem(BGM_TITLE.handle);	//BGMを止める
		}

		SetMouseDispFlag(FALSE);			//マウスカーソルを非表示


		//プレイヤーの中心位置を計算する
		player.CenterX = startPt.x;
		player.CenterY = startPt.y;

		//プレイヤーの画像の位置を設定する
		player.image.x = player.CenterX;
		player.image.y = player.CenterY;

		//プレイヤーの当たる以前の位置を設定する
		player.collBeforePt.x = player.CenterX;
		player.collBeforePt.y = player.CenterY;

		//スタート位置をマウスの位置にする
		SetMousePoint(player.image.x, player.image.y);

		//ゲームの終了状態を初期化する
		GameEndKind = GAME_END_FAIL;

		GameScene = GAME_SCENE_PLAY;
	}

	//タイトルロゴを拡大
	if (ImageTitleROGO.rate < ImageTitleROGO.rateMAX)
	{
		ImageTitleROGO.rate += IMAGE_TITLE_ROGO_ROTA;
	}

	//タイトルロゴを移動
	if (ImageTitleROGO.image.x < GAME_WIDTH / 2)
	{
		ImageTitleROGO.image.x += IMAGE_TITLE_ROGO_X_SPEED;
	}
	else
	{
		//タイトルロゴが移動しきったら

		//スタートを点滅
		if (ImageTitleSTART.Cnt < ImageTitleSTART.CntMAX)
		{
			ImageTitleSTART.Cnt += IMAGE_TITLE_START_CNT;
		}
		else
		{
			//描画する/しないを決める
			if (ImageTitleSTART.IsDraw == FALSE)
			{
				ImageTitleSTART.IsDraw = TRUE;
			}
			else if (ImageTitleSTART.IsDraw == TRUE)
			{
				ImageTitleSTART.IsDraw = FALSE;
			}
			ImageTitleSTART.Cnt = 0;
		}
	}

	return;
}

//スタート画面の描画
VOID MY_START_DRAW(VOID)
{
	//赤の四角を描画
	/*DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(255, 0, 0), TRUE);*/

	DrawGraph(ImageTitleBK.x, ImageTitleBK.y, ImageTitleBK.handle, TRUE);	//タイトル背景の描画

	//タイトルロゴを回転しながら描画
	DrawRotaGraph(
		ImageTitleROGO.image.x, ImageTitleROGO.image.y,	//画像の座標
		ImageTitleROGO.rate,							//画像の拡大率
		ImageTitleROGO.angle,							//画像の回転率
		ImageTitleROGO.image.handle, TRUE);				//画像のハンドル

	//点滅
	if (ImageTitleSTART.IsDraw == TRUE)
	{
		//タイトルスタートの描画
		DrawGraph(ImageTitleSTART.image.x, ImageTitleSTART.image.y, ImageTitleSTART.image.handle, TRUE);
	}

	DrawString(0, 0, "スタート画面(エンターキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//プレイ画面
VOID MY_PLAY(VOID)
{
	MY_PLAY_PROC();	//プレイ画面の処理
	MY_PLAY_DRAW();	//プレイ画面の描画

	return;
}

//プレイ画面の処理
VOID MY_PLAY_PROC(VOID)
{

	//BGMが流れていないなら
	if (CheckSoundMem(BGM.handle) == 0)
	{
		//BGMの音量を下げる
		ChangeVolumeSoundMem(255 * 50 / 100, BGM.handle);	//50%の音量にする

		//BGMを流す
		//DX_PLAYTYPE_NORMAL:　ノーマル再生
		//DX_PLAYTYPE_BACK  : バックグラウンド再生
		//DX_PLAYTYPE_LOOP  : ループ再生
		PlaySoundMem(BGM.handle, DX_PLAYTYPE_LOOP);
	}

	//マウスを右クリックすると、タイトル画面に戻る
	if (mouse.Button[MOUSE_INPUT_RIGHT] == TRUE)
	{
		//クリックした座標を取得しておく
		iPOINT R_ClickPt = mouse.Point;

		//マウスを表示
		SetMouseDispFlag(TRUE);

		//終了ダイアログを表示
		int Ret = MessageBox(GetMainWindowHandle(), MOUSE_R_CLICK_CAPTION, MOUSE_R_CLICK_TITLE, MB_YESNO);

		if (Ret == IDYES)		//YESなら、ゲームを中断する
		{
			//強制的にタイトル画面に飛ぶ
			GameScene = GAME_SCENE_START;
			return;

		}
		else if (Ret == IDNO)	//NOなら、ゲームを続行する
		{
			//マウスの位置を、クリックする前に戻す
			SetMousePoint(R_ClickPt.x, R_ClickPt.y);

			//マウスを非表示にする。
			SetMouseDispFlag(FALSE);
		}
	}

	//画面内にマウスがいれば
	if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH
		&& mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
	{

		//マウスの当たる前の位置から、現在位置の差がこの数値以内なら、動ける
		int MoveValue = 100;

		//マウスの移動量が少ないときに、移動させる
		if (abs(player.collBeforePt.x - mouse.Point.x) < MoveValue
			&& abs(player.collBeforePt.y - mouse.Point.y) < MoveValue)
		{
			//プレイヤーの中心位置を設定する
			player.CenterX = mouse.Point.x;
			player.CenterY = mouse.Point.y;
		}
		else
		{
			//プレイヤーの中心位置を設定する
			player.CenterX = player.collBeforePt.x;
			player.CenterY = player.collBeforePt.y;

			//マウスの位置を設定する
			SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
		}

	}

	//プレイヤーの当たり判定の設定
	player.coll.left = player.CenterX - mapChip.width / 2 + 5;
	player.coll.top = player.CenterY - mapChip.height / 2 + 5;
	player.coll.right = player.CenterX + mapChip.width / 2 - 5;
	player.coll.bottom = player.CenterY + mapChip.height / 2 - 5;

	BOOL IsMove = TRUE;

	//プレイヤーとマップがあたっていたら
	if (MY_CHECK_MAP1_PLAYER_COLL(player.coll) == TRUE)
	{
		SetMousePoint(player.collBeforePt.x, player.collBeforePt.y);
		IsMove = FALSE;
	}

	if (IsMove == TRUE)
	{
		//画面内にマウスがいれば
		if (mouse.Point.x >= 0 && mouse.Point.x <= GAME_WIDTH
			&& mouse.Point.y >= 0 && mouse.Point.y <= GAME_HEIGHT)
		{
			//プレイヤーの位置に置き換える
			player.image.x = player.CenterX - player.image.width / 2;
			player.image.y = player.CenterY - player.image.height / 2;

			//あたっていないときの座標を取得
			player.collBeforePt.x = player.CenterX;
			player.collBeforePt.y = player.CenterY;
		}
	}

	//当たり判定が追いつかないので、画像の位置を当たり判定に使用する
	//当たり判定の領域は、画像よりも少し縮小する。縮小加減は、お好みで。
	RECT PlayerRect;
	PlayerRect.left = player.image.x + 40;
	PlayerRect.top = player.image.y + 40;
	PlayerRect.right = player.image.x + player.image.width - 40;
	PlayerRect.bottom = player.image.y + player.image.height - 40;

	//ゴールに触れているかチェック
	if (MY_CHECK_RECT_COLL(PlayerRect, GoalRect) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);		//マウスカーソルを表示

		GameEndKind = GAME_END_COMP;	//ミッションコンプリート！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//プレイヤーが画面外に出たら
	if (player.image.x > GAME_WIDTH || player.image.y > GAME_HEIGHT
		|| player.image.x + player.image.width < 0 || player.image.y + player.image.height < 0)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM.handle) != 0)
		{
			StopSoundMem(BGM.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);			//マウスカーソルを表示

		GameEndKind = GAME_END_FAIL;	//ミッションフォールト！

		GameScene = GAME_SCENE_END;

		return;	//強制的にエンド画面に飛ぶ
	}

	//ショットが撃てないとき
	if (player.CanShot == FALSE)
	{
		//リロード時間が終わったとき
		if (player.ShotReLoadCnt == player.ShotReLoadCntMAX)
		{
			player.ShotReLoadCnt = 0;
			player.CanShot = TRUE;		//再びショットできる
		}

		player.ShotReLoadCnt++;	//リロードする
	}


	ImageBack.IsDraw = true;

	return;
}

//プレイ画面の描画
VOID MY_PLAY_DRAW(VOID)
{
	//背景を描画する

			//背景を描画
	DrawGraph(ImageBack.image.x, ImageBack.image.y, ImageBack.image.handle, TRUE);


	/*プレイヤーを描画する*/
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

	//敵の描画
	/*DrawGraph(teki.image.x, teki.image.y, teki.image.handle, TRUE);*/




	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップを描画
			DrawGraph(
				map[tate][yoko].x,
				map[tate][yoko].y,
				mapChip.handle[map[tate][yoko].kind],
				TRUE);
		}
	}


	//プレイヤーを描画する
	DrawGraph(player.image.x, player.image.y, player.image.handle, TRUE);

}

//エンド画面
VOID MY_END(VOID)
{
	MY_END_PROC();	//エンド画面の処理
	MY_END_DRAW();	//エンド画面の描画
	return;
}

//エンド画面の処理
VOID MY_END_PROC(VOID)
{


	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//コンプリートのとき

		//BGMが流れていないなら
		if (CheckSoundMem(BGM_COMP.handle) == 0)
		{
			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_COMP.handle);	//50%の音量にする
			PlaySoundMem(BGM_COMP.handle, DX_PLAYTYPE_LOOP);
		}

		//コンプリートを点滅
		if (ImageEndCOMP.Cnt < ImageEndCOMP.CntMAX)
		{
			ImageEndCOMP.Cnt += IMAGE_END_COMP_CNT;
		}
		else
		{
			//描画する/しないを決める
			if (ImageEndCOMP.IsDraw == FALSE)
			{
				ImageEndCOMP.IsDraw = TRUE;
			}
			else if (ImageEndCOMP.IsDraw == TRUE)
			{
				ImageEndCOMP.IsDraw = FALSE;
			}
			ImageEndCOMP.Cnt = 0;
		}
		break;

	case GAME_END_FAIL:
		//フォールトのとき

		//BGMが流れていないなら
		if (CheckSoundMem(BGM_FAIL.handle) == 0)
		{
			//BGMの音量を下げる
			ChangeVolumeSoundMem(255 * 50 / 100, BGM_FAIL.handle);	//50%の音量にする
			PlaySoundMem(BGM_FAIL.handle, DX_PLAYTYPE_LOOP);
		}

		//フォールトを点滅
		if (ImageEndFAIL.Cnt < ImageEndFAIL.CntMAX)
		{
			ImageEndFAIL.Cnt += IMAGE_END_FAIL_CNT;
		}
		else
		{
			//描画する/しないを決める
			if (ImageEndFAIL.IsDraw == FALSE)
			{
				ImageEndFAIL.IsDraw = TRUE;
			}
			else if (ImageEndFAIL.IsDraw == TRUE)
			{
				ImageEndFAIL.IsDraw = FALSE;
			}
			ImageEndFAIL.Cnt = 0;
		}
		break;
	}
	//エスケープキーを押したら、スタートシーンへ移動する
	if (MY_KEY_DOWN(KEY_INPUT_ESCAPE) == TRUE)
	{
		//BGMが流れているなら
		if (CheckSoundMem(BGM_COMP.handle) != 0)
		{
			StopSoundMem(BGM_COMP.handle);	//BGMを止める
		}

		//BGMが流れているなら
		if (CheckSoundMem(BGM_FAIL.handle) != 0)
		{
			StopSoundMem(BGM_FAIL.handle);	//BGMを止める
		}

		SetMouseDispFlag(TRUE);		//マウスカーソルを表示

		GameScene = GAME_SCENE_START;
	}
	return;
}

//エンド画面の描画
VOID MY_END_DRAW(VOID)
{
	//青の四角を描画
	/*DrawBox(10, 10, GAME_WIDTH - 10, GAME_HEIGHT - 10, GetColor(0, 0, 255), TRUE);*/

	MY_PLAY_DRAW();	//プレイ画面を描画

	//ゲームの終了状態により、描画を変える
	switch (GameEndKind)
	{
	case GAME_END_COMP:
		//コンプリートのとき

		//点滅

			//コンプリートの描画
		DrawGraph(ImageEndCOMP.image.x, ImageEndCOMP.image.y, ImageEndCOMP.image.handle, TRUE);

		break;

	case GAME_END_FAIL:
		//フォールトのとき

		//点滅

			//フォールトの描画
		DrawGraph(ImageEndFAIL.image.x, ImageEndFAIL.image.y, ImageEndFAIL.image.handle, TRUE);

		break;

	}

	DrawString(0, 0, "エンド画面(エスケープキーを押して下さい)", GetColor(255, 255, 255));
	return;
}

//画像をまとめて読み込む関数
BOOL MY_LOAD_IMAGE(VOID)
{
	//タイトル背景
	strcpy_s(ImageTitleBK.path, IMAGE_TITLE_BK_PATH);			//パスの設定
	ImageTitleBK.handle = LoadGraph(ImageTitleBK.path);			//読み込み
	if (ImageTitleBK.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_BK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleBK.handle, &ImageTitleBK.width, &ImageTitleBK.height);	//画像の幅と高さを取得
	ImageTitleBK.x = GAME_WIDTH / 2 - ImageTitleBK.width / 2;		//左右中央揃え
	ImageTitleBK.y = GAME_HEIGHT / 2 - ImageTitleBK.height / 2;		//上下中央揃え

	//タイトルロゴ
	strcpy_s(ImageTitleROGO.image.path, IMAGE_TITLE_ROGO_PATH);					//パスの設定
	ImageTitleROGO.image.handle = LoadGraph(ImageTitleROGO.image.path);			//読み込み
	if (ImageTitleROGO.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_ROGO_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleROGO.image.handle, &ImageTitleROGO.image.width, &ImageTitleROGO.image.height);	//画像の幅と高さを取得
	ImageTitleROGO.image.x = 230;							//光っている部分から描画したい
	ImageTitleROGO.image.y = GAME_HEIGHT / 2;				//中央寄せ
	ImageTitleROGO.angle = DX_PI * 2;						//回転率
	ImageTitleROGO.angleMAX = DX_PI * 2;					//回転率MAX
	ImageTitleROGO.rate = 0.0;								//拡大率
	ImageTitleROGO.rateMAX = IMAGE_TITLE_ROGO_ROTA_MAX;		//拡大率MAX

	//タイトルスタート
	strcpy_s(ImageTitleSTART.image.path, IMAGE_TITLE_START_PATH);					//パスの設定
	ImageTitleSTART.image.handle = LoadGraph(ImageTitleSTART.image.path);			//読み込み
	if (ImageTitleSTART.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_TITLE_START_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageTitleSTART.image.handle, &ImageTitleSTART.image.width, &ImageTitleSTART.image.height);	//画像の幅と高さを取得
	ImageTitleSTART.image.x = GAME_WIDTH / 2 - ImageTitleSTART.image.width / 2;					//左右中央揃え
	ImageTitleSTART.image.y = ImageTitleROGO.image.y + ImageTitleROGO.image.height / 2 + 10;	//ロゴの下に表示
	ImageTitleSTART.Cnt = 0.0;								//カウンタ
	ImageTitleSTART.CntMAX = IMAGE_TITLE_START_CNT_MAX;		//カウンタMAX
	ImageTitleSTART.IsDraw = FALSE;							//描画させない

	//エンドコンプ
	strcpy_s(ImageEndCOMP.image.path, IMAGE_END_COMP_PATH);					//パスの設定
	ImageEndCOMP.image.handle = LoadGraph(ImageEndCOMP.image.path);			//読み込み
	if (ImageEndCOMP.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_END_COMP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndCOMP.image.handle, &ImageEndCOMP.image.width, &ImageEndCOMP.image.height);	//画像の幅と高さを取得
	ImageEndCOMP.image.x = GAME_WIDTH / 2 - ImageEndCOMP.image.width / 2;			//左右中央揃え
	ImageEndCOMP.image.y = GAME_HEIGHT / 2 - ImageEndCOMP.image.height / 2;			//上下中央揃え
	ImageEndCOMP.Cnt = 0.0;									//カウンタ
	ImageEndCOMP.CntMAX = IMAGE_END_COMP_CNT_MAX;			//カウンタMAX
	ImageEndCOMP.IsDraw = FALSE;							//描画させない

	//エンドフォール
	strcpy_s(ImageEndFAIL.image.path, IMAGE_END_FAIL_PATH);				//パスの設定
	ImageEndFAIL.image.handle = LoadGraph(ImageEndFAIL.image.path);			//読み込み
	if (ImageEndFAIL.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_END_FAIL_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(ImageEndFAIL.image.handle, &ImageEndFAIL.image.width, &ImageEndFAIL.image.height);	//画像の幅と高さを取得
	ImageEndFAIL.image.x = GAME_WIDTH / 2 - ImageEndFAIL.image.width / 2;			//左右中央揃え
	ImageEndFAIL.image.y = GAME_HEIGHT / 2 - ImageEndFAIL.image.height / 2;			//上下中央揃え
	ImageEndFAIL.Cnt = 0.0;									//カウンタ
	ImageEndFAIL.CntMAX = IMAGE_END_FAIL_CNT_MAX;			//カウンタMAX
	ImageEndFAIL.IsDraw = FALSE;							//描画させない

	//背景画像
	strcpy_s(ImageBack.image.path, IMAGE_BACK_PATH);			//パスの設定


	//画像を連続して読み込み
	{
		ImageBack.image.handle = LoadGraph(ImageBack.image.path);	//読み込み
		if (ImageBack.image.handle == -1)
		{
			//エラーメッセージ表示
			MessageBox(GetMainWindowHandle(), IMAGE_BACK_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}
		//画像の幅と高さを取得
		GetGraphSize(ImageBack.image.handle, &ImageBack.image.width, &ImageBack.image.height);
	}
	//背景画像�@の設定
	ImageBack.image.x = GAME_WIDTH / 2 - ImageBack.image.width / 2;	//左右中央揃え
	ImageBack.image.y = 0 - ImageBack.image.height * 0;				//yは原点から
	ImageBack.IsDraw = FALSE;



	//プレイヤーの画像
	strcpy_s(player.image.path, IMAGE_PLAYER_PATH);		//パスの設定
	player.image.handle = LoadGraph(player.image.path);	//読み込み
	if (player.image.handle == -1)
	{
		//エラーメッセージ表示
		MessageBox(GetMainWindowHandle(), IMAGE_PLAYER_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);
		return FALSE;
	}
	GetGraphSize(player.image.handle, &player.image.width, &player.image.height);	//画像の幅と高さを取得
	player.image.x = GAME_WIDTH / 2 - player.image.width / 2;		//左右中央揃え
	player.image.y = GAME_HEIGHT / 2 - player.image.height / 2;		//上下中央揃え
	player.CenterX = player.image.x + player.image.width / 2;		//画像の横の中心を探す
	player.CenterY = player.image.y + player.image.height / 2;		//画像の縦の中心を探す
	player.speed = CHARA_SPEED_LOW;									//スピードを設定




	//マップの画像を分割する
	int mapRes = LoadDivGraph(
		GAME_MAP_PATH,										//マップのパス
		MAP_DIV_NUM, MAP_DIV_TATE, MAP_DIV_YOKO,			//マップを分割する数
		MAP_DIV_WIDTH, MAP_DIV_HEIGHT,						//画像を分割するの幅と高さ
		&mapChip.handle[0]);								//分割した画像が入るハンドル

	if (mapRes == -1)
	{
		//エラーメッセージ表示
		/*MessageBox(GetMainWindowHandle(), GAME_MAP_PATH, IMAGE_LOAD_ERR_TITLE, MB_OK);*/
		return FALSE;
	}


	//幅と高さを取得
	GetGraphSize(mapChip.handle[0], &mapChip.width, &mapChip.height);

	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップデータ初期化用に情報をコピー
			mapDataInit[tate][yoko] = mapData[tate][yoko];

			//マップの種類をコピー
			map[tate][yoko].kind = mapData[tate][yoko];

			//マップの幅と高さをコピー
			map[tate][yoko].width = mapChip.width;
			map[tate][yoko].height = mapChip.height;

			//マップの座標を設定
			map[tate][yoko].x = yoko * map[tate][yoko].width;
			map[tate][yoko].y = tate * map[tate][yoko].height;
		}
	}

	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//マップの当たり判定を設定
			mapColl[tate][yoko].left = (yoko + 0) * mapChip.width + 1;
			mapColl[tate][yoko].top = (tate + 0) * mapChip.height + 1;
			mapColl[tate][yoko].right = (yoko + 1) * mapChip.width - 1;
			mapColl[tate][yoko].bottom = (tate + 1) * mapChip.height - 1;
		}
	}

	return TRUE;
}

//画像をまとめて削除する関数
VOID MY_DELETE_IMAGE(VOID)
{

	{
		DeleteGraph(ImageBack.image.handle);
	}

	DeleteGraph(player.image.handle);

	DeleteGraph(ImageTitleBK.handle);
	DeleteGraph(ImageTitleROGO.image.handle);
	DeleteGraph(ImageTitleSTART.image.handle);
	DeleteGraph(ImageEndCOMP.image.handle);
	DeleteGraph(ImageEndFAIL.image.handle);


	for (int i_num = 0; i_num < MAP_DIV_NUM; i_num++) { DeleteGraph(mapChip.handle[i_num]); }


	return;
}



//マップとプレイヤーの当たり判定をする関数
BOOL MY_CHECK_MAP1_PLAYER_COLL(RECT player)
{
	//マップの当たり判定を設定する
	for (int tate = 0; tate < GAME_MAP_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < GAME_MAP_YOKO_MAX; yoko++)
		{
			//プレイヤーとマップが当たっているとき
			if (MY_CHECK_RECT_COLL(player, mapColl[tate][yoko]) == TRUE)
			{
				//壁のときは、プレイヤーとマップが当たっている
				if (map[tate][yoko].kind == k) { return TRUE; }
			}
		}
	}

	return FALSE;
}

//領域の当たり判定をする関数
BOOL MY_CHECK_RECT_COLL(RECT a, RECT b)
{
	if (a.left < b.right &&
		a.top < b.bottom &&
		a.right > b.left &&
		a.bottom > b.top
		)
	{
		return TRUE;	//当たっている
	}

	return FALSE;		//当たっていない
}
