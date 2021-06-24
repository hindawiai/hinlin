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

#अगर_अघोषित __IA_CSS_RAW_PARAM_H
#घोषणा __IA_CSS_RAW_PARAM_H

#समावेश "type_support.h"

#समावेश "dma.h"

/* Raw channel */
काष्ठा sh_css_isp_raw_isp_config अणु
	u32 width_a_over_b;
	काष्ठा dma_port_config port_b;
	u32 inout_port_config;
	u32 input_needs_raw_binning;
	u32 क्रमmat; /* क्रमागत ia_css_frame_क्रमmat */
	u32 required_bds_factor;
	u32 two_ppc;
	u32 stream_क्रमmat; /* क्रमागत sh_stream_क्रमmat */
	u32 deपूर्णांकerleaved;
	u32 start_column; /*left crop offset*/
	u32 start_line; /*top crop offset*/
	u8 enable_left_padding; /*need this क्रम multiple binary हाल*/
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_RAW_PARAM_H */
