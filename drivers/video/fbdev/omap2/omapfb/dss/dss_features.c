<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/dss_features.c
 *
 * Copyright (C) 2010 Texas Instruments
 * Author: Archit Taneja <archit@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

/* Defines a generic omap रेजिस्टर field */
काष्ठा dss_reg_field अणु
	u8 start, end;
पूर्ण;

काष्ठा dss_param_range अणु
	पूर्णांक min, max;
पूर्ण;

काष्ठा omap_dss_features अणु
	स्थिर काष्ठा dss_reg_field *reg_fields;
	स्थिर पूर्णांक num_reg_fields;

	स्थिर क्रमागत dss_feat_id *features;
	स्थिर पूर्णांक num_features;

	स्थिर पूर्णांक num_mgrs;
	स्थिर पूर्णांक num_ovls;
	स्थिर क्रमागत omap_display_type *supported_displays;
	स्थिर क्रमागत omap_dss_output_id *supported_outमाला_दो;
	स्थिर क्रमागत omap_color_mode *supported_color_modes;
	स्थिर क्रमागत omap_overlay_caps *overlay_caps;
	स्थिर अक्षर * स्थिर *clksrc_names;
	स्थिर काष्ठा dss_param_range *dss_params;

	स्थिर क्रमागत omap_dss_rotation_type supported_rotation_types;

	स्थिर u32 buffer_size_unit;
	स्थिर u32 burst_size_unit;
पूर्ण;

/* This काष्ठा is asचिन्हित to one of the below during initialization */
अटल स्थिर काष्ठा omap_dss_features *omap_current_dss_features;

अटल स्थिर काष्ठा dss_reg_field omap2_dss_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 11, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 27, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]		= अणु 8, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 24, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]			= अणु 8, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 9, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 25, 16 पूर्ण,
	[FEAT_REG_DISPC_CLK_SWITCH]		= अणु 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_reg_field omap3_dss_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 12, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 28, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]		= अणु 11, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 27, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]			= अणु 10, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 9, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 25, 16 पूर्ण,
	[FEAT_REG_DISPC_CLK_SWITCH]		= अणु 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_reg_field am43xx_dss_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 12, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 28, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]	= अणु 11, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 27, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]		= अणु 10, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 9, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 25, 16 पूर्ण,
	[FEAT_REG_DISPC_CLK_SWITCH]		= अणु 0, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_reg_field omap4_dss_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 12, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 28, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]		= अणु 15, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 31, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]			= अणु 15, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 10, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 26, 16 पूर्ण,
	[FEAT_REG_DISPC_CLK_SWITCH]		= अणु 9, 8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_reg_field omap5_dss_reg_fields[] = अणु
	[FEAT_REG_FIRHINC]			= अणु 12, 0 पूर्ण,
	[FEAT_REG_FIRVINC]			= अणु 28, 16 पूर्ण,
	[FEAT_REG_FIFOLOWTHRESHOLD]		= अणु 15, 0 पूर्ण,
	[FEAT_REG_FIFOHIGHTHRESHOLD]		= अणु 31, 16 पूर्ण,
	[FEAT_REG_FIFOSIZE]			= अणु 15, 0 पूर्ण,
	[FEAT_REG_HORIZONTALACCU]		= अणु 10, 0 पूर्ण,
	[FEAT_REG_VERTICALACCU]			= अणु 26, 16 पूर्ण,
	[FEAT_REG_DISPC_CLK_SWITCH]		= अणु 9, 7 पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type omap2_dss_supported_displays[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DISPLAY_TYPE_DPI | OMAP_DISPLAY_TYPE_DBI,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DISPLAY_TYPE_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type omap3430_dss_supported_displays[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DISPLAY_TYPE_DPI | OMAP_DISPLAY_TYPE_DBI |
	OMAP_DISPLAY_TYPE_SDI | OMAP_DISPLAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DISPLAY_TYPE_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type omap3630_dss_supported_displays[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DISPLAY_TYPE_DPI | OMAP_DISPLAY_TYPE_DBI |
	OMAP_DISPLAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DISPLAY_TYPE_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type am43xx_dss_supported_displays[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DISPLAY_TYPE_DPI | OMAP_DISPLAY_TYPE_DBI,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type omap4_dss_supported_displays[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DISPLAY_TYPE_DBI | OMAP_DISPLAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DISPLAY_TYPE_VENC | OMAP_DISPLAY_TYPE_HDMI,

	/* OMAP_DSS_CHANNEL_LCD2 */
	OMAP_DISPLAY_TYPE_DPI | OMAP_DISPLAY_TYPE_DBI |
	OMAP_DISPLAY_TYPE_DSI,
पूर्ण;

अटल स्थिर क्रमागत omap_display_type omap5_dss_supported_displays[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DISPLAY_TYPE_DPI | OMAP_DISPLAY_TYPE_DBI |
	OMAP_DISPLAY_TYPE_DSI,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DISPLAY_TYPE_HDMI | OMAP_DISPLAY_TYPE_DPI,

	/* OMAP_DSS_CHANNEL_LCD2 */
	OMAP_DISPLAY_TYPE_DPI | OMAP_DISPLAY_TYPE_DBI |
	OMAP_DISPLAY_TYPE_DSI,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap2_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap3430_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_SDI | OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap3630_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id am43xx_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap4_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DBI | OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_VENC | OMAP_DSS_OUTPUT_HDMI,

	/* OMAP_DSS_CHANNEL_LCD2 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI2,
पूर्ण;

अटल स्थिर क्रमागत omap_dss_output_id omap5_dss_supported_outमाला_दो[] = अणु
	/* OMAP_DSS_CHANNEL_LCD */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1 | OMAP_DSS_OUTPUT_DSI2,

	/* OMAP_DSS_CHANNEL_DIGIT */
	OMAP_DSS_OUTPUT_HDMI,

	/* OMAP_DSS_CHANNEL_LCD2 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI1,

	/* OMAP_DSS_CHANNEL_LCD3 */
	OMAP_DSS_OUTPUT_DPI | OMAP_DSS_OUTPUT_DBI |
	OMAP_DSS_OUTPUT_DSI2,
पूर्ण;

अटल स्थिर क्रमागत omap_color_mode omap2_dss_supported_color_modes[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_COLOR_CLUT1 | OMAP_DSS_COLOR_CLUT2 |
	OMAP_DSS_COLOR_CLUT4 | OMAP_DSS_COLOR_CLUT8 |
	OMAP_DSS_COLOR_RGB12U | OMAP_DSS_COLOR_RGB16 |
	OMAP_DSS_COLOR_RGB24U | OMAP_DSS_COLOR_RGB24P,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_YUV2 |
	OMAP_DSS_COLOR_UYVY,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_YUV2 |
	OMAP_DSS_COLOR_UYVY,
पूर्ण;

अटल स्थिर क्रमागत omap_color_mode omap3_dss_supported_color_modes[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_COLOR_CLUT1 | OMAP_DSS_COLOR_CLUT2 |
	OMAP_DSS_COLOR_CLUT4 | OMAP_DSS_COLOR_CLUT8 |
	OMAP_DSS_COLOR_RGB12U | OMAP_DSS_COLOR_ARGB16 |
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_ARGB32 |
	OMAP_DSS_COLOR_RGBA32 | OMAP_DSS_COLOR_RGBX32,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_COLOR_RGB24U | OMAP_DSS_COLOR_RGB24P |
	OMAP_DSS_COLOR_RGB12U | OMAP_DSS_COLOR_RGB16 |
	OMAP_DSS_COLOR_YUV2 | OMAP_DSS_COLOR_UYVY,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_COLOR_RGB12U | OMAP_DSS_COLOR_ARGB16 |
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_YUV2 |
	OMAP_DSS_COLOR_UYVY | OMAP_DSS_COLOR_ARGB32 |
	OMAP_DSS_COLOR_RGBA32 | OMAP_DSS_COLOR_RGBX32,
पूर्ण;

अटल स्थिर क्रमागत omap_color_mode omap4_dss_supported_color_modes[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_COLOR_CLUT1 | OMAP_DSS_COLOR_CLUT2 |
	OMAP_DSS_COLOR_CLUT4 | OMAP_DSS_COLOR_CLUT8 |
	OMAP_DSS_COLOR_RGB12U | OMAP_DSS_COLOR_ARGB16 |
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_ARGB32 |
	OMAP_DSS_COLOR_RGBA32 | OMAP_DSS_COLOR_RGBX32 |
	OMAP_DSS_COLOR_ARGB16_1555 | OMAP_DSS_COLOR_RGBX16 |
	OMAP_DSS_COLOR_RGBA16 | OMAP_DSS_COLOR_XRGB16_1555,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB12U |
	OMAP_DSS_COLOR_YUV2 | OMAP_DSS_COLOR_ARGB16_1555 |
	OMAP_DSS_COLOR_RGBA32 | OMAP_DSS_COLOR_NV12 |
	OMAP_DSS_COLOR_RGBA16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_UYVY |
	OMAP_DSS_COLOR_ARGB16 | OMAP_DSS_COLOR_XRGB16_1555 |
	OMAP_DSS_COLOR_ARGB32 | OMAP_DSS_COLOR_RGBX16 |
	OMAP_DSS_COLOR_RGBX32,

       /* OMAP_DSS_VIDEO2 */
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB12U |
	OMAP_DSS_COLOR_YUV2 | OMAP_DSS_COLOR_ARGB16_1555 |
	OMAP_DSS_COLOR_RGBA32 | OMAP_DSS_COLOR_NV12 |
	OMAP_DSS_COLOR_RGBA16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_UYVY |
	OMAP_DSS_COLOR_ARGB16 | OMAP_DSS_COLOR_XRGB16_1555 |
	OMAP_DSS_COLOR_ARGB32 | OMAP_DSS_COLOR_RGBX16 |
	OMAP_DSS_COLOR_RGBX32,

	/* OMAP_DSS_VIDEO3 */
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB12U |
	OMAP_DSS_COLOR_YUV2 | OMAP_DSS_COLOR_ARGB16_1555 |
	OMAP_DSS_COLOR_RGBA32 | OMAP_DSS_COLOR_NV12 |
	OMAP_DSS_COLOR_RGBA16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_UYVY |
	OMAP_DSS_COLOR_ARGB16 | OMAP_DSS_COLOR_XRGB16_1555 |
	OMAP_DSS_COLOR_ARGB32 | OMAP_DSS_COLOR_RGBX16 |
	OMAP_DSS_COLOR_RGBX32,

	/* OMAP_DSS_WB */
	OMAP_DSS_COLOR_RGB16 | OMAP_DSS_COLOR_RGB12U |
	OMAP_DSS_COLOR_YUV2 | OMAP_DSS_COLOR_ARGB16_1555 |
	OMAP_DSS_COLOR_RGBA32 | OMAP_DSS_COLOR_NV12 |
	OMAP_DSS_COLOR_RGBA16 | OMAP_DSS_COLOR_RGB24U |
	OMAP_DSS_COLOR_RGB24P | OMAP_DSS_COLOR_UYVY |
	OMAP_DSS_COLOR_ARGB16 | OMAP_DSS_COLOR_XRGB16_1555 |
	OMAP_DSS_COLOR_ARGB32 | OMAP_DSS_COLOR_RGBX16 |
	OMAP_DSS_COLOR_RGBX32,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap2_dss_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap3430_dss_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_GLOBAL_ALPHA | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap3630_dss_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_GLOBAL_ALPHA | OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

अटल स्थिर क्रमागत omap_overlay_caps omap4_dss_overlay_caps[] = अणु
	/* OMAP_DSS_GFX */
	OMAP_DSS_OVL_CAP_GLOBAL_ALPHA | OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA |
		OMAP_DSS_OVL_CAP_ZORDER | OMAP_DSS_OVL_CAP_POS |
		OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO1 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_ZORDER |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO2 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_ZORDER |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,

	/* OMAP_DSS_VIDEO3 */
	OMAP_DSS_OVL_CAP_SCALE | OMAP_DSS_OVL_CAP_GLOBAL_ALPHA |
		OMAP_DSS_OVL_CAP_PRE_MULT_ALPHA | OMAP_DSS_OVL_CAP_ZORDER |
		OMAP_DSS_OVL_CAP_POS | OMAP_DSS_OVL_CAP_REPLICATION,
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap2_dss_clk_source_names[] = अणु
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC]	= "N/A",
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI]	= "N/A",
	[OMAP_DSS_CLK_SRC_FCK]			= "DSS_FCLK1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap3_dss_clk_source_names[] = अणु
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC]	= "DSI1_PLL_FCLK",
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI]	= "DSI2_PLL_FCLK",
	[OMAP_DSS_CLK_SRC_FCK]			= "DSS1_ALWON_FCLK",
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap4_dss_clk_source_names[] = अणु
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC]	= "PLL1_CLK1",
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI]	= "PLL1_CLK2",
	[OMAP_DSS_CLK_SRC_FCK]			= "DSS_FCLK",
	[OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC]	= "PLL2_CLK1",
	[OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI]	= "PLL2_CLK2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर omap5_dss_clk_source_names[] = अणु
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC]	= "DPLL_DSI1_A_CLK1",
	[OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI]	= "DPLL_DSI1_A_CLK2",
	[OMAP_DSS_CLK_SRC_FCK]			= "DSS_CLK",
	[OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC]	= "DPLL_DSI1_C_CLK1",
	[OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI]	= "DPLL_DSI1_C_CLK2",
पूर्ण;

अटल स्थिर काष्ठा dss_param_range omap2_dss_param_range[] = अणु
	[FEAT_PARAM_DSS_FCK]			= अणु 0, 133000000 पूर्ण,
	[FEAT_PARAM_DSS_PCD]			= अणु 2, 255 पूर्ण,
	[FEAT_PARAM_DOWNSCALE]			= अणु 1, 2 पूर्ण,
	/*
	 * Assuming the line width buffer to be 768 pixels as OMAP2 DISPC
	 * scaler cannot scale a image with width more than 768.
	 */
	[FEAT_PARAM_LINEWIDTH]			= अणु 1, 768 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_param_range omap3_dss_param_range[] = अणु
	[FEAT_PARAM_DSS_FCK]			= अणु 0, 173000000 पूर्ण,
	[FEAT_PARAM_DSS_PCD]			= अणु 1, 255 पूर्ण,
	[FEAT_PARAM_DSIPLL_LPDIV]		= अणु 1, (1 << 13) - 1पूर्ण,
	[FEAT_PARAM_DSI_FCK]			= अणु 0, 173000000 पूर्ण,
	[FEAT_PARAM_DOWNSCALE]			= अणु 1, 4 पूर्ण,
	[FEAT_PARAM_LINEWIDTH]			= अणु 1, 1024 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_param_range am43xx_dss_param_range[] = अणु
	[FEAT_PARAM_DSS_FCK]			= अणु 0, 200000000 पूर्ण,
	[FEAT_PARAM_DSS_PCD]			= अणु 1, 255 पूर्ण,
	[FEAT_PARAM_DOWNSCALE]			= अणु 1, 4 पूर्ण,
	[FEAT_PARAM_LINEWIDTH]			= अणु 1, 1024 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_param_range omap4_dss_param_range[] = अणु
	[FEAT_PARAM_DSS_FCK]			= अणु 0, 186000000 पूर्ण,
	[FEAT_PARAM_DSS_PCD]			= अणु 1, 255 पूर्ण,
	[FEAT_PARAM_DSIPLL_LPDIV]		= अणु 0, (1 << 13) - 1 पूर्ण,
	[FEAT_PARAM_DSI_FCK]			= अणु 0, 170000000 पूर्ण,
	[FEAT_PARAM_DOWNSCALE]			= अणु 1, 4 पूर्ण,
	[FEAT_PARAM_LINEWIDTH]			= अणु 1, 2048 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dss_param_range omap5_dss_param_range[] = अणु
	[FEAT_PARAM_DSS_FCK]			= अणु 0, 209250000 पूर्ण,
	[FEAT_PARAM_DSS_PCD]			= अणु 1, 255 पूर्ण,
	[FEAT_PARAM_DSIPLL_LPDIV]		= अणु 0, (1 << 13) - 1 पूर्ण,
	[FEAT_PARAM_DSI_FCK]			= अणु 0, 209250000 पूर्ण,
	[FEAT_PARAM_DOWNSCALE]			= अणु 1, 4 पूर्ण,
	[FEAT_PARAM_LINEWIDTH]			= अणु 1, 2048 पूर्ण,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id omap2_dss_feat_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id omap3430_dss_feat_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	FEAT_DSI_REVERSE_TXCLKESC,
	FEAT_VENC_REQUIRES_TV_DAC_CLK,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_DPI_USES_VDDS_DSI,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id am35xx_dss_feat_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	FEAT_DSI_REVERSE_TXCLKESC,
	FEAT_VENC_REQUIRES_TV_DAC_CLK,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id am43xx_dss_feat_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_FIFO_MERGE,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id omap3630_dss_feat_list[] = अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	FEAT_DSI_PLL_PWR_BUG,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_DPI_USES_VDDS_DSI,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id omap4430_es1_0_dss_feat_list[] = अणु
	FEAT_MGR_LCD2,
	FEAT_CORE_CLK_DIV,
	FEAT_LCD_CLK_SRC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_BURST_2D,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id omap4430_es2_0_1_2_dss_feat_list[] = अणु
	FEAT_MGR_LCD2,
	FEAT_CORE_CLK_DIV,
	FEAT_LCD_CLK_SRC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_BURST_2D,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id omap4_dss_feat_list[] = अणु
	FEAT_MGR_LCD2,
	FEAT_CORE_CLK_DIV,
	FEAT_LCD_CLK_SRC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HDMI_AUDIO_USE_MCLK,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_BURST_2D,
पूर्ण;

अटल स्थिर क्रमागत dss_feat_id omap5_dss_feat_list[] = अणु
	FEAT_MGR_LCD2,
	FEAT_MGR_LCD3,
	FEAT_CORE_CLK_DIV,
	FEAT_LCD_CLK_SRC,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_GNQ,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HDMI_AUDIO_USE_MCLK,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	FEAT_BURST_2D,
	FEAT_DSI_PHY_DCC,
	FEAT_MFLAG,
पूर्ण;

/* OMAP2 DSS Features */
अटल स्थिर काष्ठा omap_dss_features omap2_dss_features = अणु
	.reg_fields = omap2_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap2_dss_reg_fields),

	.features = omap2_dss_feat_list,
	.num_features = ARRAY_SIZE(omap2_dss_feat_list),

	.num_mgrs = 2,
	.num_ovls = 3,
	.supported_displays = omap2_dss_supported_displays,
	.supported_outमाला_दो = omap2_dss_supported_outमाला_दो,
	.supported_color_modes = omap2_dss_supported_color_modes,
	.overlay_caps = omap2_dss_overlay_caps,
	.clksrc_names = omap2_dss_clk_source_names,
	.dss_params = omap2_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_VRFB,
	.buffer_size_unit = 1,
	.burst_size_unit = 8,
पूर्ण;

/* OMAP3 DSS Features */
अटल स्थिर काष्ठा omap_dss_features omap3430_dss_features = अणु
	.reg_fields = omap3_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap3_dss_reg_fields),

	.features = omap3430_dss_feat_list,
	.num_features = ARRAY_SIZE(omap3430_dss_feat_list),

	.num_mgrs = 2,
	.num_ovls = 3,
	.supported_displays = omap3430_dss_supported_displays,
	.supported_outमाला_दो = omap3430_dss_supported_outमाला_दो,
	.supported_color_modes = omap3_dss_supported_color_modes,
	.overlay_caps = omap3430_dss_overlay_caps,
	.clksrc_names = omap3_dss_clk_source_names,
	.dss_params = omap3_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_VRFB,
	.buffer_size_unit = 1,
	.burst_size_unit = 8,
पूर्ण;

/*
 * AM35xx DSS Features. This is basically OMAP3 DSS Features without the
 * vdds_dsi regulator.
 */
अटल स्थिर काष्ठा omap_dss_features am35xx_dss_features = अणु
	.reg_fields = omap3_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap3_dss_reg_fields),

	.features = am35xx_dss_feat_list,
	.num_features = ARRAY_SIZE(am35xx_dss_feat_list),

	.num_mgrs = 2,
	.num_ovls = 3,
	.supported_displays = omap3430_dss_supported_displays,
	.supported_outमाला_दो = omap3430_dss_supported_outमाला_दो,
	.supported_color_modes = omap3_dss_supported_color_modes,
	.overlay_caps = omap3430_dss_overlay_caps,
	.clksrc_names = omap3_dss_clk_source_names,
	.dss_params = omap3_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_VRFB,
	.buffer_size_unit = 1,
	.burst_size_unit = 8,
पूर्ण;

अटल स्थिर काष्ठा omap_dss_features am43xx_dss_features = अणु
	.reg_fields = am43xx_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(am43xx_dss_reg_fields),

	.features = am43xx_dss_feat_list,
	.num_features = ARRAY_SIZE(am43xx_dss_feat_list),

	.num_mgrs = 1,
	.num_ovls = 3,
	.supported_displays = am43xx_dss_supported_displays,
	.supported_outमाला_दो = am43xx_dss_supported_outमाला_दो,
	.supported_color_modes = omap3_dss_supported_color_modes,
	.overlay_caps = omap3430_dss_overlay_caps,
	.clksrc_names = omap2_dss_clk_source_names,
	.dss_params = am43xx_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA,
	.buffer_size_unit = 1,
	.burst_size_unit = 8,
पूर्ण;

अटल स्थिर काष्ठा omap_dss_features omap3630_dss_features = अणु
	.reg_fields = omap3_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap3_dss_reg_fields),

	.features = omap3630_dss_feat_list,
	.num_features = ARRAY_SIZE(omap3630_dss_feat_list),

	.num_mgrs = 2,
	.num_ovls = 3,
	.supported_displays = omap3630_dss_supported_displays,
	.supported_outमाला_दो = omap3630_dss_supported_outमाला_दो,
	.supported_color_modes = omap3_dss_supported_color_modes,
	.overlay_caps = omap3630_dss_overlay_caps,
	.clksrc_names = omap3_dss_clk_source_names,
	.dss_params = omap3_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_VRFB,
	.buffer_size_unit = 1,
	.burst_size_unit = 8,
पूर्ण;

/* OMAP4 DSS Features */
/* For OMAP4430 ES 1.0 revision */
अटल स्थिर काष्ठा omap_dss_features omap4430_es1_0_dss_features  = अणु
	.reg_fields = omap4_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap4_dss_reg_fields),

	.features = omap4430_es1_0_dss_feat_list,
	.num_features = ARRAY_SIZE(omap4430_es1_0_dss_feat_list),

	.num_mgrs = 3,
	.num_ovls = 4,
	.supported_displays = omap4_dss_supported_displays,
	.supported_outमाला_दो = omap4_dss_supported_outमाला_दो,
	.supported_color_modes = omap4_dss_supported_color_modes,
	.overlay_caps = omap4_dss_overlay_caps,
	.clksrc_names = omap4_dss_clk_source_names,
	.dss_params = omap4_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_TILER,
	.buffer_size_unit = 16,
	.burst_size_unit = 16,
पूर्ण;

/* For OMAP4430 ES 2.0, 2.1 and 2.2 revisions */
अटल स्थिर काष्ठा omap_dss_features omap4430_es2_0_1_2_dss_features = अणु
	.reg_fields = omap4_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap4_dss_reg_fields),

	.features = omap4430_es2_0_1_2_dss_feat_list,
	.num_features = ARRAY_SIZE(omap4430_es2_0_1_2_dss_feat_list),

	.num_mgrs = 3,
	.num_ovls = 4,
	.supported_displays = omap4_dss_supported_displays,
	.supported_outमाला_दो = omap4_dss_supported_outमाला_दो,
	.supported_color_modes = omap4_dss_supported_color_modes,
	.overlay_caps = omap4_dss_overlay_caps,
	.clksrc_names = omap4_dss_clk_source_names,
	.dss_params = omap4_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_TILER,
	.buffer_size_unit = 16,
	.burst_size_unit = 16,
पूर्ण;

/* For all the other OMAP4 versions */
अटल स्थिर काष्ठा omap_dss_features omap4_dss_features = अणु
	.reg_fields = omap4_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap4_dss_reg_fields),

	.features = omap4_dss_feat_list,
	.num_features = ARRAY_SIZE(omap4_dss_feat_list),

	.num_mgrs = 3,
	.num_ovls = 4,
	.supported_displays = omap4_dss_supported_displays,
	.supported_outमाला_दो = omap4_dss_supported_outमाला_दो,
	.supported_color_modes = omap4_dss_supported_color_modes,
	.overlay_caps = omap4_dss_overlay_caps,
	.clksrc_names = omap4_dss_clk_source_names,
	.dss_params = omap4_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_TILER,
	.buffer_size_unit = 16,
	.burst_size_unit = 16,
पूर्ण;

/* OMAP5 DSS Features */
अटल स्थिर काष्ठा omap_dss_features omap5_dss_features = अणु
	.reg_fields = omap5_dss_reg_fields,
	.num_reg_fields = ARRAY_SIZE(omap5_dss_reg_fields),

	.features = omap5_dss_feat_list,
	.num_features = ARRAY_SIZE(omap5_dss_feat_list),

	.num_mgrs = 4,
	.num_ovls = 4,
	.supported_displays = omap5_dss_supported_displays,
	.supported_outमाला_दो = omap5_dss_supported_outमाला_दो,
	.supported_color_modes = omap4_dss_supported_color_modes,
	.overlay_caps = omap4_dss_overlay_caps,
	.clksrc_names = omap5_dss_clk_source_names,
	.dss_params = omap5_dss_param_range,
	.supported_rotation_types = OMAP_DSS_ROT_DMA | OMAP_DSS_ROT_TILER,
	.buffer_size_unit = 16,
	.burst_size_unit = 16,
पूर्ण;

/* Functions वापसing values related to a DSS feature */
पूर्णांक dss_feat_get_num_mgrs(व्योम)
अणु
	वापस omap_current_dss_features->num_mgrs;
पूर्ण
EXPORT_SYMBOL(dss_feat_get_num_mgrs);

पूर्णांक dss_feat_get_num_ovls(व्योम)
अणु
	वापस omap_current_dss_features->num_ovls;
पूर्ण
EXPORT_SYMBOL(dss_feat_get_num_ovls);

अचिन्हित दीर्घ dss_feat_get_param_min(क्रमागत dss_range_param param)
अणु
	वापस omap_current_dss_features->dss_params[param].min;
पूर्ण

अचिन्हित दीर्घ dss_feat_get_param_max(क्रमागत dss_range_param param)
अणु
	वापस omap_current_dss_features->dss_params[param].max;
पूर्ण

क्रमागत omap_display_type dss_feat_get_supported_displays(क्रमागत omap_channel channel)
अणु
	वापस omap_current_dss_features->supported_displays[channel];
पूर्ण

क्रमागत omap_dss_output_id dss_feat_get_supported_outमाला_दो(क्रमागत omap_channel channel)
अणु
	वापस omap_current_dss_features->supported_outमाला_दो[channel];
पूर्ण

क्रमागत omap_color_mode dss_feat_get_supported_color_modes(क्रमागत omap_plane plane)
अणु
	वापस omap_current_dss_features->supported_color_modes[plane];
पूर्ण
EXPORT_SYMBOL(dss_feat_get_supported_color_modes);

क्रमागत omap_overlay_caps dss_feat_get_overlay_caps(क्रमागत omap_plane plane)
अणु
	वापस omap_current_dss_features->overlay_caps[plane];
पूर्ण

bool dss_feat_color_mode_supported(क्रमागत omap_plane plane,
		क्रमागत omap_color_mode color_mode)
अणु
	वापस omap_current_dss_features->supported_color_modes[plane] &
			color_mode;
पूर्ण

स्थिर अक्षर *dss_feat_get_clk_source_name(क्रमागत omap_dss_clk_source id)
अणु
	वापस omap_current_dss_features->clksrc_names[id];
पूर्ण

u32 dss_feat_get_buffer_size_unit(व्योम)
अणु
	वापस omap_current_dss_features->buffer_size_unit;
पूर्ण

u32 dss_feat_get_burst_size_unit(व्योम)
अणु
	वापस omap_current_dss_features->burst_size_unit;
पूर्ण

/* DSS has_feature check */
bool dss_has_feature(क्रमागत dss_feat_id id)
अणु
	पूर्णांक i;
	स्थिर क्रमागत dss_feat_id *features = omap_current_dss_features->features;
	स्थिर पूर्णांक num_features = omap_current_dss_features->num_features;

	क्रम (i = 0; i < num_features; i++) अणु
		अगर (features[i] == id)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम dss_feat_get_reg_field(क्रमागत dss_feat_reg_field id, u8 *start, u8 *end)
अणु
	BUG_ON(id >= omap_current_dss_features->num_reg_fields);

	*start = omap_current_dss_features->reg_fields[id].start;
	*end = omap_current_dss_features->reg_fields[id].end;
पूर्ण

bool dss_feat_rotation_type_supported(क्रमागत omap_dss_rotation_type rot_type)
अणु
	वापस omap_current_dss_features->supported_rotation_types & rot_type;
पूर्ण

व्योम dss_features_init(क्रमागत omapdss_version version)
अणु
	चयन (version) अणु
	हाल OMAPDSS_VER_OMAP24xx:
		omap_current_dss_features = &omap2_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_OMAP34xx_ES1:
	हाल OMAPDSS_VER_OMAP34xx_ES3:
		omap_current_dss_features = &omap3430_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_OMAP3630:
		omap_current_dss_features = &omap3630_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_OMAP4430_ES1:
		omap_current_dss_features = &omap4430_es1_0_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_OMAP4430_ES2:
		omap_current_dss_features = &omap4430_es2_0_1_2_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_OMAP4:
		omap_current_dss_features = &omap4_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_OMAP5:
	हाल OMAPDSS_VER_DRA7xx:
		omap_current_dss_features = &omap5_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_AM35xx:
		omap_current_dss_features = &am35xx_dss_features;
		अवरोध;

	हाल OMAPDSS_VER_AM43xx:
		omap_current_dss_features = &am43xx_dss_features;
		अवरोध;

	शेष:
		DSSWARN("Unsupported OMAP version");
		अवरोध;
	पूर्ण
पूर्ण
