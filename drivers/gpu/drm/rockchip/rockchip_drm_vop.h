<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#अगर_अघोषित _ROCKCHIP_DRM_VOP_H
#घोषणा _ROCKCHIP_DRM_VOP_H

/*
 * major: IP major version, used क्रम IP काष्ठाure
 * minor: big feature change under same काष्ठाure
 */
#घोषणा VOP_VERSION(major, minor)	((major) << 8 | (minor))
#घोषणा VOP_MAJOR(version)		((version) >> 8)
#घोषणा VOP_MINOR(version)		((version) & 0xff)

#घोषणा NUM_YUV2YUV_COEFFICIENTS 12

/* AFBC supports a number of configurable modes. Relevant to us is block size
 * (16x16 or 32x8), storage modअगरiers (SPARSE, SPLIT), and the YUV-like
 * colourspace transक्रमm (YTR). 16x16 SPARSE mode is always used. SPLIT mode
 * could be enabled via the hreg_block_split रेजिस्टर, but is not currently
 * handled. The colourspace transक्रमm is implicitly always assumed by the
 * decoder, so consumers must use this transक्रमm as well.
 *
 * Failure to match modअगरiers will cause errors displaying AFBC buffers
 * produced by conक्रमmant AFBC producers, including Mesa.
 */
#घोषणा ROCKCHIP_AFBC_MOD \
	DRM_FORMAT_MOD_ARM_AFBC( \
		AFBC_FORMAT_MOD_BLOCK_SIZE_16x16 | AFBC_FORMAT_MOD_SPARSE \
			| AFBC_FORMAT_MOD_YTR \
	)

क्रमागत vop_data_क्रमmat अणु
	VOP_FMT_ARGB8888 = 0,
	VOP_FMT_RGB888,
	VOP_FMT_RGB565,
	VOP_FMT_YUV420SP = 4,
	VOP_FMT_YUV422SP,
	VOP_FMT_YUV444SP,
पूर्ण;

काष्ठा vop_reg अणु
	uपूर्णांक32_t mask;
	uपूर्णांक16_t offset;
	uपूर्णांक8_t shअगरt;
	bool ग_लिखो_mask;
	bool relaxed;
पूर्ण;

काष्ठा vop_afbc अणु
	काष्ठा vop_reg enable;
	काष्ठा vop_reg win_sel;
	काष्ठा vop_reg क्रमmat;
	काष्ठा vop_reg hreg_block_split;
	काष्ठा vop_reg pic_size;
	काष्ठा vop_reg hdr_ptr;
	काष्ठा vop_reg rstn;
पूर्ण;

काष्ठा vop_modeset अणु
	काष्ठा vop_reg htotal_pw;
	काष्ठा vop_reg hact_st_end;
	काष्ठा vop_reg hpost_st_end;
	काष्ठा vop_reg vtotal_pw;
	काष्ठा vop_reg vact_st_end;
	काष्ठा vop_reg vpost_st_end;
पूर्ण;

काष्ठा vop_output अणु
	काष्ठा vop_reg pin_pol;
	काष्ठा vop_reg dp_pin_pol;
	काष्ठा vop_reg dp_dclk_pol;
	काष्ठा vop_reg edp_pin_pol;
	काष्ठा vop_reg edp_dclk_pol;
	काष्ठा vop_reg hdmi_pin_pol;
	काष्ठा vop_reg hdmi_dclk_pol;
	काष्ठा vop_reg mipi_pin_pol;
	काष्ठा vop_reg mipi_dclk_pol;
	काष्ठा vop_reg rgb_pin_pol;
	काष्ठा vop_reg rgb_dclk_pol;
	काष्ठा vop_reg dp_en;
	काष्ठा vop_reg edp_en;
	काष्ठा vop_reg hdmi_en;
	काष्ठा vop_reg mipi_en;
	काष्ठा vop_reg mipi_dual_channel_en;
	काष्ठा vop_reg rgb_en;
पूर्ण;

काष्ठा vop_common अणु
	काष्ठा vop_reg cfg_करोne;
	काष्ठा vop_reg dsp_blank;
	काष्ठा vop_reg data_blank;
	काष्ठा vop_reg pre_dither_करोwn;
	काष्ठा vop_reg dither_करोwn_sel;
	काष्ठा vop_reg dither_करोwn_mode;
	काष्ठा vop_reg dither_करोwn_en;
	काष्ठा vop_reg dither_up;
	काष्ठा vop_reg dsp_lut_en;
	काष्ठा vop_reg gate_en;
	काष्ठा vop_reg mmu_en;
	काष्ठा vop_reg out_mode;
	काष्ठा vop_reg standby;
पूर्ण;

काष्ठा vop_misc अणु
	काष्ठा vop_reg global_regकरोne_en;
पूर्ण;

काष्ठा vop_पूर्णांकr अणु
	स्थिर पूर्णांक *पूर्णांकrs;
	uपूर्णांक32_t nपूर्णांकrs;

	काष्ठा vop_reg line_flag_num[2];
	काष्ठा vop_reg enable;
	काष्ठा vop_reg clear;
	काष्ठा vop_reg status;
पूर्ण;

काष्ठा vop_scl_extension अणु
	काष्ठा vop_reg cbcr_vsd_mode;
	काष्ठा vop_reg cbcr_vsu_mode;
	काष्ठा vop_reg cbcr_hsd_mode;
	काष्ठा vop_reg cbcr_ver_scl_mode;
	काष्ठा vop_reg cbcr_hor_scl_mode;
	काष्ठा vop_reg yrgb_vsd_mode;
	काष्ठा vop_reg yrgb_vsu_mode;
	काष्ठा vop_reg yrgb_hsd_mode;
	काष्ठा vop_reg yrgb_ver_scl_mode;
	काष्ठा vop_reg yrgb_hor_scl_mode;
	काष्ठा vop_reg line_load_mode;
	काष्ठा vop_reg cbcr_axi_gather_num;
	काष्ठा vop_reg yrgb_axi_gather_num;
	काष्ठा vop_reg vsd_cbcr_gt2;
	काष्ठा vop_reg vsd_cbcr_gt4;
	काष्ठा vop_reg vsd_yrgb_gt2;
	काष्ठा vop_reg vsd_yrgb_gt4;
	काष्ठा vop_reg bic_coe_sel;
	काष्ठा vop_reg cbcr_axi_gather_en;
	काष्ठा vop_reg yrgb_axi_gather_en;
	काष्ठा vop_reg lb_mode;
पूर्ण;

काष्ठा vop_scl_regs अणु
	स्थिर काष्ठा vop_scl_extension *ext;

	काष्ठा vop_reg scale_yrgb_x;
	काष्ठा vop_reg scale_yrgb_y;
	काष्ठा vop_reg scale_cbcr_x;
	काष्ठा vop_reg scale_cbcr_y;
पूर्ण;

काष्ठा vop_yuv2yuv_phy अणु
	काष्ठा vop_reg y2r_coefficients[NUM_YUV2YUV_COEFFICIENTS];
पूर्ण;

काष्ठा vop_win_phy अणु
	स्थिर काष्ठा vop_scl_regs *scl;
	स्थिर uपूर्णांक32_t *data_क्रमmats;
	uपूर्णांक32_t nक्रमmats;
	स्थिर uपूर्णांक64_t *क्रमmat_modअगरiers;

	काष्ठा vop_reg enable;
	काष्ठा vop_reg gate;
	काष्ठा vop_reg क्रमmat;
	काष्ठा vop_reg rb_swap;
	काष्ठा vop_reg act_info;
	काष्ठा vop_reg dsp_info;
	काष्ठा vop_reg dsp_st;
	काष्ठा vop_reg yrgb_mst;
	काष्ठा vop_reg uv_mst;
	काष्ठा vop_reg yrgb_vir;
	काष्ठा vop_reg uv_vir;
	काष्ठा vop_reg y_mir_en;
	काष्ठा vop_reg x_mir_en;

	काष्ठा vop_reg dst_alpha_ctl;
	काष्ठा vop_reg src_alpha_ctl;
	काष्ठा vop_reg alpha_pre_mul;
	काष्ठा vop_reg alpha_mode;
	काष्ठा vop_reg alpha_en;
	काष्ठा vop_reg channel;
पूर्ण;

काष्ठा vop_win_yuv2yuv_data अणु
	uपूर्णांक32_t base;
	स्थिर काष्ठा vop_yuv2yuv_phy *phy;
	काष्ठा vop_reg y2r_en;
पूर्ण;

काष्ठा vop_win_data अणु
	uपूर्णांक32_t base;
	स्थिर काष्ठा vop_win_phy *phy;
	क्रमागत drm_plane_type type;
पूर्ण;

काष्ठा vop_data अणु
	uपूर्णांक32_t version;
	स्थिर काष्ठा vop_पूर्णांकr *पूर्णांकr;
	स्थिर काष्ठा vop_common *common;
	स्थिर काष्ठा vop_misc *misc;
	स्थिर काष्ठा vop_modeset *modeset;
	स्थिर काष्ठा vop_output *output;
	स्थिर काष्ठा vop_afbc *afbc;
	स्थिर काष्ठा vop_win_yuv2yuv_data *win_yuv2yuv;
	स्थिर काष्ठा vop_win_data *win;
	अचिन्हित पूर्णांक win_size;
	अचिन्हित पूर्णांक lut_size;

#घोषणा VOP_FEATURE_OUTPUT_RGB10	BIT(0)
#घोषणा VOP_FEATURE_INTERNAL_RGB	BIT(1)
	u64 feature;
पूर्ण;

/* पूर्णांकerrupt define */
#घोषणा DSP_HOLD_VALID_INTR		(1 << 0)
#घोषणा FS_INTR				(1 << 1)
#घोषणा LINE_FLAG_INTR			(1 << 2)
#घोषणा BUS_ERROR_INTR			(1 << 3)

#घोषणा INTR_MASK			(DSP_HOLD_VALID_INTR | FS_INTR | \
					 LINE_FLAG_INTR | BUS_ERROR_INTR)

#घोषणा DSP_HOLD_VALID_INTR_EN(x)	((x) << 4)
#घोषणा FS_INTR_EN(x)			((x) << 5)
#घोषणा LINE_FLAG_INTR_EN(x)		((x) << 6)
#घोषणा BUS_ERROR_INTR_EN(x)		((x) << 7)
#घोषणा DSP_HOLD_VALID_INTR_MASK	(1 << 4)
#घोषणा FS_INTR_MASK			(1 << 5)
#घोषणा LINE_FLAG_INTR_MASK		(1 << 6)
#घोषणा BUS_ERROR_INTR_MASK		(1 << 7)

#घोषणा INTR_CLR_SHIFT			8
#घोषणा DSP_HOLD_VALID_INTR_CLR		(1 << (INTR_CLR_SHIFT + 0))
#घोषणा FS_INTR_CLR			(1 << (INTR_CLR_SHIFT + 1))
#घोषणा LINE_FLAG_INTR_CLR		(1 << (INTR_CLR_SHIFT + 2))
#घोषणा BUS_ERROR_INTR_CLR		(1 << (INTR_CLR_SHIFT + 3))

#घोषणा DSP_LINE_NUM(x)			(((x) & 0x1fff) << 12)
#घोषणा DSP_LINE_NUM_MASK		(0x1fff << 12)

/* src alpha ctrl define */
#घोषणा SRC_FADING_VALUE(x)		(((x) & 0xff) << 24)
#घोषणा SRC_GLOBAL_ALPHA(x)		(((x) & 0xff) << 16)
#घोषणा SRC_FACTOR_M0(x)		(((x) & 0x7) << 6)
#घोषणा SRC_ALPHA_CAL_M0(x)		(((x) & 0x1) << 5)
#घोषणा SRC_BLEND_M0(x)			(((x) & 0x3) << 3)
#घोषणा SRC_ALPHA_M0(x)			(((x) & 0x1) << 2)
#घोषणा SRC_COLOR_M0(x)			(((x) & 0x1) << 1)
#घोषणा SRC_ALPHA_EN(x)			(((x) & 0x1) << 0)
/* dst alpha ctrl define */
#घोषणा DST_FACTOR_M0(x)		(((x) & 0x7) << 6)

/*
 * display output पूर्णांकerface supported by rockchip lcdc
 */
#घोषणा ROCKCHIP_OUT_MODE_P888	0
#घोषणा ROCKCHIP_OUT_MODE_P666	1
#घोषणा ROCKCHIP_OUT_MODE_P565	2
/* क्रम use special outface */
#घोषणा ROCKCHIP_OUT_MODE_AAAA	15

/* output flags */
#घोषणा ROCKCHIP_OUTPUT_DSI_DUAL	BIT(0)

क्रमागत alpha_mode अणु
	ALPHA_STRAIGHT,
	ALPHA_INVERSE,
पूर्ण;

क्रमागत global_blend_mode अणु
	ALPHA_GLOBAL,
	ALPHA_PER_PIX,
	ALPHA_PER_PIX_GLOBAL,
पूर्ण;

क्रमागत alpha_cal_mode अणु
	ALPHA_SATURATION,
	ALPHA_NO_SATURATION,
पूर्ण;

क्रमागत color_mode अणु
	ALPHA_SRC_PRE_MUL,
	ALPHA_SRC_NO_PRE_MUL,
पूर्ण;

क्रमागत factor_mode अणु
	ALPHA_ZERO,
	ALPHA_ONE,
	ALPHA_SRC,
	ALPHA_SRC_INVERSE,
	ALPHA_SRC_GLOBAL,
पूर्ण;

क्रमागत scale_mode अणु
	SCALE_NONE = 0x0,
	SCALE_UP   = 0x1,
	SCALE_DOWN = 0x2
पूर्ण;

क्रमागत lb_mode अणु
	LB_YUV_3840X5 = 0x0,
	LB_YUV_2560X8 = 0x1,
	LB_RGB_3840X2 = 0x2,
	LB_RGB_2560X4 = 0x3,
	LB_RGB_1920X5 = 0x4,
	LB_RGB_1280X8 = 0x5
पूर्ण;

क्रमागत sacle_up_mode अणु
	SCALE_UP_BIL = 0x0,
	SCALE_UP_BIC = 0x1
पूर्ण;

क्रमागत scale_करोwn_mode अणु
	SCALE_DOWN_BIL = 0x0,
	SCALE_DOWN_AVG = 0x1
पूर्ण;

क्रमागत dither_करोwn_mode अणु
	RGB888_TO_RGB565 = 0x0,
	RGB888_TO_RGB666 = 0x1
पूर्ण;

क्रमागत dither_करोwn_mode_sel अणु
	DITHER_DOWN_ALLEGRO = 0x0,
	DITHER_DOWN_FRC = 0x1
पूर्ण;

क्रमागत vop_pol अणु
	HSYNC_POSITIVE = 0,
	VSYNC_POSITIVE = 1,
	DEN_NEGATIVE   = 2
पूर्ण;

#घोषणा FRAC_16_16(mult, भाग)    (((mult) << 16) / (भाग))
#घोषणा SCL_FT_DEFAULT_FIXPOINT_SHIFT	12
#घोषणा SCL_MAX_VSKIPLINES		4
#घोषणा MIN_SCL_FT_AFTER_VSKIP		1

अटल अंतरभूत uपूर्णांक16_t scl_cal_scale(पूर्णांक src, पूर्णांक dst, पूर्णांक shअगरt)
अणु
	वापस ((src * 2 - 3) << (shअगरt - 1)) / (dst - 1);
पूर्ण

अटल अंतरभूत uपूर्णांक16_t scl_cal_scale2(पूर्णांक src, पूर्णांक dst)
अणु
	वापस ((src - 1) << 12) / (dst - 1);
पूर्ण

#घोषणा GET_SCL_FT_BILI_DN(src, dst)	scl_cal_scale(src, dst, 12)
#घोषणा GET_SCL_FT_BILI_UP(src, dst)	scl_cal_scale(src, dst, 16)
#घोषणा GET_SCL_FT_BIC(src, dst)	scl_cal_scale(src, dst, 16)

अटल अंतरभूत uपूर्णांक16_t scl_get_bili_dn_vskip(पूर्णांक src_h, पूर्णांक dst_h,
					     पूर्णांक vskiplines)
अणु
	पूर्णांक act_height;

	act_height = DIV_ROUND_UP(src_h, vskiplines);

	अगर (act_height == dst_h)
		वापस GET_SCL_FT_BILI_DN(src_h, dst_h) / vskiplines;

	वापस GET_SCL_FT_BILI_DN(act_height, dst_h);
पूर्ण

अटल अंतरभूत क्रमागत scale_mode scl_get_scl_mode(पूर्णांक src, पूर्णांक dst)
अणु
	अगर (src < dst)
		वापस SCALE_UP;
	अन्यथा अगर (src > dst)
		वापस SCALE_DOWN;

	वापस SCALE_NONE;
पूर्ण

अटल अंतरभूत पूर्णांक scl_get_vskiplines(uपूर्णांक32_t srch, uपूर्णांक32_t dsth)
अणु
	uपूर्णांक32_t vskiplines;

	क्रम (vskiplines = SCL_MAX_VSKIPLINES; vskiplines > 1; vskiplines /= 2)
		अगर (srch >= vskiplines * dsth * MIN_SCL_FT_AFTER_VSKIP)
			अवरोध;

	वापस vskiplines;
पूर्ण

अटल अंतरभूत पूर्णांक scl_vop_cal_lb_mode(पूर्णांक width, bool is_yuv)
अणु
	पूर्णांक lb_mode;

	अगर (is_yuv) अणु
		अगर (width > 1280)
			lb_mode = LB_YUV_3840X5;
		अन्यथा
			lb_mode = LB_YUV_2560X8;
	पूर्ण अन्यथा अणु
		अगर (width > 2560)
			lb_mode = LB_RGB_3840X2;
		अन्यथा अगर (width > 1920)
			lb_mode = LB_RGB_2560X4;
		अन्यथा
			lb_mode = LB_RGB_1920X5;
	पूर्ण

	वापस lb_mode;
पूर्ण

बाह्य स्थिर काष्ठा component_ops vop_component_ops;
#पूर्ण_अगर /* _ROCKCHIP_DRM_VOP_H */
