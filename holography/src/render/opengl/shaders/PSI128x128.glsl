#version 460 core

layout(local_size_x = 128) in;
layout(binding = 0, rgba8) uniform image2D PSIFirstTexture;
layout(binding = 1, rgba8) uniform image2D PSISecondTexture;
layout(binding = 2, rgba8) uniform image2D PSIThirdTexture;
layout(binding = 3, rgba8) uniform image2D PSIFourthTexture;
layout(binding = 4, rgba8) uniform image2D AmplitudeTexture;
layout(binding = 5, rgba8) uniform image2D PhaseTexture;

const float M_PI = 3.14159265358979323846;
const float M_2PI = 2 * M_PI;
float K = 0.25;

uniform float PhaseValOne = 0;
uniform float PhaseValTwo = M_PI / 2;
uniform float PhaseValThree = M_PI;
uniform float PhaseValFour = 3 * (M_PI / 2);

float calc_ampl(float i1, float i2, float i3, float i4)
{
	float IS = (i2 - i4) * sin(PhaseValOne) + 
		(i3 - i1) * sin(PhaseValTwo) + 
		(i4 - i2) * sin(PhaseValThree) + 
		(i1 - i3) * sin(PhaseValFour);

	float IC = (i2 - i4) * cos(PhaseValOne) + 
		(i3 - i1) * cos(PhaseValTwo) + 
		(i4 - i2) * cos(PhaseValThree) + 
		(i1 - i3) * cos(PhaseValFour);

	float CS = (cos(PhaseValTwo) - cos(PhaseValFour)) * sin(PhaseValOne) + 
		(cos(PhaseValThree) - cos(PhaseValOne)) * sin(PhaseValTwo) + 
		(cos(PhaseValFour) - cos(PhaseValTwo)) * sin(PhaseValThree) + 
		(cos(PhaseValOne) - cos(PhaseValThree)) * sin(PhaseValFour);

	return (1 / abs(CS)) * (sqrt(IS * IS + IC * IC)) * K;
}

float calc_phi(float i1, float i2, float i3, float i4)
{
	float numenator = (i2 - i4) * sin(PhaseValOne) + 
		(i3 - i1) * sin(PhaseValTwo) + 
		(i4 - i2) * sin(PhaseValThree) * 
		(i1 - i3) * sin(PhaseValFour);

	float denominatior = (i2 -i4) * cos(PhaseValOne) + 
		(i3 - i1) * cos(PhaseValTwo) + 
		(i4 - i2) * cos(PhaseValThree) + 
		(i1 - i3) * cos(PhaseValFour);
	
	return (atan(numenator, denominatior) + M_PI) / M_2PI;
}

void main()
{
	uint texPosX = gl_GlobalInvocationID.x;
	vec3 pixelVal;

	for(uint i = 0; i < 128; i++)
	{
		float I1 = imageLoad(PSIFirstTexture, ivec2(i, texPosX)).r;
		float I2 = imageLoad(PSISecondTexture, ivec2(i, texPosX)).r;
		float I3 = imageLoad(PSIThirdTexture, ivec2(i, texPosX)).r;
		float I4 = imageLoad(PSIFourthTexture, ivec2(i, texPosX)).r;

		float ampl = calc_ampl(I1, I2, I3, I4);
		float phi = calc_phi(I1, I2, I3, I4);

		pixelVal = imageLoad(PSIFirstTexture, ivec2(i, texPosX)).rgb;
		imageStore(AmplitudeTexture, ivec2(i, texPosX), vec4(pixelVal, 0.0));

		pixelVal = imageLoad(PSISecondTexture, ivec2(i, texPosX)).rgb;
		imageStore(PhaseTexture, ivec2(i, texPosX), vec4(pixelVal, 0.0));

		imageStore(AmplitudeTexture, ivec2(i, texPosX), ivec4(ampl, ampl, ampl, 0.0));
		imageStore(PhaseTexture, ivec2(i, texPosX), ivec4(phi, phi, phi, 0.0));
	}
}
