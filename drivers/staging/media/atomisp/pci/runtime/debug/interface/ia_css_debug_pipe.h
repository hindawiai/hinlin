<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
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

#अगर_अघोषित _IA_CSS_DEBUG_PIPE_H_
#घोषणा _IA_CSS_DEBUG_PIPE_H_

/*! \पile */

#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_stream_खुला.h>
#समावेश "ia_css_pipeline.h"

/**
 * @brief Internal debug support क्रम स्थिरructing a pipe graph.
 *
 * @वापस	None
 */
व्योम ia_css_debug_pipe_graph_dump_prologue(व्योम);

/**
 * @brief Internal debug support क्रम स्थिरructing a pipe graph.
 *
 * @वापस	None
 */
व्योम ia_css_debug_pipe_graph_dump_epilogue(व्योम);

/**
 * @brief Internal debug support क्रम स्थिरructing a pipe graph.
 * @param[in]	stage		Pipeline stage.
 * @param[in]	id		Pipe id.
 *
 * @वापस	None
 */
व्योम ia_css_debug_pipe_graph_dump_stage(
    काष्ठा ia_css_pipeline_stage *stage,
    क्रमागत ia_css_pipe_id id);

/**
 * @brief Internal debug support क्रम स्थिरructing a pipe graph.
 * @param[in]	out_frame	Output frame of SP raw copy.
 *
 * @वापस	None
 */
व्योम ia_css_debug_pipe_graph_dump_sp_raw_copy(
    काष्ठा ia_css_frame *out_frame);

/**
 * @brief Internal debug support क्रम स्थिरructing a pipe graph.
 * @param[in]	stream_config	info about sensor and input क्रमmatter.
 *
 * @वापस	None
 */
व्योम ia_css_debug_pipe_graph_dump_stream_config(
    स्थिर काष्ठा ia_css_stream_config *stream_config);

#पूर्ण_अगर /* _IA_CSS_DEBUG_PIPE_H_ */
