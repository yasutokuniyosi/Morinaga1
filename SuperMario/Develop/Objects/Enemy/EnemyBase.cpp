#include "EnemyBase.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "../../Utility/ProjectConfig.h"

#define D_ENEMY_SPEED	(50.0f)

EnemyBase::EnemyBase() :
	kuribo_move_animation(),
	//body_move_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::EMOVE),
	now_direction_state(eEnemyDirectionState::LEFT),
	animation_time(0.0f),
	animation_count(0),
	move_left(false),
	move_right(false),
	jump(false),
	jump_flag(false),
	jump_down(false),
	G(),
	IDLE(false),
	WARK(false),
	JUMP(false),
	wark_count(),
	T(),
	J(),
	is_power_up(false),
	is_destroy(false)
{

}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	kuribo_move_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	//body_move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	image = kuribo_move_animation[0];

	velocity = Vector2D(0.0f, 0.0f);
}

void EnemyBase::Update(float delta_second)
{
	float g = 0.5;
	G += g / 400.0;

	location += velocity * D_ENEMY_SPEED * delta_second;

	if (location.y < 295)
	{
		T++;
		velocity.y += G;
	}
	else if (location.y > 295)
	{
		G = 0;
		velocity.y = 0;
	}

	// プレイヤー状態によって、動作を変える
	switch (enemy_state)
	{
	case eEnemyState::EIDLE:
		// 画像の設定
		image = kuribo_move_animation[0];
		//body_image = body_move_animation[0];
		break;
	case eEnemyState::EMOVE:
		// 移動処理
		Movement(delta_second);
		// アニメーション制御
		AnimationControl(delta_second);
		break;
	case eEnemyState::EDIE:
		// 死亡中のアニメーション
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
		}
		break;
	default:
		break;
	}
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);

	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	//DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, body_image, TRUE);
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void EnemyBase::Finalize()
{
	// 動的配列の解放
	kuribo_move_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;

		velocity *= -1;
	}

	// 当たったオブジェクトが敵だったら
	if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		enemy_state = eEnemyState::EDIE;
	}
}

/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

/// <summary>
/// プレイヤーがパワーアップしてるか確認する
/// </summary>
/// <returns>プレイヤーの状態</returns>
bool EnemyBase::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// パワーダウンさせる
/// </summary>
void EnemyBase::SetPowerDown()
{
	is_power_up = false;
}

bool EnemyBase::GetDestroy() const
{
	return is_destroy;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Movement(float delta_second)
{
	// 移動量 = 速さ * 時間 で移動先を決定する
	/*location += velocity * D_ENEMY_SPEED * delta_second;*/
	InputManager* rm = InputManager::GetInstance();


	if (jump_flag == true)
	{

	}
	else if (jump_down == true)
	{

	}
	else
	{
		move_left = rm->GetKey(KEY_INPUT_A);
		move_right = rm->GetKey(KEY_INPUT_D);
		jump = rm->GetKeyDown(KEY_INPUT_W);
	}

	if (velocity.x == 0) {
		IDLE = true;
		WARK = false;
	}
	else
	{
		IDLE = false;
	}

	if (move_left == true)
	{
		WARK = true;

		//左移動
		//移動方向決定
		velocity.x = -3.0f;
		flip_flag = TRUE;

	}
	else if (move_right == true)
	{
		WARK = true;

		//右移動
		//移動方向決定
		velocity.x = 3.0f;
		flip_flag = FALSE;

		if (location.x > D_WIN_MAX_X / 2)
		{
			location.x = D_WIN_MAX_X / 2;
		}
	}
	else
	{
		velocity.x = 0.0f;
	}


	if (jump == true && location.y >=295)
	{		jump_flag = true;
		JUMP = true;
	}

	if (location.y < 150)
	{
		jump_flag = false;
		//// そしてキャラクターの座標( y座標 )に値渡す
		//charPos.y += velocity;
	}
	if (jump_flag == true)
	{
		velocity.y -=  0.3f;
	}

	if (location.y > 300)
	{
		// ここで0にしなかったら、地面の下まで行くので
		/*velocity.y = 0;*/

		// ジャンプのフラグオフに
		jump_down = false;


		JUMP = false;

		jump_flag = false;

		location.y = 295;
	}

	//jump_downを地面から離れたらtrueにする
	//地面についたら、jump_downをfalseにする
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::AnimationControl(float delta_second)
{
	//// 移動中のアニメーション
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 16.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 2)
	//	{
	//		animation_count = 0;
	//	}
	//	body_image = body_move_animation[animation_num[animation_count]];
	//}

	//if (velocity.x > 0)
	//{
	//	image = eyes_move_animation[1];
	//}
	//else if (velocity.x < 0)
	//{
	//	image = eyes_move_animation[3];
	//}
}

