<शैली गुरु>
/*
 * Copyright (c) 2016 Intel Corporation
 *
 * Permission to use, copy, modअगरy, distribute, and sell this software and its
 * करोcumentation क्रम any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting करोcumentation, and
 * that the name of the copyright holders not be used in advertising or
 * खुलाity pertaining to distribution of the software without specअगरic,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software क्रम any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INसूचीECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#अगर_अघोषित __DRM_COLOR_MGMT_H__
#घोषणा __DRM_COLOR_MGMT_H__

#समावेश <linux/प्रकार.स>
#समावेश <drm/drm_property.h>

काष्ठा drm_crtc;
काष्ठा drm_plane;

/**
 * drm_color_lut_extract - clamp and round LUT entries
 * @user_input: input value
 * @bit_precision: number of bits the hw LUT supports
 *
 * Extract a degamma/gamma LUT value provided by user (in the क्रमm of
 * &drm_color_lut entries) and round it to the precision supported by the
 * hardware.
 */
अटल अंतरभूत u32 drm_color_lut_extract(u32 user_input, पूर्णांक bit_precision)
अणु
	u32 val = user_input;
	u32 max = 0xffff >> (16 - bit_precision);

	/* Round only अगर we're not using full precision. */
	अगर (bit_precision < 16) अणु
		val += 1UL << (16 - bit_precision - 1);
		val >>= 16 - bit_precision;
	पूर्ण

	वापस clamp_val(val, 0, max);
पूर्ण

u64 drm_color_cपंचांग_s31_32_to_qm_n(u64 user_input, u32 m, u32 n);

व्योम drm_crtc_enable_color_mgmt(काष्ठा drm_crtc *crtc,
				uपूर्णांक degamma_lut_size,
				bool has_cपंचांग,
				uपूर्णांक gamma_lut_size);

पूर्णांक drm_mode_crtc_set_gamma_size(काष्ठा drm_crtc *crtc,
				 पूर्णांक gamma_size);

/**
 * drm_color_lut_size - calculate the number of entries in the LUT
 * @blob: blob containing the LUT
 *
 * Returns:
 * The number of entries in the color LUT stored in @blob.
 */
अटल अंतरभूत पूर्णांक drm_color_lut_size(स्थिर काष्ठा drm_property_blob *blob)
अणु
	वापस blob->length / माप(काष्ठा drm_color_lut);
पूर्ण

क्रमागत drm_color_encoding अणु
	DRM_COLOR_YCBCR_BT601,
	DRM_COLOR_YCBCR_BT709,
	DRM_COLOR_YCBCR_BT2020,
	DRM_COLOR_ENCODING_MAX,
पूर्ण;

क्रमागत drm_color_range अणु
	DRM_COLOR_YCBCR_LIMITED_RANGE,
	DRM_COLOR_YCBCR_FULL_RANGE,
	DRM_COLOR_RANGE_MAX,
पूर्ण;

पूर्णांक drm_plane_create_color_properties(काष्ठा drm_plane *plane,
				      u32 supported_encodings,
				      u32 supported_ranges,
				      क्रमागत drm_color_encoding शेष_encoding,
				      क्रमागत drm_color_range शेष_range);

/**
 * क्रमागत drm_color_lut_tests - hw-specअगरic LUT tests to perक्रमm
 *
 * The drm_color_lut_check() function takes a biपंचांगask of the values here to
 * determine which tests to apply to a userspace-provided LUT.
 */
क्रमागत drm_color_lut_tests अणु
	/**
	 * @DRM_COLOR_LUT_EQUAL_CHANNELS:
	 *
	 * Checks whether the entries of a LUT all have equal values क्रम the
	 * red, green, and blue channels.  Intended क्रम hardware that only
	 * accepts a single value per LUT entry and assumes that value applies
	 * to all three color components.
	 */
	DRM_COLOR_LUT_EQUAL_CHANNELS = BIT(0),

	/**
	 * @DRM_COLOR_LUT_NON_DECREASING:
	 *
	 * Checks whether the entries of a LUT are always flat or increasing
	 * (never decreasing).
	 */
	DRM_COLOR_LUT_NON_DECREASING = BIT(1),
पूर्ण;

पूर्णांक drm_color_lut_check(स्थिर काष्ठा drm_property_blob *lut, u32 tests);
#पूर्ण_अगर
