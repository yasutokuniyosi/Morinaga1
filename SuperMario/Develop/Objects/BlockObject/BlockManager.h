#pragma once

#include "BlockData.h"
#include <vector>

// �u���b�N���Ǘ�����N���X
class BlockManager
{
public:
    // �V�����u���b�N��ǉ�����֐�
    void AddBlock(Block* block);

    // �S�u���b�N���X�V����֐�
    void UpdateBlocks(float delta_second);

    // �S�u���b�N��`�悷��֐�
    void DrawBlocks(const Vector2D& screen_offset) const;

    // �S�u���b�N���ŏI��������֐�
    void FinalizeBlocks();

    // �u���b�N�Ƒ��̃Q�[���I�u�W�F�N�g�̏Փ˂��`�F�b�N����֐�
    void CheckCollisions(const std::vector<GameObjectBase*>& game_objects);

private:
    std::vector<Block*> blocks_; // �Ǘ�����u���b�N�̃��X�g

};
