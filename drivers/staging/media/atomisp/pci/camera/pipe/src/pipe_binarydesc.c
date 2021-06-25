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

#समावेश "ia_css_pipe_binarydesc.h"
#समावेश "ia_css_frame_format.h"
#समावेश "ia_css_pipe.h"
#समावेश "ia_css_pipe_util.h"
#समावेश "ia_css_util.h"
#समावेश "ia_css_debug.h"
#समावेश "sh_css_params.h"
#समावेश <निश्चित_support.h>
/* HRT_GDC_N */
#समावेश "gdc_device.h"
#समावेश <linux/kernel.h>

/* This module provides a binary descriptions to used to find a binary. Since,
 * every stage is associated with a binary, it implicity helps stage
 * description. Apart from providing a binary description, this module also
 * populates the frame info's when required.*/

/* Generic descriptor क्रम offline binaries. Internal function. */
अटल व्योम pipe_binarydesc_get_offline(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    स्थिर पूर्णांक mode,
    काष्ठा ia_css_binary_descr *descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info[],
    काष्ठा ia_css_frame_info *vf_info)
अणु
	अचिन्हित पूर्णांक i;
	/* in_info, out_info, vf_info can be शून्य */
	निश्चित(pipe);
	निश्चित(descr);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
			    "pipe_binarydesc_get_offline() enter:\n");

	descr->mode = mode;
	descr->online = false;
	descr->continuous = pipe->stream->config.continuous;
	descr->striped = false;
	descr->two_ppc = false;
	descr->enable_yuv_ds = false;
	descr->enable_high_speed = false;
	descr->enable_dvs_6axis = false;
	descr->enable_reduced_pipe = false;
	descr->enable_dz = true;
	descr->enable_xnr = false;
	descr->enable_dpc = false;
	descr->enable_luma_only = false;
	descr->enable_tnr = false;
	descr->enable_capture_pp_bli = false;
	descr->enable_fractional_ds = false;
	descr->dvs_env.width = 0;
	descr->dvs_env.height = 0;
	descr->stream_क्रमmat = pipe->stream->config.input_config.क्रमmat;
	descr->in_info = in_info;
	descr->bds_out_info = शून्य;
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		descr->out_info[i] = out_info[i];
	descr->vf_info = vf_info;
	descr->isp_pipe_version = pipe->config.isp_pipe_version;
	descr->required_bds_factor = SH_CSS_BDS_FACTOR_1_00;
	descr->stream_config_left_padding = -1;
पूर्ण

व्योम ia_css_pipe_get_copy_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *copy_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info)
अणु
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	अचिन्हित पूर्णांक i;
	/* out_info can be शून्य */
	निश्चित(pipe);
	निश्चित(in_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;
	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_COPY,
				    copy_descr, in_info, out_infos, vf_info);
	copy_descr->online = true;
	copy_descr->continuous = false;
	copy_descr->two_ppc = (pipe->stream->config.pixels_per_घड़ी == 2);
	copy_descr->enable_dz = false;
	copy_descr->isp_pipe_version = IA_CSS_PIPE_VERSION_1;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_vfpp_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *vf_pp_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info)
अणु
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	अचिन्हित पूर्णांक i;
	/* out_info can be शून्य ??? */
	निश्चित(pipe);
	निश्चित(in_info);
	IA_CSS_ENTER_PRIVATE("");

	in_info->raw_bit_depth = 0;
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_VF_PP,
				    vf_pp_descr, in_info, out_infos, शून्य);
	vf_pp_descr->enable_fractional_ds = true;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

अटल काष्ठा sh_css_bds_factor bds_factors_list[] = अणु
	अणु1, 1, SH_CSS_BDS_FACTOR_1_00पूर्ण,
	अणु5, 4, SH_CSS_BDS_FACTOR_1_25पूर्ण,
	अणु3, 2, SH_CSS_BDS_FACTOR_1_50पूर्ण,
	अणु2, 1, SH_CSS_BDS_FACTOR_2_00पूर्ण,
	अणु9, 4, SH_CSS_BDS_FACTOR_2_25पूर्ण,
	अणु5, 2, SH_CSS_BDS_FACTOR_2_50पूर्ण,
	अणु3, 1, SH_CSS_BDS_FACTOR_3_00पूर्ण,
	अणु4, 1, SH_CSS_BDS_FACTOR_4_00पूर्ण,
	अणु9, 2, SH_CSS_BDS_FACTOR_4_50पूर्ण,
	अणु5, 1, SH_CSS_BDS_FACTOR_5_00पूर्ण,
	अणु6, 1, SH_CSS_BDS_FACTOR_6_00पूर्ण,
	अणु8, 1, SH_CSS_BDS_FACTOR_8_00पूर्ण
पूर्ण;

पूर्णांक sh_css_bds_factor_get_numerator_denominator(
    अचिन्हित पूर्णांक bds_factor,
    अचिन्हित पूर्णांक *bds_factor_numerator,
    अचिन्हित पूर्णांक *bds_factor_denominator)
अणु
	अचिन्हित पूर्णांक i;

	/* Loop over all bds factors until a match is found */
	क्रम (i = 0; i < ARRAY_SIZE(bds_factors_list); i++) अणु
		अगर (bds_factors_list[i].bds_factor == bds_factor) अणु
			*bds_factor_numerator = bds_factors_list[i].numerator;
			*bds_factor_denominator = bds_factors_list[i].denominator;
			वापस 0;
		पूर्ण
	पूर्ण

	/* Throw an error since bds_factor cannot be found
	in bds_factors_list */
	वापस -EINVAL;
पूर्ण

पूर्णांक binarydesc_calculate_bds_factor(
    काष्ठा ia_css_resolution input_res,
    काष्ठा ia_css_resolution output_res,
    अचिन्हित पूर्णांक *bds_factor)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक in_w = input_res.width,
		     in_h = input_res.height,
		     out_w = output_res.width, out_h = output_res.height;

	अचिन्हित पूर्णांक max_bds_factor = 8;
	अचिन्हित पूर्णांक max_rounding_margin = 2;
	/* delta in pixels to account क्रम rounding margin in the calculation */
	अचिन्हित पूर्णांक delta = max_bds_factor * max_rounding_margin;

	/* Assert अगर the resolutions are not set */
	निश्चित(in_w != 0 && in_h != 0);
	निश्चित(out_w != 0 && out_h != 0);

	/* Loop over all bds factors until a match is found */
	क्रम (i = 0; i < ARRAY_SIZE(bds_factors_list); i++) अणु
		अचिन्हित पूर्णांक num = bds_factors_list[i].numerator;
		अचिन्हित पूर्णांक den = bds_factors_list[i].denominator;

		/* See width-wise and height-wise अगर this bds_factor
		 * satisfies the condition */
		bool cond = (out_w * num / den + delta > in_w) &&
			    (out_w * num / den <= in_w) &&
			    (out_h * num / den + delta > in_h) &&
			    (out_h * num / den <= in_h);

		अगर (cond) अणु
			*bds_factor = bds_factors_list[i].bds_factor;
			वापस 0;
		पूर्ण
	पूर्ण

	/* Throw an error since a suitable bds_factor cannot be found */
	वापस -EINVAL;
पूर्ण

पूर्णांक ia_css_pipe_get_preview_binarydesc(
    काष्ठा ia_css_pipe *स्थिर pipe,
    काष्ठा ia_css_binary_descr *preview_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *bds_out_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info)
अणु
	पूर्णांक err;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	पूर्णांक mode = IA_CSS_BINARY_MODE_PREVIEW;
	अचिन्हित पूर्णांक i;

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	निश्चित(vf_info);
	IA_CSS_ENTER_PRIVATE("");

	/*
	 * Set up the info of the input frame with
	 * the ISP required resolution
	 */
	in_info->res = pipe->config.input_effective_res;
	in_info->padded_width = in_info->res.width;
	in_info->raw_bit_depth = ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);

	अगर (ia_css_util_is_input_क्रमmat_yuv(pipe->stream->config.input_config.क्रमmat))
		mode = IA_CSS_BINARY_MODE_COPY;
	अन्यथा
		in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;

	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, mode,
				    preview_descr, in_info, out_infos, vf_info);
	अगर (pipe->stream->config.online) अणु
		preview_descr->online = pipe->stream->config.online;
		preview_descr->two_ppc =
		    (pipe->stream->config.pixels_per_घड़ी == 2);
	पूर्ण
	preview_descr->stream_क्रमmat = pipe->stream->config.input_config.क्रमmat;

	/* TODO: Remove this when bds_out_info is available! */
	*bds_out_info = *in_info;

	अगर (pipe->extra_config.enable_raw_binning) अणु
		अगर (pipe->config.bayer_ds_out_res.width != 0 &&
		    pipe->config.bayer_ds_out_res.height != 0) अणु
			bds_out_info->res.width =
			    pipe->config.bayer_ds_out_res.width;
			bds_out_info->res.height =
			    pipe->config.bayer_ds_out_res.height;
			bds_out_info->padded_width =
			    pipe->config.bayer_ds_out_res.width;
			err =
			    binarydesc_calculate_bds_factor(in_info->res,
							    bds_out_info->res,
							    &preview_descr->required_bds_factor);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			bds_out_info->res.width = in_info->res.width / 2;
			bds_out_info->res.height = in_info->res.height / 2;
			bds_out_info->padded_width = in_info->padded_width / 2;
			preview_descr->required_bds_factor =
			    SH_CSS_BDS_FACTOR_2_00;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* TODO: Remove this when bds_out_info->is available! */
		bds_out_info->res.width = in_info->res.width;
		bds_out_info->res.height = in_info->res.height;
		bds_out_info->padded_width = in_info->padded_width;
		preview_descr->required_bds_factor = SH_CSS_BDS_FACTOR_1_00;
	पूर्ण
	pipe->required_bds_factor = preview_descr->required_bds_factor;

	/* bayer ds and fractional ds cannot be enabled at the same समय,
	so we disable bds_out_info when fractional ds is used */
	अगर (!pipe->extra_config.enable_fractional_ds)
		preview_descr->bds_out_info = bds_out_info;
	अन्यथा
		preview_descr->bds_out_info = शून्य;
	/*
	   ----Preview binary-----
	   --in-->|--out->|vf_veceven|--|--->vf
	   -----------------------
	   * Preview binary normally करोesn't have a vf_port but
	   * instead it has an output port. However, the output is
	   * generated by vf_veceven module in which we might have
	   * a करोwnscaling (by 1x, 2x, or 4x). Because the resolution
	   * might change, we need two dअगरferent info, namely out_info
	   * & vf_info. In fill_binary_info we use out&vf info to
	   * calculate vf decimation factor.
	 */
	*out_info = *vf_info;

	/* In हाल of preview_ds binary, we can करो any fractional amount
	 * of करोwnscale, so there is no DS needed in vf_veceven. Thereक्रमe,
	 * out and vf infos will be the same. Otherwise, we set out resolution
	 * equal to in resolution. */
	अगर (!pipe->extra_config.enable_fractional_ds) अणु
		/* TODO: Change this when bds_out_info is available! */
		out_info->res.width = bds_out_info->res.width;
		out_info->res.height = bds_out_info->res.height;
		out_info->padded_width = bds_out_info->padded_width;
	पूर्ण
	preview_descr->enable_fractional_ds =
	    pipe->extra_config.enable_fractional_ds;

	preview_descr->enable_dpc = pipe->config.enable_dpc;

	preview_descr->isp_pipe_version = pipe->config.isp_pipe_version;
	IA_CSS_LEAVE_ERR_PRIVATE(0);
	वापस 0;
पूर्ण

पूर्णांक ia_css_pipe_get_video_binarydesc(
    काष्ठा ia_css_pipe *स्थिर pipe,
    काष्ठा ia_css_binary_descr *video_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *bds_out_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info,
    पूर्णांक stream_config_left_padding)
अणु
	पूर्णांक mode = IA_CSS_BINARY_MODE_VIDEO;
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	पूर्णांक err = 0;
	bool stream_dz_config = false;

	/* vf_info can be शून्य */
	निश्चित(pipe);
	निश्चित(in_info);
	/* निश्चित(vf_info != शून्य); */
	IA_CSS_ENTER_PRIVATE("");

	/* The solution below is not optimal; we should move to using ia_css_pipe_get_copy_binarydesc()
	 * But क्रम now this fixes things; this code used to be there but was हटाओd
	 * with gerrit 8908 as this was wrong क्रम Skycam; however 240x still needs this
	 */
	अगर (ia_css_util_is_input_क्रमmat_yuv(pipe->stream->config.input_config.क्रमmat))
		mode = IA_CSS_BINARY_MODE_COPY;

	in_info->res = pipe->config.input_effective_res;
	in_info->padded_width = in_info->res.width;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
	in_info->raw_bit_depth = ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, mode,
				    video_descr, in_info, out_infos, vf_info);

	अगर (pipe->stream->config.online) अणु
		video_descr->online = pipe->stream->config.online;
		video_descr->two_ppc =
		    (pipe->stream->config.pixels_per_घड़ी == 2);
	पूर्ण

	अगर (mode == IA_CSS_BINARY_MODE_VIDEO) अणु
		stream_dz_config =
		    ((pipe->stream->isp_params_configs->dz_config.dx !=
		      HRT_GDC_N)
		     || (pipe->stream->isp_params_configs->dz_config.dy !=
			 HRT_GDC_N));

		video_descr->enable_dz = pipe->config.enable_dz
					 || stream_dz_config;
		video_descr->dvs_env = pipe->config.dvs_envelope;
		video_descr->enable_yuv_ds = pipe->extra_config.enable_yuv_ds;
		video_descr->enable_high_speed =
		    pipe->extra_config.enable_high_speed;
		video_descr->enable_dvs_6axis =
		    pipe->extra_config.enable_dvs_6axis;
		video_descr->enable_reduced_pipe =
		    pipe->extra_config.enable_reduced_pipe;
		video_descr->isp_pipe_version = pipe->config.isp_pipe_version;
		video_descr->enable_fractional_ds =
		    pipe->extra_config.enable_fractional_ds;
		video_descr->enable_dpc =
		    pipe->config.enable_dpc;
		video_descr->enable_luma_only =
		    pipe->config.enable_luma_only;
		video_descr->enable_tnr =
		    pipe->config.enable_tnr;

		अगर (pipe->extra_config.enable_raw_binning) अणु
			अगर (pipe->config.bayer_ds_out_res.width != 0 &&
			    pipe->config.bayer_ds_out_res.height != 0) अणु
				bds_out_info->res.width =
				    pipe->config.bayer_ds_out_res.width;
				bds_out_info->res.height =
				    pipe->config.bayer_ds_out_res.height;
				bds_out_info->padded_width =
				    pipe->config.bayer_ds_out_res.width;
				err =
				    binarydesc_calculate_bds_factor(
					in_info->res, bds_out_info->res,
					&video_descr->required_bds_factor);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अणु
				bds_out_info->res.width =
				    in_info->res.width / 2;
				bds_out_info->res.height =
				    in_info->res.height / 2;
				bds_out_info->padded_width =
				    in_info->padded_width / 2;
				video_descr->required_bds_factor =
				    SH_CSS_BDS_FACTOR_2_00;
			पूर्ण
		पूर्ण अन्यथा अणु
			bds_out_info->res.width = in_info->res.width;
			bds_out_info->res.height = in_info->res.height;
			bds_out_info->padded_width = in_info->padded_width;
			video_descr->required_bds_factor =
			    SH_CSS_BDS_FACTOR_1_00;
		पूर्ण

		pipe->required_bds_factor = video_descr->required_bds_factor;

		/* bayer ds and fractional ds cannot be enabled
		at the same समय, so we disable bds_out_info when
		fractional ds is used */
		अगर (!pipe->extra_config.enable_fractional_ds)
			video_descr->bds_out_info = bds_out_info;
		अन्यथा
			video_descr->bds_out_info = शून्य;

		video_descr->enable_fractional_ds =
		    pipe->extra_config.enable_fractional_ds;
		video_descr->stream_config_left_padding = stream_config_left_padding;
	पूर्ण
	IA_CSS_LEAVE_ERR_PRIVATE(err);
	वापस err;
पूर्ण

व्योम ia_css_pipe_get_yuvscaler_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *yuv_scaler_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *पूर्णांकernal_out_info,
    काष्ठा ia_css_frame_info *vf_info)
अणु
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_frame_info *this_vf_info = शून्य;

	निश्चित(pipe);
	निश्चित(in_info);
	/* Note: अगर the following निश्चित fails, the number of ports has been
	 * changed; in that हाल an additional initializer must be added
	 * a few lines below after which this निश्चित can be updated.
	 */
	निश्चित(IA_CSS_BINARY_MAX_OUTPUT_PORTS == 2);
	IA_CSS_ENTER_PRIVATE("");

	in_info->padded_width = in_info->res.width;
	in_info->raw_bit_depth = 0;
	ia_css_frame_info_set_width(in_info, in_info->res.width, 0);
	out_infos[0] = out_info;
	out_infos[1] = पूर्णांकernal_out_info;
	/* add initializers here अगर
	 * निश्चित(IA_CSS_BINARY_MAX_OUTPUT_PORTS == ...);
	 * fails
	 */

	अगर (vf_info) अणु
		this_vf_info = (vf_info->res.width == 0 &&
				vf_info->res.height == 0) ? शून्य : vf_info;
	पूर्ण

	pipe_binarydesc_get_offline(pipe,
				    IA_CSS_BINARY_MODE_CAPTURE_PP,
				    yuv_scaler_descr,
				    in_info, out_infos, this_vf_info);

	yuv_scaler_descr->enable_fractional_ds = true;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_capturepp_binarydesc(
    काष्ठा ia_css_pipe *स्थिर pipe,
    काष्ठा ia_css_binary_descr *capture_pp_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(vf_info);
	IA_CSS_ENTER_PRIVATE("");

	/* the in_info is only used क्रम resolution to enable
	   bayer करोwn scaling. */
	अगर (pipe->out_yuv_ds_input_info.res.width)
		*in_info = pipe->out_yuv_ds_input_info;
	अन्यथा
		*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
	in_info->raw_bit_depth = 0;
	ia_css_frame_info_set_width(in_info, in_info->res.width, 0);

	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe,
				    IA_CSS_BINARY_MODE_CAPTURE_PP,
				    capture_pp_descr,
				    in_info, out_infos, vf_info);

	capture_pp_descr->enable_capture_pp_bli =
	    pipe->config.शेष_capture_config.enable_capture_pp_bli;
	capture_pp_descr->enable_fractional_ds = true;
	capture_pp_descr->enable_xnr =
	    pipe->config.शेष_capture_config.enable_xnr != 0;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

/* lookup table क्रम high quality primary binaries */
अटल अचिन्हित पूर्णांक primary_hq_binary_modes[NUM_PRIMARY_HQ_STAGES] = अणु
	IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE0,
	IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE1,
	IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE2,
	IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE3,
	IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE4,
	IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE5
पूर्ण;

व्योम ia_css_pipe_get_primary_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *prim_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info,
    अचिन्हित पूर्णांक stage_idx)
अणु
	क्रमागत ia_css_pipe_version pipe_version = pipe->config.isp_pipe_version;
	पूर्णांक mode;
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	निश्चित(stage_idx < NUM_PRIMARY_HQ_STAGES);
	/* vf_info can be शून्य - example video_binarydescr */
	/*निश्चित(vf_info != शून्य);*/
	IA_CSS_ENTER_PRIVATE("");

	अगर (pipe_version == IA_CSS_PIPE_VERSION_2_6_1)
		mode = primary_hq_binary_modes[stage_idx];
	अन्यथा
		mode = IA_CSS_BINARY_MODE_PRIMARY;

	अगर (ia_css_util_is_input_क्रमmat_yuv(pipe->stream->config.input_config.क्रमmat))
		mode = IA_CSS_BINARY_MODE_COPY;

	in_info->res = pipe->config.input_effective_res;
	in_info->padded_width = in_info->res.width;

#अगर !defined(HAS_NO_PACKED_RAW_PIXELS)
	अगर (pipe->stream->config.pack_raw_pixels)
		in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW_PACKED;
	अन्यथा
#पूर्ण_अगर
		in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;

	in_info->raw_bit_depth = ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, mode,
				    prim_descr, in_info, out_infos, vf_info);

	अगर (pipe->stream->config.online &&
	    pipe->stream->config.mode != IA_CSS_INPUT_MODE_MEMORY) अणु
		prim_descr->online = true;
		prim_descr->two_ppc =
		    (pipe->stream->config.pixels_per_घड़ी == 2);
		prim_descr->stream_क्रमmat = pipe->stream->config.input_config.क्रमmat;
	पूर्ण
	अगर (mode == IA_CSS_BINARY_MODE_PRIMARY) अणु
		prim_descr->isp_pipe_version = pipe->config.isp_pipe_version;
		prim_descr->enable_fractional_ds =
		    pipe->extra_config.enable_fractional_ds;
		prim_descr->enable_luma_only =
		    pipe->config.enable_luma_only;
		/* We have both striped and non-striped primary binaries,
		 * अगर continuous viewfinder is required, then we must select
		 * a striped one. Otherwise we prefer to use a non-striped
		 * since it has better perक्रमmance. */
		अगर (pipe_version == IA_CSS_PIPE_VERSION_2_6_1)
			prim_descr->striped = false;
		अन्यथा अगर (!IS_ISP2401) अणु
			prim_descr->striped = prim_descr->continuous &&
					      (!pipe->stream->stop_copy_preview || !pipe->stream->disable_cont_vf);
		पूर्ण अन्यथा अणु
			prim_descr->striped = prim_descr->continuous && !pipe->stream->disable_cont_vf;

			अगर ((pipe->config.शेष_capture_config.enable_xnr != 0) &&
			    (pipe->extra_config.enable_dvs_6axis == true))
				prim_descr->enable_xnr = true;
		पूर्ण
	पूर्ण
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_pre_gdc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *pre_gdc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
	in_info->raw_bit_depth = ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_PRE_ISP,
				    pre_gdc_descr, in_info, out_infos, शून्य);
	pre_gdc_descr->isp_pipe_version = pipe->config.isp_pipe_version;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_gdc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *gdc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_QPLANE6;
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_GDC,
				    gdc_descr, in_info, out_infos, शून्य);
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_post_gdc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *post_gdc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	निश्चित(vf_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_YUV420_16;
	in_info->raw_bit_depth = 16;
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_POST_ISP,
				    post_gdc_descr, in_info, out_infos, vf_info);

	post_gdc_descr->isp_pipe_version = pipe->config.isp_pipe_version;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_pre_de_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *pre_de_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
	in_info->raw_bit_depth = ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	अगर (pipe->config.isp_pipe_version == IA_CSS_PIPE_VERSION_1)
		pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_PRE_ISP,
					    pre_de_descr, in_info, out_infos, शून्य);
	अन्यथा अगर (pipe->config.isp_pipe_version == IA_CSS_PIPE_VERSION_2_2) अणु
		pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_PRE_DE,
					    pre_de_descr, in_info, out_infos, शून्य);
	पूर्ण

	अगर (pipe->stream->config.online) अणु
		pre_de_descr->online = true;
		pre_de_descr->two_ppc =
		    (pipe->stream->config.pixels_per_घड़ी == 2);
		pre_de_descr->stream_क्रमmat = pipe->stream->config.input_config.क्रमmat;
	पूर्ण
	pre_de_descr->isp_pipe_version = pipe->config.isp_pipe_version;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_pre_anr_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *pre_anr_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
	in_info->raw_bit_depth = ia_css_pipe_util_pipe_input_क्रमmat_bpp(pipe);
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_PRE_ISP,
				    pre_anr_descr, in_info, out_infos, शून्य);

	अगर (pipe->stream->config.online) अणु
		pre_anr_descr->online = true;
		pre_anr_descr->two_ppc =
		    (pipe->stream->config.pixels_per_घड़ी == 2);
		pre_anr_descr->stream_क्रमmat = pipe->stream->config.input_config.क्रमmat;
	पूर्ण
	pre_anr_descr->isp_pipe_version = pipe->config.isp_pipe_version;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_anr_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *anr_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
	in_info->raw_bit_depth = ANR_ELEMENT_BITS;
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_ANR,
				    anr_descr, in_info, out_infos, शून्य);

	anr_descr->isp_pipe_version = pipe->config.isp_pipe_version;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_post_anr_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *post_anr_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	निश्चित(vf_info);
	IA_CSS_ENTER_PRIVATE("");

	*in_info = *out_info;
	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_RAW;
	in_info->raw_bit_depth = ANR_ELEMENT_BITS;
	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_POST_ISP,
				    post_anr_descr, in_info, out_infos, vf_info);

	post_anr_descr->isp_pipe_version = pipe->config.isp_pipe_version;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_pipe_get_ldc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *ldc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_frame_info *out_infos[IA_CSS_BINARY_MAX_OUTPUT_PORTS];

	निश्चित(pipe);
	निश्चित(in_info);
	निश्चित(out_info);
	IA_CSS_ENTER_PRIVATE("");

	अगर (!IS_ISP2401) अणु
		*in_info = *out_info;
	पूर्ण अन्यथा अणु
		अगर (pipe->out_yuv_ds_input_info.res.width)
			*in_info = pipe->out_yuv_ds_input_info;
		अन्यथा
			*in_info = *out_info;
	पूर्ण

	in_info->क्रमmat = IA_CSS_FRAME_FORMAT_YUV420;
	in_info->raw_bit_depth = 0;
	ia_css_frame_info_set_width(in_info, in_info->res.width, 0);

	out_infos[0] = out_info;
	क्रम (i = 1; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++)
		out_infos[i] = शून्य;

	pipe_binarydesc_get_offline(pipe, IA_CSS_BINARY_MODE_CAPTURE_PP,
				    ldc_descr, in_info, out_infos, शून्य);
	ldc_descr->enable_dvs_6axis =
	    pipe->extra_config.enable_dvs_6axis;
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण
