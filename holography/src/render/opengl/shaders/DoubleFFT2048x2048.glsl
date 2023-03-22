#version 460 core

layout(local_size_x = 1024) in;
layout(binding = 0, rgba8) uniform image2D AmplitudeTextureID;
layout(binding = 1, rgba8) uniform image2D PhaseTextureID;

const uint PixelsX= 2048;
const uint Log2Levels = 11;

const float M_PI = 3.14159265358979323846;
const float M_2PI = 2 * M_PI;

const uint MAX_POINTS_COUNT_PER_THREAD = 2;
const uint MAX_SUB_ARRAY_COUNT = 2;
const uint MAX_SUB_ARRAY_SIZE = 2048;

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

vec2 array[2048];

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

void load_from_texture_to_array(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	for(uint i = 0; i < PixelsX; i++)
	{
		uint reverse_i = BitReverse(i, Log2Levels);
		array[i].r = imageLoad(AmplitudeTextureID, ivec2(reverse_i, texPosX)).r;
		array[i].g = imageLoad(PhaseTextureID, ivec2(reverse_i, texPosX)).r * M_2PI;
	}
}

void load_from_texture_to_array1(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	for(uint i = 0; i < PixelsX; i++)
	{
		array[i].r = imageLoad(AmplitudeTextureID, ivec2(i, texPosX)).r;
		array[i].g = imageLoad(PhaseTextureID, ivec2(i, texPosX)).r;
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
	float k = 1 / max;

	for(uint i = 0; i < PixelsX; i++)
	{
		val_ampl = array[i].r * k;
		val_phi = array[i].g;

		pixelVal = vec4(val_ampl, val_phi, k, 0.0);

		imageStore(AmplitudeTextureID, ivec2(i, texPosX), pixelVal);
	}
}

void load_from_array_to_texture1(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	vec4 pixelVal;

	float val_ampl = 0;
	float val_phi = 0;

	for(uint i = 0; i < PixelsX; i++)
	{
		val_ampl = array[i].r;
		val_phi = array[i].g;

		pixelVal = vec4(val_ampl, val_ampl, val_ampl, 0.0);

		imageStore(AmplitudeTextureID, ivec2(i, texPosX), pixelVal);

		pixelVal = vec4(val_phi, val_phi, val_phi, 0.0);

		imageStore(PhaseTextureID, ivec2(i, texPosX), pixelVal);
	}
}

void load_from_texture_to_array_2(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	for(uint i = 0; i < PixelsX; i++)
	{
		uint reverse_i = BitReverse(i, Log2Levels);
		vec3 val = imageLoad(AmplitudeTextureID, ivec2(texPosX, reverse_i)).rgb;
		float k = val.b;

		array[i].r = (val.r) * cos(val.g * M_2PI);
		array[i].g = (val.r) * sin(val.g * M_2PI);
	}
}

void load_from_texture_to_array_3(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	for(uint i = 0; i < PixelsX; i++)
	{
		array[i].r = imageLoad(AmplitudeTextureID, ivec2(texPosX, i)).r;
		array[i].g = imageLoad(PhaseTextureID, ivec2(texPosX, i)).r;
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
		val_ampl = array[i].r;
		val_phi = array[i].g;

		pixelVal = vec4(val_ampl, val_ampl, val_ampl, 0.0);

		imageStore(AmplitudeTextureID, ivec2(texPosX, i), pixelVal);

		pixelVal = vec4(val_phi, val_phi, val_phi, 0.0);

		imageStore(PhaseTextureID, ivec2(texPosX, i), pixelVal);
	}
}

void load_from_array_to_texture_3(uint index)
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD) + index;

	vec4 pixelVal;

	float val_ampl = 0;
	float val_phi = 0;

	for(uint i = 0; i < PixelsX; i++)
	{
		val_ampl = array[i].r;
		val_phi = array[i].g;

		pixelVal = vec4(val_ampl, val_ampl, val_ampl, 0.0);

		imageStore(AmplitudeTextureID, ivec2(texPosX, i), pixelVal);

		pixelVal = vec4(val_phi, val_phi, val_phi, 0.0);

		imageStore(PhaseTextureID, ivec2(texPosX, i), pixelVal);
	}
}

void sort()
{
	for(int i = 0; i < 1024; i++)
	{
		vec2 temp = array[i];
		array[i] = array[i+ 1024];
		array[i+1024] = temp;
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
	
	for(uint id = 0; id < MAX_POINTS_COUNT_PER_THREAD; id++)
	{
		load_from_texture_to_array_2(id);
	
		fft_array();
	
		load_from_array_to_texture_2(id);
	}
	
	barrier();

	for(uint id = 0; id < MAX_POINTS_COUNT_PER_THREAD; id++)
	{
		load_from_texture_to_array1(id);

		sort();

		load_from_array_to_texture1(id);
	}

	barrier();

	for(uint id = 0; id < MAX_POINTS_COUNT_PER_THREAD; id++)
	{
		load_from_texture_to_array_3(id);
	
		sort();
	
		load_from_array_to_texture_3(id);
	}

	barrier();
}
