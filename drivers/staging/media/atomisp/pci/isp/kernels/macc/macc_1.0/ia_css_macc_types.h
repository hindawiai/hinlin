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

#अगर_अघोषित __IA_CSS_MACC_TYPES_H
#घोषणा __IA_CSS_MACC_TYPES_H

/* @file
* CSS-API header file क्रम Multi-Axis Color Correction (MACC) parameters.
*/

/* Number of axes in the MACC table. */
#घोषणा IA_CSS_MACC_NUM_AXES           16
/* Number of coefficients per MACC axes. */
#घोषणा IA_CSS_MACC_NUM_COEFS          4
/* The number of planes in the morphing table. */

/* Multi-Axis Color Correction (MACC) table.
 *
 *  ISP block: MACC1 (MACC by only matrix)
 *             MACC2 (MACC by matrix and exponent(ia_css_macc_config))
 *  ISP1: MACC1 is used.
 *  ISP2: MACC2 is used.
 *
 *  [MACC1]
 *   OutU = (data00 * InU + data01 * InV) >> 13
 *   OutV = (data10 * InU + data11 * InV) >> 13
 *
 *   शेष/ineffective:
 *   OutU = (8192 * InU +    0 * InV) >> 13
 *   OutV = (   0 * InU + 8192 * InV) >> 13
 *
 *  [MACC2]
 *   OutU = (data00 * InU + data01 * InV) >> (13 - exp)
 *   OutV = (data10 * InU + data11 * InV) >> (13 - exp)
 *
 *   शेष/ineffective: (exp=1)
 *   OutU = (4096 * InU +    0 * InV) >> (13 - 1)
 *   OutV = (   0 * InU + 4096 * InV) >> (13 - 1)
 */

काष्ठा ia_css_macc_table अणु
	s16 data[IA_CSS_MACC_NUM_COEFS * IA_CSS_MACC_NUM_AXES];
	/** 16 of 2x2 matix
	  MACC1: s2.13, [-65536,65535]
	    शेष/ineffective:
		16 of "identity 2x2 matix" अणु8192,0,0,8192पूर्ण
	  MACC2: s[macc_config.exp].[13-macc_config.exp], [-8192,8191]
	    शेष/ineffective: (s1.12)
		16 of "identity 2x2 matix" अणु4096,0,0,4096पूर्ण */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_MACC_TYPES_H */
