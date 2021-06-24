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

#अगर_अघोषित __IA_CSS_EED1_8_PARAM_H
#घोषणा __IA_CSS_EED1_8_PARAM_H

#समावेश "type_support.h"
#समावेश "vmem.h" /* needed क्रम VMEM_ARRAY */

#समावेश "ia_css_eed1_8_types.h" /* IA_CSS_NUMBER_OF_DEW_ENHANCE_SEGMENTS */

/* Configuration parameters: */

/* Enable median क्रम false color correction
 * 0: Do not use median
 * 1: Use median
 * Default: 1
 */
#घोषणा EED1_8_FC_ENABLE_MEDIAN		1

/* Coring Threshold minima
 * Used in Tपूर्णांक color suppression.
 * Default: 1
 */
#घोषणा EED1_8_CORINGTHMIN	1

/* Define size of the state..... TODO: check अगर this is the correct place */
/* 4 planes : GR, R, B, GB */
#घोषणा NUM_PLANES	4

/* 5 lines state per color plane input_line_state */
#घोषणा EED1_8_STATE_INPUT_BUFFER_HEIGHT	(5 * NUM_PLANES)

/* Each plane has width equal to half frame line */
#घोषणा EED1_8_STATE_INPUT_BUFFER_WIDTH	CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 1 line state per color plane LD_H state */
#घोषणा EED1_8_STATE_LD_H_HEIGHT	(1 * NUM_PLANES)
#घोषणा EED1_8_STATE_LD_H_WIDTH		CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 1 line state per color plane LD_V state */
#घोषणा EED1_8_STATE_LD_V_HEIGHT	(1 * NUM_PLANES)
#घोषणा EED1_8_STATE_LD_V_WIDTH		CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 1 line (single plane) state क्रम D_Hr state */
#घोषणा EED1_8_STATE_D_HR_HEIGHT	1
#घोषणा EED1_8_STATE_D_HR_WIDTH		CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 1 line (single plane) state क्रम D_Hb state */
#घोषणा EED1_8_STATE_D_HB_HEIGHT	1
#घोषणा EED1_8_STATE_D_HB_WIDTH		CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 2 lines (single plane) state क्रम D_Vr state */
#घोषणा EED1_8_STATE_D_VR_HEIGHT	2
#घोषणा EED1_8_STATE_D_VR_WIDTH		CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 2 line (single plane) state क्रम D_Vb state */
#घोषणा EED1_8_STATE_D_VB_HEIGHT	2
#घोषणा EED1_8_STATE_D_VB_WIDTH		CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 2 lines state क्रम R and B (= 2 planes) rb_zipped_state */
#घोषणा EED1_8_STATE_RB_ZIPPED_HEIGHT	(2 * 2)
#घोषणा EED1_8_STATE_RB_ZIPPED_WIDTH	CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

#अगर EED1_8_FC_ENABLE_MEDIAN
/* 1 full input line (GR-R color line) क्रम Yc state */
#घोषणा EED1_8_STATE_YC_HEIGHT	1
#घोषणा EED1_8_STATE_YC_WIDTH	MAX_FRAME_SIMDWIDTH

/* 1 line state per color plane Cg_state */
#घोषणा EED1_8_STATE_CG_HEIGHT	(1 * NUM_PLANES)
#घोषणा EED1_8_STATE_CG_WIDTH	CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 1 line state per color plane Co_state */
#घोषणा EED1_8_STATE_CO_HEIGHT	(1 * NUM_PLANES)
#घोषणा EED1_8_STATE_CO_WIDTH	CEIL_DIV(MAX_FRAME_SIMDWIDTH, 2)

/* 1 full input line (GR-R color line) क्रम AbsK state */
#घोषणा EED1_8_STATE_ABSK_HEIGHT	1
#घोषणा EED1_8_STATE_ABSK_WIDTH		MAX_FRAME_SIMDWIDTH
#पूर्ण_अगर

काष्ठा eed1_8_vmem_params अणु
	VMEM_ARRAY(e_dew_enh_x, ISP_VEC_NELEMS);
	VMEM_ARRAY(e_dew_enh_y, ISP_VEC_NELEMS);
	VMEM_ARRAY(e_dew_enh_a, ISP_VEC_NELEMS);
	VMEM_ARRAY(e_dew_enh_f, ISP_VEC_NELEMS);
	VMEM_ARRAY(chgrinv_x, ISP_VEC_NELEMS);
	VMEM_ARRAY(chgrinv_a, ISP_VEC_NELEMS);
	VMEM_ARRAY(chgrinv_b, ISP_VEC_NELEMS);
	VMEM_ARRAY(chgrinv_c, ISP_VEC_NELEMS);
	VMEM_ARRAY(fcinv_x, ISP_VEC_NELEMS);
	VMEM_ARRAY(fcinv_a, ISP_VEC_NELEMS);
	VMEM_ARRAY(fcinv_b, ISP_VEC_NELEMS);
	VMEM_ARRAY(fcinv_c, ISP_VEC_NELEMS);
	VMEM_ARRAY(tcinv_x, ISP_VEC_NELEMS);
	VMEM_ARRAY(tcinv_a, ISP_VEC_NELEMS);
	VMEM_ARRAY(tcinv_b, ISP_VEC_NELEMS);
	VMEM_ARRAY(tcinv_c, ISP_VEC_NELEMS);
पूर्ण;

/* EED (Edge Enhancing Demosaic) ISP parameters */
काष्ठा eed1_8_dmem_params अणु
	s32 rbzp_strength;

	s32 fcstrength;
	s32 fcthres_0;
	s32 fc_sat_coef;
	s32 fc_coring_prm;
	s32 fc_slope;

	s32 aerel_thres0;
	s32 aerel_gain0;
	s32 aerel_thres_dअगरf;
	s32 aerel_gain_dअगरf;

	s32 derel_thres0;
	s32 derel_gain0;
	s32 derel_thres_dअगरf;
	s32 derel_gain_dअगरf;

	s32 coring_pos0;
	s32 coring_pos_dअगरf;
	s32 coring_neg0;
	s32 coring_neg_dअगरf;

	s32 gain_exp;
	s32 gain_pos0;
	s32 gain_pos_dअगरf;
	s32 gain_neg0;
	s32 gain_neg_dअगरf;

	s32 margin_pos0;
	s32 margin_pos_dअगरf;
	s32 margin_neg0;
	s32 margin_neg_dअगरf;

	s32 e_dew_enh_asr;
	s32 dedgew_max;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_EED1_8_PARAM_H */
