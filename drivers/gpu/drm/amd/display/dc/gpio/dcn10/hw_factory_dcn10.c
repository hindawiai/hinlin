<शैली गुरु>
/*
 * Copyright 2013-15 Advanced Micro Devices, Inc.
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
#समावेश "include/gpio_types.h"
#समावेश "../hw_factory.h"


#समावेश "../hw_gpio.h"
#समावेश "../hw_ddc.h"
#समावेश "../hw_hpd.h"
#समावेश "../hw_generic.h"

#समावेश "hw_factory_dcn10.h"

#समावेश "dcn/dcn_1_0_offset.h"
#समावेश "dcn/dcn_1_0_sh_mask.h"
#समावेश "soc15_hw_ip.h"
#समावेश "vega10_ip_offset.h"

#घोषणा block HPD
#घोषणा reg_num 0

/* set field name */
#घोषणा SF_HPD(reg_name, field_name, post_fix)\
	.field_name = HPD0_ ## reg_name ## __ ## field_name ## post_fix

#घोषणा BASE_INNER(seg) \
	DCE_BASE__INST0_SEG ## seg

/* compile समय expand base address. */
#घोषणा BASE(seg) \
	BASE_INNER(seg)

#घोषणा REG(reg_name)\
		BASE(mm ## reg_name ## _BASE_IDX) + mm ## reg_name

#घोषणा REGI(reg_name, block, id)\
	BASE(mm ## block ## id ## _ ## reg_name ## _BASE_IDX) + \
				mm ## block ## id ## _ ## reg_name

#समावेश "reg_helper.h"
#समावेश "../hpd_regs.h"

#घोषणा hpd_regs(id) \
अणु\
	HPD_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा hpd_रेजिस्टरs hpd_regs[] = अणु
	hpd_regs(0),
	hpd_regs(1),
	hpd_regs(2),
	hpd_regs(3),
	hpd_regs(4),
	hpd_regs(5)
पूर्ण;

अटल स्थिर काष्ठा hpd_sh_mask hpd_shअगरt = अणु
		HPD_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा hpd_sh_mask hpd_mask = अणु
		HPD_MASK_SH_LIST(_MASK)
पूर्ण;

#समावेश "../ddc_regs.h"

 /* set field name */
#घोषणा SF_DDC(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

अटल स्थिर काष्ठा ddc_रेजिस्टरs ddc_data_regs[] = अणु
	ddc_data_regs(1),
	ddc_data_regs(2),
	ddc_data_regs(3),
	ddc_data_regs(4),
	ddc_data_regs(5),
	ddc_data_regs(6),
	ddc_vga_data_regs,
	ddc_i2c_data_regs
पूर्ण;

अटल स्थिर काष्ठा ddc_रेजिस्टरs ddc_clk_regs[] = अणु
	ddc_clk_regs(1),
	ddc_clk_regs(2),
	ddc_clk_regs(3),
	ddc_clk_regs(4),
	ddc_clk_regs(5),
	ddc_clk_regs(6),
	ddc_vga_clk_regs,
	ddc_i2c_clk_regs
पूर्ण;

अटल स्थिर काष्ठा ddc_sh_mask ddc_shअगरt = अणु
		DDC_MASK_SH_LIST(__SHIFT)
पूर्ण;

अटल स्थिर काष्ठा ddc_sh_mask ddc_mask = अणु
		DDC_MASK_SH_LIST(_MASK)
पूर्ण;

#समावेश "../generic_regs.h"

/* set field name */
#घोषणा SF_GENERIC(reg_name, field_name, post_fix)\
	.field_name = reg_name ## __ ## field_name ## post_fix

#घोषणा generic_regs(id) \
अणु\
	GENERIC_REG_LIST(id)\
पूर्ण

अटल स्थिर काष्ठा generic_रेजिस्टरs generic_regs[] = अणु
	generic_regs(A),
	generic_regs(B),
पूर्ण;

अटल स्थिर काष्ठा generic_sh_mask generic_shअगरt[] = अणु
	GENERIC_MASK_SH_LIST(__SHIFT, A),
	GENERIC_MASK_SH_LIST(__SHIFT, B),
पूर्ण;

अटल स्थिर काष्ठा generic_sh_mask generic_mask[] = अणु
	GENERIC_MASK_SH_LIST(_MASK, A),
	GENERIC_MASK_SH_LIST(_MASK, B),
पूर्ण;

अटल व्योम define_generic_रेजिस्टरs(काष्ठा hw_gpio_pin *pin, uपूर्णांक32_t en)
अणु
	काष्ठा hw_generic *generic = HW_GENERIC_FROM_BASE(pin);

	generic->regs = &generic_regs[en];
	generic->shअगरts = &generic_shअगरt[en];
	generic->masks = &generic_mask[en];
	generic->base.regs = &generic_regs[en].gpio;
पूर्ण

अटल व्योम define_ddc_रेजिस्टरs(
		काष्ठा hw_gpio_pin *pin,
		uपूर्णांक32_t en)
अणु
	काष्ठा hw_ddc *ddc = HW_DDC_FROM_BASE(pin);

	चयन (pin->id) अणु
	हाल GPIO_ID_DDC_DATA:
		ddc->regs = &ddc_data_regs[en];
		ddc->base.regs = &ddc_data_regs[en].gpio;
		अवरोध;
	हाल GPIO_ID_DDC_CLOCK:
		ddc->regs = &ddc_clk_regs[en];
		ddc->base.regs = &ddc_clk_regs[en].gpio;
		अवरोध;
	शेष:
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	ddc->shअगरts = &ddc_shअगरt;
	ddc->masks = &ddc_mask;

पूर्ण

अटल व्योम define_hpd_रेजिस्टरs(काष्ठा hw_gpio_pin *pin, uपूर्णांक32_t en)
अणु
	काष्ठा hw_hpd *hpd = HW_HPD_FROM_BASE(pin);

	hpd->regs = &hpd_regs[en];
	hpd->shअगरts = &hpd_shअगरt;
	hpd->masks = &hpd_mask;
	hpd->base.regs = &hpd_regs[en].gpio;
पूर्ण


/* function table */
अटल स्थिर काष्ठा hw_factory_funcs funcs = अणु
	.init_ddc_data = dal_hw_ddc_init,
	.init_generic = dal_hw_generic_init,
	.init_hpd = dal_hw_hpd_init,
	.get_ddc_pin = dal_hw_ddc_get_pin,
	.get_hpd_pin = dal_hw_hpd_get_pin,
	.get_generic_pin = dal_hw_generic_get_pin,
	.define_hpd_रेजिस्टरs = define_hpd_रेजिस्टरs,
	.define_ddc_रेजिस्टरs = define_ddc_रेजिस्टरs,
	.define_generic_रेजिस्टरs = define_generic_रेजिस्टरs
पूर्ण;
/*
 * dal_hw_factory_dcn10_init
 *
 * @brief
 * Initialize HW factory function poपूर्णांकers and pin info
 *
 * @param
 * काष्ठा hw_factory *factory - [out] काष्ठा of function poपूर्णांकers
 */
व्योम dal_hw_factory_dcn10_init(काष्ठा hw_factory *factory)
अणु
	/*TODO check ASIC CAPs*/
	factory->number_of_pins[GPIO_ID_DDC_DATA] = 8;
	factory->number_of_pins[GPIO_ID_DDC_CLOCK] = 8;
	factory->number_of_pins[GPIO_ID_GENERIC] = 7;
	factory->number_of_pins[GPIO_ID_HPD] = 6;
	factory->number_of_pins[GPIO_ID_GPIO_PAD] = 31;
	factory->number_of_pins[GPIO_ID_VIP_PAD] = 0;
	factory->number_of_pins[GPIO_ID_SYNC] = 2;
	factory->number_of_pins[GPIO_ID_GSL] = 4;

	factory->funcs = &funcs;
पूर्ण
