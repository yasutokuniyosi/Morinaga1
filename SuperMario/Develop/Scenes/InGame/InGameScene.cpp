#include "InGameScene.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/EnemyBase.h"
#include "../../Objects/Wall/Wall.h"
#include "../../Objects/Food/Food.h"
#include "../../Objects/Food/PowerFood.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/ProjectConfig.h"
#include "DxLib.h"
#include <fstream>

InGameScene::InGameScene()
	: player(nullptr)
	,enemybase(nullptr)
	, back_ground_image(NULL)
	, back_ground_sound(NULL)
	, pause_flag(false)
	, scroll(0)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	//LoadStageMapFoodsCSV();

	// スクリーンオフセットを設定
	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// 背景画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/配置素材/NES---Super-Mario-Bros---World-1-1（修正版）.png")[0];
	back_ground_3 = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_4 = rm->GetImages("Resource/Images/Block/kai_block.png")[0];
	back_ground_S = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_L = rm->GetImages("Resource/Images/cloud1.png")[0];
	back_ground_K = rm->GetImages("Resource/Images/cloud3.png")[0];
	back_ground_O = rm->GetImages("Resource/Images/cloud6.png")[0];
	back_ground_I = rm->GetImages("Resource/Images/cloud4.png")[0];
	back_ground_U = rm->GetImages("Resource/Images/cloud2.png")[0];
	back_ground_J = rm->GetImages("Resource/Images/cloud5.png")[0];
	back_ground_H = rm->GetImages("Resource/Images/ha2.png")[0];
	back_ground_N = rm->GetImages("Resource/Images/ha1.png")[0];
	back_ground_Y = rm->GetImages("Resource/Images/ha0.png")[0];
	back_ground_f = rm->GetImages("Resource/Images/mountain_right.png")[0];
	back_ground_g = rm->GetImages("Resource/Images/mountain_left.png")[0];
	back_ground_h = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
	back_ground_n = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
	back_ground_y = rm->GetImages("Resource/Images/mountain_up.png")[0];
	back_ground_p = rm->GetImages("Resource/Images/mountain_surface.png")[0];
	back_ground_E = rm->GetImages(("Resource/Images/Enemy/kuribo.png"), 3, 3, 1, 32, 32)[0];
	back_ground_B = rm->GetImages("Resource/Images/Block/block.png")[0];
	back_ground_Q = rm->GetImages(("Resource/Images/Block/hatena.png"),4,4,1,32,32)[0];
	back_ground_R = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
	back_ground_C = rm->GetImages("Resource/Images/dokan_left_down.png")[0];
	back_ground_W = rm->GetImages("Resource/Images/dokan_right_up.png")[0];
	back_ground_X = rm->GetImages("Resource/Images/dokan_right_down.png")[0];
	back_ground_F = rm->GetImages("Resource/Images/flag.png")[0];          //旗の画像
	back_ground_s = rm->GetImages("Resource/Images/pole.png")[0];          //ポールの上の点の画像
	back_ground_r = rm->GetImages("Resource/Images/pole_down.png")[0];          //ポールの棒の部分の画像

	// BGMの読み込み
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

	// モードによって、生成するオブジェクトを変える
			// 生成位置の情報
	player = CreateObject<Player>(Vector2D(100,100));
	enemybase = CreateObject<EnemyBase>(Vector2D(150, 100));

}

eSceneType InGameScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}
	if (player->GetLocation().x >= D_WIN_MAX_X/2 && input->GetKey(KEY_INPUT_D))
	{
		scroll -= 300* delta_second;
		if (scroll < -6080)
		{
			scroll += 300 * delta_second;
		}
	}


	if (!pause_flag)
	{
		// 親クラスの更新処理を呼び出す
		__super::Update(delta_second);

		// プレイヤーが死んだら、再スタート
		//if (player->GetDestroy())
		//{
		//	return eSceneType::re_start;
		//}
	}

	// シーン情報を返却する
	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	// マップデータ読み込み生成処理
	LoadStageMapCSV();

	//当たり判定のある画像の生成処理
	LoadStageMapHanteiCSV();

	// 背景画像の描画
	//DrawRotaGraph(336, 432, 1.5, 0.0, back_ground_image, TRUE);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	// UI系の描画処理
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// 当たり判定確認処理
/// </summary>
/// <param name="target">1つ目のゲームオブジェクト</param>
/// <param name="partner">2つ目のゲームオブジェクト</param>
void InGameScene::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
	// ヌルポチェック
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// 当たり判定情報を取得
	CapsuleCollision tc = target->GetCollision();
	CapsuleCollision pc = partner->GetCollision();

	// 当たり判定が有効か確認する
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// 線分の始点と終点を設定する
		tc.point[0] += target->GetLocation();
		tc.point[1] += target->GetLocation();
		pc.point[0] += partner->GetLocation();
		pc.point[1] += partner->GetLocation();

		// カプセル同士の当たり判定
		if (IsCheckCollision(tc, pc))
		{
			// 当たっていることを通知する
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}
}

/// <summary>
/// ステージマップ（壁）読み込み処理
/// </summary>
void InGameScene::LoadStageMapCSV() const
{
	 //読み込むファイル名
	FILE* fp = NULL;
	//指定ファイルを読み込む
	fopen_s(&fp, "Map/SuperMario_Map.csv", "r");

	 //エラーチェック
	if (fp==NULL)
	{
		throw ("ファイルが開けません\n");
	}
	else
	{
		//マップチップ見込み用変数
		int mode = 0;

		//カウント用変数
		int i = 0;
		int j = 0;

		while (mode != EOF)
		{
			mode = fgetc(fp);


			if (mode == ',')
			{
				j++;
				continue;
			}
			else if (mode == '\n')
			{
				i++;
				j = 0;
				continue;
			}
			else
			{
				//モードによって、生成するオブジェクトを変える
				Vector2D generate_location;		// 生成位置の情報
				generate_location.x = (float)(j * 32 - 16) + scroll;
				generate_location.y = (float)(i * 32 - 16);

				switch (mode)
				{
					//壁
				case '#':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_3, TRUE);
					break;
				//	// 階段ブロック
				//case '$':
				//	DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_4, TRUE);
				//	break;
				//	//プレイヤー
				//case 'P':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	player = CreateObject<Player>(generate_location);
				//	break;
				//	//クリボーエネミー
				//case 'E':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//ノコノコエネミー
				//case 'a':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//ブロック
				//case 'B':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//？ブロック
				//case 'Q':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//空
				case 'S':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_S, TRUE);
					break;
				//雲の左下
				case 'L':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_L, TRUE);
					break;
				//雲の右下
				case 'K':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_K, TRUE);
					break;
				//雲の左上
				case 'O':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_O, TRUE);
					break;
				//雲の右上
				case 'I':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_I, TRUE);
					break;
				//雲の中下
				case 'U':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_U, TRUE);
					break;
				//雲の中上
				case 'J':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_J, TRUE);
					break;
				//	//フラグ
				//case 'F':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//星フラグ
				//case 'G':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//葉っぱの右
				case 'H':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_H, TRUE);
					break;
				//葉っぱの中
				case 'N':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_N, TRUE);
					break;
				//葉っぱの左
				case 'Y':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_Y, TRUE);
					break;
				//山の右
				case 'f':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_f, TRUE);
					break;
				//山の左
				case 'g':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_g, TRUE);
					break;
				//山の中右
				case 'h':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_h, TRUE);
					break;
				//山の中左
				case 'n':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_n, TRUE);
					break;
				//山のてっぺん
				case 'y':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_y, TRUE);
					break;
				//山の中心
				case 'p':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_p, TRUE);
					break;
				//	//ポールの上の点
				//case 's':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//ポールの棒の部分
				//case 'r':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//城
				//case 'c':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//横土管の左上
				//case 'w':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//横土管の左下
				//case 'x':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//横土管の右下
				//case 'l':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//横土管の右上
				//case 'k':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//横土管の中上
				//case 'o':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//横土管の中下
				//case 'i':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
					//上記以外
				default:
					break;
				}
			}
		}
		fclose(fp); // ファイルを閉じる
	}

	
}

 //<summary>
 //ステージマップ(判定)読み込み処理
 //</summary>
void InGameScene::LoadStageMapHanteiCSV() const
{
	//読み込むファイル名
	FILE* fp = NULL;
	//指定ファイルを読み込む
	fopen_s(&fp, "Map/SupeerMario_Map_Hantei.csv", "r");

	//エラーチェック
	if (fp == NULL)
	{
		throw ("ファイルが開けません\n");
	}
	else
	{
		//マップチップ見込み用変数
		int mode = 0;

		//カウント用変数
		int i = 0;
		int j = 0;

		while (mode != EOF)
		{
			mode = fgetc(fp);


			if (mode == ',')
			{
				j++;
				continue;
			}
			else if (mode == '\n')
			{
				i++;
				j = 0;
				continue;
			}
			else
			{
				//モードによって、生成するオブジェクトを変える
				Vector2D generate_location;		// 生成位置の情報
				generate_location.x = (float)(j * 32 - 16) + scroll;
				generate_location.y = (float)(i * 32 - 16);

				switch (mode)
				{
					//壁
				case '#':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_3, TRUE);
					break;
					// 階段ブロック
				case '$':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_4, TRUE);
					break;
				
						//クリボーエネミー
					case 'E':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_E, TRUE);
						break;
					//	//ノコノコエネミー
					//case 'a':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
						//ブロック
					case 'B':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_B, TRUE);
						break;
						//？ブロック
					case 'Q':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_Q, TRUE);
						break;
						//土管の右上
					case 'R':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_R, TRUE);
						break;
						//土管の右下
					case 'C':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_C, TRUE);
						break;
						//土管の左上
					case 'W':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_W, TRUE);
						break;
						//土管の左下
					case 'X':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_X, TRUE);
						break;
						//フラグ
					case 'F':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_F, TRUE);
						break;
					//	//星フラグ
					//case 'G':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
	
						//ポールの上の点
					case 's':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_s, TRUE);
						break;
						//ポールの棒の部分
					case 'r':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_r, TRUE);
						break;
					//	//城
					//case 'c':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//横土管の左上
					//case 'w':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//横土管の左下
					//case 'x':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//横土管の右下
					//case 'l':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//横土管の右上
					//case 'k':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//横土管の中上
					//case 'o':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//横土管の中下
					//case 'i':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
						//上記以外
				default:
					break;
				}
			}
		}
		fclose(fp); // ファイルを閉じる
	}


}
