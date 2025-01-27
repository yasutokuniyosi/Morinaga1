#pragma once

#include "GameObjectBase.h"
#include "../Scenes/SceneBase.h"

// �Q�[���I�u�W�F�N�g�N���X
class GameObject : public GameObjectBase
{
public:
	/// <summary>
	/// �Q�[���I�u�W�F�N�g��������
	/// </summary>
	/// <typeparam name="OBJECT">��������Q�[���I�u�W�F�N�g�N���X</typeparam>
	/// <param name="generate_location">�����ʒu</param>
	/// <returns>���������Q�[���I�u�W�F�N�g�̃|�C���^</returns>
	template <class OBJECT>
	OBJECT* CreateObject(const Vector2D& generate_location)
	{
		return owner_scene->CreateObject<OBJECT>(generate_location);
	}

	/// <summary>
	/// �I�u�W�F�N�g�j������
	/// </summary>
	/// <param name="target">�j�����s���Q�[���I�u�W�F�N�g�̃|�C���^</param>
	void DestroyObject(GameObjectBase* target)
	{
		owner_scene->DestroyObject(target);
	}

	/// <summary>
	/// �X�N���[���I�t�Z�b�g���擾����
	/// </summary>
	/// <returns>�X�N���[���I�t�Z�b�g�l</returns>
	const Vector2D GetScreenOffset() const
	{
		return owner_scene->GetScreenOffset();
	}
};