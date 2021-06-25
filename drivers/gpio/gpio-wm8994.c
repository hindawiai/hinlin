<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * gpiolib support क्रम Wolfson WM8994
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/wm8994/core.h>
#समावेश <linux/mfd/wm8994/pdata.h>
#समावेश <linux/mfd/wm8994/gpपन.स>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>

काष्ठा wm8994_gpio अणु
	काष्ठा wm8994 *wm8994;
	काष्ठा gpio_chip gpio_chip;
पूर्ण;

अटल पूर्णांक wm8994_gpio_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;

	चयन (wm8994->type) अणु
	हाल WM8958:
		चयन (offset) अणु
		हाल 1:
		हाल 2:
		हाल 3:
		हाल 4:
		हाल 6:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8994_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;

	वापस wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
			       WM8994_GPN_सूची, WM8994_GPN_सूची);
पूर्ण

अटल पूर्णांक wm8994_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;
	पूर्णांक ret;

	ret = wm8994_reg_पढ़ो(wm8994, WM8994_GPIO_1 + offset);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & WM8994_GPN_LVL)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक wm8994_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;

	अगर (value)
		value = WM8994_GPN_LVL;

	वापस wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
			       WM8994_GPN_सूची | WM8994_GPN_LVL, value);
पूर्ण

अटल व्योम wm8994_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;

	अगर (value)
		value = WM8994_GPN_LVL;

	wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset, WM8994_GPN_LVL, value);
पूर्ण

अटल पूर्णांक wm8994_gpio_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
				  अचिन्हित दीर्घ config)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
				       WM8994_GPN_OP_CFG_MASK,
				       WM8994_GPN_OP_CFG);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
				       WM8994_GPN_OP_CFG_MASK, 0);
	शेष:
		अवरोध;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक wm8994_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;

	वापस regmap_irq_get_virq(wm8994->irq_data, offset);
पूर्ण


#अगर_घोषित CONFIG_DEBUG_FS
अटल स्थिर अक्षर *wm8994_gpio_fn(u16 fn)
अणु
	चयन (fn) अणु
	हाल WM8994_GP_FN_PIN_SPECIFIC:
		वापस "pin-specific";
	हाल WM8994_GP_FN_GPIO:
		वापस "GPIO";
	हाल WM8994_GP_FN_SDOUT:
		वापस "SDOUT";
	हाल WM8994_GP_FN_IRQ:
		वापस "IRQ";
	हाल WM8994_GP_FN_TEMPERATURE:
		वापस "Temperature";
	हाल WM8994_GP_FN_MICBIAS1_DET:
		वापस "MICBIAS1 detect";
	हाल WM8994_GP_FN_MICBIAS1_SHORT:
		वापस "MICBIAS1 short";
	हाल WM8994_GP_FN_MICBIAS2_DET:
		वापस "MICBIAS2 detect";
	हाल WM8994_GP_FN_MICBIAS2_SHORT:
		वापस "MICBIAS2 short";
	हाल WM8994_GP_FN_FLL1_LOCK:
		वापस "FLL1 lock";
	हाल WM8994_GP_FN_FLL2_LOCK:
		वापस "FLL2 lock";
	हाल WM8994_GP_FN_SRC1_LOCK:
		वापस "SRC1 lock";
	हाल WM8994_GP_FN_SRC2_LOCK:
		वापस "SRC2 lock";
	हाल WM8994_GP_FN_DRC1_ACT:
		वापस "DRC1 activity";
	हाल WM8994_GP_FN_DRC2_ACT:
		वापस "DRC2 activity";
	हाल WM8994_GP_FN_DRC3_ACT:
		वापस "DRC3 activity";
	हाल WM8994_GP_FN_WSEQ_STATUS:
		वापस "Write sequencer";
	हाल WM8994_GP_FN_FIFO_ERROR:
		वापस "FIFO error";
	हाल WM8994_GP_FN_OPCLK:
		वापस "OPCLK";
	हाल WM8994_GP_FN_THW:
		वापस "Thermal warning";
	हाल WM8994_GP_FN_DCS_DONE:
		वापस "DC servo";
	हाल WM8994_GP_FN_FLL1_OUT:
		वापस "FLL1 output";
	हाल WM8994_GP_FN_FLL2_OUT:
		वापस "FLL1 output";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल व्योम wm8994_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	काष्ठा wm8994 *wm8994 = wm8994_gpio->wm8994;
	पूर्णांक i;

	क्रम (i = 0; i < chip->ngpio; i++) अणु
		पूर्णांक gpio = i + chip->base;
		पूर्णांक reg;
		स्थिर अक्षर *label;

		/* We report the GPIO even अगर it's not requested since
		 * we're also reporting things like alternate
		 * functions which apply even when the GPIO is not in
		 * use as a GPIO.
		 */
		label = gpiochip_is_requested(chip, i);
		अगर (!label)
			label = "Unrequested";

		seq_म_लिखो(s, " gpio-%-3d (%-20.20s) ", gpio, label);

		reg = wm8994_reg_पढ़ो(wm8994, WM8994_GPIO_1 + i);
		अगर (reg < 0) अणु
			dev_err(wm8994->dev,
				"GPIO control %d read failed: %d\n",
				gpio, reg);
			seq_म_लिखो(s, "\n");
			जारी;
		पूर्ण

		अगर (reg & WM8994_GPN_सूची)
			seq_म_लिखो(s, "in ");
		अन्यथा
			seq_म_लिखो(s, "out ");

		अगर (reg & WM8994_GPN_PU)
			seq_म_लिखो(s, "pull up ");

		अगर (reg & WM8994_GPN_PD)
			seq_म_लिखो(s, "pull down ");

		अगर (reg & WM8994_GPN_POL)
			seq_म_लिखो(s, "inverted ");
		अन्यथा
			seq_म_लिखो(s, "noninverted ");

		अगर (reg & WM8994_GPN_OP_CFG)
			seq_म_लिखो(s, "open drain ");
		अन्यथा
			seq_म_लिखो(s, "push-pull ");

		seq_म_लिखो(s, "%s (%x)\n",
			   wm8994_gpio_fn(reg & WM8994_GPN_FN_MASK), reg);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा wm8994_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "wm8994",
	.owner			= THIS_MODULE,
	.request		= wm8994_gpio_request,
	.direction_input	= wm8994_gpio_direction_in,
	.get			= wm8994_gpio_get,
	.direction_output	= wm8994_gpio_direction_out,
	.set			= wm8994_gpio_set,
	.set_config		= wm8994_gpio_set_config,
	.to_irq			= wm8994_gpio_to_irq,
	.dbg_show		= wm8994_gpio_dbg_show,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक wm8994_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8994 *wm8994 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm8994_pdata *pdata = dev_get_platdata(wm8994->dev);
	काष्ठा wm8994_gpio *wm8994_gpio;
	पूर्णांक ret;

	wm8994_gpio = devm_kzalloc(&pdev->dev, माप(*wm8994_gpio),
				   GFP_KERNEL);
	अगर (wm8994_gpio == शून्य)
		वापस -ENOMEM;

	wm8994_gpio->wm8994 = wm8994;
	wm8994_gpio->gpio_chip = ढाँचा_chip;
	wm8994_gpio->gpio_chip.ngpio = WM8994_GPIO_MAX;
	wm8994_gpio->gpio_chip.parent = &pdev->dev;
	अगर (pdata && pdata->gpio_base)
		wm8994_gpio->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		wm8994_gpio->gpio_chip.base = -1;

	ret = devm_gpiochip_add_data(&pdev->dev, &wm8994_gpio->gpio_chip,
				     wm8994_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n",
			ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, wm8994_gpio);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8994_gpio_driver = अणु
	.driver.name	= "wm8994-gpio",
	.probe		= wm8994_gpio_probe,
पूर्ण;

अटल पूर्णांक __init wm8994_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&wm8994_gpio_driver);
पूर्ण
subsys_initcall(wm8994_gpio_init);

अटल व्योम __निकास wm8994_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wm8994_gpio_driver);
पूर्ण
module_निकास(wm8994_gpio_निकास);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("GPIO interface for WM8994");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8994-gpio");
