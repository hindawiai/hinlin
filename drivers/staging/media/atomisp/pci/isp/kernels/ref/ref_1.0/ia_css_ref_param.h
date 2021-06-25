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

#अगर_अघोषित __IA_CSS_REF_PARAM_H
#घोषणा __IA_CSS_REF_PARAM_H

#समावेश <type_support.h>
#समावेश "sh_css_defs.h"
#समावेश "dma.h"

/* Reference frame */
काष्ठा ia_css_ref_configuration अणु
	स्थिर काष्ठा ia_css_frame *ref_frames[MAX_NUM_VIDEO_DELAY_FRAMES];
	u32 dvs_frame_delay;
पूर्ण;

काष्ठा sh_css_isp_ref_isp_config अणु
	u32 width_a_over_b;
	काष्ठा dma_port_config port_b;
	ia_css_ptr ref_frame_addr_y[MAX_NUM_VIDEO_DELAY_FRAMES];
	ia_css_ptr ref_frame_addr_c[MAX_NUM_VIDEO_DELAY_FRAMES];
	u32 dvs_frame_delay;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_REF_PARAM_H */
