#version 330

// indice = 0
layout(location = 0) in vec3 Position;
// indice = 1
layout(location = 1) in vec3 Normal;
// indice = 2
layout(location = 2) in vec2 TexCoord;
// indice = 3
layout(location = 3) in vec4 Color;

out block {
    vec4 Color;
    vec3 Normal;
    vec2 TexCoord;
} Out;

uniform mat4 modelviewProjection;
uniform mat4 normalTransformation;

void main()
{
    gl_Position = modelviewProjection*vec4(Position,1.0);
    vec4 n = normalTransformation * vec4(Normal, 0.);
    Out.Normal = n.xyz;
    Out.Color = Color;
    Out.TexCoord = TexCoord;
}
