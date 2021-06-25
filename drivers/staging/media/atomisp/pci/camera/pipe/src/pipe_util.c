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

#समावेश "ia_css_pipe_util.h"
#समावेश "ia_css_frame_public.h"
#समावेश "ia_css_pipe.h"
#समावेश "ia_css_util.h"
#समावेश "assert_support.h"

अचिन्हित पूर्णांक ia_css_pipe_util_pipe_input_क्रमmat_bpp(
    स्थिर काष्ठा ia_css_pipe *स्थिर pipe)
अणु
	निश्चित(pipe);
	निश्चित(pipe->stream);

	वापस ia_css_util_input_क्रमmat_bpp(pipe->stream->config.input_config.क्रमmat,
					    pipe->stream->config.pixels_per_घड़ी == 2);
पूर्ण

व्योम ia_css_pipe_util_create_output_frames(
    काष्ठा ia_css_frame *frames[])
अणु
	अचिन्हित पूर्णांक i;

	निश्चित(frames);
	क्रम (i = 0; i < IA_CSS_BINARY_MAX_OUTPUT_PORTS; i++) अणु
		frames[i] = शून्य;
	पूर्ण
पूर्ण

व्योम ia_css_pipe_util_set_output_frames(
    काष्ठा ia_css_frame *frames[],
    अचिन्हित पूर्णांक idx,
    काष्ठा ia_css_frame *frame)
अणु
	निश्चित(idx < IA_CSS_BINARY_MAX_OUTPUT_PORTS);

	frames[idx] = frame;
पूर्ण
