/*!
 * \file AnimatedLabel.cpp
 *
 * \author dhcdht
 * \date 五月 2014
 *
 * 
 */
#include "AnimatedLabel.h"

using namespace std;
using namespace cocos2d;


AnimatedLabel::AnimatedLabel(
	FontAtlas* atlas /*= nullptr*/,
	TextHAlignment hAlignment /*= TextHAlignment::LEFT*/,
	TextVAlignment vAlignment /*= TextVAlignment::TOP*/,
	bool useDistanceField /*= false*/,
	bool useA8Shader /*= false*/)
	:Label(atlas, hAlignment, vAlignment, useDistanceField, useA8Shader)
{

}

#pragma mark - Override Create Methods	//重写Label的create方法，返回AnimatedLabel实例
AnimatedLabel* AnimatedLabel::create()
{
	AnimatedLabel* ret = new AnimatedLabel();

	if (ret)
	{
		ret->autorelease();
	}
	
	return ret;
}

AnimatedLabel* AnimatedLabel::createWithSystemFont(
	const std::string& text, 
	const std::string& font, 
	float fontSize,
	const Size& dimensions /*= Size::ZERO*/,
	TextHAlignment hAlignment /*= TextHAlignment::LEFT*/,
	TextVAlignment vAlignment /*= TextVAlignment::TOP*/)
{
	AnimatedLabel* ret = new AnimatedLabel(nullptr, hAlignment, vAlignment);

	if (ret)
	{
		ret->setSystemFontName(font);
		ret->setSystemFontSize(fontSize);
		ret->setDimensions(dimensions.width, dimensions.height);
		ret->setString(text);

		ret->autorelease();

		return ret;
	}

	delete ret;
	return nullptr;
}

AnimatedLabel* AnimatedLabel::createWithTTF(
	const std::string& text,
	const std::string& fontFile,
	float fontSize,
	const Size& dimensions /*= Size::ZERO*/, 
	TextHAlignment hAlignment /*= TextHAlignment::LEFT*/, 
	TextVAlignment vAlignment /*= TextVAlignment::TOP*/)
{
	AnimatedLabel* ret = new AnimatedLabel(nullptr, hAlignment, vAlignment);

	if (ret && FileUtils::getInstance()->isFileExist(fontFile))
	{
		TTFConfig ttfConfig(
			fontFile.c_str(), 
			fontSize, 
			GlyphCollection::DYNAMIC);
		if (ret->setTTFConfig(ttfConfig))
		{
			ret->setDimensions(dimensions.width, dimensions.height);
			ret->setString(text);

			ret->autorelease();

			return ret;
		}	
	}
	
	delete ret;
	return nullptr;
}

AnimatedLabel* AnimatedLabel::createWithTTF(
	const TTFConfig& ttfConfig,
	const std::string& text,
	TextHAlignment alignment /*= TextHAlignment::LEFT*/,
	int maxLineWidth /*= 0*/)
{
	AnimatedLabel* ret = new AnimatedLabel(nullptr, alignment);

	if (ret && 
		FileUtils::getInstance()->isFileExist(ttfConfig.fontFilePath) &&
		ret->setTTFConfig(ttfConfig))
	{
		ret->setMaxLineWidth(maxLineWidth);
		ret->setString(text);
		
		ret->autorelease();

		return ret;
	}
	
	delete ret;
	return nullptr;
}

AnimatedLabel* AnimatedLabel::createWithBMFont(
	const std::string& bmfontFilePath,
	const std::string& text, 
	const TextHAlignment& alignment /*= TextHAlignment::LEFT*/, 
	int maxLineWidth /*= 0*/,
	const Point& imageOffset /*= Point::ZERO*/)
{
	AnimatedLabel* ret = new AnimatedLabel(nullptr, alignment);

	if (ret &&
		ret->setBMFontFilePath(bmfontFilePath, imageOffset))
	{
		ret->setMaxLineWidth(maxLineWidth);
		ret->setString(text);

		ret->autorelease();

		return ret;
	}
	
	delete ret;
	return nullptr;
}

AnimatedLabel* AnimatedLabel::createWithCharMap(
	const std::string& charMapFile,
	int itemWidth,
	int itemHeight,
	int startCharMap)
{
	AnimatedLabel* ret = new AnimatedLabel();

	if (ret &&
		ret->setCharMap(charMapFile))
	{
		ret->autorelease();

		return ret;
	}
	
	delete ret;
	return nullptr;
}

AnimatedLabel * AnimatedLabel::createWithCharMap(
	Texture2D* texture, 
	int itemWidth, 
	int itemHeight, 
	int startCharMap)
{
	AnimatedLabel* ret = new AnimatedLabel();

	if (ret &&
		ret->setCharMap(texture, itemWidth, itemHeight, startCharMap))
	{
		ret->autorelease();

		return ret;
	}
	
	delete ret;
	return nullptr;
}

AnimatedLabel* AnimatedLabel::createWithCharMap(const std::string& plistFile)
{
	AnimatedLabel* ret = new AnimatedLabel();

	if (ret &&
		ret->setCharMap(plistFile))
	{
		ret->autorelease();

		return ret;
	}

	delete ret;
	return nullptr;
}

#pragma mark - Basic Functions For Character Sprite	//针对字符精灵的基本操作
int AnimatedLabel::getCharSpriteCount()
{
	int stringLength = getStringLength();
	if (stringLength > 0 &&
		getLetter(0))
	{
		return stringLength;
	}
	
	return 0;
}

Sprite* AnimatedLabel::getCharSprite(int index)
{
	if (index >= getCharSpriteCount() || index < 0)
	{
		log("AnimatedLabel::getCharSprite - index out of bounds");
		return nullptr;
	}

	return getLetter(index);
}

Point AnimatedLabel::getCharOffset(int index)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return Point::ZERO;
	}

	return charSprite->getPosition();
}

void AnimatedLabel::setCharOffset(int index, Point offset)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return;
	}

	charSprite->setPosition(offset);
}

void AnimatedLabel::setAllCharOffset(Point offset)
{
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		setCharOffset(i, offset);
	}
}

void AnimatedLabel::setCharColor(int index, Color3B color)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return;
	}

	charSprite->setColor(color);
}

Color3B AnimatedLabel::getCharColor(int index)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return Color3B::WHITE;
	}

	return charSprite->getColor();
}

void AnimatedLabel::setAllCharColor(Color3B color)
{
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		setCharColor(i, color);
	}
}

float AnimatedLabel::getCharScale(int index)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return 0.0f;
	}
	
	return charSprite->getScale();
}

void AnimatedLabel::setCharScale(int index, float scale)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return;
	}
	
	charSprite->setScale(scale);
}

void AnimatedLabel::setAllCharScale(float scale)
{
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		setCharScale(i, scale);
	}
}

float AnimatedLabel::getCharOpacity(int index)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return 0.0f;
	}

	return charSprite->getOpacity();
}

void AnimatedLabel::setCharOpacity(int index, float opacity)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return;
	}

	charSprite->setOpacity(opacity);
}

void AnimatedLabel::setAllCharOpacity(float opacity)
{
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		setCharOpacity(i, opacity);
	}
}

float AnimatedLabel::getCharRotation(int index)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return 0.0f;
	}

	return charSprite->getRotation();
}

void AnimatedLabel::setCharRotation(int index, float rotation)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return;
	}

	charSprite->setRotation(rotation);
}

void AnimatedLabel::setAllCharRotation(float rotation)
{
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		setCharRotation(i, rotation);
	}	
}

#pragma mark - Run Custom Actions	//自定义动作
bool AnimatedLabel::checkCanAnimate()
{
	if (this->getCharSpriteCount() > 0)
	{
		if (nullptr != getCharSprite(0))
		{
			return true;
		}
	}

	return false;
}

void AnimatedLabel::runActionOnSpriteAtIndex(int index, Action* action)
{
	if (!checkCanAnimate())
	{
		log("AnimatedLabel::runActionOnSpriteAtIndex - label not animatable");
		return;
	}
	
    if (index >= getCharSpriteCount() || index < 0)
	{
        log("AnimatedLabel::runActionOnSpriteAtIndex - index out of bounds");
        return;
    }
    
	Action* actionCopy = action->clone();
    Sprite* charSprite = getCharSprite(index);
	if (nullptr != charSprite)
	{
		charSprite->runAction(actionCopy);
	}
}

void AnimatedLabel::runActionOnAllSprites(Action* action)
{
	if (!checkCanAnimate())
	{
		log("AnimatedLabel::runActionOnAllSprites - label not animatable");
		return;
	}

	Action* actionCopy = action->clone();
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		runActionOnSpriteAtIndex(i, actionCopy);
	}
}

void AnimatedLabel::runActionOnSpriteAtIndex(
	int index,
	FiniteTimeAction* action,
	float delay /*= 0.0f*/,
	CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	if (!checkCanAnimate())
	{
		log("AnimatedLabel::runActionOnSpriteAtIndex - label not animatable");
		return;
	}

	FiniteTimeAction* actionCopy = action->clone();
	DelayTime* delayTime = DelayTime::create(delay);
	Sequence* delayAndAction = Sequence::create(delayTime, actionCopy, callFuncOnCompletion, nullptr);

	Sprite* charSprite = getCharSprite(index);
	if (nullptr != charSprite)
	{
		charSprite->runAction(delayAndAction);
	}
}

void AnimatedLabel::runActionOnAllSprites(
	FiniteTimeAction* action, 
	float delay /*= 0.0f*/,
	bool isSequentially /*= true*/,
	float sequenceDelay /*= 0.0f*/,
	CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	if (!checkCanAnimate())
	{
		log("AnimatedLabel::runActionOnAllSprites - label not animatable");
		return;
	}

	float actionSequenceDelay = 0.0f;
	if (isSequentially)
	{
		actionSequenceDelay = sequenceDelay;
		actionSequenceDelay += action->getDuration();
	}

	FiniteTimeAction* actionCopy = action->clone();
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		runActionOnSpriteAtIndex(i, actionCopy, delay + actionSequenceDelay*i);
	}

	if (nullptr != callFuncOnCompletion)
	{
		DelayTime* delayTime = DelayTime::create(delay + actionSequenceDelay*getCharSpriteCount() + actionCopy->getDuration());
		Sequence* delayAndAction = Sequence::create(delayTime, actionCopy, callFuncOnCompletion, nullptr);
		runAction(delayAndAction);
	}
}

#pragma mark - Common Animation	//常用动画
ActionInterval* AnimatedLabel::createEaseAction(
	ActionInterval* action,
	LabelAnimationType animationType /*= LabelAnimationLinear*/,
	float animationRate /*= 1.0f*/)
{
	ActionInterval* ret = nullptr;
	switch (animationType)
	{
		case LabelAnimationLinear:
		{
			ret = action;
		}break;

		case LabelAnimationEaseIn:
		{
			ret = EaseIn::create(action, animationRate);
		}break;

		case LabelAnimationEaseOut:
		{
			ret = EaseOut::create(action, animationRate);
		}break;

		default:
		{
			ret = action;
		}break;
	}

	return ret;
}

void AnimatedLabel::animateMoveBy(float duration, Point moveByDistance, float delay /*= 0.0f*/, bool isSequentially /*= true*/, float sequenceDelay /*= 0.0f*/, LabelAnimationType animationType /*= LabelAnimationLinear*/, float animationRate /*= 1.0f*/, CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	setPosition(getPosition() + moveByDistance);
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		setCharOffset(i, getCharOffset(i) - moveByDistance);
	}

	MoveBy *moveBy = MoveBy::create(duration, moveByDistance);
	ActionInterval* easeAction = createEaseAction(moveBy, animationType, animationRate);

	runActionOnAllSprites(easeAction, delay, isSequentially, sequenceDelay, callFuncOnCompletion);
}

void AnimatedLabel::animateMoveTo(float duration, Point moveToPosition, float delay /*= 0.0f*/, bool isSequentially /*= true*/, float sequenceDelay /*= 0.0f*/, LabelAnimationType animationType /*= LabelAnimationLinear*/, float animationRate /*= 1.0f*/, CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	Point moveByDistance = moveToPosition - getPosition();
	animateMoveBy(duration, moveByDistance, delay, isSequentially, sequenceDelay, animationType, animationRate, callFuncOnCompletion);
}

void AnimatedLabel::animateTypewriter(float duration /*= 0.01f*/, float fromScale /*= 0.0f*/, float toScale /*= 1.0f*/, float delay /*= 0.0f*/, float sequenceDelay /*= 0.0f*/, LabelAnimationType animationType /*= LabelAnimationLinear*/, float animationRate /*= 1.0f*/, CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	setAllCharScale(fromScale);

	ScaleTo *scaleTo = ScaleTo::create(duration, toScale);

	runActionOnAllSprites(scaleTo, delay, true, sequenceDelay, callFuncOnCompletion);
}

void AnimatedLabel::animateSwell(float durationSwell /*= 0.2f*/, float durationReveal /*= 0.2f*/, float beginScale /*= 1.0f*/, float swellScale /*= 1.5f*/, float endScale /*= 1.0f*/, float delay /*= 0.0f*/, float sequenceDelay /*= 0.0f*/, CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	setAllCharScale(beginScale);

	ScaleTo *scaleUp = ScaleTo::create(durationSwell, swellScale);
	ScaleTo *scaleDown = ScaleTo::create(durationReveal, endScale);
	Sequence *scaleSeq = Sequence::create(scaleUp, scaleDown, NULL);

	runActionOnAllSprites(scaleSeq, delay, true, sequenceDelay, callFuncOnCompletion);
}

void AnimatedLabel::animateRainbow(float duration /*= 0.2f*/)
{
    TintTo *red = TintTo::create(duration, 255, 0, 0);
    TintTo *orange = TintTo::create(duration, 255, 153, 51);
    TintTo *yellow = TintTo::create(duration, 255, 255, 0);
    TintTo *green = TintTo::create(duration, 0, 255, 0);
    TintTo *blue = TintTo::create(duration, 0, 0, 255);
    TintTo *purple = TintTo::create(duration, 102, 0, 204);
    TintTo *pink = TintTo::create(duration, 255, 51, 255);
    TintTo *white = TintTo::create(duration, 255, 255, 255);
    
    Sequence *rainbow = Sequence::create(red, orange, yellow, green, blue, purple, pink, white, NULL);
    
    runActionOnAllSprites(rainbow, 0.0f, true, -duration * 7);
}
