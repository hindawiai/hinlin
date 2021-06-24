<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IA_CSS_FRAME_COMM_H__
#घोषणा __IA_CSS_FRAME_COMM_H__

#समावेश "type_support.h"
#समावेश "platform_support.h"
#समावेश "runtime/bufq/interface/ia_css_bufq_comm.h"
#समावेश <प्रणाली_local.h>	 /* ia_css_ptr */

/*
 * These काष्ठाs are derived from काष्ठाs defined in ia_css_types.h
 * (just take out the "_sp" from the काष्ठा name to get the "original")
 * All the fields that are not needed by the SP are हटाओd.
 */
काष्ठा ia_css_frame_sp_plane अणु
	अचिन्हित पूर्णांक offset;	/* offset in bytes to start of frame data */
	/* offset is wrt data in sh_css_sp_sp_frame */
पूर्ण;

काष्ठा ia_css_frame_sp_binary_plane अणु
	अचिन्हित पूर्णांक size;
	काष्ठा ia_css_frame_sp_plane data;
पूर्ण;

काष्ठा ia_css_frame_sp_yuv_planes अणु
	काष्ठा ia_css_frame_sp_plane y;
	काष्ठा ia_css_frame_sp_plane u;
	काष्ठा ia_css_frame_sp_plane v;
पूर्ण;

काष्ठा ia_css_frame_sp_nv_planes अणु
	काष्ठा ia_css_frame_sp_plane y;
	काष्ठा ia_css_frame_sp_plane uv;
पूर्ण;

काष्ठा ia_css_frame_sp_rgb_planes अणु
	काष्ठा ia_css_frame_sp_plane r;
	काष्ठा ia_css_frame_sp_plane g;
	काष्ठा ia_css_frame_sp_plane b;
पूर्ण;

काष्ठा ia_css_frame_sp_plane6 अणु
	काष्ठा ia_css_frame_sp_plane r;
	काष्ठा ia_css_frame_sp_plane r_at_b;
	काष्ठा ia_css_frame_sp_plane gr;
	काष्ठा ia_css_frame_sp_plane gb;
	काष्ठा ia_css_frame_sp_plane b;
	काष्ठा ia_css_frame_sp_plane b_at_r;
पूर्ण;

काष्ठा ia_css_sp_resolution अणु
	u16 width;		/* width of valid data in pixels */
	u16 height;	/* Height of valid data in lines */
पूर्ण;

/*
 * Frame info काष्ठा. This describes the contents of an image frame buffer.
 */
काष्ठा ia_css_frame_sp_info अणु
	काष्ठा ia_css_sp_resolution res;
	u16 padded_width;		/* stride of line in memory
					(in pixels) */
	अचिन्हित अक्षर क्रमmat;		/* क्रमmat of the frame data */
	अचिन्हित अक्षर raw_bit_depth;	/* number of valid bits per pixel,
					only valid क्रम RAW bayer frames */
	अचिन्हित अक्षर raw_bayer_order;	/* bayer order, only valid
					क्रम RAW bayer frames */
	अचिन्हित अक्षर padding[3];	/* Extend to 32 bit multiple */
पूर्ण;

काष्ठा ia_css_buffer_sp अणु
	जोड़ अणु
		ia_css_ptr xmem_addr;
		क्रमागत sh_css_queue_id queue_id;
	पूर्ण buf_src;
	क्रमागत ia_css_buffer_type buf_type;
पूर्ण;

काष्ठा ia_css_frame_sp अणु
	काष्ठा ia_css_frame_sp_info info;
	काष्ठा ia_css_buffer_sp buf_attr;
	जोड़ अणु
		काष्ठा ia_css_frame_sp_plane raw;
		काष्ठा ia_css_frame_sp_plane rgb;
		काष्ठा ia_css_frame_sp_rgb_planes planar_rgb;
		काष्ठा ia_css_frame_sp_plane yuyv;
		काष्ठा ia_css_frame_sp_yuv_planes yuv;
		काष्ठा ia_css_frame_sp_nv_planes nv;
		काष्ठा ia_css_frame_sp_plane6 plane6;
		काष्ठा ia_css_frame_sp_binary_plane binary;
	पूर्ण planes;
पूर्ण;

व्योम ia_css_frame_info_to_frame_sp_info(
    काष्ठा ia_css_frame_sp_info *sp_info,
    स्थिर काष्ठा ia_css_frame_info *info);

व्योम ia_css_resolution_to_sp_resolution(
    काष्ठा ia_css_sp_resolution *sp_info,
    स्थिर काष्ठा ia_css_resolution *info);

#पूर्ण_अगर /*__IA_CSS_FRAME_COMM_H__*/
