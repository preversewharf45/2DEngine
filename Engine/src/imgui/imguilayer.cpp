#include "pch.h"
#include "imguilayer.h" 

#ifdef IMGUI_ENABLED

#include <imgui.h>
#include <imgui_internal.h>

#include "graphics/window.h"

namespace prev {

	ImGuiLayer::ImGuiLayer() : Layer(IMGUI_LAYER_NAME) {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO & io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGuiStyle & style = ImGui::GetStyle();
		style.WindowRounding = 0.0f;

		ImGui::StyleColorsDark();
		InitImGui();

		ImFontConfig config;
		config.OversampleH = 3;
		config.OversampleV = 3;

		io.Fonts->AddFontFromFileTTF("res/fonts/Roboto-Regular.ttf", 15.0f, &config);
		SetupImGuiStyle(true, 1.0f);

		LOG_TRACE("ImGui Initialized");
	}

	ImGuiLayer::~ImGuiLayer() {
		DeleteImGui();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::StartFrame() {

		static bool windowMoved = false;

		Start();
		ImGui::NewFrame();

		if (ImGui::BeginMainMenuBar()) {

			if (ImGui::IsWindowHovered() || windowMoved) {
				if (ImGui::IsMouseDragging()) {
					windowMoved = true;
					ImVec2 delta = ImGui::GetMouseDragDelta();
					Window::Ref().SetPosition(Window::Ref().GetPosition() + Vec2i((int)delta.x, (int)delta.y));
				} else {
					windowMoved = false;
				}
			}

			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("Open File")) {}
				if (ImGui::MenuItem("Close Engine")) { WindowCloseEvent e; REGISTER_EVENT(e); }
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Settings")) {
				for (auto & setting : m_Settings) {
					if (ImGui::MenuItem(setting.first.c_str(), nullptr, setting.second)) {}
				}
				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

	}

	void ImGuiLayer::EndFrame() {
		ImGui::Render();
		End();
	}

	void ImGuiLayer::AddGuiFunction(GuiFunc func) {
		if (func)
			m_GuiFunctions.push_back(func);
		else {
			LOG_ERROR("Inavlid gui function");
		}
	}

	void ImGuiLayer::OnImGuiUpdate() {
		for (auto & func : m_GuiFunctions)
			func();
	}

	void ImGuiLayer::SetupImGuiStyle(bool bStyleDark_ /*= true*/, float alpha_ /*= 1.0f*/) {
		ImGuiStyle & style = ImGui::GetStyle();

		// light style from Pacome Danhiez (user itamago) https://github.com/ocornut/imgui/pull/511#issuecomment-175719267
		style.Alpha = 1.0f;
		style.FrameRounding = 3.0f;
		style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.94f);
		style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.19f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.29f, 0.48f, 0.54f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
		//style.Colors[ImGuiCol_ComboBg] = ImVec4(0.86f, 0.86f, 0.86f, 0.99f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		//style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		//style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
		//style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.25f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		//style.Colors[ImGuiCol_CloseButton] = ImVec4(0.59f, 0.59f, 0.59f, 0.50f);
		//style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		//style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.98f, 0.39f, 0.36f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0, 1.0, 0.0f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

		if (bStyleDark_) {
			for (int i = 0; i <= ImGuiCol_COUNT; i++) {
				ImVec4 & col = style.Colors[i];
				float H, S, V;
				ImGui::ColorConvertRGBtoHSV(col.x, col.y, col.z, H, S, V);

				if (S < 0.1f) {
					V = 1.0f - V;
				}
				ImGui::ColorConvertHSVtoRGB(H, S, V, col.x, col.y, col.z);
				if (col.w < 1.00f) {
					col.w *= alpha_;
				}
			}
		} else {
			for (int i = 0; i <= ImGuiCol_COUNT; i++) {
				ImVec4 & col = style.Colors[i];
				if (col.w < 1.00f) {
					col.x *= alpha_;
					col.y *= alpha_;
					col.z *= alpha_;
					col.w *= alpha_;
				}
			}
		}

	}

	bool ImGuiLayer::IsImGuiInitialized() {
		return GImGui != nullptr;
	}

}

#endif