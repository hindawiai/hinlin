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

#अगर_अघोषित __IA_CSS_VF_PARAM_H
#घोषणा __IA_CSS_VF_PARAM_H

#समावेश "type_support.h"
#समावेश "dma.h"
#समावेश "gc/gc_1.0/ia_css_gc_param.h" /* GAMMA_OUTPUT_BITS */
#समावेश "ia_css_frame_comm.h" /* ia_css_frame_sp_info */
#समावेश "ia_css_vf_types.h"

#घोषणा VFDEC_BITS_PER_PIXEL	GAMMA_OUTPUT_BITS

/* Viewfinder decimation */
काष्ठा sh_css_isp_vf_isp_config अणु
	u32 vf_करोwnscale_bits; /** Log VF करोwnscale value */
	u32 enable;
	काष्ठा ia_css_frame_sp_info info;
	काष्ठा अणु
		u32 width_a_over_b;
		काष्ठा dma_port_config port_b;
	पूर्ण dma;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_VF_PARAM_H */
