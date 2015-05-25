#version 330

uniform sampler2D Diffuse;
uniform sampler2D Spec;
uniform sampler2D Bump;
layout(location = 0) out vec4 FragColor;

in block {
    vec4 Color;
    vec3 Normal;
    vec2 TexCoord;
} In;

void main()
{
    vec3 diffuse = texture(Diffuse, In.TexCoord).rgb;
    FragColor = vec4(In.Color.rgb * diffuse, In.Color.z);
}
