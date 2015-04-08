#version 330

// indice = 0
layout(location = 0) in vec3 vx_pos;
// indice = 1
layout(location = 1) in vec3 Normal;
// indice = 3
layout(location = 3) in vec4 vx_col;

out vec4 color;
out vec3 normal;

uniform mat4 modelviewProjection;
uniform mat4 normalTransformation;

void main()
{
    gl_Position = modelviewProjection*vec4(vx_pos,1.0);
    vec4 n = normalTransformation * vec4(Normal, 0.);
    normal = n.xyz;
    color = vx_col;
}
