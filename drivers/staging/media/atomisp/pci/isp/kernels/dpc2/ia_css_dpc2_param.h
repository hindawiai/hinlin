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

#अगर_अघोषित __IA_CSS_DPC2_PARAM_H
#घोषणा __IA_CSS_DPC2_PARAM_H

#समावेश "type_support.h"
#समावेश "vmem.h" /* क्रम VMEM_ARRAY*/

/* 4 planes : GR, R, B, GB */
#घोषणा NUM_PLANES		4

/* ToDo: Move this to testsetup */
#घोषणा MAX_FRAME_SIMDWIDTH	30

/* 3 lines state per color plane input_line_state */
#घोषणा DPC2_STATE_INPUT_BUFFER_HEIGHT	(3 * NUM_PLANES)
/* Each plane has width equal to half frame line */
#घोषणा DPC2_STATE_INPUT_BUFFER_WIDTH	CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 1 line state per color plane क्रम local deviation state*/
#घोषणा DPC2_STATE_LOCAL_DEVIATION_BUFFER_HEIGHT	(1 * NUM_PLANES)
/* Each plane has width equal to half frame line */
#घोषणा DPC2_STATE_LOCAL_DEVIATION_BUFFER_WIDTH		CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* MINMAX state buffer stores 1 full input line (GR-R color line) */
#घोषणा DPC2_STATE_SECOND_MINMAX_BUFFER_HEIGHT	1
#घोषणा DPC2_STATE_SECOND_MINMAX_BUFFER_WIDTH	MAX_FRAME_SIMDWIDTH

काष्ठा ia_css_isp_dpc2_params अणु
	s32 metric1;
	s32 metric2;
	s32 metric3;
	s32 wb_gain_gr;
	s32 wb_gain_r;
	s32 wb_gain_b;
	s32 wb_gain_gb;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_DPC2_PARAM_H */
