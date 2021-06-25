<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Linus Walleij <linus.walleij@linaro.org>
 * Parts of this file were based on the MCDE driver by Marcus Lorentzon
 * (C) ST-Ericsson SA 2013
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/media-bus-क्रमmat.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_simple_kms_helper.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_vblank.h>
#समावेश <video/mipi_display.h>

#समावेश "mcde_drm.h"
#समावेश "mcde_display_regs.h"

क्रमागत mcde_fअगरo अणु
	MCDE_FIFO_A,
	MCDE_FIFO_B,
	/* TODO: implement FIFO C0 and FIFO C1 */
पूर्ण;

क्रमागत mcde_channel अणु
	MCDE_CHANNEL_0 = 0,
	MCDE_CHANNEL_1,
	MCDE_CHANNEL_2,
	MCDE_CHANNEL_3,
पूर्ण;

क्रमागत mcde_extsrc अणु
	MCDE_EXTSRC_0 = 0,
	MCDE_EXTSRC_1,
	MCDE_EXTSRC_2,
	MCDE_EXTSRC_3,
	MCDE_EXTSRC_4,
	MCDE_EXTSRC_5,
	MCDE_EXTSRC_6,
	MCDE_EXTSRC_7,
	MCDE_EXTSRC_8,
	MCDE_EXTSRC_9,
पूर्ण;

क्रमागत mcde_overlay अणु
	MCDE_OVERLAY_0 = 0,
	MCDE_OVERLAY_1,
	MCDE_OVERLAY_2,
	MCDE_OVERLAY_3,
	MCDE_OVERLAY_4,
	MCDE_OVERLAY_5,
पूर्ण;

क्रमागत mcde_क्रमmatter अणु
	MCDE_DSI_FORMATTER_0 = 0,
	MCDE_DSI_FORMATTER_1,
	MCDE_DSI_FORMATTER_2,
	MCDE_DSI_FORMATTER_3,
	MCDE_DSI_FORMATTER_4,
	MCDE_DSI_FORMATTER_5,
	MCDE_DPI_FORMATTER_0,
	MCDE_DPI_FORMATTER_1,
पूर्ण;

व्योम mcde_display_irq(काष्ठा mcde *mcde)
अणु
	u32 mispp, misovl, mischnl;
	bool vblank = false;

	/* Handle display IRQs */
	mispp = पढ़ोl(mcde->regs + MCDE_MISPP);
	misovl = पढ़ोl(mcde->regs + MCDE_MISOVL);
	mischnl = पढ़ोl(mcde->regs + MCDE_MISCHNL);

	/*
	 * Handle IRQs from the DSI link. All IRQs from the DSI links
	 * are just latched onto the MCDE IRQ line, so we need to traverse
	 * any active DSI masters and check अगर an IRQ is originating from
	 * them.
	 *
	 * TODO: Currently only one DSI link is supported.
	 */
	अगर (!mcde->dpi_output && mcde_dsi_irq(mcde->mdsi)) अणु
		u32 val;

		/*
		 * In oneshot mode we करो not send continuous updates
		 * to the display, instead we only push out updates when
		 * the update function is called, then we disable the
		 * flow on the channel once we get the TE IRQ.
		 */
		अगर (mcde->flow_mode == MCDE_COMMAND_ONESHOT_FLOW) अणु
			spin_lock(&mcde->flow_lock);
			अगर (--mcde->flow_active == 0) अणु
				dev_dbg(mcde->dev, "TE0 IRQ\n");
				/* Disable FIFO A flow */
				val = पढ़ोl(mcde->regs + MCDE_CRA0);
				val &= ~MCDE_CRX0_FLOEN;
				ग_लिखोl(val, mcde->regs + MCDE_CRA0);
			पूर्ण
			spin_unlock(&mcde->flow_lock);
		पूर्ण
	पूर्ण

	/* Vblank from one of the channels */
	अगर (mispp & MCDE_PP_VCMPA) अणु
		dev_dbg(mcde->dev, "chnl A vblank IRQ\n");
		vblank = true;
	पूर्ण
	अगर (mispp & MCDE_PP_VCMPB) अणु
		dev_dbg(mcde->dev, "chnl B vblank IRQ\n");
		vblank = true;
	पूर्ण
	अगर (mispp & MCDE_PP_VCMPC0)
		dev_dbg(mcde->dev, "chnl C0 vblank IRQ\n");
	अगर (mispp & MCDE_PP_VCMPC1)
		dev_dbg(mcde->dev, "chnl C1 vblank IRQ\n");
	अगर (mispp & MCDE_PP_VSCC0)
		dev_dbg(mcde->dev, "chnl C0 TE IRQ\n");
	अगर (mispp & MCDE_PP_VSCC1)
		dev_dbg(mcde->dev, "chnl C1 TE IRQ\n");
	ग_लिखोl(mispp, mcde->regs + MCDE_RISPP);

	अगर (vblank)
		drm_crtc_handle_vblank(&mcde->pipe.crtc);

	अगर (misovl)
		dev_info(mcde->dev, "some stray overlay IRQ %08x\n", misovl);
	ग_लिखोl(misovl, mcde->regs + MCDE_RISOVL);

	अगर (mischnl)
		dev_info(mcde->dev, "some stray channel error IRQ %08x\n",
			 mischnl);
	ग_लिखोl(mischnl, mcde->regs + MCDE_RISCHNL);
पूर्ण

व्योम mcde_display_disable_irqs(काष्ठा mcde *mcde)
अणु
	/* Disable all IRQs */
	ग_लिखोl(0, mcde->regs + MCDE_IMSCPP);
	ग_लिखोl(0, mcde->regs + MCDE_IMSCOVL);
	ग_लिखोl(0, mcde->regs + MCDE_IMSCCHNL);

	/* Clear any pending IRQs */
	ग_लिखोl(0xFFFFFFFF, mcde->regs + MCDE_RISPP);
	ग_लिखोl(0xFFFFFFFF, mcde->regs + MCDE_RISOVL);
	ग_लिखोl(0xFFFFFFFF, mcde->regs + MCDE_RISCHNL);
पूर्ण

अटल पूर्णांक mcde_display_check(काष्ठा drm_simple_display_pipe *pipe,
			      काष्ठा drm_plane_state *pstate,
			      काष्ठा drm_crtc_state *cstate)
अणु
	स्थिर काष्ठा drm_display_mode *mode = &cstate->mode;
	काष्ठा drm_framebuffer *old_fb = pipe->plane.state->fb;
	काष्ठा drm_framebuffer *fb = pstate->fb;

	अगर (fb) अणु
		u32 offset = drm_fb_cma_get_gem_addr(fb, pstate, 0);

		/* FB base address must be dword aligned. */
		अगर (offset & 3) अणु
			DRM_DEBUG_KMS("FB not 32-bit aligned\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * There's no pitch register, the mode's hdisplay
		 * controls this.
		 */
		अगर (fb->pitches[0] != mode->hdisplay * fb->क्रमmat->cpp[0]) अणु
			DRM_DEBUG_KMS("can't handle pitches\n");
			वापस -EINVAL;
		पूर्ण

		/*
		 * We can't change the FB क्रमmat in a flicker-मुक्त
		 * manner (and only update it during CRTC enable).
		 */
		अगर (old_fb && old_fb->क्रमmat != fb->क्रमmat)
			cstate->mode_changed = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mcde_configure_extsrc(काष्ठा mcde *mcde, क्रमागत mcde_extsrc src,
				 u32 क्रमmat)
अणु
	u32 val;
	u32 conf;
	u32 cr;

	चयन (src) अणु
	हाल MCDE_EXTSRC_0:
		conf = MCDE_EXTSRC0CONF;
		cr = MCDE_EXTSRC0CR;
		अवरोध;
	हाल MCDE_EXTSRC_1:
		conf = MCDE_EXTSRC1CONF;
		cr = MCDE_EXTSRC1CR;
		अवरोध;
	हाल MCDE_EXTSRC_2:
		conf = MCDE_EXTSRC2CONF;
		cr = MCDE_EXTSRC2CR;
		अवरोध;
	हाल MCDE_EXTSRC_3:
		conf = MCDE_EXTSRC3CONF;
		cr = MCDE_EXTSRC3CR;
		अवरोध;
	हाल MCDE_EXTSRC_4:
		conf = MCDE_EXTSRC4CONF;
		cr = MCDE_EXTSRC4CR;
		अवरोध;
	हाल MCDE_EXTSRC_5:
		conf = MCDE_EXTSRC5CONF;
		cr = MCDE_EXTSRC5CR;
		अवरोध;
	हाल MCDE_EXTSRC_6:
		conf = MCDE_EXTSRC6CONF;
		cr = MCDE_EXTSRC6CR;
		अवरोध;
	हाल MCDE_EXTSRC_7:
		conf = MCDE_EXTSRC7CONF;
		cr = MCDE_EXTSRC7CR;
		अवरोध;
	हाल MCDE_EXTSRC_8:
		conf = MCDE_EXTSRC8CONF;
		cr = MCDE_EXTSRC8CR;
		अवरोध;
	हाल MCDE_EXTSRC_9:
		conf = MCDE_EXTSRC9CONF;
		cr = MCDE_EXTSRC9CR;
		अवरोध;
	पूर्ण

	/*
	 * Configure बाह्यal source 0 one buffer (buffer 0)
	 * primary overlay ID 0.
	 * From mcde_hw.c ovly_update_रेजिस्टरs() in the venकरोr tree
	 */
	val = 0 << MCDE_EXTSRCXCONF_BUF_ID_SHIFT;
	val |= 1 << MCDE_EXTSRCXCONF_BUF_NB_SHIFT;
	val |= 0 << MCDE_EXTSRCXCONF_PRI_OVLID_SHIFT;

	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_ARGB8888:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	हाल DRM_FORMAT_ABGR8888:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		val |= MCDE_EXTSRCXCONF_BPP_XRGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
		val |= MCDE_EXTSRCXCONF_BPP_XRGB8888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		अवरोध;
	हाल DRM_FORMAT_RGB888:
		val |= MCDE_EXTSRCXCONF_BPP_RGB888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	हाल DRM_FORMAT_BGR888:
		val |= MCDE_EXTSRCXCONF_BPP_RGB888 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		अवरोध;
	हाल DRM_FORMAT_ARGB4444:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB4444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	हाल DRM_FORMAT_ABGR4444:
		val |= MCDE_EXTSRCXCONF_BPP_ARGB4444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		अवरोध;
	हाल DRM_FORMAT_XRGB4444:
		val |= MCDE_EXTSRCXCONF_BPP_RGB444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	हाल DRM_FORMAT_XBGR4444:
		val |= MCDE_EXTSRCXCONF_BPP_RGB444 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		val |= MCDE_EXTSRCXCONF_BPP_IRGB1555 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	हाल DRM_FORMAT_XBGR1555:
		val |= MCDE_EXTSRCXCONF_BPP_IRGB1555 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		val |= MCDE_EXTSRCXCONF_BPP_RGB565 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	हाल DRM_FORMAT_BGR565:
		val |= MCDE_EXTSRCXCONF_BPP_RGB565 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		val |= MCDE_EXTSRCXCONF_BGR;
		अवरोध;
	हाल DRM_FORMAT_YUV422:
		val |= MCDE_EXTSRCXCONF_BPP_YCBCR422 <<
			MCDE_EXTSRCXCONF_BPP_SHIFT;
		अवरोध;
	शेष:
		dev_err(mcde->dev, "Unknown pixel format 0x%08x\n",
			क्रमmat);
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(val, mcde->regs + conf);

	/* Software select, primary */
	val = MCDE_EXTSRCXCR_SEL_MOD_SOFTWARE_SEL;
	val |= MCDE_EXTSRCXCR_MULTIOVL_CTRL_PRIMARY;
	ग_लिखोl(val, mcde->regs + cr);

	वापस 0;
पूर्ण

अटल व्योम mcde_configure_overlay(काष्ठा mcde *mcde, क्रमागत mcde_overlay ovl,
				   क्रमागत mcde_extsrc src,
				   क्रमागत mcde_channel ch,
				   स्थिर काष्ठा drm_display_mode *mode,
				   u32 क्रमmat, पूर्णांक cpp)
अणु
	u32 val;
	u32 conf1;
	u32 conf2;
	u32 crop;
	u32 ljinc;
	u32 cr;
	u32 comp;
	u32 pixel_fetcher_watermark;

	चयन (ovl) अणु
	हाल MCDE_OVERLAY_0:
		conf1 = MCDE_OVL0CONF;
		conf2 = MCDE_OVL0CONF2;
		crop = MCDE_OVL0CROP;
		ljinc = MCDE_OVL0LJINC;
		cr = MCDE_OVL0CR;
		comp = MCDE_OVL0COMP;
		अवरोध;
	हाल MCDE_OVERLAY_1:
		conf1 = MCDE_OVL1CONF;
		conf2 = MCDE_OVL1CONF2;
		crop = MCDE_OVL1CROP;
		ljinc = MCDE_OVL1LJINC;
		cr = MCDE_OVL1CR;
		comp = MCDE_OVL1COMP;
		अवरोध;
	हाल MCDE_OVERLAY_2:
		conf1 = MCDE_OVL2CONF;
		conf2 = MCDE_OVL2CONF2;
		crop = MCDE_OVL2CROP;
		ljinc = MCDE_OVL2LJINC;
		cr = MCDE_OVL2CR;
		comp = MCDE_OVL2COMP;
		अवरोध;
	हाल MCDE_OVERLAY_3:
		conf1 = MCDE_OVL3CONF;
		conf2 = MCDE_OVL3CONF2;
		crop = MCDE_OVL3CROP;
		ljinc = MCDE_OVL3LJINC;
		cr = MCDE_OVL3CR;
		comp = MCDE_OVL3COMP;
		अवरोध;
	हाल MCDE_OVERLAY_4:
		conf1 = MCDE_OVL4CONF;
		conf2 = MCDE_OVL4CONF2;
		crop = MCDE_OVL4CROP;
		ljinc = MCDE_OVL4LJINC;
		cr = MCDE_OVL4CR;
		comp = MCDE_OVL4COMP;
		अवरोध;
	हाल MCDE_OVERLAY_5:
		conf1 = MCDE_OVL5CONF;
		conf2 = MCDE_OVL5CONF2;
		crop = MCDE_OVL5CROP;
		ljinc = MCDE_OVL5LJINC;
		cr = MCDE_OVL5CR;
		comp = MCDE_OVL5COMP;
		अवरोध;
	पूर्ण

	val = mode->hdisplay << MCDE_OVLXCONF_PPL_SHIFT;
	val |= mode->vdisplay << MCDE_OVLXCONF_LPF_SHIFT;
	/* Use बाह्यal source 0 that we just configured */
	val |= src << MCDE_OVLXCONF_EXTSRC_ID_SHIFT;
	ग_लिखोl(val, mcde->regs + conf1);

	val = MCDE_OVLXCONF2_BP_PER_PIXEL_ALPHA;
	val |= 0xff << MCDE_OVLXCONF2_ALPHAVALUE_SHIFT;
	/* OPQ: overlay is opaque */
	चयन (क्रमmat) अणु
	हाल DRM_FORMAT_ARGB8888:
	हाल DRM_FORMAT_ABGR8888:
	हाल DRM_FORMAT_ARGB4444:
	हाल DRM_FORMAT_ABGR4444:
	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_XBGR1555:
		/* No OPQ */
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_XBGR8888:
	हाल DRM_FORMAT_RGB888:
	हाल DRM_FORMAT_BGR888:
	हाल DRM_FORMAT_RGB565:
	हाल DRM_FORMAT_BGR565:
	हाल DRM_FORMAT_YUV422:
		val |= MCDE_OVLXCONF2_OPQ;
		अवरोध;
	शेष:
		dev_err(mcde->dev, "Unknown pixel format 0x%08x\n",
			क्रमmat);
		अवरोध;
	पूर्ण

	/*
	 * Pixel fetch watermark level is max 0x1FFF pixels.
	 * Two basic rules should be followed:
	 * 1. The value should be at least 256 bits.
	 * 2. The sum of all active overlays pixelfetch watermark level
	 *    multiplied with bits per pixel, should be lower than the
	 *    size of input_fअगरo_size in bits.
	 * 3. The value should be a multiple of a line (256 bits).
	 */
	चयन (cpp) अणु
	हाल 2:
		pixel_fetcher_watermark = 128;
		अवरोध;
	हाल 3:
		pixel_fetcher_watermark = 96;
		अवरोध;
	हाल 4:
		pixel_fetcher_watermark = 48;
		अवरोध;
	शेष:
		pixel_fetcher_watermark = 48;
		अवरोध;
	पूर्ण
	dev_dbg(mcde->dev, "pixel fetcher watermark level %d pixels\n",
		pixel_fetcher_watermark);
	val |= pixel_fetcher_watermark << MCDE_OVLXCONF2_PIXELFETCHERWATERMARKLEVEL_SHIFT;
	ग_लिखोl(val, mcde->regs + conf2);

	/* Number of bytes to fetch per line */
	ग_लिखोl(mcde->stride, mcde->regs + ljinc);
	/* No cropping */
	ग_लिखोl(0, mcde->regs + crop);

	/* Set up overlay control रेजिस्टर */
	val = MCDE_OVLXCR_OVLEN;
	val |= MCDE_OVLXCR_COLCCTRL_DISABLED;
	val |= MCDE_OVLXCR_BURSTSIZE_8W <<
		MCDE_OVLXCR_BURSTSIZE_SHIFT;
	val |= MCDE_OVLXCR_MAXOUTSTANDING_8_REQ <<
		MCDE_OVLXCR_MAXOUTSTANDING_SHIFT;
	/* Not using rotation but set it up anyways */
	val |= MCDE_OVLXCR_ROTBURSTSIZE_8W <<
		MCDE_OVLXCR_ROTBURSTSIZE_SHIFT;
	ग_लिखोl(val, mcde->regs + cr);

	/*
	 * Set up the overlay compositor to route the overlay out to
	 * the desired channel
	 */
	val = ch << MCDE_OVLXCOMP_CH_ID_SHIFT;
	ग_लिखोl(val, mcde->regs + comp);
पूर्ण

अटल व्योम mcde_configure_channel(काष्ठा mcde *mcde, क्रमागत mcde_channel ch,
				   क्रमागत mcde_fअगरo fअगरo,
				   स्थिर काष्ठा drm_display_mode *mode)
अणु
	u32 val;
	u32 conf;
	u32 sync;
	u32 stat;
	u32 bgcol;
	u32 mux;

	चयन (ch) अणु
	हाल MCDE_CHANNEL_0:
		conf = MCDE_CHNL0CONF;
		sync = MCDE_CHNL0SYNCHMOD;
		stat = MCDE_CHNL0STAT;
		bgcol = MCDE_CHNL0BCKGNDCOL;
		mux = MCDE_CHNL0MUXING;
		अवरोध;
	हाल MCDE_CHANNEL_1:
		conf = MCDE_CHNL1CONF;
		sync = MCDE_CHNL1SYNCHMOD;
		stat = MCDE_CHNL1STAT;
		bgcol = MCDE_CHNL1BCKGNDCOL;
		mux = MCDE_CHNL1MUXING;
		अवरोध;
	हाल MCDE_CHANNEL_2:
		conf = MCDE_CHNL2CONF;
		sync = MCDE_CHNL2SYNCHMOD;
		stat = MCDE_CHNL2STAT;
		bgcol = MCDE_CHNL2BCKGNDCOL;
		mux = MCDE_CHNL2MUXING;
		अवरोध;
	हाल MCDE_CHANNEL_3:
		conf = MCDE_CHNL3CONF;
		sync = MCDE_CHNL3SYNCHMOD;
		stat = MCDE_CHNL3STAT;
		bgcol = MCDE_CHNL3BCKGNDCOL;
		mux = MCDE_CHNL3MUXING;
		वापस;
	पूर्ण

	/* Set up channel 0 sync (based on chnl_update_रेजिस्टरs()) */
	चयन (mcde->flow_mode) अणु
	हाल MCDE_COMMAND_ONESHOT_FLOW:
		/* Oneshot is achieved with software sync */
		val = MCDE_CHNLXSYNCHMOD_SRC_SYNCH_SOFTWARE
			<< MCDE_CHNLXSYNCHMOD_SRC_SYNCH_SHIFT;
		अवरोध;
	हाल MCDE_COMMAND_TE_FLOW:
		val = MCDE_CHNLXSYNCHMOD_SRC_SYNCH_HARDWARE
			<< MCDE_CHNLXSYNCHMOD_SRC_SYNCH_SHIFT;
		val |= MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_TE0
			<< MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_SHIFT;
		अवरोध;
	हाल MCDE_COMMAND_BTA_TE_FLOW:
		val = MCDE_CHNLXSYNCHMOD_SRC_SYNCH_HARDWARE
			<< MCDE_CHNLXSYNCHMOD_SRC_SYNCH_SHIFT;
		/*
		 * TODO:
		 * The venकरोr driver uses the क्रमmatter as sync source
		 * क्रम BTA TE mode. Test to use TE अगर you have a panel
		 * that uses this mode.
		 */
		val |= MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_FORMATTER
			<< MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_SHIFT;
		अवरोध;
	हाल MCDE_VIDEO_TE_FLOW:
		val = MCDE_CHNLXSYNCHMOD_SRC_SYNCH_HARDWARE
			<< MCDE_CHNLXSYNCHMOD_SRC_SYNCH_SHIFT;
		val |= MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_TE0
			<< MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_SHIFT;
		अवरोध;
	हाल MCDE_VIDEO_FORMATTER_FLOW:
	हाल MCDE_DPI_FORMATTER_FLOW:
		val = MCDE_CHNLXSYNCHMOD_SRC_SYNCH_HARDWARE
			<< MCDE_CHNLXSYNCHMOD_SRC_SYNCH_SHIFT;
		val |= MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_FORMATTER
			<< MCDE_CHNLXSYNCHMOD_OUT_SYNCH_SRC_SHIFT;
		अवरोध;
	शेष:
		dev_err(mcde->dev, "unknown flow mode %d\n",
			mcde->flow_mode);
		वापस;
	पूर्ण

	ग_लिखोl(val, mcde->regs + sync);

	/* Set up pixels per line and lines per frame */
	val = (mode->hdisplay - 1) << MCDE_CHNLXCONF_PPL_SHIFT;
	val |= (mode->vdisplay - 1) << MCDE_CHNLXCONF_LPF_SHIFT;
	ग_लिखोl(val, mcde->regs + conf);

	/*
	 * Normalize color conversion:
	 * black background, OLED conversion disable on channel
	 */
	val = MCDE_CHNLXSTAT_CHNLBLBCKGND_EN |
		MCDE_CHNLXSTAT_CHNLRD;
	ग_लिखोl(val, mcde->regs + stat);
	ग_लिखोl(0, mcde->regs + bgcol);

	/* Set up muxing: connect the channel to the desired FIFO */
	चयन (fअगरo) अणु
	हाल MCDE_FIFO_A:
		ग_लिखोl(MCDE_CHNLXMUXING_FIFO_ID_FIFO_A,
		       mcde->regs + mux);
		अवरोध;
	हाल MCDE_FIFO_B:
		ग_लिखोl(MCDE_CHNLXMUXING_FIFO_ID_FIFO_B,
		       mcde->regs + mux);
		अवरोध;
	पूर्ण

	/*
	 * If using DPI configure the sync event.
	 * TODO: this is क्रम LCD only, it करोes not cover TV out.
	 */
	अगर (mcde->dpi_output) अणु
		u32 stripwidth;

		stripwidth = 0xF000 / (mode->vdisplay * 4);
		dev_info(mcde->dev, "stripwidth: %d\n", stripwidth);

		val = MCDE_SYNCHCONF_HWREQVEVENT_ACTIVE_VIDEO |
			(mode->hdisplay - 1 - stripwidth) << MCDE_SYNCHCONF_HWREQVCNT_SHIFT |
			MCDE_SYNCHCONF_SWINTVEVENT_ACTIVE_VIDEO |
			(mode->hdisplay - 1 - stripwidth) << MCDE_SYNCHCONF_SWINTVCNT_SHIFT;

		चयन (fअगरo) अणु
		हाल MCDE_FIFO_A:
			ग_लिखोl(val, mcde->regs + MCDE_SYNCHCONFA);
			अवरोध;
		हाल MCDE_FIFO_B:
			ग_लिखोl(val, mcde->regs + MCDE_SYNCHCONFB);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mcde_configure_fअगरo(काष्ठा mcde *mcde, क्रमागत mcde_fअगरo fअगरo,
				क्रमागत mcde_क्रमmatter fmt,
				पूर्णांक fअगरo_wtrmrk)
अणु
	u32 val;
	u32 ctrl;
	u32 cr0, cr1;

	चयन (fअगरo) अणु
	हाल MCDE_FIFO_A:
		ctrl = MCDE_CTRLA;
		cr0 = MCDE_CRA0;
		cr1 = MCDE_CRA1;
		अवरोध;
	हाल MCDE_FIFO_B:
		ctrl = MCDE_CTRLB;
		cr0 = MCDE_CRB0;
		cr1 = MCDE_CRB1;
		अवरोध;
	पूर्ण

	val = fअगरo_wtrmrk << MCDE_CTRLX_FIFOWTRMRK_SHIFT;

	/*
	 * Select the क्रमmatter to use क्रम this FIFO
	 *
	 * The रेजिस्टर definitions imply that dअगरferent IDs should be used
	 * by the DSI क्रमmatters depending on अगर they are in VID or CMD
	 * mode, and the manual says they are dedicated but identical.
	 * The venकरोr code uses them as it seems fit.
	 */
	चयन (fmt) अणु
	हाल MCDE_DSI_FORMATTER_0:
		val |= MCDE_CTRLX_FORMTYPE_DSI << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DSI0VID << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	हाल MCDE_DSI_FORMATTER_1:
		val |= MCDE_CTRLX_FORMTYPE_DSI << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DSI0CMD << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	हाल MCDE_DSI_FORMATTER_2:
		val |= MCDE_CTRLX_FORMTYPE_DSI << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DSI1VID << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	हाल MCDE_DSI_FORMATTER_3:
		val |= MCDE_CTRLX_FORMTYPE_DSI << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DSI1CMD << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	हाल MCDE_DSI_FORMATTER_4:
		val |= MCDE_CTRLX_FORMTYPE_DSI << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DSI2VID << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	हाल MCDE_DSI_FORMATTER_5:
		val |= MCDE_CTRLX_FORMTYPE_DSI << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DSI2CMD << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	हाल MCDE_DPI_FORMATTER_0:
		val |= MCDE_CTRLX_FORMTYPE_DPITV << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DPIA << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	हाल MCDE_DPI_FORMATTER_1:
		val |= MCDE_CTRLX_FORMTYPE_DPITV << MCDE_CTRLX_FORMTYPE_SHIFT;
		val |= MCDE_CTRLX_FORMID_DPIB << MCDE_CTRLX_FORMID_SHIFT;
		अवरोध;
	पूर्ण
	ग_लिखोl(val, mcde->regs + ctrl);

	/* Blend source with Alpha 0xff on FIFO */
	val = MCDE_CRX0_BLENDEN |
		0xff << MCDE_CRX0_ALPHABLEND_SHIFT;
	ग_लिखोl(val, mcde->regs + cr0);

	spin_lock(&mcde->fअगरo_crx1_lock);
	val = पढ़ोl(mcde->regs + cr1);
	/*
	 * Set-up from mcde_fmtr_dsi.c, fmtr_dsi_enable_video()
	 * FIXME: a dअगरferent घड़ी needs to be selected क्रम TV out.
	 */
	अगर (mcde->dpi_output) अणु
		काष्ठा drm_connector *connector = drm_panel_bridge_connector(mcde->bridge);
		u32 bus_क्रमmat;

		/* Assume RGB888 24 bit अगर we have no further info */
		अगर (!connector->display_info.num_bus_क्रमmats) अणु
			dev_info(mcde->dev, "panel does not specify bus format, assume RGB888\n");
			bus_क्रमmat = MEDIA_BUS_FMT_RGB888_1X24;
		पूर्ण अन्यथा अणु
			bus_क्रमmat = connector->display_info.bus_क्रमmats[0];
		पूर्ण

		/*
		 * Set up the CDWIN and OUTBPP क्रम the LCD
		 *
		 * FIXME: fill this in अगर you know the correspondance between the MIPI
		 * DPI specअगरication and the media bus क्रमmats.
		 */
		val &= ~MCDE_CRX1_CDWIN_MASK;
		val &= ~MCDE_CRX1_OUTBPP_MASK;
		चयन (bus_क्रमmat) अणु
		हाल MEDIA_BUS_FMT_RGB888_1X24:
			val |= MCDE_CRX1_CDWIN_24BPP << MCDE_CRX1_CDWIN_SHIFT;
			val |= MCDE_CRX1_OUTBPP_24BPP << MCDE_CRX1_OUTBPP_SHIFT;
			अवरोध;
		शेष:
			dev_err(mcde->dev, "unknown bus format, assume RGB888\n");
			val |= MCDE_CRX1_CDWIN_24BPP << MCDE_CRX1_CDWIN_SHIFT;
			val |= MCDE_CRX1_OUTBPP_24BPP << MCDE_CRX1_OUTBPP_SHIFT;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Use the MCDE घड़ी क्रम DSI */
		val &= ~MCDE_CRX1_CLKSEL_MASK;
		val |= MCDE_CRX1_CLKSEL_MCDECLK << MCDE_CRX1_CLKSEL_SHIFT;
	पूर्ण
	ग_लिखोl(val, mcde->regs + cr1);
	spin_unlock(&mcde->fअगरo_crx1_lock);
पूर्ण;

अटल व्योम mcde_configure_dsi_क्रमmatter(काष्ठा mcde *mcde,
					 क्रमागत mcde_क्रमmatter fmt,
					 u32 क्रमmatter_frame,
					 पूर्णांक pkt_size)
अणु
	u32 val;
	u32 conf0;
	u32 frame;
	u32 pkt;
	u32 sync;
	u32 cmdw;
	u32 delay0, delay1;

	चयन (fmt) अणु
	हाल MCDE_DSI_FORMATTER_0:
		conf0 = MCDE_DSIVID0CONF0;
		frame = MCDE_DSIVID0FRAME;
		pkt = MCDE_DSIVID0PKT;
		sync = MCDE_DSIVID0SYNC;
		cmdw = MCDE_DSIVID0CMDW;
		delay0 = MCDE_DSIVID0DELAY0;
		delay1 = MCDE_DSIVID0DELAY1;
		अवरोध;
	हाल MCDE_DSI_FORMATTER_1:
		conf0 = MCDE_DSIVID1CONF0;
		frame = MCDE_DSIVID1FRAME;
		pkt = MCDE_DSIVID1PKT;
		sync = MCDE_DSIVID1SYNC;
		cmdw = MCDE_DSIVID1CMDW;
		delay0 = MCDE_DSIVID1DELAY0;
		delay1 = MCDE_DSIVID1DELAY1;
		अवरोध;
	हाल MCDE_DSI_FORMATTER_2:
		conf0 = MCDE_DSIVID2CONF0;
		frame = MCDE_DSIVID2FRAME;
		pkt = MCDE_DSIVID2PKT;
		sync = MCDE_DSIVID2SYNC;
		cmdw = MCDE_DSIVID2CMDW;
		delay0 = MCDE_DSIVID2DELAY0;
		delay1 = MCDE_DSIVID2DELAY1;
		अवरोध;
	शेष:
		dev_err(mcde->dev, "tried to configure a non-DSI formatter as DSI\n");
		वापस;
	पूर्ण

	/*
	 * Enable क्रमmatter
	 * 8 bit commands and DCS commands (notgen = not generic)
	 */
	val = MCDE_DSICONF0_CMD8 | MCDE_DSICONF0_DCSVID_NOTGEN;
	अगर (mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO)
		val |= MCDE_DSICONF0_VID_MODE_VID;
	चयन (mcde->mdsi->क्रमmat) अणु
	हाल MIPI_DSI_FMT_RGB888:
		val |= MCDE_DSICONF0_PACKING_RGB888 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		val |= MCDE_DSICONF0_PACKING_RGB666 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		dev_err(mcde->dev,
			"we cannot handle the packed RGB666 format\n");
		val |= MCDE_DSICONF0_PACKING_RGB666 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		val |= MCDE_DSICONF0_PACKING_RGB565 <<
			MCDE_DSICONF0_PACKING_SHIFT;
		अवरोध;
	शेष:
		dev_err(mcde->dev, "unknown DSI format\n");
		वापस;
	पूर्ण
	ग_लिखोl(val, mcde->regs + conf0);

	ग_लिखोl(क्रमmatter_frame, mcde->regs + frame);
	ग_लिखोl(pkt_size, mcde->regs + pkt);
	ग_लिखोl(0, mcde->regs + sync);
	/* Define the MIPI command: we want to ग_लिखो पूर्णांकo display memory */
	val = MIPI_DCS_WRITE_MEMORY_CONTINUE <<
		MCDE_DSIVIDXCMDW_CMDW_CONTINUE_SHIFT;
	val |= MIPI_DCS_WRITE_MEMORY_START <<
		MCDE_DSIVIDXCMDW_CMDW_START_SHIFT;
	ग_लिखोl(val, mcde->regs + cmdw);

	/*
	 * FIXME: the venकरोr driver has some hack around this value in
	 * CMD mode with स्वतःtrig.
	 */
	ग_लिखोl(0, mcde->regs + delay0);
	ग_लिखोl(0, mcde->regs + delay1);
पूर्ण

अटल व्योम mcde_enable_fअगरo(काष्ठा mcde *mcde, क्रमागत mcde_fअगरo fअगरo)
अणु
	u32 val;
	u32 cr;

	चयन (fअगरo) अणु
	हाल MCDE_FIFO_A:
		cr = MCDE_CRA0;
		अवरोध;
	हाल MCDE_FIFO_B:
		cr = MCDE_CRB0;
		अवरोध;
	शेष:
		dev_err(mcde->dev, "cannot enable FIFO %c\n",
			'A' + fअगरo);
		वापस;
	पूर्ण

	spin_lock(&mcde->flow_lock);
	val = पढ़ोl(mcde->regs + cr);
	val |= MCDE_CRX0_FLOEN;
	ग_लिखोl(val, mcde->regs + cr);
	mcde->flow_active++;
	spin_unlock(&mcde->flow_lock);
पूर्ण

अटल व्योम mcde_disable_fअगरo(काष्ठा mcde *mcde, क्रमागत mcde_fअगरo fअगरo,
			      bool रुको_क्रम_drain)
अणु
	पूर्णांक समयout = 100;
	u32 val;
	u32 cr;

	चयन (fअगरo) अणु
	हाल MCDE_FIFO_A:
		cr = MCDE_CRA0;
		अवरोध;
	हाल MCDE_FIFO_B:
		cr = MCDE_CRB0;
		अवरोध;
	शेष:
		dev_err(mcde->dev, "cannot disable FIFO %c\n",
			'A' + fअगरo);
		वापस;
	पूर्ण

	spin_lock(&mcde->flow_lock);
	val = पढ़ोl(mcde->regs + cr);
	val &= ~MCDE_CRX0_FLOEN;
	ग_लिखोl(val, mcde->regs + cr);
	mcde->flow_active = 0;
	spin_unlock(&mcde->flow_lock);

	अगर (!रुको_क्रम_drain)
		वापस;

	/* Check that we really drained and stopped the flow */
	जबतक (पढ़ोl(mcde->regs + cr) & MCDE_CRX0_FLOEN) अणु
		usleep_range(1000, 1500);
		अगर (!--समयout) अणु
			dev_err(mcde->dev,
				"FIFO timeout while clearing FIFO %c\n",
				'A' + fअगरo);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * This drains a pipe i.e. a FIFO connected to a certain channel
 */
अटल व्योम mcde_drain_pipe(काष्ठा mcde *mcde, क्रमागत mcde_fअगरo fअगरo,
			    क्रमागत mcde_channel ch)
अणु
	u32 val;
	u32 ctrl;
	u32 synsw;

	चयन (fअगरo) अणु
	हाल MCDE_FIFO_A:
		ctrl = MCDE_CTRLA;
		अवरोध;
	हाल MCDE_FIFO_B:
		ctrl = MCDE_CTRLB;
		अवरोध;
	पूर्ण

	चयन (ch) अणु
	हाल MCDE_CHANNEL_0:
		synsw = MCDE_CHNL0SYNCHSW;
		अवरोध;
	हाल MCDE_CHANNEL_1:
		synsw = MCDE_CHNL1SYNCHSW;
		अवरोध;
	हाल MCDE_CHANNEL_2:
		synsw = MCDE_CHNL2SYNCHSW;
		अवरोध;
	हाल MCDE_CHANNEL_3:
		synsw = MCDE_CHNL3SYNCHSW;
		वापस;
	पूर्ण

	val = पढ़ोl(mcde->regs + ctrl);
	अगर (!(val & MCDE_CTRLX_FIFOEMPTY)) अणु
		dev_err(mcde->dev, "Channel A FIFO not empty (handover)\n");
		/* Attempt to clear the FIFO */
		mcde_enable_fअगरo(mcde, fअगरo);
		/* Trigger a software sync out on respective channel (0-3) */
		ग_लिखोl(MCDE_CHNLXSYNCHSW_SW_TRIG, mcde->regs + synsw);
		/* Disable FIFO A flow again */
		mcde_disable_fअगरo(mcde, fअगरo, true);
	पूर्ण
पूर्ण

अटल पूर्णांक mcde_dsi_get_pkt_भाग(पूर्णांक ppl, पूर्णांक fअगरo_size)
अणु
	/*
	 * DSI command mode line packets should be split पूर्णांकo an even number of
	 * packets smaller than or equal to the fअगरo size.
	 */
	पूर्णांक भाग;
	स्थिर पूर्णांक max_भाग = DIV_ROUND_UP(MCDE_MAX_WIDTH, fअगरo_size);

	क्रम (भाग = 1; भाग < max_भाग; भाग++)
		अगर (ppl % भाग == 0 && ppl / भाग <= fअगरo_size)
			वापस भाग;
	वापस 1;
पूर्ण

अटल व्योम mcde_setup_dpi(काष्ठा mcde *mcde, स्थिर काष्ठा drm_display_mode *mode,
			   पूर्णांक *fअगरo_wtrmrk_lvl)
अणु
	काष्ठा drm_connector *connector = drm_panel_bridge_connector(mcde->bridge);
	u32 hsw, hfp, hbp;
	u32 vsw, vfp, vbp;
	u32 val;

	/* FIXME: we only support LCD, implement TV out */
	hsw = mode->hsync_end - mode->hsync_start;
	hfp = mode->hsync_start - mode->hdisplay;
	hbp = mode->htotal - mode->hsync_end;
	vsw = mode->vsync_end - mode->vsync_start;
	vfp = mode->vsync_start - mode->vdisplay;
	vbp = mode->vtotal - mode->vsync_end;

	dev_info(mcde->dev, "output on DPI LCD from channel A\n");
	/* Display actual values */
	dev_info(mcde->dev, "HSW: %d, HFP: %d, HBP: %d, VSW: %d, VFP: %d, VBP: %d\n",
		 hsw, hfp, hbp, vsw, vfp, vbp);

	/*
	 * The pixel fetcher is 128 64-bit words deep = 1024 bytes.
	 * One overlay of 32bpp (4 cpp) assumed, fetch 160 pixels.
	 * 160 * 4 = 640 bytes.
	 */
	*fअगरo_wtrmrk_lvl = 640;

	/* Set up the मुख्य control, watermark level at 7 */
	val = 7 << MCDE_CONF0_IFIFOCTRLWTRMRKLVL_SHIFT;

	/*
	 * This sets up the पूर्णांकernal silicon muxing of the DPI
	 * lines. This is how the silicon connects out to the
	 * बाह्यal pins, then the pins need to be further
	 * configured पूर्णांकo "alternate functions" using pin control
	 * to actually get the संकेतs out.
	 *
	 * FIXME: this is hardcoded to the only setting found in
	 * the wild. If we need to use dअगरferent settings क्रम
	 * dअगरferent DPI displays, make this parameterizable from
	 * the device tree.
	 */
	/* 24 bits DPI: connect Ch A LSB to D[0:7] */
	val |= 0 << MCDE_CONF0_OUTMUX0_SHIFT;
	/* 24 bits DPI: connect Ch A MID to D[8:15] */
	val |= 1 << MCDE_CONF0_OUTMUX1_SHIFT;
	/* Don't care about this muxing */
	val |= 0 << MCDE_CONF0_OUTMUX2_SHIFT;
	/* Don't care about this muxing */
	val |= 0 << MCDE_CONF0_OUTMUX3_SHIFT;
	/* 24 bits DPI: connect Ch A MSB to D[32:39] */
	val |= 2 << MCDE_CONF0_OUTMUX4_SHIFT;
	/* Syncmux bits zero: DPI channel A */
	ग_लिखोl(val, mcde->regs + MCDE_CONF0);

	/* This hammers us पूर्णांकo LCD mode */
	ग_लिखोl(0, mcde->regs + MCDE_TVCRA);

	/* Front porch and sync width */
	val = (vsw << MCDE_TVBL1_BEL1_SHIFT);
	val |= (vfp << MCDE_TVBL1_BSL1_SHIFT);
	ग_लिखोl(val, mcde->regs + MCDE_TVBL1A);
	/* The venकरोr driver sets the same value पूर्णांकo TVBL2A */
	ग_लिखोl(val, mcde->regs + MCDE_TVBL2A);

	/* Vertical back porch */
	val = (vbp << MCDE_TVDVO_DVO1_SHIFT);
	/* The venकरोr drivers sets the same value पूर्णांकo TVDVOA */
	val |= (vbp << MCDE_TVDVO_DVO2_SHIFT);
	ग_लिखोl(val, mcde->regs + MCDE_TVDVOA);

	/* Horizontal back porch, as 0 = 1 cycle we need to subtract 1 */
	ग_लिखोl((hbp - 1), mcde->regs + MCDE_TVTIM1A);

	/* Horizongal sync width and horizonal front porch, 0 = 1 cycle */
	val = ((hsw - 1) << MCDE_TVLBALW_LBW_SHIFT);
	val |= ((hfp - 1) << MCDE_TVLBALW_ALW_SHIFT);
	ग_लिखोl(val, mcde->regs + MCDE_TVLBALWA);

	/* Blank some TV रेजिस्टरs we करोn't use */
	ग_लिखोl(0, mcde->regs + MCDE_TVISLA);
	ग_लिखोl(0, mcde->regs + MCDE_TVBLUA);

	/* Set up sync inversion etc */
	val = 0;
	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		val |= MCDE_LCDTIM1B_IHS;
	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		val |= MCDE_LCDTIM1B_IVS;
	अगर (connector->display_info.bus_flags & DRM_BUS_FLAG_DE_LOW)
		val |= MCDE_LCDTIM1B_IOE;
	अगर (connector->display_info.bus_flags & DRM_BUS_FLAG_PIXDATA_DRIVE_NEGEDGE)
		val |= MCDE_LCDTIM1B_IPC;
	ग_लिखोl(val, mcde->regs + MCDE_LCDTIM1A);
पूर्ण

अटल व्योम mcde_setup_dsi(काष्ठा mcde *mcde, स्थिर काष्ठा drm_display_mode *mode,
			   पूर्णांक cpp, पूर्णांक *fअगरo_wtrmrk_lvl, पूर्णांक *dsi_क्रमmatter_frame,
			   पूर्णांक *dsi_pkt_size)
अणु
	u32 क्रमmatter_ppl = mode->hdisplay; /* pixels per line */
	u32 क्रमmatter_lpf = mode->vdisplay; /* lines per frame */
	पूर्णांक क्रमmatter_frame;
	पूर्णांक क्रमmatter_cpp;
	पूर्णांक fअगरo_wtrmrk;
	u32 pkt_भाग;
	पूर्णांक pkt_size;
	u32 val;

	dev_info(mcde->dev, "output in %s mode, format %dbpp\n",
		 (mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) ?
		 "VIDEO" : "CMD",
		 mipi_dsi_pixel_क्रमmat_to_bpp(mcde->mdsi->क्रमmat));
	क्रमmatter_cpp =
		mipi_dsi_pixel_क्रमmat_to_bpp(mcde->mdsi->क्रमmat) / 8;
	dev_info(mcde->dev, "Overlay CPP: %d bytes, DSI formatter CPP %d bytes\n",
		 cpp, क्रमmatter_cpp);

	/* Set up the मुख्य control, watermark level at 7 */
	val = 7 << MCDE_CONF0_IFIFOCTRLWTRMRKLVL_SHIFT;

	/*
	 * This is the पूर्णांकernal silicon muxing of the DPI
	 * (parallell display) lines. Since we are not using
	 * this at all (we are using DSI) these are just
	 * dummy values from the venकरोr tree.
	 */
	val |= 3 << MCDE_CONF0_OUTMUX0_SHIFT;
	val |= 3 << MCDE_CONF0_OUTMUX1_SHIFT;
	val |= 0 << MCDE_CONF0_OUTMUX2_SHIFT;
	val |= 4 << MCDE_CONF0_OUTMUX3_SHIFT;
	val |= 5 << MCDE_CONF0_OUTMUX4_SHIFT;
	ग_लिखोl(val, mcde->regs + MCDE_CONF0);

	/* Calculations from mcde_fmtr_dsi.c, fmtr_dsi_enable_video() */

	/*
	 * Set up FIFO A watermark level:
	 * 128 क्रम LCD 32bpp video mode
	 * 48  क्रम LCD 32bpp command mode
	 * 128 क्रम LCD 16bpp video mode
	 * 64  क्रम LCD 16bpp command mode
	 * 128 क्रम HDMI 32bpp
	 * 192 क्रम HDMI 16bpp
	 */
	fअगरo_wtrmrk = mode->hdisplay;
	अगर (mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		fअगरo_wtrmrk = min(fअगरo_wtrmrk, 128);
		pkt_भाग = 1;
	पूर्ण अन्यथा अणु
		fअगरo_wtrmrk = min(fअगरo_wtrmrk, 48);
		/* The FIFO is 640 entries deep on this v3 hardware */
		pkt_भाग = mcde_dsi_get_pkt_भाग(mode->hdisplay, 640);
	पूर्ण
	dev_dbg(mcde->dev, "FIFO watermark after flooring: %d bytes\n",
		fअगरo_wtrmrk);
	dev_dbg(mcde->dev, "Packet divisor: %d bytes\n", pkt_भाग);

	/* NOTE: pkt_भाग is 1 क्रम video mode */
	pkt_size = (क्रमmatter_ppl * क्रमmatter_cpp) / pkt_भाग;
	/* Commands CMD8 need one extra byte */
	अगर (!(mcde->mdsi->mode_flags & MIPI_DSI_MODE_VIDEO))
		pkt_size++;

	dev_dbg(mcde->dev, "DSI packet size: %d * %d bytes per line\n",
		pkt_size, pkt_भाग);
	dev_dbg(mcde->dev, "Overlay frame size: %u bytes\n",
		mode->hdisplay * mode->vdisplay * cpp);
	/* NOTE: pkt_भाग is 1 क्रम video mode */
	क्रमmatter_frame = pkt_size * pkt_भाग * क्रमmatter_lpf;
	dev_dbg(mcde->dev, "Formatter frame size: %u bytes\n", क्रमmatter_frame);

	*fअगरo_wtrmrk_lvl = fअगरo_wtrmrk;
	*dsi_pkt_size = pkt_size;
	*dsi_क्रमmatter_frame = क्रमmatter_frame;
पूर्ण

अटल व्योम mcde_display_enable(काष्ठा drm_simple_display_pipe *pipe,
				काष्ठा drm_crtc_state *cstate,
				काष्ठा drm_plane_state *plane_state)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा mcde *mcde = to_mcde(drm);
	स्थिर काष्ठा drm_display_mode *mode = &cstate->mode;
	काष्ठा drm_framebuffer *fb = plane->state->fb;
	u32 क्रमmat = fb->क्रमmat->क्रमmat;
	पूर्णांक dsi_pkt_size;
	पूर्णांक fअगरo_wtrmrk;
	पूर्णांक cpp = fb->क्रमmat->cpp[0];
	u32 dsi_क्रमmatter_frame;
	u32 val;
	पूर्णांक ret;

	/* This घातers up the entire MCDE block and the DSI hardware */
	ret = regulator_enable(mcde->epod);
	अगर (ret) अणु
		dev_err(drm->dev, "can't re-enable EPOD regulator\n");
		वापस;
	पूर्ण

	dev_info(drm->dev, "enable MCDE, %d x %d format %p4cc\n",
		 mode->hdisplay, mode->vdisplay, &क्रमmat);


	/* Clear any pending पूर्णांकerrupts */
	mcde_display_disable_irqs(mcde);
	ग_लिखोl(0, mcde->regs + MCDE_IMSCERR);
	ग_लिखोl(0xFFFFFFFF, mcde->regs + MCDE_RISERR);

	अगर (mcde->dpi_output)
		mcde_setup_dpi(mcde, mode, &fअगरo_wtrmrk);
	अन्यथा
		mcde_setup_dsi(mcde, mode, cpp, &fअगरo_wtrmrk,
			       &dsi_क्रमmatter_frame, &dsi_pkt_size);

	mcde->stride = mode->hdisplay * cpp;
	dev_dbg(drm->dev, "Overlay line stride: %u bytes\n",
		 mcde->stride);

	/* Drain the FIFO A + channel 0 pipe so we have a clean slate */
	mcde_drain_pipe(mcde, MCDE_FIFO_A, MCDE_CHANNEL_0);

	/*
	 * We set up our display pipeline:
	 * EXTSRC 0 -> OVERLAY 0 -> CHANNEL 0 -> FIFO A -> DSI FORMATTER 0
	 *
	 * First configure the बाह्यal source (memory) on बाह्यal source 0
	 * using the desired bitstream/biपंचांगap क्रमmat
	 */
	mcde_configure_extsrc(mcde, MCDE_EXTSRC_0, क्रमmat);

	/*
	 * Configure overlay 0 according to क्रमmat and mode and take input
	 * from बाह्यal source 0 and route the output of this overlay to
	 * channel 0
	 */
	mcde_configure_overlay(mcde, MCDE_OVERLAY_0, MCDE_EXTSRC_0,
			       MCDE_CHANNEL_0, mode, क्रमmat, cpp);

	/*
	 * Configure pixel-per-line and line-per-frame क्रम channel 0 and then
	 * route channel 0 to FIFO A
	 */
	mcde_configure_channel(mcde, MCDE_CHANNEL_0, MCDE_FIFO_A, mode);

	अगर (mcde->dpi_output) अणु
		अचिन्हित दीर्घ lcd_freq;

		/* Configure FIFO A to use DPI क्रमmatter 0 */
		mcde_configure_fअगरo(mcde, MCDE_FIFO_A, MCDE_DPI_FORMATTER_0,
				    fअगरo_wtrmrk);

		/* Set up and enable the LCD घड़ी */
		lcd_freq = clk_round_rate(mcde->fअगरoa_clk, mode->घड़ी * 1000);
		ret = clk_set_rate(mcde->fअगरoa_clk, lcd_freq);
		अगर (ret)
			dev_err(mcde->dev, "failed to set LCD clock rate %lu Hz\n",
				lcd_freq);
		ret = clk_prepare_enable(mcde->fअगरoa_clk);
		अगर (ret) अणु
			dev_err(mcde->dev, "failed to enable FIFO A DPI clock\n");
			वापस;
		पूर्ण
		dev_info(mcde->dev, "LCD FIFO A clk rate %lu Hz\n",
			 clk_get_rate(mcde->fअगरoa_clk));
	पूर्ण अन्यथा अणु
		/* Configure FIFO A to use DSI क्रमmatter 0 */
		mcde_configure_fअगरo(mcde, MCDE_FIFO_A, MCDE_DSI_FORMATTER_0,
				    fअगरo_wtrmrk);

		/*
		 * This brings up the DSI bridge which is tightly connected
		 * to the MCDE DSI क्रमmatter.
		 */
		mcde_dsi_enable(mcde->bridge);

		/* Configure the DSI क्रमmatter 0 क्रम the DSI panel output */
		mcde_configure_dsi_क्रमmatter(mcde, MCDE_DSI_FORMATTER_0,
					     dsi_क्रमmatter_frame, dsi_pkt_size);
	पूर्ण

	चयन (mcde->flow_mode) अणु
	हाल MCDE_COMMAND_TE_FLOW:
	हाल MCDE_COMMAND_BTA_TE_FLOW:
	हाल MCDE_VIDEO_TE_FLOW:
		/* We are using TE in some combination */
		अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
			val = MCDE_VSCRC_VSPOL;
		अन्यथा
			val = 0;
		ग_लिखोl(val, mcde->regs + MCDE_VSCRC0);
		/* Enable VSYNC capture on TE0 */
		val = पढ़ोl(mcde->regs + MCDE_CRC);
		val |= MCDE_CRC_SYCEN0;
		ग_लिखोl(val, mcde->regs + MCDE_CRC);
		अवरोध;
	शेष:
		/* No TE capture */
		अवरोध;
	पूर्ण

	drm_crtc_vblank_on(crtc);

	/*
	 * If we're using oneshot mode we don't start the flow
	 * until each समय the display is given an update, and
	 * then we disable it immediately after. For all other
	 * modes (command or video) we start the FIFO flow
	 * right here. This is necessary क्रम the hardware to
	 * behave right.
	 */
	अगर (mcde->flow_mode != MCDE_COMMAND_ONESHOT_FLOW) अणु
		mcde_enable_fअगरo(mcde, MCDE_FIFO_A);
		dev_dbg(mcde->dev, "started MCDE video FIFO flow\n");
	पूर्ण

	/* Enable MCDE with स्वतःmatic घड़ी gating */
	val = पढ़ोl(mcde->regs + MCDE_CR);
	val |= MCDE_CR_MCDEEN | MCDE_CR_AUTOCLKG_EN;
	ग_लिखोl(val, mcde->regs + MCDE_CR);

	dev_info(drm->dev, "MCDE display is enabled\n");
पूर्ण

अटल व्योम mcde_display_disable(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा mcde *mcde = to_mcde(drm);
	काष्ठा drm_pending_vblank_event *event;
	पूर्णांक ret;

	drm_crtc_vblank_off(crtc);

	/* Disable FIFO A flow */
	mcde_disable_fअगरo(mcde, MCDE_FIFO_A, true);

	अगर (mcde->dpi_output) अणु
		clk_disable_unprepare(mcde->fअगरoa_clk);
	पूर्ण अन्यथा अणु
		/* This disables the DSI bridge */
		mcde_dsi_disable(mcde->bridge);
	पूर्ण

	event = crtc->state->event;
	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण

	ret = regulator_disable(mcde->epod);
	अगर (ret)
		dev_err(drm->dev, "can't disable EPOD regulator\n");
	/* Make sure we are घातered करोwn (beक्रमe we may घातer up again) */
	usleep_range(50000, 70000);

	dev_info(drm->dev, "MCDE display is disabled\n");
पूर्ण

अटल व्योम mcde_start_flow(काष्ठा mcde *mcde)
अणु
	/* Request a TE ACK only in TE+BTA mode */
	अगर (mcde->flow_mode == MCDE_COMMAND_BTA_TE_FLOW)
		mcde_dsi_te_request(mcde->mdsi);

	/* Enable FIFO A flow */
	mcde_enable_fअगरo(mcde, MCDE_FIFO_A);

	/*
	 * If oneshot mode is enabled, the flow will be disabled
	 * when the TE0 IRQ arrives in the पूर्णांकerrupt handler. Otherwise
	 * updates are continuously streamed to the display after this
	 * poपूर्णांक.
	 */

	अगर (mcde->flow_mode == MCDE_COMMAND_ONESHOT_FLOW) अणु
		/* Trigger a software sync out on channel 0 */
		ग_लिखोl(MCDE_CHNLXSYNCHSW_SW_TRIG,
		       mcde->regs + MCDE_CHNL0SYNCHSW);

		/*
		 * Disable FIFO A flow again: since we are using TE sync we
		 * need to रुको क्रम the FIFO to drain beक्रमe we जारी
		 * so repeated calls to this function will not cause a mess
		 * in the hardware by pushing updates will updates are going
		 * on alपढ़ोy.
		 */
		mcde_disable_fअगरo(mcde, MCDE_FIFO_A, true);
	पूर्ण

	dev_dbg(mcde->dev, "started MCDE FIFO flow\n");
पूर्ण

अटल व्योम mcde_set_extsrc(काष्ठा mcde *mcde, u32 buffer_address)
अणु
	/* Write biपंचांगap base address to रेजिस्टर */
	ग_लिखोl(buffer_address, mcde->regs + MCDE_EXTSRCXA0);
	/*
	 * Base address क्रम next line this is probably only used
	 * in पूर्णांकerlace modes.
	 */
	ग_लिखोl(buffer_address + mcde->stride, mcde->regs + MCDE_EXTSRCXA1);
पूर्ण

अटल व्योम mcde_display_update(काष्ठा drm_simple_display_pipe *pipe,
				काष्ठा drm_plane_state *old_pstate)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा mcde *mcde = to_mcde(drm);
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;
	काष्ठा drm_plane *plane = &pipe->plane;
	काष्ठा drm_plane_state *pstate = plane->state;
	काष्ठा drm_framebuffer *fb = pstate->fb;

	/*
	 * Handle any pending event first, we need to arm the vblank
	 * पूर्णांकerrupt beक्रमe sending any update to the display so we करोn't
	 * miss the पूर्णांकerrupt.
	 */
	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		/*
		 * Hardware must be on beक्रमe we can arm any vblank event,
		 * this is not a scanout controller where there is always
		 * some periodic update going on, it is completely frozen
		 * until we get an update. If MCDE output isn't yet enabled,
		 * we just send a vblank dummy event back.
		 */
		अगर (crtc->state->active && drm_crtc_vblank_get(crtc) == 0) अणु
			dev_dbg(mcde->dev, "arm vblank event\n");
			drm_crtc_arm_vblank_event(crtc, event);
		पूर्ण अन्यथा अणु
			dev_dbg(mcde->dev, "insert fake vblank event\n");
			drm_crtc_send_vblank_event(crtc, event);
		पूर्ण

		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण

	/*
	 * We करो not start sending framebuffer updates beक्रमe the
	 * display is enabled. Update events will however be dispatched
	 * from the DRM core beक्रमe the display is enabled.
	 */
	अगर (fb) अणु
		mcde_set_extsrc(mcde, drm_fb_cma_get_gem_addr(fb, pstate, 0));
		dev_info_once(mcde->dev, "first update of display contents\n");
		/*
		 * Usually the flow is alपढ़ोy active, unless we are in
		 * oneshot mode, then we need to kick the flow right here.
		 */
		अगर (mcde->flow_active == 0)
			mcde_start_flow(mcde);
	पूर्ण अन्यथा अणु
		/*
		 * If an update is receieved beक्रमe the MCDE is enabled
		 * (beक्रमe mcde_display_enable() is called) we can't really
		 * करो much with that buffer.
		 */
		dev_info(mcde->dev, "ignored a display update\n");
	पूर्ण
पूर्ण

अटल पूर्णांक mcde_display_enable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा mcde *mcde = to_mcde(drm);
	u32 val;

	/* Enable all VBLANK IRQs */
	val = MCDE_PP_VCMPA |
		MCDE_PP_VCMPB |
		MCDE_PP_VSCC0 |
		MCDE_PP_VSCC1 |
		MCDE_PP_VCMPC0 |
		MCDE_PP_VCMPC1;
	ग_लिखोl(val, mcde->regs + MCDE_IMSCPP);

	वापस 0;
पूर्ण

अटल व्योम mcde_display_disable_vblank(काष्ठा drm_simple_display_pipe *pipe)
अणु
	काष्ठा drm_crtc *crtc = &pipe->crtc;
	काष्ठा drm_device *drm = crtc->dev;
	काष्ठा mcde *mcde = to_mcde(drm);

	/* Disable all VBLANK IRQs */
	ग_लिखोl(0, mcde->regs + MCDE_IMSCPP);
	/* Clear any pending IRQs */
	ग_लिखोl(0xFFFFFFFF, mcde->regs + MCDE_RISPP);
पूर्ण

अटल काष्ठा drm_simple_display_pipe_funcs mcde_display_funcs = अणु
	.check = mcde_display_check,
	.enable = mcde_display_enable,
	.disable = mcde_display_disable,
	.update = mcde_display_update,
	.enable_vblank = mcde_display_enable_vblank,
	.disable_vblank = mcde_display_disable_vblank,
	.prepare_fb = drm_gem_simple_display_pipe_prepare_fb,
पूर्ण;

पूर्णांक mcde_display_init(काष्ठा drm_device *drm)
अणु
	काष्ठा mcde *mcde = to_mcde(drm);
	पूर्णांक ret;
	अटल स्थिर u32 क्रमmats[] = अणु
		DRM_FORMAT_ARGB8888,
		DRM_FORMAT_ABGR8888,
		DRM_FORMAT_XRGB8888,
		DRM_FORMAT_XBGR8888,
		DRM_FORMAT_RGB888,
		DRM_FORMAT_BGR888,
		DRM_FORMAT_ARGB4444,
		DRM_FORMAT_ABGR4444,
		DRM_FORMAT_XRGB4444,
		DRM_FORMAT_XBGR4444,
		/* These are actually IRGB1555 so पूर्णांकensity bit is lost */
		DRM_FORMAT_XRGB1555,
		DRM_FORMAT_XBGR1555,
		DRM_FORMAT_RGB565,
		DRM_FORMAT_BGR565,
		DRM_FORMAT_YUV422,
	पूर्ण;

	ret = mcde_init_घड़ी_भागider(mcde);
	अगर (ret)
		वापस ret;

	ret = drm_simple_display_pipe_init(drm, &mcde->pipe,
					   &mcde_display_funcs,
					   क्रमmats, ARRAY_SIZE(क्रमmats),
					   शून्य,
					   mcde->connector);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mcde_display_init);
