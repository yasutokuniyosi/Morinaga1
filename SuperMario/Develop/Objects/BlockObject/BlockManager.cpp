#include "BlockManager.h"

// �V�����u���b�N��ǉ�����֐�
void BlockManager::AddBlock(Block* block)
{
    blocks_.push_back(block);
}

// �u���b�N���X�V����֐�
void BlockManager::UpdateBlocks(float delta_second)
{
    for (auto& block : blocks_)
    {
        block->Update(delta_second);
    }
}

// �u���b�N��`�悷��֐�
void BlockManager::DrawBlocks(const Vector2D& screen_offset) const
{
    for (const auto& block : blocks_)
    {
        block->Draw(screen_offset);
    }
}

// �u���b�N���ŏI��������֐�
void BlockManager::FinalizeBlocks()
{
    for (auto& block : blocks_)
    {
        block->Finalize();
        delete block;
    }
    blocks_.clear();
}

// �Փ˂��`�F�b�N����֐�
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
