#pragma once

namespace prev {

	enum BindableType {
		VERTEX_BUFFER,
		VERTEX_SHADER,
		PIXEL_SHADER,
		UNIFORM,
		VERTEX_LAYOUT, //INPUT_LAYOUT
		TEXTURE_2D,
		SHADER_PROGRAM
	};

	class Bindable {
	public:
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual BindableType GetType() const = 0;
	};

}
