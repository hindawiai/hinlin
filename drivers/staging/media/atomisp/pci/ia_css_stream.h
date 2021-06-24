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

#अगर_अघोषित _IA_CSS_STREAM_H_
#घोषणा _IA_CSS_STREAM_H_

#समावेश <type_support.h>
#समावेश <प्रणाली_local.h>
#अगर !defined(ISP2401)
#समावेश <input_प्रणाली.h>
#पूर्ण_अगर
#समावेश "ia_css_types.h"
#समावेश "ia_css_stream_public.h"

/**
 * काष्ठाure to hold all पूर्णांकernal stream related inक्रमmation
 */
काष्ठा ia_css_stream अणु
	काष्ठा ia_css_stream_config    config;
	काष्ठा ia_css_stream_info      info;
#अगर !defined(ISP2401)
	rx_cfg_t                       csi_rx_config;
#पूर्ण_अगर
	bool                           reconfigure_css_rx;
	काष्ठा ia_css_pipe            *last_pipe;
	पूर्णांक                            num_pipes;
	काष्ठा ia_css_pipe           **pipes;
	काष्ठा ia_css_pipe            *continuous_pipe;
	काष्ठा ia_css_isp_parameters  *isp_params_configs;
	काष्ठा ia_css_isp_parameters  *per_frame_isp_params_configs;

	bool                           cont_capt;
	bool                           disable_cont_vf;

	/* ISP2401 */
	bool                           stop_copy_preview;
	bool                           started;
पूर्ण;

/* @brief Get a binary in the stream, which binary has the shading correction.
 *
 * @param[in] stream: The stream.
 * @वापस	The binary which has the shading correction.
 *
 */
काष्ठा ia_css_binary *
ia_css_stream_get_shading_correction_binary(स्थिर काष्ठा ia_css_stream *stream);

काष्ठा ia_css_binary *
ia_css_stream_get_dvs_binary(स्थिर काष्ठा ia_css_stream *stream);

काष्ठा ia_css_binary *
ia_css_stream_get_3a_binary(स्थिर काष्ठा ia_css_stream *stream);

अचिन्हित पूर्णांक
ia_css_stream_input_क्रमmat_bits_per_pixel(काष्ठा ia_css_stream *stream);

bool
sh_css_params_set_binning_factor(काष्ठा ia_css_stream *stream,
				 अचिन्हित पूर्णांक sensor_binning);

व्योम
sh_css_invalidate_params(काष्ठा ia_css_stream *stream);

/* The following functions are used क्रम testing purposes only */
स्थिर काष्ठा ia_css_fpn_table *
ia_css_get_fpn_table(काष्ठा ia_css_stream *stream);

/* @brief Get a poपूर्णांकer to the shading table.
 *
 * @param[in] stream: The stream.
 * @वापस	The poपूर्णांकer to the shading table.
 *
 */
काष्ठा ia_css_shading_table *
ia_css_get_shading_table(काष्ठा ia_css_stream *stream);

व्योम
ia_css_get_isp_dis_coefficients(काष्ठा ia_css_stream *stream,
				लघु *horizontal_coefficients,
				लघु *vertical_coefficients);

व्योम
ia_css_get_isp_dvs2_coefficients(काष्ठा ia_css_stream *stream,
				 लघु *hor_coefs_odd_real,
				 लघु *hor_coefs_odd_imag,
				 लघु *hor_coefs_even_real,
				 लघु *hor_coefs_even_imag,
				 लघु *ver_coefs_odd_real,
				 लघु *ver_coefs_odd_imag,
				 लघु *ver_coefs_even_real,
				 लघु *ver_coefs_even_imag);

पूर्णांक
ia_css_stream_isp_parameters_init(काष्ठा ia_css_stream *stream);

व्योम
ia_css_stream_isp_parameters_uninit(काष्ठा ia_css_stream *stream);

#पूर्ण_अगर /*_IA_CSS_STREAM_H_*/
