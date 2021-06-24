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

#समावेश "system_global.h"
#समावेश <linux/kernel.h>

#अगर_अघोषित ISP2401

#समावेश "ia_css_ifmtr.h"
#समावेश <math_support.h>
#समावेश "sh_css_internal.h"
#समावेश "input_formatter.h"
#समावेश "assert_support.h"
#समावेश "sh_css_sp.h"
#समावेश "isp/modes/interface/input_buf.isp.h"

/************************************************************
 * Static functions declarations
 ************************************************************/
अटल पूर्णांक अगरmtr_start_column(
    स्थिर काष्ठा ia_css_stream_config *config,
    अचिन्हित पूर्णांक bin_in,
    अचिन्हित पूर्णांक *start_column);

अटल पूर्णांक अगरmtr_input_start_line(
    स्थिर काष्ठा ia_css_stream_config *config,
    अचिन्हित पूर्णांक bin_in,
    अचिन्हित पूर्णांक *start_line);

अटल व्योम अगरmtr_set_अगर_blocking_mode(
    स्थिर input_क्रमmatter_cfg_t *स्थिर config_a,
    स्थिर input_क्रमmatter_cfg_t *स्थिर config_b);

/************************************************************
 * Public functions
 ************************************************************/

/* ISP expects GRBG bayer order, we skip one line and/or one row
 * to correct in हाल the input bayer order is dअगरferent.
 */
अचिन्हित पूर्णांक ia_css_अगरmtr_lines_needed_क्रम_bayer_order(
    स्थिर काष्ठा ia_css_stream_config *config)
अणु
	निश्चित(config);
	अगर ((config->input_config.bayer_order == IA_CSS_BAYER_ORDER_BGGR)
	    || (config->input_config.bayer_order == IA_CSS_BAYER_ORDER_GBRG))
		वापस 1;

	वापस 0;
पूर्ण

अचिन्हित पूर्णांक ia_css_अगरmtr_columns_needed_क्रम_bayer_order(
    स्थिर काष्ठा ia_css_stream_config *config)
अणु
	निश्चित(config);
	अगर ((config->input_config.bayer_order == IA_CSS_BAYER_ORDER_RGGB)
	    || (config->input_config.bayer_order == IA_CSS_BAYER_ORDER_GBRG))
		वापस 1;

	वापस 0;
पूर्ण

पूर्णांक ia_css_अगरmtr_configure(काष्ठा ia_css_stream_config *config,
				       काष्ठा ia_css_binary *binary)
अणु
	अचिन्हित पूर्णांक start_line, start_column = 0,
				 cropped_height,
				 cropped_width,
				 num_vectors,
				 buffer_height = 2,
				 buffer_width,
				 two_ppc,
				 vmem_increment = 0,
				 deपूर्णांकerleaving = 0,
				 deपूर्णांकerleaving_b = 0,
				 width_a = 0,
				 width_b = 0,
				 bits_per_pixel,
				 vectors_per_buffer,
				 vectors_per_line = 0,
				 buffers_per_line = 0,
				 buf_offset_a = 0,
				 buf_offset_b = 0,
				 line_width = 0,
				 width_b_factor = 1, start_column_b,
				 left_padding = 0;
	input_क्रमmatter_cfg_t अगर_a_config, अगर_b_config;
	क्रमागत atomisp_input_क्रमmat input_क्रमmat;
	पूर्णांक err = 0;
	u8 अगर_config_index;

	/* Determine which input क्रमmatter config set is targeted. */
	/* Index is equal to the CSI-2 port used. */
	क्रमागत mipi_port_id port;

	अगर (binary) अणु
		cropped_height = binary->in_frame_info.res.height;
		cropped_width = binary->in_frame_info.res.width;
		/* This should correspond to the input buffer definition क्रम
		ISP binaries in input_buf.isp.h */
		अगर (binary->info->sp.enable.continuous &&
		    binary->info->sp.pipeline.mode != IA_CSS_BINARY_MODE_COPY)
			buffer_width = MAX_VECTORS_PER_INPUT_LINE_CONT * ISP_VEC_NELEMS;
		अन्यथा
			buffer_width = binary->info->sp.input.max_width;
		input_क्रमmat = binary->input_क्रमmat;
	पूर्ण अन्यथा अणु
		/* sp raw copy pipe (IA_CSS_PIPE_MODE_COPY): binary is शून्य */
		cropped_height = config->input_config.input_res.height;
		cropped_width = config->input_config.input_res.width;
		buffer_width = MAX_VECTORS_PER_INPUT_LINE_CONT * ISP_VEC_NELEMS;
		input_क्रमmat = config->input_config.क्रमmat;
	पूर्ण
	two_ppc = config->pixels_per_घड़ी == 2;
	अगर (config->mode == IA_CSS_INPUT_MODE_SENSOR
	    || config->mode == IA_CSS_INPUT_MODE_BUFFERED_SENSOR) अणु
		port = config->source.port.port;
		अगर_config_index = (uपूर्णांक8_t)(port - MIPI_PORT0_ID);
	पूर्ण अन्यथा अगर (config->mode == IA_CSS_INPUT_MODE_MEMORY) अणु
		अगर_config_index = SH_CSS_IF_CONFIG_NOT_NEEDED;
	पूर्ण अन्यथा अणु
		अगर_config_index = 0;
	पूर्ण

	निश्चित(अगर_config_index <= SH_CSS_MAX_IF_CONFIGS
	       || अगर_config_index == SH_CSS_IF_CONFIG_NOT_NEEDED);

	/* TODO: check to see अगर input is RAW and अगर current mode पूर्णांकerprets
	 * RAW data in any particular bayer order. copy binary with output
	 * क्रमmat other than raw should not result in dropping lines and/or
	 * columns.
	 */
	err = अगरmtr_input_start_line(config, cropped_height, &start_line);
	अगर (err)
		वापस err;
	err = अगरmtr_start_column(config, cropped_width, &start_column);
	अगर (err)
		वापस err;

	अगर (config->left_padding == -1)
		अगर (!binary)
			/* sp raw copy pipe: set left_padding value */
			left_padding = 0;
		अन्यथा
			left_padding = binary->left_padding;
	अन्यथा
		left_padding = 2 * ISP_VEC_NELEMS - config->left_padding;

	अगर (left_padding) अणु
		num_vectors = CEIL_DIV(cropped_width + left_padding,
				       ISP_VEC_NELEMS);
	पूर्ण अन्यथा अणु
		num_vectors = CEIL_DIV(cropped_width, ISP_VEC_NELEMS);
		num_vectors *= buffer_height;
		/* toकरो: in हाल of left padding,
		   num_vectors is vectors per line,
		   otherwise vectors per line * buffer_height. */
	पूर्ण

	start_column_b = start_column;

	bits_per_pixel = input_क्रमmatter_get_alignment(INPUT_FORMATTER0_ID)
			 * 8 / ISP_VEC_NELEMS;
	चयन (input_क्रमmat) अणु
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_LEGACY:
		अगर (two_ppc) अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 1;
			deपूर्णांकerleaving_b = 1;
			/* half lines */
			width_a = cropped_width * deपूर्णांकerleaving / 2;
			width_b_factor = 2;
			/* full lines */
			width_b = width_a * width_b_factor;
			buffer_width *= deपूर्णांकerleaving * 2;
			/* Patch from bayer to yuv */
			num_vectors *= deपूर्णांकerleaving;
			buf_offset_b = buffer_width / 2 / ISP_VEC_NELEMS;
			vectors_per_line = num_vectors / buffer_height;
			/* Even lines are half size */
			line_width = vectors_per_line *
				     input_क्रमmatter_get_alignment(INPUT_FORMATTER0_ID) /
				     2;
			start_column /= 2;
		पूर्ण अन्यथा अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 3;
			width_a = cropped_width * deपूर्णांकerleaving / 2;
			buffer_width = buffer_width * deपूर्णांकerleaving / 2;
			/* Patch from bayer to yuv */
			num_vectors = num_vectors / 2 * deपूर्णांकerleaving;
			start_column = start_column * deपूर्णांकerleaving / 2;
		पूर्ण
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV420_8:
	हाल ATOMISP_INPUT_FORMAT_YUV420_10:
	हाल ATOMISP_INPUT_FORMAT_YUV420_16:
		अगर (two_ppc) अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 1;
			width_a = width_b = cropped_width * deपूर्णांकerleaving / 2;
			buffer_width *= deपूर्णांकerleaving * 2;
			num_vectors *= deपूर्णांकerleaving;
			buf_offset_b = buffer_width / 2 / ISP_VEC_NELEMS;
			vectors_per_line = num_vectors / buffer_height;
			/* Even lines are half size */
			line_width = vectors_per_line *
				     input_क्रमmatter_get_alignment(INPUT_FORMATTER0_ID) /
				     2;
			start_column *= deपूर्णांकerleaving;
			start_column /= 2;
			start_column_b = start_column;
		पूर्ण अन्यथा अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 1;
			width_a = cropped_width * deपूर्णांकerleaving;
			buffer_width *= deपूर्णांकerleaving * 2;
			num_vectors *= deपूर्णांकerleaving;
			start_column *= deपूर्णांकerleaving;
		पूर्ण
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_YUV422_8:
	हाल ATOMISP_INPUT_FORMAT_YUV422_10:
	हाल ATOMISP_INPUT_FORMAT_YUV422_16:
		अगर (two_ppc) अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 1;
			width_a = width_b = cropped_width * deपूर्णांकerleaving;
			buffer_width *= deपूर्णांकerleaving * 2;
			num_vectors *= deपूर्णांकerleaving;
			start_column *= deपूर्णांकerleaving;
			buf_offset_b = buffer_width / 2 / ISP_VEC_NELEMS;
			start_column_b = start_column;
		पूर्ण अन्यथा अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 2;
			width_a = cropped_width * deपूर्णांकerleaving;
			buffer_width *= deपूर्णांकerleaving;
			num_vectors *= deपूर्णांकerleaving;
			start_column *= deपूर्णांकerleaving;
		पूर्ण
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RGB_444:
	हाल ATOMISP_INPUT_FORMAT_RGB_555:
	हाल ATOMISP_INPUT_FORMAT_RGB_565:
	हाल ATOMISP_INPUT_FORMAT_RGB_666:
	हाल ATOMISP_INPUT_FORMAT_RGB_888:
		num_vectors *= 2;
		अगर (two_ppc) अणु
			deपूर्णांकerleaving = 2;	/* BR in अगर_a, G in अगर_b */
			deपूर्णांकerleaving_b = 1;	/* BR in अगर_a, G in अगर_b */
			buffers_per_line = 4;
			start_column_b = start_column;
			start_column *= deपूर्णांकerleaving;
			start_column_b *= deपूर्णांकerleaving_b;
		पूर्ण अन्यथा अणु
			deपूर्णांकerleaving = 3;	/* BGR */
			buffers_per_line = 3;
			start_column *= deपूर्णांकerleaving;
		पूर्ण
		vmem_increment = 1;
		width_a = cropped_width * deपूर्णांकerleaving;
		width_b = cropped_width * deपूर्णांकerleaving_b;
		buffer_width *= buffers_per_line;
		/* Patch from bayer to rgb */
		num_vectors = num_vectors / 2 * deपूर्णांकerleaving;
		buf_offset_b = buffer_width / 2 / ISP_VEC_NELEMS;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_6:
	हाल ATOMISP_INPUT_FORMAT_RAW_7:
	हाल ATOMISP_INPUT_FORMAT_RAW_8:
	हाल ATOMISP_INPUT_FORMAT_RAW_10:
	हाल ATOMISP_INPUT_FORMAT_RAW_12:
		अगर (two_ppc) अणु
			पूर्णांक crop_col = (start_column % 2) == 1;

			vmem_increment = 2;
			deपूर्णांकerleaving = 1;
			width_a = width_b = cropped_width / 2;

			/* When two_ppc is enabled AND we need to crop one extra
			 * column, अगर_a crops by one extra and we swap the
			 * output offsets to पूर्णांकerleave the bayer pattern in
			 * the correct order.
			 */
			buf_offset_a   = crop_col ? 1 : 0;
			buf_offset_b   = crop_col ? 0 : 1;
			start_column_b = start_column / 2;
			start_column   = start_column / 2 + crop_col;
		पूर्ण अन्यथा अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 2;
			अगर ((!binary) || (config->continuous && binary
					  && binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_COPY)) अणु
				/* !binary -> sp raw copy pipe, no deपूर्णांकerleaving */
				deपूर्णांकerleaving = 1;
			पूर्ण
			width_a = cropped_width;
			/* Must be multiple of deपूर्णांकerleaving */
			num_vectors = CEIL_MUL(num_vectors, deपूर्णांकerleaving);
		पूर्ण
		buffer_height *= 2;
		अगर ((!binary) || config->continuous)
			/* !binary -> sp raw copy pipe */
			buffer_height *= 2;
		vectors_per_line = CEIL_DIV(cropped_width, ISP_VEC_NELEMS);
		vectors_per_line = CEIL_MUL(vectors_per_line, deपूर्णांकerleaving);
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_RAW_14:
	हाल ATOMISP_INPUT_FORMAT_RAW_16:
		अगर (two_ppc) अणु
			num_vectors *= 2;
			vmem_increment = 1;
			deपूर्णांकerleaving = 2;
			width_a = width_b = cropped_width;
			/* B buffer is one line further */
			buf_offset_b = buffer_width / ISP_VEC_NELEMS;
			bits_per_pixel *= 2;
		पूर्ण अन्यथा अणु
			vmem_increment = 1;
			deपूर्णांकerleaving = 2;
			width_a = cropped_width;
			start_column /= deपूर्णांकerleaving;
		पूर्ण
		buffer_height *= 2;
		अवरोध;
	हाल ATOMISP_INPUT_FORMAT_BINARY_8:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT1:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT2:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT3:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT4:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT5:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT6:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT7:
	हाल ATOMISP_INPUT_FORMAT_GENERIC_SHORT8:
	हाल ATOMISP_INPUT_FORMAT_YUV420_8_SHIFT:
	हाल ATOMISP_INPUT_FORMAT_YUV420_10_SHIFT:
	हाल ATOMISP_INPUT_FORMAT_EMBEDDED:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF1:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF2:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF3:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF4:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF5:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF6:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF7:
	हाल ATOMISP_INPUT_FORMAT_USER_DEF8:
		अवरोध;
	पूर्ण
	अगर (width_a == 0)
		वापस -EINVAL;

	अगर (two_ppc)
		left_padding /= 2;

	/* Default values */
	अगर (left_padding)
		vectors_per_line = num_vectors;
	अगर (!vectors_per_line) अणु
		vectors_per_line = CEIL_MUL(num_vectors / buffer_height,
					    deपूर्णांकerleaving);
		line_width = 0;
	पूर्ण
	अगर (!line_width)
		line_width = vectors_per_line *
			     input_क्रमmatter_get_alignment(INPUT_FORMATTER0_ID);
	अगर (!buffers_per_line)
		buffers_per_line = deपूर्णांकerleaving;
	line_width = CEIL_MUL(line_width,
			      input_क्रमmatter_get_alignment(INPUT_FORMATTER0_ID)
			      * vmem_increment);

	vectors_per_buffer = buffer_height * buffer_width / ISP_VEC_NELEMS;

	अगर (config->mode == IA_CSS_INPUT_MODE_TPG &&
	    ((binary && binary->info->sp.pipeline.mode == IA_CSS_BINARY_MODE_VIDEO) ||
	     (!binary))) अणु
		/* !binary -> sp raw copy pipe */
		/* workaround क्रम TPG in video mode */
		start_line = 0;
		start_column = 0;
		cropped_height -= start_line;
		width_a -= start_column;
	पूर्ण

	अगर_a_config.start_line = start_line;
	अगर_a_config.start_column = start_column;
	अगर_a_config.left_padding = left_padding / deपूर्णांकerleaving;
	अगर_a_config.cropped_height = cropped_height;
	अगर_a_config.cropped_width = width_a;
	अगर_a_config.deपूर्णांकerleaving = deपूर्णांकerleaving;
	अगर_a_config.buf_vecs = vectors_per_buffer;
	अगर_a_config.buf_start_index = buf_offset_a;
	अगर_a_config.buf_increment = vmem_increment;
	अगर_a_config.buf_eol_offset =
	    buffer_width * bits_per_pixel / 8 - line_width;
	अगर_a_config.is_yuv420_क्रमmat =
	    (input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8)
	    || (input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_10)
	    || (input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_16);
	अगर_a_config.block_no_reqs = (config->mode != IA_CSS_INPUT_MODE_SENSOR);

	अगर (two_ppc) अणु
		अगर (deपूर्णांकerleaving_b) अणु
			deपूर्णांकerleaving = deपूर्णांकerleaving_b;
			width_b = cropped_width * deपूर्णांकerleaving;
			buffer_width *= deपूर्णांकerleaving;
			/* Patch from bayer to rgb */
			num_vectors = num_vectors / 2 *
				      deपूर्णांकerleaving * width_b_factor;
			vectors_per_line = num_vectors / buffer_height;
			line_width = vectors_per_line *
				     input_क्रमmatter_get_alignment(INPUT_FORMATTER0_ID);
		पूर्ण
		अगर_b_config.start_line = start_line;
		अगर_b_config.start_column = start_column_b;
		अगर_b_config.left_padding = left_padding / deपूर्णांकerleaving;
		अगर_b_config.cropped_height = cropped_height;
		अगर_b_config.cropped_width = width_b;
		अगर_b_config.deपूर्णांकerleaving = deपूर्णांकerleaving;
		अगर_b_config.buf_vecs = vectors_per_buffer;
		अगर_b_config.buf_start_index = buf_offset_b;
		अगर_b_config.buf_increment = vmem_increment;
		अगर_b_config.buf_eol_offset =
		    buffer_width * bits_per_pixel / 8 - line_width;
		अगर_b_config.is_yuv420_क्रमmat =
		    input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_8
		    || input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_10
		    || input_क्रमmat == ATOMISP_INPUT_FORMAT_YUV420_16;
		अगर_b_config.block_no_reqs =
		    (config->mode != IA_CSS_INPUT_MODE_SENSOR);

		अगर (अगर_config_index != SH_CSS_IF_CONFIG_NOT_NEEDED) अणु
			निश्चित(अगर_config_index <= SH_CSS_MAX_IF_CONFIGS);

			अगरmtr_set_अगर_blocking_mode(&अगर_a_config, &अगर_b_config);
			/* Set the अगरconfigs to SP group */
			sh_css_sp_set_अगर_configs(&अगर_a_config, &अगर_b_config,
						 अगर_config_index);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (अगर_config_index != SH_CSS_IF_CONFIG_NOT_NEEDED) अणु
			निश्चित(अगर_config_index <= SH_CSS_MAX_IF_CONFIGS);

			अगरmtr_set_अगर_blocking_mode(&अगर_a_config, शून्य);
			/* Set the अगरconfigs to SP group */
			sh_css_sp_set_अगर_configs(&अगर_a_config, शून्य,
						 अगर_config_index);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

bool अगरmtr_set_अगर_blocking_mode_reset = true;

/************************************************************
 * Static functions
 ************************************************************/
अटल व्योम अगरmtr_set_अगर_blocking_mode(
    स्थिर input_क्रमmatter_cfg_t *स्थिर config_a,
    स्थिर input_क्रमmatter_cfg_t *स्थिर config_b)
अणु
	पूर्णांक i;
	bool block[] = अणु false, false, false, false पूर्ण;

	निश्चित(N_INPUT_FORMATTER_ID <= (ARRAY_SIZE(block)));

	block[INPUT_FORMATTER0_ID] = (bool)config_a->block_no_reqs;
	अगर (config_b)
		block[INPUT_FORMATTER1_ID] = (bool)config_b->block_no_reqs;

	/* TODO: next could cause issues when streams are started after
	 * eachother. */
	/*IF should not be reconfigured/reset from host */
	अगर (अगरmtr_set_अगर_blocking_mode_reset) अणु
		अगरmtr_set_अगर_blocking_mode_reset = false;
		क्रम (i = 0; i < N_INPUT_FORMATTER_ID; i++) अणु
			input_क्रमmatter_ID_t id = (input_क्रमmatter_ID_t)i;

			input_क्रमmatter_rst(id);
			input_क्रमmatter_set_fअगरo_blocking_mode(id, block[id]);
		पूर्ण
	पूर्ण

	वापस;
पूर्ण

अटल पूर्णांक अगरmtr_start_column(
    स्थिर काष्ठा ia_css_stream_config *config,
    अचिन्हित पूर्णांक bin_in,
    अचिन्हित पूर्णांक *start_column)
अणु
	अचिन्हित पूर्णांक in = config->input_config.input_res.width, start,
		     क्रम_bayer = ia_css_अगरmtr_columns_needed_क्रम_bayer_order(config);

	अगर (bin_in + 2 * क्रम_bayer > in)
		वापस -EINVAL;

	/* On the hardware, we want to use the middle of the input, so we
	 * भागide the start column by 2. */
	start = (in - bin_in) / 2;
	/* in हाल the number of extra columns is 2 or odd, we round the start
	 * column करोwn */
	start &= ~0x1;

	/* now we add the one column (अगर needed) to correct क्रम the bayer
	 * order).
	 */
	start += क्रम_bayer;
	*start_column = start;
	वापस 0;
पूर्ण

अटल पूर्णांक अगरmtr_input_start_line(
    स्थिर काष्ठा ia_css_stream_config *config,
    अचिन्हित पूर्णांक bin_in,
    अचिन्हित पूर्णांक *start_line)
अणु
	अचिन्हित पूर्णांक in = config->input_config.input_res.height, start,
		     क्रम_bayer = ia_css_अगरmtr_lines_needed_क्रम_bayer_order(config);

	अगर (bin_in + 2 * क्रम_bayer > in)
		वापस -EINVAL;

	/* On the hardware, we want to use the middle of the input, so we
	 * भागide the start line by 2. On the simulator, we cannot handle extra
	 * lines at the end of the frame.
	 */
	start = (in - bin_in) / 2;
	/* in हाल the number of extra lines is 2 or odd, we round the start
	 * line करोwn.
	 */
	start &= ~0x1;

	/* now we add the one line (अगर needed) to correct क्रम the bayer order */
	start += क्रम_bayer;
	*start_line = start;
	वापस 0;
पूर्ण

#पूर्ण_अगर
