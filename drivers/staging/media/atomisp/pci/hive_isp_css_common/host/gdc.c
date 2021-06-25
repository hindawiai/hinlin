<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
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

/* The name "gdc.h is already taken" */
#समावेश "gdc_device.h"

#समावेश "device_access.h"

#समावेश "assert_support.h"

/*
 * Local function declarations
 */
अटल अंतरभूत व्योम gdc_reg_store(
    स्थिर gdc_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value);

अटल अंतरभूत hrt_data gdc_reg_load(
    स्थिर gdc_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg);

#अगर_अघोषित __INLINE_GDC__
#समावेश "gdc_private.h"
#पूर्ण_अगर /* __INLINE_GDC__ */

/*
 * Exported function implementations
 */
व्योम gdc_lut_store(
    स्थिर gdc_ID_t		ID,
    स्थिर पूर्णांक			data[4][HRT_GDC_N])
अणु
	अचिन्हित पूर्णांक i, lut_offset = HRT_GDC_LUT_IDX;

	निश्चित(ID < N_GDC_ID);
	निश्चित(HRT_GDC_LUT_COEFF_OFFSET <= (4 * माप(hrt_data)));

	क्रम (i = 0; i < HRT_GDC_N; i++) अणु
		hrt_data	entry_0 = data[0][i] & HRT_GDC_BCI_COEF_MASK;
		hrt_data	entry_1 = data[1][i] & HRT_GDC_BCI_COEF_MASK;
		hrt_data	entry_2 = data[2][i] & HRT_GDC_BCI_COEF_MASK;
		hrt_data	entry_3 = data[3][i] & HRT_GDC_BCI_COEF_MASK;

		hrt_data	word_0 = entry_0 |
				     (entry_1 << HRT_GDC_LUT_COEFF_OFFSET);
		hrt_data	word_1 = entry_2 |
				     (entry_3 << HRT_GDC_LUT_COEFF_OFFSET);

		gdc_reg_store(ID, lut_offset++, word_0);
		gdc_reg_store(ID, lut_offset++, word_1);
	पूर्ण
	वापस;
पूर्ण

/*
 * Input LUT क्रमmat:
 * c0[0-1023], c1[0-1023], c2[0-1023] c3[0-1023]
 *
 * Output LUT क्रमmat (पूर्णांकerleaved):
 * c0[0], c1[0], c2[0], c3[0], c0[1], c1[1], c2[1], c3[1], ....
 * c0[1023], c1[1023], c2[1023], c3[1023]
 *
 * The first क्रमmat needs c0[0], c1[0] (which are 1024 words apart)
 * to program gdc LUT रेजिस्टरs. This makes it dअगरficult to करो piecemeal
 * पढ़ोs in SP side gdc_lut_store
 *
 * Interleaved क्रमmat allows use of contiguous bytes to store पूर्णांकo
 * gdc LUT रेजिस्टरs.
 *
 * See gdc_lut_store() definition in host/gdc.c vs sp/gdc_निजी.h
 *
 */
व्योम gdc_lut_convert_to_isp_क्रमmat(स्थिर पूर्णांक in_lut[4][HRT_GDC_N],
				   पूर्णांक out_lut[4][HRT_GDC_N])
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक *out = (पूर्णांक *)out_lut;

	क्रम (i = 0; i < HRT_GDC_N; i++) अणु
		out[0] = in_lut[0][i];
		out[1] = in_lut[1][i];
		out[2] = in_lut[2][i];
		out[3] = in_lut[3][i];
		out += 4;
	पूर्ण
पूर्ण

पूर्णांक gdc_get_unity(
    स्थिर gdc_ID_t		ID)
अणु
	निश्चित(ID < N_GDC_ID);
	(व्योम)ID;
	वापस (पूर्णांक)(1UL << HRT_GDC_FRAC_BITS);
पूर्ण

/*
 * Local function implementations
 */
अटल अंतरभूत व्योम gdc_reg_store(
    स्थिर gdc_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg,
    स्थिर hrt_data		value)
अणु
	ia_css_device_store_uपूर्णांक32(GDC_BASE[ID] + reg * माप(hrt_data), value);
	वापस;
पूर्ण

अटल अंतरभूत hrt_data gdc_reg_load(
    स्थिर gdc_ID_t		ID,
    स्थिर अचिन्हित पूर्णांक	reg)
अणु
	वापस ia_css_device_load_uपूर्णांक32(GDC_BASE[ID] + reg * माप(hrt_data));
पूर्ण
