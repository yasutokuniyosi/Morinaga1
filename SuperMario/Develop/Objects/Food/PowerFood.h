#pragma once

#include "../GameObject.h"

// �p���[�a�N���X
class PowerFood : public GameObject
{
private:
	bool is_disp;
	float disp_time;

public:
	PowerFood();
	virtual ~PowerFood();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

};