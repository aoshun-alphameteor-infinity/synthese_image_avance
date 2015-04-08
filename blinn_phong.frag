#version 410 core

#define POSITION    0
#define NORMAL      1
#define TEXCOORD    2
#define FRAG_COLOR  0

precision highp int;

uniform sampler2D Diffuse;
uniform sampler2D Spec;
uniform sampler2D Bump;
uniform vec3 light_color;
uniform float l_intensity;
uniform vec3 cam_location;
uniform int specularPower;

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

in block
{
    vec2 TexCoord;
    vec4 NormalCoord;
    vec3 PositionCoord;
    vec3 lightPosition;
} In;

vec4 Blinn_Phong_Shading(vec3 diffuseColor, vec3 specular, vec3 normal, vec3 light_position);

void main()
{
    vec3 diffuseColor = texture(Diffuse, In.TexCoord).rgb;
    vec3 specular = texture(Spec, In.TexCoord).rgb;
    vec3 n = normalize(In.NormalCoord.rgb);


    vec3 l = In.lightPosition - In.PositionCoord;
    l = normalize(l);

    float ndotl =  clamp(dot(n, l), 0.0, 1.0);
    vec3 color = diffuseColor * ndotl;
    vec3 v = normalize(In.PositionCoord - cam_location);

    vec3 h = normalize(l-v);
    float ndoth = clamp(dot(n, h), 0.0, 1.0);
    vec3 specularColor =  specular * pow(ndoth, specularPower);

    float d = distance(In.lightPosition, In.PositionCoord);

    FragColor = vec4((1.0 / d*d) * l_intensity * light_color*(specularColor + color), 1.0);
    FragColor = Blinn_Phong_Shading(diffuseColor, specular, In.NormalCoord.rgb, In.lightPosition);

}

vec4 Blinn_Phong_Shading(vec3 diffuseColor, vec3 specular, vec3 normal, vec3 light_position)
{
    vec3 n = normalize(normal);


    vec3 l = light_position - In.PositionCoord;
    l = normalize(l);

    float ndotl =  clamp(dot(n, l), 0.0, 1.0);
    vec3 color = diffuseColor * ndotl;
    vec3 v = normalize(In.PositionCoord - cam_location);

    vec3 h = normalize(l-v);
    float ndoth = clamp(dot(n, h), 0.0, 1.0);
    vec3 specularColor =  specular * pow(ndoth, specularPower);

    float d = distance(light_position, In.PositionCoord);

    return vec4((1.0 / d*d) * l_intensity * light_color*(specularColor + color), 1.0);
}
