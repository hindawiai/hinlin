<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright (C) 2017 - 2018 Intel Corporation */

#अगर_अघोषित __IPU3_UAPI_H
#घोषणा __IPU3_UAPI_H

#समावेश <linux/types.h>

/* from /drivers/staging/media/ipu3/include/videodev2.h */

/* Venकरोr specअगरic - used क्रम IPU3 camera sub-प्रणाली */
#घोषणा V4L2_META_FMT_IPU3_PARAMS	v4l2_fourcc('i', 'p', '3', 'p') /* IPU3 processing parameters */
#घोषणा V4L2_META_FMT_IPU3_STAT_3A	v4l2_fourcc('i', 'p', '3', 's') /* IPU3 3A statistics */

/* from include/uapi/linux/v4l2-controls.h */
#घोषणा V4L2_CID_INTEL_IPU3_BASE	(V4L2_CID_USER_BASE + 0x10c0)
#घोषणा V4L2_CID_INTEL_IPU3_MODE	(V4L2_CID_INTEL_IPU3_BASE + 1)

/******************* ipu3_uapi_stats_3a *******************/

#घोषणा IPU3_UAPI_MAX_STRIPES				2
#घोषणा IPU3_UAPI_MAX_BUBBLE_SIZE			10

#घोषणा IPU3_UAPI_GRID_START_MASK			((1 << 12) - 1)
#घोषणा IPU3_UAPI_GRID_Y_START_EN			(1 << 15)

/* controls generation of meta_data (like FF enable/disable) */
#घोषणा IPU3_UAPI_AWB_RGBS_THR_B_EN			(1 << 14)
#घोषणा IPU3_UAPI_AWB_RGBS_THR_B_INCL_SAT		(1 << 15)

/**
 * काष्ठा ipu3_uapi_grid_config - Grid plane config
 *
 * @width:	Grid horizontal dimensions, in number of grid blocks(cells).
 * @height:	Grid vertical dimensions, in number of grid cells.
 * @block_width_log2:	Log2 of the width of each cell in pixels.
 *			क्रम (2^3, 2^4, 2^5, 2^6, 2^7), values [3, 7].
 * @block_height_log2:	Log2 of the height of each cell in pixels.
 *			क्रम (2^3, 2^4, 2^5, 2^6, 2^7), values [3, 7].
 * @height_per_slice:	The number of blocks in vertical axis per slice.
 *			Default 2.
 * @x_start: X value of top left corner of Region of Interest(ROI).
 * @y_start: Y value of top left corner of ROI
 * @x_end: X value of bottom right corner of ROI
 * @y_end: Y value of bottom right corner of ROI
 *
 * Due to the size of total amount of collected data, most statistics
 * create a grid-based output, and the data is then भागided पूर्णांकo "slices".
 */
काष्ठा ipu3_uapi_grid_config अणु
	__u8 width;
	__u8 height;
	__u16 block_width_log2:3;
	__u16 block_height_log2:3;
	__u16 height_per_slice:8;
	__u16 x_start;
	__u16 y_start;
	__u16 x_end;
	__u16 y_end;
पूर्ण __packed;

/*
 * The grid based data is भागided पूर्णांकo "slices" called set, each slice of setX
 * refers to ipu3_uapi_grid_config width * height_per_slice.
 */
#घोषणा IPU3_UAPI_AWB_MAX_SETS				60
/* Based on grid size 80 * 60 and cell size 16 x 16 */
#घोषणा IPU3_UAPI_AWB_SET_SIZE				1280
#घोषणा IPU3_UAPI_AWB_MD_ITEM_SIZE			8
#घोषणा IPU3_UAPI_AWB_SPARE_FOR_BUBBLES \
	(IPU3_UAPI_MAX_BUBBLE_SIZE * IPU3_UAPI_MAX_STRIPES * \
	 IPU3_UAPI_AWB_MD_ITEM_SIZE)
#घोषणा IPU3_UAPI_AWB_MAX_BUFFER_SIZE \
	(IPU3_UAPI_AWB_MAX_SETS * \
	 (IPU3_UAPI_AWB_SET_SIZE + IPU3_UAPI_AWB_SPARE_FOR_BUBBLES))


/**
 * काष्ठा ipu3_uapi_awb_raw_buffer - AWB raw buffer
 *
 * @meta_data: buffer to hold स्वतः white balance meta data which is
 *		the average values क्रम each color channel.
 */
काष्ठा ipu3_uapi_awb_raw_buffer अणु
	__u8 meta_data[IPU3_UAPI_AWB_MAX_BUFFER_SIZE]
		__attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_awb_config_s - AWB config
 *
 * @rgbs_thr_gr: gr threshold value.
 * @rgbs_thr_r: Red threshold value.
 * @rgbs_thr_gb: gb threshold value.
 * @rgbs_thr_b: Blue threshold value.
 * @grid: &ipu3_uapi_grid_config, the शेष grid resolution is 16x16 cells.
 *
 * The threshold is a saturation measure range [0, 8191], 8191 is शेष.
 * Values over threshold may be optionally rejected क्रम averaging.
 */
काष्ठा ipu3_uapi_awb_config_s अणु
	__u16 rgbs_thr_gr;
	__u16 rgbs_thr_r;
	__u16 rgbs_thr_gb;
	__u16 rgbs_thr_b;
	काष्ठा ipu3_uapi_grid_config grid;
पूर्ण __attribute__((aligned(32))) __packed;

/**
 * काष्ठा ipu3_uapi_awb_config - AWB config wrapper
 *
 * @config: config क्रम स्वतः white balance as defined by &ipu3_uapi_awb_config_s
 */
काष्ठा ipu3_uapi_awb_config अणु
	काष्ठा ipu3_uapi_awb_config_s config __attribute__((aligned(32)));
पूर्ण __packed;

#घोषणा IPU3_UAPI_AE_COLORS				4	/* R, G, B, Y */
#घोषणा IPU3_UAPI_AE_BINS				256
#घोषणा IPU3_UAPI_AE_WEIGHTS				96

/**
 * काष्ठा ipu3_uapi_ae_raw_buffer - AE global weighted histogram
 *
 * @vals: Sum of IPU3_UAPI_AE_COLORS in cell
 *
 * Each histogram contains IPU3_UAPI_AE_BINS bins. Each bin has 24 bit अचिन्हित
 * क्रम counting the number of the pixel.
 */
काष्ठा ipu3_uapi_ae_raw_buffer अणु
	__u32 vals[IPU3_UAPI_AE_BINS * IPU3_UAPI_AE_COLORS];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_ae_raw_buffer_aligned - AE raw buffer
 *
 * @buff: &ipu3_uapi_ae_raw_buffer to hold full frame meta data.
 */
काष्ठा ipu3_uapi_ae_raw_buffer_aligned अणु
	काष्ठा ipu3_uapi_ae_raw_buffer buff __attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_ae_grid_config - AE weight grid
 *
 * @width: Grid horizontal dimensions. Value: [16, 32], शेष 16.
 * @height: Grid vertical dimensions. Value: [16, 24], शेष 16.
 * @block_width_log2: Log2 of the width of the grid cell, value: [3, 7].
 * @block_height_log2: Log2 of the height of the grid cell, value: [3, 7].
 *			शेष is 3 (cell size 8x8), 4 cell per grid.
 * @reserved0: reserved
 * @ae_en: 0: करोes not ग_लिखो to &ipu3_uapi_ae_raw_buffer_aligned array,
 *		1: ग_लिखो normally.
 * @rst_hist_array: ग_लिखो 1 to trigger histogram array reset.
 * @करोne_rst_hist_array: flag क्रम histogram array reset करोne.
 * @x_start: X value of top left corner of ROI, शेष 0.
 * @y_start: Y value of top left corner of ROI, शेष 0.
 * @x_end: X value of bottom right corner of ROI
 * @y_end: Y value of bottom right corner of ROI
 *
 * The AE block accumulates 4 global weighted histograms(R, G, B, Y) over
 * a defined ROI within the frame. The contribution of each pixel पूर्णांकo the
 * histogram, defined by &ipu3_uapi_ae_weight_elem LUT, is indexed by a grid.
 */
काष्ठा ipu3_uapi_ae_grid_config अणु
	__u8 width;
	__u8 height;
	__u8 block_width_log2:4;
	__u8 block_height_log2:4;
	__u8 reserved0:5;
	__u8 ae_en:1;
	__u8 rst_hist_array:1;
	__u8 करोne_rst_hist_array:1;
	__u16 x_start;
	__u16 y_start;
	__u16 x_end;
	__u16 y_end;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_ae_weight_elem - AE weights LUT
 *
 * @cell0: weighted histogram grid value.
 * @cell1: weighted histogram grid value.
 * @cell2: weighted histogram grid value.
 * @cell3: weighted histogram grid value.
 * @cell4: weighted histogram grid value.
 * @cell5: weighted histogram grid value.
 * @cell6: weighted histogram grid value.
 * @cell7: weighted histogram grid value.
 *
 * Use weighted grid value to give a dअगरferent contribution factor to each cell.
 * Precision u4, range [0, 15].
 */
काष्ठा ipu3_uapi_ae_weight_elem अणु
	__u32 cell0:4;
	__u32 cell1:4;
	__u32 cell2:4;
	__u32 cell3:4;
	__u32 cell4:4;
	__u32 cell5:4;
	__u32 cell6:4;
	__u32 cell7:4;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_ae_ccm - AE coefficients क्रम WB and CCM
 *
 * @gain_gr: WB gain factor क्रम the gr channels. Default 256.
 * @gain_r: WB gain factor क्रम the r channel. Default 256.
 * @gain_b: WB gain factor क्रम the b channel. Default 256.
 * @gain_gb: WB gain factor क्रम the gb channels. Default 256.
 * @mat: 4x4 matrix that transक्रमms Bayer quad output from WB to RGB+Y.
 *
 * Default:
 *	128, 0, 0, 0,
 *	0, 128, 0, 0,
 *	0, 0, 128, 0,
 *	0, 0, 0, 128,
 *
 * As part of the raw frame pre-process stage, the WB and color conversion need
 * to be applied to expose the impact of these gain operations.
 */
काष्ठा ipu3_uapi_ae_ccm अणु
	__u16 gain_gr;
	__u16 gain_r;
	__u16 gain_b;
	__u16 gain_gb;
	__s16 mat[16];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_ae_config - AE config
 *
 * @grid_cfg:	config क्रम स्वतः exposure statistics grid. See काष्ठा
 *		&ipu3_uapi_ae_grid_config
 * @weights:	&IPU3_UAPI_AE_WEIGHTS is based on 32x24 blocks in the grid.
 *		Each grid cell has a corresponding value in weights LUT called
 *		grid value, global histogram is updated based on grid value and
 *		pixel value.
 * @ae_ccm:	Color convert matrix pre-processing block.
 *
 * Calculate AE grid from image resolution, resample ae weights.
 */
काष्ठा ipu3_uapi_ae_config अणु
	काष्ठा ipu3_uapi_ae_grid_config grid_cfg __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_ae_weight_elem weights[
			IPU3_UAPI_AE_WEIGHTS] __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_ae_ccm ae_ccm __attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_af_filter_config - AF 2D filter क्रम contrast measurements
 *
 * @y1_coeff_0:	filter Y1, काष्ठाure: 3x11, support both symmetry and
 *		anti-symmetry type. A12 is center, A1-A11 are neighbours.
 *		क्रम analyzing low frequency content, used to calculate sum
 *		of gradients in x direction.
 * @y1_coeff_0.a1:	filter1 coefficients A1, u8, शेष 0.
 * @y1_coeff_0.a2:	filter1 coefficients A2, u8, शेष 0.
 * @y1_coeff_0.a3:	filter1 coefficients A3, u8, शेष 0.
 * @y1_coeff_0.a4:	filter1 coefficients A4, u8, शेष 0.
 * @y1_coeff_1:		Struct
 * @y1_coeff_1.a5:	filter1 coefficients A5, u8, शेष 0.
 * @y1_coeff_1.a6:	filter1 coefficients A6, u8, शेष 0.
 * @y1_coeff_1.a7:	filter1 coefficients A7, u8, शेष 0.
 * @y1_coeff_1.a8:	filter1 coefficients A8, u8, शेष 0.
 * @y1_coeff_2:		Struct
 * @y1_coeff_2.a9:	filter1 coefficients A9, u8, शेष 0.
 * @y1_coeff_2.a10:	filter1 coefficients A10, u8, शेष 0.
 * @y1_coeff_2.a11:	filter1 coefficients A11, u8, शेष 0.
 * @y1_coeff_2.a12:	filter1 coefficients A12, u8, शेष 128.
 * @y1_sign_vec:	Each bit corresponds to one coefficient sign bit,
 *			0: positive, 1: negative, शेष 0.
 * @y2_coeff_0:	Y2, same काष्ठाure as Y1. For analyzing high frequency content.
 * @y2_coeff_0.a1:	filter2 coefficients A1, u8, शेष 0.
 * @y2_coeff_0.a2:	filter2 coefficients A2, u8, शेष 0.
 * @y2_coeff_0.a3:	filter2 coefficients A3, u8, शेष 0.
 * @y2_coeff_0.a4:	filter2 coefficients A4, u8, शेष 0.
 * @y2_coeff_1:	Struct
 * @y2_coeff_1.a5:	filter2 coefficients A5, u8, शेष 0.
 * @y2_coeff_1.a6:	filter2 coefficients A6, u8, शेष 0.
 * @y2_coeff_1.a7:	filter2 coefficients A7, u8, शेष 0.
 * @y2_coeff_1.a8:	filter2 coefficients A8, u8, शेष 0.
 * @y2_coeff_2:	Struct
 * @y2_coeff_2.a9:	filter1 coefficients A9, u8, शेष 0.
 * @y2_coeff_2.a10:	filter1 coefficients A10, u8, शेष 0.
 * @y2_coeff_2.a11:	filter1 coefficients A11, u8, शेष 0.
 * @y2_coeff_2.a12:	filter1 coefficients A12, u8, शेष 128.
 * @y2_sign_vec:	Each bit corresponds to one coefficient sign bit,
 *			0: positive, 1: negative, शेष 0.
 * @y_calc:	Pre-processing that converts Bayer quad to RGB+Y values to be
 *		used क्रम building histogram. Range [0, 32], शेष 8.
 * Rule:
 *		y_gen_rate_gr + y_gen_rate_r + y_gen_rate_b + y_gen_rate_gb = 32
 *		A single Y is calculated based on sum of Gr/R/B/Gb based on
 *		their contribution ratio.
 * @y_calc.y_gen_rate_gr:	Contribution ratio Gr क्रम Y
 * @y_calc.y_gen_rate_r:	Contribution ratio R क्रम Y
 * @y_calc.y_gen_rate_b:	Contribution ratio B क्रम Y
 * @y_calc.y_gen_rate_gb:	Contribution ratio Gb क्रम Y
 * @nf:	The shअगरt right value that should be applied during the Y1/Y2 filter to
 *	make sure the total memory needed is 2 bytes per grid cell.
 * @nf.reserved0:	reserved
 * @nf.y1_nf:	Normalization factor क्रम the convolution coeffs of y1,
 *		should be log2 of the sum of the असल values of the filter
 *		coeffs, शेष 7 (2^7 = 128).
 * @nf.reserved1:	reserved
 * @nf.y2_nf:	Normalization factor क्रम y2, should be log2 of the sum of the
 *		असल values of the filter coeffs.
 * @nf.reserved2:	reserved
 */
काष्ठा ipu3_uapi_af_filter_config अणु
	काष्ठा अणु
		__u8 a1;
		__u8 a2;
		__u8 a3;
		__u8 a4;
	पूर्ण y1_coeff_0;
	काष्ठा अणु
		__u8 a5;
		__u8 a6;
		__u8 a7;
		__u8 a8;
	पूर्ण y1_coeff_1;
	काष्ठा अणु
		__u8 a9;
		__u8 a10;
		__u8 a11;
		__u8 a12;
	पूर्ण y1_coeff_2;

	__u32 y1_sign_vec;

	काष्ठा अणु
		__u8 a1;
		__u8 a2;
		__u8 a3;
		__u8 a4;
	पूर्ण y2_coeff_0;
	काष्ठा अणु
		__u8 a5;
		__u8 a6;
		__u8 a7;
		__u8 a8;
	पूर्ण y2_coeff_1;
	काष्ठा अणु
		__u8 a9;
		__u8 a10;
		__u8 a11;
		__u8 a12;
	पूर्ण y2_coeff_2;

	__u32 y2_sign_vec;

	काष्ठा अणु
		__u8 y_gen_rate_gr;
		__u8 y_gen_rate_r;
		__u8 y_gen_rate_b;
		__u8 y_gen_rate_gb;
	पूर्ण y_calc;

	काष्ठा अणु
		__u32 reserved0:8;
		__u32 y1_nf:4;
		__u32 reserved1:4;
		__u32 y2_nf:4;
		__u32 reserved2:12;
	पूर्ण nf;
पूर्ण __packed;

#घोषणा IPU3_UAPI_AF_MAX_SETS				24
#घोषणा IPU3_UAPI_AF_MD_ITEM_SIZE			4
#घोषणा IPU3_UAPI_AF_SPARE_FOR_BUBBLES \
	(IPU3_UAPI_MAX_BUBBLE_SIZE * IPU3_UAPI_MAX_STRIPES * \
	 IPU3_UAPI_AF_MD_ITEM_SIZE)
#घोषणा IPU3_UAPI_AF_Y_TABLE_SET_SIZE			128
#घोषणा IPU3_UAPI_AF_Y_TABLE_MAX_SIZE \
	(IPU3_UAPI_AF_MAX_SETS * \
	 (IPU3_UAPI_AF_Y_TABLE_SET_SIZE + IPU3_UAPI_AF_SPARE_FOR_BUBBLES) * \
	 IPU3_UAPI_MAX_STRIPES)

/**
 * काष्ठा ipu3_uapi_af_raw_buffer - AF meta data
 *
 * @y_table:	Each color component will be convolved separately with filter1
 *		and filter2 and the result will be summed out and averaged क्रम
 *		each cell.
 */
काष्ठा ipu3_uapi_af_raw_buffer अणु
	__u8 y_table[IPU3_UAPI_AF_Y_TABLE_MAX_SIZE] __attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_af_config_s - AF config
 *
 * @filter_config: AF uses Y1 and Y2 filters as configured in
 *		   &ipu3_uapi_af_filter_config
 * @padding: paddings
 * @grid_cfg: See &ipu3_uapi_grid_config, शेष resolution 16x16. Use large
 *	      grid size क्रम large image and vice versa.
 */
काष्ठा ipu3_uapi_af_config_s अणु
	काष्ठा ipu3_uapi_af_filter_config filter_config __attribute__((aligned(32)));
	__u8 padding[4];
	काष्ठा ipu3_uapi_grid_config grid_cfg __attribute__((aligned(32)));
पूर्ण __packed;

#घोषणा IPU3_UAPI_AWB_FR_MAX_SETS			24
#घोषणा IPU3_UAPI_AWB_FR_MD_ITEM_SIZE			8
#घोषणा IPU3_UAPI_AWB_FR_BAYER_TBL_SIZE			256
#घोषणा IPU3_UAPI_AWB_FR_SPARE_FOR_BUBBLES \
	(IPU3_UAPI_MAX_BUBBLE_SIZE * IPU3_UAPI_MAX_STRIPES * \
	 IPU3_UAPI_AWB_FR_MD_ITEM_SIZE)
#घोषणा IPU3_UAPI_AWB_FR_BAYER_TABLE_MAX_SIZE \
	(IPU3_UAPI_AWB_FR_MAX_SETS * \
	(IPU3_UAPI_AWB_FR_BAYER_TBL_SIZE + \
	 IPU3_UAPI_AWB_FR_SPARE_FOR_BUBBLES) * IPU3_UAPI_MAX_STRIPES)

/**
 * काष्ठा ipu3_uapi_awb_fr_raw_buffer - AWB filter response meta data
 *
 * @meta_data: Statistics output on the grid after convolving with 1D filter.
 */
काष्ठा ipu3_uapi_awb_fr_raw_buffer अणु
	__u8 meta_data[IPU3_UAPI_AWB_FR_BAYER_TABLE_MAX_SIZE]
		__attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_awb_fr_config_s - AWB filter response config
 *
 * @grid_cfg:	grid config, शेष 16x16.
 * @bayer_coeff:	1D Filter 1x11 center symmetry/anti-symmetry.
 *			coefficients शेषs अणु 0, 0, 0, 0, 0, 128 पूर्ण.
 *			Applied on whole image क्रम each Bayer channel separately
 *			by a weighted sum of its 11x1 neighbors.
 * @reserved1:	reserved
 * @bayer_sign:	sign of filter coefficients, शेष 0.
 * @bayer_nf:	normalization factor क्रम the convolution coeffs, to make sure
 *		total memory needed is within pre-determined range.
 *		NF should be the log2 of the sum of the असल values of the
 *		filter coeffs, range [7, 14], शेष 7.
 * @reserved2:	reserved
 */
काष्ठा ipu3_uapi_awb_fr_config_s अणु
	काष्ठा ipu3_uapi_grid_config grid_cfg;
	__u8 bayer_coeff[6];
	__u16 reserved1;
	__u32 bayer_sign;
	__u8 bayer_nf;
	__u8 reserved2[7];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_4a_config - 4A config
 *
 * @awb_config: &ipu3_uapi_awb_config_s, शेष resolution 16x16
 * @ae_grd_config: स्वतः exposure statistics &ipu3_uapi_ae_grid_config
 * @padding: paddings
 * @af_config: स्वतः focus config &ipu3_uapi_af_config_s
 * @awb_fr_config: &ipu3_uapi_awb_fr_config_s, शेष resolution 16x16
 */
काष्ठा ipu3_uapi_4a_config अणु
	काष्ठा ipu3_uapi_awb_config_s awb_config __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_ae_grid_config ae_grd_config;
	__u8 padding[20];
	काष्ठा ipu3_uapi_af_config_s af_config;
	काष्ठा ipu3_uapi_awb_fr_config_s awb_fr_config
		__attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bubble_info - Bubble info क्रम host side debugging
 *
 * @num_of_stripes: A single frame is भागided पूर्णांकo several parts called stripes
 *		    due to limitation on line buffer memory.
 *		    The separation between the stripes is vertical. Each such
 *		    stripe is processed as a single frame by the ISP pipe.
 * @padding: padding bytes.
 * @num_sets: number of sets.
 * @padding1: padding bytes.
 * @size_of_set: set size.
 * @padding2: padding bytes.
 * @bubble_size: is the amount of padding in the bubble expressed in "sets".
 * @padding3: padding bytes.
 */
काष्ठा ipu3_uapi_bubble_info अणु
	__u32 num_of_stripes __attribute__((aligned(32)));
	__u8 padding[28];
	__u32 num_sets;
	__u8 padding1[28];
	__u32 size_of_set;
	__u8 padding2[28];
	__u32 bubble_size;
	__u8 padding3[28];
पूर्ण __packed;

/*
 * काष्ठा ipu3_uapi_stats_3a_bubble_info_per_stripe
 */
काष्ठा ipu3_uapi_stats_3a_bubble_info_per_stripe अणु
	काष्ठा ipu3_uapi_bubble_info awb[IPU3_UAPI_MAX_STRIPES];
	काष्ठा ipu3_uapi_bubble_info af[IPU3_UAPI_MAX_STRIPES];
	काष्ठा ipu3_uapi_bubble_info awb_fr[IPU3_UAPI_MAX_STRIPES];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_ff_status - Enable bits क्रम each 3A fixed function
 *
 * @awb_en: स्वतः white balance enable
 * @padding: padding config
 * @ae_en: स्वतः exposure enable
 * @padding1: padding config
 * @af_en: स्वतः focus enable
 * @padding2: padding config
 * @awb_fr_en: awb filter response enable bit
 * @padding3: padding config
 */
काष्ठा ipu3_uapi_ff_status अणु
	__u32 awb_en __attribute__((aligned(32)));
	__u8 padding[28];
	__u32 ae_en;
	__u8 padding1[28];
	__u32 af_en;
	__u8 padding2[28];
	__u32 awb_fr_en;
	__u8 padding3[28];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_stats_3a - 3A statistics
 *
 * @awb_raw_buffer: स्वतः white balance meta data &ipu3_uapi_awb_raw_buffer
 * @ae_raw_buffer: स्वतः exposure raw data &ipu3_uapi_ae_raw_buffer_aligned
 * @af_raw_buffer: &ipu3_uapi_af_raw_buffer क्रम स्वतः focus meta data
 * @awb_fr_raw_buffer: value as specअगरied by &ipu3_uapi_awb_fr_raw_buffer
 * @stats_4a_config: 4a statistics config as defined by &ipu3_uapi_4a_config.
 * @ae_join_buffers: 1 to use ae_raw_buffer.
 * @padding: padding config
 * @stats_3a_bubble_per_stripe: a &ipu3_uapi_stats_3a_bubble_info_per_stripe
 * @stats_3a_status: 3a statistics status set in &ipu3_uapi_ff_status
 */
काष्ठा ipu3_uapi_stats_3a अणु
	काष्ठा ipu3_uapi_awb_raw_buffer awb_raw_buffer;
	काष्ठा ipu3_uapi_ae_raw_buffer_aligned
			ae_raw_buffer[IPU3_UAPI_MAX_STRIPES];
	काष्ठा ipu3_uapi_af_raw_buffer af_raw_buffer;
	काष्ठा ipu3_uapi_awb_fr_raw_buffer awb_fr_raw_buffer;
	काष्ठा ipu3_uapi_4a_config stats_4a_config;
	__u32 ae_join_buffers;
	__u8 padding[28];
	काष्ठा ipu3_uapi_stats_3a_bubble_info_per_stripe
			stats_3a_bubble_per_stripe;
	काष्ठा ipu3_uapi_ff_status stats_3a_status;
पूर्ण __packed;

/******************* ipu3_uapi_acc_param *******************/

#घोषणा IPU3_UAPI_ISP_VEC_ELEMS				64
#घोषणा IPU3_UAPI_ISP_TNR3_VMEM_LEN			9

#घोषणा IPU3_UAPI_BNR_LUT_SIZE				32

/* number of elements in gamma correction LUT */
#घोषणा IPU3_UAPI_GAMMA_CORR_LUT_ENTRIES		256

/* largest grid is 73x56, क्रम grid_height_per_slice of 2, 73x2 = 146 */
#घोषणा IPU3_UAPI_SHD_MAX_CELLS_PER_SET			146
#घोषणा IPU3_UAPI_SHD_MAX_CFG_SETS			28
/* Normalization shअगरt aka nf */
#घोषणा IPU3_UAPI_SHD_BLGR_NF_SHIFT			13
#घोषणा IPU3_UAPI_SHD_BLGR_NF_MASK			7

#घोषणा IPU3_UAPI_YUVP2_TCC_MACC_TABLE_ELEMENTS		16
#घोषणा IPU3_UAPI_YUVP2_TCC_INV_Y_LUT_ELEMENTS		14
#घोषणा IPU3_UAPI_YUVP2_TCC_GAIN_PCWL_LUT_ELEMENTS	258
#घोषणा IPU3_UAPI_YUVP2_TCC_R_SQR_LUT_ELEMENTS		24

#घोषणा IPU3_UAPI_ANR_LUT_SIZE				26
#घोषणा IPU3_UAPI_ANR_PYRAMID_SIZE			22

#घोषणा IPU3_UAPI_LIN_LUT_SIZE				64

/* Bayer Noise Reduction related काष्ठाs */

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_wb_gains_config - White balance gains
 *
 * @gr:	white balance gain क्रम Gr channel.
 * @r:	white balance gain क्रम R channel.
 * @b:	white balance gain क्रम B channel.
 * @gb:	white balance gain क्रम Gb channel.
 *
 * Precision u3.13, range [0, 8). White balance correction is करोne by applying
 * a multiplicative gain to each color channels prior to BNR.
 */
काष्ठा ipu3_uapi_bnr_अटल_config_wb_gains_config अणु
	__u16 gr;
	__u16 r;
	__u16 b;
	__u16 gb;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_wb_gains_thr_config - Threshold config
 *
 * @gr:	white balance threshold gain क्रम Gr channel.
 * @r:	white balance threshold gain क्रम R channel.
 * @b:	white balance threshold gain क्रम B channel.
 * @gb:	white balance threshold gain क्रम Gb channel.
 *
 * Defines the threshold that specअगरies how dअगरferent a defect pixel can be from
 * its neighbors.(used by dynamic defect pixel correction sub block)
 * Precision u4.4 range [0, 8].
 */
काष्ठा ipu3_uapi_bnr_अटल_config_wb_gains_thr_config अणु
	__u8 gr;
	__u8 r;
	__u8 b;
	__u8 gb;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_thr_coeffs_config - Noise model
 *				coefficients that controls noise threshold
 *
 * @cf:	Free coefficient क्रम threshold calculation, range [0, 8191], शेष 0.
 * @reserved0:	reserved
 * @cg:	Gain coefficient क्रम threshold calculation, [0, 31], शेष 8.
 * @ci:	Intensity coefficient क्रम threshold calculation. range [0, 0x1f]
 *	शेष 6.
 * 	क्रमmat: u3.2 (3 most signअगरicant bits represent whole number,
 *	2 least signअगरicant bits represent the fractional part
 *	with each count representing 0.25)
 *	e.g. 6 in binary क्रमmat is 00110, that translates to 1.5
 * @reserved1:	reserved
 * @r_nf:	Normalization shअगरt value क्रम r^2 calculation, range [12, 20]
 *		where r is a radius of pixel [row, col] from centor of sensor.
 *		शेष 14.
 *
 * Threshold used to distinguish between noise and details.
 */
काष्ठा ipu3_uapi_bnr_अटल_config_thr_coeffs_config अणु
	__u32 cf:13;
	__u32 reserved0:3;
	__u32 cg:5;
	__u32 ci:5;
	__u32 reserved1:1;
	__u32 r_nf:5;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_thr_ctrl_shd_config - Shading config
 *
 * @gr:	Coefficient defines lens shading gain approximation क्रम gr channel
 * @r:	Coefficient defines lens shading gain approximation क्रम r channel
 * @b:	Coefficient defines lens shading gain approximation क्रम b channel
 * @gb:	Coefficient defines lens shading gain approximation क्रम gb channel
 *
 * Parameters क्रम noise model (NM) adaptation of BNR due to shading correction.
 * All above have precision of u3.3, शेष to 0.
 */
काष्ठा ipu3_uapi_bnr_अटल_config_thr_ctrl_shd_config अणु
	__u8 gr;
	__u8 r;
	__u8 b;
	__u8 gb;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_opt_center_config - Optical center config
 *
 * @x_reset:	Reset value of X (col start - X center). Precision s12.0.
 * @reserved0:	reserved
 * @y_reset:	Reset value of Y (row start - Y center). Precision s12.0.
 * @reserved2:	reserved
 *
 * Distance from corner to optical center क्रम NM adaptation due to shading
 * correction (should be calculated based on shading tables)
 */
काष्ठा ipu3_uapi_bnr_अटल_config_opt_center_config अणु
	__s32 x_reset:13;
	__u32 reserved0:3;
	__s32 y_reset:13;
	__u32 reserved2:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_lut_config - BNR square root lookup table
 *
 * @values: pre-calculated values of square root function.
 *
 * LUT implementation of square root operation.
 */
काष्ठा ipu3_uapi_bnr_अटल_config_lut_config अणु
	__u8 values[IPU3_UAPI_BNR_LUT_SIZE];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_bp_ctrl_config - Detect bad pixels (bp)
 *
 * @bp_thr_gain:	Defines the threshold that specअगरies how dअगरferent a
 *			defect pixel can be from its neighbors. Threshold is
 *			dependent on de-noise threshold calculated by algorithm.
 *			Range [4, 31], शेष 4.
 * @reserved0:	reserved
 * @defect_mode:	Mode of addressed defect pixels,
 *			0 - single defect pixel is expected,
 *			1 - 2 adjacent defect pixels are expected, शेष 1.
 * @bp_gain:	Defines how 2nd derivation that passes through a defect pixel
 *		is dअगरferent from 2nd derivations that pass through
 *		neighbor pixels. u4.2, range [0, 256], शेष 8.
 * @reserved1:	reserved
 * @w0_coeff:	Blending coefficient of defect pixel correction.
 *		Precision u4, range [0, 8], शेष 8.
 * @reserved2:	reserved
 * @w1_coeff:	Enable influence of incorrect defect pixel correction to be
 *		aव्योमed. Precision u4, range [1, 8], शेष 8.
 * @reserved3:	reserved
 */
काष्ठा ipu3_uapi_bnr_अटल_config_bp_ctrl_config अणु
	__u32 bp_thr_gain:5;
	__u32 reserved0:2;
	__u32 defect_mode:1;
	__u32 bp_gain:6;
	__u32 reserved1:18;
	__u32 w0_coeff:4;
	__u32 reserved2:4;
	__u32 w1_coeff:4;
	__u32 reserved3:20;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_dn_detect_ctrl_config - Denoising config
 *
 * @alpha:	Weight of central element of smoothing filter.
 * @beta:	Weight of peripheral elements of smoothing filter, शेष 4.
 * @gamma:	Weight of diagonal elements of smoothing filter, शेष 4.
 *
 * beta and gamma parameter define the strength of the noise removal filter.
 *		All above has precision u0.4, range [0, 0xf]
 *		क्रमmat: u0.4 (no / zero bits represent whole number,
 *		4 bits represent the fractional part
 *		with each count representing 0.0625)
 *		e.g. 0xf translates to 0.0625x15 = 0.9375
 *
 * @reserved0:	reserved
 * @max_inf:	Maximum increase of peripheral or diagonal element influence
 *		relative to the pre-defined value range: [0x5, 0xa]
 * @reserved1:	reserved
 * @gd_enable:	Green disparity enable control, 0 - disable, 1 - enable.
 * @bpc_enable:	Bad pixel correction enable control, 0 - disable, 1 - enable.
 * @bnr_enable:	Bayer noise removal enable control, 0 - disable, 1 - enable.
 * @ff_enable:	Fixed function enable, 0 - disable, 1 - enable.
 * @reserved2:	reserved
 */
काष्ठा ipu3_uapi_bnr_अटल_config_dn_detect_ctrl_config अणु
	__u32 alpha:4;
	__u32 beta:4;
	__u32 gamma:4;
	__u32 reserved0:4;
	__u32 max_inf:4;
	__u32 reserved1:7;
	__u32 gd_enable:1;
	__u32 bpc_enable:1;
	__u32 bnr_enable:1;
	__u32 ff_enable:1;
	__u32 reserved2:1;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_opt_center_sqr_config - BNR optical square
 *
 * @x_sqr_reset: Reset value of X^2.
 * @y_sqr_reset: Reset value of Y^2.
 *
 * Please note:
 *
 *    #. X and Y ref to
 *       &ipu3_uapi_bnr_अटल_config_opt_center_config
 *    #. Both काष्ठाs are used in threshold क्रमmula to calculate r^2, where r
 *       is a radius of pixel [row, col] from centor of sensor.
 */
काष्ठा ipu3_uapi_bnr_अटल_config_opt_center_sqr_config अणु
	__u32 x_sqr_reset;
	__u32 y_sqr_reset;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config - BNR अटल config
 *
 * @wb_gains:	white balance gains &ipu3_uapi_bnr_अटल_config_wb_gains_config
 * @wb_gains_thr:	white balance gains threshold as defined by
 *			&ipu3_uapi_bnr_अटल_config_wb_gains_thr_config
 * @thr_coeffs:	coefficients of threshold
 *		&ipu3_uapi_bnr_अटल_config_thr_coeffs_config
 * @thr_ctrl_shd:	control of shading threshold
 *			&ipu3_uapi_bnr_अटल_config_thr_ctrl_shd_config
 * @opt_center:	optical center &ipu3_uapi_bnr_अटल_config_opt_center_config
 *
 * Above parameters and opt_center_sqr are used क्रम white balance and shading.
 *
 * @lut:	lookup table &ipu3_uapi_bnr_अटल_config_lut_config
 * @bp_ctrl:	detect and हटाओ bad pixels as defined in काष्ठा
 *		&ipu3_uapi_bnr_अटल_config_bp_ctrl_config
 * @dn_detect_ctrl:	detect and हटाओ noise.
 *			&ipu3_uapi_bnr_अटल_config_dn_detect_ctrl_config
 * @column_size:	The number of pixels in column.
 * @opt_center_sqr:	Reset value of r^2 to optical center, see
 *			&ipu3_uapi_bnr_अटल_config_opt_center_sqr_config.
 */
काष्ठा ipu3_uapi_bnr_अटल_config अणु
	काष्ठा ipu3_uapi_bnr_अटल_config_wb_gains_config wb_gains;
	काष्ठा ipu3_uapi_bnr_अटल_config_wb_gains_thr_config wb_gains_thr;
	काष्ठा ipu3_uapi_bnr_अटल_config_thr_coeffs_config thr_coeffs;
	काष्ठा ipu3_uapi_bnr_अटल_config_thr_ctrl_shd_config thr_ctrl_shd;
	काष्ठा ipu3_uapi_bnr_अटल_config_opt_center_config opt_center;
	काष्ठा ipu3_uapi_bnr_अटल_config_lut_config lut;
	काष्ठा ipu3_uapi_bnr_अटल_config_bp_ctrl_config bp_ctrl;
	काष्ठा ipu3_uapi_bnr_अटल_config_dn_detect_ctrl_config dn_detect_ctrl;
	__u32 column_size;
	काष्ठा ipu3_uapi_bnr_अटल_config_opt_center_sqr_config opt_center_sqr;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_bnr_अटल_config_green_disparity - Correct green disparity
 *
 * @gd_red:	Shading gain coeff क्रम gr disparity level in bright red region.
 *		Precision u0.6, शेष 4(0.0625).
 * @reserved0:	reserved
 * @gd_green:	Shading gain coeff क्रम gr disparity level in bright green
 *		region. Precision u0.6, शेष 4(0.0625).
 * @reserved1:	reserved
 * @gd_blue:	Shading gain coeff क्रम gr disparity level in bright blue region.
 *		Precision u0.6, शेष 4(0.0625).
 * @reserved2:	reserved
 * @gd_black:	Maximal green disparity level in dark region (stronger disparity
 *		assumed to be image detail). Precision u14, शेष 80.
 * @reserved3:	reserved
 * @gd_shading:	Change maximal green disparity level according to square
 *		distance from image center.
 * @reserved4:	reserved
 * @gd_support:	Lower bound क्रम the number of second green color pixels in
 *		current pixel neighborhood with less than threshold dअगरference
 *		from it.
 *
 * The shading gain coeff of red, green, blue and black are used to calculate
 * threshold given a pixel's color value and its coordinates in the image.
 *
 * @reserved5:	reserved
 * @gd_clip:	Turn green disparity clip on/off, [0, 1], शेष 1.
 * @gd_central_weight:	Central pixel weight in 9 pixels weighted sum.
 */
काष्ठा ipu3_uapi_bnr_अटल_config_green_disparity अणु
	__u32 gd_red:6;
	__u32 reserved0:2;
	__u32 gd_green:6;
	__u32 reserved1:2;
	__u32 gd_blue:6;
	__u32 reserved2:10;
	__u32 gd_black:14;
	__u32 reserved3:2;
	__u32 gd_shading:7;
	__u32 reserved4:1;
	__u32 gd_support:2;
	__u32 reserved5:1;
	__u32 gd_clip:1;
	__u32 gd_central_weight:4;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_dm_config - De-mosaic parameters
 *
 * @dm_en:	de-mosaic enable.
 * @ch_ar_en:	Checker artअगरacts removal enable flag. Default 0.
 * @fcc_en:	False color correction (FCC) enable flag. Default 0.
 * @reserved0:	reserved
 * @frame_width:	करो not care
 * @gamma_sc:	Sharpening coefficient (coefficient of 2-d derivation of
 *		complementary color in Hamilton-Adams पूर्णांकerpolation).
 *		u5, range [0, 31], शेष 8.
 * @reserved1:	reserved
 * @lc_ctrl:	Parameter that controls weights of Chroma Homogeneity metric
 *		in calculation of final homogeneity metric.
 *		u5, range [0, 31], शेष 7.
 * @reserved2:	reserved
 * @cr_param1:	First parameter that defines Checker artअगरact removal
 *		feature gain. Precision u5, range [0, 31], शेष 8.
 * @reserved3:	reserved
 * @cr_param2:	Second parameter that defines Checker artअगरact removal
 *		feature gain. Precision u5, range [0, 31], शेष 8.
 * @reserved4:	reserved
 * @coring_param:	Defines घातer of false color correction operation.
 *			low क्रम preserving edge colors, high क्रम preserving gray
 *			edge artअगरacts.
 *			Precision u1.4, range [0, 1.9375], शेष 4 (0.25).
 * @reserved5:	reserved
 *
 * The demosaic fixed function block is responsible to covert Bayer(mosaiced)
 * images पूर्णांकo color images based on demosaicing algorithm.
 */
काष्ठा ipu3_uapi_dm_config अणु
	__u32 dm_en:1;
	__u32 ch_ar_en:1;
	__u32 fcc_en:1;
	__u32 reserved0:13;
	__u32 frame_width:16;

	__u32 gamma_sc:5;
	__u32 reserved1:3;
	__u32 lc_ctrl:5;
	__u32 reserved2:3;
	__u32 cr_param1:5;
	__u32 reserved3:3;
	__u32 cr_param2:5;
	__u32 reserved4:3;

	__u32 coring_param:5;
	__u32 reserved5:27;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_ccm_mat_config - Color correction matrix
 *
 * @coeff_m11: CCM 3x3 coefficient, range [-65536, 65535]
 * @coeff_m12: CCM 3x3 coefficient, range [-8192, 8191]
 * @coeff_m13: CCM 3x3 coefficient, range [-32768, 32767]
 * @coeff_o_r: Bias 3x1 coefficient, range [-8191, 8181]
 * @coeff_m21: CCM 3x3 coefficient, range [-32767, 32767]
 * @coeff_m22: CCM 3x3 coefficient, range [-8192, 8191]
 * @coeff_m23: CCM 3x3 coefficient, range [-32768, 32767]
 * @coeff_o_g: Bias 3x1 coefficient, range [-8191, 8181]
 * @coeff_m31: CCM 3x3 coefficient, range [-32768, 32767]
 * @coeff_m32: CCM 3x3 coefficient, range [-8192, 8191]
 * @coeff_m33: CCM 3x3 coefficient, range [-32768, 32767]
 * @coeff_o_b: Bias 3x1 coefficient, range [-8191, 8181]
 *
 * Transक्रमm sensor specअगरic color space to standard sRGB by applying 3x3 matrix
 * and adding a bias vector O. The transक्रमmation is basically a rotation and
 * translation in the 3-dimensional color spaces. Here are the शेषs:
 *
 *	9775,	-2671,	1087,	0
 *	-1071,	8303,	815,	0
 *	-23,	-7887,	16103,	0
 */
काष्ठा ipu3_uapi_ccm_mat_config अणु
	__s16 coeff_m11;
	__s16 coeff_m12;
	__s16 coeff_m13;
	__s16 coeff_o_r;
	__s16 coeff_m21;
	__s16 coeff_m22;
	__s16 coeff_m23;
	__s16 coeff_o_g;
	__s16 coeff_m31;
	__s16 coeff_m32;
	__s16 coeff_m33;
	__s16 coeff_o_b;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_gamma_corr_ctrl - Gamma correction
 *
 * @enable: gamma correction enable.
 * @reserved: reserved
 */
काष्ठा ipu3_uapi_gamma_corr_ctrl अणु
	__u32 enable:1;
	__u32 reserved:31;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_gamma_corr_lut - Per-pixel tone mapping implemented as LUT.
 *
 * @lut:	256 tabulated values of the gamma function. LUT[1].. LUT[256]
 *		क्रमmat u13.0, range [0, 8191].
 *
 * The tone mapping operation is करोne by a Piece wise linear graph
 * that is implemented as a lookup table(LUT). The pixel component input
 * पूर्णांकensity is the X-axis of the graph which is the table entry.
 */
काष्ठा ipu3_uapi_gamma_corr_lut अणु
	__u16 lut[IPU3_UAPI_GAMMA_CORR_LUT_ENTRIES];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_gamma_config - Gamma config
 *
 * @gc_ctrl: control of gamma correction &ipu3_uapi_gamma_corr_ctrl
 * @gc_lut: lookup table of gamma correction &ipu3_uapi_gamma_corr_lut
 */
काष्ठा ipu3_uapi_gamma_config अणु
	काष्ठा ipu3_uapi_gamma_corr_ctrl gc_ctrl __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_gamma_corr_lut gc_lut __attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_csc_mat_config - Color space conversion matrix config
 *
 * @coeff_c11:	Conversion matrix value, क्रमmat s0.14, range [-16384, 16383].
 * @coeff_c12:	Conversion matrix value, क्रमmat s0.14, range [-8192, 8191].
 * @coeff_c13:	Conversion matrix value, क्रमmat s0.14, range [-16384, 16383].
 * @coeff_b1:	Bias 3x1 coefficient, s13.0 range [-8192, 8191].
 * @coeff_c21:	Conversion matrix value, क्रमmat s0.14, range [-16384, 16383].
 * @coeff_c22:	Conversion matrix value, क्रमmat s0.14, range [-8192, 8191].
 * @coeff_c23:	Conversion matrix value, क्रमmat s0.14, range [-16384, 16383].
 * @coeff_b2:	Bias 3x1 coefficient, s13.0 range [-8192, 8191].
 * @coeff_c31:	Conversion matrix value, क्रमmat s0.14, range [-16384, 16383].
 * @coeff_c32:	Conversion matrix value, क्रमmat s0.14, range [-8192, 8191].
 * @coeff_c33:	Conversion matrix value, क्रमmat s0.14, range [-16384, 16383].
 * @coeff_b3:	Bias 3x1 coefficient, s13.0 range [-8192, 8191].
 *
 * To transक्रमm each pixel from RGB to YUV (Y - brightness/luminance,
 * UV -chroma) by applying the pixel's values by a 3x3 matrix and adding an
 * optional bias 3x1 vector. Here are the शेष values क्रम the matrix:
 *
 *	4898,   9617,  1867, 0,
 *	-2410, -4732,  7143, 0,
 *	10076, -8437, -1638, 0,
 *
 *	(i.e. क्रम real number 0.299, 0.299 * 2^14 becomes 4898.)
 */
काष्ठा ipu3_uapi_csc_mat_config अणु
	__s16 coeff_c11;
	__s16 coeff_c12;
	__s16 coeff_c13;
	__s16 coeff_b1;
	__s16 coeff_c21;
	__s16 coeff_c22;
	__s16 coeff_c23;
	__s16 coeff_b2;
	__s16 coeff_c31;
	__s16 coeff_c32;
	__s16 coeff_c33;
	__s16 coeff_b3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_cds_params - Chroma करोwn-scaling
 *
 * @ds_c00:	range [0, 3]
 * @ds_c01:	range [0, 3]
 * @ds_c02:	range [0, 3]
 * @ds_c03:	range [0, 3]
 * @ds_c10:	range [0, 3]
 * @ds_c11:	range [0, 3]
 * @ds_c12:	range [0, 3]
 * @ds_c13:	range [0, 3]
 *
 * In हाल user करोes not provide, above 4x2 filter will use following शेषs:
 *	1, 3, 3, 1,
 *	1, 3, 3, 1,
 *
 * @ds_nf:	Normalization factor क्रम Chroma output करोwnscaling filter,
 *		range 0,4, शेष 2.
 * @reserved0:	reserved
 * @csc_en:	Color space conversion enable
 * @uv_bin_output:	0: output YUV 4.2.0, 1: output YUV 4.2.2(शेष).
 * @reserved1:	reserved
 */
काष्ठा ipu3_uapi_cds_params अणु
	__u32 ds_c00:2;
	__u32 ds_c01:2;
	__u32 ds_c02:2;
	__u32 ds_c03:2;
	__u32 ds_c10:2;
	__u32 ds_c11:2;
	__u32 ds_c12:2;
	__u32 ds_c13:2;
	__u32 ds_nf:5;
	__u32 reserved0:3;
	__u32 csc_en:1;
	__u32 uv_bin_output:1;
	__u32 reserved1:6;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_shd_grid_config - Bayer shading(darkening) correction
 *
 * @width:	Grid horizontal dimensions, u8, [8, 128], शेष 73
 * @height:	Grid vertical dimensions, u8, [8, 128], शेष 56
 * @block_width_log2:	Log2 of the width of the grid cell in pixel count
 *			u4, [0, 15], शेष value 5.
 * @reserved0:	reserved
 * @block_height_log2:	Log2 of the height of the grid cell in pixel count
 *			u4, [0, 15], शेष value 6.
 * @reserved1:	reserved
 * @grid_height_per_slice:	SHD_MAX_CELLS_PER_SET/width.
 *				(with SHD_MAX_CELLS_PER_SET = 146).
 * @x_start:	X value of top left corner of sensor relative to ROI
 *		s13, [-4096, 0], शेष 0, only negative values.
 * @y_start:	Y value of top left corner of sensor relative to ROI
 *		s13, [-4096, 0], शेष 0, only negative values.
 */
काष्ठा ipu3_uapi_shd_grid_config अणु
	/* reg 0 */
	__u8 width;
	__u8 height;
	__u8 block_width_log2:3;
	__u8 reserved0:1;
	__u8 block_height_log2:3;
	__u8 reserved1:1;
	__u8 grid_height_per_slice;
	/* reg 1 */
	__s16 x_start;
	__s16 y_start;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_shd_general_config - Shading general config
 *
 * @init_set_vrt_offst_ul: set vertical offset,
 *			y_start >> block_height_log2 % grid_height_per_slice.
 * @shd_enable: shading enable.
 * @gain_factor: Gain factor. Shअगरt calculated anti shading value. Precision u2.
 *		0x0 - gain factor [1, 5], means no shअगरt पूर्णांकerpolated value.
 *		0x1 - gain factor [1, 9], means shअगरt पूर्णांकerpolated by 1.
 *		0x2 - gain factor [1, 17], means shअगरt पूर्णांकerpolated by 2.
 * @reserved: reserved
 *
 * Correction is perक्रमmed by multiplying a gain factor क्रम each of the 4 Bayer
 * channels as a function of the pixel location in the sensor.
 */
काष्ठा ipu3_uapi_shd_general_config अणु
	__u32 init_set_vrt_offst_ul:8;
	__u32 shd_enable:1;
	__u32 gain_factor:2;
	__u32 reserved:21;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_shd_black_level_config - Black level correction
 *
 * @bl_r:	Bios values क्रम green red. s11 range [-2048, 2047].
 * @bl_gr:	Bios values क्रम green blue. s11 range [-2048, 2047].
 * @bl_gb:	Bios values क्रम red. s11 range [-2048, 2047].
 * @bl_b:	Bios values क्रम blue. s11 range [-2048, 2047].
 */
काष्ठा ipu3_uapi_shd_black_level_config अणु
	__s16 bl_r;
	__s16 bl_gr;
	__s16 bl_gb;
	__s16 bl_b;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_shd_config_अटल - Shading config अटल
 *
 * @grid:	shading grid config &ipu3_uapi_shd_grid_config
 * @general:	shading general config &ipu3_uapi_shd_general_config
 * @black_level:	black level config क्रम shading correction as defined by
 *			&ipu3_uapi_shd_black_level_config
 */
काष्ठा ipu3_uapi_shd_config_अटल अणु
	काष्ठा ipu3_uapi_shd_grid_config grid;
	काष्ठा ipu3_uapi_shd_general_config general;
	काष्ठा ipu3_uapi_shd_black_level_config black_level;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_shd_lut - Shading gain factor lookup table.
 *
 * @sets: array
 * @sets.r_and_gr: Red and GreenR Lookup table.
 * @sets.r_and_gr.r: Red shading factor.
 * @sets.r_and_gr.gr: GreenR shading factor.
 * @sets.reserved1: reserved
 * @sets.gb_and_b: GreenB and Blue Lookup table.
 * @sets.gb_and_b.gb: GreenB shading factor.
 * @sets.gb_and_b.b: Blue shading factor.
 * @sets.reserved2: reserved
 *
 * Map to shading correction LUT रेजिस्टर set.
 */
काष्ठा ipu3_uapi_shd_lut अणु
	काष्ठा अणु
		काष्ठा अणु
			__u16 r;
			__u16 gr;
		पूर्ण r_and_gr[IPU3_UAPI_SHD_MAX_CELLS_PER_SET];
		__u8 reserved1[24];
		काष्ठा अणु
			__u16 gb;
			__u16 b;
		पूर्ण gb_and_b[IPU3_UAPI_SHD_MAX_CELLS_PER_SET];
		__u8 reserved2[24];
	पूर्ण sets[IPU3_UAPI_SHD_MAX_CFG_SETS];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_shd_config - Shading config
 *
 * @shd:	shading अटल config, see &ipu3_uapi_shd_config_अटल
 * @shd_lut:	shading lookup table &ipu3_uapi_shd_lut
 */
काष्ठा ipu3_uapi_shd_config अणु
	काष्ठा ipu3_uapi_shd_config_अटल shd __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_shd_lut shd_lut __attribute__((aligned(32)));
पूर्ण __packed;

/* Image Enhancement Filter directed */

/**
 * काष्ठा ipu3_uapi_iefd_cux2 - IEFd Config Unit 2 parameters
 *
 * @x0:		X0 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @x1:		X1 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @a01:	Slope A of Config Unit, s4.4, शेष 0.
 * @b01:	Slope B, always 0.
 *
 * Calculate weight क्रम blending directed and non-directed denoise elements
 *
 * Note:
 * Each instance of Config Unit needs X coordinate of n poपूर्णांकs and
 * slope A factor between poपूर्णांकs calculated by driver based on calibration
 * parameters.
 *
 * All CU inमाला_दो are अचिन्हित, they will be converted to चिन्हित when written
 * to रेजिस्टर, i.e. a01 will be written to 9 bit रेजिस्टर in s4.4 क्रमmat.
 * The data precision s4.4 means 4 bits क्रम पूर्णांकeger parts and 4 bits क्रम the
 * fractional part, the first bit indicates positive or negative value.
 * For userspace software (commonly the imaging library), the computation क्रम
 * the CU slope values should be based on the slope resolution 1/16 (binary
 * 0.0001 - the minimal पूर्णांकerval value), the slope value range is [-256, +255].
 * This applies to &ipu3_uapi_iefd_cux6_ed, &ipu3_uapi_iefd_cux2_1,
 * &ipu3_uapi_iefd_cux2_1, &ipu3_uapi_iefd_cux4 and &ipu3_uapi_iefd_cux6_rad.
 */
काष्ठा ipu3_uapi_iefd_cux2 अणु
	__u32 x0:9;
	__u32 x1:9;
	__u32 a01:9;
	__u32 b01:5;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_iefd_cux6_ed - Calculate घातer of non-directed sharpening
 *				   element, Config Unit 6 क्रम edge detail (ED).
 *
 * @x0:	X coordinate of poपूर्णांक 0, u9.0, शेष 0.
 * @x1:	X coordinate of poपूर्णांक 1, u9.0, शेष 0.
 * @x2:	X coordinate of poपूर्णांक 2, u9.0, शेष 0.
 * @reserved0:	reserved
 * @x3:	X coordinate of poपूर्णांक 3, u9.0, शेष 0.
 * @x4:	X coordinate of poपूर्णांक 4, u9.0, शेष 0.
 * @x5:	X coordinate of poपूर्णांक 5, u9.0, शेष 0.
 * @reserved1:	reserved
 * @a01:	slope A poपूर्णांकs 01, s4.4, शेष 0.
 * @a12:	slope A poपूर्णांकs 12, s4.4, शेष 0.
 * @a23:	slope A poपूर्णांकs 23, s4.4, शेष 0.
 * @reserved2:	reserved
 * @a34:	slope A poपूर्णांकs 34, s4.4, शेष 0.
 * @a45:	slope A poपूर्णांकs 45, s4.4, शेष 0.
 * @reserved3:	reserved
 * @b01:	slope B poपूर्णांकs 01, s4.4, शेष 0.
 * @b12:	slope B poपूर्णांकs 12, s4.4, शेष 0.
 * @b23:	slope B poपूर्णांकs 23, s4.4, शेष 0.
 * @reserved4:	reserved
 * @b34:	slope B poपूर्णांकs 34, s4.4, शेष 0.
 * @b45:	slope B poपूर्णांकs 45, s4.4, शेष 0.
 * @reserved5:	reserved.
 */
काष्ठा ipu3_uapi_iefd_cux6_ed अणु
	__u32 x0:9;
	__u32 x1:9;
	__u32 x2:9;
	__u32 reserved0:5;

	__u32 x3:9;
	__u32 x4:9;
	__u32 x5:9;
	__u32 reserved1:5;

	__u32 a01:9;
	__u32 a12:9;
	__u32 a23:9;
	__u32 reserved2:5;

	__u32 a34:9;
	__u32 a45:9;
	__u32 reserved3:14;

	__u32 b01:9;
	__u32 b12:9;
	__u32 b23:9;
	__u32 reserved4:5;

	__u32 b34:9;
	__u32 b45:9;
	__u32 reserved5:14;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_iefd_cux2_1 - Calculate घातer of non-directed denoise
 *				  element apply.
 * @x0: X0 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @x1: X1 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @a01: Slope A of Config Unit, s4.4, शेष 0.
 * @reserved1: reserved
 * @b01: offset B0 of Config Unit, u7.0, शेष 0.
 * @reserved2: reserved
 */
काष्ठा ipu3_uapi_iefd_cux2_1 अणु
	__u32 x0:9;
	__u32 x1:9;
	__u32 a01:9;
	__u32 reserved1:5;

	__u32 b01:8;
	__u32 reserved2:24;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_iefd_cux4 - Calculate घातer of non-directed sharpening
 *				element.
 *
 * @x0:	X0 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @x1:	X1 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @x2:	X2 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @reserved0:	reserved
 * @x3:	X3 poपूर्णांक of Config Unit, u9.0, शेष 0.
 * @a01:	Slope A0 of Config Unit, s4.4, शेष 0.
 * @a12:	Slope A1 of Config Unit, s4.4, शेष 0.
 * @reserved1:	reserved
 * @a23:	Slope A2 of Config Unit, s4.4, शेष 0.
 * @b01:	Offset B0 of Config Unit, s7.0, शेष 0.
 * @b12:	Offset B1 of Config Unit, s7.0, शेष 0.
 * @reserved2:	reserved
 * @b23:	Offset B2 of Config Unit, s7.0, शेष 0.
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_iefd_cux4 अणु
	__u32 x0:9;
	__u32 x1:9;
	__u32 x2:9;
	__u32 reserved0:5;

	__u32 x3:9;
	__u32 a01:9;
	__u32 a12:9;
	__u32 reserved1:5;

	__u32 a23:9;
	__u32 b01:8;
	__u32 b12:8;
	__u32 reserved2:7;

	__u32 b23:8;
	__u32 reserved3:24;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_iefd_cux6_rad - Radial Config Unit (CU)
 *
 * @x0:	x0 poपूर्णांकs of Config Unit radial, u8.0
 * @x1:	x1 poपूर्णांकs of Config Unit radial, u8.0
 * @x2:	x2 poपूर्णांकs of Config Unit radial, u8.0
 * @x3:	x3 poपूर्णांकs of Config Unit radial, u8.0
 * @x4:	x4 poपूर्णांकs of Config Unit radial, u8.0
 * @x5:	x5 poपूर्णांकs of Config Unit radial, u8.0
 * @reserved1: reserved
 * @a01:	Slope A of Config Unit radial, s7.8
 * @a12:	Slope A of Config Unit radial, s7.8
 * @a23:	Slope A of Config Unit radial, s7.8
 * @a34:	Slope A of Config Unit radial, s7.8
 * @a45:	Slope A of Config Unit radial, s7.8
 * @reserved2: reserved
 * @b01:	Slope B of Config Unit radial, s9.0
 * @b12:	Slope B of Config Unit radial, s9.0
 * @b23:	Slope B of Config Unit radial, s9.0
 * @reserved4: reserved
 * @b34:	Slope B of Config Unit radial, s9.0
 * @b45:	Slope B of Config Unit radial, s9.0
 * @reserved5: reserved
 */
काष्ठा ipu3_uapi_iefd_cux6_rad अणु
	__u32 x0:8;
	__u32 x1:8;
	__u32 x2:8;
	__u32 x3:8;

	__u32 x4:8;
	__u32 x5:8;
	__u32 reserved1:16;

	__u32 a01:16;
	__u32 a12:16;

	__u32 a23:16;
	__u32 a34:16;

	__u32 a45:16;
	__u32 reserved2:16;

	__u32 b01:10;
	__u32 b12:10;
	__u32 b23:10;
	__u32 reserved4:2;

	__u32 b34:10;
	__u32 b45:10;
	__u32 reserved5:12;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_cfg_units - IEFd Config Units parameters
 *
 * @cu_1: calculate weight क्रम blending directed and
 *	  non-directed denoise elements. See &ipu3_uapi_iefd_cux2
 * @cu_ed: calculate घातer of non-directed sharpening element, see
 *	   &ipu3_uapi_iefd_cux6_ed
 * @cu_3: calculate weight क्रम blending directed and
 *	  non-directed denoise elements. A &ipu3_uapi_iefd_cux2
 * @cu_5: calculate घातer of non-directed denoise element apply, use
 *	  &ipu3_uapi_iefd_cux2_1
 * @cu_6: calculate घातer of non-directed sharpening element. See
 *	  &ipu3_uapi_iefd_cux4
 * @cu_7: calculate weight क्रम blending directed and
 *	  non-directed denoise elements. Use &ipu3_uapi_iefd_cux2
 * @cu_unsharp: Config Unit of unsharp &ipu3_uapi_iefd_cux4
 * @cu_radial: Config Unit of radial &ipu3_uapi_iefd_cux6_rad
 * @cu_vssnlm: Config Unit of vssnlm &ipu3_uapi_iefd_cux2
 */
काष्ठा ipu3_uapi_yuvp1_iefd_cfg_units अणु
	काष्ठा ipu3_uapi_iefd_cux2 cu_1;
	काष्ठा ipu3_uapi_iefd_cux6_ed cu_ed;
	काष्ठा ipu3_uapi_iefd_cux2 cu_3;
	काष्ठा ipu3_uapi_iefd_cux2_1 cu_5;
	काष्ठा ipu3_uapi_iefd_cux4 cu_6;
	काष्ठा ipu3_uapi_iefd_cux2 cu_7;
	काष्ठा ipu3_uapi_iefd_cux4 cu_unsharp;
	काष्ठा ipu3_uapi_iefd_cux6_rad cu_radial;
	काष्ठा ipu3_uapi_iefd_cux2 cu_vssnlm;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_config_s - IEFd config
 *
 * @horver_diag_coeff: Gradient compensation. Compared with vertical /
 *		       horizontal (0 / 90 degree), coefficient of diagonal (45 /
 *		       135 degree) direction should be corrected by approx.
 *		       1/वर्ग_मूल(2).
 * @reserved0: reserved
 * @clamp_stitch: Slope to stitch between clamped and unclamped edge values
 * @reserved1: reserved
 * @direct_metric_update: Update coeff क्रम direction metric
 * @reserved2: reserved
 * @ed_horver_diag_coeff: Radial Coefficient that compensates क्रम
 *			  dअगरferent distance क्रम vertical/horizontal and
 *			  diagonal gradient calculation (approx. 1/वर्ग_मूल(2))
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_yuvp1_iefd_config_s अणु
	__u32 horver_diag_coeff:7;
	__u32 reserved0:1;
	__u32 clamp_stitch:6;
	__u32 reserved1:2;
	__u32 direct_metric_update:5;
	__u32 reserved2:3;
	__u32 ed_horver_diag_coeff:7;
	__u32 reserved3:1;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_control - IEFd control
 *
 * @iefd_en:	Enable IEFd
 * @denoise_en:	Enable denoise
 * @direct_smooth_en:	Enable directional smooth
 * @rad_en:	Enable radial update
 * @vssnlm_en:	Enable VSSNLM output filter
 * @reserved:	reserved
 */
काष्ठा ipu3_uapi_yuvp1_iefd_control अणु
	__u32 iefd_en:1;
	__u32 denoise_en:1;
	__u32 direct_smooth_en:1;
	__u32 rad_en:1;
	__u32 vssnlm_en:1;
	__u32 reserved:27;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_sharp_cfg - Sharpening config
 *
 * @nega_lmt_txt: Sharpening limit क्रम negative overshoots क्रम texture.
 * @reserved0: reserved
 * @posi_lmt_txt: Sharpening limit क्रम positive overshoots क्रम texture.
 * @reserved1: reserved
 * @nega_lmt_dir: Sharpening limit क्रम negative overshoots क्रम direction (edge).
 * @reserved2: reserved
 * @posi_lmt_dir: Sharpening limit क्रम positive overshoots क्रम direction (edge).
 * @reserved3: reserved
 *
 * Fixed poपूर्णांक type u13.0, range [0, 8191].
 */
काष्ठा ipu3_uapi_sharp_cfg अणु
	__u32 nega_lmt_txt:13;
	__u32 reserved0:19;
	__u32 posi_lmt_txt:13;
	__u32 reserved1:19;
	__u32 nega_lmt_dir:13;
	__u32 reserved2:19;
	__u32 posi_lmt_dir:13;
	__u32 reserved3:19;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_far_w - Sharpening config क्रम far sub-group
 *
 * @dir_shrp:	Weight of wide direct sharpening, u1.6, range [0, 64], शेष 64.
 * @reserved0:	reserved
 * @dir_dns:	Weight of wide direct denoising, u1.6, range [0, 64], शेष 0.
 * @reserved1:	reserved
 * @ndir_dns_घातr:	Power of non-direct denoising,
 *			Precision u1.6, range [0, 64], शेष 64.
 * @reserved2:	reserved
 */
काष्ठा ipu3_uapi_far_w अणु
	__u32 dir_shrp:7;
	__u32 reserved0:1;
	__u32 dir_dns:7;
	__u32 reserved1:1;
	__u32 ndir_dns_घातr:7;
	__u32 reserved2:9;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_unsharp_cfg - Unsharp config
 *
 * @unsharp_weight: Unsharp mask blending weight.
 *		    u1.6, range [0, 64], शेष 16.
 *		    0 - disabled, 64 - use only unsharp.
 * @reserved0: reserved
 * @unsharp_amount: Unsharp mask amount, u4.5, range [0, 511], शेष 0.
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_unsharp_cfg अणु
	__u32 unsharp_weight:7;
	__u32 reserved0:1;
	__u32 unsharp_amount:9;
	__u32 reserved1:15;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_shrp_cfg - IEFd sharpness config
 *
 * @cfg: sharpness config &ipu3_uapi_sharp_cfg
 * @far_w: wide range config, value as specअगरied by &ipu3_uapi_far_w:
 *	The 5x5 environment is separated पूर्णांकo 2 sub-groups, the 3x3 nearest
 *	neighbors (8 pixels called Near), and the second order neighborhood
 *	around them (16 pixels called Far).
 * @unshrp_cfg: unsharpness config. &ipu3_uapi_unsharp_cfg
 */
काष्ठा ipu3_uapi_yuvp1_iefd_shrp_cfg अणु
	काष्ठा ipu3_uapi_sharp_cfg cfg;
	काष्ठा ipu3_uapi_far_w far_w;
	काष्ठा ipu3_uapi_unsharp_cfg unshrp_cfg;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_unsharp_coef0 - Unsharp mask coefficients
 *
 * @c00: Coeff11, s0.8, range [-255, 255], शेष 1.
 * @c01: Coeff12, s0.8, range [-255, 255], शेष 5.
 * @c02: Coeff13, s0.8, range [-255, 255], शेष 9.
 * @reserved: reserved
 *
 * Configurable रेजिस्टरs क्रम common sharpening support.
 */
काष्ठा ipu3_uapi_unsharp_coef0 अणु
	__u32 c00:9;
	__u32 c01:9;
	__u32 c02:9;
	__u32 reserved:5;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_unsharp_coef1 - Unsharp mask coefficients
 *
 * @c11: Coeff22, s0.8, range [-255, 255], शेष 29.
 * @c12: Coeff23, s0.8, range [-255, 255], शेष 55.
 * @c22: Coeff33, s0.8, range [-255, 255], शेष 96.
 * @reserved: reserved
 */
काष्ठा ipu3_uapi_unsharp_coef1 अणु
	__u32 c11:9;
	__u32 c12:9;
	__u32 c22:9;
	__u32 reserved:5;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_unshrp_cfg - Unsharp mask config
 *
 * @unsharp_coef0: unsharp coefficient 0 config. See &ipu3_uapi_unsharp_coef0
 * @unsharp_coef1: unsharp coefficient 1 config. See &ipu3_uapi_unsharp_coef1
 */
काष्ठा ipu3_uapi_yuvp1_iefd_unshrp_cfg अणु
	काष्ठा ipu3_uapi_unsharp_coef0 unsharp_coef0;
	काष्ठा ipu3_uapi_unsharp_coef1 unsharp_coef1;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_radial_reset_xy - Radial coordinate reset
 *
 * @x:	Radial reset of x coordinate. Precision s12, [-4095, 4095], शेष 0.
 * @reserved0:	reserved
 * @y:	Radial center y coordinate. Precision s12, [-4095, 4095], शेष 0.
 * @reserved1:	reserved
 */
काष्ठा ipu3_uapi_radial_reset_xy अणु
	__s32 x:13;
	__u32 reserved0:3;
	__s32 y:13;
	__u32 reserved1:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_radial_reset_x2 - Radial X^2 reset
 *
 * @x2:	Radial reset of x^2 coordinate. Precision u24, शेष 0.
 * @reserved:	reserved
 */
काष्ठा ipu3_uapi_radial_reset_x2 अणु
	__u32 x2:24;
	__u32 reserved:8;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_radial_reset_y2 - Radial Y^2 reset
 *
 * @y2:	Radial reset of y^2 coordinate. Precision u24, शेष 0.
 * @reserved:	reserved
 */
काष्ठा ipu3_uapi_radial_reset_y2 अणु
	__u32 y2:24;
	__u32 reserved:8;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_radial_cfg - Radial config
 *
 * @rad_nf: Radial. R^2 normalization factor is scale करोwn by 2^ - (15 + scale)
 * @reserved0: reserved
 * @rad_inv_r2: Radial R^-2 normelized to (0.5..1).
 *		Precision u7, range [0, 127].
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_radial_cfg अणु
	__u32 rad_nf:4;
	__u32 reserved0:4;
	__u32 rad_inv_r2:7;
	__u32 reserved1:17;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_rad_far_w - Radial FAR sub-group
 *
 * @rad_dir_far_sharp_w: Weight of wide direct sharpening, u1.6, range [0, 64],
 *			 शेष 64.
 * @rad_dir_far_dns_w: Weight of wide direct denoising, u1.6, range [0, 64],
 *			 शेष 0.
 * @rad_ndir_far_dns_घातer: घातer of non-direct sharpening, u1.6, range [0, 64],
 *			 शेष 0.
 * @reserved: reserved
 */
काष्ठा ipu3_uapi_rad_far_w अणु
	__u32 rad_dir_far_sharp_w:8;
	__u32 rad_dir_far_dns_w:8;
	__u32 rad_ndir_far_dns_घातer:8;
	__u32 reserved:8;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_cu_cfg0 - Radius Config Unit cfg0 रेजिस्टर
 *
 * @cu6_घात: Power of CU6. Power of non-direct sharpening, u3.4.
 * @reserved0: reserved
 * @cu_unsharp_घात: Power of unsharp mask, u2.4.
 * @reserved1: reserved
 * @rad_cu6_घात: Radial/corner CU6. Directed sharpening घातer, u3.4.
 * @reserved2: reserved
 * @rad_cu_unsharp_घात: Radial घातer of unsharp mask, u2.4.
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_cu_cfg0 अणु
	__u32 cu6_घात:7;
	__u32 reserved0:1;
	__u32 cu_unsharp_घात:7;
	__u32 reserved1:1;
	__u32 rad_cu6_घात:7;
	__u32 reserved2:1;
	__u32 rad_cu_unsharp_घात:6;
	__u32 reserved3:2;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_cu_cfg1 - Radius Config Unit cfg1 रेजिस्टर
 *
 * @rad_cu6_x1: X1 poपूर्णांक of Config Unit 6, precision u9.0.
 * @reserved0: reserved
 * @rad_cu_unsharp_x1: X1 poपूर्णांक क्रम Config Unit unsharp क्रम radial/corner poपूर्णांक
 *			precision u9.0.
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_cu_cfg1 अणु
	__u32 rad_cu6_x1:9;
	__u32 reserved0:1;
	__u32 rad_cu_unsharp_x1:9;
	__u32 reserved1:13;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_rad_cfg - IEFd parameters changed radially over
 *					 the picture plane.
 *
 * @reset_xy: reset xy value in radial calculation. &ipu3_uapi_radial_reset_xy
 * @reset_x2: reset x square value in radial calculation. See काष्ठा
 *	      &ipu3_uapi_radial_reset_x2
 * @reset_y2: reset y square value in radial calculation. See काष्ठा
 *	      &ipu3_uapi_radial_reset_y2
 * @cfg: radial config defined in &ipu3_uapi_radial_cfg
 * @rad_far_w: weight क्रम wide range radial. &ipu3_uapi_rad_far_w
 * @cu_cfg0: configuration unit 0. See &ipu3_uapi_cu_cfg0
 * @cu_cfg1: configuration unit 1. See &ipu3_uapi_cu_cfg1
 */
काष्ठा ipu3_uapi_yuvp1_iefd_rad_cfg अणु
	काष्ठा ipu3_uapi_radial_reset_xy reset_xy;
	काष्ठा ipu3_uapi_radial_reset_x2 reset_x2;
	काष्ठा ipu3_uapi_radial_reset_y2 reset_y2;
	काष्ठा ipu3_uapi_radial_cfg cfg;
	काष्ठा ipu3_uapi_rad_far_w rad_far_w;
	काष्ठा ipu3_uapi_cu_cfg0 cu_cfg0;
	काष्ठा ipu3_uapi_cu_cfg1 cu_cfg1;
पूर्ण __packed;

/* Vssnlm - Very small scale non-local mean algorithm */

/**
 * काष्ठा ipu3_uapi_vss_lut_x - Vssnlm LUT x0/x1/x2
 *
 * @vs_x0: Vssnlm LUT x0, precision u8, range [0, 255], शेष 16.
 * @vs_x1: Vssnlm LUT x1, precision u8, range [0, 255], शेष 32.
 * @vs_x2: Vssnlm LUT x2, precision u8, range [0, 255], शेष 64.
 * @reserved2: reserved
 */
काष्ठा ipu3_uapi_vss_lut_x अणु
	__u32 vs_x0:8;
	__u32 vs_x1:8;
	__u32 vs_x2:8;
	__u32 reserved2:8;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_vss_lut_y - Vssnlm LUT y0/y1/y2
 *
 * @vs_y1: Vssnlm LUT y1, precision u4, range [0, 8], शेष 1.
 * @reserved0: reserved
 * @vs_y2: Vssnlm LUT y2, precision u4, range [0, 8], शेष 3.
 * @reserved1: reserved
 * @vs_y3: Vssnlm LUT y3, precision u4, range [0, 8], शेष 8.
 * @reserved2: reserved
 */
काष्ठा ipu3_uapi_vss_lut_y अणु
	__u32 vs_y1:4;
	__u32 reserved0:4;
	__u32 vs_y2:4;
	__u32 reserved1:4;
	__u32 vs_y3:4;
	__u32 reserved2:12;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_vssnlm_cfg - IEFd Vssnlm Lookup table
 *
 * @vss_lut_x: vss lookup table. See &ipu3_uapi_vss_lut_x description
 * @vss_lut_y: vss lookup table. See &ipu3_uapi_vss_lut_y description
 */
काष्ठा ipu3_uapi_yuvp1_iefd_vssnlm_cfg अणु
	काष्ठा ipu3_uapi_vss_lut_x vss_lut_x;
	काष्ठा ipu3_uapi_vss_lut_y vss_lut_y;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_iefd_config - IEFd config
 *
 * @units: configuration unit setting, &ipu3_uapi_yuvp1_iefd_cfg_units
 * @config: configuration, as defined by &ipu3_uapi_yuvp1_iefd_config_s
 * @control: control setting, as defined by &ipu3_uapi_yuvp1_iefd_control
 * @sharp: sharpness setting, as defined by &ipu3_uapi_yuvp1_iefd_shrp_cfg
 * @unsharp: unsharpness setting, as defined by &ipu3_uapi_yuvp1_iefd_unshrp_cfg
 * @rad: radial setting, as defined by &ipu3_uapi_yuvp1_iefd_rad_cfg
 * @vsslnm: vsslnm setting, as defined by &ipu3_uapi_yuvp1_iefd_vssnlm_cfg
 */
काष्ठा ipu3_uapi_yuvp1_iefd_config अणु
	काष्ठा ipu3_uapi_yuvp1_iefd_cfg_units units;
	काष्ठा ipu3_uapi_yuvp1_iefd_config_s config;
	काष्ठा ipu3_uapi_yuvp1_iefd_control control;
	काष्ठा ipu3_uapi_yuvp1_iefd_shrp_cfg sharp;
	काष्ठा ipu3_uapi_yuvp1_iefd_unshrp_cfg unsharp;
	काष्ठा ipu3_uapi_yuvp1_iefd_rad_cfg rad;
	काष्ठा ipu3_uapi_yuvp1_iefd_vssnlm_cfg vsslnm;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_yds_config - Y Down-Sampling config
 *
 * @c00: range [0, 3], शेष 0x0
 * @c01: range [0, 3], शेष 0x1
 * @c02: range [0, 3], शेष 0x1
 * @c03: range [0, 3], शेष 0x0
 * @c10: range [0, 3], शेष 0x0
 * @c11: range [0, 3], शेष 0x1
 * @c12: range [0, 3], शेष 0x1
 * @c13: range [0, 3], शेष 0x0
 *
 * Above are 4x2 filter coefficients क्रम chroma output करोwnscaling.
 *
 * @norm_factor: Normalization factor, range [0, 4], शेष 2
 *		0 - भागide by 1
 *		1 - भागide by 2
 *		2 - भागide by 4
 *		3 - भागide by 8
 *		4 - भागide by 16
 * @reserved0: reserved
 * @bin_output: Down sampling on Luma channel in two optional modes
 *		0 - Bin output 4.2.0 (शेष), 1 output 4.2.2.
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_yuvp1_yds_config अणु
	__u32 c00:2;
	__u32 c01:2;
	__u32 c02:2;
	__u32 c03:2;
	__u32 c10:2;
	__u32 c11:2;
	__u32 c12:2;
	__u32 c13:2;
	__u32 norm_factor:5;
	__u32 reserved0:4;
	__u32 bin_output:1;
	__u32 reserved1:6;
पूर्ण __packed;

/* Chroma Noise Reduction */

/**
 * काष्ठा ipu3_uapi_yuvp1_chnr_enable_config - Chroma noise reduction enable
 *
 * @enable: enable/disable chroma noise reduction
 * @yuv_mode: 0 - YUV420, 1 - YUV422
 * @reserved0: reserved
 * @col_size: number of columns in the frame, max width is 2560
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_yuvp1_chnr_enable_config अणु
	__u32 enable:1;
	__u32 yuv_mode:1;
	__u32 reserved0:14;
	__u32 col_size:12;
	__u32 reserved1:4;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_chnr_coring_config - Coring thresholds क्रम UV
 *
 * @u: U coring level, u0.13, range [0.0, 1.0], शेष 0.0
 * @reserved0: reserved
 * @v: V coring level, u0.13, range [0.0, 1.0], शेष 0.0
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_yuvp1_chnr_coring_config अणु
	__u32 u:13;
	__u32 reserved0:3;
	__u32 v:13;
	__u32 reserved1:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_chnr_sense_gain_config - Chroma noise reduction gains
 *
 * All sensitivity gain parameters have precision u13.0, range [0, 8191].
 *
 * @vy: Sensitivity of horizontal edge of Y, शेष 100
 * @vu: Sensitivity of horizontal edge of U, शेष 100
 * @vv: Sensitivity of horizontal edge of V, शेष 100
 * @reserved0: reserved
 * @hy: Sensitivity of vertical edge of Y, शेष 50
 * @hu: Sensitivity of vertical edge of U, शेष 50
 * @hv: Sensitivity of vertical edge of V, शेष 50
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_yuvp1_chnr_sense_gain_config अणु
	__u32 vy:8;
	__u32 vu:8;
	__u32 vv:8;
	__u32 reserved0:8;

	__u32 hy:8;
	__u32 hu:8;
	__u32 hv:8;
	__u32 reserved1:8;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_chnr_iir_fir_config - Chroma IIR/FIR filter config
 *
 * @fir_0h: Value of center tap in horizontal FIR, range [0, 32], शेष 8.
 * @reserved0: reserved
 * @fir_1h: Value of distance 1 in horizontal FIR, range [0, 32], शेष 12.
 * @reserved1: reserved
 * @fir_2h: Value of distance 2 tap in horizontal FIR, range [0, 32], शेष 0.
 * @dalpha_clip_val: weight क्रम previous row in IIR, range [1, 256], शेष 0.
 * @reserved2: reserved
 */
काष्ठा ipu3_uapi_yuvp1_chnr_iir_fir_config अणु
	__u32 fir_0h:6;
	__u32 reserved0:2;
	__u32 fir_1h:6;
	__u32 reserved1:2;
	__u32 fir_2h:6;
	__u32 dalpha_clip_val:9;
	__u32 reserved2:1;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_chnr_config - Chroma noise reduction config
 *
 * @enable: chroma noise reduction enable, see
 *	    &ipu3_uapi_yuvp1_chnr_enable_config
 * @coring: coring config क्रम chroma noise reduction, see
 *	    &ipu3_uapi_yuvp1_chnr_coring_config
 * @sense_gain: sensitivity config क्रम chroma noise reduction, see
 *		ipu3_uapi_yuvp1_chnr_sense_gain_config
 * @iir_fir: iir and fir config क्रम chroma noise reduction, see
 *	     ipu3_uapi_yuvp1_chnr_iir_fir_config
 */
काष्ठा ipu3_uapi_yuvp1_chnr_config अणु
	काष्ठा ipu3_uapi_yuvp1_chnr_enable_config enable;
	काष्ठा ipu3_uapi_yuvp1_chnr_coring_config coring;
	काष्ठा ipu3_uapi_yuvp1_chnr_sense_gain_config sense_gain;
	काष्ठा ipu3_uapi_yuvp1_chnr_iir_fir_config iir_fir;
पूर्ण __packed;

/* Edge Enhancement and Noise Reduction */

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_lpf_config - Luma(Y) edge enhancement low-pass
 *					       filter coefficients
 *
 * @a_diag: Smoothing diagonal coefficient, u5.0.
 * @reserved0: reserved
 * @a_periph: Image smoothing perpherial, u5.0.
 * @reserved1: reserved
 * @a_cent: Image Smoothing center coefficient, u5.0.
 * @reserved2: reserved
 * @enable: 0: Y_EE_NR disabled, output = input; 1: Y_EE_NR enabled.
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_lpf_config अणु
	__u32 a_diag:5;
	__u32 reserved0:3;
	__u32 a_periph:5;
	__u32 reserved1:3;
	__u32 a_cent:5;
	__u32 reserved2:9;
	__u32 enable:1;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_sense_config - Luma(Y) edge enhancement
 *					noise reduction sensitivity gains
 *
 * @edge_sense_0: Sensitivity of edge in dark area. u13.0, शेष 8191.
 * @reserved0: reserved
 * @delta_edge_sense: Dअगरference in the sensitivity of edges between
 *		      the bright and dark areas. u13.0, शेष 0.
 * @reserved1: reserved
 * @corner_sense_0: Sensitivity of corner in dark area. u13.0, शेष 0.
 * @reserved2: reserved
 * @delta_corner_sense: Dअगरference in the sensitivity of corners between
 *			the bright and dark areas. u13.0, शेष 8191.
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_sense_config अणु
	__u32 edge_sense_0:13;
	__u32 reserved0:3;
	__u32 delta_edge_sense:13;
	__u32 reserved1:3;
	__u32 corner_sense_0:13;
	__u32 reserved2:3;
	__u32 delta_corner_sense:13;
	__u32 reserved3:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_gain_config - Luma(Y) edge enhancement
 *						noise reduction gain config
 *
 * @gain_pos_0: Gain क्रम positive edge in dark area. u5.0, [0, 16], शेष 2.
 * @reserved0: reserved
 * @delta_gain_posi: Dअगरference in the gain of edges between the bright and
 *		     dark areas क्रम positive edges. u5.0, [0, 16], शेष 0.
 * @reserved1: reserved
 * @gain_neg_0: Gain क्रम negative edge in dark area. u5.0, [0, 16], शेष 8.
 * @reserved2: reserved
 * @delta_gain_neg: Dअगरference in the gain of edges between the bright and
 *		    dark areas क्रम negative edges. u5.0, [0, 16], शेष 0.
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_gain_config अणु
	__u32 gain_pos_0:5;
	__u32 reserved0:3;
	__u32 delta_gain_posi:5;
	__u32 reserved1:3;
	__u32 gain_neg_0:5;
	__u32 reserved2:3;
	__u32 delta_gain_neg:5;
	__u32 reserved3:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_clip_config - Luma(Y) edge enhancement
 *					noise reduction clipping config
 *
 * @clip_pos_0: Limit of positive edge in dark area
 *		u5, value [0, 16], शेष 8.
 * @reserved0: reserved
 * @delta_clip_posi: Dअगरference in the limit of edges between the bright
 *		     and dark areas क्रम positive edges.
 *		     u5, value [0, 16], शेष 8.
 * @reserved1: reserved
 * @clip_neg_0: Limit of negative edge in dark area
 *		u5, value [0, 16], शेष 8.
 * @reserved2: reserved
 * @delta_clip_neg: Dअगरference in the limit of edges between the bright
 *		    and dark areas क्रम negative edges.
 *		    u5, value [0, 16], शेष 8.
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_clip_config अणु
	__u32 clip_pos_0:5;
	__u32 reserved0:3;
	__u32 delta_clip_posi:5;
	__u32 reserved1:3;
	__u32 clip_neg_0:5;
	__u32 reserved2:3;
	__u32 delta_clip_neg:5;
	__u32 reserved3:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_frng_config - Luma(Y) edge enhancement
 *						noise reduction fringe config
 *
 * @gain_exp: Common exponent of gains, u4, [0, 8], शेष 2.
 * @reserved0: reserved
 * @min_edge: Threshold क्रम edge and smooth stitching, u13.
 * @reserved1: reserved
 * @lin_seg_param: Power of LinSeg, u4.
 * @reserved2: reserved
 * @t1: Parameter क्रम enabling/disabling the edge enhancement, u1.0, [0, 1],
 *	शेष 1.
 * @t2: Parameter क्रम enabling/disabling the smoothing, u1.0, [0, 1],
 *	शेष 1.
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_frng_config अणु
	__u32 gain_exp:4;
	__u32 reserved0:28;
	__u32 min_edge:13;
	__u32 reserved1:3;
	__u32 lin_seg_param:4;
	__u32 reserved2:4;
	__u32 t1:1;
	__u32 t2:1;
	__u32 reserved3:6;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_diag_config - Luma(Y) edge enhancement
 *					noise reduction diagonal config
 *
 * @diag_disc_g: Coefficient that prioritize diagonal edge direction on
 *		 horizontal or vertical क्रम final enhancement.
 *		 u4.0, [1, 15], शेष 1.
 * @reserved0: reserved
 * @hvw_hor: Weight of horizontal/vertical edge enhancement क्रम hv edge.
 *		u2.2, [1, 15], शेष 4.
 * @dw_hor: Weight of diagonal edge enhancement क्रम hv edge.
 *		u2.2, [1, 15], शेष 1.
 * @hvw_diag: Weight of horizontal/vertical edge enhancement क्रम diagonal edge.
 *		u2.2, [1, 15], शेष 1.
 * @dw_diag: Weight of diagonal edge enhancement क्रम diagonal edge.
 *		u2.2, [1, 15], शेष 4.
 * @reserved1: reserved
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_diag_config अणु
	__u32 diag_disc_g:4;
	__u32 reserved0:4;
	__u32 hvw_hor:4;
	__u32 dw_hor:4;
	__u32 hvw_diag:4;
	__u32 dw_diag:4;
	__u32 reserved1:8;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_fc_coring_config - Luma(Y) edge enhancement
 *		noise reduction false color correction (FCC) coring config
 *
 * @pos_0: Gain क्रम positive edge in dark, u13.0, [0, 16], शेष 0.
 * @reserved0: reserved
 * @pos_delta: Gain क्रम positive edge in bright, value: pos_0 + pos_delta <=16
 *		u13.0, शेष 0.
 * @reserved1: reserved
 * @neg_0: Gain क्रम negative edge in dark area, u13.0, range [0, 16], शेष 0.
 * @reserved2: reserved
 * @neg_delta: Gain क्रम negative edge in bright area. neg_0 + neg_delta <=16
 *		u13.0, शेष 0.
 * @reserved3: reserved
 *
 * Coring is a simple soft thresholding technique.
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_fc_coring_config अणु
	__u32 pos_0:13;
	__u32 reserved0:3;
	__u32 pos_delta:13;
	__u32 reserved1:3;
	__u32 neg_0:13;
	__u32 reserved2:3;
	__u32 neg_delta:13;
	__u32 reserved3:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp1_y_ee_nr_config - Edge enhancement and noise reduction
 *
 * @lpf: low-pass filter config. See &ipu3_uapi_yuvp1_y_ee_nr_lpf_config
 * @sense: sensitivity config. See &ipu3_uapi_yuvp1_y_ee_nr_sense_config
 * @gain: gain config as defined in &ipu3_uapi_yuvp1_y_ee_nr_gain_config
 * @clip: clip config as defined in &ipu3_uapi_yuvp1_y_ee_nr_clip_config
 * @frng: fringe config as defined in &ipu3_uapi_yuvp1_y_ee_nr_frng_config
 * @diag: diagonal edge config. See &ipu3_uapi_yuvp1_y_ee_nr_diag_config
 * @fc_coring: coring config क्रम fringe control. See
 *	       &ipu3_uapi_yuvp1_y_ee_nr_fc_coring_config
 */
काष्ठा ipu3_uapi_yuvp1_y_ee_nr_config अणु
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_lpf_config lpf;
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_sense_config sense;
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_gain_config gain;
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_clip_config clip;
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_frng_config frng;
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_diag_config diag;
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_fc_coring_config fc_coring;
पूर्ण __packed;

/* Total Color Correction */

/**
 * काष्ठा ipu3_uapi_yuvp2_tcc_gen_control_अटल_config - Total color correction
 *				general control config
 *
 * @en:	0 - TCC disabled. Output = input 1 - TCC enabled.
 * @blend_shअगरt:	blend shअगरt, Range[3, 4], शेष NA.
 * @gain_according_to_y_only:	0: Gain is calculated according to YUV,
 *				1: Gain is calculated according to Y only
 * @reserved0: reserved
 * @gamma:	Final blending coefficients. Values[-16, 16], शेष NA.
 * @reserved1: reserved
 * @delta:	Final blending coefficients. Values[-16, 16], शेष NA.
 * @reserved2: reserved
 */
काष्ठा ipu3_uapi_yuvp2_tcc_gen_control_अटल_config अणु
	__u32 en:1;
	__u32 blend_shअगरt:3;
	__u32 gain_according_to_y_only:1;
	__u32 reserved0:11;
	__s32 gamma:5;
	__u32 reserved1:3;
	__s32 delta:5;
	__u32 reserved2:3;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp2_tcc_macc_elem_अटल_config - Total color correction
 *				multi-axis color control (MACC) config
 *
 * @a: a coefficient क्रम 2x2 MACC conversion matrix.
 * @reserved0: reserved
 * @b: b coefficient  2x2 MACC conversion matrix.
 * @reserved1: reserved
 * @c: c coefficient क्रम 2x2 MACC conversion matrix.
 * @reserved2: reserved
 * @d: d coefficient क्रम 2x2 MACC conversion matrix.
 * @reserved3: reserved
 */
काष्ठा ipu3_uapi_yuvp2_tcc_macc_elem_अटल_config अणु
	__s32 a:12;
	__u32 reserved0:4;
	__s32 b:12;
	__u32 reserved1:4;
	__s32 c:12;
	__u32 reserved2:4;
	__s32 d:12;
	__u32 reserved3:4;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp2_tcc_macc_table_अटल_config - Total color correction
 *				multi-axis color control (MACC) table array
 *
 * @entries: config क्रम multi axis color correction, as specअगरied by
 *	     &ipu3_uapi_yuvp2_tcc_macc_elem_अटल_config
 */
काष्ठा ipu3_uapi_yuvp2_tcc_macc_table_अटल_config अणु
	काष्ठा ipu3_uapi_yuvp2_tcc_macc_elem_अटल_config
		entries[IPU3_UAPI_YUVP2_TCC_MACC_TABLE_ELEMENTS];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp2_tcc_inv_y_lut_अटल_config - Total color correction
 *				inverse y lookup table
 *
 * @entries: lookup table क्रम inverse y estimation, and use it to estimate the
 *	     ratio between luma and chroma. Chroma by approximate the असलolute
 *	     value of the radius on the chroma plane (R = वर्ग_मूल(u^2+v^2) ) and
 *	     luma by approximate by 1/Y.
 */
काष्ठा ipu3_uapi_yuvp2_tcc_inv_y_lut_अटल_config अणु
	__u16 entries[IPU3_UAPI_YUVP2_TCC_INV_Y_LUT_ELEMENTS];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp2_tcc_gain_pcwl_lut_अटल_config - Total color
 *					correction lookup table क्रम PCWL
 *
 * @entries: lookup table क्रम gain piece wise linear transक्रमmation (PCWL)
 */
काष्ठा ipu3_uapi_yuvp2_tcc_gain_pcwl_lut_अटल_config अणु
	__u16 entries[IPU3_UAPI_YUVP2_TCC_GAIN_PCWL_LUT_ELEMENTS];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp2_tcc_r_sqr_lut_अटल_config - Total color correction
 *				lookup table क्रम r square root
 *
 * @entries: lookup table क्रम r square root estimation
 */
काष्ठा ipu3_uapi_yuvp2_tcc_r_sqr_lut_अटल_config अणु
	__s16 entries[IPU3_UAPI_YUVP2_TCC_R_SQR_LUT_ELEMENTS];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_yuvp2_tcc_अटल_config- Total color correction अटल
 *
 * @gen_control: general config क्रम Total Color Correction
 * @macc_table: config क्रम multi axis color correction
 * @inv_y_lut: lookup table क्रम inverse y estimation
 * @gain_pcwl: lookup table क्रम gain PCWL
 * @r_sqr_lut: lookup table क्रम r square root estimation.
 */
काष्ठा ipu3_uapi_yuvp2_tcc_अटल_config अणु
	काष्ठा ipu3_uapi_yuvp2_tcc_gen_control_अटल_config gen_control;
	काष्ठा ipu3_uapi_yuvp2_tcc_macc_table_अटल_config macc_table;
	काष्ठा ipu3_uapi_yuvp2_tcc_inv_y_lut_अटल_config inv_y_lut;
	काष्ठा ipu3_uapi_yuvp2_tcc_gain_pcwl_lut_अटल_config gain_pcwl;
	काष्ठा ipu3_uapi_yuvp2_tcc_r_sqr_lut_अटल_config r_sqr_lut;
पूर्ण __packed;

/* Advanced Noise Reduction related काष्ठाs */

/*
 * काष्ठा ipu3_uapi_anr_alpha - Advanced noise reduction alpha
 *
 * Tunable parameters that are subject to modअगरication according to the
 * total gain used.
 */
काष्ठा ipu3_uapi_anr_alpha अणु
	__u16 gr;
	__u16 r;
	__u16 b;
	__u16 gb;
	__u16 dc_gr;
	__u16 dc_r;
	__u16 dc_b;
	__u16 dc_gb;
पूर्ण __packed;

/*
 * काष्ठा ipu3_uapi_anr_beta - Advanced noise reduction beta
 *
 * Tunable parameters that are subject to modअगरication according to the
 * total gain used.
 */
काष्ठा ipu3_uapi_anr_beta अणु
	__u16 beta_gr;
	__u16 beta_r;
	__u16 beta_b;
	__u16 beta_gb;
पूर्ण __packed;

/*
 * काष्ठा ipu3_uapi_anr_plane_color - Advanced noise reduction per plane R, Gr,
 *				      Gb and B रेजिस्टर settings
 *
 * Tunable parameters that are subject to modअगरication according to the
 * total gain used.
 */
काष्ठा ipu3_uapi_anr_plane_color अणु
	__u16 reg_w_gr[16];
	__u16 reg_w_r[16];
	__u16 reg_w_b[16];
	__u16 reg_w_gb[16];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_anr_transक्रमm_config - Advanced noise reduction transक्रमm
 *
 * @enable: advanced noise reduction enabled.
 * @adaptive_treshhold_en: On IPU3, adaptive threshold is always enabled.
 * @reserved1: reserved
 * @reserved2: reserved
 * @alpha: using following शेषs:
 *		13, 13, 13, 13, 0, 0, 0, 0
 *		11, 11, 11, 11, 0, 0, 0, 0
 *		14,  14, 14, 14, 0, 0, 0, 0
 * @beta: use following शेषs:
 *		24, 24, 24, 24
 *		21, 20, 20, 21
 *		25, 25, 25, 25
 * @color: use शेषs defined in driver/media/pci/पूर्णांकel/ipu3-tables.c
 * @वर्ग_मूल_lut: 11 bits per element, values =
 *					[724 768 810 849 887
 *					923 958 991 1024 1056
 *					1116 1145 1173 1201 1086
 *					1228 1254 1280 1305 1330
 *					1355 1379 1402 1425 1448]
 * @xreset: Reset value of X क्रम r^2 calculation Value: col_start-X_center
 *	Constraपूर्णांक: Xreset + FrameWdith=4095 Xreset= -4095, शेष -1632.
 * @reserved3: reserved
 * @yreset: Reset value of Y क्रम r^2 calculation Value: row_start-Y_center
 *	 Constraपूर्णांक: Yreset + FrameHeight=4095 Yreset= -4095, शेष -1224.
 * @reserved4: reserved
 * @x_sqr_reset: Reset value of X^2 क्रम r^2 calculation Value = (Xreset)^2
 * @r_normfactor: Normalization factor क्रम R. Default 14.
 * @reserved5: reserved
 * @y_sqr_reset: Reset value of Y^2 क्रम r^2 calculation Value = (Yreset)^2
 * @gain_scale: Parameter describing shading gain as a function of distance
 *		from the image center.
 *		A single value per frame, loaded by the driver. Default 115.
 */
काष्ठा ipu3_uapi_anr_transक्रमm_config अणु
	__u32 enable:1;			/* 0 or 1, disabled or enabled */
	__u32 adaptive_treshhold_en:1;	/* On IPU3, always enabled */

	__u32 reserved1:30;
	__u8 reserved2[44];

	काष्ठा ipu3_uapi_anr_alpha alpha[3];
	काष्ठा ipu3_uapi_anr_beta beta[3];
	काष्ठा ipu3_uapi_anr_plane_color color[3];

	__u16 वर्ग_मूल_lut[IPU3_UAPI_ANR_LUT_SIZE];	/* 11 bits per element */

	__s16 xreset:13;
	__u16 reserved3:3;
	__s16 yreset:13;
	__u16 reserved4:3;

	__u32 x_sqr_reset:24;
	__u32 r_normfactor:5;
	__u32 reserved5:3;

	__u32 y_sqr_reset:24;
	__u32 gain_scale:8;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_anr_stitch_pyramid - ANR stitch pyramid
 *
 * @entry0: pyramid LUT entry0, range [0x0, 0x3f]
 * @entry1: pyramid LUT entry1, range [0x0, 0x3f]
 * @entry2: pyramid LUT entry2, range [0x0, 0x3f]
 * @reserved: reserved
 */
काष्ठा ipu3_uapi_anr_stitch_pyramid अणु
	__u32 entry0:6;
	__u32 entry1:6;
	__u32 entry2:6;
	__u32 reserved:14;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_anr_stitch_config - ANR stitch config
 *
 * @anr_stitch_en: enable stitch. Enabled with 1.
 * @reserved: reserved
 * @pyramid: pyramid table as defined by &ipu3_uapi_anr_stitch_pyramid
 *		शेष values:
 *		अणु 1, 3, 5 पूर्ण, अणु 7, 7, 5 पूर्ण, अणु 3, 1, 3 पूर्ण,
 *		अणु 9, 15, 21 पूर्ण, अणु 21, 15, 9 पूर्ण, अणु 3, 5, 15 पूर्ण,
 *		अणु 25, 35, 35 पूर्ण, अणु 25, 15, 5 पूर्ण, अणु 7, 21, 35 पूर्ण,
 *		अणु 49, 49, 35 पूर्ण, अणु 21, 7, 7 पूर्ण, अणु 21, 35, 49 पूर्ण,
 *		अणु 49, 35, 21 पूर्ण, अणु 7, 5, 15 पूर्ण, अणु 25, 35, 35 पूर्ण,
 *		अणु 25, 15, 5 पूर्ण, अणु 3, 9, 15 पूर्ण, अणु 21, 21, 15 पूर्ण,
 *		अणु 9, 3, 1 पूर्ण, अणु 3, 5, 7 पूर्ण, अणु 7, 5, 3पूर्ण, अणु 1 पूर्ण
 */
काष्ठा ipu3_uapi_anr_stitch_config अणु
	__u32 anr_stitch_en;
	__u8 reserved[44];
	काष्ठा ipu3_uapi_anr_stitch_pyramid pyramid[IPU3_UAPI_ANR_PYRAMID_SIZE];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_anr_config - ANR config
 *
 * @transक्रमm:	advanced noise reduction transक्रमm config as specअगरied by
 *		&ipu3_uapi_anr_transक्रमm_config
 * @stitch: create 4x4 patch from 4 surrounding 8x8 patches.
 */
काष्ठा ipu3_uapi_anr_config अणु
	काष्ठा ipu3_uapi_anr_transक्रमm_config transक्रमm __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_anr_stitch_config stitch __attribute__((aligned(32)));
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_acc_param - Accelerator cluster parameters
 *
 * ACC refers to the HW cluster containing all Fixed Functions (FFs). Each FF
 * implements a specअगरic algorithm.
 *
 * @bnr:	parameters क्रम bayer noise reduction अटल config. See
 *		&ipu3_uapi_bnr_अटल_config
 * @green_disparity:	disparity अटल config between gr and gb channel.
 *			See &ipu3_uapi_bnr_अटल_config_green_disparity
 * @dm:	de-mosaic config. See &ipu3_uapi_dm_config
 * @ccm:	color correction matrix. See &ipu3_uapi_ccm_mat_config
 * @gamma:	gamma correction config. See &ipu3_uapi_gamma_config
 * @csc:	color space conversion matrix. See &ipu3_uapi_csc_mat_config
 * @cds:	color करोwn sample config. See &ipu3_uapi_cds_params
 * @shd:	lens shading correction config. See &ipu3_uapi_shd_config
 * @iefd:	Image enhancement filter and denoise config.
 *		&ipu3_uapi_yuvp1_iefd_config
 * @yds_c0:	y करोwn scaler config. &ipu3_uapi_yuvp1_yds_config
 * @chnr_c0:	chroma noise reduction config. &ipu3_uapi_yuvp1_chnr_config
 * @y_ee_nr:	y edge enhancement and noise reduction config.
 *		&ipu3_uapi_yuvp1_y_ee_nr_config
 * @yds:	y करोwn scaler config. See &ipu3_uapi_yuvp1_yds_config
 * @chnr:	chroma noise reduction config. See &ipu3_uapi_yuvp1_chnr_config
 * @reserved1: reserved
 * @yds2:	y channel करोwn scaler config. See &ipu3_uapi_yuvp1_yds_config
 * @tcc:	total color correction config as defined in काष्ठा
 *		&ipu3_uapi_yuvp2_tcc_अटल_config
 * @reserved2: reserved
 * @anr:	advanced noise reduction config.See &ipu3_uapi_anr_config
 * @awb_fr:	AWB filter response config. See ipu3_uapi_awb_fr_config
 * @ae:	स्वतः exposure config  As specअगरied by &ipu3_uapi_ae_config
 * @af:	स्वतः focus config. As specअगरied by &ipu3_uapi_af_config
 * @awb:	स्वतः white balance config. As specअगरied by &ipu3_uapi_awb_config
 */
काष्ठा ipu3_uapi_acc_param अणु
	काष्ठा ipu3_uapi_bnr_अटल_config bnr;
	काष्ठा ipu3_uapi_bnr_अटल_config_green_disparity
				green_disparity __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_dm_config dm __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_ccm_mat_config ccm __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_gamma_config gamma __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_csc_mat_config csc __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_cds_params cds __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_shd_config shd __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp1_iefd_config iefd __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp1_yds_config yds_c0 __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp1_chnr_config chnr_c0 __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp1_y_ee_nr_config y_ee_nr __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp1_yds_config yds __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp1_chnr_config chnr __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp1_yds_config yds2 __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_yuvp2_tcc_अटल_config tcc __attribute__((aligned(32)));
	काष्ठा ipu3_uapi_anr_config anr;
	काष्ठा ipu3_uapi_awb_fr_config_s awb_fr;
	काष्ठा ipu3_uapi_ae_config ae;
	काष्ठा ipu3_uapi_af_config_s af;
	काष्ठा ipu3_uapi_awb_config awb;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_isp_lin_vmem_params - Linearization parameters
 *
 * @lin_lutlow_gr: linearization look-up table क्रम GR channel पूर्णांकerpolation.
 * @lin_lutlow_r: linearization look-up table क्रम R channel पूर्णांकerpolation.
 * @lin_lutlow_b: linearization look-up table क्रम B channel पूर्णांकerpolation.
 * @lin_lutlow_gb: linearization look-up table क्रम GB channel पूर्णांकerpolation.
 *			lin_lutlow_gr / lin_lutlow_r / lin_lutlow_b /
 *			lin_lutlow_gb <= LIN_MAX_VALUE - 1.
 * @lin_lutdअगर_gr:	lin_lutlow_gr[i+1] - lin_lutlow_gr[i].
 * @lin_lutdअगर_r:	lin_lutlow_r[i+1] - lin_lutlow_r[i].
 * @lin_lutdअगर_b:	lin_lutlow_b[i+1] - lin_lutlow_b[i].
 * @lin_lutdअगर_gb:	lin_lutlow_gb[i+1] - lin_lutlow_gb[i].
 */
काष्ठा ipu3_uapi_isp_lin_vmem_params अणु
	__s16 lin_lutlow_gr[IPU3_UAPI_LIN_LUT_SIZE];
	__s16 lin_lutlow_r[IPU3_UAPI_LIN_LUT_SIZE];
	__s16 lin_lutlow_b[IPU3_UAPI_LIN_LUT_SIZE];
	__s16 lin_lutlow_gb[IPU3_UAPI_LIN_LUT_SIZE];
	__s16 lin_lutdअगर_gr[IPU3_UAPI_LIN_LUT_SIZE];
	__s16 lin_lutdअगर_r[IPU3_UAPI_LIN_LUT_SIZE];
	__s16 lin_lutdअगर_b[IPU3_UAPI_LIN_LUT_SIZE];
	__s16 lin_lutdअगर_gb[IPU3_UAPI_LIN_LUT_SIZE];
पूर्ण __packed;

/* Temporal Noise Reduction */

/**
 * काष्ठा ipu3_uapi_isp_tnr3_vmem_params - Temporal noise reduction vector
 *					   memory parameters
 *
 * @slope: slope setting in पूर्णांकerpolation curve क्रम temporal noise reduction.
 * @reserved1: reserved
 * @sigma: knee poपूर्णांक setting in पूर्णांकerpolation curve क्रम temporal
 *	   noise reduction.
 * @reserved2: reserved
 */
काष्ठा ipu3_uapi_isp_tnr3_vmem_params अणु
	__u16 slope[IPU3_UAPI_ISP_TNR3_VMEM_LEN];
	__u16 reserved1[IPU3_UAPI_ISP_VEC_ELEMS
						- IPU3_UAPI_ISP_TNR3_VMEM_LEN];
	__u16 sigma[IPU3_UAPI_ISP_TNR3_VMEM_LEN];
	__u16 reserved2[IPU3_UAPI_ISP_VEC_ELEMS
						- IPU3_UAPI_ISP_TNR3_VMEM_LEN];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_isp_tnr3_params - Temporal noise reduction v3 parameters
 *
 * @knee_y1: Knee poपूर्णांक TNR3 assumes standard deviation of Y,U and
 *	V at Y1 are TnrY1_Sigma_Y, U and V.
 * @knee_y2: Knee poपूर्णांक TNR3 assumes standard deviation of Y,U and
 *		V at Y2 are TnrY2_Sigma_Y, U and V.
 * @maxfb_y: Max feedback gain क्रम Y
 * @maxfb_u: Max feedback gain क्रम U
 * @maxfb_v: Max feedback gain क्रम V
 * @round_adj_y: rounding Adjust क्रम Y
 * @round_adj_u: rounding Adjust क्रम U
 * @round_adj_v: rounding Adjust क्रम V
 * @ref_buf_select: selection of the reference frame buffer to be used.
 */
काष्ठा ipu3_uapi_isp_tnr3_params अणु
	__u32 knee_y1;
	__u32 knee_y2;
	__u32 maxfb_y;
	__u32 maxfb_u;
	__u32 maxfb_v;
	__u32 round_adj_y;
	__u32 round_adj_u;
	__u32 round_adj_v;
	__u32 ref_buf_select;
पूर्ण __packed;

/* Extreme Noise Reduction version 3 */

/**
 * काष्ठा ipu3_uapi_isp_xnr3_vmem_params - Extreme noise reduction v3
 *					   vector memory parameters
 *
 * @x: xnr3 parameters.
 * @a: xnr3 parameters.
 * @b: xnr3 parameters.
 * @c: xnr3 parameters.
 */
काष्ठा ipu3_uapi_isp_xnr3_vmem_params अणु
	__u16 x[IPU3_UAPI_ISP_VEC_ELEMS];
	__u16 a[IPU3_UAPI_ISP_VEC_ELEMS];
	__u16 b[IPU3_UAPI_ISP_VEC_ELEMS];
	__u16 c[IPU3_UAPI_ISP_VEC_ELEMS];
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_xnr3_alpha_params - Extreme noise reduction v3
 *					alpha tuning parameters
 *
 * @y0: Sigma क्रम Y range similarity in dark area.
 * @u0: Sigma क्रम U range similarity in dark area.
 * @v0: Sigma क्रम V range similarity in dark area.
 * @ydअगरf: Sigma dअगरference क्रम Y between bright area and dark area.
 * @udअगरf: Sigma dअगरference क्रम U between bright area and dark area.
 * @vdअगरf: Sigma dअगरference क्रम V between bright area and dark area.
 */
काष्ठा ipu3_uapi_xnr3_alpha_params अणु
	__u32 y0;
	__u32 u0;
	__u32 v0;
	__u32 ydअगरf;
	__u32 udअगरf;
	__u32 vdअगरf;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_xnr3_coring_params - Extreme noise reduction v3
 *					 coring parameters
 *
 * @u0: Coring Threshold of U channel in dark area.
 * @v0: Coring Threshold of V channel in dark area.
 * @udअगरf: Threshold dअगरference of U channel between bright and dark area.
 * @vdअगरf: Threshold dअगरference of V channel between bright and dark area.
 */
काष्ठा ipu3_uapi_xnr3_coring_params अणु
	__u32 u0;
	__u32 v0;
	__u32 udअगरf;
	__u32 vdअगरf;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_xnr3_blending_params - Blending factor
 *
 * @strength: The factor क्रम blending output with input. This is tuning
 *	      parameterHigher values lead to more aggressive XNR operation.
 */
काष्ठा ipu3_uapi_xnr3_blending_params अणु
	__u32 strength;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_isp_xnr3_params - Extreme noise reduction v3 parameters
 *
 * @alpha: parameters क्रम xnr3 alpha. See &ipu3_uapi_xnr3_alpha_params
 * @coring: parameters क्रम xnr3 coring. See &ipu3_uapi_xnr3_coring_params
 * @blending: parameters क्रम xnr3 blending. See &ipu3_uapi_xnr3_blending_params
 */
काष्ठा ipu3_uapi_isp_xnr3_params अणु
	काष्ठा ipu3_uapi_xnr3_alpha_params alpha;
	काष्ठा ipu3_uapi_xnr3_coring_params coring;
	काष्ठा ipu3_uapi_xnr3_blending_params blending;
पूर्ण __packed;

/***** Obgrid (optical black level compensation) table entry *****/

/**
 * काष्ठा ipu3_uapi_obgrid_param - Optical black level compensation parameters
 *
 * @gr: Grid table values क्रम color GR
 * @r: Grid table values क्रम color R
 * @b: Grid table values क्रम color B
 * @gb: Grid table values क्रम color GB
 *
 * Black level is dअगरferent क्रम red, green, and blue channels. So black level
 * compensation is dअगरferent per channel.
 */
काष्ठा ipu3_uapi_obgrid_param अणु
	__u16 gr;
	__u16 r;
	__u16 b;
	__u16 gb;
पूर्ण __packed;

/******************* V4L2_META_FMT_IPU3_PARAMS *******************/

/**
 * काष्ठा ipu3_uapi_flags - bits to indicate which pipeline needs update
 *
 * @gdc: 0 = no update, 1 = update.
 * @obgrid: 0 = no update, 1 = update.
 * @reserved1: Not used.
 * @acc_bnr: 0 = no update, 1 = update.
 * @acc_green_disparity: 0 = no update, 1 = update.
 * @acc_dm: 0 = no update, 1 = update.
 * @acc_ccm: 0 = no update, 1 = update.
 * @acc_gamma: 0 = no update, 1 = update.
 * @acc_csc: 0 = no update, 1 = update.
 * @acc_cds: 0 = no update, 1 = update.
 * @acc_shd: 0 = no update, 1 = update.
 * @reserved2: Not used.
 * @acc_iefd: 0 = no update, 1 = update.
 * @acc_yds_c0: 0 = no update, 1 = update.
 * @acc_chnr_c0: 0 = no update, 1 = update.
 * @acc_y_ee_nr: 0 = no update, 1 = update.
 * @acc_yds: 0 = no update, 1 = update.
 * @acc_chnr: 0 = no update, 1 = update.
 * @acc_yपंचांग: 0 = no update, 1 = update.
 * @acc_yds2: 0 = no update, 1 = update.
 * @acc_tcc: 0 = no update, 1 = update.
 * @acc_dpc: 0 = no update, 1 = update.
 * @acc_bds: 0 = no update, 1 = update.
 * @acc_anr: 0 = no update, 1 = update.
 * @acc_awb_fr: 0 = no update, 1 = update.
 * @acc_ae: 0 = no update, 1 = update.
 * @acc_af: 0 = no update, 1 = update.
 * @acc_awb: 0 = no update, 1 = update.
 * @__acc_osys: 0 = no update, 1 = update.
 * @reserved3: Not used.
 * @lin_vmem_params: 0 = no update, 1 = update.
 * @tnr3_vmem_params: 0 = no update, 1 = update.
 * @xnr3_vmem_params: 0 = no update, 1 = update.
 * @tnr3_dmem_params: 0 = no update, 1 = update.
 * @xnr3_dmem_params: 0 = no update, 1 = update.
 * @reserved4: Not used.
 * @obgrid_param: 0 = no update, 1 = update.
 * @reserved5: Not used.
 */
काष्ठा ipu3_uapi_flags अणु
	__u32 gdc:1;
	__u32 obgrid:1;
	__u32 reserved1:30;

	__u32 acc_bnr:1;
	__u32 acc_green_disparity:1;
	__u32 acc_dm:1;
	__u32 acc_ccm:1;
	__u32 acc_gamma:1;
	__u32 acc_csc:1;
	__u32 acc_cds:1;
	__u32 acc_shd:1;
	__u32 reserved2:2;
	__u32 acc_iefd:1;
	__u32 acc_yds_c0:1;
	__u32 acc_chnr_c0:1;
	__u32 acc_y_ee_nr:1;
	__u32 acc_yds:1;
	__u32 acc_chnr:1;
	__u32 acc_yपंचांग:1;
	__u32 acc_yds2:1;
	__u32 acc_tcc:1;
	__u32 acc_dpc:1;
	__u32 acc_bds:1;
	__u32 acc_anr:1;
	__u32 acc_awb_fr:1;
	__u32 acc_ae:1;
	__u32 acc_af:1;
	__u32 acc_awb:1;
	__u32 reserved3:4;

	__u32 lin_vmem_params:1;
	__u32 tnr3_vmem_params:1;
	__u32 xnr3_vmem_params:1;
	__u32 tnr3_dmem_params:1;
	__u32 xnr3_dmem_params:1;
	__u32 reserved4:1;
	__u32 obgrid_param:1;
	__u32 reserved5:25;
पूर्ण __packed;

/**
 * काष्ठा ipu3_uapi_params - V4L2_META_FMT_IPU3_PARAMS
 *
 * @use:	select which parameters to apply, see &ipu3_uapi_flags
 * @acc_param:	ACC parameters, as specअगरied by &ipu3_uapi_acc_param
 * @lin_vmem_params:	linearization VMEM, as specअगरied by
 *			&ipu3_uapi_isp_lin_vmem_params
 * @tnr3_vmem_params:	tnr3 VMEM as specअगरied by
 *			&ipu3_uapi_isp_tnr3_vmem_params
 * @xnr3_vmem_params:	xnr3 VMEM as specअगरied by
 *			&ipu3_uapi_isp_xnr3_vmem_params
 * @tnr3_dmem_params:	tnr3 DMEM as specअगरied by &ipu3_uapi_isp_tnr3_params
 * @xnr3_dmem_params:	xnr3 DMEM as specअगरied by &ipu3_uapi_isp_xnr3_params
 * @obgrid_param:	obgrid parameters as specअगरied by
 *			&ipu3_uapi_obgrid_param
 *
 * The video queue "parameters" is of क्रमmat V4L2_META_FMT_IPU3_PARAMS.
 * This is a "single plane" v4l2_meta_क्रमmat using V4L2_BUF_TYPE_META_OUTPUT.
 *
 * काष्ठा ipu3_uapi_params as defined below contains a lot of parameters and
 * ipu3_uapi_flags selects which parameters to apply.
 */
काष्ठा ipu3_uapi_params अणु
	/* Flags which of the settings below are to be applied */
	काष्ठा ipu3_uapi_flags use __attribute__((aligned(32)));

	/* Accelerator cluster parameters */
	काष्ठा ipu3_uapi_acc_param acc_param;

	/* ISP vector address space parameters */
	काष्ठा ipu3_uapi_isp_lin_vmem_params lin_vmem_params;
	काष्ठा ipu3_uapi_isp_tnr3_vmem_params tnr3_vmem_params;
	काष्ठा ipu3_uapi_isp_xnr3_vmem_params xnr3_vmem_params;

	/* ISP data memory (DMEM) parameters */
	काष्ठा ipu3_uapi_isp_tnr3_params tnr3_dmem_params;
	काष्ठा ipu3_uapi_isp_xnr3_params xnr3_dmem_params;

	/* Optical black level compensation */
	काष्ठा ipu3_uapi_obgrid_param obgrid_param;
पूर्ण __packed;

#पूर्ण_अगर /* __IPU3_UAPI_H */
