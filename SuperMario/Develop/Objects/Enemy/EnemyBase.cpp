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
	// �A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	kuribo_move_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	//body_move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// ���C���[�̐ݒ�
	z_layer = 5;

	// �����̐ݒ�
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

	// �v���C���[��Ԃɂ���āA�����ς���
	switch (enemy_state)
	{
	case eEnemyState::EIDLE:
		// �摜�̐ݒ�
		image = kuribo_move_animation[0];
		//body_image = body_move_animation[0];
		break;
	case eEnemyState::EMOVE:
		// �ړ�����
		Movement(delta_second);
		// �A�j���[�V��������
		AnimationControl(delta_second);
		break;
	case eEnemyState::EDIE:
		// ���S���̃A�j���[�V����
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
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);

	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	//DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, body_image, TRUE);
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image, TRUE);
}

void EnemyBase::Finalize()
{
	// ���I�z��̉��
	kuribo_move_animation.clear();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
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

		velocity *= -1;
	}

	// ���������I�u�W�F�N�g���G��������
	if (hit_object->GetCollision().object_type == eObjectType::enemy)
	{
		enemy_state = eEnemyState::EDIE;
	}
}

/// <summary>
/// �v���C���[�̏�Ԃ��擾����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
eEnemyState EnemyBase::GetEnemyState() const
{
	return enemy_state;
}

/// <summary>
/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
bool EnemyBase::GetPowerUp() const
{
	return is_power_up;
}

/// <summary>
/// �p���[�_�E��������
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
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::Movement(float delta_second)
{
	// �ړ��� = ���� * ���� �ňړ�������肷��
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


	if (jump == true && location.y >=295)
	{		jump_flag = true;
		JUMP = true;
	}

	if (location.y < 150)
	{
		jump_flag = false;
		//// �����ăL�����N�^�[�̍��W( y���W )�ɒl�n��
		//charPos.y += velocity;
	}
	if (jump_flag == true)
	{
		velocity.y -=  0.3f;
	}

	if (location.y > 300)
	{
		// ������0�ɂ��Ȃ�������A�n�ʂ̉��܂ōs���̂�
		/*velocity.y = 0;*/

		// �W�����v�̃t���O�I�t��
		jump_down = false;


		JUMP = false;

		jump_flag = false;

		location.y = 295;
	}

	//jump_down��n�ʂ��痣�ꂽ��true�ɂ���
	//�n�ʂɂ�����Ajump_down��false�ɂ���
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void EnemyBase::AnimationControl(float delta_second)
{
	//// �ړ����̃A�j���[�V����
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

