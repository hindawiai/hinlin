<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* drivers/gpu/drm/exynos/exynos7_drm_decon.c
 *
 * Copyright (C) 2014 Samsung Electronics Co.Ltd
 * Authors:
 *	Akshu Agarwal <akshua@gmail.com>
 *	Ajay Kumar <ajaykumar.rs@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <video/of_display_timing.h>
#समावेश <video/of_videomode.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_plane.h"
#समावेश "regs-decon7.h"

/*
 * DECON stands क्रम Display and Enhancement controller.
 */

#घोषणा MIN_FB_WIDTH_FOR_16WORD_BURST 128

#घोषणा WINDOWS_NR	2

काष्ठा decon_context अणु
	काष्ठा device			*dev;
	काष्ठा drm_device		*drm_dev;
	व्योम				*dma_priv;
	काष्ठा exynos_drm_crtc		*crtc;
	काष्ठा exynos_drm_plane		planes[WINDOWS_NR];
	काष्ठा exynos_drm_plane_config	configs[WINDOWS_NR];
	काष्ठा clk			*pclk;
	काष्ठा clk			*aclk;
	काष्ठा clk			*eclk;
	काष्ठा clk			*vclk;
	व्योम __iomem			*regs;
	अचिन्हित दीर्घ			irq_flags;
	bool				i80_अगर;
	bool				suspended;
	रुको_queue_head_t		रुको_vsync_queue;
	atomic_t			रुको_vsync_event;

	काष्ठा drm_encoder *encoder;
पूर्ण;

अटल स्थिर काष्ठा of_device_id decon_driver_dt_match[] = अणु
	अणु.compatible = "samsung,exynos7-decon"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, decon_driver_dt_match);

अटल स्थिर uपूर्णांक32_t decon_क्रमmats[] = अणु
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGBX8888,
	DRM_FORMAT_BGRX8888,
	DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888,
	DRM_FORMAT_RGBA8888,
	DRM_FORMAT_BGRA8888,
पूर्ण;

अटल स्थिर क्रमागत drm_plane_type decon_win_types[WINDOWS_NR] = अणु
	DRM_PLANE_TYPE_PRIMARY,
	DRM_PLANE_TYPE_CURSOR,
पूर्ण;

अटल व्योम decon_रुको_क्रम_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;

	अगर (ctx->suspended)
		वापस;

	atomic_set(&ctx->रुको_vsync_event, 1);

	/*
	 * रुको क्रम DECON to संकेत VSYNC पूर्णांकerrupt or वापस after
	 * समयout which is set to 50ms (refresh rate of 20).
	 */
	अगर (!रुको_event_समयout(ctx->रुको_vsync_queue,
				!atomic_पढ़ो(&ctx->रुको_vsync_event),
				HZ/20))
		DRM_DEV_DEBUG_KMS(ctx->dev, "vblank wait timed out.\n");
पूर्ण

अटल व्योम decon_clear_channels(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	अचिन्हित पूर्णांक win, ch_enabled = 0;

	/* Check अगर any channel is enabled. */
	क्रम (win = 0; win < WINDOWS_NR; win++) अणु
		u32 val = पढ़ोl(ctx->regs + WINCON(win));

		अगर (val & WINCONx_ENWIN) अणु
			val &= ~WINCONx_ENWIN;
			ग_लिखोl(val, ctx->regs + WINCON(win));
			ch_enabled = 1;
		पूर्ण
	पूर्ण

	/* Wait क्रम vsync, as disable channel takes effect at next vsync */
	अगर (ch_enabled)
		decon_रुको_क्रम_vblank(ctx->crtc);
पूर्ण

अटल पूर्णांक decon_ctx_initialize(काष्ठा decon_context *ctx,
			काष्ठा drm_device *drm_dev)
अणु
	ctx->drm_dev = drm_dev;

	decon_clear_channels(ctx->crtc);

	वापस exynos_drm_रेजिस्टर_dma(drm_dev, ctx->dev, &ctx->dma_priv);
पूर्ण

अटल व्योम decon_ctx_हटाओ(काष्ठा decon_context *ctx)
अणु
	/* detach this sub driver from iommu mapping अगर supported. */
	exynos_drm_unरेजिस्टर_dma(ctx->drm_dev, ctx->dev, &ctx->dma_priv);
पूर्ण

अटल u32 decon_calc_clkभाग(काष्ठा decon_context *ctx,
		स्थिर काष्ठा drm_display_mode *mode)
अणु
	अचिन्हित दीर्घ ideal_clk = mode->घड़ी;
	u32 clkभाग;

	/* Find the घड़ी भागider value that माला_लो us बंदst to ideal_clk */
	clkभाग = DIV_ROUND_UP(clk_get_rate(ctx->vclk), ideal_clk);

	वापस (clkभाग < 0x100) ? clkभाग : 0xff;
पूर्ण

अटल व्योम decon_commit(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	काष्ठा drm_display_mode *mode = &crtc->base.state->adjusted_mode;
	u32 val, clkभाग;

	अगर (ctx->suspended)
		वापस;

	/* nothing to करो अगर we haven't set the mode yet */
	अगर (mode->htotal == 0 || mode->vtotal == 0)
		वापस;

	अगर (!ctx->i80_अगर) अणु
		पूर्णांक vsync_len, vbpd, vfpd, hsync_len, hbpd, hfpd;
	      /* setup vertical timing values. */
		vsync_len = mode->crtc_vsync_end - mode->crtc_vsync_start;
		vbpd = mode->crtc_vtotal - mode->crtc_vsync_end;
		vfpd = mode->crtc_vsync_start - mode->crtc_vdisplay;

		val = VIDTCON0_VBPD(vbpd - 1) | VIDTCON0_VFPD(vfpd - 1);
		ग_लिखोl(val, ctx->regs + VIDTCON0);

		val = VIDTCON1_VSPW(vsync_len - 1);
		ग_लिखोl(val, ctx->regs + VIDTCON1);

		/* setup horizontal timing values.  */
		hsync_len = mode->crtc_hsync_end - mode->crtc_hsync_start;
		hbpd = mode->crtc_htotal - mode->crtc_hsync_end;
		hfpd = mode->crtc_hsync_start - mode->crtc_hdisplay;

		/* setup horizontal timing values.  */
		val = VIDTCON2_HBPD(hbpd - 1) | VIDTCON2_HFPD(hfpd - 1);
		ग_लिखोl(val, ctx->regs + VIDTCON2);

		val = VIDTCON3_HSPW(hsync_len - 1);
		ग_लिखोl(val, ctx->regs + VIDTCON3);
	पूर्ण

	/* setup horizontal and vertical display size. */
	val = VIDTCON4_LINEVAL(mode->vdisplay - 1) |
	       VIDTCON4_HOZVAL(mode->hdisplay - 1);
	ग_लिखोl(val, ctx->regs + VIDTCON4);

	ग_लिखोl(mode->vdisplay - 1, ctx->regs + LINECNT_OP_THRESHOLD);

	/*
	 * fields of रेजिस्टर with prefix '_F' would be updated
	 * at vsync(same as dma start)
	 */
	val = VIDCON0_ENVID | VIDCON0_ENVID_F;
	ग_लिखोl(val, ctx->regs + VIDCON0);

	clkभाग = decon_calc_clkभाग(ctx, mode);
	अगर (clkभाग > 1) अणु
		val = VCLKCON1_CLKVAL_NUM_VCLK(clkभाग - 1);
		ग_लिखोl(val, ctx->regs + VCLKCON1);
		ग_लिखोl(val, ctx->regs + VCLKCON2);
	पूर्ण

	val = पढ़ोl(ctx->regs + DECON_UPDATE);
	val |= DECON_UPDATE_STANDALONE_F;
	ग_लिखोl(val, ctx->regs + DECON_UPDATE);
पूर्ण

अटल पूर्णांक decon_enable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	u32 val;

	अगर (ctx->suspended)
		वापस -EPERM;

	अगर (!test_and_set_bit(0, &ctx->irq_flags)) अणु
		val = पढ़ोl(ctx->regs + VIDINTCON0);

		val |= VIDINTCON0_INT_ENABLE;

		अगर (!ctx->i80_अगर) अणु
			val |= VIDINTCON0_INT_FRAME;
			val &= ~VIDINTCON0_FRAMESEL0_MASK;
			val |= VIDINTCON0_FRAMESEL0_VSYNC;
		पूर्ण

		ग_लिखोl(val, ctx->regs + VIDINTCON0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम decon_disable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	u32 val;

	अगर (ctx->suspended)
		वापस;

	अगर (test_and_clear_bit(0, &ctx->irq_flags)) अणु
		val = पढ़ोl(ctx->regs + VIDINTCON0);

		val &= ~VIDINTCON0_INT_ENABLE;
		अगर (!ctx->i80_अगर)
			val &= ~VIDINTCON0_INT_FRAME;

		ग_लिखोl(val, ctx->regs + VIDINTCON0);
	पूर्ण
पूर्ण

अटल व्योम decon_win_set_pixfmt(काष्ठा decon_context *ctx, अचिन्हित पूर्णांक win,
				 काष्ठा drm_framebuffer *fb)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक padding;

	val = पढ़ोl(ctx->regs + WINCON(win));
	val &= ~WINCONx_BPPMODE_MASK;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_RGB565:
		val |= WINCONx_BPPMODE_16BPP_565;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		val |= WINCONx_BPPMODE_24BPP_xRGB;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_XBGR8888:
		val |= WINCONx_BPPMODE_24BPP_xBGR;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_RGBX8888:
		val |= WINCONx_BPPMODE_24BPP_RGBx;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_BGRX8888:
		val |= WINCONx_BPPMODE_24BPP_BGRx;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
		val |= WINCONx_BPPMODE_32BPP_ARGB | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_ABGR8888:
		val |= WINCONx_BPPMODE_32BPP_ABGR | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_RGBA8888:
		val |= WINCONx_BPPMODE_32BPP_RGBA | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_BGRA8888:
	शेष:
		val |= WINCONx_BPPMODE_32BPP_BGRA | WINCONx_BLD_PIX |
			WINCONx_ALPHA_SEL;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	पूर्ण

	DRM_DEV_DEBUG_KMS(ctx->dev, "cpp = %d\n", fb->क्रमmat->cpp[0]);

	/*
	 * In हाल of exynos, setting dma-burst to 16Word causes permanent
	 * tearing क्रम very small buffers, e.g. cursor buffer. Burst Mode
	 * चयनing which is based on plane size is not recommended as
	 * plane size varies a lot towards the end of the screen and rapid
	 * movement causes unstable DMA which results पूर्णांकo iommu crash/tear.
	 */

	padding = (fb->pitches[0] / fb->क्रमmat->cpp[0]) - fb->width;
	अगर (fb->width + padding < MIN_FB_WIDTH_FOR_16WORD_BURST) अणु
		val &= ~WINCONx_BURSTLEN_MASK;
		val |= WINCONx_BURSTLEN_8WORD;
	पूर्ण

	ग_लिखोl(val, ctx->regs + WINCON(win));
पूर्ण

अटल व्योम decon_win_set_colkey(काष्ठा decon_context *ctx, अचिन्हित पूर्णांक win)
अणु
	अचिन्हित पूर्णांक keycon0 = 0, keycon1 = 0;

	keycon0 = ~(WxKEYCON0_KEYBL_EN | WxKEYCON0_KEYEN_F |
			WxKEYCON0_सूचीCON) | WxKEYCON0_COMPKEY(0);

	keycon1 = WxKEYCON1_COLVAL(0xffffffff);

	ग_लिखोl(keycon0, ctx->regs + WKEYCON0_BASE(win));
	ग_लिखोl(keycon1, ctx->regs + WKEYCON1_BASE(win));
पूर्ण

/**
 * shaकरोw_protect_win() - disable updating values from shaकरोw रेजिस्टरs at vsync
 *
 * @ctx: display and enhancement controller context
 * @win: winकरोw to protect रेजिस्टरs क्रम
 * @protect: 1 to protect (disable updates)
 */
अटल व्योम decon_shaकरोw_protect_win(काष्ठा decon_context *ctx,
				     अचिन्हित पूर्णांक win, bool protect)
अणु
	u32 bits, val;

	bits = SHADOWCON_WINx_PROTECT(win);

	val = पढ़ोl(ctx->regs + SHADOWCON);
	अगर (protect)
		val |= bits;
	अन्यथा
		val &= ~bits;
	ग_लिखोl(val, ctx->regs + SHADOWCON);
पूर्ण

अटल व्योम decon_atomic_begin(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (ctx->suspended)
		वापस;

	क्रम (i = 0; i < WINDOWS_NR; i++)
		decon_shaकरोw_protect_win(ctx, i, true);
पूर्ण

अटल व्योम decon_update_plane(काष्ठा exynos_drm_crtc *crtc,
			       काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	काष्ठा decon_context *ctx = crtc->ctx;
	काष्ठा drm_framebuffer *fb = state->base.fb;
	पूर्णांक padding;
	अचिन्हित दीर्घ val, alpha;
	अचिन्हित पूर्णांक last_x;
	अचिन्हित पूर्णांक last_y;
	अचिन्हित पूर्णांक win = plane->index;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];
	अचिन्हित पूर्णांक pitch = fb->pitches[0];

	अगर (ctx->suspended)
		वापस;

	/*
	 * SHADOWCON/PRTCON रेजिस्टर is used क्रम enabling timing.
	 *
	 * क्रम example, once only width value of a रेजिस्टर is set,
	 * अगर the dma is started then decon hardware could malfunction so
	 * with protect winकरोw setting, the रेजिस्टर fields with prefix '_F'
	 * wouldn't be updated at vsync also but updated once unprotect winकरोw
	 * is set.
	 */

	/* buffer start address */
	val = (अचिन्हित दीर्घ)exynos_drm_fb_dma_addr(fb, 0);
	ग_लिखोl(val, ctx->regs + VIDW_BUF_START(win));

	padding = (pitch / cpp) - fb->width;

	/* buffer size */
	ग_लिखोl(fb->width + padding, ctx->regs + VIDW_WHOLE_X(win));
	ग_लिखोl(fb->height, ctx->regs + VIDW_WHOLE_Y(win));

	/* offset from the start of the buffer to पढ़ो */
	ग_लिखोl(state->src.x, ctx->regs + VIDW_OFFSET_X(win));
	ग_लिखोl(state->src.y, ctx->regs + VIDW_OFFSET_Y(win));

	DRM_DEV_DEBUG_KMS(ctx->dev, "start addr = 0x%lx\n",
			(अचिन्हित दीर्घ)val);
	DRM_DEV_DEBUG_KMS(ctx->dev, "ovl_width = %d, ovl_height = %d\n",
			state->crtc.w, state->crtc.h);

	val = VIDOSDxA_TOPLEFT_X(state->crtc.x) |
		VIDOSDxA_TOPLEFT_Y(state->crtc.y);
	ग_लिखोl(val, ctx->regs + VIDOSD_A(win));

	last_x = state->crtc.x + state->crtc.w;
	अगर (last_x)
		last_x--;
	last_y = state->crtc.y + state->crtc.h;
	अगर (last_y)
		last_y--;

	val = VIDOSDxB_BOTRIGHT_X(last_x) | VIDOSDxB_BOTRIGHT_Y(last_y);

	ग_लिखोl(val, ctx->regs + VIDOSD_B(win));

	DRM_DEV_DEBUG_KMS(ctx->dev, "osd pos: tx = %d, ty = %d, bx = %d, by = %d\n",
			state->crtc.x, state->crtc.y, last_x, last_y);

	/* OSD alpha */
	alpha = VIDOSDxC_ALPHA0_R_F(0x0) |
			VIDOSDxC_ALPHA0_G_F(0x0) |
			VIDOSDxC_ALPHA0_B_F(0x0);

	ग_लिखोl(alpha, ctx->regs + VIDOSD_C(win));

	alpha = VIDOSDxD_ALPHA1_R_F(0xff) |
			VIDOSDxD_ALPHA1_G_F(0xff) |
			VIDOSDxD_ALPHA1_B_F(0xff);

	ग_लिखोl(alpha, ctx->regs + VIDOSD_D(win));

	decon_win_set_pixfmt(ctx, win, fb);

	/* hardware winकरोw 0 करोesn't support color key. */
	अगर (win != 0)
		decon_win_set_colkey(ctx, win);

	/* wincon */
	val = पढ़ोl(ctx->regs + WINCON(win));
	val |= WINCONx_TRIPLE_BUF_MODE;
	val |= WINCONx_ENWIN;
	ग_लिखोl(val, ctx->regs + WINCON(win));

	/* Enable DMA channel and unprotect winकरोws */
	decon_shaकरोw_protect_win(ctx, win, false);

	val = पढ़ोl(ctx->regs + DECON_UPDATE);
	val |= DECON_UPDATE_STANDALONE_F;
	ग_लिखोl(val, ctx->regs + DECON_UPDATE);
पूर्ण

अटल व्योम decon_disable_plane(काष्ठा exynos_drm_crtc *crtc,
				काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	अचिन्हित पूर्णांक win = plane->index;
	u32 val;

	अगर (ctx->suspended)
		वापस;

	/* protect winकरोws */
	decon_shaकरोw_protect_win(ctx, win, true);

	/* wincon */
	val = पढ़ोl(ctx->regs + WINCON(win));
	val &= ~WINCONx_ENWIN;
	ग_लिखोl(val, ctx->regs + WINCON(win));

	val = पढ़ोl(ctx->regs + DECON_UPDATE);
	val |= DECON_UPDATE_STANDALONE_F;
	ग_लिखोl(val, ctx->regs + DECON_UPDATE);
पूर्ण

अटल व्योम decon_atomic_flush(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (ctx->suspended)
		वापस;

	क्रम (i = 0; i < WINDOWS_NR; i++)
		decon_shaकरोw_protect_win(ctx, i, false);
	exynos_crtc_handle_event(crtc);
पूर्ण

अटल व्योम decon_init(काष्ठा decon_context *ctx)
अणु
	u32 val;

	ग_लिखोl(VIDCON0_SWRESET, ctx->regs + VIDCON0);

	val = VIDOUTCON0_DISP_IF_0_ON;
	अगर (!ctx->i80_अगर)
		val |= VIDOUTCON0_RGBIF;
	ग_लिखोl(val, ctx->regs + VIDOUTCON0);

	ग_लिखोl(VCLKCON0_CLKVALUP | VCLKCON0_VCLKFREE, ctx->regs + VCLKCON0);

	अगर (!ctx->i80_अगर)
		ग_लिखोl(VIDCON1_VCLK_HOLD, ctx->regs + VIDCON1(0));
पूर्ण

अटल व्योम decon_atomic_enable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;

	अगर (!ctx->suspended)
		वापस;

	pm_runसमय_get_sync(ctx->dev);

	decon_init(ctx);

	/* अगर vblank was enabled status, enable it again. */
	अगर (test_and_clear_bit(0, &ctx->irq_flags))
		decon_enable_vblank(ctx->crtc);

	decon_commit(ctx->crtc);

	ctx->suspended = false;
पूर्ण

अटल व्योम decon_atomic_disable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (ctx->suspended)
		वापस;

	/*
	 * We need to make sure that all winकरोws are disabled beक्रमe we
	 * suspend that connector. Otherwise we might try to scan from
	 * a destroyed buffer later.
	 */
	क्रम (i = 0; i < WINDOWS_NR; i++)
		decon_disable_plane(crtc, &ctx->planes[i]);

	pm_runसमय_put_sync(ctx->dev);

	ctx->suspended = true;
पूर्ण

अटल स्थिर काष्ठा exynos_drm_crtc_ops decon_crtc_ops = अणु
	.atomic_enable = decon_atomic_enable,
	.atomic_disable = decon_atomic_disable,
	.enable_vblank = decon_enable_vblank,
	.disable_vblank = decon_disable_vblank,
	.atomic_begin = decon_atomic_begin,
	.update_plane = decon_update_plane,
	.disable_plane = decon_disable_plane,
	.atomic_flush = decon_atomic_flush,
पूर्ण;


अटल irqवापस_t decon_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा decon_context *ctx = (काष्ठा decon_context *)dev_id;
	u32 val, clear_bit;

	val = पढ़ोl(ctx->regs + VIDINTCON1);

	clear_bit = ctx->i80_अगर ? VIDINTCON1_INT_I80 : VIDINTCON1_INT_FRAME;
	अगर (val & clear_bit)
		ग_लिखोl(clear_bit, ctx->regs + VIDINTCON1);

	/* check the crtc is detached alपढ़ोy from encoder */
	अगर (!ctx->drm_dev)
		जाओ out;

	अगर (!ctx->i80_अगर) अणु
		drm_crtc_handle_vblank(&ctx->crtc->base);

		/* set रुको vsync event to zero and wake up queue. */
		अगर (atomic_पढ़ो(&ctx->रुको_vsync_event)) अणु
			atomic_set(&ctx->रुको_vsync_event, 0);
			wake_up(&ctx->रुको_vsync_queue);
		पूर्ण
	पूर्ण
out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक decon_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_plane *exynos_plane;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = decon_ctx_initialize(ctx, drm_dev);
	अगर (ret) अणु
		DRM_DEV_ERROR(dev, "decon_ctx_initialize failed.\n");
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < WINDOWS_NR; i++) अणु
		ctx->configs[i].pixel_क्रमmats = decon_क्रमmats;
		ctx->configs[i].num_pixel_क्रमmats = ARRAY_SIZE(decon_क्रमmats);
		ctx->configs[i].zpos = i;
		ctx->configs[i].type = decon_win_types[i];

		ret = exynos_plane_init(drm_dev, &ctx->planes[i], i,
					&ctx->configs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	exynos_plane = &ctx->planes[DEFAULT_WIN];
	ctx->crtc = exynos_drm_crtc_create(drm_dev, &exynos_plane->base,
			EXYNOS_DISPLAY_TYPE_LCD, &decon_crtc_ops, ctx);
	अगर (IS_ERR(ctx->crtc)) अणु
		decon_ctx_हटाओ(ctx);
		वापस PTR_ERR(ctx->crtc);
	पूर्ण

	अगर (ctx->encoder)
		exynos_dpi_bind(drm_dev, ctx->encoder);

	वापस 0;

पूर्ण

अटल व्योम decon_unbind(काष्ठा device *dev, काष्ठा device *master,
			व्योम *data)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);

	decon_atomic_disable(ctx->crtc);

	अगर (ctx->encoder)
		exynos_dpi_हटाओ(ctx->encoder);

	decon_ctx_हटाओ(ctx);
पूर्ण

अटल स्थिर काष्ठा component_ops decon_component_ops = अणु
	.bind	= decon_bind,
	.unbind = decon_unbind,
पूर्ण;

अटल पूर्णांक decon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा decon_context *ctx;
	काष्ठा device_node *i80_अगर_timings;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (!dev->of_node)
		वापस -ENODEV;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;
	ctx->suspended = true;

	i80_अगर_timings = of_get_child_by_name(dev->of_node, "i80-if-timings");
	अगर (i80_अगर_timings)
		ctx->i80_अगर = true;
	of_node_put(i80_अगर_timings);

	ctx->regs = of_iomap(dev->of_node, 0);
	अगर (!ctx->regs)
		वापस -ENOMEM;

	ctx->pclk = devm_clk_get(dev, "pclk_decon0");
	अगर (IS_ERR(ctx->pclk)) अणु
		dev_err(dev, "failed to get bus clock pclk\n");
		ret = PTR_ERR(ctx->pclk);
		जाओ err_iounmap;
	पूर्ण

	ctx->aclk = devm_clk_get(dev, "aclk_decon0");
	अगर (IS_ERR(ctx->aclk)) अणु
		dev_err(dev, "failed to get bus clock aclk\n");
		ret = PTR_ERR(ctx->aclk);
		जाओ err_iounmap;
	पूर्ण

	ctx->eclk = devm_clk_get(dev, "decon0_eclk");
	अगर (IS_ERR(ctx->eclk)) अणु
		dev_err(dev, "failed to get eclock\n");
		ret = PTR_ERR(ctx->eclk);
		जाओ err_iounmap;
	पूर्ण

	ctx->vclk = devm_clk_get(dev, "decon0_vclk");
	अगर (IS_ERR(ctx->vclk)) अणु
		dev_err(dev, "failed to get vclock\n");
		ret = PTR_ERR(ctx->vclk);
		जाओ err_iounmap;
	पूर्ण

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ,
					   ctx->i80_अगर ? "lcd_sys" : "vsync");
	अगर (!res) अणु
		dev_err(dev, "irq request failed.\n");
		ret = -ENXIO;
		जाओ err_iounmap;
	पूर्ण

	ret = devm_request_irq(dev, res->start, decon_irq_handler,
							0, "drm_decon", ctx);
	अगर (ret) अणु
		dev_err(dev, "irq request failed.\n");
		जाओ err_iounmap;
	पूर्ण

	init_रुकोqueue_head(&ctx->रुको_vsync_queue);
	atomic_set(&ctx->रुको_vsync_event, 0);

	platक्रमm_set_drvdata(pdev, ctx);

	ctx->encoder = exynos_dpi_probe(dev);
	अगर (IS_ERR(ctx->encoder)) अणु
		ret = PTR_ERR(ctx->encoder);
		जाओ err_iounmap;
	पूर्ण

	pm_runसमय_enable(dev);

	ret = component_add(dev, &decon_component_ops);
	अगर (ret)
		जाओ err_disable_pm_runसमय;

	वापस ret;

err_disable_pm_runसमय:
	pm_runसमय_disable(dev);

err_iounmap:
	iounmap(ctx->regs);

	वापस ret;
पूर्ण

अटल पूर्णांक decon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(&pdev->dev);

	pm_runसमय_disable(&pdev->dev);

	iounmap(ctx->regs);

	component_del(&pdev->dev, &decon_component_ops);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक exynos7_decon_suspend(काष्ठा device *dev)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);

	clk_disable_unprepare(ctx->vclk);
	clk_disable_unprepare(ctx->eclk);
	clk_disable_unprepare(ctx->aclk);
	clk_disable_unprepare(ctx->pclk);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos7_decon_resume(काष्ठा device *dev)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(ctx->pclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to prepare_enable the pclk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(ctx->aclk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to prepare_enable the aclk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(ctx->eclk);
	अगर  (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to prepare_enable the eclk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(ctx->vclk);
	अगर  (ret < 0) अणु
		DRM_DEV_ERROR(dev, "Failed to prepare_enable the vclk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos7_decon_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos7_decon_suspend, exynos7_decon_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver decon_driver = अणु
	.probe		= decon_probe,
	.हटाओ		= decon_हटाओ,
	.driver		= अणु
		.name	= "exynos-decon",
		.pm	= &exynos7_decon_pm_ops,
		.of_match_table = decon_driver_dt_match,
	पूर्ण,
पूर्ण;
