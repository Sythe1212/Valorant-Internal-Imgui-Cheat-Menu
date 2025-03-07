#include "Visuals.h"

uintptr_t shader;

namespace ImGui
{
	IMGUI_API bool Tab(unsigned int index, const char* label, int* selected, float width = 0)
	{
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4 color = style.Colors[ImGuiCol_Button];
		ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];

		if (index > 0)
			ImGui::SameLine();

		if (index == *selected)
		{
			style.Colors[ImGuiCol_Button] = colorActive;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorActive;
		}
		else
		{
			style.Colors[ImGuiCol_Button] = color;
			style.Colors[ImGuiCol_ButtonActive] = colorActive;
			style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		}

		if (ImGui::Button(label, ImVec2(width, 30)))
			*selected = index;

		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;

		return *selected == index;
	}
}

float ImGuiWidth = 400.f;
float ImGuiHight = 400.f;

void Visuals::DrawMenu()
{

	if (features::Menu)
	{
		ImGui::Begin("naivecheats.com " "[" __DATE__ "]");
		ImGui::SetWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHight));

		if (ImGui::CollapsingHeader(("Player ESP")))
		{
			ImGui::Checkbox("Player Box", &features::Visuals::ShowPlayerBox);
			//ImGui::Spacing();					
			ImGui::Checkbox("Corner Box", &features::Visuals::ShowPlayerCornerBox);
			//ImGui::Spacing();
			ImGui::Checkbox("Name", &features::Visuals::ShowPlayerName);
			//ImGui::Spacing();
			ImGui::Checkbox("Distance", &features::Visuals::ShowPlayerDistance); // - will fix later on ( johnn )
			//ImGui::Spacing();
			ImGui::Checkbox("Health Bar", &features::Visuals::HealthBarESP);
			//ImGui::Spacing();
			ImGui::Checkbox("Health (HP)", &features::Visuals::ShowPlayerHP); // -broke
		}

		if (ImGui::CollapsingHeader("AI ESP")) {
			//ImGui::Checkbox("Scientists", &features::Visuals_AI::ScientistESP);
			//ImGui::Spacing();
			ImGui::Checkbox("Bradley", &features::Visuals_AI::BradleyESP);
			//ImGui::Spacing();
			ImGui::Checkbox("Patrol Helicopter", &features::Visuals_AI::PatrolHelicopterESP);
			//ImGui::Spacing();
		}
		if (ImGui::CollapsingHeader("Ore ESP")) {
			ImGui::Checkbox("Stone Ore", &features::Visuals_Ores::StoneOre);
			//ImGui::Spacing();
			ImGui::Checkbox("Metal Ore", &features::Visuals_Ores::MetalOre);
			//ImGui::Spacing();
			ImGui::Checkbox("Sulfur Ore", &features::Visuals_Ores::SulfurOre);
			//ImGui::Spacing();
		}
		if (ImGui::CollapsingHeader("Collectable ESP")) {
			ImGui::Checkbox("Hemp", &features::Visuals_Collectables::HempESP);
			//ImGui::Spacing();
			ImGui::Checkbox("Mushroom", &features::Visuals_Collectables::MushroomESP);
			//ImGui::Spacing();
		}
		if (ImGui::CollapsingHeader("Other ESP")) {
			ImGui::Checkbox("Barrels", &features::Visuals_Collectables::LootBarrel);
			//ImGui::Spacing();
		}



		/* TODO List:
		- make esp box for bradley APC + hp
		- make scientist esp with box around it like players
		- make box for patrol helicopter AND health display
		*/


		//ImGui::Checkbox("Skeleton", &features::Visuals::SkeletonESP);
		ImGui::Checkbox("NoRecoil", &features::aimbot::NoRecoil);

		ImGui::SliderFloat("FOV", &features::exploits::SexyFuckingFovValue, 30.f, 150.f);

		



		ImGui::End();
	}
}
bool mfound = false;

void FindMatrix(HMODULE mxdle) {
	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVAA((DWORD64)g_Scanner->FindPattern(mxdle, "\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx"), 7); //UnityPlayer.dll

	DWORD64 ObjMgr = readnew<uintptr_t>((uintptr_t)dwGameObjectManager);
	if (!ObjMgr) return;
	UINT64 end = readnew<uintptr_t>((uintptr_t)ObjMgr);
	for (UINT64 Obj = readnew<uintptr_t>((uintptr_t)ObjMgr + 0x8); (Obj && (Obj != end)); Obj = readnew<uintptr_t>((uintptr_t)Obj + 0x8))
	{
		UINT64 GameObject = readnew<uintptr_t>((uintptr_t)Obj + 0x10);
		WORD Tag = readnew<uintptr_t>((uintptr_t)GameObject + 0x54);
		if (Tag == 5)
		{
			UINT64 ObjClass = readnew<uintptr_t>((uintptr_t)GameObject + 0x30);
			UINT64	Entity = readnew<uintptr_t>((uintptr_t)ObjClass + 0x18);
			LxcalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0xDC); //0x2e4 | Matrix
			mfound = true;
			return;
		}
	}
}



inline void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color)
{
	VisualHelper::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f, Entity_y }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f, Entity_y }, color);
	VisualHelper::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 3.5f, Entity_y }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 3.5f }, color);

	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y }, color);
	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 3.5f }, color);

	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 3.5f, Entity_y + Entity_h }, color);
	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 3.5f }, color);

	VisualHelper::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f, Entity_y + Entity_h }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 3.5f, Entity_y + Entity_h }, color);
	VisualHelper::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, D2D1::ColorF::White, 3.f);
	VisualHelper::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 3.5f }, color);
}

/*Skeleton Esp (Broken)*/
inline void iHateBlacksESP(LocalPlayer* BasePlayer)
{
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos

	for (int j = 0; j < 15; j++) {
		if (!LxcalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
		if ((int)BasePlayer->GetHealth() > 0)
		{
			if (LxcalPlayer.lclPlayer->IsTeamMate(BasePlayer->GetSteamID()))
			{
				for (int j = 0; j < 15; j += 3) {
					VisualHelper::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::LimeGreen, 0.5f);
					VisualHelper::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::LimeGreen);
					VisualHelper::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::LimeGreen, 0.5f);
					VisualHelper::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::LimeGreen);
				}

				//draw add lines
				VisualHelper::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen);
				VisualHelper::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::LimeGreen);
				VisualHelper::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen);
				VisualHelper::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::LimeGreen);
			}
			else
			{
				for (int j = 0; j < 15; j += 3) {
					VisualHelper::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::White, 0.5f);
					VisualHelper::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::White);
					VisualHelper::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::White, 0.5f);
					VisualHelper::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::White);
				}

				//draw add lines
				VisualHelper::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White);
				VisualHelper::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::White);
				VisualHelper::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White);
				VisualHelper::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::White);
			}
		}
		else
		{
			for (int j = 0; j < 15; j += 3) {
				VisualHelper::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Red, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Red);
				VisualHelper::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Red, 0.5f);
				VisualHelper::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Red);
			}

			//draw add lines
			VisualHelper::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red, 0.5f);
			VisualHelper::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red);
			VisualHelper::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red, 0.5f);
			VisualHelper::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Red);
			VisualHelper::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red, 0.5f);
			VisualHelper::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red);
			VisualHelper::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red, 0.5f);
			VisualHelper::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Red);
		}
	}
}



    /* Start The ESP Rendering  (johnn) */
	void Visuals::Entity()
	{
		bool LocalPlayerValid = false;
		DWORD64 BaseNetworkable;
		LocalPlayer* AimPlayer = nullptr;
		LocalPlayer* BP;
		LocalPlayer* LP;
		float FOV = features::FOV, CurFOV;
		int CurPos = 0;
		if (isSteam == -1) BaseNetworkable = readnew<uintptr_t>((uintptr_t)GetModBase((L"GameAssembly.dll")) + g_BN); /* BaseNetworkable */ /* in Script -> BaseNetworkable_TypeInfo. */
		else BaseNetworkable = readnew<uintptr_t>((uintptr_t)GetModBase((L"GameAssembly.dll")) + g_BN_Steam); /* BaseNetworkable */
		DWORD64 EntityRealm = readnew<uintptr_t>((uintptr_t)BaseNetworkable + 0xB8);
		DWORD64 ClientEntities = readnew<uintptr_t>((uintptr_t)EntityRealm);
		DWORD64 ClientEntities_list = readnew<uintptr_t>((uintptr_t)ClientEntities + 0x10);
		DWORD64 ClientEntities_values = readnew<uintptr_t>((uintptr_t)ClientEntities_list + 0x28);
		if (!ClientEntities_values) return;
		int EntityCount = readnew<uintptr_t>((uintptr_t)ClientEntities_values + 0x10);
		DWORD64 EntityBuffer = readnew<uintptr_t>((uintptr_t)ClientEntities_values + 0x18);

		auto unityplayer = GetModuleHandle(L"UnityPlayer.dll");

		if (!LxcalPlayer.pViewMatrix || !mfound)
		{
			FindMatrix(unityplayer);
		}

		for (int i = 0; i <= EntityCount; i++)
		{
			DWORD64 Entity = readnew<uintptr_t>((uintptr_t)EntityBuffer + 0x20 + (i * 0x8));
			if (Entity <= 100000) continue;
			DWORD64 Object = readnew<uintptr_t>((uintptr_t)Entity + 0x10);
			if (Object <= 100000) continue;
			DWORD64 ObjectClass = readnew<uintptr_t>((uintptr_t)Object + 0x30);
			if (ObjectClass <= 100000) continue;
			pUncStr name = readnew<pUncStr>((uintptr_t)ObjectClass + 0x60);
			if (!name) continue;
			char* buff = name->stub;
			if (strstr(buff, ("Local"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);                                             /* offset = playermodel */
				if (!readnew<uintptr_t>((uintptr_t)Player + 0x50) || readnew<uintptr_t>((uintptr_t)Player + 0x18) || !readnew<uintptr_t>((uintptr_t)Player + 0x4A8)) continue;
				if (Player != LxcalPlayer.lclPlayer) {
					mfound = false;
				}
				Vector3 pos = Player->GetPosition();
				LxcalPlayer.lclPlayer = Player;
			}


			if (features::Visuals_AI::BradleyESP && strstr(buff, ("bradleyapc"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {
					wchar_t res[256]; //90
					swprintf(res, L"Bradley");
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Red, true);
				}
			}

			if (features::Visuals_AI::PatrolHelicopterESP && strstr(buff, ("assets/prefabs/npc/patrol helicopter/patrolhelicopter.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64);
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				uintptr_t BaseObject = unsafe_read(Object + 0x30, uintptr_t);
				uintptr_t BaseEntity = unsafe_read(BaseObject + 0x18, uintptr_t);
				uintptr_t BaseHelicopter = unsafe_read(BaseEntity + 0x28, uintptr_t);
				Vector2 Pos;
				int health = (int)ceil(unsafe_read(BaseHelicopter + 0x20C, float));

				if (LxcalPlayer.WorldToScreen(pos, Pos)) {
					wchar_t res[256]; //90
					//_swprintf(res, L"Patrol Helicopter");
					swprintf(res, L"Helicopter [%dHP] [%dm]", health, (int)Math::Calc3D_Dist(Player->GetBoneByID(head), pos));
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Red, true);
				}
			}




			if (features::Visuals_Collectables::LootBarrel && strstr(buff, ("loot-barrel-2.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {


					wchar_t res[256];//90
					swprintf(res, L"Barrel");
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Yellow, true);
				}
			}

			if (features::Visuals_Collectables::LootBarrel && strstr(buff, ("loot-barrel-1.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {


					wchar_t res[256];
					swprintf(res, L"Barrel");
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Yellow, true);
				}
			}


			if (features::Visuals_Collectables::MushroomESP && strstr(buff, ("mushroom-cluster-5.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {


					wchar_t res[256];
					swprintf(res, L"Mushroom");
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Yellow, true);
				}
			}


			if (features::Visuals_Collectables::HempESP && strstr(buff, ("hemp-collectable.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);                                              /* offset = playermodel */

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {
					wchar_t res[256];
					swprintf(res, L"Hemp");
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Lime, true);
				}
			}

			if (features::Visuals_Ores::StoneOre && strstr(buff, ("stone-ore.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);                                              /* offset = playermodel */

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {
					wchar_t res[256];
					//_swprintf(res, L"Stone Ore [%d m]", (int)Math::Calc3D_Dist(Player->GetBoneByID(r_foot), pos)); // fix this fucking shit later (distance)
					_swprintf(res, L"Stone-Ore [%dm]", (int)Math::Calc3D_Dist(LxcalPlayer.lclPlayer->GetBoneByID(r_foot), pos));
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::RosyBrown, true);
				}
			}

			if (features::Visuals_Ores::MetalOre && strstr(buff, ("metal-ore.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {
					wchar_t res[256];
					//_swprintf(res, L"Stone Ore [%d m]", (int)Math::Calc3D_Dist(Player->GetBoneByID(r_foot), pos)); // fix this fucking shit later (distance)
					swprintf(res, L"Metal-Ore [%dm]", (int)Math::Calc3D_Dist(LxcalPlayer.lclPlayer->GetBoneByID(r_foot), pos));
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Gray, true);
				}
			}

			if (features::Visuals_Ores::SulfurOre && strstr(buff, ("sulfur-ore.prefab"))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;
				if (LxcalPlayer.WorldToScreen(pos, Pos)) {
					wchar_t res[256];
					//_swprintf(res, L"Stone Ore [%d m]", (int)Math::Calc3D_Dist(Player->GetBoneByID(r_foot), pos)); // fix this fucking shit later (distance)
					swprintf(res, L"Sulfur-Ore [%dm]", (int)Math::Calc3D_Dist(LxcalPlayer.lclPlayer->GetBoneByID(r_foot), pos));
					VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, res, false, D2D1::ColorF::Gold, true);
				}
			}

			/*if (features::Visuals::ShowPlayerDistance)
			{
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);

				DWORD64 Res = unsafe_read(Object + 0x28, DWORD64);
				DWORD64 gameObject = unsafe_read(ObjectClass + 0x30, DWORD64); //Tag 449
				DWORD64 Trans = unsafe_read(gameObject + 0x8, DWORD64);
				DWORD64 Vec = unsafe_read(Trans + 0x38, DWORD64);
				Vector3 pos = unsafe_read(Vec + 0x90, Vector3); ///public Vector3 PointEnd
				Vector2 Pos;

				Vector2 tempHead;
				Vector2 screenPos;


				Vector3 position = Player->GetPosition();
				Vector2 tempFeetR, tempFeetL;
				Vector3 ro = Player->GetBoneByID(r_foot);

				Vector2 leftTopCorner = tempHead - Vector2(0.4f, 0.f);
				Vector2 rightBottomCorner = tempFeetR;

				Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
				float Entity_h = tempHead.y - tempFeet.y;
				float w = Entity_h / 4;
				float Entity_x = tempFeet.x - w;
				float Entity_y = tempFeet.y;
				float Entity_w = Entity_h / 2;


				wchar_t buffer[0x100];
				//_swprintf(buffer, L"[%d m]", (Player->GetBoneByID(r_foot).midPoint(Player->GetBoneByID(l_foot)), pos));
				swprintf(buffer, L"[%d m]", (int)ceil(Player->GetPosition().distance(Player->GetBoneByID(l_foot))));
				VisualHelper::Render.RenderString(Vector2{ Pos.x - 0.f, Pos.y - 0.f }, buffer, false, D2D1::ColorF::Gold, true);
				//VisualHelper::Render.RenderString(Vector2{ Entity_x - 7.f, Entity_y - 0.f }, buffer, false, D2D1::ColorF::Yellow, true);
			}*/

			/*Vector3 GetPosition()
			{
				return GetBoneById(r_foot).midPoint(GetBonePos(l_foot));
			}*/

			if (features::Visuals::Player && (strstr(buff, ("player.prefab")) || strstr(buff, ("playermodel")))) {
				LocalPlayer* Player = (LocalPlayer*)readnew<uintptr_t>((uintptr_t)Object + 0x28);                                              /* offset = playermodel */
				if (!readnew<uintptr_t>((uintptr_t)Player + 0x50) || readnew<uintptr_t>((uintptr_t)Player + 0x18) || !readnew<uintptr_t>((uintptr_t)Player + 0x4A8)) continue;



				Vector3 pos = Player->GetPosition();
				Vector2 tempFeetR, tempFeetL;
				Vector3 ro = Player->GetBoneByID(r_foot);
				if (ro.x == 0 && ro.y == 0 && ro.z == 0) return;
				if (LxcalPlayer.WorldToScreen(ro, tempFeetR) && LxcalPlayer.WorldToScreen(Player->GetBoneByID(l_foot), tempFeetL))
				{
					Vector2 tempHead;
					if (LxcalPlayer.WorldToScreen(Player->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead))
					{
						Vector2 leftTopCorner = tempHead - Vector2(0.4f, 0.f);
						Vector2 rightBottomCorner = tempFeetR;

						Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
						float Entity_h = tempHead.y - tempFeet.y;
						float w = Entity_h / 4;
						float Entity_x = tempFeet.x - w;
						float Entity_y = tempFeet.y;
						float Entity_w = Entity_h / 2;

						if (features::Visuals::ShowPlayerBox) {
							VisualHelper::Render.Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, { 0.f, 0.f, 0.f, 255.f }, 3.f);
							VisualHelper::Render.Rectangle(Vector2{ Entity_x, Entity_y }, Vector2{ Entity_w, Entity_h }, D2D1::ColorF::YellowGreen);

						}

						if (features::Visuals::HealthBarESP)
						{
							int health = (int)Player->GetHealth();
							float maxhealth = 100.f;
							if ((int)Player->GetHealth() <= 33)
							{
								VisualHelper::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxhealth) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
							}
							if ((int)Player->GetHealth() >= 34 && (int)Player->GetHealth() <= 66)
							{
								VisualHelper::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxhealth) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
							}
							if ((int)Player->GetHealth() >= 67)
							{
								VisualHelper::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxhealth) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
							}
							VisualHelper::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}

						/*if (features::Visuals::ShowPlayerName || features::Visuals::ShowPlayerDistance) {
							wchar_t res[90];
							swprintf(res, L"%s", Player->GetName());

							VisualHelper::Render.RenderString(Vector2{ Entity_x - 7.f, Entity_y - 0.f }, res, false, D2D1::ColorF::Red, true);
						}*/

						if (features::Visuals::ShowPlayerName || features::Visuals::ShowPlayerDistance)
						{
							wchar_t ress[64];
							if (wcslen(Player->GetName()) > 0)
							{

								if (features::Visuals::ShowPlayerDistance)
								{
									_swprintf(ress, L"[%dm]", (int)Math::Calc3D_Dist(Player->GetBoneByID(head), Player->GetBoneByID(r_foot)));
								}
								else
								{
									_swprintf(ress, L"[%s]", Player->GetName());
								}
								VisualHelper::Render.String(Vector2{ Entity_x + Entity_w, Entity_y + Entity_h - 20.f }, ress, D2D1::ColorF(features::ColorsNShit::playercolors[0], features::ColorsNShit::playercolors[1], features::ColorsNShit::playercolors[2], features::ColorsNShit::playercolors[3]));
							}
						}


						/*if (features::Visuals::ShowPlayerHP) {
					
							//wchar_t res[100];
							if (wcslen(Player->GetName()) > 0) {
								wchar_t res[100];

								float hp = readnew<float>((uintptr_t)this + 0x20C);

								if (features::Visuals::ShowPlayerHP) {
									swprintf(res, L"%d HP", hp); // Fix this fucking shit later on - specific
								}
								VisualHelper::Render.RenderString(Vector2{ Entity_x - 7.f, Entity_y - 0.f }, res, false, D2D1::ColorF::Yellow, true);
							}
						}*/

						if (features::Visuals::ShowPlayerCornerBox)
						{
							if ((int)Player->GetHealth() > 0)
							{
								if (LxcalPlayer.lclPlayer->IsTeamMate(Player->GetSteamID()))
								{
									CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::LimeGreen);
								}
								else
								{
									CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::White);
								}
							}
							else
							{
								CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, D2D1::ColorF::Red);
							}
						}
						}
					}
				}
			}






		}
		