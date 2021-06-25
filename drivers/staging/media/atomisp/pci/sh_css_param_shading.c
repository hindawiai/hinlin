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

#समावेश <linux/slab.h>

#समावेश <math_support.h>
#समावेश "sh_css_param_shading.h"
#समावेश "ia_css_shading.h"
#समावेश "assert_support.h"
#समावेश "sh_css_defs.h"
#समावेश "sh_css_internal.h"
#समावेश "ia_css_debug.h"
#समावेश "ia_css_pipe_binarydesc.h"

#समावेश "sh_css_hrt.h"

#समावेश "platform_support.h"

/* Bilinear पूर्णांकerpolation on shading tables:
 * For each target poपूर्णांक T, we calculate the 4 surrounding source poपूर्णांकs:
 * ul (upper left), ur (upper right), ll (lower left) and lr (lower right).
 * We then calculate the distances from the T to the source poपूर्णांकs: x0, x1,
 * y0 and y1.
 * We then calculate the value of T:
 *   dx0*dy0*Slr + dx0*dy1*Sur + dx1*dy0*Sll + dx1*dy1*Sul.
 * We choose a grid size of 1x1 which means:
 *   dx1 = 1-dx0
 *   dy1 = 1-dy0
 *
 *   Sul dx0         dx1      Sur
 *    .<----->|<------------->.
 *    ^
 * dy0|
 *    v        T
 *    -        .
 *    ^
 *    |
 * dy1|
 *    v
 *    .                        .
 *   Sll                      Slr
 *
 * Padding:
 * The area that the ISP operates on can include padding both on the left
 * and the right. We need to padd the shading table such that the shading
 * values end up on the correct pixel values. This means we must padd the
 * shading table to match the ISP padding.
 * We can have 5 हालs:
 * 1. All 4 poपूर्णांकs fall in the left padding.
 * 2. The left 2 poपूर्णांकs fall in the left padding.
 * 3. All 4 poपूर्णांकs fall in the cropped (target) region.
 * 4. The right 2 poपूर्णांकs fall in the right padding.
 * 5. All 4 poपूर्णांकs fall in the right padding.
 * Cases 1 and 5 are easy to handle: we simply use the
 * value 1 in the shading table.
 * Cases 2 and 4 require पूर्णांकerpolation that takes पूर्णांकo
 * account how far पूर्णांकo the padding area the pixels
 * fall. We extrapolate the shading table पूर्णांकo the
 * padded area and then पूर्णांकerpolate.
 */
अटल व्योम
crop_and_पूर्णांकerpolate(अचिन्हित पूर्णांक cropped_width,
		     अचिन्हित पूर्णांक cropped_height,
		     अचिन्हित पूर्णांक left_padding,
		     पूर्णांक right_padding,
		     पूर्णांक top_padding,
		     स्थिर काष्ठा ia_css_shading_table *in_table,
		     काष्ठा ia_css_shading_table *out_table,
		     क्रमागत ia_css_sc_color color)
अणु
	अचिन्हित पूर्णांक i, j,
		 sensor_width,
		 sensor_height,
		 table_width,
		 table_height,
		 table_cell_h,
		 out_cell_size,
		 in_cell_size,
		 out_start_row,
		 padded_width;
	पूर्णांक out_start_col, /* can be negative to indicate padded space */
	    table_cell_w;
	अचिन्हित लघु *in_ptr,
		 *out_ptr;

	निश्चित(in_table);
	निश्चित(out_table);

	sensor_width  = in_table->sensor_width;
	sensor_height = in_table->sensor_height;
	table_width   = in_table->width;
	table_height  = in_table->height;
	in_ptr = in_table->data[color];
	out_ptr = out_table->data[color];

	padded_width = cropped_width + left_padding + right_padding;
	out_cell_size = CEIL_DIV(padded_width, out_table->width - 1);
	in_cell_size  = CEIL_DIV(sensor_width, table_width - 1);

	out_start_col = ((पूर्णांक)sensor_width - (पूर्णांक)cropped_width) / 2 - left_padding;
	out_start_row = ((पूर्णांक)sensor_height - (पूर्णांक)cropped_height) / 2 - top_padding;
	table_cell_w = (पूर्णांक)((table_width - 1) * in_cell_size);
	table_cell_h = (table_height - 1) * in_cell_size;

	क्रम (i = 0; i < out_table->height; i++) अणु
		पूर्णांक ty, src_y0, src_y1;
		अचिन्हित पूर्णांक sy0, sy1, dy0, dy1, भागy;

		/* calculate target poपूर्णांक and make sure it falls within
		   the table */
		ty = out_start_row + i * out_cell_size;

		/* calculate बंदst source poपूर्णांकs in shading table and
		   make sure they fall within the table */
		src_y0 = ty / (पूर्णांक)in_cell_size;
		अगर (in_cell_size < out_cell_size)
			src_y1 = (ty + out_cell_size) / in_cell_size;
		अन्यथा
			src_y1 = src_y0 + 1;
		src_y0 = clamp(src_y0, 0, (पूर्णांक)table_height - 1);
		src_y1 = clamp(src_y1, 0, (पूर्णांक)table_height - 1);
		ty = min(clamp(ty, 0, (पूर्णांक)sensor_height - 1),
			 (पूर्णांक)table_cell_h);

		/* calculate बंदst source poपूर्णांकs क्रम distance computation */
		sy0 = min(src_y0 * in_cell_size, sensor_height - 1);
		sy1 = min(src_y1 * in_cell_size, sensor_height - 1);
		/* calculate distance between source and target pixels */
		dy0 = ty - sy0;
		dy1 = sy1 - ty;
		भागy = sy1 - sy0;
		अगर (भागy == 0) अणु
			dy0 = 1;
			भागy = 1;
		पूर्ण

		क्रम (j = 0; j < out_table->width; j++, out_ptr++) अणु
			पूर्णांक tx, src_x0, src_x1;
			अचिन्हित पूर्णांक sx0, sx1, dx0, dx1, भागx;
			अचिन्हित लघु s_ul, s_ur, s_ll, s_lr;

			/* calculate target poपूर्णांक */
			tx = out_start_col + j * out_cell_size;
			/* calculate बंदst source poपूर्णांकs. */
			src_x0 = tx / (पूर्णांक)in_cell_size;
			अगर (in_cell_size < out_cell_size) अणु
				src_x1 = (tx + out_cell_size) /
					 (पूर्णांक)in_cell_size;
			पूर्ण अन्यथा अणु
				src_x1 = src_x0 + 1;
			पूर्ण
			/* अगर src poपूर्णांकs fall in padding, select बंदst ones.*/
			src_x0 = clamp(src_x0, 0, (पूर्णांक)table_width - 1);
			src_x1 = clamp(src_x1, 0, (पूर्णांक)table_width - 1);
			tx = min(clamp(tx, 0, (पूर्णांक)sensor_width - 1),
				 (पूर्णांक)table_cell_w);
			/* calculate बंदst source poपूर्णांकs क्रम distance
			   computation */
			sx0 = min(src_x0 * in_cell_size, sensor_width - 1);
			sx1 = min(src_x1 * in_cell_size, sensor_width - 1);
			/* calculate distances between source and target
			   pixels */
			dx0 = tx - sx0;
			dx1 = sx1 - tx;
			भागx = sx1 - sx0;
			/* अगर we're at the edge, we just use the बंदst
			   poपूर्णांक still in the grid. We make up क्रम the भागider
			   in this हाल by setting the distance to
			   out_cell_size, since it's actually 0. */
			अगर (भागx == 0) अणु
				dx0 = 1;
				भागx = 1;
			पूर्ण

			/* get source pixel values */
			s_ul = in_ptr[(table_width * src_y0) + src_x0];
			s_ur = in_ptr[(table_width * src_y0) + src_x1];
			s_ll = in_ptr[(table_width * src_y1) + src_x0];
			s_lr = in_ptr[(table_width * src_y1) + src_x1];

			*out_ptr = (अचिन्हित लघु)((dx0 * dy0 * s_lr + dx0 * dy1 * s_ur + dx1 * dy0 *
						     s_ll + dx1 * dy1 * s_ul) /
						    (भागx * भागy));
		पूर्ण
	पूर्ण
पूर्ण

व्योम
sh_css_params_shading_id_table_generate(
    काष्ठा ia_css_shading_table **target_table,
    अचिन्हित पूर्णांक table_width,
    अचिन्हित पूर्णांक table_height)
अणु
	/* initialize table with ones, shअगरt becomes zero */
	अचिन्हित पूर्णांक i, j;
	काष्ठा ia_css_shading_table *result;

	निश्चित(target_table);

	result = ia_css_shading_table_alloc(table_width, table_height);
	अगर (!result) अणु
		*target_table = शून्य;
		वापस;
	पूर्ण

	क्रम (i = 0; i < IA_CSS_SC_NUM_COLORS; i++) अणु
		क्रम (j = 0; j < table_height * table_width; j++)
			result->data[i][j] = 1;
	पूर्ण
	result->fraction_bits = 0;
	*target_table = result;
पूर्ण

व्योम
prepare_shading_table(स्थिर काष्ठा ia_css_shading_table *in_table,
		      अचिन्हित पूर्णांक sensor_binning,
		      काष्ठा ia_css_shading_table **target_table,
		      स्थिर काष्ठा ia_css_binary *binary,
		      अचिन्हित पूर्णांक bds_factor)
अणु
	अचिन्हित पूर्णांक input_width, input_height, table_width, table_height, i;
	अचिन्हित पूर्णांक left_padding, top_padding, left_cropping;
	अचिन्हित पूर्णांक bds_numerator, bds_denominator;
	पूर्णांक right_padding;

	काष्ठा ia_css_shading_table *result;

	निश्चित(target_table);
	निश्चित(binary);

	अगर (!in_table) अणु
		sh_css_params_shading_id_table_generate(target_table,
							binary->sctbl_legacy_width_per_color,
							binary->sctbl_legacy_height);
		वापस;
	पूर्ण

	/*
	 * We use the ISP input resolution क्रम the shading table because
	 * shading correction is perक्रमmed in the bayer करोमुख्य (beक्रमe bayer
	 * करोwn scaling).
	 */
	input_height  = binary->in_frame_info.res.height;
	input_width   = binary->in_frame_info.res.width;
	left_padding  = binary->left_padding;
	left_cropping = (binary->info->sp.pipeline.left_cropping == 0) ?
			binary->dvs_envelope.width : 2 * ISP_VEC_NELEMS;

	sh_css_bds_factor_get_numerator_denominator
	(bds_factor, &bds_numerator, &bds_denominator);

	left_padding  = (left_padding + binary->info->sp.pipeline.left_cropping) *
			bds_numerator / bds_denominator -
			binary->info->sp.pipeline.left_cropping;
	right_padding = (binary->पूर्णांकernal_frame_info.res.width -
			 binary->effective_in_frame_res.width * bds_denominator /
			 bds_numerator - left_cropping) * bds_numerator / bds_denominator;
	top_padding = binary->info->sp.pipeline.top_cropping * bds_numerator /
		      bds_denominator -
		      binary->info->sp.pipeline.top_cropping;

#अगर !defined(USE_WINDOWS_BINNING_FACTOR)
	/* @deprecatedअणुThis part of the code will be replaced by the code
	 * in the #अन्यथा section below to make the calculation same across
	 * all platक्रमms.
	 * Android and Winकरोws platक्रमms पूर्णांकerpret the binning_factor parameter
	 * dअगरferently. In Android, the binning factor is expressed in the क्रमm
	 * 2^N * 2^N, whereas in Winकरोws platक्रमm, the binning factor is N*Nपूर्ण
	 */

	/* We take पूर्णांकo account the binning करोne by the sensor. We करो this
	   by cropping the non-binned part of the shading table and then
	   increasing the size of a grid cell with this same binning factor. */
	input_width  <<= sensor_binning;
	input_height <<= sensor_binning;
	/* We also scale the padding by the same binning factor. This will
	   make it much easier later on to calculate the padding of the
	   shading table. */
	left_padding  <<= sensor_binning;
	right_padding <<= sensor_binning;
	top_padding   <<= sensor_binning;
#अन्यथा
	input_width   *= sensor_binning;
	input_height  *= sensor_binning;
	left_padding  *= sensor_binning;
	right_padding *= sensor_binning;
	top_padding   *= sensor_binning;
#पूर्ण_अगर /*USE_WINDOWS_BINNING_FACTOR*/

	/* during simulation, the used resolution can exceed the sensor
	   resolution, so we clip it. */
	input_width  = min(input_width,  in_table->sensor_width);
	input_height = min(input_height, in_table->sensor_height);

	/* This prepare_shading_table() function is called only in legacy API (not in new API).
	   Then, the legacy shading table width and height should be used. */
	table_width  = binary->sctbl_legacy_width_per_color;
	table_height = binary->sctbl_legacy_height;

	result = ia_css_shading_table_alloc(table_width, table_height);
	अगर (!result) अणु
		*target_table = शून्य;
		वापस;
	पूर्ण
	result->sensor_width  = in_table->sensor_width;
	result->sensor_height = in_table->sensor_height;
	result->fraction_bits = in_table->fraction_bits;

	/* now we crop the original shading table and then पूर्णांकerpolate to the
	   requested resolution and decimation factor. */
	क्रम (i = 0; i < IA_CSS_SC_NUM_COLORS; i++) अणु
		crop_and_पूर्णांकerpolate(input_width, input_height,
				     left_padding, right_padding, top_padding,
				     in_table,
				     result, i);
	पूर्ण
	*target_table = result;
पूर्ण

काष्ठा ia_css_shading_table *
ia_css_shading_table_alloc(
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक height)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा ia_css_shading_table *me;

	IA_CSS_ENTER("");

	me = kदो_स्मृति(माप(*me), GFP_KERNEL);
	अगर (!me)
		वापस me;

	me->width         = width;
	me->height        = height;
	me->sensor_width  = 0;
	me->sensor_height = 0;
	me->fraction_bits = 0;
	क्रम (i = 0; i < IA_CSS_SC_NUM_COLORS; i++) अणु
		me->data[i] =
		    kvदो_स्मृति(width * height * माप(*me->data[0]),
			     GFP_KERNEL);
		अगर (!me->data[i]) अणु
			अचिन्हित पूर्णांक j;

			क्रम (j = 0; j < i; j++) अणु
				kvमुक्त(me->data[j]);
				me->data[j] = शून्य;
			पूर्ण
			kमुक्त(me);
			वापस शून्य;
		पूर्ण
	पूर्ण

	IA_CSS_LEAVE("");
	वापस me;
पूर्ण

व्योम
ia_css_shading_table_मुक्त(काष्ठा ia_css_shading_table *table)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!table)
		वापस;

	/* We only output logging when the table is not शून्य, otherwise
	 * logs will give the impression that a table was मुक्तd.
	 * */
	IA_CSS_ENTER("");

	क्रम (i = 0; i < IA_CSS_SC_NUM_COLORS; i++) अणु
		अगर (table->data[i]) अणु
			kvमुक्त(table->data[i]);
			table->data[i] = शून्य;
		पूर्ण
	पूर्ण
	kमुक्त(table);

	IA_CSS_LEAVE("");
पूर्ण
