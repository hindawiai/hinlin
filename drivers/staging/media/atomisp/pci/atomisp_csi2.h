<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
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
#अगर_अघोषित __ATOMISP_CSI2_H__
#घोषणा __ATOMISP_CSI2_H__

#समावेश <media/v4l2-subdev.h>
#समावेश <media/v4l2-ctrls.h>

#घोषणा CSI2_PAD_SINK		0
#घोषणा CSI2_PAD_SOURCE		1
#घोषणा CSI2_PADS_NUM		2

#घोषणा CSI2_OUTPUT_ISP_SUBDEV	BIT(0)
#घोषणा CSI2_OUTPUT_MEMORY	BIT(1)

काष्ठा atomisp_device;
काष्ठा v4l2_device;
काष्ठा atomisp_sub_device;

काष्ठा atomisp_mipi_csi2_device अणु
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[CSI2_PADS_NUM];
	काष्ठा v4l2_mbus_framefmt क्रमmats[CSI2_PADS_NUM];

	काष्ठा v4l2_ctrl_handler ctrls;
	काष्ठा atomisp_device *isp;

	u32 output; /* output direction */
पूर्ण;

पूर्णांक atomisp_csi2_set_ffmt(काष्ठा v4l2_subdev *sd,
			  काष्ठा v4l2_subdev_pad_config *cfg,
			  अचिन्हित पूर्णांक which, uपूर्णांक16_t pad,
			  काष्ठा v4l2_mbus_framefmt *ffmt);
पूर्णांक atomisp_mipi_csi2_init(काष्ठा atomisp_device *isp);
व्योम atomisp_mipi_csi2_cleanup(काष्ठा atomisp_device *isp);
व्योम atomisp_mipi_csi2_unरेजिस्टर_entities(
    काष्ठा atomisp_mipi_csi2_device *csi2);
पूर्णांक atomisp_mipi_csi2_रेजिस्टर_entities(काष्ठा atomisp_mipi_csi2_device *csi2,
					काष्ठा v4l2_device *vdev);

व्योम atomisp_csi2_configure(काष्ठा atomisp_sub_device *asd);

#पूर्ण_अगर /* __ATOMISP_CSI2_H__ */
