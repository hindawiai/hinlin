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

#अगर_अघोषित _SH_CSS_LEGACY_H_
#घोषणा _SH_CSS_LEGACY_H_

#समावेश <type_support.h>
#समावेश <ia_css_err.h>
#समावेश <ia_css_types.h>
#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_pipe_खुला.h>
#समावेश <ia_css_stream_खुला.h>

/* The pipe id type, distinguishes the kind of pipes that
 *  can be run in parallel.
 */
क्रमागत ia_css_pipe_id अणु
	IA_CSS_PIPE_ID_PREVIEW,
	IA_CSS_PIPE_ID_COPY,
	IA_CSS_PIPE_ID_VIDEO,
	IA_CSS_PIPE_ID_CAPTURE,
	IA_CSS_PIPE_ID_YUVPP,
	IA_CSS_PIPE_ID_ACC,
	IA_CSS_PIPE_ID_NUM
पूर्ण;

काष्ठा ia_css_pipe_extra_config अणु
	bool enable_raw_binning;
	bool enable_yuv_ds;
	bool enable_high_speed;
	bool enable_dvs_6axis;
	bool enable_reduced_pipe;
	bool enable_fractional_ds;
	bool disable_vf_pp;
पूर्ण;

पूर्णांक
ia_css_pipe_create_extra(स्थिर काष्ठा ia_css_pipe_config *config,
			 स्थिर काष्ठा ia_css_pipe_extra_config *extra_config,
			 काष्ठा ia_css_pipe **pipe);

व्योम
ia_css_pipe_extra_config_शेषs(काष्ठा ia_css_pipe_extra_config
				  *extra_config);

पूर्णांक
ia_css_temp_pipe_to_pipe_id(स्थिर काष्ठा ia_css_pipe *pipe,
			    क्रमागत ia_css_pipe_id *pipe_id);

/* DEPRECATED. FPN is not supported. */
पूर्णांक
sh_css_set_black_frame(काष्ठा ia_css_stream *stream,
		       स्थिर काष्ठा ia_css_frame *raw_black_frame);

/* ISP2400 */
व्योम
sh_css_enable_cont_capt(bool enable, bool stop_copy_preview);

#पूर्ण_अगर /* _SH_CSS_LEGACY_H_ */
