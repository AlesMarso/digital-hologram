#version 460 core

layout(local_size_x = 704) in;
layout(binding = 0, rgba8) uniform image2D out_tex;

uniform uint PixelsX;

const float M_PI = 3.14159265358979323846;
const float M_2PI = 2 * M_PI;
const uint MAX_POINTS_COUNT_PER_THREAD = 4;
const uint MAX_SUB_ARRAY_COUNT = 11;
const uint MAX_SUB_ARRAY_SIZE = 256;

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

vec2 array[2816];
vec2 temp_array[2816];

void load_from_texture_to_array(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	for(uint i = 0; i < PixelsX; i++)
	{
		array[i] = imageLoad(out_tex, ivec2(i, texPosX)).rg;
	}
}

void load_from_array_to_texture(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

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

void load_from_texture_to_array_2(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	for(uint i = 0; i < PixelsX; i++)
	{
		array[i] = imageLoad(out_tex, ivec2(texPosX, i)).rg;
	}
}

void load_from_array_to_texture_2(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

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

vec2 input_temp[256];
vec2 output_temp[256];

void fft_256(uint id)
{
	for(uint i = 0; i < MAX_SUB_ARRAY_SIZE; i++)
	{
		input_temp[i] = array[id + i * MAX_SUB_ARRAY_COUNT];
	}

	uint Num2LogLevels = 8;
	uint numBlocks = 128;
	uint numButterflyOperations = 1;
	uint offset = 2;
	uint offsetId = 1;

	for(uint i = 0; i < MAX_SUB_ARRAY_SIZE; i++)
	{
		uint reverse_i = BitReverse(i, Num2LogLevels);
		output_temp[i] = input_temp[reverse_i];
	}

	for (uint logLevel = 0, _2_k = 2; logLevel < Num2LogLevels; logLevel++, _2_k *= 2)
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

				vec2 right = output_temp[rightId];
				vec2 left = ComplexMul(output_temp[leftId], W);

				output_temp[rightId] = ComplexSum(right, left);
				output_temp[leftId] = ComplexDiff(right, left);
			}
		}

		numBlocks /= 2; // numBlocks = numBlocks / 2
		numButterflyOperations *= 2; // numButterflyOperations = numButterflyOperations * 2

		offset *= 2; // offset = offset * 2
		offsetId *= 2; // offsetId = offsetId * 2
	}

	for(uint i = 0; i < MAX_SUB_ARRAY_SIZE; i++)
	{
		temp_array[id + i * MAX_SUB_ARRAY_COUNT] = output_temp[i];
	}
}

void fft_array()
{
	for(int i = 0; i < MAX_SUB_ARRAY_COUNT; i++)
	{
		fft_256(i);
	}

	for(int i = 0; i < MAX_SUB_ARRAY_SIZE; i++)
	{
		for(int j = 0; j < MAX_SUB_ARRAY_COUNT; j++)
		{
			uint outId = i + j * MAX_SUB_ARRAY_SIZE;

			vec2 res;

			res.r = 0;
			res.g = 0;

			for(int k = 0; k < MAX_SUB_ARRAY_COUNT; k++)
			{
				float a = k * outId;
				float b = PixelsX;

				float y = a / b;
				float phi = M_2PI * y;

				vec2 W;

				W.r = cos(phi);
				W.g = sin(phi);

				vec2 temp = ComplexMul(temp_array[k + i * MAX_SUB_ARRAY_COUNT], W);
				res = ComplexSum(res, temp);
			}

			array[outId] = res;
		}
	}
}

void main()
{
	for(uint id = 0; id < MAX_POINTS_COUNT_PER_THREAD; id++)
	{
		load_from_texture_to_array(id);

		fft_array();

		load_from_array_to_texture(id);
	}

	barrier();

	//for(uint id = 0; id < MAX_POINTS_COUNT_PER_THREAD; id++)
	//{
	//	load_from_texture_to_array_2(id);
	//
	//	fft_array();
	//
	//	load_from_array_to_texture_2(id);
	//}
	//
	//barrier();
}
