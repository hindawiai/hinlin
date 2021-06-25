<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2019 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */

#समावेश "komeda_color_mgmt.h"

/* 10bit precision YUV2RGB matrix */
अटल स्थिर s32 yuv2rgb_bt601_narrow[KOMEDA_N_YUV2RGB_COEFFS] = अणु
	1192,    0, 1634,
	1192, -401, -832,
	1192, 2066,    0,
	  64,  512,  512
पूर्ण;

अटल स्थिर s32 yuv2rgb_bt601_wide[KOMEDA_N_YUV2RGB_COEFFS] = अणु
	1024,    0, 1436,
	1024, -352, -731,
	1024, 1815,    0,
	   0,  512,  512
पूर्ण;

अटल स्थिर s32 yuv2rgb_bt709_narrow[KOMEDA_N_YUV2RGB_COEFFS] = अणु
	1192,    0, 1836,
	1192, -218, -546,
	1192, 2163,    0,
	  64,  512,  512
पूर्ण;

अटल स्थिर s32 yuv2rgb_bt709_wide[KOMEDA_N_YUV2RGB_COEFFS] = अणु
	1024,    0, 1613,
	1024, -192, -479,
	1024, 1900,    0,
	   0,  512,  512
पूर्ण;

अटल स्थिर s32 yuv2rgb_bt2020[KOMEDA_N_YUV2RGB_COEFFS] = अणु
	1024,    0, 1476,
	1024, -165, -572,
	1024, 1884,    0,
	   0,  512,  512
पूर्ण;

स्थिर s32 *komeda_select_yuv2rgb_coeffs(u32 color_encoding, u32 color_range)
अणु
	bool narrow = color_range == DRM_COLOR_YCBCR_LIMITED_RANGE;
	स्थिर s32 *coeffs;

	चयन (color_encoding) अणु
	हाल DRM_COLOR_YCBCR_BT709:
		coeffs = narrow ? yuv2rgb_bt709_narrow : yuv2rgb_bt709_wide;
		अवरोध;
	हाल DRM_COLOR_YCBCR_BT601:
		coeffs = narrow ? yuv2rgb_bt601_narrow : yuv2rgb_bt601_wide;
		अवरोध;
	हाल DRM_COLOR_YCBCR_BT2020:
		coeffs = yuv2rgb_bt2020;
		अवरोध;
	शेष:
		coeffs = शून्य;
		अवरोध;
	पूर्ण

	वापस coeffs;
पूर्ण

काष्ठा gamma_curve_sector अणु
	u32 boundary_start;
	u32 num_of_segments;
	u32 segment_width;
पूर्ण;

काष्ठा gamma_curve_segment अणु
	u32 start;
	u32 end;
पूर्ण;

अटल काष्ठा gamma_curve_sector sector_tbl[] = अणु
	अणु 0,    4,  4   पूर्ण,
	अणु 16,   4,  4   पूर्ण,
	अणु 32,   4,  8   पूर्ण,
	अणु 64,   4,  16  पूर्ण,
	अणु 128,  4,  32  पूर्ण,
	अणु 256,  4,  64  पूर्ण,
	अणु 512,  16, 32  पूर्ण,
	अणु 1024, 24, 128 पूर्ण,
पूर्ण;

अटल व्योम
drm_lut_to_coeffs(काष्ठा drm_property_blob *lut_blob, u32 *coeffs,
		  काष्ठा gamma_curve_sector *sector_tbl, u32 num_sectors)
अणु
	काष्ठा drm_color_lut *lut;
	u32 i, j, in, num = 0;

	अगर (!lut_blob)
		वापस;

	lut = lut_blob->data;

	क्रम (i = 0; i < num_sectors; i++) अणु
		क्रम (j = 0; j < sector_tbl[i].num_of_segments; j++) अणु
			in = sector_tbl[i].boundary_start +
			     j * sector_tbl[i].segment_width;

			coeffs[num++] = drm_color_lut_extract(lut[in].red,
						KOMEDA_COLOR_PRECISION);
		पूर्ण
	पूर्ण

	coeffs[num] = BIT(KOMEDA_COLOR_PRECISION);
पूर्ण

व्योम drm_lut_to_fgamma_coeffs(काष्ठा drm_property_blob *lut_blob, u32 *coeffs)
अणु
	drm_lut_to_coeffs(lut_blob, coeffs, sector_tbl, ARRAY_SIZE(sector_tbl));
पूर्ण

व्योम drm_cपंचांग_to_coeffs(काष्ठा drm_property_blob *cपंचांग_blob, u32 *coeffs)
अणु
	काष्ठा drm_color_cपंचांग *cपंचांग;
	u32 i;

	अगर (!cपंचांग_blob)
		वापस;

	cपंचांग = cपंचांग_blob->data;

	क्रम (i = 0; i < KOMEDA_N_CTM_COEFFS; i++)
		coeffs[i] = drm_color_cपंचांग_s31_32_to_qm_n(cपंचांग->matrix[i], 3, 12);
पूर्ण
