#version 430 core

uniform sampler2D u_Texture;

in vec2 TextureCord;

void main() 
{
	vec4 Texture = texture(u_Texture, TextureCord);
	gl_FragColor = Texture;
}
