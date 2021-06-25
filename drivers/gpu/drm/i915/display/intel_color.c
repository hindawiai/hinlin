<शैली गुरु>
/*
 * Copyright तऊ 2016 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#समावेश "intel_color.h"
#समावेश "intel_display_types.h"

#घोषणा CTM_COEFF_SIGN	(1ULL << 63)

#घोषणा CTM_COEFF_1_0	(1ULL << 32)
#घोषणा CTM_COEFF_2_0	(CTM_COEFF_1_0 << 1)
#घोषणा CTM_COEFF_4_0	(CTM_COEFF_2_0 << 1)
#घोषणा CTM_COEFF_8_0	(CTM_COEFF_4_0 << 1)
#घोषणा CTM_COEFF_0_5	(CTM_COEFF_1_0 >> 1)
#घोषणा CTM_COEFF_0_25	(CTM_COEFF_0_5 >> 1)
#घोषणा CTM_COEFF_0_125	(CTM_COEFF_0_25 >> 1)

#घोषणा CTM_COEFF_LIMITED_RANGE ((235ULL - 16ULL) * CTM_COEFF_1_0 / 255)

#घोषणा CTM_COEFF_NEGATIVE(coeff)	(((coeff) & CTM_COEFF_SIGN) != 0)
#घोषणा CTM_COEFF_ABS(coeff)		((coeff) & (CTM_COEFF_SIGN - 1))

#घोषणा LEGACY_LUT_LENGTH		256

/*
 * ILK+ csc matrix:
 *
 * |R/Cr|   | c0 c1 c2 |   ( |R/Cr|   |preoff0| )   |postoff0|
 * |G/Y | = | c3 c4 c5 | x ( |G/Y | + |preoff1| ) + |postoff1|
 * |B/Cb|   | c6 c7 c8 |   ( |B/Cb|   |preoff2| )   |postoff2|
 *
 * ILK/SNB करोn't have explicit post offsets, and instead
 * CSC_MODE_YUV_TO_RGB and CSC_BLACK_SCREEN_OFFSET are used:
 *  CSC_MODE_YUV_TO_RGB=0 + CSC_BLACK_SCREEN_OFFSET=0 -> 1/2, 0, 1/2
 *  CSC_MODE_YUV_TO_RGB=0 + CSC_BLACK_SCREEN_OFFSET=1 -> 1/2, 1/16, 1/2
 *  CSC_MODE_YUV_TO_RGB=1 + CSC_BLACK_SCREEN_OFFSET=0 -> 0, 0, 0
 *  CSC_MODE_YUV_TO_RGB=1 + CSC_BLACK_SCREEN_OFFSET=1 -> 1/16, 1/16, 1/16
 */

/*
 * Extract the CSC coefficient from a CTM coefficient (in U32.32 fixed poपूर्णांक
 * क्रमmat). This macro takes the coefficient we want transक्रमmed and the
 * number of fractional bits.
 *
 * We only have a 9 bits precision winकरोw which slides depending on the value
 * of the CTM coefficient and we ग_लिखो the value from bit 3. We also round the
 * value.
 */
#घोषणा ILK_CSC_COEFF_FP(coeff, fbits)	\
	(clamp_val(((coeff) >> (32 - (fbits) - 3)) + 4, 0, 0xfff) & 0xff8)

#घोषणा ILK_CSC_COEFF_LIMITED_RANGE 0x0dc0
#घोषणा ILK_CSC_COEFF_1_0 0x7800

#घोषणा ILK_CSC_POSTOFF_LIMITED_RANGE (16 * (1 << 12) / 255)

/* Nop pre/post offsets */
अटल स्थिर u16 ilk_csc_off_zero[3] = अणुपूर्ण;

/* Identity matrix */
अटल स्थिर u16 ilk_csc_coeff_identity[9] = अणु
	ILK_CSC_COEFF_1_0, 0, 0,
	0, ILK_CSC_COEFF_1_0, 0,
	0, 0, ILK_CSC_COEFF_1_0,
पूर्ण;

/* Limited range RGB post offsets */
अटल स्थिर u16 ilk_csc_postoff_limited_range[3] = अणु
	ILK_CSC_POSTOFF_LIMITED_RANGE,
	ILK_CSC_POSTOFF_LIMITED_RANGE,
	ILK_CSC_POSTOFF_LIMITED_RANGE,
पूर्ण;

/* Full range RGB -> limited range RGB matrix */
अटल स्थिर u16 ilk_csc_coeff_limited_range[9] = अणु
	ILK_CSC_COEFF_LIMITED_RANGE, 0, 0,
	0, ILK_CSC_COEFF_LIMITED_RANGE, 0,
	0, 0, ILK_CSC_COEFF_LIMITED_RANGE,
पूर्ण;

/* BT.709 full range RGB -> limited range YCbCr matrix */
अटल स्थिर u16 ilk_csc_coeff_rgb_to_ycbcr[9] = अणु
	0x1e08, 0x9cc0, 0xb528,
	0x2ba8, 0x09d8, 0x37e8,
	0xbce8, 0x9ad8, 0x1e08,
पूर्ण;

/* Limited range YCbCr post offsets */
अटल स्थिर u16 ilk_csc_postoff_rgb_to_ycbcr[3] = अणु
	0x0800, 0x0100, 0x0800,
पूर्ण;

अटल bool lut_is_legacy(स्थिर काष्ठा drm_property_blob *lut)
अणु
	वापस drm_color_lut_size(lut) == LEGACY_LUT_LENGTH;
पूर्ण

अटल bool crtc_state_is_legacy_gamma(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	वापस !crtc_state->hw.degamma_lut &&
		!crtc_state->hw.cपंचांग &&
		crtc_state->hw.gamma_lut &&
		lut_is_legacy(crtc_state->hw.gamma_lut);
पूर्ण

/*
 * When using limited range, multiply the matrix given by userspace by
 * the matrix that we would use क्रम the limited range.
 */
अटल u64 *cपंचांग_mult_by_limited(u64 *result, स्थिर u64 *input)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 9; i++) अणु
		u64 user_coeff = input[i];
		u32 limited_coeff = CTM_COEFF_LIMITED_RANGE;
		u32 असल_coeff = clamp_val(CTM_COEFF_ABS(user_coeff), 0,
					  CTM_COEFF_4_0 - 1) >> 2;

		/*
		 * By scaling every co-efficient with limited range (16-235)
		 * vs full range (0-255) the final o/p will be scaled करोwn to
		 * fit in the limited range supported by the panel.
		 */
		result[i] = mul_u32_u32(limited_coeff, असल_coeff) >> 30;
		result[i] |= user_coeff & CTM_COEFF_SIGN;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम ilk_update_pipe_csc(काष्ठा पूर्णांकel_crtc *crtc,
				स्थिर u16 preoff[3],
				स्थिर u16 coeff[9],
				स्थिर u16 postoff[3])
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_PRखातापूर्णF_HI(pipe), preoff[0]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_PRखातापूर्णF_ME(pipe), preoff[1]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_PRखातापूर्णF_LO(pipe), preoff[2]);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_COEFF_RY_GY(pipe),
		       coeff[0] << 16 | coeff[1]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_COEFF_BY(pipe), coeff[2] << 16);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_COEFF_RU_GU(pipe),
		       coeff[3] << 16 | coeff[4]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_COEFF_BU(pipe), coeff[5] << 16);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_COEFF_RV_GV(pipe),
		       coeff[6] << 16 | coeff[7]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_COEFF_BV(pipe), coeff[8] << 16);

	अगर (DISPLAY_VER(dev_priv) >= 7) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_POSTOFF_HI(pipe),
			       postoff[0]);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_POSTOFF_ME(pipe),
			       postoff[1]);
		पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_POSTOFF_LO(pipe),
			       postoff[2]);
	पूर्ण
पूर्ण

अटल व्योम icl_update_output_csc(काष्ठा पूर्णांकel_crtc *crtc,
				  स्थिर u16 preoff[3],
				  स्थिर u16 coeff[9],
				  स्थिर u16 postoff[3])
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_PRखातापूर्णF_HI(pipe), preoff[0]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_PRखातापूर्णF_ME(pipe), preoff[1]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_PRखातापूर्णF_LO(pipe), preoff[2]);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_COEFF_RY_GY(pipe),
		       coeff[0] << 16 | coeff[1]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_COEFF_BY(pipe),
		       coeff[2] << 16);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_COEFF_RU_GU(pipe),
		       coeff[3] << 16 | coeff[4]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_COEFF_BU(pipe),
		       coeff[5] << 16);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_COEFF_RV_GV(pipe),
		       coeff[6] << 16 | coeff[7]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_COEFF_BV(pipe),
		       coeff[8] << 16);

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_POSTOFF_HI(pipe), postoff[0]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_POSTOFF_ME(pipe), postoff[1]);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_OUTPUT_POSTOFF_LO(pipe), postoff[2]);
पूर्ण

अटल bool ilk_csc_limited_range(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	/*
	 * FIXME अगर there's a gamma LUT after the CSC, we should
	 * करो the range compression using the gamma LUT instead.
	 */
	वापस crtc_state->limited_color_range &&
		(IS_HASWELL(dev_priv) || IS_BROADWELL(dev_priv) ||
		 IS_DISPLAY_RANGE(dev_priv, 9, 10));
पूर्ण

अटल व्योम ilk_csc_convert_cपंचांग(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				u16 coeffs[9])
अणु
	स्थिर काष्ठा drm_color_cपंचांग *cपंचांग = crtc_state->hw.cपंचांग->data;
	स्थिर u64 *input;
	u64 temp[9];
	पूर्णांक i;

	अगर (ilk_csc_limited_range(crtc_state))
		input = cपंचांग_mult_by_limited(temp, cपंचांग->matrix);
	अन्यथा
		input = cपंचांग->matrix;

	/*
	 * Convert fixed poपूर्णांक S31.32 input to क्रमmat supported by the
	 * hardware.
	 */
	क्रम (i = 0; i < 9; i++) अणु
		u64 असल_coeff = ((1ULL << 63) - 1) & input[i];

		/*
		 * Clamp input value to min/max supported by
		 * hardware.
		 */
		असल_coeff = clamp_val(असल_coeff, 0, CTM_COEFF_4_0 - 1);

		coeffs[i] = 0;

		/* sign bit */
		अगर (CTM_COEFF_NEGATIVE(input[i]))
			coeffs[i] |= 1 << 15;

		अगर (असल_coeff < CTM_COEFF_0_125)
			coeffs[i] |= (3 << 12) |
				ILK_CSC_COEFF_FP(असल_coeff, 12);
		अन्यथा अगर (असल_coeff < CTM_COEFF_0_25)
			coeffs[i] |= (2 << 12) |
				ILK_CSC_COEFF_FP(असल_coeff, 11);
		अन्यथा अगर (असल_coeff < CTM_COEFF_0_5)
			coeffs[i] |= (1 << 12) |
				ILK_CSC_COEFF_FP(असल_coeff, 10);
		अन्यथा अगर (असल_coeff < CTM_COEFF_1_0)
			coeffs[i] |= ILK_CSC_COEFF_FP(असल_coeff, 9);
		अन्यथा अगर (असल_coeff < CTM_COEFF_2_0)
			coeffs[i] |= (7 << 12) |
				ILK_CSC_COEFF_FP(असल_coeff, 8);
		अन्यथा
			coeffs[i] |= (6 << 12) |
				ILK_CSC_COEFF_FP(असल_coeff, 7);
	पूर्ण
पूर्ण

अटल व्योम ilk_load_csc_matrix(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	bool limited_color_range = ilk_csc_limited_range(crtc_state);

	अगर (crtc_state->hw.cपंचांग) अणु
		u16 coeff[9];

		ilk_csc_convert_cपंचांग(crtc_state, coeff);
		ilk_update_pipe_csc(crtc, ilk_csc_off_zero, coeff,
				    limited_color_range ?
				    ilk_csc_postoff_limited_range :
				    ilk_csc_off_zero);
	पूर्ण अन्यथा अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB) अणु
		ilk_update_pipe_csc(crtc, ilk_csc_off_zero,
				    ilk_csc_coeff_rgb_to_ycbcr,
				    ilk_csc_postoff_rgb_to_ycbcr);
	पूर्ण अन्यथा अगर (limited_color_range) अणु
		ilk_update_pipe_csc(crtc, ilk_csc_off_zero,
				    ilk_csc_coeff_limited_range,
				    ilk_csc_postoff_limited_range);
	पूर्ण अन्यथा अगर (crtc_state->csc_enable) अणु
		/*
		 * On GLK+ both pipe CSC and degamma LUT are controlled
		 * by csc_enable. Hence क्रम the हालs where the degama
		 * LUT is needed but CSC is not we need to load an
		 * identity matrix.
		 */
		drm_WARN_ON(&dev_priv->drm, !IS_CANNONLAKE(dev_priv) &&
			    !IS_GEMINILAKE(dev_priv));

		ilk_update_pipe_csc(crtc, ilk_csc_off_zero,
				    ilk_csc_coeff_identity,
				    ilk_csc_off_zero);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_MODE(crtc->pipe),
		       crtc_state->csc_mode);
पूर्ण

अटल व्योम icl_load_csc_matrix(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (crtc_state->hw.cपंचांग) अणु
		u16 coeff[9];

		ilk_csc_convert_cपंचांग(crtc_state, coeff);
		ilk_update_pipe_csc(crtc, ilk_csc_off_zero,
				    coeff, ilk_csc_off_zero);
	पूर्ण

	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB) अणु
		icl_update_output_csc(crtc, ilk_csc_off_zero,
				      ilk_csc_coeff_rgb_to_ycbcr,
				      ilk_csc_postoff_rgb_to_ycbcr);
	पूर्ण अन्यथा अगर (crtc_state->limited_color_range) अणु
		icl_update_output_csc(crtc, ilk_csc_off_zero,
				      ilk_csc_coeff_limited_range,
				      ilk_csc_postoff_limited_range);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPE_CSC_MODE(crtc->pipe),
		       crtc_state->csc_mode);
पूर्ण

अटल व्योम chv_load_cgm_csc(काष्ठा पूर्णांकel_crtc *crtc,
			     स्थिर काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_color_cपंचांग *cपंचांग = blob->data;
	क्रमागत pipe pipe = crtc->pipe;
	u16 coeffs[9];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeffs); i++) अणु
		u64 असल_coeff = ((1ULL << 63) - 1) & cपंचांग->matrix[i];

		/* Round coefficient. */
		असल_coeff += 1 << (32 - 13);
		/* Clamp to hardware limits. */
		असल_coeff = clamp_val(असल_coeff, 0, CTM_COEFF_8_0 - 1);

		coeffs[i] = 0;

		/* Write coefficients in S3.12 क्रमmat. */
		अगर (cपंचांग->matrix[i] & (1ULL << 63))
			coeffs[i] |= 1 << 15;

		coeffs[i] |= ((असल_coeff >> 32) & 7) << 12;
		coeffs[i] |= (असल_coeff >> 20) & 0xfff;
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_CSC_COEFF01(pipe),
		       coeffs[1] << 16 | coeffs[0]);
	पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_CSC_COEFF23(pipe),
		       coeffs[3] << 16 | coeffs[2]);
	पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_CSC_COEFF45(pipe),
		       coeffs[5] << 16 | coeffs[4]);
	पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_CSC_COEFF67(pipe),
		       coeffs[7] << 16 | coeffs[6]);
	पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_CSC_COEFF8(pipe),
		       coeffs[8]);
पूर्ण

/* convert hw value with given bit_precision to lut property val */
अटल u32 पूर्णांकel_color_lut_pack(u32 val, पूर्णांक bit_precision)
अणु
	u32 max = 0xffff >> (16 - bit_precision);

	val = clamp_val(val, 0, max);

	अगर (bit_precision < 16)
		val <<= 16 - bit_precision;

	वापस val;
पूर्ण

अटल u32 i9xx_lut_8(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस drm_color_lut_extract(color->red, 8) << 16 |
		drm_color_lut_extract(color->green, 8) << 8 |
		drm_color_lut_extract(color->blue, 8);
पूर्ण

अटल व्योम i9xx_lut_8_pack(काष्ठा drm_color_lut *entry, u32 val)
अणु
	entry->red = पूर्णांकel_color_lut_pack(REG_FIELD_GET(LGC_PALETTE_RED_MASK, val), 8);
	entry->green = पूर्णांकel_color_lut_pack(REG_FIELD_GET(LGC_PALETTE_GREEN_MASK, val), 8);
	entry->blue = पूर्णांकel_color_lut_pack(REG_FIELD_GET(LGC_PALETTE_BLUE_MASK, val), 8);
पूर्ण

/* i965+ "10.6" bit पूर्णांकerpolated क्रमmat "even DW" (low 8 bits) */
अटल u32 i965_lut_10p6_ldw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस (color->red & 0xff) << 16 |
		(color->green & 0xff) << 8 |
		(color->blue & 0xff);
पूर्ण

/* i965+ "10.6" पूर्णांकerpolated क्रमmat "odd DW" (high 8 bits) */
अटल u32 i965_lut_10p6_udw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस (color->red >> 8) << 16 |
		(color->green >> 8) << 8 |
		(color->blue >> 8);
पूर्ण

अटल व्योम i965_lut_10p6_pack(काष्ठा drm_color_lut *entry, u32 ldw, u32 udw)
अणु
	entry->red = REG_FIELD_GET(PALETTE_RED_MASK, udw) << 8 |
		REG_FIELD_GET(PALETTE_RED_MASK, ldw);
	entry->green = REG_FIELD_GET(PALETTE_GREEN_MASK, udw) << 8 |
		REG_FIELD_GET(PALETTE_GREEN_MASK, ldw);
	entry->blue = REG_FIELD_GET(PALETTE_BLUE_MASK, udw) << 8 |
		REG_FIELD_GET(PALETTE_BLUE_MASK, ldw);
पूर्ण

अटल u16 i965_lut_11p6_max_pack(u32 val)
अणु
	/* PIPEGCMAX is 11.6, clamp to 10.6 */
	वापस clamp_val(val, 0, 0xffff);
पूर्ण

अटल u32 ilk_lut_10(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस drm_color_lut_extract(color->red, 10) << 20 |
		drm_color_lut_extract(color->green, 10) << 10 |
		drm_color_lut_extract(color->blue, 10);
पूर्ण

अटल व्योम ilk_lut_10_pack(काष्ठा drm_color_lut *entry, u32 val)
अणु
	entry->red = पूर्णांकel_color_lut_pack(REG_FIELD_GET(PREC_PALETTE_RED_MASK, val), 10);
	entry->green = पूर्णांकel_color_lut_pack(REG_FIELD_GET(PREC_PALETTE_GREEN_MASK, val), 10);
	entry->blue = पूर्णांकel_color_lut_pack(REG_FIELD_GET(PREC_PALETTE_BLUE_MASK, val), 10);
पूर्ण

अटल व्योम icl_lut_multi_seg_pack(काष्ठा drm_color_lut *entry, u32 ldw, u32 udw)
अणु
	entry->red = REG_FIELD_GET(PAL_PREC_MULTI_SEG_RED_UDW_MASK, udw) << 6 |
				   REG_FIELD_GET(PAL_PREC_MULTI_SEG_RED_LDW_MASK, ldw);
	entry->green = REG_FIELD_GET(PAL_PREC_MULTI_SEG_GREEN_UDW_MASK, udw) << 6 |
				     REG_FIELD_GET(PAL_PREC_MULTI_SEG_GREEN_LDW_MASK, ldw);
	entry->blue = REG_FIELD_GET(PAL_PREC_MULTI_SEG_BLUE_UDW_MASK, udw) << 6 |
				    REG_FIELD_GET(PAL_PREC_MULTI_SEG_BLUE_LDW_MASK, ldw);
पूर्ण

अटल व्योम i9xx_color_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe));
	val &= ~PIPECONF_GAMMA_MODE_MASK_I9XX;
	val |= PIPECONF_GAMMA_MODE(crtc_state->gamma_mode);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(pipe), val);
पूर्ण

अटल व्योम ilk_color_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val;

	val = पूर्णांकel_de_पढ़ो(dev_priv, PIPECONF(pipe));
	val &= ~PIPECONF_GAMMA_MODE_MASK_ILK;
	val |= PIPECONF_GAMMA_MODE(crtc_state->gamma_mode);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPECONF(pipe), val);

	ilk_load_csc_matrix(crtc_state);
पूर्ण

अटल व्योम hsw_color_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	पूर्णांकel_de_ग_लिखो(dev_priv, GAMMA_MODE(crtc->pipe),
		       crtc_state->gamma_mode);

	ilk_load_csc_matrix(crtc_state);
पूर्ण

अटल व्योम skl_color_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 val = 0;

	/*
	 * We करोn't (yet) allow userspace to control the pipe background color,
	 * so क्रमce it to black, but apply pipe gamma and CSC appropriately
	 * so that its handling will match how we program our planes.
	 */
	अगर (crtc_state->gamma_enable)
		val |= SKL_BOTTOM_COLOR_GAMMA_ENABLE;
	अगर (crtc_state->csc_enable)
		val |= SKL_BOTTOM_COLOR_CSC_ENABLE;
	पूर्णांकel_de_ग_लिखो(dev_priv, SKL_BOTTOM_COLOR(pipe), val);

	पूर्णांकel_de_ग_लिखो(dev_priv, GAMMA_MODE(crtc->pipe),
		       crtc_state->gamma_mode);

	अगर (DISPLAY_VER(dev_priv) >= 11)
		icl_load_csc_matrix(crtc_state);
	अन्यथा
		ilk_load_csc_matrix(crtc_state);
पूर्ण

अटल व्योम i9xx_load_lut_8(काष्ठा पूर्णांकel_crtc *crtc,
			    स्थिर काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_color_lut *lut;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक i;

	अगर (!blob)
		वापस;

	lut = blob->data;

	क्रम (i = 0; i < 256; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, PALETTE(pipe, i),
			       i9xx_lut_8(&lut[i]));
पूर्ण

अटल व्योम i9xx_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;

	निश्चित_pll_enabled(dev_priv, crtc->pipe);

	i9xx_load_lut_8(crtc, gamma_lut);
पूर्ण

अटल व्योम i965_load_lut_10p6(काष्ठा पूर्णांकel_crtc *crtc,
			       स्थिर काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	पूर्णांक i, lut_size = drm_color_lut_size(blob);
	क्रमागत pipe pipe = crtc->pipe;

	क्रम (i = 0; i < lut_size - 1; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, PALETTE(pipe, 2 * i + 0),
			       i965_lut_10p6_ldw(&lut[i]));
		पूर्णांकel_de_ग_लिखो(dev_priv, PALETTE(pipe, 2 * i + 1),
			       i965_lut_10p6_udw(&lut[i]));
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PIPEGCMAX(pipe, 0), lut[i].red);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPEGCMAX(pipe, 1), lut[i].green);
	पूर्णांकel_de_ग_लिखो(dev_priv, PIPEGCMAX(pipe, 2), lut[i].blue);
पूर्ण

अटल व्योम i965_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;

	अगर (पूर्णांकel_crtc_has_type(crtc_state, INTEL_OUTPUT_DSI))
		निश्चित_dsi_pll_enabled(dev_priv);
	अन्यथा
		निश्चित_pll_enabled(dev_priv, crtc->pipe);

	अगर (crtc_state->gamma_mode == GAMMA_MODE_MODE_8BIT)
		i9xx_load_lut_8(crtc, gamma_lut);
	अन्यथा
		i965_load_lut_10p6(crtc, gamma_lut);
पूर्ण

अटल व्योम ilk_load_lut_8(काष्ठा पूर्णांकel_crtc *crtc,
			   स्थिर काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_color_lut *lut;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक i;

	अगर (!blob)
		वापस;

	lut = blob->data;

	क्रम (i = 0; i < 256; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, LGC_PALETTE(pipe, i),
			       i9xx_lut_8(&lut[i]));
पूर्ण

अटल व्योम ilk_load_lut_10(काष्ठा पूर्णांकel_crtc *crtc,
			    स्थिर काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	पूर्णांक i, lut_size = drm_color_lut_size(blob);
	क्रमागत pipe pipe = crtc->pipe;

	क्रम (i = 0; i < lut_size; i++)
		पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PALETTE(pipe, i),
			       ilk_lut_10(&lut[i]));
पूर्ण

अटल व्योम ilk_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		ilk_load_lut_8(crtc, gamma_lut);
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:
		ilk_load_lut_10(crtc, gamma_lut);
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ivb_lut_10_size(u32 prec_index)
अणु
	अगर (prec_index & PAL_PREC_SPLIT_MODE)
		वापस 512;
	अन्यथा
		वापस 1024;
पूर्ण

/*
 * IVB/HSW Bspec / PAL_PREC_INDEX:
 * "Restriction : Index स्वतः increment mode is not
 *  supported and must not be enabled."
 */
अटल व्योम ivb_load_lut_10(काष्ठा पूर्णांकel_crtc *crtc,
			    स्थिर काष्ठा drm_property_blob *blob,
			    u32 prec_index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक hw_lut_size = ivb_lut_10_size(prec_index);
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	पूर्णांक i, lut_size = drm_color_lut_size(blob);
	क्रमागत pipe pipe = crtc->pipe;

	क्रम (i = 0; i < hw_lut_size; i++) अणु
		/* We discard half the user entries in split gamma mode */
		स्थिर काष्ठा drm_color_lut *entry =
			&lut[i * (lut_size - 1) / (hw_lut_size - 1)];

		पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_INDEX(pipe), prec_index++);
		पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_DATA(pipe),
			       ilk_lut_10(entry));
	पूर्ण

	/*
	 * Reset the index, otherwise it prevents the legacy palette to be
	 * written properly.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_INDEX(pipe), 0);
पूर्ण

/* On BDW+ the index स्वतः increment mode actually works */
अटल व्योम bdw_load_lut_10(काष्ठा पूर्णांकel_crtc *crtc,
			    स्थिर काष्ठा drm_property_blob *blob,
			    u32 prec_index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक hw_lut_size = ivb_lut_10_size(prec_index);
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	पूर्णांक i, lut_size = drm_color_lut_size(blob);
	क्रमागत pipe pipe = crtc->pipe;

	पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_INDEX(pipe),
		       prec_index | PAL_PREC_AUTO_INCREMENT);

	क्रम (i = 0; i < hw_lut_size; i++) अणु
		/* We discard half the user entries in split gamma mode */
		स्थिर काष्ठा drm_color_lut *entry =
			&lut[i * (lut_size - 1) / (hw_lut_size - 1)];

		पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_DATA(pipe),
			       ilk_lut_10(entry));
	पूर्ण

	/*
	 * Reset the index, otherwise it prevents the legacy palette to be
	 * written properly.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_INDEX(pipe), 0);
पूर्ण

अटल व्योम ivb_load_lut_ext_max(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;

	/* Program the max रेजिस्टर to clamp values > 1.0. */
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_EXT_GC_MAX(pipe, 0), 1 << 16);
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_EXT_GC_MAX(pipe, 1), 1 << 16);
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_EXT_GC_MAX(pipe, 2), 1 << 16);

	/*
	 * Program the gc max 2 रेजिस्टर to clamp values > 1.0.
	 * ToDo: Extend the ABI to be able to program values
	 * from 3.0 to 7.0
	 */
	अगर (DISPLAY_VER(dev_priv) >= 10) अणु
		पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_EXT2_GC_MAX(pipe, 0),
				    1 << 16);
		पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_EXT2_GC_MAX(pipe, 1),
				    1 << 16);
		पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_EXT2_GC_MAX(pipe, 2),
				    1 << 16);
	पूर्ण
पूर्ण

अटल व्योम ivb_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;
	स्थिर काष्ठा drm_property_blob *degamma_lut = crtc_state->hw.degamma_lut;
	स्थिर काष्ठा drm_property_blob *blob = gamma_lut ?: degamma_lut;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		ilk_load_lut_8(crtc, blob);
		अवरोध;
	हाल GAMMA_MODE_MODE_SPLIT:
		ivb_load_lut_10(crtc, degamma_lut, PAL_PREC_SPLIT_MODE |
				PAL_PREC_INDEX_VALUE(0));
		ivb_load_lut_ext_max(crtc_state);
		ivb_load_lut_10(crtc, gamma_lut, PAL_PREC_SPLIT_MODE |
				PAL_PREC_INDEX_VALUE(512));
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:
		ivb_load_lut_10(crtc, blob,
				PAL_PREC_INDEX_VALUE(0));
		ivb_load_lut_ext_max(crtc_state);
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम bdw_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;
	स्थिर काष्ठा drm_property_blob *degamma_lut = crtc_state->hw.degamma_lut;
	स्थिर काष्ठा drm_property_blob *blob = gamma_lut ?: degamma_lut;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		ilk_load_lut_8(crtc, blob);
		अवरोध;
	हाल GAMMA_MODE_MODE_SPLIT:
		bdw_load_lut_10(crtc, degamma_lut, PAL_PREC_SPLIT_MODE |
				PAL_PREC_INDEX_VALUE(0));
		ivb_load_lut_ext_max(crtc_state);
		bdw_load_lut_10(crtc, gamma_lut, PAL_PREC_SPLIT_MODE |
				PAL_PREC_INDEX_VALUE(512));
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:

		bdw_load_lut_10(crtc, blob,
				PAL_PREC_INDEX_VALUE(0));
		ivb_load_lut_ext_max(crtc_state);
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम glk_load_degamma_lut(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक i, lut_size = INTEL_INFO(dev_priv)->color.degamma_lut_size;
	स्थिर काष्ठा drm_color_lut *lut = crtc_state->hw.degamma_lut->data;

	/*
	 * When setting the स्वतः-increment bit, the hardware seems to
	 * ignore the index bits, so we need to reset it to index 0
	 * separately.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_INDEX(pipe), 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_INDEX(pipe),
		       PRE_CSC_GAMC_AUTO_INCREMENT);

	क्रम (i = 0; i < lut_size; i++) अणु
		/*
		 * First 33 entries represent range from 0 to 1.0
		 * 34th and 35th entry will represent extended range
		 * inमाला_दो 3.0 and 7.0 respectively, currently clamped
		 * at 1.0. Since the precision is 16bit, the user
		 * value can be directly filled to रेजिस्टर.
		 * The pipe degamma table in GLK+ onwards करोesn't
		 * support dअगरferent values per channel, so this just
		 * programs green value which will be equal to Red and
		 * Blue पूर्णांकo the lut रेजिस्टरs.
		 * ToDo: Extend to max 7.0. Enable 32 bit input value
		 * as compared to just 16 to achieve this.
		 */
		पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_DATA(pipe),
			       lut[i].green);
	पूर्ण

	/* Clamp values > 1.0. */
	जबतक (i++ < 35)
		पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_DATA(pipe), 1 << 16);

	पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_INDEX(pipe), 0);
पूर्ण

अटल व्योम glk_load_degamma_lut_linear(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक i, lut_size = INTEL_INFO(dev_priv)->color.degamma_lut_size;

	/*
	 * When setting the स्वतः-increment bit, the hardware seems to
	 * ignore the index bits, so we need to reset it to index 0
	 * separately.
	 */
	पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_INDEX(pipe), 0);
	पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_INDEX(pipe),
		       PRE_CSC_GAMC_AUTO_INCREMENT);

	क्रम (i = 0; i < lut_size; i++) अणु
		u32 v = (i << 16) / (lut_size - 1);

		पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_DATA(pipe), v);
	पूर्ण

	/* Clamp values > 1.0. */
	जबतक (i++ < 35)
		पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_DATA(pipe), 1 << 16);

	पूर्णांकel_de_ग_लिखो(dev_priv, PRE_CSC_GAMC_INDEX(pipe), 0);
पूर्ण

अटल व्योम glk_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	/*
	 * On GLK+ both pipe CSC and degamma LUT are controlled
	 * by csc_enable. Hence क्रम the हालs where the CSC is
	 * needed but degamma LUT is not we need to load a
	 * linear degamma LUT. In fact we'll just always load
	 * the degama LUT so that we करोn't have to reload
	 * it every समय the pipe CSC is being enabled.
	 */
	अगर (crtc_state->hw.degamma_lut)
		glk_load_degamma_lut(crtc_state);
	अन्यथा
		glk_load_degamma_lut_linear(crtc_state);

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		ilk_load_lut_8(crtc, gamma_lut);
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:
		bdw_load_lut_10(crtc, gamma_lut, PAL_PREC_INDEX_VALUE(0));
		ivb_load_lut_ext_max(crtc_state);
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण
पूर्ण

/* ilk+ "12.4" पूर्णांकerpolated क्रमmat (high 10 bits) */
अटल u32 ilk_lut_12p4_udw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस (color->red >> 6) << 20 | (color->green >> 6) << 10 |
		(color->blue >> 6);
पूर्ण

/* ilk+ "12.4" पूर्णांकerpolated क्रमmat (low 6 bits) */
अटल u32 ilk_lut_12p4_ldw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस (color->red & 0x3f) << 24 | (color->green & 0x3f) << 14 |
		(color->blue & 0x3f) << 4;
पूर्ण

अटल व्योम
icl_load_gcmax(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
	       स्थिर काष्ठा drm_color_lut *color)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	क्रमागत pipe pipe = crtc->pipe;

	/* FIXME LUT entries are 16 bit only, so we can prog 0xFFFF max */
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_GC_MAX(pipe, 0), color->red);
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_GC_MAX(pipe, 1), color->green);
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_GC_MAX(pipe, 2), color->blue);
पूर्ण

अटल व्योम
icl_program_gamma_superfine_segment(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_property_blob *blob = crtc_state->hw.gamma_lut;
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक i;

	/*
	 * Program Super Fine segment (let's call it seg1)...
	 *
	 * Super Fine segment's step is 1/(8 * 128 * 256) and it has
	 * 9 entries, corresponding to values 0, 1/(8 * 128 * 256),
	 * 2/(8 * 128 * 256) ... 8/(8 * 128 * 256).
	 */
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_MULTI_SEG_INDEX(pipe),
			    PAL_PREC_AUTO_INCREMENT);

	क्रम (i = 0; i < 9; i++) अणु
		स्थिर काष्ठा drm_color_lut *entry = &lut[i];

		पूर्णांकel_dsb_indexed_reg_ग_लिखो(crtc_state, PREC_PAL_MULTI_SEG_DATA(pipe),
					    ilk_lut_12p4_ldw(entry));
		पूर्णांकel_dsb_indexed_reg_ग_लिखो(crtc_state, PREC_PAL_MULTI_SEG_DATA(pipe),
					    ilk_lut_12p4_udw(entry));
	पूर्ण
पूर्ण

अटल व्योम
icl_program_gamma_multi_segment(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	स्थिर काष्ठा drm_property_blob *blob = crtc_state->hw.gamma_lut;
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	स्थिर काष्ठा drm_color_lut *entry;
	क्रमागत pipe pipe = crtc->pipe;
	पूर्णांक i;

	/*
	 * Program Fine segment (let's call it seg2)...
	 *
	 * Fine segment's step is 1/(128 * 256) i.e. 1/(128 * 256), 2/(128 * 256)
	 * ... 256/(128 * 256). So in order to program fine segment of LUT we
	 * need to pick every 8th entry in the LUT, and program 256 indexes.
	 *
	 * PAL_PREC_INDEX[0] and PAL_PREC_INDEX[1] map to seg2[1],
	 * seg2[0] being unused by the hardware.
	 */
	पूर्णांकel_dsb_reg_ग_लिखो(crtc_state, PREC_PAL_INDEX(pipe),
			    PAL_PREC_AUTO_INCREMENT);
	क्रम (i = 1; i < 257; i++) अणु
		entry = &lut[i * 8];
		पूर्णांकel_dsb_indexed_reg_ग_लिखो(crtc_state, PREC_PAL_DATA(pipe),
					    ilk_lut_12p4_ldw(entry));
		पूर्णांकel_dsb_indexed_reg_ग_लिखो(crtc_state, PREC_PAL_DATA(pipe),
					    ilk_lut_12p4_udw(entry));
	पूर्ण

	/*
	 * Program Coarse segment (let's call it seg3)...
	 *
	 * Coarse segment starts from index 0 and it's step is 1/256 ie 0,
	 * 1/256, 2/256 ... 256/256. As per the description of each entry in LUT
	 * above, we need to pick every (8 * 128)th entry in LUT, and
	 * program 256 of those.
	 *
	 * Spec is not very clear about अगर entries seg3[0] and seg3[1] are
	 * being used or not, but we still need to program these to advance
	 * the index.
	 */
	क्रम (i = 0; i < 256; i++) अणु
		entry = &lut[i * 8 * 128];
		पूर्णांकel_dsb_indexed_reg_ग_लिखो(crtc_state, PREC_PAL_DATA(pipe),
					    ilk_lut_12p4_ldw(entry));
		पूर्णांकel_dsb_indexed_reg_ग_लिखो(crtc_state, PREC_PAL_DATA(pipe),
					    ilk_lut_12p4_udw(entry));
	पूर्ण

	/* The last entry in the LUT is to be programmed in GCMAX */
	entry = &lut[256 * 8 * 128];
	icl_load_gcmax(crtc_state, entry);
	ivb_load_lut_ext_max(crtc_state);
पूर्ण

अटल व्योम icl_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	अगर (crtc_state->hw.degamma_lut)
		glk_load_degamma_lut(crtc_state);

	चयन (crtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		ilk_load_lut_8(crtc, gamma_lut);
		अवरोध;
	हाल GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED:
		icl_program_gamma_superfine_segment(crtc_state);
		icl_program_gamma_multi_segment(crtc_state);
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:
		bdw_load_lut_10(crtc, gamma_lut, PAL_PREC_INDEX_VALUE(0));
		ivb_load_lut_ext_max(crtc_state);
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण

	पूर्णांकel_dsb_commit(crtc_state);
पूर्ण

अटल u32 chv_cgm_degamma_ldw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस drm_color_lut_extract(color->green, 14) << 16 |
		drm_color_lut_extract(color->blue, 14);
पूर्ण

अटल u32 chv_cgm_degamma_udw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस drm_color_lut_extract(color->red, 14);
पूर्ण

अटल व्योम chv_load_cgm_degamma(काष्ठा पूर्णांकel_crtc *crtc,
				 स्थिर काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	पूर्णांक i, lut_size = drm_color_lut_size(blob);
	क्रमागत pipe pipe = crtc->pipe;

	क्रम (i = 0; i < lut_size; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_DEGAMMA(pipe, i, 0),
			       chv_cgm_degamma_ldw(&lut[i]));
		पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_DEGAMMA(pipe, i, 1),
			       chv_cgm_degamma_udw(&lut[i]));
	पूर्ण
पूर्ण

अटल u32 chv_cgm_gamma_ldw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस drm_color_lut_extract(color->green, 10) << 16 |
		drm_color_lut_extract(color->blue, 10);
पूर्ण

अटल u32 chv_cgm_gamma_udw(स्थिर काष्ठा drm_color_lut *color)
अणु
	वापस drm_color_lut_extract(color->red, 10);
पूर्ण

अटल व्योम chv_cgm_gamma_pack(काष्ठा drm_color_lut *entry, u32 ldw, u32 udw)
अणु
	entry->green = पूर्णांकel_color_lut_pack(REG_FIELD_GET(CGM_PIPE_GAMMA_GREEN_MASK, ldw), 10);
	entry->blue = पूर्णांकel_color_lut_pack(REG_FIELD_GET(CGM_PIPE_GAMMA_BLUE_MASK, ldw), 10);
	entry->red = पूर्णांकel_color_lut_pack(REG_FIELD_GET(CGM_PIPE_GAMMA_RED_MASK, udw), 10);
पूर्ण

अटल व्योम chv_load_cgm_gamma(काष्ठा पूर्णांकel_crtc *crtc,
			       स्थिर काष्ठा drm_property_blob *blob)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_color_lut *lut = blob->data;
	पूर्णांक i, lut_size = drm_color_lut_size(blob);
	क्रमागत pipe pipe = crtc->pipe;

	क्रम (i = 0; i < lut_size; i++) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_GAMMA(pipe, i, 0),
			       chv_cgm_gamma_ldw(&lut[i]));
		पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_GAMMA(pipe, i, 1),
			       chv_cgm_gamma_udw(&lut[i]));
	पूर्ण
पूर्ण

अटल व्योम chv_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	स्थिर काष्ठा drm_property_blob *degamma_lut = crtc_state->hw.degamma_lut;
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;
	स्थिर काष्ठा drm_property_blob *cपंचांग = crtc_state->hw.cपंचांग;

	अगर (crtc_state->cgm_mode & CGM_PIPE_MODE_CSC)
		chv_load_cgm_csc(crtc, cपंचांग);

	अगर (crtc_state->cgm_mode & CGM_PIPE_MODE_DEGAMMA)
		chv_load_cgm_degamma(crtc, degamma_lut);

	अगर (crtc_state->cgm_mode & CGM_PIPE_MODE_GAMMA)
		chv_load_cgm_gamma(crtc, gamma_lut);
	अन्यथा
		i965_load_luts(crtc_state);

	पूर्णांकel_de_ग_लिखो(dev_priv, CGM_PIPE_MODE(crtc->pipe),
		       crtc_state->cgm_mode);
पूर्ण

व्योम पूर्णांकel_color_load_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	dev_priv->display.load_luts(crtc_state);
पूर्ण

व्योम पूर्णांकel_color_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	dev_priv->display.color_commit(crtc_state);
पूर्ण

अटल bool पूर्णांकel_can_preload_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);

	वापस !old_crtc_state->hw.gamma_lut &&
		!old_crtc_state->hw.degamma_lut;
पूर्ण

अटल bool chv_can_preload_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);

	/*
	 * CGM_PIPE_MODE is itself single buffered. We'd have to
	 * somehow split it out from chv_load_luts() अगर we wanted
	 * the ability to preload the CGM LUTs/CSC without tearing.
	 */
	अगर (old_crtc_state->cgm_mode || new_crtc_state->cgm_mode)
		वापस false;

	वापस !old_crtc_state->hw.gamma_lut;
पूर्ण

अटल bool glk_can_preload_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);

	/*
	 * The hardware degamma is active whenever the pipe
	 * CSC is active. Thus even अगर the old state has no
	 * software degamma we need to aव्योम clobbering the
	 * linear hardware degamma mid scanout.
	 */
	वापस !old_crtc_state->csc_enable &&
		!old_crtc_state->hw.gamma_lut;
पूर्ण

पूर्णांक पूर्णांकel_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	वापस dev_priv->display.color_check(crtc_state);
पूर्ण

व्योम पूर्णांकel_color_get_config(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);

	अगर (dev_priv->display.पढ़ो_luts)
		dev_priv->display.पढ़ो_luts(crtc_state);
पूर्ण

अटल bool need_plane_update(काष्ठा पूर्णांकel_plane *plane,
			      स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(plane->base.dev);

	/*
	 * On pre-SKL the pipe gamma enable and pipe csc enable क्रम
	 * the pipe bottom color are configured via the primary plane.
	 * We have to reconfigure that even अगर the plane is inactive.
	 */
	वापस crtc_state->active_planes & BIT(plane->id) ||
		(DISPLAY_VER(dev_priv) < 9 &&
		 plane->id == PLANE_PRIMARY);
पूर्ण

अटल पूर्णांक
पूर्णांकel_color_add_affected_planes(काष्ठा पूर्णांकel_crtc_state *new_crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(new_crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_atomic_state *state =
		to_पूर्णांकel_atomic_state(new_crtc_state->uapi.state);
	स्थिर काष्ठा पूर्णांकel_crtc_state *old_crtc_state =
		पूर्णांकel_atomic_get_old_crtc_state(state, crtc);
	काष्ठा पूर्णांकel_plane *plane;

	अगर (!new_crtc_state->hw.active ||
	    drm_atomic_crtc_needs_modeset(&new_crtc_state->uapi))
		वापस 0;

	अगर (new_crtc_state->gamma_enable == old_crtc_state->gamma_enable &&
	    new_crtc_state->csc_enable == old_crtc_state->csc_enable)
		वापस 0;

	क्रम_each_पूर्णांकel_plane_on_crtc(&dev_priv->drm, crtc, plane) अणु
		काष्ठा पूर्णांकel_plane_state *plane_state;

		अगर (!need_plane_update(plane, new_crtc_state))
			जारी;

		plane_state = पूर्णांकel_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state))
			वापस PTR_ERR(plane_state);

		new_crtc_state->update_planes |= BIT(plane->id);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_lut_size(स्थिर काष्ठा drm_property_blob *lut, पूर्णांक expected)
अणु
	पूर्णांक len;

	अगर (!lut)
		वापस 0;

	len = drm_color_lut_size(lut);
	अगर (len != expected) अणु
		DRM_DEBUG_KMS("Invalid LUT size; got %d, expected %d\n",
			      len, expected);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_luts(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	स्थिर काष्ठा drm_property_blob *gamma_lut = crtc_state->hw.gamma_lut;
	स्थिर काष्ठा drm_property_blob *degamma_lut = crtc_state->hw.degamma_lut;
	पूर्णांक gamma_length, degamma_length;
	u32 gamma_tests, degamma_tests;

	/* Always allow legacy gamma LUT with no further checking. */
	अगर (crtc_state_is_legacy_gamma(crtc_state))
		वापस 0;

	/* C8 relies on its palette being stored in the legacy LUT */
	अगर (crtc_state->c8_planes) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "C8 pixelformat requires the legacy LUT\n");
		वापस -EINVAL;
	पूर्ण

	degamma_length = INTEL_INFO(dev_priv)->color.degamma_lut_size;
	gamma_length = INTEL_INFO(dev_priv)->color.gamma_lut_size;
	degamma_tests = INTEL_INFO(dev_priv)->color.degamma_lut_tests;
	gamma_tests = INTEL_INFO(dev_priv)->color.gamma_lut_tests;

	अगर (check_lut_size(degamma_lut, degamma_length) ||
	    check_lut_size(gamma_lut, gamma_length))
		वापस -EINVAL;

	अगर (drm_color_lut_check(degamma_lut, degamma_tests) ||
	    drm_color_lut_check(gamma_lut, gamma_tests))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल u32 i9xx_gamma_mode(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->gamma_enable ||
	    crtc_state_is_legacy_gamma(crtc_state))
		वापस GAMMA_MODE_MODE_8BIT;
	अन्यथा
		वापस GAMMA_MODE_MODE_10BIT; /* i965+ only */
पूर्ण

अटल पूर्णांक i9xx_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक ret;

	ret = check_luts(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->gamma_enable =
		crtc_state->hw.gamma_lut &&
		!crtc_state->c8_planes;

	crtc_state->gamma_mode = i9xx_gamma_mode(crtc_state);

	ret = पूर्णांकel_color_add_affected_planes(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->preload_luts = पूर्णांकel_can_preload_luts(crtc_state);

	वापस 0;
पूर्ण

अटल u32 chv_cgm_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 cgm_mode = 0;

	अगर (crtc_state_is_legacy_gamma(crtc_state))
		वापस 0;

	अगर (crtc_state->hw.degamma_lut)
		cgm_mode |= CGM_PIPE_MODE_DEGAMMA;
	अगर (crtc_state->hw.cपंचांग)
		cgm_mode |= CGM_PIPE_MODE_CSC;
	अगर (crtc_state->hw.gamma_lut)
		cgm_mode |= CGM_PIPE_MODE_GAMMA;

	वापस cgm_mode;
पूर्ण

/*
 * CHV color pipeline:
 * u0.10 -> CGM degamma -> u0.14 -> CGM csc -> u0.14 -> CGM gamma ->
 * u0.10 -> WGC csc -> u0.10 -> pipe gamma -> u0.10
 *
 * We always bypass the WGC csc and use the CGM csc
 * instead since it has degamma and better precision.
 */
अटल पूर्णांक chv_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक ret;

	ret = check_luts(crtc_state);
	अगर (ret)
		वापस ret;

	/*
	 * Pipe gamma will be used only क्रम the legacy LUT.
	 * Otherwise we bypass it and use the CGM gamma instead.
	 */
	crtc_state->gamma_enable =
		crtc_state_is_legacy_gamma(crtc_state) &&
		!crtc_state->c8_planes;

	crtc_state->gamma_mode = GAMMA_MODE_MODE_8BIT;

	crtc_state->cgm_mode = chv_cgm_mode(crtc_state);

	ret = पूर्णांकel_color_add_affected_planes(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->preload_luts = chv_can_preload_luts(crtc_state);

	वापस 0;
पूर्ण

अटल u32 ilk_gamma_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->gamma_enable ||
	    crtc_state_is_legacy_gamma(crtc_state))
		वापस GAMMA_MODE_MODE_8BIT;
	अन्यथा
		वापस GAMMA_MODE_MODE_10BIT;
पूर्ण

अटल u32 ilk_csc_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	/*
	 * CSC comes after the LUT in RGB->YCbCr mode.
	 * RGB->YCbCr needs the limited range offsets added to
	 * the output. RGB limited range output is handled by
	 * the hw स्वतःmagically अन्यथाwhere.
	 */
	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB)
		वापस CSC_BLACK_SCREEN_OFFSET;

	वापस CSC_MODE_YUV_TO_RGB |
		CSC_POSITION_BEFORE_GAMMA;
पूर्ण

अटल पूर्णांक ilk_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक ret;

	ret = check_luts(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->gamma_enable =
		crtc_state->hw.gamma_lut &&
		!crtc_state->c8_planes;

	/*
	 * We करोn't expose the cपंचांग on ilk/snb currently, also RGB
	 * limited range output is handled by the hw स्वतःmagically.
	 */
	crtc_state->csc_enable =
		crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB;

	crtc_state->gamma_mode = ilk_gamma_mode(crtc_state);

	crtc_state->csc_mode = ilk_csc_mode(crtc_state);

	ret = पूर्णांकel_color_add_affected_planes(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->preload_luts = पूर्णांकel_can_preload_luts(crtc_state);

	वापस 0;
पूर्ण

अटल u32 ivb_gamma_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->gamma_enable ||
	    crtc_state_is_legacy_gamma(crtc_state))
		वापस GAMMA_MODE_MODE_8BIT;
	अन्यथा अगर (crtc_state->hw.gamma_lut &&
		 crtc_state->hw.degamma_lut)
		वापस GAMMA_MODE_MODE_SPLIT;
	अन्यथा
		वापस GAMMA_MODE_MODE_10BIT;
पूर्ण

अटल u32 ivb_csc_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	bool limited_color_range = ilk_csc_limited_range(crtc_state);

	/*
	 * CSC comes after the LUT in degamma, RGB->YCbCr,
	 * and RGB full->limited range mode.
	 */
	अगर (crtc_state->hw.degamma_lut ||
	    crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB ||
	    limited_color_range)
		वापस 0;

	वापस CSC_POSITION_BEFORE_GAMMA;
पूर्ण

अटल पूर्णांक ivb_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	bool limited_color_range = ilk_csc_limited_range(crtc_state);
	पूर्णांक ret;

	ret = check_luts(crtc_state);
	अगर (ret)
		वापस ret;

	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB &&
	    crtc_state->hw.cपंचांग) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "YCBCR and CTM together are not possible\n");
		वापस -EINVAL;
	पूर्ण

	crtc_state->gamma_enable =
		(crtc_state->hw.gamma_lut ||
		 crtc_state->hw.degamma_lut) &&
		!crtc_state->c8_planes;

	crtc_state->csc_enable =
		crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB ||
		crtc_state->hw.cपंचांग || limited_color_range;

	crtc_state->gamma_mode = ivb_gamma_mode(crtc_state);

	crtc_state->csc_mode = ivb_csc_mode(crtc_state);

	ret = पूर्णांकel_color_add_affected_planes(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->preload_luts = पूर्णांकel_can_preload_luts(crtc_state);

	वापस 0;
पूर्ण

अटल u32 glk_gamma_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->gamma_enable ||
	    crtc_state_is_legacy_gamma(crtc_state))
		वापस GAMMA_MODE_MODE_8BIT;
	अन्यथा
		वापस GAMMA_MODE_MODE_10BIT;
पूर्ण

अटल पूर्णांक glk_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc_state->uapi.crtc->dev);
	पूर्णांक ret;

	ret = check_luts(crtc_state);
	अगर (ret)
		वापस ret;

	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB &&
	    crtc_state->hw.cपंचांग) अणु
		drm_dbg_kms(&dev_priv->drm,
			    "YCBCR and CTM together are not possible\n");
		वापस -EINVAL;
	पूर्ण

	crtc_state->gamma_enable =
		crtc_state->hw.gamma_lut &&
		!crtc_state->c8_planes;

	/* On GLK+ degamma LUT is controlled by csc_enable */
	crtc_state->csc_enable =
		crtc_state->hw.degamma_lut ||
		crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB ||
		crtc_state->hw.cपंचांग || crtc_state->limited_color_range;

	crtc_state->gamma_mode = glk_gamma_mode(crtc_state);

	crtc_state->csc_mode = 0;

	ret = पूर्णांकel_color_add_affected_planes(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->preload_luts = glk_can_preload_luts(crtc_state);

	वापस 0;
पूर्ण

अटल u32 icl_gamma_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 gamma_mode = 0;

	अगर (crtc_state->hw.degamma_lut)
		gamma_mode |= PRE_CSC_GAMMA_ENABLE;

	अगर (crtc_state->hw.gamma_lut &&
	    !crtc_state->c8_planes)
		gamma_mode |= POST_CSC_GAMMA_ENABLE;

	अगर (!crtc_state->hw.gamma_lut ||
	    crtc_state_is_legacy_gamma(crtc_state))
		gamma_mode |= GAMMA_MODE_MODE_8BIT;
	अन्यथा
		gamma_mode |= GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED;

	वापस gamma_mode;
पूर्ण

अटल u32 icl_csc_mode(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	u32 csc_mode = 0;

	अगर (crtc_state->hw.cपंचांग)
		csc_mode |= ICL_CSC_ENABLE;

	अगर (crtc_state->output_क्रमmat != INTEL_OUTPUT_FORMAT_RGB ||
	    crtc_state->limited_color_range)
		csc_mode |= ICL_OUTPUT_CSC_ENABLE;

	वापस csc_mode;
पूर्ण

अटल पूर्णांक icl_color_check(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	पूर्णांक ret;

	ret = check_luts(crtc_state);
	अगर (ret)
		वापस ret;

	crtc_state->gamma_mode = icl_gamma_mode(crtc_state);

	crtc_state->csc_mode = icl_csc_mode(crtc_state);

	crtc_state->preload_luts = पूर्णांकel_can_preload_luts(crtc_state);

	वापस 0;
पूर्ण

अटल पूर्णांक i9xx_gamma_precision(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->gamma_enable)
		वापस 0;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		वापस 8;
	हाल GAMMA_MODE_MODE_10BIT:
		वापस 16;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ilk_gamma_precision(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->gamma_enable)
		वापस 0;

	अगर ((crtc_state->csc_mode & CSC_POSITION_BEFORE_GAMMA) == 0)
		वापस 0;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		वापस 8;
	हाल GAMMA_MODE_MODE_10BIT:
		वापस 10;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक chv_gamma_precision(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (crtc_state->cgm_mode & CGM_PIPE_MODE_GAMMA)
		वापस 10;
	अन्यथा
		वापस i9xx_gamma_precision(crtc_state);
पूर्ण

अटल पूर्णांक glk_gamma_precision(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->gamma_enable)
		वापस 0;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		वापस 8;
	हाल GAMMA_MODE_MODE_10BIT:
		वापस 10;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक icl_gamma_precision(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर ((crtc_state->gamma_mode & POST_CSC_GAMMA_ENABLE) == 0)
		वापस 0;

	चयन (crtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		वापस 8;
	हाल GAMMA_MODE_MODE_10BIT:
		वापस 10;
	हाल GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED:
		वापस 16;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक पूर्णांकel_color_get_gamma_bit_precision(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);

	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_CHERRYVIEW(dev_priv))
			वापस chv_gamma_precision(crtc_state);
		अन्यथा
			वापस i9xx_gamma_precision(crtc_state);
	पूर्ण अन्यथा अणु
		अगर (DISPLAY_VER(dev_priv) >= 11)
			वापस icl_gamma_precision(crtc_state);
		अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 10))
			वापस glk_gamma_precision(crtc_state);
		अन्यथा अगर (IS_IRONLAKE(dev_priv))
			वापस ilk_gamma_precision(crtc_state);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool err_check(काष्ठा drm_color_lut *lut1,
		      काष्ठा drm_color_lut *lut2, u32 err)
अणु
	वापस ((असल((दीर्घ)lut2->red - lut1->red)) <= err) &&
		((असल((दीर्घ)lut2->blue - lut1->blue)) <= err) &&
		((असल((दीर्घ)lut2->green - lut1->green)) <= err);
पूर्ण

अटल bool पूर्णांकel_color_lut_entries_equal(काष्ठा drm_color_lut *lut1,
					  काष्ठा drm_color_lut *lut2,
					  पूर्णांक lut_size, u32 err)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < lut_size; i++) अणु
		अगर (!err_check(&lut1[i], &lut2[i], err))
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool पूर्णांकel_color_lut_equal(काष्ठा drm_property_blob *blob1,
			   काष्ठा drm_property_blob *blob2,
			   u32 gamma_mode, u32 bit_precision)
अणु
	काष्ठा drm_color_lut *lut1, *lut2;
	पूर्णांक lut_size1, lut_size2;
	u32 err;

	अगर (!blob1 != !blob2)
		वापस false;

	अगर (!blob1)
		वापस true;

	lut_size1 = drm_color_lut_size(blob1);
	lut_size2 = drm_color_lut_size(blob2);

	/* check sw and hw lut size */
	अगर (lut_size1 != lut_size2)
		वापस false;

	lut1 = blob1->data;
	lut2 = blob2->data;

	err = 0xffff >> bit_precision;

	/* check sw and hw lut entry to be equal */
	चयन (gamma_mode & GAMMA_MODE_MODE_MASK) अणु
	हाल GAMMA_MODE_MODE_8BIT:
	हाल GAMMA_MODE_MODE_10BIT:
		अगर (!पूर्णांकel_color_lut_entries_equal(lut1, lut2,
						   lut_size2, err))
			वापस false;
		अवरोध;
	हाल GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED:
		अगर (!पूर्णांकel_color_lut_entries_equal(lut1, lut2,
						   9, err))
			वापस false;
		अवरोध;
	शेष:
		MISSING_CASE(gamma_mode);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा drm_property_blob *i9xx_पढ़ो_lut_8(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_color_lut *lut;
	पूर्णांक i;

	blob = drm_property_create_blob(&dev_priv->drm,
					माप(काष्ठा drm_color_lut) * LEGACY_LUT_LENGTH,
					शून्य);
	अगर (IS_ERR(blob))
		वापस शून्य;

	lut = blob->data;

	क्रम (i = 0; i < LEGACY_LUT_LENGTH; i++) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, PALETTE(pipe, i));

		i9xx_lut_8_pack(&lut[i], val);
	पूर्ण

	वापस blob;
पूर्ण

अटल व्योम i9xx_पढ़ो_luts(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	अगर (!crtc_state->gamma_enable)
		वापस;

	crtc_state->hw.gamma_lut = i9xx_पढ़ो_lut_8(crtc);
पूर्ण

अटल काष्ठा drm_property_blob *i965_पढ़ो_lut_10p6(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक i, lut_size = INTEL_INFO(dev_priv)->color.gamma_lut_size;
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_color_lut *lut;

	blob = drm_property_create_blob(&dev_priv->drm,
					माप(काष्ठा drm_color_lut) * lut_size,
					शून्य);
	अगर (IS_ERR(blob))
		वापस शून्य;

	lut = blob->data;

	क्रम (i = 0; i < lut_size - 1; i++) अणु
		u32 ldw = पूर्णांकel_de_पढ़ो(dev_priv, PALETTE(pipe, 2 * i + 0));
		u32 udw = पूर्णांकel_de_पढ़ो(dev_priv, PALETTE(pipe, 2 * i + 1));

		i965_lut_10p6_pack(&lut[i], ldw, udw);
	पूर्ण

	lut[i].red = i965_lut_11p6_max_pack(पूर्णांकel_de_पढ़ो(dev_priv, PIPEGCMAX(pipe, 0)));
	lut[i].green = i965_lut_11p6_max_pack(पूर्णांकel_de_पढ़ो(dev_priv, PIPEGCMAX(pipe, 1)));
	lut[i].blue = i965_lut_11p6_max_pack(पूर्णांकel_de_पढ़ो(dev_priv, PIPEGCMAX(pipe, 2)));

	वापस blob;
पूर्ण

अटल व्योम i965_पढ़ो_luts(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	अगर (!crtc_state->gamma_enable)
		वापस;

	अगर (crtc_state->gamma_mode == GAMMA_MODE_MODE_8BIT)
		crtc_state->hw.gamma_lut = i9xx_पढ़ो_lut_8(crtc);
	अन्यथा
		crtc_state->hw.gamma_lut = i965_पढ़ो_lut_10p6(crtc);
पूर्ण

अटल काष्ठा drm_property_blob *chv_पढ़ो_cgm_gamma(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक i, lut_size = INTEL_INFO(dev_priv)->color.gamma_lut_size;
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_color_lut *lut;

	blob = drm_property_create_blob(&dev_priv->drm,
					माप(काष्ठा drm_color_lut) * lut_size,
					शून्य);
	अगर (IS_ERR(blob))
		वापस शून्य;

	lut = blob->data;

	क्रम (i = 0; i < lut_size; i++) अणु
		u32 ldw = पूर्णांकel_de_पढ़ो(dev_priv, CGM_PIPE_GAMMA(pipe, i, 0));
		u32 udw = पूर्णांकel_de_पढ़ो(dev_priv, CGM_PIPE_GAMMA(pipe, i, 1));

		chv_cgm_gamma_pack(&lut[i], ldw, udw);
	पूर्ण

	वापस blob;
पूर्ण

अटल व्योम chv_पढ़ो_luts(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	अगर (crtc_state->cgm_mode & CGM_PIPE_MODE_GAMMA)
		crtc_state->hw.gamma_lut = chv_पढ़ो_cgm_gamma(crtc);
	अन्यथा
		i965_पढ़ो_luts(crtc_state);
पूर्ण

अटल काष्ठा drm_property_blob *ilk_पढ़ो_lut_8(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_color_lut *lut;
	पूर्णांक i;

	blob = drm_property_create_blob(&dev_priv->drm,
					माप(काष्ठा drm_color_lut) * LEGACY_LUT_LENGTH,
					शून्य);
	अगर (IS_ERR(blob))
		वापस शून्य;

	lut = blob->data;

	क्रम (i = 0; i < LEGACY_LUT_LENGTH; i++) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, LGC_PALETTE(pipe, i));

		i9xx_lut_8_pack(&lut[i], val);
	पूर्ण

	वापस blob;
पूर्ण

अटल काष्ठा drm_property_blob *ilk_पढ़ो_lut_10(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक i, lut_size = INTEL_INFO(dev_priv)->color.gamma_lut_size;
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_color_lut *lut;

	blob = drm_property_create_blob(&dev_priv->drm,
					माप(काष्ठा drm_color_lut) * lut_size,
					शून्य);
	अगर (IS_ERR(blob))
		वापस शून्य;

	lut = blob->data;

	क्रम (i = 0; i < lut_size; i++) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, PREC_PALETTE(pipe, i));

		ilk_lut_10_pack(&lut[i], val);
	पूर्ण

	वापस blob;
पूर्ण

अटल व्योम ilk_पढ़ो_luts(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	अगर (!crtc_state->gamma_enable)
		वापस;

	अगर ((crtc_state->csc_mode & CSC_POSITION_BEFORE_GAMMA) == 0)
		वापस;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		crtc_state->hw.gamma_lut = ilk_पढ़ो_lut_8(crtc);
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:
		crtc_state->hw.gamma_lut = ilk_पढ़ो_lut_10(crtc);
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण
पूर्ण

/* On BDW+ the index स्वतः increment mode actually works */
अटल काष्ठा drm_property_blob *bdw_पढ़ो_lut_10(काष्ठा पूर्णांकel_crtc *crtc,
						 u32 prec_index)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक i, hw_lut_size = ivb_lut_10_size(prec_index);
	पूर्णांक lut_size = INTEL_INFO(dev_priv)->color.gamma_lut_size;
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_color_lut *lut;

	drm_WARN_ON(&dev_priv->drm, lut_size != hw_lut_size);

	blob = drm_property_create_blob(&dev_priv->drm,
					माप(काष्ठा drm_color_lut) * lut_size,
					शून्य);
	अगर (IS_ERR(blob))
		वापस शून्य;

	lut = blob->data;

	पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_INDEX(pipe),
		       prec_index | PAL_PREC_AUTO_INCREMENT);

	क्रम (i = 0; i < lut_size; i++) अणु
		u32 val = पूर्णांकel_de_पढ़ो(dev_priv, PREC_PAL_DATA(pipe));

		ilk_lut_10_pack(&lut[i], val);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_INDEX(pipe), 0);

	वापस blob;
पूर्ण

अटल व्योम glk_पढ़ो_luts(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	अगर (!crtc_state->gamma_enable)
		वापस;

	चयन (crtc_state->gamma_mode) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		crtc_state->hw.gamma_lut = ilk_पढ़ो_lut_8(crtc);
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:
		crtc_state->hw.gamma_lut = bdw_पढ़ो_lut_10(crtc, PAL_PREC_INDEX_VALUE(0));
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा drm_property_blob *
icl_पढ़ो_lut_multi_segment(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	पूर्णांक i, lut_size = INTEL_INFO(dev_priv)->color.gamma_lut_size;
	क्रमागत pipe pipe = crtc->pipe;
	काष्ठा drm_property_blob *blob;
	काष्ठा drm_color_lut *lut;

	blob = drm_property_create_blob(&dev_priv->drm,
					माप(काष्ठा drm_color_lut) * lut_size,
					शून्य);
	अगर (IS_ERR(blob))
		वापस शून्य;

	lut = blob->data;

	पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_MULTI_SEG_INDEX(pipe),
		       PAL_PREC_AUTO_INCREMENT);

	क्रम (i = 0; i < 9; i++) अणु
		u32 ldw = पूर्णांकel_de_पढ़ो(dev_priv, PREC_PAL_MULTI_SEG_DATA(pipe));
		u32 udw = पूर्णांकel_de_पढ़ो(dev_priv, PREC_PAL_MULTI_SEG_DATA(pipe));

		icl_lut_multi_seg_pack(&lut[i], ldw, udw);
	पूर्ण

	पूर्णांकel_de_ग_लिखो(dev_priv, PREC_PAL_MULTI_SEG_INDEX(pipe), 0);

	/*
	 * FIXME पढ़ोouts from PAL_PREC_DATA रेजिस्टर aren't giving
	 * correct values in the हाल of fine and coarse segments.
	 * Restricting पढ़ोouts only क्रम super fine segment as of now.
	 */

	वापस blob;
पूर्ण

अटल व्योम icl_पढ़ो_luts(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);

	अगर ((crtc_state->gamma_mode & POST_CSC_GAMMA_ENABLE) == 0)
		वापस;

	चयन (crtc_state->gamma_mode & GAMMA_MODE_MODE_MASK) अणु
	हाल GAMMA_MODE_MODE_8BIT:
		crtc_state->hw.gamma_lut = ilk_पढ़ो_lut_8(crtc);
		अवरोध;
	हाल GAMMA_MODE_MODE_10BIT:
		crtc_state->hw.gamma_lut = bdw_पढ़ो_lut_10(crtc, PAL_PREC_INDEX_VALUE(0));
		अवरोध;
	हाल GAMMA_MODE_MODE_12BIT_MULTI_SEGMENTED:
		crtc_state->hw.gamma_lut = icl_पढ़ो_lut_multi_segment(crtc);
		अवरोध;
	शेष:
		MISSING_CASE(crtc_state->gamma_mode);
		अवरोध;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_color_init(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	bool has_cपंचांग = INTEL_INFO(dev_priv)->color.degamma_lut_size != 0;

	drm_mode_crtc_set_gamma_size(&crtc->base, 256);

	अगर (HAS_GMCH(dev_priv)) अणु
		अगर (IS_CHERRYVIEW(dev_priv)) अणु
			dev_priv->display.color_check = chv_color_check;
			dev_priv->display.color_commit = i9xx_color_commit;
			dev_priv->display.load_luts = chv_load_luts;
			dev_priv->display.पढ़ो_luts = chv_पढ़ो_luts;
		पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 4) अणु
			dev_priv->display.color_check = i9xx_color_check;
			dev_priv->display.color_commit = i9xx_color_commit;
			dev_priv->display.load_luts = i965_load_luts;
			dev_priv->display.पढ़ो_luts = i965_पढ़ो_luts;
		पूर्ण अन्यथा अणु
			dev_priv->display.color_check = i9xx_color_check;
			dev_priv->display.color_commit = i9xx_color_commit;
			dev_priv->display.load_luts = i9xx_load_luts;
			dev_priv->display.पढ़ो_luts = i9xx_पढ़ो_luts;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (DISPLAY_VER(dev_priv) >= 11)
			dev_priv->display.color_check = icl_color_check;
		अन्यथा अगर (DISPLAY_VER(dev_priv) >= 10)
			dev_priv->display.color_check = glk_color_check;
		अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7)
			dev_priv->display.color_check = ivb_color_check;
		अन्यथा
			dev_priv->display.color_check = ilk_color_check;

		अगर (DISPLAY_VER(dev_priv) >= 9)
			dev_priv->display.color_commit = skl_color_commit;
		अन्यथा अगर (IS_BROADWELL(dev_priv) || IS_HASWELL(dev_priv))
			dev_priv->display.color_commit = hsw_color_commit;
		अन्यथा
			dev_priv->display.color_commit = ilk_color_commit;

		अगर (DISPLAY_VER(dev_priv) >= 11) अणु
			dev_priv->display.load_luts = icl_load_luts;
			dev_priv->display.पढ़ो_luts = icl_पढ़ो_luts;
		पूर्ण अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 10)) अणु
			dev_priv->display.load_luts = glk_load_luts;
			dev_priv->display.पढ़ो_luts = glk_पढ़ो_luts;
		पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 8) अणु
			dev_priv->display.load_luts = bdw_load_luts;
		पूर्ण अन्यथा अगर (DISPLAY_VER(dev_priv) >= 7) अणु
			dev_priv->display.load_luts = ivb_load_luts;
		पूर्ण अन्यथा अणु
			dev_priv->display.load_luts = ilk_load_luts;
			dev_priv->display.पढ़ो_luts = ilk_पढ़ो_luts;
		पूर्ण
	पूर्ण

	drm_crtc_enable_color_mgmt(&crtc->base,
				   INTEL_INFO(dev_priv)->color.degamma_lut_size,
				   has_cपंचांग,
				   INTEL_INFO(dev_priv)->color.gamma_lut_size);
पूर्ण
