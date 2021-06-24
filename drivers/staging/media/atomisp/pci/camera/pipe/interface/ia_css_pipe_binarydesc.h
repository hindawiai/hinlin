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

#अगर_अघोषित __IA_CSS_PIPE_BINARYDESC_H__
#घोषणा __IA_CSS_PIPE_BINARYDESC_H__

#समावेश <ia_css_types.h>		/* ia_css_pipe */
#समावेश <ia_css_frame_खुला.h>	/* ia_css_frame_info */
#समावेश <ia_css_binary.h>		/* ia_css_binary_descr */

/* @brief Get a binary descriptor क्रम copy.
 *
 * @param[in] pipe
 * @param[out] copy_desc
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @param[in/out] vf_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_copy_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *copy_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info);

/* @brief Get a binary descriptor क्रम vfpp.
 *
 * @param[in] pipe
 * @param[out] vfpp_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_vfpp_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *vf_pp_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info);

/* @brief Get numerator and denominator of bayer करोwnscaling factor.
 *
 * @param[in] bds_factor: The bayer करोwnscaling factor.
 *		(= The bds_factor member in the sh_css_bds_factor काष्ठाure.)
 * @param[out] bds_factor_numerator: The numerator of the bayer करोwnscaling factor.
 *		(= The numerator member in the sh_css_bds_factor काष्ठाure.)
 * @param[out] bds_factor_denominator: The denominator of the bayer करोwnscaling factor.
 *		(= The denominator member in the sh_css_bds_factor काष्ठाure.)
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक sh_css_bds_factor_get_numerator_denominator(
    अचिन्हित पूर्णांक bds_factor,
    अचिन्हित पूर्णांक *bds_factor_numerator,
    अचिन्हित पूर्णांक *bds_factor_denominator);

/* @brief Get a binary descriptor क्रम preview stage.
 *
 * @param[in] pipe
 * @param[out] preview_descr
 * @param[in/out] in_info
 * @param[in/out] bds_out_info
 * @param[in/out] out_info
 * @param[in/out] vf_info
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_pipe_get_preview_binarydesc(
    काष्ठा ia_css_pipe *स्थिर pipe,
    काष्ठा ia_css_binary_descr *preview_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *bds_out_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info);

/* @brief Get a binary descriptor क्रम video stage.
 *
 * @param[in/out] pipe
 * @param[out] video_descr
 * @param[in/out] in_info
 * @param[in/out] bds_out_info
 * @param[in/out] vf_info
 * @वापस	0 or error code upon error.
 *
 */
पूर्णांक ia_css_pipe_get_video_binarydesc(
    काष्ठा ia_css_pipe *स्थिर pipe,
    काष्ठा ia_css_binary_descr *video_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *bds_out_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info,
    पूर्णांक stream_config_left_padding);

/* @brief Get a binary descriptor क्रम yuv scaler stage.
 *
 * @param[in/out] pipe
 * @param[out] yuv_scaler_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @param[in/out] पूर्णांकernal_out_info
 * @param[in/out] vf_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_yuvscaler_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *yuv_scaler_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *पूर्णांकernal_out_info,
    काष्ठा ia_css_frame_info *vf_info);

/* @brief Get a binary descriptor क्रम capture pp stage.
 *
 * @param[in/out] pipe
 * @param[out] capture_pp_descr
 * @param[in/out] in_info
 * @param[in/out] vf_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_capturepp_binarydesc(
    काष्ठा ia_css_pipe *स्थिर pipe,
    काष्ठा ia_css_binary_descr *capture_pp_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info);

/* @brief Get a binary descriptor क्रम primary capture.
 *
 * @param[in] pipe
 * @param[out] prim_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @param[in/out] vf_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_primary_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *prim_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info,
    अचिन्हित पूर्णांक stage_idx);

/* @brief Get a binary descriptor क्रम pre gdc stage.
 *
 * @param[in] pipe
 * @param[out] pre_gdc_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_pre_gdc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *gdc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info);

/* @brief Get a binary descriptor क्रम gdc stage.
 *
 * @param[in] pipe
 * @param[out] gdc_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_gdc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *gdc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info);

/* @brief Get a binary descriptor क्रम post gdc.
 *
 * @param[in] pipe
 * @param[out] post_gdc_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @param[in/out] vf_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_post_gdc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *post_gdc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info);

/* @brief Get a binary descriptor क्रम de.
 *
 * @param[in] pipe
 * @param[out] pre_de_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_pre_de_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *pre_de_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info);

/* @brief Get a binary descriptor क्रम pre anr stage.
 *
 * @param[in] pipe
 * @param[out] pre_anr_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_pre_anr_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *pre_anr_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info);

/* @brief Get a binary descriptor क्रम ANR stage.
 *
 * @param[in] pipe
 * @param[out] anr_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_anr_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *anr_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info);

/* @brief Get a binary descriptor क्रम post anr stage.
 *
 * @param[in] pipe
 * @param[out] post_anr_descr
 * @param[in/out] in_info
 * @param[in/out] out_info
 * @param[in/out] vf_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_post_anr_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *post_anr_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info,
    काष्ठा ia_css_frame_info *vf_info);

/* @brief Get a binary descriptor क्रम ldc stage.
 *
 * @param[in/out] pipe
 * @param[out] capture_pp_descr
 * @param[in/out] in_info
 * @param[in/out] vf_info
 * @वापस    None
 *
 */
व्योम ia_css_pipe_get_ldc_binarydesc(
    काष्ठा ia_css_pipe स्थिर *स्थिर pipe,
    काष्ठा ia_css_binary_descr *ldc_descr,
    काष्ठा ia_css_frame_info *in_info,
    काष्ठा ia_css_frame_info *out_info);

/* @brief Calculates the required BDS factor
 *
 * @param[in] input_res
 * @param[in] output_res
 * @param[in/out] bds_factor
 * @वापस	0 or error code upon error.
 */
पूर्णांक binarydesc_calculate_bds_factor(
    काष्ठा ia_css_resolution input_res,
    काष्ठा ia_css_resolution output_res,
    अचिन्हित पूर्णांक *bds_factor);

#पूर्ण_अगर /* __IA_CSS_PIPE_BINARYDESC_H__ */
