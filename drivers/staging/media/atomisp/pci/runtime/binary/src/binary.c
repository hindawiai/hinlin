<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश <math_support.h>
#समावेश <gdc_device.h>	/* HR_GDC_N */

#समावेश "hmm.h"

#समावेश "isp.h"	/* ISP_VEC_NELEMS */

#समावेश "ia_css_binary.h"
#समावेश "ia_css_debug.h"
#समावेश "ia_css_util.h"
#समावेश "ia_css_isp_param.h"
#समावेश "sh_css_internal.h"
#समावेश "sh_css_sp.h"
#समावेश "sh_css_firmware.h"
#समावेश "sh_css_defs.h"
#समावेश "sh_css_legacy.h"

#समावेश "atomisp_internal.h"

#समावेश "vf/vf_1.0/ia_css_vf.host.h"
#समावेश "sc/sc_1.0/ia_css_sc.host.h"
#समावेश "sdis/sdis_1.0/ia_css_sdis.host.h"
#समावेश "fixedbds/fixedbds_1.0/ia_css_fixedbds_param.h"	/* FRAC_ACC */

#समावेश "camera/pipe/interface/ia_css_pipe_binarydesc.h"

#समावेश "assert_support.h"

#घोषणा IMPLIES(a, b)           (!(a) || (b))   /* A => B */

अटल काष्ठा ia_css_binary_xinfo *all_binaries; /* ISP binaries only (no SP) */
अटल काष्ठा ia_css_binary_xinfo
	*binary_infos[IA_CSS_BINARY_NUM_MODES] = अणु शून्य, पूर्ण;

अटल व्योम
ia_css_binary_dvs_env(स्थिर काष्ठा ia_css_binary_info *info,
		      स्थिर काष्ठा ia_css_resolution *dvs_env,
		      काष्ठा ia_css_resolution *binary_dvs_env)
अणु
	अगर (info->enable.dvs_envelope) अणु
		निश्चित(dvs_env);
		binary_dvs_env->width  = max(dvs_env->width, SH_CSS_MIN_DVS_ENVELOPE);
		binary_dvs_env->height = max(dvs_env->height, SH_CSS_MIN_DVS_ENVELOPE);
	पूर्ण
पूर्ण

अटल व्योम
ia_css_binary_पूर्णांकernal_res(स्थिर काष्ठा ia_css_frame_info *in_info,
			   स्थिर काष्ठा ia_css_frame_info *bds_out_info,
			   स्थिर काष्ठा ia_css_frame_info *out_info,
			   स्थिर काष्ठा ia_css_resolution *dvs_env,
			   स्थिर काष्ठा ia_css_binary_info *info,
			   काष्ठा ia_css_resolution *पूर्णांकernal_res)
अणु
	अचिन्हित पूर्णांक isp_पंचांगp_पूर्णांकernal_width = 0,
		     isp_पंचांगp_पूर्णांकernal_height = 0;
	bool binary_supports_yuv_ds = info->enable.ds & 2;
	काष्ठा ia_css_resolution binary_dvs_env;

	binary_dvs_env.width = 0;
	binary_dvs_env.height = 0;
	ia_css_binary_dvs_env(info, dvs_env, &binary_dvs_env);

	अगर (binary_supports_yuv_ds) अणु
		अगर (in_info) अणु
			isp_पंचांगp_पूर्णांकernal_width = in_info->res.width
						 + info->pipeline.left_cropping + binary_dvs_env.width;
			isp_पंचांगp_पूर्णांकernal_height = in_info->res.height
						  + info->pipeline.top_cropping + binary_dvs_env.height;
		पूर्ण
	पूर्ण अन्यथा अगर ((bds_out_info) && (out_info) &&
		   /* TODO: hack to make video_us हाल work. this should be reverted after
		   a nice solution in ISP */
		   (bds_out_info->res.width >= out_info->res.width)) अणु
		isp_पंचांगp_पूर्णांकernal_width = bds_out_info->padded_width;
		isp_पंचांगp_पूर्णांकernal_height = bds_out_info->res.height;
	पूर्ण अन्यथा अणु
		अगर (out_info) अणु
			isp_पंचांगp_पूर्णांकernal_width = out_info->padded_width;
			isp_पंचांगp_पूर्णांकernal_height = out_info->res.height;
		पूर्ण
	पूर्ण

	/* We first calculate the resolutions used by the ISP. After that,
	 * we use those resolutions to compute sizes क्रम tables etc. */
	पूर्णांकernal_res->width = __ISP_INTERNAL_WIDTH(isp_पंचांगp_पूर्णांकernal_width,
			      (पूर्णांक)binary_dvs_env.width,
			      info->pipeline.left_cropping, info->pipeline.mode,
			      info->pipeline.c_subsampling,
			      info->output.num_chunks, info->pipeline.pipelining);
	पूर्णांकernal_res->height = __ISP_INTERNAL_HEIGHT(isp_पंचांगp_पूर्णांकernal_height,
			       info->pipeline.top_cropping,
			       binary_dvs_env.height);
पूर्ण

/* ISP2400 */
/* Computation results of the origin coordinate of bayer on the shading table. */
काष्ठा sh_css_shading_table_bayer_origin_compute_results अणु
	u32 bayer_scale_hor_ratio_in;	/* Horizontal ratio (in) of bayer scaling. */
	u32 bayer_scale_hor_ratio_out;	/* Horizontal ratio (out) of bayer scaling. */
	u32 bayer_scale_ver_ratio_in;	/* Vertical ratio (in) of bayer scaling. */
	u32 bayer_scale_ver_ratio_out;	/* Vertical ratio (out) of bayer scaling. */
	u32 sc_bayer_origin_x_bqs_on_shading_table; /* X coordinate (in bqs) of bayer origin on shading table. */
	u32 sc_bayer_origin_y_bqs_on_shading_table; /* Y coordinate (in bqs) of bayer origin on shading table. */
पूर्ण;

/* ISP2401 */
/* Requirements क्रम the shading correction. */
काष्ठा sh_css_binary_sc_requirements अणु
	/* Bayer scaling factor, क्रम the scaling which is applied beक्रमe shading correction. */
	u32 bayer_scale_hor_ratio_in;  /* Horizontal ratio (in) of scaling applied BEFORE shading correction. */
	u32 bayer_scale_hor_ratio_out; /* Horizontal ratio (out) of scaling applied BEFORE shading correction. */
	u32 bayer_scale_ver_ratio_in;  /* Vertical ratio (in) of scaling applied BEFORE shading correction. */
	u32 bayer_scale_ver_ratio_out; /* Vertical ratio (out) of scaling applied BEFORE shading correction. */

	/* ISP पूर्णांकernal frame is composed of the real sensor data and the padding data. */
	u32 sensor_data_origin_x_bqs_on_पूर्णांकernal; /* X origin (in bqs) of sensor data on पूर्णांकernal frame
								at shading correction. */
	u32 sensor_data_origin_y_bqs_on_पूर्णांकernal; /* Y origin (in bqs) of sensor data on पूर्णांकernal frame
								at shading correction. */
पूर्ण;

/* ISP2400: Get the requirements क्रम the shading correction. */
अटल पूर्णांक
ia_css_binary_compute_shading_table_bayer_origin(
    स्थिर काष्ठा ia_css_binary *binary,				/* [in] */
    अचिन्हित पूर्णांक required_bds_factor,				/* [in] */
    स्थिर काष्ठा ia_css_stream_config *stream_config,		/* [in] */
    काष्ठा sh_css_shading_table_bayer_origin_compute_results *res)	/* [out] */
अणु
	पूर्णांक err;

	/* Numerator and denominator of the fixed bayer करोwnscaling factor.
	(numerator >= denominator) */
	अचिन्हित पूर्णांक bds_num, bds_den;

	/* Horizontal/Vertical ratio of bayer scaling
	between input area and output area. */
	अचिन्हित पूर्णांक bs_hor_ratio_in;
	अचिन्हित पूर्णांक bs_hor_ratio_out;
	अचिन्हित पूर्णांक bs_ver_ratio_in;
	अचिन्हित पूर्णांक bs_ver_ratio_out;

	/* Left padding set by InputFormatter. */
	अचिन्हित पूर्णांक left_padding_bqs;			/* in bqs */

	/* Flag क्रम the NEED_BDS_FACTOR_2_00 macro defined in isp kernels. */
	अचिन्हित पूर्णांक need_bds_factor_2_00;

	/* Left padding adjusted inside the isp. */
	अचिन्हित पूर्णांक left_padding_adjusted_bqs;		/* in bqs */

	/* Bad pixels caused by filters.
	NxN-filter (beक्रमe/after bayer scaling) moves the image position
	to right/bottom directions by a few pixels.
	It causes bad pixels at left/top sides,
	and effective bayer size decreases. */
	अचिन्हित पूर्णांक bad_bqs_on_left_beक्रमe_bs;	/* in bqs */
	अचिन्हित पूर्णांक bad_bqs_on_left_after_bs;	/* in bqs */
	अचिन्हित पूर्णांक bad_bqs_on_top_beक्रमe_bs;	/* in bqs */
	अचिन्हित पूर्णांक bad_bqs_on_top_after_bs;	/* in bqs */

	/* Get the numerator and denominator of bayer करोwnscaling factor. */
	err = sh_css_bds_factor_get_numerator_denominator
	(required_bds_factor, &bds_num, &bds_den);
	अगर (err)
		वापस err;

	/* Set the horizontal/vertical ratio of bayer scaling
	between input area and output area. */
	bs_hor_ratio_in  = bds_num;
	bs_hor_ratio_out = bds_den;
	bs_ver_ratio_in  = bds_num;
	bs_ver_ratio_out = bds_den;

	/* Set the left padding set by InputFormatter. (अगरmtr.c) */
	अगर (stream_config->left_padding == -1)
		left_padding_bqs = _ISP_BQS(binary->left_padding);
	अन्यथा
		left_padding_bqs = (अचिन्हित पूर्णांक)((पूर्णांक)ISP_VEC_NELEMS
				   - _ISP_BQS(stream_config->left_padding));

	/* Set the left padding adjusted inside the isp.
	When bds_factor 2.00 is needed, some padding is added to left_padding
	inside the isp, beक्रमe bayer करोwnscaling. (raw.isp.c)
	(Hopefully, left_crop/left_padding/top_crop should be defined in css
	appropriately, depending on bds_factor.)
	*/
	need_bds_factor_2_00 = ((binary->info->sp.bds.supported_bds_factors &
				(PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_2_00) |
				 PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_2_50) |
				 PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_3_00) |
				 PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_4_00) |
				 PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_4_50) |
				 PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_5_00) |
				 PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_6_00) |
				 PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_8_00))) != 0);

	अगर (need_bds_factor_2_00 && binary->info->sp.pipeline.left_cropping > 0)
		left_padding_adjusted_bqs = left_padding_bqs + ISP_VEC_NELEMS;
	अन्यथा
		left_padding_adjusted_bqs = left_padding_bqs;

	/* Currently, the bad pixel caused by filters beक्रमe bayer scaling
	is NOT considered, because the bad pixel is subtle.
	When some large filter is used in the future,
	we need to consider the bad pixel.

	Currently, when bds_factor isn't 1.00, 3x3 anti-alias filter is applied
	to each color plane(Gr/R/B/Gb) beक्रमe bayer करोwnscaling.
	This filter moves each color plane to right/bottom directions
	by 1 pixel at the most, depending on करोwnscaling factor.
	*/
	bad_bqs_on_left_beक्रमe_bs = 0;
	bad_bqs_on_top_beक्रमe_bs = 0;

	/* Currently, the bad pixel caused by filters after bayer scaling
	is NOT considered, because the bad pixel is subtle.
	When some large filter is used in the future,
	we need to consider the bad pixel.

	Currently, when DPC&BNR is processed between bayer scaling and
	shading correction, DPC&BNR moves each color plane to
	right/bottom directions by 1 pixel.
	*/
	bad_bqs_on_left_after_bs = 0;
	bad_bqs_on_top_after_bs = 0;

	/* Calculate the origin of bayer (real sensor data area)
	located on the shading table during the shading correction. */
	res->sc_bayer_origin_x_bqs_on_shading_table =
		((left_padding_adjusted_bqs + bad_bqs_on_left_beक्रमe_bs)
		* bs_hor_ratio_out + bs_hor_ratio_in / 2) / bs_hor_ratio_in
		+ bad_bqs_on_left_after_bs;
	/* "+ bs_hor_ratio_in/2": rounding क्रम भागision by bs_hor_ratio_in */
	res->sc_bayer_origin_y_bqs_on_shading_table =
		(bad_bqs_on_top_beक्रमe_bs * bs_ver_ratio_out + bs_ver_ratio_in / 2) / bs_ver_ratio_in
		+ bad_bqs_on_top_after_bs;
	/* "+ bs_ver_ratio_in/2": rounding क्रम भागision by bs_ver_ratio_in */

	res->bayer_scale_hor_ratio_in  = (uपूर्णांक32_t)bs_hor_ratio_in;
	res->bayer_scale_hor_ratio_out = (uपूर्णांक32_t)bs_hor_ratio_out;
	res->bayer_scale_ver_ratio_in  = (uपूर्णांक32_t)bs_ver_ratio_in;
	res->bayer_scale_ver_ratio_out = (uपूर्णांक32_t)bs_ver_ratio_out;

	वापस err;
पूर्ण

/* ISP2401: Get the requirements क्रम the shading correction. */
अटल पूर्णांक
sh_css_binary_get_sc_requirements(स्थिर काष्ठा ia_css_binary *binary, /* [in] */
				  अचिन्हित पूर्णांक required_bds_factor,   /* [in] */
				  स्थिर काष्ठा ia_css_stream_config *stream_config, /* [in] */
				  काष्ठा sh_css_binary_sc_requirements *scr) /* [out] */
अणु
	पूर्णांक err;

	/* Numerator and denominator of the fixed bayer करोwnscaling factor. (numerator >= denominator) */
	अचिन्हित पूर्णांक bds_num, bds_den;

	/* Horizontal/Vertical ratio of bayer scaling between input area and output area. */
	अचिन्हित पूर्णांक bs_hor_ratio_in, bs_hor_ratio_out, bs_ver_ratio_in, bs_ver_ratio_out;

	/* Left padding set by InputFormatter. */
	अचिन्हित पूर्णांक left_padding_bqs;

	/* Flags corresponding to NEED_BDS_FACTOR_2_00/NEED_BDS_FACTOR_1_50/NEED_BDS_FACTOR_1_25 macros
	 * defined in isp kernels. */
	अचिन्हित पूर्णांक need_bds_factor_2_00, need_bds_factor_1_50, need_bds_factor_1_25;

	/* Left padding adjusted inside the isp kernels. */
	अचिन्हित पूर्णांक left_padding_adjusted_bqs;

	/* Top padding padded inside the isp kernel क्रम bayer करोwnscaling binaries. */
	अचिन्हित पूर्णांक top_padding_bqs;

	/* Bayer करोwnscaling factor 1.0 by fixed-poपूर्णांक. */
	पूर्णांक bds_frac_acc = FRAC_ACC;	/* FRAC_ACC is defined in ia_css_fixedbds_param.h. */

	/* Right/Down shअगरt amount caused by filters applied BEFORE shading corrertion. */
	अचिन्हित पूर्णांक right_shअगरt_bqs_beक्रमe_bs; /* right shअगरt beक्रमe bayer scaling */
	अचिन्हित पूर्णांक right_shअगरt_bqs_after_bs;  /* right shअगरt after bayer scaling */
	अचिन्हित पूर्णांक करोwn_shअगरt_bqs_beक्रमe_bs;  /* करोwn shअगरt beक्रमe bayer scaling */
	अचिन्हित पूर्णांक करोwn_shअगरt_bqs_after_bs;   /* करोwn shअगरt after bayer scaling */

	/* Origin of the real sensor data area on the पूर्णांकernal frame at shading correction. */
	अचिन्हित पूर्णांक sensor_data_origin_x_bqs_on_पूर्णांकernal;
	अचिन्हित पूर्णांक sensor_data_origin_y_bqs_on_पूर्णांकernal;

	अचिन्हित पूर्णांक bs_frac = bds_frac_acc;	/* scaling factor 1.0 in fixed poपूर्णांक */
	अचिन्हित पूर्णांक bs_out, bs_in;		/* scaling ratio in fixed poपूर्णांक */

	IA_CSS_ENTER_PRIVATE("binary=%p, required_bds_factor=%d, stream_config=%p",
			     binary, required_bds_factor, stream_config);

	/* Get the numerator and denominator of the required bayer करोwnscaling factor. */
	err = sh_css_bds_factor_get_numerator_denominator(required_bds_factor,
							  &bds_num, &bds_den);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	IA_CSS_LOG("bds_num=%d, bds_den=%d", bds_num, bds_den);

	/* Set the horizontal/vertical ratio of bayer scaling between input area and output area. */
	bs_hor_ratio_in  = bds_num;
	bs_hor_ratio_out = bds_den;
	bs_ver_ratio_in  = bds_num;
	bs_ver_ratio_out = bds_den;

	/* Set the left padding set by InputFormatter. (ia_css_अगरmtr_configure() in अगरmtr.c) */
	अगर (stream_config->left_padding == -1)
		left_padding_bqs = _ISP_BQS(binary->left_padding);
	अन्यथा
		left_padding_bqs = (अचिन्हित पूर्णांक)((पूर्णांक)ISP_VEC_NELEMS - _ISP_BQS(stream_config->left_padding));

	IA_CSS_LOG("stream.left_padding=%d, binary.left_padding=%d, left_padding_bqs=%d",
		   stream_config->left_padding, binary->left_padding,
		   left_padding_bqs);

	/* Set the left padding adjusted inside the isp kernels.
	* When the bds_factor isn't 1.00, the left padding size is adjusted inside the isp,
	* beक्रमe bayer करोwnscaling. (scaled_hor_plane_index(), raw_compute_hphase() in raw.isp.c)
	*/
	need_bds_factor_2_00 = ((binary->info->sp.bds.supported_bds_factors &
				(PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_2_00) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_2_50) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_3_00) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_4_00) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_4_50) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_5_00) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_6_00) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_8_00))) != 0);

	need_bds_factor_1_50 = ((binary->info->sp.bds.supported_bds_factors &
				(PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_1_50) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_2_25) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_3_00) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_4_50) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_6_00))) != 0);

	need_bds_factor_1_25 = ((binary->info->sp.bds.supported_bds_factors &
				(PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_1_25) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_2_50) |
				PACK_BDS_FACTOR(SH_CSS_BDS_FACTOR_5_00))) != 0);

	अगर (binary->info->sp.pipeline.left_cropping > 0 &&
	    (need_bds_factor_2_00 || need_bds_factor_1_50 || need_bds_factor_1_25)) अणु
		/*
		* करोwnscale 2.0  -> first_vec_adjusted_bqs = 128
		* करोwnscale 1.5  -> first_vec_adjusted_bqs = 96
		* करोwnscale 1.25 -> first_vec_adjusted_bqs = 80
		*/
		अचिन्हित पूर्णांक first_vec_adjusted_bqs = ISP_VEC_NELEMS * bs_hor_ratio_in / bs_hor_ratio_out;
		left_padding_adjusted_bqs = first_vec_adjusted_bqs
			    - _ISP_BQS(binary->info->sp.pipeline.left_cropping);
	पूर्ण अन्यथा अणु
		left_padding_adjusted_bqs = left_padding_bqs;
	पूर्ण

	IA_CSS_LOG("supported_bds_factors=%d, need_bds_factor:2_00=%d, 1_50=%d, 1_25=%d",
		   binary->info->sp.bds.supported_bds_factors,
		   need_bds_factor_2_00, need_bds_factor_1_50,
		   need_bds_factor_1_25);
	IA_CSS_LOG("left_cropping=%d, left_padding_adjusted_bqs=%d",
		   binary->info->sp.pipeline.left_cropping,
		   left_padding_adjusted_bqs);

	/* Set the top padding padded inside the isp kernel क्रम bayer करोwnscaling binaries.
	* When the bds_factor isn't 1.00, the top padding is padded inside the isp
	* beक्रमe bayer करोwnscaling, because the top cropping size (input margin) is not enough.
	* (calculate_input_line(), raw_compute_vphase(), dma_पढ़ो_raw() in raw.isp.c)
	* NOTE: In dma_पढ़ो_raw(), the factor passed to raw_compute_vphase() is got by get_bds_factor_क्रम_dma_पढ़ो().
	*       This factor is BDS_FPVAL_100/BDS_FPVAL_125/BDS_FPVAL_150/BDS_FPVAL_200.
	*/
	top_padding_bqs = 0;
	अगर (binary->info->sp.pipeline.top_cropping > 0 &&
	    (required_bds_factor == SH_CSS_BDS_FACTOR_1_25 ||
	    required_bds_factor == SH_CSS_BDS_FACTOR_1_50 ||
	    required_bds_factor == SH_CSS_BDS_FACTOR_2_00)) अणु
		/* Calculation from calculate_input_line() and raw_compute_vphase() in raw.isp.c. */
		पूर्णांक top_cropping_bqs = _ISP_BQS(binary->info->sp.pipeline.top_cropping);
		/* top cropping (in bqs) */
		पूर्णांक factor = bds_num * bds_frac_acc /
		bds_den;	/* करोwnscaling factor by fixed-poपूर्णांक */
		पूर्णांक top_padding_bqsxfrac_acc = (top_cropping_bqs * factor - top_cropping_bqs *
						bds_frac_acc)
		+ (2 * bds_frac_acc - factor);	/* top padding by fixed-poपूर्णांक (in bqs) */

		top_padding_bqs = (अचिन्हित पूर्णांक)((top_padding_bqsxfrac_acc + bds_frac_acc / 2 -
						1) / bds_frac_acc);
	पूर्ण

	IA_CSS_LOG("top_cropping=%d, top_padding_bqs=%d",
		   binary->info->sp.pipeline.top_cropping, top_padding_bqs);

	/* Set the right/करोwn shअगरt amount caused by filters applied BEFORE bayer scaling,
	* which scaling is applied BEFORE shading corrertion.
	*
	* When the bds_factor isn't 1.00, 3x3 anti-alias filter is applied to each color plane(Gr/R/B/Gb)
	* beक्रमe bayer करोwnscaling.
	* This filter shअगरts each color plane (Gr/R/B/Gb) to right/करोwn directions by 1 pixel.
	*/
	right_shअगरt_bqs_beक्रमe_bs = 0;
	करोwn_shअगरt_bqs_beक्रमe_bs = 0;

	अगर (need_bds_factor_2_00 || need_bds_factor_1_50 || need_bds_factor_1_25) अणु
		right_shअगरt_bqs_beक्रमe_bs = 1;
		करोwn_shअगरt_bqs_beक्रमe_bs = 1;
	पूर्ण

	IA_CSS_LOG("right_shift_bqs_before_bs=%d, down_shift_bqs_before_bs=%d",
		   right_shअगरt_bqs_beक्रमe_bs, करोwn_shअगरt_bqs_beक्रमe_bs);

	/* Set the right/करोwn shअगरt amount caused by filters applied AFTER bayer scaling,
	* which scaling is applied BEFORE shading corrertion.
	*
	* When DPC&BNR is processed between bayer scaling and shading correction,
	* DPC&BNR moves each color plane (Gr/R/B/Gb) to right/करोwn directions by 1 pixel.
	*/
	right_shअगरt_bqs_after_bs = 0;
	करोwn_shअगरt_bqs_after_bs = 0;

	/* अगर DPC&BNR is enabled in the binary */
	अगर (binary->info->mem_offsets.offsets.param->dmem.dp.size != 0) अणु
		right_shअगरt_bqs_after_bs = 1;
		करोwn_shअगरt_bqs_after_bs = 1;
	पूर्ण

	IA_CSS_LOG("right_shift_bqs_after_bs=%d, down_shift_bqs_after_bs=%d",
		   right_shअगरt_bqs_after_bs, करोwn_shअगरt_bqs_after_bs);

	bs_out = bs_hor_ratio_out * bs_frac;
	bs_in = bs_hor_ratio_in * bs_frac;
	sensor_data_origin_x_bqs_on_पूर्णांकernal =
		((left_padding_adjusted_bqs + right_shअगरt_bqs_beक्रमe_bs) * bs_out + bs_in / 2) / bs_in
		+ right_shअगरt_bqs_after_bs;	/* "+ bs_in/2": rounding */

	bs_out = bs_ver_ratio_out * bs_frac;
	bs_in = bs_ver_ratio_in * bs_frac;
	sensor_data_origin_y_bqs_on_पूर्णांकernal =
		((top_padding_bqs + करोwn_shअगरt_bqs_beक्रमe_bs) * bs_out + bs_in / 2) / bs_in
		+ करोwn_shअगरt_bqs_after_bs;	/* "+ bs_in/2": rounding */

	scr->bayer_scale_hor_ratio_in			= (uपूर्णांक32_t)bs_hor_ratio_in;
	scr->bayer_scale_hor_ratio_out			= (uपूर्णांक32_t)bs_hor_ratio_out;
	scr->bayer_scale_ver_ratio_in			= (uपूर्णांक32_t)bs_ver_ratio_in;
	scr->bayer_scale_ver_ratio_out			= (uपूर्णांक32_t)bs_ver_ratio_out;
	scr->sensor_data_origin_x_bqs_on_पूर्णांकernal	= (uपूर्णांक32_t)sensor_data_origin_x_bqs_on_पूर्णांकernal;
	scr->sensor_data_origin_y_bqs_on_पूर्णांकernal	= (uपूर्णांक32_t)sensor_data_origin_y_bqs_on_पूर्णांकernal;

	IA_CSS_LOG("sc_requirements: %d, %d, %d, %d, %d, %d",
		   scr->bayer_scale_hor_ratio_in,
		   scr->bayer_scale_hor_ratio_out,
		   scr->bayer_scale_ver_ratio_in, scr->bayer_scale_ver_ratio_out,
		   scr->sensor_data_origin_x_bqs_on_पूर्णांकernal,
		   scr->sensor_data_origin_y_bqs_on_पूर्णांकernal);

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

/* Get the shading inक्रमmation of Shading Correction Type 1. */
अटल पूर्णांक
isp2400_binary_get_shading_info_type_1(स्थिर काष्ठा ia_css_binary *binary,	/* [in] */
				       अचिन्हित पूर्णांक required_bds_factor,			/* [in] */
				       स्थिर काष्ठा ia_css_stream_config *stream_config,	/* [in] */
				       काष्ठा ia_css_shading_info *info)			/* [out] */
अणु
	पूर्णांक err;
	काष्ठा sh_css_shading_table_bayer_origin_compute_results res;

	निश्चित(binary);
	निश्चित(info);

	info->type = IA_CSS_SHADING_CORRECTION_TYPE_1;

	info->info.type_1.enable	    = binary->info->sp.enable.sc;
	info->info.type_1.num_hor_grids	    = binary->sctbl_width_per_color;
	info->info.type_1.num_ver_grids	    = binary->sctbl_height;
	info->info.type_1.bqs_per_grid_cell = (1 << binary->deci_factor_log2);

	/* Initialize by शेष values. */
	info->info.type_1.bayer_scale_hor_ratio_in	= 1;
	info->info.type_1.bayer_scale_hor_ratio_out	= 1;
	info->info.type_1.bayer_scale_ver_ratio_in	= 1;
	info->info.type_1.bayer_scale_ver_ratio_out	= 1;
	info->info.type_1.sc_bayer_origin_x_bqs_on_shading_table = 0;
	info->info.type_1.sc_bayer_origin_y_bqs_on_shading_table = 0;

	err = ia_css_binary_compute_shading_table_bayer_origin(
	    binary,
	    required_bds_factor,
	    stream_config,
	    &res);
	अगर (err)
		वापस err;

	info->info.type_1.bayer_scale_hor_ratio_in	= res.bayer_scale_hor_ratio_in;
	info->info.type_1.bayer_scale_hor_ratio_out	= res.bayer_scale_hor_ratio_out;
	info->info.type_1.bayer_scale_ver_ratio_in	= res.bayer_scale_ver_ratio_in;
	info->info.type_1.bayer_scale_ver_ratio_out	= res.bayer_scale_ver_ratio_out;
	info->info.type_1.sc_bayer_origin_x_bqs_on_shading_table = res.sc_bayer_origin_x_bqs_on_shading_table;
	info->info.type_1.sc_bayer_origin_y_bqs_on_shading_table = res.sc_bayer_origin_y_bqs_on_shading_table;

	वापस err;
पूर्ण

/* Get the shading inक्रमmation of Shading Correction Type 1. */
अटल पूर्णांक
isp2401_binary_get_shading_info_type_1(स्थिर काष्ठा ia_css_binary *binary,	/* [in] */
				       अचिन्हित पूर्णांक required_bds_factor,			/* [in] */
				       स्थिर काष्ठा ia_css_stream_config *stream_config,	/* [in] */
				       काष्ठा ia_css_shading_info *shading_info,		/* [out] */
				       काष्ठा ia_css_pipe_config *pipe_config)			/* [out] */
अणु
	पूर्णांक err;
	काष्ठा sh_css_binary_sc_requirements scr;

	u32 in_width_bqs, in_height_bqs, पूर्णांकernal_width_bqs, पूर्णांकernal_height_bqs;
	u32 num_hor_grids, num_ver_grids, bqs_per_grid_cell, tbl_width_bqs, tbl_height_bqs;
	u32 sensor_org_x_bqs_on_पूर्णांकernal, sensor_org_y_bqs_on_पूर्णांकernal, sensor_width_bqs, sensor_height_bqs;
	u32 sensor_center_x_bqs_on_पूर्णांकernal, sensor_center_y_bqs_on_पूर्णांकernal;
	u32 left, right, upper, lower;
	u32 adjust_left, adjust_right, adjust_upper, adjust_lower, adjust_width_bqs, adjust_height_bqs;
	u32 पूर्णांकernal_org_x_bqs_on_tbl, पूर्णांकernal_org_y_bqs_on_tbl;
	u32 sensor_org_x_bqs_on_tbl, sensor_org_y_bqs_on_tbl;

	निश्चित(binary);
	निश्चित(stream_config);
	निश्चित(shading_info);
	निश्चित(pipe_config);

	IA_CSS_ENTER_PRIVATE("binary=%p, required_bds_factor=%d, stream_config=%p",
			     binary, required_bds_factor, stream_config);

	/* Initialize by शेष values. */
	*shading_info = DEFAULT_SHADING_INFO_TYPE_1;

	err = sh_css_binary_get_sc_requirements(binary, required_bds_factor, stream_config, &scr);
	अगर (err) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	IA_CSS_LOG("binary: id=%d, sctbl=%dx%d, deci=%d",
		binary->info->sp.id, binary->sctbl_width_per_color, binary->sctbl_height, binary->deci_factor_log2);
	IA_CSS_LOG("binary: in=%dx%d, in_padded_w=%d, int=%dx%d, int_padded_w=%d, out=%dx%d, out_padded_w=%d",
		binary->in_frame_info.res.width, binary->in_frame_info.res.height, binary->in_frame_info.padded_width,
		binary->पूर्णांकernal_frame_info.res.width, binary->पूर्णांकernal_frame_info.res.height,
		binary->पूर्णांकernal_frame_info.padded_width,
		binary->out_frame_info[0].res.width, binary->out_frame_info[0].res.height,
		binary->out_frame_info[0].padded_width);

	/* Set the input size from sensor, which includes left/top crop size. */
	in_width_bqs	    = _ISP_BQS(binary->in_frame_info.res.width);
	in_height_bqs	    = _ISP_BQS(binary->in_frame_info.res.height);

	/*
	 * Frame size पूर्णांकernally used in ISP, including sensor data and padding.
	 * This is the frame size, to which the shading correction is applied.
	 */
	पूर्णांकernal_width_bqs  = _ISP_BQS(binary->पूर्णांकernal_frame_info.res.width);
	पूर्णांकernal_height_bqs = _ISP_BQS(binary->पूर्णांकernal_frame_info.res.height);

	/* Shading table. */
	num_hor_grids = binary->sctbl_width_per_color;
	num_ver_grids = binary->sctbl_height;
	bqs_per_grid_cell = (1 << binary->deci_factor_log2);
	tbl_width_bqs  = (num_hor_grids - 1) * bqs_per_grid_cell;
	tbl_height_bqs = (num_ver_grids - 1) * bqs_per_grid_cell;

	IA_CSS_LOG("tbl_width_bqs=%d, tbl_height_bqs=%d", tbl_width_bqs, tbl_height_bqs);

	/*
	 * Real sensor data area on the पूर्णांकernal frame at shading correction.
	 * Filters and scaling are applied to the पूर्णांकernal frame beक्रमe
	 * shading correction, depending on the binary.
	 */
	sensor_org_x_bqs_on_पूर्णांकernal = scr.sensor_data_origin_x_bqs_on_पूर्णांकernal;
	sensor_org_y_bqs_on_पूर्णांकernal = scr.sensor_data_origin_y_bqs_on_पूर्णांकernal;
	अणु
		अचिन्हित पूर्णांक bs_frac = 8;	/* scaling factor 1.0 in fixed poपूर्णांक (8 == FRAC_ACC macro in ISP) */
		अचिन्हित पूर्णांक bs_out, bs_in;	/* scaling ratio in fixed poपूर्णांक */

		bs_out = scr.bayer_scale_hor_ratio_out * bs_frac;
		bs_in = scr.bayer_scale_hor_ratio_in * bs_frac;
		sensor_width_bqs  = (in_width_bqs * bs_out + bs_in / 2) / bs_in; /* "+ bs_in/2": rounding */

		bs_out = scr.bayer_scale_ver_ratio_out * bs_frac;
		bs_in = scr.bayer_scale_ver_ratio_in * bs_frac;
		sensor_height_bqs = (in_height_bqs * bs_out + bs_in / 2) / bs_in; /* "+ bs_in/2": rounding */
	पूर्ण

	/* Center of the sensor data on the पूर्णांकernal frame at shading correction. */
	sensor_center_x_bqs_on_पूर्णांकernal = sensor_org_x_bqs_on_पूर्णांकernal + sensor_width_bqs / 2;
	sensor_center_y_bqs_on_पूर्णांकernal = sensor_org_y_bqs_on_पूर्णांकernal + sensor_height_bqs / 2;

	/* Size of left/right/upper/lower sides of the sensor center on the पूर्णांकernal frame. */
	left  = sensor_center_x_bqs_on_पूर्णांकernal;
	right = पूर्णांकernal_width_bqs - sensor_center_x_bqs_on_पूर्णांकernal;
	upper = sensor_center_y_bqs_on_पूर्णांकernal;
	lower = पूर्णांकernal_height_bqs - sensor_center_y_bqs_on_पूर्णांकernal;

	/* Align the size of left/right/upper/lower sides to a multiple of the grid cell size. */
	adjust_left  = CEIL_MUL(left,  bqs_per_grid_cell);
	adjust_right = CEIL_MUL(right, bqs_per_grid_cell);
	adjust_upper = CEIL_MUL(upper, bqs_per_grid_cell);
	adjust_lower = CEIL_MUL(lower, bqs_per_grid_cell);

	/* Shading table should cover the adjusted frame size. */
	adjust_width_bqs  = adjust_left + adjust_right;
	adjust_height_bqs = adjust_upper + adjust_lower;

	IA_CSS_LOG("adjust_width_bqs=%d, adjust_height_bqs=%d", adjust_width_bqs, adjust_height_bqs);

	अगर (adjust_width_bqs > tbl_width_bqs || adjust_height_bqs > tbl_height_bqs) अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-EINVAL);
		वापस -EINVAL;
	पूर्ण

	/* Origin of the पूर्णांकernal frame on the shading table. */
	पूर्णांकernal_org_x_bqs_on_tbl = adjust_left - left;
	पूर्णांकernal_org_y_bqs_on_tbl = adjust_upper - upper;

	/* Origin of the real sensor data area on the shading table. */
	sensor_org_x_bqs_on_tbl = पूर्णांकernal_org_x_bqs_on_tbl + sensor_org_x_bqs_on_पूर्णांकernal;
	sensor_org_y_bqs_on_tbl = पूर्णांकernal_org_y_bqs_on_tbl + sensor_org_y_bqs_on_पूर्णांकernal;

	/* The shading inक्रमmation necessary as API is stored in the shading_info. */
	shading_info->info.type_1.num_hor_grids	    = num_hor_grids;
	shading_info->info.type_1.num_ver_grids	    = num_ver_grids;
	shading_info->info.type_1.bqs_per_grid_cell = bqs_per_grid_cell;

	shading_info->info.type_1.bayer_scale_hor_ratio_in  = scr.bayer_scale_hor_ratio_in;
	shading_info->info.type_1.bayer_scale_hor_ratio_out = scr.bayer_scale_hor_ratio_out;
	shading_info->info.type_1.bayer_scale_ver_ratio_in  = scr.bayer_scale_ver_ratio_in;
	shading_info->info.type_1.bayer_scale_ver_ratio_out = scr.bayer_scale_ver_ratio_out;

	shading_info->info.type_1.isp_input_sensor_data_res_bqs.width  = in_width_bqs;
	shading_info->info.type_1.isp_input_sensor_data_res_bqs.height = in_height_bqs;

	shading_info->info.type_1.sensor_data_res_bqs.width  = sensor_width_bqs;
	shading_info->info.type_1.sensor_data_res_bqs.height = sensor_height_bqs;

	shading_info->info.type_1.sensor_data_origin_bqs_on_sctbl.x = (पूर्णांक32_t)sensor_org_x_bqs_on_tbl;
	shading_info->info.type_1.sensor_data_origin_bqs_on_sctbl.y = (पूर्णांक32_t)sensor_org_y_bqs_on_tbl;

	/* The shading inक्रमmation related to ISP (but, not necessary as API) is stored in the pipe_config. */
	pipe_config->पूर्णांकernal_frame_origin_bqs_on_sctbl.x = (पूर्णांक32_t)पूर्णांकernal_org_x_bqs_on_tbl;
	pipe_config->पूर्णांकernal_frame_origin_bqs_on_sctbl.y = (पूर्णांक32_t)पूर्णांकernal_org_y_bqs_on_tbl;

	IA_CSS_LOG("shading_info: grids=%dx%d, cell=%d, scale=%d,%d,%d,%d, input=%dx%d, data=%dx%d, origin=(%d,%d)",
		   shading_info->info.type_1.num_hor_grids,
		   shading_info->info.type_1.num_ver_grids,
		   shading_info->info.type_1.bqs_per_grid_cell,
		   shading_info->info.type_1.bayer_scale_hor_ratio_in,
		   shading_info->info.type_1.bayer_scale_hor_ratio_out,
		   shading_info->info.type_1.bayer_scale_ver_ratio_in,
		   shading_info->info.type_1.bayer_scale_ver_ratio_out,
		   shading_info->info.type_1.isp_input_sensor_data_res_bqs.width,
		   shading_info->info.type_1.isp_input_sensor_data_res_bqs.height,
		   shading_info->info.type_1.sensor_data_res_bqs.width,
		   shading_info->info.type_1.sensor_data_res_bqs.height,
		   shading_info->info.type_1.sensor_data_origin_bqs_on_sctbl.x,
		   shading_info->info.type_1.sensor_data_origin_bqs_on_sctbl.y);

	IA_CSS_LOG("pipe_config: origin=(%d,%d)",
		   pipe_config->पूर्णांकernal_frame_origin_bqs_on_sctbl.x,
		   pipe_config->पूर्णांकernal_frame_origin_bqs_on_sctbl.y);

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण


पूर्णांक
ia_css_binary_get_shading_info(स्थिर काष्ठा ia_css_binary *binary,			/* [in] */
			       क्रमागत ia_css_shading_correction_type type,		/* [in] */
			       अचिन्हित पूर्णांक required_bds_factor,			/* [in] */
			       स्थिर काष्ठा ia_css_stream_config *stream_config,	/* [in] */
			       काष्ठा ia_css_shading_info *shading_info,		/* [out] */
			       काष्ठा ia_css_pipe_config *pipe_config)			/* [out] */
अणु
	पूर्णांक err;

	निश्चित(binary);
	निश्चित(shading_info);

	IA_CSS_ENTER_PRIVATE("binary=%p, type=%d, required_bds_factor=%d, stream_config=%p",
			     binary, type, required_bds_factor, stream_config);

	अगर (type != IA_CSS_SHADING_CORRECTION_TYPE_1) अणु
		err = -ENOTSUPP;

		IA_CSS_LEAVE_ERR_PRIVATE(err);
		वापस err;
	पूर्ण

	अगर (!IS_ISP2401)
		err = isp2400_binary_get_shading_info_type_1(binary,
							     required_bds_factor,
							     stream_config,
							     shading_info);
	अन्यथा
		err = isp2401_binary_get_shading_info_type_1(binary,
							     required_bds_factor,
							     stream_config,
							     shading_info,
							     pipe_config);

	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल व्योम sh_css_binary_common_grid_info(स्थिर काष्ठा ia_css_binary *binary,
	काष्ठा ia_css_grid_info *info)
अणु
	निश्चित(binary);
	निश्चित(info);

	info->isp_in_width = binary->पूर्णांकernal_frame_info.res.width;
	info->isp_in_height = binary->पूर्णांकernal_frame_info.res.height;

	info->vamem_type = IA_CSS_VAMEM_TYPE_2;
पूर्ण

व्योम
ia_css_binary_dvs_grid_info(स्थिर काष्ठा ia_css_binary *binary,
			    काष्ठा ia_css_grid_info *info,
			    काष्ठा ia_css_pipe *pipe)
अणु
	काष्ठा ia_css_dvs_grid_info *dvs_info;

	(व्योम)pipe;
	निश्चित(binary);
	निश्चित(info);

	dvs_info = &info->dvs_grid.dvs_grid_info;

	/* क्रम DIS, we use a भागision instead of a उच्चमान_भाग. If this is smaller
	 * than the 3a grid size, it indicates that the outer values are not
	 * valid क्रम DIS.
	 */
	dvs_info->enable            = binary->info->sp.enable.dis;
	dvs_info->width             = binary->dis.grid.dim.width;
	dvs_info->height            = binary->dis.grid.dim.height;
	dvs_info->aligned_width     = binary->dis.grid.pad.width;
	dvs_info->aligned_height    = binary->dis.grid.pad.height;
	dvs_info->bqs_per_grid_cell = 1 << binary->dis.deci_factor_log2;
	dvs_info->num_hor_coefs     = binary->dis.coef.dim.width;
	dvs_info->num_ver_coefs     = binary->dis.coef.dim.height;

	sh_css_binary_common_grid_info(binary, info);
पूर्ण

व्योम
ia_css_binary_dvs_stat_grid_info(
    स्थिर काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_grid_info *info,
    काष्ठा ia_css_pipe *pipe)
अणु
	(व्योम)pipe;
	sh_css_binary_common_grid_info(binary, info);
	वापस;
पूर्ण

पूर्णांक
ia_css_binary_3a_grid_info(स्थिर काष्ठा ia_css_binary *binary,
			   काष्ठा ia_css_grid_info *info,
			   काष्ठा ia_css_pipe *pipe) अणु
	काष्ठा ia_css_3a_grid_info *s3a_info;
	पूर्णांक err = 0;

	IA_CSS_ENTER_PRIVATE("binary=%p, info=%p, pipe=%p",
			     binary, info, pipe);

	निश्चित(binary);
	निश्चित(info);
	s3a_info = &info->s3a_grid;

	/* 3A statistics grid */
	s3a_info->enable            = binary->info->sp.enable.s3a;
	s3a_info->width             = binary->s3atbl_width;
	s3a_info->height            = binary->s3atbl_height;
	s3a_info->aligned_width     = binary->s3atbl_isp_width;
	s3a_info->aligned_height    = binary->s3atbl_isp_height;
	s3a_info->bqs_per_grid_cell = (1 << binary->deci_factor_log2);
	s3a_info->deci_factor_log2  = binary->deci_factor_log2;
	s3a_info->elem_bit_depth    = SH_CSS_BAYER_BITS;
	s3a_info->use_dmem          = binary->info->sp.s3a.s3atbl_use_dmem;
#अगर defined(HAS_NO_HMEM)
	s3a_info->has_histogram     = 1;
#अन्यथा
	s3a_info->has_histogram     = 0;
#पूर्ण_अगर
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

अटल व्योम
binary_init_pc_histogram(काष्ठा sh_css_pc_histogram *histo)
अणु
	निश्चित(histo);

	histo->length = 0;
	histo->run = शून्य;
	histo->stall = शून्य;
पूर्ण

अटल व्योम
binary_init_metrics(काष्ठा sh_css_binary_metrics *metrics,
		    स्थिर काष्ठा ia_css_binary_info *info)
अणु
	निश्चित(metrics);
	निश्चित(info);

	metrics->mode = info->pipeline.mode;
	metrics->id   = info->id;
	metrics->next = शून्य;
	binary_init_pc_histogram(&metrics->isp_histogram);
	binary_init_pc_histogram(&metrics->sp_histogram);
पूर्ण

/* move to host part of output module */
अटल bool
binary_supports_output_क्रमmat(स्थिर काष्ठा ia_css_binary_xinfo *info,
			      क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	पूर्णांक i;

	निश्चित(info);

	क्रम (i = 0; i < info->num_output_क्रमmats; i++) अणु
		अगर (info->output_क्रमmats[i] == क्रमmat)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool
binary_supports_vf_क्रमmat(स्थिर काष्ठा ia_css_binary_xinfo *info,
			  क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	पूर्णांक i;

	निश्चित(info);

	क्रम (i = 0; i < info->num_vf_क्रमmats; i++) अणु
		अगर (info->vf_क्रमmats[i] == क्रमmat)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/* move to host part of bds module */
अटल bool
supports_bds_factor(u32 supported_factors,
		    uपूर्णांक32_t bds_factor)
अणु
	वापस ((supported_factors & PACK_BDS_FACTOR(bds_factor)) != 0);
पूर्ण

अटल पूर्णांक
binary_init_info(काष्ठा ia_css_binary_xinfo *info, अचिन्हित पूर्णांक i,
		 bool *binary_found) अणु
	स्थिर अचिन्हित अक्षर *blob = sh_css_blob_info[i].blob;
	अचिन्हित पूर्णांक size = sh_css_blob_info[i].header.blob.size;

	अगर ((!info) || (!binary_found))
		वापस -EINVAL;

	*info = sh_css_blob_info[i].header.info.isp;
	*binary_found = blob;
	info->blob_index = i;
	/* we करोn't have this binary, skip it */
	अगर (!size)
		वापस 0;

	info->xmem_addr = sh_css_load_blob(blob, size);
	अगर (!info->xmem_addr)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/* When binaries are put at the beginning, they will only
 * be selected अगर no other primary matches.
 */
पूर्णांक
ia_css_binary_init_infos(व्योम) अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_of_isp_binaries = sh_css_num_binaries - NUM_OF_SPS - NUM_OF_BLS;

	अगर (num_of_isp_binaries == 0)
		वापस 0;

	all_binaries = kvदो_स्मृति(num_of_isp_binaries * माप(*all_binaries),
				GFP_KERNEL);
	अगर (!all_binaries)
		वापस -ENOMEM;

	क्रम (i = 0; i < num_of_isp_binaries; i++)
	अणु
		पूर्णांक ret;
		काष्ठा ia_css_binary_xinfo *binary = &all_binaries[i];
		bool binary_found;

		ret = binary_init_info(binary, i, &binary_found);
		अगर (ret)
			वापस ret;
		अगर (!binary_found)
			जारी;
		/* Prepend new binary inक्रमmation */
		binary->next = binary_infos[binary->sp.pipeline.mode];
		binary_infos[binary->sp.pipeline.mode] = binary;
		binary->blob = &sh_css_blob_info[i];
		binary->mem_offsets = sh_css_blob_info[i].mem_offsets;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
ia_css_binary_uninit(व्योम) अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_binary_xinfo *b;

	क्रम (i = 0; i < IA_CSS_BINARY_NUM_MODES; i++)
	अणु
		क्रम (b = binary_infos[i]; b; b = b->next) अणु
			अगर (b->xmem_addr)
				hmm_मुक्त(b->xmem_addr);
			b->xmem_addr = mmgr_शून्य;
		पूर्ण
		binary_infos[i] = शून्य;
	पूर्ण
	kvमुक्त(all_binaries);
	वापस 0;
पूर्ण

/* @brief Compute decimation factor क्रम 3A statistics and shading correction.
 *
 * @param[in]	width	Frame width in pixels.
 * @param[in]	height	Frame height in pixels.
 * @वापस	Log2 of decimation factor (= grid cell size) in bayer quads.
 */
अटल पूर्णांक
binary_grid_deci_factor_log2(पूर्णांक width, पूर्णांक height)
अणु
	/* 3A/Shading decimation factor spcअगरication (at August 2008)
	 * ------------------------------------------------------------------
	 * [Image Width (BQ)] [Decimation Factor (BQ)] [Resulting grid cells]
	#अगर_अघोषित ISP2401
	 * 1280 ?c             32                       40 ?c
	 *  640 ?c 1279        16                       40 ?c 80
	 *      ?c  639         8                          ?c 80
	#अन्यथा
	 * from 1280                   32                 from 40
	 * from  640 to 1279           16                 from 40 to 80
	 *           to  639            8                         to 80
	#पूर्ण_अगर
	 * ------------------------------------------------------------------
	 */
	/* Maximum and minimum decimation factor by the specअगरication */
#घोषणा MAX_SPEC_DECI_FACT_LOG2		5
#घोषणा MIN_SPEC_DECI_FACT_LOG2		3
	/* the smallest frame width in bayer quads when decimation factor (log2) is 5 or 4, by the specअगरication */
#घोषणा DECI_FACT_LOG2_5_SMALLEST_FRAME_WIDTH_BQ	1280
#घोषणा DECI_FACT_LOG2_4_SMALLEST_FRAME_WIDTH_BQ	640

	पूर्णांक smallest_factor; /* the smallest factor (log2) where the number of cells करोes not exceed the limitation */
	पूर्णांक spec_factor;     /* the factor (log2) which satisfies the specअगरication */

	/* Currently supported maximum width and height are 5120(=80*64) and 3840(=60*64). */
	निश्चित(ISP_BQ_GRID_WIDTH(width,
				 MAX_SPEC_DECI_FACT_LOG2) <= SH_CSS_MAX_BQ_GRID_WIDTH);
	निश्चित(ISP_BQ_GRID_HEIGHT(height,
				  MAX_SPEC_DECI_FACT_LOG2) <= SH_CSS_MAX_BQ_GRID_HEIGHT);

	/* Compute the smallest factor. */
	smallest_factor = MAX_SPEC_DECI_FACT_LOG2;
	जबतक (ISP_BQ_GRID_WIDTH(width,
				 smallest_factor - 1) <= SH_CSS_MAX_BQ_GRID_WIDTH &&
	       ISP_BQ_GRID_HEIGHT(height, smallest_factor - 1) <= SH_CSS_MAX_BQ_GRID_HEIGHT
	       && smallest_factor > MIN_SPEC_DECI_FACT_LOG2)
		smallest_factor--;

	/* Get the factor by the specअगरication. */
	अगर (_ISP_BQS(width) >= DECI_FACT_LOG2_5_SMALLEST_FRAME_WIDTH_BQ)
		spec_factor = 5;
	अन्यथा अगर (_ISP_BQS(width) >= DECI_FACT_LOG2_4_SMALLEST_FRAME_WIDTH_BQ)
		spec_factor = 4;
	अन्यथा
		spec_factor = 3;

	/* If smallest_factor is smaller than or equal to spec_factor, choose spec_factor to follow the specअगरication.
	   If smallest_factor is larger than spec_factor, choose smallest_factor.

		ex. width=2560, height=1920
			smallest_factor=4, spec_factor=5
			smallest_factor < spec_factor   ->   वापस spec_factor

		ex. width=300, height=3000
			smallest_factor=5, spec_factor=3
			smallest_factor > spec_factor   ->   वापस smallest_factor
	*/
	वापस max(smallest_factor, spec_factor);

#अघोषित MAX_SPEC_DECI_FACT_LOG2
#अघोषित MIN_SPEC_DECI_FACT_LOG2
#अघोषित DECI_FACT_LOG2_5_SMALLEST_FRAME_WIDTH_BQ
#अघोषित DECI_FACT_LOG2_4_SMALLEST_FRAME_WIDTH_BQ
पूर्ण

अटल पूर्णांक
binary_in_frame_padded_width(पूर्णांक in_frame_width,
			     पूर्णांक isp_पूर्णांकernal_width,
			     पूर्णांक dvs_env_width,
			     पूर्णांक stream_config_left_padding,
			     पूर्णांक left_cropping,
			     bool need_scaling)
अणु
	पूर्णांक rval;
	पूर्णांक nr_of_left_paddings;	/* number of paddings pixels on the left of an image line */

#अगर defined(ISP2401)
	/* the output image line of Input System 2401 करोes not have the left paddings  */
	nr_of_left_paddings = 0;
#अन्यथा
	/* in other हालs, the left padding pixels are always 128 */
	nr_of_left_paddings = 2 * ISP_VEC_NELEMS;
#पूर्ण_अगर
	अगर (need_scaling) अणु
		/* In SDV use-हाल, we need to match left-padding of
		 * primary and the video binary. */
		अगर (stream_config_left_padding != -1) अणु
			/* Dअगरferent than beक्रमe, we करो left&right padding. */
			rval =
			    CEIL_MUL(in_frame_width + nr_of_left_paddings,
				     2 * ISP_VEC_NELEMS);
		पूर्ण अन्यथा अणु
			/* Dअगरferent than beक्रमe, we करो left&right padding. */
			in_frame_width += dvs_env_width;
			rval =
			    CEIL_MUL(in_frame_width +
				     (left_cropping ? nr_of_left_paddings : 0),
				     2 * ISP_VEC_NELEMS);
		पूर्ण
	पूर्ण अन्यथा अणु
		rval = isp_पूर्णांकernal_width;
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
ia_css_binary_fill_info(स्थिर काष्ठा ia_css_binary_xinfo *xinfo,
			bool online,
			bool two_ppc,
			क्रमागत atomisp_input_क्रमmat stream_क्रमmat,
			स्थिर काष्ठा ia_css_frame_info *in_info, /* can be शून्य */
			स्थिर काष्ठा ia_css_frame_info *bds_out_info, /* can be शून्य */
			स्थिर काष्ठा ia_css_frame_info *out_info[], /* can be शून्य */
			स्थिर काष्ठा ia_css_frame_info *vf_info, /* can be शून्य */
			काष्ठा ia_css_binary *binary,
			काष्ठा ia_css_resolution *dvs_env,
			पूर्णांक stream_config_left_padding,
			bool accelerator) अणु
	स्थिर काष्ठा ia_css_binary_info *info = &xinfo->sp;
	अचिन्हित पूर्णांक dvs_env_width = 0,
	dvs_env_height = 0,
	vf_log_ds = 0,
	s3a_log_deci = 0,
	bits_per_pixel = 0,
	/* Resolution at SC/3A/DIS kernel. */
	sc_3a_dis_width = 0,
	/* Resolution at SC/3A/DIS kernel. */
	sc_3a_dis_padded_width = 0,
	/* Resolution at SC/3A/DIS kernel. */
	sc_3a_dis_height = 0,
	isp_पूर्णांकernal_width = 0,
	isp_पूर्णांकernal_height = 0,
	s3a_isp_width = 0;

	bool need_scaling = false;
	काष्ठा ia_css_resolution binary_dvs_env, पूर्णांकernal_res;
	पूर्णांक err;
	अचिन्हित पूर्णांक i;
	स्थिर काष्ठा ia_css_frame_info *bin_out_info = शून्य;

	निश्चित(info);
	निश्चित(binary);

	binary->info = xinfo;
	अगर (!accelerator)
	अणु
		/* binary->css_params has been filled by accelerator itself. */
		err = ia_css_isp_param_allocate_isp_parameters(
		    &binary->mem_params, &binary->css_params,
		    &info->mem_initializers);
		अगर (err) अणु
			वापस err;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
	अणु
		अगर (out_info[i] && (out_info[i]->res.width != 0)) अणु
			bin_out_info = out_info[i];
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (in_info && bin_out_info)
	अणु
		need_scaling = (in_info->res.width != bin_out_info->res.width) ||
			       (in_info->res.height != bin_out_info->res.height);
	पूर्ण

	/* binary_dvs_env has to be equal or larger than SH_CSS_MIN_DVS_ENVELOPE */
	binary_dvs_env.width = 0;
	binary_dvs_env.height = 0;
	ia_css_binary_dvs_env(info, dvs_env, &binary_dvs_env);
	dvs_env_width = binary_dvs_env.width;
	dvs_env_height = binary_dvs_env.height;
	binary->dvs_envelope.width  = dvs_env_width;
	binary->dvs_envelope.height = dvs_env_height;

	/* पूर्णांकernal resolution calculation */
	पूर्णांकernal_res.width = 0;
	पूर्णांकernal_res.height = 0;
	ia_css_binary_पूर्णांकernal_res(in_info, bds_out_info, bin_out_info, dvs_env,
				   info, &पूर्णांकernal_res);
	isp_पूर्णांकernal_width = पूर्णांकernal_res.width;
	isp_पूर्णांकernal_height = पूर्णांकernal_res.height;

	/* पूर्णांकernal frame info */
	अगर (bin_out_info) /* अणु */
		binary->पूर्णांकernal_frame_info.क्रमmat = bin_out_info->क्रमmat;
	/* पूर्ण */
	binary->पूर्णांकernal_frame_info.res.width       = isp_पूर्णांकernal_width;
	binary->पूर्णांकernal_frame_info.padded_width    = CEIL_MUL(isp_पूर्णांकernal_width, 2 * ISP_VEC_NELEMS);
	binary->पूर्णांकernal_frame_info.res.height      = isp_पूर्णांकernal_height;
	binary->पूर्णांकernal_frame_info.raw_bit_depth   = bits_per_pixel;

	अगर (in_info)
	अणु
		binary->effective_in_frame_res.width = in_info->res.width;
		binary->effective_in_frame_res.height = in_info->res.height;

		bits_per_pixel = in_info->raw_bit_depth;

		/* input info */
		binary->in_frame_info.res.width = in_info->res.width +
						  info->pipeline.left_cropping;
		binary->in_frame_info.res.height = in_info->res.height +
						   info->pipeline.top_cropping;

		binary->in_frame_info.res.width += dvs_env_width;
		binary->in_frame_info.res.height += dvs_env_height;

		binary->in_frame_info.padded_width =
		    binary_in_frame_padded_width(in_info->res.width,
						 isp_पूर्णांकernal_width,
						 dvs_env_width,
						 stream_config_left_padding,
						 info->pipeline.left_cropping,
						 need_scaling);

		binary->in_frame_info.क्रमmat = in_info->क्रमmat;
		binary->in_frame_info.raw_bayer_order = in_info->raw_bayer_order;
		binary->in_frame_info.crop_info = in_info->crop_info;
	पूर्ण

	अगर (online)
	अणु
		bits_per_pixel = ia_css_util_input_क्रमmat_bpp(
				     stream_क्रमmat, two_ppc);
	पूर्ण
	binary->in_frame_info.raw_bit_depth = bits_per_pixel;

	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
	अणु
		अगर (out_info[i]) अणु
			binary->out_frame_info[i].res.width     = out_info[i]->res.width;
			binary->out_frame_info[i].res.height    = out_info[i]->res.height;
			binary->out_frame_info[i].padded_width  = out_info[i]->padded_width;
			अगर (info->pipeline.mode == IA_CSS_BINARY_MODE_COPY) अणु
				binary->out_frame_info[i].raw_bit_depth = bits_per_pixel;
			पूर्ण अन्यथा अणु
				/* Only relevant क्रम RAW क्रमmat.
				 * At the moment, all outमाला_दो are raw, 16 bit per pixel, except क्रम copy.
				 * To करो this cleanly, the binary should specअगरy in its info
				 * the bit depth per output channel.
				 */
				binary->out_frame_info[i].raw_bit_depth = 16;
			पूर्ण
			binary->out_frame_info[i].क्रमmat        = out_info[i]->क्रमmat;
		पूर्ण
	पूर्ण

	अगर (vf_info && (vf_info->res.width != 0))
	अणु
		err = ia_css_vf_configure(binary, bin_out_info,
					  (काष्ठा ia_css_frame_info *)vf_info, &vf_log_ds);
		अगर (err) अणु
			अगर (!accelerator) अणु
				ia_css_isp_param_destroy_isp_parameters(
				    &binary->mem_params,
				    &binary->css_params);
			पूर्ण
			वापस err;
		पूर्ण
	पूर्ण
	binary->vf_करोwnscale_log2 = vf_log_ds;

	binary->online            = online;
	binary->input_क्रमmat      = stream_क्रमmat;

	/* viewfinder output info */
	अगर ((vf_info) && (vf_info->res.width != 0))
	अणु
		अचिन्हित पूर्णांक vf_out_vecs, vf_out_width, vf_out_height;

		binary->vf_frame_info.क्रमmat = vf_info->क्रमmat;
		अगर (!bin_out_info)
			वापस -EINVAL;
		vf_out_vecs = __ISP_VF_OUTPUT_WIDTH_VECS(bin_out_info->padded_width,
			      vf_log_ds);
		vf_out_width = _ISP_VF_OUTPUT_WIDTH(vf_out_vecs);
		vf_out_height = _ISP_VF_OUTPUT_HEIGHT(bin_out_info->res.height,
						      vf_log_ds);

		/* For preview mode, output pin is used instead of vf. */
		अगर (info->pipeline.mode == IA_CSS_BINARY_MODE_PREVIEW) अणु
			binary->out_frame_info[0].res.width =
			    (bin_out_info->res.width >> vf_log_ds);
			binary->out_frame_info[0].padded_width = vf_out_width;
			binary->out_frame_info[0].res.height   = vf_out_height;

			binary->vf_frame_info.res.width    = 0;
			binary->vf_frame_info.padded_width = 0;
			binary->vf_frame_info.res.height   = 0;
		पूर्ण अन्यथा अणु
			/* we also store the raw करोwnscaled width. This is
			 * used क्रम digital zoom in preview to zoom only on
			 * the width that we actually want to keep, not on
			 * the aligned width. */
			binary->vf_frame_info.res.width =
			    (bin_out_info->res.width >> vf_log_ds);
			binary->vf_frame_info.padded_width = vf_out_width;
			binary->vf_frame_info.res.height   = vf_out_height;
		पूर्ण
	पूर्ण अन्यथा
	अणु
		binary->vf_frame_info.res.width    = 0;
		binary->vf_frame_info.padded_width = 0;
		binary->vf_frame_info.res.height   = 0;
	पूर्ण

	अगर (info->enable.ca_gdc)
	अणु
		binary->morph_tbl_width =
		    _ISP_MORPH_TABLE_WIDTH(isp_पूर्णांकernal_width);
		binary->morph_tbl_aligned_width  =
		    _ISP_MORPH_TABLE_ALIGNED_WIDTH(isp_पूर्णांकernal_width);
		binary->morph_tbl_height =
		    _ISP_MORPH_TABLE_HEIGHT(isp_पूर्णांकernal_height);
	पूर्ण अन्यथा
	अणु
		binary->morph_tbl_width  = 0;
		binary->morph_tbl_aligned_width  = 0;
		binary->morph_tbl_height = 0;
	पूर्ण

	sc_3a_dis_width = binary->in_frame_info.res.width;
	sc_3a_dis_padded_width = binary->in_frame_info.padded_width;
	sc_3a_dis_height = binary->in_frame_info.res.height;
	अगर (bds_out_info && in_info &&
	    bds_out_info->res.width != in_info->res.width)
	अणु
		/* TODO: Next, "internal_frame_info" should be derived from
		 * bds_out. So this part will change once it is in place! */
		sc_3a_dis_width = bds_out_info->res.width + info->pipeline.left_cropping;
		sc_3a_dis_padded_width = isp_पूर्णांकernal_width;
		sc_3a_dis_height = isp_पूर्णांकernal_height;
	पूर्ण

	s3a_isp_width = _ISP_S3A_ELEMS_ISP_WIDTH(sc_3a_dis_padded_width,
			info->pipeline.left_cropping);
	अगर (info->s3a.fixed_s3a_deci_log)
	अणु
		s3a_log_deci = info->s3a.fixed_s3a_deci_log;
	पूर्ण अन्यथा
	अणु
		s3a_log_deci = binary_grid_deci_factor_log2(s3a_isp_width,
			       sc_3a_dis_height);
	पूर्ण
	binary->deci_factor_log2  = s3a_log_deci;

	अगर (info->enable.s3a)
	अणु
		binary->s3atbl_width  =
		    _ISP_S3ATBL_WIDTH(sc_3a_dis_width,
				      s3a_log_deci);
		binary->s3atbl_height =
		    _ISP_S3ATBL_HEIGHT(sc_3a_dis_height,
				       s3a_log_deci);
		binary->s3atbl_isp_width =
		    _ISP_S3ATBL_ISP_WIDTH(s3a_isp_width,
					  s3a_log_deci);
		binary->s3atbl_isp_height =
		    _ISP_S3ATBL_ISP_HEIGHT(sc_3a_dis_height,
					   s3a_log_deci);
	पूर्ण अन्यथा
	अणु
		binary->s3atbl_width  = 0;
		binary->s3atbl_height = 0;
		binary->s3atbl_isp_width  = 0;
		binary->s3atbl_isp_height = 0;
	पूर्ण

	अगर (info->enable.sc)
	अणु
		अगर (!IS_ISP2401) अणु
			binary->sctbl_width_per_color = _ISP2400_SCTBL_WIDTH_PER_COLOR(sc_3a_dis_padded_width, s3a_log_deci);
			binary->sctbl_aligned_width_per_color = ISP2400_SH_CSS_MAX_SCTBL_ALIGNED_WIDTH_PER_COLOR;
			binary->sctbl_height = _ISP2400_SCTBL_HEIGHT(sc_3a_dis_height, s3a_log_deci);
		पूर्ण अन्यथा अणु
			binary->sctbl_width_per_color = _ISP2401_SCTBL_WIDTH_PER_COLOR(isp_पूर्णांकernal_width, s3a_log_deci);
			binary->sctbl_aligned_width_per_color = ISP2401_SH_CSS_MAX_SCTBL_ALIGNED_WIDTH_PER_COLOR;
			binary->sctbl_height = _ISP2401_SCTBL_HEIGHT(isp_पूर्णांकernal_height, s3a_log_deci);
			binary->sctbl_legacy_width_per_color  = _ISP_SCTBL_LEGACY_WIDTH_PER_COLOR(sc_3a_dis_padded_width, s3a_log_deci);
			binary->sctbl_legacy_height = _ISP_SCTBL_LEGACY_HEIGHT(sc_3a_dis_height, s3a_log_deci);
		पूर्ण
	पूर्ण अन्यथा
	अणु
		binary->sctbl_width_per_color         = 0;
		binary->sctbl_aligned_width_per_color = 0;
		binary->sctbl_height                  = 0;
		अगर (IS_ISP2401) अणु
			binary->sctbl_legacy_width_per_color  = 0;
			binary->sctbl_legacy_height	      = 0;
		पूर्ण
	पूर्ण
	ia_css_sdis_init_info(&binary->dis,
			      sc_3a_dis_width,
			      sc_3a_dis_padded_width,
			      sc_3a_dis_height,
			      info->pipeline.isp_pipe_version,
			      info->enable.dis);
	अगर (info->pipeline.left_cropping)
		binary->left_padding = 2 * ISP_VEC_NELEMS - info->pipeline.left_cropping;
	अन्यथा
		binary->left_padding = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक __ia_css_binary_find(काष्ठा ia_css_binary_descr *descr,
				काष्ठा ia_css_binary *binary) अणु
	पूर्णांक mode;
	bool online;
	bool two_ppc;
	क्रमागत atomisp_input_क्रमmat stream_क्रमmat;
	स्थिर काष्ठा ia_css_frame_info *req_in_info,
		*req_bds_out_info,
		*req_out_info[IA_CSS_BINARY_MAX_OUTPUT_PORTS],
		*req_bin_out_info = शून्य,
		*req_vf_info;

	काष्ठा ia_css_binary_xinfo *xcandidate;
#अगर_अघोषित ISP2401
	bool need_ds, need_dz, need_dvs, need_xnr, need_dpc;
#अन्यथा
	bool need_ds, need_dz, need_dvs, need_xnr, need_dpc, need_tnr;
#पूर्ण_अगर
	bool striped;
	bool enable_yuv_ds;
	bool enable_high_speed;
	bool enable_dvs_6axis;
	bool enable_reduced_pipe;
	bool enable_capture_pp_bli;
#अगर_घोषित ISP2401
	bool enable_luma_only;
#पूर्ण_अगर
	पूर्णांक err = -EINVAL;
	bool continuous;
	अचिन्हित पूर्णांक isp_pipe_version;
	काष्ठा ia_css_resolution dvs_env, पूर्णांकernal_res;
	अचिन्हित पूर्णांक i;

	निश्चित(descr);
	/* MW: used after an error check, may accept शून्य, but करोubtfull */
	निश्चित(binary);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_binary_find() enter: descr=%p, (mode=%d), binary=%p\n",
			    descr, descr->mode,
			    binary);

	mode = descr->mode;
	online = descr->online;
	two_ppc = descr->two_ppc;
	stream_क्रमmat = descr->stream_क्रमmat;
	req_in_info = descr->in_info;
	req_bds_out_info = descr->bds_out_info;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
	अणु
		req_out_info[i] = descr->out_info[i];
		अगर (req_out_info[i] && (req_out_info[i]->res.width != 0))
			req_bin_out_info = req_out_info[i];
	पूर्ण
	अगर (!req_bin_out_info)
		वापस -EINVAL;
#अगर_अघोषित ISP2401
	req_vf_info = descr->vf_info;
#अन्यथा

	अगर ((descr->vf_info) && (descr->vf_info->res.width == 0))
		/* width==0 means that there is no vf pin (e.g. in SkyCam preview हाल) */
		req_vf_info = शून्य;
	अन्यथा
		req_vf_info = descr->vf_info;
#पूर्ण_अगर

	need_xnr = descr->enable_xnr;
	need_ds = descr->enable_fractional_ds;
	need_dz = false;
	need_dvs = false;
	need_dpc = descr->enable_dpc;
#अगर_घोषित ISP2401
	need_tnr = descr->enable_tnr;
#पूर्ण_अगर
	enable_yuv_ds = descr->enable_yuv_ds;
	enable_high_speed = descr->enable_high_speed;
	enable_dvs_6axis  = descr->enable_dvs_6axis;
	enable_reduced_pipe = descr->enable_reduced_pipe;
	enable_capture_pp_bli = descr->enable_capture_pp_bli;
#अगर_घोषित ISP2401
	enable_luma_only = descr->enable_luma_only;
#पूर्ण_अगर
	continuous = descr->continuous;
	striped = descr->striped;
	isp_pipe_version = descr->isp_pipe_version;

	dvs_env.width = 0;
	dvs_env.height = 0;
	पूर्णांकernal_res.width = 0;
	पूर्णांकernal_res.height = 0;

	अगर (mode == IA_CSS_BINARY_MODE_VIDEO)
	अणु
		dvs_env = descr->dvs_env;
		need_dz = descr->enable_dz;
		/* Video is the only mode that has a nodz variant. */
		need_dvs = dvs_env.width || dvs_env.height;
	पूर्ण

	/* prपूर्णांक a map of the binary file */
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,	"BINARY INFO:\n");
	क्रम (i = 0; i < IA_CSS_BINARY_NUM_MODES; i++)
	अणु
		xcandidate = binary_infos[i];
		अगर (xcandidate) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,	"%d:\n", i);
			जबतक (xcandidate) अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, " Name:%s Type:%d Cont:%d\n",
						    xcandidate->blob->name, xcandidate->type,
						    xcandidate->sp.enable.continuous);
				xcandidate = xcandidate->next;
			पूर्ण
		पूर्ण
	पूर्ण

	/* म_लिखो("sh_css_binary_find: pipe version %d\n", isp_pipe_version); */
	क्रम (xcandidate = binary_infos[mode]; xcandidate;
	     xcandidate = xcandidate->next)
	अणु
		काष्ठा ia_css_binary_info *candidate = &xcandidate->sp;
		/* म_लिखो("sh_css_binary_find: evaluating candidate:
		 * %d\न",candidate->id); */
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_binary_find() candidate = %p, mode = %d ID = %d\n",
				    candidate, candidate->pipeline.mode, candidate->id);

		/*
		 * MW: Only a limited set of joपूर्णांकly configured binaries can
		 * be used in a continuous preview/video mode unless it is
		 * the copy mode and runs on SP.
		*/
		अगर (!candidate->enable.continuous &&
		    continuous && (mode != IA_CSS_BINARY_MODE_COPY)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && %d && (%d != %d)\n",
					    __LINE__, candidate->enable.continuous,
					    continuous, mode,
					    IA_CSS_BINARY_MODE_COPY);
			जारी;
		पूर्ण
		अगर (striped && candidate->iterator.num_stripes == 1) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: binary is not striped\n",
					    __LINE__);
			जारी;
		पूर्ण

		अगर (candidate->pipeline.isp_pipe_version != isp_pipe_version &&
		    (mode != IA_CSS_BINARY_MODE_COPY) &&
		    (mode != IA_CSS_BINARY_MODE_CAPTURE_PP) &&
		    (mode != IA_CSS_BINARY_MODE_VF_PP)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%d != %d)\n",
					    __LINE__,
					    candidate->pipeline.isp_pipe_version, isp_pipe_version);
			जारी;
		पूर्ण
		अगर (!candidate->enable.reduced_pipe && enable_reduced_pipe) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && %d\n",
					    __LINE__,
					    candidate->enable.reduced_pipe,
					    enable_reduced_pipe);
			जारी;
		पूर्ण
		अगर (!candidate->enable.dvs_6axis && enable_dvs_6axis) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && %d\n",
					    __LINE__,
					    candidate->enable.dvs_6axis,
					    enable_dvs_6axis);
			जारी;
		पूर्ण
		अगर (candidate->enable.high_speed && !enable_high_speed) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: %d && !%d\n",
					    __LINE__,
					    candidate->enable.high_speed,
					    enable_high_speed);
			जारी;
		पूर्ण
		अगर (!candidate->enable.xnr && need_xnr) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: %d && !%d\n",
					    __LINE__,
					    candidate->enable.xnr,
					    need_xnr);
			जारी;
		पूर्ण
		अगर (!(candidate->enable.ds & 2) && enable_yuv_ds) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && %d\n",
					    __LINE__,
					    ((candidate->enable.ds & 2) != 0),
					    enable_yuv_ds);
			जारी;
		पूर्ण
		अगर ((candidate->enable.ds & 2) && !enable_yuv_ds) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: %d && !%d\n",
					    __LINE__,
					    ((candidate->enable.ds & 2) != 0),
					    enable_yuv_ds);
			जारी;
		पूर्ण

		अगर (mode == IA_CSS_BINARY_MODE_VIDEO &&
		    candidate->enable.ds && need_ds)
			need_dz = false;

		/* when we require vf output, we need to have vf_veceven */
		अगर ((req_vf_info) && !(candidate->enable.vf_veceven ||
				       /* or variable vf vec even */
				       candidate->vf_dec.is_variable ||
				       /* or more than one output pin. */
				       xcandidate->num_output_pins > 1)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%p != NULL) && !(%d || %d || (%d >%d))\n",
					    __LINE__, req_vf_info,
					    candidate->enable.vf_veceven,
					    candidate->vf_dec.is_variable,
					    xcandidate->num_output_pins, 1);
			जारी;
		पूर्ण
		अगर (!candidate->enable.dvs_envelope && need_dvs) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && %d\n",
					    __LINE__,
					    candidate->enable.dvs_envelope, (पूर्णांक)need_dvs);
			जारी;
		पूर्ण
		/* पूर्णांकernal_res check considers input, output, and dvs envelope sizes */
		ia_css_binary_पूर्णांकernal_res(req_in_info, req_bds_out_info,
					   req_bin_out_info, &dvs_env, candidate, &पूर्णांकernal_res);
		अगर (पूर्णांकernal_res.width > candidate->पूर्णांकernal.max_width) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%d > %d)\n",
					    __LINE__, पूर्णांकernal_res.width,
					    candidate->पूर्णांकernal.max_width);
			जारी;
		पूर्ण
		अगर (पूर्णांकernal_res.height > candidate->पूर्णांकernal.max_height) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%d > %d)\n",
					    __LINE__, पूर्णांकernal_res.height,
					    candidate->पूर्णांकernal.max_height);
			जारी;
		पूर्ण
		अगर (!candidate->enable.ds && need_ds && !(xcandidate->num_output_pins > 1)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && %d\n",
					    __LINE__, candidate->enable.ds, (पूर्णांक)need_ds);
			जारी;
		पूर्ण
		अगर (!candidate->enable.uds && !candidate->enable.dvs_6axis && need_dz) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && !%d && %d\n",
					    __LINE__, candidate->enable.uds,
					    candidate->enable.dvs_6axis, (पूर्णांक)need_dz);
			जारी;
		पूर्ण
		अगर (online && candidate->input.source == IA_CSS_BINARY_INPUT_MEMORY) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: %d && (%d == %d)\n",
					    __LINE__, online, candidate->input.source,
					    IA_CSS_BINARY_INPUT_MEMORY);
			जारी;
		पूर्ण
		अगर (!online && candidate->input.source == IA_CSS_BINARY_INPUT_SENSOR) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && (%d == %d)\n",
					    __LINE__, online, candidate->input.source,
					    IA_CSS_BINARY_INPUT_SENSOR);
			जारी;
		पूर्ण
		अगर (req_bin_out_info->res.width < candidate->output.min_width ||
		    req_bin_out_info->res.width > candidate->output.max_width) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%d > %d) || (%d < %d)\n",
					    __LINE__,
					    req_bin_out_info->padded_width,
					    candidate->output.min_width,
					    req_bin_out_info->padded_width,
					    candidate->output.max_width);
			जारी;
		पूर्ण
		अगर (xcandidate->num_output_pins > 1 &&
		    /* in हाल we have a second output pin, */
		    req_vf_info) अणु /* and we need vf output. */
			अगर (req_vf_info->res.width > candidate->output.max_width) अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "ia_css_binary_find() [%d] continue: (%d < %d)\n",
						    __LINE__,
						    req_vf_info->res.width,
						    candidate->output.max_width);
				जारी;
			पूर्ण
		पूर्ण
		अगर (req_in_info->padded_width > candidate->input.max_width) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%d > %d)\n",
					    __LINE__, req_in_info->padded_width,
					    candidate->input.max_width);
			जारी;
		पूर्ण
		अगर (!binary_supports_output_क्रमmat(xcandidate, req_bin_out_info->क्रमmat)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d\n",
					    __LINE__,
					    binary_supports_output_क्रमmat(xcandidate, req_bin_out_info->क्रमmat));
			जारी;
		पूर्ण
		अगर (xcandidate->num_output_pins > 1 &&
		    /* in हाल we have a second output pin, */
		    req_vf_info                   && /* and we need vf output. */
		    /* check अगर the required vf क्रमmat
		    is supported. */
		    !binary_supports_output_क्रमmat(xcandidate, req_vf_info->क्रमmat)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%d > %d) && (%p != NULL) && !%d\n",
					    __LINE__, xcandidate->num_output_pins, 1,
					    req_vf_info,
					    binary_supports_output_क्रमmat(xcandidate, req_vf_info->क्रमmat));
			जारी;
		पूर्ण

		/* Check अगर vf_veceven supports the requested vf क्रमmat */
		अगर (xcandidate->num_output_pins == 1 &&
		    req_vf_info && candidate->enable.vf_veceven &&
		    !binary_supports_vf_क्रमmat(xcandidate, req_vf_info->क्रमmat)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: (%d == %d) && (%p != NULL) && %d && !%d\n",
					    __LINE__, xcandidate->num_output_pins, 1,
					    req_vf_info, candidate->enable.vf_veceven,
					    binary_supports_vf_क्रमmat(xcandidate, req_vf_info->क्रमmat));
			जारी;
		पूर्ण

		/* Check अगर vf_veceven supports the requested vf width */
		अगर (xcandidate->num_output_pins == 1 &&
		    req_vf_info && candidate->enable.vf_veceven) अणु /* and we need vf output. */
			अगर (req_vf_info->res.width > candidate->output.max_width) अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "ia_css_binary_find() [%d] continue: (%d < %d)\n",
						    __LINE__,
						    req_vf_info->res.width,
						    candidate->output.max_width);
				जारी;
			पूर्ण
		पूर्ण

		अगर (!supports_bds_factor(candidate->bds.supported_bds_factors,
					 descr->required_bds_factor)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: 0x%x & 0x%x)\n",
					    __LINE__, candidate->bds.supported_bds_factors,
					    descr->required_bds_factor);
			जारी;
		पूर्ण

		अगर (!candidate->enable.dpc && need_dpc) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: 0x%x & 0x%x)\n",
					    __LINE__, candidate->enable.dpc,
					    descr->enable_dpc);
			जारी;
		पूर्ण

		अगर (candidate->uds.use_bci && enable_capture_pp_bli) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: 0x%x & 0x%x)\n",
					    __LINE__, candidate->uds.use_bci,
					    descr->enable_capture_pp_bli);
			जारी;
		पूर्ण

#अगर_घोषित ISP2401
		अगर (candidate->enable.luma_only != enable_luma_only) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: %d != %d\n",
					    __LINE__, candidate->enable.luma_only,
					    descr->enable_luma_only);
			जारी;
		पूर्ण

		अगर (!candidate->enable.tnr && need_tnr) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "ia_css_binary_find() [%d] continue: !%d && %d\n",
					    __LINE__, candidate->enable.tnr,
					    descr->enable_tnr);
			जारी;
		पूर्ण

#पूर्ण_अगर
		/* reconfigure any variable properties of the binary */
		err = ia_css_binary_fill_info(xcandidate, online, two_ppc,
					      stream_क्रमmat, req_in_info,
					      req_bds_out_info,
					      req_out_info, req_vf_info,
					      binary, &dvs_env,
					      descr->stream_config_left_padding,
					      false);

		अगर (err)
			अवरोध;
		binary_init_metrics(&binary->metrics, &binary->info->sp);
		अवरोध;
	पूर्ण

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_binary_find() selected = %p, mode = %d ID = %d\n",
			    xcandidate, xcandidate ? xcandidate->sp.pipeline.mode : 0, xcandidate ? xcandidate->sp.id : 0);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_binary_find() leave: return_err=%d\n", err);

	अगर (!err && xcandidate)
		dev_dbg(atomisp_dev,
			"Using binary %s (id %d), type %d, mode %d, continuous %s\n",
			xcandidate->blob->name,
			xcandidate->sp.id,
			xcandidate->type,
			xcandidate->sp.pipeline.mode,
			xcandidate->sp.enable.continuous ? "true" : "false");


	वापस err;
पूर्ण

पूर्णांक ia_css_binary_find(काष्ठा ia_css_binary_descr *descr,
		       काष्ठा ia_css_binary *binary)
अणु
	पूर्णांक ret = __ia_css_binary_find(descr, binary);

	अगर (unlikely(ret)) अणु
		dev_dbg(atomisp_dev, "Seeking for binary failed at:");
		dump_stack();
	पूर्ण

	वापस ret;
पूर्ण

अचिन्हित
ia_css_binary_max_vf_width(व्योम)
अणु
	/* This is (should be) true क्रम IPU1 and IPU2 */
	/* For IPU3 (SkyCam) this poपूर्णांकer is guaranteed to be शून्य simply because such a binary करोes not exist  */
	अगर (binary_infos[IA_CSS_BINARY_MODE_VF_PP])
		वापस binary_infos[IA_CSS_BINARY_MODE_VF_PP]->sp.output.max_width;
	वापस 0;
पूर्ण

व्योम
ia_css_binary_destroy_isp_parameters(काष्ठा ia_css_binary *binary)
अणु
	अगर (binary) अणु
		ia_css_isp_param_destroy_isp_parameters(&binary->mem_params,
							&binary->css_params);
	पूर्ण
पूर्ण

व्योम
ia_css_binary_get_isp_binaries(काष्ठा ia_css_binary_xinfo **binaries,
			       uपूर्णांक32_t *num_isp_binaries)
अणु
	निश्चित(binaries);

	अगर (num_isp_binaries)
		*num_isp_binaries = 0;

	*binaries = all_binaries;
	अगर (all_binaries && num_isp_binaries) अणु
		/* -1 to account क्रम sp binary which is not stored in all_binaries */
		अगर (sh_css_num_binaries > 0)
			*num_isp_binaries = sh_css_num_binaries - 1;
	पूर्ण
पूर्ण
