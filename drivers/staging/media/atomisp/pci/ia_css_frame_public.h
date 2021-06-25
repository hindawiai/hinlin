<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IA_CSS_FRAME_PUBLIC_H
#घोषणा __IA_CSS_FRAME_PUBLIC_H

/* @file
 * This file contains काष्ठाs to describe various frame-क्रमmats supported by the ISP.
 */

#समावेश <type_support.h>
#समावेश "ia_css_err.h"
#समावेश "ia_css_types.h"
#समावेश "ia_css_frame_format.h"
#समावेश "ia_css_buffer.h"

/* For RAW input, the bayer order needs to be specअगरied separately. There
 *  are 4 possible orders. The name is स्थिरructed by taking the first two
 *  colors on the first line and the first two colors from the second line.
 */
क्रमागत ia_css_bayer_order अणु
	IA_CSS_BAYER_ORDER_GRBG, /** GRGRGRGRGR .. BGBGBGBGBG */
	IA_CSS_BAYER_ORDER_RGGB, /** RGRGRGRGRG .. GBGBGBGBGB */
	IA_CSS_BAYER_ORDER_BGGR, /** BGBGBGBGBG .. GRGRGRGRGR */
	IA_CSS_BAYER_ORDER_GBRG, /** GBGBGBGBGB .. RGRGRGRGRG */
पूर्ण;

#घोषणा IA_CSS_BAYER_ORDER_NUM (IA_CSS_BAYER_ORDER_GBRG + 1)

/* Frame plane काष्ठाure. This describes one plane in an image
 *  frame buffer.
 */
काष्ठा ia_css_frame_plane अणु
	अचिन्हित पूर्णांक height; /** height of a plane in lines */
	अचिन्हित पूर्णांक width;  /** width of a line, in DMA elements, note that
				  क्रम RGB565 the three subpixels are stored in
				  one element. For all other क्रमmats this is
				  the number of subpixels per line. */
	अचिन्हित पूर्णांक stride; /** stride of a line in bytes */
	अचिन्हित पूर्णांक offset; /** offset in bytes to start of frame data.
				  offset is wrt data field in ia_css_frame */
पूर्ण;

/* Binary "plane". This is used to story binary streams such as jpeg
 *  images. This is not actually a real plane.
 */
काष्ठा ia_css_frame_binary_plane अणु
	अचिन्हित पूर्णांक		  size; /** number of bytes in the stream */
	काष्ठा ia_css_frame_plane data; /** plane */
पूर्ण;

/* Container क्रम planar YUV frames. This contains 3 planes.
 */
काष्ठा ia_css_frame_yuv_planes अणु
	काष्ठा ia_css_frame_plane y; /** Y plane */
	काष्ठा ia_css_frame_plane u; /** U plane */
	काष्ठा ia_css_frame_plane v; /** V plane */
पूर्ण;

/* Container क्रम semi-planar YUV frames.
  */
काष्ठा ia_css_frame_nv_planes अणु
	काष्ठा ia_css_frame_plane y;  /** Y plane */
	काष्ठा ia_css_frame_plane uv; /** UV plane */
पूर्ण;

/* Container क्रम planar RGB frames. Each color has its own plane.
 */
काष्ठा ia_css_frame_rgb_planes अणु
	काष्ठा ia_css_frame_plane r; /** Red plane */
	काष्ठा ia_css_frame_plane g; /** Green plane */
	काष्ठा ia_css_frame_plane b; /** Blue plane */
पूर्ण;

/* Container क्रम 6-plane frames. These frames are used पूर्णांकernally
 *  in the advanced ISP only.
 */
काष्ठा ia_css_frame_plane6_planes अणु
	काष्ठा ia_css_frame_plane r;	  /** Red plane */
	काष्ठा ia_css_frame_plane r_at_b; /** Red at blue plane */
	काष्ठा ia_css_frame_plane gr;	  /** Red-green plane */
	काष्ठा ia_css_frame_plane gb;	  /** Blue-green plane */
	काष्ठा ia_css_frame_plane b;	  /** Blue plane */
	काष्ठा ia_css_frame_plane b_at_r; /** Blue at red plane */
पूर्ण;

/* Crop info काष्ठा - stores the lines to be cropped in isp */
काष्ठा ia_css_crop_info अणु
	/* the final start column and start line
	 * sum of lines to be cropped + bayer offset
	 */
	अचिन्हित पूर्णांक start_column;
	अचिन्हित पूर्णांक start_line;
पूर्ण;

/* Frame info काष्ठा. This describes the contents of an image frame buffer.
  */
काष्ठा ia_css_frame_info अणु
	काष्ठा ia_css_resolution res; /** Frame resolution (valid data) */
	अचिन्हित पूर्णांक padded_width; /** stride of line in memory (in pixels) */
	क्रमागत ia_css_frame_क्रमmat क्रमmat; /** क्रमmat of the frame data */
	अचिन्हित पूर्णांक raw_bit_depth; /** number of valid bits per pixel,
					 only valid क्रम RAW bayer frames */
	क्रमागत ia_css_bayer_order raw_bayer_order; /** bayer order, only valid
						      क्रम RAW bayer frames */
	/* the params below are computed based on bayer_order
	 * we can हटाओ the raw_bayer_order अगर it is redundant
	 * keeping it क्रम now as bxt and fpn code seem to use it
	 */
	काष्ठा ia_css_crop_info crop_info;
पूर्ण;

#घोषणा IA_CSS_BINARY_DEFAULT_FRAME_INFO अणु \
	.क्रमmat			= IA_CSS_FRAME_FORMAT_NUM,  \
	.raw_bayer_order	= IA_CSS_BAYER_ORDER_NUM, \
पूर्ण

/**
 *  Specअगरies the DVS loop delay in "frame periods"
 */
क्रमागत ia_css_frame_delay अणु
	IA_CSS_FRAME_DELAY_0, /** Frame delay = 0 */
	IA_CSS_FRAME_DELAY_1, /** Frame delay = 1 */
	IA_CSS_FRAME_DELAY_2  /** Frame delay = 2 */
पूर्ण;

क्रमागत ia_css_frame_flash_state अणु
	IA_CSS_FRAME_FLASH_STATE_NONE,
	IA_CSS_FRAME_FLASH_STATE_PARTIAL,
	IA_CSS_FRAME_FLASH_STATE_FULL
पूर्ण;

/* Frame काष्ठाure. This काष्ठाure describes an image buffer or frame.
 *  This is the मुख्य काष्ठाure used क्रम all input and output images.
 */
काष्ठा ia_css_frame अणु
	काष्ठा ia_css_frame_info info; /** info काष्ठा describing the frame */
	ia_css_ptr   data;	       /** poपूर्णांकer to start of image data */
	अचिन्हित पूर्णांक data_bytes;       /** size of image data in bytes */
	/* LA: move this to ia_css_buffer */
	/*
	 * -1 अगर data address is अटल during lअगरe समय of pipeline
	 * >=0 अगर data address can change per pipeline/frame iteration
	 *     index to dynamic data: ia_css_frame_in, ia_css_frame_out
	 *                            ia_css_frame_out_vf
	 *     index to host-sp queue id: queue_0, queue_1 etc.
	 */
	पूर्णांक dynamic_queue_id;
	/*
	 * अगर it is dynamic frame, buf_type indicates which buffer type it
	 * should use क्रम event generation. we have this because in vf_pp
	 * binary, we use output port, but we expect VF_OUTPUT_DONE event
	 */
	क्रमागत ia_css_buffer_type buf_type;
	क्रमागत ia_css_frame_flash_state flash_state;
	अचिन्हित पूर्णांक exp_id;
	/** exposure id, see ia_css_event_खुला.h क्रम more detail */
	u32 isp_config_id; /** Unique ID to track which config was actually applied to a particular frame */
	bool valid; /** First video output frame is not valid */
	bool contiguous; /** memory is allocated physically contiguously */
	जोड़ अणु
		अचिन्हित पूर्णांक	_initialisation_dummy;
		काष्ठा ia_css_frame_plane raw;
		काष्ठा ia_css_frame_plane rgb;
		काष्ठा ia_css_frame_rgb_planes planar_rgb;
		काष्ठा ia_css_frame_plane yuyv;
		काष्ठा ia_css_frame_yuv_planes yuv;
		काष्ठा ia_css_frame_nv_planes nv;
		काष्ठा ia_css_frame_plane6_planes plane6;
		काष्ठा ia_css_frame_binary_plane binary;
	पूर्ण planes; /** frame planes, select the right one based on
		       info.क्रमmat */
पूर्ण;

#घोषणा DEFAULT_FRAME अणु \
	.info			= IA_CSS_BINARY_DEFAULT_FRAME_INFO, \
	.dynamic_queue_id	= SH_CSS_INVALID_QUEUE_ID, \
	.buf_type		= IA_CSS_BUFFER_TYPE_INVALID, \
	.flash_state		= IA_CSS_FRAME_FLASH_STATE_NONE, \
पूर्ण

/* @brief Fill a frame with zeros
 *
 * @param	frame		The frame.
 * @वापस	None
 *
 * Fill a frame with pixel values of zero
 */
व्योम ia_css_frame_zero(काष्ठा ia_css_frame *frame);

/* @brief Allocate a CSS frame काष्ठाure
 *
 * @param	frame		The allocated frame.
 * @param	width		The width (in pixels) of the frame.
 * @param	height		The height (in lines) of the frame.
 * @param	क्रमmat		The frame क्रमmat.
 * @param	stride		The padded stride, in pixels.
 * @param	raw_bit_depth	The raw bit depth, in bits.
 * @वापस			The error code.
 *
 * Allocate a CSS frame काष्ठाure. The memory क्रम the frame data will be
 * allocated in the CSS address space.
 */
पूर्णांक
ia_css_frame_allocate(काष्ठा ia_css_frame **frame,
		      अचिन्हित पूर्णांक width,
		      अचिन्हित पूर्णांक height,
		      क्रमागत ia_css_frame_क्रमmat क्रमmat,
		      अचिन्हित पूर्णांक stride,
		      अचिन्हित पूर्णांक raw_bit_depth);

/* @brief Allocate a CSS frame काष्ठाure using a frame info काष्ठाure.
 *
 * @param	frame	The allocated frame.
 * @param[in]	info	The frame info काष्ठाure.
 * @वापस		The error code.
 *
 * Allocate a frame using the resolution and क्रमmat from a frame info काष्ठा.
 * This is a convenience function, implemented on top of
 * ia_css_frame_allocate().
 */
पूर्णांक
ia_css_frame_allocate_from_info(काष्ठा ia_css_frame **frame,
				स्थिर काष्ठा ia_css_frame_info *info);
/* @brief Free a CSS frame काष्ठाure.
 *
 * @param[in]	frame	Poपूर्णांकer to the frame.
 * @वापस	None
 *
 * Free a CSS frame काष्ठाure. This will मुक्त both the frame काष्ठाure
 * and the pixel data poपूर्णांकer contained within the frame काष्ठाure.
 */
व्योम
ia_css_frame_मुक्त(काष्ठा ia_css_frame *frame);

/* @brief Allocate a contiguous CSS frame काष्ठाure
 *
 * @param	frame		The allocated frame.
 * @param	width		The width (in pixels) of the frame.
 * @param	height		The height (in lines) of the frame.
 * @param	क्रमmat		The frame क्रमmat.
 * @param	stride		The padded stride, in pixels.
 * @param	raw_bit_depth	The raw bit depth, in bits.
 * @वापस			The error code.
 *
 * Contiguous frame allocation, only क्रम FPGA display driver which needs
 * physically contiguous memory.
 * Deprecated.
 */
पूर्णांक
ia_css_frame_allocate_contiguous(काष्ठा ia_css_frame **frame,
				 अचिन्हित पूर्णांक width,
				 अचिन्हित पूर्णांक height,
				 क्रमागत ia_css_frame_क्रमmat क्रमmat,
				 अचिन्हित पूर्णांक stride,
				 अचिन्हित पूर्णांक raw_bit_depth);

/* @brief Allocate a contiguous CSS frame from a frame info काष्ठाure.
 *
 * @param	frame	The allocated frame.
 * @param[in]	info	The frame info काष्ठाure.
 * @वापस		The error code.
 *
 * Allocate a frame using the resolution and क्रमmat from a frame info काष्ठा.
 * This is a convenience function, implemented on top of
 * ia_css_frame_allocate_contiguous().
 * Only क्रम FPGA display driver which needs physically contiguous memory.
 * Deprecated.
 */
पूर्णांक
ia_css_frame_allocate_contiguous_from_info(काष्ठा ia_css_frame **frame,
	स्थिर काष्ठा ia_css_frame_info *info);

/* @brief Allocate a CSS frame काष्ठाure using a frame info काष्ठाure.
 *
 * @param	frame	The allocated frame.
 * @param[in]	info	The frame info काष्ठाure.
 * @वापस		The error code.
 *
 * Allocate an empty CSS frame with no data buffer using the parameters
 * in the frame info.
 */
पूर्णांक
ia_css_frame_create_from_info(काष्ठा ia_css_frame **frame,
			      स्थिर काष्ठा ia_css_frame_info *info);

/* @brief Set a mapped data buffer to a CSS frame
 *
 * @param[in]	frame       Valid CSS frame poपूर्णांकer
 * @param[in]	mapped_data  Mapped data buffer to be asचिन्हित to the CSS frame
 * @param[in]	data_size_bytes  Size of the mapped_data in bytes
 * @वापस      The error code.
 *
 * Sets a mapped data buffer to this frame. This function can be called multiple
 * बार with dअगरferent buffers or शून्य to reset the data poपूर्णांकer. This API
 * would not try मुक्त the mapped_data and its the callers responsiblity to
 * मुक्त the mapped_data buffer. However अगर ia_css_frame_मुक्त() is called and
 * the frame had a valid data buffer, it would be मुक्तd aदीर्घ with the frame.
 */
पूर्णांक
ia_css_frame_set_data(काष्ठा ia_css_frame *frame,
		      स्थिर ia_css_ptr   mapped_data,
		      माप_प्रकार data_size_bytes);

/* @brief Map an existing frame data poपूर्णांकer to a CSS frame.
 *
 * @param	frame		Poपूर्णांकer to the frame to be initialized
 * @param[in]	info		The frame info.
 * @param[in]	data		Poपूर्णांकer to the allocated frame data.
 * @param[in]	attribute	Attributes to be passed to mmgr_mmap.
 * @param[in]	context		Poपूर्णांकer to the a context to be passed to mmgr_mmap.
 * @वापस			The allocated frame काष्ठाure.
 *
 * This function maps a pre-allocated poपूर्णांकer पूर्णांकo a CSS frame. This can be
 * used when an upper software layer is responsible क्रम allocating the frame
 * data and it wants to share that frame poपूर्णांकer with the CSS code.
 * This function will fill the CSS frame काष्ठाure just like
 * ia_css_frame_allocate() करोes, but instead of allocating the memory, it will
 * map the pre-allocated memory पूर्णांकo the CSS address space.
 */
पूर्णांक
ia_css_frame_map(काष्ठा ia_css_frame **frame,
		 स्थिर काष्ठा ia_css_frame_info *info,
		 स्थिर व्योम __user *data,
		 u16 attribute,
		 अचिन्हित पूर्णांक pgnr);

/* @brief Unmap a CSS frame काष्ठाure.
 *
 * @param[in]	frame	Poपूर्णांकer to the CSS frame.
 * @वापस	None
 *
 * This function unmaps the frame data poपूर्णांकer within a CSS frame and
 * then मुक्तs the CSS frame काष्ठाure. Use this क्रम frame poपूर्णांकers created
 * using ia_css_frame_map().
 */
व्योम
ia_css_frame_unmap(काष्ठा ia_css_frame *frame);

#पूर्ण_अगर /* __IA_CSS_FRAME_PUBLIC_H */
