#include "Player.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "../Food/Food.h"
#include "../../Utility/ProjectConfig.h"

#define D_PLAYER_SPEED	(50.0f)

Player::Player() :
	move_animation(),
	dying_animation(),
	velocity(0.0f),
	player_state(ePlayerState::MOVE),
	now_direction_state(eDirectionState::LEFT),
	next_direction_state(eDirectionState::LEFT),
	animation_time(0.0f),
	animation_count(0),
	animation(),
	old_panel(ePanelID::NONE),
	move_left(false),
	move_right(false),
	jump(false),
	jump_flag(false),
	jump_down(false),
	G(false),
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

Player::~Player()
{

}

void Player::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	//dying_animation = rm->GetImages("Resource/Images/dying.png", 11, 11, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::player;
	collision.hit_object_type.push_back(eObjectType::enemy);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::food);
	collision.hit_object_type.push_back(eObjectType::power_food);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	image = move_animation[0];

	wark_count = 0;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	velocity = Vector2D(0.0f, 0.0f);
}

void Player::Update(float delta_second)
{
	float g = 0.5;
	G += g / 400.0;

	location += velocity * D_PLAYER_SPEED * delta_second;

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
	switch (player_state)
	{
	case ePlayerState::IDLE:
		// 画像の設定
		image = move_animation[0];
		break;
	case ePlayerState::MOVE:
		// 移動処理
		Movement(delta_second);
		// アニメーション制御
		AnimationControl(delta_second);
		break;
	case ePlayerState::DIE:
		// 死亡中のアニメーション
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			// 復活させる
			if (animation_count >= dying_animation.size())
			{
				player_state = ePlayerState::IDLE;
				animation_count = 0;
				is_destroy = true;
			}
		}
		image = dying_animation[animation_count];
		break;
	default:
		break;
	}
}

void Player::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Player::OnHitCollision(GameObjectBase* hit_object)
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
	}

	// 当たったオブジェクトが敵だったら
	if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		//DrawBox(0, 0, 31, 31, GetColor(255, 255, ), TRUE);
	}
}


/// <summary>
/// プレイヤーの状態を取得する
/// </summary>
/// <returns>プレイヤーの状態</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

Vector2D Player::GetVelocity()
{
	return velocity;
}

/// <summary>
/// プレイヤーがパワーアップしてるか確認する
/// </summary>
/// <returns>プレイヤーの状態</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// パワーダウンさせる
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}


/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Movement(float delta_second)
{
	InputManager* rm = InputManager::GetInstance();

	if (jump_flag==true)
	{

	}
	else if (jump_down==true)
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

	int s = 0;

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
	
	//jump_downを地面から離れたらtrueにする
	//地面についたら、jump_downをfalseにする

	if (jump == true && location.y >= 295)
	{
		jump_flag = true;
		JUMP = true;
	}

	if (location.y < 150)
	{
		jump_flag = false;
	}

	if (jump_flag == true)
	{
		velocity.y -= 0.3f;
	}

	if (velocity.y == 0.0f)
	{
		JUMP = false;
	}

	if (location.y > 300)
	{
		// ここで0にしなかったら、地面の下まで行くので
		//velocity = 0;

		// ジャンプのフラグオフに

		jump_flag = false;

		location.y = 295;

		JUMP = false;
	}

	//// 移動量から移動方向を更新
	//if (Vector2D::Distance(old_location, location) == 0.0f)
	//{
	//	// 移動がなければ direction_state を変更する
	//	velocity = 0.0f;
	//	now_direction_state = next_direction_state;
	//	next_direction_state = eDirectionState::NONE;
	//}
	//else
	//{
	//	// 移動方向に移動していなければ direction_state を変更する
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::UP:
	//	case eDirectionState::DOWN:
	//	{
	//		float diff = location.y - old_location.y;
	//		if (((now_direction_state == eDirectionState::UP) && (diff < 0.0f)) ||
	//			((now_direction_state == eDirectionState::DOWN) && (0.0f < diff)))
	//		{
	//			// 移動方向に移動してるので break
	//			break;
	//		}

	//		velocity.y = 0.0f;
	//		now_direction_state = next_direction_state;
	//		next_direction_state = eDirectionState::NONE;
	//	}
	//	break;

	//	case eDirectionState::LEFT:
	//	case eDirectionState::RIGHT:
	//	{

	//		float diff = location.x - old_location.x;
	//		if (((now_direction_state == eDirectionState::LEFT) && (diff < 0.0f)) ||
	//			((now_direction_state == eDirectionState::RIGHT) && (0.0f < diff)))
	//		{
	//			// 移動方向に移動してるので break
	//			break;
	//		}

	//		velocity.x = 0.0f;
	//		now_direction_state = next_direction_state;
	//		next_direction_state = eDirectionState::NONE;
	//	}
	//	break;

	//	default:// 何もしない
	//		break;
	//	}
	//}

	//// 入力状態の取得
	//InputManager* input = InputManager::GetInstance();

	//// 現在パネルの状態を確認
	//ePanelID panel = StageData::GetPanelData(location);

	//// 入力から移動方向を設定
	//if (input->GetKeyDown(KEY_INPUT_UP) || input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::UP:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::DOWN:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::UP;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::UP;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_DOWN) || input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::DOWN:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::UP:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::DOWN;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::DOWN;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_LEFT) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::LEFT:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::RIGHT:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::LEFT;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::LEFT;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::RIGHT:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::LEFT:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::RIGHT;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::RIGHT;
	//	}
	//}

	//// 進行方向の移動量を追加
	//switch (now_direction_state)
	//{
	//case Player::UP:
	//	velocity.y = -1.0f;
	//	break;
	//case Player::DOWN:
	//	velocity.y = 1.0f;
	//	break;
	//case Player::LEFT:
	//	velocity.x = -2.0f;
	//	break;
	//case Player::RIGHT:
	//	velocity.x = 2.0f;
	//	break;
	//default:
	//	velocity = 0.0f;
	//	now_direction_state = next_direction_state;
	//	next_direction_state = Player::NONE;
	//	break;
	//}

	//// 先行入力の移動量を追加
	//if ((panel != ePanelID::NONE)
	//	&& (old_panel != panel))
	//{
	//	switch (next_direction_state)
	//	{
	//	case Player::UP:
	//		velocity.y = -1.0f;
	//		break;
	//	case Player::RIGHT:
	//		velocity.x = 1.0f;
	//		break;
	//	case Player::DOWN:
	//		velocity.y = 1.0f;
	//		break;
	//	case Player::LEFT:
	//		velocity.x = -1.0f;
	//		break;
	//	default:
	//		break;
	//	}
	//}

	//// 前回座標の更新
	//old_location = location;

	//// 前回パネルの更新
	//old_panel = panel;

	//// 移動量 * 速さ * 時間 で移動先を決定する
	//location += velocity * D_PLAYER_SPEED * delta_second;

	//// 画面外に行ったら、反対側にワープさせる
	//if (location.x < 0.0f)
	//{
	//	old_location.x = 672.0f;
	//	location.x = 672.0f - collision.radius;
	//	velocity.y = 0.0f;
	//}
	//if (672.0f < location.x)
	//{
	//	old_location.x = 0.0f;
	//	location.x = collision.radius;
	//	velocity.y = 0.0f;
	//}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::AnimationControl(float delta_second)
{

	//アニメーションカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切替
		if (IDLE == TRUE)
		{
			image = move_animation[0];
		}

		if(WARK == TRUE)
		{
				wark_count += 1;
				image = move_animation[wark_count];
				if (wark_count >= 3)
				{
					wark_count = 0;
				}
		}

		if (JUMP == true)
		{
			image = move_animation[5];
		}
	}
	//// 移動中のアニメーション
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 16.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 4)
	//	{
	//		animation_count = 0;
	//	}
	//	// 画像の設定
	//	int dir_num = (int)now_direction_state;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		image = move_animation[(dir_num * 3) + animation_num[animation_count]];
	//	}

	//}
}
