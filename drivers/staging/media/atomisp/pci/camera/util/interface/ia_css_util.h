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

#अगर_अघोषित __IA_CSS_UTIL_H__
#घोषणा __IA_CSS_UTIL_H__

#समावेश <linux/त्रुटिसं.स>

#समावेश <ia_css_err.h>
#समावेश <type_support.h>
#समावेश <ia_css_frame_खुला.h>
#समावेश <ia_css_stream_खुला.h>
#समावेश <ia_css_stream_क्रमmat.h>

/* @brief convert "errno" error code to "ia_css_err" error code
 *
 * @param[in]	"errno" error code
 * @वापस	"ia_css_err" error code
 *
 */
पूर्णांक ia_css_convert_त्रुटि_सं(
    पूर्णांक in_err);

/* @brief check vf frame info.
 *
 * @param[in] info
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_util_check_vf_info(
    स्थिर काष्ठा ia_css_frame_info *स्थिर info);

/* @brief check input configuration.
 *
 * @param[in] stream_config
 * @param[in] must_be_raw
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_util_check_input(
    स्थिर काष्ठा ia_css_stream_config *स्थिर stream_config,
    bool must_be_raw,
    bool must_be_yuv);

/* @brief check vf and out frame info.
 *
 * @param[in] out_info
 * @param[in] vf_info
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_util_check_vf_out_info(
    स्थिर काष्ठा ia_css_frame_info *स्थिर out_info,
    स्थिर काष्ठा ia_css_frame_info *स्थिर vf_info);

/* @brief check width and height
 *
 * @param[in] width
 * @param[in] height
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_util_check_res(
    अचिन्हित पूर्णांक width,
    अचिन्हित पूर्णांक height);

/* ISP2401 */
/* @brief compare resolutions (less or equal)
 *
 * @param[in] a resolution
 * @param[in] b resolution
 * @वापस    true अगर both dimensions of a are less or
 *            equal than those of b, false otherwise
 *
 */
bool ia_css_util_res_leq(
    काष्ठा ia_css_resolution a,
    काष्ठा ia_css_resolution b);

/* ISP2401 */
/**
 * @brief Check अगर resolution is zero
 *
 * @param[in] resolution The resolution to check
 *
 * @वापसs true अगर resolution is zero
 */
bool ia_css_util_resolution_is_zero(
    स्थिर काष्ठा ia_css_resolution resolution);

/* ISP2401 */
/**
 * @brief Check अगर resolution is even
 *
 * @param[in] resolution The resolution to check
 *
 * @वापसs true अगर resolution is even
 */
bool ia_css_util_resolution_is_even(
    स्थिर काष्ठा ia_css_resolution resolution);

/* @brief check width and height
 *
 * @param[in] stream_क्रमmat
 * @param[in] two_ppc
 * @वापस bits per pixel based on given parameters.
 *
 */
अचिन्हित पूर्णांक ia_css_util_input_क्रमmat_bpp(
    क्रमागत atomisp_input_क्रमmat stream_क्रमmat,
    bool two_ppc);

/* @brief check अगर input क्रमmat it raw
 *
 * @param[in] stream_क्रमmat
 * @वापस true अगर the input क्रमmat is raw or false otherwise
 *
 */
bool ia_css_util_is_input_क्रमmat_raw(
    क्रमागत atomisp_input_क्रमmat stream_क्रमmat);

/* @brief check अगर input क्रमmat it yuv
 *
 * @param[in] stream_क्रमmat
 * @वापस true अगर the input क्रमmat is yuv or false otherwise
 *
 */
bool ia_css_util_is_input_क्रमmat_yuv(
    क्रमागत atomisp_input_क्रमmat stream_क्रमmat);

#पूर्ण_अगर /* __IA_CSS_UTIL_H__ */
