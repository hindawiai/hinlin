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

#अगर_अघोषित __IA_CSS_FRAME_H__
#घोषणा __IA_CSS_FRAME_H__

/* ISP2401 */
#समावेश <ia_css_types.h>

#समावेश <ia_css_frame_क्रमmat.h>
#समावेश <ia_css_frame_खुला.h>
#समावेश "dma.h"

/*********************************************************************
****	Frame INFO APIs
**********************************************************************/
/* @brief Sets the given width and alignment to the frame info
 *
 * @param
 * @param[in]	info        The info to which parameters would set
 * @param[in]	width       The width to be set to info
 * @param[in]	aligned     The aligned to be set to info
 * @वापस
 */
व्योम ia_css_frame_info_set_width(काष्ठा ia_css_frame_info *info,
				 अचिन्हित पूर्णांक width,
				 अचिन्हित पूर्णांक min_padded_width);

/* @brief Sets the given क्रमmat to the frame info
 *
 * @param
 * @param[in]	info        The info to which parameters would set
 * @param[in]	क्रमmat      The क्रमmat to be set to info
 * @वापस
 */
व्योम ia_css_frame_info_set_क्रमmat(काष्ठा ia_css_frame_info *info,
				  क्रमागत ia_css_frame_क्रमmat क्रमmat);

/* @brief Sets the frame info with the given parameters
 *
 * @param
 * @param[in]	info        The info to which parameters would set
 * @param[in]	width       The width to be set to info
 * @param[in]	height      The height to be set to info
 * @param[in]	क्रमmat      The क्रमmat to be set to info
 * @param[in]	aligned     The aligned to be set to info
 * @वापस
 */
व्योम ia_css_frame_info_init(काष्ठा ia_css_frame_info *info,
			    अचिन्हित पूर्णांक width,
			    अचिन्हित पूर्णांक height,
			    क्रमागत ia_css_frame_क्रमmat क्रमmat,
			    अचिन्हित पूर्णांक aligned);

/* @brief Checks whether 2 frame infos has the same resolution
 *
 * @param
 * @param[in]	frame_a         The first frame to be compared
 * @param[in]	frame_b         The second frame to be compared
 * @वापस      Returns true अगर the frames are equal
 */
bool ia_css_frame_info_is_same_resolution(
    स्थिर काष्ठा ia_css_frame_info *info_a,
    स्थिर काष्ठा ia_css_frame_info *info_b);

/* @brief Check the frame info is valid
 *
 * @param
 * @param[in]	info       The frame attributes to be initialized
 * @वापस	The error code.
 */
पूर्णांक ia_css_frame_check_info(स्थिर काष्ठा ia_css_frame_info *info);

/*********************************************************************
****	Frame APIs
**********************************************************************/

/* @brief Initialize the plane depending on the frame type
 *
 * @param
 * @param[in]	frame           The frame attributes to be initialized
 * @वापस	The error code.
 */
पूर्णांक ia_css_frame_init_planes(काष्ठा ia_css_frame *frame);

/* @brief Free an array of frames
 *
 * @param
 * @param[in]	num_frames      The number of frames to be मुक्तd in the array
 * @param[in]   **frames_array  The array of frames to be हटाओd
 * @वापस
 */
व्योम ia_css_frame_मुक्त_multiple(अचिन्हित पूर्णांक num_frames,
				काष्ठा ia_css_frame **frames_array);

/* @brief Allocate a CSS frame काष्ठाure of given size in bytes..
 *
 * @param	frame	The allocated frame.
 * @param[in]	size_bytes	The frame size in bytes.
 * @param[in]	contiguous	Allocate memory physically contiguously or not.
 * @वापस	The error code.
 *
 * Allocate a frame using the given size in bytes.
 * The frame काष्ठाure is partially null initialized.
 */
पूर्णांक ia_css_frame_allocate_with_buffer_size(
    काष्ठा ia_css_frame **frame,
    स्थिर अचिन्हित पूर्णांक size_bytes,
    स्थिर bool contiguous);

/* @brief Check whether 2 frames are same type
 *
 * @param
 * @param[in]	frame_a         The first frame to be compared
 * @param[in]	frame_b         The second frame to be compared
 * @वापस      Returns true अगर the frames are equal
 */
bool ia_css_frame_is_same_type(
    स्थिर काष्ठा ia_css_frame *frame_a,
    स्थिर काष्ठा ia_css_frame *frame_b);

/* @brief Configure a dma port from frame info
 *
 * @param
 * @param[in]	config         The DAM port configuration
 * @param[in]	info           The frame info
 * @वापस
 */
व्योम ia_css_dma_configure_from_info(
    काष्ठा dma_port_config *config,
    स्थिर काष्ठा ia_css_frame_info *info);

/* ISP2401 */
/* @brief Finds the cropping resolution
 * This function finds the maximum cropping resolution in an input image keeping
 * the aspect ratio क्रम the given output resolution.Calculates the coordinates
 * क्रम cropping from the center and वापसs the starting pixel location of the
 * region in the input image. Also वापसs the dimension of the cropping
 * resolution.
 *
 * @param
 * @param[in]	in_res		Resolution of input image
 * @param[in]	out_res		Resolution of output image
 * @param[out]	crop_res	Crop resolution of input image
 * @वापस	Returns 0 or -EINVAL on error
 */
पूर्णांक
ia_css_frame_find_crop_resolution(स्थिर काष्ठा ia_css_resolution *in_res,
				  स्थिर काष्ठा ia_css_resolution *out_res,
				  काष्ठा ia_css_resolution *crop_res);

#पूर्ण_अगर /* __IA_CSS_FRAME_H__ */
