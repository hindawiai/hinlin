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

#अगर_अघोषित __IA_CSS_GC2_PARAM_H
#घोषणा __IA_CSS_GC2_PARAM_H

#समावेश "type_support.h"
/* Extend GC1 */
#समावेश "ia_css_gc2_types.h"
#समावेश "gc/gc_1.0/ia_css_gc_param.h"
#समावेश "csc/csc_1.0/ia_css_csc_param.h"

#अगर_अघोषित PIPE_GENERATION
#अगर defined(IS_VAMEM_VERSION_1)
#घोषणा SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE IA_CSS_VAMEM_1_RGB_GAMMA_TABLE_SIZE
#या_अगर defined(IS_VAMEM_VERSION_2)
#घोषणा SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE IA_CSS_VAMEM_2_RGB_GAMMA_TABLE_SIZE
#अन्यथा
#त्रुटि "Undefined vamem version"
#पूर्ण_अगर

#अन्यथा
/* For pipe generation, the size is not relevant */
#घोषणा SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE 0
#पूर्ण_अगर

/* This should be vamem_data_t, but that अवरोधs the pipe generator */
काष्ठा sh_css_isp_rgb_gamma_vamem_params अणु
	u16 gc[SH_CSS_ISP_RGB_GAMMA_TABLE_SIZE];
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_GC2_PARAM_H */
