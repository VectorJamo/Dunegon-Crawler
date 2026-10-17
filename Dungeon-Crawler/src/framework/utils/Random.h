#pragma once
#include <random>

class Random
{
private:
	static std::mt19937 m_Generator;

public:
	static int32_t GetInt(int32_t min, int32_t max);
};

