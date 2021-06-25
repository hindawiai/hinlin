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

#अगर_अघोषित __ATOMISP_TPG_H__
#घोषणा __ATOMISP_TPG_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-subdev.h>

काष्ठा atomisp_tpg_device अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा atomisp_device *isp;
	काष्ठा media_pad pads[1];
पूर्ण;

व्योम atomisp_tpg_cleanup(काष्ठा atomisp_device *isp);
पूर्णांक atomisp_tpg_init(काष्ठा atomisp_device *isp);
व्योम atomisp_tpg_unरेजिस्टर_entities(काष्ठा atomisp_tpg_device *tpg);
पूर्णांक atomisp_tpg_रेजिस्टर_entities(काष्ठा atomisp_tpg_device *tpg,
				  काष्ठा v4l2_device *vdev);

#पूर्ण_अगर /* __ATOMISP_TPG_H__ */
