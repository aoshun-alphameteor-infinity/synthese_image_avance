#version 410 core

#define POSITION    0
#define NORMAL      1
#define TEXCOORD    2
#define FRAG_COLOR  0

precision highp float;
precision highp int;

uniform mat4 modelviewProjection;
uniform float Time;
uniform vec3 spotlight;

in int gl_VertexID;
in int gl_InstanceID;

layout(location = POSITION) in vec3 Position;
layout(location = NORMAL) in vec3 Normal;
layout(location = TEXCOORD) in vec2 TexCoord;

out gl_PerVertex
{
    vec4 gl_Position;
};

out block
{
    float time;
    vec2 TexCoord;
    vec4 NormalCoord;
    vec3 PositionCoord;
    vec3 lightPosition;
} Out;

void main()
{
    float theta = Time*3.14/6;
    vec3 pos;
    switch(gl_InstanceID) {/*
        case 0 :
            pos = vec3(Position.x*cos(theta) + Position.z*sin(theta), Position.y, Position.z * cos(theta) - Position.x*sin(theta));
            break;
        case 1 :
            pos.z = Position.z;
            pos.y = Position.y + 2;
            pos.x = Position.x + sin(Time);
            break;
        case 2 :
            pos = Position;
            pos.y = Position.y + 4 + cos(Time);
            break;
        case 3 :
            pos.x = Position.x*cos(-theta*3) + Position.z*sin(-theta*3) + 2 * cos(-theta*3);
            pos.y = Position.y - 3 + sin(Time)/2;
            pos.z = Position.z * cos(-theta*3) - Position.x*sin(-theta*3) - 2 * sin(-theta*3);
            break;*/
        default :
            pos = Position;
    }
    gl_Position = modelviewProjection * vec4(pos, 1.0);
    Out.TexCoord = TexCoord;
    Out.NormalCoord = Normal;
    Out.PositionCoord = Position;
    Out.time = Time;
    Out.lightPosition = spotlight;
}
