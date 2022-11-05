#include "FFT.h"

namespace math
{
	// right = a + ib, left = c + id
	// right + left = (a + ib) + (c + id) = 
	// = (a + c) + i(b + d)
	Complex operator+(const Complex& right, const Complex& left)
	{
		float a = right.m_A + left.m_A;
		float b = right.m_B + left.m_B;

		return Complex(a, b);
	}

	// right = a + ib, left = c + id
	// right - left = (a + ib) - (c + id) = 
	// = (a - c) + i(b - d)
	Complex operator-(const Complex& right, const Complex& left)
	{
		float a = right.m_A - left.m_A;
		float b = right.m_B - left.m_B;

		return Complex(a, b);
	}

	// right = a + ib, left = c + id
	// right * left = (a + ib) * (c + id) = a*c + i(a*d) + i(b*c) + i^2(b*d) = 
	// = (ac - bd) + i (ad+bc)
	Complex operator*(const Complex& right, const Complex& left)
	{
		float a = (right.m_A * left.m_A) - (right.m_B * left.m_B);
		float b = (right.m_A * left.m_B) + (right.m_B * left.m_A);

		return Complex(a, b);
	}

	Complex::Complex(float a, float b)
	{
		m_A = a;
		m_B = b;
	}

	Complex::Complex(const Complex& left)
	{
		this->m_A = left.m_A;
		this->m_B = left.m_B;
	}

	void Complex::SetA(float a)
	{
		m_A = a;
	}

	void Complex::SetB(float b)
	{
		m_B = b;
	}

	float Complex::GetA() const
	{
		return m_A;
	}

	float Complex::GetB() const
	{
		return m_B;
	}

	void Complex::operator*=(int val)
	{
		this->m_A *= val;
		this->m_B *= val;
	}

	void Complex::operator=(const Complex& left)
	{
		this->m_A = left.m_A;
		this->m_B = left.m_B;
	}

	uint32_t BitReverseOfCenter(uint32_t index, uint32_t logm = 16)
	{
		uint32_t j = index;

		j = (j & 0x00005555) << 1 | (j & 0x0000AAAA) >> 1;
		j = (j & 0x00003333) << 2 | (j & 0x0000CCCC) >> 2;
		j = (j & 0x00000F0F) << 4 | (j & 0x0000F0F0) >> 4;
		j = (j & 0x000000FF) << 8 | (j & 0x0000FF00) >> 8;

		return j >> (16 - logm);
	}

	void fft(const std::vector<Complex>& input, std::vector<Complex>& output)
	{
		if (!input.size())
			throw std::exception("Input array is empty!!!");

		output.resize(input.size());

		uint32_t sz = output.size();
		uint32_t numLog2Levels = static_cast<uint32_t>(std::log2(static_cast<double>(sz)));

		for (int i = 0; i < sz; i++)
		{
			int reverse_i = BitReverseOfCenter(i, numLog2Levels);
			output[i] = input[reverse_i];
		}

		uint32_t numBlocks = sz / 2;
		uint32_t numButterflyOperations = 1;
		uint32_t offset = 2;
		uint32_t offsetId = 1;
		constexpr auto M_2PI = 2 * M_PI;

		for (uint32_t logLevel = 0, _2_k = 2; logLevel < numLog2Levels; logLevel++, _2_k *= 2)
		{
			for (uint32_t block = 0, idFirstElemInBlock = 0; block < numBlocks; block++, idFirstElemInBlock += offset)
			{
				for (uint32_t operation = 0; operation < numButterflyOperations; operation++)
				{
					double y = static_cast<double>(operation) / static_cast<double>(_2_k);
					double phi = M_2PI * y;

					Complex W;
					W.SetA(std::cosf(phi));
					W.SetB(std::sinf(phi));

					uint32_t rightId = idFirstElemInBlock + operation;
					uint32_t leftId = rightId + offsetId;

					auto right = output[rightId];
					auto left = output[leftId] * W;

					output[rightId] = right + left;
					output[leftId] = right - left;
				}
			}

			numBlocks /= 2; // numBlocks = numBlocks / 2
			numButterflyOperations *= 2; // numButterflyOperations = numButterflyOperations * 2

			offset *= 2; // offset = offset * 2
			offsetId *= 2; // offsetId = offsetId * 2
		}
	}
}
