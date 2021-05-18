Texture2D box_texture : register(t0);
SamplerState box_sampler : register(s0);

struct Material
{
    float4 albedo;
    float4 specular;
};

struct DirectionalLight
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float3 direction;
};

struct PointLight
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float3 position;
};


cbuffer VSConstBuffer : register(b0)
{
    row_major float4x4 model;
    row_major float4x4 view;
    row_major float4x4 project;
};

cbuffer PSConstBuffer : register(b1)
{
    
    DirectionalLight dir_light;
    PointLight point_light;
    Material material;
    float3 view_pos;
};

struct VertexIn
{
    float3 position : POS;
    float3 normal : NOR;
      // @TODO : add TEX definition
	float2 texcoord : TEX;
};

struct VertexOut
{
    float4 position : SV_POSITION;
    float3 pos_w : POS;
    float3 normal : NOR;
    // @TODO : add TEX definition
	float2 texcoord : TEX;
};



// calculate directional light here
void CalcDirectionalLight(Material mat, DirectionalLight L,
	float3 normal, float3 to_eye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec)
{
    float3 light_vec = normalize(-L.direction);
    // halfway vector
    float3 H = normalize(light_vec + to_eye);

    ambient = mat.albedo * L.ambient;

    float diffuse_factor = max(0.0f, dot(light_vec, normal));

    float3 v = reflect(-light_vec, normal);
    float spec_factor = pow(max(dot(H, normal), 0.0f), mat.specular.w);

    diffuse = diffuse_factor * mat.albedo * L.diffuse;
    spec = spec_factor * mat.specular * L.specular;
}

// calculate point light color here
void CalcPointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 to_eye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
    float3 light_vec = L.position - pos;
    float distance = length(light_vec);
    light_vec /= distance;
    // halfway vector
    float3 H = normalize(light_vec + to_eye);

    ambient = mat.albedo * L.ambient;

    float diffuse_factor = max(0.0f, dot(light_vec, normal));

    float3 v = reflect(-light_vec, normal);
    float spec_factor = pow(max(dot(H, normal), 0.0f), mat.specular.w);

    diffuse = diffuse_factor * mat.albedo * L.diffuse;
    spec = spec_factor * mat.specular * L.specular;

    // attenuation
    float attenuate = 1.0f / (distance * distance);
    diffuse *= attenuate;
    spec *= attenuate;
}


VertexOut vs_main(VertexIn input)
{
    VertexOut output;
    row_major matrix transform = mul(model, view);

    float4 pos_w = mul(float4(input.position, 1.0f), model);

    output.position = mul(float4(input.position, 1.0f), mul(transform, project));
    output.pos_w = pos_w.xyz;
    output.normal = normalize(mul(float4(input.normal, 0), transform).xyz);
    // @TODO : pass texcoord to ps shader
    output.texcoord = input.texcoord;

    return output;
}

float4 ps_main(VertexOut input) : SV_TARGET
{
    float3 to_eye = normalize(view_pos - input.pos_w);
    input.normal = normalize(input.normal);

    float4 ambient, diffuse, specular;
    float4 A, D, S;
    ambient = diffuse = specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float4 tex_color = box_texture.Sample(box_sampler, input.texcoord);

    CalcDirectionalLight(material, dir_light, input.normal, to_eye, A, D, S);
    ambient += A;
    diffuse += D;
    specular += S;

    CalcPointLight(material, point_light, input.pos_w, input.normal, to_eye, A, D, S);
    ambient += A;
    diffuse += D;
    specular += S;

// @TODO : modify the shader to use texture

    return  tex_color * (ambient + diffuse) + specular ;
}