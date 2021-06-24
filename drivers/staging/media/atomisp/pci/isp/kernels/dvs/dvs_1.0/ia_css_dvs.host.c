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

#समावेश "hmm.h"

#समावेश "ia_css_frame_public.h"
#घोषणा IA_CSS_INCLUDE_CONFIGURATIONS
#समावेश "ia_css_isp_configs.h"

#समावेश "ia_css_types.h"
#समावेश "ia_css_host_data.h"
#समावेश "sh_css_param_dvs.h"
#समावेश "sh_css_params.h"
#समावेश "ia_css_binary.h"
#समावेश "ia_css_debug.h"
#समावेश "assert_support.h"

#समावेश "ia_css_dvs.host.h"

अटल स्थिर काष्ठा ia_css_dvs_configuration शेष_config = अणु
	.info = (काष्ठा ia_css_frame_info *)शून्य,
पूर्ण;

व्योम
ia_css_dvs_config(
    काष्ठा sh_css_isp_dvs_isp_config *to,
    स्थिर काष्ठा ia_css_dvs_configuration  *from,
    अचिन्हित पूर्णांक size)
अणु
	(व्योम)size;
	to->num_horizontal_blocks =
	    DVS_NUM_BLOCKS_X(from->info->res.width);
	to->num_vertical_blocks =
	    DVS_NUM_BLOCKS_Y(from->info->res.height);
पूर्ण

व्योम
ia_css_dvs_configure(
    स्थिर काष्ठा ia_css_binary     *binary,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	काष्ठा ia_css_dvs_configuration config = शेष_config;

	config.info = info;

	ia_css_configure_dvs(binary, &config);
पूर्ण

अटल व्योम
convert_coords_to_ispparams(
    काष्ठा ia_css_host_data *gdc_warp_table,
    स्थिर काष्ठा ia_css_dvs_6axis_config *config,
    अचिन्हित पूर्णांक i_stride,
    अचिन्हित पूर्णांक o_width,
    अचिन्हित पूर्णांक o_height,
    अचिन्हित पूर्णांक uv_flag)
अणु
	अचिन्हित पूर्णांक i, j;
	gdc_warp_param_mem_t s = अणु 0 पूर्ण;
	अचिन्हित पूर्णांक x00, x01, x10, x11,
		 y00, y01, y10, y11;

	अचिन्हित पूर्णांक xmin, ymin, xmax, ymax;
	अचिन्हित पूर्णांक topleft_x, topleft_y, bottom_x, bottom_y,
		 topleft_x_frac, topleft_y_frac;
	अचिन्हित पूर्णांक dvs_पूर्णांकerp_envelope = (DVS_GDC_INTERP_METHOD == HRT_GDC_BLI_MODE ?
					    DVS_GDC_BLI_INTERP_ENVELOPE : DVS_GDC_BCI_INTERP_ENVELOPE);

	/* number of blocks per height and width */
	अचिन्हित पूर्णांक num_blocks_y =  (uv_flag ? DVS_NUM_BLOCKS_Y_CHROMA(
					  o_height) : DVS_NUM_BLOCKS_Y(o_height));
	अचिन्हित पूर्णांक num_blocks_x =  (uv_flag ? DVS_NUM_BLOCKS_X_CHROMA(
					  o_width)  : DVS_NUM_BLOCKS_X(
					  o_width)); // round num_x up to blockdim_x, अगर it concerns the Y0Y1 block (uv_flag==0) round up to even

	अचिन्हित पूर्णांक in_stride = i_stride * DVS_INPUT_BYTES_PER_PIXEL;
	अचिन्हित पूर्णांक width, height;
	अचिन्हित पूर्णांक *xbuff = शून्य;
	अचिन्हित पूर्णांक *ybuff = शून्य;
	काष्ठा gdc_warp_param_mem_s *ptr;

	निश्चित(config);
	निश्चित(gdc_warp_table);
	निश्चित(gdc_warp_table->address);

	ptr = (काष्ठा gdc_warp_param_mem_s *)gdc_warp_table->address;

	ptr += (2 * uv_flag); /* क्रमmat is Y0 Y1 UV, so UV starts at 3rd position */

	अगर (uv_flag == 0) अणु
		xbuff = config->xcoords_y;
		ybuff = config->ycoords_y;
		width = config->width_y;
		height = config->height_y;
	पूर्ण अन्यथा अणु
		xbuff = config->xcoords_uv;
		ybuff = config->ycoords_uv;
		width = config->width_uv;
		height = config->height_uv;
	पूर्ण

	IA_CSS_LOG("blockdim_x %d blockdim_y %d",
		   DVS_BLOCKDIM_X, DVS_BLOCKDIM_Y_LUMA >> uv_flag);
	IA_CSS_LOG("num_blocks_x %d num_blocks_y %d", num_blocks_x, num_blocks_y);
	IA_CSS_LOG("width %d height %d", width, height);

	निश्चित(width == num_blocks_x +
	       1); // the width and height of the provided morphing table should be 1 more than the number of blocks
	निश्चित(height == num_blocks_y + 1);

	क्रम (j = 0; j < num_blocks_y; j++) अणु
		क्रम (i = 0; i < num_blocks_x; i++) अणु
			x00 = xbuff[j * width + i];
			x01 = xbuff[j * width + (i + 1)];
			x10 = xbuff[(j + 1) * width + i];
			x11 = xbuff[(j + 1) * width + (i + 1)];

			y00 = ybuff[j * width + i];
			y01 = ybuff[j * width + (i + 1)];
			y10 = ybuff[(j + 1) * width + i];
			y11 = ybuff[(j + 1) * width + (i + 1)];

			xmin = min(x00, x10);
			xmax = max(x01, x11);
			ymin = min(y00, y01);
			ymax = max(y10, y11);

			/* Assert that right column's X is greater */
			निश्चित(x01 >= xmin);
			निश्चित(x11 >= xmin);
			/* Assert that bottom row's Y is greater */
			निश्चित(y10 >= ymin);
			निश्चित(y11 >= ymin);

			topleft_y = ymin >> DVS_COORD_FRAC_BITS;
			topleft_x = ((xmin >> DVS_COORD_FRAC_BITS)
				     >> XMEM_ALIGN_LOG2)
				    << (XMEM_ALIGN_LOG2);
			s.in_addr_offset = topleft_y * in_stride + topleft_x;

			/* similar to topleft_y calculation, but round up अगर ymax
			 * has any fraction bits */
			bottom_y = CEIL_DIV(ymax, 1 << DVS_COORD_FRAC_BITS);
			s.in_block_height = bottom_y - topleft_y + dvs_पूर्णांकerp_envelope;

			bottom_x = CEIL_DIV(xmax, 1 << DVS_COORD_FRAC_BITS);
			s.in_block_width = bottom_x - topleft_x + dvs_पूर्णांकerp_envelope;

			topleft_x_frac = topleft_x << (DVS_COORD_FRAC_BITS);
			topleft_y_frac = topleft_y << (DVS_COORD_FRAC_BITS);

			s.p0_x = x00 - topleft_x_frac;
			s.p1_x = x01 - topleft_x_frac;
			s.p2_x = x10 - topleft_x_frac;
			s.p3_x = x11 - topleft_x_frac;

			s.p0_y = y00 - topleft_y_frac;
			s.p1_y = y01 - topleft_y_frac;
			s.p2_y = y10 - topleft_y_frac;
			s.p3_y = y11 - topleft_y_frac;

			// block should fit within the boundingbox.
			निश्चित(s.p0_x < (s.in_block_width << DVS_COORD_FRAC_BITS));
			निश्चित(s.p1_x < (s.in_block_width << DVS_COORD_FRAC_BITS));
			निश्चित(s.p2_x < (s.in_block_width << DVS_COORD_FRAC_BITS));
			निश्चित(s.p3_x < (s.in_block_width << DVS_COORD_FRAC_BITS));
			निश्चित(s.p0_y < (s.in_block_height << DVS_COORD_FRAC_BITS));
			निश्चित(s.p1_y < (s.in_block_height << DVS_COORD_FRAC_BITS));
			निश्चित(s.p2_y < (s.in_block_height << DVS_COORD_FRAC_BITS));
			निश्चित(s.p3_y < (s.in_block_height << DVS_COORD_FRAC_BITS));

			// block size should be greater than zero.
			निश्चित(s.p0_x < s.p1_x);
			निश्चित(s.p2_x < s.p3_x);
			निश्चित(s.p0_y < s.p2_y);
			निश्चित(s.p1_y < s.p3_y);

#अगर 0
			म_लिखो("j: %d\ti:%d\n", j, i);
			म_लिखो("offset: %d\n", s.in_addr_offset);
			म_लिखो("p0_x: %d\n", s.p0_x);
			म_लिखो("p0_y: %d\n", s.p0_y);
			म_लिखो("p1_x: %d\n", s.p1_x);
			म_लिखो("p1_y: %d\n", s.p1_y);
			म_लिखो("p2_x: %d\n", s.p2_x);
			म_लिखो("p2_y: %d\n", s.p2_y);
			म_लिखो("p3_x: %d\n", s.p3_x);
			म_लिखो("p3_y: %d\n", s.p3_y);

			म_लिखो("p0_x_nofrac[0]: %d\n", s.p0_x >> DVS_COORD_FRAC_BITS);
			म_लिखो("p0_y_nofrac[1]: %d\n", s.p0_y >> DVS_COORD_FRAC_BITS);
			म_लिखो("p1_x_nofrac[2]: %d\n", s.p1_x >> DVS_COORD_FRAC_BITS);
			म_लिखो("p1_y_nofrac[3]: %d\n", s.p1_y >> DVS_COORD_FRAC_BITS);
			म_लिखो("p2_x_nofrac[0]: %d\n", s.p2_x >> DVS_COORD_FRAC_BITS);
			म_लिखो("p2_y_nofrac[1]: %d\n", s.p2_y >> DVS_COORD_FRAC_BITS);
			म_लिखो("p3_x_nofrac[2]: %d\n", s.p3_x >> DVS_COORD_FRAC_BITS);
			म_लिखो("p3_y_nofrac[3]: %d\n", s.p3_y >> DVS_COORD_FRAC_BITS);
			म_लिखो("\n");
#पूर्ण_अगर

			*ptr = s;

			// storage क्रमmat:
			// Y0 Y1 UV0 Y2 Y3 UV1
			/* अगर uv_flag equals true increment with 2 inहाल x is odd, this to
			skip the uv position. */
			अगर (uv_flag)
				ptr += 3;
			अन्यथा
				ptr += (1 + (i & 1));
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा ia_css_host_data *
convert_allocate_dvs_6axis_config(
    स्थिर काष्ठा ia_css_dvs_6axis_config *dvs_6axis_config,
    स्थिर काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_frame_info *dvs_in_frame_info)
अणु
	अचिन्हित पूर्णांक i_stride;
	अचिन्हित पूर्णांक o_width;
	अचिन्हित पूर्णांक o_height;
	काष्ठा ia_css_host_data *me;

	निश्चित(binary);
	निश्चित(dvs_6axis_config);
	निश्चित(dvs_in_frame_info);

	me = ia_css_host_data_allocate((माप_प्रकार)((DVS_6AXIS_BYTES(binary) / 2) * 3));

	अगर (!me)
		वापस शून्य;

	/*DVS only supports input frame of YUV420 or NV12. Fail क्रम all other हालs*/
	निश्चित((dvs_in_frame_info->क्रमmat == IA_CSS_FRAME_FORMAT_NV12)
	       || (dvs_in_frame_info->क्रमmat == IA_CSS_FRAME_FORMAT_YUV420));

	i_stride  = dvs_in_frame_info->padded_width;

	o_width  = binary->out_frame_info[0].res.width;
	o_height = binary->out_frame_info[0].res.height;

	/* Y plane */
	convert_coords_to_ispparams(me, dvs_6axis_config,
				    i_stride, o_width, o_height, 0);

	अगर (dvs_in_frame_info->क्रमmat == IA_CSS_FRAME_FORMAT_YUV420) अणु
		/*YUV420 has half the stride क्रम U/V plane*/
		i_stride /= 2;
	पूर्ण

	/* UV plane (packed inside the y plane) */
	convert_coords_to_ispparams(me, dvs_6axis_config,
				    i_stride, o_width / 2, o_height / 2, 1);

	वापस me;
पूर्ण

पूर्णांक
store_dvs_6axis_config(
    स्थिर काष्ठा ia_css_dvs_6axis_config *dvs_6axis_config,
    स्थिर काष्ठा ia_css_binary *binary,
    स्थिर काष्ठा ia_css_frame_info *dvs_in_frame_info,
    ia_css_ptr ddr_addr_y) अणु
	काष्ठा ia_css_host_data *me;

	निश्चित(dvs_6axis_config);
	निश्चित(ddr_addr_y != mmgr_शून्य);
	निश्चित(dvs_in_frame_info);

	me = convert_allocate_dvs_6axis_config(dvs_6axis_config,
					       binary,
					       dvs_in_frame_info);

	अगर (!me)
	अणु
		IA_CSS_LEAVE_ERR_PRIVATE(-ENOMEM);
		वापस -ENOMEM;
	पूर्ण

	ia_css_params_store_ia_css_host_data(
	    ddr_addr_y,
	    me);
	ia_css_host_data_मुक्त(me);

	वापस 0;
पूर्ण
