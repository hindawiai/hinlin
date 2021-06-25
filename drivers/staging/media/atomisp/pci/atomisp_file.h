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

#अगर_अघोषित __ATOMISP_खाता_H__
#घोषणा __ATOMISP_खाता_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>

काष्ठा atomisp_device;

काष्ठा atomisp_file_device अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा atomisp_device *isp;
	काष्ठा media_pad pads[1];

	काष्ठा workqueue_काष्ठा *work_queue;
	काष्ठा work_काष्ठा work;
पूर्ण;

व्योम atomisp_file_input_cleanup(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_file_input_init(काष्ठा atomisp_device *isp);
व्योम atomisp_file_input_unरेजिस्टर_entities(
    काष्ठा atomisp_file_device *file_dev);
पूर्णांक atomisp_file_input_रेजिस्टर_entities(काष्ठा atomisp_file_device *file_dev,
	काष्ठा v4l2_device *vdev);
#पूर्ण_अगर /* __ATOMISP_खाता_H__ */
