<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2011 Samsung Electronics Co.Ltd
 * Authors:
 * Seung-Woo Kim <sw0312.kim@samsung.com>
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *
 * Based on drivers/media/video/s5p-tv/mixer_reg.c
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_vblank.h>
#समावेश <drm/exynos_drm.h>

#समावेश "exynos_drm_crtc.h"
#समावेश "exynos_drm_drv.h"
#समावेश "exynos_drm_fb.h"
#समावेश "exynos_drm_plane.h"
#समावेश "regs-mixer.h"
#समावेश "regs-vp.h"

#घोषणा MIXER_WIN_NR		3
#घोषणा VP_DEFAULT_WIN		2

/*
 * Mixer color space conversion coefficient triplet.
 * Used क्रम CSC from RGB to YCbCr.
 * Each coefficient is a 10-bit fixed poपूर्णांक number with
 * sign and no पूर्णांकeger part, i.e.
 * [0:8] = fractional part (representing a value y = x / 2^9)
 * [9] = sign
 * Negative values are encoded with two's complement.
 */
#घोषणा MXR_CSC_C(x) ((पूर्णांक)((x) * 512.0) & 0x3ff)
#घोषणा MXR_CSC_CT(a0, a1, a2) \
  ((MXR_CSC_C(a0) << 20) | (MXR_CSC_C(a1) << 10) | (MXR_CSC_C(a2) << 0))

/* YCbCr value, used क्रम mixer background color configuration. */
#घोषणा MXR_YCBCR_VAL(y, cb, cr) (((y) << 16) | ((cb) << 8) | ((cr) << 0))

/* The pixelक्रमmats that are natively supported by the mixer. */
#घोषणा MXR_FORMAT_RGB565	4
#घोषणा MXR_FORMAT_ARGB1555	5
#घोषणा MXR_FORMAT_ARGB4444	6
#घोषणा MXR_FORMAT_ARGB8888	7

क्रमागत mixer_version_id अणु
	MXR_VER_0_0_0_16,
	MXR_VER_16_0_33_0,
	MXR_VER_128_0_0_184,
पूर्ण;

क्रमागत mixer_flag_bits अणु
	MXR_BIT_POWERED,
	MXR_BIT_VSYNC,
	MXR_BIT_INTERLACE,
	MXR_BIT_VP_ENABLED,
	MXR_BIT_HAS_SCLK,
पूर्ण;

अटल स्थिर uपूर्णांक32_t mixer_क्रमmats[] = अणु
	DRM_FORMAT_XRGB4444,
	DRM_FORMAT_ARGB4444,
	DRM_FORMAT_XRGB1555,
	DRM_FORMAT_ARGB1555,
	DRM_FORMAT_RGB565,
	DRM_FORMAT_XRGB8888,
	DRM_FORMAT_ARGB8888,
पूर्ण;

अटल स्थिर uपूर्णांक32_t vp_क्रमmats[] = अणु
	DRM_FORMAT_NV12,
	DRM_FORMAT_NV21,
पूर्ण;

काष्ठा mixer_context अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा device		*dev;
	काष्ठा drm_device	*drm_dev;
	व्योम			*dma_priv;
	काष्ठा exynos_drm_crtc	*crtc;
	काष्ठा exynos_drm_plane	planes[MIXER_WIN_NR];
	अचिन्हित दीर्घ		flags;

	पूर्णांक			irq;
	व्योम __iomem		*mixer_regs;
	व्योम __iomem		*vp_regs;
	spinlock_t		reg_slock;
	काष्ठा clk		*mixer;
	काष्ठा clk		*vp;
	काष्ठा clk		*hdmi;
	काष्ठा clk		*sclk_mixer;
	काष्ठा clk		*sclk_hdmi;
	काष्ठा clk		*mout_mixer;
	क्रमागत mixer_version_id	mxr_ver;
	पूर्णांक			scan_value;
पूर्ण;

काष्ठा mixer_drv_data अणु
	क्रमागत mixer_version_id	version;
	bool					is_vp_enabled;
	bool					has_sclk;
पूर्ण;

अटल स्थिर काष्ठा exynos_drm_plane_config plane_configs[MIXER_WIN_NR] = अणु
	अणु
		.zpos = 0,
		.type = DRM_PLANE_TYPE_PRIMARY,
		.pixel_क्रमmats = mixer_क्रमmats,
		.num_pixel_क्रमmats = ARRAY_SIZE(mixer_क्रमmats),
		.capabilities = EXYNOS_DRM_PLANE_CAP_DOUBLE |
				EXYNOS_DRM_PLANE_CAP_ZPOS |
				EXYNOS_DRM_PLANE_CAP_PIX_BLEND |
				EXYNOS_DRM_PLANE_CAP_WIN_BLEND,
	पूर्ण, अणु
		.zpos = 1,
		.type = DRM_PLANE_TYPE_CURSOR,
		.pixel_क्रमmats = mixer_क्रमmats,
		.num_pixel_क्रमmats = ARRAY_SIZE(mixer_क्रमmats),
		.capabilities = EXYNOS_DRM_PLANE_CAP_DOUBLE |
				EXYNOS_DRM_PLANE_CAP_ZPOS |
				EXYNOS_DRM_PLANE_CAP_PIX_BLEND |
				EXYNOS_DRM_PLANE_CAP_WIN_BLEND,
	पूर्ण, अणु
		.zpos = 2,
		.type = DRM_PLANE_TYPE_OVERLAY,
		.pixel_क्रमmats = vp_क्रमmats,
		.num_pixel_क्रमmats = ARRAY_SIZE(vp_क्रमmats),
		.capabilities = EXYNOS_DRM_PLANE_CAP_SCALE |
				EXYNOS_DRM_PLANE_CAP_ZPOS |
				EXYNOS_DRM_PLANE_CAP_TILE |
				EXYNOS_DRM_PLANE_CAP_WIN_BLEND,
	पूर्ण,
पूर्ण;

अटल स्थिर u8 filter_y_horiz_tap8[] = अणु
	0,	-1,	-1,	-1,	-1,	-1,	-1,	-1,
	-1,	-1,	-1,	-1,	-1,	0,	0,	0,
	0,	2,	4,	5,	6,	6,	6,	6,
	6,	5,	5,	4,	3,	2,	1,	1,
	0,	-6,	-12,	-16,	-18,	-20,	-21,	-20,
	-20,	-18,	-16,	-13,	-10,	-8,	-5,	-2,
	127,	126,	125,	121,	114,	107,	99,	89,
	79,	68,	57,	46,	35,	25,	16,	8,
पूर्ण;

अटल स्थिर u8 filter_y_vert_tap4[] = अणु
	0,	-3,	-6,	-8,	-8,	-8,	-8,	-7,
	-6,	-5,	-4,	-3,	-2,	-1,	-1,	0,
	127,	126,	124,	118,	111,	102,	92,	81,
	70,	59,	48,	37,	27,	19,	11,	5,
	0,	5,	11,	19,	27,	37,	48,	59,
	70,	81,	92,	102,	111,	118,	124,	126,
	0,	0,	-1,	-1,	-2,	-3,	-4,	-5,
	-6,	-7,	-8,	-8,	-8,	-8,	-6,	-3,
पूर्ण;

अटल स्थिर u8 filter_cr_horiz_tap4[] = अणु
	0,	-3,	-6,	-8,	-8,	-8,	-8,	-7,
	-6,	-5,	-4,	-3,	-2,	-1,	-1,	0,
	127,	126,	124,	118,	111,	102,	92,	81,
	70,	59,	48,	37,	27,	19,	11,	5,
पूर्ण;

अटल अंतरभूत u32 vp_reg_पढ़ो(काष्ठा mixer_context *ctx, u32 reg_id)
अणु
	वापस पढ़ोl(ctx->vp_regs + reg_id);
पूर्ण

अटल अंतरभूत व्योम vp_reg_ग_लिखो(काष्ठा mixer_context *ctx, u32 reg_id,
				 u32 val)
अणु
	ग_लिखोl(val, ctx->vp_regs + reg_id);
पूर्ण

अटल अंतरभूत व्योम vp_reg_ग_लिखोmask(काष्ठा mixer_context *ctx, u32 reg_id,
				 u32 val, u32 mask)
अणु
	u32 old = vp_reg_पढ़ो(ctx, reg_id);

	val = (val & mask) | (old & ~mask);
	ग_लिखोl(val, ctx->vp_regs + reg_id);
पूर्ण

अटल अंतरभूत u32 mixer_reg_पढ़ो(काष्ठा mixer_context *ctx, u32 reg_id)
अणु
	वापस पढ़ोl(ctx->mixer_regs + reg_id);
पूर्ण

अटल अंतरभूत व्योम mixer_reg_ग_लिखो(काष्ठा mixer_context *ctx, u32 reg_id,
				 u32 val)
अणु
	ग_लिखोl(val, ctx->mixer_regs + reg_id);
पूर्ण

अटल अंतरभूत व्योम mixer_reg_ग_लिखोmask(काष्ठा mixer_context *ctx,
				 u32 reg_id, u32 val, u32 mask)
अणु
	u32 old = mixer_reg_पढ़ो(ctx, reg_id);

	val = (val & mask) | (old & ~mask);
	ग_लिखोl(val, ctx->mixer_regs + reg_id);
पूर्ण

अटल व्योम mixer_regs_dump(काष्ठा mixer_context *ctx)
अणु
#घोषणा DUMPREG(reg_id) \
करो अणु \
	DRM_DEV_DEBUG_KMS(ctx->dev, #reg_id " = %08x\n", \
			 (u32)पढ़ोl(ctx->mixer_regs + reg_id)); \
पूर्ण जबतक (0)

	DUMPREG(MXR_STATUS);
	DUMPREG(MXR_CFG);
	DUMPREG(MXR_INT_EN);
	DUMPREG(MXR_INT_STATUS);

	DUMPREG(MXR_LAYER_CFG);
	DUMPREG(MXR_VIDEO_CFG);

	DUMPREG(MXR_GRAPHIC0_CFG);
	DUMPREG(MXR_GRAPHIC0_BASE);
	DUMPREG(MXR_GRAPHIC0_SPAN);
	DUMPREG(MXR_GRAPHIC0_WH);
	DUMPREG(MXR_GRAPHIC0_SXY);
	DUMPREG(MXR_GRAPHIC0_DXY);

	DUMPREG(MXR_GRAPHIC1_CFG);
	DUMPREG(MXR_GRAPHIC1_BASE);
	DUMPREG(MXR_GRAPHIC1_SPAN);
	DUMPREG(MXR_GRAPHIC1_WH);
	DUMPREG(MXR_GRAPHIC1_SXY);
	DUMPREG(MXR_GRAPHIC1_DXY);
#अघोषित DUMPREG
पूर्ण

अटल व्योम vp_regs_dump(काष्ठा mixer_context *ctx)
अणु
#घोषणा DUMPREG(reg_id) \
करो अणु \
	DRM_DEV_DEBUG_KMS(ctx->dev, #reg_id " = %08x\n", \
			 (u32) पढ़ोl(ctx->vp_regs + reg_id)); \
पूर्ण जबतक (0)

	DUMPREG(VP_ENABLE);
	DUMPREG(VP_SRESET);
	DUMPREG(VP_SHADOW_UPDATE);
	DUMPREG(VP_FIELD_ID);
	DUMPREG(VP_MODE);
	DUMPREG(VP_IMG_SIZE_Y);
	DUMPREG(VP_IMG_SIZE_C);
	DUMPREG(VP_PER_RATE_CTRL);
	DUMPREG(VP_TOP_Y_PTR);
	DUMPREG(VP_BOT_Y_PTR);
	DUMPREG(VP_TOP_C_PTR);
	DUMPREG(VP_BOT_C_PTR);
	DUMPREG(VP_ENDIAN_MODE);
	DUMPREG(VP_SRC_H_POSITION);
	DUMPREG(VP_SRC_V_POSITION);
	DUMPREG(VP_SRC_WIDTH);
	DUMPREG(VP_SRC_HEIGHT);
	DUMPREG(VP_DST_H_POSITION);
	DUMPREG(VP_DST_V_POSITION);
	DUMPREG(VP_DST_WIDTH);
	DUMPREG(VP_DST_HEIGHT);
	DUMPREG(VP_H_RATIO);
	DUMPREG(VP_V_RATIO);

#अघोषित DUMPREG
पूर्ण

अटल अंतरभूत व्योम vp_filter_set(काष्ठा mixer_context *ctx,
		पूर्णांक reg_id, स्थिर u8 *data, अचिन्हित पूर्णांक size)
अणु
	/* assure 4-byte align */
	BUG_ON(size & 3);
	क्रम (; size; size -= 4, reg_id += 4, data += 4) अणु
		u32 val = (data[0] << 24) |  (data[1] << 16) |
			(data[2] << 8) | data[3];
		vp_reg_ग_लिखो(ctx, reg_id, val);
	पूर्ण
पूर्ण

अटल व्योम vp_शेष_filter(काष्ठा mixer_context *ctx)
अणु
	vp_filter_set(ctx, VP_POLY8_Y0_LL,
		filter_y_horiz_tap8, माप(filter_y_horiz_tap8));
	vp_filter_set(ctx, VP_POLY4_Y0_LL,
		filter_y_vert_tap4, माप(filter_y_vert_tap4));
	vp_filter_set(ctx, VP_POLY4_C0_LL,
		filter_cr_horiz_tap4, माप(filter_cr_horiz_tap4));
पूर्ण

अटल व्योम mixer_cfg_gfx_blend(काष्ठा mixer_context *ctx, अचिन्हित पूर्णांक win,
				अचिन्हित पूर्णांक pixel_alpha, अचिन्हित पूर्णांक alpha)
अणु
	u32 win_alpha = alpha >> 8;
	u32 val;

	val  = MXR_GRP_CFG_COLOR_KEY_DISABLE; /* no blank key */
	चयन (pixel_alpha) अणु
	हाल DRM_MODE_BLEND_PIXEL_NONE:
		अवरोध;
	हाल DRM_MODE_BLEND_COVERAGE:
		val |= MXR_GRP_CFG_PIXEL_BLEND_EN;
		अवरोध;
	हाल DRM_MODE_BLEND_PREMULTI:
	शेष:
		val |= MXR_GRP_CFG_BLEND_PRE_MUL;
		val |= MXR_GRP_CFG_PIXEL_BLEND_EN;
		अवरोध;
	पूर्ण

	अगर (alpha != DRM_BLEND_ALPHA_OPAQUE) अणु
		val |= MXR_GRP_CFG_WIN_BLEND_EN;
		val |= win_alpha;
	पूर्ण
	mixer_reg_ग_लिखोmask(ctx, MXR_GRAPHIC_CFG(win),
			    val, MXR_GRP_CFG_MISC_MASK);
पूर्ण

अटल व्योम mixer_cfg_vp_blend(काष्ठा mixer_context *ctx, अचिन्हित पूर्णांक alpha)
अणु
	u32 win_alpha = alpha >> 8;
	u32 val = 0;

	अगर (alpha != DRM_BLEND_ALPHA_OPAQUE) अणु
		val |= MXR_VID_CFG_BLEND_EN;
		val |= win_alpha;
	पूर्ण
	mixer_reg_ग_लिखो(ctx, MXR_VIDEO_CFG, val);
पूर्ण

अटल bool mixer_is_synced(काष्ठा mixer_context *ctx)
अणु
	u32 base, shaकरोw;

	अगर (ctx->mxr_ver == MXR_VER_16_0_33_0 ||
	    ctx->mxr_ver == MXR_VER_128_0_0_184)
		वापस !(mixer_reg_पढ़ो(ctx, MXR_CFG) &
			 MXR_CFG_LAYER_UPDATE_COUNT_MASK);

	अगर (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags) &&
	    vp_reg_पढ़ो(ctx, VP_SHADOW_UPDATE))
		वापस false;

	base = mixer_reg_पढ़ो(ctx, MXR_CFG);
	shaकरोw = mixer_reg_पढ़ो(ctx, MXR_CFG_S);
	अगर (base != shaकरोw)
		वापस false;

	base = mixer_reg_पढ़ो(ctx, MXR_GRAPHIC_BASE(0));
	shaकरोw = mixer_reg_पढ़ो(ctx, MXR_GRAPHIC_BASE_S(0));
	अगर (base != shaकरोw)
		वापस false;

	base = mixer_reg_पढ़ो(ctx, MXR_GRAPHIC_BASE(1));
	shaकरोw = mixer_reg_पढ़ो(ctx, MXR_GRAPHIC_BASE_S(1));
	अगर (base != shaकरोw)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक mixer_रुको_क्रम_sync(काष्ठा mixer_context *ctx)
अणु
	kसमय_प्रकार समयout = kसमय_add_us(kसमय_get(), 100000);

	जबतक (!mixer_is_synced(ctx)) अणु
		usleep_range(1000, 2000);
		अगर (kसमय_compare(kसमय_get(), समयout) > 0)
			वापस -ETIMEDOUT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम mixer_disable_sync(काष्ठा mixer_context *ctx)
अणु
	mixer_reg_ग_लिखोmask(ctx, MXR_STATUS, 0, MXR_STATUS_SYNC_ENABLE);
पूर्ण

अटल व्योम mixer_enable_sync(काष्ठा mixer_context *ctx)
अणु
	अगर (ctx->mxr_ver == MXR_VER_16_0_33_0 ||
	    ctx->mxr_ver == MXR_VER_128_0_0_184)
		mixer_reg_ग_लिखोmask(ctx, MXR_CFG, ~0, MXR_CFG_LAYER_UPDATE);
	mixer_reg_ग_लिखोmask(ctx, MXR_STATUS, ~0, MXR_STATUS_SYNC_ENABLE);
	अगर (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags))
		vp_reg_ग_लिखो(ctx, VP_SHADOW_UPDATE, VP_SHADOW_UPDATE_ENABLE);
पूर्ण

अटल व्योम mixer_cfg_scan(काष्ठा mixer_context *ctx, पूर्णांक width, पूर्णांक height)
अणु
	u32 val;

	/* choosing between पूर्णांकerlace and progressive mode */
	val = test_bit(MXR_BIT_INTERLACE, &ctx->flags) ?
		MXR_CFG_SCAN_INTERLACE : MXR_CFG_SCAN_PROGRESSIVE;

	अगर (ctx->mxr_ver == MXR_VER_128_0_0_184)
		mixer_reg_ग_लिखो(ctx, MXR_RESOLUTION,
			MXR_MXR_RES_HEIGHT(height) | MXR_MXR_RES_WIDTH(width));
	अन्यथा
		val |= ctx->scan_value;

	mixer_reg_ग_लिखोmask(ctx, MXR_CFG, val, MXR_CFG_SCAN_MASK);
पूर्ण

अटल व्योम mixer_cfg_rgb_fmt(काष्ठा mixer_context *ctx, काष्ठा drm_display_mode *mode)
अणु
	क्रमागत hdmi_quantization_range range = drm_शेष_rgb_quant_range(mode);
	u32 val;

	अगर (mode->vdisplay < 720) अणु
		val = MXR_CFG_RGB601;
	पूर्ण अन्यथा अणु
		val = MXR_CFG_RGB709;

		/* Configure the BT.709 CSC matrix क्रम full range RGB. */
		mixer_reg_ग_लिखो(ctx, MXR_CM_COEFF_Y,
			MXR_CSC_CT( 0.184,  0.614,  0.063) |
			MXR_CM_COEFF_RGB_FULL);
		mixer_reg_ग_लिखो(ctx, MXR_CM_COEFF_CB,
			MXR_CSC_CT(-0.102, -0.338,  0.440));
		mixer_reg_ग_लिखो(ctx, MXR_CM_COEFF_CR,
			MXR_CSC_CT( 0.440, -0.399, -0.040));
	पूर्ण

	अगर (range == HDMI_QUANTIZATION_RANGE_FULL)
		val |= MXR_CFG_QUANT_RANGE_FULL;
	अन्यथा
		val |= MXR_CFG_QUANT_RANGE_LIMITED;

	mixer_reg_ग_लिखोmask(ctx, MXR_CFG, val, MXR_CFG_RGB_FMT_MASK);
पूर्ण

अटल व्योम mixer_cfg_layer(काष्ठा mixer_context *ctx, अचिन्हित पूर्णांक win,
			    अचिन्हित पूर्णांक priority, bool enable)
अणु
	u32 val = enable ? ~0 : 0;

	चयन (win) अणु
	हाल 0:
		mixer_reg_ग_लिखोmask(ctx, MXR_CFG, val, MXR_CFG_GRP0_ENABLE);
		mixer_reg_ग_लिखोmask(ctx, MXR_LAYER_CFG,
				    MXR_LAYER_CFG_GRP0_VAL(priority),
				    MXR_LAYER_CFG_GRP0_MASK);
		अवरोध;
	हाल 1:
		mixer_reg_ग_लिखोmask(ctx, MXR_CFG, val, MXR_CFG_GRP1_ENABLE);
		mixer_reg_ग_लिखोmask(ctx, MXR_LAYER_CFG,
				    MXR_LAYER_CFG_GRP1_VAL(priority),
				    MXR_LAYER_CFG_GRP1_MASK);

		अवरोध;
	हाल VP_DEFAULT_WIN:
		अगर (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags)) अणु
			vp_reg_ग_लिखोmask(ctx, VP_ENABLE, val, VP_ENABLE_ON);
			mixer_reg_ग_लिखोmask(ctx, MXR_CFG, val,
				MXR_CFG_VP_ENABLE);
			mixer_reg_ग_लिखोmask(ctx, MXR_LAYER_CFG,
					    MXR_LAYER_CFG_VP_VAL(priority),
					    MXR_LAYER_CFG_VP_MASK);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mixer_run(काष्ठा mixer_context *ctx)
अणु
	mixer_reg_ग_लिखोmask(ctx, MXR_STATUS, ~0, MXR_STATUS_REG_RUN);
पूर्ण

अटल व्योम mixer_stop(काष्ठा mixer_context *ctx)
अणु
	पूर्णांक समयout = 20;

	mixer_reg_ग_लिखोmask(ctx, MXR_STATUS, 0, MXR_STATUS_REG_RUN);

	जबतक (!(mixer_reg_पढ़ो(ctx, MXR_STATUS) & MXR_STATUS_REG_IDLE) &&
			--समयout)
		usleep_range(10000, 12000);
पूर्ण

अटल व्योम mixer_commit(काष्ठा mixer_context *ctx)
अणु
	काष्ठा drm_display_mode *mode = &ctx->crtc->base.state->adjusted_mode;

	mixer_cfg_scan(ctx, mode->hdisplay, mode->vdisplay);
	mixer_cfg_rgb_fmt(ctx, mode);
	mixer_run(ctx);
पूर्ण

अटल व्योम vp_video_buffer(काष्ठा mixer_context *ctx,
			    काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	काष्ठा drm_framebuffer *fb = state->base.fb;
	अचिन्हित पूर्णांक priority = state->base.normalized_zpos + 1;
	अचिन्हित दीर्घ flags;
	dma_addr_t luma_addr[2], chroma_addr[2];
	bool is_tiled, is_nv21;
	u32 val;

	is_nv21 = (fb->क्रमmat->क्रमmat == DRM_FORMAT_NV21);
	is_tiled = (fb->modअगरier == DRM_FORMAT_MOD_SAMSUNG_64_32_TILE);

	luma_addr[0] = exynos_drm_fb_dma_addr(fb, 0);
	chroma_addr[0] = exynos_drm_fb_dma_addr(fb, 1);

	अगर (test_bit(MXR_BIT_INTERLACE, &ctx->flags)) अणु
		अगर (is_tiled) अणु
			luma_addr[1] = luma_addr[0] + 0x40;
			chroma_addr[1] = chroma_addr[0] + 0x40;
		पूर्ण अन्यथा अणु
			luma_addr[1] = luma_addr[0] + fb->pitches[0];
			chroma_addr[1] = chroma_addr[0] + fb->pitches[1];
		पूर्ण
	पूर्ण अन्यथा अणु
		luma_addr[1] = 0;
		chroma_addr[1] = 0;
	पूर्ण

	spin_lock_irqsave(&ctx->reg_slock, flags);

	/* पूर्णांकerlace or progressive scan mode */
	val = (test_bit(MXR_BIT_INTERLACE, &ctx->flags) ? ~0 : 0);
	vp_reg_ग_लिखोmask(ctx, VP_MODE, val, VP_MODE_LINE_SKIP);

	/* setup क्रमmat */
	val = (is_nv21 ? VP_MODE_NV21 : VP_MODE_NV12);
	val |= (is_tiled ? VP_MODE_MEM_TILED : VP_MODE_MEM_LINEAR);
	vp_reg_ग_लिखोmask(ctx, VP_MODE, val, VP_MODE_FMT_MASK);

	/* setting size of input image */
	vp_reg_ग_लिखो(ctx, VP_IMG_SIZE_Y, VP_IMG_HSIZE(fb->pitches[0]) |
		VP_IMG_VSIZE(fb->height));
	/* chroma plane क्रम NV12/NV21 is half the height of the luma plane */
	vp_reg_ग_लिखो(ctx, VP_IMG_SIZE_C, VP_IMG_HSIZE(fb->pitches[1]) |
		VP_IMG_VSIZE(fb->height / 2));

	vp_reg_ग_लिखो(ctx, VP_SRC_WIDTH, state->src.w);
	vp_reg_ग_लिखो(ctx, VP_SRC_H_POSITION,
			VP_SRC_H_POSITION_VAL(state->src.x));
	vp_reg_ग_लिखो(ctx, VP_DST_WIDTH, state->crtc.w);
	vp_reg_ग_लिखो(ctx, VP_DST_H_POSITION, state->crtc.x);

	अगर (test_bit(MXR_BIT_INTERLACE, &ctx->flags)) अणु
		vp_reg_ग_लिखो(ctx, VP_SRC_HEIGHT, state->src.h / 2);
		vp_reg_ग_लिखो(ctx, VP_SRC_V_POSITION, state->src.y / 2);
		vp_reg_ग_लिखो(ctx, VP_DST_HEIGHT, state->crtc.h / 2);
		vp_reg_ग_लिखो(ctx, VP_DST_V_POSITION, state->crtc.y / 2);
	पूर्ण अन्यथा अणु
		vp_reg_ग_लिखो(ctx, VP_SRC_HEIGHT, state->src.h);
		vp_reg_ग_लिखो(ctx, VP_SRC_V_POSITION, state->src.y);
		vp_reg_ग_लिखो(ctx, VP_DST_HEIGHT, state->crtc.h);
		vp_reg_ग_लिखो(ctx, VP_DST_V_POSITION, state->crtc.y);
	पूर्ण

	vp_reg_ग_लिखो(ctx, VP_H_RATIO, state->h_ratio);
	vp_reg_ग_लिखो(ctx, VP_V_RATIO, state->v_ratio);

	vp_reg_ग_लिखो(ctx, VP_ENDIAN_MODE, VP_ENDIAN_MODE_LITTLE);

	/* set buffer address to vp */
	vp_reg_ग_लिखो(ctx, VP_TOP_Y_PTR, luma_addr[0]);
	vp_reg_ग_लिखो(ctx, VP_BOT_Y_PTR, luma_addr[1]);
	vp_reg_ग_लिखो(ctx, VP_TOP_C_PTR, chroma_addr[0]);
	vp_reg_ग_लिखो(ctx, VP_BOT_C_PTR, chroma_addr[1]);

	mixer_cfg_layer(ctx, plane->index, priority, true);
	mixer_cfg_vp_blend(ctx, state->base.alpha);

	spin_unlock_irqrestore(&ctx->reg_slock, flags);

	mixer_regs_dump(ctx);
	vp_regs_dump(ctx);
पूर्ण

अटल व्योम mixer_graph_buffer(काष्ठा mixer_context *ctx,
			       काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा exynos_drm_plane_state *state =
				to_exynos_plane_state(plane->base.state);
	काष्ठा drm_framebuffer *fb = state->base.fb;
	अचिन्हित पूर्णांक priority = state->base.normalized_zpos + 1;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक win = plane->index;
	अचिन्हित पूर्णांक x_ratio = 0, y_ratio = 0;
	अचिन्हित पूर्णांक dst_x_offset, dst_y_offset;
	अचिन्हित पूर्णांक pixel_alpha;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक fmt;
	u32 val;

	अगर (fb->क्रमmat->has_alpha)
		pixel_alpha = state->base.pixel_blend_mode;
	अन्यथा
		pixel_alpha = DRM_MODE_BLEND_PIXEL_NONE;

	चयन (fb->क्रमmat->क्रमmat) अणु
	हाल DRM_FORMAT_XRGB4444:
	हाल DRM_FORMAT_ARGB4444:
		fmt = MXR_FORMAT_ARGB4444;
		अवरोध;

	हाल DRM_FORMAT_XRGB1555:
	हाल DRM_FORMAT_ARGB1555:
		fmt = MXR_FORMAT_ARGB1555;
		अवरोध;

	हाल DRM_FORMAT_RGB565:
		fmt = MXR_FORMAT_RGB565;
		अवरोध;

	हाल DRM_FORMAT_XRGB8888:
	हाल DRM_FORMAT_ARGB8888:
	शेष:
		fmt = MXR_FORMAT_ARGB8888;
		अवरोध;
	पूर्ण

	/* ratio is alपढ़ोy checked by common plane code */
	x_ratio = state->h_ratio == (1 << 15);
	y_ratio = state->v_ratio == (1 << 15);

	dst_x_offset = state->crtc.x;
	dst_y_offset = state->crtc.y;

	/* translate dma address base s.t. the source image offset is zero */
	dma_addr = exynos_drm_fb_dma_addr(fb, 0)
		+ (state->src.x * fb->क्रमmat->cpp[0])
		+ (state->src.y * fb->pitches[0]);

	spin_lock_irqsave(&ctx->reg_slock, flags);

	/* setup क्रमmat */
	mixer_reg_ग_लिखोmask(ctx, MXR_GRAPHIC_CFG(win),
		MXR_GRP_CFG_FORMAT_VAL(fmt), MXR_GRP_CFG_FORMAT_MASK);

	/* setup geometry */
	mixer_reg_ग_लिखो(ctx, MXR_GRAPHIC_SPAN(win),
			fb->pitches[0] / fb->क्रमmat->cpp[0]);

	val  = MXR_GRP_WH_WIDTH(state->src.w);
	val |= MXR_GRP_WH_HEIGHT(state->src.h);
	val |= MXR_GRP_WH_H_SCALE(x_ratio);
	val |= MXR_GRP_WH_V_SCALE(y_ratio);
	mixer_reg_ग_लिखो(ctx, MXR_GRAPHIC_WH(win), val);

	/* setup offsets in display image */
	val  = MXR_GRP_DXY_DX(dst_x_offset);
	val |= MXR_GRP_DXY_DY(dst_y_offset);
	mixer_reg_ग_लिखो(ctx, MXR_GRAPHIC_DXY(win), val);

	/* set buffer address to mixer */
	mixer_reg_ग_लिखो(ctx, MXR_GRAPHIC_BASE(win), dma_addr);

	mixer_cfg_layer(ctx, win, priority, true);
	mixer_cfg_gfx_blend(ctx, win, pixel_alpha, state->base.alpha);

	spin_unlock_irqrestore(&ctx->reg_slock, flags);

	mixer_regs_dump(ctx);
पूर्ण

अटल व्योम vp_win_reset(काष्ठा mixer_context *ctx)
अणु
	अचिन्हित पूर्णांक tries = 100;

	vp_reg_ग_लिखो(ctx, VP_SRESET, VP_SRESET_PROCESSING);
	जबतक (--tries) अणु
		/* रुकोing until VP_SRESET_PROCESSING is 0 */
		अगर (~vp_reg_पढ़ो(ctx, VP_SRESET) & VP_SRESET_PROCESSING)
			अवरोध;
		mdelay(10);
	पूर्ण
	WARN(tries == 0, "failed to reset Video Processor\n");
पूर्ण

अटल व्योम mixer_win_reset(काष्ठा mixer_context *ctx)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctx->reg_slock, flags);

	mixer_reg_ग_लिखोmask(ctx, MXR_CFG, MXR_CFG_DST_HDMI, MXR_CFG_DST_MASK);

	/* set output in RGB888 mode */
	mixer_reg_ग_लिखोmask(ctx, MXR_CFG, MXR_CFG_OUT_RGB888, MXR_CFG_OUT_MASK);

	/* 16 beat burst in DMA */
	mixer_reg_ग_लिखोmask(ctx, MXR_STATUS, MXR_STATUS_16_BURST,
		MXR_STATUS_BURST_MASK);

	/* reset शेष layer priority */
	mixer_reg_ग_लिखो(ctx, MXR_LAYER_CFG, 0);

	/* set all background colors to RGB (0,0,0) */
	mixer_reg_ग_लिखो(ctx, MXR_BG_COLOR0, MXR_YCBCR_VAL(0, 128, 128));
	mixer_reg_ग_लिखो(ctx, MXR_BG_COLOR1, MXR_YCBCR_VAL(0, 128, 128));
	mixer_reg_ग_लिखो(ctx, MXR_BG_COLOR2, MXR_YCBCR_VAL(0, 128, 128));

	अगर (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags)) अणु
		/* configuration of Video Processor Registers */
		vp_win_reset(ctx);
		vp_शेष_filter(ctx);
	पूर्ण

	/* disable all layers */
	mixer_reg_ग_लिखोmask(ctx, MXR_CFG, 0, MXR_CFG_GRP0_ENABLE);
	mixer_reg_ग_लिखोmask(ctx, MXR_CFG, 0, MXR_CFG_GRP1_ENABLE);
	अगर (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags))
		mixer_reg_ग_लिखोmask(ctx, MXR_CFG, 0, MXR_CFG_VP_ENABLE);

	/* set all source image offsets to zero */
	mixer_reg_ग_लिखो(ctx, MXR_GRAPHIC_SXY(0), 0);
	mixer_reg_ग_लिखो(ctx, MXR_GRAPHIC_SXY(1), 0);

	spin_unlock_irqrestore(&ctx->reg_slock, flags);
पूर्ण

अटल irqवापस_t mixer_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा mixer_context *ctx = arg;
	u32 val;

	spin_lock(&ctx->reg_slock);

	/* पढ़ो पूर्णांकerrupt status क्रम handling and clearing flags क्रम VSYNC */
	val = mixer_reg_पढ़ो(ctx, MXR_INT_STATUS);

	/* handling VSYNC */
	अगर (val & MXR_INT_STATUS_VSYNC) अणु
		/* vsync पूर्णांकerrupt use dअगरferent bit क्रम पढ़ो and clear */
		val |= MXR_INT_CLEAR_VSYNC;
		val &= ~MXR_INT_STATUS_VSYNC;

		/* पूर्णांकerlace scan need to check shaकरोw रेजिस्टर */
		अगर (test_bit(MXR_BIT_INTERLACE, &ctx->flags)
		    && !mixer_is_synced(ctx))
			जाओ out;

		drm_crtc_handle_vblank(&ctx->crtc->base);
	पूर्ण

out:
	/* clear पूर्णांकerrupts */
	mixer_reg_ग_लिखो(ctx, MXR_INT_STATUS, val);

	spin_unlock(&ctx->reg_slock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mixer_resources_init(काष्ठा mixer_context *mixer_ctx)
अणु
	काष्ठा device *dev = &mixer_ctx->pdev->dev;
	काष्ठा resource *res;
	पूर्णांक ret;

	spin_lock_init(&mixer_ctx->reg_slock);

	mixer_ctx->mixer = devm_clk_get(dev, "mixer");
	अगर (IS_ERR(mixer_ctx->mixer)) अणु
		dev_err(dev, "failed to get clock 'mixer'\n");
		वापस -ENODEV;
	पूर्ण

	mixer_ctx->hdmi = devm_clk_get(dev, "hdmi");
	अगर (IS_ERR(mixer_ctx->hdmi)) अणु
		dev_err(dev, "failed to get clock 'hdmi'\n");
		वापस PTR_ERR(mixer_ctx->hdmi);
	पूर्ण

	mixer_ctx->sclk_hdmi = devm_clk_get(dev, "sclk_hdmi");
	अगर (IS_ERR(mixer_ctx->sclk_hdmi)) अणु
		dev_err(dev, "failed to get clock 'sclk_hdmi'\n");
		वापस -ENODEV;
	पूर्ण
	res = platक्रमm_get_resource(mixer_ctx->pdev, IORESOURCE_MEM, 0);
	अगर (res == शून्य) अणु
		dev_err(dev, "get memory resource failed.\n");
		वापस -ENXIO;
	पूर्ण

	mixer_ctx->mixer_regs = devm_ioremap(dev, res->start,
							resource_size(res));
	अगर (mixer_ctx->mixer_regs == शून्य) अणु
		dev_err(dev, "register mapping failed.\n");
		वापस -ENXIO;
	पूर्ण

	res = platक्रमm_get_resource(mixer_ctx->pdev, IORESOURCE_IRQ, 0);
	अगर (res == शून्य) अणु
		dev_err(dev, "get interrupt resource failed.\n");
		वापस -ENXIO;
	पूर्ण

	ret = devm_request_irq(dev, res->start, mixer_irq_handler,
						0, "drm_mixer", mixer_ctx);
	अगर (ret) अणु
		dev_err(dev, "request interrupt failed.\n");
		वापस ret;
	पूर्ण
	mixer_ctx->irq = res->start;

	वापस 0;
पूर्ण

अटल पूर्णांक vp_resources_init(काष्ठा mixer_context *mixer_ctx)
अणु
	काष्ठा device *dev = &mixer_ctx->pdev->dev;
	काष्ठा resource *res;

	mixer_ctx->vp = devm_clk_get(dev, "vp");
	अगर (IS_ERR(mixer_ctx->vp)) अणु
		dev_err(dev, "failed to get clock 'vp'\n");
		वापस -ENODEV;
	पूर्ण

	अगर (test_bit(MXR_BIT_HAS_SCLK, &mixer_ctx->flags)) अणु
		mixer_ctx->sclk_mixer = devm_clk_get(dev, "sclk_mixer");
		अगर (IS_ERR(mixer_ctx->sclk_mixer)) अणु
			dev_err(dev, "failed to get clock 'sclk_mixer'\n");
			वापस -ENODEV;
		पूर्ण
		mixer_ctx->mout_mixer = devm_clk_get(dev, "mout_mixer");
		अगर (IS_ERR(mixer_ctx->mout_mixer)) अणु
			dev_err(dev, "failed to get clock 'mout_mixer'\n");
			वापस -ENODEV;
		पूर्ण

		अगर (mixer_ctx->sclk_hdmi && mixer_ctx->mout_mixer)
			clk_set_parent(mixer_ctx->mout_mixer,
				       mixer_ctx->sclk_hdmi);
	पूर्ण

	res = platक्रमm_get_resource(mixer_ctx->pdev, IORESOURCE_MEM, 1);
	अगर (res == शून्य) अणु
		dev_err(dev, "get memory resource failed.\n");
		वापस -ENXIO;
	पूर्ण

	mixer_ctx->vp_regs = devm_ioremap(dev, res->start,
							resource_size(res));
	अगर (mixer_ctx->vp_regs == शून्य) अणु
		dev_err(dev, "register mapping failed.\n");
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mixer_initialize(काष्ठा mixer_context *mixer_ctx,
			काष्ठा drm_device *drm_dev)
अणु
	पूर्णांक ret;

	mixer_ctx->drm_dev = drm_dev;

	/* acquire resources: regs, irqs, घड़ीs */
	ret = mixer_resources_init(mixer_ctx);
	अगर (ret) अणु
		DRM_DEV_ERROR(mixer_ctx->dev,
			      "mixer_resources_init failed ret=%d\n", ret);
		वापस ret;
	पूर्ण

	अगर (test_bit(MXR_BIT_VP_ENABLED, &mixer_ctx->flags)) अणु
		/* acquire vp resources: regs, irqs, घड़ीs */
		ret = vp_resources_init(mixer_ctx);
		अगर (ret) अणु
			DRM_DEV_ERROR(mixer_ctx->dev,
				      "vp_resources_init failed ret=%d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस exynos_drm_रेजिस्टर_dma(drm_dev, mixer_ctx->dev,
				       &mixer_ctx->dma_priv);
पूर्ण

अटल व्योम mixer_ctx_हटाओ(काष्ठा mixer_context *mixer_ctx)
अणु
	exynos_drm_unरेजिस्टर_dma(mixer_ctx->drm_dev, mixer_ctx->dev,
				  &mixer_ctx->dma_priv);
पूर्ण

अटल पूर्णांक mixer_enable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा mixer_context *mixer_ctx = crtc->ctx;

	__set_bit(MXR_BIT_VSYNC, &mixer_ctx->flags);
	अगर (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		वापस 0;

	/* enable vsync पूर्णांकerrupt */
	mixer_reg_ग_लिखोmask(mixer_ctx, MXR_INT_STATUS, ~0, MXR_INT_CLEAR_VSYNC);
	mixer_reg_ग_लिखोmask(mixer_ctx, MXR_INT_EN, ~0, MXR_INT_EN_VSYNC);

	वापस 0;
पूर्ण

अटल व्योम mixer_disable_vblank(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा mixer_context *mixer_ctx = crtc->ctx;

	__clear_bit(MXR_BIT_VSYNC, &mixer_ctx->flags);

	अगर (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		वापस;

	/* disable vsync पूर्णांकerrupt */
	mixer_reg_ग_लिखोmask(mixer_ctx, MXR_INT_STATUS, ~0, MXR_INT_CLEAR_VSYNC);
	mixer_reg_ग_लिखोmask(mixer_ctx, MXR_INT_EN, 0, MXR_INT_EN_VSYNC);
पूर्ण

अटल व्योम mixer_atomic_begin(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा mixer_context *ctx = crtc->ctx;

	अगर (!test_bit(MXR_BIT_POWERED, &ctx->flags))
		वापस;

	अगर (mixer_रुको_क्रम_sync(ctx))
		dev_err(ctx->dev, "timeout waiting for VSYNC\n");
	mixer_disable_sync(ctx);
पूर्ण

अटल व्योम mixer_update_plane(काष्ठा exynos_drm_crtc *crtc,
			       काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा mixer_context *mixer_ctx = crtc->ctx;

	DRM_DEV_DEBUG_KMS(mixer_ctx->dev, "win: %d\n", plane->index);

	अगर (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		वापस;

	अगर (plane->index == VP_DEFAULT_WIN)
		vp_video_buffer(mixer_ctx, plane);
	अन्यथा
		mixer_graph_buffer(mixer_ctx, plane);
पूर्ण

अटल व्योम mixer_disable_plane(काष्ठा exynos_drm_crtc *crtc,
				काष्ठा exynos_drm_plane *plane)
अणु
	काष्ठा mixer_context *mixer_ctx = crtc->ctx;
	अचिन्हित दीर्घ flags;

	DRM_DEV_DEBUG_KMS(mixer_ctx->dev, "win: %d\n", plane->index);

	अगर (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		वापस;

	spin_lock_irqsave(&mixer_ctx->reg_slock, flags);
	mixer_cfg_layer(mixer_ctx, plane->index, 0, false);
	spin_unlock_irqrestore(&mixer_ctx->reg_slock, flags);
पूर्ण

अटल व्योम mixer_atomic_flush(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा mixer_context *mixer_ctx = crtc->ctx;

	अगर (!test_bit(MXR_BIT_POWERED, &mixer_ctx->flags))
		वापस;

	mixer_enable_sync(mixer_ctx);
	exynos_crtc_handle_event(crtc);
पूर्ण

अटल व्योम mixer_atomic_enable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा mixer_context *ctx = crtc->ctx;

	अगर (test_bit(MXR_BIT_POWERED, &ctx->flags))
		वापस;

	pm_runसमय_get_sync(ctx->dev);

	exynos_drm_pipe_clk_enable(crtc, true);

	mixer_disable_sync(ctx);

	mixer_reg_ग_लिखोmask(ctx, MXR_STATUS, ~0, MXR_STATUS_SOFT_RESET);

	अगर (test_bit(MXR_BIT_VSYNC, &ctx->flags)) अणु
		mixer_reg_ग_लिखोmask(ctx, MXR_INT_STATUS, ~0,
					MXR_INT_CLEAR_VSYNC);
		mixer_reg_ग_लिखोmask(ctx, MXR_INT_EN, ~0, MXR_INT_EN_VSYNC);
	पूर्ण
	mixer_win_reset(ctx);

	mixer_commit(ctx);

	mixer_enable_sync(ctx);

	set_bit(MXR_BIT_POWERED, &ctx->flags);
पूर्ण

अटल व्योम mixer_atomic_disable(काष्ठा exynos_drm_crtc *crtc)
अणु
	काष्ठा mixer_context *ctx = crtc->ctx;
	पूर्णांक i;

	अगर (!test_bit(MXR_BIT_POWERED, &ctx->flags))
		वापस;

	mixer_stop(ctx);
	mixer_regs_dump(ctx);

	क्रम (i = 0; i < MIXER_WIN_NR; i++)
		mixer_disable_plane(crtc, &ctx->planes[i]);

	exynos_drm_pipe_clk_enable(crtc, false);

	pm_runसमय_put(ctx->dev);

	clear_bit(MXR_BIT_POWERED, &ctx->flags);
पूर्ण

अटल पूर्णांक mixer_mode_valid(काष्ठा exynos_drm_crtc *crtc,
		स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा mixer_context *ctx = crtc->ctx;
	u32 w = mode->hdisplay, h = mode->vdisplay;

	DRM_DEV_DEBUG_KMS(ctx->dev, "xres=%d, yres=%d, refresh=%d, intl=%d\n",
			  w, h, drm_mode_vrefresh(mode),
			  !!(mode->flags & DRM_MODE_FLAG_INTERLACE));

	अगर (ctx->mxr_ver == MXR_VER_128_0_0_184)
		वापस MODE_OK;

	अगर ((w >= 464 && w <= 720 && h >= 261 && h <= 576) ||
	    (w >= 1024 && w <= 1280 && h >= 576 && h <= 720) ||
	    (w >= 1664 && w <= 1920 && h >= 936 && h <= 1080))
		वापस MODE_OK;

	अगर ((w == 1024 && h == 768) ||
	    (w == 1366 && h == 768) ||
	    (w == 1280 && h == 1024))
		वापस MODE_OK;

	वापस MODE_BAD;
पूर्ण

अटल bool mixer_mode_fixup(काष्ठा exynos_drm_crtc *crtc,
		   स्थिर काष्ठा drm_display_mode *mode,
		   काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा mixer_context *ctx = crtc->ctx;
	पूर्णांक width = mode->hdisplay, height = mode->vdisplay, i;

	अटल स्थिर काष्ठा अणु
		पूर्णांक hdisplay, vdisplay, htotal, vtotal, scan_val;
	पूर्ण modes[] = अणु
		अणु 720, 480, 858, 525, MXR_CFG_SCAN_NTSC | MXR_CFG_SCAN_SD पूर्ण,
		अणु 720, 576, 864, 625, MXR_CFG_SCAN_PAL | MXR_CFG_SCAN_SD पूर्ण,
		अणु 1280, 720, 1650, 750, MXR_CFG_SCAN_HD_720 | MXR_CFG_SCAN_HD पूर्ण,
		अणु 1920, 1080, 2200, 1125, MXR_CFG_SCAN_HD_1080 |
						MXR_CFG_SCAN_HD पूर्ण
	पूर्ण;

	अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
		__set_bit(MXR_BIT_INTERLACE, &ctx->flags);
	अन्यथा
		__clear_bit(MXR_BIT_INTERLACE, &ctx->flags);

	अगर (ctx->mxr_ver == MXR_VER_128_0_0_184)
		वापस true;

	क्रम (i = 0; i < ARRAY_SIZE(modes); ++i)
		अगर (width <= modes[i].hdisplay && height <= modes[i].vdisplay) अणु
			ctx->scan_value = modes[i].scan_val;
			अगर (width < modes[i].hdisplay ||
			    height < modes[i].vdisplay) अणु
				adjusted_mode->hdisplay = modes[i].hdisplay;
				adjusted_mode->hsync_start = modes[i].hdisplay;
				adjusted_mode->hsync_end = modes[i].htotal;
				adjusted_mode->htotal = modes[i].htotal;
				adjusted_mode->vdisplay = modes[i].vdisplay;
				adjusted_mode->vsync_start = modes[i].vdisplay;
				adjusted_mode->vsync_end = modes[i].vtotal;
				adjusted_mode->vtotal = modes[i].vtotal;
			पूर्ण

			वापस true;
		पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा exynos_drm_crtc_ops mixer_crtc_ops = अणु
	.atomic_enable		= mixer_atomic_enable,
	.atomic_disable		= mixer_atomic_disable,
	.enable_vblank		= mixer_enable_vblank,
	.disable_vblank		= mixer_disable_vblank,
	.atomic_begin		= mixer_atomic_begin,
	.update_plane		= mixer_update_plane,
	.disable_plane		= mixer_disable_plane,
	.atomic_flush		= mixer_atomic_flush,
	.mode_valid		= mixer_mode_valid,
	.mode_fixup		= mixer_mode_fixup,
पूर्ण;

अटल स्थिर काष्ठा mixer_drv_data exynos5420_mxr_drv_data = अणु
	.version = MXR_VER_128_0_0_184,
	.is_vp_enabled = 0,
पूर्ण;

अटल स्थिर काष्ठा mixer_drv_data exynos5250_mxr_drv_data = अणु
	.version = MXR_VER_16_0_33_0,
	.is_vp_enabled = 0,
पूर्ण;

अटल स्थिर काष्ठा mixer_drv_data exynos4212_mxr_drv_data = अणु
	.version = MXR_VER_0_0_0_16,
	.is_vp_enabled = 1,
पूर्ण;

अटल स्थिर काष्ठा mixer_drv_data exynos4210_mxr_drv_data = अणु
	.version = MXR_VER_0_0_0_16,
	.is_vp_enabled = 1,
	.has_sclk = 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mixer_match_types[] = अणु
	अणु
		.compatible = "samsung,exynos4210-mixer",
		.data	= &exynos4210_mxr_drv_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos4212-mixer",
		.data	= &exynos4212_mxr_drv_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5-mixer",
		.data	= &exynos5250_mxr_drv_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5250-mixer",
		.data	= &exynos5250_mxr_drv_data,
	पूर्ण, अणु
		.compatible = "samsung,exynos5420-mixer",
		.data	= &exynos5420_mxr_drv_data,
	पूर्ण, अणु
		/* end node */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mixer_match_types);

अटल पूर्णांक mixer_bind(काष्ठा device *dev, काष्ठा device *manager, व्योम *data)
अणु
	काष्ठा mixer_context *ctx = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा exynos_drm_plane *exynos_plane;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = mixer_initialize(ctx, drm_dev);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < MIXER_WIN_NR; i++) अणु
		अगर (i == VP_DEFAULT_WIN && !test_bit(MXR_BIT_VP_ENABLED,
						     &ctx->flags))
			जारी;

		ret = exynos_plane_init(drm_dev, &ctx->planes[i], i,
					&plane_configs[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	exynos_plane = &ctx->planes[DEFAULT_WIN];
	ctx->crtc = exynos_drm_crtc_create(drm_dev, &exynos_plane->base,
			EXYNOS_DISPLAY_TYPE_HDMI, &mixer_crtc_ops, ctx);
	अगर (IS_ERR(ctx->crtc)) अणु
		mixer_ctx_हटाओ(ctx);
		ret = PTR_ERR(ctx->crtc);
		जाओ मुक्त_ctx;
	पूर्ण

	वापस 0;

मुक्त_ctx:
	devm_kमुक्त(dev, ctx);
	वापस ret;
पूर्ण

अटल व्योम mixer_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा mixer_context *ctx = dev_get_drvdata(dev);

	mixer_ctx_हटाओ(ctx);
पूर्ण

अटल स्थिर काष्ठा component_ops mixer_component_ops = अणु
	.bind	= mixer_bind,
	.unbind	= mixer_unbind,
पूर्ण;

अटल पूर्णांक mixer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा mixer_drv_data *drv;
	काष्ठा mixer_context *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx) अणु
		DRM_DEV_ERROR(dev, "failed to alloc mixer context.\n");
		वापस -ENOMEM;
	पूर्ण

	drv = of_device_get_match_data(dev);

	ctx->pdev = pdev;
	ctx->dev = dev;
	ctx->mxr_ver = drv->version;

	अगर (drv->is_vp_enabled)
		__set_bit(MXR_BIT_VP_ENABLED, &ctx->flags);
	अगर (drv->has_sclk)
		__set_bit(MXR_BIT_HAS_SCLK, &ctx->flags);

	platक्रमm_set_drvdata(pdev, ctx);

	pm_runसमय_enable(dev);

	ret = component_add(&pdev->dev, &mixer_component_ops);
	अगर (ret)
		pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mixer_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);

	component_del(&pdev->dev, &mixer_component_ops);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_mixer_suspend(काष्ठा device *dev)
अणु
	काष्ठा mixer_context *ctx = dev_get_drvdata(dev);

	clk_disable_unprepare(ctx->hdmi);
	clk_disable_unprepare(ctx->mixer);
	अगर (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags)) अणु
		clk_disable_unprepare(ctx->vp);
		अगर (test_bit(MXR_BIT_HAS_SCLK, &ctx->flags))
			clk_disable_unprepare(ctx->sclk_mixer);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused exynos_mixer_resume(काष्ठा device *dev)
अणु
	काष्ठा mixer_context *ctx = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(ctx->mixer);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(ctx->dev,
			      "Failed to prepare_enable the mixer clk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण
	ret = clk_prepare_enable(ctx->hdmi);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dev,
			      "Failed to prepare_enable the hdmi clk [%d]\n",
			      ret);
		वापस ret;
	पूर्ण
	अगर (test_bit(MXR_BIT_VP_ENABLED, &ctx->flags)) अणु
		ret = clk_prepare_enable(ctx->vp);
		अगर (ret < 0) अणु
			DRM_DEV_ERROR(dev,
				      "Failed to prepare_enable the vp clk [%d]\n",
				      ret);
			वापस ret;
		पूर्ण
		अगर (test_bit(MXR_BIT_HAS_SCLK, &ctx->flags)) अणु
			ret = clk_prepare_enable(ctx->sclk_mixer);
			अगर (ret < 0) अणु
				DRM_DEV_ERROR(dev,
					   "Failed to prepare_enable the " \
					   "sclk_mixer clk [%d]\n",
					   ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops exynos_mixer_pm_ops = अणु
	SET_RUNTIME_PM_OPS(exynos_mixer_suspend, exynos_mixer_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver mixer_driver = अणु
	.driver = अणु
		.name = "exynos-mixer",
		.owner = THIS_MODULE,
		.pm = &exynos_mixer_pm_ops,
		.of_match_table = mixer_match_types,
	पूर्ण,
	.probe = mixer_probe,
	.हटाओ = mixer_हटाओ,
पूर्ण;
