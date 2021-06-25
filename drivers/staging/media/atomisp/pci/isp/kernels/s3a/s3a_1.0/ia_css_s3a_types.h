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

#अगर_अघोषित __IA_CSS_S3A_TYPES_H
#घोषणा __IA_CSS_S3A_TYPES_H

/* @file
* CSS-API header file क्रम 3A statistics parameters.
*/

#समावेश <ia_css_frac.h>

#अगर (defined(SYSTEM_css_skycam_c0_प्रणाली)) && (!defined(PIPE_GENERATION))
#समावेश "../../../../components/stats_3a/src/stats_3a_public.h"
#पूर्ण_अगर

/* 3A configuration. This configures the 3A statistics collection
 *  module.
 */

/* 3A statistics grid
 *
 *  ISP block: S3A1 (3A Support क्रम 3A ver.1 (Histogram is not used क्रम AE))
 *             S3A2 (3A Support क्रम 3A ver.2 (Histogram is used क्रम AE))
 *  ISP1: S3A1 is used.
 *  ISP2: S3A2 is used.
 */
काष्ठा ia_css_3a_grid_info अणु
#अगर defined(SYSTEM_css_skycam_c0_प्रणाली)
	u32 ae_enable;					/** ae enabled in binary,
								   0:disabled, 1:enabled */
	काष्ठा ae_खुला_config_grid_config
		ae_grd_info;	/** see description in ae_खुला.h*/

	u32 awb_enable;					/** awb enabled in binary,
								   0:disabled, 1:enabled */
	काष्ठा awb_खुला_config_grid_config
		awb_grd_info;	/** see description in awb_खुला.h*/

	u32 af_enable;					/** af enabled in binary,
								   0:disabled, 1:enabled */
	काष्ठा af_खुला_grid_config		af_grd_info;	/** see description in af_खुला.h*/

	u32 awb_fr_enable;					/** awb_fr enabled in binary,
								   0:disabled, 1:enabled */
	काष्ठा awb_fr_खुला_grid_config
		awb_fr_grd_info;/** see description in awb_fr_खुला.h*/

	u32 elem_bit_depth;    /** TODO:Taken from BYT  - need input from AIQ
					अगर needed क्रम SKC
					Bit depth of element used
					to calculate 3A statistics.
					This is 13, which is the normalized
					bayer bit depth in DSP. */

#अन्यथा
	u32 enable;            /** 3A statistics enabled.
					0:disabled, 1:enabled */
	u32 use_dmem;          /** DMEM or VMEM determines layout.
					0:3A statistics are stored to VMEM,
					1:3A statistics are stored to DMEM */
	u32 has_histogram;     /** Statistics include histogram.
					0:no histogram, 1:has histogram */
	u32 width;		    /** Width of 3A grid table.
					(= Horizontal number of grid cells
					in table, which cells have effective
					statistics.) */
	u32 height;	    /** Height of 3A grid table.
					(= Vertical number of grid cells
					in table, which cells have effective
					statistics.) */
	u32 aligned_width;     /** Horizontal stride (क्रम alloc).
					(= Horizontal number of grid cells
					in table, which means
					the allocated width.) */
	u32 aligned_height;    /** Vertical stride (क्रम alloc).
					(= Vertical number of grid cells
					in table, which means
					the allocated height.) */
	u32 bqs_per_grid_cell; /** Grid cell size in BQ(Bayer Quad) unit.
					(1BQ means अणुGr,R,B,Gbपूर्ण(2x2 pixels).)
					Valid values are 8,16,32,64. */
	u32 deci_factor_log2;  /** log2 of bqs_per_grid_cell. */
	u32 elem_bit_depth;    /** Bit depth of element used
					to calculate 3A statistics.
					This is 13, which is the normalized
					bayer bit depth in DSP. */
#पूर्ण_अगर
पूर्ण;

/* This काष्ठा should be split पूर्णांकo 3, क्रम AE, AWB and AF.
 * However, that will require driver/ 3A lib modअगरications.
 */

/* 3A configuration. This configures the 3A statistics collection
 *  module.
 *
 *  ae_y_*: Coefficients to calculate luminance from bayer.
 *  awb_lg_*: Thresholds to check the saturated bayer pixels क्रम AWB.
 *    Condition of effective pixel क्रम AWB level gate check:
 *      bayer(sensor) <= awb_lg_high_raw &&
 *      bayer(when AWB statisitcs is calculated) >= awb_lg_low &&
 *      bayer(when AWB statisitcs is calculated) <= awb_lg_high
 *  af_fir*: Coefficients of high pass filter to calculate AF statistics.
 *
 *  ISP block: S3A1(ae_y_* क्रम AE/AF, awb_lg_* क्रम AWB)
 *             S3A2(ae_y_* क्रम AF, awb_lg_* क्रम AWB)
 *             SDVS1(ae_y_*)
 *             SDVS2(ae_y_*)
 *  ISP1: S3A1 and SDVS1 are used.
 *  ISP2: S3A2 and SDVS2 are used.
 */
काष्ठा ia_css_3a_config अणु
	ia_css_u0_16 ae_y_coef_r;	/** Weight of R क्रम Y.
						u0.16, [0,65535],
						शेष/ineffective 25559 */
	ia_css_u0_16 ae_y_coef_g;	/** Weight of G क्रम Y.
						u0.16, [0,65535],
						शेष/ineffective 32768 */
	ia_css_u0_16 ae_y_coef_b;	/** Weight of B क्रम Y.
						u0.16, [0,65535],
						शेष/ineffective 7209 */
	ia_css_u0_16 awb_lg_high_raw;	/** AWB level gate high क्रम raw.
						u0.16, [0,65535],
						शेष 65472(=1023*64),
						ineffective 65535 */
	ia_css_u0_16 awb_lg_low;	/** AWB level gate low.
						u0.16, [0,65535],
						शेष 64(=1*64),
						ineffective 0 */
	ia_css_u0_16 awb_lg_high;	/** AWB level gate high.
						u0.16, [0,65535],
						शेष 65535,
						ineffective 65535 */
	ia_css_s0_15 af_fir1_coef[7];	/** AF FIR coefficients of fir1.
						s0.15, [-32768,32767],
				शेष/ineffective
				-6689,-12207,-32768,32767,12207,6689,0 */
	ia_css_s0_15 af_fir2_coef[7];	/** AF FIR coefficients of fir2.
						s0.15, [-32768,32767],
				शेष/ineffective
				2053,0,-18437,32767,-18437,2053,0 */
पूर्ण;

/* 3A statistics. This काष्ठाure describes the data stored
 *  in each 3A grid poपूर्णांक.
 *
 *  ISP block: S3A1 (3A Support क्रम 3A ver.1) (Histogram is not used क्रम AE)
 *             S3A2 (3A Support क्रम 3A ver.2) (Histogram is used क्रम AE)
 *             - ae_y is used only क्रम S3A1.
 *             - awb_* and af_* are used both क्रम S3A1 and S3A2.
 *  ISP1: S3A1 is used.
 *  ISP2: S3A2 is used.
 */
काष्ठा ia_css_3a_output अणु
	s32 ae_y;    /** Sum of Y in a statistics winकरोw, क्रम AE.
				(u19.13) */
	s32 awb_cnt; /** Number of effective pixels
				in a statistics winकरोw.
				Pixels passed by the AWB level gate check are
				judged as "effective". (u32) */
	s32 awb_gr;  /** Sum of Gr in a statistics winकरोw, क्रम AWB.
				All Gr pixels (not only क्रम effective pixels)
				are summed. (u19.13) */
	s32 awb_r;   /** Sum of R in a statistics winकरोw, क्रम AWB.
				All R pixels (not only क्रम effective pixels)
				are summed. (u19.13) */
	s32 awb_b;   /** Sum of B in a statistics winकरोw, क्रम AWB.
				All B pixels (not only क्रम effective pixels)
				are summed. (u19.13) */
	s32 awb_gb;  /** Sum of Gb in a statistics winकरोw, क्रम AWB.
				All Gb pixels (not only क्रम effective pixels)
				are summed. (u19.13) */
	s32 af_hpf1; /** Sum of |Y| following high pass filter af_fir1
				within a statistics winकरोw, क्रम AF. (u19.13) */
	s32 af_hpf2; /** Sum of |Y| following high pass filter af_fir2
				within a statistics winकरोw, क्रम AF. (u19.13) */
पूर्ण;

/* 3A Statistics. This काष्ठाure describes the statistics that are generated
 *  using the provided configuration (ia_css_3a_config).
 */
काष्ठा ia_css_3a_statistics अणु
	काष्ठा ia_css_3a_grid_info
		grid;	/** grid info contains the dimensions of the 3A grid */
	काष्ठा ia_css_3a_output
		*data;	/** the poपूर्णांकer to 3a_output[grid.width * grid.height]
						     containing the 3A statistics */
	काष्ठा ia_css_3a_rgby_output *rgby_data;/** the poपूर्णांकer to 3a_rgby_output[256]
						     containing the histogram */
पूर्ण;

/* Histogram (Statistics क्रम AE).
 *
 *  4 histograms(r,g,b,y),
 *  256 bins क्रम each histogram, अचिन्हित 24bit value क्रम each bin.
 *    काष्ठा ia_css_3a_rgby_output data[256];

 *  ISP block: HIST2
 * (ISP1: HIST2 is not used.)
 *  ISP2: HIST2 is used.
 */
काष्ठा ia_css_3a_rgby_output अणु
	u32 r;	/** Number of R of one bin of the histogram R. (u24) */
	u32 g;	/** Number of G of one bin of the histogram G. (u24) */
	u32 b;	/** Number of B of one bin of the histogram B. (u24) */
	u32 y;	/** Number of Y of one bin of the histogram Y. (u24) */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_S3A_TYPES_H */
