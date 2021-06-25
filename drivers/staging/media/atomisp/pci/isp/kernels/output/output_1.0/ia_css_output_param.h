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

#अगर_अघोषित __IA_CSS_OUTPUT_PARAM_H
#घोषणा __IA_CSS_OUTPUT_PARAM_H

#समावेश <type_support.h>
#समावेश "dma.h"
#समावेश "ia_css_frame_comm.h" /* ia_css_frame_sp_info */

/* output frame */
काष्ठा sh_css_isp_output_isp_config अणु
	u32 width_a_over_b;
	u32 height;
	u32 enable;
	काष्ठा ia_css_frame_sp_info info;
	काष्ठा dma_port_config port_b;
पूर्ण;

काष्ठा sh_css_isp_output_params अणु
	u8 enable_hflip;
	u8 enable_vflip;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_OUTPUT_PARAM_H */
