#pragma once
#include <iostream>
#include <queue>

#include "Dialogue.h"
#include "framework/ui/Button.h"

class DialogueSystem
{
private:
	std::queue<Dialogue*> m_Dialogues;
	Dialogue* m_CurrentPlayingDialogue;

	Button* m_NextDialogueButton;

public:
	DialogueSystem(AssetManager* assets);
	~DialogueSystem();

	void PushDialogueIntoQueue(Dialogue* dialogue);
	void PlayCurrentDialogueQueue();

	void Update(float deltaTime);
	void Render(Window* window);

	bool IsCurrentlyPlaying();
};

