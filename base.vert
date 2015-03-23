#version 330

// indice = 0
layout(location = 0) in vec3 vx_pos;
// indice = 2
layout(location = 2) in vec3 vx_col;

out vec3 color;

uniform mat4 modelviewProjection;

void main()
{
  gl_Position = vec4(vx_pos,1.0);
  //gl_Position = modelviewProjection*vec4(vx_pos,1.0);
  color = vx_col;
}
