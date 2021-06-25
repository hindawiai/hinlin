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

#अगर_अघोषित	__ATOMISP_IOCTL_H__
#घोषणा	__ATOMISP_IOCTL_H__

#समावेश "ia_css.h"

काष्ठा atomisp_device;
काष्ठा atomisp_video_pipe;

बाह्य स्थिर काष्ठा atomisp_क्रमmat_bridge atomisp_output_fmts[];

स्थिर काष्ठा
atomisp_क्रमmat_bridge *atomisp_get_क्रमmat_bridge(अचिन्हित पूर्णांक pixelक्रमmat);

स्थिर काष्ठा
atomisp_क्रमmat_bridge *atomisp_get_क्रमmat_bridge_from_mbus(u32 mbus_code);

पूर्णांक atomisp_alloc_css_stat_bufs(काष्ठा atomisp_sub_device *asd,
				uपूर्णांक16_t stream_id);

पूर्णांक __atomisp_streamoff(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type type);
पूर्णांक __atomisp_reqbufs(काष्ठा file *file, व्योम *fh,
		      काष्ठा v4l2_requestbuffers *req);

पूर्णांक atomisp_reqbufs(काष्ठा file *file, व्योम *fh,
		    काष्ठा v4l2_requestbuffers *req);

क्रमागत ia_css_pipe_id atomisp_get_css_pipe_id(काष्ठा atomisp_sub_device
	*asd);

व्योम atomisp_videobuf_मुक्त_buf(काष्ठा videobuf_buffer *vb);

बाह्य स्थिर काष्ठा v4l2_file_operations atomisp_file_fops;

बाह्य स्थिर काष्ठा v4l2_ioctl_ops atomisp_ioctl_ops;

बाह्य स्थिर काष्ठा v4l2_ioctl_ops atomisp_file_ioctl_ops;

अचिन्हित पूर्णांक atomisp_streaming_count(काष्ठा atomisp_device *isp);

अचिन्हित पूर्णांक atomisp_is_acc_enabled(काष्ठा atomisp_device *isp);
/* compat_ioctl क्रम 32bit userland app and 64bit kernel */
दीर्घ atomisp_compat_ioctl32(काष्ठा file *file,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

पूर्णांक atomisp_stream_on_master_slave_sensor(काष्ठा atomisp_device *isp,
	bool isp_समयout);
#पूर्ण_अगर /* __ATOMISP_IOCTL_H__ */
