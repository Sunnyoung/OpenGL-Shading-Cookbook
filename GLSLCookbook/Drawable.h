#pragma once

class Drawable{
public:
	Drawable(void);
	virtual ~Drawable(void);
	virtual void render() const = 0;
};


