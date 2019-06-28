#include "pch.h"
#include "particlerenderer.h"
#include "graphics/renderstate.h"

namespace prev {

	ParticleRenderer::ParticleRenderer() {
		if (!SpriteRenderer::InstExists())
			SpriteRenderer::CreateInst();

		m_PixelShader = ShaderManager::Ref().LoadPixelShaderFromFile("PARTICLE_DEFAULT_PIXEL", "res/shaders/particleDefaultPixel.hlsl");

		m_DrawGroupIndex = SpriteRenderer::Ref().AddEmptyDrawGroup();
		SpriteRenderer::Ref().SetPixelShader(m_PixelShader, m_DrawGroupIndex);
	}

	ParticleRenderer::~ParticleRenderer() {

	}

	void ParticleRenderer::Render(const ParticleSystem & particleSystem) {
		for (auto & part : particleSystem.m_Particles) {
			Sprite sprite;
			sprite.Position = part.Position;
			sprite.Dimension = Vec2(part.Scale);
			sprite.Color = SpriteColor(part.Color);
			SpriteRenderer::Ref().Submit(sprite, m_DrawGroupIndex);
		}

		BlendFunction bf;
		bf.SrcBlend = PV_BLEND_SRC_ALPHA;
		bf.DestBlend = PV_BLEND_ONE;
		bf.Operation = PV_BLEND_OP_ADD;

		BlendFunction pbf = RenderState::Ref().GetBlendFunction();
		RenderState::Ref().SetBlendFunction(bf);
		SpriteRenderer::Ref().Render(m_DrawGroupIndex);
		RenderState::Ref().SetBlendFunction(pbf);
	}

}