#include "BlockManager.h"

// 新しいブロックを追加する関数
void BlockManager::AddBlock(Block* block)
{
    blocks_.push_back(block);
}

// ブロックを更新する関数
void BlockManager::UpdateBlocks(float delta_second)
{
    for (auto& block : blocks_)
    {
        block->Update(delta_second);
    }
}

// ブロックを描画する関数
void BlockManager::DrawBlocks(const Vector2D& screen_offset) const
{
    for (const auto& block : blocks_)
    {
        block->Draw(screen_offset);
    }
}

// ブロックを最終処理する関数
void BlockManager::FinalizeBlocks()
{
    for (auto& block : blocks_)
    {
        block->Finalize();
        delete block;
    }
    blocks_.clear();
}

// 衝突をチェックする関数
void BlockManager::CheckCollisions(const std::vector<GameObjectBase*>& game_objects)
{
    for (auto& block : blocks_)
    {
        for (auto& object : game_objects)
        {
            if (IsCheckCollision(block->GetCollision(), object->GetCollision()))
            {
                block->OnHitCollision(object);
                object->OnHitCollision(block);
            }
        }
    }
}
