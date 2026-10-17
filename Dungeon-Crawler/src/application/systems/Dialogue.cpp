#include "Dialogue.h"

Dialogue::Dialogue(const std::string& dialogue, AssetManager* assetManager)
	:m_Dialogue(dialogue)
{
	m_DialogueBox.setOutlineThickness(2);
	m_DialogueBox.setOutlineColor({ 255, 255, 255, 255 });
	m_DialogueBox.setFillColor(DialogueBoxColor);

	m_DialogueBox.setPosition(DialogueBoxOffset);
	m_DialogueBox.setSize({ (float)DialogueBoxWidth, (float)DialogueBoxHeight });

	m_Text = new Text(assetManager->GetFontByName("8-bit/8-bit-pusab.ttf"));
	m_Text->SetString(std::string(1, m_Dialogue[0]));
	m_Text->SetPosition({ m_DialogueBox.getPosition().x + DialogueCharacterSize, m_DialogueBox.getPosition().y + DialogueCharacterSize });

	m_CurrentChar = 0; 
	m_Timer = 0.0f;
	m_HasFinishedDialogue = false;
}

Dialogue::~Dialogue()
{
	delete m_Text;
}

void Dialogue::Update(float deltaTime)
{
	m_Timer += deltaTime;
	if (m_Timer > DialogueSpeed)
	{
		m_Timer = 0.0f;
		if (m_CurrentChar + 1 <= m_Dialogue.length())
		{
			m_CurrentChar++;
			m_Text->SetString(m_Dialogue.substr(0, m_CurrentChar));
		}
		else {
			m_HasFinishedDialogue = true;
		}
	}
}

void Dialogue::Render(Window* window)
{
	window->GetWindowInstance()->draw(m_DialogueBox);
	m_Text->Render(window);

	if (m_HasFinishedDialogue)
	{
		
	}
}
