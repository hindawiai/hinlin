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

#अगर_अघोषित __IA_CSS_DPC2_HOST_H
#घोषणा __IA_CSS_DPC2_HOST_H

#समावेश "ia_css_dpc2_types.h"
#समावेश "ia_css_dpc2_param.h"

व्योम
ia_css_dpc2_encode(
    काष्ठा ia_css_isp_dpc2_params *to,
    स्थिर काष्ठा ia_css_dpc2_config *from,
    माप_प्रकार size);

व्योम
ia_css_init_dpc2_state(
    व्योम *state,
    माप_प्रकार size);

#अगर_अघोषित IA_CSS_NO_DEBUG
व्योम
ia_css_dpc2_debug_dtrace(
    स्थिर काष्ठा ia_css_dpc2_config *config,
    अचिन्हित पूर्णांक level);
#पूर्ण_अगर

#पूर्ण_अगर /* __IA_CSS_DPC2_HOST_H */
