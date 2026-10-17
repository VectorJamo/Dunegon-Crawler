#pragma once
#include <iostream>

namespace MapConstants
{
	// Tile
	static constexpr int32_t TileSize = 32;
	
	// World
	static constexpr int32_t WorldTileRows = 20;
	static constexpr int32_t WorldTileCols = 20;
	static constexpr int32_t WorldWidth = TileSize * WorldTileCols;
	static constexpr int32_t WorldHeight = TileSize * WorldTileRows;

	// Screen
	static constexpr int32_t ScreenTileRows = 20;
	static constexpr int32_t ScreenTileCols = 20;
	static constexpr int32_t ScreenWidth = TileSize * ScreenTileRows;
	static constexpr int32_t ScreenHeight = TileSize * ScreenTileCols;
}
