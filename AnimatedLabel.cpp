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
	cocos2d::FontAtlas* atlas /*= nullptr*/,
	cocos2d::TextHAlignment hAlignment /*= cocos2d::TextHAlignment::LEFT*/,
	cocos2d::TextVAlignment vAlignment /*= cocos2d::TextVAlignment::TOP*/,
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
	const cocos2d::Size& dimensions /*= cocos2d::Size::ZERO*/,
	cocos2d::TextHAlignment hAlignment /*= cocos2d::TextHAlignment::LEFT*/,
	cocos2d::TextVAlignment vAlignment /*= cocos2d::TextVAlignment::TOP*/)
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
	const cocos2d::Size& dimensions /*= cocos2d::Size::ZERO*/, 
	cocos2d::TextHAlignment hAlignment /*= cocos2d::TextHAlignment::LEFT*/, 
	cocos2d::TextVAlignment vAlignment /*= cocos2d::TextVAlignment::TOP*/)
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
	const cocos2d::TTFConfig& ttfConfig,
	const std::string& text,
	cocos2d::TextHAlignment alignment /*= cocos2d::TextHAlignment::LEFT*/,
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
	const cocos2d::TextHAlignment& alignment /*= cocos2d::TextHAlignment::LEFT*/, 
	int maxLineWidth /*= 0*/,
	const cocos2d::Point& imageOffset /*= cocos2d::Point::ZERO*/)
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
	cocos2d::Texture2D* texture, 
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

cocos2d::CCSprite* AnimatedLabel::getCharSprite(int index)
{
	if (index >= getCharSpriteCount() || index < 0)
	{
		cocos2d::log("AnimatedLabel::getCharSprite - index out of bounds");
		return nullptr;
	}

	return getLetter(index);
}

cocos2d::Point AnimatedLabel::getCharOffset(int index)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return Point::ZERO;
	}

	return charSprite->getPosition();
}

void AnimatedLabel::setCharOffset(int index, cocos2d::Point offset)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return;
	}

	charSprite->setPosition(offset);
}

void AnimatedLabel::setAllCharOffset(cocos2d::Point offset)
{
	for (int i = 0; i < getCharSpriteCount(); i++)
	{
		setCharOffset(i, offset);
	}
}

void AnimatedLabel::setCharColor(int index, cocos2d::Color3B color)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return;
	}

	charSprite->setColor(color);
}

cocos2d::Color3B AnimatedLabel::getCharColor(int index)
{
	Sprite* charSprite = getCharSprite(index);
	if (nullptr == charSprite)
	{
		return Color3B::WHITE;
	}

	return charSprite->getColor();
}

void AnimatedLabel::setAllCharColor(cocos2d::Color3B color)
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

void AnimatedLabel::runActionOnSpriteAtIndex(int index, cocos2d::Action* action)
{
	if (!checkCanAnimate())
	{
		cocos2d::log("AnimatedLabel::runActionOnSpriteAtIndex - label not animatable");
		return;
	}
	
    if (index >= getCharSpriteCount() || index < 0)
	{
        cocos2d::log("AnimatedLabel::runActionOnSpriteAtIndex - index out of bounds");
        return;
    }
    
	Action* actionCopy = action->clone();
    Sprite* charSprite = getCharSprite(index);
	if (nullptr != charSprite)
	{
		charSprite->runAction(actionCopy);
	}
}

void AnimatedLabel::runActionOnAllSprites(cocos2d::Action* action)
{
	if (!checkCanAnimate())
	{
		cocos2d::log("AnimatedLabel::runActionOnAllSprites - label not animatable");
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
	cocos2d::FiniteTimeAction* action,
	float delay /*= 0.0f*/,
	cocos2d::CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	if (!checkCanAnimate())
	{
		cocos2d::log("AnimatedLabel::runActionOnSpriteAtIndex - label not animatable");
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
	cocos2d::FiniteTimeAction* action, 
	float delay /*= 0.0f*/,
	bool isSequentially /*= true*/,
	float sequenceDelay /*= 0.0f*/,
	cocos2d::CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	if (!checkCanAnimate())
	{
		cocos2d::log("AnimatedLabel::runActionOnAllSprites - label not animatable");
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
		runActionOnSpriteAtIndex(i, actionCopy, delay + actionSequenceDelay*i, callFuncOnCompletion);
	}
}

#pragma mark - Common Animation	//常用动画
cocos2d::ActionInterval* AnimatedLabel::createEaseAction(
	cocos2d::ActionInterval* action,
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

void AnimatedLabel::animateMoveBy(float duration, cocos2d::Point moveByDistance, float delay /*= 0.0f*/, bool isSequentially /*= true*/, float sequenceDelay /*= 0.0f*/, LabelAnimationType animationType /*= LabelAnimationLinear*/, float animationRate /*= 1.0f*/, cocos2d::CallFuncN* callFuncOnCompletion /*= nullptr*/)
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

void AnimatedLabel::animateMoveTo(float duration, cocos2d::Point moveToPosition, float delay /*= 0.0f*/, bool isSequentially /*= true*/, float sequenceDelay /*= 0.0f*/, LabelAnimationType animationType /*= LabelAnimationLinear*/, float animationRate /*= 1.0f*/, cocos2d::CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	Point moveByDistance = moveToPosition - getPosition();
	animateMoveBy(duration, moveByDistance, delay, isSequentially, sequenceDelay, animationType, animationRate, callFuncOnCompletion);
}

void AnimatedLabel::animateTypewriter(float duration /*= 0.01f*/, float fromScale /*= 0.0f*/, float toScale /*= 1.0f*/, float delay /*= 0.0f*/, float sequenceDelay /*= 0.0f*/, LabelAnimationType animationType /*= LabelAnimationLinear*/, float animationRate /*= 1.0f*/, cocos2d::CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	setAllCharScale(fromScale);

	ScaleTo *scaleTo = ScaleTo::create(duration, toScale);

	runActionOnAllSprites(scaleTo, delay, true, sequenceDelay, callFuncOnCompletion);
}

void AnimatedLabel::animateSwell(float durationSwell /*= 0.2f*/, float durationReveal /*= 0.2f*/, float beginScale /*= 1.0f*/, float swellScale /*= 1.5f*/, float endScale /*= 1.0f*/, float delay /*= 0.0f*/, float sequenceDelay /*= 0.0f*/, cocos2d::CallFuncN* callFuncOnCompletion /*= nullptr*/)
{
	setAllCharScale(beginScale);

	cocos2d::ScaleTo *scaleUp = cocos2d::ScaleTo::create(durationSwell, swellScale);
	cocos2d::ScaleTo *scaleDown = cocos2d::ScaleTo::create(durationReveal, endScale);
	cocos2d::Sequence *scaleSeq = cocos2d::Sequence::create(scaleUp, scaleDown, NULL);

	runActionOnAllSprites(scaleSeq, delay, true, sequenceDelay, callFuncOnCompletion);
}
