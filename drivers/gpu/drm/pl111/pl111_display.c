<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) COPYRIGHT 2012-2013 ARM Limited. All rights reserved.
 *
 * Parts of this file were based on sources as follows:
 *
 * Copyright (c) 2006-2008 Intel Corporation
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 * Copyright (C) 2011 Texas Instruments
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/version.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/of_graph.h>

#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "pl111_drm.h"

irqवापस_t pl111_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा pl111_drm_dev_निजी *priv = data;
	u32 irq_stat;
	irqवापस_t status = IRQ_NONE;

	irq_stat = पढ़ोl(priv->regs + CLCD_PL111_MIS);

	अगर (!irq_stat)
		वापस IRQ_NONE;

	अगर (irq_stat & CLCD_IRQ_NEXTBASE_UPDATE) अणु
		drm_crtc_handle_vblank(&priv->pipe.crtc);

		status = IRQ_HANDLED;
	पूर्ण

	/* Clear the पूर्णांकerrupt once करोne */
	ग_लिखोl(irq_stat, priv->regs + CLCD_PL111_ICR);

	वापस status;
पूर्ण

अटल क्रमागत drm_mode_status
pl111_mode_valid(काष्ठा drm_simple_display_pipe *pipe,
		 स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *drm = pipe->crtc.dev;
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;
	u32 cpp = priv->variant->fb_bpp / 8;
	u64 bw;

	/*
	 * We use the pixelघड़ी to also account क्रम पूर्णांकerlaced modes, the
	 * resulting bandwidth is in bytes per second.
	 */
	bw = mode->घड़ी * 1000ULL; /* In Hz */
	bw = bw * mode->hdisplay * mode->vdisplay * cpp;
	bw = भाग_u64(bw, mode->htotal * mode->vtotal);

	/*
	 * If no bandwidth स्थिरraपूर्णांकs, anything goes, अन्यथा
	 * check अगर we are too fast.
	 */
	अगर (priv->memory_bw && (bw > priv->memory_bw)) अणु
		DRM_DEBUG_KMS("%d x %d @ %d Hz, %d cpp, bw %llu too fast\n",
			      mode->hdisplay, mode->vdisplay,
			      mode->घड़ी * 1000, cpp, bw);

		वापस MODE_BAD;
	पूर्ण
	DRM_DEBUG_KMS("%d x %d @ %d Hz, %d cpp, bw %llu bytes/s OK\n",
		      mode->hdisplay, mode->vdisplay,
		      mode->घड़ी * 1000, cpp, bw);

	वापस MODE_OK;
पूर्ण

अटल पूर्णांक pl111_display_check(काष्ठा drm_simple_display_pipe *pipe,
			       काष्ठा drm_plane_state *pstate,
			       काष्ठा drm_crtc_state *cstate)
अणु
	स्थिर काष्ठा drm_display_mode *mode = &cstate->mode;
	काष्ठा drm_framebuffer *old_fb = pipe->plane.state->fb;
	काष्ठा drm_framebuffer *fb = pstate->fb;

	अगर (mode->hdisplay % 16)
		वापस -EINVAL;

	अगर (fb) अणु
		u32 offset = drm_fb_cma_get_gem_addr(fb, pstate, 0);

		/* FB base address must be dword aligned. */
		अगर (offset & 3)
			वापस -EINVAL;

		/* There's no pitch register -- the mode's hdisplay
		 * controls it.
		 */
		अगर (fb->pitches[0] != mode->hdisplay * fb->क्रमmat->cpp[0])
			वापस -EINVAL;

		/* We can't change the FB क्रमmat in a flicker-मुक्त
		 * manner (and only update it during CRTC enable).
		 */
		अगर (old_fb && old_fb->क्रमmat != fb->क्रमmat)
			cstate->mode_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pl111_display_enable(काष्ठा drm_simple_display_pipe *pipe,
				 काष्ठा drm_crtc_state *cstate,
				 काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;
	स्थिर काष्ठा drm_display_mode *mode = &cstate->mode;
	काष्ठा drm_framebuffer *fb = plane->state->fb;
	काष्ठा drm_connector *connector = priv->connector;
	काष्ठा drm_bridge *bridge = priv->bridge;
	bool grayscale = false;
	u32 cntl;
	u32 ppl, hsw, hfp, hbp;
	u32 lpp, vsw, vfp, vbp;
	u32 cpl, tim2;
	पूर्णांक ret;

	ret = clk_set_rate(priv->clk, mode->घड़ी * 1000);
	अगर (ret) अणु
		dev_err(drm->dev,
			"Failed to set pixel clock rate to %d: %d\n",
			mode->घड़ी * 1000, ret);
	पूर्ण

	clk_prepare_enable(priv->clk);

	ppl = (mode->hdisplay / 16) - 1;
	hsw = mode->hsync_end - mode->hsync_start - 1;
	hfp = mode->hsync_start - mode->hdisplay - 1;
	hbp = mode->htotal - mode->hsync_end - 1;

	lpp = mode->vdisplay - 1;
	vsw = mode->vsync_end - mode->vsync_start - 1;
	vfp = mode->vsync_start - mode->vdisplay;
	vbp = mode->vtotal - mode->vsync_end;

	cpl = mode->hdisplay - 1;

	ग_लिखोl((ppl << 2) |
	       (hsw << 8) |
	       (hfp << 16) |
	       (hbp << 24),
	       priv->regs + CLCD_TIM0);
	ग_लिखोl(lpp |
	       (vsw << 10) |
	       (vfp << 16) |
	       (vbp << 24),
	       priv->regs + CLCD_TIM1);

	spin_lock(&priv->tim2_lock);

	tim2 = पढ़ोl(priv->regs + CLCD_TIM2);
	tim2 &= (TIM2_BCD | TIM2_PCD_LO_MASK | TIM2_PCD_HI_MASK);

	अगर (priv->variant->broken_घड़ीभागider)
		tim2 |= TIM2_BCD;

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		tim2 |= TIM2_IHS;

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		tim2 |= TIM2_IVS;

	अगर (connector) अणु
		अगर (connector->display_info.bus_flags & DRM_BUS_FLAG_DE_LOW)
			tim2 |= TIM2_IOE;

		अगर (connector->display_info.bus_flags &
		    DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
			tim2 |= TIM2_IPC;

		अगर (connector->display_info.num_bus_क्रमmats == 1 &&
		    connector->display_info.bus_क्रमmats[0] ==
		    MEDIA_BUS_FMT_Y8_1X8)
			grayscale = true;

		/*
		 * The AC pin bias frequency is set to max count when using
		 * grayscale so at least once in a जबतक we will reverse
		 * polarity and get rid of any DC built up that could
		 * damage the display.
		 */
		अगर (grayscale)
			tim2 |= TIM2_ACB_MASK;
	पूर्ण

	अगर (bridge) अणु
		स्थिर काष्ठा drm_bridge_timings *btimings = bridge->timings;

		/*
		 * Here is when things get really fun. Someबार the bridge
		 * timings are such that the संकेत out from PL11x is not
		 * stable beक्रमe the receiving bridge (such as a dumb VGA DAC
		 * or similar) samples it. If that happens, we compensate by
		 * the only method we have: output the data on the opposite
		 * edge of the घड़ी so it is क्रम sure stable when it माला_लो
		 * sampled.
		 *
		 * The PL111 manual करोes not contain proper timining diagrams
		 * or data क्रम these details, but we know from experiments
		 * that the setup समय is more than 3000 picoseconds (3 ns).
		 * If we have a bridge that requires the संकेत to be stable
		 * earlier than 3000 ps beक्रमe the घड़ी pulse, we have to
		 * output the data on the opposite edge to aव्योम flicker.
		 */
		अगर (btimings && btimings->setup_समय_ps >= 3000)
			tim2 ^= TIM2_IPC;
	पूर्ण

	tim2 |= cpl << 16;
	ग_लिखोl(tim2, priv->regs + CLCD_TIM2);
	spin_unlock(&priv->tim2_lock);

	ग_लिखोl(0, priv->regs + CLCD_TIM3);

	/*
	 * Detect grayscale bus क्रमmat. We करो not support a grayscale mode
	 * toward userspace, instead we expose an RGB24 buffer and then the
	 * hardware will activate its grayscaler to convert to the grayscale
	 * क्रमmat.
	 */
	अगर (grayscale)
		cntl = CNTL_LCDEN | CNTL_LCDMONO8;
	अन्यथा
		/* Else we assume TFT display */
		cntl = CNTL_LCDEN | CNTL_LCDTFT | CNTL_LCDVCOMP(1);

	/* On the ST Micro variant, assume all 24 bits are connected */
	अगर (priv->variant->st_biपंचांगux_control)
		cntl |= CNTL_ST_CDWID_24;

	/*
	 * Note that the the ARM hardware's format reader takes 'r' from
	 * the low bit, जबतक DRM क्रमmats list channels from high bit
	 * to low bit as you पढ़ो left to right. The ST Micro version of
	 * the PL110 (LCDC) however uses the standard DRM क्रमmat.
	 */
	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_BGR888:
		/* Only supported on the ST Micro variant */
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_ST_LCDBPP24_PACKED | CNTL_BGR;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
		/* Only supported on the ST Micro variant */
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_ST_LCDBPP24_PACKED;
		अवरोध;
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_XBGR8888:
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_LCDBPP24 | CNTL_BGR;
		अन्यथा
			cntl |= CNTL_LCDBPP24;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_XRGB8888:
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_LCDBPP24;
		अन्यथा
			cntl |= CNTL_LCDBPP24 | CNTL_BGR;
		अवरोध;
	हाल DRM_FORMAT_BGR565:
		अगर (priv->variant->is_pl110)
			cntl |= CNTL_LCDBPP16;
		अन्यथा अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_LCDBPP16 | CNTL_ST_1XBPP_565 | CNTL_BGR;
		अन्यथा
			cntl |= CNTL_LCDBPP16_565;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		अगर (priv->variant->is_pl110)
			cntl |= CNTL_LCDBPP16 | CNTL_BGR;
		अन्यथा अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_LCDBPP16 | CNTL_ST_1XBPP_565;
		अन्यथा
			cntl |= CNTL_LCDBPP16_565 | CNTL_BGR;
		अवरोध;
	हाल DRM_FORMAT_ABGR1555:
	हाल DRM_FORMAT_XBGR1555:
		cntl |= CNTL_LCDBPP16;
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_ST_1XBPP_5551 | CNTL_BGR;
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
	हाल DRM_FORMAT_XRGB1555:
		cntl |= CNTL_LCDBPP16;
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_ST_1XBPP_5551;
		अन्यथा
			cntl |= CNTL_BGR;
		अवरोध;
	हाल DRM_FORMAT_ABGR4444:
	हाल DRM_FORMAT_XBGR4444:
		cntl |= CNTL_LCDBPP16_444;
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_ST_1XBPP_444 | CNTL_BGR;
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_XRGB4444:
		cntl |= CNTL_LCDBPP16_444;
		अगर (priv->variant->st_biपंचांगux_control)
			cntl |= CNTL_ST_1XBPP_444;
		अन्यथा
			cntl |= CNTL_BGR;
		अवरोध;
	शेष:
		WARN_ONCE(true, "Unknown FB format 0x%08x\n",
			  fb->क्रमmat->क्रमmat);
		अवरोध;
	पूर्ण

	/* The PL110 in Integrator/Versatile करोes the BGR routing बाह्यally */
	अगर (priv->variant->बाह्यal_bgr)
		cntl &= ~CNTL_BGR;

	/* Power sequence: first enable and chill */
	ग_लिखोl(cntl, priv->regs + priv->ctrl);

	/*
	 * We expect this delay to stabilize the contrast
	 * voltage Vee as stipulated by the manual
	 */
	msleep(20);

	अगर (priv->variant_display_enable)
		priv->variant_display_enable(drm, fb->क्रमmat->क्रमmat);

	/* Power Up */
	cntl |= CNTL_LCDPWR;
	ग_लिखोl(cntl, priv->regs + priv->ctrl);

	अगर (!priv->variant->broken_vblank)
		drm_crtc_vblank_on(crtc);
पूर्ण

अटल व्योम pl111_display_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;
	u32 cntl;

	अगर (!priv->variant->broken_vblank)
		drm_crtc_vblank_off(crtc);

	/* Power Down */
	cntl = पढ़ोl(priv->regs + priv->ctrl);
	अगर (cntl & CNTL_LCDPWR) अणु
		cntl &= ~CNTL_LCDPWR;
		ग_लिखोl(cntl, priv->regs + priv->ctrl);
	पूर्ण

	/*
	 * We expect this delay to stabilize the contrast voltage Vee as
	 * stipulated by the manual
	 */
	msleep(20);

	अगर (priv->variant_display_disable)
		priv->variant_display_disable(drm);

	/* Disable */
	ग_लिखोl(0, priv->regs + priv->ctrl);

	clk_disable_unprepare(priv->clk);
पूर्ण

अटल व्योम pl111_display_update(काष्ठा drm_simple_display_pipe *pipe,
				 काष्ठा drm_plane_state *old_pstate)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_plane_state *pstate = plane->state;
	काष्ठा drm_framebuffer *fb = pstate->fb;

	अगर (fb) अणु
		u32 addr = drm_fb_cma_get_gem_addr(fb, pstate, 0);

		ग_लिखोl(addr, priv->regs + CLCD_UBAS);
	पूर्ण

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		अगर (crtc->state->active && drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल पूर्णांक pl111_display_enable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;

	ग_लिखोl(CLCD_IRQ_NEXTBASE_UPDATE, priv->regs + priv->ienb);

	वापस 0;
पूर्ण

अटल व्योम pl111_display_disable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;

	ग_लिखोl(0, priv->regs + priv->ienb);
पूर्ण

अटल काष्ठा drm_simple_display_pipe_funcs pl111_display_funcs = अणु
	.mode_valid = pl111_mode_valid,
	.check = pl111_display_check,
	.enable = pl111_display_enable,
	.disable = pl111_display_disable,
	.update = pl111_display_update,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

अटल पूर्णांक pl111_clk_भाग_choose_भाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *prate, bool set_parent)
अणु
	पूर्णांक best_भाग = 1, भाग;
	काष्ठा clk_hw *parent = clk_hw_get_parent(hw);
	अचिन्हित दीर्घ best_prate = 0;
	अचिन्हित दीर्घ best_dअगरf = ~0ul;
	पूर्णांक max_भाग = (1 << (TIM2_PCD_LO_BITS + TIM2_PCD_HI_BITS)) - 1;

	क्रम (भाग = 1; भाग < max_भाग; भाग++) अणु
		अचिन्हित दीर्घ this_prate, भाग_rate, dअगरf;

		अगर (set_parent)
			this_prate = clk_hw_round_rate(parent, rate * भाग);
		अन्यथा
			this_prate = *prate;
		भाग_rate = DIV_ROUND_UP_ULL(this_prate, भाग);
		dअगरf = असल(rate - भाग_rate);

		अगर (dअगरf < best_dअगरf) अणु
			best_भाग = भाग;
			best_dअगरf = dअगरf;
			best_prate = this_prate;
		पूर्ण
	पूर्ण

	*prate = best_prate;
	वापस best_भाग;
पूर्ण

अटल दीर्घ pl111_clk_भाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक भाग = pl111_clk_भाग_choose_भाग(hw, rate, prate, true);

	वापस DIV_ROUND_UP_ULL(*prate, भाग);
पूर्ण

अटल अचिन्हित दीर्घ pl111_clk_भाग_recalc_rate(काष्ठा clk_hw *hw,
					       अचिन्हित दीर्घ prate)
अणु
	काष्ठा pl111_drm_dev_निजी *priv =
		container_of(hw, काष्ठा pl111_drm_dev_निजी, clk_भाग);
	u32 tim2 = पढ़ोl(priv->regs + CLCD_TIM2);
	पूर्णांक भाग;

	अगर (tim2 & TIM2_BCD)
		वापस prate;

	भाग = tim2 & TIM2_PCD_LO_MASK;
	भाग |= (tim2 & TIM2_PCD_HI_MASK) >>
		(TIM2_PCD_HI_SHIFT - TIM2_PCD_LO_BITS);
	भाग += 2;

	वापस DIV_ROUND_UP_ULL(prate, भाग);
पूर्ण

अटल पूर्णांक pl111_clk_भाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ prate)
अणु
	काष्ठा pl111_drm_dev_निजी *priv =
		container_of(hw, काष्ठा pl111_drm_dev_निजी, clk_भाग);
	पूर्णांक भाग = pl111_clk_भाग_choose_भाग(hw, rate, &prate, false);
	u32 tim2;

	spin_lock(&priv->tim2_lock);
	tim2 = पढ़ोl(priv->regs + CLCD_TIM2);
	tim2 &= ~(TIM2_BCD | TIM2_PCD_LO_MASK | TIM2_PCD_HI_MASK);

	अगर (भाग == 1) अणु
		tim2 |= TIM2_BCD;
	पूर्ण अन्यथा अणु
		भाग -= 2;
		tim2 |= भाग & TIM2_PCD_LO_MASK;
		tim2 |= (भाग >> TIM2_PCD_LO_BITS) << TIM2_PCD_HI_SHIFT;
	पूर्ण

	ग_लिखोl(tim2, priv->regs + CLCD_TIM2);
	spin_unlock(&priv->tim2_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops pl111_clk_भाग_ops = अणु
	.recalc_rate = pl111_clk_भाग_recalc_rate,
	.round_rate = pl111_clk_भाग_round_rate,
	.set_rate = pl111_clk_भाग_set_rate,
पूर्ण;

अटल पूर्णांक
pl111_init_घड़ी_भागider(काष्ठा drm_device *drm)
अणु
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;
	काष्ठा clk *parent = devm_clk_get(drm->dev, "clcdclk");
	काष्ठा clk_hw *भाग = &priv->clk_भाग;
	स्थिर अक्षर *parent_name;
	काष्ठा clk_init_data init = अणु
		.name = "pl111_div",
		.ops = &pl111_clk_भाग_ops,
		.parent_names = &parent_name,
		.num_parents = 1,
		.flags = CLK_SET_RATE_PARENT,
	पूर्ण;
	पूर्णांक ret;

	अगर (IS_ERR(parent)) अणु
		dev_err(drm->dev, "CLCD: unable to get clcdclk.\n");
		वापस PTR_ERR(parent);
	पूर्ण

	spin_lock_init(&priv->tim2_lock);

	/* If the घड़ी भागider is broken, use the parent directly */
	अगर (priv->variant->broken_घड़ीभागider) अणु
		priv->clk = parent;
		वापस 0;
	पूर्ण
	parent_name = __clk_get_name(parent);
	भाग->init = &init;

	ret = devm_clk_hw_रेजिस्टर(drm->dev, भाग);

	priv->clk = भाग->clk;
	वापस ret;
पूर्ण

पूर्णांक pl111_display_init(काष्ठा drm_device *drm)
अणु
	काष्ठा pl111_drm_dev_निजी *priv = drm->dev_निजी;
	पूर्णांक ret;

	ret = pl111_init_घड़ी_भागider(drm);
	अगर (ret)
		वापस ret;

	अगर (!priv->variant->broken_vblank) अणु
		pl111_display_funcs.enable_vblank = pl111_display_enable_vblank;
		pl111_display_funcs.disable_vblank = pl111_display_disable_vblank;
	पूर्ण

	ret = drm_simple_display_pipe_init(drm, &priv->pipe,
					   &pl111_display_funcs,
					   priv->variant->क्रमmats,
					   priv->variant->nक्रमmats,
					   शून्य,
					   priv->connector);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
