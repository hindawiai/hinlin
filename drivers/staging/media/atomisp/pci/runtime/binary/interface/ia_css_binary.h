<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित _IA_CSS_BINARY_H_
#घोषणा _IA_CSS_BINARY_H_

#समावेश <type_support.h>
#समावेश "ia_css_types.h"
#समावेश "ia_css_err.h"
#समावेश "ia_css_stream_format.h"
#समावेश "ia_css_stream_public.h"
#समावेश "ia_css_frame_public.h"
#समावेश "sh_css_metrics.h"
#समावेश "isp/kernels/fixedbds/fixedbds_1.0/ia_css_fixedbds_types.h"

/* The binary mode is used in pre-processor expressions so we cannot
 * use an क्रमागत here. */
#घोषणा IA_CSS_BINARY_MODE_COPY       0
#घोषणा IA_CSS_BINARY_MODE_PREVIEW    1
#घोषणा IA_CSS_BINARY_MODE_PRIMARY    2
#घोषणा IA_CSS_BINARY_MODE_VIDEO      3
#घोषणा IA_CSS_BINARY_MODE_PRE_ISP    4
#घोषणा IA_CSS_BINARY_MODE_GDC        5
#घोषणा IA_CSS_BINARY_MODE_POST_ISP   6
#घोषणा IA_CSS_BINARY_MODE_ANR        7
#घोषणा IA_CSS_BINARY_MODE_CAPTURE_PP 8
#घोषणा IA_CSS_BINARY_MODE_VF_PP      9
#घोषणा IA_CSS_BINARY_MODE_PRE_DE     10
#घोषणा IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE0    11
#घोषणा IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE1    12
#घोषणा IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE2    13
#घोषणा IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE3    14
#घोषणा IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE4    15
#घोषणा IA_CSS_BINARY_MODE_PRIMARY_HQ_STAGE5    16
#घोषणा IA_CSS_BINARY_NUM_MODES       17

#घोषणा MAX_NUM_PRIMARY_STAGES 6
#घोषणा NUM_PRIMARY_HQ_STAGES  6  /* number of primary stages क्रम ISP2.6.1 high quality pipe */
#घोषणा NUM_PRIMARY_STAGES     1  /* number of primary satges क्रम ISP1/ISP2.2 pipe */

/* Indicate where binaries can पढ़ो input from */
#घोषणा IA_CSS_BINARY_INPUT_SENSOR   0
#घोषणा IA_CSS_BINARY_INPUT_MEMORY   1
#घोषणा IA_CSS_BINARY_INPUT_VARIABLE 2

/* Should be included without the path.
   However, that requires adding the path to numerous makefiles
   that have nothing to करो with isp parameters.
 */
#समावेश "runtime/isp_param/interface/ia_css_isp_param_types.h"

/* now these ports only include output ports but not vf output ports */
क्रमागत अणु
	IA_CSS_BINARY_OUTPUT_PORT_0 = 0,
	IA_CSS_BINARY_OUTPUT_PORT_1 = 1,
	IA_CSS_BINARY_MAX_OUTPUT_PORTS = 2
पूर्ण;

काष्ठा ia_css_cas_binary_descr अणु
	अचिन्हित पूर्णांक num_stage;
	अचिन्हित पूर्णांक num_output_stage;
	काष्ठा ia_css_frame_info *in_info;
	काष्ठा ia_css_frame_info *पूर्णांकernal_out_info;
	काष्ठा ia_css_frame_info *out_info;
	काष्ठा ia_css_frame_info *vf_info;
	bool *is_output_stage;
पूर्ण;

काष्ठा ia_css_binary_descr अणु
	पूर्णांक mode;
	bool online;
	bool continuous;
	bool striped;
	bool two_ppc;
	bool enable_yuv_ds;
	bool enable_high_speed;
	bool enable_dvs_6axis;
	bool enable_reduced_pipe;
	bool enable_dz;
	bool enable_xnr;
	bool enable_fractional_ds;
	bool enable_dpc;

	/* ISP2401 */
	bool enable_luma_only;
	bool enable_tnr;

	bool enable_capture_pp_bli;
	काष्ठा ia_css_resolution dvs_env;
	क्रमागत atomisp_input_क्रमmat stream_क्रमmat;
	काष्ठा ia_css_frame_info *in_info;		/* the info of the input-frame with the
							   ISP required resolution. */
	काष्ठा ia_css_frame_info *bds_out_info;
	काष्ठा ia_css_frame_info *out_info[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_frame_info *vf_info;
	अचिन्हित पूर्णांक isp_pipe_version;
	अचिन्हित पूर्णांक required_bds_factor;
	पूर्णांक stream_config_left_padding;
पूर्ण;

काष्ठा ia_css_binary अणु
	स्थिर काष्ठा ia_css_binary_xinfo *info;
	क्रमागत atomisp_input_क्रमmat input_क्रमmat;
	काष्ठा ia_css_frame_info in_frame_info;
	काष्ठा ia_css_frame_info पूर्णांकernal_frame_info;
	काष्ठा ia_css_frame_info out_frame_info[IA_CSS_BINARY_MAX_OUTPUT_PORTS];
	काष्ठा ia_css_resolution effective_in_frame_res;
	काष्ठा ia_css_frame_info vf_frame_info;
	पूर्णांक                      input_buf_vectors;
	पूर्णांक                      deci_factor_log2;
	पूर्णांक                      vf_करोwnscale_log2;
	पूर्णांक                      s3atbl_width;
	पूर्णांक                      s3atbl_height;
	पूर्णांक                      s3atbl_isp_width;
	पूर्णांक                      s3atbl_isp_height;
	अचिन्हित पूर्णांक             morph_tbl_width;
	अचिन्हित पूर्णांक             morph_tbl_aligned_width;
	अचिन्हित पूर्णांक             morph_tbl_height;
	पूर्णांक                      sctbl_width_per_color;
	पूर्णांक                      sctbl_aligned_width_per_color;
	पूर्णांक                      sctbl_height;
	पूर्णांक                      sctbl_legacy_width_per_color;
	पूर्णांक                      sctbl_legacy_height;
	काष्ठा ia_css_sdis_info	 dis;
	काष्ठा ia_css_resolution dvs_envelope;
	bool                     online;
	अचिन्हित पूर्णांक             uds_xc;
	अचिन्हित पूर्णांक             uds_yc;
	अचिन्हित पूर्णांक             left_padding;
	काष्ठा sh_css_binary_metrics metrics;
	काष्ठा ia_css_isp_param_host_segments mem_params;
	काष्ठा ia_css_isp_param_css_segments  css_params;
पूर्ण;

#घोषणा IA_CSS_BINARY_DEFAULT_SETTINGS अणु \
	.input_क्रमmat		= ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY, \
	.in_frame_info		= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
	.पूर्णांकernal_frame_info	= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
	.out_frame_info		= अणुIA_CSS_BINARY_DEFAULT_FRAME_INFOपूर्ण, \
	.vf_frame_info		= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
पूर्ण

पूर्णांक
ia_css_binary_init_infos(व्योम);

पूर्णांक
ia_css_binary_uninit(व्योम);

पूर्णांक
ia_css_binary_fill_info(स्थिर काष्ठा ia_css_binary_xinfo *xinfo,
			bool online,
			bool two_ppc,
			क्रमागत atomisp_input_क्रमmat stream_क्रमmat,
			स्थिर काष्ठा ia_css_frame_info *in_info,
			स्थिर काष्ठा ia_css_frame_info *bds_out_info,
			स्थिर काष्ठा ia_css_frame_info *out_info[],
			स्थिर काष्ठा ia_css_frame_info *vf_info,
			काष्ठा ia_css_binary *binary,
			काष्ठा ia_css_resolution *dvs_env,
			पूर्णांक stream_config_left_padding,
			bool accelerator);

पूर्णांक
ia_css_binary_find(काष्ठा ia_css_binary_descr *descr,
		   काष्ठा ia_css_binary *binary);

/* @brief Get the shading inक्रमmation of the specअगरied shading correction type.
 *
 * @param[in] binary: The isp binary which has the shading correction.
 * @param[in] type: The shading correction type.
 * @param[in] required_bds_factor: The bayer करोwnscaling factor required in the pipe.
 * @param[in] stream_config: The stream configuration.
 * @param[out] shading_info: The shading inक्रमmation.
 *		The shading inक्रमmation necessary as API is stored in the shading_info.
 *		The driver needs to get this inक्रमmation to generate
 *		the shading table directly required from ISP.
 * @param[out] pipe_config: The pipe configuration.
 *		The shading inक्रमmation related to ISP (but, not necessary as API) is stored in the pipe_config.
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक
ia_css_binary_get_shading_info(स्थिर काष्ठा ia_css_binary *binary,
			       क्रमागत ia_css_shading_correction_type type,
			       अचिन्हित पूर्णांक required_bds_factor,
			       स्थिर काष्ठा ia_css_stream_config *stream_config,
			       काष्ठा ia_css_shading_info *shading_info,
			       काष्ठा ia_css_pipe_config *pipe_config);

पूर्णांक
ia_css_binary_3a_grid_info(स्थिर काष्ठा ia_css_binary *binary,
			   काष्ठा ia_css_grid_info *info,
			   काष्ठा ia_css_pipe *pipe);

व्योम
ia_css_binary_dvs_grid_info(स्थिर काष्ठा ia_css_binary *binary,
			    काष्ठा ia_css_grid_info *info,
			    काष्ठा ia_css_pipe *pipe);

व्योम
ia_css_binary_dvs_stat_grid_info(
    स्थिर काष्ठा ia_css_binary *binary,
    काष्ठा ia_css_grid_info *info,
    काष्ठा ia_css_pipe *pipe);

अचिन्हित
ia_css_binary_max_vf_width(व्योम);

व्योम
ia_css_binary_destroy_isp_parameters(काष्ठा ia_css_binary *binary);

व्योम
ia_css_binary_get_isp_binaries(काष्ठा ia_css_binary_xinfo **binaries,
			       uपूर्णांक32_t *num_isp_binaries);

#पूर्ण_अगर /* _IA_CSS_BINARY_H_ */
