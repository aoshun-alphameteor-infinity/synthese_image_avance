#version 410 core

#define POSITION	0
#define NORMAL		1
#define TEXCOORD	2
#define FRAG_COLOR	0

precision highp float;
precision highp int;

uniform mat4 modelviewProjection;
uniform mat4 normalTransformation;

layout(location = POSITION) in vec3 Position;
layout(location = NORMAL) in vec4 Normal;
layout(location = TEXCOORD) in vec2 TexCoord;
layout(location = 3) in vec4 Color;

out gl_PerVertex
{
	vec4 gl_Position;
};

out block
{
	vec2 TexCoord;
    vec4 NormalCoord;
    vec3 PositionCoord;
    vec4 Color;
} Out;

void main()
{	
    gl_Position = modelviewProjection * vec4(Position, 1.0);
	Out.TexCoord = TexCoord;
    Out.NormalCoord = normalTransformation * Normal;
    Out.PositionCoord = Position;
    Out.Color = Color;
}
