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

#समावेश "ia_css_frame.h"
#समावेश "ia_css_types.h"
#समावेश "sh_css_defs.h"
#समावेश "ia_css_debug.h"
#समावेश "assert_support.h"
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"
#समावेश "isp.h"
#समावेश "isp/modes/interface/isp_types.h"

#समावेश "ia_css_raw.host.h"

अटल स्थिर काष्ठा ia_css_raw_configuration शेष_config = अणु
	.pipe = (काष्ठा sh_css_sp_pipeline *)शून्य,
पूर्ण;

अटल अंतरभूत अचिन्हित
sh_css_elems_bytes_from_info(अचिन्हित पूर्णांक raw_bit_depth)
अणु
	वापस CEIL_DIV(raw_bit_depth, 8);
पूर्ण

/* MW: These areMIPI / ISYS properties, not camera function properties */
अटल क्रमागत sh_stream_क्रमmat
css2isp_stream_क्रमmat(क्रमागत atomisp_input_क्रमmat from) अणु
	चयन (from)
	अणु
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
				वापस sh_stream_क्रमmat_yuv420_legacy;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
		वापस sh_stream_क्रमmat_yuv420;
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
		वापस sh_stream_क्रमmat_yuv422;
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
		वापस sh_stream_क्रमmat_rgb;
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
		वापस sh_stream_क्रमmat_raw;
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
	शेष:
		वापस sh_stream_क्रमmat_raw;
	पूर्ण
पूर्ण

व्योम
ia_css_raw_config(
    काष्ठा sh_css_isp_raw_isp_config *to,
    स्थिर काष्ठा ia_css_raw_configuration  *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक elems_a = ISP_VEC_NELEMS;
	स्थिर काष्ठा ia_css_frame_info *in_info = from->in_info;
	स्थिर काष्ठा ia_css_frame_info *पूर्णांकernal_info = from->पूर्णांकernal_info;

	(व्योम)size;
#अगर !defined(ISP2401)
	/* 2401 input प्रणाली uses input width width */
	in_info = पूर्णांकernal_info;
#अन्यथा
	/*in some हालs, in_info is शून्य*/
	अगर (in_info)
		(व्योम)पूर्णांकernal_info;
	अन्यथा
		in_info = पूर्णांकernal_info;

#पूर्ण_अगर
	ia_css_dma_configure_from_info(&to->port_b, in_info);

	/* Assume भागisiblity here, may need to generalize to fixed poपूर्णांक. */
	निश्चित((in_info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW_PACKED) ||
	       (elems_a % to->port_b.elems == 0));

	to->width_a_over_b      = elems_a / to->port_b.elems;
	to->inout_port_config   = from->pipe->inout_port_config;
	to->क्रमmat              = in_info->क्रमmat;
	to->required_bds_factor = from->pipe->required_bds_factor;
	to->two_ppc             = from->two_ppc;
	to->stream_क्रमmat       = css2isp_stream_क्रमmat(from->stream_क्रमmat);
	to->deपूर्णांकerleaved       = from->deपूर्णांकerleaved;
#अगर defined(ISP2401)
	to->start_column        = in_info->crop_info.start_column;
	to->start_line          = in_info->crop_info.start_line;
	to->enable_left_padding = from->enable_left_padding;
#पूर्ण_अगर
पूर्ण

व्योम
ia_css_raw_configure(
    स्थिर काष्ठा sh_css_sp_pipeline *pipe,
    स्थिर काष्ठा ia_css_binary      *binary,
    स्थिर काष्ठा ia_css_frame_info  *in_info,
    स्थिर काष्ठा ia_css_frame_info  *पूर्णांकernal_info,
    bool two_ppc,
    bool deपूर्णांकerleaved)
अणु
	u8 enable_left_padding = (uपूर्णांक8_t)((binary->left_padding) ? 1 : 0);
	काष्ठा ia_css_raw_configuration config = शेष_config;

	config.pipe                = pipe;
	config.in_info             = in_info;
	config.पूर्णांकernal_info       = पूर्णांकernal_info;
	config.two_ppc             = two_ppc;
	config.stream_क्रमmat       = binary->input_क्रमmat;
	config.deपूर्णांकerleaved       = deपूर्णांकerleaved;
	config.enable_left_padding = enable_left_padding;

	ia_css_configure_raw(binary, &config);
पूर्ण
