#pragma once

#include <d3dcompiler.h>
#include <dxgi.h>

#include "d3dcontext.h"

#include "graphics/datatypes.h"

#define LOG_ON_CONDITION(x, l, m, ...) { if (!(x)) { l(m); __VA_ARGS__; } }

namespace prev {

	ID3D11Device * GetDevice();
	ID3D11DeviceContext * GetDeviceContext();
	DXGI_FORMAT GetTextureFormat(TextureFormat texFormat);
	TextureFormat GetTextureFormat(DXGI_FORMAT texFormat);

}
