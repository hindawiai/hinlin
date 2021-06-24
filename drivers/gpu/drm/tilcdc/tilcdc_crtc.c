<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "tilcdc_drv.h"
#समावेश "tilcdc_regs.h"

#घोषणा TILCDC_VBLANK_SAFETY_THRESHOLD_US	1000
#घोषणा TILCDC_PALETTE_SIZE			32
#घोषणा TILCDC_PALETTE_FIRST_ENTRY		0x4000

काष्ठा tilcdc_crtc अणु
	काष्ठा drm_crtc base;

	काष्ठा drm_plane primary;
	स्थिर काष्ठा tilcdc_panel_info *info;
	काष्ठा drm_pending_vblank_event *event;
	काष्ठा mutex enable_lock;
	bool enabled;
	bool shutकरोwn;
	रुको_queue_head_t frame_करोne_wq;
	bool frame_करोne;
	spinlock_t irq_lock;

	अचिन्हित पूर्णांक lcd_fck_rate;

	kसमय_प्रकार last_vblank;
	अचिन्हित पूर्णांक hvtotal_us;

	काष्ठा drm_framebuffer *next_fb;

	/* Only set अगर an बाह्यal encoder is connected */
	bool simulate_vesa_sync;

	पूर्णांक sync_lost_count;
	bool frame_पूर्णांकact;
	काष्ठा work_काष्ठा recover_work;

	dma_addr_t palette_dma_handle;
	u16 *palette_base;
	काष्ठा completion palette_loaded;
पूर्ण;
#घोषणा to_tilcdc_crtc(x) container_of(x, काष्ठा tilcdc_crtc, base)

अटल व्योम set_scanout(काष्ठा drm_crtc *crtc, काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	काष्ठा drm_gem_cma_object *gem;
	dma_addr_t start, end;
	u64 dma_base_and_उच्चमानing;

	gem = drm_fb_cma_get_gem_obj(fb, 0);

	start = gem->paddr + fb->offsets[0] +
		crtc->y * fb->pitches[0] +
		crtc->x * fb->क्रमmat->cpp[0];

	end = start + (crtc->mode.vdisplay * fb->pitches[0]);

	/* Write LCDC_DMA_FB_BASE_ADDR_0_REG and LCDC_DMA_FB_CEILING_ADDR_0_REG
	 * with a single insruction, अगर available. This should make it more
	 * unlikely that LCDC would fetch the DMA addresses in the middle of
	 * an update.
	 */
	अगर (priv->rev == 1)
		end -= 1;

	dma_base_and_उच्चमानing = (u64)end << 32 | start;
	tilcdc_ग_लिखो64(dev, LCDC_DMA_FB_BASE_ADDR_0_REG, dma_base_and_उच्चमानing);
पूर्ण

/*
 * The driver currently only supports only true color क्रमmats. For
 * true color the palette block is bypassed, but a 32 byte palette
 * should still be loaded. The first 16-bit entry must be 0x4000 जबतक
 * all other entries must be zeroed.
 */
अटल व्योम tilcdc_crtc_load_palette(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	पूर्णांक ret;

	reinit_completion(&tilcdc_crtc->palette_loaded);

	/* Tell the LCDC where the palette is located. */
	tilcdc_ग_लिखो(dev, LCDC_DMA_FB_BASE_ADDR_0_REG,
		     tilcdc_crtc->palette_dma_handle);
	tilcdc_ग_लिखो(dev, LCDC_DMA_FB_CEILING_ADDR_0_REG,
		     (u32) tilcdc_crtc->palette_dma_handle +
		     TILCDC_PALETTE_SIZE - 1);

	/* Set dma load mode क्रम palette loading only. */
	tilcdc_ग_लिखो_mask(dev, LCDC_RASTER_CTRL_REG,
			  LCDC_PALETTE_LOAD_MODE(PALETTE_ONLY),
			  LCDC_PALETTE_LOAD_MODE_MASK);

	/* Enable DMA Palette Loaded Interrupt */
	अगर (priv->rev == 1)
		tilcdc_set(dev, LCDC_RASTER_CTRL_REG, LCDC_V1_PL_INT_ENA);
	अन्यथा
		tilcdc_ग_लिखो(dev, LCDC_INT_ENABLE_SET_REG, LCDC_V2_PL_INT_ENA);

	/* Enable LCDC DMA and रुको क्रम palette to be loaded. */
	tilcdc_clear_irqstatus(dev, 0xffffffff);
	tilcdc_set(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ENABLE);

	ret = रुको_क्रम_completion_समयout(&tilcdc_crtc->palette_loaded,
					  msecs_to_jअगरfies(50));
	अगर (ret == 0)
		dev_err(dev->dev, "%s: Palette loading timeout", __func__);

	/* Disable LCDC DMA and DMA Palette Loaded Interrupt. */
	tilcdc_clear(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ENABLE);
	अगर (priv->rev == 1)
		tilcdc_clear(dev, LCDC_RASTER_CTRL_REG, LCDC_V1_PL_INT_ENA);
	अन्यथा
		tilcdc_ग_लिखो(dev, LCDC_INT_ENABLE_CLR_REG, LCDC_V2_PL_INT_ENA);
पूर्ण

अटल व्योम tilcdc_crtc_enable_irqs(काष्ठा drm_device *dev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;

	tilcdc_clear_irqstatus(dev, 0xffffffff);

	अगर (priv->rev == 1) अणु
		tilcdc_set(dev, LCDC_RASTER_CTRL_REG,
			LCDC_V1_SYNC_LOST_INT_ENA | LCDC_V1_FRAME_DONE_INT_ENA |
			LCDC_V1_UNDERFLOW_INT_ENA);
	पूर्ण अन्यथा अणु
		tilcdc_ग_लिखो(dev, LCDC_INT_ENABLE_SET_REG,
			LCDC_V2_UNDERFLOW_INT_ENA |
			LCDC_FRAME_DONE | LCDC_SYNC_LOST);
	पूर्ण
पूर्ण

अटल व्योम tilcdc_crtc_disable_irqs(काष्ठा drm_device *dev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;

	/* disable irqs that we might have enabled: */
	अगर (priv->rev == 1) अणु
		tilcdc_clear(dev, LCDC_RASTER_CTRL_REG,
			LCDC_V1_SYNC_LOST_INT_ENA | LCDC_V1_FRAME_DONE_INT_ENA |
			LCDC_V1_UNDERFLOW_INT_ENA | LCDC_V1_PL_INT_ENA);
		tilcdc_clear(dev, LCDC_DMA_CTRL_REG,
			LCDC_V1_END_OF_FRAME_INT_ENA);
	पूर्ण अन्यथा अणु
		tilcdc_ग_लिखो(dev, LCDC_INT_ENABLE_CLR_REG,
			LCDC_V2_UNDERFLOW_INT_ENA | LCDC_V2_PL_INT_ENA |
			LCDC_V2_END_OF_FRAME0_INT_ENA |
			LCDC_FRAME_DONE | LCDC_SYNC_LOST);
	पूर्ण
पूर्ण

अटल व्योम reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;

	अगर (priv->rev != 2)
		वापस;

	tilcdc_set(dev, LCDC_CLK_RESET_REG, LCDC_CLK_MAIN_RESET);
	usleep_range(250, 1000);
	tilcdc_clear(dev, LCDC_CLK_RESET_REG, LCDC_CLK_MAIN_RESET);
पूर्ण

/*
 * Calculate the percentage dअगरference between the requested pixel घड़ी rate
 * and the effective rate resulting from calculating the घड़ी भागider value.
 */
अटल अचिन्हित पूर्णांक tilcdc_pclk_dअगरf(अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ real_rate)
अणु
	पूर्णांक r = rate / 100, rr = real_rate / 100;

	वापस (अचिन्हित पूर्णांक)(असल(((rr - r) * 100) / r));
पूर्ण

अटल व्योम tilcdc_crtc_set_clk(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	अचिन्हित दीर्घ clk_rate, real_pclk_rate, pclk_rate;
	अचिन्हित पूर्णांक clkभाग;
	पूर्णांक ret;

	clkभाग = 2; /* first try using a standard भागider of 2 */

	/* mode.घड़ी is in KHz, set_rate wants parameter in Hz */
	pclk_rate = crtc->mode.घड़ी * 1000;

	ret = clk_set_rate(priv->clk, pclk_rate * clkभाग);
	clk_rate = clk_get_rate(priv->clk);
	real_pclk_rate = clk_rate / clkभाग;
	अगर (ret < 0 || tilcdc_pclk_dअगरf(pclk_rate, real_pclk_rate) > 5) अणु
		/*
		 * If we fail to set the घड़ी rate (some architectures करोn't
		 * use the common घड़ी framework yet and may not implement
		 * all the clk API calls क्रम every घड़ी), try the next best
		 * thing: adjusting the घड़ी भागider, unless clk_get_rate()
		 * failed as well.
		 */
		अगर (!clk_rate) अणु
			/* Nothing more we can करो. Just bail out. */
			dev_err(dev->dev,
				"failed to set the pixel clock - unable to read current lcdc clock rate\n");
			वापस;
		पूर्ण

		clkभाग = DIV_ROUND_CLOSEST(clk_rate, pclk_rate);

		/*
		 * Emit a warning अगर the real घड़ी rate resulting from the
		 * calculated भागider dअगरfers much from the requested rate.
		 *
		 * 5% is an arbitrary value - LCDs are usually quite tolerant
		 * about pixel घड़ी rates.
		 */
		real_pclk_rate = clk_rate / clkभाग;

		अगर (tilcdc_pclk_dअगरf(pclk_rate, real_pclk_rate) > 5) अणु
			dev_warn(dev->dev,
				 "effective pixel clock rate (%luHz) differs from the requested rate (%luHz)\n",
				 real_pclk_rate, pclk_rate);
		पूर्ण
	पूर्ण

	tilcdc_crtc->lcd_fck_rate = clk_rate;

	DBG("lcd_clk=%u, mode clock=%d, div=%u",
	    tilcdc_crtc->lcd_fck_rate, crtc->mode.घड़ी, clkभाग);

	/* Configure the LCD घड़ी भागisor. */
	tilcdc_ग_लिखो(dev, LCDC_CTRL_REG, LCDC_CLK_DIVISOR(clkभाग) |
		     LCDC_RASTER_MODE);

	अगर (priv->rev == 2)
		tilcdc_set(dev, LCDC_CLK_ENABLE_REG,
				LCDC_V2_DMA_CLK_EN | LCDC_V2_LIDD_CLK_EN |
				LCDC_V2_CORE_CLK_EN);
पूर्ण

अटल uपूर्णांक tilcdc_mode_hvtotal(स्थिर काष्ठा drm_display_mode *mode)
अणु
	वापस (uपूर्णांक) भाग_u64(1000llu * mode->htotal * mode->vtotal,
			      mode->घड़ी);
पूर्ण

अटल व्योम tilcdc_crtc_set_mode(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	स्थिर काष्ठा tilcdc_panel_info *info = tilcdc_crtc->info;
	uपूर्णांक32_t reg, hbp, hfp, hsw, vbp, vfp, vsw;
	काष्ठा drm_display_mode *mode = &crtc->state->adjusted_mode;
	काष्ठा drm_framebuffer *fb = crtc->primary->state->fb;

	अगर (WARN_ON(!info))
		वापस;

	अगर (WARN_ON(!fb))
		वापस;

	/* Configure the Burst Size and fअगरo threshold of DMA: */
	reg = tilcdc_पढ़ो(dev, LCDC_DMA_CTRL_REG) & ~0x00000770;
	चयन (info->dma_burst_sz) अणु
	हाल 1:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_1);
		अवरोध;
	हाल 2:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_2);
		अवरोध;
	हाल 4:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_4);
		अवरोध;
	हाल 8:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_8);
		अवरोध;
	हाल 16:
		reg |= LCDC_DMA_BURST_SIZE(LCDC_DMA_BURST_16);
		अवरोध;
	शेष:
		dev_err(dev->dev, "invalid burst size\n");
		वापस;
	पूर्ण
	reg |= (info->fअगरo_th << 8);
	tilcdc_ग_लिखो(dev, LCDC_DMA_CTRL_REG, reg);

	/* Configure timings: */
	hbp = mode->htotal - mode->hsync_end;
	hfp = mode->hsync_start - mode->hdisplay;
	hsw = mode->hsync_end - mode->hsync_start;
	vbp = mode->vtotal - mode->vsync_end;
	vfp = mode->vsync_start - mode->vdisplay;
	vsw = mode->vsync_end - mode->vsync_start;

	DBG("%dx%d, hbp=%u, hfp=%u, hsw=%u, vbp=%u, vfp=%u, vsw=%u",
	    mode->hdisplay, mode->vdisplay, hbp, hfp, hsw, vbp, vfp, vsw);

	/* Set AC Bias Period and Number of Transitions per Interrupt: */
	reg = tilcdc_पढ़ो(dev, LCDC_RASTER_TIMING_2_REG) & ~0x000fff00;
	reg |= LCDC_AC_BIAS_FREQUENCY(info->ac_bias) |
		LCDC_AC_BIAS_TRANSITIONS_PER_INT(info->ac_bias_पूर्णांकrpt);

	/*
	 * subtract one from hfp, hbp, hsw because the hardware uses
	 * a value of 0 as 1
	 */
	अगर (priv->rev == 2) अणु
		/* clear bits we're going to set */
		reg &= ~0x78000033;
		reg |= ((hfp-1) & 0x300) >> 8;
		reg |= ((hbp-1) & 0x300) >> 4;
		reg |= ((hsw-1) & 0x3c0) << 21;
	पूर्ण
	tilcdc_ग_लिखो(dev, LCDC_RASTER_TIMING_2_REG, reg);

	reg = (((mode->hdisplay >> 4) - 1) << 4) |
		(((hbp-1) & 0xff) << 24) |
		(((hfp-1) & 0xff) << 16) |
		(((hsw-1) & 0x3f) << 10);
	अगर (priv->rev == 2)
		reg |= (((mode->hdisplay >> 4) - 1) & 0x40) >> 3;
	tilcdc_ग_लिखो(dev, LCDC_RASTER_TIMING_0_REG, reg);

	reg = ((mode->vdisplay - 1) & 0x3ff) |
		((vbp & 0xff) << 24) |
		((vfp & 0xff) << 16) |
		(((vsw-1) & 0x3f) << 10);
	tilcdc_ग_लिखो(dev, LCDC_RASTER_TIMING_1_REG, reg);

	/*
	 * be sure to set Bit 10 क्रम the V2 LCDC controller,
	 * otherwise limited to 1024 pixels width, stopping
	 * 1920x1080 being supported.
	 */
	अगर (priv->rev == 2) अणु
		अगर ((mode->vdisplay - 1) & 0x400) अणु
			tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG,
				LCDC_LPP_B10);
		पूर्ण अन्यथा अणु
			tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG,
				LCDC_LPP_B10);
		पूर्ण
	पूर्ण

	/* Configure display type: */
	reg = tilcdc_पढ़ो(dev, LCDC_RASTER_CTRL_REG) &
		~(LCDC_TFT_MODE | LCDC_MONO_8BIT_MODE | LCDC_MONOCHROME_MODE |
		  LCDC_V2_TFT_24BPP_MODE | LCDC_V2_TFT_24BPP_UNPACK |
		  0x000ff000 /* Palette Loading Delay bits */);
	reg |= LCDC_TFT_MODE; /* no monochrome/passive support */
	अगर (info->tft_alt_mode)
		reg |= LCDC_TFT_ALT_ENABLE;
	अगर (priv->rev == 2) अणु
		चयन (fb->क्रमmat->क्रमmat) अणु
		हाल DRM_FORMAT_BGR565:
		हाल DRM_FORMAT_RGB565:
			अवरोध;
		हाल DRM_FORMAT_XBGR8888:
		हाल DRM_FORMAT_XRGB8888:
			reg |= LCDC_V2_TFT_24BPP_UNPACK;
			fallthrough;
		हाल DRM_FORMAT_BGR888:
		हाल DRM_FORMAT_RGB888:
			reg |= LCDC_V2_TFT_24BPP_MODE;
			अवरोध;
		शेष:
			dev_err(dev->dev, "invalid pixel format\n");
			वापस;
		पूर्ण
	पूर्ण
	reg |= info->fdd << 12;
	tilcdc_ग_लिखो(dev, LCDC_RASTER_CTRL_REG, reg);

	अगर (info->invert_pxl_clk)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_PIXEL_CLOCK);
	अन्यथा
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_PIXEL_CLOCK);

	अगर (info->sync_ctrl)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_CTRL);
	अन्यथा
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_CTRL);

	अगर (info->sync_edge)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_EDGE);
	अन्यथा
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_SYNC_EDGE);

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_HSYNC);
	अन्यथा
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_HSYNC);

	अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
		tilcdc_set(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_VSYNC);
	अन्यथा
		tilcdc_clear(dev, LCDC_RASTER_TIMING_2_REG, LCDC_INVERT_VSYNC);

	अगर (info->raster_order)
		tilcdc_set(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ORDER);
	अन्यथा
		tilcdc_clear(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ORDER);

	tilcdc_crtc_set_clk(crtc);

	tilcdc_crtc_load_palette(crtc);

	set_scanout(crtc, fb);

	crtc->hwmode = crtc->state->adjusted_mode;

	tilcdc_crtc->hvtotal_us =
		tilcdc_mode_hvtotal(&crtc->hwmode);
पूर्ण

अटल व्योम tilcdc_crtc_enable(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	अचिन्हित दीर्घ flags;

	mutex_lock(&tilcdc_crtc->enable_lock);
	अगर (tilcdc_crtc->enabled || tilcdc_crtc->shutकरोwn) अणु
		mutex_unlock(&tilcdc_crtc->enable_lock);
		वापस;
	पूर्ण

	pm_runसमय_get_sync(dev->dev);

	reset(crtc);

	tilcdc_crtc_set_mode(crtc);

	tilcdc_crtc_enable_irqs(dev);

	tilcdc_clear(dev, LCDC_DMA_CTRL_REG, LCDC_DUAL_FRAME_BUFFER_ENABLE);
	tilcdc_ग_लिखो_mask(dev, LCDC_RASTER_CTRL_REG,
			  LCDC_PALETTE_LOAD_MODE(DATA_ONLY),
			  LCDC_PALETTE_LOAD_MODE_MASK);

	/* There is no real chance क्रम a race here as the समय stamp
	 * is taken beक्रमe the raster DMA is started. The spin-lock is
	 * taken to have a memory barrier after taking the समय-stamp
	 * and to aव्योम a context चयन between taking the stamp and
	 * enabling the raster.
	 */
	spin_lock_irqsave(&tilcdc_crtc->irq_lock, flags);
	tilcdc_crtc->last_vblank = kसमय_get();
	tilcdc_set(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ENABLE);
	spin_unlock_irqrestore(&tilcdc_crtc->irq_lock, flags);

	drm_crtc_vblank_on(crtc);

	tilcdc_crtc->enabled = true;
	mutex_unlock(&tilcdc_crtc->enable_lock);
पूर्ण

अटल व्योम tilcdc_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	tilcdc_crtc_enable(crtc);
पूर्ण

अटल व्योम tilcdc_crtc_off(काष्ठा drm_crtc *crtc, bool shutकरोwn)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	पूर्णांक ret;

	mutex_lock(&tilcdc_crtc->enable_lock);
	अगर (shutकरोwn)
		tilcdc_crtc->shutकरोwn = true;
	अगर (!tilcdc_crtc->enabled) अणु
		mutex_unlock(&tilcdc_crtc->enable_lock);
		वापस;
	पूर्ण
	tilcdc_crtc->frame_करोne = false;
	tilcdc_clear(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ENABLE);

	/*
	 * Wait क्रम frameकरोne irq which will still come beक्रमe putting
	 * things to sleep..
	 */
	ret = रुको_event_समयout(tilcdc_crtc->frame_करोne_wq,
				 tilcdc_crtc->frame_करोne,
				 msecs_to_jअगरfies(500));
	अगर (ret == 0)
		dev_err(dev->dev, "%s: timeout waiting for framedone\n",
			__func__);

	drm_crtc_vblank_off(crtc);

	spin_lock_irq(&crtc->dev->event_lock);

	अगर (crtc->state->event) अणु
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
	पूर्ण

	spin_unlock_irq(&crtc->dev->event_lock);

	tilcdc_crtc_disable_irqs(dev);

	pm_runसमय_put_sync(dev->dev);

	tilcdc_crtc->enabled = false;
	mutex_unlock(&tilcdc_crtc->enable_lock);
पूर्ण

अटल व्योम tilcdc_crtc_disable(काष्ठा drm_crtc *crtc)
अणु
	tilcdc_crtc_off(crtc, false);
पूर्ण

अटल व्योम tilcdc_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
	tilcdc_crtc_disable(crtc);
पूर्ण

अटल व्योम tilcdc_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				     काष्ठा drm_atomic_state *state)
अणु
	अगर (!crtc->state->event)
		वापस;

	spin_lock_irq(&crtc->dev->event_lock);
	drm_crtc_send_vblank_event(crtc, crtc->state->event);
	crtc->state->event = शून्य;
	spin_unlock_irq(&crtc->dev->event_lock);
पूर्ण

व्योम tilcdc_crtc_shutकरोwn(काष्ठा drm_crtc *crtc)
अणु
	tilcdc_crtc_off(crtc, true);
पूर्ण

अटल bool tilcdc_crtc_is_on(काष्ठा drm_crtc *crtc)
अणु
	वापस crtc->state && crtc->state->enable && crtc->state->active;
पूर्ण

अटल व्योम tilcdc_crtc_recover_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc =
		container_of(work, काष्ठा tilcdc_crtc, recover_work);
	काष्ठा drm_crtc *crtc = &tilcdc_crtc->base;

	dev_info(crtc->dev->dev, "%s: Reset CRTC", __func__);

	drm_modeset_lock(&crtc->mutex, शून्य);

	अगर (!tilcdc_crtc_is_on(crtc))
		जाओ out;

	tilcdc_crtc_disable(crtc);
	tilcdc_crtc_enable(crtc);
out:
	drm_modeset_unlock(&crtc->mutex);
पूर्ण

अटल व्योम tilcdc_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tilcdc_drm_निजी *priv = crtc->dev->dev_निजी;

	tilcdc_crtc_shutकरोwn(crtc);

	flush_workqueue(priv->wq);

	of_node_put(crtc->port);
	drm_crtc_cleanup(crtc);
पूर्ण

पूर्णांक tilcdc_crtc_update_fb(काष्ठा drm_crtc *crtc,
		काष्ठा drm_framebuffer *fb,
		काष्ठा drm_pending_vblank_event *event)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;

	अगर (tilcdc_crtc->event) अणु
		dev_err(dev->dev, "already pending page flip!\n");
		वापस -EBUSY;
	पूर्ण

	tilcdc_crtc->event = event;

	mutex_lock(&tilcdc_crtc->enable_lock);

	अगर (tilcdc_crtc->enabled) अणु
		अचिन्हित दीर्घ flags;
		kसमय_प्रकार next_vblank;
		s64 tdअगरf;

		spin_lock_irqsave(&tilcdc_crtc->irq_lock, flags);

		next_vblank = kसमय_add_us(tilcdc_crtc->last_vblank,
					   tilcdc_crtc->hvtotal_us);
		tdअगरf = kसमय_प्रकारo_us(kसमय_sub(next_vblank, kसमय_get()));

		अगर (tdअगरf < TILCDC_VBLANK_SAFETY_THRESHOLD_US)
			tilcdc_crtc->next_fb = fb;
		अन्यथा
			set_scanout(crtc, fb);

		spin_unlock_irqrestore(&tilcdc_crtc->irq_lock, flags);
	पूर्ण

	mutex_unlock(&tilcdc_crtc->enable_lock);

	वापस 0;
पूर्ण

अटल bool tilcdc_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);

	अगर (!tilcdc_crtc->simulate_vesa_sync)
		वापस true;

	/*
	 * tilcdc करोes not generate VESA-compliant sync but aligns
	 * VS on the second edge of HS instead of first edge.
	 * We use adjusted_mode, to fixup sync by aligning both rising
	 * edges and add HSKEW offset to fix the sync.
	 */
	adjusted_mode->hskew = mode->hsync_end - mode->hsync_start;
	adjusted_mode->flags |= DRM_MODE_FLAG_HSKEW;

	अगर (mode->flags & DRM_MODE_FLAG_NHSYNC) अणु
		adjusted_mode->flags |= DRM_MODE_FLAG_PHSYNC;
		adjusted_mode->flags &= ~DRM_MODE_FLAG_NHSYNC;
	पूर्ण अन्यथा अणु
		adjusted_mode->flags |= DRM_MODE_FLAG_NHSYNC;
		adjusted_mode->flags &= ~DRM_MODE_FLAG_PHSYNC;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक tilcdc_crtc_atomic_check(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	/* If we are not active we करोn't care */
	अगर (!crtc_state->active)
		वापस 0;

	अगर (state->planes[0].ptr != crtc->primary ||
	    state->planes[0].state == शून्य ||
	    state->planes[0].state->crtc != crtc) अणु
		dev_dbg(crtc->dev->dev, "CRTC primary plane must be present");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tilcdc_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tilcdc_crtc->irq_lock, flags);

	tilcdc_clear_irqstatus(dev, LCDC_END_OF_FRAME0);

	अगर (priv->rev == 1)
		tilcdc_set(dev, LCDC_DMA_CTRL_REG,
			   LCDC_V1_END_OF_FRAME_INT_ENA);
	अन्यथा
		tilcdc_set(dev, LCDC_INT_ENABLE_SET_REG,
			   LCDC_V2_END_OF_FRAME0_INT_ENA);

	spin_unlock_irqrestore(&tilcdc_crtc->irq_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम tilcdc_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tilcdc_crtc->irq_lock, flags);

	अगर (priv->rev == 1)
		tilcdc_clear(dev, LCDC_DMA_CTRL_REG,
			     LCDC_V1_END_OF_FRAME_INT_ENA);
	अन्यथा
		tilcdc_clear(dev, LCDC_INT_ENABLE_SET_REG,
			     LCDC_V2_END_OF_FRAME0_INT_ENA);

	spin_unlock_irqrestore(&tilcdc_crtc->irq_lock, flags);
पूर्ण

अटल व्योम tilcdc_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	पूर्णांक ret;

	drm_atomic_helper_crtc_reset(crtc);

	/* Turn the raster off अगर it क्रम some reason is on. */
	pm_runसमय_get_sync(dev->dev);
	अगर (tilcdc_पढ़ो(dev, LCDC_RASTER_CTRL_REG) & LCDC_RASTER_ENABLE) अणु
		/* Enable DMA Frame Done Interrupt */
		tilcdc_ग_लिखो(dev, LCDC_INT_ENABLE_SET_REG, LCDC_FRAME_DONE);
		tilcdc_clear_irqstatus(dev, 0xffffffff);

		tilcdc_crtc->frame_करोne = false;
		tilcdc_clear(dev, LCDC_RASTER_CTRL_REG, LCDC_RASTER_ENABLE);

		ret = रुको_event_समयout(tilcdc_crtc->frame_करोne_wq,
					 tilcdc_crtc->frame_करोne,
					 msecs_to_jअगरfies(500));
		अगर (ret == 0)
			dev_err(dev->dev, "%s: timeout waiting for framedone\n",
				__func__);
	पूर्ण
	pm_runसमय_put_sync(dev->dev);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs tilcdc_crtc_funcs = अणु
	.destroy        = tilcdc_crtc_destroy,
	.set_config     = drm_atomic_helper_set_config,
	.page_flip      = drm_atomic_helper_page_flip,
	.reset		= tilcdc_crtc_reset,
	.atomic_duplicate_state = drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_crtc_destroy_state,
	.enable_vblank	= tilcdc_crtc_enable_vblank,
	.disable_vblank	= tilcdc_crtc_disable_vblank,
पूर्ण;

अटल क्रमागत drm_mode_status
tilcdc_crtc_mode_valid(काष्ठा drm_crtc *crtc,
		       स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा tilcdc_drm_निजी *priv = crtc->dev->dev_निजी;
	अचिन्हित पूर्णांक bandwidth;
	uपूर्णांक32_t hbp, hfp, hsw, vbp, vfp, vsw;

	/*
	 * check to see अगर the width is within the range that
	 * the LCD Controller physically supports
	 */
	अगर (mode->hdisplay > priv->max_width)
		वापस MODE_VIRTUAL_X;

	/* width must be multiple of 16 */
	अगर (mode->hdisplay & 0xf)
		वापस MODE_VIRTUAL_X;

	अगर (mode->vdisplay > 2048)
		वापस MODE_VIRTUAL_Y;

	DBG("Processing mode %dx%d@%d with pixel clock %d",
		mode->hdisplay, mode->vdisplay,
		drm_mode_vrefresh(mode), mode->घड़ी);

	hbp = mode->htotal - mode->hsync_end;
	hfp = mode->hsync_start - mode->hdisplay;
	hsw = mode->hsync_end - mode->hsync_start;
	vbp = mode->vtotal - mode->vsync_end;
	vfp = mode->vsync_start - mode->vdisplay;
	vsw = mode->vsync_end - mode->vsync_start;

	अगर ((hbp-1) & ~0x3ff) अणु
		DBG("Pruning mode: Horizontal Back Porch out of range");
		वापस MODE_HBLANK_WIDE;
	पूर्ण

	अगर ((hfp-1) & ~0x3ff) अणु
		DBG("Pruning mode: Horizontal Front Porch out of range");
		वापस MODE_HBLANK_WIDE;
	पूर्ण

	अगर ((hsw-1) & ~0x3ff) अणु
		DBG("Pruning mode: Horizontal Sync Width out of range");
		वापस MODE_HSYNC_WIDE;
	पूर्ण

	अगर (vbp & ~0xff) अणु
		DBG("Pruning mode: Vertical Back Porch out of range");
		वापस MODE_VBLANK_WIDE;
	पूर्ण

	अगर (vfp & ~0xff) अणु
		DBG("Pruning mode: Vertical Front Porch out of range");
		वापस MODE_VBLANK_WIDE;
	पूर्ण

	अगर ((vsw-1) & ~0x3f) अणु
		DBG("Pruning mode: Vertical Sync Width out of range");
		वापस MODE_VSYNC_WIDE;
	पूर्ण

	/*
	 * some devices have a maximum allowed pixel घड़ी
	 * configured from the DT
	 */
	अगर (mode->घड़ी > priv->max_pixelघड़ी) अणु
		DBG("Pruning mode: pixel clock too high");
		वापस MODE_CLOCK_HIGH;
	पूर्ण

	/*
	 * some devices further limit the max horizontal resolution
	 * configured from the DT
	 */
	अगर (mode->hdisplay > priv->max_width)
		वापस MODE_BAD_WIDTH;

	/* filter out modes that would require too much memory bandwidth: */
	bandwidth = mode->hdisplay * mode->vdisplay *
		drm_mode_vrefresh(mode);
	अगर (bandwidth > priv->max_bandwidth) अणु
		DBG("Pruning mode: exceeds defined bandwidth limit");
		वापस MODE_BAD;
	पूर्ण

	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs tilcdc_crtc_helper_funcs = अणु
	.mode_valid	= tilcdc_crtc_mode_valid,
	.mode_fixup	= tilcdc_crtc_mode_fixup,
	.atomic_check	= tilcdc_crtc_atomic_check,
	.atomic_enable	= tilcdc_crtc_atomic_enable,
	.atomic_disable	= tilcdc_crtc_atomic_disable,
	.atomic_flush	= tilcdc_crtc_atomic_flush,
पूर्ण;

व्योम tilcdc_crtc_set_panel_info(काष्ठा drm_crtc *crtc,
		स्थिर काष्ठा tilcdc_panel_info *info)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	tilcdc_crtc->info = info;
पूर्ण

व्योम tilcdc_crtc_set_simulate_vesa_sync(काष्ठा drm_crtc *crtc,
					bool simulate_vesa_sync)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);

	tilcdc_crtc->simulate_vesa_sync = simulate_vesa_sync;
पूर्ण

व्योम tilcdc_crtc_update_clk(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);

	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (tilcdc_crtc->lcd_fck_rate != clk_get_rate(priv->clk)) अणु
		अगर (tilcdc_crtc_is_on(crtc)) अणु
			pm_runसमय_get_sync(dev->dev);
			tilcdc_crtc_disable(crtc);

			tilcdc_crtc_set_clk(crtc);

			tilcdc_crtc_enable(crtc);
			pm_runसमय_put_sync(dev->dev);
		पूर्ण
	पूर्ण
	drm_modeset_unlock(&crtc->mutex);
पूर्ण

#घोषणा SYNC_LOST_COUNT_LIMIT 50

irqवापस_t tilcdc_crtc_irq(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	uपूर्णांक32_t stat, reg;

	stat = tilcdc_पढ़ो_irqstatus(dev);
	tilcdc_clear_irqstatus(dev, stat);

	अगर (stat & LCDC_END_OF_FRAME0) अणु
		bool skip_event = false;
		kसमय_प्रकार now;

		now = kसमय_get();

		spin_lock(&tilcdc_crtc->irq_lock);

		tilcdc_crtc->last_vblank = now;

		अगर (tilcdc_crtc->next_fb) अणु
			set_scanout(crtc, tilcdc_crtc->next_fb);
			tilcdc_crtc->next_fb = शून्य;
			skip_event = true;
		पूर्ण

		spin_unlock(&tilcdc_crtc->irq_lock);

		drm_crtc_handle_vblank(crtc);

		अगर (!skip_event) अणु
			काष्ठा drm_pending_vblank_event *event;

			spin_lock(&dev->event_lock);

			event = tilcdc_crtc->event;
			tilcdc_crtc->event = शून्य;
			अगर (event)
				drm_crtc_send_vblank_event(crtc, event);

			spin_unlock(&dev->event_lock);
		पूर्ण

		अगर (tilcdc_crtc->frame_पूर्णांकact)
			tilcdc_crtc->sync_lost_count = 0;
		अन्यथा
			tilcdc_crtc->frame_पूर्णांकact = true;
	पूर्ण

	अगर (stat & LCDC_FIFO_UNDERFLOW)
		dev_err_ratelimited(dev->dev, "%s(0x%08x): FIFO underflow",
				    __func__, stat);

	अगर (stat & LCDC_PL_LOAD_DONE) अणु
		complete(&tilcdc_crtc->palette_loaded);
		अगर (priv->rev == 1)
			tilcdc_clear(dev, LCDC_RASTER_CTRL_REG,
				     LCDC_V1_PL_INT_ENA);
		अन्यथा
			tilcdc_ग_लिखो(dev, LCDC_INT_ENABLE_CLR_REG,
				     LCDC_V2_PL_INT_ENA);
	पूर्ण

	अगर (stat & LCDC_SYNC_LOST) अणु
		dev_err_ratelimited(dev->dev, "%s(0x%08x): Sync lost",
				    __func__, stat);
		tilcdc_crtc->frame_पूर्णांकact = false;
		अगर (priv->rev == 1) अणु
			reg = tilcdc_पढ़ो(dev, LCDC_RASTER_CTRL_REG);
			अगर (reg & LCDC_RASTER_ENABLE) अणु
				tilcdc_clear(dev, LCDC_RASTER_CTRL_REG,
					     LCDC_RASTER_ENABLE);
				tilcdc_set(dev, LCDC_RASTER_CTRL_REG,
					   LCDC_RASTER_ENABLE);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (tilcdc_crtc->sync_lost_count++ >
			    SYNC_LOST_COUNT_LIMIT) अणु
				dev_err(dev->dev,
					"%s(0x%08x): Sync lost flood detected, recovering",
					__func__, stat);
				queue_work(प्रणाली_wq,
					   &tilcdc_crtc->recover_work);
				tilcdc_ग_लिखो(dev, LCDC_INT_ENABLE_CLR_REG,
					     LCDC_SYNC_LOST);
				tilcdc_crtc->sync_lost_count = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (stat & LCDC_FRAME_DONE) अणु
		tilcdc_crtc->frame_करोne = true;
		wake_up(&tilcdc_crtc->frame_करोne_wq);
		/* rev 1 lcdc appears to hang अगर irq is not disbaled here */
		अगर (priv->rev == 1)
			tilcdc_clear(dev, LCDC_RASTER_CTRL_REG,
				     LCDC_V1_FRAME_DONE_INT_ENA);
	पूर्ण

	/* For revision 2 only */
	अगर (priv->rev == 2) अणु
		/* Indicate to LCDC that the पूर्णांकerrupt service routine has
		 * completed, see 13.3.6.1.6 in AM335x TRM.
		 */
		tilcdc_ग_लिखो(dev, LCDC_END_OF_INT_IND_REG, 0);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक tilcdc_crtc_create(काष्ठा drm_device *dev)
अणु
	काष्ठा tilcdc_drm_निजी *priv = dev->dev_निजी;
	काष्ठा tilcdc_crtc *tilcdc_crtc;
	काष्ठा drm_crtc *crtc;
	पूर्णांक ret;

	tilcdc_crtc = devm_kzalloc(dev->dev, माप(*tilcdc_crtc), GFP_KERNEL);
	अगर (!tilcdc_crtc)
		वापस -ENOMEM;

	init_completion(&tilcdc_crtc->palette_loaded);
	tilcdc_crtc->palette_base = dmam_alloc_coherent(dev->dev,
					TILCDC_PALETTE_SIZE,
					&tilcdc_crtc->palette_dma_handle,
					GFP_KERNEL | __GFP_ZERO);
	अगर (!tilcdc_crtc->palette_base)
		वापस -ENOMEM;
	*tilcdc_crtc->palette_base = TILCDC_PALETTE_FIRST_ENTRY;

	crtc = &tilcdc_crtc->base;

	ret = tilcdc_plane_init(dev, &tilcdc_crtc->primary);
	अगर (ret < 0)
		जाओ fail;

	mutex_init(&tilcdc_crtc->enable_lock);

	init_रुकोqueue_head(&tilcdc_crtc->frame_करोne_wq);

	spin_lock_init(&tilcdc_crtc->irq_lock);
	INIT_WORK(&tilcdc_crtc->recover_work, tilcdc_crtc_recover_work);

	ret = drm_crtc_init_with_planes(dev, crtc,
					&tilcdc_crtc->primary,
					शून्य,
					&tilcdc_crtc_funcs,
					"tilcdc crtc");
	अगर (ret < 0)
		जाओ fail;

	drm_crtc_helper_add(crtc, &tilcdc_crtc_helper_funcs);

	अगर (priv->is_componentized) अणु
		crtc->port = of_graph_get_port_by_id(dev->dev->of_node, 0);
		अगर (!crtc->port) अणु /* This should never happen */
			dev_err(dev->dev, "Port node not found in %pOF\n",
				dev->dev->of_node);
			ret = -EINVAL;
			जाओ fail;
		पूर्ण
	पूर्ण

	priv->crtc = crtc;
	वापस 0;

fail:
	tilcdc_crtc_destroy(crtc);
	वापस ret;
पूर्ण
