<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/drivers/video/omap2/dss/dss_features.h
 *
 * Copyright (C) 2010 Texas Instruments
 * Author: Archit Taneja <archit@ti.com>
 */

#अगर_अघोषित __OMAP2_DSS_FEATURES_H
#घोषणा __OMAP2_DSS_FEATURES_H

#घोषणा MAX_DSS_MANAGERS	4
#घोषणा MAX_DSS_OVERLAYS	4
#घोषणा MAX_DSS_LCD_MANAGERS	3
#घोषणा MAX_NUM_DSI		2

/* DSS has feature id */
क्रमागत dss_feat_id अणु
	FEAT_LCDENABLEPOL,
	FEAT_LCDENABLESIGNAL,
	FEAT_PCKFREEENABLE,
	FEAT_FUNCGATED,
	FEAT_MGR_LCD2,
	FEAT_MGR_LCD3,
	FEAT_LINEBUFFERSPLIT,
	FEAT_ROWREPEATENABLE,
	FEAT_RESIZECONF,
	/* Independent core clk भागider */
	FEAT_CORE_CLK_DIV,
	FEAT_LCD_CLK_SRC,
	/* DSI-PLL घातer command 0x3 is not working */
	FEAT_DSI_PLL_PWR_BUG,
	FEAT_DSI_DCS_CMD_CONFIG_VC,
	FEAT_DSI_VC_OCP_WIDTH,
	FEAT_DSI_REVERSE_TXCLKESC,
	FEAT_DSI_GNQ,
	FEAT_DPI_USES_VDDS_DSI,
	FEAT_HDMI_CTS_SWMODE,
	FEAT_HDMI_AUDIO_USE_MCLK,
	FEAT_HANDLE_UV_SEPARATE,
	FEAT_ATTR2,
	FEAT_VENC_REQUIRES_TV_DAC_CLK,
	FEAT_CPR,
	FEAT_PRELOAD,
	FEAT_FIR_COEF_V,
	FEAT_ALPHA_FIXED_ZORDER,
	FEAT_ALPHA_FREE_ZORDER,
	FEAT_FIFO_MERGE,
	/* An unknown HW bug causing the normal FIFO thresholds not to work */
	FEAT_OMAP3_DSI_FIFO_BUG,
	FEAT_BURST_2D,
	FEAT_DSI_PHY_DCC,
	FEAT_MFLAG,
पूर्ण;

/* DSS रेजिस्टर field id */
क्रमागत dss_feat_reg_field अणु
	FEAT_REG_FIRHINC,
	FEAT_REG_FIRVINC,
	FEAT_REG_FIFOHIGHTHRESHOLD,
	FEAT_REG_FIFOLOWTHRESHOLD,
	FEAT_REG_FIFOSIZE,
	FEAT_REG_HORIZONTALACCU,
	FEAT_REG_VERTICALACCU,
	FEAT_REG_DISPC_CLK_SWITCH,
पूर्ण;

क्रमागत dss_range_param अणु
	FEAT_PARAM_DSS_FCK,
	FEAT_PARAM_DSS_PCD,
	FEAT_PARAM_DSIPLL_LPDIV,
	FEAT_PARAM_DSI_FCK,
	FEAT_PARAM_DOWNSCALE,
	FEAT_PARAM_LINEWIDTH,
पूर्ण;

/* DSS Feature Functions */
अचिन्हित दीर्घ dss_feat_get_param_min(क्रमागत dss_range_param param);
अचिन्हित दीर्घ dss_feat_get_param_max(क्रमागत dss_range_param param);
क्रमागत omap_overlay_caps dss_feat_get_overlay_caps(क्रमागत omap_plane plane);
bool dss_feat_color_mode_supported(क्रमागत omap_plane plane,
		क्रमागत omap_color_mode color_mode);
स्थिर अक्षर *dss_feat_get_clk_source_name(क्रमागत omap_dss_clk_source id);

u32 dss_feat_get_buffer_size_unit(व्योम);	/* in bytes */
u32 dss_feat_get_burst_size_unit(व्योम);		/* in bytes */

bool dss_feat_rotation_type_supported(क्रमागत omap_dss_rotation_type rot_type);

bool dss_has_feature(क्रमागत dss_feat_id id);
व्योम dss_feat_get_reg_field(क्रमागत dss_feat_reg_field id, u8 *start, u8 *end);
व्योम dss_features_init(क्रमागत omapdss_version version);

क्रमागत omap_display_type dss_feat_get_supported_displays(क्रमागत omap_channel channel);
क्रमागत omap_dss_output_id dss_feat_get_supported_outमाला_दो(क्रमागत omap_channel channel);

#पूर्ण_अगर
