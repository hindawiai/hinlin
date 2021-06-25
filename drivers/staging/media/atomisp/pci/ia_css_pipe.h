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

#अगर_अघोषित __IA_CSS_PIPE_H__
#घोषणा __IA_CSS_PIPE_H__

#समावेश <type_support.h>
#समावेश "ia_css_stream.h"
#समावेश "ia_css_frame.h"
#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_binary.h"
#समावेश "sh_css_legacy.h"

#घोषणा PIPE_ENTRY_EMPTY_TOKEN                (~0U)
#घोषणा PIPE_ENTRY_RESERVED_TOKEN             (0x1)

काष्ठा ia_css_preview_settings अणु
	काष्ठा ia_css_binary copy_binary;
	काष्ठा ia_css_binary preview_binary;
	काष्ठा ia_css_binary vf_pp_binary;

	/* 2401 only क्रम these two - करो we in fact use them क्रम anything real */
	काष्ठा ia_css_frame *delay_frames[MAX_NUM_VIDEO_DELAY_FRAMES];
	काष्ठा ia_css_frame *tnr_frames[NUM_TNR_FRAMES];

	काष्ठा ia_css_pipe *copy_pipe;
	काष्ठा ia_css_pipe *capture_pipe;
	काष्ठा ia_css_pipe *acc_pipe;
पूर्ण;

#घोषणा IA_CSS_DEFAULT_PREVIEW_SETTINGS अणु \
	.copy_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.preview_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.vf_pp_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
पूर्ण

काष्ठा ia_css_capture_settings अणु
	काष्ठा ia_css_binary copy_binary;
	/* we extend primary binary to multiple stages because in ISP2.6.1
	 * the computation load is too high to fit in one single binary. */
	काष्ठा ia_css_binary primary_binary[MAX_NUM_PRIMARY_STAGES];
	अचिन्हित पूर्णांक num_primary_stage;
	काष्ठा ia_css_binary pre_isp_binary;
	काष्ठा ia_css_binary anr_gdc_binary;
	काष्ठा ia_css_binary post_isp_binary;
	काष्ठा ia_css_binary capture_pp_binary;
	काष्ठा ia_css_binary vf_pp_binary;
	काष्ठा ia_css_binary capture_ldc_binary;
	काष्ठा ia_css_binary *yuv_scaler_binary;
	काष्ठा ia_css_frame *delay_frames[MAX_NUM_VIDEO_DELAY_FRAMES];
	bool *is_output_stage;
	अचिन्हित पूर्णांक num_yuv_scaler;
पूर्ण;

#घोषणा IA_CSS_DEFAULT_CAPTURE_SETTINGS अणु \
	.copy_binary		= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.primary_binary		= अणुIA_CSS_BINARY_DEFAULT_SETTINGSपूर्ण, \
	.pre_isp_binary		= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.anr_gdc_binary		= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.post_isp_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.capture_pp_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.vf_pp_binary		= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.capture_ldc_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
पूर्ण

काष्ठा ia_css_video_settings अणु
	काष्ठा ia_css_binary copy_binary;
	काष्ठा ia_css_binary video_binary;
	काष्ठा ia_css_binary vf_pp_binary;
	काष्ठा ia_css_binary *yuv_scaler_binary;
	काष्ठा ia_css_frame *delay_frames[MAX_NUM_VIDEO_DELAY_FRAMES];
	काष्ठा ia_css_frame *tnr_frames[NUM_TNR_FRAMES];
	काष्ठा ia_css_frame *vf_pp_in_frame;
	काष्ठा ia_css_pipe *copy_pipe;
	काष्ठा ia_css_pipe *capture_pipe;
	bool *is_output_stage;
	अचिन्हित पूर्णांक num_yuv_scaler;
पूर्ण;

#घोषणा IA_CSS_DEFAULT_VIDEO_SETTINGS अणु \
	.copy_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.video_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
	.vf_pp_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
पूर्ण

काष्ठा ia_css_yuvpp_settings अणु
	काष्ठा ia_css_binary copy_binary;
	काष्ठा ia_css_binary *yuv_scaler_binary;
	काष्ठा ia_css_binary *vf_pp_binary;
	bool *is_output_stage;
	अचिन्हित पूर्णांक num_yuv_scaler;
	अचिन्हित पूर्णांक num_vf_pp;
	अचिन्हित पूर्णांक num_output;
पूर्ण;

#घोषणा IA_CSS_DEFAULT_YUVPP_SETTINGS अणु \
	.copy_binary	= IA_CSS_BINARY_DEFAULT_SETTINGS, \
पूर्ण

काष्ठा osys_object;

काष्ठा ia_css_pipe अणु
	/* TODO: Remove stop_requested and use stop_requested in the pipeline */
	bool                            stop_requested;
	काष्ठा ia_css_pipe_config       config;
	काष्ठा ia_css_pipe_extra_config extra_config;
	काष्ठा ia_css_pipe_info         info;
	क्रमागत ia_css_pipe_id		mode;
	काष्ठा ia_css_shading_table	*shading_table;
	काष्ठा ia_css_pipeline		pipeline;
	काष्ठा ia_css_frame_info	output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_frame_info	bds_output_info;
	काष्ठा ia_css_frame_info	vf_output_info[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_frame_info	out_yuv_ds_input_info;
	काष्ठा ia_css_frame_info	vf_yuv_ds_input_info;
	काष्ठा ia_css_fw_info		*output_stage;	/* extra output stage */
	काष्ठा ia_css_fw_info		*vf_stage;	/* extra vf_stage */
	अचिन्हित पूर्णांक			required_bds_factor;
	अचिन्हित पूर्णांक			dvs_frame_delay;
	पूर्णांक				num_invalid_frames;
	bool				enable_viewfinder[IA_CSS_PIPE_MAX_OUTPUT_STAGE];
	काष्ठा ia_css_stream		*stream;
	काष्ठा ia_css_frame		in_frame_काष्ठा;
	काष्ठा ia_css_frame		out_frame_काष्ठा;
	काष्ठा ia_css_frame		vf_frame_काष्ठा;
	काष्ठा ia_css_frame		*continuous_frames[NUM_CONTINUOUS_FRAMES];
	काष्ठा ia_css_metadata	*cont_md_buffers[NUM_CONTINUOUS_FRAMES];
	जोड़ अणु
		काष्ठा ia_css_preview_settings preview;
		काष्ठा ia_css_video_settings   video;
		काष्ठा ia_css_capture_settings capture;
		काष्ठा ia_css_yuvpp_settings yuvpp;
	पूर्ण pipe_settings;
	ia_css_ptr scaler_pp_lut;
	काष्ठा osys_object *osys_obj;

	/* This number is unique per pipe each instance of css. This number is
	 * reused as pipeline number also. There is a 1-1 mapping between pipe_num
	 * and sp thपढ़ो id. Current logic limits pipe_num to
	 * SH_CSS_MAX_SP_THREADS */
	अचिन्हित पूर्णांक pipe_num;
पूर्ण;

#घोषणा IA_CSS_DEFAULT_PIPE अणु \
	.config			= DEFAULT_PIPE_CONFIG, \
	.info			= DEFAULT_PIPE_INFO, \
	.mode			= IA_CSS_PIPE_ID_ACC, /* (pipe_id) */ \
	.pipeline		= DEFAULT_PIPELINE, \
	.output_info		= अणुIA_CSS_BINARY_DEFAULT_FRAME_INFOपूर्ण, \
	.bds_output_info	= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
	.vf_output_info		= अणुIA_CSS_BINARY_DEFAULT_FRAME_INFOपूर्ण, \
	.out_yuv_ds_input_info	= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
	.vf_yuv_ds_input_info	= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
	.required_bds_factor	= SH_CSS_BDS_FACTOR_1_00, \
	.dvs_frame_delay	= 1, \
	.enable_viewfinder	= अणुtrueपूर्ण, \
	.in_frame_काष्ठा	= DEFAULT_FRAME, \
	.out_frame_काष्ठा	= DEFAULT_FRAME, \
	.vf_frame_काष्ठा	= DEFAULT_FRAME, \
	.pipe_settings		= अणु \
		.preview = IA_CSS_DEFAULT_PREVIEW_SETTINGS \
	पूर्ण, \
	.pipe_num		= PIPE_ENTRY_EMPTY_TOKEN, \
पूर्ण

व्योम ia_css_pipe_map_queue(काष्ठा ia_css_pipe *pipe, bool map);

पूर्णांक
sh_css_param_update_isp_params(काष्ठा ia_css_pipe *curr_pipe,
			       काष्ठा ia_css_isp_parameters *params,
			       bool commit, काष्ठा ia_css_pipe *pipe);

#पूर्ण_अगर /* __IA_CSS_PIPE_H__ */
