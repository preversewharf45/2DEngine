#pragma once

#include "utils/layerstack.h"
#include "imgui/imguilayer.h"

namespace prev {

	class Application : public Singleton<Application> {
		friend class Singleton<Application>;
	private:
		Application();
		~Application();
	public:
		void Run();
	private:
		void Gui();
	private:
		void OnEvent(Event & e);
		bool WindowClosed(WindowCloseEvent & e);
		bool WindowResized(WindowResizeEvent & e);
	private:
		ImGuiLayer * m_ImGuiLayer = nullptr;
		bool m_ApplicationRunning = true;
		bool m_IsWindowReiszed = false;
	};

}