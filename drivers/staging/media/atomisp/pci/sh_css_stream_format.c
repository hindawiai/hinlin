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

#समावेश "sh_css_stream_format.h"
#समावेश <ia_css_stream_क्रमmat.h>

अचिन्हित पूर्णांक sh_css_stream_क्रमmat_2_bits_per_subpixel(
    क्रमागत atomisp_input_क्रमmat क्रमmat)
अणु
	अचिन्हित पूर्णांक rval;

	चयन (क्रमmat) अणु
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
		rval = 4;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
		rval = 5;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
		rval = 6;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
		rval = 7;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF1:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF2:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF3:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF4:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF5:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF6:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF7:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF8:
		rval = 8;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
		rval = 10;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
		rval = 12;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
		rval = 14;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
		rval = 16;
		अवरोध;
	शेष:
		rval = 0;
		अवरोध;
	पूर्ण

	वापस rval;
पूर्ण
