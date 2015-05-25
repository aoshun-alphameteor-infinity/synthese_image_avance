#version 430 core
#extension GL_ARB_shader_storage_buffer_object : require

#define POSITION    0
#define NORMAL      1
#define TEXCOORD    2
#define FRAG_COLOR  0

const float PI = 3.14159265359;
const float TWOPI = 6.28318530718;
const float PI_2 = 1.57079632679;
const float DEG2RAD = TWOPI / 360.0;

precision highp int;

uniform sampler2D Diffuse;
uniform sampler2D Spec;
uniform sampler2D Bump;
uniform vec3 cam_location;

float specularPower = 30.;

struct spotlight{
    vec3 position;
    float angle;
    vec3 direction;
    float penumbraAngle;
    vec3 color;
    float intensity;
};

struct pointlight{
    vec3 position;
    float intensity;
    vec3 color;
    float _;
};

layout(std430, binding = 0) buffer spotlights
{
    int count;
    spotlight Lights[];
} SpotLights;

layout(std430, binding = 1) buffer pointlights
{
    int count;
    pointlight Lights[];
} PointLights;

layout(location = FRAG_COLOR, index = 0) out vec4 FragColor;

in block
{
    vec2 TexCoord;
    vec4 NormalCoord;
    vec3 PositionCoord;
    vec4 Color;
} In;

vec3 spotLights(vec3 diffuseColor, vec3 specularColor, vec3 normal);
vec3 Blinn_Phong_Shading(vec3 diffuseColor, vec3 specular, vec3 normal);

void main()
{
    vec3 diffuse = texture(Diffuse, In.TexCoord).rgb;
    vec3 bump = texture(Bump, In.TexCoord).rgb;

    vec3 specular = texture(Spec, In.TexCoord).rgb;

    if(specular==vec3(0,0,0))
    {
        specular=vec3(.75,.75,.75);
    }

    vec3 spotlight_color = spotLights(diffuse, specular, In.NormalCoord.rgb);
    vec3 pointlight_color = Blinn_Phong_Shading(diffuse, specular, In.NormalCoord.rgb);

    FragColor = vec4(clamp(spotlight_color + pointlight_color, vec3(0,0,0), vec3(1,1,1)), 1.0) * In.Color;
}

vec3 spotLights(vec3 diffuseColor, vec3 specularColor, vec3 normal)
{
    vec3 outColor = vec3(0);
    vec3 n = normalize(normal);
    vec3 v = normalize(In.PositionCoord - cam_location);
    for (int i = 0; i < SpotLights.count; ++i) {
        vec3 l = normalize(SpotLights.Lights[i].position - In.PositionCoord);
        float a = cos(SpotLights.Lights[i].angle * DEG2RAD);
        float pa = cos(SpotLights.Lights[i].penumbraAngle * DEG2RAD);
        float ndotl =  max(dot(n, l), 0.0);
        float ldotd =  dot(-l, normalize(SpotLights.Lights[i].direction));
        vec3 h = normalize(l-v);
        float ndoth = max(dot(n, h), 0.0);
        float fallof = clamp(pow( (ldotd  - a) /  (a-pa), 4), 0.0, 1.0);
        float d = distance(SpotLights.Lights[i].position, In.PositionCoord);
        float att = 1.f / (d*d);
        outColor += att * fallof * SpotLights.Lights[i].color * SpotLights.Lights[i].intensity * (diffuseColor * ndotl + specularColor * pow(ndoth, specularPower));
    }
    return outColor;
}

vec3 Blinn_Phong_Shading(vec3 diffuseColor, vec3 specular, vec3 normal)
{
    vec3 outColor = vec3(0);
    vec3 n = normalize(normal);

    for (int i = 0; i < PointLights.count; ++i) {

        vec3 l = normalize(PointLights.Lights[i].position - In.PositionCoord);

        float ndotl =  clamp(dot(n, l), 0.0, 1.0);
        vec3 color = diffuseColor * ndotl;
        vec3 v = normalize(In.PositionCoord - cam_location);

        vec3 h = normalize(l-v);
        float ndoth = clamp(dot(n, h), 0.0, 1.0);
        vec3 specularColor = specular * pow(ndoth, specularPower);

        float d = distance(PointLights.Lights[i].position, In.PositionCoord);

        float factor = PointLights.Lights[i].intensity / d*d;
        outColor += vec3(factor, factor, factor) * PointLights.Lights[i].color * clamp(specularColor + color, vec3(0., 0., 0.), vec3(1., 1., 1.));
    }

    return outColor;
}
