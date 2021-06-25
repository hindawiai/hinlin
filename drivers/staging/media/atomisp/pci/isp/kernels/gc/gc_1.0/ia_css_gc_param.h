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

#अगर_अघोषित __IA_CSS_GC_PARAM_H
#घोषणा __IA_CSS_GC_PARAM_H

#समावेश "type_support.h"
#अगर_अघोषित PIPE_GENERATION
#अगर_घोषित __ISP
#घोषणा __INLINE_VAMEM__
#पूर्ण_अगर
#समावेश "vamem.h"
#समावेश "ia_css_gc_types.h"

#अगर defined(IS_VAMEM_VERSION_1)
#घोषणा SH_CSS_ISP_GAMMA_TABLE_SIZE_LOG2 IA_CSS_VAMEM_1_GAMMA_TABLE_SIZE_LOG2
#घोषणा SH_CSS_ISP_GC_TABLE_SIZE	 IA_CSS_VAMEM_1_GAMMA_TABLE_SIZE
#या_अगर defined(IS_VAMEM_VERSION_2)
#घोषणा SH_CSS_ISP_GAMMA_TABLE_SIZE_LOG2 IA_CSS_VAMEM_2_GAMMA_TABLE_SIZE_LOG2
#घोषणा SH_CSS_ISP_GC_TABLE_SIZE	 IA_CSS_VAMEM_2_GAMMA_TABLE_SIZE
#अन्यथा
#त्रुटि "Undefined vamem version"
#पूर्ण_अगर

#अन्यथा
/* For pipe generation, the size is not relevant */
#घोषणा SH_CSS_ISP_GC_TABLE_SIZE 0
#पूर्ण_अगर

#घोषणा GAMMA_OUTPUT_BITS		8
#घोषणा GAMMA_OUTPUT_MAX_VAL		((1 << GAMMA_OUTPUT_BITS) - 1)

/* GC (Gamma Correction) */
काष्ठा sh_css_isp_gc_params अणु
	s32 gain_k1;
	s32 gain_k2;
पूर्ण;

/* CE (Chroma Enhancement) */
काष्ठा sh_css_isp_ce_params अणु
	s32 uv_level_min;
	s32 uv_level_max;
पूर्ण;

/* This should be vamem_data_t, but that अवरोधs the pipe generator */
काष्ठा sh_css_isp_gc_vamem_params अणु
	u16 gc[SH_CSS_ISP_GC_TABLE_SIZE];
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_GC_PARAM_H */
