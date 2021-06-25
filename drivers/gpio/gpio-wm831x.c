<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * gpiolib support क्रम Wolfson WM831x PMICs
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

#समावेश <linux/mfd/wm831x/core.h>
#समावेश <linux/mfd/wm831x/pdata.h>
#समावेश <linux/mfd/wm831x/gpपन.स>
#समावेश <linux/mfd/wm831x/irq.h>

काष्ठा wm831x_gpio अणु
	काष्ठा wm831x *wm831x;
	काष्ठा gpio_chip gpio_chip;
पूर्ण;

अटल पूर्णांक wm831x_gpio_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	काष्ठा wm831x *wm831x = wm831x_gpio->wm831x;
	पूर्णांक val = WM831X_GPN_सूची;

	अगर (wm831x->has_gpio_ena)
		val |= WM831X_GPN_TRI;

	वापस wm831x_set_bits(wm831x, WM831X_GPIO1_CONTROL + offset,
			       WM831X_GPN_सूची | WM831X_GPN_TRI |
			       WM831X_GPN_FN_MASK, val);
पूर्ण

अटल पूर्णांक wm831x_gpio_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	काष्ठा wm831x *wm831x = wm831x_gpio->wm831x;
	पूर्णांक ret;

	ret = wm831x_reg_पढ़ो(wm831x, WM831X_GPIO_LEVEL);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & 1 << offset)
		वापस 1;
	अन्यथा
		वापस 0;
पूर्ण

अटल व्योम wm831x_gpio_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	काष्ठा wm831x *wm831x = wm831x_gpio->wm831x;

	wm831x_set_bits(wm831x, WM831X_GPIO_LEVEL, 1 << offset,
			value << offset);
पूर्ण

अटल पूर्णांक wm831x_gpio_direction_out(काष्ठा gpio_chip *chip,
				     अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	काष्ठा wm831x *wm831x = wm831x_gpio->wm831x;
	पूर्णांक val = 0;
	पूर्णांक ret;

	अगर (wm831x->has_gpio_ena)
		val |= WM831X_GPN_TRI;

	ret = wm831x_set_bits(wm831x, WM831X_GPIO1_CONTROL + offset,
			      WM831X_GPN_सूची | WM831X_GPN_TRI |
			      WM831X_GPN_FN_MASK, val);
	अगर (ret < 0)
		वापस ret;

	/* Can only set GPIO state once it's in output mode */
	wm831x_gpio_set(chip, offset, value);

	वापस 0;
पूर्ण

अटल पूर्णांक wm831x_gpio_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	काष्ठा wm831x *wm831x = wm831x_gpio->wm831x;

	वापस irq_create_mapping(wm831x->irq_करोमुख्य,
				  WM831X_IRQ_GPIO_1 + offset);
पूर्ण

अटल पूर्णांक wm831x_gpio_set_debounce(काष्ठा wm831x *wm831x, अचिन्हित offset,
				    अचिन्हित debounce)
अणु
	पूर्णांक reg = WM831X_GPIO1_CONTROL + offset;
	पूर्णांक ret, fn;

	ret = wm831x_reg_पढ़ो(wm831x, reg);
	अगर (ret < 0)
		वापस ret;

	चयन (ret & WM831X_GPN_FN_MASK) अणु
	हाल 0:
	हाल 1:
		अवरोध;
	शेष:
		/* Not in GPIO mode */
		वापस -EBUSY;
	पूर्ण

	अगर (debounce >= 32 && debounce <= 64)
		fn = 0;
	अन्यथा अगर (debounce >= 4000 && debounce <= 8000)
		fn = 1;
	अन्यथा
		वापस -EINVAL;

	वापस wm831x_set_bits(wm831x, reg, WM831X_GPN_FN_MASK, fn);
पूर्ण

अटल पूर्णांक wm831x_set_config(काष्ठा gpio_chip *chip, अचिन्हित पूर्णांक offset,
			     अचिन्हित दीर्घ config)
अणु
	काष्ठा wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	काष्ठा wm831x *wm831x = wm831x_gpio->wm831x;
	पूर्णांक reg = WM831X_GPIO1_CONTROL + offset;

	चयन (pinconf_to_config_param(config)) अणु
	हाल PIN_CONFIG_DRIVE_OPEN_DRAIN:
		वापस wm831x_set_bits(wm831x, reg,
				       WM831X_GPN_OD_MASK, WM831X_GPN_OD);
	हाल PIN_CONFIG_DRIVE_PUSH_PULL:
		वापस wm831x_set_bits(wm831x, reg,
				       WM831X_GPN_OD_MASK, 0);
	हाल PIN_CONFIG_INPUT_DEBOUNCE:
		वापस wm831x_gpio_set_debounce(wm831x, offset,
			pinconf_to_config_argument(config));
	शेष:
		अवरोध;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
अटल व्योम wm831x_gpio_dbg_show(काष्ठा seq_file *s, काष्ठा gpio_chip *chip)
अणु
	काष्ठा wm831x_gpio *wm831x_gpio = gpiochip_get_data(chip);
	काष्ठा wm831x *wm831x = wm831x_gpio->wm831x;
	पूर्णांक i, tristated;

	क्रम (i = 0; i < chip->ngpio; i++) अणु
		पूर्णांक gpio = i + chip->base;
		पूर्णांक reg;
		स्थिर अक्षर *label, *pull, *घातerकरोमुख्य;

		/* We report the GPIO even अगर it's not requested since
		 * we're also reporting things like alternate
		 * functions which apply even when the GPIO is not in
		 * use as a GPIO.
		 */
		label = gpiochip_is_requested(chip, i);
		अगर (!label)
			label = "Unrequested";

		seq_म_लिखो(s, " gpio-%-3d (%-20.20s) ", gpio, label);

		reg = wm831x_reg_पढ़ो(wm831x, WM831X_GPIO1_CONTROL + i);
		अगर (reg < 0) अणु
			dev_err(wm831x->dev,
				"GPIO control %d read failed: %d\n",
				gpio, reg);
			seq_अ_दो(s, '\n');
			जारी;
		पूर्ण

		चयन (reg & WM831X_GPN_PULL_MASK) अणु
		हाल WM831X_GPIO_PULL_NONE:
			pull = "nopull";
			अवरोध;
		हाल WM831X_GPIO_PULL_DOWN:
			pull = "pulldown";
			अवरोध;
		हाल WM831X_GPIO_PULL_UP:
			pull = "pullup";
			अवरोध;
		शेष:
			pull = "INVALID PULL";
			अवरोध;
		पूर्ण

		चयन (i + 1) अणु
		हाल 1 ... 3:
		हाल 7 ... 9:
			अगर (reg & WM831X_GPN_PWR_DOM)
				घातerकरोमुख्य = "VPMIC";
			अन्यथा
				घातerकरोमुख्य = "DBVDD";
			अवरोध;

		हाल 4 ... 6:
		हाल 10 ... 12:
			अगर (reg & WM831X_GPN_PWR_DOM)
				घातerकरोमुख्य = "SYSVDD";
			अन्यथा
				घातerकरोमुख्य = "DBVDD";
			अवरोध;

		हाल 13 ... 16:
			घातerकरोमुख्य = "TPVDD";
			अवरोध;

		शेष:
			BUG();
			अवरोध;
		पूर्ण

		tristated = reg & WM831X_GPN_TRI;
		अगर (wm831x->has_gpio_ena)
			tristated = !tristated;

		seq_म_लिखो(s, " %s %s %s %s%s\n"
			   "                                  %s%s (0x%4x)\n",
			   reg & WM831X_GPN_सूची ? "in" : "out",
			   wm831x_gpio_get(chip, i) ? "high" : "low",
			   pull,
			   घातerकरोमुख्य,
			   reg & WM831X_GPN_POL ? "" : " inverted",
			   reg & WM831X_GPN_OD ? "open-drain" : "push-pull",
			   tristated ? " tristated" : "",
			   reg);
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा wm831x_gpio_dbg_show शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "wm831x",
	.owner			= THIS_MODULE,
	.direction_input	= wm831x_gpio_direction_in,
	.get			= wm831x_gpio_get,
	.direction_output	= wm831x_gpio_direction_out,
	.set			= wm831x_gpio_set,
	.to_irq			= wm831x_gpio_to_irq,
	.set_config		= wm831x_set_config,
	.dbg_show		= wm831x_gpio_dbg_show,
	.can_sleep		= true,
पूर्ण;

अटल पूर्णांक wm831x_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm831x *wm831x = dev_get_drvdata(pdev->dev.parent);
	काष्ठा wm831x_pdata *pdata = &wm831x->pdata;
	काष्ठा wm831x_gpio *wm831x_gpio;
	पूर्णांक ret;

	wm831x_gpio = devm_kzalloc(&pdev->dev, माप(*wm831x_gpio),
				   GFP_KERNEL);
	अगर (wm831x_gpio == शून्य)
		वापस -ENOMEM;

	wm831x_gpio->wm831x = wm831x;
	wm831x_gpio->gpio_chip = ढाँचा_chip;
	wm831x_gpio->gpio_chip.ngpio = wm831x->num_gpio;
	wm831x_gpio->gpio_chip.parent = &pdev->dev;
	अगर (pdata && pdata->gpio_base)
		wm831x_gpio->gpio_chip.base = pdata->gpio_base;
	अन्यथा
		wm831x_gpio->gpio_chip.base = -1;
#अगर_घोषित CONFIG_OF_GPIO
	wm831x_gpio->gpio_chip.of_node = wm831x->dev->of_node;
#पूर्ण_अगर

	ret = devm_gpiochip_add_data(&pdev->dev, &wm831x_gpio->gpio_chip,
				     wm831x_gpio);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Could not register gpiochip, %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, wm831x_gpio);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm831x_gpio_driver = अणु
	.driver.name	= "wm831x-gpio",
	.probe		= wm831x_gpio_probe,
पूर्ण;

अटल पूर्णांक __init wm831x_gpio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&wm831x_gpio_driver);
पूर्ण
subsys_initcall(wm831x_gpio_init);

अटल व्योम __निकास wm831x_gpio_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&wm831x_gpio_driver);
पूर्ण
module_निकास(wm831x_gpio_निकास);

MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_DESCRIPTION("GPIO interface for WM831x PMICs");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm831x-gpio");
