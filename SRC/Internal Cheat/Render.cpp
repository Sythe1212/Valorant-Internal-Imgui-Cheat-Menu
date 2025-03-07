#include "Render.h"

HWND hWnd;

HRESULT(WINAPI* PresentOriginal)(IDXGISwapChain*, UINT, UINT) = NULL;
HRESULT(WINAPI* ResizeBuffersOriginal)(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) = NULL;

ID3D11Device* device;
ID3D11DeviceContext* deviceContext = NULL;
ID3D11RenderTargetView* renderTargetView = NULL;
static IDXGISwapChain* g_pSwapChain;
WNDPROC WndProc;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK hkWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (msg == WM_KEYUP &&
		(wparam == VK_INSERT ||
			(features::Menu && wparam == VK_ESCAPE))
		) {
		features::Menu = !features::Menu;
		ImGui::GetIO().MouseDrawCursor = features::Menu;

	}

	if (features::Menu) {
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
		return TRUE;
	}

	return CallWindowProcW(WndProc, hwnd, msg, wparam, lparam);
}

HRESULT Present(IDXGISwapChain* swapChain, UINT buffer, UINT syncInterval) {

	if (!device) {

		swapChain->GetDevice(__uuidof(device), (VOID**)(&device));
		device->GetImmediateContext(&deviceContext);

		ID3D11Texture2D* renderTarget = NULL;
		swapChain->GetBuffer(0, __uuidof(renderTarget), (VOID**)(&renderTarget));
		device->CreateRenderTargetView(renderTarget, NULL, &renderTargetView);
		renderTarget->Release();

		ID3D11Texture2D* backBuffer = 0;
		swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (VOID**)&backBuffer);
		D3D11_TEXTURE2D_DESC desc = { 0 };
		backBuffer->GetDesc(&desc);


		DXGI_SWAP_CHAIN_DESC Window;
		swapChain->GetDesc(&Window);

		hWnd = Window.OutputWindow;

		width = (float)desc.Width;
		height = (float)desc.Height;
		backBuffer->Release();
		WndProc = (WNDPROC)SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)hkWndProc);

		ImGui::GetIO().Fonts->AddFontFromFileTTF("arial.ttf", 16);

		ImGui_ImplDX11_Init(hWnd, device, deviceContext);
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	if (renderTargetView)
	{
		deviceContext->OMSetRenderTargets(1, &renderTargetView, NULL);
		ImGui_ImplDX11_NewFrame();


		/* Crosshair */
		//ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2 - 12, height / 2), ImVec2(width / 2 - 2, height / 2), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 1.0f);
		//ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2 + 13, height / 2), ImVec2(width / 2 + 3, height / 2), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 1.0f);
		//ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2, height / 2 - 12), ImVec2(width / 2, height / 2 - 2), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 1.0f);
		//ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2, height / 2 + 13), ImVec2(width / 2, height / 2 + 3), ImGui::GetColorU32({ 1.f, 1.f, 1.f, 1.f }), 1.0f);
		


		//ImGui::GetOverlayDrawList()->AddCircle(ImVec2(width / 2, height / 2), 30.f, ImGui::GetColorU32({ 255.0f, 255.0f, 255.0f, 1.0f }), 64);



		g_Visuals->DrawMenu(); // change up later on - johnn

		g_Fucker->WeaponPatchh(); // fixed it - johnn

		g_Fucker->MiscOptionssV2(); // fixed it - johnn

		if (VisualHelper::Render.NewFrame(swapChain)) {

			if (features::aimbot::EnableAimbot) {
				float xs = width / 2, ys = height / 2;
				VisualHelper::Render.Circle(Vector2{ xs, ys }, D2D1::ColorF::Black, features::FOV, 1.f); /* fov circle - johnn ( change this a little bit ) */
				VisualHelper::Render.Circle(Vector2{ xs, ys }, D2D1::ColorF::White, features::FOV);
			}

			g_Visuals->Entity();

			VisualHelper::Render.EndFrame();
		}

		ImGui::Render();
	}

	return PresentOriginal(swapChain, buffer, syncInterval);
}

HRESULT ResizeBuffers(IDXGISwapChain* SwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	renderTargetView = nullptr;

	deviceContext->Release();
	deviceContext = nullptr;

	device->Release();
	device = nullptr;

	return ResizeBuffersOriginal(SwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

short render::DiscordGetAsyncKeyState(const int vKey)
{
	static PBYTE addrGetAsyncKeyState = 0;

	auto discordModuleBase = GetModuleHandleA(("DiscordHook64.dll"));

	if (!addrGetAsyncKeyState)
	{
		addrGetAsyncKeyState = g_Scanner->FindPattern(discordModuleBase, "\x56\x48\x83\xEC\x20\x89\xCE", "xxxxxxx");
	}

	if (!addrGetAsyncKeyState)
		return false;

	using GetAsyncKeyState_t = short(__fastcall*)(int);
	auto fnGetAyncKeyState = (GetAsyncKeyState_t)addrGetAsyncKeyState;

	return fnGetAyncKeyState(vKey);
}

void render::execute(HMODULE mxdule) {

	if (!mxdule) {
		return;
	}

	auto dxgi = g_Scanner->FindPattern
	(
		mxdule,
		"\x56\x57\x53\x48\x83\xEC\x30\x44\x89\xC6\x89\xD7\x48\x89\xCB\x48",
		"xxxxxxxxxxxxxxxx" 
	);

	printf("\nDiscord Present - > 0x%x", dxgi);

	MH_CreateHook(dxgi, Present, (VOID**)&PresentOriginal);
	MH_EnableHook(dxgi);

}
