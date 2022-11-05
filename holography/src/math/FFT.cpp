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

	Complex Butterfuy(const Complex& rigth, const Complex& left)
	{
		return Complex();
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
			int reverse_i = BitReverseOfCenter(i, 3);
			output[i] = input[reverse_i];
		}

		uint32_t log = static_cast<uint32_t>(std::log2(static_cast<double>(sz)));
		uint32_t num_blocks = sz / 2;
		uint32_t vals = 2;

		for (uint32_t level = 0; level < log; level++)
		{
			for (uint32_t block = 0; block < num_blocks; block++)
			{
				for (uint32_t id_val = 0; id_val < vals; id_val++)
				{

				}
			}

			vals >>= 1; // vals *= 2
			num_blocks <<= 1; // num_blocks / 2
		}

		return output;
	}
}
