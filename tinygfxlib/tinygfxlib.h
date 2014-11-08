// ----------------------------------------------------------------------------
// tinygfxlib.h 
// ----------------------------------------------------------------------------
// Description : DirectX11�̃T���v�����������߂̃��b�p. 
#pragma once
#define  WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace tgl
{
	//! �R�}���h�R���e�L�X�g. 
	class Command
	{
		friend class Device;
	private:
		ID3D11DeviceContext*			m_dc;

	public:

		ID3D11DeviceContext*			DC				();

		void							DrawIndexed		(UINT indexCount, UINT startIndexLocation, UINT baseVertexLocation);

	protected:
		Command(ID3D11DeviceContext* dc);
	}; // class Command 

	//! �o�b�t�@���. 
	class Buffer
	{
		friend class Device;
	private:
		ID3D11Buffer*					m_buffer;
	protected:
		ID3D11Buffer*					Get();
	public:
		         Buffer();
		virtual ~Buffer();

		virtual void					Bind(Command& cmd, int slot)=0;
		virtual void*					Map()=0;
		virtual void					Unmap()=0;

	}; // class Buffer 

	//! ���_�o�b�t�@. 
	class VertexBuffer : public Buffer
	{
	public:
		         VertexBuffer();
		virtual ~VertexBuffer();

		virtual void					Bind(Command& cmd, int slot);
		virtual void*					Map();
		virtual void					Unmap();

	}; // class VertexBuffer 

	//! �C���f�b�N�X�o�b�t�@. 
	class IndexBuffer : public Buffer
	{
	public:
		         IndexBuffer();
		virtual ~IndexBuffer();

		virtual void					Bind(Command& cmd, int slot);
		virtual void*					Map();
		virtual void					Unmap();

	}; // class IndexBuffer 

	//! �R���X�^���g�o�b�t�@. 
	class ConstantBuffer : public Buffer
	{
	public:
		         ConstantBuffer();
		virtual ~ConstantBuffer();

		virtual void					Bind(Command& cmd, int slot);
		virtual void*					Map();
		virtual void					Unmap();

	}; // class ConstantBuffer 

	//! �e�N�X�`�����. 
	class Texture
	{
	public:
		         Texture();
		virtual ~Texture();

		virtual void					Bind(Command& cmd, int slot)=0;
		virtual void*					Map() = 0;
		virtual void					Unmap() = 0;

	}; // class Texture 

	//! 2D�e�N�X�`��. 
	class Texture2D : public Texture
	{
		friend class Device;
	private:
		ID3D11Texture2D*				m_texture;
		ID3D11ShaderResourceView*		m_srv;
		ID3D11RenderTargetView*			m_rtv;
		ID3D11UnorderedAccessView*		m_uav;
	public:
		         Texture2D();
		virtual ~Texture2D();

		virtual void					Bind(Command& cmd, int slot)=0;
		virtual void*					Map();
		virtual void					Unmap();

	}; // class Texture2D 

	//! �L���[�u�}�b�v. 
	class TextureCube : public Texture
	{
	private:

	public:
		         TextureCube();
		virtual ~TextureCube();

		virtual void					Bind(Command& cmd, int slot)=0;
		virtual void*					Map();
		virtual void					Unmap();

	}; // class TextureCube 

	//! �V�F�[�_���. 
	class Shader
	{
	public:
		         Shader();
		virtual ~Shader();

		virtual void					Bind(Command& cmd, int slot)=0;

	}; // class Shader 

	//! VS-PS�V�F�[�_. 
	class ShaderVSPS : public Shader
	{
		friend class Device;
	private:
		ID3D11VertexShader*				m_vertexShader;
		ID3D11PixelShader*				m_pixelShader;
		ID3D11InputLayout*				m_inputLayout;

	public:
		         ShaderVSPS();
		virtual ~ShaderVSPS();

		virtual void					Bind(Command& cmd);

	}; // class ShaderVSPS 

	//! CS�V�F�[�_. 
	class ShaderCS : public Shader
	{
		friend class Device;
	private:
		ID3D11ComputeShader*			m_computeShader;
	public:
		         ShaderCS();
		virtual ~ShaderCS();

		virtual void					Bind(Command& cmd);

	}; // class ShaderCS 

	//! �T���v��. 
	class Sampler
	{
		friend class Device;
	private:
		ID3D11SamplerState*				m_sampler;
	public:
		 Sampler();
		~Sampler();

		void							Bind(Command& cmd, int slot);

	}; // class Sampler 

	//! �O���t�B�b�N�X�f�o�C�X. 
	class Device
	{
	private:
		ID3D11Device*					m_device;
		ID3D11DeviceContext*			m_deviceContext;

	public:
		 Device();
		~Device();

		void							Initialize				(int width, int height);
		void							Terminate				();

		Command&						CommandContext			();
		void							PresentScreen			();

		Buffer*							CreateVertexBuffer		(UINT stride, UINT bufferSize, const uint8_t* img=nullptr, UINT usage=D3D11_USAGE_DEFAULT);
		Buffer*							CreateIndexBuffer		(UINT stride, UINT bufferSize, const uint8_t* img=nullptr, UINT usage=D3D11_USAGE_DEFAULT);
		Buffer*							CreateConstantBuffer	(             UINT bufferSize, const uint8_t* img=nullptr, UINT usage=D3D11_USAGE_DEFAULT);

		Shader*							CreateShaderVSPSFromFile(const WCHAR* vsFileName, const WCHAR* psFileName);
		Shader*							CreateShaderCSFromFile	(const WCHAR* csFileName);

		Texture*						CreateTexture2D			(int w, int h, const uint8_t* img);
		Texture*						CreateTextureFromFile	(const WCHAR* texFileName);

	}; // class Device 

} // namespace tgl 

