#pragma once

namespace prev {

	enum LayoutDataType {
		PV_DATA_TYPE_FLOAT_32,
		PV_DATA_TYPE_FLOAT_16,

		PV_DATA_TYPE_SINT_32,
		PV_DATA_TYPE_SINT_16,
		PV_DATA_TYPE_SINT_8,

		PV_DATA_TYPE_UINT_32,
		PV_DATA_TYPE_UINT_16,
		PV_DATA_TYPE_UINT_8,
	};

	enum TextureFormat {
		PV_TEXTURE_FORMAT_RGBA8,
	};

	enum TextureWrapType {
		PV_TEXTURE_WRAP_DEFAULT
	};

	enum TextureFilterType {
		PV_TEXTURE_FILTER_DEFAULT,
		PV_TEXTURE_FILTER_NEAREST
	};

	enum BlendOption {
		PV_BLEND_ZERO,
		PV_BLEND_ONE,
		PV_BLEND_SRC_ALPHA,
		PV_BLEND_INV_SRC_ALPHA,
		PV_BLEND_DEST_ALPHA,
		PV_BLEND_INV_DEST_ALPHA
	};

	enum BlendOperation {
		PV_BLEND_OP_ADD,
		PV_BLEND_OP_SUBTRACT,
		PV_BLEND_OP_REV_SUBTRACT,
		PV_BLEND_OP_MIN,
		PV_BLEND_OP_MAX
	};

	struct BlendFunction {
		BlendOption SrcBlend;
		BlendOption DestBlend;
		BlendOperation Operation;
	};

}
