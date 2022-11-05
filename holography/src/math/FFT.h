#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <exception>
#include <cstdint>
#include <algorithm>
#include <cmath>

namespace math
{
	class Complex
	{
	public:
		Complex() = default;
		Complex(float, float);
		Complex(const Complex&);
		~Complex() = default;

		void SetA(float);
		void SetB(float);

		float GetA() const;
		float GetB() const;

		void operator=(const Complex&);
		void operator*=(int);

		friend Complex operator+(const Complex&, const Complex&);
		friend Complex operator-(const Complex&, const Complex&);
		friend Complex operator*(const Complex&, const Complex&);

	private:
		float m_A;
		float m_B;
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
	Complex Butterfly(const Complex&, const Complex&);

	void fft(const std::vector<Complex>&, std::vector<Complex>&);
}
