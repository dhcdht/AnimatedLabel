/*!
 * \file AnimatedLabel.h
 *
 * \author dhcdht
 * \date 五月 2014
 *
 * 
 */
#ifndef AnimatedLabel_h
#define AnimatedLabel_h

#include "cocos2d.h"

typedef enum
{
	LabelAnimationLinear = 0,
	LabelAnimationEaseIn,
	LabelAnimationEaseOut,
}LabelAnimationType;

class AnimatedLabel : public cocos2d::Label
{
protected:
	AnimatedLabel(
		cocos2d::FontAtlas* atlas = nullptr,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP,
		bool useDistanceField = false,
		bool useA8Shader = false);

public:
#pragma mark - Override Create Methods	//重写Label的create方法，返回AnimatedLabel实例
	static AnimatedLabel* create();

	static AnimatedLabel* createWithSystemFont(
		const std::string& text, 
		const std::string& font, 
		float fontSize,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);

	static AnimatedLabel* createWithTTF(
		const std::string& text,
		const std::string& fontFile,
		float fontSize,
		const cocos2d::Size& dimensions = cocos2d::Size::ZERO,
		cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
		cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP);

	static AnimatedLabel* createWithTTF(
		const cocos2d::TTFConfig& ttfConfig, 
		const std::string& text, 
		cocos2d::TextHAlignment alignment = cocos2d::TextHAlignment::LEFT, 
		int maxLineWidth = 0);

	static AnimatedLabel* createWithBMFont(
		const std::string& bmfontFilePath, 
		const std::string& text,
		const cocos2d::TextHAlignment& alignment = cocos2d::TextHAlignment::LEFT, 
		int maxLineWidth = 0,
		const cocos2d::Point& imageOffset = cocos2d::Point::ZERO);

	static AnimatedLabel* createWithCharMap(
		const std::string& charMapFile, 
		int itemWidth, 
		int itemHeight, 
		int startCharMap);

	static AnimatedLabel * createWithCharMap(
		cocos2d::Texture2D* texture, 
		int itemWidth, 
		int itemHeight, 
		int startCharMap);

	static AnimatedLabel* createWithCharMap(const std::string& plistFile);

#pragma mark - Basic Functions For Character Sprite	//针对字符精灵的基本操作
	int getCharSpriteCount();
	cocos2d::Sprite* getCharSprite(int index);

	cocos2d::Point getCharOffset(int index);
	void setCharOffset(int index, cocos2d::Point offset);
	void setAllCharOffset(cocos2d::Point offset);

	void setCharColor(int index, cocos2d::Color3B color);
	cocos2d::Color3B getCharColor(int index);
	void setAllCharColor(cocos2d::Color3B color);

	float getCharScale(int index);
	void setCharScale(int index, float scale);
	void setAllCharScale(float scale);

	float getCharOpacity(int index);
	void setCharOpacity(int index, float opacity);
	void setAllCharOpacity(float opacity);

	float getCharRotation(int index);
	void setCharRotation(int index, float rotation);
	void setAllCharRotation(float rotation);

#pragma mark - Run Custom Actions	//自定义动作
	virtual bool checkCanAnimate();

	//对字符精灵执行动作的方法
	void runActionOnSpriteAtIndex(int index, cocos2d::Action* action);
	void runActionOnAllSprites(cocos2d::Action* action);
	
	//对字符精灵执行有限时间动作的方法
	void runActionOnSpriteAtIndex(
		int index, 
		cocos2d::FiniteTimeAction* action,
		float delay = 0.0f,
		cocos2d::CallFuncN* callFuncOnCompletion = nullptr);
	void runActionOnAllSprites(
		cocos2d::FiniteTimeAction* action,
		float delay = 0.0f,
		bool isSequentially = true,
		float sequenceDelay = 0.0f,
		cocos2d::CallFuncN* callFuncOnCompletion = nullptr);

#pragma mark - Common Animation	//常用动画
	cocos2d::ActionInterval* createEaseAction(
		cocos2d::ActionInterval* action,
		LabelAnimationType animationType = LabelAnimationLinear,
		float animationRate = 1.0f);

	void animateMoveBy(
		float duration,
		cocos2d::Point moveByDistance,
		float delay = 0.0f,
		bool isSequentially = true,
		float sequenceDelay = 0.0f,
		LabelAnimationType animationType = LabelAnimationLinear,
		float animationRate = 1.0f,
		cocos2d::CallFuncN* callFuncOnCompletion = nullptr);
	void animateMoveTo(
		float duration,
		cocos2d::Point moveToPosition,
		float delay = 0.0f,
		bool isSequentially = true,
		float sequenceDelay = 0.0f,
		LabelAnimationType animationType = LabelAnimationLinear,
		float animationRate = 1.0f,
		cocos2d::CallFuncN* callFuncOnCompletion = nullptr);

	void animateTypewriter(
		float duration = 0.05f,
		float fromScale = 0.0f,
		float toScale = 1.0f,
		float delay = 0.0f,
		float sequenceDelay = 0.0f,
		LabelAnimationType animationType = LabelAnimationLinear,
		float animationRate = 1.0f,
		cocos2d::CallFuncN* callFuncOnCompletion = nullptr);

	void animateSwell(
		float durationSwell = 0.2f,
		float durationReveal = 0.2f,
		float beginScale = 1.0f,
		float swellScale = 1.5f,
		float endScale = 1.0f,
		float delay = 0.0f,
		float sequenceDelay = 0.0f,
		cocos2d::CallFuncN* callFuncOnCompletion = nullptr);
    
    void animateRainbow(
        float duration = 0.2f,
        cocos2d::CallFuncN* callFuncOnCompletion = nullptr);
};

#endif // AnimatedLabel_h
