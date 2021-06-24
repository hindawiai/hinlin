<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित _ATOM_ISP_H
#घोषणा _ATOM_ISP_H

#समावेश <linux/types.h>
#समावेश <linux/version.h>

/* काष्ठा media_device_info.hw_revision */
#घोषणा ATOMISP_HW_REVISION_MASK	0x0000ff00
#घोषणा ATOMISP_HW_REVISION_SHIFT	8
#घोषणा ATOMISP_HW_REVISION_ISP2300	0x00
#घोषणा ATOMISP_HW_REVISION_ISP2400	0x10
#घोषणा ATOMISP_HW_REVISION_ISP2401_LEGACY 0x11
#घोषणा ATOMISP_HW_REVISION_ISP2401	0x20

#घोषणा ATOMISP_HW_STEPPING_MASK	0x000000ff
#घोषणा ATOMISP_HW_STEPPING_A0		0x00
#घोषणा ATOMISP_HW_STEPPING_B0		0x10

/*ISP binary running mode*/
#घोषणा CI_MODE_PREVIEW		0x8000
#घोषणा CI_MODE_VIDEO		0x4000
#घोषणा CI_MODE_STILL_CAPTURE	0x2000
#घोषणा CI_MODE_CONTINUOUS	0x1000
#घोषणा CI_MODE_NONE		0x0000

#घोषणा OUTPUT_MODE_खाता 0x0100
#घोषणा OUTPUT_MODE_TEXT 0x0200

/*
 * Camera HAL sets this flag in v4l2_buffer reserved2 to indicate this
 * buffer has a per-frame parameter.
 */
#घोषणा ATOMISP_BUFFER_HAS_PER_FRAME_SETTING	0x80000000

/* Custom क्रमmat क्रम RAW capture from M10MO 0x3130314d */
#घोषणा V4L2_PIX_FMT_CUSTOM_M10MO_RAW	v4l2_fourcc('M', '1', '0', '1')

/* Custom media bus क्रमmats being used in atomisp */
#घोषणा V4L2_MBUS_FMT_CUSTOM_YUV420	0x8001
#घोषणा V4L2_MBUS_FMT_CUSTOM_YVU420	0x8002
#घोषणा V4L2_MBUS_FMT_CUSTOM_YUV422P	0x8003
#घोषणा V4L2_MBUS_FMT_CUSTOM_YUV444	0x8004
#घोषणा V4L2_MBUS_FMT_CUSTOM_NV12	0x8005
#घोषणा V4L2_MBUS_FMT_CUSTOM_NV21	0x8006
#घोषणा V4L2_MBUS_FMT_CUSTOM_NV16	0x8007
#घोषणा V4L2_MBUS_FMT_CUSTOM_YUYV	0x8008
#घोषणा V4L2_MBUS_FMT_CUSTOM_SBGGR16	0x8009
#घोषणा V4L2_MBUS_FMT_CUSTOM_RGB32	0x800a

/* Custom media bus क्रमmat क्रम M10MO RAW capture */
#अगर 0
#घोषणा V4L2_MBUS_FMT_CUSTOM_M10MO_RAW	0x800b
#पूर्ण_अगर

/* Configuration used by Bayer noise reduction and YCC noise reduction */
काष्ठा atomisp_nr_config अणु
	/* [gain] Strength of noise reduction क्रम Bayer NR (Used by Bayer NR) */
	अचिन्हित पूर्णांक bnr_gain;
	/* [gain] Strength of noise reduction क्रम YCC NR (Used by YCC NR) */
	अचिन्हित पूर्णांक ynr_gain;
	/* [पूर्णांकensity] Sensitivity of Edge (Used by Bayer NR) */
	अचिन्हित पूर्णांक direction;
	/* [पूर्णांकensity] coring threshold क्रम Cb (Used by YCC NR) */
	अचिन्हित पूर्णांक threshold_cb;
	/* [पूर्णांकensity] coring threshold क्रम Cr (Used by YCC NR) */
	अचिन्हित पूर्णांक threshold_cr;
पूर्ण;

/* Temporal noise reduction configuration */
काष्ठा atomisp_tnr_config अणु
	अचिन्हित पूर्णांक gain;	 /* [gain] Strength of NR */
	अचिन्हित पूर्णांक threshold_y;/* [पूर्णांकensity] Motion sensitivity क्रम Y */
	अचिन्हित पूर्णांक threshold_uv;/* [पूर्णांकensity] Motion sensitivity क्रम U/V */
पूर्ण;

/* Histogram. This contains num_elements values of type अचिन्हित पूर्णांक.
 * The data poपूर्णांकer is a DDR poपूर्णांकer (भव address).
 */
काष्ठा atomisp_histogram अणु
	अचिन्हित पूर्णांक num_elements;
	व्योम __user *data;
पूर्ण;

क्रमागत atomisp_ob_mode अणु
	atomisp_ob_mode_none,
	atomisp_ob_mode_fixed,
	atomisp_ob_mode_raster
पूर्ण;

/* Optical black level configuration */
काष्ठा atomisp_ob_config अणु
	/* Obtical black level mode (Fixed / Raster) */
	क्रमागत atomisp_ob_mode mode;
	/* [पूर्णांकensity] optical black level क्रम GR (relevant क्रम fixed mode) */
	अचिन्हित पूर्णांक level_gr;
	/* [पूर्णांकensity] optical black level क्रम R (relevant क्रम fixed mode) */
	अचिन्हित पूर्णांक level_r;
	/* [पूर्णांकensity] optical black level क्रम B (relevant क्रम fixed mode) */
	अचिन्हित पूर्णांक level_b;
	/* [पूर्णांकensity] optical black level क्रम GB (relevant क्रम fixed mode) */
	अचिन्हित पूर्णांक level_gb;
	/* [BQ] 0..63 start position of OB area (relevant क्रम raster mode) */
	अचिन्हित लघु start_position;
	/* [BQ] start..63 end position of OB area (relevant क्रम raster mode) */
	अचिन्हित लघु end_position;
पूर्ण;

/* Edge enhancement (sharpen) configuration */
काष्ठा atomisp_ee_config अणु
	/* [gain] The strength of sharpness. u5_11 */
	अचिन्हित पूर्णांक gain;
	/* [पूर्णांकensity] The threshold that भागides noises from edge. u8_8 */
	अचिन्हित पूर्णांक threshold;
	/* [gain] The strength of sharpness in pell-mell area. u5_11 */
	अचिन्हित पूर्णांक detail_gain;
पूर्ण;

काष्ठा atomisp_3a_output अणु
	पूर्णांक ae_y;
	पूर्णांक awb_cnt;
	पूर्णांक awb_gr;
	पूर्णांक awb_r;
	पूर्णांक awb_b;
	पूर्णांक awb_gb;
	पूर्णांक af_hpf1;
	पूर्णांक af_hpf2;
पूर्ण;

क्रमागत atomisp_calibration_type अणु
	calibration_type1,
	calibration_type2,
	calibration_type3
पूर्ण;

काष्ठा atomisp_calibration_group अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक type;
	अचिन्हित लघु *calb_grp_values;
पूर्ण;

काष्ठा atomisp_gc_config अणु
	__u16 gain_k1;
	__u16 gain_k2;
पूर्ण;

काष्ठा atomisp_3a_config अणु
	अचिन्हित पूर्णांक ae_y_coef_r;	/* [gain] Weight of R क्रम Y */
	अचिन्हित पूर्णांक ae_y_coef_g;	/* [gain] Weight of G क्रम Y */
	अचिन्हित पूर्णांक ae_y_coef_b;	/* [gain] Weight of B क्रम Y */
	अचिन्हित पूर्णांक awb_lg_high_raw;	/* [पूर्णांकensity]
					   AWB level gate high क्रम raw */
	अचिन्हित पूर्णांक awb_lg_low;	/* [पूर्णांकensity] AWB level gate low */
	अचिन्हित पूर्णांक awb_lg_high;	/* [पूर्णांकensity] AWB level gate high */
	पूर्णांक af_fir1_coef[7];	/* [factor] AF FIR coefficients of fir1 */
	पूर्णांक af_fir2_coef[7];	/* [factor] AF FIR coefficients of fir2 */
पूर्ण;

काष्ठा atomisp_dvs_grid_info अणु
	u32 enable;
	u32 width;
	u32 aligned_width;
	u32 height;
	u32 aligned_height;
	u32 bqs_per_grid_cell;
	u32 num_hor_coefs;
	u32 num_ver_coefs;
पूर्ण;

काष्ठा atomisp_dvs_envelop अणु
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
पूर्ण;

काष्ठा atomisp_grid_info अणु
	u32 enable;
	u32 use_dmem;
	u32 has_histogram;
	u32 s3a_width;
	u32 s3a_height;
	u32 aligned_width;
	u32 aligned_height;
	u32 s3a_bqs_per_grid_cell;
	u32 deci_factor_log2;
	u32 elem_bit_depth;
पूर्ण;

काष्ठा atomisp_dis_vector अणु
	पूर्णांक x;
	पूर्णांक y;
पूर्ण;

/* DVS 2.0 Coefficient types. This काष्ठाure contains 4 poपूर्णांकers to
 *  arrays that contain the coeffients क्रम each type.
 */
काष्ठा atomisp_dvs2_coef_types अणु
	लघु __user *odd_real; /** real part of the odd coefficients*/
	लघु __user *odd_imag; /** imaginary part of the odd coefficients*/
	लघु __user *even_real;/** real part of the even coefficients*/
	लघु __user *even_imag;/** imaginary part of the even coefficients*/
पूर्ण;

/*
 * DVS 2.0 Statistic types. This काष्ठाure contains 4 poपूर्णांकers to
 * arrays that contain the statistics क्रम each type.
 */
काष्ठा atomisp_dvs2_stat_types अणु
	पूर्णांक __user *odd_real; /** real part of the odd statistics*/
	पूर्णांक __user *odd_imag; /** imaginary part of the odd statistics*/
	पूर्णांक __user *even_real;/** real part of the even statistics*/
	पूर्णांक __user *even_imag;/** imaginary part of the even statistics*/
पूर्ण;

काष्ठा atomisp_dis_coefficients अणु
	काष्ठा atomisp_dvs_grid_info grid_info;
	काष्ठा atomisp_dvs2_coef_types hor_coefs;
	काष्ठा atomisp_dvs2_coef_types ver_coefs;
पूर्ण;

काष्ठा atomisp_dvs2_statistics अणु
	काष्ठा atomisp_dvs_grid_info grid_info;
	काष्ठा atomisp_dvs2_stat_types hor_prod;
	काष्ठा atomisp_dvs2_stat_types ver_prod;
पूर्ण;

काष्ठा atomisp_dis_statistics अणु
	काष्ठा atomisp_dvs2_statistics dvs2_stat;
	u32 exp_id;
पूर्ण;

काष्ठा atomisp_3a_rgby_output अणु
	u32 r;
	u32 g;
	u32 b;
	u32 y;
पूर्ण;

/*
 * Because we have 2 pipes at max to output metadata, thereक्रमe driver will use
 * ATOMISP_MAIN_METADATA to specअगरy the metadata from the pipe which keeps
 * streaming always and use ATOMISP_SEC_METADATA to specअगरy the metadata from
 * the pipe which is streaming by request like capture pipe of ZSL or SDV mode
 * as secondary metadata. And क्रम the use हाल which has only one pipe
 * streaming like online capture, ATOMISP_MAIN_METADATA will be used.
 */
क्रमागत atomisp_metadata_type अणु
	ATOMISP_MAIN_METADATA = 0,
	ATOMISP_SEC_METADATA,
	ATOMISP_METADATA_TYPE_NUM,
पूर्ण;

काष्ठा atomisp_metadata_with_type अणु
	/* to specअगरy which type of metadata to get */
	क्रमागत atomisp_metadata_type type;
	व्योम __user *data;
	u32 width;
	u32 height;
	u32 stride; /* in bytes */
	u32 exp_id; /* exposure ID */
	u32 *effective_width; /* mipi packets valid data size */
पूर्ण;

काष्ठा atomisp_metadata अणु
	व्योम __user *data;
	u32 width;
	u32 height;
	u32 stride; /* in bytes */
	u32 exp_id; /* exposure ID */
	u32 *effective_width; /* mipi packets valid data size */
पूर्ण;

काष्ठा atomisp_ext_isp_ctrl अणु
	u32 id;
	u32 data;
पूर्ण;

काष्ठा atomisp_3a_statistics अणु
	काष्ठा atomisp_grid_info  grid_info;
	काष्ठा atomisp_3a_output __user *data;
	काष्ठा atomisp_3a_rgby_output __user *rgby_data;
	u32 exp_id; /* exposure ID */
	u32 isp_config_id; /* isp config ID */
पूर्ण;

/**
 * काष्ठा atomisp_cont_capture_conf - continuous capture parameters
 * @num_captures: number of still images to capture
 * @skip_frames: number of frames to skip between 2 captures
 * @offset: offset in ring buffer to start capture
 *
 * For example, to capture 1 frame from past, current, and 1 from future
 * and skip one frame between each capture, parameters would be:
 * num_captures:3
 * skip_frames:1
 * offset:-2
 */

काष्ठा atomisp_cont_capture_conf अणु
	पूर्णांक num_captures;
	अचिन्हित पूर्णांक skip_frames;
	पूर्णांक offset;
	__u32 reserved[5];
पूर्ण;

काष्ठा atomisp_ae_winकरोw अणु
	पूर्णांक x_left;
	पूर्णांक x_right;
	पूर्णांक y_top;
	पूर्णांक y_bottom;
	पूर्णांक weight;
पूर्ण;

/* White Balance (Gain Adjust) */
काष्ठा atomisp_wb_config अणु
	अचिन्हित पूर्णांक पूर्णांकeger_bits;
	अचिन्हित पूर्णांक gr;	/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
	अचिन्हित पूर्णांक r;		/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
	अचिन्हित पूर्णांक b;		/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
	अचिन्हित पूर्णांक gb;	/* अचिन्हित <पूर्णांकeger_bits>.<16-पूर्णांकeger_bits> */
पूर्ण;

/* Color Space Conversion settings */
काष्ठा atomisp_cc_config अणु
	अचिन्हित पूर्णांक fraction_bits;
	पूर्णांक matrix[3 * 3];	/* RGB2YUV Color matrix, चिन्हित
				   <13-fraction_bits>.<fraction_bits> */
पूर्ण;

/* De pixel noise configuration */
काष्ठा atomisp_de_config अणु
	अचिन्हित पूर्णांक pixelnoise;
	अचिन्हित पूर्णांक c1_coring_threshold;
	अचिन्हित पूर्णांक c2_coring_threshold;
पूर्ण;

/* Chroma enhancement */
काष्ठा atomisp_ce_config अणु
	अचिन्हित अक्षर uv_level_min;
	अचिन्हित अक्षर uv_level_max;
पूर्ण;

/* Defect pixel correction configuration */
काष्ठा atomisp_dp_config अणु
	/* [पूर्णांकensity] The threshold of defect Pixel Correction, representing
	 * the permissible dअगरference of पूर्णांकensity between one pixel and its
	 * surrounding pixels. Smaller values result in more frequent pixel
	 * corrections. u0_16
	 */
	अचिन्हित पूर्णांक threshold;
	/* [gain] The sensitivity of mis-correction. ISP will miss a lot of
	 * defects अगर the value is set too large. u8_8
	 */
	अचिन्हित पूर्णांक gain;
	अचिन्हित पूर्णांक gr;
	अचिन्हित पूर्णांक r;
	अचिन्हित पूर्णांक b;
	अचिन्हित पूर्णांक gb;
पूर्ण;

/* XNR threshold */
काष्ठा atomisp_xnr_config अणु
	__u16 threshold;
पूर्ण;

/* metadata config */
काष्ठा atomisp_metadata_config अणु
	u32 metadata_height;
	u32 metadata_stride;
पूर्ण;

/*
 * Generic resolution काष्ठाure.
 */
काष्ठा atomisp_resolution अणु
	u32 width;  /** Width */
	u32 height; /** Height */
पूर्ण;

/*
 * This specअगरies the coordinates (x,y)
 */
काष्ठा atomisp_zoom_poपूर्णांक अणु
	s32 x; /** x coordinate */
	s32 y; /** y coordinate */
पूर्ण;

/*
 * This specअगरies the region
 */
काष्ठा atomisp_zoom_region अणु
	काष्ठा atomisp_zoom_poपूर्णांक
		origin; /* Starting poपूर्णांक coordinates क्रम the region */
	काष्ठा atomisp_resolution resolution; /* Region resolution */
पूर्ण;

काष्ठा atomisp_dz_config अणु
	u32 dx; /** Horizontal zoom factor */
	u32 dy; /** Vertical zoom factor */
	काष्ठा atomisp_zoom_region zoom_region; /** region क्रम zoom */
पूर्ण;

काष्ठा atomisp_parm अणु
	काष्ठा atomisp_grid_info info;
	काष्ठा atomisp_dvs_grid_info dvs_grid;
	काष्ठा atomisp_dvs_envelop dvs_envelop;
	काष्ठा atomisp_wb_config wb_config;
	काष्ठा atomisp_cc_config cc_config;
	काष्ठा atomisp_ob_config ob_config;
	काष्ठा atomisp_de_config de_config;
	काष्ठा atomisp_dz_config dz_config;
	काष्ठा atomisp_ce_config ce_config;
	काष्ठा atomisp_dp_config dp_config;
	काष्ठा atomisp_nr_config nr_config;
	काष्ठा atomisp_ee_config ee_config;
	काष्ठा atomisp_tnr_config tnr_config;
	काष्ठा atomisp_metadata_config metadata_config;
पूर्ण;

काष्ठा dvs2_bq_resolution अणु
	पूर्णांक width_bq;         /* width [BQ] */
	पूर्णांक height_bq;        /* height [BQ] */
पूर्ण;

काष्ठा atomisp_dvs2_bq_resolutions अणु
	/* GDC source image size [BQ] */
	काष्ठा dvs2_bq_resolution source_bq;
	/* GDC output image size [BQ] */
	काष्ठा dvs2_bq_resolution output_bq;
	/* GDC effective envelope size [BQ] */
	काष्ठा dvs2_bq_resolution envelope_bq;
	/* isp pipe filter size [BQ] */
	काष्ठा dvs2_bq_resolution ispfilter_bq;
	/* GDC shit size [BQ] */
	काष्ठा dvs2_bq_resolution gdc_shअगरt_bq;
पूर्ण;

काष्ठा atomisp_dvs_6axis_config अणु
	u32 exp_id;
	u32 width_y;
	u32 height_y;
	u32 width_uv;
	u32 height_uv;
	u32 *xcoords_y;
	u32 *ycoords_y;
	u32 *xcoords_uv;
	u32 *ycoords_uv;
पूर्ण;

काष्ठा atomisp_क्रमmats_config अणु
	u32 video_full_range_flag;
पूर्ण;

काष्ठा atomisp_parameters अणु
	काष्ठा atomisp_wb_config   *wb_config;  /* White Balance config */
	काष्ठा atomisp_cc_config   *cc_config;  /* Color Correction config */
	काष्ठा atomisp_tnr_config  *tnr_config; /* Temporal Noise Reduction */
	काष्ठा atomisp_ecd_config  *ecd_config; /* Eigen Color Demosaicing */
	काष्ठा atomisp_ynr_config  *ynr_config; /* Y(Luma) Noise Reduction */
	काष्ठा atomisp_fc_config   *fc_config;  /* Fringe Control */
	काष्ठा atomisp_क्रमmats_config *क्रमmats_config; /* Formats Control */
	काष्ठा atomisp_cnr_config  *cnr_config; /* Chroma Noise Reduction */
	काष्ठा atomisp_macc_config *macc_config;  /* MACC */
	काष्ठा atomisp_ctc_config  *ctc_config; /* Chroma Tone Control */
	काष्ठा atomisp_aa_config   *aa_config;  /* Anti-Aliasing */
	काष्ठा atomisp_aa_config   *baa_config;  /* Anti-Aliasing */
	काष्ठा atomisp_ce_config   *ce_config;
	काष्ठा atomisp_dvs_6axis_config *dvs_6axis_config;
	काष्ठा atomisp_ob_config   *ob_config;  /* Objective Black config */
	काष्ठा atomisp_dp_config   *dp_config;  /* Dead Pixel config */
	काष्ठा atomisp_nr_config   *nr_config;  /* Noise Reduction config */
	काष्ठा atomisp_ee_config   *ee_config;  /* Edge Enhancement config */
	काष्ठा atomisp_de_config   *de_config;  /* Demosaic config */
	काष्ठा atomisp_gc_config   *gc_config;  /* Gamma Correction config */
	काष्ठा atomisp_anr_config  *anr_config; /* Advanced Noise Reduction */
	काष्ठा atomisp_3a_config   *a3a_config; /* 3A Statistics config */
	काष्ठा atomisp_xnr_config  *xnr_config; /* eXtra Noise Reduction */
	काष्ठा atomisp_dz_config   *dz_config;  /* Digital Zoom */
	काष्ठा atomisp_cc_config *yuv2rgb_cc_config; /* Color
							Correction config */
	काष्ठा atomisp_cc_config *rgb2yuv_cc_config; /* Color
							Correction config */
	काष्ठा atomisp_macc_table  *macc_table;
	काष्ठा atomisp_gamma_table *gamma_table;
	काष्ठा atomisp_ctc_table   *ctc_table;
	काष्ठा atomisp_xnr_table   *xnr_table;
	काष्ठा atomisp_rgb_gamma_table *r_gamma_table;
	काष्ठा atomisp_rgb_gamma_table *g_gamma_table;
	काष्ठा atomisp_rgb_gamma_table *b_gamma_table;
	काष्ठा atomisp_vector      *motion_vector; /* For 2-axis DVS */
	काष्ठा atomisp_shading_table *shading_table;
	काष्ठा atomisp_morph_table   *morph_table;
	काष्ठा atomisp_dvs_coefficients *dvs_coefs; /* DVS 1.0 coefficients */
	काष्ठा atomisp_dis_coefficients *dvs2_coefs; /* DVS 2.0 coefficients */
	काष्ठा atomisp_capture_config   *capture_config;
	काष्ठा atomisp_anr_thres   *anr_thres;

	व्योम	*lin_2500_config;       /* Skylake: Linearization config */
	व्योम	*obgrid_2500_config;    /* Skylake: OBGRID config */
	व्योम	*bnr_2500_config;       /* Skylake: bayer denoise config */
	व्योम	*shd_2500_config;       /* Skylake: shading config */
	व्योम	*dm_2500_config;        /* Skylake: demosaic config */
	व्योम	*rgbpp_2500_config;     /* Skylake: RGBPP config */
	व्योम	*dvs_stat_2500_config;  /* Skylake: DVS STAT config */
	व्योम	*lace_stat_2500_config; /* Skylake: LACE STAT config */
	व्योम	*yuvp1_2500_config;     /* Skylake: yuvp1 config */
	व्योम	*yuvp2_2500_config;     /* Skylake: yuvp2 config */
	व्योम	*tnr_2500_config;       /* Skylake: TNR config */
	व्योम	*dpc_2500_config;       /* Skylake: DPC config */
	व्योम	*awb_2500_config;       /* Skylake: स्वतः white balance config */
	व्योम	*awb_fr_2500_config;    /* Skylake: स्वतः white balance filter response config */
	व्योम	*anr_2500_config;       /* Skylake: ANR config */
	व्योम	*af_2500_config;        /* Skylake: स्वतः focus config */
	व्योम	*ae_2500_config;        /* Skylake: स्वतः exposure config */
	व्योम	*bds_2500_config;       /* Skylake: bayer करोwnscaler config */
	व्योम	*dvs_2500_config;       /* Skylake: digital video stabilization config */
	व्योम	*res_mgr_2500_config;

	/*
	 * Output frame poपूर्णांकer the config is to be applied to (optional),
	 * set to शून्य to make this config is applied as global.
	 */
	व्योम	*output_frame;
	/*
	 * Unique ID to track which config was actually applied to a particular
	 * frame, driver will send this id back with output frame together.
	 */
	u32	isp_config_id;

	/*
	 * Switch to control per_frame setting:
	 * 0: this is a global setting
	 * 1: this is a per_frame setting
	 * PLEASE KEEP THIS AT THE END OF THE STRUCTURE!!
	 */
	u32	per_frame_setting;
पूर्ण;

#घोषणा ATOMISP_GAMMA_TABLE_SIZE        1024
काष्ठा atomisp_gamma_table अणु
	अचिन्हित लघु data[ATOMISP_GAMMA_TABLE_SIZE];
पूर्ण;

/* Morphing table क्रम advanced ISP.
 * Each line of width elements takes up COORD_TABLE_EXT_WIDTH elements
 * in memory.
 */
#घोषणा ATOMISP_MORPH_TABLE_NUM_PLANES  6
काष्ठा atomisp_morph_table अणु
	अचिन्हित पूर्णांक enabled;

	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक width;	/* number of valid elements per line */
	अचिन्हित लघु __user *coordinates_x[ATOMISP_MORPH_TABLE_NUM_PLANES];
	अचिन्हित लघु __user *coordinates_y[ATOMISP_MORPH_TABLE_NUM_PLANES];
पूर्ण;

#घोषणा ATOMISP_NUM_SC_COLORS	4
#घोषणा ATOMISP_SC_FLAG_QUERY	BIT(0)

काष्ठा atomisp_shading_table अणु
	__u32 enable;

	__u32 sensor_width;
	__u32 sensor_height;
	__u32 width;
	__u32 height;
	__u32 fraction_bits;

	__u16 *data[ATOMISP_NUM_SC_COLORS];
पूर्ण;

काष्ठा atomisp_makernote_info अणु
	/* bits 31-16: numerator, bits 15-0: denominator */
	अचिन्हित पूर्णांक focal_length;
	/* bits 31-16: numerator, bits 15-0: denominator*/
	अचिन्हित पूर्णांक f_number_curr;
	/*
	* bits 31-24: max f-number numerator
	* bits 23-16: max f-number denominator
	* bits 15-8: min f-number numerator
	* bits 7-0: min f-number denominator
	*/
	अचिन्हित पूर्णांक f_number_range;
पूर्ण;

/* parameter क्रम MACC */
#घोषणा ATOMISP_NUM_MACC_AXES           16
काष्ठा atomisp_macc_table अणु
	लघु data[4 * ATOMISP_NUM_MACC_AXES];
पूर्ण;

काष्ठा atomisp_macc_config अणु
	पूर्णांक color_effect;
	काष्ठा atomisp_macc_table table;
पूर्ण;

/* Parameter क्रम ctc parameter control */
#घोषणा ATOMISP_CTC_TABLE_SIZE          1024
काष्ठा atomisp_ctc_table अणु
	अचिन्हित लघु data[ATOMISP_CTC_TABLE_SIZE];
पूर्ण;

/* Parameter क्रम overlay image loading */
काष्ठा atomisp_overlay अणु
	/* the frame containing the overlay data The overlay frame width should
	 * be the multiples of 2*ISP_VEC_NELEMS. The overlay frame height
	 * should be the multiples of 2.
	 */
	काष्ठा v4l2_framebuffer *frame;
	/* Y value of overlay background */
	अचिन्हित अक्षर bg_y;
	/* U value of overlay background */
	अक्षर bg_u;
	/* V value of overlay background */
	अक्षर bg_v;
	/* the blending percent of input data क्रम Y subpixels */
	अचिन्हित अक्षर blend_input_perc_y;
	/* the blending percent of input data क्रम U subpixels */
	अचिन्हित अक्षर blend_input_perc_u;
	/* the blending percent of input data क्रम V subpixels */
	अचिन्हित अक्षर blend_input_perc_v;
	/* the blending percent of overlay data क्रम Y subpixels */
	अचिन्हित अक्षर blend_overlay_perc_y;
	/* the blending percent of overlay data क्रम U subpixels */
	अचिन्हित अक्षर blend_overlay_perc_u;
	/* the blending percent of overlay data क्रम V subpixels */
	अचिन्हित अक्षर blend_overlay_perc_v;
	/* the overlay start x pixel position on output frame It should be the
	   multiples of 2*ISP_VEC_NELEMS. */
	अचिन्हित पूर्णांक overlay_start_x;
	/* the overlay start y pixel position on output frame It should be the
	   multiples of 2. */
	अचिन्हित पूर्णांक overlay_start_y;
पूर्ण;

/* Sensor resolution specअगरic data क्रम AE calculation.*/
काष्ठा atomisp_sensor_mode_data अणु
	अचिन्हित पूर्णांक coarse_पूर्णांकegration_समय_min;
	अचिन्हित पूर्णांक coarse_पूर्णांकegration_समय_max_margin;
	अचिन्हित पूर्णांक fine_पूर्णांकegration_समय_min;
	अचिन्हित पूर्णांक fine_पूर्णांकegration_समय_max_margin;
	अचिन्हित पूर्णांक fine_पूर्णांकegration_समय_def;
	अचिन्हित पूर्णांक frame_length_lines;
	अचिन्हित पूर्णांक line_length_pck;
	अचिन्हित पूर्णांक पढ़ो_mode;
	अचिन्हित पूर्णांक vt_pix_clk_freq_mhz;
	अचिन्हित पूर्णांक crop_horizontal_start; /* Sensor crop start cord. (x0,y0)*/
	अचिन्हित पूर्णांक crop_vertical_start;
	अचिन्हित पूर्णांक crop_horizontal_end; /* Sensor crop end cord. (x1,y1)*/
	अचिन्हित पूर्णांक crop_vertical_end;
	अचिन्हित पूर्णांक output_width; /* input size to ISP after binning/scaling */
	अचिन्हित पूर्णांक output_height;
	u8 binning_factor_x; /* horizontal binning factor used */
	u8 binning_factor_y; /* vertical binning factor used */
	u16 hts;
पूर्ण;

काष्ठा atomisp_exposure अणु
	अचिन्हित पूर्णांक पूर्णांकegration_समय[8];
	अचिन्हित पूर्णांक shutter_speed[8];
	अचिन्हित पूर्णांक gain[4];
	अचिन्हित पूर्णांक aperture;
पूर्ण;

/* For texture streaming. */
काष्ठा atomisp_bc_video_package अणु
	पूर्णांक ioctl_cmd;
	पूर्णांक device_id;
	पूर्णांक inputparam;
	पूर्णांक outputparam;
पूर्ण;

क्रमागत atomisp_focus_hp अणु
	ATOMISP_FOCUS_HP_IN_PROGRESS = (1U << 2),
	ATOMISP_FOCUS_HP_COMPLETE    = (2U << 2),
	ATOMISP_FOCUS_HP_FAILED      = (3U << 2)
पूर्ण;

/* Masks */
#घोषणा ATOMISP_FOCUS_STATUS_MOVING           BIT(0)
#घोषणा ATOMISP_FOCUS_STATUS_ACCEPTS_NEW_MOVE BIT(1)
#घोषणा ATOMISP_FOCUS_STATUS_HOME_POSITION    (3U << 2)

क्रमागत atomisp_camera_port अणु
	ATOMISP_CAMERA_PORT_SECONDARY,
	ATOMISP_CAMERA_PORT_PRIMARY,
	ATOMISP_CAMERA_PORT_TERTIARY,
	ATOMISP_CAMERA_NR_PORTS
पूर्ण;

/* Flash modes. Default is off.
 * Setting a flash to TORCH or INDICATOR mode will स्वतःmatically
 * turn it on. Setting it to FLASH mode will not turn on the flash
 * until the FLASH_STROBE command is sent. */
क्रमागत atomisp_flash_mode अणु
	ATOMISP_FLASH_MODE_OFF,
	ATOMISP_FLASH_MODE_FLASH,
	ATOMISP_FLASH_MODE_TORCH,
	ATOMISP_FLASH_MODE_INDICATOR,
पूर्ण;

/* Flash statuses, used by atomisp driver to check beक्रमe starting
 * flash and after having started flash. */
क्रमागत atomisp_flash_status अणु
	ATOMISP_FLASH_STATUS_OK,
	ATOMISP_FLASH_STATUS_HW_ERROR,
	ATOMISP_FLASH_STATUS_INTERRUPTED,
	ATOMISP_FLASH_STATUS_TIMEOUT,
पूर्ण;

/* Frame status. This is used to detect corrupted frames and flash
 * exposed frames. Usually, the first 2 frames coming out of the sensor
 * are corrupted. When using flash, the frame beक्रमe and the frame after
 * the flash exposed frame may be partially exposed by flash. The ISP
 * statistics क्रम these frames should not be used by the 3A library.
 * The frame status value can be found in the "reserved" field in the
 * v4l2_buffer काष्ठा. */
क्रमागत atomisp_frame_status अणु
	ATOMISP_FRAME_STATUS_OK,
	ATOMISP_FRAME_STATUS_CORRUPTED,
	ATOMISP_FRAME_STATUS_FLASH_EXPOSED,
	ATOMISP_FRAME_STATUS_FLASH_PARTIAL,
	ATOMISP_FRAME_STATUS_FLASH_FAILED,
पूर्ण;

क्रमागत atomisp_acc_type अणु
	ATOMISP_ACC_STANDALONE,	/* Stand-alone acceleration */
	ATOMISP_ACC_OUTPUT,	/* Accelerator stage on output frame */
	ATOMISP_ACC_VIEWFINDER	/* Accelerator stage on viewfinder frame */
पूर्ण;

क्रमागत atomisp_acc_arg_type अणु
	ATOMISP_ACC_ARG_SCALAR_IN,    /* Scalar input argument */
	ATOMISP_ACC_ARG_SCALAR_OUT,   /* Scalar output argument */
	ATOMISP_ACC_ARG_SCALAR_IO,    /* Scalar in/output argument */
	ATOMISP_ACC_ARG_PTR_IN,	     /* Poपूर्णांकer input argument */
	ATOMISP_ACC_ARG_PTR_OUT,	     /* Poपूर्णांकer output argument */
	ATOMISP_ACC_ARG_PTR_IO,	     /* Poपूर्णांकer in/output argument */
	ATOMISP_ARG_PTR_NOFLUSH,  /* Poपूर्णांकer argument will not be flushed */
	ATOMISP_ARG_PTR_STABLE,   /* Poपूर्णांकer input argument that is stable */
	ATOMISP_ACC_ARG_FRAME	     /* Frame argument */
पूर्ण;

/* ISP memories, isp2400 */
क्रमागत atomisp_acc_memory अणु
	ATOMISP_ACC_MEMORY_PMEM0 = 0,
	ATOMISP_ACC_MEMORY_DMEM0,
	/* क्रम backward compatibility */
	ATOMISP_ACC_MEMORY_DMEM = ATOMISP_ACC_MEMORY_DMEM0,
	ATOMISP_ACC_MEMORY_VMEM0,
	ATOMISP_ACC_MEMORY_VAMEM0,
	ATOMISP_ACC_MEMORY_VAMEM1,
	ATOMISP_ACC_MEMORY_VAMEM2,
	ATOMISP_ACC_MEMORY_HMEM0,
	ATOMISP_ACC_NR_MEMORY
पूर्ण;

क्रमागत atomisp_ext_isp_id अणु
	EXT_ISP_CID_ISO = 0,
	EXT_ISP_CID_CAPTURE_HDR,
	EXT_ISP_CID_CAPTURE_LLS,
	EXT_ISP_CID_FOCUS_MODE,
	EXT_ISP_CID_FOCUS_EXECUTION,
	EXT_ISP_CID_TOUCH_POSX,
	EXT_ISP_CID_TOUCH_POSY,
	EXT_ISP_CID_CAF_STATUS,
	EXT_ISP_CID_AF_STATUS,
	EXT_ISP_CID_GET_AF_MODE,
	EXT_ISP_CID_CAPTURE_BURST,
	EXT_ISP_CID_FLASH_MODE,
	EXT_ISP_CID_ZOOM,
	EXT_ISP_CID_SHOT_MODE
पूर्ण;

#घोषणा EXT_ISP_FOCUS_MODE_NORMAL	0
#घोषणा EXT_ISP_FOCUS_MODE_MACRO	1
#घोषणा EXT_ISP_FOCUS_MODE_TOUCH_AF	2
#घोषणा EXT_ISP_FOCUS_MODE_PREVIEW_CAF	3
#घोषणा EXT_ISP_FOCUS_MODE_MOVIE_CAF	4
#घोषणा EXT_ISP_FOCUS_MODE_FACE_CAF	5
#घोषणा EXT_ISP_FOCUS_MODE_TOUCH_MACRO	6
#घोषणा EXT_ISP_FOCUS_MODE_TOUCH_CAF	7

#घोषणा EXT_ISP_FOCUS_STOP		0
#घोषणा EXT_ISP_FOCUS_SEARCH		1
#घोषणा EXT_ISP_PAN_FOCUSING		2

#घोषणा EXT_ISP_CAF_RESTART_CHECK	1
#घोषणा EXT_ISP_CAF_STATUS_FOCUSING	2
#घोषणा EXT_ISP_CAF_STATUS_SUCCESS	3
#घोषणा EXT_ISP_CAF_STATUS_FAIL         4

#घोषणा EXT_ISP_AF_STATUS_INVALID	1
#घोषणा EXT_ISP_AF_STATUS_FOCUSING	2
#घोषणा EXT_ISP_AF_STATUS_SUCCESS	3
#घोषणा EXT_ISP_AF_STATUS_FAIL		4

क्रमागत atomisp_burst_capture_options अणु
	EXT_ISP_BURST_CAPTURE_CTRL_START = 0,
	EXT_ISP_BURST_CAPTURE_CTRL_STOP
पूर्ण;

#घोषणा EXT_ISP_FLASH_MODE_OFF		0
#घोषणा EXT_ISP_FLASH_MODE_ON		1
#घोषणा EXT_ISP_FLASH_MODE_AUTO		2
#घोषणा EXT_ISP_LED_TORCH_OFF		3
#घोषणा EXT_ISP_LED_TORCH_ON		4

#घोषणा EXT_ISP_SHOT_MODE_AUTO		0
#घोषणा EXT_ISP_SHOT_MODE_BEAUTY_FACE	1
#घोषणा EXT_ISP_SHOT_MODE_BEST_PHOTO	2
#घोषणा EXT_ISP_SHOT_MODE_DRAMA		3
#घोषणा EXT_ISP_SHOT_MODE_BEST_FACE	4
#घोषणा EXT_ISP_SHOT_MODE_ERASER	5
#घोषणा EXT_ISP_SHOT_MODE_PANORAMA	6
#घोषणा EXT_ISP_SHOT_MODE_RICH_TONE_HDR	7
#घोषणा EXT_ISP_SHOT_MODE_NIGHT		8
#घोषणा EXT_ISP_SHOT_MODE_SOUND_SHOT	9
#घोषणा EXT_ISP_SHOT_MODE_ANIMATED_PHOTO	10
#घोषणा EXT_ISP_SHOT_MODE_SPORTS	11

काष्ठा atomisp_sp_arg अणु
	क्रमागत atomisp_acc_arg_type type;	/* Type  of SP argument */
	व्योम                    *value;	/* Value of SP argument */
	अचिन्हित पूर्णांक             size;	/* Size  of SP argument */
पूर्ण;

/* Acceleration API */

/* For CSS 1.0 only */
काष्ठा atomisp_acc_fw_arg अणु
	अचिन्हित पूर्णांक fw_handle;
	अचिन्हित पूर्णांक index;
	व्योम __user *value;
	माप_प्रकार size;
पूर्ण;

/*
 * Set arguments after first mapping with ATOMISP_IOC_ACC_S_MAPPED_ARG.
 */
काष्ठा atomisp_acc_s_mapped_arg अणु
	अचिन्हित पूर्णांक fw_handle;
	__u32 memory;			/* one of क्रमागत atomisp_acc_memory */
	माप_प्रकार length;
	अचिन्हित दीर्घ css_ptr;
पूर्ण;

काष्ठा atomisp_acc_fw_पात अणु
	अचिन्हित पूर्णांक fw_handle;
	/* Timeout in us */
	अचिन्हित पूर्णांक समयout;
पूर्ण;

काष्ठा atomisp_acc_fw_load अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक fw_handle;
	व्योम __user *data;
पूर्ण;

/*
 * Load firmware to specअगरied pipeline.
 */
काष्ठा atomisp_acc_fw_load_to_pipe अणु
	__u32 flags;			/* Flags, see below क्रम valid values */
	अचिन्हित पूर्णांक fw_handle;		/* Handle, filled by kernel. */
	__u32 size;			/* Firmware binary size */
	व्योम __user *data;		/* Poपूर्णांकer to firmware */
	__u32 type;			/* Binary type */
	__u32 reserved[3];		/* Set to zero */
पूर्ण;

/*
 * Set Senor run mode
 */
काष्ठा atomisp_s_runmode अणु
	__u32 mode;
पूर्ण;

#घोषणा ATOMISP_ACC_FW_LOAD_FL_PREVIEW		BIT(0)
#घोषणा ATOMISP_ACC_FW_LOAD_FL_COPY		BIT(1)
#घोषणा ATOMISP_ACC_FW_LOAD_FL_VIDEO		BIT(2)
#घोषणा ATOMISP_ACC_FW_LOAD_FL_CAPTURE		BIT(3)
#घोषणा ATOMISP_ACC_FW_LOAD_FL_ACC		BIT(4)
#घोषणा ATOMISP_ACC_FW_LOAD_FL_ENABLE		BIT(16)

#घोषणा ATOMISP_ACC_FW_LOAD_TYPE_NONE		0 /* Normal binary: करोn't use */
#घोषणा ATOMISP_ACC_FW_LOAD_TYPE_OUTPUT		1 /* Stage on output */
#घोषणा ATOMISP_ACC_FW_LOAD_TYPE_VIEWFINDER	2 /* Stage on viewfinder */
#घोषणा ATOMISP_ACC_FW_LOAD_TYPE_STANDALONE	3 /* Stand-alone acceleration */

काष्ठा atomisp_acc_map अणु
	__u32 flags;			/* Flags, see list below */
	__u32 length;			/* Length of data in bytes */
	व्योम __user *user_ptr;		/* Poपूर्णांकer पूर्णांकo user space */
	अचिन्हित दीर्घ css_ptr;		/* Poपूर्णांकer पूर्णांकo CSS address space */
	__u32 reserved[4];		/* Set to zero */
पूर्ण;

#घोषणा ATOMISP_MAP_FLAG_NOFLUSH	0x0001	/* Do not flush cache */
#घोषणा ATOMISP_MAP_FLAG_CACHED		0x0002	/* Enable cache */
#घोषणा ATOMISP_MAP_FLAG_CONTIGUOUS	0x0004
#घोषणा ATOMISP_MAP_FLAG_CLEARED	0x0008

काष्ठा atomisp_acc_state अणु
	__u32 flags;			/* Flags, see list below */
#घोषणा ATOMISP_STATE_FLAG_ENABLE	ATOMISP_ACC_FW_LOAD_FL_ENABLE
	अचिन्हित पूर्णांक fw_handle;
पूर्ण;

काष्ठा atomisp_update_exposure अणु
	अचिन्हित पूर्णांक gain;
	अचिन्हित पूर्णांक digi_gain;
	अचिन्हित पूर्णांक update_gain;
	अचिन्हित पूर्णांक update_digi_gain;
पूर्ण;

/*
 * V4L2 निजी पूर्णांकernal data पूर्णांकerface.
 * -----------------------------------------------------------------------------
 * काष्ठा v4l2_निजी_पूर्णांक_data - request निजी data stored in video device
 * पूर्णांकernal memory.
 * @size: sanity check to ensure userspace's buffer fits whole निजी data.
 *	  If not, kernel will make partial copy (or nothing अगर @size == 0).
 *	  @size is always corrected क्रम the minimum necessary अगर IOCTL वापसs
 *	  no error.
 * @data: poपूर्णांकer to userspace buffer.
 */
काष्ठा v4l2_निजी_पूर्णांक_data अणु
	__u32 size;
	व्योम __user *data;
	__u32 reserved[2];
पूर्ण;

क्रमागत atomisp_sensor_ae_bracketing_mode अणु
	SENSOR_AE_BRACKETING_MODE_OFF = 0,
	SENSOR_AE_BRACKETING_MODE_SINGLE, /* back to SW standby after bracketing */
	SENSOR_AE_BRACKETING_MODE_SINGLE_TO_STREAMING, /* back to normal streaming after bracketing */
	SENSOR_AE_BRACKETING_MODE_LOOP, /* जारी AE bracketing in loop mode */
पूर्ण;

काष्ठा atomisp_sensor_ae_bracketing_info अणु
	अचिन्हित पूर्णांक modes; /* bit mask to indicate supported modes  */
	अचिन्हित पूर्णांक lut_depth;
पूर्ण;

काष्ठा atomisp_sensor_ae_bracketing_lut_entry अणु
	__u16 coarse_पूर्णांकegration_समय;
	__u16 analog_gain;
	__u16 digital_gain;
पूर्ण;

काष्ठा atomisp_sensor_ae_bracketing_lut अणु
	काष्ठा atomisp_sensor_ae_bracketing_lut_entry *lut;
	अचिन्हित पूर्णांक lut_size;
पूर्ण;

/*Private IOCTLs क्रम ISP */
#घोषणा ATOMISP_IOC_G_XNR \
	_IOR('v', BASE_VIDIOC_PRIVATE + 0, पूर्णांक)
#घोषणा ATOMISP_IOC_S_XNR \
	_IOW('v', BASE_VIDIOC_PRIVATE + 0, पूर्णांक)
#घोषणा ATOMISP_IOC_G_NR \
	_IOR('v', BASE_VIDIOC_PRIVATE + 1, काष्ठा atomisp_nr_config)
#घोषणा ATOMISP_IOC_S_NR \
	_IOW('v', BASE_VIDIOC_PRIVATE + 1, काष्ठा atomisp_nr_config)
#घोषणा ATOMISP_IOC_G_TNR \
	_IOR('v', BASE_VIDIOC_PRIVATE + 2, काष्ठा atomisp_tnr_config)
#घोषणा ATOMISP_IOC_S_TNR \
	_IOW('v', BASE_VIDIOC_PRIVATE + 2, काष्ठा atomisp_tnr_config)
#घोषणा ATOMISP_IOC_G_HISTOGRAM \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 3, काष्ठा atomisp_histogram)
#घोषणा ATOMISP_IOC_S_HISTOGRAM \
	_IOW('v', BASE_VIDIOC_PRIVATE + 3, काष्ठा atomisp_histogram)
#घोषणा ATOMISP_IOC_G_BLACK_LEVEL_COMP \
	_IOR('v', BASE_VIDIOC_PRIVATE + 4, काष्ठा atomisp_ob_config)
#घोषणा ATOMISP_IOC_S_BLACK_LEVEL_COMP \
	_IOW('v', BASE_VIDIOC_PRIVATE + 4, काष्ठा atomisp_ob_config)
#घोषणा ATOMISP_IOC_G_EE \
	_IOR('v', BASE_VIDIOC_PRIVATE + 5, काष्ठा atomisp_ee_config)
#घोषणा ATOMISP_IOC_S_EE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 5, काष्ठा atomisp_ee_config)
/* Digital Image Stabilization:
 * 1. get dis statistics: पढ़ोs DIS statistics from ISP (every frame)
 * 2. set dis coefficients: set DIS filter coefficients (one समय)
 * 3. set dis motion vecotr: set motion vector (result of DIS, every frame)
 */
#घोषणा ATOMISP_IOC_G_DIS_STAT \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 6, काष्ठा atomisp_dis_statistics)

#घोषणा ATOMISP_IOC_G_DVS2_BQ_RESOLUTIONS \
	_IOR('v', BASE_VIDIOC_PRIVATE + 6, काष्ठा atomisp_dvs2_bq_resolutions)

#घोषणा ATOMISP_IOC_S_DIS_COEFS \
	_IOW('v', BASE_VIDIOC_PRIVATE + 6, काष्ठा atomisp_dis_coefficients)

#घोषणा ATOMISP_IOC_S_DIS_VECTOR \
	_IOW('v', BASE_VIDIOC_PRIVATE + 6, काष्ठा atomisp_dvs_6axis_config)

#घोषणा ATOMISP_IOC_G_3A_STAT \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 7, काष्ठा atomisp_3a_statistics)
#घोषणा ATOMISP_IOC_G_ISP_PARM \
	_IOR('v', BASE_VIDIOC_PRIVATE + 8, काष्ठा atomisp_parm)
#घोषणा ATOMISP_IOC_S_ISP_PARM \
	_IOW('v', BASE_VIDIOC_PRIVATE + 8, काष्ठा atomisp_parm)
#घोषणा ATOMISP_IOC_G_ISP_GAMMA \
	_IOR('v', BASE_VIDIOC_PRIVATE + 9, काष्ठा atomisp_gamma_table)
#घोषणा ATOMISP_IOC_S_ISP_GAMMA \
	_IOW('v', BASE_VIDIOC_PRIVATE + 9, काष्ठा atomisp_gamma_table)
#घोषणा ATOMISP_IOC_G_ISP_GDC_TAB \
	_IOR('v', BASE_VIDIOC_PRIVATE + 10, काष्ठा atomisp_morph_table)
#घोषणा ATOMISP_IOC_S_ISP_GDC_TAB \
	_IOW('v', BASE_VIDIOC_PRIVATE + 10, काष्ठा atomisp_morph_table)
#घोषणा ATOMISP_IOC_ISP_MAKERNOTE \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 11, काष्ठा atomisp_makernote_info)

/* macc parameter control*/
#घोषणा ATOMISP_IOC_G_ISP_MACC \
	_IOR('v', BASE_VIDIOC_PRIVATE + 12, काष्ठा atomisp_macc_config)
#घोषणा ATOMISP_IOC_S_ISP_MACC \
	_IOW('v', BASE_VIDIOC_PRIVATE + 12, काष्ठा atomisp_macc_config)

/* Defect pixel detection & Correction */
#घोषणा ATOMISP_IOC_G_ISP_BAD_PIXEL_DETECTION \
	_IOR('v', BASE_VIDIOC_PRIVATE + 13, काष्ठा atomisp_dp_config)
#घोषणा ATOMISP_IOC_S_ISP_BAD_PIXEL_DETECTION \
	_IOW('v', BASE_VIDIOC_PRIVATE + 13, काष्ठा atomisp_dp_config)

/* False Color Correction */
#घोषणा ATOMISP_IOC_G_ISP_FALSE_COLOR_CORRECTION \
	_IOR('v', BASE_VIDIOC_PRIVATE + 14, काष्ठा atomisp_de_config)
#घोषणा ATOMISP_IOC_S_ISP_FALSE_COLOR_CORRECTION \
	_IOW('v', BASE_VIDIOC_PRIVATE + 14, काष्ठा atomisp_de_config)

/* ctc parameter control */
#घोषणा ATOMISP_IOC_G_ISP_CTC \
	_IOR('v', BASE_VIDIOC_PRIVATE + 15, काष्ठा atomisp_ctc_table)
#घोषणा ATOMISP_IOC_S_ISP_CTC \
	_IOW('v', BASE_VIDIOC_PRIVATE + 15, काष्ठा atomisp_ctc_table)

/* white balance Correction */
#घोषणा ATOMISP_IOC_G_ISP_WHITE_BALANCE \
	_IOR('v', BASE_VIDIOC_PRIVATE + 16, काष्ठा atomisp_wb_config)
#घोषणा ATOMISP_IOC_S_ISP_WHITE_BALANCE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 16, काष्ठा atomisp_wb_config)

/* fpn table loading */
#घोषणा ATOMISP_IOC_S_ISP_FPN_TABLE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 17, काष्ठा v4l2_framebuffer)

/* overlay image loading */
#घोषणा ATOMISP_IOC_G_ISP_OVERLAY \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 18, काष्ठा atomisp_overlay)
#घोषणा ATOMISP_IOC_S_ISP_OVERLAY \
	_IOW('v', BASE_VIDIOC_PRIVATE + 18, काष्ठा atomisp_overlay)

/* bcd driver bridge */
#घोषणा ATOMISP_IOC_CAMERA_BRIDGE \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 19, काष्ठा atomisp_bc_video_package)

/* Sensor resolution specअगरic info क्रम AE */
#घोषणा ATOMISP_IOC_G_SENSOR_MODE_DATA \
	_IOR('v', BASE_VIDIOC_PRIVATE + 20, काष्ठा atomisp_sensor_mode_data)

#घोषणा ATOMISP_IOC_S_EXPOSURE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 21, काष्ठा atomisp_exposure)

/* sensor calibration रेजिस्टरs group */
#घोषणा ATOMISP_IOC_G_SENSOR_CALIBRATION_GROUP \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 22, काष्ठा atomisp_calibration_group)

/* white balance Correction */
#घोषणा ATOMISP_IOC_G_3A_CONFIG \
	_IOR('v', BASE_VIDIOC_PRIVATE + 23, काष्ठा atomisp_3a_config)
#घोषणा ATOMISP_IOC_S_3A_CONFIG \
	_IOW('v', BASE_VIDIOC_PRIVATE + 23, काष्ठा atomisp_3a_config)

/* Accelerate ioctls */
#घोषणा ATOMISP_IOC_ACC_LOAD \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 24, काष्ठा atomisp_acc_fw_load)

#घोषणा ATOMISP_IOC_ACC_UNLOAD \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 24, अचिन्हित पूर्णांक)

/* For CSS 1.0 only */
#घोषणा ATOMISP_IOC_ACC_S_ARG \
	_IOW('v', BASE_VIDIOC_PRIVATE + 24, काष्ठा atomisp_acc_fw_arg)

#घोषणा ATOMISP_IOC_ACC_START \
	_IOW('v', BASE_VIDIOC_PRIVATE + 24, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_ACC_WAIT \
	_IOW('v', BASE_VIDIOC_PRIVATE + 25, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_ACC_ABORT \
	_IOW('v', BASE_VIDIOC_PRIVATE + 25, काष्ठा atomisp_acc_fw_पात)

#घोषणा ATOMISP_IOC_ACC_DESTAB \
	_IOW('v', BASE_VIDIOC_PRIVATE + 25, काष्ठा atomisp_acc_fw_arg)

/* sensor OTP memory पढ़ो */
#घोषणा ATOMISP_IOC_G_SENSOR_PRIV_INT_DATA \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 26, काष्ठा v4l2_निजी_पूर्णांक_data)

/* LCS (shading) table ग_लिखो */
#घोषणा ATOMISP_IOC_S_ISP_SHD_TAB \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 27, काष्ठा atomisp_shading_table)

/* Gamma Correction */
#घोषणा ATOMISP_IOC_G_ISP_GAMMA_CORRECTION \
	_IOR('v', BASE_VIDIOC_PRIVATE + 28, काष्ठा atomisp_gc_config)

#घोषणा ATOMISP_IOC_S_ISP_GAMMA_CORRECTION \
	_IOW('v', BASE_VIDIOC_PRIVATE + 28, काष्ठा atomisp_gc_config)

/* motor पूर्णांकernal memory पढ़ो */
#घोषणा ATOMISP_IOC_G_MOTOR_PRIV_INT_DATA \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 29, काष्ठा v4l2_निजी_पूर्णांक_data)

/*
 * Ioctls to map and unmap user buffers to CSS address space क्रम acceleration.
 * User fills fields length and user_ptr and sets other fields to zero,
 * kernel may modअगरy the flags and sets css_ptr.
 */
#घोषणा ATOMISP_IOC_ACC_MAP \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 30, काष्ठा atomisp_acc_map)

/* User fills fields length, user_ptr, and css_ptr and zeroes other fields. */
#घोषणा ATOMISP_IOC_ACC_UNMAP \
	_IOW('v', BASE_VIDIOC_PRIVATE + 30, काष्ठा atomisp_acc_map)

#घोषणा ATOMISP_IOC_ACC_S_MAPPED_ARG \
	_IOW('v', BASE_VIDIOC_PRIVATE + 30, काष्ठा atomisp_acc_s_mapped_arg)

#घोषणा ATOMISP_IOC_ACC_LOAD_TO_PIPE \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 31, काष्ठा atomisp_acc_fw_load_to_pipe)

#घोषणा ATOMISP_IOC_S_PARAMETERS \
	_IOW('v', BASE_VIDIOC_PRIVATE + 32, काष्ठा atomisp_parameters)

#घोषणा ATOMISP_IOC_S_CONT_CAPTURE_CONFIG \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 33, काष्ठा atomisp_cont_capture_conf)

#घोषणा ATOMISP_IOC_G_METADATA \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 34, काष्ठा atomisp_metadata)

#घोषणा ATOMISP_IOC_G_METADATA_BY_TYPE \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 34, काष्ठा atomisp_metadata_with_type)

#घोषणा ATOMISP_IOC_EXT_ISP_CTRL \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 35, काष्ठा atomisp_ext_isp_ctrl)

#घोषणा ATOMISP_IOC_EXP_ID_UNLOCK \
	_IOW('v', BASE_VIDIOC_PRIVATE + 36, पूर्णांक)

#घोषणा ATOMISP_IOC_EXP_ID_CAPTURE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 37, पूर्णांक)

#घोषणा ATOMISP_IOC_S_ENABLE_DZ_CAPT_PIPE \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 38, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_G_FORMATS_CONFIG \
	_IOR('v', BASE_VIDIOC_PRIVATE + 39, काष्ठा atomisp_क्रमmats_config)

#घोषणा ATOMISP_IOC_S_FORMATS_CONFIG \
	_IOW('v', BASE_VIDIOC_PRIVATE + 39, काष्ठा atomisp_क्रमmats_config)

#घोषणा ATOMISP_IOC_S_EXPOSURE_WINDOW \
	_IOW('v', BASE_VIDIOC_PRIVATE + 40, काष्ठा atomisp_ae_winकरोw)

#घोषणा ATOMISP_IOC_S_ACC_STATE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 41, काष्ठा atomisp_acc_state)

#घोषणा ATOMISP_IOC_G_ACC_STATE \
	_IOR('v', BASE_VIDIOC_PRIVATE + 41, काष्ठा atomisp_acc_state)

#घोषणा ATOMISP_IOC_INJECT_A_FAKE_EVENT \
	_IOW('v', BASE_VIDIOC_PRIVATE + 42, पूर्णांक)

#घोषणा ATOMISP_IOC_G_SENSOR_AE_BRACKETING_INFO \
	_IOR('v', BASE_VIDIOC_PRIVATE + 43, काष्ठा atomisp_sensor_ae_bracketing_info)

#घोषणा ATOMISP_IOC_S_SENSOR_AE_BRACKETING_MODE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 43, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_G_SENSOR_AE_BRACKETING_MODE \
	_IOR('v', BASE_VIDIOC_PRIVATE + 43, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_S_SENSOR_AE_BRACKETING_LUT \
	_IOW('v', BASE_VIDIOC_PRIVATE + 43, काष्ठा atomisp_sensor_ae_bracketing_lut)

#घोषणा ATOMISP_IOC_G_INVALID_FRAME_NUM \
	_IOR('v', BASE_VIDIOC_PRIVATE + 44, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_S_ARRAY_RESOLUTION \
	_IOW('v', BASE_VIDIOC_PRIVATE + 45, काष्ठा atomisp_resolution)

/* क्रम depth mode sensor frame sync compensation */
#घोषणा ATOMISP_IOC_G_DEPTH_SYNC_COMP \
	_IOR('v', BASE_VIDIOC_PRIVATE + 46, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_S_SENSOR_EE_CONFIG \
	_IOW('v', BASE_VIDIOC_PRIVATE + 47, अचिन्हित पूर्णांक)

#घोषणा ATOMISP_IOC_S_SENSOR_RUNMODE \
	_IOW('v', BASE_VIDIOC_PRIVATE + 48, काष्ठा atomisp_s_runmode)

#घोषणा ATOMISP_IOC_G_UPDATE_EXPOSURE \
	_IOWR('v', BASE_VIDIOC_PRIVATE + 49, काष्ठा atomisp_update_exposure)

/*
 * Reserved ioctls. We have customer implementing it पूर्णांकernally.
 * We can't use both numbers to not cause ABI conflict.
 * Anyway, those ioctls are hacks and not implemented by us:
 *
 * #घोषणा ATOMISP_IOC_G_SENSOR_REG \
 *	_IOW('v', BASE_VIDIOC_PRIVATE + 55, काष्ठा atomisp_sensor_regs)
 * #घोषणा ATOMISP_IOC_S_SENSOR_REG \
 *	_IOW('v', BASE_VIDIOC_PRIVATE + 56, काष्ठा atomisp_sensor_regs)
 */

/*  ISP Private control IDs */
#घोषणा V4L2_CID_ATOMISP_BAD_PIXEL_DETECTION \
	(V4L2_CID_PRIVATE_BASE + 0)
#घोषणा V4L2_CID_ATOMISP_POSTPROCESS_GDC_CAC \
	(V4L2_CID_PRIVATE_BASE + 1)
#घोषणा V4L2_CID_ATOMISP_VIDEO_STABLIZATION \
	(V4L2_CID_PRIVATE_BASE + 2)
#घोषणा V4L2_CID_ATOMISP_FIXED_PATTERN_NR \
	(V4L2_CID_PRIVATE_BASE + 3)
#घोषणा V4L2_CID_ATOMISP_FALSE_COLOR_CORRECTION \
	(V4L2_CID_PRIVATE_BASE + 4)
#घोषणा V4L2_CID_ATOMISP_LOW_LIGHT \
	(V4L2_CID_PRIVATE_BASE + 5)

/* Camera class:
 * Exposure, Flash and privacy (indicator) light controls, to be upstreamed */
#घोषणा V4L2_CID_CAMERA_LASTP1             (V4L2_CID_CAMERA_CLASS_BASE + 1024)

#घोषणा V4L2_CID_FOCAL_ABSOLUTE            (V4L2_CID_CAMERA_LASTP1 + 0)
#घोषणा V4L2_CID_FNUMBER_ABSOLUTE          (V4L2_CID_CAMERA_LASTP1 + 1)
#घोषणा V4L2_CID_FNUMBER_RANGE             (V4L2_CID_CAMERA_LASTP1 + 2)

/* Flash related CIDs, see also:
 * http://linuxtv.org/करोwnloads/v4l-dvb-apis/extended-controls.hपंचांगl\
 * #flash-controls */

/* Request a number of flash-exposed frames. The frame status can be
 * found in the reserved field in the v4l2_buffer काष्ठा. */
#घोषणा V4L2_CID_REQUEST_FLASH             (V4L2_CID_CAMERA_LASTP1 + 3)
/* Query flash driver status. See क्रमागत atomisp_flash_status above. */
#घोषणा V4L2_CID_FLASH_STATUS              (V4L2_CID_CAMERA_LASTP1 + 5)
/* Set the flash mode (see क्रमागत atomisp_flash_mode) */
#घोषणा V4L2_CID_FLASH_MODE                (V4L2_CID_CAMERA_LASTP1 + 10)

/* VCM slew control */
#घोषणा V4L2_CID_VCM_SLEW                  (V4L2_CID_CAMERA_LASTP1 + 11)
/* VCM step समय */
#घोषणा V4L2_CID_VCM_TIMING                (V4L2_CID_CAMERA_LASTP1 + 12)

/* Query Focus Status */
#घोषणा V4L2_CID_FOCUS_STATUS              (V4L2_CID_CAMERA_LASTP1 + 14)

/* Query sensor's binning factor */
#घोषणा V4L2_CID_BIN_FACTOR_HORZ	   (V4L2_CID_CAMERA_LASTP1 + 15)
#घोषणा V4L2_CID_BIN_FACTOR_VERT	   (V4L2_CID_CAMERA_LASTP1 + 16)

/* number of frames to skip at stream start */
#घोषणा V4L2_CID_G_SKIP_FRAMES		   (V4L2_CID_CAMERA_LASTP1 + 17)

/* Query sensor's 2A status */
#घोषणा V4L2_CID_2A_STATUS                 (V4L2_CID_CAMERA_LASTP1 + 18)
#घोषणा V4L2_2A_STATUS_AE_READY            BIT(0)
#घोषणा V4L2_2A_STATUS_AWB_READY           BIT(1)

#घोषणा V4L2_CID_FMT_AUTO			(V4L2_CID_CAMERA_LASTP1 + 19)

#घोषणा V4L2_CID_RUN_MODE			(V4L2_CID_CAMERA_LASTP1 + 20)
#घोषणा ATOMISP_RUN_MODE_VIDEO			1
#घोषणा ATOMISP_RUN_MODE_STILL_CAPTURE		2
#घोषणा ATOMISP_RUN_MODE_CONTINUOUS_CAPTURE	3
#घोषणा ATOMISP_RUN_MODE_PREVIEW		4
#घोषणा ATOMISP_RUN_MODE_SDV			5

#घोषणा V4L2_CID_ENABLE_VFPP			(V4L2_CID_CAMERA_LASTP1 + 21)
#घोषणा V4L2_CID_ATOMISP_CONTINUOUS_MODE	(V4L2_CID_CAMERA_LASTP1 + 22)
#घोषणा V4L2_CID_ATOMISP_CONTINUOUS_RAW_BUFFER_SIZE \
						(V4L2_CID_CAMERA_LASTP1 + 23)
#घोषणा V4L2_CID_ATOMISP_CONTINUOUS_VIEWFINDER \
						(V4L2_CID_CAMERA_LASTP1 + 24)

#घोषणा V4L2_CID_VFPP				(V4L2_CID_CAMERA_LASTP1 + 25)
#घोषणा ATOMISP_VFPP_ENABLE			0
#घोषणा ATOMISP_VFPP_DISABLE_SCALER		1
#घोषणा ATOMISP_VFPP_DISABLE_LOWLAT		2

/* Query real flash status रेजिस्टर value */
#घोषणा V4L2_CID_FLASH_STATUS_REGISTER  (V4L2_CID_CAMERA_LASTP1 + 26)

#घोषणा V4L2_CID_START_ZSL_CAPTURE	(V4L2_CID_CAMERA_LASTP1 + 28)
/* Lock and unlock raw buffer */
#घोषणा V4L2_CID_ENABLE_RAW_BUFFER_LOCK (V4L2_CID_CAMERA_LASTP1 + 29)

#घोषणा V4L2_CID_DEPTH_MODE		(V4L2_CID_CAMERA_LASTP1 + 30)

#घोषणा V4L2_CID_EXPOSURE_ZONE_NUM	(V4L2_CID_CAMERA_LASTP1 + 31)
/* Disable digital zoom */
#घोषणा V4L2_CID_DISABLE_DZ		(V4L2_CID_CAMERA_LASTP1 + 32)

#घोषणा V4L2_CID_TEST_PATTERN_COLOR_R	(V4L2_CID_CAMERA_LASTP1 + 33)
#घोषणा V4L2_CID_TEST_PATTERN_COLOR_GR	(V4L2_CID_CAMERA_LASTP1 + 34)
#घोषणा V4L2_CID_TEST_PATTERN_COLOR_GB	(V4L2_CID_CAMERA_LASTP1 + 35)
#घोषणा V4L2_CID_TEST_PATTERN_COLOR_B	(V4L2_CID_CAMERA_LASTP1 + 36)

#घोषणा V4L2_CID_ATOMISP_SELECT_ISP_VERSION	(V4L2_CID_CAMERA_LASTP1 + 38)

#घोषणा V4L2_BUF_FLAG_BUFFER_INVALID       0x0400
#घोषणा V4L2_BUF_FLAG_BUFFER_VALID         0x0800

#घोषणा V4L2_BUF_TYPE_VIDEO_CAPTURE_ION  (V4L2_BUF_TYPE_PRIVATE + 1024)

#घोषणा V4L2_EVENT_ATOMISP_3A_STATS_READY   (V4L2_EVENT_PRIVATE_START + 1)
#घोषणा V4L2_EVENT_ATOMISP_METADATA_READY   (V4L2_EVENT_PRIVATE_START + 2)
#घोषणा V4L2_EVENT_ATOMISP_RAW_BUFFERS_ALLOC_DONE   (V4L2_EVENT_PRIVATE_START + 3)
#घोषणा V4L2_EVENT_ATOMISP_ACC_COMPLETE     (V4L2_EVENT_PRIVATE_START + 4)
#घोषणा V4L2_EVENT_ATOMISP_PAUSE_BUFFER	    (V4L2_EVENT_PRIVATE_START + 5)
#घोषणा V4L2_EVENT_ATOMISP_CSS_RESET	    (V4L2_EVENT_PRIVATE_START + 6)
/* Nonstandard color effects क्रम V4L2_CID_COLORFX */
क्रमागत अणु
	V4L2_COLORFX_SKIN_WHITEN_LOW = 1001,
	V4L2_COLORFX_SKIN_WHITEN_HIGH = 1002,
	V4L2_COLORFX_WARM = 1003,
	V4L2_COLORFX_COLD = 1004,
	V4L2_COLORFX_WASHED = 1005,
	V4L2_COLORFX_RED = 1006,
	V4L2_COLORFX_GREEN = 1007,
	V4L2_COLORFX_BLUE = 1008,
	V4L2_COLORFX_PINK = 1009,
	V4L2_COLORFX_YELLOW = 1010,
	V4L2_COLORFX_PURPLE = 1011,
पूर्ण;

#पूर्ण_अगर /* _ATOM_ISP_H */
