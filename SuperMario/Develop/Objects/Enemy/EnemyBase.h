#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"

// �v���C���[���
enum eEnemyState
{
	EIDLE,		// �ҋ@���
	EMOVE,		// �ړ����
	EDIE,		// ���S���
};

/// <summary>
/// �v���C���[�N���X�i�p�b�N�}���j
/// </summary>
class EnemyBase : public GameObject
{
private:
	// �i�s�������
	enum eEnemyDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

private:
	std::vector<int> kuribo_move_animation;		// �ڂ̈ړ��̃A�j���[�V�����摜
	//std::vector<int> body_move_animation;       //�̂̃A�j���[�V����
	Vector2D old_location;					// �O���location
	Vector2D velocity;						// �ړ���
	eEnemyState enemy_state;				// �v���C���[���
	eEnemyDirectionState now_direction_state;	// ���ݐi�s�������
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
	bool is_power_up;						// �p���[�a��H�ׂ����H
	bool is_destroy;						// ���񂾏�ԂɂȂ������H
	//int body_image;                         //�̂̉摜

	const int animation_num[2] = { 0, 1 };

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:

	/// <summary>
	/// �v���C���[�̏�Ԃ��擾����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	eEnemyState GetEnemyState() const;

	/// <summary>
	/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	bool GetPowerUp() const;

	/// <summary>
	/// �p���[�_�E��������
	/// </summary>
	void SetPowerDown();

	/// <summary>
	/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	bool GetDestroy() const;


private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);
	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);
};

