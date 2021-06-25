<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// Copyright 2018 IBM Corporation

#समावेश <linux/clk.h>
#समावेश <linux/reset.h>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "aspeed_gfx.h"

अटल काष्ठा aspeed_gfx *
drm_pipe_to_aspeed_gfx(काष्ठा drm_simple_display_pipe *pipe)
अणु
	वापस container_of(pipe, काष्ठा aspeed_gfx, pipe);
पूर्ण

अटल पूर्णांक aspeed_gfx_set_pixel_fmt(काष्ठा aspeed_gfx *priv, u32 *bpp)
अणु
	काष्ठा drm_crtc *crtc = &priv->pipe.crtc;
	काष्ठा drm_device *drm = crtc->dev;
	स्थिर u32 क्रमmat = crtc->primary->state->fb->क्रमmat->क्रमmat;
	u32 ctrl1;

	ctrl1 = पढ़ोl(priv->base + CRT_CTRL1);
	ctrl1 &= ~CRT_CTRL_COLOR_MASK;

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
		dev_dbg(drm->dev, "Setting up RGB565 mode\n");
		ctrl1 |= CRT_CTRL_COLOR_RGB565;
		*bpp = 16;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		dev_dbg(drm->dev, "Setting up XRGB8888 mode\n");
		ctrl1 |= CRT_CTRL_COLOR_XRGB8888;
		*bpp = 32;
		अवरोध;
	शेष:
		dev_err(drm->dev, "Unhandled pixel format %08x\n", क्रमmat);
		वापस -EINVAL;
	पूर्ण

	ग_लिखोl(ctrl1, priv->base + CRT_CTRL1);

	वापस 0;
पूर्ण

अटल व्योम aspeed_gfx_enable_controller(काष्ठा aspeed_gfx *priv)
अणु
	u32 ctrl1 = पढ़ोl(priv->base + CRT_CTRL1);
	u32 ctrl2 = पढ़ोl(priv->base + CRT_CTRL2);

	/* Set DAC source क्रम display output to Graphics CRT (GFX) */
	regmap_update_bits(priv->scu, priv->dac_reg, BIT(16), BIT(16));

	ग_लिखोl(ctrl1 | CRT_CTRL_EN, priv->base + CRT_CTRL1);
	ग_लिखोl(ctrl2 | CRT_CTRL_DAC_EN, priv->base + CRT_CTRL2);
पूर्ण

अटल व्योम aspeed_gfx_disable_controller(काष्ठा aspeed_gfx *priv)
अणु
	u32 ctrl1 = पढ़ोl(priv->base + CRT_CTRL1);
	u32 ctrl2 = पढ़ोl(priv->base + CRT_CTRL2);

	ग_लिखोl(ctrl1 & ~CRT_CTRL_EN, priv->base + CRT_CTRL1);
	ग_लिखोl(ctrl2 & ~CRT_CTRL_DAC_EN, priv->base + CRT_CTRL2);

	regmap_update_bits(priv->scu, priv->dac_reg, BIT(16), 0);
पूर्ण

अटल व्योम aspeed_gfx_crtc_mode_set_nofb(काष्ठा aspeed_gfx *priv)
अणु
	काष्ठा drm_display_mode *m = &priv->pipe.crtc.state->adjusted_mode;
	u32 ctrl1, d_offset, t_count, bpp;
	पूर्णांक err;

	err = aspeed_gfx_set_pixel_fmt(priv, &bpp);
	अगर (err)
		वापस;

#अगर 0
	/* TODO: we have only been able to test with the 40MHz USB घड़ी. The
	 * घड़ी is fixed, so we cannot adjust it here. */
	clk_set_rate(priv->pixel_clk, m->crtc_घड़ी * 1000);
#पूर्ण_अगर

	ctrl1 = पढ़ोl(priv->base + CRT_CTRL1);
	ctrl1 &= ~(CRT_CTRL_INTERLACED |
			CRT_CTRL_HSYNC_NEGATIVE |
			CRT_CTRL_VSYNC_NEGATIVE);

	अगर (m->flags & DRM_MODE_FLAG_INTERLACE)
		ctrl1 |= CRT_CTRL_INTERLACED;

	अगर (!(m->flags & DRM_MODE_FLAG_PHSYNC))
		ctrl1 |= CRT_CTRL_HSYNC_NEGATIVE;

	अगर (!(m->flags & DRM_MODE_FLAG_PVSYNC))
		ctrl1 |= CRT_CTRL_VSYNC_NEGATIVE;

	ग_लिखोl(ctrl1, priv->base + CRT_CTRL1);

	/* Horizontal timing */
	ग_लिखोl(CRT_H_TOTAL(m->htotal - 1) | CRT_H_DE(m->hdisplay - 1),
			priv->base + CRT_HORIZ0);
	ग_लिखोl(CRT_H_RS_START(m->hsync_start - 1) | CRT_H_RS_END(m->hsync_end),
			priv->base + CRT_HORIZ1);


	/* Vertical timing */
	ग_लिखोl(CRT_V_TOTAL(m->vtotal - 1) | CRT_V_DE(m->vdisplay - 1),
			priv->base + CRT_VERT0);
	ग_लिखोl(CRT_V_RS_START(m->vsync_start) | CRT_V_RS_END(m->vsync_end),
			priv->base + CRT_VERT1);

	/*
	 * Display Offset: address dअगरference between consecutive scan lines
	 * Terminal Count: memory size of one scan line
	 */
	d_offset = m->hdisplay * bpp / 8;
	t_count = DIV_ROUND_UP(m->hdisplay * bpp, priv->scan_line_max);

	ग_लिखोl(CRT_DISP_OFFSET(d_offset) | CRT_TERM_COUNT(t_count),
			priv->base + CRT_OFFSET);

	/*
	 * Threshold: FIFO thresholds of refill and stop (16 byte chunks
	 * per line, rounded up)
	 */
	ग_लिखोl(priv->throd_val, priv->base + CRT_THROD);
पूर्ण

अटल व्योम aspeed_gfx_pipe_enable(काष्ठा drm_simple_display_pipe *pipe,
			      काष्ठा drm_crtc_state *crtc_state,
			      काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा aspeed_gfx *priv = drm_pipe_to_aspeed_gfx(pipe);
	काष्ठा drm_crtc *crtc = &pipe->crtc;

	aspeed_gfx_crtc_mode_set_nofb(priv);
	aspeed_gfx_enable_controller(priv);
	drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम aspeed_gfx_pipe_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा aspeed_gfx *priv = drm_pipe_to_aspeed_gfx(pipe);
	काष्ठा drm_crtc *crtc = &pipe->crtc;

	drm_crtc_vblank_off(crtc);
	aspeed_gfx_disable_controller(priv);
पूर्ण

अटल व्योम aspeed_gfx_pipe_update(काष्ठा drm_simple_display_pipe *pipe,
				   काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा aspeed_gfx *priv = drm_pipe_to_aspeed_gfx(pipe);
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_framebuffer *fb = pipe->plane.state->fb;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा drm_gem_cma_object *gem;

	spin_lock_irq(&crtc->dev->event_lock);
	event = crtc->state->event;
	अगर (event) अणु
		crtc->state->event = शून्य;

		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
	पूर्ण
	spin_unlock_irq(&crtc->dev->event_lock);

	अगर (!fb)
		वापस;

	gem = drm_fb_cma_get_gem_obj(fb, 0);
	अगर (!gem)
		वापस;
	ग_लिखोl(gem->paddr, priv->base + CRT_ADDR);
पूर्ण

अटल पूर्णांक aspeed_gfx_enable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा aspeed_gfx *priv = drm_pipe_to_aspeed_gfx(pipe);
	u32 reg = पढ़ोl(priv->base + CRT_CTRL1);

	/* Clear pending VBLANK IRQ */
	ग_लिखोl(reg | CRT_CTRL_VERTICAL_INTR_STS, priv->base + CRT_CTRL1);

	reg |= CRT_CTRL_VERTICAL_INTR_EN;
	ग_लिखोl(reg, priv->base + CRT_CTRL1);

	वापस 0;
पूर्ण

अटल व्योम aspeed_gfx_disable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा aspeed_gfx *priv = drm_pipe_to_aspeed_gfx(pipe);
	u32 reg = पढ़ोl(priv->base + CRT_CTRL1);

	reg &= ~CRT_CTRL_VERTICAL_INTR_EN;
	ग_लिखोl(reg, priv->base + CRT_CTRL1);

	/* Clear pending VBLANK IRQ */
	ग_लिखोl(reg | CRT_CTRL_VERTICAL_INTR_STS, priv->base + CRT_CTRL1);
पूर्ण

अटल स्थिर काष्ठा drm_simple_display_pipe_funcs aspeed_gfx_funcs = अणु
	.enable		= aspeed_gfx_pipe_enable,
	.disable	= aspeed_gfx_pipe_disable,
	.update		= aspeed_gfx_pipe_update,
	.prepare_fb	= drm_gem_simple_display_pipe_prepare_fb,
	.enable_vblank	= aspeed_gfx_enable_vblank,
	.disable_vblank	= aspeed_gfx_disable_vblank,
पूर्ण;

अटल स्थिर uपूर्णांक32_t aspeed_gfx_क्रमmats[] = अणु
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_RGB565,
पूर्ण;

पूर्णांक aspeed_gfx_create_pipe(काष्ठा drm_device *drm)
अणु
	काष्ठा aspeed_gfx *priv = to_aspeed_gfx(drm);

	वापस drm_simple_display_pipe_init(drm, &priv->pipe, &aspeed_gfx_funcs,
					    aspeed_gfx_क्रमmats,
					    ARRAY_SIZE(aspeed_gfx_क्रमmats),
					    शून्य,
					    &priv->connector);
पूर्ण
