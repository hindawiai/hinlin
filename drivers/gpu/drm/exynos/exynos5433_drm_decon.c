<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* drivers/gpu/drm/exynos5433_drm_decon.c
 *
 * Copyright (C) 2015 Samsung Electronics Co.Ltd
 * Authors:
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Hyungwon Hwang <human.hwang@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_plane.h"
#समावेश "regs-decon5433.h"

#घोषणा DSD_CFG_MUX 0x1004
#घोषणा DSD_CFG_MUX_TE_UNMASK_GLOBAL BIT(13)

#घोषणा WINDOWS_NR	5
#घोषणा PRIMARY_WIN	2
#घोषणा CURSON_WIN	4

#घोषणा MIN_FB_WIDTH_FOR_16WORD_BURST	128

#घोषणा I80_HW_TRG	(1 << 0)
#घोषणा IFTYPE_HDMI	(1 << 1)

अटल स्थिर अक्षर * स्थिर decon_clks_name[] = अणु
	"pclk",
	"aclk_decon",
	"aclk_smmu_decon0x",
	"aclk_xiu_decon0x",
	"pclk_smmu_decon0x",
	"aclk_smmu_decon1x",
	"aclk_xiu_decon1x",
	"pclk_smmu_decon1x",
	"sclk_decon_vclk",
	"sclk_decon_eclk",
पूर्ण;

काष्ठा decon_context अणु
	काष्ठा device			*dev;
	काष्ठा drm_device		*drm_dev;
	व्योम				*dma_priv;
	काष्ठा exynos_drm_crtc		*crtc;
	काष्ठा exynos_drm_plane		planes[WINDOWS_NR];
	काष्ठा exynos_drm_plane_config	configs[WINDOWS_NR];
	व्योम __iomem			*addr;
	काष्ठा regmap			*sysreg;
	काष्ठा clk			*clks[ARRAY_SIZE(decon_clks_name)];
	अचिन्हित पूर्णांक			irq;
	अचिन्हित पूर्णांक			irq_vsync;
	अचिन्हित पूर्णांक			irq_lcd_sys;
	अचिन्हित पूर्णांक			te_irq;
	अचिन्हित दीर्घ			out_type;
	पूर्णांक				first_win;
	spinlock_t			vblank_lock;
	u32				frame_id;
पूर्ण;

अटल स्थिर uपूर्णांक32_t decon_क्रमmats[] = अणु
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर क्रमागत drm_plane_type decon_win_types[WINDOWS_NR] = अणु
	[PRIMARY_WIN] = DRM_PLANE_TYPE_PRIMARY,
	[CURSON_WIN] = DRM_PLANE_TYPE_CURSOR,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक capabilities[WINDOWS_NR] = अणु
	0,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
पूर्ण;

अटल अंतरभूत व्योम decon_set_bits(काष्ठा decon_context *ctx, u32 reg, u32 mask,
				  u32 val)
अणु
	val = (val & mask) | (पढ़ोl(ctx->addr + reg) & ~mask);
	ग_लिखोl(val, ctx->addr + reg);
पूर्ण

अटल पूर्णांक decon_enable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	u32 val;

	val = VIDINTCON0_INTEN;
	अगर (crtc->i80_mode)
		val |= VIDINTCON0_FRAMEDONE;
	अन्यथा
		val |= VIDINTCON0_INTFRMEN | VIDINTCON0_FRAMESEL_FP;

	ग_लिखोl(val, ctx->addr + DECON_VIDINTCON0);

	enable_irq(ctx->irq);
	अगर (!(ctx->out_type & I80_HW_TRG))
		enable_irq(ctx->te_irq);

	वापस 0;
पूर्ण

अटल व्योम decon_disable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;

	अगर (!(ctx->out_type & I80_HW_TRG))
		disable_irq_nosync(ctx->te_irq);
	disable_irq_nosync(ctx->irq);

	ग_लिखोl(0, ctx->addr + DECON_VIDINTCON0);
पूर्ण

/* वापस number of starts/ends of frame transmissions since reset */
अटल u32 decon_get_frame_count(काष्ठा decon_context *ctx, bool end)
अणु
	u32 frm, pfrm, status, cnt = 2;

	/* To get consistent result repeat पढ़ो until frame id is stable.
	 * Usually the loop will be executed once, in rare हालs when the loop
	 * is executed at frame change समय 2nd pass will be needed.
	 */
	frm = पढ़ोl(ctx->addr + DECON_CRFMID);
	करो अणु
		status = पढ़ोl(ctx->addr + DECON_VIDCON1);
		pfrm = frm;
		frm = पढ़ोl(ctx->addr + DECON_CRFMID);
	पूर्ण जबतक (frm != pfrm && --cnt);

	/* CRFMID is incremented on BPORCH in हाल of I80 and on VSYNC in हाल
	 * of RGB, it should be taken पूर्णांकo account.
	 */
	अगर (!frm)
		वापस 0;

	चयन (status & (VIDCON1_VSTATUS_MASK | VIDCON1_I80_ACTIVE)) अणु
	हाल VIDCON1_VSTATUS_VS:
		अगर (!(ctx->crtc->i80_mode))
			--frm;
		अवरोध;
	हाल VIDCON1_VSTATUS_BP:
		--frm;
		अवरोध;
	हाल VIDCON1_I80_ACTIVE:
	हाल VIDCON1_VSTATUS_AC:
		अगर (end)
			--frm;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस frm;
पूर्ण

अटल व्योम decon_setup_trigger(काष्ठा decon_context *ctx)
अणु
	अगर (!ctx->crtc->i80_mode && !(ctx->out_type & I80_HW_TRG))
		वापस;

	अगर (!(ctx->out_type & I80_HW_TRG)) अणु
		ग_लिखोl(TRIGCON_TRIGEN_PER_F | TRIGCON_TRIGEN_F |
		       TRIGCON_TE_AUTO_MASK | TRIGCON_SWTRIGEN,
		       ctx->addr + DECON_TRIGCON);
		वापस;
	पूर्ण

	ग_लिखोl(TRIGCON_TRIGEN_PER_F | TRIGCON_TRIGEN_F | TRIGCON_HWTRIGMASK
	       | TRIGCON_HWTRIGEN, ctx->addr + DECON_TRIGCON);

	अगर (regmap_update_bits(ctx->sysreg, DSD_CFG_MUX,
			       DSD_CFG_MUX_TE_UNMASK_GLOBAL, ~0))
		DRM_DEV_ERROR(ctx->dev, "Cannot update sysreg.\n");
पूर्ण

अटल व्योम decon_commit(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	काष्ठा drm_display_mode *m = &crtc->base.mode;
	bool पूर्णांकerlaced = false;
	u32 val;

	अगर (ctx->out_type & IFTYPE_HDMI) अणु
		m->crtc_hsync_start = m->crtc_hdisplay + 10;
		m->crtc_hsync_end = m->crtc_htotal - 92;
		m->crtc_vsync_start = m->crtc_vdisplay + 1;
		m->crtc_vsync_end = m->crtc_vsync_start + 1;
		अगर (m->flags & DRM_MODE_FLAG_INTERLACE)
			पूर्णांकerlaced = true;
	पूर्ण

	decon_setup_trigger(ctx);

	/* lcd on and use command अगर */
	val = VIDOUT_LCD_ON;
	अगर (पूर्णांकerlaced)
		val |= VIDOUT_INTERLACE_EN_F;
	अगर (crtc->i80_mode) अणु
		val |= VIDOUT_COMMAND_IF;
	पूर्ण अन्यथा अणु
		val |= VIDOUT_RGB_IF;
	पूर्ण

	ग_लिखोl(val, ctx->addr + DECON_VIDOUTCON0);

	अगर (पूर्णांकerlaced)
		val = VIDTCON2_LINEVAL(m->vdisplay / 2 - 1) |
			VIDTCON2_HOZVAL(m->hdisplay - 1);
	अन्यथा
		val = VIDTCON2_LINEVAL(m->vdisplay - 1) |
			VIDTCON2_HOZVAL(m->hdisplay - 1);
	ग_लिखोl(val, ctx->addr + DECON_VIDTCON2);

	अगर (!crtc->i80_mode) अणु
		पूर्णांक vbp = m->crtc_vtotal - m->crtc_vsync_end;
		पूर्णांक vfp = m->crtc_vsync_start - m->crtc_vdisplay;

		अगर (पूर्णांकerlaced)
			vbp = vbp / 2 - 1;
		val = VIDTCON00_VBPD_F(vbp - 1) | VIDTCON00_VFPD_F(vfp - 1);
		ग_लिखोl(val, ctx->addr + DECON_VIDTCON00);

		val = VIDTCON01_VSPW_F(
				m->crtc_vsync_end - m->crtc_vsync_start - 1);
		ग_लिखोl(val, ctx->addr + DECON_VIDTCON01);

		val = VIDTCON10_HBPD_F(
				m->crtc_htotal - m->crtc_hsync_end - 1) |
			VIDTCON10_HFPD_F(
				m->crtc_hsync_start - m->crtc_hdisplay - 1);
		ग_लिखोl(val, ctx->addr + DECON_VIDTCON10);

		val = VIDTCON11_HSPW_F(
				m->crtc_hsync_end - m->crtc_hsync_start - 1);
		ग_लिखोl(val, ctx->addr + DECON_VIDTCON11);
	पूर्ण

	/* enable output and display संकेत */
	decon_set_bits(ctx, DECON_VIDCON0, VIDCON0_ENVID | VIDCON0_ENVID_F, ~0);

	decon_set_bits(ctx, DECON_UPDATE, STANDALONE_UPDATE_F, ~0);
पूर्ण

अटल व्योम decon_win_set_bldeq(काष्ठा decon_context *ctx, अचिन्हित पूर्णांक win,
				अचिन्हित पूर्णांक alpha, अचिन्हित पूर्णांक pixel_alpha)
अणु
	u32 mask = BLENDERQ_A_FUNC_F(0xf) | BLENDERQ_B_FUNC_F(0xf);
	u32 val = 0;

	चयन (pixel_alpha) अणु
	हाल DRM_MODE_BLEND_PIXEL_NONE:
	हाल DRM_MODE_BLEND_COVERAGE:
		val |= BLENDERQ_A_FUNC_F(BLENDERQ_ALPHA_A);
		val |= BLENDERQ_B_FUNC_F(BLENDERQ_ONE_MINUS_ALPHA_A);
		अवरोध;
	हाल DRM_MODE_BLEND_PREMULTI:
	शेष:
		अगर (alpha != DRM_BLEND_ALPHA_OPAQUE) अणु
			val |= BLENDERQ_A_FUNC_F(BLENDERQ_ALPHA0);
			val |= BLENDERQ_B_FUNC_F(BLENDERQ_ONE_MINUS_ALPHA_A);
		पूर्ण अन्यथा अणु
			val |= BLENDERQ_A_FUNC_F(BLENDERQ_ONE);
			val |= BLENDERQ_B_FUNC_F(BLENDERQ_ONE_MINUS_ALPHA_A);
		पूर्ण
		अवरोध;
	पूर्ण
	decon_set_bits(ctx, DECON_BLENDERQx(win), mask, val);
पूर्ण

अटल व्योम decon_win_set_bldmod(काष्ठा decon_context *ctx, अचिन्हित पूर्णांक win,
				 अचिन्हित पूर्णांक alpha, अचिन्हित पूर्णांक pixel_alpha)
अणु
	u32 win_alpha = alpha >> 8;
	u32 val = 0;

	चयन (pixel_alpha) अणु
	हाल DRM_MODE_BLEND_PIXEL_NONE:
		अवरोध;
	हाल DRM_MODE_BLEND_COVERAGE:
	हाल DRM_MODE_BLEND_PREMULTI:
	शेष:
		val |= WINCONx_ALPHA_SEL_F;
		val |= WINCONx_BLD_PIX_F;
		val |= WINCONx_ALPHA_MUL_F;
		अवरोध;
	पूर्ण
	decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_BLEND_MODE_MASK, val);

	अगर (alpha != DRM_BLEND_ALPHA_OPAQUE) अणु
		val = VIDOSD_Wx_ALPHA_R_F(win_alpha) |
		      VIDOSD_Wx_ALPHA_G_F(win_alpha) |
		      VIDOSD_Wx_ALPHA_B_F(win_alpha);
		decon_set_bits(ctx, DECON_VIDOSDxC(win),
			       VIDOSDxC_ALPHA0_RGB_MASK, val);
		decon_set_bits(ctx, DECON_BLENDCON, BLEND_NEW, BLEND_NEW);
	पूर्ण
पूर्ण

अटल व्योम decon_win_set_pixfmt(काष्ठा decon_context *ctx, अचिन्हित पूर्णांक win,
				 काष्ठा drm_framebuffer *fb)
अणु
	काष्ठा exynos_drm_plane plane = ctx->planes[win];
	काष्ठा exynos_drm_plane_state *state =
		to_exynos_plane_state(plane.base.state);
	अचिन्हित पूर्णांक alpha = state->base.alpha;
	अचिन्हित पूर्णांक pixel_alpha;
	अचिन्हित दीर्घ val;

	अगर (fb->क्रमmat->has_alpha)
		pixel_alpha = state->base.pixel_blend_mode;
	अन्यथा
		pixel_alpha = DRM_MODE_BLEND_PIXEL_NONE;

	val = पढ़ोl(ctx->addr + DECON_WINCONx(win));
	val &= WINCONx_ENWIN_F;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_XRGB1555:
		val |= WINCONx_BPPMODE_16BPP_I1555;
		val |= WINCONx_HAWSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		val |= WINCONx_BPPMODE_16BPP_565;
		val |= WINCONx_HAWSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		val |= WINCONx_BPPMODE_24BPP_888;
		val |= WINCONx_WSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	शेष:
		val |= WINCONx_BPPMODE_32BPP_A8888;
		val |= WINCONx_WSWP_F;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	पूर्ण

	DRM_DEV_DEBUG_KMS(ctx->dev, "cpp = %u\n", fb->क्रमmat->cpp[0]);

	/*
	 * In हाल of exynos, setting dma-burst to 16Word causes permanent
	 * tearing क्रम very small buffers, e.g. cursor buffer. Burst Mode
	 * चयनing which is based on plane size is not recommended as
	 * plane size varies a lot towards the end of the screen and rapid
	 * movement causes unstable DMA which results पूर्णांकo iommu crash/tear.
	 */

	अगर (fb->width < MIN_FB_WIDTH_FOR_16WORD_BURST) अणु
		val &= ~WINCONx_BURSTLEN_MASK;
		val |= WINCONx_BURSTLEN_8WORD;
	पूर्ण
	decon_set_bits(ctx, DECON_WINCONx(win), ~WINCONx_BLEND_MODE_MASK, val);

	अगर (win > 0) अणु
		decon_win_set_bldmod(ctx, win, alpha, pixel_alpha);
		decon_win_set_bldeq(ctx, win, alpha, pixel_alpha);
	पूर्ण
पूर्ण

अटल व्योम decon_shaकरोw_protect(काष्ठा decon_context *ctx, bool protect)
अणु
	decon_set_bits(ctx, DECON_SHADOWCON, SHADOWCON_PROTECT_MASK,
		       protect ? ~0 : 0);
पूर्ण

अटल व्योम decon_atomic_begin(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;

	decon_shaकरोw_protect(ctx, true);
पूर्ण

#घोषणा BIT_VAL(x, e, s) (((x) & ((1 << ((e) - (s) + 1)) - 1)) << (s))
#घोषणा COORDINATE_X(x) BIT_VAL((x), 23, 12)
#घोषणा COORDINATE_Y(x) BIT_VAL((x), 11, 0)

अटल व्योम decon_update_plane(काष्ठा exynos_drm_crtc *crtc,
			       काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	काष्ठा decon_context *ctx = crtc->ctx;
	काष्ठा drm_framebuffer *fb = state->base.fb;
	अचिन्हित पूर्णांक win = plane->index;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];
	अचिन्हित पूर्णांक pitch = fb->pitches[0];
	dma_addr_t dma_addr = exynos_drm_fb_dma_addr(fb, 0);
	u32 val;

	अगर (crtc->base.mode.flags & DRM_MODE_FLAG_INTERLACE) अणु
		val = COORDINATE_X(state->crtc.x) |
			COORDINATE_Y(state->crtc.y / 2);
		ग_लिखोl(val, ctx->addr + DECON_VIDOSDxA(win));

		val = COORDINATE_X(state->crtc.x + state->crtc.w - 1) |
			COORDINATE_Y((state->crtc.y + state->crtc.h) / 2 - 1);
		ग_लिखोl(val, ctx->addr + DECON_VIDOSDxB(win));
	पूर्ण अन्यथा अणु
		val = COORDINATE_X(state->crtc.x) | COORDINATE_Y(state->crtc.y);
		ग_लिखोl(val, ctx->addr + DECON_VIDOSDxA(win));

		val = COORDINATE_X(state->crtc.x + state->crtc.w - 1) |
				COORDINATE_Y(state->crtc.y + state->crtc.h - 1);
		ग_लिखोl(val, ctx->addr + DECON_VIDOSDxB(win));
	पूर्ण

	val = VIDOSD_Wx_ALPHA_R_F(0xff) | VIDOSD_Wx_ALPHA_G_F(0xff) |
		VIDOSD_Wx_ALPHA_B_F(0xff);
	ग_लिखोl(val, ctx->addr + DECON_VIDOSDxC(win));

	val = VIDOSD_Wx_ALPHA_R_F(0x0) | VIDOSD_Wx_ALPHA_G_F(0x0) |
		VIDOSD_Wx_ALPHA_B_F(0x0);
	ग_लिखोl(val, ctx->addr + DECON_VIDOSDxD(win));

	ग_लिखोl(dma_addr, ctx->addr + DECON_VIDW0xADD0B0(win));

	val = dma_addr + pitch * state->src.h;
	ग_लिखोl(val, ctx->addr + DECON_VIDW0xADD1B0(win));

	अगर (!(ctx->out_type & IFTYPE_HDMI))
		val = BIT_VAL(pitch - state->crtc.w * cpp, 27, 14)
			| BIT_VAL(state->crtc.w * cpp, 13, 0);
	अन्यथा
		val = BIT_VAL(pitch - state->crtc.w * cpp, 29, 15)
			| BIT_VAL(state->crtc.w * cpp, 14, 0);
	ग_लिखोl(val, ctx->addr + DECON_VIDW0xADD2(win));

	decon_win_set_pixfmt(ctx, win, fb);

	/* winकरोw enable */
	decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_ENWIN_F, ~0);
पूर्ण

अटल व्योम decon_disable_plane(काष्ठा exynos_drm_crtc *crtc,
				काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	अचिन्हित पूर्णांक win = plane->index;

	decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_ENWIN_F, 0);
पूर्ण

अटल व्योम decon_atomic_flush(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->vblank_lock, flags);

	decon_shaकरोw_protect(ctx, false);

	decon_set_bits(ctx, DECON_UPDATE, STANDALONE_UPDATE_F, ~0);

	ctx->frame_id = decon_get_frame_count(ctx, true);

	exynos_crtc_handle_event(crtc);

	spin_unlock_irqrestore(&ctx->vblank_lock, flags);
पूर्ण

अटल व्योम decon_swreset(काष्ठा decon_context *ctx)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;

	ग_लिखोl(0, ctx->addr + DECON_VIDCON0);
	पढ़ोl_poll_समयout(ctx->addr + DECON_VIDCON0, val,
			   ~val & VIDCON0_STOP_STATUS, 12, 20000);

	ग_लिखोl(VIDCON0_SWRESET, ctx->addr + DECON_VIDCON0);
	ret = पढ़ोl_poll_समयout(ctx->addr + DECON_VIDCON0, val,
				 ~val & VIDCON0_SWRESET, 12, 20000);

	WARN(ret < 0, "failed to software reset DECON\n");

	spin_lock_irqsave(&ctx->vblank_lock, flags);
	ctx->frame_id = 0;
	spin_unlock_irqrestore(&ctx->vblank_lock, flags);

	अगर (!(ctx->out_type & IFTYPE_HDMI))
		वापस;

	ग_लिखोl(VIDCON0_CLKVALUP | VIDCON0_VLCKFREE, ctx->addr + DECON_VIDCON0);
	decon_set_bits(ctx, DECON_CMU,
		       CMU_CLKGAGE_MODE_SFR_F | CMU_CLKGAGE_MODE_MEM_F, ~0);
	ग_लिखोl(VIDCON1_VCLK_RUN_VDEN_DISABLE, ctx->addr + DECON_VIDCON1);
	ग_लिखोl(CRCCTRL_CRCEN | CRCCTRL_CRCSTART_F | CRCCTRL_CRCCLKEN,
	       ctx->addr + DECON_CRCCTRL);
पूर्ण

अटल व्योम decon_atomic_enable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;

	pm_runसमय_get_sync(ctx->dev);

	exynos_drm_pipe_clk_enable(crtc, true);

	decon_swreset(ctx);

	decon_commit(ctx->crtc);
पूर्ण

अटल व्योम decon_atomic_disable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (!(ctx->out_type & I80_HW_TRG))
		synchronize_irq(ctx->te_irq);
	synchronize_irq(ctx->irq);

	/*
	 * We need to make sure that all winकरोws are disabled beक्रमe we
	 * suspend that connector. Otherwise we might try to scan from
	 * a destroyed buffer later.
	 */
	क्रम (i = ctx->first_win; i < WINDOWS_NR; i++)
		decon_disable_plane(crtc, &ctx->planes[i]);

	decon_swreset(ctx);

	exynos_drm_pipe_clk_enable(crtc, false);

	pm_runसमय_put_sync(ctx->dev);
पूर्ण

अटल irqवापस_t decon_te_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा decon_context *ctx = dev_id;

	decon_set_bits(ctx, DECON_TRIGCON, TRIGCON_SWTRIGCMD, ~0);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम decon_clear_channels(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;
	पूर्णांक win, i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(decon_clks_name); i++) अणु
		ret = clk_prepare_enable(ctx->clks[i]);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	decon_shaकरोw_protect(ctx, true);
	क्रम (win = 0; win < WINDOWS_NR; win++)
		decon_set_bits(ctx, DECON_WINCONx(win), WINCONx_ENWIN_F, 0);
	decon_shaकरोw_protect(ctx, false);

	decon_set_bits(ctx, DECON_UPDATE, STANDALONE_UPDATE_F, ~0);

	/* TODO: रुको क्रम possible vsync */
	msleep(50);

err:
	जबतक (--i >= 0)
		clk_disable_unprepare(ctx->clks[i]);
पूर्ण

अटल क्रमागत drm_mode_status decon_mode_valid(काष्ठा exynos_drm_crtc *crtc,
		स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा decon_context *ctx = crtc->ctx;

	ctx->irq = crtc->i80_mode ? ctx->irq_lcd_sys : ctx->irq_vsync;

	अगर (ctx->irq)
		वापस MODE_OK;

	dev_info(ctx->dev, "Sink requires %s mode, but appropriate interrupt is not provided.\n",
			crtc->i80_mode ? "command" : "video");

	वापस MODE_BAD;
पूर्ण

अटल स्थिर काष्ठा exynos_drm_crtc_ops decon_crtc_ops = अणु
	.atomic_enable		= decon_atomic_enable,
	.atomic_disable		= decon_atomic_disable,
	.enable_vblank		= decon_enable_vblank,
	.disable_vblank		= decon_disable_vblank,
	.atomic_begin		= decon_atomic_begin,
	.update_plane		= decon_update_plane,
	.disable_plane		= decon_disable_plane,
	.mode_valid		= decon_mode_valid,
	.atomic_flush		= decon_atomic_flush,
पूर्ण;

अटल पूर्णांक decon_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_plane *exynos_plane;
	क्रमागत exynos_drm_output_type out_type;
	अचिन्हित पूर्णांक win;
	पूर्णांक ret;

	ctx->drm_dev = drm_dev;

	क्रम (win = ctx->first_win; win < WINDOWS_NR; win++) अणु
		ctx->configs[win].pixel_क्रमmats = decon_क्रमmats;
		ctx->configs[win].num_pixel_क्रमmats = ARRAY_SIZE(decon_क्रमmats);
		ctx->configs[win].zpos = win - ctx->first_win;
		ctx->configs[win].type = decon_win_types[win];
		ctx->configs[win].capabilities = capabilities[win];

		ret = exynos_plane_init(drm_dev, &ctx->planes[win], win,
					&ctx->configs[win]);
		अगर (ret)
			वापस ret;
	पूर्ण

	exynos_plane = &ctx->planes[PRIMARY_WIN];
	out_type = (ctx->out_type & IFTYPE_HDMI) ? EXYNOS_DISPLAY_TYPE_HDMI
						  : EXYNOS_DISPLAY_TYPE_LCD;
	ctx->crtc = exynos_drm_crtc_create(drm_dev, &exynos_plane->base,
			out_type, &decon_crtc_ops, ctx);
	अगर (IS_ERR(ctx->crtc))
		वापस PTR_ERR(ctx->crtc);

	decon_clear_channels(ctx->crtc);

	वापस exynos_drm_रेजिस्टर_dma(drm_dev, dev, &ctx->dma_priv);
पूर्ण

अटल व्योम decon_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);

	decon_atomic_disable(ctx->crtc);

	/* detach this sub driver from iommu mapping अगर supported. */
	exynos_drm_unरेजिस्टर_dma(ctx->drm_dev, ctx->dev, &ctx->dma_priv);
पूर्ण

अटल स्थिर काष्ठा component_ops decon_component_ops = अणु
	.bind	= decon_bind,
	.unbind = decon_unbind,
पूर्ण;

अटल व्योम decon_handle_vblank(काष्ठा decon_context *ctx)
अणु
	u32 frm;

	spin_lock(&ctx->vblank_lock);

	frm = decon_get_frame_count(ctx, true);

	अगर (frm != ctx->frame_id) अणु
		/* handle only अगर incremented, take care of wrap-around */
		अगर ((s32)(frm - ctx->frame_id) > 0)
			drm_crtc_handle_vblank(&ctx->crtc->base);
		ctx->frame_id = frm;
	पूर्ण

	spin_unlock(&ctx->vblank_lock);
पूर्ण

अटल irqवापस_t decon_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा decon_context *ctx = dev_id;
	u32 val;

	val = पढ़ोl(ctx->addr + DECON_VIDINTCON1);
	val &= VIDINTCON1_INTFRMDONEPEND | VIDINTCON1_INTFRMPEND;

	अगर (val) अणु
		ग_लिखोl(val, ctx->addr + DECON_VIDINTCON1);
		अगर (ctx->out_type & IFTYPE_HDMI) अणु
			val = पढ़ोl(ctx->addr + DECON_VIDOUTCON0);
			val &= VIDOUT_INTERLACE_EN_F | VIDOUT_INTERLACE_FIELD_F;
			अगर (val ==
			    (VIDOUT_INTERLACE_EN_F | VIDOUT_INTERLACE_FIELD_F))
				वापस IRQ_HANDLED;
		पूर्ण
		decon_handle_vblank(ctx);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक exynos5433_decon_suspend(काष्ठा device *dev)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);
	पूर्णांक i = ARRAY_SIZE(decon_clks_name);

	जबतक (--i >= 0)
		clk_disable_unprepare(ctx->clks[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos5433_decon_resume(काष्ठा device *dev)
अणु
	काष्ठा decon_context *ctx = dev_get_drvdata(dev);
	पूर्णांक i, ret;

	क्रम (i = 0; i < ARRAY_SIZE(decon_clks_name); i++) अणु
		ret = clk_prepare_enable(ctx->clks[i]);
		अगर (ret < 0)
			जाओ err;
	पूर्ण

	वापस 0;

err:
	जबतक (--i >= 0)
		clk_disable_unprepare(ctx->clks[i]);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos5433_decon_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos5433_decon_suspend, exynos5433_decon_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				     pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id exynos5433_decon_driver_dt_match[] = अणु
	अणु
		.compatible = "samsung,exynos5433-decon",
		.data = (व्योम *)I80_HW_TRG
	पूर्ण,
	अणु
		.compatible = "samsung,exynos5433-decon-tv",
		.data = (व्योम *)(I80_HW_TRG | IFTYPE_HDMI)
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, exynos5433_decon_driver_dt_match);

अटल पूर्णांक decon_conf_irq(काष्ठा decon_context *ctx, स्थिर अक्षर *name,
		irq_handler_t handler, अचिन्हित दीर्घ पूर्णांक flags)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(ctx->dev);
	पूर्णांक ret, irq = platक्रमm_get_irq_byname(pdev, name);

	अगर (irq < 0) अणु
		चयन (irq) अणु
		हाल -EPROBE_DEFER:
			वापस irq;
		हाल -ENODATA:
		हाल -ENXIO:
			वापस 0;
		शेष:
			dev_err(ctx->dev, "IRQ %s get failed, %d\n", name, irq);
			वापस irq;
		पूर्ण
	पूर्ण
	ret = devm_request_irq(ctx->dev, irq, handler,
			       flags | IRQF_NO_AUTOEN, "drm_decon", ctx);
	अगर (ret < 0) अणु
		dev_err(ctx->dev, "IRQ %s request failed\n", name);
		वापस ret;
	पूर्ण

	वापस irq;
पूर्ण

अटल पूर्णांक exynos5433_decon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा decon_context *ctx;
	काष्ठा resource *res;
	पूर्णांक ret;
	पूर्णांक i;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->dev = dev;
	ctx->out_type = (अचिन्हित दीर्घ)of_device_get_match_data(dev);
	spin_lock_init(&ctx->vblank_lock);

	अगर (ctx->out_type & IFTYPE_HDMI)
		ctx->first_win = 1;

	क्रम (i = 0; i < ARRAY_SIZE(decon_clks_name); i++) अणु
		काष्ठा clk *clk;

		clk = devm_clk_get(ctx->dev, decon_clks_name[i]);
		अगर (IS_ERR(clk))
			वापस PTR_ERR(clk);

		ctx->clks[i] = clk;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->addr = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->addr))
		वापस PTR_ERR(ctx->addr);

	ret = decon_conf_irq(ctx, "vsync", decon_irq_handler, 0);
	अगर (ret < 0)
		वापस ret;
	ctx->irq_vsync = ret;

	ret = decon_conf_irq(ctx, "lcd_sys", decon_irq_handler, 0);
	अगर (ret < 0)
		वापस ret;
	ctx->irq_lcd_sys = ret;

	ret = decon_conf_irq(ctx, "te", decon_te_irq_handler,
			IRQF_TRIGGER_RISING);
	अगर (ret < 0)
			वापस ret;
	अगर (ret) अणु
		ctx->te_irq = ret;
		ctx->out_type &= ~I80_HW_TRG;
	पूर्ण

	अगर (ctx->out_type & I80_HW_TRG) अणु
		ctx->sysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
							"samsung,disp-sysreg");
		अगर (IS_ERR(ctx->sysreg)) अणु
			dev_err(dev, "failed to get system register\n");
			वापस PTR_ERR(ctx->sysreg);
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, ctx);

	pm_runसमय_enable(dev);

	ret = component_add(dev, &decon_component_ops);
	अगर (ret)
		जाओ err_disable_pm_runसमय;

	वापस 0;

err_disable_pm_runसमय:
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक exynos5433_decon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	component_del(&pdev->dev, &decon_component_ops);

	वापस 0;
पूर्ण

काष्ठा platक्रमm_driver exynos5433_decon_driver = अणु
	.probe		= exynos5433_decon_probe,
	.हटाओ		= exynos5433_decon_हटाओ,
	.driver		= अणु
		.name	= "exynos5433-decon",
		.pm	= &exynos5433_decon_pm_ops,
		.of_match_table = exynos5433_decon_driver_dt_match,
	पूर्ण,
पूर्ण;
