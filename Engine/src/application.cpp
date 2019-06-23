#include "pch.h"
#include "application.h"

#include "common/log.h"

#include "graphics/window.h"
#include "graphics/graphicscontext.h"
#include "utils/input.h"

#include "graphics/renderstate.h"

#include "graphics/immediategfx.h"
#include "graphics/shadermanager.h"
#include "math/mvp.h"

#include "math/mat4.h"

#include "common/profiler.h"

#include "vm/virtualmachine.h"

#include <imgui.h>

extern unsigned int GLOBAL_DRAW_CALL_COUNT;

namespace prev {

	Application::Application() {
		Timer::FPSCounter(true);
		EventHandler::CreateInst();

		auto dis = GraphicsContext::GetDisplayModes();
		unsigned int selectedDis = 0;
		dis[selectedDis].SetWindowStyle(WindowStyle::FULLSCREEN);
		Window::CreateInst(dis[selectedDis]);
		EventHandler::Ref().RegisterEventFunction(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		Input::CreateInst();
		MVP::CreateInst();
		GraphicsContext::CreateInst(Window::Ref().GetWindowRawPointer(), Window::Ref().GetDisplayMode());
		RenderState::CreateInst();
		ShaderManager::CreateInst();
		ImmediateGFX::CreateInst();
		LayerStack::CreateInst();
		//ImGui Layer

		m_ImGuiLayer = new ImGuiLayer();

		LayerStack::Ref().PushLayer(m_ImGuiLayer);

		Profiler::CreateInst(); // Because profiler use imguilayer

		////////////////////////////////////////TESTING////////////////////////////////////////

		VirtualMachine::CreateInst();
		VirtualMachine::Ref().RunMain();

		////////////////////////////////////////TESTING////////////////////////////////////////

	}

	Application::~Application() {
		MVP::Ref().Projection().Pop();

		VirtualMachine::DestroyInst();
		Profiler::DestroyInst();
		LayerStack::DestroyInst();
		ImmediateGFX::DestroyInst();
		ShaderManager::DestroyInst();
		RenderState::DestroyInst();
		GraphicsContext::DestroyInst();
		MVP::DestroyInst();
		Input::DestroyInst();
		Window::DestroyInst();
		EventHandler::DestroyInst();
	}

	void Application::Run() {
		srand(Timer::GetTime());

		while (m_ApplicationRunning) {
			PROFILER_ROOT_BEGIN;

			Timer::Update();

			GraphicsContext::Ref().BeginFrame();
			LayerStack::Ref().GetImGuiLayer()->StartFrame();

			LayerStack::Ref().OnUpdate();

			////////////////////////////////////////TESTING////////////////////////////////////////

			VirtualMachine::Ref().Update();
			VirtualMachine::Ref().Render();

			PROFILER_BEGIN("App::Gui");
			Gui();
			PROFILER_END("App::Gui");

			static LineGraph graph(0.0f, 30.0f);

			ImGui::Begin("Test");
			graph.DrawImGui();
			ImGui::End();

			graph.PushValue(Timer::GetDeltaTime() * 1000.0f);

			////////////////////////////////////////TESTING////////////////////////////////////////

			LayerStack::Ref().GetImGuiLayer()->EndFrame();
			GraphicsContext::Ref().EndFrame();

			Window::Ref().PollEvents();
			Input::Ref().Update();
			EventHandler::Ref().FlushEventQueue();

			PROFILER_ROOT_END;
		}
	}

	void Application::Gui() {
		LayerStack::Ref().OnImGuiUpdate();
	}

	void Application::OnEvent(Event & e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::WindowClosed));

		LayerStack::Ref().OnEvent(e);
	}

	bool Application::WindowClosed(WindowCloseEvent & e) {
		m_ApplicationRunning = false;
		return true;
	}

}