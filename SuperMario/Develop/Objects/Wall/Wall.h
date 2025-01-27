#pragma once

#include "../GameObject.h"

class Wall : public GameObject
{
public:
	Wall();
	virtual ~Wall();

	virtual void Initialize() override;
	virtual void Draw(const Vector2D& screen_offset) const override;

public:
	// ï«ÉfÅ[É^ÇÃê›íË
	void SetWallData(int x_size, int y_size);
};