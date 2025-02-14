#include "DxLib.h"
#include "BlockData.h"
#include <iostream>

Block::Block(const Vector2D& position, int width, int height, int image)
    : GameObjectBase(), width_(width), height_(height)
{
    this->location = position;
    this->image = image;
    this->collision = CapsuleCollision();
    this->collision.point[0] = position;
    this->collision.point[1] = Vector2D(position.x + width, position.y + height);
    this->collision.radius = width / 2;
}

void Block::Initialize()
{
    // �摜�ǂݍ��ݏ���
    this->image = LoadGraph("Resource/Images/Block/block.png");
    if (this->image == -1)
    {
        std::cerr << "�摜�̃��[�h�Ɏ��s���܂����B" << std::endl;
    }
}

void Block::Update(float delta_second)
{
    // �X�V�����i�K�v�ɉ����Ēǉ�
}

void Block::Draw(const Vector2D& screen_offset) const
{

    Vector2D draw_location = location + screen_offset;
    DrawRotaGraphF(draw_location.x, draw_location.y, 220.0, 200.0, image, TRUE, FALSE);
}

void Block::Finalize()
{
    // �I���������i�K�v�ɉ����Ēǉ��j
}

void Block::OnHitCollision(GameObjectBase* hit_object)
{
    std::cout << "Block at (" << location.x << ", " << location.y << ") was hit!\n";
}

