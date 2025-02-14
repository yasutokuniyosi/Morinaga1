#pragma once

#include "../../Objects/GameObjectBase.h"
#include "../../Utility/Vector2D.h"

// �u���b�N�N���X�BGameObjectBase���p��
class Block : public GameObjectBase
{
public:
    // �R���X�g���N�^�B�ʒu�A���A�����A�摜���󂯎��
    Block(const Vector2D& position, int width, int height, int image);

    // �������֐�
    void Initialize() override;

    // �X�V�֐�
    void Update(float delta_second) override;

    // �`��֐�
    void Draw(const Vector2D& screen_offset) const override;

    // �ŏI�����֐�
    void Finalize() override;

    // �Փˎ��ɌĂ΂��֐�
    void OnHitCollision(GameObjectBase* hit_object) override;

private:
    int width_;    // �u���b�N�̕�
    int height_;   // �u���b�N�̍���
};
