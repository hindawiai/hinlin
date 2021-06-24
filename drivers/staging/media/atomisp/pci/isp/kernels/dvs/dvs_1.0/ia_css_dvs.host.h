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

#अगर_अघोषित __IA_CSS_DVS_HOST_H
#घोषणा __IA_CSS_DVS_HOST_H

#समावेश "ia_css_frame_public.h"
#समावेश "ia_css_binary.h"
#समावेश "sh_css_params.h"

#समावेश "ia_css_types.h"
#समावेश "ia_css_dvs_types.h"
#समावेश "ia_css_dvs_param.h"

/* For bilinear पूर्णांकerpolation, we need to add +1 to input block height calculation.
 * For bicubic पूर्णांकerpolation, we will need to add +3 instaed */
#घोषणा DVS_GDC_BLI_INTERP_ENVELOPE 1
#घोषणा DVS_GDC_BCI_INTERP_ENVELOPE 3

व्योम
ia_css_dvs_config(
    काष्ठा sh_css_isp_dvs_isp_config      *to,
    स्थिर काष्ठा ia_css_dvs_configuration *from,
    अचिन्हित पूर्णांक size);

व्योम
ia_css_dvs_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *from);

व्योम
convert_dvs_6axis_config(
    काष्ठा ia_css_isp_parameters *params,
    स्थिर काष्ठा ia_css_binary *binary);

काष्ठा ia_css_host_data *
convert_allocate_dvs_6axis_config(
    स्थिर काष्ठा ia_css_dvs_6axis_config *dvs_6axis_config,
    स्थिर काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_frame_info *dvs_in_frame_info);

पूर्णांक
store_dvs_6axis_config(
    स्थिर काष्ठा ia_css_dvs_6axis_config *dvs_6axis_config,
    स्थिर काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_frame_info *dvs_in_frame_info,
    ia_css_ptr ddr_addr_y);

#पूर्ण_अगर /* __IA_CSS_DVS_HOST_H */
