<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Access to GPIOs on TWL4030/TPS659x0 chips
 *
 * Copyright (C) 2006-2007 Texas Instruments, Inc.
 * Copyright (C) 2006 MontaVista Software, Inc.
 *
 * Code re-arranged and cleaned up by:
 *	Syed Mohammed Khasim <x0khasim@ti.com>
 *
 * Initial Code:
 *	Andy Lowe / Nishanth Menon
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/irqकरोमुख्य.h>

#समावेश <linux/mfd/twl.h>

/*
 * The GPIO "subchip" supports 18 GPIOs which can be configured as
 * inमाला_दो or outमाला_दो, with pullups or pullकरोwns on each pin.  Each
 * GPIO can trigger पूर्णांकerrupts on either or both edges.
 *
 * GPIO पूर्णांकerrupts can be fed to either of two IRQ lines; this is
 * पूर्णांकended to support multiple hosts.
 *
 * There are also two LED pins used someबार as output-only GPIOs.
 */

/* genirq पूर्णांकerfaces are not available to modules */
#अगर_घोषित MODULE
#घोषणा is_module()	true
#अन्यथा
#घोषणा is_module()	false
#पूर्ण_अगर

/* GPIO_CTRL Fields */
#घोषणा MASK_GPIO_CTRL_GPIO0CD1		BIT(0)
#घोषणा MASK_GPIO_CTRL_GPIO1CD2		BIT(1)
#घोषणा MASK_GPIO_CTRL_GPIO_ON		BIT(2)

/* Mask क्रम GPIO रेजिस्टरs when aggregated पूर्णांकo a 32-bit पूर्णांकeger */
#घोषणा GPIO_32_MASK			0x0003ffff

काष्ठा gpio_twl4030_priv अणु
	काष्ठा gpio_chip gpio_chip;
	काष्ठा mutex mutex;
	पूर्णांक irq_base;

	/* Bitfields क्रम state caching */
	अचिन्हित पूर्णांक usage_count;
	अचिन्हित पूर्णांक direction;
	अचिन्हित पूर्णांक out_state;
पूर्ण;

/*----------------------------------------------------------------------*/

/*
 * To configure TWL4030 GPIO module रेजिस्टरs
 */
अटल अंतरभूत पूर्णांक gpio_twl4030_ग_लिखो(u8 address, u8 data)
अणु
	वापस twl_i2c_ग_लिखो_u8(TWL4030_MODULE_GPIO, data, address);
पूर्ण

/*----------------------------------------------------------------------*/

/*
 * LED रेजिस्टर offsets from TWL_MODULE_LED base
 * PWMs A and B are dedicated to LEDs A and B, respectively.
 */

#घोषणा TWL4030_LED_LEDEN_REG	0x00
#घोषणा TWL4030_PWMAON_REG	0x01
#घोषणा TWL4030_PWMAOFF_REG	0x02
#घोषणा TWL4030_PWMBON_REG	0x03
#घोषणा TWL4030_PWMBOFF_REG	0x04

/* LEDEN bits */
#घोषणा LEDEN_LEDAON		BIT(0)
#घोषणा LEDEN_LEDBON		BIT(1)
#घोषणा LEDEN_LEDAEXT		BIT(2)
#घोषणा LEDEN_LEDBEXT		BIT(3)
#घोषणा LEDEN_LEDAPWM		BIT(4)
#घोषणा LEDEN_LEDBPWM		BIT(5)
#घोषणा LEDEN_PWM_LENGTHA	BIT(6)
#घोषणा LEDEN_PWM_LENGTHB	BIT(7)

#घोषणा PWMxON_LENGTH		BIT(7)

/*----------------------------------------------------------------------*/

/*
 * To पढ़ो a TWL4030 GPIO module रेजिस्टर
 */
अटल अंतरभूत पूर्णांक gpio_twl4030_पढ़ो(u8 address)
अणु
	u8 data;
	पूर्णांक ret = 0;

	ret = twl_i2c_पढ़ो_u8(TWL4030_MODULE_GPIO, &data, address);
	वापस (ret < 0) ? ret : data;
पूर्ण

/*----------------------------------------------------------------------*/

अटल u8 cached_leden;

/* The LED lines are खोलो drain outमाला_दो ... a FET pulls to GND, so an
 * बाह्यal pullup is needed.  We could also expose the पूर्णांकegrated PWM
 * as a LED brightness control; we initialize it as "always on".
 */
अटल व्योम twl4030_led_set_value(पूर्णांक led, पूर्णांक value)
अणु
	u8 mask = LEDEN_LEDAON | LEDEN_LEDAPWM;

	अगर (led)
		mask <<= 1;

	अगर (value)
		cached_leden &= ~mask;
	अन्यथा
		cached_leden |= mask;

	WARN_ON_ONCE(twl_i2c_ग_लिखो_u8(TWL4030_MODULE_LED, cached_leden,
				      TWL4030_LED_LEDEN_REG));
पूर्ण

अटल पूर्णांक twl4030_set_gpio_direction(पूर्णांक gpio, पूर्णांक is_input)
अणु
	u8 d_bnk = gpio >> 3;
	u8 d_msk = BIT(gpio & 0x7);
	u8 reg = 0;
	u8 base = REG_GPIODATAसूची1 + d_bnk;
	पूर्णांक ret = 0;

	ret = gpio_twl4030_पढ़ो(base);
	अगर (ret >= 0) अणु
		अगर (is_input)
			reg = ret & ~d_msk;
		अन्यथा
			reg = ret | d_msk;

		ret = gpio_twl4030_ग_लिखो(base, reg);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक twl4030_get_gpio_direction(पूर्णांक gpio)
अणु
	u8 d_bnk = gpio >> 3;
	u8 d_msk = BIT(gpio & 0x7);
	u8 base = REG_GPIODATAसूची1 + d_bnk;
	पूर्णांक ret = 0;

	ret = gpio_twl4030_पढ़ो(base);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & d_msk)
		वापस GPIO_LINE_सूचीECTION_OUT;

	वापस GPIO_LINE_सूचीECTION_IN;
पूर्ण

अटल पूर्णांक twl4030_set_gpio_dataout(पूर्णांक gpio, पूर्णांक enable)
अणु
	u8 d_bnk = gpio >> 3;
	u8 d_msk = BIT(gpio & 0x7);
	u8 base = 0;

	अगर (enable)
		base = REG_SETGPIODATAOUT1 + d_bnk;
	अन्यथा
		base = REG_CLEARGPIODATAOUT1 + d_bnk;

	वापस gpio_twl4030_ग_लिखो(base, d_msk);
पूर्ण

अटल पूर्णांक twl4030_get_gpio_datain(पूर्णांक gpio)
अणु
	u8 d_bnk = gpio >> 3;
	u8 d_off = gpio & 0x7;
	u8 base = 0;
	पूर्णांक ret = 0;

	base = REG_GPIODATAIN1 + d_bnk;
	ret = gpio_twl4030_पढ़ो(base);
	अगर (ret > 0)
		ret = (ret >> d_off) & 0x1;

	वापस ret;
पूर्ण

/*----------------------------------------------------------------------*/

अटल पूर्णांक twl_request(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);
	पूर्णांक status = 0;

	mutex_lock(&priv->mutex);

	/* Support the two LED outमाला_दो as output-only GPIOs. */
	अगर (offset >= TWL4030_GPIO_MAX) अणु
		u8	ledclr_mask = LEDEN_LEDAON | LEDEN_LEDAEXT
				| LEDEN_LEDAPWM | LEDEN_PWM_LENGTHA;
		u8	reg = TWL4030_PWMAON_REG;

		offset -= TWL4030_GPIO_MAX;
		अगर (offset) अणु
			ledclr_mask <<= 1;
			reg = TWL4030_PWMBON_REG;
		पूर्ण

		/* initialize PWM to always-drive */
		/* Configure PWM OFF रेजिस्टर first */
		status = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_LED, 0x7f, reg + 1);
		अगर (status < 0)
			जाओ करोne;

		/* Followed by PWM ON रेजिस्टर */
		status = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_LED, 0x7f, reg);
		अगर (status < 0)
			जाओ करोne;

		/* init LED to not-driven (high) */
		status = twl_i2c_पढ़ो_u8(TWL4030_MODULE_LED, &cached_leden,
					 TWL4030_LED_LEDEN_REG);
		अगर (status < 0)
			जाओ करोne;
		cached_leden &= ~ledclr_mask;
		status = twl_i2c_ग_लिखो_u8(TWL4030_MODULE_LED, cached_leden,
					  TWL4030_LED_LEDEN_REG);
		अगर (status < 0)
			जाओ करोne;

		status = 0;
		जाओ करोne;
	पूर्ण

	/* on first use, turn GPIO module "on" */
	अगर (!priv->usage_count) अणु
		काष्ठा twl4030_gpio_platक्रमm_data *pdata;
		u8 value = MASK_GPIO_CTRL_GPIO_ON;

		/* optionally have the first two GPIOs चयन vMMC1
		 * and vMMC2 घातer supplies based on card presence.
		 */
		pdata = dev_get_platdata(chip->parent);
		अगर (pdata)
			value |= pdata->mmc_cd & 0x03;

		status = gpio_twl4030_ग_लिखो(REG_GPIO_CTRL, value);
	पूर्ण

करोne:
	अगर (!status)
		priv->usage_count |= BIT(offset);

	mutex_unlock(&priv->mutex);
	वापस status;
पूर्ण

अटल व्योम twl_मुक्त(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);

	mutex_lock(&priv->mutex);
	अगर (offset >= TWL4030_GPIO_MAX) अणु
		twl4030_led_set_value(offset - TWL4030_GPIO_MAX, 1);
		जाओ out;
	पूर्ण

	priv->usage_count &= ~BIT(offset);

	/* on last use, चयन off GPIO module */
	अगर (!priv->usage_count)
		gpio_twl4030_ग_लिखो(REG_GPIO_CTRL, 0x0);

out:
	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक twl_direction_in(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);
	पूर्णांक ret;

	mutex_lock(&priv->mutex);
	अगर (offset < TWL4030_GPIO_MAX)
		ret = twl4030_set_gpio_direction(offset, 1);
	अन्यथा
		ret = -EINVAL;	/* LED outमाला_दो can't be set as input */

	अगर (!ret)
		priv->direction &= ~BIT(offset);

	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक twl_get(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);
	पूर्णांक ret;
	पूर्णांक status = 0;

	mutex_lock(&priv->mutex);
	अगर (!(priv->usage_count & BIT(offset))) अणु
		ret = -EPERM;
		जाओ out;
	पूर्ण

	अगर (priv->direction & BIT(offset))
		status = priv->out_state & BIT(offset);
	अन्यथा
		status = twl4030_get_gpio_datain(offset);

	ret = (status < 0) ? status : !!status;
out:
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

अटल व्योम twl_set(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);

	mutex_lock(&priv->mutex);
	अगर (offset < TWL4030_GPIO_MAX)
		twl4030_set_gpio_dataout(offset, value);
	अन्यथा
		twl4030_led_set_value(offset - TWL4030_GPIO_MAX, value);

	अगर (value)
		priv->out_state |= BIT(offset);
	अन्यथा
		priv->out_state &= ~BIT(offset);

	mutex_unlock(&priv->mutex);
पूर्ण

अटल पूर्णांक twl_direction_out(काष्ठा gpio_chip *chip, अचिन्हित offset, पूर्णांक value)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);
	पूर्णांक ret = 0;

	mutex_lock(&priv->mutex);
	अगर (offset < TWL4030_GPIO_MAX) अणु
		ret = twl4030_set_gpio_direction(offset, 0);
		अगर (ret) अणु
			mutex_unlock(&priv->mutex);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 *  LED gpios i.e. offset >= TWL4030_GPIO_MAX are always output
	 */

	priv->direction |= BIT(offset);
	mutex_unlock(&priv->mutex);

	twl_set(chip, offset, value);

	वापस ret;
पूर्ण

अटल पूर्णांक twl_get_direction(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);
	/*
	 * Default GPIO_LINE_सूचीECTION_OUT
	 * LED GPIOs >= TWL4030_GPIO_MAX are always output
	 */
	पूर्णांक ret = GPIO_LINE_सूचीECTION_OUT;

	mutex_lock(&priv->mutex);
	अगर (offset < TWL4030_GPIO_MAX) अणु
		ret = twl4030_get_gpio_direction(offset);
		अगर (ret) अणु
			mutex_unlock(&priv->mutex);
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&priv->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक twl_to_irq(काष्ठा gpio_chip *chip, अचिन्हित offset)
अणु
	काष्ठा gpio_twl4030_priv *priv = gpiochip_get_data(chip);

	वापस (priv->irq_base && (offset < TWL4030_GPIO_MAX))
		? (priv->irq_base + offset)
		: -EINVAL;
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.label			= "twl4030",
	.owner			= THIS_MODULE,
	.request		= twl_request,
	.मुक्त			= twl_मुक्त,
	.direction_input	= twl_direction_in,
	.direction_output	= twl_direction_out,
	.get_direction		= twl_get_direction,
	.get			= twl_get,
	.set			= twl_set,
	.to_irq			= twl_to_irq,
	.can_sleep		= true,
पूर्ण;

/*----------------------------------------------------------------------*/

अटल पूर्णांक gpio_twl4030_pulls(u32 ups, u32 करोwns)
अणु
	u8		message[5];
	अचिन्हित	i, gpio_bit;

	/* For most pins, a pullकरोwn was enabled by शेष.
	 * We should have data that's specअगरic to this board.
	 */
	क्रम (gpio_bit = 1, i = 0; i < 5; i++) अणु
		u8		bit_mask;
		अचिन्हित	j;

		क्रम (bit_mask = 0, j = 0; j < 8; j += 2, gpio_bit <<= 1) अणु
			अगर (ups & gpio_bit)
				bit_mask |= 1 << (j + 1);
			अन्यथा अगर (करोwns & gpio_bit)
				bit_mask |= 1 << (j + 0);
		पूर्ण
		message[i] = bit_mask;
	पूर्ण

	वापस twl_i2c_ग_लिखो(TWL4030_MODULE_GPIO, message,
				REG_GPIOPUPDCTR1, 5);
पूर्ण

अटल पूर्णांक gpio_twl4030_debounce(u32 debounce, u8 mmc_cd)
अणु
	u8		message[3];

	/* 30 msec of debouncing is always used क्रम MMC card detect,
	 * and is optional क्रम everything अन्यथा.
	 */
	message[0] = (debounce & 0xff) | (mmc_cd & 0x03);
	debounce >>= 8;
	message[1] = (debounce & 0xff);
	debounce >>= 8;
	message[2] = (debounce & 0x03);

	वापस twl_i2c_ग_लिखो(TWL4030_MODULE_GPIO, message,
				REG_GPIO_DEBEN1, 3);
पूर्ण

अटल पूर्णांक gpio_twl4030_हटाओ(काष्ठा platक्रमm_device *pdev);

अटल काष्ठा twl4030_gpio_platक्रमm_data *of_gpio_twl4030(काष्ठा device *dev,
				काष्ठा twl4030_gpio_platक्रमm_data *pdata)
अणु
	काष्ठा twl4030_gpio_platक्रमm_data *omap_twl_info;

	omap_twl_info = devm_kzalloc(dev, माप(*omap_twl_info), GFP_KERNEL);
	अगर (!omap_twl_info)
		वापस शून्य;

	अगर (pdata)
		*omap_twl_info = *pdata;

	omap_twl_info->use_leds = of_property_पढ़ो_bool(dev->of_node,
			"ti,use-leds");

	of_property_पढ़ो_u32(dev->of_node, "ti,debounce",
			     &omap_twl_info->debounce);
	of_property_पढ़ो_u32(dev->of_node, "ti,mmc-cd",
			     (u32 *)&omap_twl_info->mmc_cd);
	of_property_पढ़ो_u32(dev->of_node, "ti,pullups",
			     &omap_twl_info->pullups);
	of_property_पढ़ो_u32(dev->of_node, "ti,pulldowns",
			     &omap_twl_info->pullकरोwns);

	वापस omap_twl_info;
पूर्ण

अटल पूर्णांक gpio_twl4030_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_gpio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा gpio_twl4030_priv *priv;
	पूर्णांक ret, irq_base;

	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा gpio_twl4030_priv),
			    GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* maybe setup IRQs */
	अगर (is_module()) अणु
		dev_err(&pdev->dev, "can't dispatch IRQs from modules\n");
		जाओ no_irqs;
	पूर्ण

	irq_base = devm_irq_alloc_descs(&pdev->dev, -1,
					0, TWL4030_GPIO_MAX, 0);
	अगर (irq_base < 0) अणु
		dev_err(&pdev->dev, "Failed to alloc irq_descs\n");
		वापस irq_base;
	पूर्ण

	irq_करोमुख्य_add_legacy(node, TWL4030_GPIO_MAX, irq_base, 0,
			      &irq_करोमुख्य_simple_ops, शून्य);

	ret = twl4030_sih_setup(&pdev->dev, TWL4030_MODULE_GPIO, irq_base);
	अगर (ret < 0)
		वापस ret;

	priv->irq_base = irq_base;

no_irqs:
	priv->gpio_chip = ढाँचा_chip;
	priv->gpio_chip.base = -1;
	priv->gpio_chip.ngpio = TWL4030_GPIO_MAX;
	priv->gpio_chip.parent = &pdev->dev;

	mutex_init(&priv->mutex);

	अगर (node)
		pdata = of_gpio_twl4030(&pdev->dev, pdata);

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "Platform data is missing\n");
		वापस -ENXIO;
	पूर्ण

	/*
	 * NOTE:  boards may waste घातer अगर they करोn't set pullups
	 * and pullकरोwns correctly ... शेष क्रम non-ULPI pins is
	 * pullकरोwn, and some other pins may have बाह्यal pullups
	 * or pullकरोwns.  Careful!
	 */
	ret = gpio_twl4030_pulls(pdata->pullups, pdata->pullकरोwns);
	अगर (ret)
		dev_dbg(&pdev->dev, "pullups %.05x %.05x --> %d\n",
			pdata->pullups, pdata->pullकरोwns, ret);

	ret = gpio_twl4030_debounce(pdata->debounce, pdata->mmc_cd);
	अगर (ret)
		dev_dbg(&pdev->dev, "debounce %.03x %.01x --> %d\n",
			pdata->debounce, pdata->mmc_cd, ret);

	/*
	 * NOTE: we assume VIBRA_CTL.VIBRA_EN, in MODULE_AUDIO_VOICE,
	 * is (still) clear अगर use_leds is set.
	 */
	अगर (pdata->use_leds)
		priv->gpio_chip.ngpio += 2;

	ret = gpiochip_add_data(&priv->gpio_chip, priv);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "could not register gpiochip, %d\n", ret);
		priv->gpio_chip.ngpio = 0;
		gpio_twl4030_हटाओ(pdev);
		जाओ out;
	पूर्ण

	platक्रमm_set_drvdata(pdev, priv);

	अगर (pdata->setup) अणु
		पूर्णांक status;

		status = pdata->setup(&pdev->dev, priv->gpio_chip.base,
				      TWL4030_GPIO_MAX);
		अगर (status)
			dev_dbg(&pdev->dev, "setup --> %d\n", status);
	पूर्ण

out:
	वापस ret;
पूर्ण

/* Cannot use as gpio_twl4030_probe() calls us */
अटल पूर्णांक gpio_twl4030_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा twl4030_gpio_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा gpio_twl4030_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक status;

	अगर (pdata && pdata->tearकरोwn) अणु
		status = pdata->tearकरोwn(&pdev->dev, priv->gpio_chip.base,
					 TWL4030_GPIO_MAX);
		अगर (status) अणु
			dev_dbg(&pdev->dev, "teardown --> %d\n", status);
			वापस status;
		पूर्ण
	पूर्ण

	gpiochip_हटाओ(&priv->gpio_chip);

	अगर (is_module())
		वापस 0;

	/* REVISIT no support yet क्रम deरेजिस्टरing all the IRQs */
	WARN_ON(1);
	वापस -EIO;
पूर्ण

अटल स्थिर काष्ठा of_device_id twl_gpio_match[] = अणु
	अणु .compatible = "ti,twl4030-gpio", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, twl_gpio_match);

/* Note:  this hardware lives inside an I2C-based multi-function device. */
MODULE_ALIAS("platform:twl4030_gpio");

अटल काष्ठा platक्रमm_driver gpio_twl4030_driver = अणु
	.driver = अणु
		.name	= "twl4030_gpio",
		.of_match_table = twl_gpio_match,
	पूर्ण,
	.probe		= gpio_twl4030_probe,
	.हटाओ		= gpio_twl4030_हटाओ,
पूर्ण;

अटल पूर्णांक __init gpio_twl4030_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&gpio_twl4030_driver);
पूर्ण
subsys_initcall(gpio_twl4030_init);

अटल व्योम __निकास gpio_twl4030_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gpio_twl4030_driver);
पूर्ण
module_निकास(gpio_twl4030_निकास);

MODULE_AUTHOR("Texas Instruments, Inc.");
MODULE_DESCRIPTION("GPIO interface for TWL4030");
MODULE_LICENSE("GPL");
