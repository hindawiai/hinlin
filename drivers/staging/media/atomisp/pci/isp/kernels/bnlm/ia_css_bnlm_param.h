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

#अगर_अघोषित __IA_CSS_BNLM_PARAM_H
#घोषणा __IA_CSS_BNLM_PARAM_H

#समावेश "type_support.h"
#समावेश "vmem.h" /* needed क्रम VMEM_ARRAY */

काष्ठा bnlm_lut अणु
	VMEM_ARRAY(thr, ISP_VEC_NELEMS); /* thresholds */
	VMEM_ARRAY(val, ISP_VEC_NELEMS); /* values */
पूर्ण;

काष्ठा bnlm_vmem_params अणु
	VMEM_ARRAY(nl_th, ISP_VEC_NELEMS);
	VMEM_ARRAY(match_quality_max_idx, ISP_VEC_NELEMS);
	काष्ठा bnlm_lut mu_root_lut;
	काष्ठा bnlm_lut sad_norm_lut;
	काष्ठा bnlm_lut sig_detail_lut;
	काष्ठा bnlm_lut sig_rad_lut;
	काष्ठा bnlm_lut rad_घात_lut;
	काष्ठा bnlm_lut nl_0_lut;
	काष्ठा bnlm_lut nl_1_lut;
	काष्ठा bnlm_lut nl_2_lut;
	काष्ठा bnlm_lut nl_3_lut;

	/* LUTs used क्रम भागision approximiation */
	काष्ठा bnlm_lut भाग_lut;

	VMEM_ARRAY(भाग_lut_पूर्णांकercepts, ISP_VEC_NELEMS);

	/* 240x करोes not have an ISP inकाष्ठाion to left shअगरt each element of a
	 * vector by dअगरferent shअगरt value. Hence it will be simulated by multiplying
	 * the elements by required 2^shअगरt. */
	VMEM_ARRAY(घातer_of_2, ISP_VEC_NELEMS);
पूर्ण;

/* BNLM ISP parameters */
काष्ठा bnlm_dmem_params अणु
	bool rad_enable;
	s32 rad_x_origin;
	s32 rad_y_origin;
	s32 avg_min_th;
	s32 max_min_th;

	s32 exp_coeff_a;
	u32 exp_coeff_b;
	s32 exp_coeff_c;
	u32 exp_exponent;
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_BNLM_PARAM_H */
