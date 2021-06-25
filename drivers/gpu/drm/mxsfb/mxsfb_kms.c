<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Marek Vasut <marex@denx.de>
 *
 * This code is based on drivers/video/fbdev/mxsfb.c :
 * Copyright (C) 2010 Juergen Beisert, Pengutronix
 * Copyright (C) 2008-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2008 Embedded Alley Solutions, Inc All Rights Reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spinlock.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "mxsfb_drv.h"
#समावेश "mxsfb_regs.h"

/* 1 second delay should be plenty of समय क्रम block reset */
#घोषणा RESET_TIMEOUT		1000000

/* -----------------------------------------------------------------------------
 * CRTC
 */

अटल u32 set_hsync_pulse_width(काष्ठा mxsfb_drm_निजी *mxsfb, u32 val)
अणु
	वापस (val & mxsfb->devdata->hs_wdth_mask) <<
		mxsfb->devdata->hs_wdth_shअगरt;
पूर्ण

/*
 * Setup the MXSFB रेजिस्टरs क्रम decoding the pixels out of the framebuffer and
 * outputting them on the bus.
 */
अटल व्योम mxsfb_set_क्रमmats(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	काष्ठा drm_device *drm = mxsfb->drm;
	स्थिर u32 क्रमmat = mxsfb->crtc.primary->state->fb->क्रमmat->क्रमmat;
	u32 bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
	u32 ctrl, ctrl1;

	अगर (mxsfb->connector->display_info.num_bus_क्रमmats)
		bus_क्रमmat = mxsfb->connector->display_info.bus_क्रमmats[0];

	DRM_DEV_DEBUG_DRIVER(drm->dev, "Using bus_format: 0x%08X\n",
			     bus_क्रमmat);

	ctrl = CTRL_BYPASS_COUNT | CTRL_MASTER;

	/* CTRL1 contains IRQ config and status bits, preserve those. */
	ctrl1 = पढ़ोl(mxsfb->base + LCDC_CTRL1);
	ctrl1 &= CTRL1_CUR_FRAME_DONE_IRQ_EN | CTRL1_CUR_FRAME_DONE_IRQ;

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
		dev_dbg(drm->dev, "Setting up RGB565 mode\n");
		ctrl |= CTRL_WORD_LENGTH_16;
		ctrl1 |= CTRL1_SET_BYTE_PACKAGING(0xf);
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		dev_dbg(drm->dev, "Setting up XRGB8888 mode\n");
		ctrl |= CTRL_WORD_LENGTH_24;
		/* Do not use packed pixels = one pixel per word instead. */
		ctrl1 |= CTRL1_SET_BYTE_PACKAGING(0x7);
		अवरोध;
	पूर्ण

	चयन (bus_क्रमmat) अणु
	हाल MEDIA_BUS_FMT_RGB565_1X16:
		ctrl |= CTRL_BUS_WIDTH_16;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB666_1X18:
		ctrl |= CTRL_BUS_WIDTH_18;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		ctrl |= CTRL_BUS_WIDTH_24;
		अवरोध;
	शेष:
		dev_err(drm->dev, "Unknown media bus format %d\n", bus_क्रमmat);
		अवरोध;
	पूर्ण

	ग_लिखोl(ctrl1, mxsfb->base + LCDC_CTRL1);
	ग_लिखोl(ctrl, mxsfb->base + LCDC_CTRL);
पूर्ण

अटल व्योम mxsfb_enable_controller(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	u32 reg;

	अगर (mxsfb->clk_disp_axi)
		clk_prepare_enable(mxsfb->clk_disp_axi);
	clk_prepare_enable(mxsfb->clk);

	/* If it was disabled, re-enable the mode again */
	ग_लिखोl(CTRL_DOTCLK_MODE, mxsfb->base + LCDC_CTRL + REG_SET);

	/* Enable the SYNC संकेतs first, then the DMA engine */
	reg = पढ़ोl(mxsfb->base + LCDC_VDCTRL4);
	reg |= VDCTRL4_SYNC_SIGNALS_ON;
	ग_लिखोl(reg, mxsfb->base + LCDC_VDCTRL4);

	ग_लिखोl(CTRL_RUN, mxsfb->base + LCDC_CTRL + REG_SET);
पूर्ण

अटल व्योम mxsfb_disable_controller(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	u32 reg;

	/*
	 * Even अगर we disable the controller here, it will still जारी
	 * until its FIFOs are running out of data
	 */
	ग_लिखोl(CTRL_DOTCLK_MODE, mxsfb->base + LCDC_CTRL + REG_CLR);

	पढ़ोl_poll_समयout(mxsfb->base + LCDC_CTRL, reg, !(reg & CTRL_RUN),
			   0, 1000);

	reg = पढ़ोl(mxsfb->base + LCDC_VDCTRL4);
	reg &= ~VDCTRL4_SYNC_SIGNALS_ON;
	ग_लिखोl(reg, mxsfb->base + LCDC_VDCTRL4);

	clk_disable_unprepare(mxsfb->clk);
	अगर (mxsfb->clk_disp_axi)
		clk_disable_unprepare(mxsfb->clk_disp_axi);
पूर्ण

/*
 * Clear the bit and poll it cleared.  This is usually called with
 * a reset address and mask being either SFTRST(bit 31) or CLKGATE
 * (bit 30).
 */
अटल पूर्णांक clear_poll_bit(व्योम __iomem *addr, u32 mask)
अणु
	u32 reg;

	ग_लिखोl(mask, addr + REG_CLR);
	वापस पढ़ोl_poll_समयout(addr, reg, !(reg & mask), 0, RESET_TIMEOUT);
पूर्ण

अटल पूर्णांक mxsfb_reset_block(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	पूर्णांक ret;

	ret = clear_poll_bit(mxsfb->base + LCDC_CTRL, CTRL_SFTRST);
	अगर (ret)
		वापस ret;

	ग_लिखोl(CTRL_CLKGATE, mxsfb->base + LCDC_CTRL + REG_CLR);

	ret = clear_poll_bit(mxsfb->base + LCDC_CTRL, CTRL_SFTRST);
	अगर (ret)
		वापस ret;

	वापस clear_poll_bit(mxsfb->base + LCDC_CTRL, CTRL_CLKGATE);
पूर्ण

अटल dma_addr_t mxsfb_get_fb_paddr(काष्ठा drm_plane *plane)
अणु
	काष्ठा drm_framebuffer *fb = plane->state->fb;
	काष्ठा drm_gem_cma_object *gem;

	अगर (!fb)
		वापस 0;

	gem = drm_fb_cma_get_gem_obj(fb, 0);
	अगर (!gem)
		वापस 0;

	वापस gem->paddr;
पूर्ण

अटल व्योम mxsfb_crtc_mode_set_nofb(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	काष्ठा drm_device *drm = mxsfb->crtc.dev;
	काष्ठा drm_display_mode *m = &mxsfb->crtc.state->adjusted_mode;
	u32 bus_flags = mxsfb->connector->display_info.bus_flags;
	u32 vdctrl0, vsync_pulse_len, hsync_pulse_len;
	पूर्णांक err;

	/*
	 * It seems, you can't re-program the controller अगर it is still
	 * running. This may lead to shअगरted pictures (FIFO issue?), so
	 * first stop the controller and drain its FIFOs.
	 */

	/* Mandatory eLCDIF reset as per the Reference Manual */
	err = mxsfb_reset_block(mxsfb);
	अगर (err)
		वापस;

	/* Clear the FIFOs */
	ग_लिखोl(CTRL1_FIFO_CLEAR, mxsfb->base + LCDC_CTRL1 + REG_SET);

	अगर (mxsfb->devdata->has_overlay)
		ग_लिखोl(0, mxsfb->base + LCDC_AS_CTRL);

	mxsfb_set_क्रमmats(mxsfb);

	clk_set_rate(mxsfb->clk, m->crtc_घड़ी * 1000);

	अगर (mxsfb->bridge && mxsfb->bridge->timings)
		bus_flags = mxsfb->bridge->timings->input_bus_flags;

	DRM_DEV_DEBUG_DRIVER(drm->dev, "Pixel clock: %dkHz (actual: %dkHz)\n",
			     m->crtc_घड़ी,
			     (पूर्णांक)(clk_get_rate(mxsfb->clk) / 1000));
	DRM_DEV_DEBUG_DRIVER(drm->dev, "Connector bus_flags: 0x%08X\n",
			     bus_flags);
	DRM_DEV_DEBUG_DRIVER(drm->dev, "Mode flags: 0x%08X\n", m->flags);

	ग_लिखोl(TRANSFER_COUNT_SET_VCOUNT(m->crtc_vdisplay) |
	       TRANSFER_COUNT_SET_HCOUNT(m->crtc_hdisplay),
	       mxsfb->base + mxsfb->devdata->transfer_count);

	vsync_pulse_len = m->crtc_vsync_end - m->crtc_vsync_start;

	vdctrl0 = VDCTRL0_ENABLE_PRESENT |	/* Always in DOTCLOCK mode */
		  VDCTRL0_VSYNC_PERIOD_UNIT |
		  VDCTRL0_VSYNC_PULSE_WIDTH_UNIT |
		  VDCTRL0_SET_VSYNC_PULSE_WIDTH(vsync_pulse_len);
	अगर (m->flags & DRM_MODE_FLAG_PHSYNC)
		vdctrl0 |= VDCTRL0_HSYNC_ACT_HIGH;
	अगर (m->flags & DRM_MODE_FLAG_PVSYNC)
		vdctrl0 |= VDCTRL0_VSYNC_ACT_HIGH;
	/* Make sure Data Enable is high active by शेष */
	अगर (!(bus_flags & DRM_BUS_FLAG_DE_LOW))
		vdctrl0 |= VDCTRL0_ENABLE_ACT_HIGH;
	/*
	 * DRM_BUS_FLAG_PIXDATA_DRIVE_ defines are controller centric,
	 * controllers VDCTRL0_DOTCLK is display centric.
	 * Drive on positive edge       -> display samples on falling edge
	 * DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE -> VDCTRL0_DOTCLK_ACT_FALLING
	 */
	अगर (bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE)
		vdctrl0 |= VDCTRL0_DOTCLK_ACT_FALLING;

	ग_लिखोl(vdctrl0, mxsfb->base + LCDC_VDCTRL0);

	/* Frame length in lines. */
	ग_लिखोl(m->crtc_vtotal, mxsfb->base + LCDC_VDCTRL1);

	/* Line length in units of घड़ीs or pixels. */
	hsync_pulse_len = m->crtc_hsync_end - m->crtc_hsync_start;
	ग_लिखोl(set_hsync_pulse_width(mxsfb, hsync_pulse_len) |
	       VDCTRL2_SET_HSYNC_PERIOD(m->crtc_htotal),
	       mxsfb->base + LCDC_VDCTRL2);

	ग_लिखोl(SET_HOR_WAIT_CNT(m->crtc_htotal - m->crtc_hsync_start) |
	       SET_VERT_WAIT_CNT(m->crtc_vtotal - m->crtc_vsync_start),
	       mxsfb->base + LCDC_VDCTRL3);

	ग_लिखोl(SET_DOTCLK_H_VALID_DATA_CNT(m->hdisplay),
	       mxsfb->base + LCDC_VDCTRL4);
पूर्ण

अटल पूर्णांक mxsfb_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	bool has_primary = crtc_state->plane_mask &
			   drm_plane_mask(crtc->primary);

	/* The primary plane has to be enabled when the CRTC is active. */
	अगर (crtc_state->active && !has_primary)
		वापस -EINVAL;

	/* TODO: Is this needed ? */
	वापस drm_atomic_add_affected_planes(state, crtc);
पूर्ण

अटल व्योम mxsfb_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_pending_vblank_event *event;

	event = crtc->state->event;
	crtc->state->event = शून्य;

	अगर (!event)
		वापस;

	spin_lock_irq(&crtc->dev->event_lock);
	अगर (drm_crtc_vblank_get(crtc) == 0)
		drm_crtc_arm_vblank_event(crtc, event);
	अन्यथा
		drm_crtc_send_vblank_event(crtc, event);
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

अटल व्योम mxsfb_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mxsfb_drm_निजी *mxsfb = to_mxsfb_drm_निजी(crtc->dev);
	काष्ठा drm_device *drm = mxsfb->drm;
	dma_addr_t paddr;

	pm_runसमय_get_sync(drm->dev);
	mxsfb_enable_axi_clk(mxsfb);

	drm_crtc_vblank_on(crtc);

	mxsfb_crtc_mode_set_nofb(mxsfb);

	/* Write cur_buf as well to aव्योम an initial corrupt frame */
	paddr = mxsfb_get_fb_paddr(crtc->primary);
	अगर (paddr) अणु
		ग_लिखोl(paddr, mxsfb->base + mxsfb->devdata->cur_buf);
		ग_लिखोl(paddr, mxsfb->base + mxsfb->devdata->next_buf);
	पूर्ण

	mxsfb_enable_controller(mxsfb);
पूर्ण

अटल व्योम mxsfb_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mxsfb_drm_निजी *mxsfb = to_mxsfb_drm_निजी(crtc->dev);
	काष्ठा drm_device *drm = mxsfb->drm;
	काष्ठा drm_pending_vblank_event *event;

	mxsfb_disable_controller(mxsfb);

	spin_lock_irq(&drm->event_lock);
	event = crtc->state->event;
	अगर (event) अणु
		crtc->state->event = शून्य;
		drm_crtc_send_vblank_event(crtc, event);
	पूर्ण
	spin_unlock_irq(&drm->event_lock);

	drm_crtc_vblank_off(crtc);

	mxsfb_disable_axi_clk(mxsfb);
	pm_runसमय_put_sync(drm->dev);
पूर्ण

अटल पूर्णांक mxsfb_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mxsfb_drm_निजी *mxsfb = to_mxsfb_drm_निजी(crtc->dev);

	/* Clear and enable VBLANK IRQ */
	ग_लिखोl(CTRL1_CUR_FRAME_DONE_IRQ, mxsfb->base + LCDC_CTRL1 + REG_CLR);
	ग_लिखोl(CTRL1_CUR_FRAME_DONE_IRQ_EN, mxsfb->base + LCDC_CTRL1 + REG_SET);

	वापस 0;
पूर्ण

अटल व्योम mxsfb_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mxsfb_drm_निजी *mxsfb = to_mxsfb_drm_निजी(crtc->dev);

	/* Disable and clear VBLANK IRQ */
	ग_लिखोl(CTRL1_CUR_FRAME_DONE_IRQ_EN, mxsfb->base + LCDC_CTRL1 + REG_CLR);
	ग_लिखोl(CTRL1_CUR_FRAME_DONE_IRQ, mxsfb->base + LCDC_CTRL1 + REG_CLR);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs mxsfb_crtc_helper_funcs = अणु
	.atomic_check = mxsfb_crtc_atomic_check,
	.atomic_flush = mxsfb_crtc_atomic_flush,
	.atomic_enable = mxsfb_crtc_atomic_enable,
	.atomic_disable = mxsfb_crtc_atomic_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs mxsfb_crtc_funcs = अणु
	.reset = drm_atomic_helper_crtc_reset,
	.destroy = drm_crtc_cleanup,
	.set_config = drm_atomic_helper_set_config,
	.page_flip = drm_atomic_helper_page_flip,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank = mxsfb_crtc_enable_vblank,
	.disable_vblank = mxsfb_crtc_disable_vblank,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Encoder
 */

अटल स्थिर काष्ठा drm_encoder_funcs mxsfb_encoder_funcs = अणु
	.destroy = drm_encoder_cleanup,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Planes
 */

अटल पूर्णांक mxsfb_plane_atomic_check(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *plane_state = drm_atomic_get_new_plane_state(state,
									     plane);
	काष्ठा mxsfb_drm_निजी *mxsfb = to_mxsfb_drm_निजी(plane->dev);
	काष्ठा drm_crtc_state *crtc_state;

	crtc_state = drm_atomic_get_new_crtc_state(state,
						   &mxsfb->crtc);

	वापस drm_atomic_helper_check_plane_state(plane_state, crtc_state,
						   DRM_PLANE_HELPER_NO_SCALING,
						   DRM_PLANE_HELPER_NO_SCALING,
						   false, true);
पूर्ण

अटल व्योम mxsfb_plane_primary_atomic_update(काष्ठा drm_plane *plane,
					      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mxsfb_drm_निजी *mxsfb = to_mxsfb_drm_निजी(plane->dev);
	dma_addr_t paddr;

	paddr = mxsfb_get_fb_paddr(plane);
	अगर (paddr)
		ग_लिखोl(paddr, mxsfb->base + mxsfb->devdata->next_buf);
पूर्ण

अटल व्योम mxsfb_plane_overlay_atomic_update(काष्ठा drm_plane *plane,
					      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *old_pstate = drm_atomic_get_old_plane_state(state,
									    plane);
	काष्ठा mxsfb_drm_निजी *mxsfb = to_mxsfb_drm_निजी(plane->dev);
	काष्ठा drm_plane_state *new_pstate = drm_atomic_get_new_plane_state(state,
									    plane);
	dma_addr_t paddr;
	u32 ctrl;

	paddr = mxsfb_get_fb_paddr(plane);
	अगर (!paddr) अणु
		ग_लिखोl(0, mxsfb->base + LCDC_AS_CTRL);
		वापस;
	पूर्ण

	/*
	 * HACK: The hardware seems to output 64 bytes of data of unknown
	 * origin, and then to proceed with the framebuffer. Until the reason
	 * is understood, live with the 16 initial invalid pixels on the first
	 * line and start 64 bytes within the framebuffer.
	 */
	paddr += 64;

	ग_लिखोl(paddr, mxsfb->base + LCDC_AS_NEXT_BUF);

	/*
	 * If the plane was previously disabled, ग_लिखो LCDC_AS_BUF as well to
	 * provide the first buffer.
	 */
	अगर (!old_pstate->fb)
		ग_लिखोl(paddr, mxsfb->base + LCDC_AS_BUF);

	ctrl = AS_CTRL_AS_ENABLE | AS_CTRL_ALPHA(255);

	चयन (new_pstate->fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_XRGB4444:
		ctrl |= AS_CTRL_FORMAT_RGB444 | AS_CTRL_ALPHA_CTRL_OVERRIDE;
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
		ctrl |= AS_CTRL_FORMAT_ARGB4444 | AS_CTRL_ALPHA_CTRL_EMBEDDED;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		ctrl |= AS_CTRL_FORMAT_RGB555 | AS_CTRL_ALPHA_CTRL_OVERRIDE;
		अवरोध;
	हाल DRM_FORMAT_ARGB1555:
		ctrl |= AS_CTRL_FORMAT_ARGB1555 | AS_CTRL_ALPHA_CTRL_EMBEDDED;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		ctrl |= AS_CTRL_FORMAT_RGB565 | AS_CTRL_ALPHA_CTRL_OVERRIDE;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		ctrl |= AS_CTRL_FORMAT_RGB888 | AS_CTRL_ALPHA_CTRL_OVERRIDE;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		ctrl |= AS_CTRL_FORMAT_ARGB8888 | AS_CTRL_ALPHA_CTRL_EMBEDDED;
		अवरोध;
	पूर्ण

	ग_लिखोl(ctrl, mxsfb->base + LCDC_AS_CTRL);
पूर्ण

अटल bool mxsfb_क्रमmat_mod_supported(काष्ठा drm_plane *plane,
				       uपूर्णांक32_t क्रमmat,
				       uपूर्णांक64_t modअगरier)
अणु
	वापस modअगरier == DRM_FORMAT_MOD_LINEAR;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs mxsfb_plane_primary_helper_funcs = अणु
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
	.atomic_check = mxsfb_plane_atomic_check,
	.atomic_update = mxsfb_plane_primary_atomic_update,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_helper_funcs mxsfb_plane_overlay_helper_funcs = अणु
	.prepare_fb = drm_gem_plane_helper_prepare_fb,
	.atomic_check = mxsfb_plane_atomic_check,
	.atomic_update = mxsfb_plane_overlay_atomic_update,
पूर्ण;

अटल स्थिर काष्ठा drm_plane_funcs mxsfb_plane_funcs = अणु
	.क्रमmat_mod_supported	= mxsfb_क्रमmat_mod_supported,
	.update_plane		= drm_atomic_helper_update_plane,
	.disable_plane		= drm_atomic_helper_disable_plane,
	.destroy		= drm_plane_cleanup,
	.reset			= drm_atomic_helper_plane_reset,
	.atomic_duplicate_state	= drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल स्थिर uपूर्णांक32_t mxsfb_primary_plane_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
पूर्ण;

अटल स्थिर uपूर्णांक32_t mxsfb_overlay_plane_क्रमmats[] = अणु
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर uपूर्णांक64_t mxsfb_modअगरiers[] = अणु
	DRM_FORMAT_MOD_LINEAR,
	DRM_FORMAT_MOD_INVALID
पूर्ण;

/* -----------------------------------------------------------------------------
 * Initialization
 */

पूर्णांक mxsfb_kms_init(काष्ठा mxsfb_drm_निजी *mxsfb)
अणु
	काष्ठा drm_encoder *encoder = &mxsfb->encoder;
	काष्ठा drm_crtc *crtc = &mxsfb->crtc;
	पूर्णांक ret;

	drm_plane_helper_add(&mxsfb->planes.primary,
			     &mxsfb_plane_primary_helper_funcs);
	ret = drm_universal_plane_init(mxsfb->drm, &mxsfb->planes.primary, 1,
				       &mxsfb_plane_funcs,
				       mxsfb_primary_plane_क्रमmats,
				       ARRAY_SIZE(mxsfb_primary_plane_क्रमmats),
				       mxsfb_modअगरiers, DRM_PLANE_TYPE_PRIMARY,
				       शून्य);
	अगर (ret)
		वापस ret;

	अगर (mxsfb->devdata->has_overlay) अणु
		drm_plane_helper_add(&mxsfb->planes.overlay,
				     &mxsfb_plane_overlay_helper_funcs);
		ret = drm_universal_plane_init(mxsfb->drm,
					       &mxsfb->planes.overlay, 1,
					       &mxsfb_plane_funcs,
					       mxsfb_overlay_plane_क्रमmats,
					       ARRAY_SIZE(mxsfb_overlay_plane_क्रमmats),
					       mxsfb_modअगरiers, DRM_PLANE_TYPE_OVERLAY,
					       शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	drm_crtc_helper_add(crtc, &mxsfb_crtc_helper_funcs);
	ret = drm_crtc_init_with_planes(mxsfb->drm, crtc,
					&mxsfb->planes.primary, शून्य,
					&mxsfb_crtc_funcs, शून्य);
	अगर (ret)
		वापस ret;

	encoder->possible_crtcs = drm_crtc_mask(crtc);
	वापस drm_encoder_init(mxsfb->drm, encoder, &mxsfb_encoder_funcs,
				DRM_MODE_ENCODER_NONE, शून्य);
पूर्ण
