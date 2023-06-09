#include "Star.h"

USING_NS_CC;

namespace
{
	const int MAX_STAR_NUM = 5;
	const float MOVE_SPEED = 300.0f;
	const std::string STAR_PATH[MAX_STAR_NUM] =
		{
			std::string("stars/red.png"),
			std::string("stars/yellow.png"),
			std::string("stars/green.png"),
			std::string("stars/blue.png"),
			std::string("stars/purple.png"),
	};

	void Clamp(int &val, int min, int max)
	{
		if (val < min)
		{
			val = min;
		}
		else if (val > max)
		{
			val = max;
		}
	}
}

Star::Star(int index)
{
	this->index = index;
	Clamp(this->index, 1, MAX_STAR_NUM);
	highlight = false;

	init();
}

Star *Star::create(int index)
{
	Star *pRet = new Star(index);
	std::string path = pRet->getPath();
	if (pRet && pRet->initWithFile(path.c_str()))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool Star::isHighLight()
{
	return highlight;
}

void Star::setHighLight(bool hl)
{
	highlight = hl;
}

int Star::getIndex()
{
	return index;
}

void Star::setPos(const cocos2d::Point &pos)
{
	Sprite::setPosition(pos);

	destPos = pos;
}

cocos2d::Point Star::getDestPos()
{
	return destPos;
}

void Star::setDestPos(const cocos2d::Point &pos)
{
	destPos = pos;
}

bool Star::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

void Star::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	if (_texture == nullptr || _texture->getBackendTexture() == nullptr)
		return;

	// TODO: arnold: current camera can be a non-default one.
	setMVPMatrixUniform();
	BlendFunc bf;

	if (highlight)
		bf = {backend::BlendFactor::ONE, backend::BlendFactor::SRC_COLOR};
	else
		bf = {backend::BlendFactor::ONE, backend::BlendFactor::ZERO};

	setBlendFunc(bf);

#if CC_USE_CULLING
	// Don't calculate the culling if the transform was not updated
	auto visitingCamera = Camera::getVisitingCamera();
	auto defaultCamera = Camera::getDefaultCamera();
	if (visitingCamera == nullptr)
		_insideBounds = true;
	else if (visitingCamera == defaultCamera)
		_insideBounds = ((flags & FLAGS_TRANSFORM_DIRTY) || visitingCamera->isViewProjectionUpdated()) ? renderer->checkVisibility(transform, _contentSize) : _insideBounds;
	else
		// XXX: this always return true since
		_insideBounds = renderer->checkVisibility(transform, _contentSize);

	if (_insideBounds)
#endif
	{
		_trianglesCommand.init(_globalZOrder,
							   _texture,
							   bf,
							   _polyInfo.triangles,
							   transform,
							   flags);
		renderer->addCommand(&_trianglesCommand);

#if CC_SPRITE_DEBUG_DRAW
		_debugDrawNode->clear();
		auto count = _polyInfo.triangles.indexCount / 3;
		auto indices = _polyInfo.triangles.indices;
		auto verts = _polyInfo.triangles.verts;
		for (unsigned int i = 0; i < count; i++)
		{
			// draw 3 lines
			Vec3 from = verts[indices[i * 3]].vertices;
			Vec3 to = verts[indices[i * 3 + 1]].vertices;
			_debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x, to.y), Color4F::WHITE);

			from = verts[indices[i * 3 + 1]].vertices;
			to = verts[indices[i * 3 + 2]].vertices;
			_debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x, to.y), Color4F::WHITE);

			from = verts[indices[i * 3 + 2]].vertices;
			to = verts[indices[i * 3]].vertices;
			_debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x, to.y), Color4F::WHITE);
		}
#endif // CC_SPRITE_DEBUG_DRAW
	}
}

void Star::onUpdate(float delta)
{
	Point curPos = getPosition();
	if (curPos.equals(destPos))
	{
		setPosition(destPos);
	}

	float speedX = 0.f;
	float speedY = 0.f;
	if (fabs(curPos.x - destPos.x) < FLT_EPSILON)
	{
		speedX = 0.f;
	}
	else if (curPos.x < destPos.x)
	{
		speedX = MOVE_SPEED;
	}
	else
	{
		speedX = -MOVE_SPEED;
	}

	if (fabs(curPos.y - destPos.y) < FLT_EPSILON)
	{
		speedY = 0.f;
	}
	else if (curPos.y < destPos.y)
	{
		speedY = MOVE_SPEED;
	}
	else
	{
		speedY = -MOVE_SPEED;
	}

	float tempPosX = curPos.x + delta * speedX;
	if (speedX > 0)
	{
		if (tempPosX > destPos.x)
		{
			tempPosX = destPos.x;
		}
	}
	else if (speedX < 0)
	{
		if (tempPosX < destPos.x)
		{
			tempPosX = destPos.x;
		}
	}

	float tempPosY = curPos.y + delta * speedY;
	if (speedY > 0)
	{
		if (tempPosY > destPos.y)
		{
			tempPosY = destPos.y;
		}
	}
	else if (speedY < 0)
	{
		if (tempPosY < destPos.y)
		{
			tempPosY = destPos.y;
		}
	}
	setPosition(Vec2(tempPosX, tempPosY));

	/*if ( ((int)curPos.x != (int)destPos.x) || ((int)curPos.y != (int)destPos.y) )
	{
		float disX = curPos.x - destPos.x;
		float disY = curPos.y - destPos.y;

		CCPoint newPos;
		newPos.x = curPos.x - disX * delta * MOVE_SPEED;
		newPos.y = curPos.y - disY * delta * MOVE_SPEED;
		setPosition(newPos);
	}*/
}

std::string Star::getPath()
{
	return STAR_PATH[index - 1];
}
