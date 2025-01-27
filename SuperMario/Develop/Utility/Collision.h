#pragma once

#include "Vector2D.h"
#include <vector>

// �I�u�W�F�N�g�^�C�v
enum class eObjectType : unsigned char
{
	none,
	player,
	enemy,
	wall,
	food,
	power_food,
	special,
};

// �����蔻����N���X
class CapsuleCollision
{
public:
	bool						is_blocking;		// ���蔲���t���O
	eObjectType					object_type;		// ���g�̃I�u�W�F�N�g�^�C�v
	std::vector<eObjectType>	hit_object_type;	// �K�p����I�u�W�F�N�g�^�C�v
	float						radius;				// �~�̔��a
	Vector2D					point[2];			// �n�_�ƏI�_�i���΍��W�j

public:
	CapsuleCollision() :
		is_blocking(false),
		object_type(eObjectType::none),
		hit_object_type(),
		radius(0.0f)
	{
		point[0] = 0.0f;
		point[1] = 0.0f;
	}
	~CapsuleCollision()
	{
		hit_object_type.clear();
	}

	// �����蔻��L���m�F����
	bool IsCheckHitTarget(eObjectType hit_object) const;
};

// �~�`��N���X
class CircleCollision
{
public:
	Vector2D point;
	float radius;

public:
	CircleCollision() :
		point(0.0f), radius(0.0f)
	{

	}
	~CircleCollision() = default;
};


/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="c1">�`��̏��1</param>
/// <param name="c2">�`��̏��2</param>
/// <returns>�������Ă���Ȃ�Atrue</returns>
bool IsCheckCollision(const CircleCollision& c1, const CircleCollision& c2);
bool IsCheckCollision(const CapsuleCollision& c1, const CircleCollision& c2);
bool IsCheckCollision(const CapsuleCollision& c1, const CapsuleCollision& c2);

/// <summary>
/// �_�ƃJ�v�Z���̐����̍ŋߖT�_�����߂鏈��
/// </summary>
/// <param name="cap">�J�v�Z�����</param>
/// <param name="point">�~�̒��S�_</param>
/// <returns>�ŋߖT�_</returns>
Vector2D NearPointCheck(const CapsuleCollision& cap, const Vector2D& point);
