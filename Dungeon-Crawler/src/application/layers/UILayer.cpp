#include "UILayer.h"

#include "application/tilemap/MapConstants.h"

UILayer::UILayer()
{
	m_Assets = new AssetManager();
	m_Assets->LoadFont(m_Assets->GetFromFontDir("8-bit/8-bit-pusab.ttf"));
	m_Assets->LoadTexture(m_Assets->GetFromImageDir("Tileset/tileset.png"));

	m_VersionText = new Text(m_Assets->GetFontByName("8-bit/8-bit-pusab.ttf"), "Beta v1.0", {20.0f, 20.0f});
	m_VersionText->SetCharacterSize(MapConstants::TileSize / 2.0f);

	m_HealthFullSprite = new Sprite(&m_Assets->GetTextureByName("Tileset/tileset.png"), { 48.0f, 48.0f }, { 16+4, 208+4, 8, 8 });
	m_HealthEmptySprite = new Sprite(&m_Assets->GetTextureByName("Tileset/tileset.png"), { 48.0f, 48.0f }, { 0 + 4, 208 + 4, 8, 8 });
}

UILayer::~UILayer()
{
	delete m_Assets;
	delete m_VersionText;
	delete m_HealthFullSprite;
}

void UILayer::Update(float deltaTime)
{
}

void UILayer::Render(Window* window, float playerHealth)
{
	m_VersionText->Render(window);

	sf::Vector2u windowSize = window->GetWindowInstance()->getSize();
	int32_t currentY = 0;
	int32_t currentX = windowSize.x - m_HealthFullSprite->GetSize().x;

	int32_t numHearts = playerHealth / 25; // Four hearts by default

	for (int i = 0; i < numHearts; i++)
	{
		m_HealthFullSprite->SetScreenPosition({ (float)currentX, (float)currentY });
		m_HealthFullSprite->Draw(window);
		
		currentX -= m_HealthFullSprite->GetSize().x;
	}

	int32_t remainingHearts = 4 - numHearts;
	for (int i = 0; i < remainingHearts; i++)
	{
		m_HealthEmptySprite->SetScreenPosition({ (float)currentX, (float)currentY });
		m_HealthEmptySprite->Draw(window);

		currentX -= m_HealthEmptySprite->GetSize().x;
	}
}
