#pragma once

#include "../SceneBase.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/EnemyBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;		// �v���C���[���
	class EnemyBase* enemybase;  //�G�̏��
	int back_ground_image;		// �w�i�摜
	int back_ground_3;          //���̉摜
	int back_ground_4;          //�K�i�̉摜
	int back_ground_S;          //��̉摜
	int back_ground_L;          //�_�̍���̉摜
	int back_ground_K;          //�_�̉E���̉摜
	int back_ground_O;          //�_�̍���̉摜
	int back_ground_I;          //�_�̉E��̉摜
	int back_ground_U;          //�_�̒����̉摜
	int back_ground_J;          //�_�̒���̉摜
	int back_ground_H;          //�t���ς̉E�̉摜
	int back_ground_N;          //�t���ς̒��̉摜
	int back_ground_Y;          //�t���ς̍��̉摜
	int back_ground_f;          //�R�̉E�̉摜
	int back_ground_g;          //�R�̍��̉摜
	int back_ground_h;          //�R�̒��E�̉摜
	int back_ground_n;          //�R�̒����̉摜
	int back_ground_y;          //�R�̂Ă��؂�̉摜
	int back_ground_p;          //�R�̒��S�̉摜
	int back_ground_E;          //�N���{�[�̉摜
	int back_ground_B;          //�u���b�N�̉摜
	int back_ground_Q;          //�n�e�i�u���b�N�̉摜
	int back_ground_R;          //�y�ǂ̉E��̉摜
	int back_ground_C;          //�y�ǂ̉E���̉摜
	int back_ground_W;          //�y�ǂ̍���̉摜
	int back_ground_X;          //�y�ǂ̍����̉摜
	int back_ground_F;          //���̉摜
	int back_ground_s;          //�|�[���̏�̓_�̉摜
	int back_ground_r;          //�|�[���̖_�̕����̉摜

	int back_ground_sound;		// BGM
	bool pause_flag;			// �ꎞ��~�t���O
	FILE* fp;
	float scroll;               //�X�N���[���l

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

	/// <summary>
	/// �����蔻��m�F����
	/// </summary>
	/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
	/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
	virtual void CheckCollision(GameObjectBase* target, GameObjectBase* partner) override;

private:
	/// <summary>
	/// �X�e�[�W�}�b�v�i�w�i�j�ǂݍ��ݏ���
	/// </summary>
	void LoadStageMapCSV() const;
	/// <summary>
	/// �X�e�[�W�}�b�v�i����)�ǂݍ��ݏ���
	/// </summary>
	void LoadStageMapHanteiCSV() const;
};
