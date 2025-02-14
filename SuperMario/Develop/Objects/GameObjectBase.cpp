#include "GameObjectBase.h"
#include "../Scenes/SceneBase.h"
#include "DxLib.h"

GameObjectBase::GameObjectBase() :
	owner_scene(nullptr),
	location(0.0f),
	image(NULL),
	z_layer(0),
	mobility(eMobilityType::Stationary),
	flip_flag(FALSE)
{

}

GameObjectBase::~GameObjectBase()
{

}

/// <summary>
/// ����������
/// </summary>
void GameObjectBase::Initialize()
{

}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void GameObjectBase::Update(float delta_second)
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset">�I�t�Z�b�g�l</param>
void GameObjectBase::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, image,TRUE, flip_flag);
}

/// <summary>
/// �I��������
/// </summary>
void GameObjectBase::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void GameObjectBase::OnHitCollision(GameObjectBase* hit_object)
{

}

/// <summary>
/// ���L�V�[�����̐ݒ�
/// </summary>
/// <param name="scene">���L�V�[�����</param>
void GameObjectBase::SetOwnerScene(SceneBase* scene)
{
	this->owner_scene = scene;
}

/// <summary>
/// �ʒu���W�擾����
/// </summary>
/// <returns>�ʒu���W���</returns>
const Vector2D& GameObjectBase::GetLocation() const
{
	return location;
}

const Vector2D& GameObjectBase::GetBoxSize() const
{
	return box_size;
}

/// <summary>
/// �ʒu���ύX����
/// </summary>
/// <param name="location">�ύX�������ʒu���</param>
void GameObjectBase::SetLocation(const Vector2D& location)
{
	this->location = location;
}

/// <summary>
/// �����蔻��擾����
/// </summary>
/// <returns>�����蔻����</returns>
CapsuleCollision GameObjectBase::GetCollision() const
{
	return collision;
}

/// <summary>
/// Z���C���[���擾����
/// </summary>
/// <returns>Z���C���[���</returns>
const int GameObjectBase::GetZLayer() const
{
	return z_layer;
}

/// <summary>
/// �������̎擾����
/// </summary>
/// <returns>�������</returns>
const eMobilityType GameObjectBase::GetMobility() const
{
	return mobility;
}
