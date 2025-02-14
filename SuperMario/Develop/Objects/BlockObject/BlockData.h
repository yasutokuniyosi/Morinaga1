#pragma once

#include "../../Objects/GameObjectBase.h"
#include "../../Utility/Vector2D.h"

// ブロッククラス。GameObjectBaseを継承
class Block : public GameObjectBase
{
public:
    // コンストラクタ。位置、幅、高さ、画像を受け取る
    Block(const Vector2D& position, int width, int height, int image);

    // 初期化関数
    void Initialize() override;

    // 更新関数
    void Update(float delta_second) override;

    // 描画関数
    void Draw(const Vector2D& screen_offset) const override;

    // 最終処理関数
    void Finalize() override;

    // 衝突時に呼ばれる関数
    void OnHitCollision(GameObjectBase* hit_object) override;

private:
    int width_;    // ブロックの幅
    int height_;   // ブロックの高さ
};
