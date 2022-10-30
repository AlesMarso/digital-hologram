#include "FFT.h"

namespace math
{
	uint32_t BitReverseOfCenter(uint32_t index, uint32_t logm = 16)
	{
		uint32_t j = index;

		j = (j & 0x00005555) << 1 | (j & 0x0000AAAA) >> 1;
		j = (j & 0x00003333) << 2 | (j & 0x0000CCCC) >> 2;
		j = (j & 0x00000F0F) << 4 | (j & 0x0000F0F0) >> 4;
		j = (j & 0x000000FF) << 8 | (j & 0x0000FF00) >> 8;

		return j >> (16 - logm);
	}

	std::vector<Complex> fft(const std::vector<Complex>& input)
	{
		if (!input.size())
			throw std::exception("Input array is empty!!!");

		std::vector<Complex> output;
		output.resize(input.size());

		uint32_t sz = output.size();

		for (int i = 0; i < sz; i++)
		{
			int reverse_i = BitReverseOfCenter(i, 4);
			output[i] = input[reverse_i];
		}



		return output;
	}
}
