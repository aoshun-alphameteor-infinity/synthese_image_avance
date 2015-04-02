#version 330

// indice = 0
layout(location = 0) in vec3 vx_pos;
// indice = 1
layout(location = 1) in vec3 Normal;
// indice = 3
layout(location = 3) in vec4 vx_col;

out vec4 color;

uniform mat4 modelviewProjection;

void main()
{
  gl_Position = modelviewProjection*vec4(vx_pos,1.0);
  color = vx_col;
}
