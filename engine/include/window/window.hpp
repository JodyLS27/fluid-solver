#pragma once
#include <iostream>

namespace engine
{
	class Window
	{
	public:
		/**
		* Initialize a GLFW window
		**/
		void init();

	private:
		// Settings
		const int m_screen_width = 800;
		const int m_screen_height = 600;
	};
}
