// ----------------------------------------------------------------------------
// tinygfxlib.cpp 
// ----------------------------------------------------------------------------
#include "tinygfxlib.h"
#include <d3dcompiler.h>
#include "DirectXTex/DDSTextureLoader/DDSTextureLoader.h"

#define SAFE_RELEASE(p) if(p){p->Release();}

namespace tgl
{
	namespace
	{
		RECT ClientRectSize(HWND wnd, UINT& width, UINT& height)
		{
			RECT rc;
			GetClientRect(wnd, &rc);
			width  = rc.right  - rc.left;
			height = rc.bottom - rc.top;
			return rc;
		}

	}


	Device::Device()
		: m_device					(nullptr)
		, m_deviceContext			(nullptr)
		, m_swapChain				(nullptr)
		, m_backBufferRenderTarget	(nullptr)
		, m_initialized				(false)
	{
	}

	Device::~Device()
	{
		if(m_initialized)
		{
			Terminate();
			m_initialized = false;
		}
	}

	void Device::Initialize(HWND wnd, UINT width, UINT height)
	{
		const UINT minimumDisplaySize = 128;
		if(m_initialized)
		{
			return;
		}
		if(width<minimumDisplaySize || height<minimumDisplaySize)
		{
			return;
		}

		// 表示矩形サイズの計算. 
		RECT rc = ClientRectSize(wnd, width, height);

		// デバイス作成時フラグ. 
		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		// ドライバタイプ. 
		D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};
		UINT numDriverTypes = ARRAYSIZE(driverTypes);

		// フィーチャーレベル : DX11 class only. 
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			//D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};
		UINT numFeatureLevels = ARRAYSIZE(featureLevels);

		// スワップチェインの設定. 
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount							= 2;
		sd.BufferDesc.Width						= width;
		sd.BufferDesc.Height					= height;
		sd.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator		= 60;
		sd.BufferDesc.RefreshRate.Denominator	= 1;
		sd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow							= wnd;
		sd.SampleDesc.Count						= 1;
		sd.SampleDesc.Quality					= 0;
		sd.Windowed								= TRUE;

		// デバイスの作成. 
		D3D_FEATURE_LEVEL featureLevel;
		HRESULT hr;
		for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
		{
			auto driverType = driverTypes[driverTypeIndex];

			hr = D3D11CreateDeviceAndSwapChain(NULL,
				driverType,
				NULL,
				createDeviceFlags,
				featureLevels,
				numFeatureLevels,
				D3D11_SDK_VERSION,
				&sd,
				&m_swapChain,
				&m_device,
				&featureLevel,
				&m_deviceContext);
			if (SUCCEEDED(hr))
			{
				break;
			}
		}
		if(FAILED(hr))
		{
			return;
		}
		if(featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			return;
		}

		// バックバッファ用レンダーターゲットの作成. 
		ID3D11Texture2D* backBuffer = NULL;
		hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
		if(FAILED(hr))
		{
			return;
		}
		hr = m_device->CreateRenderTargetView(backBuffer, NULL, &m_backBufferRenderTarget);
		backBuffer->Release();
		if(FAILED(hr))
		{
			return;
		}

		// 初期化終わり. 
		m_initialized = true;
	}

	void Device::Terminate()
	{
		if(m_initialized)
		{
			SAFE_RELEASE(m_backBufferRenderTarget);
			SAFE_RELEASE(m_swapChain);
			SAFE_RELEASE(m_deviceContext);
			SAFE_RELEASE(m_device);
			m_initialized = false;
		}
	}

	bool Device::IsInitialized() const
	{
		return m_initialized;
	}


} // namespace tgl 
