#version 460 core

layout(local_size_x = 128) in;
layout(binding = 0, rgba8) uniform image2D PSIFirstTexture;
layout(binding = 1, rgba8) uniform image2D PSISecondTexture;
layout(binding = 2, rgba8) uniform image2D PSIThirdTexture;
layout(binding = 3, rgba8) uniform image2D PSIFourthTexture;
layout(binding = 4, rgba8) uniform image2D AmplitudeTexture;
layout(binding = 5, rgba8) uniform image2D PhaseTexture;

uniform float PhaseValOne;
uniform float PhaseValTwo;
uniform float PhaseValThree;
uniform float PhaseValFour;

const float M_PI = 3.14159265358979323846;
const float M_2PI = 2 * M_PI;

void main()
{
	uint texPosX = gl_GlobalInvocationID.x;
	vec3 pixelVal;

	for(uint i = 0; i < 128; i++)
	{
		pixelVal = imageLoad(PSIFirstTexture, ivec2(i, texPosX)).rgb;
		imageStore(AmplitudeTexture, ivec2(i, texPosX), vec4(pixelVal, 0.0));

		pixelVal = imageLoad(PSISecondTexture, ivec2(i, texPosX)).rgb;
		imageStore(PhaseTexture, ivec2(i, texPosX), vec4(pixelVal, 0.0));
	}
}
