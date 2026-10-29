#pragma once
#include "../utils/Rect.h"
#include <unordered_map>
#include <vector>

class AnimationComponent
{
private:
	std::unordered_map<std::string, std::vector<Rect>> m_Animations;
	std::string m_LastAnimation;

	float m_CurrentFrame;
	float m_AnimationSpeed = 0.05f;

	bool m_HasFinishedAnAnimation = false;

private:
	bool CheckAnimationExists(const std::string& animationName);

public:
	AnimationComponent();
	~AnimationComponent();

	void PushAnimationRect(const std::string& animationName, const Rect& rect);
	void PlayAnimation(const std::string& animationName);

	void SetHasFinishedAnAnimation(bool value);

	Rect GetCurrentAnimationRect(const std::string& animationName);
	inline const bool& HasFinishedLastAnimation() { return m_HasFinishedAnAnimation; }
};

