
struct Material
{
    float4 ambient;
    float4 diffuse;
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
}

cbuffer PSConstBuffer : register(b1)
{
    
    DirectionalLight dir_light;
    PointLight point_light;
    Material material;
    float3 view_pos;
}

struct VertexIn
{
    float3 position : POS;
    float3 normal : NOR;
};

struct VertexOut
{
    float4 position : SV_POSITION;
    float3 pos_w : POS;
    float3 normal : NOR;
};

// @TODO: calculate directional light here
void calc_directional_light(Material mat, DirectionalLight L,
	float3 normal, float3 to_eye,
	out float4 ambient,
	out float4 diffuse,
	out float4 spec)
{
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// 光线方向
	float3 lightVec = -L.direction;
	// 环境光计算
	ambient = mat.ambient * L.ambient;
	// 计算漫反射系数
	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{

		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, to_eye), 0.0f), mat.specular.w);
		//计算漫反射光
		diffuse = diffuseFactor * mat.diffuse * L.diffuse;
		//计算高光
		spec = specFactor * mat.specular * L.specular;
	}
}


//@TODO: calculate point light color here
void calc_point_light(Material mat, PointLight L, float3 pos, float3 normal, float3 to_eye,
	out float4 ambient, out float4 diffuse, out float4 spec)
{
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
	//光照方向：顶点到光源
	float3 lightVec = L.position - pos;

	//顶点到光源距离
	float d = length(lightVec);

	//归一化光照方向
	lightVec /= d;

	//计算环境光
	ambient = mat.ambient * L.ambient;

	//漫反射系数
	float diffuseFactor = dot(lightVec, normal);

	[flatten]
	if (diffuseFactor > 0.0f)
	{
		float3 v = reflect(-lightVec, normal);
		float specFactor = pow(max(dot(v, to_eye), 0.0f), mat.specular.w);
		//计算漫反射光
		diffuse = diffuseFactor * mat.diffuse * L.diffuse;
		//计算高光
		spec = specFactor * mat.specular * L.specular;
	}

	// 计算衰减
	float att = 1.0f / dot(0.01f, float3(1.0f, d, d*d));

	diffuse *= att;
	spec *= att;
}


VertexOut vs_main(VertexIn input)
{
    VertexOut output;
    row_major matrix transform = mul(model, view);

    float4 pos_w = mul(float4(input.position, 1.0f), model);
    
    output.position = mul(float4(input.position, 1.0f), mul(transform, project));
    output.pos_w = pos_w.xyz;
    output.normal = normalize(mul(float4(input.normal, 0), transform).xyz);
    return output;
}

float4 ps_main(VertexOut input) : SV_TARGET
{   
    float3 to_eye = normalize(view_pos - input.pos_w);
    input.normal = normalize(input.normal);
       
    float4 ambient, diffuse, specular;
    float4 A, D, S;
    ambient = diffuse = specular = float4(0.0f, 0.0f, 0.0f, 0.0f);

    //calc_directional_light(material, dir_light, input.normal, to_eye, A, D, S);
   // ambient += A;
    //diffuse += D;
    //specular += S;
    
    calc_point_light(material, point_light, input.pos_w, input.normal, to_eye, A, D, S);
    ambient += A;
    diffuse += D;
    specular += S;
    
    return ambient + diffuse + specular;
}