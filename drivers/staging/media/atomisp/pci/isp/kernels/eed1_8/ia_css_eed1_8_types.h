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

#अगर_अघोषित __IA_CSS_EED1_8_TYPES_H
#घोषणा __IA_CSS_EED1_8_TYPES_H

/* @file
* CSS-API header file क्रम Edge Enhanced Demosaic parameters.
*/

#समावेश "type_support.h"

/**
 * \मrief EED1_8 खुला parameters.
 * \details Struct with all parameters क्रम the EED1.8 kernel that can be set
 * from the CSS API.
 */

/* parameter list is based on ISP261 CSS API खुला parameter list_all.xlsx from 28-01-2015 */

/* Number of segments + 1 segment used in edge reliability enhancement
 * Ineffective: N/A
 * Default:	9
 */
#घोषणा IA_CSS_NUMBER_OF_DEW_ENHANCE_SEGMENTS	9

/* Edge Enhanced Demosaic configuration
 *
 * ISP2.6.1: EED1_8 is used.
 */

काष्ठा ia_css_eed1_8_config अणु
	s32 rbzp_strength;	/** Strength of zipper reduction. */

	s32 fcstrength;	/** Strength of false color reduction. */
	s32 fcthres_0;	/** Threshold to prevent chroma coring due to noise or green disparity in dark region. */
	s32 fcthres_1;	/** Threshold to prevent chroma coring due to noise or green disparity in bright region. */
	s32 fc_sat_coef;	/** How much color saturation to मुख्यtain in high color saturation region. */
	s32 fc_coring_prm;	/** Chroma coring coefficient क्रम tपूर्णांक color suppression. */

	s32 aerel_thres0;	/** Threshold क्रम Non-Directional Reliability at dark region. */
	s32 aerel_gain0;	/** Gain क्रम Non-Directional Reliability at dark region. */
	s32 aerel_thres1;	/** Threshold क्रम Non-Directional Reliability at bright region. */
	s32 aerel_gain1;	/** Gain क्रम Non-Directional Reliability at bright region. */

	s32 derel_thres0;	/** Threshold क्रम Directional Reliability at dark region. */
	s32 derel_gain0;	/** Gain क्रम Directional Reliability at dark region. */
	s32 derel_thres1;	/** Threshold क्रम Directional Reliability at bright region. */
	s32 derel_gain1;	/** Gain क्रम Directional Reliability at bright region. */

	s32 coring_pos0;	/** Positive Edge Coring Threshold in dark region. */
	s32 coring_pos1;	/** Positive Edge Coring Threshold in bright region. */
	s32 coring_neg0;	/** Negative Edge Coring Threshold in dark region. */
	s32 coring_neg1;	/** Negative Edge Coring Threshold in bright region. */

	s32 gain_exp;	/** Common Exponent of Gain. */
	s32 gain_pos0;	/** Gain क्रम Positive Edge in dark region. */
	s32 gain_pos1;	/** Gain क्रम Positive Edge in bright region. */
	s32 gain_neg0;	/** Gain क्रम Negative Edge in dark region. */
	s32 gain_neg1;	/** Gain क्रम Negative Edge in bright region. */

	s32 pos_margin0;	/** Margin क्रम Positive Edge in dark region. */
	s32 pos_margin1;	/** Margin क्रम Positive Edge in bright region. */
	s32 neg_margin0;	/** Margin क्रम Negative Edge in dark region. */
	s32 neg_margin1;	/** Margin क्रम Negative Edge in bright region. */

	s32 dew_enhance_seg_x[IA_CSS_NUMBER_OF_DEW_ENHANCE_SEGMENTS];		/** Segment data क्रम directional edge weight: X. */
	s32 dew_enhance_seg_y[IA_CSS_NUMBER_OF_DEW_ENHANCE_SEGMENTS];		/** Segment data क्रम directional edge weight: Y. */
	s32 dew_enhance_seg_slope[(IA_CSS_NUMBER_OF_DEW_ENHANCE_SEGMENTS -
				   1)];	/** Segment data क्रम directional edge weight: Slope. */
	s32 dew_enhance_seg_exp[(IA_CSS_NUMBER_OF_DEW_ENHANCE_SEGMENTS -
				 1)];	/** Segment data क्रम directional edge weight: Exponent. */
	s32 dedgew_max;	/** Max Weight क्रम Directional Edge. */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_EED1_8_TYPES_H */
