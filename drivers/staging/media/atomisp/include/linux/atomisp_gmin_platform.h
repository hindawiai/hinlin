<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel MID SoC Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2014 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित ATOMISP_GMIN_PLATFORM_H_
#घोषणा ATOMISP_GMIN_PLATFORM_H_

#समावेश "atomisp_platform.h"

पूर्णांक atomisp_रेजिस्टर_i2c_module(काष्ठा v4l2_subdev *subdev,
				काष्ठा camera_sensor_platक्रमm_data *plat_data,
				क्रमागत पूर्णांकel_v4l2_subdev_type type);
काष्ठा v4l2_subdev *atomisp_gmin_find_subdev(काष्ठा i2c_adapter *adapter,
	काष्ठा i2c_board_info *board_info);
पूर्णांक atomisp_gmin_हटाओ_subdev(काष्ठा v4l2_subdev *sd);
पूर्णांक gmin_get_var_पूर्णांक(काष्ठा device *dev, bool is_gmin,
		     स्थिर अक्षर *var, पूर्णांक def);
पूर्णांक camera_sensor_csi(काष्ठा v4l2_subdev *sd, u32 port,
		      u32 lanes, u32 क्रमmat, u32 bayer_order, पूर्णांक flag);
काष्ठा camera_sensor_platक्रमm_data *
gmin_camera_platक्रमm_data(
    काष्ठा v4l2_subdev *subdev,
    क्रमागत atomisp_input_क्रमmat csi_क्रमmat,
    क्रमागत atomisp_bayer_order csi_bayer);

पूर्णांक atomisp_gmin_रेजिस्टर_vcm_control(काष्ठा camera_vcm_control *);

#पूर्ण_अगर
