<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010 - 2015, Intel Corporation.
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

#समावेश "ia_css_bayer_io.host.h"
#समावेश "dma.h"
#समावेश "math_support.h"
#अगर_अघोषित IA_CSS_NO_DEBUG
#समावेश "ia_css_debug.h"
#पूर्ण_अगर
#समावेश "ia_css_isp_params.h"
#समावेश "ia_css_frame.h"

व्योम
ia_css_bayer_io_config(
    स्थिर काष्ठा ia_css_binary      *binary,
    स्थिर काष्ठा sh_css_binary_args *args)
अणु
	स्थिर काष्ठा ia_css_frame *in_frame = args->in_frame;
	स्थिर काष्ठा ia_css_frame **out_frames = (स्थिर काष्ठा ia_css_frame **)
		&args->out_frame;
	स्थिर काष्ठा ia_css_frame_info *in_frame_info = (in_frame) ? &in_frame->info :
		&binary->in_frame_info;

	स्थिर अचिन्हित पूर्णांक ddr_bits_per_element = माप(लघु) * 8;
	स्थिर अचिन्हित पूर्णांक ddr_elems_per_word = उच्चमान_भाग(HIVE_ISP_DDR_WORD_BITS,
						ddr_bits_per_element);
	अचिन्हित पूर्णांक size_get = 0, size_put = 0;
	अचिन्हित पूर्णांक offset = 0;

	अगर (binary->info->mem_offsets.offsets.param) अणु
		size_get = binary->info->mem_offsets.offsets.param->dmem.get.size;
		offset = binary->info->mem_offsets.offsets.param->dmem.get.offset;
	पूर्ण

	अगर (size_get) अणु
		काष्ठा ia_css_common_io_config *to = (काष्ठा ia_css_common_io_config *)
						     &binary->mem_params.params[IA_CSS_PARAM_CLASS_PARAM][IA_CSS_ISP_DMEM].address[offset];
		काष्ठा dma_port_config config;
#अगर_अघोषित IA_CSS_NO_DEBUG
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "ia_css_bayer_io_config() get part enter:\n");
#पूर्ण_अगर

		ia_css_dma_configure_from_info(&config, in_frame_info);
		// The base_address of the input frame will be set in the ISP
		to->width = in_frame_info->res.width;
		to->height = in_frame_info->res.height;
		to->stride = config.stride;
		to->ddr_elems_per_word = ddr_elems_per_word;
#अगर_अघोषित IA_CSS_NO_DEBUG
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "ia_css_bayer_io_config() get part leave:\n");
#पूर्ण_अगर
	पूर्ण

	अगर (binary->info->mem_offsets.offsets.param) अणु
		size_put = binary->info->mem_offsets.offsets.param->dmem.put.size;
		offset = binary->info->mem_offsets.offsets.param->dmem.put.offset;
	पूर्ण

	अगर (size_put) अणु
		काष्ठा ia_css_common_io_config *to = (काष्ठा ia_css_common_io_config *)
						     &binary->mem_params.params[IA_CSS_PARAM_CLASS_PARAM][IA_CSS_ISP_DMEM].address[offset];
		काष्ठा dma_port_config config;
#अगर_अघोषित IA_CSS_NO_DEBUG
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "ia_css_bayer_io_config() put part enter:\n");
#पूर्ण_अगर

		ia_css_dma_configure_from_info(&config, &out_frames[0]->info);
		to->base_address = out_frames[0]->data;
		to->width = out_frames[0]->info.res.width;
		to->height = out_frames[0]->info.res.height;
		to->stride = config.stride;
		to->ddr_elems_per_word = ddr_elems_per_word;

#अगर_अघोषित IA_CSS_NO_DEBUG
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE_PRIVATE,
				    "ia_css_bayer_io_config() put part leave:\n");
#पूर्ण_अगर
	पूर्ण
पूर्ण
