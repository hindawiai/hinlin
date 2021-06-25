<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hisilicon Hi6220 SoC ADE(Advanced Display Engine)'s crtc&plane driver
 *
 * Copyright (c) 2016 Linaro Limited.
 * Copyright (c) 2014-2016 Hisilicon Limited.
 *
 * Author:
 *	Xinliang Liu <z.liuxinliang@hisilicon.com>
 *	Xinliang Liu <xinliang.liu@linaro.org>
 *	Xinwei Kong <kong.kongxinwei@hisilicon.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <video/display_timing.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>

#समावेश "kirin_drm_drv.h"
#समावेश "kirin_ade_reg.h"

#घोषणा OUT_OVLY	ADE_OVLY2 /* output overlay compositor */
#घोषणा ADE_DEBUG	1


काष्ठा ade_hw_ctx अणु
	व्योम __iomem  *base;
	काष्ठा regmap *noc_regmap;
	काष्ठा clk *ade_core_clk;
	काष्ठा clk *media_noc_clk;
	काष्ठा clk *ade_pix_clk;
	काष्ठा reset_control *reset;
	bool घातer_on;
	पूर्णांक irq;

	काष्ठा drm_crtc *crtc;
पूर्ण;

अटल स्थिर काष्ठा kirin_क्रमmat ade_क्रमmats[] = अणु
	/* 16bpp RGB: */
	अणु DRM_FORMAT_RGB565, ADE_RGB_565 पूर्ण,
	अणु DRM_FORMAT_BGR565, ADE_BGR_565 पूर्ण,
	/* 24bpp RGB: */
	अणु DRM_FORMAT_RGB888, ADE_RGB_888 पूर्ण,
	अणु DRM_FORMAT_BGR888, ADE_BGR_888 पूर्ण,
	/* 32bpp [A]RGB: */
	अणु DRM_FORMAT_XRGB8888, ADE_XRGB_8888 पूर्ण,
	अणु DRM_FORMAT_XBGR8888, ADE_XBGR_8888 पूर्ण,
	अणु DRM_FORMAT_RGBA8888, ADE_RGBA_8888 पूर्ण,
	अणु DRM_FORMAT_BGRA8888, ADE_BGRA_8888 पूर्ण,
	अणु DRM_FORMAT_ARGB8888, ADE_ARGB_8888 पूर्ण,
	अणु DRM_FORMAT_ABGR8888, ADE_ABGR_8888 पूर्ण,
पूर्ण;

अटल स्थिर u32 channel_क्रमmats[] = अणु
	/* channel 1,2,3,4 */
	DRM_FORMAT_RGB565, DRM_FORMAT_BGR565, DRM_FORMAT_RGB888,
	DRM_FORMAT_BGR888, DRM_FORMAT_XRGB8888, DRM_FORMAT_XBGR8888,
	DRM_FORMAT_RGBA8888, DRM_FORMAT_BGRA8888, DRM_FORMAT_ARGB8888,
	DRM_FORMAT_ABGR8888
पूर्ण;

/* convert from fourcc क्रमmat to ade क्रमmat */
अटल u32 ade_get_क्रमmat(u32 pixel_क्रमmat)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ade_क्रमmats); i++)
		अगर (ade_क्रमmats[i].pixel_क्रमmat == pixel_क्रमmat)
			वापस ade_क्रमmats[i].hw_क्रमmat;

	/* not found */
	DRM_ERROR("Not found pixel format!!fourcc_format= %d\n",
		  pixel_क्रमmat);
	वापस ADE_FORMAT_UNSUPPORT;
पूर्ण

अटल व्योम ade_update_reload_bit(व्योम __iomem *base, u32 bit_num, u32 val)
अणु
	u32 bit_ofst, reg_num;

	bit_ofst = bit_num % 32;
	reg_num = bit_num / 32;

	ade_update_bits(base + ADE_RELOAD_DIS(reg_num), bit_ofst,
			MASK(1), !!val);
पूर्ण

अटल u32 ade_पढ़ो_reload_bit(व्योम __iomem *base, u32 bit_num)
अणु
	u32 पंचांगp, bit_ofst, reg_num;

	bit_ofst = bit_num % 32;
	reg_num = bit_num / 32;

	पंचांगp = पढ़ोl(base + ADE_RELOAD_DIS(reg_num));
	वापस !!(BIT(bit_ofst) & पंचांगp);
पूर्ण

अटल व्योम ade_init(काष्ठा ade_hw_ctx *ctx)
अणु
	व्योम __iomem *base = ctx->base;

	/* enable clk gate */
	ade_update_bits(base + ADE_CTRL1, AUTO_CLK_GATE_EN_OFST,
			AUTO_CLK_GATE_EN, ADE_ENABLE);
	/* clear overlay */
	ग_लिखोl(0, base + ADE_OVLY1_TRANS_CFG);
	ग_लिखोl(0, base + ADE_OVLY_CTL);
	ग_लिखोl(0, base + ADE_OVLYX_CTL(OUT_OVLY));
	/* clear reset and reload regs */
	ग_लिखोl(MASK(32), base + ADE_SOFT_RST_SEL(0));
	ग_लिखोl(MASK(32), base + ADE_SOFT_RST_SEL(1));
	ग_लिखोl(MASK(32), base + ADE_RELOAD_DIS(0));
	ग_लिखोl(MASK(32), base + ADE_RELOAD_DIS(1));
	/*
	 * क्रम video mode, all the ade रेजिस्टरs should
	 * become effective at frame end.
	 */
	ade_update_bits(base + ADE_CTRL, FRM_END_START_OFST,
			FRM_END_START_MASK, REG_EFFECTIVE_IN_ADEEN_FRMEND);
पूर्ण

अटल bool ade_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				स्थिर काष्ठा drm_display_mode *mode,
				काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;

	adjusted_mode->घड़ी =
		clk_round_rate(ctx->ade_pix_clk, mode->घड़ी * 1000) / 1000;
	वापस true;
पूर्ण


अटल व्योम ade_set_pix_clk(काष्ठा ade_hw_ctx *ctx,
			    काष्ठा drm_display_mode *mode,
			    काष्ठा drm_display_mode *adj_mode)
अणु
	u32 clk_Hz = mode->घड़ी * 1000;
	पूर्णांक ret;

	/*
	 * Success should be guaranteed in mode_valid call back,
	 * so failure shouldn't happen here
	 */
	ret = clk_set_rate(ctx->ade_pix_clk, clk_Hz);
	अगर (ret)
		DRM_ERROR("failed to set pixel clk %dHz (%d)\n", clk_Hz, ret);
	adj_mode->घड़ी = clk_get_rate(ctx->ade_pix_clk) / 1000;
पूर्ण

अटल व्योम ade_ldi_set_mode(काष्ठा ade_hw_ctx *ctx,
			     काष्ठा drm_display_mode *mode,
			     काष्ठा drm_display_mode *adj_mode)
अणु
	व्योम __iomem *base = ctx->base;
	u32 width = mode->hdisplay;
	u32 height = mode->vdisplay;
	u32 hfp, hbp, hsw, vfp, vbp, vsw;
	u32 plr_flags;

	plr_flags = (mode->flags & DRM_MODE_FLAG_NVSYNC) ? FLAG_NVSYNC : 0;
	plr_flags |= (mode->flags & DRM_MODE_FLAG_NHSYNC) ? FLAG_NHSYNC : 0;
	hfp = mode->hsync_start - mode->hdisplay;
	hbp = mode->htotal - mode->hsync_end;
	hsw = mode->hsync_end - mode->hsync_start;
	vfp = mode->vsync_start - mode->vdisplay;
	vbp = mode->vtotal - mode->vsync_end;
	vsw = mode->vsync_end - mode->vsync_start;
	अगर (vsw > 15) अणु
		DRM_DEBUG_DRIVER("vsw exceeded 15\n");
		vsw = 15;
	पूर्ण

	ग_लिखोl((hbp << HBP_OFST) | hfp, base + LDI_HRZ_CTRL0);
	 /* the configured value is actual value - 1 */
	ग_लिखोl(hsw - 1, base + LDI_HRZ_CTRL1);
	ग_लिखोl((vbp << VBP_OFST) | vfp, base + LDI_VRT_CTRL0);
	 /* the configured value is actual value - 1 */
	ग_लिखोl(vsw - 1, base + LDI_VRT_CTRL1);
	 /* the configured value is actual value - 1 */
	ग_लिखोl(((height - 1) << VSIZE_OFST) | (width - 1),
	       base + LDI_DSP_SIZE);
	ग_लिखोl(plr_flags, base + LDI_PLR_CTRL);

	/* set overlay compositor output size */
	ग_लिखोl(((width - 1) << OUTPUT_XSIZE_OFST) | (height - 1),
	       base + ADE_OVLY_OUTPUT_SIZE(OUT_OVLY));

	/* ctran6 setting */
	ग_लिखोl(CTRAN_BYPASS_ON, base + ADE_CTRAN_DIS(ADE_CTRAN6));
	 /* the configured value is actual value - 1 */
	ग_लिखोl(width * height - 1, base + ADE_CTRAN_IMAGE_SIZE(ADE_CTRAN6));
	ade_update_reload_bit(base, CTRAN_OFST + ADE_CTRAN6, 0);

	ade_set_pix_clk(ctx, mode, adj_mode);

	DRM_DEBUG_DRIVER("set mode: %dx%d\n", width, height);
पूर्ण

अटल पूर्णांक ade_घातer_up(काष्ठा ade_hw_ctx *ctx)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(ctx->media_noc_clk);
	अगर (ret) अणु
		DRM_ERROR("failed to enable media_noc_clk (%d)\n", ret);
		वापस ret;
	पूर्ण

	ret = reset_control_deनिश्चित(ctx->reset);
	अगर (ret) अणु
		DRM_ERROR("failed to deassert reset\n");
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(ctx->ade_core_clk);
	अगर (ret) अणु
		DRM_ERROR("failed to enable ade_core_clk (%d)\n", ret);
		वापस ret;
	पूर्ण

	ade_init(ctx);
	ctx->घातer_on = true;
	वापस 0;
पूर्ण

अटल व्योम ade_घातer_करोwn(काष्ठा ade_hw_ctx *ctx)
अणु
	व्योम __iomem *base = ctx->base;

	ग_लिखोl(ADE_DISABLE, base + LDI_CTRL);
	/* dsi pixel off */
	ग_लिखोl(DSI_PCLK_OFF, base + LDI_HDMI_DSI_GT);

	clk_disable_unprepare(ctx->ade_core_clk);
	reset_control_निश्चित(ctx->reset);
	clk_disable_unprepare(ctx->media_noc_clk);
	ctx->घातer_on = false;
पूर्ण

अटल व्योम ade_set_medianoc_qos(काष्ठा ade_hw_ctx *ctx)
अणु
	काष्ठा regmap *map = ctx->noc_regmap;

	regmap_update_bits(map, ADE0_QOSGENERATOR_MODE,
			   QOSGENERATOR_MODE_MASK, BYPASS_MODE);
	regmap_update_bits(map, ADE0_QOSGENERATOR_EXTCONTROL,
			   SOCKET_QOS_EN, SOCKET_QOS_EN);

	regmap_update_bits(map, ADE1_QOSGENERATOR_MODE,
			   QOSGENERATOR_MODE_MASK, BYPASS_MODE);
	regmap_update_bits(map, ADE1_QOSGENERATOR_EXTCONTROL,
			   SOCKET_QOS_EN, SOCKET_QOS_EN);
पूर्ण

अटल पूर्णांक ade_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;
	व्योम __iomem *base = ctx->base;

	अगर (!ctx->घातer_on)
		(व्योम)ade_घातer_up(ctx);

	ade_update_bits(base + LDI_INT_EN, FRAME_END_INT_EN_OFST,
			MASK(1), 1);

	वापस 0;
पूर्ण

अटल व्योम ade_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;
	व्योम __iomem *base = ctx->base;

	अगर (!ctx->घातer_on) अणु
		DRM_ERROR("power is down! vblank disable fail\n");
		वापस;
	पूर्ण

	ade_update_bits(base + LDI_INT_EN, FRAME_END_INT_EN_OFST,
			MASK(1), 0);
पूर्ण

अटल irqवापस_t ade_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ade_hw_ctx *ctx = data;
	काष्ठा drm_crtc *crtc = ctx->crtc;
	व्योम __iomem *base = ctx->base;
	u32 status;

	status = पढ़ोl(base + LDI_MSK_INT);
	DRM_DEBUG_VBL("LDI IRQ: status=0x%X\n", status);

	/* vblank irq */
	अगर (status & BIT(FRAME_END_INT_EN_OFST)) अणु
		ade_update_bits(base + LDI_INT_CLR, FRAME_END_INT_EN_OFST,
				MASK(1), 1);
		drm_crtc_handle_vblank(crtc);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ade_display_enable(काष्ठा ade_hw_ctx *ctx)
अणु
	व्योम __iomem *base = ctx->base;
	u32 out_fmt = LDI_OUT_RGB_888;

	/* enable output overlay compositor */
	ग_लिखोl(ADE_ENABLE, base + ADE_OVLYX_CTL(OUT_OVLY));
	ade_update_reload_bit(base, OVLY_OFST + OUT_OVLY, 0);

	/* display source setting */
	ग_लिखोl(DISP_SRC_OVLY2, base + ADE_DISP_SRC_CFG);

	/* enable ade */
	ग_लिखोl(ADE_ENABLE, base + ADE_EN);
	/* enable ldi */
	ग_लिखोl(NORMAL_MODE, base + LDI_WORK_MODE);
	ग_लिखोl((out_fmt << BPP_OFST) | DATA_GATE_EN | LDI_EN,
	       base + LDI_CTRL);
	/* dsi pixel on */
	ग_लिखोl(DSI_PCLK_ON, base + LDI_HDMI_DSI_GT);
पूर्ण

#अगर ADE_DEBUG
अटल व्योम ade_rdma_dump_regs(व्योम __iomem *base, u32 ch)
अणु
	u32 reg_ctrl, reg_addr, reg_size, reg_stride, reg_space, reg_en;
	u32 val;

	reg_ctrl = RD_CH_CTRL(ch);
	reg_addr = RD_CH_ADDR(ch);
	reg_size = RD_CH_SIZE(ch);
	reg_stride = RD_CH_STRIDE(ch);
	reg_space = RD_CH_SPACE(ch);
	reg_en = RD_CH_EN(ch);

	val = ade_पढ़ो_reload_bit(base, RDMA_OFST + ch);
	DRM_DEBUG_DRIVER("[rdma%d]: reload(%d)\n", ch + 1, val);
	val = पढ़ोl(base + reg_ctrl);
	DRM_DEBUG_DRIVER("[rdma%d]: reg_ctrl(0x%08x)\n", ch + 1, val);
	val = पढ़ोl(base + reg_addr);
	DRM_DEBUG_DRIVER("[rdma%d]: reg_addr(0x%08x)\n", ch + 1, val);
	val = पढ़ोl(base + reg_size);
	DRM_DEBUG_DRIVER("[rdma%d]: reg_size(0x%08x)\n", ch + 1, val);
	val = पढ़ोl(base + reg_stride);
	DRM_DEBUG_DRIVER("[rdma%d]: reg_stride(0x%08x)\n", ch + 1, val);
	val = पढ़ोl(base + reg_space);
	DRM_DEBUG_DRIVER("[rdma%d]: reg_space(0x%08x)\n", ch + 1, val);
	val = पढ़ोl(base + reg_en);
	DRM_DEBUG_DRIVER("[rdma%d]: reg_en(0x%08x)\n", ch + 1, val);
पूर्ण

अटल व्योम ade_clip_dump_regs(व्योम __iomem *base, u32 ch)
अणु
	u32 val;

	val = ade_पढ़ो_reload_bit(base, CLIP_OFST + ch);
	DRM_DEBUG_DRIVER("[clip%d]: reload(%d)\n", ch + 1, val);
	val = पढ़ोl(base + ADE_CLIP_DISABLE(ch));
	DRM_DEBUG_DRIVER("[clip%d]: reg_clip_disable(0x%08x)\n", ch + 1, val);
	val = पढ़ोl(base + ADE_CLIP_SIZE0(ch));
	DRM_DEBUG_DRIVER("[clip%d]: reg_clip_size0(0x%08x)\n", ch + 1, val);
	val = पढ़ोl(base + ADE_CLIP_SIZE1(ch));
	DRM_DEBUG_DRIVER("[clip%d]: reg_clip_size1(0x%08x)\n", ch + 1, val);
पूर्ण

अटल व्योम ade_compositor_routing_dump_regs(व्योम __iomem *base, u32 ch)
अणु
	u8 ovly_ch = 0; /* TODO: Only primary plane now */
	u32 val;

	val = पढ़ोl(base + ADE_OVLY_CH_XY0(ovly_ch));
	DRM_DEBUG_DRIVER("[overlay ch%d]: reg_ch_xy0(0x%08x)\n", ovly_ch, val);
	val = पढ़ोl(base + ADE_OVLY_CH_XY1(ovly_ch));
	DRM_DEBUG_DRIVER("[overlay ch%d]: reg_ch_xy1(0x%08x)\n", ovly_ch, val);
	val = पढ़ोl(base + ADE_OVLY_CH_CTL(ovly_ch));
	DRM_DEBUG_DRIVER("[overlay ch%d]: reg_ch_ctl(0x%08x)\n", ovly_ch, val);
पूर्ण

अटल व्योम ade_dump_overlay_compositor_regs(व्योम __iomem *base, u32 comp)
अणु
	u32 val;

	val = ade_पढ़ो_reload_bit(base, OVLY_OFST + comp);
	DRM_DEBUG_DRIVER("[overlay%d]: reload(%d)\n", comp + 1, val);
	ग_लिखोl(ADE_ENABLE, base + ADE_OVLYX_CTL(comp));
	DRM_DEBUG_DRIVER("[overlay%d]: reg_ctl(0x%08x)\n", comp + 1, val);
	val = पढ़ोl(base + ADE_OVLY_CTL);
	DRM_DEBUG_DRIVER("ovly_ctl(0x%08x)\n", val);
पूर्ण

अटल व्योम ade_dump_regs(व्योम __iomem *base)
अणु
	u32 i;

	/* dump channel regs */
	क्रम (i = 0; i < ADE_CH_NUM; i++) अणु
		/* dump rdma regs */
		ade_rdma_dump_regs(base, i);

		/* dump clip regs */
		ade_clip_dump_regs(base, i);

		/* dump compositor routing regs */
		ade_compositor_routing_dump_regs(base, i);
	पूर्ण

	/* dump overlay compositor regs */
	ade_dump_overlay_compositor_regs(base, OUT_OVLY);
पूर्ण
#अन्यथा
अटल व्योम ade_dump_regs(व्योम __iomem *base) अणु पूर्ण
#पूर्ण_अगर

अटल व्योम ade_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				   काष्ठा drm_atomic_state *state)
अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;
	पूर्णांक ret;

	अगर (kcrtc->enable)
		वापस;

	अगर (!ctx->घातer_on) अणु
		ret = ade_घातer_up(ctx);
		अगर (ret)
			वापस;
	पूर्ण

	ade_set_medianoc_qos(ctx);
	ade_display_enable(ctx);
	ade_dump_regs(ctx->base);
	drm_crtc_vblank_on(crtc);
	kcrtc->enable = true;
पूर्ण

अटल व्योम ade_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;

	अगर (!kcrtc->enable)
		वापस;

	drm_crtc_vblank_off(crtc);
	ade_घातer_करोwn(ctx);
	kcrtc->enable = false;
पूर्ण

अटल व्योम ade_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;
	काष्ठा drm_display_mode *mode = &crtc->state->mode;
	काष्ठा drm_display_mode *adj_mode = &crtc->state->adjusted_mode;

	अगर (!ctx->घातer_on)
		(व्योम)ade_घातer_up(ctx);
	ade_ldi_set_mode(ctx, mode, adj_mode);
पूर्ण

अटल व्योम ade_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;
	काष्ठा drm_display_mode *mode = &crtc->state->mode;
	काष्ठा drm_display_mode *adj_mode = &crtc->state->adjusted_mode;

	अगर (!ctx->घातer_on)
		(व्योम)ade_घातer_up(ctx);
	ade_ldi_set_mode(ctx, mode, adj_mode);
पूर्ण

अटल व्योम ade_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				  काष्ठा drm_atomic_state *state)

अणु
	काष्ठा kirin_crtc *kcrtc = to_kirin_crtc(crtc);
	काष्ठा ade_hw_ctx *ctx = kcrtc->hw_ctx;
	काष्ठा drm_pending_vblank_event *event = crtc->state->event;
	व्योम __iomem *base = ctx->base;

	/* only crtc is enabled regs take effect */
	अगर (kcrtc->enable) अणु
		ade_dump_regs(base);
		/* flush ade रेजिस्टरs */
		ग_लिखोl(ADE_ENABLE, base + ADE_EN);
	पूर्ण

	अगर (event) अणु
		crtc->state->event = शून्य;

		spin_lock_irq(&crtc->dev->event_lock);
		अगर (drm_crtc_vblank_get(crtc) == 0)
			drm_crtc_arm_vblank_event(crtc, event);
		अन्यथा
			drm_crtc_send_vblank_event(crtc, event);
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_crtc_helper_funcs ade_crtc_helper_funcs = अणु
	.mode_fixup	= ade_crtc_mode_fixup,
	.mode_set_nofb	= ade_crtc_mode_set_nofb,
	.atomic_begin	= ade_crtc_atomic_begin,
	.atomic_flush	= ade_crtc_atomic_flush,
	.atomic_enable	= ade_crtc_atomic_enable,
	.atomic_disable	= ade_crtc_atomic_disable,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_funcs ade_crtc_funcs = अणु
	.destroy	= drm_crtc_cleanup,
	.set_config	= drm_atomic_helper_set_config,
	.page_flip	= drm_atomic_helper_page_flip,
	.reset		= drm_atomic_helper_crtc_reset,
	.atomic_duplicate_state	= drm_atomic_helper_crtc_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_crtc_destroy_state,
	.enable_vblank	= ade_crtc_enable_vblank,
	.disable_vblank	= ade_crtc_disable_vblank,
पूर्ण;

अटल व्योम ade_rdma_set(व्योम __iomem *base, काष्ठा drm_framebuffer *fb,
			 u32 ch, u32 y, u32 in_h, u32 fmt)
अणु
	काष्ठा drm_gem_cma_object *obj = drm_fb_cma_get_gem_obj(fb, 0);
	u32 reg_ctrl, reg_addr, reg_size, reg_stride, reg_space, reg_en;
	u32 stride = fb->pitches[0];
	u32 addr = (u32)obj->paddr + y * stride;

	DRM_DEBUG_DRIVER("rdma%d: (y=%d, height=%d), stride=%d, paddr=0x%x\n",
			 ch + 1, y, in_h, stride, (u32)obj->paddr);
	DRM_DEBUG_DRIVER("addr=0x%x, fb:%dx%d, pixel_format=%d(%p4cc)\n",
			 addr, fb->width, fb->height, fmt,
			 &fb->क्रमmat->क्रमmat);

	/* get reg offset */
	reg_ctrl = RD_CH_CTRL(ch);
	reg_addr = RD_CH_ADDR(ch);
	reg_size = RD_CH_SIZE(ch);
	reg_stride = RD_CH_STRIDE(ch);
	reg_space = RD_CH_SPACE(ch);
	reg_en = RD_CH_EN(ch);

	/*
	 * TODO: set rotation
	 */
	ग_लिखोl((fmt << 16) & 0x1f0000, base + reg_ctrl);
	ग_लिखोl(addr, base + reg_addr);
	ग_लिखोl((in_h << 16) | stride, base + reg_size);
	ग_लिखोl(stride, base + reg_stride);
	ग_लिखोl(in_h * stride, base + reg_space);
	ग_लिखोl(ADE_ENABLE, base + reg_en);
	ade_update_reload_bit(base, RDMA_OFST + ch, 0);
पूर्ण

अटल व्योम ade_rdma_disable(व्योम __iomem *base, u32 ch)
अणु
	u32 reg_en;

	/* get reg offset */
	reg_en = RD_CH_EN(ch);
	ग_लिखोl(0, base + reg_en);
	ade_update_reload_bit(base, RDMA_OFST + ch, 1);
पूर्ण

अटल व्योम ade_clip_set(व्योम __iomem *base, u32 ch, u32 fb_w, u32 x,
			 u32 in_w, u32 in_h)
अणु
	u32 disable_val;
	u32 clip_left;
	u32 clip_right;

	/*
	 * clip width, no need to clip height
	 */
	अगर (fb_w == in_w) अणु /* bypass */
		disable_val = 1;
		clip_left = 0;
		clip_right = 0;
	पूर्ण अन्यथा अणु
		disable_val = 0;
		clip_left = x;
		clip_right = fb_w - (x + in_w) - 1;
	पूर्ण

	DRM_DEBUG_DRIVER("clip%d: clip_left=%d, clip_right=%d\n",
			 ch + 1, clip_left, clip_right);

	ग_लिखोl(disable_val, base + ADE_CLIP_DISABLE(ch));
	ग_लिखोl((fb_w - 1) << 16 | (in_h - 1), base + ADE_CLIP_SIZE0(ch));
	ग_लिखोl(clip_left << 16 | clip_right, base + ADE_CLIP_SIZE1(ch));
	ade_update_reload_bit(base, CLIP_OFST + ch, 0);
पूर्ण

अटल व्योम ade_clip_disable(व्योम __iomem *base, u32 ch)
अणु
	ग_लिखोl(1, base + ADE_CLIP_DISABLE(ch));
	ade_update_reload_bit(base, CLIP_OFST + ch, 1);
पूर्ण

अटल bool has_Alpha_channel(पूर्णांक क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल ADE_ARGB_8888:
	हाल ADE_ABGR_8888:
	हाल ADE_RGBA_8888:
	हाल ADE_BGRA_8888:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम ade_get_blending_params(u32 fmt, u8 glb_alpha, u8 *alp_mode,
				    u8 *alp_sel, u8 *under_alp_sel)
अणु
	bool has_alpha = has_Alpha_channel(fmt);

	/*
	 * get alp_mode
	 */
	अगर (has_alpha && glb_alpha < 255)
		*alp_mode = ADE_ALP_PIXEL_AND_GLB;
	अन्यथा अगर (has_alpha)
		*alp_mode = ADE_ALP_PIXEL;
	अन्यथा
		*alp_mode = ADE_ALP_GLOBAL;

	/*
	 * get alp sel
	 */
	*alp_sel = ADE_ALP_MUL_COEFF_3; /* 1 */
	*under_alp_sel = ADE_ALP_MUL_COEFF_2; /* 0 */
पूर्ण

अटल व्योम ade_compositor_routing_set(व्योम __iomem *base, u8 ch,
				       u32 x0, u32 y0,
				       u32 in_w, u32 in_h, u32 fmt)
अणु
	u8 ovly_ch = 0; /* TODO: This is the zpos, only one plane now */
	u8 glb_alpha = 255;
	u32 x1 = x0 + in_w - 1;
	u32 y1 = y0 + in_h - 1;
	u32 val;
	u8 alp_sel;
	u8 under_alp_sel;
	u8 alp_mode;

	ade_get_blending_params(fmt, glb_alpha, &alp_mode, &alp_sel,
				&under_alp_sel);

	/* overlay routing setting
	 */
	ग_लिखोl(x0 << 16 | y0, base + ADE_OVLY_CH_XY0(ovly_ch));
	ग_लिखोl(x1 << 16 | y1, base + ADE_OVLY_CH_XY1(ovly_ch));
	val = (ch + 1) << CH_SEL_OFST | BIT(CH_EN_OFST) |
		alp_sel << CH_ALP_SEL_OFST |
		under_alp_sel << CH_UNDER_ALP_SEL_OFST |
		glb_alpha << CH_ALP_GBL_OFST |
		alp_mode << CH_ALP_MODE_OFST;
	ग_लिखोl(val, base + ADE_OVLY_CH_CTL(ovly_ch));
	/* connect this plane/channel to overlay2 compositor */
	ade_update_bits(base + ADE_OVLY_CTL, CH_OVLY_SEL_OFST(ovly_ch),
			CH_OVLY_SEL_MASK, CH_OVLY_SEL_VAL(OUT_OVLY));
पूर्ण

अटल व्योम ade_compositor_routing_disable(व्योम __iomem *base, u32 ch)
अणु
	u8 ovly_ch = 0; /* TODO: Only primary plane now */

	/* disable this plane/channel */
	ade_update_bits(base + ADE_OVLY_CH_CTL(ovly_ch), CH_EN_OFST,
			MASK(1), 0);
	/* dis-connect this plane/channel of overlay2 compositor */
	ade_update_bits(base + ADE_OVLY_CTL, CH_OVLY_SEL_OFST(ovly_ch),
			CH_OVLY_SEL_MASK, 0);
पूर्ण

/*
 * Typicaly, a channel looks like: DMA-->clip-->scale-->ctrans-->compositor
 */
अटल व्योम ade_update_channel(काष्ठा kirin_plane *kplane,
			       काष्ठा drm_framebuffer *fb, पूर्णांक crtc_x,
			       पूर्णांक crtc_y, अचिन्हित पूर्णांक crtc_w,
			       अचिन्हित पूर्णांक crtc_h, u32 src_x,
			       u32 src_y, u32 src_w, u32 src_h)
अणु
	काष्ठा ade_hw_ctx *ctx = kplane->hw_ctx;
	व्योम __iomem *base = ctx->base;
	u32 fmt = ade_get_क्रमmat(fb->क्रमmat->क्रमmat);
	u32 ch = kplane->ch;
	u32 in_w;
	u32 in_h;

	DRM_DEBUG_DRIVER("channel%d: src:(%d, %d)-%dx%d, crtc:(%d, %d)-%dx%d",
			 ch + 1, src_x, src_y, src_w, src_h,
			 crtc_x, crtc_y, crtc_w, crtc_h);

	/* 1) DMA setting */
	in_w = src_w;
	in_h = src_h;
	ade_rdma_set(base, fb, ch, src_y, in_h, fmt);

	/* 2) clip setting */
	ade_clip_set(base, ch, fb->width, src_x, in_w, in_h);

	/* 3) TODO: scale setting क्रम overlay planes */

	/* 4) TODO: ctran/csc setting क्रम overlay planes */

	/* 5) compositor routing setting */
	ade_compositor_routing_set(base, ch, crtc_x, crtc_y, in_w, in_h, fmt);
पूर्ण

अटल व्योम ade_disable_channel(काष्ठा kirin_plane *kplane)
अणु
	काष्ठा ade_hw_ctx *ctx = kplane->hw_ctx;
	व्योम __iomem *base = ctx->base;
	u32 ch = kplane->ch;

	DRM_DEBUG_DRIVER("disable channel%d\n", ch + 1);

	/* disable पढ़ो DMA */
	ade_rdma_disable(base, ch);

	/* disable clip */
	ade_clip_disable(base, ch);

	/* disable compositor routing */
	ade_compositor_routing_disable(base, ch);
पूर्ण

अटल पूर्णांक ade_plane_atomic_check(काष्ठा drm_plane *plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 plane);
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_crtc_state *crtc_state;
	u32 src_x = new_plane_state->src_x >> 16;
	u32 src_y = new_plane_state->src_y >> 16;
	u32 src_w = new_plane_state->src_w >> 16;
	u32 src_h = new_plane_state->src_h >> 16;
	पूर्णांक crtc_x = new_plane_state->crtc_x;
	पूर्णांक crtc_y = new_plane_state->crtc_y;
	u32 crtc_w = new_plane_state->crtc_w;
	u32 crtc_h = new_plane_state->crtc_h;
	u32 fmt;

	अगर (!crtc || !fb)
		वापस 0;

	fmt = ade_get_क्रमmat(fb->क्रमmat->क्रमmat);
	अगर (fmt == ADE_FORMAT_UNSUPPORT)
		वापस -EINVAL;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	अगर (IS_ERR(crtc_state))
		वापस PTR_ERR(crtc_state);

	अगर (src_w != crtc_w || src_h != crtc_h) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (src_x + src_w > fb->width ||
	    src_y + src_h > fb->height)
		वापस -EINVAL;

	अगर (crtc_x < 0 || crtc_y < 0)
		वापस -EINVAL;

	अगर (crtc_x + crtc_w > crtc_state->adjusted_mode.hdisplay ||
	    crtc_y + crtc_h > crtc_state->adjusted_mode.vdisplay)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम ade_plane_atomic_update(काष्ठा drm_plane *plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_state = drm_atomic_get_new_plane_state(state,
									   plane);
	काष्ठा kirin_plane *kplane = to_kirin_plane(plane);

	ade_update_channel(kplane, new_state->fb, new_state->crtc_x,
			   new_state->crtc_y,
			   new_state->crtc_w, new_state->crtc_h,
			   new_state->src_x >> 16, new_state->src_y >> 16,
			   new_state->src_w >> 16, new_state->src_h >> 16);
पूर्ण

अटल व्योम ade_plane_atomic_disable(काष्ठा drm_plane *plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा kirin_plane *kplane = to_kirin_plane(plane);

	ade_disable_channel(kplane);
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs ade_plane_helper_funcs = अणु
	.atomic_check = ade_plane_atomic_check,
	.atomic_update = ade_plane_atomic_update,
	.atomic_disable = ade_plane_atomic_disable,
पूर्ण;

अटल काष्ठा drm_plane_funcs ade_plane_funcs = अणु
	.update_plane	= drm_atomic_helper_update_plane,
	.disable_plane	= drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = drm_atomic_helper_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
पूर्ण;

अटल व्योम *ade_hw_ctx_alloc(काष्ठा platक्रमm_device *pdev,
			      काष्ठा drm_crtc *crtc)
अणु
	काष्ठा resource *res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा ade_hw_ctx *ctx = शून्य;
	पूर्णांक ret;

	ctx = devm_kzalloc(dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		DRM_ERROR("failed to alloc ade_hw_ctx\n");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(ctx->base)) अणु
		DRM_ERROR("failed to remap ade io base\n");
		वापस ERR_PTR(-EIO);
	पूर्ण

	ctx->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(ctx->reset))
		वापस ERR_PTR(-ENODEV);

	ctx->noc_regmap =
		syscon_regmap_lookup_by_phandle(np, "hisilicon,noc-syscon");
	अगर (IS_ERR(ctx->noc_regmap)) अणु
		DRM_ERROR("failed to get noc regmap\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ctx->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ctx->irq < 0) अणु
		DRM_ERROR("failed to get irq\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ctx->ade_core_clk = devm_clk_get(dev, "clk_ade_core");
	अगर (IS_ERR(ctx->ade_core_clk)) अणु
		DRM_ERROR("failed to parse clk ADE_CORE\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ctx->media_noc_clk = devm_clk_get(dev, "clk_codec_jpeg");
	अगर (IS_ERR(ctx->media_noc_clk)) अणु
		DRM_ERROR("failed to parse clk CODEC_JPEG\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	ctx->ade_pix_clk = devm_clk_get(dev, "clk_ade_pix");
	अगर (IS_ERR(ctx->ade_pix_clk)) अणु
		DRM_ERROR("failed to parse clk ADE_PIX\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/* vblank irq init */
	ret = devm_request_irq(dev, ctx->irq, ade_irq_handler,
			       IRQF_SHARED, dev->driver->name, ctx);
	अगर (ret)
		वापस ERR_PTR(-EIO);

	ctx->crtc = crtc;

	वापस ctx;
पूर्ण

अटल व्योम ade_hw_ctx_cleanup(व्योम *hw_ctx)
अणु
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs ade_mode_config_funcs = अणु
	.fb_create = drm_gem_fb_create,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,

पूर्ण;

DEFINE_DRM_GEM_CMA_FOPS(ade_fops);

अटल स्थिर काष्ठा drm_driver ade_driver = अणु
	.driver_features = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.fops = &ade_fops,
	DRM_GEM_CMA_DRIVER_OPS,
	.name = "kirin",
	.desc = "Hisilicon Kirin620 SoC DRM Driver",
	.date = "20150718",
	.major = 1,
	.minor = 0,
पूर्ण;

काष्ठा kirin_drm_data ade_driver_data = अणु
	.num_planes = ADE_CH_NUM,
	.prim_plane = ADE_CH1,
	.channel_क्रमmats = channel_क्रमmats,
	.channel_क्रमmats_cnt = ARRAY_SIZE(channel_क्रमmats),
	.config_max_width = 2048,
	.config_max_height = 2048,
	.driver = &ade_driver,
	.crtc_helper_funcs = &ade_crtc_helper_funcs,
	.crtc_funcs = &ade_crtc_funcs,
	.plane_helper_funcs = &ade_plane_helper_funcs,
	.plane_funcs = &ade_plane_funcs,
	.mode_config_funcs = &ade_mode_config_funcs,

	.alloc_hw_ctx = ade_hw_ctx_alloc,
	.cleanup_hw_ctx = ade_hw_ctx_cleanup,
पूर्ण;
