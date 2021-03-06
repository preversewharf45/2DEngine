#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include "graphics/window.h"

#include "math/vecconversion.h"

namespace prev {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const DisplayMode & displayMode);
		~WindowsWindow();

		// Inherited via Window
		virtual void PollEvents() override;
		virtual void SetPosition(Vec2i pos) override;
		virtual void SetWindowSize(Vec2i size) override;
		virtual uintptr_t GetWindowRawPointer() { return (uintptr_t)(void *)m_HWnd; }
		virtual Vec2i GetPosition() override { return m_DisplayPos; }
	private:
		bool RegisterWindowClass(const DisplayMode & displayMode);
		bool CreateWindowsWindow(const DisplayMode & displayMode);
		bool RegisterRawInput();

		void OnEvent(Event & event);

		bool WindowResized(WindowResizeEvent & e);
		bool WindowMoved(WindowMoveEvent & e);
	private:
		HWND m_HWnd					= nullptr;
		HINSTANCE m_HInst			= nullptr;
		UINT m_WindowClassStyle		= 0u;
		DWORD m_WindowStyle			= 0u;
		DWORD m_WindowExStyle		= 0u;
		MSG m_Message				= {};

		Vec2i m_DisplaySize = Vec2i(0u, 0u); //Monitor native resolution
		Vec2i m_DisplayPos  = Vec2i(0u, 0u);
	};

}