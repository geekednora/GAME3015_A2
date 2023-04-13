/*
* Name: Gastello, Andrii
* Date: 01.28.2023
* Last Modified: 04.10.2023
*/
#include "World.hpp"
#include "StateStack.h"
#include "TitleState.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PauseState.h"

class Game : public D3DApp
{
public:
	Game(HINSTANCE hInstance);
	Game(const Game& rhs) = delete;
	Game& operator=(const Game& rhs) = delete;
	~Game() override;

	void PushCurrentRenderState(States::ID id);
	void PopCurrentRenderState();
	std::vector<States::ID> GetCurrentState();
	bool Initialize() override;

private:
	void OnResize() override;
	void Update(const GameTimer& gt) override;
	void Draw(const GameTimer& gt) override;

	void OnMouseDown(WPARAM btnState, int x, int y) override;
	void OnMouseUp(WPARAM btnState, int x, int y) override;
	void OnMouseMove(WPARAM btnState, int x, int y) override;

	void OnKeyboardInput(const GameTimer& gt);
	void UpdateCamera(const GameTimer& gt);
	void AnimateMaterials(const GameTimer& gt);
	void UpdateObjectCBs(const GameTimer& gt);
	void UpdateMaterialCBs(const GameTimer& gt);
	void UpdateMainPassCB(const GameTimer& gt);

	// States
	void registerStates();

	//step5
	void LoadTextures();
	void CreateTexture(std::string Name, std::wstring PathName);

	void BuildRootSignature();

	//step9
	void BuildDescriptorHeaps();

	void BuildShadersAndInputLayout();
	void BuildShapeGeometry();
	void BuildPSOs();
	void BuildFrameResources();
	void BuildMaterials();
	void CreateMaterials(std::string Name, XMFLOAT4 DiffuseAlbedo, XMFLOAT3 Fresnel, float Roughness);
	void BuildRenderItems();
	void DrawRenderItems(ID3D12GraphicsCommandList* cmdList, const std::vector<RenderItem*>& ritems);

	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();

private:
	std::vector<std::unique_ptr<FrameResource>> mFrameResources;
	FrameResource* mCurrFrameResource = nullptr;
	int mCurrFrameResourceIndex = 0;

	UINT mCbvSrvDescriptorSize = 0;

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;

	//step11
	ComPtr<ID3D12DescriptorHeap> mSrvDescriptorHeap = nullptr;

	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>> mGeometries;
	std::unordered_map<std::string, std::unique_ptr<Material>> mMaterials;

	//step7
	std::unordered_map<std::string, std::unique_ptr<Texture>> mTextures;

	std::unordered_map<std::string, ComPtr<ID3DBlob>> mShaders;

	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	ComPtr<ID3D12PipelineState> mOpaquePSO = nullptr;

	// List of all the render items.
	std::vector<std::unique_ptr<RenderItem>> mAllRitems;

	// Render items divided by PSO.
	std::vector<RenderItem*> mOpaqueRitems;

	PassConstants mMainPassCB;

	//XMFLOAT3 mEyePos = { 0.0f, 0.0f, -10.0f };
	//XMFLOAT4X4 mView = MathHelper::Identity4x4();
	//XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	//float mTheta = 1.3f * XM_PI;
	//float mPhi = 0.4f * XM_PI;
	//float mRadius = 2.5f;

	POINT mLastMousePos;
	Camera mCamera;


	// States
	StateStack mStateStack;
	std::vector<States::ID> currentStates;

public:
	std::vector<std::unique_ptr<RenderItem>>& getRenderItems() { return mAllRitems; }
	std::unordered_map<std::string, std::unique_ptr<Material>>& getMaterials() { return mMaterials; }
	std::unordered_map<std::string, std::unique_ptr<MeshGeometry>>& getGeometries() { return mGeometries; }
};
