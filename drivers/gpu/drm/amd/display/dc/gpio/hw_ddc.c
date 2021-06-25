<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
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
#समावेश <linux/slab.h>

#समावेश "dm_services.h"

#समावेश "include/gpio_interface.h"
#समावेश "include/gpio_types.h"
#समावेश "hw_gpio.h"
#समावेश "hw_ddc.h"

#समावेश "reg_helper.h"
#समावेश "gpio_regs.h"


#अघोषित FN
#घोषणा FN(reg_name, field_name) \
	ddc->shअगरts->field_name, ddc->masks->field_name

#घोषणा CTX \
	ddc->base.base.ctx
#घोषणा REG(reg)\
	(ddc->regs->reg)

काष्ठा gpio;

अटल व्योम dal_hw_ddc_deकाष्ठा(
	काष्ठा hw_ddc *pin)
अणु
	dal_hw_gpio_deकाष्ठा(&pin->base);
पूर्ण

अटल व्योम dal_hw_ddc_destroy(
	काष्ठा hw_gpio_pin **ptr)
अणु
	काष्ठा hw_ddc *pin = HW_DDC_FROM_BASE(*ptr);

	dal_hw_ddc_deकाष्ठा(pin);

	kमुक्त(pin);

	*ptr = शून्य;
पूर्ण

अटल क्रमागत gpio_result set_config(
	काष्ठा hw_gpio_pin *ptr,
	स्थिर काष्ठा gpio_config_data *config_data)
अणु
	काष्ठा hw_ddc *ddc = HW_DDC_FROM_BASE(ptr);
	काष्ठा hw_gpio *hw_gpio = शून्य;
	uपूर्णांक32_t regval;
	uपूर्णांक32_t ddc_data_pd_en = 0;
	uपूर्णांक32_t ddc_clk_pd_en = 0;
	uपूर्णांक32_t aux_pad_mode = 0;

	hw_gpio = &ddc->base;

	अगर (hw_gpio == शून्य) अणु
		ASSERT_CRITICAL(false);
		वापस GPIO_RESULT_शून्य_HANDLE;
	पूर्ण

	regval = REG_GET_3(gpio.MASK_reg,
			DC_GPIO_DDC1DATA_PD_EN, &ddc_data_pd_en,
			DC_GPIO_DDC1CLK_PD_EN, &ddc_clk_pd_en,
			AUX_PAD1_MODE, &aux_pad_mode);

	चयन (config_data->config.ddc.type) अणु
	हाल GPIO_DDC_CONFIG_TYPE_MODE_I2C:
		/* On plug-in, there is a transient level on the pad
		 * which must be disअक्षरged through the पूर्णांकernal pull-करोwn.
		 * Enable पूर्णांकernal pull-करोwn, 2.5msec disअक्षरge समय
		 * is required क्रम detection of AUX mode */
		अगर (hw_gpio->base.en != GPIO_DDC_LINE_VIP_PAD) अणु
			अगर (!ddc_data_pd_en || !ddc_clk_pd_en) अणु

				REG_SET_2(gpio.MASK_reg, regval,
						DC_GPIO_DDC1DATA_PD_EN, 1,
						DC_GPIO_DDC1CLK_PD_EN, 1);

				अगर (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE)
					msleep(3);
			पूर्ण
		पूर्ण अन्यथा अणु
			uपूर्णांक32_t sda_pd_dis = 0;
			uपूर्णांक32_t scl_pd_dis = 0;

			REG_GET_2(gpio.MASK_reg,
				  DC_GPIO_SDA_PD_DIS, &sda_pd_dis,
				  DC_GPIO_SCL_PD_DIS, &scl_pd_dis);

			अगर (sda_pd_dis) अणु
				REG_SET(gpio.MASK_reg, regval,
						DC_GPIO_SDA_PD_DIS, 0);

				अगर (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE)
					msleep(3);
			पूर्ण

			अगर (!scl_pd_dis) अणु
				REG_SET(gpio.MASK_reg, regval,
						DC_GPIO_SCL_PD_DIS, 1);

				अगर (config_data->type ==
						GPIO_CONFIG_TYPE_I2C_AUX_DUAL_MODE)
					msleep(3);
			पूर्ण
		पूर्ण

		अगर (aux_pad_mode) अणु
			/* let pins to get de-निश्चितed
			 * beक्रमe setting pad to I2C mode */
			अगर (config_data->config.ddc.data_en_bit_present ||
				config_data->config.ddc.घड़ी_en_bit_present)
				/* [anaumov] in DAL2, there was
				 * dc_service_delay_in_microseconds(2000); */
				msleep(2);

			/* set the I2C pad mode */
			/* पढ़ो the रेजिस्टर again,
			 * some bits may have been changed */
			REG_UPDATE(gpio.MASK_reg,
					AUX_PAD1_MODE, 0);
		पूर्ण

		अगर (ddc->regs->dc_gpio_aux_ctrl_5 != 0) अणु
				REG_UPDATE(dc_gpio_aux_ctrl_5, DDC_PAD_I2CMODE, 1);
		पूर्ण
		//set  DC_IO_aux_rxsel = 2'b01
		अगर (ddc->regs->phy_aux_cntl != 0) अणु
				REG_UPDATE(phy_aux_cntl, AUX_PAD_RXSEL, 1);
		पूर्ण
		वापस GPIO_RESULT_OK;
	हाल GPIO_DDC_CONFIG_TYPE_MODE_AUX:
		/* set the AUX pad mode */
		अगर (!aux_pad_mode) अणु
			REG_SET(gpio.MASK_reg, regval,
					AUX_PAD1_MODE, 1);
		पूर्ण
		अगर (ddc->regs->dc_gpio_aux_ctrl_5 != 0) अणु
			REG_UPDATE(dc_gpio_aux_ctrl_5,
					DDC_PAD_I2CMODE, 0);
		पूर्ण

		वापस GPIO_RESULT_OK;
	हाल GPIO_DDC_CONFIG_TYPE_POLL_FOR_CONNECT:
		अगर ((hw_gpio->base.en >= GPIO_DDC_LINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_LINE_DDC_VGA)) अणु
			REG_UPDATE_3(ddc_setup,
				DC_I2C_DDC1_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_MODE, 0);
			वापस GPIO_RESULT_OK;
		पूर्ण
	अवरोध;
	हाल GPIO_DDC_CONFIG_TYPE_POLL_FOR_DISCONNECT:
		अगर ((hw_gpio->base.en >= GPIO_DDC_LINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_LINE_DDC_VGA)) अणु
			REG_UPDATE_3(ddc_setup,
				DC_I2C_DDC1_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_ENABLE, 1,
				DC_I2C_DDC1_EDID_DETECT_MODE, 1);
			वापस GPIO_RESULT_OK;
		पूर्ण
	अवरोध;
	हाल GPIO_DDC_CONFIG_TYPE_DISABLE_POLLING:
		अगर ((hw_gpio->base.en >= GPIO_DDC_LINE_DDC1) &&
			(hw_gpio->base.en <= GPIO_DDC_LINE_DDC_VGA)) अणु
			REG_UPDATE_2(ddc_setup,
				DC_I2C_DDC1_ENABLE, 0,
				DC_I2C_DDC1_EDID_DETECT_ENABLE, 0);
			वापस GPIO_RESULT_OK;
		पूर्ण
	अवरोध;
	पूर्ण

	BREAK_TO_DEBUGGER();

	वापस GPIO_RESULT_NON_SPECIFIC_ERROR;
पूर्ण

अटल स्थिर काष्ठा hw_gpio_pin_funcs funcs = अणु
	.destroy = dal_hw_ddc_destroy,
	.खोलो = dal_hw_gpio_खोलो,
	.get_value = dal_hw_gpio_get_value,
	.set_value = dal_hw_gpio_set_value,
	.set_config = set_config,
	.change_mode = dal_hw_gpio_change_mode,
	.बंद = dal_hw_gpio_बंद,
पूर्ण;

अटल व्योम dal_hw_ddc_स्थिरruct(
	काष्ठा hw_ddc *ddc,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en,
	काष्ठा dc_context *ctx)
अणु
	dal_hw_gpio_स्थिरruct(&ddc->base, id, en, ctx);
	ddc->base.base.funcs = &funcs;
पूर्ण

व्योम dal_hw_ddc_init(
	काष्ठा hw_ddc **hw_ddc,
	काष्ठा dc_context *ctx,
	क्रमागत gpio_id id,
	uपूर्णांक32_t en)
अणु
	अगर ((en < GPIO_DDC_LINE_MIN) || (en > GPIO_DDC_LINE_MAX)) अणु
		ASSERT_CRITICAL(false);
		*hw_ddc = शून्य;
	पूर्ण

	*hw_ddc = kzalloc(माप(काष्ठा hw_ddc), GFP_KERNEL);
	अगर (!*hw_ddc) अणु
		ASSERT_CRITICAL(false);
		वापस;
	पूर्ण

	dal_hw_ddc_स्थिरruct(*hw_ddc, id, en, ctx);
पूर्ण

काष्ठा hw_gpio_pin *dal_hw_ddc_get_pin(काष्ठा gpio *gpio)
अणु
	काष्ठा hw_ddc *hw_ddc = dal_gpio_get_ddc(gpio);

	वापस &hw_ddc->base.base;
पूर्ण
