#pragma once

#include "BlockData.h"
#include <vector>

class BlockManager
{

public:
    void AddBlock(Block* block);
    void UpdateBlocks(float delta_second);
    void DrawBlocks(const Vector2D& screen_offset) const;
    void FinalizeBlocks();
    void CheckCollisions(const std::vector<GameObjectBase*>& game_objects);

private:
    std::vector<Block*> blocks_;

};
