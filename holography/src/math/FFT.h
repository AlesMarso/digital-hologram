#pragma once

#include <vector>
#include <exception>
#include <cstdint>
#include <algorithm>
#include <cmath>

namespace math
{
	struct Complex
	{
		float m_A;
		float m_B;

		void operator=(const Complex& left)
		{
			this->m_A = left.m_A;
			this->m_B = left.m_B;
		}
	};

	constexpr uint32_t MASK_AAAA = 0x0000AAAA;
	constexpr uint32_t MASK_5555 = 0x00005555;
	constexpr uint32_t MASK_CCCC = 0x0000CCCC;
	constexpr uint32_t MASK_3333 = 0x00003333;
	constexpr uint32_t MASK_F0F0 = 0x0000F0F0;
	constexpr uint32_t MASK_0F0F = 0x00000F0F;
	constexpr uint32_t MASK_FF00 = 0x0000FF00;
	constexpr uint32_t MASK_00FF = 0x000000FF;
	constexpr uint32_t MASK_FFFF = 0xFFFF0000;
	constexpr uint32_t MASK_0000 = 0x0000FFFF;

	uint32_t BitReverseOfCenter(uint32_t, uint32_t);

	Complex Butterfuy(const Complex&, const Complex&);

	std::vector<Complex> fft(const std::vector<Complex>&);
}
