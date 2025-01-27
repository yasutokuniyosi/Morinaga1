#pragma once

#include "SceneBase.h"

class SceneManager
{
private:
	SceneBase* current_scene;	// ���݂̃V�[�����

public:
	SceneManager();
	~SceneManager();

	/// <summary>
	/// ����������
	/// </summary>
	void WakeUp();

	/// <summary>
	///  ���s����
	/// </summary>
	void Run();

	/// <summary>
	/// �I��������
	/// </summary>
	void Shutdown();

private:
	/// <summary>
	/// �`�揈��
	/// </summary>
	void Graph() const;

	/// <summary>
	/// �V�[���؂�ւ�����
	/// </summary>
	/// <param name="next_type">���̃V�[���^�C�v</param>
	void ChangeScene(eSceneType next_type);

	/// <summary>
	/// �V�[����������
	/// </summary>
	/// <param name="next_type">���̃V�[���^�C�v</param>
	/// <returns>���������V�[�����̃|�C���^</returns>
	SceneBase* CreateScene(eSceneType next_type);
};