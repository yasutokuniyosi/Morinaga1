#include "ResultScene.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{

}

eSceneType ResultScene::Update(const float& delta_second)
{
	// �e�N���X�̍X�V�������Ăяo��
	__super::Update(delta_second);

	// �V�[�����
	return GetNowSceneType();
}

void ResultScene::Draw() const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

void ResultScene::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::result;
}
