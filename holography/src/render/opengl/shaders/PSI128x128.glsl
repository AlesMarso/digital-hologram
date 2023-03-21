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
float K = 2 * sqrt(2);

const float PhaseValOne = 0;
const float PhaseValTwo = M_PI / 2;
const float PhaseValThree = M_PI;
const float PhaseValFour = 3 * (M_PI / 2);

float cosd1 = 0;
float cosd2 = 0;
float cosd3 = 0;
float cosd4 = 0;

float sind1 = 0;
float sind2 = 0;
float sind3 = 0;
float sind4 = 0;

float calc_ampl(float i1, float i2, float i3, float i4)
{
	float IS = (i2 - i4) * sind1 + 
		(i3 - i1) * sind2 + 
		(i4 - i2) * sind3 + 
		(i1 - i3) * sind4;

	float IC = (i2 - i4) * cosd1 + 
		(i3 - i1) * cosd2 + 
		(i4 - i2) * cosd3 + 
		(i1 - i3) * cosd4;

	float CS = (cosd2 - cosd4) * sind1 + 
		(cosd3 - cosd1) * sind2 + 
		(cosd4 - cosd2) * sind3 + 
		(cosd1 - cosd3) * sind4;

	float bxy = (1 / abs(CS)) * (sqrt(IS * IS + IC * IC));

	float ap = bxy / 2;

	return bxy * K;
}

float calc_phi(float i1, float i2, float i3, float i4)
{
	float numenator = (i2 - i4) * sind1 + 
		(i3 - i1) * sind2 + 
		(i4 - i2) * sind3 * 
		(i1 - i3) * sind4;

	float denominatior = (i2 -i4) * cosd1 + 
		(i3 - i1) * cosd2 + 
		(i4 - i2) * cosd3 + 
		(i1 - i3) * cosd4;
	
	return (atan(numenator, denominatior) + M_PI) / M_2PI;
}

void main()
{
	uint texPosX = gl_GlobalInvocationID.x;
	vec3 pixelVal;

	cosd1 = cos(PhaseValOne);
	cosd2 = cos(PhaseValTwo);
	cosd3 = cos(PhaseValThree);
	cosd4 = cos(PhaseValFour);
	
	sind1 = sin(PhaseValOne);
	sind2 = sin(PhaseValTwo);
	sind3 = sin(PhaseValThree);
	sind4 = sin(PhaseValFour);

	for(uint i = 0; i < 128; i++)
	{
		ivec2 id = ivec2(i, texPosX);

		float I1 = imageLoad(PSIFirstTexture, id).r;
		float I2 = imageLoad(PSISecondTexture, id).r;
		float I3 = imageLoad(PSIThirdTexture, id).r;
		float I4 = imageLoad(PSIFourthTexture, id).r;

		float ampl = calc_ampl(I1, I2, I3, I4);
		float phi = calc_phi(I1, I2, I3, I4);

		//pixelVal = imageLoad(PSIThirdTexture, id).rgb;
		//imageStore(AmplitudeTexture, id, vec4(pixelVal, 0.0));
		//
		//pixelVal = imageLoad(PSIFourthTexture, id).rgb;
		//imageStore(PhaseTexture, id, vec4(pixelVal, 0.0));

		imageStore(AmplitudeTexture, id, vec4(ampl, ampl, ampl, 0.0));
		imageStore(PhaseTexture, id, vec4(phi, phi, phi, 0.0));
	}
}
