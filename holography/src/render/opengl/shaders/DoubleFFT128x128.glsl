#version 460 core

layout(local_size_x = 128) in;
layout(binding = 0, rgba8) uniform image2D out_tex;

uniform uint PixelsX;
uniform uint Log2Levels;

const float M_PI = 3.14159265358979323846;
const float M_2PI = 2 * M_PI;

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

float calc_ampl(float a, float b)
{
	float a_2 = a * a;
	float b_2 = b * b;

	return sqrt(a_2 + b_2);
}

float calc_phi(float a, float b)
{
	float atan_val = (atan(a,b) + M_PI) / M_2PI;
	return atan_val;
}

vec2 array[128];

void fft_array()
{
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
}

void load_from_texture_to_array()
{
	uint texPosX = gl_GlobalInvocationID.x;

	for(uint i = 0; i < PixelsX; i++)
	{
		uint reverse_i = BitReverse(i, Log2Levels);
		array[i] = imageLoad(out_tex, ivec2(reverse_i, texPosX)).rg;
	}
}

void load_from_array_to_texture()
{
	uint texPosX = gl_GlobalInvocationID.x;

	float ampl = 0;
	float phi = 0;
	vec4 pixelVal;
	float max = -100000000;

	for(uint i = 0; i < PixelsX; i++)
	{
		float a = array[i].r;
		float b = array[i].g;

		ampl = calc_ampl(a, b);
		if(ampl > max) max = ampl;
		phi = calc_phi(a, b);

		array[i].r = ampl;
		array[i].g = phi;
	}

	float val_ampl = 0;
	float val_phi = 0;

	for(uint i = 0; i < PixelsX; i++)
	{
		val_ampl = array[i].r / max;
		val_phi = array[i].g;

		pixelVal = vec4(val_ampl, val_ampl, val_ampl, 0.0);

		imageStore(out_tex, ivec2(i, texPosX), pixelVal);
	}
}

void load_from_texture_to_array_2()
{
	uint texPosX = gl_GlobalInvocationID.x;

	for(uint i = 0; i < PixelsX; i++)
	{
		uint reverse_i = BitReverse(i, Log2Levels);
		array[i] = imageLoad(out_tex, ivec2(texPosX, reverse_i)).rg;
	}
}

void load_from_array_to_texture_2()
{
	uint texPosX = gl_GlobalInvocationID.x;

	float ampl = 0;
	float phi = 0;
	vec4 pixelVal;
	float max = -100000000;

	for(uint i = 0; i < PixelsX; i++)
	{
		float a = array[i].r;
		float b = array[i].g;

		ampl = calc_ampl(a, b);
		if(ampl > max) max = ampl;
		phi = calc_phi(a, b);

		array[i].r = ampl;
		array[i].g = phi;
	}

	float val_ampl = 0;
	float val_phi = 0;

	for(uint i = 0; i < PixelsX; i++)
	{
		val_ampl = array[i].r / max;
		val_phi = array[i].g;

		pixelVal = vec4(val_ampl, val_ampl, val_ampl, 0.0);

		imageStore(out_tex, ivec2(texPosX, i), pixelVal);
	}
}

void main()
{
	load_from_texture_to_array();

	fft_array();

	load_from_array_to_texture();

	barrier();

	load_from_texture_to_array_2();
	
	fft_array();
	
	load_from_array_to_texture_2();
	
	barrier();
}
