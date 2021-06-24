<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित _IA_CSS_ISP_PARAM_TYPES_H_
#घोषणा _IA_CSS_ISP_PARAM_TYPES_H_

#समावेश "ia_css_types.h"
#समावेश <platक्रमm_support.h>
#समावेश <प्रणाली_global.h>

/* Short hands */
#घोषणा IA_CSS_ISP_DMEM IA_CSS_ISP_DMEM0
#घोषणा IA_CSS_ISP_VMEM IA_CSS_ISP_VMEM0

/* The driver depends on this, to be हटाओd later. */
#घोषणा IA_CSS_NUM_ISP_MEMORIES IA_CSS_NUM_MEMORIES

/* Explicit member numbering to aव्योम fish type checker bug */
क्रमागत ia_css_param_class अणु
	IA_CSS_PARAM_CLASS_PARAM  = 0,	/* Late binding parameters, like 3A */
	IA_CSS_PARAM_CLASS_CONFIG = 1,	/* Pipe config समय parameters, like resolution */
	IA_CSS_PARAM_CLASS_STATE  = 2,  /* State parameters, like tnr buffer index */
#अगर 0 /* Not yet implemented */
	IA_CSS_PARAM_CLASS_FRAME  = 3,  /* Frame समय parameters, like output buffer */
#पूर्ण_अगर
पूर्ण;

#घोषणा IA_CSS_NUM_PARAM_CLASSES (IA_CSS_PARAM_CLASS_STATE + 1)

/* ISP parameter descriptor */
काष्ठा ia_css_isp_parameter अणु
	u32 offset; /* Offset in isp_<mem>)parameters, etc. */
	u32 size;   /* Disabled अगर 0 */
पूर्ण;

/* Address/size of each parameter class in each isp memory, host memory poपूर्णांकers */
काष्ठा ia_css_isp_param_host_segments अणु
	काष्ठा ia_css_host_data params[IA_CSS_NUM_PARAM_CLASSES][IA_CSS_NUM_MEMORIES];
पूर्ण;

/* Address/size of each parameter class in each isp memory, css memory poपूर्णांकers */
काष्ठा ia_css_isp_param_css_segments अणु
	काष्ठा ia_css_data      params[IA_CSS_NUM_PARAM_CLASSES][IA_CSS_NUM_MEMORIES];
पूर्ण;

/* Address/size of each parameter class in each isp memory, isp memory poपूर्णांकers */
काष्ठा ia_css_isp_param_isp_segments अणु
	काष्ठा ia_css_isp_data  params[IA_CSS_NUM_PARAM_CLASSES][IA_CSS_NUM_MEMORIES];
पूर्ण;

/* Memory offsets in binary info */
काष्ठा ia_css_isp_param_memory_offsets अणु
	u32 offsets[IA_CSS_NUM_PARAM_CLASSES];  /** offset wrt hdr in bytes */
पूर्ण;

/* Offsets क्रम ISP kernel parameters per isp memory.
 * Only relevant क्रम standard ISP binaries, not ACC or SP.
 */
जोड़ ia_css_all_memory_offsets अणु
	काष्ठा अणु
		CSS_ALIGN(काष्ठा ia_css_memory_offsets	      *param, 8);
		CSS_ALIGN(काष्ठा ia_css_config_memory_offsets *config, 8);
		CSS_ALIGN(काष्ठा ia_css_state_memory_offsets  *state, 8);
	पूर्ण offsets;
	काष्ठा अणु
		CSS_ALIGN(व्योम *ptr, 8);
	पूर्ण array[IA_CSS_NUM_PARAM_CLASSES];
पूर्ण;

#पूर्ण_अगर /* _IA_CSS_ISP_PARAM_TYPES_H_ */
