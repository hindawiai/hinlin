<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI/National Semiconductor LP3943 MFD Core Driver
 *
 * Copyright 2013 Texas Instruments
 *
 * Author: Milo Kim <milo.kim@ti.com>
 *
 * Driver काष्ठाure:
 *   LP3943 is an पूर्णांकegrated device capable of driving 16 output channels.
 *   It can be used क्रम a GPIO expander and PWM generators.
 *
 *                                   LED control    General usage क्रम a device
 *                                   ___________   ____________________________
 *
 *   LP3943 MFD ---- GPIO expander    leds-gpio        eg) HW enable pin
 *               |
 *               --- PWM generator    leds-pwm         eg) PWM input
 *
 *   Internal two PWM channels are used क्रम LED dimming effect.
 *   And each output pin can be used as a GPIO as well.
 *   The LED functionality can work with GPIOs or PWMs.
 *   LEDs can be controlled with legacy leds-gpio(अटल brightness) or
 *   leds-pwm drivers(dynamic brightness control).
 *   Alternatively, it can be used क्रम generic GPIO and PWM controller.
 *   For example, a GPIO is HW enable pin of a device.
 *   A PWM is input pin of a backlight device.
 */

#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/lp3943.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#घोषणा LP3943_MAX_REGISTERS		0x09

/* Register configuration क्रम pin MUX */
अटल स्थिर काष्ठा lp3943_reg_cfg lp3943_mux_cfg[] = अणु
	/* address, mask, shअगरt */
	अणु LP3943_REG_MUX0, 0x03, 0 पूर्ण,
	अणु LP3943_REG_MUX0, 0x0C, 2 पूर्ण,
	अणु LP3943_REG_MUX0, 0x30, 4 पूर्ण,
	अणु LP3943_REG_MUX0, 0xC0, 6 पूर्ण,
	अणु LP3943_REG_MUX1, 0x03, 0 पूर्ण,
	अणु LP3943_REG_MUX1, 0x0C, 2 पूर्ण,
	अणु LP3943_REG_MUX1, 0x30, 4 पूर्ण,
	अणु LP3943_REG_MUX1, 0xC0, 6 पूर्ण,
	अणु LP3943_REG_MUX2, 0x03, 0 पूर्ण,
	अणु LP3943_REG_MUX2, 0x0C, 2 पूर्ण,
	अणु LP3943_REG_MUX2, 0x30, 4 पूर्ण,
	अणु LP3943_REG_MUX2, 0xC0, 6 पूर्ण,
	अणु LP3943_REG_MUX3, 0x03, 0 पूर्ण,
	अणु LP3943_REG_MUX3, 0x0C, 2 पूर्ण,
	अणु LP3943_REG_MUX3, 0x30, 4 पूर्ण,
	अणु LP3943_REG_MUX3, 0xC0, 6 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lp3943_devs[] = अणु
	अणु
		.name = "lp3943-pwm",
		.of_compatible = "ti,lp3943-pwm",
	पूर्ण,
	अणु
		.name = "lp3943-gpio",
		.of_compatible = "ti,lp3943-gpio",
	पूर्ण,
पूर्ण;

पूर्णांक lp3943_पढ़ो_byte(काष्ठा lp3943 *lp3943, u8 reg, u8 *पढ़ो)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(lp3943->regmap, reg, &val);
	अगर (ret < 0)
		वापस ret;

	*पढ़ो = (u8)val;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lp3943_पढ़ो_byte);

पूर्णांक lp3943_ग_लिखो_byte(काष्ठा lp3943 *lp3943, u8 reg, u8 data)
अणु
	वापस regmap_ग_लिखो(lp3943->regmap, reg, data);
पूर्ण
EXPORT_SYMBOL_GPL(lp3943_ग_लिखो_byte);

पूर्णांक lp3943_update_bits(काष्ठा lp3943 *lp3943, u8 reg, u8 mask, u8 data)
अणु
	वापस regmap_update_bits(lp3943->regmap, reg, mask, data);
पूर्ण
EXPORT_SYMBOL_GPL(lp3943_update_bits);

अटल स्थिर काष्ठा regmap_config lp3943_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = LP3943_MAX_REGISTERS,
पूर्ण;

अटल पूर्णांक lp3943_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lp3943 *lp3943;
	काष्ठा device *dev = &cl->dev;

	lp3943 = devm_kzalloc(dev, माप(*lp3943), GFP_KERNEL);
	अगर (!lp3943)
		वापस -ENOMEM;

	lp3943->regmap = devm_regmap_init_i2c(cl, &lp3943_regmap_config);
	अगर (IS_ERR(lp3943->regmap))
		वापस PTR_ERR(lp3943->regmap);

	lp3943->pdata = dev_get_platdata(dev);
	lp3943->dev = dev;
	lp3943->mux_cfg = lp3943_mux_cfg;
	i2c_set_clientdata(cl, lp3943);

	वापस devm_mfd_add_devices(dev, -1, lp3943_devs,
				    ARRAY_SIZE(lp3943_devs),
				    शून्य, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp3943_ids[] = अणु
	अणु "lp3943", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp3943_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lp3943_of_match[] = अणु
	अणु .compatible = "ti,lp3943", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lp3943_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver lp3943_driver = अणु
	.probe = lp3943_probe,
	.driver = अणु
		.name = "lp3943",
		.of_match_table = of_match_ptr(lp3943_of_match),
	पूर्ण,
	.id_table = lp3943_ids,
पूर्ण;

module_i2c_driver(lp3943_driver);

MODULE_DESCRIPTION("LP3943 MFD Core Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
