#pragma once

#include <vector>
#include <exception>

namespace math
{
	struct Complex
	{
		float m_A;
		float m_B;
	};

	unsigned int BitReverseOfCenter(unsigned int, unsigned int);

	std::vector<Complex> fft(const std::vector<Complex>&);
}
