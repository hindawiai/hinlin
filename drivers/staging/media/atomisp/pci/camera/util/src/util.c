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

#समावेश "ia_css_util.h"
#समावेश <ia_css_frame.h>
#समावेश <निश्चित_support.h>
#समावेश <math_support.h>

/* क्रम ia_css_binary_max_vf_width() */
#समावेश "ia_css_binary.h"

/* MW: Table look-up ??? */
अचिन्हित पूर्णांक ia_css_util_input_क्रमmat_bpp(
    क्रमागत atomisp_input_क्रमmat क्रमmat,
    bool two_ppc)
अणु
	अचिन्हित पूर्णांक rval = 0;

	चयन (क्रमmat) अणु
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
	हाल ATOMISP_INPUT_FORMAT_EMBEDDED:
		rval = 8;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
		rval = 10;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
		rval = 16;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
		rval = 4;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
		rval = 5;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
		rval = 65;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
		rval = 6;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
		rval = 7;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
		rval = 12;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
		अगर (two_ppc)
			rval = 14;
		अन्यथा
			rval = 12;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
		अगर (two_ppc)
			rval = 16;
		अन्यथा
			rval = 12;
		अवरोध;
	शेष:
		rval = 0;
		अवरोध;
	पूर्ण
	वापस rval;
पूर्ण

पूर्णांक ia_css_util_check_vf_info(
    स्थिर काष्ठा ia_css_frame_info *स्थिर info)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक max_vf_width;

	निश्चित(info);
	err = ia_css_frame_check_info(info);
	अगर (err)
		वापस err;
	max_vf_width = ia_css_binary_max_vf_width();
	अगर (max_vf_width != 0 && info->res.width > max_vf_width * 2)
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक ia_css_util_check_vf_out_info(
    स्थिर काष्ठा ia_css_frame_info *स्थिर out_info,
    स्थिर काष्ठा ia_css_frame_info *स्थिर vf_info)
अणु
	पूर्णांक err;

	निश्चित(out_info);
	निश्चित(vf_info);

	err = ia_css_frame_check_info(out_info);
	अगर (err)
		वापस err;
	err = ia_css_util_check_vf_info(vf_info);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

पूर्णांक ia_css_util_check_res(अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	/* height can be odd number क्रम jpeg/embedded data from ISYS2401 */
	अगर (((width  == 0)   ||
	     (height == 0)   ||
	     IS_ODD(width))) अणु
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* ISP2401 */
bool ia_css_util_res_leq(काष्ठा ia_css_resolution a, काष्ठा ia_css_resolution b)
अणु
	वापस a.width <= b.width && a.height <= b.height;
पूर्ण

/* ISP2401 */
bool ia_css_util_resolution_is_zero(स्थिर काष्ठा ia_css_resolution resolution)
अणु
	वापस (resolution.width == 0) || (resolution.height == 0);
पूर्ण

/* ISP2401 */
bool ia_css_util_resolution_is_even(स्थिर काष्ठा ia_css_resolution resolution)
अणु
	वापस IS_EVEN(resolution.height) && IS_EVEN(resolution.width);
पूर्ण

bool ia_css_util_is_input_क्रमmat_raw(क्रमागत atomisp_input_क्रमmat क्रमmat)
अणु
	वापस ((क्रमmat == ATOMISP_INPUT_FORMAT_RAW_6) ||
		(क्रमmat == ATOMISP_INPUT_FORMAT_RAW_7) ||
		(क्रमmat == ATOMISP_INPUT_FORMAT_RAW_8) ||
		(क्रमmat == ATOMISP_INPUT_FORMAT_RAW_10) ||
		(क्रमmat == ATOMISP_INPUT_FORMAT_RAW_12));
	/* raw_14 and raw_16 are not supported as input क्रमmats to the ISP.
	 * They can only be copied to a frame in memory using the
	 * copy binary.
	 */
पूर्ण

bool ia_css_util_is_input_क्रमmat_yuv(क्रमागत atomisp_input_क्रमmat क्रमmat)
अणु
	वापस क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY ||
	       क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8  ||
	       क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_10 ||
	       क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_16 ||
	       क्रमmat == ATOMISP_INPUT_FORMAT_YUV422_8  ||
	       क्रमmat == ATOMISP_INPUT_FORMAT_YUV422_10 ||
	       क्रमmat == ATOMISP_INPUT_FORMAT_YUV422_16;
पूर्ण

पूर्णांक ia_css_util_check_input(
    स्थिर काष्ठा ia_css_stream_config *स्थिर stream_config,
    bool must_be_raw,
    bool must_be_yuv)
अणु
	निश्चित(stream_config);

	अगर (!stream_config)
		वापस -EINVAL;

	अगर (stream_config->input_config.effective_res.width == 0 ||
	    stream_config->input_config.effective_res.height == 0)
		वापस -EINVAL;
	अगर (must_be_raw &&
	    !ia_css_util_is_input_क्रमmat_raw(stream_config->input_config.क्रमmat))
		वापस -EINVAL;

	अगर (must_be_yuv &&
	    !ia_css_util_is_input_क्रमmat_yuv(stream_config->input_config.क्रमmat))
		वापस -EINVAL;

	वापस 0;
पूर्ण
