<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0+ WITH Linux-syscall-note) OR MIT) */
/*
 * Rockchip ISP1 userspace API
 * Copyright (C) 2017 Rockchip Electronics Co., Ltd.
 */

#अगर_अघोषित _UAPI_RKISP1_CONFIG_H
#घोषणा _UAPI_RKISP1_CONFIG_H

#समावेश <linux/types.h>

/* Defect Pixel Cluster Detection */
#घोषणा RKISP1_CIF_ISP_MODULE_DPCC		(1U << 0)
/* Black Level Subtraction */
#घोषणा RKISP1_CIF_ISP_MODULE_BLS		(1U << 1)
/* Sensor De-gamma */
#घोषणा RKISP1_CIF_ISP_MODULE_SDG		(1U << 2)
/* Histogram statistics configuration */
#घोषणा RKISP1_CIF_ISP_MODULE_HST		(1U << 3)
/* Lens Shade Control */
#घोषणा RKISP1_CIF_ISP_MODULE_LSC		(1U << 4)
/* Auto White Balance Gain */
#घोषणा RKISP1_CIF_ISP_MODULE_AWB_GAIN		(1U << 5)
/* Filter */
#घोषणा RKISP1_CIF_ISP_MODULE_FLT		(1U << 6)
/* Bayer Demosaic */
#घोषणा RKISP1_CIF_ISP_MODULE_BDM		(1U << 7)
/* Cross Talk */
#घोषणा RKISP1_CIF_ISP_MODULE_CTK		(1U << 8)
/* Gamma Out Curve */
#घोषणा RKISP1_CIF_ISP_MODULE_GOC		(1U << 9)
/* Color Processing */
#घोषणा RKISP1_CIF_ISP_MODULE_CPROC		(1U << 10)
/* Auto Focus Control statistics configuration */
#घोषणा RKISP1_CIF_ISP_MODULE_AFC		(1U << 11)
/* Auto White Balancing statistics configuration */
#घोषणा RKISP1_CIF_ISP_MODULE_AWB		(1U << 12)
/* Image Effect */
#घोषणा RKISP1_CIF_ISP_MODULE_IE		(1U << 13)
/* Auto Exposure Control statistics configuration */
#घोषणा RKISP1_CIF_ISP_MODULE_AEC		(1U << 14)
/* Wide Dynamic Range */
#घोषणा RKISP1_CIF_ISP_MODULE_WDR		(1U << 15)
/* Denoise Pre-Filter */
#घोषणा RKISP1_CIF_ISP_MODULE_DPF		(1U << 16)
/* Denoise Pre-Filter Strength */
#घोषणा RKISP1_CIF_ISP_MODULE_DPF_STRENGTH	(1U << 17)

#घोषणा RKISP1_CIF_ISP_CTK_COEFF_MAX            0x100
#घोषणा RKISP1_CIF_ISP_CTK_OFFSET_MAX           0x800

#घोषणा RKISP1_CIF_ISP_AE_MEAN_MAX_V10		25
#घोषणा RKISP1_CIF_ISP_AE_MEAN_MAX_V12		81
#घोषणा RKISP1_CIF_ISP_AE_MEAN_MAX		RKISP1_CIF_ISP_AE_MEAN_MAX_V12

#घोषणा RKISP1_CIF_ISP_HIST_BIN_N_MAX_V10	16
#घोषणा RKISP1_CIF_ISP_HIST_BIN_N_MAX_V12	32
#घोषणा RKISP1_CIF_ISP_HIST_BIN_N_MAX		RKISP1_CIF_ISP_HIST_BIN_N_MAX_V12

#घोषणा RKISP1_CIF_ISP_AFM_MAX_WINDOWS          3
#घोषणा RKISP1_CIF_ISP_DEGAMMA_CURVE_SIZE       17

#घोषणा RKISP1_CIF_ISP_BDM_MAX_TH               0xff

/*
 * Black level compensation
 */
/* maximum value क्रम horizontal start address */
#घोषणा RKISP1_CIF_ISP_BLS_START_H_MAX             0x00000fff
/* maximum value क्रम horizontal stop address */
#घोषणा RKISP1_CIF_ISP_BLS_STOP_H_MAX              0x00000fff
/* maximum value क्रम vertical start address */
#घोषणा RKISP1_CIF_ISP_BLS_START_V_MAX             0x00000fff
/* maximum value क्रम vertical stop address */
#घोषणा RKISP1_CIF_ISP_BLS_STOP_V_MAX              0x00000fff
/* maximum is 2^18 = 262144*/
#घोषणा RKISP1_CIF_ISP_BLS_SAMPLES_MAX             0x00000012
/* maximum value क्रम fixed black level */
#घोषणा RKISP1_CIF_ISP_BLS_FIX_SUB_MAX             0x00000fff
/* minimum value क्रम fixed black level */
#घोषणा RKISP1_CIF_ISP_BLS_FIX_SUB_MIN             0xfffff000
/* 13 bit range (चिन्हित)*/
#घोषणा RKISP1_CIF_ISP_BLS_FIX_MASK                0x00001fff

/*
 * Automatic white balance measurements
 */
#घोषणा RKISP1_CIF_ISP_AWB_MAX_GRID                1
#घोषणा RKISP1_CIF_ISP_AWB_MAX_FRAMES              7

/*
 * Gamma out
 */
/* Maximum number of color samples supported */
#घोषणा RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES_V10   17
#घोषणा RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES_V12   34
#घोषणा RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES       RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES_V12

/*
 * Lens shade correction
 */
#घोषणा RKISP1_CIF_ISP_LSC_SECTORS_TBL_SIZE        8

/*
 * The following matches the tuning process,
 * not the max capabilities of the chip.
 */
#घोषणा RKISP1_CIF_ISP_LSC_SAMPLES_MAX             17

/*
 * Histogram calculation
 */
#घोषणा RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE_V10 25
#घोषणा RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE_V12 81
#घोषणा RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE     RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE_V12

/*
 * Defect Pixel Cluster Correction
 */
#घोषणा RKISP1_CIF_ISP_DPCC_METHODS_MAX       3

/*
 * Denoising pre filter
 */
#घोषणा RKISP1_CIF_ISP_DPF_MAX_NLF_COEFFS      17
#घोषणा RKISP1_CIF_ISP_DPF_MAX_SPATIAL_COEFFS  6

/*
 * Measurement types
 */
#घोषणा RKISP1_CIF_ISP_STAT_AWB           (1U << 0)
#घोषणा RKISP1_CIF_ISP_STAT_AUTOEXP       (1U << 1)
#घोषणा RKISP1_CIF_ISP_STAT_AFM           (1U << 2)
#घोषणा RKISP1_CIF_ISP_STAT_HIST          (1U << 3)

/**
 * क्रमागत rkisp1_cअगर_isp_version - ISP variants
 *
 * @RKISP1_V10: used at least in rk3288 and rk3399
 * @RKISP1_V11: declared in the original venकरोr code, but not used
 * @RKISP1_V12: used at least in rk3326 and px30
 * @RKISP1_V13: used at least in rk1808
 */
क्रमागत rkisp1_cअगर_isp_version अणु
	RKISP1_V10 = 10,
	RKISP1_V11,
	RKISP1_V12,
	RKISP1_V13,
पूर्ण;

क्रमागत rkisp1_cअगर_isp_histogram_mode अणु
	RKISP1_CIF_ISP_HISTOGRAM_MODE_DISABLE,
	RKISP1_CIF_ISP_HISTOGRAM_MODE_RGB_COMBINED,
	RKISP1_CIF_ISP_HISTOGRAM_MODE_R_HISTOGRAM,
	RKISP1_CIF_ISP_HISTOGRAM_MODE_G_HISTOGRAM,
	RKISP1_CIF_ISP_HISTOGRAM_MODE_B_HISTOGRAM,
	RKISP1_CIF_ISP_HISTOGRAM_MODE_Y_HISTOGRAM
पूर्ण;

क्रमागत rkisp1_cअगर_isp_awb_mode_type अणु
	RKISP1_CIF_ISP_AWB_MODE_MANUAL,
	RKISP1_CIF_ISP_AWB_MODE_RGB,
	RKISP1_CIF_ISP_AWB_MODE_YCBCR
पूर्ण;

क्रमागत rkisp1_cअगर_isp_flt_mode अणु
	RKISP1_CIF_ISP_FLT_STATIC_MODE,
	RKISP1_CIF_ISP_FLT_DYNAMIC_MODE
पूर्ण;

/**
 * क्रमागत rkisp1_cअगर_isp_exp_ctrl_स्वतःstop - stop modes
 * @RKISP1_CIF_ISP_EXP_CTRL_AUTOSTOP_0: continuous measurement
 * @RKISP1_CIF_ISP_EXP_CTRL_AUTOSTOP_1: stop measuring after a complete frame
 */
क्रमागत rkisp1_cअगर_isp_exp_ctrl_स्वतःstop अणु
	RKISP1_CIF_ISP_EXP_CTRL_AUTOSTOP_0 = 0,
	RKISP1_CIF_ISP_EXP_CTRL_AUTOSTOP_1 = 1,
पूर्ण;

/**
 * क्रमागत rkisp1_cअगर_isp_exp_meas_mode - Exposure measure mode
 * @RKISP1_CIF_ISP_EXP_MEASURING_MODE_0: Y = 16 + 0.25R + 0.5G + 0.1094B
 * @RKISP1_CIF_ISP_EXP_MEASURING_MODE_1: Y = (R + G + B) x (85/256)
 */
क्रमागत rkisp1_cअगर_isp_exp_meas_mode अणु
	RKISP1_CIF_ISP_EXP_MEASURING_MODE_0,
	RKISP1_CIF_ISP_EXP_MEASURING_MODE_1,
पूर्ण;

/*---------- PART1: Input Parameters ------------*/

/**
 * काष्ठा rkisp1_cअगर_isp_winकरोw -  measurement winकरोw.
 *
 * Measurements are calculated per winकरोw inside the frame.
 * This काष्ठा represents a winकरोw क्रम a measurement.
 *
 * @h_offs: the horizontal offset of the winकरोw from the left of the frame in pixels.
 * @v_offs: the vertical offset of the winकरोw from the top of the frame in pixels.
 * @h_size: the horizontal size of the winकरोw in pixels
 * @v_size: the vertical size of the winकरोw in pixels.
 */
काष्ठा rkisp1_cअगर_isp_winकरोw अणु
	__u16 h_offs;
	__u16 v_offs;
	__u16 h_size;
	__u16 v_size;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_bls_fixed_val - BLS fixed subtraction values
 *
 * The values will be subtracted from the sensor
 * values. Thereक्रमe a negative value means addition instead of subtraction!
 *
 * @r: Fixed (चिन्हित!) subtraction value क्रम Bayer pattern R
 * @gr: Fixed (चिन्हित!) subtraction value क्रम Bayer pattern Gr
 * @gb: Fixed (चिन्हित!) subtraction value क्रम Bayer pattern Gb
 * @b: Fixed (चिन्हित!) subtraction value क्रम Bayer pattern B
 */
काष्ठा rkisp1_cअगर_isp_bls_fixed_val अणु
	__s16 r;
	__s16 gr;
	__s16 gb;
	__s16 b;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_bls_config - Configuration used by black level subtraction
 *
 * @enable_स्वतः: Automatic mode activated means that the measured values
 *		 are subtracted. Otherwise the fixed subtraction
 *		 values will be subtracted.
 * @en_winकरोws: enabled winकरोw
 * @bls_winकरोw1: Measurement winकरोw 1 size
 * @bls_winकरोw2: Measurement winकरोw 2 size
 * @bls_samples: Set amount of measured pixels क्रम each Bayer position
 *		 (A, B,C and D) to 2^bls_samples.
 * @fixed_val: Fixed subtraction values
 */
काष्ठा rkisp1_cअगर_isp_bls_config अणु
	__u8 enable_स्वतः;
	__u8 en_winकरोws;
	काष्ठा rkisp1_cअगर_isp_winकरोw bls_winकरोw1;
	काष्ठा rkisp1_cअगर_isp_winकरोw bls_winकरोw2;
	__u8 bls_samples;
	काष्ठा rkisp1_cअगर_isp_bls_fixed_val fixed_val;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpcc_methods_config - Methods Configuration used by DPCC
 *
 * Methods Configuration used by Defect Pixel Cluster Correction
 *
 * @method: Method enable bits
 * @line_thresh: Line threshold
 * @line_mad_fac: Line MAD factor
 * @pg_fac: Peak gradient factor
 * @rnd_thresh: Rank Neighbor Dअगरference threshold
 * @rg_fac: Rank gradient factor
 */
काष्ठा rkisp1_cअगर_isp_dpcc_methods_config अणु
	__u32 method;
	__u32 line_thresh;
	__u32 line_mad_fac;
	__u32 pg_fac;
	__u32 rnd_thresh;
	__u32 rg_fac;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpcc_config - Configuration used by DPCC
 *
 * Configuration used by Defect Pixel Cluster Correction
 *
 * @mode: dpcc output mode
 * @output_mode: whether use hard coded methods
 * @set_use: stage1 methods set
 * @methods: methods config
 * @ro_limits: rank order limits
 * @rnd_offs: dअगरferential rank offsets क्रम rank neighbor dअगरference
 */
काष्ठा rkisp1_cअगर_isp_dpcc_config अणु
	__u32 mode;
	__u32 output_mode;
	__u32 set_use;
	काष्ठा rkisp1_cअगर_isp_dpcc_methods_config methods[RKISP1_CIF_ISP_DPCC_METHODS_MAX];
	__u32 ro_limits;
	__u32 rnd_offs;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_gamma_corr_curve - gamma curve poपूर्णांक definition y-axis (output).
 *
 * The reset values define a linear curve which has the same effect as bypass. Reset values are:
 * gamma_y[0] = 0x0000, gamma_y[1] = 0x0100, ... gamma_y[15] = 0x0f00, gamma_y[16] = 0xfff
 *
 * @gamma_y: the values क्रम the y-axis of gamma curve poपूर्णांकs. Each value is 12 bit.
 */
काष्ठा rkisp1_cअगर_isp_gamma_corr_curve अणु
	__u16 gamma_y[RKISP1_CIF_ISP_DEGAMMA_CURVE_SIZE];
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_gamma_curve_x_axis_pnts - De-Gamma Curve definition x increments
 *		(sampling poपूर्णांकs). gamma_dx0 is क्रम the lower samples (1-8), gamma_dx1 is क्रम the
 *		higher samples (9-16). The reset values क्रम both fields is 0x44444444. This means
 *		that each sample is 4 units away from the previous one on the x-axis.
 *
 * @gamma_dx0: gamma curve sample poपूर्णांकs definitions. Bits 0:2 क्रम sample 1. Bit 3 unused.
 *		Bits 4:6 क्रम sample 2. bit 7 unused ... Bits 28:30 क्रम sample 8. Bit 31 unused
 * @gamma_dx1: gamma curve sample poपूर्णांकs definitions. Bits 0:2 क्रम sample 9. Bit 3 unused.
 *		Bits 4:6 क्रम sample 10. bit 7 unused ... Bits 28:30 क्रम sample 16. Bit 31 unused
 */
काष्ठा rkisp1_cअगर_isp_gamma_curve_x_axis_pnts अणु
	__u32 gamma_dx0;
	__u32 gamma_dx1;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_sdg_config - Configuration used by sensor degamma
 *
 * @curve_r: gamma curve poपूर्णांक definition axis क्रम red
 * @curve_g: gamma curve poपूर्णांक definition axis क्रम green
 * @curve_b: gamma curve poपूर्णांक definition axis क्रम blue
 * @xa_pnts: x axis increments
 */
काष्ठा rkisp1_cअगर_isp_sdg_config अणु
	काष्ठा rkisp1_cअगर_isp_gamma_corr_curve curve_r;
	काष्ठा rkisp1_cअगर_isp_gamma_corr_curve curve_g;
	काष्ठा rkisp1_cअगर_isp_gamma_corr_curve curve_b;
	काष्ठा rkisp1_cअगर_isp_gamma_curve_x_axis_pnts xa_pnts;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_lsc_config - Configuration used by Lens shading correction
 *
 * @r_data_tbl: sample table red
 * @gr_data_tbl: sample table green (red)
 * @gb_data_tbl: sample table green (blue)
 * @b_data_tbl: sample table blue
 * @x_grad_tbl: gradient table x
 * @y_grad_tbl: gradient table y
 * @x_माप_प्रकारbl: size table x
 * @y_माप_प्रकारbl: size table y
 * @config_width: not used at the moment
 * @config_height: not used at the moment
 */
काष्ठा rkisp1_cअगर_isp_lsc_config अणु
	__u16 r_data_tbl[RKISP1_CIF_ISP_LSC_SAMPLES_MAX][RKISP1_CIF_ISP_LSC_SAMPLES_MAX];
	__u16 gr_data_tbl[RKISP1_CIF_ISP_LSC_SAMPLES_MAX][RKISP1_CIF_ISP_LSC_SAMPLES_MAX];
	__u16 gb_data_tbl[RKISP1_CIF_ISP_LSC_SAMPLES_MAX][RKISP1_CIF_ISP_LSC_SAMPLES_MAX];
	__u16 b_data_tbl[RKISP1_CIF_ISP_LSC_SAMPLES_MAX][RKISP1_CIF_ISP_LSC_SAMPLES_MAX];

	__u16 x_grad_tbl[RKISP1_CIF_ISP_LSC_SECTORS_TBL_SIZE];
	__u16 y_grad_tbl[RKISP1_CIF_ISP_LSC_SECTORS_TBL_SIZE];

	__u16 x_माप_प्रकारbl[RKISP1_CIF_ISP_LSC_SECTORS_TBL_SIZE];
	__u16 y_माप_प्रकारbl[RKISP1_CIF_ISP_LSC_SECTORS_TBL_SIZE];
	__u16 config_width;
	__u16 config_height;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_ie_config - Configuration used by image effects
 *
 * @effect: values from 'enum v4l2_colorfx'. Possible values are: V4L2_COLORFX_SEPIA,
 *		V4L2_COLORFX_SET_CBCR, V4L2_COLORFX_AQUA, V4L2_COLORFX_EMBOSS,
 *		V4L2_COLORFX_SKETCH,   V4L2_COLORFX_BW,   V4L2_COLORFX_NEGATIVE
 * @color_sel: bits 0:2 - colors biपंचांगask (001 - blue, 010 - green, 100 - red).
 *		bits 8:15 - Threshold value of the RGB colors क्रम the color selection effect.
 * @eff_mat_1: 3x3 Matrix Coefficients क्रम Emboss Effect 1
 * @eff_mat_2: 3x3 Matrix Coefficients क्रम Emboss Effect 2
 * @eff_mat_3: 3x3 Matrix Coefficients क्रम Emboss 3/Sketch 1
 * @eff_mat_4: 3x3 Matrix Coefficients क्रम Sketch Effect 2
 * @eff_mat_5: 3x3 Matrix Coefficients क्रम Sketch Effect 3
 * @eff_tपूर्णांक: Chrominance increment values of tपूर्णांक (used क्रम sepia effect)
 */
काष्ठा rkisp1_cअगर_isp_ie_config अणु
	__u16 effect;
	__u16 color_sel;
	__u16 eff_mat_1;
	__u16 eff_mat_2;
	__u16 eff_mat_3;
	__u16 eff_mat_4;
	__u16 eff_mat_5;
	__u16 eff_tपूर्णांक;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_cproc_config - Configuration used by Color Processing
 *
 * @c_out_range: Chrominance pixel clipping range at output.
 *		 (0 क्रम limit, 1 क्रम full)
 * @y_in_range: Luminance pixel clipping range at output.
 * @y_out_range: Luminance pixel clipping range at output.
 * @contrast: 00~ff, 0.0~1.992
 * @brightness: 80~7F, -128~+127
 * @sat: saturation, 00~FF, 0.0~1.992
 * @hue: 80~7F, -90~+87.188
 */
काष्ठा rkisp1_cअगर_isp_cproc_config अणु
	__u8 c_out_range;
	__u8 y_in_range;
	__u8 y_out_range;
	__u8 contrast;
	__u8 brightness;
	__u8 sat;
	__u8 hue;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_awb_meas_config - Configuration क्रम the AWB statistics
 *
 * @awb_mode: the awb meas mode. From क्रमागत rkisp1_cअगर_isp_awb_mode_type.
 * @awb_wnd: white balance measurement winकरोw (in pixels)
 * @max_y: only pixels values < max_y contribute to awb measurement, set to 0
 *	   to disable this feature
 * @min_y: only pixels values > min_y contribute to awb measurement
 * @max_csum: Chrominance sum maximum value, only consider pixels with Cb+Cr,
 *	      smaller than threshold क्रम awb measurements
 * @min_c: Chrominance minimum value, only consider pixels with Cb/Cr
 *	   each greater than threshold value क्रम awb measurements
 * @frames: number of frames - 1 used क्रम mean value calculation
 *	    (ucFrames=0 means 1 Frame)
 * @awb_ref_cr: reference Cr value क्रम AWB regulation, target क्रम AWB
 * @awb_ref_cb: reference Cb value क्रम AWB regulation, target क्रम AWB
 * @enable_ymax_cmp: enable Y_MAX compare (Not valid in RGB measurement mode.)
 */
काष्ठा rkisp1_cअगर_isp_awb_meas_config अणु
	/*
	 * Note: currently the h and v offsets are mapped to grid offsets
	 */
	काष्ठा rkisp1_cअगर_isp_winकरोw awb_wnd;
	__u32 awb_mode;
	__u8 max_y;
	__u8 min_y;
	__u8 max_csum;
	__u8 min_c;
	__u8 frames;
	__u8 awb_ref_cr;
	__u8 awb_ref_cb;
	__u8 enable_ymax_cmp;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_awb_gain_config - Configuration used by स्वतः white balance gain
 *
 * All fields in this काष्ठा are 10 bit, where:
 * 0x100h = 1, अचिन्हित पूर्णांकeger value, range 0 to 4 with 8 bit fractional part.
 *
 * out_data_x = ( AWB_GAIN_X * in_data + 128) >> 8
 *
 * @gain_red: gain value क्रम red component.
 * @gain_green_r: gain value क्रम green component in red line.
 * @gain_blue: gain value क्रम blue component.
 * @gain_green_b: gain value क्रम green component in blue line.
 */
काष्ठा rkisp1_cअगर_isp_awb_gain_config अणु
	__u16 gain_red;
	__u16 gain_green_r;
	__u16 gain_blue;
	__u16 gain_green_b;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_flt_config - Configuration used by ISP filtering
 *
 * All 4 threshold fields (thresh_*) are 10 bits.
 * All 6 factor fields (fac_*) are 6 bits.
 *
 * @mode: ISP_FILT_MODE रेजिस्टर fields (from क्रमागत rkisp1_cअगर_isp_flt_mode)
 * @grn_stage1: Green filter stage 1 select (range 0x0...0x8)
 * @chr_h_mode: Chroma filter horizontal mode
 * @chr_v_mode: Chroma filter vertical mode
 * @thresh_bl0: If thresh_bl1 < sum_grad < thresh_bl0 then fac_bl0 is selected (blurring th)
 * @thresh_bl1: If sum_grad < thresh_bl1 then fac_bl1 is selected (blurring th)
 * @thresh_sh0: If thresh_sh0 < sum_grad < thresh_sh1 then thresh_sh0 is selected (sharpening th)
 * @thresh_sh1: If thresh_sh1 < sum_grad then thresh_sh1 is selected (sharpening th)
 * @lum_weight: Parameters क्रम luminance weight function.
 * @fac_sh1: filter factor क्रम sharp1 level
 * @fac_sh0: filter factor क्रम sharp0 level
 * @fac_mid: filter factor क्रम mid level and क्रम अटल filter mode
 * @fac_bl0: filter factor क्रम blur 0 level
 * @fac_bl1: filter factor क्रम blur 1 level (max blur)
 */
काष्ठा rkisp1_cअगर_isp_flt_config अणु
	__u32 mode;
	__u8 grn_stage1;
	__u8 chr_h_mode;
	__u8 chr_v_mode;
	__u32 thresh_bl0;
	__u32 thresh_bl1;
	__u32 thresh_sh0;
	__u32 thresh_sh1;
	__u32 lum_weight;
	__u32 fac_sh1;
	__u32 fac_sh0;
	__u32 fac_mid;
	__u32 fac_bl0;
	__u32 fac_bl1;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_bdm_config - Configuration used by Bayer DeMosaic
 *
 * @demosaic_th: threshold क्रम bayer demosaicing texture detection
 */
काष्ठा rkisp1_cअगर_isp_bdm_config अणु
	__u8 demosaic_th;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_ctk_config - Configuration used by Cross Talk correction
 *
 * @coeff: color correction matrix. Values are 11-bit चिन्हित fixed-poपूर्णांक numbers with 4 bit पूर्णांकeger
 *		and 7 bit fractional part, ranging from -8 (0x400) to +7.992 (0x3FF). 0 is
 *		represented by 0x000 and a coefficient value of 1 as 0x080.
 * @ct_offset: Red, Green, Blue offsets क्रम the crosstalk correction matrix
 */
काष्ठा rkisp1_cअगर_isp_ctk_config अणु
	__u16 coeff[3][3];
	__u16 ct_offset[3];
पूर्ण;

क्रमागत rkisp1_cअगर_isp_goc_mode अणु
	RKISP1_CIF_ISP_GOC_MODE_LOGARITHMIC,
	RKISP1_CIF_ISP_GOC_MODE_EQUIDISTANT
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_goc_config - Configuration used by Gamma Out correction
 *
 * @mode: goc mode (from क्रमागत rkisp1_cअगर_isp_goc_mode)
 * @gamma_y: gamma out curve y-axis क्रम all color components
 *
 * The number of entries of @gamma_y depends on the hardware revision
 * as is reported by the hw_revision field of the काष्ठा media_device_info
 * that is वापसed by ioctl MEDIA_IOC_DEVICE_INFO.
 *
 * Versions <= V11 have RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES_V10
 * entries, versions >= V12 have RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES_V12
 * entries. RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES is equal to the maximum
 * of the two.
 */
काष्ठा rkisp1_cअगर_isp_goc_config अणु
	__u32 mode;
	__u16 gamma_y[RKISP1_CIF_ISP_GAMMA_OUT_MAX_SAMPLES];
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_hst_config - Configuration क्रम Histogram statistics
 *
 * @mode: histogram mode (from क्रमागत rkisp1_cअगर_isp_histogram_mode)
 * @histogram_preभागider: process every stepsize pixel, all other pixels are
 *			  skipped
 * @meas_winकरोw: coordinates of the measure winकरोw
 * @hist_weight: weighting factor क्रम sub-winकरोws
 *
 * The number of entries of @hist_weight depends on the hardware revision
 * as is reported by the hw_revision field of the काष्ठा media_device_info
 * that is वापसed by ioctl MEDIA_IOC_DEVICE_INFO.
 *
 * Versions <= V11 have RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE_V10
 * entries, versions >= V12 have RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE_V12
 * entries. RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE is equal to the maximum
 * of the two.
 */
काष्ठा rkisp1_cअगर_isp_hst_config अणु
	__u32 mode;
	__u8 histogram_preभागider;
	काष्ठा rkisp1_cअगर_isp_winकरोw meas_winकरोw;
	__u8 hist_weight[RKISP1_CIF_ISP_HISTOGRAM_WEIGHT_GRIDS_SIZE];
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_aec_config - Configuration क्रम Auto Exposure statistics
 *
 * @mode: Exposure measure mode (from क्रमागत rkisp1_cअगर_isp_exp_meas_mode)
 * @स्वतःstop: stop mode (from क्रमागत rkisp1_cअगर_isp_exp_ctrl_स्वतःstop)
 * @meas_winकरोw: coordinates of the measure winकरोw
 */
काष्ठा rkisp1_cअगर_isp_aec_config अणु
	__u32 mode;
	__u32 स्वतःstop;
	काष्ठा rkisp1_cअगर_isp_winकरोw meas_winकरोw;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_afc_config - Configuration क्रम the Auto Focus statistics
 *
 * @num_afm_win: max RKISP1_CIF_ISP_AFM_MAX_WINDOWS
 * @afm_win: coordinates of the meas winकरोw
 * @thres: threshold used क्रम minimizing the influence of noise
 * @var_shअगरt: the number of bits क्रम the shअगरt operation at the end of the
 *	       calculation chain.
 */
काष्ठा rkisp1_cअगर_isp_afc_config अणु
	__u8 num_afm_win;
	काष्ठा rkisp1_cअगर_isp_winकरोw afm_win[RKISP1_CIF_ISP_AFM_MAX_WINDOWS];
	__u32 thres;
	__u32 var_shअगरt;
पूर्ण;

/**
 * क्रमागत rkisp1_cअगर_isp_dpf_gain_usage - dpf gain usage
 * @RKISP1_CIF_ISP_DPF_GAIN_USAGE_DISABLED: करोn't use any gains in preprocessing stage
 * @RKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_GAINS: use only the noise function gains from
 *				    रेजिस्टरs DPF_NF_GAIN_R, ...
 * @RKISP1_CIF_ISP_DPF_GAIN_USAGE_LSC_GAINS:  use only the gains from LSC module
 * @RKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_LSC_GAINS: use the noise function gains and the
 *					gains from LSC module
 * @RKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_GAINS: use only the gains from AWB module
 * @RKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_LSC_GAINS: use the gains from AWB and LSC module
 * @RKISP1_CIF_ISP_DPF_GAIN_USAGE_MAX: upper border (only क्रम an पूर्णांकernal evaluation)
 */
क्रमागत rkisp1_cअगर_isp_dpf_gain_usage अणु
	RKISP1_CIF_ISP_DPF_GAIN_USAGE_DISABLED,
	RKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_GAINS,
	RKISP1_CIF_ISP_DPF_GAIN_USAGE_LSC_GAINS,
	RKISP1_CIF_ISP_DPF_GAIN_USAGE_NF_LSC_GAINS,
	RKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_GAINS,
	RKISP1_CIF_ISP_DPF_GAIN_USAGE_AWB_LSC_GAINS,
	RKISP1_CIF_ISP_DPF_GAIN_USAGE_MAX
पूर्ण;

/**
 * क्रमागत rkisp1_cअगर_isp_dpf_rb_filtersize - Red and blue filter sizes
 * @RKISP1_CIF_ISP_DPF_RB_FILTERSIZE_13x9: red and blue filter kernel size 13x9
 *				   (means 7x5 active pixel)
 * @RKISP1_CIF_ISP_DPF_RB_FILTERSIZE_9x9: red and blue filter kernel size 9x9
 *				   (means 5x5 active pixel)
 */
क्रमागत rkisp1_cअगर_isp_dpf_rb_filtersize अणु
	RKISP1_CIF_ISP_DPF_RB_FILTERSIZE_13x9,
	RKISP1_CIF_ISP_DPF_RB_FILTERSIZE_9x9,
पूर्ण;

/**
 * क्रमागत rkisp1_cअगर_isp_dpf_nll_scale_mode - dpf noise level scale mode
 * @RKISP1_CIF_ISP_NLL_SCALE_LINEAR: use a linear scaling
 * @RKISP1_CIF_ISP_NLL_SCALE_LOGARITHMIC: use a logarithmic scaling
 */
क्रमागत rkisp1_cअगर_isp_dpf_nll_scale_mode अणु
	RKISP1_CIF_ISP_NLL_SCALE_LINEAR,
	RKISP1_CIF_ISP_NLL_SCALE_LOGARITHMIC,
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpf_nll - Noise level lookup
 *
 * @coeff: Noise level Lookup coefficient
 * @scale_mode: dpf noise level scale mode (from क्रमागत rkisp1_cअगर_isp_dpf_nll_scale_mode)
 */
काष्ठा rkisp1_cअगर_isp_dpf_nll अणु
	__u16 coeff[RKISP1_CIF_ISP_DPF_MAX_NLF_COEFFS];
	__u32 scale_mode;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpf_rb_flt - Red blue filter config
 *
 * @fltsize: The filter size क्रम the red and blue pixels
 *	     (from क्रमागत rkisp1_cअगर_isp_dpf_rb_filtersize)
 * @spatial_coeff: Spatial weights
 * @r_enable: enable filter processing क्रम red pixels
 * @b_enable: enable filter processing क्रम blue pixels
 */
काष्ठा rkisp1_cअगर_isp_dpf_rb_flt अणु
	__u32 fltsize;
	__u8 spatial_coeff[RKISP1_CIF_ISP_DPF_MAX_SPATIAL_COEFFS];
	__u8 r_enable;
	__u8 b_enable;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpf_g_flt - Green filter Configuration
 *
 * @spatial_coeff: Spatial weights
 * @gr_enable: enable filter processing क्रम green pixels in green/red lines
 * @gb_enable: enable filter processing क्रम green pixels in green/blue lines
 */
काष्ठा rkisp1_cअगर_isp_dpf_g_flt अणु
	__u8 spatial_coeff[RKISP1_CIF_ISP_DPF_MAX_SPATIAL_COEFFS];
	__u8 gr_enable;
	__u8 gb_enable;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpf_gain - Noise function Configuration
 *
 * @mode: dpf gain usage  (from क्रमागत rkisp1_cअगर_isp_dpf_gain_usage)
 * @nf_r_gain: Noise function Gain that replaces the AWB gain क्रम red pixels
 * @nf_b_gain: Noise function Gain that replaces the AWB gain क्रम blue pixels
 * @nf_gr_gain: Noise function Gain that replaces the AWB gain
 *		क्रम green pixels in a red line
 * @nf_gb_gain: Noise function Gain that replaces the AWB gain
 *		क्रम green pixels in a blue line
 */
काष्ठा rkisp1_cअगर_isp_dpf_gain अणु
	__u32 mode;
	__u16 nf_r_gain;
	__u16 nf_b_gain;
	__u16 nf_gr_gain;
	__u16 nf_gb_gain;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpf_config - Configuration used by De-noising pre-filter
 *
 * @gain: noise function gain
 * @g_flt: green filter config
 * @rb_flt: red blue filter config
 * @nll: noise level lookup
 */
काष्ठा rkisp1_cअगर_isp_dpf_config अणु
	काष्ठा rkisp1_cअगर_isp_dpf_gain gain;
	काष्ठा rkisp1_cअगर_isp_dpf_g_flt g_flt;
	काष्ठा rkisp1_cअगर_isp_dpf_rb_flt rb_flt;
	काष्ठा rkisp1_cअगर_isp_dpf_nll nll;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_dpf_strength_config - strength of the filter
 *
 * @r: filter strength of the RED filter
 * @g: filter strength of the GREEN filter
 * @b: filter strength of the BLUE filter
 */
काष्ठा rkisp1_cअगर_isp_dpf_strength_config अणु
	__u8 r;
	__u8 g;
	__u8 b;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_isp_other_cfg - Parameters क्रम some blocks in rockchip isp1
 *
 * @dpcc_config: Defect Pixel Cluster Correction config
 * @bls_config: Black Level Subtraction config
 * @sdg_config: sensor degamma config
 * @lsc_config: Lens Shade config
 * @awb_gain_config: Auto White balance gain config
 * @flt_config: filter config
 * @bdm_config: demosaic config
 * @ctk_config: cross talk config
 * @goc_config: gamma out config
 * @bls_config: black level subtraction config
 * @dpf_config: De-noising pre-filter config
 * @dpf_strength_config: dpf strength config
 * @cproc_config: color process config
 * @ie_config: image effects config
 */
काष्ठा rkisp1_cअगर_isp_isp_other_cfg अणु
	काष्ठा rkisp1_cअगर_isp_dpcc_config dpcc_config;
	काष्ठा rkisp1_cअगर_isp_bls_config bls_config;
	काष्ठा rkisp1_cअगर_isp_sdg_config sdg_config;
	काष्ठा rkisp1_cअगर_isp_lsc_config lsc_config;
	काष्ठा rkisp1_cअगर_isp_awb_gain_config awb_gain_config;
	काष्ठा rkisp1_cअगर_isp_flt_config flt_config;
	काष्ठा rkisp1_cअगर_isp_bdm_config bdm_config;
	काष्ठा rkisp1_cअगर_isp_ctk_config ctk_config;
	काष्ठा rkisp1_cअगर_isp_goc_config goc_config;
	काष्ठा rkisp1_cअगर_isp_dpf_config dpf_config;
	काष्ठा rkisp1_cअगर_isp_dpf_strength_config dpf_strength_config;
	काष्ठा rkisp1_cअगर_isp_cproc_config cproc_config;
	काष्ठा rkisp1_cअगर_isp_ie_config ie_config;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_isp_meas_cfg - Rockchip ISP1 Measure Parameters
 *
 * @awb_meas_config: स्वतः white balance config
 * @hst_config: histogram config
 * @aec_config: स्वतः exposure config
 * @afc_config: स्वतः focus config
 */
काष्ठा rkisp1_cअगर_isp_isp_meas_cfg अणु
	काष्ठा rkisp1_cअगर_isp_awb_meas_config awb_meas_config;
	काष्ठा rkisp1_cअगर_isp_hst_config hst_config;
	काष्ठा rkisp1_cअगर_isp_aec_config aec_config;
	काष्ठा rkisp1_cअगर_isp_afc_config afc_config;
पूर्ण;

/**
 * काष्ठा rkisp1_params_cfg - Rockchip ISP1 Input Parameters Meta Data
 *
 * @module_en_update: mask the enable bits of which module should be updated
 * @module_ens: mask the enable value of each module, only update the module
 *		which correspond bit was set in module_en_update
 * @module_cfg_update: mask the config bits of which module should be updated
 * @meas: measurement config
 * @others: other config
 */
काष्ठा rkisp1_params_cfg अणु
	__u32 module_en_update;
	__u32 module_ens;
	__u32 module_cfg_update;

	काष्ठा rkisp1_cअगर_isp_isp_meas_cfg meas;
	काष्ठा rkisp1_cअगर_isp_isp_other_cfg others;
पूर्ण;

/*---------- PART2: Measurement Statistics ------------*/

/**
 * काष्ठा rkisp1_cअगर_isp_awb_meas - AWB measured values
 *
 * @cnt: White pixel count, number of "white pixels" found during last
 *	 measurement
 * @mean_y_or_g: Mean value of Y within winकरोw and frames,
 *		 Green अगर RGB is selected.
 * @mean_cb_or_b: Mean value of Cb within winकरोw and frames,
 *		  Blue अगर RGB is selected.
 * @mean_cr_or_r: Mean value of Cr within winकरोw and frames,
 *		  Red अगर RGB is selected.
 */
काष्ठा rkisp1_cअगर_isp_awb_meas अणु
	__u32 cnt;
	__u8 mean_y_or_g;
	__u8 mean_cb_or_b;
	__u8 mean_cr_or_r;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_awb_stat - statistics स्वतःmatic white balance data
 *
 * @awb_mean: Mean measured data
 */
काष्ठा rkisp1_cअगर_isp_awb_stat अणु
	काष्ठा rkisp1_cअगर_isp_awb_meas awb_mean[RKISP1_CIF_ISP_AWB_MAX_GRID];
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_bls_meas_val - BLS measured values
 *
 * @meas_r: Mean measured value क्रम Bayer pattern R
 * @meas_gr: Mean measured value क्रम Bayer pattern Gr
 * @meas_gb: Mean measured value क्रम Bayer pattern Gb
 * @meas_b: Mean measured value क्रम Bayer pattern B
 */
काष्ठा rkisp1_cअगर_isp_bls_meas_val अणु
	__u16 meas_r;
	__u16 meas_gr;
	__u16 meas_gb;
	__u16 meas_b;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_ae_stat - statistics स्वतः exposure data
 *
 * @exp_mean: Mean luminance value of block xx
 * @bls_val:  BLS measured values
 *
 * The number of entries of @exp_mean depends on the hardware revision
 * as is reported by the hw_revision field of the काष्ठा media_device_info
 * that is वापसed by ioctl MEDIA_IOC_DEVICE_INFO.
 *
 * Versions <= V11 have RKISP1_CIF_ISP_AE_MEAN_MAX_V10 entries,
 * versions >= V12 have RKISP1_CIF_ISP_AE_MEAN_MAX_V12 entries.
 * RKISP1_CIF_ISP_AE_MEAN_MAX is equal to the maximum of the two.
 *
 * Image is भागided पूर्णांकo 5x5 blocks on V10 and 9x9 blocks on V12.
 */
काष्ठा rkisp1_cअगर_isp_ae_stat अणु
	__u8 exp_mean[RKISP1_CIF_ISP_AE_MEAN_MAX];
	काष्ठा rkisp1_cअगर_isp_bls_meas_val bls_val;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_af_meas_val - AF measured values
 *
 * @sum: sharpness value
 * @lum: luminance value
 */
काष्ठा rkisp1_cअगर_isp_af_meas_val अणु
	__u32 sum;
	__u32 lum;
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_af_stat - statistics स्वतः focus data
 *
 * @winकरोw: AF measured value of winकरोw x
 *
 * The module measures the sharpness in 3 winकरोws of selectable size via
 * रेजिस्टर settings(ISP_AFM_*_A/B/C)
 */
काष्ठा rkisp1_cअगर_isp_af_stat अणु
	काष्ठा rkisp1_cअगर_isp_af_meas_val winकरोw[RKISP1_CIF_ISP_AFM_MAX_WINDOWS];
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_hist_stat - statistics histogram data
 *
 * @hist_bins: measured bin counters. Each bin is a 20 bits अचिन्हित fixed poपूर्णांक
 *	       type. Bits 0-4 are the fractional part and bits 5-19 are the
 *	       पूर्णांकeger part.
 *
 * The winकरोw of the measurements area is भागided to 5x5 sub-winकरोws क्रम
 * V10/V11 and to 9x9 sub-winकरोws क्रम V12. The histogram is then computed क्रम
 * each sub-winकरोw independently and the final result is a weighted average of
 * the histogram measurements on all sub-winकरोws. The winकरोw of the
 * measurements area and the weight of each sub-winकरोw are configurable using
 * काष्ठा @rkisp1_cअगर_isp_hst_config.
 *
 * The histogram contains 16 bins in V10/V11 and 32 bins in V12/V13.
 *
 * The number of entries of @hist_bins depends on the hardware revision
 * as is reported by the hw_revision field of the काष्ठा media_device_info
 * that is वापसed by ioctl MEDIA_IOC_DEVICE_INFO.
 *
 * Versions <= V11 have RKISP1_CIF_ISP_HIST_BIN_N_MAX_V10 entries,
 * versions >= V12 have RKISP1_CIF_ISP_HIST_BIN_N_MAX_V12 entries.
 * RKISP1_CIF_ISP_HIST_BIN_N_MAX is equal to the maximum of the two.
 */
काष्ठा rkisp1_cअगर_isp_hist_stat अणु
	__u32 hist_bins[RKISP1_CIF_ISP_HIST_BIN_N_MAX];
पूर्ण;

/**
 * काष्ठा rkisp1_cअगर_isp_stat - Rockchip ISP1 Statistics Data
 *
 * @awb: statistics data क्रम स्वतःmatic white balance
 * @ae: statistics data क्रम स्वतः exposure
 * @af: statistics data क्रम स्वतः focus
 * @hist: statistics histogram data
 */
काष्ठा rkisp1_cअगर_isp_stat अणु
	काष्ठा rkisp1_cअगर_isp_awb_stat awb;
	काष्ठा rkisp1_cअगर_isp_ae_stat ae;
	काष्ठा rkisp1_cअगर_isp_af_stat af;
	काष्ठा rkisp1_cअगर_isp_hist_stat hist;
पूर्ण;

/**
 * काष्ठा rkisp1_stat_buffer - Rockchip ISP1 Statistics Meta Data
 *
 * @meas_type: measurement types (RKISP1_CIF_ISP_STAT_* definitions)
 * @frame_id: frame ID क्रम sync
 * @params: statistics data
 */
काष्ठा rkisp1_stat_buffer अणु
	__u32 meas_type;
	__u32 frame_id;
	काष्ठा rkisp1_cअगर_isp_stat params;
पूर्ण;

#पूर्ण_अगर /* _UAPI_RKISP1_CONFIG_H */
