#include "BlockManager.h"

void BlockManager::AddBlock(Block* block)
{
    blocks_.push_back(block);
}

void BlockManager::UpdateBlocks(float delta_second)
{
    for (auto& block : blocks_)
    {
        block->Update(delta_second);
    }
}

void BlockManager::DrawBlocks(const Vector2D& screen_offset) const
{
    for (const auto& block : blocks_)
    {
        block->Draw(screen_offset);
    }
}

void BlockManager::FinalizeBlocks()
{
    for (auto& block : blocks_)
    {
        block->Finalize();
        delete block;
    }
    blocks_.clear();
}

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
