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

#अगर_अघोषित __IA_CSS_TNR_PARAM_H
#घोषणा __IA_CSS_TNR_PARAM_H

#समावेश "type_support.h"
#समावेश "sh_css_defs.h"
#समावेश "dma.h"

/* TNR (Temporal Noise Reduction) */
काष्ठा sh_css_isp_tnr_params अणु
	s32 coef;
	s32 threshold_Y;
	s32 threshold_C;
पूर्ण;

काष्ठा ia_css_tnr_configuration अणु
	स्थिर काष्ठा ia_css_frame *tnr_frames[NUM_TNR_FRAMES];
पूर्ण;

काष्ठा sh_css_isp_tnr_isp_config अणु
	u32 width_a_over_b;
	u32 frame_height;
	काष्ठा dma_port_config port_b;
	ia_css_ptr tnr_frame_addr[NUM_TNR_FRAMES];
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_TNR_PARAM_H */
