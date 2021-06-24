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

#अगर_अघोषित __IA_CSS_PIPE_UTIL_H__
#घोषणा __IA_CSS_PIPE_UTIL_H__

#समावेश <ia_css_types.h>
#समावेश <ia_css_frame_खुला.h>

/* @brief Get Input क्रमmat bits per pixel based on stream configuration of this
 * pipe.
 *
 * @param[in] pipe
 * @वापस   bits per pixel क्रम the underlying stream
 *
 */
अचिन्हित पूर्णांक ia_css_pipe_util_pipe_input_क्रमmat_bpp(
    स्थिर काष्ठा ia_css_pipe *स्थिर pipe);

व्योम ia_css_pipe_util_create_output_frames(
    काष्ठा ia_css_frame *frames[]);

व्योम ia_css_pipe_util_set_output_frames(
    काष्ठा ia_css_frame *frames[],
    अचिन्हित पूर्णांक idx,
    काष्ठा ia_css_frame *frame);

#पूर्ण_अगर /* __IA_CSS_PIPE_UTIL_H__ */
