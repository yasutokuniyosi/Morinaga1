#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// プレイヤー状態
enum eEnemyState
{
	EIDLE,		// 待機状態
	EMOVE,		// 移動状態
	EDIE,		// 死亡状態
};

/// <summary>
/// プレイヤークラス（パックマン）
/// </summary>
class EnemyBase : public GameObject
{
private:
	// 進行方向状態
	enum eEnemyDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

private:
	std::vector<int> kuribo_move_animation;		// 目の移動のアニメーション画像
	//std::vector<int> body_move_animation;       //体のアニメーション
	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// プレイヤー状態
	eEnemyDirectionState now_direction_state;	// 現在進行方向状態
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	bool is_power_up;						// パワー餌を食べたか？
	bool is_destroy;						// 死んだ状態になったか？
	//int body_image;                         //体の画像

	const int animation_num[2] = { 0, 1 };

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:

	/// <summary>
	/// プレイヤーの状態を取得する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetPowerUp() const;

	/// <summary>
	/// パワーダウンさせる
	/// </summary>
	void SetPowerDown();

	/// <summary>
	/// プレイヤーがパワーアップしてるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetDestroy() const;


private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);
	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);
};

