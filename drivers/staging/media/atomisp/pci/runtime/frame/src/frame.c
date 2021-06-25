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

#समावेश "ia_css_frame.h"
#समावेश <math_support.h>
#समावेश "assert_support.h"
#समावेश "ia_css_debug.h"
#समावेश "isp.h"
#समावेश "sh_css_internal.h"
#समावेश "atomisp_internal.h"

#घोषणा NV12_TILEY_TILE_WIDTH  128
#घोषणा NV12_TILEY_TILE_HEIGHT  32

/**************************************************************************
**	Static functions declarations
**************************************************************************/
अटल व्योम frame_init_plane(काष्ठा ia_css_frame_plane *plane,
			     अचिन्हित पूर्णांक width,
			     अचिन्हित पूर्णांक stride,
			     अचिन्हित पूर्णांक height,
			     अचिन्हित पूर्णांक offset);

अटल व्योम frame_init_single_plane(काष्ठा ia_css_frame *frame,
				    काष्ठा ia_css_frame_plane *plane,
				    अचिन्हित पूर्णांक height,
				    अचिन्हित पूर्णांक subpixels_per_line,
				    अचिन्हित पूर्णांक bytes_per_pixel);

अटल व्योम frame_init_raw_single_plane(
    काष्ठा ia_css_frame *frame,
    काष्ठा ia_css_frame_plane *plane,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक subpixels_per_line,
    अचिन्हित पूर्णांक bits_per_pixel);

अटल व्योम frame_init_mipi_plane(काष्ठा ia_css_frame *frame,
				  काष्ठा ia_css_frame_plane *plane,
				  अचिन्हित पूर्णांक height,
				  अचिन्हित पूर्णांक subpixels_per_line,
				  अचिन्हित पूर्णांक bytes_per_pixel);

अटल व्योम frame_init_nv_planes(काष्ठा ia_css_frame *frame,
				 अचिन्हित पूर्णांक horizontal_decimation,
				 अचिन्हित पूर्णांक vertical_decimation,
				 अचिन्हित पूर्णांक bytes_per_element);

अटल व्योम frame_init_yuv_planes(काष्ठा ia_css_frame *frame,
				  अचिन्हित पूर्णांक horizontal_decimation,
				  अचिन्हित पूर्णांक vertical_decimation,
				  bool swap_uv,
				  अचिन्हित पूर्णांक bytes_per_element);

अटल व्योम frame_init_rgb_planes(काष्ठा ia_css_frame *frame,
				  अचिन्हित पूर्णांक bytes_per_element);

अटल व्योम frame_init_qplane6_planes(काष्ठा ia_css_frame *frame);

अटल पूर्णांक frame_allocate_buffer_data(काष्ठा ia_css_frame *frame);

अटल पूर्णांक frame_allocate_with_data(काष्ठा ia_css_frame **frame,
	अचिन्हित पूर्णांक width,
	अचिन्हित पूर्णांक height,
	क्रमागत ia_css_frame_क्रमmat क्रमmat,
	अचिन्हित पूर्णांक padded_width,
	अचिन्हित पूर्णांक raw_bit_depth,
	bool contiguous);

अटल काष्ठा ia_css_frame *frame_create(अचिन्हित पूर्णांक width,
	अचिन्हित पूर्णांक height,
	क्रमागत ia_css_frame_क्रमmat क्रमmat,
	अचिन्हित पूर्णांक padded_width,
	अचिन्हित पूर्णांक raw_bit_depth,
	bool contiguous,
	bool valid);

अटल अचिन्हित
ia_css_elems_bytes_from_info(
    स्थिर काष्ठा ia_css_frame_info *info);

/**************************************************************************
**	CSS API functions, exposed by ia_css.h
**************************************************************************/

व्योम ia_css_frame_zero(काष्ठा ia_css_frame *frame)
अणु
	निश्चित(frame);
	hmm_set(frame->data, 0, frame->data_bytes);
पूर्ण

पूर्णांक ia_css_frame_allocate_from_info(काष्ठा ia_css_frame **frame,
	स्थिर काष्ठा ia_css_frame_info *info)
अणु
	पूर्णांक err = 0;

	अगर (!frame || !info)
		वापस -EINVAL;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_allocate_from_info() enter:\n");
	err =
	    ia_css_frame_allocate(frame, info->res.width, info->res.height,
				  info->क्रमmat, info->padded_width,
				  info->raw_bit_depth);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_allocate_from_info() leave:\n");
	वापस err;
पूर्ण

पूर्णांक ia_css_frame_allocate(काष्ठा ia_css_frame **frame,
				      अचिन्हित पूर्णांक width,
				      अचिन्हित पूर्णांक height,
				      क्रमागत ia_css_frame_क्रमmat क्रमmat,
				      अचिन्हित पूर्णांक padded_width,
				      अचिन्हित पूर्णांक raw_bit_depth)
अणु
	पूर्णांक err = 0;

	अगर (!frame || width == 0 || height == 0)
		वापस -EINVAL;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_allocate() enter: width=%d, height=%d, format=%d, padded_width=%d, raw_bit_depth=%d\n",
			    width, height, क्रमmat, padded_width, raw_bit_depth);

	err = frame_allocate_with_data(frame, width, height, क्रमmat,
				       padded_width, raw_bit_depth, false);

	अगर ((*frame) && err == 0)
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_frame_allocate() leave: frame=%p, data(DDR address)=0x%x\n", *frame,
				    (*frame)->data);
	अन्यथा
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_frame_allocate() leave: frame=%p, data(DDR address)=0x%x\n",
				    (व्योम *)-1, (अचिन्हित पूर्णांक)-1);

	वापस err;
पूर्ण

पूर्णांक ia_css_frame_map(काष्ठा ia_css_frame **frame,
				 स्थिर काष्ठा ia_css_frame_info *info,
				 स्थिर व्योम __user *data,
				 u16 attribute,
				 अचिन्हित पूर्णांक pgnr)
अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_frame *me;

	निश्चित(frame);

	/* Create the frame काष्ठाure */
	err = ia_css_frame_create_from_info(&me, info);

	अगर (err)
		वापस err;

	अगर (!err) अणु
		अगर (pgnr < ((PAGE_ALIGN(me->data_bytes)) >> PAGE_SHIFT)) अणु
			dev_err(atomisp_dev,
				"user space memory size is less than the expected size..\n");
			err = -ENOMEM;
			जाओ error;
		पूर्ण अन्यथा अगर (pgnr > ((PAGE_ALIGN(me->data_bytes)) >> PAGE_SHIFT)) अणु
			dev_err(atomisp_dev,
				"user space memory size is large than the expected size..\n");
			err = -ENOMEM;
			जाओ error;
		पूर्ण

		me->data = hmm_alloc(me->data_bytes, HMM_BO_USER, 0, data,
				     attribute & ATOMISP_MAP_FLAG_CACHED);

		अगर (me->data == mmgr_शून्य)
			err = -EINVAL;
	पूर्ण

error:
	अगर (err) अणु
		kvमुक्त(me);
		me = शून्य;
	पूर्ण

	*frame = me;

	वापस err;
पूर्ण

पूर्णांक ia_css_frame_create_from_info(काष्ठा ia_css_frame **frame,
	स्थिर काष्ठा ia_css_frame_info *info)
अणु
	पूर्णांक err = 0;
	काष्ठा ia_css_frame *me;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_create_from_info() enter:\n");
	अगर (!frame || !info) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_frame_create_from_info() leave: invalid arguments\n");
		वापस -EINVAL;
	पूर्ण

	me = frame_create(info->res.width,
			  info->res.height,
			  info->क्रमmat,
			  info->padded_width,
			  info->raw_bit_depth,
			  false,
			  false);
	अगर (!me) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_frame_create_from_info() leave: frame create failed\n");
		वापस -ENOMEM;
	पूर्ण

	err = ia_css_frame_init_planes(me);

	अगर (err) अणु
		kvमुक्त(me);
		me = शून्य;
	पूर्ण

	*frame = me;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_create_from_info() leave:\n");

	वापस err;
पूर्ण

पूर्णांक ia_css_frame_set_data(काष्ठा ia_css_frame *frame,
				      स्थिर ia_css_ptr mapped_data,
				      माप_प्रकार data_bytes)
अणु
	पूर्णांक err = 0;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_set_data() enter:\n");
	अगर (!frame) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_frame_set_data() leave: NULL frame\n");
		वापस -EINVAL;
	पूर्ण

	/* If we are setting a valid data.
	 * Make sure that there is enough
	 * room क्रम the expected frame क्रमmat
	 */
	अगर ((mapped_data != mmgr_शून्य) && (frame->data_bytes > data_bytes)) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "ia_css_frame_set_data() leave: invalid arguments\n");
		वापस -EINVAL;
	पूर्ण

	frame->data = mapped_data;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "ia_css_frame_set_data() leave:\n");

	वापस err;
पूर्ण

पूर्णांक ia_css_frame_allocate_contiguous(काष्ठा ia_css_frame **frame,
	अचिन्हित पूर्णांक width,
	अचिन्हित पूर्णांक height,
	क्रमागत ia_css_frame_क्रमmat क्रमmat,
	अचिन्हित पूर्णांक padded_width,
	अचिन्हित पूर्णांक raw_bit_depth)
अणु
	पूर्णांक err = 0;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_allocate_contiguous() enter: width=%d, height=%d, format=%d, padded_width=%d, raw_bit_depth=%d\n",
			    width, height, क्रमmat, padded_width, raw_bit_depth);

	err = frame_allocate_with_data(frame, width, height, क्रमmat,
				       padded_width, raw_bit_depth, true);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_allocate_contiguous() leave: frame=%p\n",
			    frame ? *frame : (व्योम *)-1);

	वापस err;
पूर्ण

पूर्णांक ia_css_frame_allocate_contiguous_from_info(
    काष्ठा ia_css_frame **frame,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	पूर्णांक err = 0;

	निश्चित(frame);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_allocate_contiguous_from_info() enter:\n");
	err = ia_css_frame_allocate_contiguous(frame,
					       info->res.width,
					       info->res.height,
					       info->क्रमmat,
					       info->padded_width,
					       info->raw_bit_depth);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_allocate_contiguous_from_info() leave:\n");
	वापस err;
पूर्ण

व्योम ia_css_frame_मुक्त(काष्ठा ia_css_frame *frame)
अणु
	IA_CSS_ENTER_PRIVATE("frame = %p", frame);

	अगर (frame) अणु
		hmm_मुक्त(frame->data);
		kvमुक्त(frame);
	पूर्ण

	IA_CSS_LEAVE_PRIVATE("void");
पूर्ण

/**************************************************************************
**	Module खुला functions
**************************************************************************/

पूर्णांक ia_css_frame_check_info(स्थिर काष्ठा ia_css_frame_info *info)
अणु
	निश्चित(info);
	अगर (info->res.width == 0 || info->res.height == 0)
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक ia_css_frame_init_planes(काष्ठा ia_css_frame *frame)
अणु
	निश्चित(frame);

	चयन (frame->info.क्रमmat) अणु
	हाल IA_CSS_FRAME_FORMAT_MIPI:
		frame_init_mipi_plane(frame, &frame->planes.raw,
				      frame->info.res.height,
				      frame->info.padded_width,
				      frame->info.raw_bit_depth <= 8 ? 1 : 2);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RAW_PACKED:
		frame_init_raw_single_plane(frame, &frame->planes.raw,
					    frame->info.res.height,
					    frame->info.padded_width,
					    frame->info.raw_bit_depth);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RAW:
		frame_init_single_plane(frame, &frame->planes.raw,
					frame->info.res.height,
					frame->info.padded_width,
					frame->info.raw_bit_depth <= 8 ? 1 : 2);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RGB565:
		frame_init_single_plane(frame, &frame->planes.rgb,
					frame->info.res.height,
					frame->info.padded_width, 2);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_RGBA888:
		frame_init_single_plane(frame, &frame->planes.rgb,
					frame->info.res.height,
					frame->info.padded_width * 4, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_PLANAR_RGB888:
		frame_init_rgb_planes(frame, 1);
		अवरोध;
	/* yuyv and uyvu have the same frame layout, only the data
	 * positioning dअगरfers.
	 */
	हाल IA_CSS_FRAME_FORMAT_YUYV:
	हाल IA_CSS_FRAME_FORMAT_UYVY:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_YUV420_8:
	हाल IA_CSS_FRAME_FORMAT_CSI_MIPI_LEGACY_YUV420_8:
		frame_init_single_plane(frame, &frame->planes.yuyv,
					frame->info.res.height,
					frame->info.padded_width * 2, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV_LINE:
		/* Needs 3 extra lines to allow vf_pp prefetching */
		frame_init_single_plane(frame, &frame->planes.yuyv,
					frame->info.res.height * 3 / 2 + 3,
					frame->info.padded_width, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_NV11:
		frame_init_nv_planes(frame, 4, 1, 1);
		अवरोध;
	/* nv12 and nv21 have the same frame layout, only the data
	 * positioning dअगरfers.
	 */
	हाल IA_CSS_FRAME_FORMAT_NV12:
	हाल IA_CSS_FRAME_FORMAT_NV21:
	हाल IA_CSS_FRAME_FORMAT_NV12_TILEY:
		frame_init_nv_planes(frame, 2, 2, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_NV12_16:
		frame_init_nv_planes(frame, 2, 2, 2);
		अवरोध;
	/* nv16 and nv61 have the same frame layout, only the data
	 * positioning dअगरfers.
	 */
	हाल IA_CSS_FRAME_FORMAT_NV16:
	हाल IA_CSS_FRAME_FORMAT_NV61:
		frame_init_nv_planes(frame, 2, 1, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV420:
		frame_init_yuv_planes(frame, 2, 2, false, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV422:
		frame_init_yuv_planes(frame, 2, 1, false, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV444:
		frame_init_yuv_planes(frame, 1, 1, false, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV420_16:
		frame_init_yuv_planes(frame, 2, 2, false, 2);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YUV422_16:
		frame_init_yuv_planes(frame, 2, 1, false, 2);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YV12:
		frame_init_yuv_planes(frame, 2, 2, true, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_YV16:
		frame_init_yuv_planes(frame, 2, 1, true, 1);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_QPLANE6:
		frame_init_qplane6_planes(frame);
		अवरोध;
	हाल IA_CSS_FRAME_FORMAT_BINARY_8:
		frame_init_single_plane(frame, &frame->planes.binary.data,
					frame->info.res.height,
					frame->info.padded_width, 1);
		frame->planes.binary.size = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

व्योम ia_css_frame_info_set_width(काष्ठा ia_css_frame_info *info,
				 अचिन्हित पूर्णांक width,
				 अचिन्हित पूर्णांक min_padded_width)
अणु
	अचिन्हित पूर्णांक align;

	IA_CSS_ENTER_PRIVATE("info = %p,width = %d, minimum padded width = %d",
			     info, width, min_padded_width);
	अगर (!info) अणु
		IA_CSS_ERROR("NULL input parameter");
		IA_CSS_LEAVE_PRIVATE("");
		वापस;
	पूर्ण
	अगर (min_padded_width > width)
		align = min_padded_width;
	अन्यथा
		align = width;

	info->res.width = width;
	/* frames with a U and V plane of 8 bits per pixel need to have
	   all planes aligned, this means द्विगुन the alignment क्रम the
	   Y plane अगर the horizontal decimation is 2. */
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_YUV420 ||
	    info->क्रमmat == IA_CSS_FRAME_FORMAT_YV12 ||
	    info->क्रमmat == IA_CSS_FRAME_FORMAT_NV12 ||
	    info->क्रमmat == IA_CSS_FRAME_FORMAT_NV21 ||
	    info->क्रमmat == IA_CSS_FRAME_FORMAT_BINARY_8 ||
	    info->क्रमmat == IA_CSS_FRAME_FORMAT_YUV_LINE)
		info->padded_width =
		    CEIL_MUL(align, 2 * HIVE_ISP_DDR_WORD_BYTES);
	अन्यथा अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_NV12_TILEY)
		info->padded_width = CEIL_MUL(align, NV12_TILEY_TILE_WIDTH);
	अन्यथा अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW ||
		 info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW_PACKED)
		info->padded_width = CEIL_MUL(align, 2 * ISP_VEC_NELEMS);
	अन्यथा अणु
		info->padded_width = CEIL_MUL(align, HIVE_ISP_DDR_WORD_BYTES);
	पूर्ण
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_frame_info_set_क्रमmat(काष्ठा ia_css_frame_info *info,
				  क्रमागत ia_css_frame_क्रमmat क्रमmat)
अणु
	निश्चित(info);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_info_set_format() enter:\n");
	info->क्रमmat = क्रमmat;
पूर्ण

व्योम ia_css_frame_info_init(काष्ठा ia_css_frame_info *info,
			    अचिन्हित पूर्णांक width,
			    अचिन्हित पूर्णांक height,
			    क्रमागत ia_css_frame_क्रमmat क्रमmat,
			    अचिन्हित पूर्णांक aligned)
अणु
	IA_CSS_ENTER_PRIVATE("info = %p, width = %d, height = %d, format = %d, aligned = %d",
			     info, width, height, क्रमmat, aligned);
	अगर (!info) अणु
		IA_CSS_ERROR("NULL input parameter");
		IA_CSS_LEAVE_PRIVATE("");
		वापस;
	पूर्ण
	info->res.height = height;
	info->क्रमmat     = क्रमmat;
	ia_css_frame_info_set_width(info, width, aligned);
	IA_CSS_LEAVE_PRIVATE("");
पूर्ण

व्योम ia_css_frame_मुक्त_multiple(अचिन्हित पूर्णांक num_frames,
				काष्ठा ia_css_frame **frames_array)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < num_frames; i++) अणु
		अगर (frames_array[i]) अणु
			ia_css_frame_मुक्त(frames_array[i]);
			frames_array[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ia_css_frame_allocate_with_buffer_size(
    काष्ठा ia_css_frame **frame,
    स्थिर अचिन्हित पूर्णांक buffer_size_bytes,
    स्थिर bool contiguous)
अणु
	/* AM: Body coppied from frame_allocate_with_data(). */
	पूर्णांक err;
	काष्ठा ia_css_frame *me = frame_create(0, 0,
					       IA_CSS_FRAME_FORMAT_NUM,/* Not valid क्रमmat yet */
					       0, 0, contiguous, false);

	अगर (!me)
		वापस -ENOMEM;

	/* Get the data size */
	me->data_bytes = buffer_size_bytes;

	err = frame_allocate_buffer_data(me);

	अगर (err) अणु
		kvमुक्त(me);
		me = शून्य;
	पूर्ण

	*frame = me;

	वापस err;
पूर्ण

bool ia_css_frame_info_is_same_resolution(
    स्थिर काष्ठा ia_css_frame_info *info_a,
    स्थिर काष्ठा ia_css_frame_info *info_b)
अणु
	अगर (!info_a || !info_b)
		वापस false;
	वापस (info_a->res.width == info_b->res.width) &&
	       (info_a->res.height == info_b->res.height);
पूर्ण

bool ia_css_frame_is_same_type(स्थिर काष्ठा ia_css_frame *frame_a,
			       स्थिर काष्ठा ia_css_frame *frame_b)
अणु
	bool is_equal = false;
	स्थिर काष्ठा ia_css_frame_info *info_a = &frame_a->info,
						*info_b = &frame_b->info;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_is_same_type() enter:\n");

	अगर (!info_a || !info_b)
		वापस false;
	अगर (info_a->क्रमmat != info_b->क्रमmat)
		वापस false;
	अगर (info_a->padded_width != info_b->padded_width)
		वापस false;
	is_equal = ia_css_frame_info_is_same_resolution(info_a, info_b);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "ia_css_frame_is_same_type() leave:\n");

	वापस is_equal;
पूर्ण

व्योम
ia_css_dma_configure_from_info(
    काष्ठा dma_port_config *config,
    स्थिर काष्ठा ia_css_frame_info *info)
अणु
	अचिन्हित पूर्णांक is_raw_packed = info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW_PACKED;
	अचिन्हित पूर्णांक bits_per_pixel = is_raw_packed ? info->raw_bit_depth :
				      ia_css_elems_bytes_from_info(info) * 8;
	अचिन्हित पूर्णांक pix_per_ddrword = HIVE_ISP_DDR_WORD_BITS / bits_per_pixel;
	अचिन्हित पूर्णांक words_per_line = CEIL_DIV(info->padded_width, pix_per_ddrword);
	अचिन्हित पूर्णांक elems_b = pix_per_ddrword;

	config->stride = HIVE_ISP_DDR_WORD_BYTES * words_per_line;
	config->elems  = (uपूर्णांक8_t)elems_b;
	config->width  = (uपूर्णांक16_t)info->res.width;
	config->crop   = 0;
	निश्चित(config->width <= info->padded_width);
पूर्ण

/**************************************************************************
**	Static functions
**************************************************************************/

अटल व्योम frame_init_plane(काष्ठा ia_css_frame_plane *plane,
			     अचिन्हित पूर्णांक width,
			     अचिन्हित पूर्णांक stride,
			     अचिन्हित पूर्णांक height,
			     अचिन्हित पूर्णांक offset)
अणु
	plane->height = height;
	plane->width = width;
	plane->stride = stride;
	plane->offset = offset;
पूर्ण

अटल व्योम frame_init_single_plane(काष्ठा ia_css_frame *frame,
				    काष्ठा ia_css_frame_plane *plane,
				    अचिन्हित पूर्णांक height,
				    अचिन्हित पूर्णांक subpixels_per_line,
				    अचिन्हित पूर्णांक bytes_per_pixel)
अणु
	अचिन्हित पूर्णांक stride;

	stride = subpixels_per_line * bytes_per_pixel;
	/* Frame height needs to be even number - needed by hw ISYS2401
	   In हाल of odd number, round up to even.
	   Images won't be impacted by this round up,
	   only needed by jpeg/embedded data.
	   As दीर्घ as buffer allocation and release are using data_bytes,
	   there won't be memory leak. */
	frame->data_bytes = stride * CEIL_MUL2(height, 2);
	frame_init_plane(plane, subpixels_per_line, stride, height, 0);
	वापस;
पूर्ण

अटल व्योम frame_init_raw_single_plane(
    काष्ठा ia_css_frame *frame,
    काष्ठा ia_css_frame_plane *plane,
    अचिन्हित पूर्णांक height,
    अचिन्हित पूर्णांक subpixels_per_line,
    अचिन्हित पूर्णांक bits_per_pixel)
अणु
	अचिन्हित पूर्णांक stride;

	निश्चित(frame);

	stride = HIVE_ISP_DDR_WORD_BYTES *
		 CEIL_DIV(subpixels_per_line,
			  HIVE_ISP_DDR_WORD_BITS / bits_per_pixel);
	frame->data_bytes = stride * height;
	frame_init_plane(plane, subpixels_per_line, stride, height, 0);
	वापस;
पूर्ण

अटल व्योम frame_init_mipi_plane(काष्ठा ia_css_frame *frame,
				  काष्ठा ia_css_frame_plane *plane,
				  अचिन्हित पूर्णांक height,
				  अचिन्हित पूर्णांक subpixels_per_line,
				  अचिन्हित पूर्णांक bytes_per_pixel)
अणु
	अचिन्हित पूर्णांक stride;

	stride = subpixels_per_line * bytes_per_pixel;
	frame->data_bytes = 8388608; /* 8*1024*1024 */
	frame->valid = false;
	frame->contiguous = true;
	frame_init_plane(plane, subpixels_per_line, stride, height, 0);
	वापस;
पूर्ण

अटल व्योम frame_init_nv_planes(काष्ठा ia_css_frame *frame,
				 अचिन्हित पूर्णांक horizontal_decimation,
				 अचिन्हित पूर्णांक vertical_decimation,
				 अचिन्हित पूर्णांक bytes_per_element)
अणु
	अचिन्हित पूर्णांक y_width = frame->info.padded_width;
	अचिन्हित पूर्णांक y_height = frame->info.res.height;
	अचिन्हित पूर्णांक uv_width;
	अचिन्हित पूर्णांक uv_height;
	अचिन्हित पूर्णांक y_bytes;
	अचिन्हित पूर्णांक uv_bytes;
	अचिन्हित पूर्णांक y_stride;
	अचिन्हित पूर्णांक uv_stride;

	निश्चित(horizontal_decimation != 0 && vertical_decimation != 0);

	uv_width = 2 * (y_width / horizontal_decimation);
	uv_height = y_height / vertical_decimation;

	अगर (frame->info.क्रमmat == IA_CSS_FRAME_FORMAT_NV12_TILEY) अणु
		y_width   = CEIL_MUL(y_width,   NV12_TILEY_TILE_WIDTH);
		uv_width  = CEIL_MUL(uv_width,  NV12_TILEY_TILE_WIDTH);
		y_height  = CEIL_MUL(y_height,  NV12_TILEY_TILE_HEIGHT);
		uv_height = CEIL_MUL(uv_height, NV12_TILEY_TILE_HEIGHT);
	पूर्ण

	y_stride = y_width * bytes_per_element;
	uv_stride = uv_width * bytes_per_element;
	y_bytes = y_stride * y_height;
	uv_bytes = uv_stride * uv_height;

	frame->data_bytes = y_bytes + uv_bytes;
	frame_init_plane(&frame->planes.nv.y, y_width, y_stride, y_height, 0);
	frame_init_plane(&frame->planes.nv.uv, uv_width,
			 uv_stride, uv_height, y_bytes);
	वापस;
पूर्ण

अटल व्योम frame_init_yuv_planes(काष्ठा ia_css_frame *frame,
				  अचिन्हित पूर्णांक horizontal_decimation,
				  अचिन्हित पूर्णांक vertical_decimation,
				  bool swap_uv,
				  अचिन्हित पूर्णांक bytes_per_element)
अणु
	अचिन्हित पूर्णांक y_width = frame->info.padded_width,
		     y_height = frame->info.res.height,
		     uv_width = y_width / horizontal_decimation,
		     uv_height = y_height / vertical_decimation,
		     y_stride, y_bytes, uv_bytes, uv_stride;

	y_stride = y_width * bytes_per_element;
	uv_stride = uv_width * bytes_per_element;
	y_bytes = y_stride * y_height;
	uv_bytes = uv_stride * uv_height;

	frame->data_bytes = y_bytes + 2 * uv_bytes;
	frame_init_plane(&frame->planes.yuv.y, y_width, y_stride, y_height, 0);
	अगर (swap_uv) अणु
		frame_init_plane(&frame->planes.yuv.v, uv_width, uv_stride,
				 uv_height, y_bytes);
		frame_init_plane(&frame->planes.yuv.u, uv_width, uv_stride,
				 uv_height, y_bytes + uv_bytes);
	पूर्ण अन्यथा अणु
		frame_init_plane(&frame->planes.yuv.u, uv_width, uv_stride,
				 uv_height, y_bytes);
		frame_init_plane(&frame->planes.yuv.v, uv_width, uv_stride,
				 uv_height, y_bytes + uv_bytes);
	पूर्ण
	वापस;
पूर्ण

अटल व्योम frame_init_rgb_planes(काष्ठा ia_css_frame *frame,
				  अचिन्हित पूर्णांक bytes_per_element)
अणु
	अचिन्हित पूर्णांक width = frame->info.res.width,
		     height = frame->info.res.height, stride, bytes;

	stride = width * bytes_per_element;
	bytes = stride * height;
	frame->data_bytes = 3 * bytes;
	frame_init_plane(&frame->planes.planar_rgb.r, width, stride, height, 0);
	frame_init_plane(&frame->planes.planar_rgb.g,
			 width, stride, height, 1 * bytes);
	frame_init_plane(&frame->planes.planar_rgb.b,
			 width, stride, height, 2 * bytes);
	वापस;
पूर्ण

अटल व्योम frame_init_qplane6_planes(काष्ठा ia_css_frame *frame)
अणु
	अचिन्हित पूर्णांक width = frame->info.padded_width / 2,
		     height = frame->info.res.height / 2, bytes, stride;

	stride = width * 2;
	bytes = stride * height;

	frame->data_bytes = 6 * bytes;
	frame_init_plane(&frame->planes.plane6.r,
			 width, stride, height, 0 * bytes);
	frame_init_plane(&frame->planes.plane6.r_at_b,
			 width, stride, height, 1 * bytes);
	frame_init_plane(&frame->planes.plane6.gr,
			 width, stride, height, 2 * bytes);
	frame_init_plane(&frame->planes.plane6.gb,
			 width, stride, height, 3 * bytes);
	frame_init_plane(&frame->planes.plane6.b,
			 width, stride, height, 4 * bytes);
	frame_init_plane(&frame->planes.plane6.b_at_r,
			 width, stride, height, 5 * bytes);
	वापस;
पूर्ण

अटल पूर्णांक frame_allocate_buffer_data(काष्ठा ia_css_frame *frame)
अणु
#अगर_घोषित ISP2401
	IA_CSS_ENTER_LEAVE_PRIVATE("frame->data_bytes=%d\n", frame->data_bytes);
#पूर्ण_अगर
	frame->data = hmm_alloc(frame->data_bytes,
				HMM_BO_PRIVATE, 0, शून्य,
				frame->contiguous ?
				ATOMISP_MAP_FLAG_CONTIGUOUS : 0);

	अगर (frame->data == mmgr_शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल पूर्णांक frame_allocate_with_data(काष्ठा ia_css_frame **frame,
	अचिन्हित पूर्णांक width,
	अचिन्हित पूर्णांक height,
	क्रमागत ia_css_frame_क्रमmat क्रमmat,
	अचिन्हित पूर्णांक padded_width,
	अचिन्हित पूर्णांक raw_bit_depth,
	bool contiguous)
अणु
	पूर्णांक err;
	काष्ठा ia_css_frame *me = frame_create(width,
					       height,
					       क्रमmat,
					       padded_width,
					       raw_bit_depth,
					       contiguous,
					       true);

	अगर (!me)
		वापस -ENOMEM;

	err = ia_css_frame_init_planes(me);

	अगर (!err)
		err = frame_allocate_buffer_data(me);

	अगर (err) अणु
		kvमुक्त(me);
#अगर_अघोषित ISP2401
		वापस err;
#अन्यथा
		me = शून्य;
#पूर्ण_अगर
	पूर्ण

	*frame = me;

	वापस err;
पूर्ण

अटल काष्ठा ia_css_frame *frame_create(अचिन्हित पूर्णांक width,
	अचिन्हित पूर्णांक height,
	क्रमागत ia_css_frame_क्रमmat क्रमmat,
	अचिन्हित पूर्णांक padded_width,
	अचिन्हित पूर्णांक raw_bit_depth,
	bool contiguous,
	bool valid)
अणु
	काष्ठा ia_css_frame *me = kvदो_स्मृति(माप(*me), GFP_KERNEL);

	अगर (!me)
		वापस शून्य;

	स_रखो(me, 0, माप(*me));
	me->info.res.width = width;
	me->info.res.height = height;
	me->info.क्रमmat = क्रमmat;
	me->info.padded_width = padded_width;
	me->info.raw_bit_depth = raw_bit_depth;
	me->contiguous = contiguous;
	me->valid = valid;
	me->data_bytes = 0;
	me->data = mmgr_शून्य;
	/* To indicate it is not valid frame. */
	me->dynamic_queue_id = (पूर्णांक)SH_CSS_INVALID_QUEUE_ID;
	me->buf_type = IA_CSS_BUFFER_TYPE_INVALID;

	वापस me;
पूर्ण

अटल अचिन्हित
ia_css_elems_bytes_from_info(स्थिर काष्ठा ia_css_frame_info *info)
अणु
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_RGB565)
		वापस 2; /* bytes per pixel */
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_YUV420_16)
		वापस 2; /* bytes per pixel */
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_YUV422_16)
		वापस 2; /* bytes per pixel */
	/* Note: Essentially NV12_16 is a 2 bytes per pixel क्रमmat, this वापस value is used
	 * to configure DMA क्रम the output buffer,
	 * At least in SKC this data is overwritten by isp_output_init.sp.c except क्रम elements(elems),
	 * which is configured from this वापस value,
	 * NV12_16 is implemented by a द्विगुन buffer of 8 bit elements hence elems should be configured as 8 */
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_NV12_16)
		वापस 1; /* bytes per pixel */

	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW
	    || (info->क्रमmat == IA_CSS_FRAME_FORMAT_RAW_PACKED)) अणु
		अगर (info->raw_bit_depth)
			वापस CEIL_DIV(info->raw_bit_depth, 8);
		अन्यथा
			वापस 2; /* bytes per pixel */
	पूर्ण
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_PLANAR_RGB888)
		वापस 3; /* bytes per pixel */
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_RGBA888)
		वापस 4; /* bytes per pixel */
	अगर (info->क्रमmat == IA_CSS_FRAME_FORMAT_QPLANE6)
		वापस 2; /* bytes per pixel */
	वापस 1; /* Default is 1 byte per pixel */
पूर्ण

व्योम ia_css_frame_info_to_frame_sp_info(
    काष्ठा ia_css_frame_sp_info *to,
    स्थिर काष्ठा ia_css_frame_info *from)
अणु
	ia_css_resolution_to_sp_resolution(&to->res, &from->res);
	to->padded_width = (uपूर्णांक16_t)from->padded_width;
	to->क्रमmat = (uपूर्णांक8_t)from->क्रमmat;
	to->raw_bit_depth = (uपूर्णांक8_t)from->raw_bit_depth;
	to->raw_bayer_order = from->raw_bayer_order;
पूर्ण

व्योम ia_css_resolution_to_sp_resolution(
    काष्ठा ia_css_sp_resolution *to,
    स्थिर काष्ठा ia_css_resolution *from)
अणु
	to->width  = (uपूर्णांक16_t)from->width;
	to->height = (uपूर्णांक16_t)from->height;
पूर्ण

/* ISP2401 */
पूर्णांक
ia_css_frame_find_crop_resolution(स्थिर काष्ठा ia_css_resolution *in_res,
				  स्थिर काष्ठा ia_css_resolution *out_res,
				  काष्ठा ia_css_resolution *crop_res) अणु
	u32 wd_even_उच्चमान, ht_even_उच्चमान;
	u32 in_ratio, out_ratio;

	अगर ((!in_res) || (!out_res) || (!crop_res))
		वापस -EINVAL;

	IA_CSS_ENTER_PRIVATE("in(%ux%u) -> out(%ux%u)", in_res->width,
			     in_res->height, out_res->width, out_res->height);

	अगर ((in_res->width == 0)
	    || (in_res->height == 0)
	    || (out_res->width == 0)
	    || (out_res->height == 0))
		वापस -EINVAL;

	अगर ((out_res->width > in_res->width) ||
	    (out_res->height > in_res->height))
		वापस -EINVAL;

	/* If aspect ratio (width/height) of out_res is higher than the aspect
	 * ratio of the in_res, then we crop vertically, otherwise we crop
	 * horizontally.
	 */
	in_ratio = in_res->width * out_res->height;
	out_ratio = out_res->width * in_res->height;

	अगर (in_ratio == out_ratio)
	अणु
		crop_res->width = in_res->width;
		crop_res->height = in_res->height;
	पूर्ण अन्यथा अगर (out_ratio > in_ratio)
	अणु
		crop_res->width = in_res->width;
		crop_res->height = ROUND_DIV(out_res->height * crop_res->width,
					     out_res->width);
	पूर्ण अन्यथा
	अणु
		crop_res->height = in_res->height;
		crop_res->width = ROUND_DIV(out_res->width * crop_res->height,
					    out_res->height);
	पूर्ण

	/* Round new (cropped) width and height to an even number.
	 * binarydesc_calculate_bds_factor is such that we should consider as
	 * much of the input as possible. This is dअगरferent only when we end up
	 * with an odd number in the last step. So, we take the next even number
	 * अगर it falls within the input, otherwise take the previous even no.
	 */
	wd_even_उच्चमान = EVEN_CEIL(crop_res->width);
	ht_even_उच्चमान = EVEN_CEIL(crop_res->height);
	अगर ((wd_even_उच्चमान > in_res->width) || (ht_even_उच्चमान > in_res->height))
	अणु
		crop_res->width = EVEN_FLOOR(crop_res->width);
		crop_res->height = EVEN_FLOOR(crop_res->height);
	पूर्ण अन्यथा
	अणु
		crop_res->width = wd_even_उच्चमान;
		crop_res->height = ht_even_उच्चमान;
	पूर्ण

	IA_CSS_LEAVE_PRIVATE("in(%ux%u) -> out(%ux%u)", crop_res->width,
			     crop_res->height, out_res->width, out_res->height);
	वापस 0;
पूर्ण
