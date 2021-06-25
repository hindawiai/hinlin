<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _SH_CSS_DEFS_H_
#घोषणा _SH_CSS_DEFS_H_

#समावेश "isp.h"

/*#समावेश "vamem.h"*/ /* Cannot include क्रम VAMEM properties this file is visible on ISP -> pipeline generator */

#समावेश "math_support.h"	/* max(), min, etc etc */

/* ID's क्रम refcount */
#घोषणा IA_CSS_REFCOUNT_PARAM_SET_POOL  0xCAFE0001
#घोषणा IA_CSS_REFCOUNT_PARAM_BUFFER    0xCAFE0002

/* Digital Image Stabilization */
#घोषणा SH_CSS_DIS_DECI_FACTOR_LOG2       6

/* UV offset: 1:uv=-128...127, 0:uv=0...255 */
#घोषणा SH_CSS_UV_OFFSET_IS_0             0

/* Bits of bayer is adjusted as 13 in ISP */
#घोषणा SH_CSS_BAYER_BITS                 13

/* Max value of bayer data (अचिन्हित 13bit in ISP) */
#घोषणा SH_CSS_BAYER_MAXVAL               ((1U << SH_CSS_BAYER_BITS) - 1)

/* Bits of yuv in ISP */
#घोषणा SH_CSS_ISP_YUV_BITS               8

#घोषणा SH_CSS_DP_GAIN_SHIFT              5
#घोषणा SH_CSS_BNR_GAIN_SHIFT             13
#घोषणा SH_CSS_YNR_GAIN_SHIFT             13
#घोषणा SH_CSS_AE_YCOEF_SHIFT             13
#घोषणा SH_CSS_AF_FIR_SHIFT               13
#घोषणा SH_CSS_YEE_DETAIL_GAIN_SHIFT      8  /* [u5.8] */
#घोषणा SH_CSS_YEE_SCALE_SHIFT            8
#घोषणा SH_CSS_TNR_COEF_SHIFT             13
#घोषणा SH_CSS_MACC_COEF_SHIFT            11 /* [s2.11] क्रम ISP1 */
#घोषणा SH_CSS_MACC2_COEF_SHIFT           13 /* [s[exp].[13-exp]] क्रम ISP2 */
#घोषणा SH_CSS_DIS_COEF_SHIFT             13

/* क्रमागतeration of the bayer करोwnscale factors. When a binary supports multiple
 * factors, the OR of these defines is used to build the mask of supported
 * factors. The BDS factor is used in pre-processor expressions so we cannot
 * use an क्रमागत here. */
#घोषणा SH_CSS_BDS_FACTOR_1_00	(0)
#घोषणा SH_CSS_BDS_FACTOR_1_25	(1)
#घोषणा SH_CSS_BDS_FACTOR_1_50	(2)
#घोषणा SH_CSS_BDS_FACTOR_2_00	(3)
#घोषणा SH_CSS_BDS_FACTOR_2_25	(4)
#घोषणा SH_CSS_BDS_FACTOR_2_50	(5)
#घोषणा SH_CSS_BDS_FACTOR_3_00	(6)
#घोषणा SH_CSS_BDS_FACTOR_4_00	(7)
#घोषणा SH_CSS_BDS_FACTOR_4_50	(8)
#घोषणा SH_CSS_BDS_FACTOR_5_00	(9)
#घोषणा SH_CSS_BDS_FACTOR_6_00	(10)
#घोषणा SH_CSS_BDS_FACTOR_8_00	(11)
#घोषणा NUM_BDS_FACTORS		(12)

#घोषणा PACK_BDS_FACTOR(factor)	(1 << (factor))

/* Following macros should match with the type क्रमागत ia_css_pipe_version in
 * ia_css_pipe_खुला.h. The reason to add these macros is that क्रमागत type
 * will be evaluted to 0 in preprocessing समय. */
#घोषणा SH_CSS_ISP_PIPE_VERSION_1	1
#घोषणा SH_CSS_ISP_PIPE_VERSION_2_2	2
#घोषणा SH_CSS_ISP_PIPE_VERSION_2_6_1	3
#घोषणा SH_CSS_ISP_PIPE_VERSION_2_7	4

/*--------------- sRGB Gamma -----------------
CCM        : YCgCo[0,8191] -> RGB[0,4095]
sRGB Gamma : RGB  [0,4095] -> RGB[0,8191]
CSC        : RGB  [0,8191] -> YUV[0,8191]

CCM:
Y[0,8191],CgCo[-4096,4095],coef[-8192,8191] -> RGB[0,4095]

sRGB Gamma:
RGB[0,4095] -(पूर्णांकerpolation step16)-> RGB[0,255] -(LUT 12bit)-> RGB[0,4095] -> RGB[0,8191]

CSC:
RGB[0,8191],coef[-8192,8191] -> RGB[0,8191]
--------------------------------------------*/
/* Bits of input/output of sRGB Gamma */
#घोषणा SH_CSS_RGB_GAMMA_INPUT_BITS       12 /* [0,4095] */
#घोषणा SH_CSS_RGB_GAMMA_OUTPUT_BITS      13 /* [0,8191] */

/* Bits of fractional part of पूर्णांकerpolation in vamem, [0,4095]->[0,255] */
#घोषणा SH_CSS_RGB_GAMMA_FRAC_BITS        \
	(SH_CSS_RGB_GAMMA_INPUT_BITS - SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE_LOG2)
#घोषणा SH_CSS_RGB_GAMMA_ONE              BIT(SH_CSS_RGB_GAMMA_FRAC_BITS)

/* Bits of input of CCM,  = 13, Y[0,8191],CgCo[-4096,4095] */
#घोषणा SH_CSS_YUV2RGB_CCM_INPUT_BITS     SH_CSS_BAYER_BITS

/* Bits of output of CCM,  = 12, RGB[0,4095] */
#घोषणा SH_CSS_YUV2RGB_CCM_OUTPUT_BITS    SH_CSS_RGB_GAMMA_INPUT_BITS

/* Maximum value of output of CCM */
#घोषणा SH_CSS_YUV2RGB_CCM_MAX_OUTPUT     \
	((1 << SH_CSS_YUV2RGB_CCM_OUTPUT_BITS) - 1)

#घोषणा SH_CSS_NUM_INPUT_BUF_LINES        4

/* Left cropping only applicable क्रम sufficiently large nway */
#अगर ISP_VEC_NELEMS == 16
#घोषणा SH_CSS_MAX_LEFT_CROPPING          0
#घोषणा SH_CSS_MAX_TOP_CROPPING           0
#अन्यथा
#घोषणा SH_CSS_MAX_LEFT_CROPPING          12
#घोषणा SH_CSS_MAX_TOP_CROPPING           12
#पूर्ण_अगर

#घोषणा	SH_CSS_SP_MAX_WIDTH               1280

/* This is the maximum grid we can handle in the ISP binaries.
 * The host code makes sure no bigger grid is ever selected. */
#घोषणा SH_CSS_MAX_BQ_GRID_WIDTH          80
#घोषणा SH_CSS_MAX_BQ_GRID_HEIGHT         60

/* The minimum dvs envelope is 12x12(क्रम IPU2) to make sure the
 * invalid rows/columns that result from filter initialization are skipped. */
#घोषणा SH_CSS_MIN_DVS_ENVELOPE           12U

/* The FPGA प्रणाली (vec_nelems == 16) only supports upto 5MP */
#अगर ISP_VEC_NELEMS == 16
#घोषणा SH_CSS_MAX_SENSOR_WIDTH           2560
#घोषणा SH_CSS_MAX_SENSOR_HEIGHT          1920
#अन्यथा
#घोषणा SH_CSS_MAX_SENSOR_WIDTH           4608
#घोषणा SH_CSS_MAX_SENSOR_HEIGHT          3450
#पूर्ण_अगर

/* Limited to reduce vmem pressure */
#अगर ISP_VMEM_DEPTH >= 3072
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_WIDTH  SH_CSS_MAX_SENSOR_WIDTH
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_HEIGHT SH_CSS_MAX_SENSOR_HEIGHT
#अन्यथा
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_WIDTH  3264
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_HEIGHT 2448
#पूर्ण_अगर
/* When using bayer decimation */
/*
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_WIDTH_DEC  4224
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_HEIGHT_DEC 3168
*/
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_WIDTH_DEC  SH_CSS_MAX_SENSOR_WIDTH
#घोषणा SH_CSS_MAX_CONTINUOUS_SENSOR_HEIGHT_DEC SH_CSS_MAX_SENSOR_HEIGHT

#घोषणा SH_CSS_MIN_SENSOR_WIDTH           2
#घोषणा SH_CSS_MIN_SENSOR_HEIGHT          2

/*
#घोषणा SH_CSS_MAX_VF_WIDTH_DEC               1920
#घोषणा SH_CSS_MAX_VF_HEIGHT_DEC              1080
*/
#घोषणा SH_CSS_MAX_VF_WIDTH_DEC               SH_CSS_MAX_VF_WIDTH
#घोषणा SH_CSS_MAX_VF_HEIGHT_DEC              SH_CSS_MAX_VF_HEIGHT

/* We use 16 bits per coordinate component, including पूर्णांकeger
   and fractional bits */
#घोषणा SH_CSS_MORPH_TABLE_GRID               ISP_VEC_NELEMS
#घोषणा SH_CSS_MORPH_TABLE_ELEM_BYTES         2
#घोषणा SH_CSS_MORPH_TABLE_ELEMS_PER_DDR_WORD \
	(HIVE_ISP_DDR_WORD_BYTES / SH_CSS_MORPH_TABLE_ELEM_BYTES)

#घोषणा ISP2400_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR   (SH_CSS_MAX_BQ_GRID_WIDTH + 1)
#घोषणा ISP2400_SH_CSS_MAX_SCTBL_HEIGHT_PER_COLOR   (SH_CSS_MAX_BQ_GRID_HEIGHT + 1)

#घोषणा ISP2400_SH_CSS_MAX_SCTBL_ALIGNED_WIDTH_PER_COLOR \
	CEIL_MUL(ISP2400_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR, ISP_VEC_NELEMS)

/* TODO: I will move macros of "*_SCTBL_*" to SC kernel.
   "+ 2" should be "+ SH_CSS_SCTBL_CENTERING_MARGIN + SH_CSS_SCTBL_LAST_GRID_COUNT". (michie, Sep/23/2014) */
#घोषणा ISP2401_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR   (SH_CSS_MAX_BQ_GRID_WIDTH + 2)
#घोषणा ISP2401_SH_CSS_MAX_SCTBL_HEIGHT_PER_COLOR   (SH_CSS_MAX_BQ_GRID_HEIGHT + 2)

#घोषणा ISP2401_SH_CSS_MAX_SCTBL_ALIGNED_WIDTH_PER_COLOR \
	CEIL_MUL(ISP2400_SH_CSS_MAX_SCTBL_WIDTH_PER_COLOR, ISP_VEC_NELEMS)

/* Each line of this table is aligned to the maximum line width. */
#घोषणा SH_CSS_MAX_S3ATBL_WIDTH              SH_CSS_MAX_BQ_GRID_WIDTH

/* Video mode specअगरic DVS define */
/* The video binary supports a delay of 1 or 2 frames */
#घोषणा VIDEO_FRAME_DELAY		2
/* +1 because DVS पढ़ोs the previous and ग_लिखोs the current frame concurrently */
#घोषणा MAX_NUM_VIDEO_DELAY_FRAMES	(VIDEO_FRAME_DELAY + 1)

/* Preview mode specअगरic DVS define. */
/* In preview we only need GDC functionality (and not the DVS functionality) */
/* The minimum number of DVS frames you need is 2, one were GDC पढ़ोs from and another where GDC ग_लिखोs पूर्णांकo */
#घोषणा NUM_PREVIEW_DVS_FRAMES		(2)

/* TNR is no दीर्घer exclusive to video, SkyCam preview has TNR too (same kernel as video).
 * All uses the generic define NUM_TNR_FRAMES. The define NUM_VIDEO_TNR_FRAMES has been deprecated.
 *
 * Notes
 * 1) The value depends on the used TNR kernel and is not something that depends on the mode
 *    and it is not something you just could choice.
 * 2) For the luma only pipeline a version that supports two dअगरferent sets of TNR reference frames
 * is being used.
 *.
 */
#घोषणा NUM_VALID_TNR_REF_FRAMES		(1) /* At least one valid TNR reference frame is required */
#घोषणा NUM_TNR_FRAMES_PER_REF_BUF_SET		(2)
/* In luma-only mode alternate illuminated frames are supported, that requires two द्विगुन buffers */
#घोषणा NUM_TNR_REF_BUF_SETS	(1)

#घोषणा NUM_TNR_FRAMES		(NUM_TNR_FRAMES_PER_REF_BUF_SET * NUM_TNR_REF_BUF_SETS)

#घोषणा NUM_VIDEO_TNR_FRAMES		2

/* Note that this is the define used to configure all data काष्ठाures common क्रम all modes */
/* It should be equal or bigger to the max number of DVS frames क्रम all possible modes */
/* Rules: these implement logic shared between the host code and ISP firmware.
   The ISP firmware needs these rules to be applied at pre-processor समय,
   that's why these are macros, not functions. */
#घोषणा _ISP_BQS(num)  ((num) / 2)
#घोषणा _ISP_VECS(width) CEIL_DIV(width, ISP_VEC_NELEMS)

#घोषणा ISP_BQ_GRID_WIDTH(elements_per_line, deci_factor_log2) \
	CEIL_SHIFT(elements_per_line / 2,  deci_factor_log2)
#घोषणा ISP_BQ_GRID_HEIGHT(lines_per_frame, deci_factor_log2) \
	CEIL_SHIFT(lines_per_frame / 2,  deci_factor_log2)
#घोषणा ISP_C_VECTORS_PER_LINE(elements_per_line) \
	_ISP_VECS(elements_per_line / 2)

/* The morphing table is similar to the shading table in the sense that we
   have 1 more value than we have cells in the grid. */
#घोषणा _ISP_MORPH_TABLE_WIDTH(पूर्णांक_width) \
	(CEIL_DIV(पूर्णांक_width, SH_CSS_MORPH_TABLE_GRID) + 1)
#घोषणा _ISP_MORPH_TABLE_HEIGHT(पूर्णांक_height) \
	(CEIL_DIV(पूर्णांक_height, SH_CSS_MORPH_TABLE_GRID) + 1)
#घोषणा _ISP_MORPH_TABLE_ALIGNED_WIDTH(width) \
	CEIL_MUL(_ISP_MORPH_TABLE_WIDTH(width), \
		 SH_CSS_MORPH_TABLE_ELEMS_PER_DDR_WORD)

#घोषणा _ISP2400_SCTBL_WIDTH_PER_COLOR(input_width, deci_factor_log2) \
	(ISP_BQ_GRID_WIDTH(input_width, deci_factor_log2) + 1)
#घोषणा _ISP2400_SCTBL_HEIGHT(input_height, deci_factor_log2) \
	(ISP_BQ_GRID_HEIGHT(input_height, deci_factor_log2) + 1)
#घोषणा _ISP2400_SCTBL_ALIGNED_WIDTH_PER_COLOR(input_width, deci_factor_log2) \
	CEIL_MUL(_ISP_SCTBL_WIDTH_PER_COLOR(input_width, deci_factor_log2), \
		 ISP_VEC_NELEMS)

/* To position the shading center grid poपूर्णांक on the center of output image,
 * one more grid cell is needed as margin. */
#घोषणा SH_CSS_SCTBL_CENTERING_MARGIN	1

/* The shading table width and height are the number of grids, not cells. The last grid should be counted. */
#घोषणा SH_CSS_SCTBL_LAST_GRID_COUNT	1

/* Number of horizontal grids per color in the shading table. */
#घोषणा _ISP2401_SCTBL_WIDTH_PER_COLOR(input_width, deci_factor_log2) \
	(ISP_BQ_GRID_WIDTH(input_width, deci_factor_log2) + \
	SH_CSS_SCTBL_CENTERING_MARGIN + SH_CSS_SCTBL_LAST_GRID_COUNT)

/* Number of vertical grids per color in the shading table. */
#घोषणा _ISP2401_SCTBL_HEIGHT(input_height, deci_factor_log2) \
	(ISP_BQ_GRID_HEIGHT(input_height, deci_factor_log2) + \
	SH_CSS_SCTBL_CENTERING_MARGIN + SH_CSS_SCTBL_LAST_GRID_COUNT)

/* ISP2401: Legacy API: Number of horizontal grids per color in the shading table. */
#घोषणा _ISP_SCTBL_LEGACY_WIDTH_PER_COLOR(input_width, deci_factor_log2) \
	(ISP_BQ_GRID_WIDTH(input_width, deci_factor_log2) + SH_CSS_SCTBL_LAST_GRID_COUNT)

/* ISP2401: Legacy API: Number of vertical grids per color in the shading table. */
#घोषणा _ISP_SCTBL_LEGACY_HEIGHT(input_height, deci_factor_log2) \
	(ISP_BQ_GRID_HEIGHT(input_height, deci_factor_log2) + SH_CSS_SCTBL_LAST_GRID_COUNT)

/* *****************************************************************
 * Statistics क्रम 3A (Auto Focus, Auto White Balance, Auto Exposure)
 * *****************************************************************/
/* अगर left cropping is used, 3A statistics are also cropped by 2 vectors. */
#घोषणा _ISP_S3ATBL_WIDTH(in_width, deci_factor_log2) \
	(_ISP_BQS(in_width) >> deci_factor_log2)
#घोषणा _ISP_S3ATBL_HEIGHT(in_height, deci_factor_log2) \
	(_ISP_BQS(in_height) >> deci_factor_log2)
#घोषणा _ISP_S3A_ELEMS_ISP_WIDTH(width, left_crop) \
	(width - ((left_crop) ? 2 * ISP_VEC_NELEMS : 0))

#घोषणा _ISP_S3ATBL_ISP_WIDTH(in_width, deci_factor_log2) \
	CEIL_SHIFT(_ISP_BQS(in_width), deci_factor_log2)
#घोषणा _ISP_S3ATBL_ISP_HEIGHT(in_height, deci_factor_log2) \
	CEIL_SHIFT(_ISP_BQS(in_height), deci_factor_log2)
#घोषणा ISP_S3ATBL_VECTORS \
	_ISP_VECS(SH_CSS_MAX_S3ATBL_WIDTH * \
		  (माप(काष्ठा ia_css_3a_output) / माप(पूर्णांक32_t)))
#घोषणा ISP_S3ATBL_HI_LO_STRIDE \
	(ISP_S3ATBL_VECTORS * ISP_VEC_NELEMS)
#घोषणा ISP_S3ATBL_HI_LO_STRIDE_BYTES \
	(माप(अचिन्हित लघु) * ISP_S3ATBL_HI_LO_STRIDE)

/* Viewfinder support */
#घोषणा __ISP_MAX_VF_OUTPUT_WIDTH(width, left_crop) \
	(width - 2 * ISP_VEC_NELEMS + ((left_crop) ? 2 * ISP_VEC_NELEMS : 0))

#घोषणा __ISP_VF_OUTPUT_WIDTH_VECS(out_width, vf_log_करोwnscale) \
	(_ISP_VECS((out_width) >> (vf_log_करोwnscale)))

#घोषणा _ISP_VF_OUTPUT_WIDTH(vf_out_vecs) ((vf_out_vecs) * ISP_VEC_NELEMS)
#घोषणा _ISP_VF_OUTPUT_HEIGHT(out_height, vf_log_ds) \
	((out_height) >> (vf_log_ds))

#घोषणा _ISP_LOG_VECTOR_STEP(mode) \
	((mode) == IA_CSS_BINARY_MODE_CAPTURE_PP ? 2 : 1)

/* It is preferred to have not more than 2x scaling at one step
 * in GDC (assumption is क्रम capture_pp and yuv_scale stages) */
#घोषणा MAX_PREFERRED_YUV_DS_PER_STEP	2

/* Rules क्रम computing the पूर्णांकernal width. This is extremely complicated
 * and definitely needs to be commented and explained. */
#घोषणा _ISP_LEFT_CROP_EXTRA(left_crop) ((left_crop) > 0 ? 2 * ISP_VEC_NELEMS : 0)

#घोषणा __ISP_MIN_INTERNAL_WIDTH(num_chunks, pipelining, mode) \
	((num_chunks) * (pipelining) * (1 << _ISP_LOG_VECTOR_STEP(mode)) * \
	 ISP_VEC_NELEMS)

#घोषणा __ISP_PADDED_OUTPUT_WIDTH(out_width, dvs_env_width, left_crop) \
	((out_width) + MAX(dvs_env_width, _ISP_LEFT_CROP_EXTRA(left_crop)))

#घोषणा __ISP_CHUNK_STRIDE_ISP(mode) \
	((1 << _ISP_LOG_VECTOR_STEP(mode)) * ISP_VEC_NELEMS)

#घोषणा __ISP_CHUNK_STRIDE_DDR(c_subsampling, num_chunks) \
	((c_subsampling) * (num_chunks) * HIVE_ISP_DDR_WORD_BYTES)
#घोषणा __ISP_INTERNAL_WIDTH(out_width, \
			     dvs_env_width, \
			     left_crop, \
			     mode, \
			     c_subsampling, \
			     num_chunks, \
			     pipelining) \
	CEIL_MUL2(CEIL_MUL2(MAX(__ISP_PADDED_OUTPUT_WIDTH(out_width, \
							    dvs_env_width, \
							    left_crop), \
				  __ISP_MIN_INTERNAL_WIDTH(num_chunks, \
							   pipelining, \
							   mode) \
				 ), \
			  __ISP_CHUNK_STRIDE_ISP(mode) \
			 ), \
		 __ISP_CHUNK_STRIDE_DDR(c_subsampling, num_chunks) \
		)

#घोषणा __ISP_INTERNAL_HEIGHT(out_height, dvs_env_height, top_crop) \
	((out_height) + (dvs_env_height) + top_crop)

/* @GC: Input can be up to sensor resolution when either bayer करोwnscaling
 *	or raw binning is enabled.
 *	Also, during continuous mode, we need to align to 4*NWAY since input
 *	should support binning */
#घोषणा _ISP_MAX_INPUT_WIDTH(max_पूर्णांकernal_width, enable_ds, enable_fixed_bayer_ds, enable_raw_bin, \
				enable_continuous) \
	((enable_ds) ? \
	   SH_CSS_MAX_SENSOR_WIDTH :\
	 (enable_fixed_bayer_ds) ? \
	   CEIL_MUL(SH_CSS_MAX_CONTINUOUS_SENSOR_WIDTH_DEC, 4 * ISP_VEC_NELEMS) : \
	 (enable_raw_bin) ? \
	   CEIL_MUL(SH_CSS_MAX_CONTINUOUS_SENSOR_WIDTH, 4 * ISP_VEC_NELEMS) : \
	 (enable_continuous) ? \
	   SH_CSS_MAX_CONTINUOUS_SENSOR_WIDTH \
	   : max_पूर्णांकernal_width)

#घोषणा _ISP_INPUT_WIDTH(पूर्णांकernal_width, ds_input_width, enable_ds) \
	((enable_ds) ? (ds_input_width) : (पूर्णांकernal_width))

#घोषणा _ISP_MAX_INPUT_HEIGHT(max_पूर्णांकernal_height, enable_ds, enable_fixed_bayer_ds, enable_raw_bin, \
				enable_continuous) \
	((enable_ds) ? \
	   SH_CSS_MAX_SENSOR_HEIGHT :\
	 (enable_fixed_bayer_ds) ? \
	   SH_CSS_MAX_CONTINUOUS_SENSOR_HEIGHT_DEC : \
	 (enable_raw_bin || enable_continuous) ? \
	   SH_CSS_MAX_CONTINUOUS_SENSOR_HEIGHT \
	   : max_पूर्णांकernal_height)

#घोषणा _ISP_INPUT_HEIGHT(पूर्णांकernal_height, ds_input_height, enable_ds) \
	((enable_ds) ? (ds_input_height) : (पूर्णांकernal_height))

#घोषणा SH_CSS_MAX_STAGES 8 /* primary_stage[1-6], capture_pp, vf_pp */

/* For CSI2+ input प्रणाली, it requires extra paddinga from vmem */
#घोषणा _ISP_EXTRA_PADDING_VECS 0

#पूर्ण_अगर /* _SH_CSS_DEFS_H_ */
