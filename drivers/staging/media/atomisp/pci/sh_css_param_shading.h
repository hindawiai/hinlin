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

#अगर_अघोषित __SH_CSS_PARAMS_SHADING_H
#घोषणा __SH_CSS_PARAMS_SHADING_H

#समावेश <ia_css_types.h>
#समावेश <ia_css_binary.h>

व्योम
sh_css_params_shading_id_table_generate(
    काष्ठा ia_css_shading_table **target_table,
    अचिन्हित पूर्णांक table_width,
    अचिन्हित पूर्णांक table_height);

व्योम
prepare_shading_table(स्थिर काष्ठा ia_css_shading_table *in_table,
		      अचिन्हित पूर्णांक sensor_binning,
		      काष्ठा ia_css_shading_table **target_table,
		      स्थिर काष्ठा ia_css_binary *binary,
		      अचिन्हित पूर्णांक bds_factor);

#पूर्ण_अगर /* __SH_CSS_PARAMS_SHADING_H */
