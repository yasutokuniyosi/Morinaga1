#pragma once

#include "../GameObject.h"
#include "../../Utility/StageData.h"
#include "../../Utility/InputManager.h"

// �v���C���[���
enum ePlayerState
{
	IDLE,		// �ҋ@���
	MOVE,		// �ړ����
	DIE,		// ���S���
};

/// <summary>
/// �v���C���[�N���X�i�p�b�N�}���j
/// </summary>
class Player : public GameObject
{
private:
	// �i�s�������
	enum eDirectionState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NONE,
	};

private:
	std::vector<int> move_animation;		// �ړ��̃A�j���[�V�����摜
	std::vector<int> dying_animation;		// ���S�̃A�j���[�V�����摜
	Vector2D old_location;					// �O���location
	Vector2D velocity;						// �ړ���
	ePlayerState player_state;				// �v���C���[���
	eDirectionState now_direction_state;	// ���ݐi�s�������
	eDirectionState next_direction_state;	// ����i�s�������
	float animation_time;					// �A�j���[�V��������
	int animation_count;					// �A�j���[�V�����Y��
	int animation[10];
	ePanelID old_panel;						// �O��p�l�����
	bool is_power_up;						// �p���[�a��H�ׂ����H
	bool is_destroy;						// ���񂾏�ԂɂȂ������H
	int move_left;                          // ���ɓ���
	int move_right;                         //�E�ɓ���
	int jump;                               //�W�����v����
	int jump_flag;                          //�W�����v����t���O
	int jump_down;                          //�W�����v������ɉ��~����
	int IDLE;                               //�~�܂��Ă���A�j���[�V����
	int WARK;                               //�����Ă���A�j���[�V����
	int wark_count;                         //�����J�E���g
	int JUMP;                               //�W�����v����A�j���[�V����
	float G;                                  //�d��
	int T;                                  //����
	int J;                                  //�W�����v���Ă��鎞��

	// �ړ��A�j���[�V�����̏���
	const int animation_num[4] = { 0, 1, 2, 1, };

public:
	Player();
	virtual ~Player();

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
	ePlayerState GetPlayerState() const;

	Vector2D GetVelocity();

	/// <summary>
	/// �v���C���[���p���[�A�b�v���Ă邩�m�F����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	bool GetPowerUp() const;

	/// <summary>
	/// �p���[�_�E��������
	/// </summary>
	void SetPowerDown();



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
