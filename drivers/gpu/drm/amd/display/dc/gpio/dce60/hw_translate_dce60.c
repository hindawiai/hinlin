<शैली गुरु>
/*
 * Copyright 2020 Mauro Rossi <issor.oruam@gmail.com>
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

#समावेश "dm_services.h"

/*
 * Pre-requisites: headers required by header of this unit
 */
#समावेश "include/gpio_types.h"
#समावेश "../hw_translate.h"

#समावेश "hw_translate_dce60.h"

#समावेश "dce/dce_6_0_d.h"
#समावेश "dce/dce_6_0_sh_mask.h"
#समावेश "smu/smu_6_0_d.h"

/*
 * @brief
 * Returns index of first bit (starting with LSB) which is set
 */
अटल uपूर्णांक32_t index_from_vector(
	uपूर्णांक32_t vector)
अणु
	uपूर्णांक32_t result = 0;
	uपूर्णांक32_t mask = 1;

	करो अणु
		अगर (vector == mask)
			वापस result;

		++result;
		mask <<= 1;
	पूर्ण जबतक (mask);

	BREAK_TO_DEBUGGER();

	वापस GPIO_ENUM_UNKNOWN;
पूर्ण

अटल bool offset_to_id(
	uपूर्णांक32_t offset,
	uपूर्णांक32_t mask,
	क्रमागत gpio_id *id,
	uपूर्णांक32_t *en)
अणु
	चयन (offset) अणु
	/* GENERIC */
	हाल mmDC_GPIO_GENERIC_A:
		*id = GPIO_ID_GENERIC;
		चयन (mask) अणु
		हाल DC_GPIO_GENERIC_A__DC_GPIO_GENERICA_A_MASK:
			*en = GPIO_GENERIC_A;
			वापस true;
		हाल DC_GPIO_GENERIC_A__DC_GPIO_GENERICB_A_MASK:
			*en = GPIO_GENERIC_B;
			वापस true;
		हाल DC_GPIO_GENERIC_A__DC_GPIO_GENERICC_A_MASK:
			*en = GPIO_GENERIC_C;
			वापस true;
		हाल DC_GPIO_GENERIC_A__DC_GPIO_GENERICD_A_MASK:
			*en = GPIO_GENERIC_D;
			वापस true;
		हाल DC_GPIO_GENERIC_A__DC_GPIO_GENERICE_A_MASK:
			*en = GPIO_GENERIC_E;
			वापस true;
		हाल DC_GPIO_GENERIC_A__DC_GPIO_GENERICF_A_MASK:
			*en = GPIO_GENERIC_F;
			वापस true;
		हाल DC_GPIO_GENERIC_A__DC_GPIO_GENERICG_A_MASK:
			*en = GPIO_GENERIC_G;
			वापस true;
		शेष:
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण
	अवरोध;
	/* HPD */
	हाल mmDC_GPIO_HPD_A:
		*id = GPIO_ID_HPD;
		चयन (mask) अणु
		हाल DC_GPIO_HPD_A__DC_GPIO_HPD1_A_MASK:
			*en = GPIO_HPD_1;
			वापस true;
		हाल DC_GPIO_HPD_A__DC_GPIO_HPD2_A_MASK:
			*en = GPIO_HPD_2;
			वापस true;
		हाल DC_GPIO_HPD_A__DC_GPIO_HPD3_A_MASK:
			*en = GPIO_HPD_3;
			वापस true;
		हाल DC_GPIO_HPD_A__DC_GPIO_HPD4_A_MASK:
			*en = GPIO_HPD_4;
			वापस true;
		हाल DC_GPIO_HPD_A__DC_GPIO_HPD5_A_MASK:
			*en = GPIO_HPD_5;
			वापस true;
		हाल DC_GPIO_HPD_A__DC_GPIO_HPD6_A_MASK:
			*en = GPIO_HPD_6;
			वापस true;
		शेष:
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण
	अवरोध;
	/* SYNCA */
	हाल mmDC_GPIO_SYNCA_A:
		*id = GPIO_ID_SYNC;
		चयन (mask) अणु
		हाल DC_GPIO_SYNCA_A__DC_GPIO_HSYNCA_A_MASK:
			*en = GPIO_SYNC_HSYNC_A;
			वापस true;
		हाल DC_GPIO_SYNCA_A__DC_GPIO_VSYNCA_A_MASK:
			*en = GPIO_SYNC_VSYNC_A;
			वापस true;
		शेष:
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण
	अवरोध;
	/* mmDC_GPIO_GENLK_MASK */
	हाल mmDC_GPIO_GENLK_A:
		*id = GPIO_ID_GSL;
		चयन (mask) अणु
		हाल DC_GPIO_GENLK_A__DC_GPIO_GENLK_CLK_A_MASK:
			*en = GPIO_GSL_GENLOCK_CLOCK;
			वापस true;
		हाल DC_GPIO_GENLK_A__DC_GPIO_GENLK_VSYNC_A_MASK:
			*en = GPIO_GSL_GENLOCK_VSYNC;
			वापस true;
		हाल DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_A_A_MASK:
			*en = GPIO_GSL_SWAPLOCK_A;
			वापस true;
		हाल DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_B_A_MASK:
			*en = GPIO_GSL_SWAPLOCK_B;
			वापस true;
		शेष:
			BREAK_TO_DEBUGGER();
			वापस false;
		पूर्ण
	अवरोध;
	/* GPIOPAD */
	हाल mmGPIOPAD_A:
		*id = GPIO_ID_GPIO_PAD;
		*en = index_from_vector(mask);
		वापस (*en <= GPIO_GPIO_PAD_MAX);
	/* DDC */
	/* we करोn't care about the GPIO_ID क्रम DDC
	 * in DdcHandle it will use GPIO_ID_DDC_DATA/GPIO_ID_DDC_CLOCK
	 * directly in the create method */
	हाल mmDC_GPIO_DDC1_A:
		*en = GPIO_DDC_LINE_DDC1;
		वापस true;
	हाल mmDC_GPIO_DDC2_A:
		*en = GPIO_DDC_LINE_DDC2;
		वापस true;
	हाल mmDC_GPIO_DDC3_A:
		*en = GPIO_DDC_LINE_DDC3;
		वापस true;
	हाल mmDC_GPIO_DDC4_A:
		*en = GPIO_DDC_LINE_DDC4;
		वापस true;
	हाल mmDC_GPIO_DDC5_A:
		*en = GPIO_DDC_LINE_DDC5;
		वापस true;
	हाल mmDC_GPIO_DDC6_A:
		*en = GPIO_DDC_LINE_DDC6;
		वापस true;
	हाल mmDC_GPIO_DDCVGA_A:
		*en = GPIO_DDC_LINE_DDC_VGA;
		वापस true;
	/* GPIO_I2CPAD */
	हाल mmDC_GPIO_I2CPAD_A:
		*en = GPIO_DDC_LINE_I2C_PAD;
		वापस true;
	/* Not implemented */
	हाल mmDC_GPIO_PWRSEQ_A:
	हाल mmDC_GPIO_PAD_STRENGTH_1:
	हाल mmDC_GPIO_PAD_STRENGTH_2:
	हाल mmDC_GPIO_DEBUG:
		वापस false;
	/* UNEXPECTED */
	शेष:
		BREAK_TO_DEBUGGER();
		वापस false;
	पूर्ण
पूर्ण

अटल bool id_to_offset(
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	काष्ठा gpio_pin_info *info)
अणु
	bool result = true;

	चयन (id) अणु
	हाल GPIO_ID_DDC_DATA:
		info->mask = DC_GPIO_DDC6_A__DC_GPIO_DDC6DATA_A_MASK;
		चयन (en) अणु
		हाल GPIO_DDC_LINE_DDC1:
			info->offset = mmDC_GPIO_DDC1_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC2:
			info->offset = mmDC_GPIO_DDC2_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC3:
			info->offset = mmDC_GPIO_DDC3_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC4:
			info->offset = mmDC_GPIO_DDC4_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC5:
			info->offset = mmDC_GPIO_DDC5_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC6:
			info->offset = mmDC_GPIO_DDC6_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC_VGA:
			info->offset = mmDC_GPIO_DDCVGA_A;
		अवरोध;
		हाल GPIO_DDC_LINE_I2C_PAD:
			info->offset = mmDC_GPIO_I2CPAD_A;
		अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			result = false;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_DDC_CLOCK:
		info->mask = DC_GPIO_DDC6_A__DC_GPIO_DDC6CLK_A_MASK;
		चयन (en) अणु
		हाल GPIO_DDC_LINE_DDC1:
			info->offset = mmDC_GPIO_DDC1_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC2:
			info->offset = mmDC_GPIO_DDC2_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC3:
			info->offset = mmDC_GPIO_DDC3_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC4:
			info->offset = mmDC_GPIO_DDC4_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC5:
			info->offset = mmDC_GPIO_DDC5_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC6:
			info->offset = mmDC_GPIO_DDC6_A;
		अवरोध;
		हाल GPIO_DDC_LINE_DDC_VGA:
			info->offset = mmDC_GPIO_DDCVGA_A;
		अवरोध;
		हाल GPIO_DDC_LINE_I2C_PAD:
			info->offset = mmDC_GPIO_I2CPAD_A;
		अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			result = false;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_GENERIC:
		info->offset = mmDC_GPIO_GENERIC_A;
		चयन (en) अणु
		हाल GPIO_GENERIC_A:
			info->mask = DC_GPIO_GENERIC_A__DC_GPIO_GENERICA_A_MASK;
		अवरोध;
		हाल GPIO_GENERIC_B:
			info->mask = DC_GPIO_GENERIC_A__DC_GPIO_GENERICB_A_MASK;
		अवरोध;
		हाल GPIO_GENERIC_C:
			info->mask = DC_GPIO_GENERIC_A__DC_GPIO_GENERICC_A_MASK;
		अवरोध;
		हाल GPIO_GENERIC_D:
			info->mask = DC_GPIO_GENERIC_A__DC_GPIO_GENERICD_A_MASK;
		अवरोध;
		हाल GPIO_GENERIC_E:
			info->mask = DC_GPIO_GENERIC_A__DC_GPIO_GENERICE_A_MASK;
		अवरोध;
		हाल GPIO_GENERIC_F:
			info->mask = DC_GPIO_GENERIC_A__DC_GPIO_GENERICF_A_MASK;
		अवरोध;
		हाल GPIO_GENERIC_G:
			info->mask = DC_GPIO_GENERIC_A__DC_GPIO_GENERICG_A_MASK;
		अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			result = false;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_HPD:
		info->offset = mmDC_GPIO_HPD_A;
		चयन (en) अणु
		हाल GPIO_HPD_1:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD1_A_MASK;
		अवरोध;
		हाल GPIO_HPD_2:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD2_A_MASK;
		अवरोध;
		हाल GPIO_HPD_3:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD3_A_MASK;
		अवरोध;
		हाल GPIO_HPD_4:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD4_A_MASK;
		अवरोध;
		हाल GPIO_HPD_5:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD5_A_MASK;
		अवरोध;
		हाल GPIO_HPD_6:
			info->mask = DC_GPIO_HPD_A__DC_GPIO_HPD6_A_MASK;
		अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			result = false;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_SYNC:
		चयन (en) अणु
		हाल GPIO_SYNC_HSYNC_A:
			info->offset = mmDC_GPIO_SYNCA_A;
			info->mask = DC_GPIO_SYNCA_A__DC_GPIO_HSYNCA_A_MASK;
		अवरोध;
		हाल GPIO_SYNC_VSYNC_A:
			info->offset = mmDC_GPIO_SYNCA_A;
			info->mask = DC_GPIO_SYNCA_A__DC_GPIO_VSYNCA_A_MASK;
		अवरोध;
		हाल GPIO_SYNC_HSYNC_B:
		हाल GPIO_SYNC_VSYNC_B:
		शेष:
			BREAK_TO_DEBUGGER();
			result = false;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_GSL:
		चयन (en) अणु
		हाल GPIO_GSL_GENLOCK_CLOCK:
			info->offset = mmDC_GPIO_GENLK_A;
			info->mask = DC_GPIO_GENLK_A__DC_GPIO_GENLK_CLK_A_MASK;
		अवरोध;
		हाल GPIO_GSL_GENLOCK_VSYNC:
			info->offset = mmDC_GPIO_GENLK_A;
			info->mask =
				DC_GPIO_GENLK_A__DC_GPIO_GENLK_VSYNC_A_MASK;
		अवरोध;
		हाल GPIO_GSL_SWAPLOCK_A:
			info->offset = mmDC_GPIO_GENLK_A;
			info->mask = DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_A_A_MASK;
		अवरोध;
		हाल GPIO_GSL_SWAPLOCK_B:
			info->offset = mmDC_GPIO_GENLK_A;
			info->mask = DC_GPIO_GENLK_A__DC_GPIO_SWAPLOCK_B_A_MASK;
		अवरोध;
		शेष:
			BREAK_TO_DEBUGGER();
			result = false;
		पूर्ण
	अवरोध;
	हाल GPIO_ID_GPIO_PAD:
		info->offset = mmGPIOPAD_A;
		info->mask = (1 << en);
		result = (info->mask <= GPIO_GPIO_PAD_MAX);
	अवरोध;
	हाल GPIO_ID_VIP_PAD:
	शेष:
		BREAK_TO_DEBUGGER();
		result = false;
	पूर्ण

	अगर (result) अणु
		info->offset_y = info->offset + 2;
		info->offset_en = info->offset + 1;
		info->offset_mask = info->offset - 1;

		info->mask_y = info->mask;
		info->mask_en = info->mask;
		info->mask_mask = info->mask;
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा hw_translate_funcs funcs = अणु
		.offset_to_id = offset_to_id,
		.id_to_offset = id_to_offset,
पूर्ण;

व्योम dal_hw_translate_dce60_init(
	काष्ठा hw_translate *translate)
अणु
	translate->funcs = &funcs;
पूर्ण
