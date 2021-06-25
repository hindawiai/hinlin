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

#अगर_अघोषित __IA_CSS_OB_PARAM_H
#घोषणा __IA_CSS_OB_PARAM_H

#समावेश "type_support.h"
#समावेश "vmem.h"

#घोषणा OBAREA_MASK_SIZE 64
#घोषणा OBAREA_LENGTHBQ_INVERSE_SHIFT     12

/* AREA_LENGTH_UNIT is dependent on NWAY, requires reग_लिखो */
#घोषणा AREA_LENGTH_UNIT BIT(12)

/* OB (Optical Black) */
काष्ठा sh_css_isp_ob_stream_config अणु
	अचिन्हित पूर्णांक isp_pipe_version;
	अचिन्हित पूर्णांक raw_bit_depth;
पूर्ण;

काष्ठा sh_css_isp_ob_params अणु
	s32 blacklevel_gr;
	s32 blacklevel_r;
	s32 blacklevel_b;
	s32 blacklevel_gb;
	s32 area_start_bq;
	s32 area_length_bq;
	s32 area_length_bq_inverse;
पूर्ण;

काष्ठा sh_css_isp_ob_vmem_params अणु
	VMEM_ARRAY(vmask, OBAREA_MASK_SIZE);
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_OB_PARAM_H */
