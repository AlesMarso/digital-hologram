#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec2 vertexPos2;

out vec2 TextureCord;

void main() {
  gl_Position.xyz = vertexPos;
  gl_Position.w = 1.0;
  
  TextureCord = vertexPos2;
}
