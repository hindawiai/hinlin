<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "type_support.h"
#समावेश "ia_css_bnlm.host.h"

#अगर_अघोषित IA_CSS_NO_DEBUG
#समावेश "ia_css_debug.h" /* ia_css_debug_dtrace() */
#पूर्ण_अगर
#समावेश <निश्चित_support.h>

#घोषणा BNLM_DIV_LUT_SIZE	(12)
अटल स्थिर s32 भाग_lut_nearests[BNLM_DIV_LUT_SIZE] = अणु
	0, 454, 948, 1484, 2070, 2710, 3412, 4184, 5035, 5978, 7025, 8191
पूर्ण;

अटल स्थिर s32 भाग_lut_slopes[BNLM_DIV_LUT_SIZE] = अणु
	-7760, -6960, -6216, -5536, -4912, -4344, -3832, -3360, -2936, -2552, -2208, -2208
    पूर्ण;

अटल स्थिर s32 भाग_lut_पूर्णांकercepts[BNLM_DIV_LUT_SIZE] = अणु
	8184, 7752, 7336, 6928, 6536, 6152, 5776, 5416, 5064, 4728, 4408, 4408
पूर्ण;

/* Encodes a look-up table from BNLM खुला parameters to vmem parameters.
 * Input:
 *	lut	:	bnlm_lut काष्ठा containing encoded vmem parameters look-up table
 *	lut_thr	:	array containing threshold values क्रम lut
 *	lut_val	:	array containing output values related to lut_thr
 *	lut_size:	Size of lut_val array
 */
अटल अंतरभूत व्योम
bnlm_lut_encode(काष्ठा bnlm_lut *lut, स्थिर पूर्णांक32_t *lut_thr,
		स्थिर s32 *lut_val, स्थिर uपूर्णांक32_t lut_size)
अणु
	u32 blk, i;
	स्थिर u32 block_size = 16;
	स्थिर u32 total_blocks = ISP_VEC_NELEMS / block_size;

	/* Create VMEM LUTs from the threshold and value arrays.
	 *
	 * Min size of the LUT is 2 entries.
	 *
	 * Max size of the LUT is 16 entries, so that the LUT can fit पूर्णांकo a
	 * single group of 16 elements inside a vector.
	 * Then these elements are copied पूर्णांकo other groups inside the same
	 * vector. If the LUT size is less than 16, then reमुख्यing elements are
	 * set to 0.
	 */
	निश्चित((lut_size >= 2) && (lut_size <= block_size));
	/* array lut_thr has (lut_size-1) entries */
	क्रम (i = 0; i < lut_size - 2; i++) अणु
		/* Check अगर the lut_thr is monotonically increasing */
		निश्चित(lut_thr[i] <= lut_thr[i + 1]);
	पूर्ण

	/* Initialize */
	क्रम (i = 0; i < total_blocks * block_size; i++) अणु
		lut->thr[0][i] = 0;
		lut->val[0][i] = 0;
	पूर्ण

	/* Copy all data */
	क्रम (i = 0; i < lut_size - 1; i++) अणु
		lut->thr[0][i] = lut_thr[i];
		lut->val[0][i] = lut_val[i];
	पूर्ण
	lut->val[0][i] = lut_val[i]; /* val has one more element than thr */

	/* Copy data from first block to all blocks */
	क्रम (blk = 1; blk < total_blocks; blk++) अणु
		u32 blk_offset = blk * block_size;

		क्रम (i = 1; i < lut_size; i++) अणु
			lut->thr[0][blk_offset + i] = lut->thr[0][i];
			lut->val[0][blk_offset + i] = lut->val[0][i];
		पूर्ण
	पूर्ण
पूर्ण

/*
 * - Encodes BNLM खुला parameters पूर्णांकo VMEM parameters
 * - Generates VMEM parameters which will needed पूर्णांकernally ISP
 */
व्योम
ia_css_bnlm_vmem_encode(
    काष्ठा bnlm_vmem_params *to,
    स्थिर काष्ठा ia_css_bnlm_config *from,
    माप_प्रकार size)
अणु
	पूर्णांक i;
	(व्योम)size;

	/* Initialize LUTs in VMEM parameters */
	bnlm_lut_encode(&to->mu_root_lut, from->mu_root_lut_thr, from->mu_root_lut_val,
			16);
	bnlm_lut_encode(&to->sad_norm_lut, from->sad_norm_lut_thr,
			from->sad_norm_lut_val, 16);
	bnlm_lut_encode(&to->sig_detail_lut, from->sig_detail_lut_thr,
			from->sig_detail_lut_val, 16);
	bnlm_lut_encode(&to->sig_rad_lut, from->sig_rad_lut_thr, from->sig_rad_lut_val,
			16);
	bnlm_lut_encode(&to->rad_घात_lut, from->rad_घात_lut_thr, from->rad_घात_lut_val,
			16);
	bnlm_lut_encode(&to->nl_0_lut, from->nl_0_lut_thr, from->nl_0_lut_val, 16);
	bnlm_lut_encode(&to->nl_1_lut, from->nl_1_lut_thr, from->nl_1_lut_val, 16);
	bnlm_lut_encode(&to->nl_2_lut, from->nl_2_lut_thr, from->nl_2_lut_val, 16);
	bnlm_lut_encode(&to->nl_3_lut, from->nl_3_lut_thr, from->nl_3_lut_val, 16);

	/* Initialize arrays in VMEM parameters */
	स_रखो(to->nl_th, 0, माप(to->nl_th));
	to->nl_th[0][0] = from->nl_th[0];
	to->nl_th[0][1] = from->nl_th[1];
	to->nl_th[0][2] = from->nl_th[2];

	स_रखो(to->match_quality_max_idx, 0, माप(to->match_quality_max_idx));
	to->match_quality_max_idx[0][0] = from->match_quality_max_idx[0];
	to->match_quality_max_idx[0][1] = from->match_quality_max_idx[1];
	to->match_quality_max_idx[0][2] = from->match_quality_max_idx[2];
	to->match_quality_max_idx[0][3] = from->match_quality_max_idx[3];

	bnlm_lut_encode(&to->भाग_lut, भाग_lut_nearests, भाग_lut_slopes,
			BNLM_DIV_LUT_SIZE);
	स_रखो(to->भाग_lut_पूर्णांकercepts, 0, माप(to->भाग_lut_पूर्णांकercepts));
	क्रम (i = 0; i < BNLM_DIV_LUT_SIZE; i++) अणु
		to->भाग_lut_पूर्णांकercepts[0][i] = भाग_lut_पूर्णांकercepts[i];
	पूर्ण

	स_रखो(to->घातer_of_2, 0, माप(to->घातer_of_2));
	क्रम (i = 0; i < (ISP_VEC_ELEMBITS - 1); i++) अणु
		to->घातer_of_2[0][i] = 1 << i;
	पूर्ण
पूर्ण

/* - Encodes BNLM खुला parameters पूर्णांकo DMEM parameters */
व्योम
ia_css_bnlm_encode(
    काष्ठा bnlm_dmem_params *to,
    स्थिर काष्ठा ia_css_bnlm_config *from,
    माप_प्रकार size)
अणु
	(व्योम)size;
	to->rad_enable = from->rad_enable;
	to->rad_x_origin = from->rad_x_origin;
	to->rad_y_origin = from->rad_y_origin;
	to->avg_min_th = from->avg_min_th;
	to->max_min_th = from->max_min_th;

	to->exp_coeff_a = from->exp_coeff_a;
	to->exp_coeff_b = from->exp_coeff_b;
	to->exp_coeff_c = from->exp_coeff_c;
	to->exp_exponent = from->exp_exponent;
पूर्ण

/* Prपूर्णांकs debug traces क्रम BNLM खुला parameters */
व्योम
ia_css_bnlm_debug_trace(
    स्थिर काष्ठा ia_css_bnlm_config *config,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!config)
		वापस;

#अगर_अघोषित IA_CSS_NO_DEBUG
	ia_css_debug_dtrace(level, "BNLM:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "rad_enable", config->rad_enable);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "rad_x_origin",
			    config->rad_x_origin);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "rad_y_origin",
			    config->rad_y_origin);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "avg_min_th", config->avg_min_th);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "max_min_th", config->max_min_th);

	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "exp_coeff_a",
			    config->exp_coeff_a);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "exp_coeff_b",
			    config->exp_coeff_b);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "exp_coeff_c",
			    config->exp_coeff_c);
	ia_css_debug_dtrace(level, "\t%-32s = %d\n", "exp_exponent",
			    config->exp_exponent);

	/* ToDo: prपूर्णांक traces क्रम LUTs */
#पूर्ण_अगर /* IA_CSS_NO_DEBUG */
पूर्ण
