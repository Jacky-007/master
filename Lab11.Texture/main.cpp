
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <DirectXMath.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <math.h>  // sin, cos for rotation
#include <windows.h>
#include <windowsx.h>

// @TODO : use the new data data2.h
#include "data2.h"
//#include "data.h"  // example 3d model (the 'cube.h' source file is provided below, along with 'shaders.hlsl')
#include "lighting.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
// Minimal D3D11 by d7samurai
#define TITLE "Lab10.Texture"

///////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
///////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
  WNDCLASSEX wndClassEx = {sizeof(wndClassEx)};
  wndClassEx.lpfnWndProc = WindowProc;
  wndClassEx.lpszClassName = TITLE;
  wndClassEx.hCursor = LoadCursor(NULL, IDC_CROSS);

  RegisterClassExA(&wndClassEx);

  HWND window = CreateWindowExA(0, TITLE, TITLE,
                                WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr,
                                nullptr, nullptr, nullptr);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  D3D_FEATURE_LEVEL featureLevels[] = {D3D_FEATURE_LEVEL_11_0};

  ID3D11Device *baseDevice;
  ID3D11DeviceContext *baseDeviceContext;

  D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                    D3D11_CREATE_DEVICE_BGRA_SUPPORT, featureLevels,
                    ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &baseDevice,
                    nullptr, &baseDeviceContext);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  ID3D11Device1 *device;

  baseDevice->QueryInterface(__uuidof(ID3D11Device1),
                             reinterpret_cast<void **>(&device));

  ID3D11DeviceContext1 *deviceContext;

  baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1),
                                    reinterpret_cast<void **>(&deviceContext));

  ///////////////////////////////////////////////////////////////////////////////////////////////

  IDXGIDevice1 *dxgiDevice;

  device->QueryInterface(__uuidof(IDXGIDevice1),
                         reinterpret_cast<void **>(&dxgiDevice));

  IDXGIAdapter *dxgiAdapter;

  dxgiDevice->GetAdapter(&dxgiAdapter);

  IDXGIFactory2 *dxgiFactory;

  dxgiAdapter->GetParent(__uuidof(IDXGIFactory2),
                         reinterpret_cast<void **>(&dxgiFactory));

  ///////////////////////////////////////////////////////////////////////////////////////////////

  DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
  swapChainDesc.Width = 0;   // use window width
  swapChainDesc.Height = 0;  // use window height
  swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
  swapChainDesc.Stereo = FALSE;
  swapChainDesc.SampleDesc.Count = 1;
  swapChainDesc.SampleDesc.Quality = 0;
  swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  swapChainDesc.BufferCount = 2;
  swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
  swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
  swapChainDesc.Flags = 0;

  IDXGISwapChain1 *swapChain;

  dxgiFactory->CreateSwapChainForHwnd(device, window, &swapChainDesc, nullptr,
                                      nullptr, &swapChain);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  ID3D11Texture2D *frameBuffer;

  swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                       reinterpret_cast<void **>(&frameBuffer));

  ID3D11RenderTargetView *frameBufferView;

  device->CreateRenderTargetView(frameBuffer, nullptr, &frameBufferView);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  D3D11_TEXTURE2D_DESC depthBufferDesc;

  frameBuffer->GetDesc(&depthBufferDesc);  // base on framebuffer properties

  depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

  ID3D11Texture2D *depthBuffer;

  device->CreateTexture2D(&depthBufferDesc, nullptr, &depthBuffer);

  ID3D11DepthStencilView *depthBufferView;

  device->CreateDepthStencilView(depthBuffer, nullptr, &depthBufferView);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  ID3DBlob *vsBlob;

  D3DCompileFromFile(L"box_shader.hlsl", nullptr, nullptr, "vs_main", "vs_5_0",
                     0, 0, &vsBlob, nullptr);

  ID3D11VertexShader *vertexShader;

  device->CreateVertexShader(vsBlob->GetBufferPointer(),
                             vsBlob->GetBufferSize(), nullptr, &vertexShader);

  D3D11_INPUT_ELEMENT_DESC
  inputElementDesc[] =  // DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 normal
      {
          {"POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
           D3D11_INPUT_PER_VERTEX_DATA, 0},
          {"NOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
           D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		     // @TODO : add TEX layout
		  {"TEX",0,DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
      };

  ID3D11InputLayout *inputLayout;

  device->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc),
                            vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(),
                            &inputLayout);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  ID3DBlob *psBlob;

  D3DCompileFromFile(L"box_shader.hlsl", nullptr, nullptr, "ps_main", "ps_5_0",
                     0, 0, &psBlob, nullptr);

  ID3D11PixelShader *pixelShader;

  device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(),
                            nullptr, &pixelShader);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  D3D11_RASTERIZER_DESC1 rasterizerDesc = {};
  rasterizerDesc.FillMode = D3D11_FILL_SOLID;
  rasterizerDesc.CullMode = D3D11_CULL_NONE;

  ID3D11RasterizerState1 *rasterizerState;

  device->CreateRasterizerState1(&rasterizerDesc, &rasterizerState);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // @TODO: define d3d11 sampler here, change its configuration
  D3D11_SAMPLER_DESC samplerDesc = {};
  samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
  samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;

  ID3D11SamplerState *samplerState;

  device->CreateSamplerState(&samplerDesc, &samplerState);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
  depthStencilDesc.DepthEnable = TRUE;
  depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
  depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

  ID3D11DepthStencilState *depthStencilState;

  device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  struct VSConstBuffer {
    DirectX::XMMATRIX model;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX project;
  };

  struct PSConstBuffer {
    DirectionalLight dirLight;
    PointLight pointLight;
    Material material;
    DirectX::XMFLOAT3 view_pos;
    float pad;
  };

  ID3D11Buffer *vs_constantBuffer;
  ID3D11Buffer *ps_constantBuffer;
  D3D11_BUFFER_DESC constantBufferDesc;
  ZeroMemory(&constantBufferDesc, sizeof(constantBufferDesc));
  constantBufferDesc.ByteWidth = sizeof(VSConstBuffer);
  constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
  constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

  device->CreateBuffer(&constantBufferDesc, nullptr, &vs_constantBuffer);
  constantBufferDesc.ByteWidth = sizeof(PSConstBuffer);
  device->CreateBuffer(&constantBufferDesc, nullptr, &ps_constantBuffer);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  D3D11_BUFFER_DESC vertexBufferDesc = {};
  vertexBufferDesc.ByteWidth = sizeof(CubeVertexData);
  vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

  D3D11_SUBRESOURCE_DATA vertexData = {CubeVertexData};

  ID3D11Buffer *vertexBuffer;

  device->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  D3D11_BUFFER_DESC indexBufferDesc = {};
  indexBufferDesc.ByteWidth = sizeof(IndexData);
  indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
  indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

  D3D11_SUBRESOURCE_DATA indexData = {IndexData};

  ID3D11Buffer *indexBuffer;

  device->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  // Read resources from files
  int imgWidth, imgHeight, nrChannels;
  auto diffuse_data =
      stbi_load("brickwall.jpg", &imgWidth, &imgHeight, &nrChannels, 4);

  // @TODO : Bind texture to D3D11, format : DXGI_FORMAT_R8G8B8A8_UNORM
  D3D11_TEXTURE2D_DESC textureDesc = {};
  textureDesc.Width = imgWidth;
  textureDesc.Height = imgHeight;
  textureDesc.MipLevels = 1;
  textureDesc.ArraySize = 1;
  textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  textureDesc.SampleDesc.Count = 1;
  textureDesc.Usage = D3D11_USAGE_IMMUTABLE;
  textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

  D3D11_SUBRESOURCE_DATA textureData = {};
  textureData.pSysMem = diffuse_data;
  textureData.SysMemPitch = imgWidth * 4; //4 bytes per pixel

  ID3D11Texture2D *texture;
  device->CreateTexture2D(&textureDesc, &textureData, &texture);

  ID3D11ShaderResourceView *textureView_diffuse;
  device->CreateShaderResourceView(texture, nullptr, &textureView_diffuse);

  ///////////////////////////////////////////////////////////////////////////////////////////////

  float width = static_cast<float>(depthBufferDesc.Width);    // width
  float height = static_cast<float>(depthBufferDesc.Height);  // height
  float nearZ = 0.1f;                                         // near
  float farZ = 1000.0f;                                       // far

  DirectX::XMFLOAT3 modelRotation = {0.0f, 0.0f, 0.0f};
  DirectX::XMFLOAT3 modelScale = {1.0f, 1.0f, 1.0f};
  DirectX::XMFLOAT3 modelTranslation = {0.0f, 0.0f, 2.0f};

  ///////////////////////////////////////////////////////////////////////////////////////////////
  while (true) {
    MSG msg;

    while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessageA(&msg);
    }

    const int constFps = 60;
    float timeInOneFps = 1000.0f / constFps;
    DWORD timeBegin = GetTickCount64();

    ///////////////////////////////////////////////////////////////////////////////////////////
    DirectX::XMMATRIX rotate_mat = DirectX::XMMatrixRotationRollPitchYaw(
        modelRotation.z, modelRotation.x, modelRotation.y);
    DirectX::XMMATRIX scale_mat =
        DirectX::XMMatrixScaling(modelScale.x, modelScale.y, modelScale.z);
    DirectX::XMMATRIX translate_mat = DirectX::XMMatrixTranslation(
        modelTranslation.x, modelTranslation.y, modelTranslation.z);

    modelRotation.x += 0.015f;
    modelRotation.y += 0.027f;
    modelRotation.z += 0.003f;

    ///////////////////////////////////////////////////////////////////////////////////////////
    D3D11_MAPPED_SUBRESOURCE mappedSubresource;

    deviceContext->Map(vs_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,
                       &mappedSubresource);

    VSConstBuffer *constants =
        reinterpret_cast<VSConstBuffer *>(mappedSubresource.pData);

    constants->model = rotate_mat * scale_mat * translate_mat;
    constants->view = DirectX::XMMatrixIdentity();
    constants->project = DirectX::XMMatrixPerspectiveFovLH(
        DirectX::XMConvertToRadians(60.0f), width / height, nearZ, farZ);

    deviceContext->Unmap(vs_constantBuffer, 0);

    deviceContext->Map(ps_constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0,
                       &mappedSubresource);

    PSConstBuffer *ps_const =
        reinterpret_cast<PSConstBuffer *>(mappedSubresource.pData);

    ps_const->dirLight.ambient = DirectX::XMFLOAT4(0.1f, 0.1f, 0.0f, 1.0f);
    ps_const->dirLight.diffuse = DirectX::XMFLOAT4(0.5f, 0.4f, 0.4f, 1.0f);
    ps_const->dirLight.specular = DirectX::XMFLOAT4(1.0f, 0.9f, 0.85f, 1.0f);
    ps_const->dirLight.direction = DirectX::XMFLOAT3(-0.577f, -0.577f, 0.577f);

    ps_const->pointLight.position = DirectX::XMFLOAT3(0.0f, 1.0f, -4.0f);
    ps_const->pointLight.ambient = DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
    ps_const->pointLight.diffuse = DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
    ps_const->pointLight.specular = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);

    ps_const->material.albedo = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    ps_const->material.specular = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
    ps_const->material.shininess = 50.0f;
    ps_const->view_pos = DirectX::XMFLOAT3(0, 0, 0);

    deviceContext->Unmap(ps_constantBuffer, 0);

    ///////////////////////////////////////////////////////////////////////////////////////////

    FLOAT backgroundColor[4] = {0.025f, 0.025f, 0.025f, 1.0f};

    //UINT stride = 6 * sizeof(float);
	// @TODO : re-calculate the stride
	UINT stride = 8 * sizeof(float);
    UINT offset = 0;

    D3D11_VIEWPORT viewport = {0.0f, 0.0f, width, height, 0.0f, 1.0f};

    ///////////////////////////////////////////////////////////////////////////////////////////

    deviceContext->ClearRenderTargetView(frameBufferView, backgroundColor);
    deviceContext->ClearDepthStencilView(depthBufferView, D3D11_CLEAR_DEPTH,
                                         1.0f, 0);

    deviceContext->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->VSSetConstantBuffers(0, 1, &vs_constantBuffer);
    deviceContext->PSSetConstantBuffers(1, 1, &ps_constantBuffer);

    deviceContext->RSSetViewports(1, &viewport);
    deviceContext->RSSetState(rasterizerState);

    deviceContext->PSSetShader(pixelShader, nullptr, 0);
	// @TODO: set PS samplers and resources
	deviceContext->PSSetShaderResources(0,1,&textureView_diffuse);
	deviceContext->PSSetSamplers(0,1,&samplerState);

    deviceContext->OMSetRenderTargets(1, &frameBufferView, depthBufferView);
    deviceContext->OMSetDepthStencilState(depthStencilState, 0);
    deviceContext->OMSetBlendState(
        nullptr, nullptr, 0xffffffff);  // use default blend mode (i.e. disable)

    ///////////////////////////////////////////////////////////////////////////////////////////

    deviceContext->DrawIndexed(ARRAYSIZE(IndexData), 0, 0);

    ///////////////////////////////////////////////////////////////////////////////////////////

    swapChain->Present(1, 0);

    ///////////////////////////////////////////////////////////////////////////////////////////

    DWORD timeTotal = GetTickCount64() - timeBegin;
    if (timeTotal < timeInOneFps) Sleep(DWORD(timeInOneFps - timeTotal));
  }
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}