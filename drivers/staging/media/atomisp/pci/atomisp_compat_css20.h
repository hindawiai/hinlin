<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Clovertrail PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
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

#अगर_अघोषित __ATOMISP_COMPAT_CSS20_H__
#घोषणा __ATOMISP_COMPAT_CSS20_H__

#समावेश <media/v4l2-mediabus.h>

#समावेश "ia_css.h"
#समावेश "ia_css_types.h"
#समावेश "ia_css_acc_types.h"
#समावेश "sh_css_legacy.h"

#घोषणा ATOMISP_CSS2_PIPE_MAX	2
#घोषणा ATOMISP_CSS2_NUM_OFFLINE_INIT_CONTINUOUS_FRAMES     3
#घोषणा ATOMISP_CSS2_NUM_OFFLINE_INIT_CONTINUOUS_FRAMES_LOCK_EN     4
#घोषणा ATOMISP_CSS2_NUM_DVS_FRAME_DELAY     2

#घोषणा CSS_MIPI_FRAME_BUFFER_SIZE_1	0x60000
#घोषणा CSS_MIPI_FRAME_BUFFER_SIZE_2	0x80000

काष्ठा atomisp_device;
काष्ठा atomisp_sub_device;

#घोषणा MAX_STREAMS_PER_CHANNEL	2

/*
 * These are used to indicate the css stream state, corresponding
 * stream handling can be करोne via judging the dअगरferent state.
 */
क्रमागत atomisp_css_stream_state अणु
	CSS_STREAM_UNINIT,
	CSS_STREAM_CREATED,
	CSS_STREAM_STARTED,
	CSS_STREAM_STOPPED,
पूर्ण;

/*
 *  Sensor of बाह्यal ISP can send multiple steams with dअगरferent mipi data
 * type in the same भव channel. This inक्रमmation needs to come from the
 * sensor or बाह्यal ISP
 */
काष्ठा atomisp_css_isys_config_info अणु
	अचिन्हित पूर्णांक input_क्रमmat;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
पूर्ण;

काष्ठा atomisp_stream_env अणु
	काष्ठा ia_css_stream *stream;
	काष्ठा ia_css_stream_config stream_config;
	काष्ठा ia_css_stream_info stream_info;
	काष्ठा ia_css_pipe *pipes[IA_CSS_PIPE_ID_NUM];
	काष्ठा ia_css_pipe *multi_pipes[IA_CSS_PIPE_ID_NUM];
	काष्ठा ia_css_pipe_config pipe_configs[IA_CSS_PIPE_ID_NUM];
	काष्ठा ia_css_pipe_extra_config pipe_extra_configs[IA_CSS_PIPE_ID_NUM];
	bool update_pipe[IA_CSS_PIPE_ID_NUM];
	क्रमागत atomisp_css_stream_state stream_state;
	काष्ठा ia_css_stream *acc_stream;
	क्रमागत atomisp_css_stream_state acc_stream_state;
	काष्ठा ia_css_stream_config acc_stream_config;
	अचिन्हित पूर्णांक ch_id; /* भव channel ID */
	अचिन्हित पूर्णांक isys_configs;
	काष्ठा atomisp_css_isys_config_info isys_info[MAX_STREAMS_PER_CHANNEL];
पूर्ण;

काष्ठा atomisp_css_env अणु
	काष्ठा ia_css_env isp_css_env;
	काष्ठा ia_css_fw isp_css_fw;
पूर्ण;

काष्ठा atomisp_s3a_buf अणु
	काष्ठा ia_css_isp_3a_statistics *s3a_data;
	काष्ठा ia_css_isp_3a_statistics_map *s3a_map;
	काष्ठा list_head list;
पूर्ण;

काष्ठा atomisp_dis_buf अणु
	काष्ठा ia_css_isp_dvs_statistics *dis_data;
	काष्ठा ia_css_isp_dvs_statistics_map *dvs_map;
	काष्ठा list_head list;
पूर्ण;

काष्ठा atomisp_css_buffer अणु
	काष्ठा ia_css_buffer css_buffer;
पूर्ण;

काष्ठा atomisp_css_event अणु
	क्रमागत ia_css_pipe_id pipe;
	काष्ठा ia_css_event event;
पूर्ण;

व्योम atomisp_css_set_macc_config(काष्ठा atomisp_sub_device *asd,
				 काष्ठा ia_css_macc_config *macc_config);

व्योम atomisp_css_set_ecd_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_ecd_config *ecd_config);

व्योम atomisp_css_set_ynr_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_ynr_config *ynr_config);

व्योम atomisp_css_set_fc_config(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_fc_config *fc_config);

व्योम atomisp_css_set_aa_config(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_aa_config *aa_config);

व्योम atomisp_css_set_baa_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_aa_config *baa_config);

व्योम atomisp_css_set_anr_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_anr_config *anr_config);

व्योम atomisp_css_set_xnr_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_xnr_config *xnr_config);

व्योम atomisp_css_set_cnr_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_cnr_config *cnr_config);

व्योम atomisp_css_set_ctc_config(काष्ठा atomisp_sub_device *asd,
				काष्ठा ia_css_ctc_config *ctc_config);

व्योम atomisp_css_set_yuv2rgb_cc_config(काष्ठा atomisp_sub_device *asd,
				       काष्ठा ia_css_cc_config *yuv2rgb_cc_config);

व्योम atomisp_css_set_rgb2yuv_cc_config(काष्ठा atomisp_sub_device *asd,
				       काष्ठा ia_css_cc_config *rgb2yuv_cc_config);

व्योम atomisp_css_set_anr_thres(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_anr_thres *anr_thres);

पूर्णांक atomisp_css_load_firmware(काष्ठा atomisp_device *isp);

व्योम atomisp_css_set_dvs_6axis(काष्ठा atomisp_sub_device *asd,
			       काष्ठा ia_css_dvs_6axis_config *dvs_6axis);

पूर्णांक atomisp_css_debug_dump_isp_binary(व्योम);

पूर्णांक atomisp_css_dump_sp_raw_copy_linecount(bool reduced);

पूर्णांक atomisp_css_dump_blob_inक्रम(काष्ठा atomisp_device *isp);

व्योम atomisp_css_set_isp_config_id(काष्ठा atomisp_sub_device *asd,
				   uपूर्णांक32_t isp_config_id);

व्योम atomisp_css_set_isp_config_applied_frame(काष्ठा atomisp_sub_device *asd,
	काष्ठा ia_css_frame *output_frame);

पूर्णांक atomisp_get_css_dbgfunc(व्योम);

पूर्णांक atomisp_set_css_dbgfunc(काष्ठा atomisp_device *isp, पूर्णांक opt);
काष्ठा ia_css_dvs_grid_info *atomisp_css_get_dvs_grid_info(
    काष्ठा ia_css_grid_info *grid_info);
#पूर्ण_अगर
