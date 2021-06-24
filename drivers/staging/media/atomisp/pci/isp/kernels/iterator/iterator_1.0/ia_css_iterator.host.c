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

#समावेश "ia_css_iterator.host.h"
#समावेश "ia_css_frame_public.h"
#समावेश "ia_css_binary.h"
#समावेश "ia_css_err.h"
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"

अटल स्थिर काष्ठा ia_css_iterator_configuration शेष_config = अणु
	.input_info = (काष्ठा ia_css_frame_info *)शून्य,
पूर्ण;

व्योम
ia_css_iterator_config(
    काष्ठा sh_css_isp_iterator_isp_config *to,
    स्थिर काष्ठा ia_css_iterator_configuration *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	ia_css_frame_info_to_frame_sp_info(&to->input_info,    from->input_info);
	ia_css_frame_info_to_frame_sp_info(&to->पूर्णांकernal_info, from->पूर्णांकernal_info);
	ia_css_frame_info_to_frame_sp_info(&to->output_info,   from->output_info);
	ia_css_frame_info_to_frame_sp_info(&to->vf_info,       from->vf_info);
	ia_css_resolution_to_sp_resolution(&to->dvs_envelope,  from->dvs_envelope);
पूर्ण

पूर्णांक
ia_css_iterator_configure(
    स्थिर काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_frame_info *in_info) अणु
	काष्ठा ia_css_frame_info my_info = IA_CSS_BINARY_DEFAULT_FRAME_INFO;
	काष्ठा ia_css_iterator_configuration config = शेष_config;

	config.input_info    = &binary->in_frame_info;
	config.पूर्णांकernal_info = &binary->पूर्णांकernal_frame_info;
	config.output_info   = &binary->out_frame_info[0];
	config.vf_info       = &binary->vf_frame_info;
	config.dvs_envelope  = &binary->dvs_envelope;

	/* Use in_info iso binary->in_frame_info.
	 * They can dअगरfer in padded width in हाल of scaling, e.g. क्रम capture_pp.
	 * Find out why.
	*/
	अगर (in_info)
		config.input_info = in_info;
	अगर (binary->out_frame_info[0].res.width == 0)
		config.output_info = &binary->out_frame_info[1];
	my_info = *config.output_info;
	config.output_info = &my_info;
	/* we करो this only क्रम preview pipe because in fill_binary_info function
	 * we assign vf_out res to out res, but क्रम ISP पूर्णांकernal processing, we need
	 * the original out res. क्रम video pipe, it has two output pins --- out and
	 * vf_out, so it can keep these two resolutions alपढ़ोy. */
	अगर (binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_PREVIEW &&
	    binary->vf_करोwnscale_log2 > 0)
	अणु
		/* TODO: Remove this after preview output decimation is fixed
		 * by configuring out&vf info files properly */
		my_info.padded_width <<= binary->vf_करोwnscale_log2;
		my_info.res.width    <<= binary->vf_करोwnscale_log2;
		my_info.res.height   <<= binary->vf_करोwnscale_log2;
	पूर्ण

	ia_css_configure_iterator(binary, &config);

	वापस 0;
पूर्ण
