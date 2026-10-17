#include "Animation.h"

bool AnimationComponent::CheckAnimationExists(const std::string& animationName)
{
	if (m_Animations.find(animationName) != m_Animations.end())
		return true;
	return false;
}

AnimationComponent::AnimationComponent()
	:m_CurrentFrame(0), m_LastAnimation(" ")
{
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::PushAnimationRect(const std::string& animationName, const Rect& rect)
{
	m_Animations[animationName].push_back(rect);
}

void AnimationComponent::PlayAnimation(const std::string& animationName)
{
	if (CheckAnimationExists(animationName))
	{
		if (m_LastAnimation != animationName)
		{
			m_LastAnimation = animationName;
			m_CurrentFrame = 0;
		}

		const std::vector<Rect>& animationRects = m_Animations[animationName];
		int32_t maxFrames = animationRects.size();

		if (int(m_CurrentFrame) < maxFrames - 1)
		{
			m_CurrentFrame += m_AnimationSpeed;
			return;
		}
		m_CurrentFrame = 0;

		m_HasFinishedAnAnimation = true; // Only useful for certain suff so the API exposes this variable.
	}
}

void AnimationComponent::SetHasFinishedAnAnimation(bool value)
{
	m_HasFinishedAnAnimation = value;
}

Rect AnimationComponent::GetCurrentAnimationRect(const std::string& animationName)
{
	if (CheckAnimationExists(animationName))
	{
		return m_Animations[animationName][m_CurrentFrame];
	}
	std::cout << "Animation Name: " << animationName << " does not exist." << std::endl;
	return Rect(0, 0, 0, 0);
}
