<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* exynos_drm_fimd.c
 *
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Authors:
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Inki Dae <inki.dae@samsung.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <video/of_display_timing.h>
#समावेश <video/of_videomode.h>
#समावेश <video/samsung_fimd.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_plane.h"

/*
 * FIMD stands क्रम Fully Interactive Mobile Display and
 * as a display controller, it transfers contents drawn on memory
 * to a LCD Panel through Display Interfaces such as RGB or
 * CPU Interface.
 */

#घोषणा MIN_FB_WIDTH_FOR_16WORD_BURST 128

/* position control रेजिस्टर क्रम hardware winकरोw 0, 2 ~ 4.*/
#घोषणा VIDOSD_A(win)		(VIDOSD_BASE + 0x00 + (win) * 16)
#घोषणा VIDOSD_B(win)		(VIDOSD_BASE + 0x04 + (win) * 16)
/*
 * size control रेजिस्टर क्रम hardware winकरोws 0 and alpha control रेजिस्टर
 * क्रम hardware winकरोws 1 ~ 4
 */
#घोषणा VIDOSD_C(win)		(VIDOSD_BASE + 0x08 + (win) * 16)
/* size control रेजिस्टर क्रम hardware winकरोws 1 ~ 2. */
#घोषणा VIDOSD_D(win)		(VIDOSD_BASE + 0x0C + (win) * 16)

#घोषणा VIDWnALPHA0(win)	(VIDW_ALPHA + 0x00 + (win) * 8)
#घोषणा VIDWnALPHA1(win)	(VIDW_ALPHA + 0x04 + (win) * 8)

#घोषणा VIDWx_BUF_START(win, buf)	(VIDW_BUF_START(buf) + (win) * 8)
#घोषणा VIDWx_BUF_START_S(win, buf)	(VIDW_BUF_START_S(buf) + (win) * 8)
#घोषणा VIDWx_BUF_END(win, buf)		(VIDW_BUF_END(buf) + (win) * 8)
#घोषणा VIDWx_BUF_SIZE(win, buf)	(VIDW_BUF_SIZE(buf) + (win) * 4)

/* color key control रेजिस्टर क्रम hardware winकरोw 1 ~ 4. */
#घोषणा WKEYCON0_BASE(x)		((WKEYCON0 + 0x140) + ((x - 1) * 8))
/* color key value रेजिस्टर क्रम hardware winकरोw 1 ~ 4. */
#घोषणा WKEYCON1_BASE(x)		((WKEYCON1 + 0x140) + ((x - 1) * 8))

/* I80 trigger control रेजिस्टर */
#घोषणा TRIGCON				0x1A4
#घोषणा TRGMODE_ENABLE			(1 << 0)
#घोषणा SWTRGCMD_ENABLE			(1 << 1)
/* Exynos3250, 3472, 5260 5410, 5420 and 5422 only supported. */
#घोषणा HWTRGEN_ENABLE			(1 << 3)
#घोषणा HWTRGMASK_ENABLE		(1 << 4)
/* Exynos3250, 3472, 5260, 5420 and 5422 only supported. */
#घोषणा HWTRIGEN_PER_ENABLE		(1 << 31)

/* display mode change control रेजिस्टर except exynos4 */
#घोषणा VIDOUT_CON			0x000
#घोषणा VIDOUT_CON_F_I80_LDI0		(0x2 << 8)

/* I80 पूर्णांकerface control क्रम मुख्य LDI रेजिस्टर */
#घोषणा I80IFCONFAx(x)			(0x1B0 + (x) * 4)
#घोषणा I80IFCONFBx(x)			(0x1B8 + (x) * 4)
#घोषणा LCD_CS_SETUP(x)			((x) << 16)
#घोषणा LCD_WR_SETUP(x)			((x) << 12)
#घोषणा LCD_WR_ACTIVE(x)		((x) << 8)
#घोषणा LCD_WR_HOLD(x)			((x) << 4)
#घोषणा I80IFEN_ENABLE			(1 << 0)

/* FIMD has totally five hardware winकरोws. */
#घोषणा WINDOWS_NR	5

/* HW trigger flag on i80 panel. */
#घोषणा I80_HW_TRG     (1 << 1)

काष्ठा fimd_driver_data अणु
	अचिन्हित पूर्णांक timing_base;
	अचिन्हित पूर्णांक lcdblk_offset;
	अचिन्हित पूर्णांक lcdblk_vt_shअगरt;
	अचिन्हित पूर्णांक lcdblk_bypass_shअगरt;
	अचिन्हित पूर्णांक lcdblk_mic_bypass_shअगरt;
	अचिन्हित पूर्णांक trg_type;

	अचिन्हित पूर्णांक has_shaकरोwcon:1;
	अचिन्हित पूर्णांक has_clksel:1;
	अचिन्हित पूर्णांक has_limited_fmt:1;
	अचिन्हित पूर्णांक has_viकरोutcon:1;
	अचिन्हित पूर्णांक has_vtsel:1;
	अचिन्हित पूर्णांक has_mic_bypass:1;
	अचिन्हित पूर्णांक has_dp_clk:1;
	अचिन्हित पूर्णांक has_hw_trigger:1;
	अचिन्हित पूर्णांक has_trigger_per_te:1;
पूर्ण;

अटल काष्ठा fimd_driver_data s3c64xx_fimd_driver_data = अणु
	.timing_base = 0x0,
	.has_clksel = 1,
	.has_limited_fmt = 1,
पूर्ण;

अटल काष्ठा fimd_driver_data s5pv210_fimd_driver_data = अणु
	.timing_base = 0x0,
	.has_shaकरोwcon = 1,
	.has_clksel = 1,
पूर्ण;

अटल काष्ठा fimd_driver_data exynos3_fimd_driver_data = अणु
	.timing_base = 0x20000,
	.lcdblk_offset = 0x210,
	.lcdblk_bypass_shअगरt = 1,
	.has_shaकरोwcon = 1,
	.has_viकरोutcon = 1,
पूर्ण;

अटल काष्ठा fimd_driver_data exynos4_fimd_driver_data = अणु
	.timing_base = 0x0,
	.lcdblk_offset = 0x210,
	.lcdblk_vt_shअगरt = 10,
	.lcdblk_bypass_shअगरt = 1,
	.has_shaकरोwcon = 1,
	.has_vtsel = 1,
पूर्ण;

अटल काष्ठा fimd_driver_data exynos5_fimd_driver_data = अणु
	.timing_base = 0x20000,
	.lcdblk_offset = 0x214,
	.lcdblk_vt_shअगरt = 24,
	.lcdblk_bypass_shअगरt = 15,
	.has_shaकरोwcon = 1,
	.has_viकरोutcon = 1,
	.has_vtsel = 1,
	.has_dp_clk = 1,
पूर्ण;

अटल काष्ठा fimd_driver_data exynos5420_fimd_driver_data = अणु
	.timing_base = 0x20000,
	.lcdblk_offset = 0x214,
	.lcdblk_vt_shअगरt = 24,
	.lcdblk_bypass_shअगरt = 15,
	.lcdblk_mic_bypass_shअगरt = 11,
	.has_shaकरोwcon = 1,
	.has_viकरोutcon = 1,
	.has_vtsel = 1,
	.has_mic_bypass = 1,
	.has_dp_clk = 1,
पूर्ण;

काष्ठा fimd_context अणु
	काष्ठा device			*dev;
	काष्ठा drm_device		*drm_dev;
	व्योम				*dma_priv;
	काष्ठा exynos_drm_crtc		*crtc;
	काष्ठा exynos_drm_plane		planes[WINDOWS_NR];
	काष्ठा exynos_drm_plane_config	configs[WINDOWS_NR];
	काष्ठा clk			*bus_clk;
	काष्ठा clk			*lcd_clk;
	व्योम __iomem			*regs;
	काष्ठा regmap			*sysreg;
	अचिन्हित दीर्घ			irq_flags;
	u32				vidcon0;
	u32				vidcon1;
	u32				viकरोut_con;
	u32				i80अगरcon;
	bool				i80_अगर;
	bool				suspended;
	रुको_queue_head_t		रुको_vsync_queue;
	atomic_t			रुको_vsync_event;
	atomic_t			win_updated;
	atomic_t			triggering;
	u32				clkभाग;

	स्थिर काष्ठा fimd_driver_data *driver_data;
	काष्ठा drm_encoder *encoder;
	काष्ठा exynos_drm_clk		dp_clk;
पूर्ण;

अटल स्थिर काष्ठा of_device_id fimd_driver_dt_match[] = अणु
	अणु .compatible = "samsung,s3c6400-fimd",
	  .data = &s3c64xx_fimd_driver_data पूर्ण,
	अणु .compatible = "samsung,s5pv210-fimd",
	  .data = &s5pv210_fimd_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos3250-fimd",
	  .data = &exynos3_fimd_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos4210-fimd",
	  .data = &exynos4_fimd_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos5250-fimd",
	  .data = &exynos5_fimd_driver_data पूर्ण,
	अणु .compatible = "samsung,exynos5420-fimd",
	  .data = &exynos5420_fimd_driver_data पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, fimd_driver_dt_match);

अटल स्थिर क्रमागत drm_plane_type fimd_win_types[WINDOWS_NR] = अणु
	DRM_PLANE_TYPE_PRIMARY,
	DRM_PLANE_TYPE_OVERLAY,
	DRM_PLANE_TYPE_OVERLAY,
	DRM_PLANE_TYPE_OVERLAY,
	DRM_PLANE_TYPE_CURSOR,
पूर्ण;

अटल स्थिर uपूर्णांक32_t fimd_क्रमmats[] = अणु
	DRM_FORMAT_C8,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक capabilities[WINDOWS_NR] = अणु
	0,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
	EXYNOS_DRM_PLANE_CAP_WIN_BLEND | EXYNOS_DRM_PLANE_CAP_PIX_BLEND,
पूर्ण;

अटल अंतरभूत व्योम fimd_set_bits(काष्ठा fimd_context *ctx, u32 reg, u32 mask,
				 u32 val)
अणु
	val = (val & mask) | (पढ़ोl(ctx->regs + reg) & ~mask);
	ग_लिखोl(val, ctx->regs + reg);
पूर्ण

अटल पूर्णांक fimd_enable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	u32 val;

	अगर (ctx->suspended)
		वापस -EPERM;

	अगर (!test_and_set_bit(0, &ctx->irq_flags)) अणु
		val = पढ़ोl(ctx->regs + VIDINTCON0);

		val |= VIDINTCON0_INT_ENABLE;

		अगर (ctx->i80_अगर) अणु
			val |= VIDINTCON0_INT_I80IFDONE;
			val |= VIDINTCON0_INT_SYSMAINCON;
			val &= ~VIDINTCON0_INT_SYSSUBCON;
		पूर्ण अन्यथा अणु
			val |= VIDINTCON0_INT_FRAME;

			val &= ~VIDINTCON0_FRAMESEL0_MASK;
			val |= VIDINTCON0_FRAMESEL0_FRONTPORCH;
			val &= ~VIDINTCON0_FRAMESEL1_MASK;
			val |= VIDINTCON0_FRAMESEL1_NONE;
		पूर्ण

		ग_लिखोl(val, ctx->regs + VIDINTCON0);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम fimd_disable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	u32 val;

	अगर (ctx->suspended)
		वापस;

	अगर (test_and_clear_bit(0, &ctx->irq_flags)) अणु
		val = पढ़ोl(ctx->regs + VIDINTCON0);

		val &= ~VIDINTCON0_INT_ENABLE;

		अगर (ctx->i80_अगर) अणु
			val &= ~VIDINTCON0_INT_I80IFDONE;
			val &= ~VIDINTCON0_INT_SYSMAINCON;
			val &= ~VIDINTCON0_INT_SYSSUBCON;
		पूर्ण अन्यथा
			val &= ~VIDINTCON0_INT_FRAME;

		ग_लिखोl(val, ctx->regs + VIDINTCON0);
	पूर्ण
पूर्ण

अटल व्योम fimd_रुको_क्रम_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;

	अगर (ctx->suspended)
		वापस;

	atomic_set(&ctx->रुको_vsync_event, 1);

	/*
	 * रुको क्रम FIMD to संकेत VSYNC पूर्णांकerrupt or वापस after
	 * समयout which is set to 50ms (refresh rate of 20).
	 */
	अगर (!रुको_event_समयout(ctx->रुको_vsync_queue,
				!atomic_पढ़ो(&ctx->रुको_vsync_event),
				HZ/20))
		DRM_DEV_DEBUG_KMS(ctx->dev, "vblank wait timed out.\n");
पूर्ण

अटल व्योम fimd_enable_video_output(काष्ठा fimd_context *ctx, अचिन्हित पूर्णांक win,
					bool enable)
अणु
	u32 val = पढ़ोl(ctx->regs + WINCON(win));

	अगर (enable)
		val |= WINCONx_ENWIN;
	अन्यथा
		val &= ~WINCONx_ENWIN;

	ग_लिखोl(val, ctx->regs + WINCON(win));
पूर्ण

अटल व्योम fimd_enable_shaकरोw_channel_path(काष्ठा fimd_context *ctx,
						अचिन्हित पूर्णांक win,
						bool enable)
अणु
	u32 val = पढ़ोl(ctx->regs + SHADOWCON);

	अगर (enable)
		val |= SHADOWCON_CHx_ENABLE(win);
	अन्यथा
		val &= ~SHADOWCON_CHx_ENABLE(win);

	ग_लिखोl(val, ctx->regs + SHADOWCON);
पूर्ण

अटल व्योम fimd_clear_channels(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	अचिन्हित पूर्णांक win, ch_enabled = 0;

	/* Hardware is in unknown state, so ensure it माला_लो enabled properly */
	pm_runसमय_get_sync(ctx->dev);

	clk_prepare_enable(ctx->bus_clk);
	clk_prepare_enable(ctx->lcd_clk);

	/* Check अगर any channel is enabled. */
	क्रम (win = 0; win < WINDOWS_NR; win++) अणु
		u32 val = पढ़ोl(ctx->regs + WINCON(win));

		अगर (val & WINCONx_ENWIN) अणु
			fimd_enable_video_output(ctx, win, false);

			अगर (ctx->driver_data->has_shaकरोwcon)
				fimd_enable_shaकरोw_channel_path(ctx, win,
								false);

			ch_enabled = 1;
		पूर्ण
	पूर्ण

	/* Wait क्रम vsync, as disable channel takes effect at next vsync */
	अगर (ch_enabled) अणु
		ctx->suspended = false;

		fimd_enable_vblank(ctx->crtc);
		fimd_रुको_क्रम_vblank(ctx->crtc);
		fimd_disable_vblank(ctx->crtc);

		ctx->suspended = true;
	पूर्ण

	clk_disable_unprepare(ctx->lcd_clk);
	clk_disable_unprepare(ctx->bus_clk);

	pm_runसमय_put(ctx->dev);
पूर्ण


अटल पूर्णांक fimd_atomic_check(काष्ठा exynos_drm_crtc *crtc,
		काष्ठा drm_crtc_state *state)
अणु
	काष्ठा drm_display_mode *mode = &state->adjusted_mode;
	काष्ठा fimd_context *ctx = crtc->ctx;
	अचिन्हित दीर्घ ideal_clk, lcd_rate;
	u32 clkभाग;

	अगर (mode->घड़ी == 0) अणु
		DRM_DEV_ERROR(ctx->dev, "Mode has zero clock value.\n");
		वापस -EINVAL;
	पूर्ण

	ideal_clk = mode->घड़ी * 1000;

	अगर (ctx->i80_अगर) अणु
		/*
		 * The frame करोne पूर्णांकerrupt should be occurred prior to the
		 * next TE संकेत.
		 */
		ideal_clk *= 2;
	पूर्ण

	lcd_rate = clk_get_rate(ctx->lcd_clk);
	अगर (2 * lcd_rate < ideal_clk) अणु
		DRM_DEV_ERROR(ctx->dev,
			      "sclk_fimd clock too low(%lu) for requested pixel clock(%lu)\n",
			      lcd_rate, ideal_clk);
		वापस -EINVAL;
	पूर्ण

	/* Find the घड़ी भागider value that माला_लो us बंदst to ideal_clk */
	clkभाग = DIV_ROUND_CLOSEST(lcd_rate, ideal_clk);
	अगर (clkभाग >= 0x200) अणु
		DRM_DEV_ERROR(ctx->dev, "requested pixel clock(%lu) too low\n",
			      ideal_clk);
		वापस -EINVAL;
	पूर्ण

	ctx->clkभाग = (clkभाग < 0x100) ? clkभाग : 0xff;

	वापस 0;
पूर्ण

अटल व्योम fimd_setup_trigger(काष्ठा fimd_context *ctx)
अणु
	व्योम __iomem *timing_base = ctx->regs + ctx->driver_data->timing_base;
	u32 trg_type = ctx->driver_data->trg_type;
	u32 val = पढ़ोl(timing_base + TRIGCON);

	val &= ~(TRGMODE_ENABLE);

	अगर (trg_type == I80_HW_TRG) अणु
		अगर (ctx->driver_data->has_hw_trigger)
			val |= HWTRGEN_ENABLE | HWTRGMASK_ENABLE;
		अगर (ctx->driver_data->has_trigger_per_te)
			val |= HWTRIGEN_PER_ENABLE;
	पूर्ण अन्यथा अणु
		val |= TRGMODE_ENABLE;
	पूर्ण

	ग_लिखोl(val, timing_base + TRIGCON);
पूर्ण

अटल व्योम fimd_commit(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	काष्ठा drm_display_mode *mode = &crtc->base.state->adjusted_mode;
	स्थिर काष्ठा fimd_driver_data *driver_data = ctx->driver_data;
	व्योम *timing_base = ctx->regs + driver_data->timing_base;
	u32 val;

	अगर (ctx->suspended)
		वापस;

	/* nothing to करो अगर we haven't set the mode yet */
	अगर (mode->htotal == 0 || mode->vtotal == 0)
		वापस;

	अगर (ctx->i80_अगर) अणु
		val = ctx->i80अगरcon | I80IFEN_ENABLE;
		ग_लिखोl(val, timing_base + I80IFCONFAx(0));

		/* disable स्वतः frame rate */
		ग_लिखोl(0, timing_base + I80IFCONFBx(0));

		/* set video type selection to I80 पूर्णांकerface */
		अगर (driver_data->has_vtsel && ctx->sysreg &&
				regmap_update_bits(ctx->sysreg,
					driver_data->lcdblk_offset,
					0x3 << driver_data->lcdblk_vt_shअगरt,
					0x1 << driver_data->lcdblk_vt_shअगरt)) अणु
			DRM_DEV_ERROR(ctx->dev,
				      "Failed to update sysreg for I80 i/f.\n");
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		पूर्णांक vsync_len, vbpd, vfpd, hsync_len, hbpd, hfpd;
		u32 vidcon1;

		/* setup polarity values */
		vidcon1 = ctx->vidcon1;
		अगर (mode->flags & DRM_MODE_FLAG_NVSYNC)
			vidcon1 |= VIDCON1_INV_VSYNC;
		अगर (mode->flags & DRM_MODE_FLAG_NHSYNC)
			vidcon1 |= VIDCON1_INV_HSYNC;
		ग_लिखोl(vidcon1, ctx->regs + driver_data->timing_base + VIDCON1);

		/* setup vertical timing values. */
		vsync_len = mode->crtc_vsync_end - mode->crtc_vsync_start;
		vbpd = mode->crtc_vtotal - mode->crtc_vsync_end;
		vfpd = mode->crtc_vsync_start - mode->crtc_vdisplay;

		val = VIDTCON0_VBPD(vbpd - 1) |
			VIDTCON0_VFPD(vfpd - 1) |
			VIDTCON0_VSPW(vsync_len - 1);
		ग_लिखोl(val, ctx->regs + driver_data->timing_base + VIDTCON0);

		/* setup horizontal timing values.  */
		hsync_len = mode->crtc_hsync_end - mode->crtc_hsync_start;
		hbpd = mode->crtc_htotal - mode->crtc_hsync_end;
		hfpd = mode->crtc_hsync_start - mode->crtc_hdisplay;

		val = VIDTCON1_HBPD(hbpd - 1) |
			VIDTCON1_HFPD(hfpd - 1) |
			VIDTCON1_HSPW(hsync_len - 1);
		ग_लिखोl(val, ctx->regs + driver_data->timing_base + VIDTCON1);
	पूर्ण

	अगर (driver_data->has_viकरोutcon)
		ग_लिखोl(ctx->viकरोut_con, timing_base + VIDOUT_CON);

	/* set bypass selection */
	अगर (ctx->sysreg && regmap_update_bits(ctx->sysreg,
				driver_data->lcdblk_offset,
				0x1 << driver_data->lcdblk_bypass_shअगरt,
				0x1 << driver_data->lcdblk_bypass_shअगरt)) अणु
		DRM_DEV_ERROR(ctx->dev,
			      "Failed to update sysreg for bypass setting.\n");
		वापस;
	पूर्ण

	/* TODO: When MIC is enabled क्रम display path, the lcdblk_mic_bypass
	 * bit should be cleared.
	 */
	अगर (driver_data->has_mic_bypass && ctx->sysreg &&
	    regmap_update_bits(ctx->sysreg,
				driver_data->lcdblk_offset,
				0x1 << driver_data->lcdblk_mic_bypass_shअगरt,
				0x1 << driver_data->lcdblk_mic_bypass_shअगरt)) अणु
		DRM_DEV_ERROR(ctx->dev,
			      "Failed to update sysreg for bypass mic.\n");
		वापस;
	पूर्ण

	/* setup horizontal and vertical display size. */
	val = VIDTCON2_LINEVAL(mode->vdisplay - 1) |
	       VIDTCON2_HOZVAL(mode->hdisplay - 1) |
	       VIDTCON2_LINEVAL_E(mode->vdisplay - 1) |
	       VIDTCON2_HOZVAL_E(mode->hdisplay - 1);
	ग_लिखोl(val, ctx->regs + driver_data->timing_base + VIDTCON2);

	fimd_setup_trigger(ctx);

	/*
	 * fields of रेजिस्टर with prefix '_F' would be updated
	 * at vsync(same as dma start)
	 */
	val = ctx->vidcon0;
	val |= VIDCON0_ENVID | VIDCON0_ENVID_F;

	अगर (ctx->driver_data->has_clksel)
		val |= VIDCON0_CLKSEL_LCD;

	अगर (ctx->clkभाग > 1)
		val |= VIDCON0_CLKVAL_F(ctx->clkभाग - 1) | VIDCON0_CLKसूची;

	ग_लिखोl(val, ctx->regs + VIDCON0);
पूर्ण

अटल व्योम fimd_win_set_bldeq(काष्ठा fimd_context *ctx, अचिन्हित पूर्णांक win,
			       अचिन्हित पूर्णांक alpha, अचिन्हित पूर्णांक pixel_alpha)
अणु
	u32 mask = BLENDEQ_A_FUNC_F(0xf) | BLENDEQ_B_FUNC_F(0xf);
	u32 val = 0;

	चयन (pixel_alpha) अणु
	हाल DRM_MODE_BLEND_PIXEL_NONE:
	हाल DRM_MODE_BLEND_COVERAGE:
		val |= BLENDEQ_A_FUNC_F(BLENDEQ_ALPHA_A);
		val |= BLENDEQ_B_FUNC_F(BLENDEQ_ONE_MINUS_ALPHA_A);
		अवरोध;
	हाल DRM_MODE_BLEND_PREMULTI:
	शेष:
		अगर (alpha != DRM_BLEND_ALPHA_OPAQUE) अणु
			val |= BLENDEQ_A_FUNC_F(BLENDEQ_ALPHA0);
			val |= BLENDEQ_B_FUNC_F(BLENDEQ_ONE_MINUS_ALPHA_A);
		पूर्ण अन्यथा अणु
			val |= BLENDEQ_A_FUNC_F(BLENDEQ_ONE);
			val |= BLENDEQ_B_FUNC_F(BLENDEQ_ONE_MINUS_ALPHA_A);
		पूर्ण
		अवरोध;
	पूर्ण
	fimd_set_bits(ctx, BLENDEQx(win), mask, val);
पूर्ण

अटल व्योम fimd_win_set_bldmod(काष्ठा fimd_context *ctx, अचिन्हित पूर्णांक win,
				अचिन्हित पूर्णांक alpha, अचिन्हित पूर्णांक pixel_alpha)
अणु
	u32 win_alpha_l = (alpha >> 8) & 0xf;
	u32 win_alpha_h = alpha >> 12;
	u32 val = 0;

	चयन (pixel_alpha) अणु
	हाल DRM_MODE_BLEND_PIXEL_NONE:
		अवरोध;
	हाल DRM_MODE_BLEND_COVERAGE:
	हाल DRM_MODE_BLEND_PREMULTI:
	शेष:
		val |= WINCON1_ALPHA_SEL;
		val |= WINCON1_BLD_PIX;
		val |= WINCON1_ALPHA_MUL;
		अवरोध;
	पूर्ण
	fimd_set_bits(ctx, WINCON(win), WINCONx_BLEND_MODE_MASK, val);

	/* OSD alpha */
	val = VIDISD14C_ALPHA0_R(win_alpha_h) |
		VIDISD14C_ALPHA0_G(win_alpha_h) |
		VIDISD14C_ALPHA0_B(win_alpha_h) |
		VIDISD14C_ALPHA1_R(0x0) |
		VIDISD14C_ALPHA1_G(0x0) |
		VIDISD14C_ALPHA1_B(0x0);
	ग_लिखोl(val, ctx->regs + VIDOSD_C(win));

	val = VIDW_ALPHA_R(win_alpha_l) | VIDW_ALPHA_G(win_alpha_l) |
		VIDW_ALPHA_B(win_alpha_l);
	ग_लिखोl(val, ctx->regs + VIDWnALPHA0(win));

	val = VIDW_ALPHA_R(0x0) | VIDW_ALPHA_G(0x0) |
		VIDW_ALPHA_B(0x0);
	ग_लिखोl(val, ctx->regs + VIDWnALPHA1(win));

	fimd_set_bits(ctx, BLENDCON, BLENDCON_NEW_MASK,
			BLENDCON_NEW_8BIT_ALPHA_VALUE);
पूर्ण

अटल व्योम fimd_win_set_pixfmt(काष्ठा fimd_context *ctx, अचिन्हित पूर्णांक win,
				काष्ठा drm_framebuffer *fb, पूर्णांक width)
अणु
	काष्ठा exynos_drm_plane plane = ctx->planes[win];
	काष्ठा exynos_drm_plane_state *state =
		to_exynos_plane_state(plane.base.state);
	uपूर्णांक32_t pixel_क्रमmat = fb->क्रमmat->क्रमmat;
	अचिन्हित पूर्णांक alpha = state->base.alpha;
	u32 val = WINCONx_ENWIN;
	अचिन्हित पूर्णांक pixel_alpha;

	अगर (fb->क्रमmat->has_alpha)
		pixel_alpha = state->base.pixel_blend_mode;
	अन्यथा
		pixel_alpha = DRM_MODE_BLEND_PIXEL_NONE;

	/*
	 * In हाल of s3c64xx, winकरोw 0 करोesn't support alpha channel.
	 * So the request क्रमmat is ARGB8888 then change it to XRGB8888.
	 */
	अगर (ctx->driver_data->has_limited_fmt && !win) अणु
		अगर (pixel_क्रमmat == DRM_FORMAT_ARGB8888)
			pixel_क्रमmat = DRM_FORMAT_XRGB8888;
	पूर्ण

	चयन (pixel_क्रमmat) अणु
	हाल DRM_FORMAT_C8:
		val |= WINCON0_BPPMODE_8BPP_PALETTE;
		val |= WINCONx_BURSTLEN_8WORD;
		val |= WINCONx_BYTSWP;
		अवरोध;
	हाल DRM_FORMAT_XRGB1555:
		val |= WINCON0_BPPMODE_16BPP_1555;
		val |= WINCONx_HAWSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_RGB565:
		val |= WINCON0_BPPMODE_16BPP_565;
		val |= WINCONx_HAWSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_XRGB8888:
		val |= WINCON0_BPPMODE_24BPP_888;
		val |= WINCONx_WSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	हाल DRM_FORMAT_ARGB8888:
	शेष:
		val |= WINCON1_BPPMODE_25BPP_A1888;
		val |= WINCONx_WSWP;
		val |= WINCONx_BURSTLEN_16WORD;
		अवरोध;
	पूर्ण

	/*
	 * Setting dma-burst to 16Word causes permanent tearing क्रम very small
	 * buffers, e.g. cursor buffer. Burst Mode चयनing which based on
	 * plane size is not recommended as plane size varies alot towards the
	 * end of the screen and rapid movement causes unstable DMA, but it is
	 * still better to change dma-burst than displaying garbage.
	 */

	अगर (width < MIN_FB_WIDTH_FOR_16WORD_BURST) अणु
		val &= ~WINCONx_BURSTLEN_MASK;
		val |= WINCONx_BURSTLEN_4WORD;
	पूर्ण
	fimd_set_bits(ctx, WINCON(win), ~WINCONx_BLEND_MODE_MASK, val);

	/* hardware winकरोw 0 करोesn't support alpha channel. */
	अगर (win != 0) अणु
		fimd_win_set_bldmod(ctx, win, alpha, pixel_alpha);
		fimd_win_set_bldeq(ctx, win, alpha, pixel_alpha);
	पूर्ण
पूर्ण

अटल व्योम fimd_win_set_colkey(काष्ठा fimd_context *ctx, अचिन्हित पूर्णांक win)
अणु
	अचिन्हित पूर्णांक keycon0 = 0, keycon1 = 0;

	keycon0 = ~(WxKEYCON0_KEYBL_EN | WxKEYCON0_KEYEN_F |
			WxKEYCON0_सूचीCON) | WxKEYCON0_COMPKEY(0);

	keycon1 = WxKEYCON1_COLVAL(0xffffffff);

	ग_लिखोl(keycon0, ctx->regs + WKEYCON0_BASE(win));
	ग_लिखोl(keycon1, ctx->regs + WKEYCON1_BASE(win));
पूर्ण

/**
 * fimd_shaकरोw_protect_win() - disable updating values from shaकरोw रेजिस्टरs at vsync
 *
 * @ctx: local driver data
 * @win: winकरोw to protect रेजिस्टरs क्रम
 * @protect: 1 to protect (disable updates)
 */
अटल व्योम fimd_shaकरोw_protect_win(काष्ठा fimd_context *ctx,
				    अचिन्हित पूर्णांक win, bool protect)
अणु
	u32 reg, bits, val;

	/*
	 * SHADOWCON/PRTCON रेजिस्टर is used क्रम enabling timing.
	 *
	 * क्रम example, once only width value of a रेजिस्टर is set,
	 * अगर the dma is started then fimd hardware could malfunction so
	 * with protect winकरोw setting, the रेजिस्टर fields with prefix '_F'
	 * wouldn't be updated at vsync also but updated once unprotect winकरोw
	 * is set.
	 */

	अगर (ctx->driver_data->has_shaकरोwcon) अणु
		reg = SHADOWCON;
		bits = SHADOWCON_WINx_PROTECT(win);
	पूर्ण अन्यथा अणु
		reg = PRTCON;
		bits = PRTCON_PROTECT;
	पूर्ण

	val = पढ़ोl(ctx->regs + reg);
	अगर (protect)
		val |= bits;
	अन्यथा
		val &= ~bits;
	ग_लिखोl(val, ctx->regs + reg);
पूर्ण

अटल व्योम fimd_atomic_begin(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (ctx->suspended)
		वापस;

	क्रम (i = 0; i < WINDOWS_NR; i++)
		fimd_shaकरोw_protect_win(ctx, i, true);
पूर्ण

अटल व्योम fimd_atomic_flush(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (ctx->suspended)
		वापस;

	क्रम (i = 0; i < WINDOWS_NR; i++)
		fimd_shaकरोw_protect_win(ctx, i, false);

	exynos_crtc_handle_event(crtc);
पूर्ण

अटल व्योम fimd_update_plane(काष्ठा exynos_drm_crtc *crtc,
			      काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	काष्ठा fimd_context *ctx = crtc->ctx;
	काष्ठा drm_framebuffer *fb = state->base.fb;
	dma_addr_t dma_addr;
	अचिन्हित दीर्घ val, size, offset;
	अचिन्हित पूर्णांक last_x, last_y, buf_offsize, line_size;
	अचिन्हित पूर्णांक win = plane->index;
	अचिन्हित पूर्णांक cpp = fb->क्रमmat->cpp[0];
	अचिन्हित पूर्णांक pitch = fb->pitches[0];

	अगर (ctx->suspended)
		वापस;

	offset = state->src.x * cpp;
	offset += state->src.y * pitch;

	/* buffer start address */
	dma_addr = exynos_drm_fb_dma_addr(fb, 0) + offset;
	val = (अचिन्हित दीर्घ)dma_addr;
	ग_लिखोl(val, ctx->regs + VIDWx_BUF_START(win, 0));

	/* buffer end address */
	size = pitch * state->crtc.h;
	val = (अचिन्हित दीर्घ)(dma_addr + size);
	ग_लिखोl(val, ctx->regs + VIDWx_BUF_END(win, 0));

	DRM_DEV_DEBUG_KMS(ctx->dev,
			  "start addr = 0x%lx, end addr = 0x%lx, size = 0x%lx\n",
			  (अचिन्हित दीर्घ)dma_addr, val, size);
	DRM_DEV_DEBUG_KMS(ctx->dev, "ovl_width = %d, ovl_height = %d\n",
			  state->crtc.w, state->crtc.h);

	/* buffer size */
	buf_offsize = pitch - (state->crtc.w * cpp);
	line_size = state->crtc.w * cpp;
	val = VIDW_BUF_SIZE_OFFSET(buf_offsize) |
		VIDW_BUF_SIZE_PAGEWIDTH(line_size) |
		VIDW_BUF_SIZE_OFFSET_E(buf_offsize) |
		VIDW_BUF_SIZE_PAGEWIDTH_E(line_size);
	ग_लिखोl(val, ctx->regs + VIDWx_BUF_SIZE(win, 0));

	/* OSD position */
	val = VIDOSDxA_TOPLEFT_X(state->crtc.x) |
		VIDOSDxA_TOPLEFT_Y(state->crtc.y) |
		VIDOSDxA_TOPLEFT_X_E(state->crtc.x) |
		VIDOSDxA_TOPLEFT_Y_E(state->crtc.y);
	ग_लिखोl(val, ctx->regs + VIDOSD_A(win));

	last_x = state->crtc.x + state->crtc.w;
	अगर (last_x)
		last_x--;
	last_y = state->crtc.y + state->crtc.h;
	अगर (last_y)
		last_y--;

	val = VIDOSDxB_BOTRIGHT_X(last_x) | VIDOSDxB_BOTRIGHT_Y(last_y) |
		VIDOSDxB_BOTRIGHT_X_E(last_x) | VIDOSDxB_BOTRIGHT_Y_E(last_y);

	ग_लिखोl(val, ctx->regs + VIDOSD_B(win));

	DRM_DEV_DEBUG_KMS(ctx->dev,
			  "osd pos: tx = %d, ty = %d, bx = %d, by = %d\n",
			  state->crtc.x, state->crtc.y, last_x, last_y);

	/* OSD size */
	अगर (win != 3 && win != 4) अणु
		u32 offset = VIDOSD_D(win);
		अगर (win == 0)
			offset = VIDOSD_C(win);
		val = state->crtc.w * state->crtc.h;
		ग_लिखोl(val, ctx->regs + offset);

		DRM_DEV_DEBUG_KMS(ctx->dev, "osd size = 0x%x\n",
				  (अचिन्हित पूर्णांक)val);
	पूर्ण

	fimd_win_set_pixfmt(ctx, win, fb, state->src.w);

	/* hardware winकरोw 0 करोesn't support color key. */
	अगर (win != 0)
		fimd_win_set_colkey(ctx, win);

	fimd_enable_video_output(ctx, win, true);

	अगर (ctx->driver_data->has_shaकरोwcon)
		fimd_enable_shaकरोw_channel_path(ctx, win, true);

	अगर (ctx->i80_अगर)
		atomic_set(&ctx->win_updated, 1);
पूर्ण

अटल व्योम fimd_disable_plane(काष्ठा exynos_drm_crtc *crtc,
			       काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	अचिन्हित पूर्णांक win = plane->index;

	अगर (ctx->suspended)
		वापस;

	fimd_enable_video_output(ctx, win, false);

	अगर (ctx->driver_data->has_shaकरोwcon)
		fimd_enable_shaकरोw_channel_path(ctx, win, false);
पूर्ण

अटल व्योम fimd_atomic_enable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;

	अगर (!ctx->suspended)
		वापस;

	ctx->suspended = false;

	pm_runसमय_get_sync(ctx->dev);

	/* अगर vblank was enabled status, enable it again. */
	अगर (test_and_clear_bit(0, &ctx->irq_flags))
		fimd_enable_vblank(ctx->crtc);

	fimd_commit(ctx->crtc);
पूर्ण

अटल व्योम fimd_atomic_disable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (ctx->suspended)
		वापस;

	/*
	 * We need to make sure that all winकरोws are disabled beक्रमe we
	 * suspend that connector. Otherwise we might try to scan from
	 * a destroyed buffer later.
	 */
	क्रम (i = 0; i < WINDOWS_NR; i++)
		fimd_disable_plane(crtc, &ctx->planes[i]);

	fimd_enable_vblank(crtc);
	fimd_रुको_क्रम_vblank(crtc);
	fimd_disable_vblank(crtc);

	ग_लिखोl(0, ctx->regs + VIDCON0);

	pm_runसमय_put_sync(ctx->dev);
	ctx->suspended = true;
पूर्ण

अटल व्योम fimd_trigger(काष्ठा device *dev)
अणु
	काष्ठा fimd_context *ctx = dev_get_drvdata(dev);
	स्थिर काष्ठा fimd_driver_data *driver_data = ctx->driver_data;
	व्योम *timing_base = ctx->regs + driver_data->timing_base;
	u32 reg;

	 /*
	  * Skips triggering अगर in triggering state, because multiple triggering
	  * requests can cause panel reset.
	  */
	अगर (atomic_पढ़ो(&ctx->triggering))
		वापस;

	/* Enters triggering mode */
	atomic_set(&ctx->triggering, 1);

	reg = पढ़ोl(timing_base + TRIGCON);
	reg |= (TRGMODE_ENABLE | SWTRGCMD_ENABLE);
	ग_लिखोl(reg, timing_base + TRIGCON);

	/*
	 * Exits triggering mode अगर vblank is not enabled yet, because when the
	 * VIDINTCON0 रेजिस्टर is not set, it can not निकास from triggering mode.
	 */
	अगर (!test_bit(0, &ctx->irq_flags))
		atomic_set(&ctx->triggering, 0);
पूर्ण

अटल व्योम fimd_te_handler(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा fimd_context *ctx = crtc->ctx;
	u32 trg_type = ctx->driver_data->trg_type;

	/* Checks the crtc is detached alपढ़ोy from encoder */
	अगर (!ctx->drm_dev)
		वापस;

	अगर (trg_type == I80_HW_TRG)
		जाओ out;

	/*
	 * If there is a page flip request, triggers and handles the page flip
	 * event so that current fb can be updated पूर्णांकo panel GRAM.
	 */
	अगर (atomic_add_unless(&ctx->win_updated, -1, 0))
		fimd_trigger(ctx->dev);

out:
	/* Wakes up vsync event queue */
	अगर (atomic_पढ़ो(&ctx->रुको_vsync_event)) अणु
		atomic_set(&ctx->रुको_vsync_event, 0);
		wake_up(&ctx->रुको_vsync_queue);
	पूर्ण

	अगर (test_bit(0, &ctx->irq_flags))
		drm_crtc_handle_vblank(&ctx->crtc->base);
पूर्ण

अटल व्योम fimd_dp_घड़ी_enable(काष्ठा exynos_drm_clk *clk, bool enable)
अणु
	काष्ठा fimd_context *ctx = container_of(clk, काष्ठा fimd_context,
						dp_clk);
	u32 val = enable ? DP_MIE_CLK_DP_ENABLE : DP_MIE_CLK_DISABLE;
	ग_लिखोl(val, ctx->regs + DP_MIE_CLKCON);
पूर्ण

अटल स्थिर काष्ठा exynos_drm_crtc_ops fimd_crtc_ops = अणु
	.atomic_enable = fimd_atomic_enable,
	.atomic_disable = fimd_atomic_disable,
	.enable_vblank = fimd_enable_vblank,
	.disable_vblank = fimd_disable_vblank,
	.atomic_begin = fimd_atomic_begin,
	.update_plane = fimd_update_plane,
	.disable_plane = fimd_disable_plane,
	.atomic_flush = fimd_atomic_flush,
	.atomic_check = fimd_atomic_check,
	.te_handler = fimd_te_handler,
पूर्ण;

अटल irqवापस_t fimd_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fimd_context *ctx = (काष्ठा fimd_context *)dev_id;
	u32 val, clear_bit;

	val = पढ़ोl(ctx->regs + VIDINTCON1);

	clear_bit = ctx->i80_अगर ? VIDINTCON1_INT_I80 : VIDINTCON1_INT_FRAME;
	अगर (val & clear_bit)
		ग_लिखोl(clear_bit, ctx->regs + VIDINTCON1);

	/* check the crtc is detached alपढ़ोy from encoder */
	अगर (!ctx->drm_dev)
		जाओ out;

	अगर (!ctx->i80_अगर)
		drm_crtc_handle_vblank(&ctx->crtc->base);

	अगर (ctx->i80_अगर) अणु
		/* Exits triggering mode */
		atomic_set(&ctx->triggering, 0);
	पूर्ण अन्यथा अणु
		/* set रुको vsync event to zero and wake up queue. */
		अगर (atomic_पढ़ो(&ctx->रुको_vsync_event)) अणु
			atomic_set(&ctx->रुको_vsync_event, 0);
			wake_up(&ctx->रुको_vsync_queue);
		पूर्ण
	पूर्ण

out:
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक fimd_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा fimd_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_plane *exynos_plane;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ctx->drm_dev = drm_dev;

	क्रम (i = 0; i < WINDOWS_NR; i++) अणु
		ctx->configs[i].pixel_क्रमmats = fimd_क्रमmats;
		ctx->configs[i].num_pixel_क्रमmats = ARRAY_SIZE(fimd_क्रमmats);
		ctx->configs[i].zpos = i;
		ctx->configs[i].type = fimd_win_types[i];
		ctx->configs[i].capabilities = capabilities[i];
		ret = exynos_plane_init(drm_dev, &ctx->planes[i], i,
					&ctx->configs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	exynos_plane = &ctx->planes[DEFAULT_WIN];
	ctx->crtc = exynos_drm_crtc_create(drm_dev, &exynos_plane->base,
			EXYNOS_DISPLAY_TYPE_LCD, &fimd_crtc_ops, ctx);
	अगर (IS_ERR(ctx->crtc))
		वापस PTR_ERR(ctx->crtc);

	अगर (ctx->driver_data->has_dp_clk) अणु
		ctx->dp_clk.enable = fimd_dp_घड़ी_enable;
		ctx->crtc->pipe_clk = &ctx->dp_clk;
	पूर्ण

	अगर (ctx->encoder)
		exynos_dpi_bind(drm_dev, ctx->encoder);

	अगर (is_drm_iommu_supported(drm_dev))
		fimd_clear_channels(ctx->crtc);

	वापस exynos_drm_रेजिस्टर_dma(drm_dev, dev, &ctx->dma_priv);
पूर्ण

अटल व्योम fimd_unbind(काष्ठा device *dev, काष्ठा device *master,
			व्योम *data)
अणु
	काष्ठा fimd_context *ctx = dev_get_drvdata(dev);

	fimd_atomic_disable(ctx->crtc);

	exynos_drm_unरेजिस्टर_dma(ctx->drm_dev, ctx->dev, &ctx->dma_priv);

	अगर (ctx->encoder)
		exynos_dpi_हटाओ(ctx->encoder);
पूर्ण

अटल स्थिर काष्ठा component_ops fimd_component_ops = अणु
	.bind	= fimd_bind,
	.unbind = fimd_unbind,
पूर्ण;

अटल पूर्णांक fimd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fimd_context *ctx;
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
	ctx->driver_data = of_device_get_match_data(dev);

	अगर (of_property_पढ़ो_bool(dev->of_node, "samsung,invert-vden"))
		ctx->vidcon1 |= VIDCON1_INV_VDEN;
	अगर (of_property_पढ़ो_bool(dev->of_node, "samsung,invert-vclk"))
		ctx->vidcon1 |= VIDCON1_INV_VCLK;

	i80_अगर_timings = of_get_child_by_name(dev->of_node, "i80-if-timings");
	अगर (i80_अगर_timings) अणु
		u32 val;

		ctx->i80_अगर = true;

		अगर (ctx->driver_data->has_viकरोutcon)
			ctx->viकरोut_con |= VIDOUT_CON_F_I80_LDI0;
		अन्यथा
			ctx->vidcon0 |= VIDCON0_VIDOUT_I80_LDI0;
		/*
		 * The user manual describes that this "DSI_EN" bit is required
		 * to enable I80 24-bit data पूर्णांकerface.
		 */
		ctx->vidcon0 |= VIDCON0_DSI_EN;

		अगर (of_property_पढ़ो_u32(i80_अगर_timings, "cs-setup", &val))
			val = 0;
		ctx->i80अगरcon = LCD_CS_SETUP(val);
		अगर (of_property_पढ़ो_u32(i80_अगर_timings, "wr-setup", &val))
			val = 0;
		ctx->i80अगरcon |= LCD_WR_SETUP(val);
		अगर (of_property_पढ़ो_u32(i80_अगर_timings, "wr-active", &val))
			val = 1;
		ctx->i80अगरcon |= LCD_WR_ACTIVE(val);
		अगर (of_property_पढ़ो_u32(i80_अगर_timings, "wr-hold", &val))
			val = 0;
		ctx->i80अगरcon |= LCD_WR_HOLD(val);
	पूर्ण
	of_node_put(i80_अगर_timings);

	ctx->sysreg = syscon_regmap_lookup_by_phandle(dev->of_node,
							"samsung,sysreg");
	अगर (IS_ERR(ctx->sysreg)) अणु
		dev_warn(dev, "failed to get system register.\n");
		ctx->sysreg = शून्य;
	पूर्ण

	ctx->bus_clk = devm_clk_get(dev, "fimd");
	अगर (IS_ERR(ctx->bus_clk)) अणु
		dev_err(dev, "failed to get bus clock\n");
		वापस PTR_ERR(ctx->bus_clk);
	पूर्ण

	ctx->lcd_clk = devm_clk_get(dev, "sclk_fimd");
	अगर (IS_ERR(ctx->lcd_clk)) अणु
		dev_err(dev, "failed to get lcd clock\n");
		वापस PTR_ERR(ctx->lcd_clk);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	ctx->regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->regs))
		वापस PTR_ERR(ctx->regs);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ,
					   ctx->i80_अगर ? "lcd_sys" : "vsync");
	अगर (!res) अणु
		dev_err(dev, "irq request failed.\n");
		वापस -ENXIO;
	पूर्ण

	ret = devm_request_irq(dev, res->start, fimd_irq_handler,
							0, "drm_fimd", ctx);
	अगर (ret) अणु
		dev_err(dev, "irq request failed.\n");
		वापस ret;
	पूर्ण

	init_रुकोqueue_head(&ctx->रुको_vsync_queue);
	atomic_set(&ctx->रुको_vsync_event, 0);

	platक्रमm_set_drvdata(pdev, ctx);

	ctx->encoder = exynos_dpi_probe(dev);
	अगर (IS_ERR(ctx->encoder))
		वापस PTR_ERR(ctx->encoder);

	pm_runसमय_enable(dev);

	ret = component_add(dev, &fimd_component_ops);
	अगर (ret)
		जाओ err_disable_pm_runसमय;

	वापस ret;

err_disable_pm_runसमय:
	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक fimd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	component_del(&pdev->dev, &fimd_component_ops);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक exynos_fimd_suspend(काष्ठा device *dev)
अणु
	काष्ठा fimd_context *ctx = dev_get_drvdata(dev);

	clk_disable_unprepare(ctx->lcd_clk);
	clk_disable_unprepare(ctx->bus_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_fimd_resume(काष्ठा device *dev)
अणु
	काष्ठा fimd_context *ctx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(ctx->bus_clk);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev,
			      "Failed to prepare_enable the bus clk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(ctx->lcd_clk);
	अगर  (ret < 0) अणु
		DRM_DEV_ERROR(dev,
			      "Failed to prepare_enable the lcd clk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops exynos_fimd_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_fimd_suspend, exynos_fimd_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver fimd_driver = अणु
	.probe		= fimd_probe,
	.हटाओ		= fimd_हटाओ,
	.driver		= अणु
		.name	= "exynos4-fb",
		.owner	= THIS_MODULE,
		.pm	= &exynos_fimd_pm_ops,
		.of_match_table = fimd_driver_dt_match,
	पूर्ण,
पूर्ण;
