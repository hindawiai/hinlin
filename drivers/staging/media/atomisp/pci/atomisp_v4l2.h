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

#अगर_अघोषित __ATOMISP_V4L2_H__
#घोषणा __ATOMISP_V4L2_H__

काष्ठा atomisp_video_pipe;
काष्ठा atomisp_acc_pipe;
काष्ठा v4l2_device;
काष्ठा atomisp_device;
काष्ठा firmware;

पूर्णांक atomisp_video_init(काष्ठा atomisp_video_pipe *video, स्थिर अक्षर *name);
व्योम atomisp_acc_init(काष्ठा atomisp_acc_pipe *video, स्थिर अक्षर *name);
व्योम atomisp_video_unरेजिस्टर(काष्ठा atomisp_video_pipe *video);
व्योम atomisp_acc_unरेजिस्टर(काष्ठा atomisp_acc_pipe *video);
स्थिर काष्ठा firmware *atomisp_load_firmware(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_csi_lane_config(काष्ठा atomisp_device *isp);

#पूर्ण_अगर /* __ATOMISP_V4L2_H__ */
