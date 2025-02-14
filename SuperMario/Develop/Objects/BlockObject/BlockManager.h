#pragma once

#include "BlockData.h"
#include <vector>

// ブロックを管理するクラス
class BlockManager
{
public:
    // 新しいブロックを追加する関数
    void AddBlock(Block* block);

    // 全ブロックを更新する関数
    void UpdateBlocks(float delta_second);

    // 全ブロックを描画する関数
    void DrawBlocks(const Vector2D& screen_offset) const;

    // 全ブロックを最終処理する関数
    void FinalizeBlocks();

    // ブロックと他のゲームオブジェクトの衝突をチェックする関数
    void CheckCollisions(const std::vector<GameObjectBase*>& game_objects);

private:
    std::vector<Block*> blocks_; // 管理するブロックのリスト

};
