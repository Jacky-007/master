#include <DirectXMath.h>

struct DirectionalLight {
  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;
  DirectX::XMFLOAT3 direction;
  float pad;
};

struct PointLight {
  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;
  DirectX::XMFLOAT3 position;
  float pad;
};

struct Material {
  DirectX::XMFLOAT4 albedo;
  DirectX::XMFLOAT3 specular;
  float shininess;
};