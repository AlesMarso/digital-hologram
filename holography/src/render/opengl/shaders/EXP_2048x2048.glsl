#version 460 core

layout(local_size_x = 1024) in;
layout(binding = 0, rgba8) uniform image2D AmplitudeTextureID;
layout(binding = 1, rgba8) uniform image2D PhaseTextureID;

uniform int Dimension;
uniform int SizeX;
uniform int SizeY;
uniform float lambda = 0.5;

const int PixelsCount = 2048;
const uint MAX_POINTS_COUNT_PER_THREAD = 2;
const uint MAX_SUB_ARRAY_COUNT = 2;
const uint MAX_SUB_ARRAY_SIZE = 2048;

const float M_PI = 3.14159265358979323846;
const float M_2PI = 2 * M_PI;

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

vec2 to_complex(float ampl, float phase)
{
	vec2 complex_num;

	complex_num.r = ampl * cos(phase);
	complex_num.g = ampl * sin(phase);

	return complex_num;
}

vec2 exp_transform(float ampl, float phase, uint k, uint l)
{
	vec2 res = to_complex(ampl, phase);

	float a = float(float(k) - float(SizeX / 2));
	float b = float(float(l) - float(SizeY / 2));
	float par1 = M_PI / (lambda * Dimension);
	float exp_phase = par1 * (a * a + b * b);

	vec2 exp_val = to_complex(1, exp_phase);

	return ComplexMul(res, exp_val);
}

void main()
{
	uint texPosX = (gl_GlobalInvocationID.x * MAX_POINTS_COUNT_PER_THREAD);

	for(int i = 0; i < MAX_POINTS_COUNT_PER_THREAD; i++)
	{
		texPosX += i;

		for(uint j = 0; j < MAX_SUB_ARRAY_SIZE; j++)
		{
			ivec2 id = ivec2(texPosX, j);
			float pixelAmplVal = imageLoad(AmplitudeTextureID, id).r;
			float pixelPhaseVal = imageLoad(PhaseTextureID, id).r;

			vec2 res = exp_transform(pixelAmplVal, pixelPhaseVal, texPosX, j);
		}
	}
}
