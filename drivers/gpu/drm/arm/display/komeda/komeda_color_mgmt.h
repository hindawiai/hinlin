<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (C) COPYRIGHT 2019 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */

#अगर_अघोषित _KOMEDA_COLOR_MGMT_H_
#घोषणा _KOMEDA_COLOR_MGMT_H_

#समावेश <drm/drm_color_mgmt.h>

#घोषणा KOMEDA_N_YUV2RGB_COEFFS		12
#घोषणा KOMEDA_N_RGB2YUV_COEFFS		12
#घोषणा KOMEDA_COLOR_PRECISION		12
#घोषणा KOMEDA_N_GAMMA_COEFFS		65
#घोषणा KOMEDA_COLOR_LUT_SIZE		BIT(KOMEDA_COLOR_PRECISION)
#घोषणा KOMEDA_N_CTM_COEFFS		9

व्योम drm_lut_to_fgamma_coeffs(काष्ठा drm_property_blob *lut_blob, u32 *coeffs);
व्योम drm_cपंचांग_to_coeffs(काष्ठा drm_property_blob *cपंचांग_blob, u32 *coeffs);

स्थिर s32 *komeda_select_yuv2rgb_coeffs(u32 color_encoding, u32 color_range);

#पूर्ण_अगर /*_KOMEDA_COLOR_MGMT_H_*/
