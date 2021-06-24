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

#अगर_अघोषित __GDC_PUBLIC_H_INCLUDED__
#घोषणा __GDC_PUBLIC_H_INCLUDED__

/*! Write the bicubic पूर्णांकerpolation table of GDC[ID]

 \param	ID[in]				GDC identअगरier
 \param data[in]			The data matrix to be written

 \pre
	- data must poपूर्णांक to a matrix[4][HRT_GDC_N]

 \implementation dependent
	- The value of "HRT_GDC_N" is device specअगरic
	- The LUT should not be partially written
	- The LUT क्रमmat is a quadri-phase पूर्णांकerpolation
	  table. The layout is device specअगरic
	- The range of the values data[n][m] is device
	  specअगरic

 \लeturn none, GDC[ID].lut[0...3][0...HRT_GDC_N-1] = data
 */
व्योम gdc_lut_store(
    स्थिर gdc_ID_t		ID,
    स्थिर पूर्णांक			data[4][HRT_GDC_N]);

/*! Convert the bicubic पूर्णांकerpolation table of GDC[ID] to the ISP-specअगरic क्रमmat

 \param	ID[in]				GDC identअगरier
 \param in_lut[in]			The data matrix to be converted
 \param out_lut[out]			The data matrix as the output of conversion
 */
व्योम gdc_lut_convert_to_isp_क्रमmat(
    स्थिर पूर्णांक in_lut[4][HRT_GDC_N],
    पूर्णांक out_lut[4][HRT_GDC_N]);

/*! Return the पूर्णांकeger representation of 1.0 of GDC[ID]

 \param	ID[in]				GDC identअगरier

 \लeturn unity
 */
पूर्णांक gdc_get_unity(
    स्थिर gdc_ID_t		ID);

#पूर्ण_अगर /* __GDC_PUBLIC_H_INCLUDED__ */
