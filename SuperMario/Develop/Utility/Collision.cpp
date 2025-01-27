#include "Collision.h"
#include <math.h>

/// <summary>
/// �K�p�I�u�W�F�N�g���m�F���鏈��
/// </summary>
/// <param name="hit_object">����̃I�u�W�F�N�g�^�C�v</param>
/// <returns>�K�p����I�u�W�F�N�g�Ȃ�Atrue</returns>
bool CapsuleCollision::IsCheckHitTarget(eObjectType hit_object) const
{
	// �K�p����I�u�W�F�N�g�^�C�v�Ȃ�Atrue
	for (eObjectType type : hit_object_type)
	{
		if (type == hit_object)
		{
			return true;
		}
	}

	return false;
}

/// <summary>
/// �~�Ɖ~�̓����蔻��m�F����
/// </summary>
/// <param name="c1">�~�̏��1</param>
/// <param name="c2">�~�̏��2</param>
/// <returns>�������Ă���Ȃ�Atrue</returns>
bool IsCheckCollision(const CircleCollision& c1, const CircleCollision& c2)
{
	// 2�_�Ԃ̋����ƒ���
	Vector2D diff = (c1.point - c2.point);
	float len = diff.SqrLength();

	// ���a�̒���
	float r = (c1.radius + c2.radius) * (c1.radius + c2.radius);

	// �O�����̒藝�ɂ��A�����蔻����m�F����
	if (len < r)
	{
		return true;
	}

	return false;
}
bool IsCheckCollision(const CapsuleCollision& c1, const CircleCollision& c2)
{
	CircleCollision circle;
	// �ŋߖT�_�����߂�
	circle.point = NearPointCheck(c1, c2.point);
	// ���a���̐ݒ�
	circle.radius = c1.radius;

	// �~�`���m�̓����蔻��
	return IsCheckCollision(circle, c2);
}
bool IsCheckCollision(const CapsuleCollision& c1, const CapsuleCollision& c2)
{
	CircleCollision circle;

	// c2�̎n�_���~�`�Ƃ��Ĉ����āA
	// c1�J�v�Z���Ɠ������Ă��邩�m�F����
	circle.radius = c2.radius;
	circle.point = c2.point[0];
	if (IsCheckCollision(c1, circle))
	{
		return true;
	}

	// c2�̏I�_���~�`�Ƃ��Ĉ����āA
	// c1�J�v�Z���Ɠ������Ă��邩�m�F����
	circle.radius = c2.radius;
	circle.point = c2.point[1];
	if (IsCheckCollision(c1, circle))
	{
		return true;
	}

	// c1�̎n�_���~�`�Ƃ��Ĉ����āA
	// c2�J�v�Z���Ɠ������Ă��邩�m�F����
	circle.radius = c1.radius;
	circle.point = c1.point[0];
	if (IsCheckCollision(c2, circle))
	{
		return true;
	}

	// c1�̏I�_���~�`�Ƃ��Ĉ����āA
	// c2�J�v�Z���Ɠ������Ă��邩�m�F����
	circle.radius = c1.radius;
	circle.point = c1.point[1];
	if (IsCheckCollision(c2, circle))
	{
		return true;
	}

	// �S�Ă̏������������Ă��Ȃ��ꍇ�A�������Ă��Ȃ�
	return false;
}

/// <summary>
/// �_�ƃJ�v�Z���̐����̍ŋߖT�_�����߂鏈��
/// </summary>
/// <param name="cap">�J�v�Z�����</param>
/// <param name="point">�~�̒��S�_</param>
/// <returns>�ŋߖT�_</returns>
Vector2D NearPointCheck(const CapsuleCollision& cap, const Vector2D& point)
{
	// �����̌�����\���x�N�g��
	Vector2D line = cap.point[1] - cap.point[0];
	// �����̎n�_����_�Ƀx�N�g�����v�Z����
	Vector2D a1 = point - cap.point[0];
	// �����̏I�_����_�Ƀx�N�g�����v�Z����
	Vector2D a2 = point - cap.point[1];

	// �_�ƃJ�v�Z���̐����̍ŋߖT�_�����߂�
	if (Vector2D::Dot(line, a1) < 0.0f)
	{
		return cap.point[0];
	}
	if (Vector2D::Dot(line, a2) > 0.0f)
	{
		return cap.point[1];
	}

	// �����Ƃ̍ŋߖT�_�����߂�
	Vector2D n = line.Normalize();
	float dot = Vector2D::Dot(n, a1);
	return (cap.point[0] + (n * dot));
}
