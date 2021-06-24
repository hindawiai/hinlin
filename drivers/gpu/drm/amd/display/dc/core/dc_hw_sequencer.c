<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#समावेश <linux/delay.h>

#समावेश "dm_services.h"
#समावेश "core_types.h"
#समावेश "timing_generator.h"
#समावेश "hw_sequencer.h"

#घोषणा NUM_ELEMENTS(a) (माप(a) / माप((a)[0]))

/* used as index in array of black_color_क्रमmat */
क्रमागत black_color_क्रमmat अणु
	BLACK_COLOR_FORMAT_RGB_FULLRANGE = 0,
	BLACK_COLOR_FORMAT_RGB_LIMITED,
	BLACK_COLOR_FORMAT_YUV_TV,
	BLACK_COLOR_FORMAT_YUV_CV,
	BLACK_COLOR_FORMAT_YUV_SUPER_AA,
	BLACK_COLOR_FORMAT_DEBUG,
पूर्ण;

क्रमागत dc_color_space_type अणु
	COLOR_SPACE_RGB_TYPE,
	COLOR_SPACE_RGB_LIMITED_TYPE,
	COLOR_SPACE_YCBCR601_TYPE,
	COLOR_SPACE_YCBCR709_TYPE,
	COLOR_SPACE_YCBCR2020_TYPE,
	COLOR_SPACE_YCBCR601_LIMITED_TYPE,
	COLOR_SPACE_YCBCR709_LIMITED_TYPE,
	COLOR_SPACE_YCBCR709_BLACK_TYPE,
पूर्ण;

अटल स्थिर काष्ठा tg_color black_color_क्रमmat[] = अणु
	/* BlackColorFormat_RGB_FullRange */
	अणु0, 0, 0पूर्ण,
	/* BlackColorFormat_RGB_Limited */
	अणु0x40, 0x40, 0x40पूर्ण,
	/* BlackColorFormat_YUV_TV */
	अणु0x200, 0x40, 0x200पूर्ण,
	/* BlackColorFormat_YUV_CV */
	अणु0x1f4, 0x40, 0x1f4पूर्ण,
	/* BlackColorFormat_YUV_SuperAA */
	अणु0x1a2, 0x20, 0x1a2पूर्ण,
	/* visual confirm debug */
	अणु0xff, 0xff, 0पूर्ण,
पूर्ण;

काष्ठा out_csc_color_matrix_type अणु
	क्रमागत dc_color_space_type color_space_type;
	uपूर्णांक16_t regval[12];
पूर्ण;

अटल स्थिर काष्ठा out_csc_color_matrix_type output_csc_matrix[] = अणु
	अणु COLOR_SPACE_RGB_TYPE,
		अणु 0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0पूर्ण पूर्ण,
	अणु COLOR_SPACE_RGB_LIMITED_TYPE,
		अणु 0x1B67, 0, 0, 0x201, 0, 0x1B67, 0, 0x201, 0, 0, 0x1B67, 0x201पूर्ण पूर्ण,
	अणु COLOR_SPACE_YCBCR601_TYPE,
		अणु 0xE04, 0xF444, 0xFDB9, 0x1004, 0x831, 0x1016, 0x320, 0x201, 0xFB45,
				0xF6B7, 0xE04, 0x1004पूर्ण पूर्ण,
	अणु COLOR_SPACE_YCBCR709_TYPE,
		अणु 0xE04, 0xF345, 0xFEB7, 0x1004, 0x5D3, 0x1399, 0x1FA,
				0x201, 0xFCCA, 0xF533, 0xE04, 0x1004पूर्ण पूर्ण,
	/* TODO: correct values below */
	अणु COLOR_SPACE_YCBCR601_LIMITED_TYPE,
		अणु 0xE00, 0xF447, 0xFDB9, 0x1000, 0x991,
				0x12C9, 0x3A6, 0x200, 0xFB47, 0xF6B9, 0xE00, 0x1000पूर्ण पूर्ण,
	अणु COLOR_SPACE_YCBCR709_LIMITED_TYPE,
		अणु 0xE00, 0xF349, 0xFEB7, 0x1000, 0x6CE, 0x16E3,
				0x24F, 0x200, 0xFCCB, 0xF535, 0xE00, 0x1000पूर्ण पूर्ण,
	अणु COLOR_SPACE_YCBCR2020_TYPE,
		अणु 0x1000, 0xF149, 0xFEB7, 0x0000, 0x0868, 0x15B2,
				0x01E6, 0x0000, 0xFB88, 0xF478, 0x1000, 0x0000पूर्ण पूर्ण,
	अणु COLOR_SPACE_YCBCR709_BLACK_TYPE,
		अणु 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000,
				0x0000, 0x0200, 0x0000, 0x0000, 0x0000, 0x1000पूर्ण पूर्ण,
पूर्ण;

अटल bool is_rgb_type(
		क्रमागत dc_color_space color_space)
अणु
	bool ret = false;

	अगर (color_space == COLOR_SPACE_SRGB			||
		color_space == COLOR_SPACE_XR_RGB		||
		color_space == COLOR_SPACE_MSREF_SCRGB		||
		color_space == COLOR_SPACE_2020_RGB_FULLRANGE	||
		color_space == COLOR_SPACE_ADOBERGB		||
		color_space == COLOR_SPACE_DCIP3	||
		color_space == COLOR_SPACE_DOLBYVISION)
		ret = true;
	वापस ret;
पूर्ण

अटल bool is_rgb_limited_type(
		क्रमागत dc_color_space color_space)
अणु
	bool ret = false;

	अगर (color_space == COLOR_SPACE_SRGB_LIMITED		||
		color_space == COLOR_SPACE_2020_RGB_LIMITEDRANGE)
		ret = true;
	वापस ret;
पूर्ण

अटल bool is_ycbcr601_type(
		क्रमागत dc_color_space color_space)
अणु
	bool ret = false;

	अगर (color_space == COLOR_SPACE_YCBCR601	||
		color_space == COLOR_SPACE_XV_YCC_601)
		ret = true;
	वापस ret;
पूर्ण

अटल bool is_ycbcr601_limited_type(
		क्रमागत dc_color_space color_space)
अणु
	bool ret = false;

	अगर (color_space == COLOR_SPACE_YCBCR601_LIMITED)
		ret = true;
	वापस ret;
पूर्ण

अटल bool is_ycbcr709_type(
		क्रमागत dc_color_space color_space)
अणु
	bool ret = false;

	अगर (color_space == COLOR_SPACE_YCBCR709	||
		color_space == COLOR_SPACE_XV_YCC_709)
		ret = true;
	वापस ret;
पूर्ण

अटल bool is_ycbcr2020_type(
	क्रमागत dc_color_space color_space)
अणु
	bool ret = false;

	अगर (color_space == COLOR_SPACE_2020_YCBCR)
		ret = true;
	वापस ret;
पूर्ण

अटल bool is_ycbcr709_limited_type(
		क्रमागत dc_color_space color_space)
अणु
	bool ret = false;

	अगर (color_space == COLOR_SPACE_YCBCR709_LIMITED)
		ret = true;
	वापस ret;
पूर्ण
अटल क्रमागत dc_color_space_type get_color_space_type(क्रमागत dc_color_space color_space)
अणु
	क्रमागत dc_color_space_type type = COLOR_SPACE_RGB_TYPE;

	अगर (is_rgb_type(color_space))
		type = COLOR_SPACE_RGB_TYPE;
	अन्यथा अगर (is_rgb_limited_type(color_space))
		type = COLOR_SPACE_RGB_LIMITED_TYPE;
	अन्यथा अगर (is_ycbcr601_type(color_space))
		type = COLOR_SPACE_YCBCR601_TYPE;
	अन्यथा अगर (is_ycbcr709_type(color_space))
		type = COLOR_SPACE_YCBCR709_TYPE;
	अन्यथा अगर (is_ycbcr601_limited_type(color_space))
		type = COLOR_SPACE_YCBCR601_LIMITED_TYPE;
	अन्यथा अगर (is_ycbcr709_limited_type(color_space))
		type = COLOR_SPACE_YCBCR709_LIMITED_TYPE;
	अन्यथा अगर (is_ycbcr2020_type(color_space))
		type = COLOR_SPACE_YCBCR2020_TYPE;
	अन्यथा अगर (color_space == COLOR_SPACE_YCBCR709)
		type = COLOR_SPACE_YCBCR709_BLACK_TYPE;
	अन्यथा अगर (color_space == COLOR_SPACE_YCBCR709_BLACK)
		type = COLOR_SPACE_YCBCR709_BLACK_TYPE;
	वापस type;
पूर्ण

स्थिर uपूर्णांक16_t *find_color_matrix(क्रमागत dc_color_space color_space,
							uपूर्णांक32_t *array_size)
अणु
	पूर्णांक i;
	क्रमागत dc_color_space_type type;
	स्थिर uपूर्णांक16_t *val = शून्य;
	पूर्णांक arr_size = NUM_ELEMENTS(output_csc_matrix);

	type = get_color_space_type(color_space);
	क्रम (i = 0; i < arr_size; i++)
		अगर (output_csc_matrix[i].color_space_type == type) अणु
			val = output_csc_matrix[i].regval;
			*array_size = 12;
			अवरोध;
		पूर्ण

	वापस val;
पूर्ण


व्योम color_space_to_black_color(
	स्थिर काष्ठा dc *dc,
	क्रमागत dc_color_space colorspace,
	काष्ठा tg_color *black_color)
अणु
	चयन (colorspace) अणु
	हाल COLOR_SPACE_YCBCR601:
	हाल COLOR_SPACE_YCBCR709:
	हाल COLOR_SPACE_YCBCR709_BLACK:
	हाल COLOR_SPACE_YCBCR601_LIMITED:
	हाल COLOR_SPACE_YCBCR709_LIMITED:
	हाल COLOR_SPACE_2020_YCBCR:
		*black_color = black_color_क्रमmat[BLACK_COLOR_FORMAT_YUV_CV];
		अवरोध;

	हाल COLOR_SPACE_SRGB_LIMITED:
		*black_color =
			black_color_क्रमmat[BLACK_COLOR_FORMAT_RGB_LIMITED];
		अवरोध;

	/**
	 * Remove शेष and add हाल क्रम all color space
	 * so when we क्रमget to add new color space
	 * compiler will give a warning
	 */
	हाल COLOR_SPACE_UNKNOWN:
	हाल COLOR_SPACE_SRGB:
	हाल COLOR_SPACE_XR_RGB:
	हाल COLOR_SPACE_MSREF_SCRGB:
	हाल COLOR_SPACE_XV_YCC_709:
	हाल COLOR_SPACE_XV_YCC_601:
	हाल COLOR_SPACE_2020_RGB_FULLRANGE:
	हाल COLOR_SPACE_2020_RGB_LIMITEDRANGE:
	हाल COLOR_SPACE_ADOBERGB:
	हाल COLOR_SPACE_DCIP3:
	हाल COLOR_SPACE_DISPLAYNATIVE:
	हाल COLOR_SPACE_DOLBYVISION:
	हाल COLOR_SPACE_APPCTRL:
	हाल COLOR_SPACE_CUSTOMPOINTS:
		/* fefault is sRGB black (full range). */
		*black_color =
			black_color_क्रमmat[BLACK_COLOR_FORMAT_RGB_FULLRANGE];
		/* शेष is sRGB black 0. */
		अवरोध;
	पूर्ण
पूर्ण

bool hwss_रुको_क्रम_blank_complete(
		काष्ठा timing_generator *tg)
अणु
	पूर्णांक counter;

	/* Not applicable अगर the pipe is not primary, save 300ms of boot समय */
	अगर (!tg->funcs->is_blanked)
		वापस true;
	क्रम (counter = 0; counter < 100; counter++) अणु
		अगर (tg->funcs->is_blanked(tg))
			अवरोध;

		msleep(1);
	पूर्ण

	अगर (counter == 100) अणु
		dm_error("DC: failed to blank crtc!\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण
