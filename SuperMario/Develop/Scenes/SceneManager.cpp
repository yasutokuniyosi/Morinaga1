#include "SceneManager.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/ProjectConfig.h"
#include "DxLib.h"

#include "Title/TitleScene.h"
#include "InGame/InGameScene.h"
#include "InGame/ResultScene.h"

SceneManager::SceneManager() :
	current_scene(nullptr)
{

}

SceneManager::~SceneManager()
{
	// ����Y��h�~
	Shutdown();
}

/// <summary>
/// ����������
/// </summary>
void SceneManager::WakeUp()
{
	// �E�B���h�E���[�h�ŋN������
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

	// �E�B���h�E�^�C�g���̐ݒ�
	SetWindowText("Game Development SuperMario 2024");

	// �����������s��Ȃ�
	SetWaitVSyncFlag(FALSE);

	// Log.txt�t�@�C���̐�������iDebug���[�h�̂ݐ�������j
#if _DEBUG
	SetOutApplicationLogValidFlag(TRUE);
#else
	SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

	// Dx���C�u�����̏�����
	if (DxLib_Init() == D_FAILURE)
	{
		throw std::string("Dx���C�u�����̏������Ɏ��s���܂����I\n");
	}

	// �`����\��ʂɔ��f����
	SetDrawScreen(DX_SCREEN_BACK);

	// �ŏ��̃V�[�����^�C�g����ʂɂ���
	ChangeScene(eSceneType::title);

	// ��A�N�e�B�u��Ԃł����삳����
	SetAlwaysRunFlag(TRUE);
}

/// <summary>
///  ���s����
/// </summary>
void SceneManager::Run()
{
	// ���͏����擾����
	InputManager* input = InputManager::GetInstance();

	// ���C�����[�v
	while (ProcessMessage() == D_SUCCESS)
	{
		// ���͏��̍X�V
		input->Update();


		// �t���[�����[�g�̐���
		FreamControl();

		// �V�[���̍X�V
		eSceneType next_scene_type = current_scene->Update(GetDeltaSecond());

		// �`�揈��
		Graph();

		// �Q�[�����I�����邩�m�F����
		if ((next_scene_type == eSceneType::exit) ||
			(input->GetButtonUp(XINPUT_BUTTON_BACK)) ||
			(input->GetKeyUp(KEY_INPUT_ESCAPE)))
		{
			break;
		}

		// ���݂̃V�[���^�C�v�����̃V�[���^�C�v�ƈ���Ă��邩�H
		if (current_scene->GetNowSceneType() != next_scene_type)
		{
			// �V�[���؂�ւ�����
			ChangeScene(next_scene_type);
		}
	}
}

/// <summary>
/// �I��������
/// </summary>
void SceneManager::Shutdown()
{
	// �V�[����񂪐�������Ă���΁A�폜����
	//if (current_scene != nullptr)
	//{
	//	current_scene->Finalize();
	//	delete current_scene;
	//	current_scene = nullptr;
	//}

	// Singleton�̃C���X�^���X���������
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();

	// Dx���C�u�����̎g�p���I������
	DxLib_End();
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Graph() const
{
	// ��ʂ̏�����
	ClearDrawScreen();

	// �V�[���̕`�揈��
	current_scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();
}

/// <summary>
/// �V�[���؂�ւ�����
/// </summary>
/// <param name="next_type">���̃V�[���^�C�v</param>
void SceneManager::ChangeScene(eSceneType next_type)
{
	// ���̃V�[���𐶐�����
	SceneBase* next_scene = CreateScene(next_type);

	// �G���[�`�F�b�N
	if (next_scene == nullptr)
	{
		throw ("�V�[���������ł��܂���ł���\n");
	}

	// �V�[����񂪊i�[����Ă�����A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// ���̃V�[���̏�����
	next_scene->Initialize();

	// ���݃V�[���̏㏑��
	current_scene = next_scene;
}

/// <summary>
/// �V�[����������
/// </summary>
/// <param name="next_type">���̃V�[���^�C�v</param>
/// <returns>���������V�[�����̃|�C���^</returns>
SceneBase* SceneManager::CreateScene(eSceneType next_type)
{
	// �V�[���^�C�v�ɂ���āA��������V�[����؂�ւ���
	switch (next_type)
	{
	case eSceneType::title:
		return dynamic_cast<SceneBase*>(new TitleScene());
	case eSceneType::in_game:
	case eSceneType::re_start:
		return dynamic_cast<SceneBase*>(new InGameScene());
	case eSceneType::result:
		return dynamic_cast<SceneBase*>(new ResultScene());
	default:
		return nullptr;
	}
}
