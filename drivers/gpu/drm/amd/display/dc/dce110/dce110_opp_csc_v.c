<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
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

#समावेश "dm_services.h"
#समावेश "dce110_transform_v.h"
#समावेश "basics/conversion.h"

/* include DCE11 रेजिस्टर header files */
#समावेश "dce/dce_11_0_d.h"
#समावेश "dce/dce_11_0_sh_mask.h"
#समावेश "dce/dce_11_0_enum.h"

क्रमागत अणु
	OUTPUT_CSC_MATRIX_SIZE = 12
पूर्ण;

/* स्थिरrast:0 - 2.0, शेष 1.0 */
#घोषणा UNDERLAY_CONTRAST_DEFAULT 100
#घोषणा UNDERLAY_CONTRAST_MAX     200
#घोषणा UNDERLAY_CONTRAST_MIN       0
#घोषणा UNDERLAY_CONTRAST_STEP      1
#घोषणा UNDERLAY_CONTRAST_DIVIDER 100

/* Saturation: 0 - 2.0; शेष 1.0 */
#घोषणा UNDERLAY_SATURATION_DEFAULT   100 /*1.00*/
#घोषणा UNDERLAY_SATURATION_MIN         0
#घोषणा UNDERLAY_SATURATION_MAX       200 /* 2.00 */
#घोषणा UNDERLAY_SATURATION_STEP        1 /* 0.01 */
/*actual max overlay saturation
 * value = UNDERLAY_SATURATION_MAX /UNDERLAY_SATURATION_DIVIDER
 */

/* Hue */
#घोषणा  UNDERLAY_HUE_DEFAULT      0
#घोषणा  UNDERLAY_HUE_MIN       -300
#घोषणा  UNDERLAY_HUE_MAX        300
#घोषणा  UNDERLAY_HUE_STEP         5
#घोषणा  UNDERLAY_HUE_DIVIDER   10 /* HW range: -30 ~ +30 */
#घोषणा UNDERLAY_SATURATION_DIVIDER   100

/* Brightness: in DAL usually -.25 ~ .25.
 * In MMD is -100 to +100 in 16-235 range; which when scaled to full range is
 *  ~-116 to +116. When normalized this is about 0.4566.
 * With 100 भागider this becomes 46, but we may use another क्रम better precision
 * The ideal one is 100/219 ((100/255)*(255/219)),
 * i.e. min/max = +-100, भागider = 219
 * शेष 0.0
 */
#घोषणा  UNDERLAY_BRIGHTNESS_DEFAULT    0
#घोषणा  UNDERLAY_BRIGHTNESS_MIN      -46 /* ~116/255 */
#घोषणा  UNDERLAY_BRIGHTNESS_MAX       46
#घोषणा  UNDERLAY_BRIGHTNESS_STEP       1 /*  .01 */
#घोषणा  UNDERLAY_BRIGHTNESS_DIVIDER  100

अटल स्थिर काष्ठा out_csc_color_matrix global_color_matrix[] = अणु
अणु COLOR_SPACE_SRGB,
	अणु 0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0पूर्ण पूर्ण,
अणु COLOR_SPACE_SRGB_LIMITED,
	अणु 0x1B60, 0, 0, 0x200, 0, 0x1B60, 0, 0x200, 0, 0, 0x1B60, 0x200पूर्ण पूर्ण,
अणु COLOR_SPACE_YCBCR601,
	अणु 0xE00, 0xF447, 0xFDB9, 0x1000, 0x82F, 0x1012, 0x31F, 0x200, 0xFB47,
		0xF6B9, 0xE00, 0x1000पूर्ण पूर्ण,
अणु COLOR_SPACE_YCBCR709, अणु 0xE00, 0xF349, 0xFEB7, 0x1000, 0x5D2, 0x1394, 0x1FA,
	0x200, 0xFCCB, 0xF535, 0xE00, 0x1000पूर्ण पूर्ण,
/* TODO: correct values below */
अणु COLOR_SPACE_YCBCR601_LIMITED, अणु 0xE00, 0xF447, 0xFDB9, 0x1000, 0x991,
	0x12C9, 0x3A6, 0x200, 0xFB47, 0xF6B9, 0xE00, 0x1000पूर्ण पूर्ण,
अणु COLOR_SPACE_YCBCR709_LIMITED, अणु 0xE00, 0xF349, 0xFEB7, 0x1000, 0x6CE, 0x16E3,
	0x24F, 0x200, 0xFCCB, 0xF535, 0xE00, 0x1000पूर्ण पूर्ण
पूर्ण;

क्रमागत csc_color_mode अणु
	/* 00 - BITS2:0 Bypass */
	CSC_COLOR_MODE_GRAPHICS_BYPASS,
	/* 01 - hard coded coefficient TV RGB */
	CSC_COLOR_MODE_GRAPHICS_PREDEFINED,
	/* 04 - programmable OUTPUT CSC coefficient */
	CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC,
पूर्ण;

क्रमागत grph_color_adjust_option अणु
	GRPH_COLOR_MATRIX_HW_DEFAULT = 1,
	GRPH_COLOR_MATRIX_SW
पूर्ण;

अटल व्योम program_color_matrix_v(
	काष्ठा dce_transक्रमm *xfm_dce,
	स्थिर काष्ठा out_csc_color_matrix *tbl_entry,
	क्रमागत grph_color_adjust_option options)
अणु
	काष्ठा dc_context *ctx = xfm_dce->base.ctx;
	uपूर्णांक32_t cntl_value = dm_पढ़ो_reg(ctx, mmCOL_MAN_OUTPUT_CSC_CONTROL);
	bool use_set_a = (get_reg_field_value(cntl_value,
			COL_MAN_OUTPUT_CSC_CONTROL,
			OUTPUT_CSC_MODE) != 4);

	set_reg_field_value(
			cntl_value,
		0,
		COL_MAN_OUTPUT_CSC_CONTROL,
		OUTPUT_CSC_MODE);

	अगर (use_set_a) अणु
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C11_C12_A;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[0],
				OUTPUT_CSC_C11_C12_A,
				OUTPUT_CSC_C11_A);

			set_reg_field_value(
				value,
				tbl_entry->regval[1],
				OUTPUT_CSC_C11_C12_A,
				OUTPUT_CSC_C12_A);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C13_C14_A;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[2],
				OUTPUT_CSC_C13_C14_A,
				OUTPUT_CSC_C13_A);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[3],
				OUTPUT_CSC_C13_C14_A,
				OUTPUT_CSC_C14_A);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C21_C22_A;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[4],
				OUTPUT_CSC_C21_C22_A,
				OUTPUT_CSC_C21_A);
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[5],
				OUTPUT_CSC_C21_C22_A,
				OUTPUT_CSC_C22_A);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C23_C24_A;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[6],
				OUTPUT_CSC_C23_C24_A,
				OUTPUT_CSC_C23_A);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[7],
				OUTPUT_CSC_C23_C24_A,
				OUTPUT_CSC_C24_A);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C31_C32_A;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[8],
				OUTPUT_CSC_C31_C32_A,
				OUTPUT_CSC_C31_A);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[9],
				OUTPUT_CSC_C31_C32_A,
				OUTPUT_CSC_C32_A);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C33_C34_A;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[10],
				OUTPUT_CSC_C33_C34_A,
				OUTPUT_CSC_C33_A);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[11],
				OUTPUT_CSC_C33_C34_A,
				OUTPUT_CSC_C34_A);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		set_reg_field_value(
			cntl_value,
			4,
			COL_MAN_OUTPUT_CSC_CONTROL,
			OUTPUT_CSC_MODE);
	पूर्ण अन्यथा अणु
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C11_C12_B;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[0],
				OUTPUT_CSC_C11_C12_B,
				OUTPUT_CSC_C11_B);

			set_reg_field_value(
				value,
				tbl_entry->regval[1],
				OUTPUT_CSC_C11_C12_B,
				OUTPUT_CSC_C12_B);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C13_C14_B;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[2],
				OUTPUT_CSC_C13_C14_B,
				OUTPUT_CSC_C13_B);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[3],
				OUTPUT_CSC_C13_C14_B,
				OUTPUT_CSC_C14_B);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C21_C22_B;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[4],
				OUTPUT_CSC_C21_C22_B,
				OUTPUT_CSC_C21_B);
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[5],
				OUTPUT_CSC_C21_C22_B,
				OUTPUT_CSC_C22_B);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C23_C24_B;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[6],
				OUTPUT_CSC_C23_C24_B,
				OUTPUT_CSC_C23_B);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[7],
				OUTPUT_CSC_C23_C24_B,
				OUTPUT_CSC_C24_B);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C31_C32_B;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[8],
				OUTPUT_CSC_C31_C32_B,
				OUTPUT_CSC_C31_B);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[9],
				OUTPUT_CSC_C31_C32_B,
				OUTPUT_CSC_C32_B);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		अणु
			uपूर्णांक32_t value = 0;
			uपूर्णांक32_t addr = mmOUTPUT_CSC_C33_C34_B;
			/* fixed S2.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[10],
				OUTPUT_CSC_C33_C34_B,
				OUTPUT_CSC_C33_B);
			/* fixed S0.13 क्रमmat */
			set_reg_field_value(
				value,
				tbl_entry->regval[11],
				OUTPUT_CSC_C33_C34_B,
				OUTPUT_CSC_C34_B);

			dm_ग_लिखो_reg(ctx, addr, value);
		पूर्ण
		set_reg_field_value(
			cntl_value,
			5,
			COL_MAN_OUTPUT_CSC_CONTROL,
			OUTPUT_CSC_MODE);
	पूर्ण

	dm_ग_लिखो_reg(ctx, mmCOL_MAN_OUTPUT_CSC_CONTROL, cntl_value);
पूर्ण

अटल bool configure_graphics_mode_v(
	काष्ठा dce_transक्रमm *xfm_dce,
	क्रमागत csc_color_mode config,
	क्रमागत graphics_csc_adjust_type csc_adjust_type,
	क्रमागत dc_color_space color_space)
अणु
	काष्ठा dc_context *ctx = xfm_dce->base.ctx;
	uपूर्णांक32_t addr = mmCOL_MAN_OUTPUT_CSC_CONTROL;
	uपूर्णांक32_t value = dm_पढ़ो_reg(ctx, addr);

	set_reg_field_value(
		value,
		0,
		COL_MAN_OUTPUT_CSC_CONTROL,
		OUTPUT_CSC_MODE);

	अगर (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_SW) अणु
		अगर (config == CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC)
			वापस true;

		चयन (color_space) अणु
		हाल COLOR_SPACE_SRGB:
			/* by pass */
			set_reg_field_value(
				value,
				0,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			अवरोध;
		हाल COLOR_SPACE_SRGB_LIMITED:
			/* not supported क्रम underlay on CZ */
			वापस false;

		हाल COLOR_SPACE_YCBCR601_LIMITED:
			/* YCbCr601 */
			set_reg_field_value(
				value,
				2,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			अवरोध;
		हाल COLOR_SPACE_YCBCR709:
		हाल COLOR_SPACE_YCBCR709_LIMITED:
			/* YCbCr709 */
			set_reg_field_value(
				value,
				3,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

	पूर्ण अन्यथा अगर (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_HW) अणु
		चयन (color_space) अणु
		हाल COLOR_SPACE_SRGB:
			/* by pass */
			set_reg_field_value(
				value,
				0,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			अवरोध;
		हाल COLOR_SPACE_SRGB_LIMITED:
			/* not supported क्रम underlay on CZ */
			वापस false;
		हाल COLOR_SPACE_YCBCR601:
		हाल COLOR_SPACE_YCBCR601_LIMITED:
			/* YCbCr601 */
			set_reg_field_value(
				value,
				2,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			अवरोध;
		हाल COLOR_SPACE_YCBCR709:
		हाल COLOR_SPACE_YCBCR709_LIMITED:
			 /* YCbCr709 */
			set_reg_field_value(
				value,
				3,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			अवरोध;
		शेष:
			वापस false;
		पूर्ण

	पूर्ण अन्यथा
		/* by pass */
		set_reg_field_value(
			value,
			0,
			COL_MAN_OUTPUT_CSC_CONTROL,
			OUTPUT_CSC_MODE);

	addr = mmCOL_MAN_OUTPUT_CSC_CONTROL;
	dm_ग_लिखो_reg(ctx, addr, value);

	वापस true;
पूर्ण

/*TODO: color depth is not correct when this is called*/
अटल व्योम set_Denormalization(काष्ठा transक्रमm *xfm,
		क्रमागत dc_color_depth color_depth)
अणु
	uपूर्णांक32_t value = dm_पढ़ो_reg(xfm->ctx, mmDENORM_CLAMP_CONTROL);

	चयन (color_depth) अणु
	हाल COLOR_DEPTH_888:
		/* 255/256 क्रम 8 bit output color depth */
		set_reg_field_value(
			value,
			1,
			DENORM_CLAMP_CONTROL,
			DENORM_MODE);
		अवरोध;
	हाल COLOR_DEPTH_101010:
		/* 1023/1024 क्रम 10 bit output color depth */
		set_reg_field_value(
			value,
			2,
			DENORM_CLAMP_CONTROL,
			DENORM_MODE);
		अवरोध;
	हाल COLOR_DEPTH_121212:
		/* 4095/4096 क्रम 12 bit output color depth */
		set_reg_field_value(
			value,
			3,
			DENORM_CLAMP_CONTROL,
			DENORM_MODE);
		अवरोध;
	शेष:
		/* not valid हाल */
		अवरोध;
	पूर्ण

	set_reg_field_value(
		value,
		1,
		DENORM_CLAMP_CONTROL,
		DENORM_10BIT_OUT);

	dm_ग_लिखो_reg(xfm->ctx, mmDENORM_CLAMP_CONTROL, value);
पूर्ण

काष्ठा input_csc_matrix अणु
	क्रमागत dc_color_space color_space;
	uपूर्णांक32_t regval[12];
पूर्ण;

अटल स्थिर काष्ठा input_csc_matrix input_csc_matrix[] = अणु
	अणुCOLOR_SPACE_SRGB,
/*1_1   1_2   1_3   1_4   2_1   2_2   2_3   2_4   3_1   3_2   3_3   3_4 */
		अणु0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0पूर्ण पूर्ण,
	अणुCOLOR_SPACE_SRGB_LIMITED,
		अणु0x2000, 0, 0, 0, 0, 0x2000, 0, 0, 0, 0, 0x2000, 0पूर्ण पूर्ण,
	अणुCOLOR_SPACE_YCBCR601,
		अणु0x2cdd, 0x2000, 0x0, 0xe991, 0xe926, 0x2000, 0xf4fd, 0x10ef,
						0x0, 0x2000, 0x38b4, 0xe3a6पूर्ण पूर्ण,
	अणुCOLOR_SPACE_YCBCR601_LIMITED,
		अणु0x3353, 0x2568, 0x0, 0xe400, 0xe5dc, 0x2568, 0xf367, 0x1108,
						0x0, 0x2568, 0x40de, 0xdd3aपूर्ण पूर्ण,
	अणुCOLOR_SPACE_YCBCR709,
		अणु0x3265, 0x2000, 0, 0xe6ce, 0xf105, 0x2000, 0xfa01, 0xa7d, 0,
						0x2000, 0x3b61, 0xe24fपूर्ण पूर्ण,
	अणुCOLOR_SPACE_YCBCR709_LIMITED,
		अणु0x39a6, 0x2568, 0, 0xe0d6, 0xeedd, 0x2568, 0xf925, 0x9a8, 0,
						0x2568, 0x43ee, 0xdbb2पूर्ण पूर्ण
पूर्ण;

अटल व्योम program_input_csc(
		काष्ठा transक्रमm *xfm, क्रमागत dc_color_space color_space)
अणु
	पूर्णांक arr_size = माप(input_csc_matrix)/माप(काष्ठा input_csc_matrix);
	काष्ठा dc_context *ctx = xfm->ctx;
	स्थिर uपूर्णांक32_t *regval = शून्य;
	bool use_set_a;
	uपूर्णांक32_t value;
	पूर्णांक i;

	क्रम (i = 0; i < arr_size; i++)
		अगर (input_csc_matrix[i].color_space == color_space) अणु
			regval = input_csc_matrix[i].regval;
			अवरोध;
		पूर्ण
	अगर (regval == शून्य) अणु
		BREAK_TO_DEBUGGER();
		वापस;
	पूर्ण

	/*
	 * 1 == set A, the logic is 'if currently we're not using set A,
	 * then use set A, otherwise use set B'
	 */
	value = dm_पढ़ो_reg(ctx, mmCOL_MAN_INPUT_CSC_CONTROL);
	use_set_a = get_reg_field_value(
		value, COL_MAN_INPUT_CSC_CONTROL, INPUT_CSC_MODE) != 1;

	अगर (use_set_a) अणु
		/* fixed S2.13 क्रमmat */
		value = 0;
		set_reg_field_value(
			value, regval[0], INPUT_CSC_C11_C12_A, INPUT_CSC_C11_A);
		set_reg_field_value(
			value, regval[1], INPUT_CSC_C11_C12_A, INPUT_CSC_C12_A);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C11_C12_A, value);

		value = 0;
		set_reg_field_value(
			value, regval[2], INPUT_CSC_C13_C14_A, INPUT_CSC_C13_A);
		set_reg_field_value(
			value, regval[3], INPUT_CSC_C13_C14_A, INPUT_CSC_C14_A);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C13_C14_A, value);

		value = 0;
		set_reg_field_value(
			value, regval[4], INPUT_CSC_C21_C22_A, INPUT_CSC_C21_A);
		set_reg_field_value(
			value, regval[5], INPUT_CSC_C21_C22_A, INPUT_CSC_C22_A);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C21_C22_A, value);

		value = 0;
		set_reg_field_value(
			value, regval[6], INPUT_CSC_C23_C24_A, INPUT_CSC_C23_A);
		set_reg_field_value(
			value, regval[7], INPUT_CSC_C23_C24_A, INPUT_CSC_C24_A);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C23_C24_A, value);

		value = 0;
		set_reg_field_value(
			value, regval[8], INPUT_CSC_C31_C32_A, INPUT_CSC_C31_A);
		set_reg_field_value(
			value, regval[9], INPUT_CSC_C31_C32_A, INPUT_CSC_C32_A);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C31_C32_A, value);

		value = 0;
		set_reg_field_value(
			value, regval[10], INPUT_CSC_C33_C34_A, INPUT_CSC_C33_A);
		set_reg_field_value(
			value, regval[11], INPUT_CSC_C33_C34_A, INPUT_CSC_C34_A);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C33_C34_A, value);
	पूर्ण अन्यथा अणु
		/* fixed S2.13 क्रमmat */
		value = 0;
		set_reg_field_value(
			value, regval[0], INPUT_CSC_C11_C12_B, INPUT_CSC_C11_B);
		set_reg_field_value(
			value, regval[1], INPUT_CSC_C11_C12_B, INPUT_CSC_C12_B);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C11_C12_B, value);

		value = 0;
		set_reg_field_value(
			value, regval[2], INPUT_CSC_C13_C14_B, INPUT_CSC_C13_B);
		set_reg_field_value(
			value, regval[3], INPUT_CSC_C13_C14_B, INPUT_CSC_C14_B);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C13_C14_B, value);

		value = 0;
		set_reg_field_value(
			value, regval[4], INPUT_CSC_C21_C22_B, INPUT_CSC_C21_B);
		set_reg_field_value(
			value, regval[5], INPUT_CSC_C21_C22_B, INPUT_CSC_C22_B);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C21_C22_B, value);

		value = 0;
		set_reg_field_value(
			value, regval[6], INPUT_CSC_C23_C24_B, INPUT_CSC_C23_B);
		set_reg_field_value(
			value, regval[7], INPUT_CSC_C23_C24_B, INPUT_CSC_C24_B);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C23_C24_B, value);

		value = 0;
		set_reg_field_value(
			value, regval[8], INPUT_CSC_C31_C32_B, INPUT_CSC_C31_B);
		set_reg_field_value(
			value, regval[9], INPUT_CSC_C31_C32_B, INPUT_CSC_C32_B);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C31_C32_B, value);

		value = 0;
		set_reg_field_value(
			value, regval[10], INPUT_CSC_C33_C34_B, INPUT_CSC_C33_B);
		set_reg_field_value(
			value, regval[11], INPUT_CSC_C33_C34_B, INPUT_CSC_C34_B);
		dm_ग_लिखो_reg(ctx, mmINPUT_CSC_C33_C34_B, value);
	पूर्ण

	/* KK: leave INPUT_CSC_CONVERSION_MODE at शेष */
	value = 0;
	/*
	 * select 8.4 input type instead of शेष 12.0. From the discussion
	 * with HW team, this क्रमmat depends on the UNP surface क्रमmat, so क्रम
	 * 8-bit we should select 8.4 (4 bits truncated). For 10 it should be
	 * 10.2. For Carrizo we only support 8-bit surfaces on underlay pipe
	 * so we can always keep this at 8.4 (input_type=2). If the later asics
	 * start supporting 10+ bits, we will have a problem: surface
	 * programming including UNP_GRPH* is being करोne in DalISR after this,
	 * so either we pass surface क्रमmat to here, or move this logic to ISR
	 */

	set_reg_field_value(
		value, 2, COL_MAN_INPUT_CSC_CONTROL, INPUT_CSC_INPUT_TYPE);
	set_reg_field_value(
		value,
		use_set_a ? 1 : 2,
		COL_MAN_INPUT_CSC_CONTROL,
		INPUT_CSC_MODE);

	dm_ग_लिखो_reg(ctx, mmCOL_MAN_INPUT_CSC_CONTROL, value);
पूर्ण

व्योम dce110_opp_v_set_csc_शेष(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा शेष_adjusपंचांगent *शेष_adjust)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	क्रमागत csc_color_mode config =
			CSC_COLOR_MODE_GRAPHICS_PREDEFINED;

	अगर (शेष_adjust->क्रमce_hw_शेष == false) अणु
		स्थिर काष्ठा out_csc_color_matrix *elm;
		/* currently parameter not in use */
		क्रमागत grph_color_adjust_option option;
		uपूर्णांक32_t i;
		/*
		 * HW शेष false we program locally defined matrix
		 * HW शेष true  we use predefined hw matrix and we
		 * करो not need to program matrix
		 * OEM wants the HW शेष via runसमय parameter.
		 */
		option = GRPH_COLOR_MATRIX_SW;

		क्रम (i = 0; i < ARRAY_SIZE(global_color_matrix); ++i) अणु
			elm = &global_color_matrix[i];
			अगर (elm->color_space != शेष_adjust->out_color_space)
				जारी;
			/* program the matrix with शेष values from this
			 * file
			 */
			program_color_matrix_v(xfm_dce, elm, option);
			config = CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC;
			अवरोध;
		पूर्ण
	पूर्ण

	program_input_csc(xfm, शेष_adjust->in_color_space);

	/* configure the what we programmed :
	 * 1. Default values from this file
	 * 2. Use hardware शेष from ROM_A and we करो not need to program
	 * matrix
	 */

	configure_graphics_mode_v(xfm_dce, config,
		शेष_adjust->csc_adjust_type,
		शेष_adjust->out_color_space);

	set_Denormalization(xfm, शेष_adjust->color_depth);
पूर्ण

व्योम dce110_opp_v_set_csc_adjusपंचांगent(
	काष्ठा transक्रमm *xfm,
	स्थिर काष्ठा out_csc_color_matrix *tbl_entry)
अणु
	काष्ठा dce_transक्रमm *xfm_dce = TO_DCE_TRANSFORM(xfm);
	क्रमागत csc_color_mode config =
			CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC;

	program_color_matrix_v(
			xfm_dce, tbl_entry, GRPH_COLOR_MATRIX_SW);

	/*  We did everything ,now program DxOUTPUT_CSC_CONTROL */
	configure_graphics_mode_v(xfm_dce, config, GRAPHICS_CSC_ADJUST_TYPE_SW,
			tbl_entry->color_space);

	/*TODO: Check अगर denormalization is needed*/
	/*set_Denormalization(opp, adjust->color_depth);*/
पूर्ण
