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

#समावेश "ia_css_frame.h"
#समावेश "ia_css_debug.h"
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"
#समावेश "ia_css_output.host.h"
#समावेश "isp.h"

#समावेश "assert_support.h"

स्थिर काष्ठा ia_css_output_config शेष_output_config = अणु
	0,
	0
पूर्ण;

अटल स्थिर काष्ठा ia_css_output_configuration शेष_output_configuration = अणु
	.info = (काष्ठा ia_css_frame_info *)शून्य,
पूर्ण;

अटल स्थिर काष्ठा ia_css_output0_configuration शेष_output0_configuration
	= अणु
	.info = (काष्ठा ia_css_frame_info *)शून्य,
पूर्ण;

अटल स्थिर काष्ठा ia_css_output1_configuration शेष_output1_configuration
	= अणु
	.info = (काष्ठा ia_css_frame_info *)शून्य,
पूर्ण;

व्योम
ia_css_output_encode(
    काष्ठा sh_css_isp_output_params *to,
    स्थिर काष्ठा ia_css_output_config *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->enable_hflip = from->enable_hflip;
	to->enable_vflip = from->enable_vflip;
पूर्ण

व्योम
ia_css_output_config(
    काष्ठा sh_css_isp_output_isp_config *to,
    स्थिर काष्ठा ia_css_output_configuration  *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक elems_a = ISP_VEC_NELEMS;

	(व्योम)size;
	ia_css_dma_configure_from_info(&to->port_b, from->info);
	to->width_a_over_b = elems_a / to->port_b.elems;
	to->height = from->info ? from->info->res.height : 0;
	to->enable = from->info != शून्य;
	ia_css_frame_info_to_frame_sp_info(&to->info, from->info);

	/* Assume भागisiblity here, may need to generalize to fixed poपूर्णांक. */
	निश्चित(elems_a % to->port_b.elems == 0);
पूर्ण

व्योम
ia_css_output0_config(
    काष्ठा sh_css_isp_output_isp_config       *to,
    स्थिर काष्ठा ia_css_output0_configuration *from,
    अचिन्हित पूर्णांक size)
अणु
	ia_css_output_config(
	    to, (स्थिर काष्ठा ia_css_output_configuration *)from, size);
पूर्ण

व्योम
ia_css_output1_config(
    काष्ठा sh_css_isp_output_isp_config       *to,
    स्थिर काष्ठा ia_css_output1_configuration *from,
    अचिन्हित पूर्णांक size)
अणु
	ia_css_output_config(
	    to, (स्थिर काष्ठा ia_css_output_configuration *)from, size);
पूर्ण

व्योम
ia_css_output_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	अगर (info) अणु
		काष्ठा ia_css_output_configuration config =
			    शेष_output_configuration;

		config.info = info;

		ia_css_configure_output(binary, &config);
	पूर्ण
पूर्ण

व्योम
ia_css_output0_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	अगर (info) अणु
		काष्ठा ia_css_output0_configuration config =
			    शेष_output0_configuration;

		config.info = info;

		ia_css_configure_output0(binary, &config);
	पूर्ण
पूर्ण

व्योम
ia_css_output1_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	अगर (info) अणु
		काष्ठा ia_css_output1_configuration config =
			    शेष_output1_configuration;

		config.info = info;

		ia_css_configure_output1(binary, &config);
	पूर्ण
पूर्ण

व्योम
ia_css_output_dump(
    स्थिर काष्ठा sh_css_isp_output_params *output,
    अचिन्हित पूर्णांक level)
अणु
	अगर (!output) वापस;
	ia_css_debug_dtrace(level, "Horizontal Output Flip:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "enable", output->enable_hflip);
	ia_css_debug_dtrace(level, "Vertical Output Flip:\n");
	ia_css_debug_dtrace(level, "\t%-32s = %d\n",
			    "enable", output->enable_vflip);
पूर्ण

व्योम
ia_css_output_debug_dtrace(
    स्थिर काष्ठा ia_css_output_config *config,
    अचिन्हित पूर्णांक level)
अणु
	ia_css_debug_dtrace(level,
			    "config.enable_hflip=%d",
			    config->enable_hflip);
	ia_css_debug_dtrace(level,
			    "config.enable_vflip=%d",
			    config->enable_vflip);
पूर्ण
