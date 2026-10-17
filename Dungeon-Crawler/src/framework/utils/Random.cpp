#include "Random.h"

std::mt19937 Random::m_Generator{std::random_device{}()};

int32_t Random::GetInt(int32_t min, int32_t max)
{
	std::uniform_int_distribution<int32_t> dist(min, max);

	return dist(m_Generator);
}
