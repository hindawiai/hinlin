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

#अगर_अघोषित __SH_CSS_MIPI_H
#घोषणा __SH_CSS_MIPI_H

#समावेश <ia_css_err.h>		  /* ia_css_err */
#समावेश <ia_css_types.h>	  /* ia_css_pipe */
#समावेश <ia_css_stream_खुला.h> /* ia_css_stream_config */

व्योम
mipi_init(व्योम);

पूर्णांक
allocate_mipi_frames(काष्ठा ia_css_pipe *pipe, काष्ठा ia_css_stream_info *info);

पूर्णांक
मुक्त_mipi_frames(काष्ठा ia_css_pipe *pipe);

पूर्णांक
send_mipi_frames(काष्ठा ia_css_pipe *pipe);

/**
 * @brief Calculate the required MIPI buffer sizes.
 * Based on the stream configuration, calculate the
 * required MIPI buffer sizes (in DDR words).
 *
 * @param[in]	stream_cfg		Poपूर्णांक to the target stream configuration
 * @param[out]	size_mem_words	MIPI buffer size in DDR words.
 *
 * @वापस
 */
पूर्णांक
calculate_mipi_buff_size(
    काष्ठा ia_css_stream_config *stream_cfg,
    अचिन्हित पूर्णांक *size_mem_words);

#पूर्ण_अगर /* __SH_CSS_MIPI_H */
