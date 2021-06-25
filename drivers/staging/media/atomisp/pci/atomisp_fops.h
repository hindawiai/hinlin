<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित	__ATOMISP_FOPS_H__
#घोषणा	__ATOMISP_FOPS_H__
#समावेश "atomisp_subdev.h"

पूर्णांक atomisp_q_video_buffers_to_css(काष्ठा atomisp_sub_device *asd,
				   काष्ठा atomisp_video_pipe *pipe,
				   क्रमागत atomisp_input_stream_id stream_id,
				   क्रमागत ia_css_buffer_type css_buf_type,
				   क्रमागत ia_css_pipe_id css_pipe_id);

अचिन्हित पूर्णांक atomisp_dev_users(काष्ठा atomisp_device *isp);
अचिन्हित पूर्णांक atomisp_sub_dev_users(काष्ठा atomisp_sub_device *asd);

/*
 * Memory help functions क्रम image frame and निजी parameters
 */

पूर्णांक atomisp_videobuf_mmap_mapper(काष्ठा videobuf_queue *q,
				 काष्ठा vm_area_काष्ठा *vma);

पूर्णांक atomisp_qbuf_to_css(काष्ठा atomisp_device *isp,
			काष्ठा atomisp_video_pipe *pipe,
			काष्ठा videobuf_buffer *vb);

पूर्णांक atomisp_qbuffers_to_css(काष्ठा atomisp_sub_device *asd);

बाह्य स्थिर काष्ठा v4l2_file_operations atomisp_fops;

बाह्य bool defer_fw_load;

#पूर्ण_अगर /* __ATOMISP_FOPS_H__ */
