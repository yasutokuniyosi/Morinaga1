#pragma once

#include "../../Objects/GameObjectBase.h"
#include "../../Utility/Vector2D.h"

class Block : public GameObjectBase
{
public:
    Block(const Vector2D& position, int width, int height, int image);


    void Initialize() override;
    void Update(float delta_second) override; 
    void Draw(const Vector2D& screen_offset) const override;
    void Finalize() override;
    void OnHitCollision(GameObjectBase* hit_object) override;

private:
    int width_;
    int height_;
};
