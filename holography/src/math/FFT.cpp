#include "FFT.h"

namespace math
{
	unsigned int BitReverseOfCenter(unsigned int index, unsigned int logm)
	{
		unsigned int reveseOfCenterIndex = 0;



		return reveseOfCenterIndex;
	}

	std::vector<Complex> fft(const std::vector<Complex>& input)
	{
		if (!input.size())
			throw std::exception("Input array is empty!!!");

		std::vector<Complex> output;
		output.resize(input.size());

		for (auto i : input)
		{

		}

		return output;
	}
}
