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
    // 画像読み込み処理
    this->image = LoadGraph("Resource/Images/Block/block.png");
    if (this->image == -1)
    {
        std::cerr << "画像のロードに失敗しました。" << std::endl;
    }
}

void Block::Update(float delta_second)
{
    // 更新処理（必要に応じて追加
}

void Block::Draw(const Vector2D& screen_offset) const
{

    Vector2D draw_location = location + screen_offset;
    DrawRotaGraphF(draw_location.x, draw_location.y, 220.0, 200.0, image, TRUE, FALSE);
}

void Block::Finalize()
{
    // 終了時処理（必要に応じて追加）
}

void Block::OnHitCollision(GameObjectBase* hit_object)
{
    std::cout << "Block at (" << location.x << ", " << location.y << ") was hit!\n";
}

