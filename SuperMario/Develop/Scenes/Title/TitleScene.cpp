#include "TitleScene.h"
#include "../../Utility/InputManager.h"
#include "DxLib.h"

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{

}

eSceneType TitleScene::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �C���Q�[���V�[���ɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	// UI�̕`��
	SetFontSize(60);
	DrawFormatString(120, 140, GetColor(255, 255, 0), "SuperMario");
	SetFontSize(40);
	DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed game start");
	SetFontSize(16);

	int TitleGraph = LoadGraph("Resource/Images/title.png");
	DrawGraph(0, 0, TitleGraph, TRUE);
	DeleteGraph(TitleGraph);
}

void TitleScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
