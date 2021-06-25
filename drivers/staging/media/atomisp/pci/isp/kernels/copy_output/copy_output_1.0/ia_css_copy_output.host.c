<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
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

#समावेश "ia_css_copy_output.host.h"
#समावेश "ia_css_binary.h"
#समावेश "type_support.h"
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"
#समावेश "isp.h"

अटल स्थिर काष्ठा ia_css_copy_output_configuration शेष_config = अणु
	.enable = false,
पूर्ण;

व्योम
ia_css_copy_output_config(
    काष्ठा sh_css_isp_copy_output_isp_config      *to,
    स्थिर काष्ठा ia_css_copy_output_configuration *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->enable = from->enable;
पूर्ण

व्योम
ia_css_copy_output_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    bool enable)
अणु
	काष्ठा ia_css_copy_output_configuration config = शेष_config;

	config.enable = enable;

	ia_css_configure_copy_output(binary, &config);
पूर्ण
