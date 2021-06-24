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

#अगर_अघोषित __IA_CSS_CTC_PARAM_H
#घोषणा __IA_CSS_CTC_PARAM_H

#समावेश "type_support.h"
#समावेश <प्रणाली_global.h>

#समावेश "ia_css_ctc_types.h"

#अगर_अघोषित PIPE_GENERATION
#घोषणा SH_CSS_ISP_CTC_TABLE_SIZE_LOG2       IA_CSS_VAMEM_2_CTC_TABLE_SIZE_LOG2
#घोषणा SH_CSS_ISP_CTC_TABLE_SIZE            IA_CSS_VAMEM_2_CTC_TABLE_SIZE

#अन्यथा
/* For pipe generation, the size is not relevant */
#घोषणा SH_CSS_ISP_CTC_TABLE_SIZE 0
#पूर्ण_अगर

/* This should be vamem_data_t, but that अवरोधs the pipe generator */
काष्ठा sh_css_isp_ctc_vamem_params अणु
	u16 ctc[SH_CSS_ISP_CTC_TABLE_SIZE];
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_CTC_PARAM_H */
