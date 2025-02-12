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
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	//dying_animation = rm->GetImages("Resource/Images/dying.png", 11, 11, 1, 32, 32);

	// �����蔻��̐ݒ�
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

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
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

	// �v���C���[��Ԃɂ���āA�����ς���
	switch (player_state)
	{
	case ePlayerState::IDLE:
		// �摜�̐ݒ�
		image = move_animation[0];
		break;
	case ePlayerState::MOVE:
		// �ړ�����
		Movement(delta_second);
		// �A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case ePlayerState::DIE:
		// ���S���̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			// ����������
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
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

void Player::Finalize()
{
	// ���I�z��̉��
	move_animation.clear();
	dying_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	// ���������A�I�u�W�F�N�g���ǂ�������
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;
	}

	// ���������I�u�W�F�N�g���G��������
	if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		//DrawBox(0, 0, 31, 31, GetColor(255, 255, ), TRUE);
	}
}


/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
ePlayerState Player::GetPlayerState() const
{
	return player_state;
}

Vector2D Player::GetVelocity()
{
	return velocity;
}

/// <summary>
/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
bool Player::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// �p���[�_�E��������
/// </summary>
void Player::SetPowerDown()
{
	is_power_up = false;
}


/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
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
			
			//���ړ�
			//�ړ���������
				velocity.x = -3.0f;
				flip_flag = TRUE;
			
		}
		else if (move_right == true)
		{
			WARK = true;

			//�E�ړ�
			//�ړ���������
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
	
	//jump_down��n�ʂ��痣�ꂽ��true�ɂ���
	//�n�ʂɂ�����Ajump_down��false�ɂ���

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
		// ������0�ɂ��Ȃ�������A�n�ʂ̉��܂ōs���̂�
		//velocity = 0;

		// �W�����v�̃t���O�I�t��

		jump_flag = false;

		location.y = 295;

		JUMP = false;
	}

	//// �ړ��ʂ���ړ��������X�V
	//if (Vector2D::Distance(old_location, location) == 0.0f)
	//{
	//	// �ړ����Ȃ���� direction_state ��ύX����
	//	velocity = 0.0f;
	//	now_direction_state = next_direction_state;
	//	next_direction_state = eDirectionState::NONE;
	//}
	//else
	//{
	//	// �ړ������Ɉړ����Ă��Ȃ���� direction_state ��ύX����
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::UP:
	//	case eDirectionState::DOWN:
	//	{
	//		float diff = location.y - old_location.y;
	//		if (((now_direction_state == eDirectionState::UP) && (diff < 0.0f)) ||
	//			((now_direction_state == eDirectionState::DOWN) && (0.0f < diff)))
	//		{
	//			// �ړ������Ɉړ����Ă�̂� break
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
	//			// �ړ������Ɉړ����Ă�̂� break
	//			break;
	//		}

	//		velocity.x = 0.0f;
	//		now_direction_state = next_direction_state;
	//		next_direction_state = eDirectionState::NONE;
	//	}
	//	break;

	//	default:// �������Ȃ�
	//		break;
	//	}
	//}

	//// ���͏�Ԃ̎擾
	//InputManager* input = InputManager::GetInstance();

	//// ���݃p�l���̏�Ԃ��m�F
	//ePanelID panel = StageData::GetPanelData(location);

	//// ���͂���ړ�������ݒ�
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

	//// �i�s�����̈ړ��ʂ�ǉ�
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

	//// ��s���͂̈ړ��ʂ�ǉ�
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

	//// �O����W�̍X�V
	//old_location = location;

	//// �O��p�l���̍X�V
	//old_panel = panel;

	//// �ړ��� * ���� * ���� �ňړ�������肷��
	//location += velocity * D_PLAYER_SPEED * delta_second;

	//// ��ʊO�ɍs������A���Α��Ƀ��[�v������
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
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::AnimationControl(float delta_second)
{

	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐ؑ�
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
	//// �ړ����̃A�j���[�V����
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 16.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 4)
	//	{
	//		animation_count = 0;
	//	}
	//	// �摜�̐ݒ�
	//	int dir_num = (int)now_direction_state;
	//	if (0 <= dir_num && dir_num < 4)
	//	{
	//		image = move_animation[(dir_num * 3) + animation_num[animation_count]];
	//	}

	//}
}
