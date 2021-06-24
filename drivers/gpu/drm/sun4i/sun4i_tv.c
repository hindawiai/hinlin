<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Free Electrons
 * Copyright (C) 2015 NextThing Co
 *
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_of.h>
#समावेश <drm/drm_panel.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

#समावेश "sun4i_crtc.h"
#समावेश "sun4i_drv.h"
#समावेश "sunxi_engine.h"

#घोषणा SUN4I_TVE_EN_REG		0x000
#घोषणा SUN4I_TVE_EN_DAC_MAP_MASK		GENMASK(19, 4)
#घोषणा SUN4I_TVE_EN_DAC_MAP(dac, out)		(((out) & 0xf) << (dac + 1) * 4)
#घोषणा SUN4I_TVE_EN_ENABLE			BIT(0)

#घोषणा SUN4I_TVE_CFG0_REG		0x004
#घोषणा SUN4I_TVE_CFG0_DAC_CONTROL_54M		BIT(26)
#घोषणा SUN4I_TVE_CFG0_CORE_DATAPATH_54M	BIT(25)
#घोषणा SUN4I_TVE_CFG0_CORE_CONTROL_54M		BIT(24)
#घोषणा SUN4I_TVE_CFG0_YC_EN			BIT(17)
#घोषणा SUN4I_TVE_CFG0_COMP_EN			BIT(16)
#घोषणा SUN4I_TVE_CFG0_RES(x)			((x) & 0xf)
#घोषणा SUN4I_TVE_CFG0_RES_480i			SUN4I_TVE_CFG0_RES(0)
#घोषणा SUN4I_TVE_CFG0_RES_576i			SUN4I_TVE_CFG0_RES(1)

#घोषणा SUN4I_TVE_DAC0_REG		0x008
#घोषणा SUN4I_TVE_DAC0_CLOCK_INVERT		BIT(24)
#घोषणा SUN4I_TVE_DAC0_LUMA(x)			(((x) & 3) << 20)
#घोषणा SUN4I_TVE_DAC0_LUMA_0_4			SUN4I_TVE_DAC0_LUMA(3)
#घोषणा SUN4I_TVE_DAC0_CHROMA(x)		(((x) & 3) << 18)
#घोषणा SUN4I_TVE_DAC0_CHROMA_0_75		SUN4I_TVE_DAC0_CHROMA(3)
#घोषणा SUN4I_TVE_DAC0_INTERNAL_DAC(x)		(((x) & 3) << 16)
#घोषणा SUN4I_TVE_DAC0_INTERNAL_DAC_37_5_OHMS	SUN4I_TVE_DAC0_INTERNAL_DAC(3)
#घोषणा SUN4I_TVE_DAC0_DAC_EN(dac)		BIT(dac)

#घोषणा SUN4I_TVE_NOTCH_REG		0x00c
#घोषणा SUN4I_TVE_NOTCH_DAC0_TO_DAC_DLY(dac, x)	((4 - (x)) << (dac * 3))

#घोषणा SUN4I_TVE_CHROMA_FREQ_REG	0x010

#घोषणा SUN4I_TVE_PORCH_REG		0x014
#घोषणा SUN4I_TVE_PORCH_BACK(x)			((x) << 16)
#घोषणा SUN4I_TVE_PORCH_FRONT(x)		(x)

#घोषणा SUN4I_TVE_LINE_REG		0x01c
#घोषणा SUN4I_TVE_LINE_FIRST(x)			((x) << 16)
#घोषणा SUN4I_TVE_LINE_NUMBER(x)		(x)

#घोषणा SUN4I_TVE_LEVEL_REG		0x020
#घोषणा SUN4I_TVE_LEVEL_BLANK(x)		((x) << 16)
#घोषणा SUN4I_TVE_LEVEL_BLACK(x)		(x)

#घोषणा SUN4I_TVE_DAC1_REG		0x024
#घोषणा SUN4I_TVE_DAC1_AMPLITUDE(dac, x)	((x) << (dac * 8))

#घोषणा SUN4I_TVE_DETECT_STA_REG	0x038
#घोषणा SUN4I_TVE_DETECT_STA_DAC(dac)		BIT((dac * 8))
#घोषणा SUN4I_TVE_DETECT_STA_UNCONNECTED		0
#घोषणा SUN4I_TVE_DETECT_STA_CONNECTED			1
#घोषणा SUN4I_TVE_DETECT_STA_GROUND			2

#घोषणा SUN4I_TVE_CB_CR_LVL_REG		0x10c
#घोषणा SUN4I_TVE_CB_CR_LVL_CR_BURST(x)		((x) << 8)
#घोषणा SUN4I_TVE_CB_CR_LVL_CB_BURST(x)		(x)

#घोषणा SUN4I_TVE_TINT_BURST_PHASE_REG	0x110
#घोषणा SUN4I_TVE_TINT_BURST_PHASE_CHROMA(x)	(x)

#घोषणा SUN4I_TVE_BURST_WIDTH_REG	0x114
#घोषणा SUN4I_TVE_BURST_WIDTH_BREEZEWAY(x)	((x) << 16)
#घोषणा SUN4I_TVE_BURST_WIDTH_BURST_WIDTH(x)	((x) << 8)
#घोषणा SUN4I_TVE_BURST_WIDTH_HSYNC_WIDTH(x)	(x)

#घोषणा SUN4I_TVE_CB_CR_GAIN_REG	0x118
#घोषणा SUN4I_TVE_CB_CR_GAIN_CR(x)		((x) << 8)
#घोषणा SUN4I_TVE_CB_CR_GAIN_CB(x)		(x)

#घोषणा SUN4I_TVE_SYNC_VBI_REG		0x11c
#घोषणा SUN4I_TVE_SYNC_VBI_SYNC(x)		((x) << 16)
#घोषणा SUN4I_TVE_SYNC_VBI_VBLANK(x)		(x)

#घोषणा SUN4I_TVE_ACTIVE_LINE_REG	0x124
#घोषणा SUN4I_TVE_ACTIVE_LINE(x)		(x)

#घोषणा SUN4I_TVE_CHROMA_REG		0x128
#घोषणा SUN4I_TVE_CHROMA_COMP_GAIN(x)		((x) & 3)
#घोषणा SUN4I_TVE_CHROMA_COMP_GAIN_50		SUN4I_TVE_CHROMA_COMP_GAIN(2)

#घोषणा SUN4I_TVE_12C_REG		0x12c
#घोषणा SUN4I_TVE_12C_NOTCH_WIDTH_WIDE		BIT(8)
#घोषणा SUN4I_TVE_12C_COMP_YUV_EN		BIT(0)

#घोषणा SUN4I_TVE_RESYNC_REG		0x130
#घोषणा SUN4I_TVE_RESYNC_FIELD			BIT(31)
#घोषणा SUN4I_TVE_RESYNC_LINE(x)		((x) << 16)
#घोषणा SUN4I_TVE_RESYNC_PIXEL(x)		(x)

#घोषणा SUN4I_TVE_SLAVE_REG		0x134

#घोषणा SUN4I_TVE_WSS_DATA2_REG		0x244

काष्ठा color_gains अणु
	u16	cb;
	u16	cr;
पूर्ण;

काष्ठा burst_levels अणु
	u16	cb;
	u16	cr;
पूर्ण;

काष्ठा video_levels अणु
	u16	black;
	u16	blank;
पूर्ण;

काष्ठा resync_parameters अणु
	bool	field;
	u16	line;
	u16	pixel;
पूर्ण;

काष्ठा tv_mode अणु
	अक्षर		*name;

	u32		mode;
	u32		chroma_freq;
	u16		back_porch;
	u16		front_porch;
	u16		line_number;
	u16		vblank_level;

	u32		hdisplay;
	u16		hfront_porch;
	u16		hsync_len;
	u16		hback_porch;

	u32		vdisplay;
	u16		vfront_porch;
	u16		vsync_len;
	u16		vback_porch;

	bool		yc_en;
	bool		dac3_en;
	bool		dac_bit25_en;

	स्थिर काष्ठा color_gains	*color_gains;
	स्थिर काष्ठा burst_levels	*burst_levels;
	स्थिर काष्ठा video_levels	*video_levels;
	स्थिर काष्ठा resync_parameters	*resync_params;
पूर्ण;

काष्ठा sun4i_tv अणु
	काष्ठा drm_connector	connector;
	काष्ठा drm_encoder	encoder;

	काष्ठा clk		*clk;
	काष्ठा regmap		*regs;
	काष्ठा reset_control	*reset;

	काष्ठा sun4i_drv	*drv;
पूर्ण;

अटल स्थिर काष्ठा video_levels ntsc_video_levels = अणु
	.black = 282,	.blank = 240,
पूर्ण;

अटल स्थिर काष्ठा video_levels pal_video_levels = अणु
	.black = 252,	.blank = 252,
पूर्ण;

अटल स्थिर काष्ठा burst_levels ntsc_burst_levels = अणु
	.cb = 79,	.cr = 0,
पूर्ण;

अटल स्थिर काष्ठा burst_levels pal_burst_levels = अणु
	.cb = 40,	.cr = 40,
पूर्ण;

अटल स्थिर काष्ठा color_gains ntsc_color_gains = अणु
	.cb = 160,	.cr = 160,
पूर्ण;

अटल स्थिर काष्ठा color_gains pal_color_gains = अणु
	.cb = 224,	.cr = 224,
पूर्ण;

अटल स्थिर काष्ठा resync_parameters ntsc_resync_parameters = अणु
	.field = false,	.line = 14,	.pixel = 12,
पूर्ण;

अटल स्थिर काष्ठा resync_parameters pal_resync_parameters = अणु
	.field = true,	.line = 13,	.pixel = 12,
पूर्ण;

अटल स्थिर काष्ठा tv_mode tv_modes[] = अणु
	अणु
		.name		= "NTSC",
		.mode		= SUN4I_TVE_CFG0_RES_480i,
		.chroma_freq	= 0x21f07c1f,
		.yc_en		= true,
		.dac3_en	= true,
		.dac_bit25_en	= true,

		.back_porch	= 118,
		.front_porch	= 32,
		.line_number	= 525,

		.hdisplay	= 720,
		.hfront_porch	= 18,
		.hsync_len	= 2,
		.hback_porch	= 118,

		.vdisplay	= 480,
		.vfront_porch	= 26,
		.vsync_len	= 2,
		.vback_porch	= 17,

		.vblank_level	= 240,

		.color_gains	= &ntsc_color_gains,
		.burst_levels	= &ntsc_burst_levels,
		.video_levels	= &ntsc_video_levels,
		.resync_params	= &ntsc_resync_parameters,
	पूर्ण,
	अणु
		.name		= "PAL",
		.mode		= SUN4I_TVE_CFG0_RES_576i,
		.chroma_freq	= 0x2a098acb,

		.back_porch	= 138,
		.front_porch	= 24,
		.line_number	= 625,

		.hdisplay	= 720,
		.hfront_porch	= 3,
		.hsync_len	= 2,
		.hback_porch	= 139,

		.vdisplay	= 576,
		.vfront_porch	= 28,
		.vsync_len	= 2,
		.vback_porch	= 19,

		.vblank_level	= 252,

		.color_gains	= &pal_color_gains,
		.burst_levels	= &pal_burst_levels,
		.video_levels	= &pal_video_levels,
		.resync_params	= &pal_resync_parameters,
	पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा sun4i_tv *
drm_encoder_to_sun4i_tv(काष्ठा drm_encoder *encoder)
अणु
	वापस container_of(encoder, काष्ठा sun4i_tv,
			    encoder);
पूर्ण

अटल अंतरभूत काष्ठा sun4i_tv *
drm_connector_to_sun4i_tv(काष्ठा drm_connector *connector)
अणु
	वापस container_of(connector, काष्ठा sun4i_tv,
			    connector);
पूर्ण

/*
 * FIXME: If only the drm_display_mode निजी field was usable, this
 * could go away...
 *
 * So far, it करोesn't seem to be preserved when the mode is passed by
 * to mode_set क्रम some reason.
 */
अटल स्थिर काष्ठा tv_mode *sun4i_tv_find_tv_by_mode(स्थिर काष्ठा drm_display_mode *mode)
अणु
	पूर्णांक i;

	/* First try to identअगरy the mode by name */
	क्रम (i = 0; i < ARRAY_SIZE(tv_modes); i++) अणु
		स्थिर काष्ठा tv_mode *tv_mode = &tv_modes[i];

		DRM_DEBUG_DRIVER("Comparing mode %s vs %s",
				 mode->name, tv_mode->name);

		अगर (!म_भेद(mode->name, tv_mode->name))
			वापस tv_mode;
	पूर्ण

	/* Then by number of lines */
	क्रम (i = 0; i < ARRAY_SIZE(tv_modes); i++) अणु
		स्थिर काष्ठा tv_mode *tv_mode = &tv_modes[i];

		DRM_DEBUG_DRIVER("Comparing mode %s vs %s (X: %d vs %d)",
				 mode->name, tv_mode->name,
				 mode->vdisplay, tv_mode->vdisplay);

		अगर (mode->vdisplay == tv_mode->vdisplay)
			वापस tv_mode;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम sun4i_tv_mode_to_drm_mode(स्थिर काष्ठा tv_mode *tv_mode,
				      काष्ठा drm_display_mode *mode)
अणु
	DRM_DEBUG_DRIVER("Creating mode %s\n", mode->name);

	mode->type = DRM_MODE_TYPE_DRIVER;
	mode->घड़ी = 13500;
	mode->flags = DRM_MODE_FLAG_INTERLACE;

	mode->hdisplay = tv_mode->hdisplay;
	mode->hsync_start = mode->hdisplay + tv_mode->hfront_porch;
	mode->hsync_end = mode->hsync_start + tv_mode->hsync_len;
	mode->htotal = mode->hsync_end  + tv_mode->hback_porch;

	mode->vdisplay = tv_mode->vdisplay;
	mode->vsync_start = mode->vdisplay + tv_mode->vfront_porch;
	mode->vsync_end = mode->vsync_start + tv_mode->vsync_len;
	mode->vtotal = mode->vsync_end  + tv_mode->vback_porch;
पूर्ण

अटल व्योम sun4i_tv_disable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_tv *tv = drm_encoder_to_sun4i_tv(encoder);
	काष्ठा sun4i_crtc *crtc = drm_crtc_to_sun4i_crtc(encoder->crtc);

	DRM_DEBUG_DRIVER("Disabling the TV Output\n");

	regmap_update_bits(tv->regs, SUN4I_TVE_EN_REG,
			   SUN4I_TVE_EN_ENABLE,
			   0);

	sunxi_engine_disable_color_correction(crtc->engine);
पूर्ण

अटल व्योम sun4i_tv_enable(काष्ठा drm_encoder *encoder)
अणु
	काष्ठा sun4i_tv *tv = drm_encoder_to_sun4i_tv(encoder);
	काष्ठा sun4i_crtc *crtc = drm_crtc_to_sun4i_crtc(encoder->crtc);

	DRM_DEBUG_DRIVER("Enabling the TV Output\n");

	sunxi_engine_apply_color_correction(crtc->engine);

	regmap_update_bits(tv->regs, SUN4I_TVE_EN_REG,
			   SUN4I_TVE_EN_ENABLE,
			   SUN4I_TVE_EN_ENABLE);
पूर्ण

अटल व्योम sun4i_tv_mode_set(काष्ठा drm_encoder *encoder,
			      काष्ठा drm_display_mode *mode,
			      काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा sun4i_tv *tv = drm_encoder_to_sun4i_tv(encoder);
	स्थिर काष्ठा tv_mode *tv_mode = sun4i_tv_find_tv_by_mode(mode);

	/* Enable and map the DAC to the output */
	regmap_update_bits(tv->regs, SUN4I_TVE_EN_REG,
			   SUN4I_TVE_EN_DAC_MAP_MASK,
			   SUN4I_TVE_EN_DAC_MAP(0, 1) |
			   SUN4I_TVE_EN_DAC_MAP(1, 2) |
			   SUN4I_TVE_EN_DAC_MAP(2, 3) |
			   SUN4I_TVE_EN_DAC_MAP(3, 4));

	/* Set PAL settings */
	regmap_ग_लिखो(tv->regs, SUN4I_TVE_CFG0_REG,
		     tv_mode->mode |
		     (tv_mode->yc_en ? SUN4I_TVE_CFG0_YC_EN : 0) |
		     SUN4I_TVE_CFG0_COMP_EN |
		     SUN4I_TVE_CFG0_DAC_CONTROL_54M |
		     SUN4I_TVE_CFG0_CORE_DATAPATH_54M |
		     SUN4I_TVE_CFG0_CORE_CONTROL_54M);

	/* Configure the DAC क्रम a composite output */
	regmap_ग_लिखो(tv->regs, SUN4I_TVE_DAC0_REG,
		     SUN4I_TVE_DAC0_DAC_EN(0) |
		     (tv_mode->dac3_en ? SUN4I_TVE_DAC0_DAC_EN(3) : 0) |
		     SUN4I_TVE_DAC0_INTERNAL_DAC_37_5_OHMS |
		     SUN4I_TVE_DAC0_CHROMA_0_75 |
		     SUN4I_TVE_DAC0_LUMA_0_4 |
		     SUN4I_TVE_DAC0_CLOCK_INVERT |
		     (tv_mode->dac_bit25_en ? BIT(25) : 0) |
		     BIT(30));

	/* Configure the sample delay between DAC0 and the other DAC */
	regmap_ग_लिखो(tv->regs, SUN4I_TVE_NOTCH_REG,
		     SUN4I_TVE_NOTCH_DAC0_TO_DAC_DLY(1, 0) |
		     SUN4I_TVE_NOTCH_DAC0_TO_DAC_DLY(2, 0));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_CHROMA_FREQ_REG,
		     tv_mode->chroma_freq);

	/* Set the front and back porch */
	regmap_ग_लिखो(tv->regs, SUN4I_TVE_PORCH_REG,
		     SUN4I_TVE_PORCH_BACK(tv_mode->back_porch) |
		     SUN4I_TVE_PORCH_FRONT(tv_mode->front_porch));

	/* Set the lines setup */
	regmap_ग_लिखो(tv->regs, SUN4I_TVE_LINE_REG,
		     SUN4I_TVE_LINE_FIRST(22) |
		     SUN4I_TVE_LINE_NUMBER(tv_mode->line_number));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_LEVEL_REG,
		     SUN4I_TVE_LEVEL_BLANK(tv_mode->video_levels->blank) |
		     SUN4I_TVE_LEVEL_BLACK(tv_mode->video_levels->black));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_DAC1_REG,
		     SUN4I_TVE_DAC1_AMPLITUDE(0, 0x18) |
		     SUN4I_TVE_DAC1_AMPLITUDE(1, 0x18) |
		     SUN4I_TVE_DAC1_AMPLITUDE(2, 0x18) |
		     SUN4I_TVE_DAC1_AMPLITUDE(3, 0x18));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_CB_CR_LVL_REG,
		     SUN4I_TVE_CB_CR_LVL_CB_BURST(tv_mode->burst_levels->cb) |
		     SUN4I_TVE_CB_CR_LVL_CR_BURST(tv_mode->burst_levels->cr));

	/* Set burst width क्रम a composite output */
	regmap_ग_लिखो(tv->regs, SUN4I_TVE_BURST_WIDTH_REG,
		     SUN4I_TVE_BURST_WIDTH_HSYNC_WIDTH(126) |
		     SUN4I_TVE_BURST_WIDTH_BURST_WIDTH(68) |
		     SUN4I_TVE_BURST_WIDTH_BREEZEWAY(22));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_CB_CR_GAIN_REG,
		     SUN4I_TVE_CB_CR_GAIN_CB(tv_mode->color_gains->cb) |
		     SUN4I_TVE_CB_CR_GAIN_CR(tv_mode->color_gains->cr));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_SYNC_VBI_REG,
		     SUN4I_TVE_SYNC_VBI_SYNC(0x10) |
		     SUN4I_TVE_SYNC_VBI_VBLANK(tv_mode->vblank_level));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_ACTIVE_LINE_REG,
		     SUN4I_TVE_ACTIVE_LINE(1440));

	/* Set composite chroma gain to 50 % */
	regmap_ग_लिखो(tv->regs, SUN4I_TVE_CHROMA_REG,
		     SUN4I_TVE_CHROMA_COMP_GAIN_50);

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_12C_REG,
		     SUN4I_TVE_12C_COMP_YUV_EN |
		     SUN4I_TVE_12C_NOTCH_WIDTH_WIDE);

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_RESYNC_REG,
		     SUN4I_TVE_RESYNC_PIXEL(tv_mode->resync_params->pixel) |
		     SUN4I_TVE_RESYNC_LINE(tv_mode->resync_params->line) |
		     (tv_mode->resync_params->field ?
		      SUN4I_TVE_RESYNC_FIELD : 0));

	regmap_ग_लिखो(tv->regs, SUN4I_TVE_SLAVE_REG, 0);
पूर्ण

अटल स्थिर काष्ठा drm_encoder_helper_funcs sun4i_tv_helper_funcs = अणु
	.disable	= sun4i_tv_disable,
	.enable		= sun4i_tv_enable,
	.mode_set	= sun4i_tv_mode_set,
पूर्ण;

अटल पूर्णांक sun4i_tv_comp_get_modes(काष्ठा drm_connector *connector)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(tv_modes); i++) अणु
		काष्ठा drm_display_mode *mode;
		स्थिर काष्ठा tv_mode *tv_mode = &tv_modes[i];

		mode = drm_mode_create(connector->dev);
		अगर (!mode) अणु
			DRM_ERROR("Failed to create a new display mode\n");
			वापस 0;
		पूर्ण

		म_नकल(mode->name, tv_mode->name);

		sun4i_tv_mode_to_drm_mode(tv_mode, mode);
		drm_mode_probed_add(connector, mode);
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक sun4i_tv_comp_mode_valid(काष्ठा drm_connector *connector,
				    काष्ठा drm_display_mode *mode)
अणु
	/* TODO */
	वापस MODE_OK;
पूर्ण

अटल स्थिर काष्ठा drm_connector_helper_funcs sun4i_tv_comp_connector_helper_funcs = अणु
	.get_modes	= sun4i_tv_comp_get_modes,
	.mode_valid	= sun4i_tv_comp_mode_valid,
पूर्ण;

अटल व्योम
sun4i_tv_comp_connector_destroy(काष्ठा drm_connector *connector)
अणु
	drm_connector_cleanup(connector);
पूर्ण

अटल स्थिर काष्ठा drm_connector_funcs sun4i_tv_comp_connector_funcs = अणु
	.fill_modes		= drm_helper_probe_single_connector_modes,
	.destroy		= sun4i_tv_comp_connector_destroy,
	.reset			= drm_atomic_helper_connector_reset,
	.atomic_duplicate_state	= drm_atomic_helper_connector_duplicate_state,
	.atomic_destroy_state	= drm_atomic_helper_connector_destroy_state,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun4i_tv_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= SUN4I_TVE_WSS_DATA2_REG,
	.name		= "tv-encoder",
पूर्ण;

अटल पूर्णांक sun4i_tv_bind(काष्ठा device *dev, काष्ठा device *master,
			 व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = data;
	काष्ठा sun4i_drv *drv = drm->dev_निजी;
	काष्ठा sun4i_tv *tv;
	काष्ठा resource *res;
	व्योम __iomem *regs;
	पूर्णांक ret;

	tv = devm_kzalloc(dev, माप(*tv), GFP_KERNEL);
	अगर (!tv)
		वापस -ENOMEM;
	tv->drv = drv;
	dev_set_drvdata(dev, tv);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(regs)) अणु
		dev_err(dev, "Couldn't map the TV encoder registers\n");
		वापस PTR_ERR(regs);
	पूर्ण

	tv->regs = devm_regmap_init_mmio(dev, regs,
					 &sun4i_tv_regmap_config);
	अगर (IS_ERR(tv->regs)) अणु
		dev_err(dev, "Couldn't create the TV encoder regmap\n");
		वापस PTR_ERR(tv->regs);
	पूर्ण

	tv->reset = devm_reset_control_get(dev, शून्य);
	अगर (IS_ERR(tv->reset)) अणु
		dev_err(dev, "Couldn't get our reset line\n");
		वापस PTR_ERR(tv->reset);
	पूर्ण

	ret = reset_control_deनिश्चित(tv->reset);
	अगर (ret) अणु
		dev_err(dev, "Couldn't deassert our reset line\n");
		वापस ret;
	पूर्ण

	tv->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(tv->clk)) अणु
		dev_err(dev, "Couldn't get the TV encoder clock\n");
		ret = PTR_ERR(tv->clk);
		जाओ err_निश्चित_reset;
	पूर्ण
	clk_prepare_enable(tv->clk);

	drm_encoder_helper_add(&tv->encoder,
			       &sun4i_tv_helper_funcs);
	ret = drm_simple_encoder_init(drm, &tv->encoder,
				      DRM_MODE_ENCODER_TVDAC);
	अगर (ret) अणु
		dev_err(dev, "Couldn't initialise the TV encoder\n");
		जाओ err_disable_clk;
	पूर्ण

	tv->encoder.possible_crtcs = drm_of_find_possible_crtcs(drm,
								dev->of_node);
	अगर (!tv->encoder.possible_crtcs) अणु
		ret = -EPROBE_DEFER;
		जाओ err_disable_clk;
	पूर्ण

	drm_connector_helper_add(&tv->connector,
				 &sun4i_tv_comp_connector_helper_funcs);
	ret = drm_connector_init(drm, &tv->connector,
				 &sun4i_tv_comp_connector_funcs,
				 DRM_MODE_CONNECTOR_Composite);
	अगर (ret) अणु
		dev_err(dev,
			"Couldn't initialise the Composite connector\n");
		जाओ err_cleanup_connector;
	पूर्ण
	tv->connector.पूर्णांकerlace_allowed = true;

	drm_connector_attach_encoder(&tv->connector, &tv->encoder);

	वापस 0;

err_cleanup_connector:
	drm_encoder_cleanup(&tv->encoder);
err_disable_clk:
	clk_disable_unprepare(tv->clk);
err_निश्चित_reset:
	reset_control_निश्चित(tv->reset);
	वापस ret;
पूर्ण

अटल व्योम sun4i_tv_unbind(काष्ठा device *dev, काष्ठा device *master,
			    व्योम *data)
अणु
	काष्ठा sun4i_tv *tv = dev_get_drvdata(dev);

	drm_connector_cleanup(&tv->connector);
	drm_encoder_cleanup(&tv->encoder);
	clk_disable_unprepare(tv->clk);
पूर्ण

अटल स्थिर काष्ठा component_ops sun4i_tv_ops = अणु
	.bind	= sun4i_tv_bind,
	.unbind	= sun4i_tv_unbind,
पूर्ण;

अटल पूर्णांक sun4i_tv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &sun4i_tv_ops);
पूर्ण

अटल पूर्णांक sun4i_tv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sun4i_tv_ops);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sun4i_tv_of_table[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-tv-encoder" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun4i_tv_of_table);

अटल काष्ठा platक्रमm_driver sun4i_tv_platक्रमm_driver = अणु
	.probe		= sun4i_tv_probe,
	.हटाओ		= sun4i_tv_हटाओ,
	.driver		= अणु
		.name		= "sun4i-tve",
		.of_match_table	= sun4i_tv_of_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun4i_tv_platक्रमm_driver);

MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_DESCRIPTION("Allwinner A10 TV Encoder Driver");
MODULE_LICENSE("GPL");
