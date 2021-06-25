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

#अगर_अघोषित __SH_CSS_STRUCT_H
#घोषणा __SH_CSS_STRUCT_H

/* This header files contains the definition of the
   sh_css काष्ठा and मित्रs; locigally the file would
   probably be called sh_css.h after the pattern
   <type>.h but sh_css.h is the predecesssor of ia_css.h
   so this could cause confusion; hence the _काष्ठा
   in the filename
*/

#समावेश <type_support.h>
#समावेश <प्रणाली_local.h>
#समावेश "ia_css_pipeline.h"
#समावेश "ia_css_pipe_public.h"
#समावेश "ia_css_frame_public.h"
#समावेश "ia_css_queue.h"
#समावेश "ia_css_irq.h"

काष्ठा sh_css अणु
	काष्ठा ia_css_pipe            *active_pipes[IA_CSS_PIPELINE_NUM_MAX];
	/* All of the pipes created at any poपूर्णांक of समय. At this moment there can
	 * be no more than MAX_SP_THREADS of them because pipe_num is reused as SP
	 * thपढ़ो_id to which a pipe's pipeline is associated. At a later poपूर्णांक, अगर
	 * we support more pipe objects, we should add test code to test that
	 * possibility. Also, active_pipes[] should be able to hold only
	 * SH_CSS_MAX_SP_THREADS objects. Anything अन्यथा is misleading. */
	काष्ठा ia_css_pipe            *all_pipes[IA_CSS_PIPELINE_NUM_MAX];
	व्योम *(*दो_स्मृति)(माप_प्रकार bytes, bool zero_mem);
	व्योम (*मुक्त)(व्योम *ptr);
	व्योम (*flush)(काष्ठा ia_css_acc_fw *fw);

/* ISP2401 */
	व्योम *(*दो_स्मृति_ex)(माप_प्रकार bytes, bool zero_mem, स्थिर अक्षर *caller_func,
			   पूर्णांक caller_line);
	व्योम (*मुक्त_ex)(व्योम *ptr, स्थिर अक्षर *caller_func, पूर्णांक caller_line);

/* ISP2400 */
	bool stop_copy_preview;

	bool                           check_प्रणाली_idle;
	अचिन्हित पूर्णांक                   num_cont_raw_frames;
	अचिन्हित पूर्णांक                   num_mipi_frames[N_CSI_PORTS];
	काष्ठा ia_css_frame
		*mipi_frames[N_CSI_PORTS][NUM_MIPI_FRAMES_PER_STREAM];
	काष्ठा ia_css_metadata
		*mipi_metadata[N_CSI_PORTS][NUM_MIPI_FRAMES_PER_STREAM];
	अचिन्हित पूर्णांक
	mipi_sizes_क्रम_check[N_CSI_PORTS][IA_CSS_MIPI_SIZE_CHECK_MAX_NOF_ENTRIES_PER_PORT];
	अचिन्हित पूर्णांक                   mipi_frame_size[N_CSI_PORTS];
	ia_css_ptr                   sp_bin_addr;
	hrt_data                       page_table_base_index;

	अचिन्हित पूर्णांक
	size_mem_words; /* \deprecatedअणुUse ia_css_mipi_buffer_config instead.पूर्ण*/
	क्रमागत ia_css_irq_type           irq_type;
	अचिन्हित पूर्णांक                   pipe_counter;

	अचिन्हित पूर्णांक		type;	/* 2400 or 2401 क्रम now */
पूर्ण;

#घोषणा IPU_2400		1
#घोषणा IPU_2401		2

#घोषणा IS_2400()		(my_css.type == IPU_2400)
#घोषणा IS_2401()		(my_css.type == IPU_2401)

बाह्य काष्ठा sh_css my_css;

#पूर्ण_अगर /* __SH_CSS_STRUCT_H */
