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

#समावेश "atomisp_internal.h"

#समावेश "ia_css_vf.host.h"
#समावेश <निश्चित_support.h>
#समावेश <ia_css_err.h>
#समावेश <ia_css_frame.h>
#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_pipeline.h>
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"

#समावेश "isp.h"

व्योम
ia_css_vf_config(
    काष्ठा sh_css_isp_vf_isp_config      *to,
    स्थिर काष्ठा ia_css_vf_configuration *from,
    अचिन्हित पूर्णांक size)
अणु
	अचिन्हित पूर्णांक elems_a = ISP_VEC_NELEMS;

	(व्योम)size;
	to->vf_करोwnscale_bits = from->vf_करोwnscale_bits;
	to->enable = from->info != शून्य;

	अगर (from->info) अणु
		ia_css_frame_info_to_frame_sp_info(&to->info, from->info);
		ia_css_dma_configure_from_info(&to->dma.port_b, from->info);
		to->dma.width_a_over_b = elems_a / to->dma.port_b.elems;

		/* Assume भागisiblity here, may need to generalize to fixed poपूर्णांक. */
		निश्चित(elems_a % to->dma.port_b.elems == 0);
	पूर्ण
पूर्ण

/* compute the log2 of the करोwnscale factor needed to get बंदst
 * to the requested viewfinder resolution on the upper side. The output cannot
 * be smaller than the requested viewfinder resolution.
 */
पूर्णांक
sh_css_vf_करोwnscale_log2(
    स्थिर काष्ठा ia_css_frame_info *out_info,
    स्थिर काष्ठा ia_css_frame_info *vf_info,
    अचिन्हित पूर्णांक *करोwnscale_log2) अणु
	अचिन्हित पूर्णांक ds_log2 = 0;
	अचिन्हित पूर्णांक out_width;

	अगर ((!out_info) || (!vf_info))
		वापस -EINVAL;

	out_width = out_info->res.width;

	अगर (out_width == 0)
		वापस -EINVAL;

	/* करोwnscale until width smaller than the viewfinder width. We करोn't
	* test क्रम the height since the vmem buffers only put restrictions on
	* the width of a line, not on the number of lines in a frame.
	*/
	जबतक (out_width >= vf_info->res.width)
	अणु
		ds_log2++;
		out_width /= 2;
	पूर्ण
	/* now width is smaller, so we go up one step */
	अगर ((ds_log2 > 0) && (out_width < ia_css_binary_max_vf_width()))
		ds_log2--;
	/* TODO: use actual max input resolution of vf_pp binary */
	अगर ((out_info->res.width >> ds_log2) >= 2 * ia_css_binary_max_vf_width())
		वापस -EINVAL;
	*करोwnscale_log2 = ds_log2;
	वापस 0;
पूर्ण

अटल पूर्णांक
configure_kernel(
    स्थिर काष्ठा ia_css_binary_info *info,
    स्थिर काष्ठा ia_css_frame_info *out_info,
    स्थिर काष्ठा ia_css_frame_info *vf_info,
    अचिन्हित पूर्णांक *करोwnscale_log2,
    काष्ठा ia_css_vf_configuration *config) अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक vf_log_ds = 0;

	/* First compute value */
	अगर (vf_info)
	अणु
		err = sh_css_vf_करोwnscale_log2(out_info, vf_info, &vf_log_ds);
		अगर (err)
			वापस err;
	पूर्ण
	vf_log_ds = min(vf_log_ds, info->vf_dec.max_log_करोwnscale);
	*करोwnscale_log2 = vf_log_ds;

	/* Then store it in isp config section */
	config->vf_करोwnscale_bits = vf_log_ds;
	वापस 0;
पूर्ण

अटल व्योम
configure_dma(
    काष्ठा ia_css_vf_configuration *config,
    स्थिर काष्ठा ia_css_frame_info *vf_info)
अणु
	config->info = vf_info;
पूर्ण

पूर्णांक
ia_css_vf_configure(
    स्थिर काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info,
    अचिन्हित पूर्णांक *करोwnscale_log2) अणु
	पूर्णांक err;
	काष्ठा ia_css_vf_configuration config;
	स्थिर काष्ठा ia_css_binary_info *info = &binary->info->sp;

	err = configure_kernel(info, out_info, vf_info, करोwnscale_log2, &config);
	अगर (err)
		dev_warn(atomisp_dev, "Couldn't setup downscale\n");

	configure_dma(&config, vf_info);

	अगर (vf_info)
		vf_info->raw_bit_depth = info->dma.vfdec_bits_per_pixel;
	ia_css_configure_vf(binary, &config);

	वापस 0;
पूर्ण
