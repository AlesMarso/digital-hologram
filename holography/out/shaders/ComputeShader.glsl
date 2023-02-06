#version 460 core

layout(local_size_x = 256, local_size_y = 1, local_size_z = 1) in;
layout(binding = 0, rgba8) uniform image2D out_tex;

uniform uint PixelsX;
uniform uint Log2Levels;

const float PI = 3.14159265358979323846;
const float M_2PI = 2 * PI;

// right = a + bi, left = c + di
// right + left = (a + bi) + (c + di) = 
// = (a + c) + i(b + d)
vec2 ComplexSum(vec2 right, vec2 left)
{
	vec2 result;

	result.x = right.x + left.x;
	result.y = right.y + left.y;

	return result;
}

// right = a + bi, left = c + di
// right * left = (a + bi) * (c + di) = 
// = (a * c) + i(a * d) + i(b * c) - (b * d) = 
// = (ac - bd) + i(ad + bc) 
vec2 ComplexMul(vec2 right, vec2 left)
{
	vec2 result;

	result.x = right.x * left.x - right.y * left.y;
	result.y = right.x * left.y + right.y * left.x;

	return result;
}

// right = a + bi, left = c + di
// right - left = (a + bi) - (c + di) =
// = a + bi - c - di = (a - c) + (b - d)i
vec2 ComplexDiff(vec2 right, vec2 left)
{
	vec2 result;

	result.x = right.x - left.x;
	result.y = right.y - left.y;

	return result;
}

uint BitReverse(uint index, uint logm)
{
	uint result = index;

	result = (result & 0x00005555) << 1 | (result & 0x0000AAAA) >> 1;
	result = (result & 0x00003333) << 2 | (result & 0x0000CCCC) >> 2;
	result = (result & 0x00000F0F) << 4 | (result & 0x0000F0F0) >> 4;
	result = (result & 0x000000FF) << 8 | (result & 0x0000FF00) >> 8;

	return result >> (16 - logm);
}

void fft_even_numbers()
{
	
}

void main()
{
	uint texPosY = gl_GlobalInvocationID.y;
	uint texPosX = gl_GlobalInvocationID.x;

	vec2 array[10000];

	for(uint i = 0; i < PixelsX; i++)
	{
		uint reverse_i = BitReverse(i, Log2Levels);
		array[i] = imageLoad(out_tex, ivec2(reverse_i, texPosX)).rg;
	}

	uint numBlocks = PixelsX / 2;
	uint numButterflyOperations = 1;
	uint offset = 2;
	uint offsetId = 1;

	for (uint logLevel = 0, _2_k = 2; logLevel < Log2Levels; logLevel++, _2_k *= 2)
	{
		for (uint block = 0, idFirstElemInBlock = 0; block < numBlocks; block++, idFirstElemInBlock += offset)
		{
			for (uint operation = 0; operation < numButterflyOperations; operation++)
			{
				float a = operation;
				float b = _2_k;

				float y = a / b;
				float phi = M_2PI * y;

				vec2 W = vec2(cos(phi), sin(phi));

				uint rightId = idFirstElemInBlock + operation;
				uint leftId = rightId + offsetId;

				vec2 right = array[rightId];
				vec2 left = ComplexMul(array[leftId], W);

				array[rightId] = ComplexSum(right, left);
				array[leftId] = ComplexDiff(right, left);
			}
		}

		numBlocks /= 2; // numBlocks = numBlocks / 2
		numButterflyOperations *= 2; // numButterflyOperations = numButterflyOperations * 2

		offset *= 2; // offset = offset * 2
		offsetId *= 2; // offsetId = offsetId * 2
	}

	float ampl = 0;
	float val = 0;
	vec4 pixelVal;
	float max = -100000000;

	for(uint i = 0; i < PixelsX; i++)
	{
		ampl = sqrt((array[i].r * array[i].r) + (array[i].g * array[i].g));
		array[i].r = ampl;
		if(ampl > max) max = ampl;
	}

	for(uint i = 0; i < PixelsX; i++)
	{
		val = array[i].r / max;
		pixelVal = vec4(val, val, val, 0.0);

		imageStore(out_tex, ivec2(i, texPosX), pixelVal);
	}
}