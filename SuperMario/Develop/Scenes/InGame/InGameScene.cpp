#include "InGameScene.h"
#include "../../Objects/Player/Player.h"
#include "../../Objects/Enemy/EnemyBase.h"
#include "../../Objects/Wall/Wall.h"
#include "../../Objects/Food/Food.h"
#include "../../Objects/Food/PowerFood.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "../../Utility/ProjectConfig.h"
#include "DxLib.h"
#include <fstream>

InGameScene::InGameScene()
	: player(nullptr)
	,enemybase(nullptr)
	, back_ground_image(NULL)
	, back_ground_sound(NULL)
	, pause_flag(false)
	, scroll(0)
{

}

InGameScene::~InGameScene()
{

}

void InGameScene::Initialize()
{
	//LoadStageMapFoodsCSV();

	// �X�N���[���I�t�Z�b�g��ݒ�
	screen_offset.y = D_OBJECT_SIZE * 3.0f;

	// �w�i�摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/�z�u�f��/NES---Super-Mario-Bros---World-1-1�i�C���Łj.png")[0];
	back_ground_3 = rm->GetImages("Resource/Images/Block/floor.png")[0];
	back_ground_4 = rm->GetImages("Resource/Images/Block/kai_block.png")[0];
	back_ground_S = rm->GetImages("Resource/Images/sora.png")[0];
	back_ground_L = rm->GetImages("Resource/Images/cloud1.png")[0];
	back_ground_K = rm->GetImages("Resource/Images/cloud3.png")[0];
	back_ground_O = rm->GetImages("Resource/Images/cloud6.png")[0];
	back_ground_I = rm->GetImages("Resource/Images/cloud4.png")[0];
	back_ground_U = rm->GetImages("Resource/Images/cloud2.png")[0];
	back_ground_J = rm->GetImages("Resource/Images/cloud5.png")[0];
	back_ground_H = rm->GetImages("Resource/Images/ha2.png")[0];
	back_ground_N = rm->GetImages("Resource/Images/ha1.png")[0];
	back_ground_Y = rm->GetImages("Resource/Images/ha0.png")[0];
	back_ground_f = rm->GetImages("Resource/Images/mountain_right.png")[0];
	back_ground_g = rm->GetImages("Resource/Images/mountain_left.png")[0];
	back_ground_h = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
	back_ground_n = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
	back_ground_y = rm->GetImages("Resource/Images/mountain_up.png")[0];
	back_ground_p = rm->GetImages("Resource/Images/mountain_surface.png")[0];
	back_ground_E = rm->GetImages(("Resource/Images/Enemy/kuribo.png"), 3, 3, 1, 32, 32)[0];
	back_ground_B = rm->GetImages("Resource/Images/Block/block.png")[0];
	back_ground_Q = rm->GetImages(("Resource/Images/Block/hatena.png"),4,4,1,32,32)[0];
	back_ground_R = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
	back_ground_C = rm->GetImages("Resource/Images/dokan_left_down.png")[0];
	back_ground_W = rm->GetImages("Resource/Images/dokan_right_up.png")[0];
	back_ground_X = rm->GetImages("Resource/Images/dokan_right_down.png")[0];
	back_ground_F = rm->GetImages("Resource/Images/flag.png")[0];          //���̉摜
	back_ground_s = rm->GetImages("Resource/Images/pole.png")[0];          //�|�[���̏�̓_�̉摜
	back_ground_r = rm->GetImages("Resource/Images/pole_down.png")[0];          //�|�[���̖_�̕����̉摜

	// BGM�̓ǂݍ���
	back_ground_sound = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	PlaySoundMem(back_ground_sound, DX_PLAYTYPE_BACK);

	// ���[�h�ɂ���āA��������I�u�W�F�N�g��ς���
			// �����ʒu�̏��
	player = CreateObject<Player>(Vector2D(100,100));
	enemybase = CreateObject<EnemyBase>(Vector2D(150, 100));

}

eSceneType InGameScene::Update(const float& delta_second)
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyDown(KEY_INPUT_P) || input->GetButtonDown(XINPUT_BUTTON_START))
	{
		pause_flag = !pause_flag;
	}
	if (player->GetLocation().x >= D_WIN_MAX_X/2 && input->GetKey(KEY_INPUT_D))
	{
		scroll -= 300* delta_second;
		if (scroll < -6080)
		{
			scroll += 300 * delta_second;
		}
	}


	if (!pause_flag)
	{
		// �e�N���X�̍X�V�������Ăяo��
		__super::Update(delta_second);

		// �v���C���[�����񂾂�A�ăX�^�[�g
		//if (player->GetDestroy())
		//{
		//	return eSceneType::re_start;
		//}
	}

	// �V�[������ԋp����
	return GetNowSceneType();
}

void InGameScene::Draw() const
{
	// �}�b�v�f�[�^�ǂݍ��ݐ�������
	LoadStageMapCSV();

	//�����蔻��̂���摜�̐�������
	LoadStageMapHanteiCSV();

	// �w�i�摜�̕`��
	//DrawRotaGraph(336, 432, 1.5, 0.0, back_ground_image, TRUE);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	// UI�n�̕`�揈��
	if (pause_flag)
	{
		DrawString(10, 10, " P A U S E ", GetColor(255, 255, 255), TRUE);
	}
}

void InGameScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="target">1�ڂ̃Q�[���I�u�W�F�N�g</param>
/// <param name="partner">2�ڂ̃Q�[���I�u�W�F�N�g</param>
void InGameScene::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	CapsuleCollision tc = target->GetCollision();
	CapsuleCollision pc = partner->GetCollision();

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{

		// �����̎n�_�ƏI�_��ݒ肷��
		tc.point[0] += target->GetLocation();
		tc.point[1] += target->GetLocation();
		pc.point[0] += partner->GetLocation();
		pc.point[1] += partner->GetLocation();

		// �J�v�Z�����m�̓����蔻��
		if (IsCheckCollision(tc, pc))
		{
			// �������Ă��邱�Ƃ�ʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}

	}
}

/// <summary>
/// �X�e�[�W�}�b�v�i�ǁj�ǂݍ��ݏ���
/// </summary>
void InGameScene::LoadStageMapCSV() const
{
	 //�ǂݍ��ރt�@�C����
	FILE* fp = NULL;
	//�w��t�@�C����ǂݍ���
	fopen_s(&fp, "Map/SuperMario_Map.csv", "r");

	 //�G���[�`�F�b�N
	if (fp==NULL)
	{
		throw ("�t�@�C�����J���܂���\n");
	}
	else
	{
		//�}�b�v�`�b�v�����ݗp�ϐ�
		int mode = 0;

		//�J�E���g�p�ϐ�
		int i = 0;
		int j = 0;

		while (mode != EOF)
		{
			mode = fgetc(fp);


			if (mode == ',')
			{
				j++;
				continue;
			}
			else if (mode == '\n')
			{
				i++;
				j = 0;
				continue;
			}
			else
			{
				//���[�h�ɂ���āA��������I�u�W�F�N�g��ς���
				Vector2D generate_location;		// �����ʒu�̏��
				generate_location.x = (float)(j * 32 - 16) + scroll;
				generate_location.y = (float)(i * 32 - 16);

				switch (mode)
				{
					//��
				case '#':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_3, TRUE);
					break;
				//	// �K�i�u���b�N
				//case '$':
				//	DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_4, TRUE);
				//	break;
				//	//�v���C���[
				//case 'P':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	player = CreateObject<Player>(generate_location);
				//	break;
				//	//�N���{�[�G�l�~�[
				//case 'E':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//�m�R�m�R�G�l�~�[
				//case 'a':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//�u���b�N
				//case 'B':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//�H�u���b�N
				//case 'Q':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//��
				case 'S':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_S, TRUE);
					break;
				//�_�̍���
				case 'L':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_L, TRUE);
					break;
				//�_�̉E��
				case 'K':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_K, TRUE);
					break;
				//�_�̍���
				case 'O':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_O, TRUE);
					break;
				//�_�̉E��
				case 'I':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_I, TRUE);
					break;
				//�_�̒���
				case 'U':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_U, TRUE);
					break;
				//�_�̒���
				case 'J':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_J, TRUE);
					break;
				//	//�t���O
				//case 'F':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//���t���O
				//case 'G':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//�t���ς̉E
				case 'H':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_H, TRUE);
					break;
				//�t���ς̒�
				case 'N':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_N, TRUE);
					break;
				//�t���ς̍�
				case 'Y':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_Y, TRUE);
					break;
				//�R�̉E
				case 'f':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_f, TRUE);
					break;
				//�R�̍�
				case 'g':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_g, TRUE);
					break;
				//�R�̒��E
				case 'h':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_h, TRUE);
					break;
				//�R�̒���
				case 'n':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_n, TRUE);
					break;
				//�R�̂Ă��؂�
				case 'y':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_y, TRUE);
					break;
				//�R�̒��S
				case 'p':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_p, TRUE);
					break;
				//	//�|�[���̏�̓_
				//case 's':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//�|�[���̖_�̕���
				//case 'r':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//��
				//case 'c':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//���y�ǂ̍���
				//case 'w':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//���y�ǂ̍���
				//case 'x':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//���y�ǂ̉E��
				//case 'l':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//���y�ǂ̉E��
				//case 'k':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//���y�ǂ̒���
				//case 'o':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
				//	//���y�ǂ̒���
				//case 'i':
				//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
				//	CreateObject<EnemyBase>(generate_location);
				//	break;
					//��L�ȊO
				default:
					break;
				}
			}
		}
		fclose(fp); // �t�@�C�������
	}

	
}

 //<summary>
 //�X�e�[�W�}�b�v(����)�ǂݍ��ݏ���
 //</summary>
void InGameScene::LoadStageMapHanteiCSV() const
{
	//�ǂݍ��ރt�@�C����
	FILE* fp = NULL;
	//�w��t�@�C����ǂݍ���
	fopen_s(&fp, "Map/SupeerMario_Map_Hantei.csv", "r");

	//�G���[�`�F�b�N
	if (fp == NULL)
	{
		throw ("�t�@�C�����J���܂���\n");
	}
	else
	{
		//�}�b�v�`�b�v�����ݗp�ϐ�
		int mode = 0;

		//�J�E���g�p�ϐ�
		int i = 0;
		int j = 0;

		while (mode != EOF)
		{
			mode = fgetc(fp);


			if (mode == ',')
			{
				j++;
				continue;
			}
			else if (mode == '\n')
			{
				i++;
				j = 0;
				continue;
			}
			else
			{
				//���[�h�ɂ���āA��������I�u�W�F�N�g��ς���
				Vector2D generate_location;		// �����ʒu�̏��
				generate_location.x = (float)(j * 32 - 16) + scroll;
				generate_location.y = (float)(i * 32 - 16);

				switch (mode)
				{
					//��
				case '#':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_3, TRUE);
					break;
					// �K�i�u���b�N
				case '$':
					DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_4, TRUE);
					break;
				
						//�N���{�[�G�l�~�[
					case 'E':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_E, TRUE);
						break;
					//	//�m�R�m�R�G�l�~�[
					//case 'a':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
						//�u���b�N
					case 'B':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_B, TRUE);
						break;
						//�H�u���b�N
					case 'Q':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_Q, TRUE);
						break;
						//�y�ǂ̉E��
					case 'R':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_R, TRUE);
						break;
						//�y�ǂ̉E��
					case 'C':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_C, TRUE);
						break;
						//�y�ǂ̍���
					case 'W':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_W, TRUE);
						break;
						//�y�ǂ̍���
					case 'X':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_X, TRUE);
						break;
						//�t���O
					case 'F':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_F, TRUE);
						break;
					//	//���t���O
					//case 'G':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
	
						//�|�[���̏�̓_
					case 's':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_s, TRUE);
						break;
						//�|�[���̖_�̕���
					case 'r':
						DrawRotaGraph(generate_location.x, generate_location.y, 1.0, 0.0, back_ground_r, TRUE);
						break;
					//	//��
					//case 'c':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//���y�ǂ̍���
					//case 'w':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//���y�ǂ̍���
					//case 'x':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//���y�ǂ̉E��
					//case 'l':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//���y�ǂ̉E��
					//case 'k':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//���y�ǂ̒���
					//case 'o':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
					//	//���y�ǂ̒���
					//case 'i':
					//	generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
					//	CreateObject<EnemyBase>(generate_location);
					//	break;
						//��L�ȊO
				default:
					break;
				}
			}
		}
		fclose(fp); // �t�@�C�������
	}


}
