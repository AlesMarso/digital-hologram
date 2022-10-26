#version 460 core

layout(local_size_x = 1, local_size_y = 704, local_size_z = 1) in;
layout(binding = 0, rgba8) uniform image2D out_tex;

void main()
{
    uint texPosY = gl_GlobalInvocationID.y;

	for(uint i = 0; i < 2816; i++)
	{
		ivec2 texPos = ivec2(i, texPosY);     
		float in_val = imageLoad( out_tex, texPos).r;
        imageStore( out_tex, texPos, vec4( in_val, 0.0, 0.0, 0.0 ) );
	}
}