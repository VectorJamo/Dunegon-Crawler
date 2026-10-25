#include "DialogueSystem.h"

DialogueSystem::DialogueSystem(AssetManager* assets)
{
    m_CurrentPlayingDialogue = nullptr;
    m_NextDialogueButton = new Button("next..", assets->GetFontByName("8-bit/8-bit-pusab.ttf"));
    m_NextDialogueButton->SetCharacterSize(Dialogue::DialogueCharacterSize);
    m_NextDialogueButton->SetPadding(10, 10);
    sf::Vector2f buttonSize = { (float)m_NextDialogueButton->GetWidth(), (float)m_NextDialogueButton->GetHeight() };
    m_NextDialogueButton->SetPosition({ Dialogue::DialogueBoxOffset.x + Dialogue::DialogueBoxWidth - buttonSize.x - 10, 
        Dialogue::DialogueBoxOffset.y + Dialogue::DialogueBoxHeight - buttonSize.y - 10});
}

DialogueSystem::~DialogueSystem()
{
}

void DialogueSystem::PushDialogueIntoQueue(Dialogue* dialogue)
{
    m_Dialogues.push(dialogue);
}

void DialogueSystem::PlayCurrentDialogueQueue()
{
    if (m_Dialogues.size() != 0)
    {
        m_CurrentPlayingDialogue = m_Dialogues.front();
        m_Dialogues.pop();
    }
}

void DialogueSystem::Update(float deltaTime)
{
    if (m_CurrentPlayingDialogue != nullptr)
    {
        m_CurrentPlayingDialogue->Update(deltaTime);
        if (m_CurrentPlayingDialogue->HasFinishedDialogue())
        {
            m_NextDialogueButton->Update(deltaTime);

            if (m_NextDialogueButton->IsClicked())
            {
                delete m_CurrentPlayingDialogue;
                m_CurrentPlayingDialogue = nullptr;

                if (m_Dialogues.size() != 0)
                {
                    m_CurrentPlayingDialogue = m_Dialogues.front();
                    m_Dialogues.pop();
                }
            }
        }
    }
}

void DialogueSystem::Render(Window* window)
{
    if (m_CurrentPlayingDialogue != nullptr)
    {
        m_CurrentPlayingDialogue->Render(window);

        if (m_CurrentPlayingDialogue->HasFinishedDialogue())
        {
            m_NextDialogueButton->Render(window);
        }
    }
}

bool DialogueSystem::IsCurrentlyPlaying()
{
    return m_CurrentPlayingDialogue != nullptr;
}
