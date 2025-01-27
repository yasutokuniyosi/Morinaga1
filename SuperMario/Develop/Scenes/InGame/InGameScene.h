#pragma once

#include "../SceneBase.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/EnemyBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;		// プレイヤー情報
	class EnemyBase* enemybase;  //敵の情報
	int back_ground_image;		// 背景画像
	int back_ground_3;          //床の画像
	int back_ground_4;          //階段の画像
	int back_ground_S;          //空の画像
	int back_ground_L;          //雲の左上の画像
	int back_ground_K;          //雲の右下の画像
	int back_ground_O;          //雲の左上の画像
	int back_ground_I;          //雲の右上の画像
	int back_ground_U;          //雲の中下の画像
	int back_ground_J;          //雲の中上の画像
	int back_ground_H;          //葉っぱの右の画像
	int back_ground_N;          //葉っぱの中の画像
	int back_ground_Y;          //葉っぱの左の画像
	int back_ground_f;          //山の右の画像
	int back_ground_g;          //山の左の画像
	int back_ground_h;          //山の中右の画像
	int back_ground_n;          //山の中左の画像
	int back_ground_y;          //山のてっぺんの画像
	int back_ground_p;          //山の中心の画像
	int back_ground_E;          //クリボーの画像
	int back_ground_B;          //ブロックの画像
	int back_ground_Q;          //ハテナブロックの画像
	int back_ground_R;          //土管の右上の画像
	int back_ground_C;          //土管の右下の画像
	int back_ground_W;          //土管の左上の画像
	int back_ground_X;          //土管の左下の画像
	int back_ground_F;          //旗の画像
	int back_ground_s;          //ポールの上の点の画像
	int back_ground_r;          //ポールの棒の部分の画像

	int back_ground_sound;		// BGM
	bool pause_flag;			// 一時停止フラグ
	FILE* fp;
	float scroll;               //スクロール値

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

	/// <summary>
	/// 当たり判定確認処理
	/// </summary>
	/// <param name="target">1つ目のゲームオブジェクト</param>
	/// <param name="partner">2つ目のゲームオブジェクト</param>
	virtual void CheckCollision(GameObjectBase* target, GameObjectBase* partner) override;

private:
	/// <summary>
	/// ステージマップ（背景）読み込み処理
	/// </summary>
	void LoadStageMapCSV() const;
	/// <summary>
	/// ステージマップ（判定)読み込み処理
	/// </summary>
	void LoadStageMapHanteiCSV() const;
};
