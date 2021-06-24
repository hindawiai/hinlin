<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * LED driver क्रम Mediatek MT6323 PMIC
 *
 * Copyright (C) 2017 Sean Wang <sean.wang@mediatek.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/leds.h>
#समावेश <linux/mfd/mt6323/रेजिस्टरs.h>
#समावेश <linux/mfd/mt6397/core.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/*
 * Register field क्रम MT6323_TOP_CKPDN0 to enable
 * 32K घड़ी common क्रम LED device.
 */
#घोषणा MT6323_RG_DRV_32K_CK_PDN	BIT(11)
#घोषणा MT6323_RG_DRV_32K_CK_PDN_MASK	BIT(11)

/*
 * Register field क्रम MT6323_TOP_CKPDN2 to enable
 * inभागidual घड़ी क्रम LED device.
 */
#घोषणा MT6323_RG_ISINK_CK_PDN(i)	BIT(i)
#घोषणा MT6323_RG_ISINK_CK_PDN_MASK(i)	BIT(i)

/*
 * Register field क्रम MT6323_TOP_CKCON1 to select
 * घड़ी source.
 */
#घोषणा MT6323_RG_ISINK_CK_SEL_MASK(i)	(BIT(10) << (i))

/*
 * Register क्रम MT6323_ISINK_CON0 to setup the
 * duty cycle of the blink.
 */
#घोषणा MT6323_ISINK_CON0(i)		(MT6323_ISINK0_CON0 + 0x8 * (i))
#घोषणा MT6323_ISINK_DIM_DUTY_MASK	(0x1f << 8)
#घोषणा MT6323_ISINK_DIM_DUTY(i)	(((i) << 8) & \
					MT6323_ISINK_DIM_DUTY_MASK)

/* Register to setup the period of the blink. */
#घोषणा MT6323_ISINK_CON1(i)		(MT6323_ISINK0_CON1 + 0x8 * (i))
#घोषणा MT6323_ISINK_DIM_FSEL_MASK	(0xffff)
#घोषणा MT6323_ISINK_DIM_FSEL(i)	((i) & MT6323_ISINK_DIM_FSEL_MASK)

/* Register to control the brightness. */
#घोषणा MT6323_ISINK_CON2(i)		(MT6323_ISINK0_CON2 + 0x8 * (i))
#घोषणा MT6323_ISINK_CH_STEP_SHIFT	12
#घोषणा MT6323_ISINK_CH_STEP_MASK	(0x7 << 12)
#घोषणा MT6323_ISINK_CH_STEP(i)		(((i) << 12) & \
					MT6323_ISINK_CH_STEP_MASK)
#घोषणा MT6323_ISINK_SFSTR0_TC_MASK	(0x3 << 1)
#घोषणा MT6323_ISINK_SFSTR0_TC(i)	(((i) << 1) & \
					MT6323_ISINK_SFSTR0_TC_MASK)
#घोषणा MT6323_ISINK_SFSTR0_EN_MASK	BIT(0)
#घोषणा MT6323_ISINK_SFSTR0_EN		BIT(0)

/* Register to LED channel enablement. */
#घोषणा MT6323_ISINK_CH_EN_MASK(i)	BIT(i)
#घोषणा MT6323_ISINK_CH_EN(i)		BIT(i)

#घोषणा MT6323_MAX_PERIOD		10000
#घोषणा MT6323_MAX_LEDS			4
#घोषणा MT6323_MAX_BRIGHTNESS		6
#घोषणा MT6323_UNIT_DUTY		3125
#घोषणा MT6323_CAL_HW_DUTY(o, p)	DIV_ROUND_CLOSEST((o) * 100000ul,\
					(p) * MT6323_UNIT_DUTY)

काष्ठा mt6323_leds;

/**
 * काष्ठा mt6323_led - state container क्रम the LED device
 * @id:			the identअगरier in MT6323 LED device
 * @parent:		the poपूर्णांकer to MT6323 LED controller
 * @cdev:		LED class device क्रम this LED device
 * @current_brightness: current state of the LED device
 */
काष्ठा mt6323_led अणु
	पूर्णांक			id;
	काष्ठा mt6323_leds	*parent;
	काष्ठा led_classdev	cdev;
	क्रमागत led_brightness	current_brightness;
पूर्ण;

/**
 * काष्ठा mt6323_leds -	state container क्रम holding LED controller
 *			of the driver
 * @dev:		the device poपूर्णांकer
 * @hw:			the underlying hardware providing shared
 *			bus क्रम the रेजिस्टर operations
 * @lock:		the lock among process context
 * @led:		the array that contains the state of inभागidual
 *			LED device
 */
काष्ठा mt6323_leds अणु
	काष्ठा device		*dev;
	काष्ठा mt6397_chip	*hw;
	/* protect among process context */
	काष्ठा mutex		lock;
	काष्ठा mt6323_led	*led[MT6323_MAX_LEDS];
पूर्ण;

अटल पूर्णांक mt6323_led_hw_brightness(काष्ठा led_classdev *cdev,
				    क्रमागत led_brightness brightness)
अणु
	काष्ठा mt6323_led *led = container_of(cdev, काष्ठा mt6323_led, cdev);
	काष्ठा mt6323_leds *leds = led->parent;
	काष्ठा regmap *regmap = leds->hw->regmap;
	u32 con2_mask = 0, con2_val = 0;
	पूर्णांक ret;

	/*
	 * Setup current output क्रम the corresponding
	 * brightness level.
	 */
	con2_mask |= MT6323_ISINK_CH_STEP_MASK |
		     MT6323_ISINK_SFSTR0_TC_MASK |
		     MT6323_ISINK_SFSTR0_EN_MASK;
	con2_val |=  MT6323_ISINK_CH_STEP(brightness - 1) |
		     MT6323_ISINK_SFSTR0_TC(2) |
		     MT6323_ISINK_SFSTR0_EN;

	ret = regmap_update_bits(regmap, MT6323_ISINK_CON2(led->id),
				 con2_mask, con2_val);
	वापस ret;
पूर्ण

अटल पूर्णांक mt6323_led_hw_off(काष्ठा led_classdev *cdev)
अणु
	काष्ठा mt6323_led *led = container_of(cdev, काष्ठा mt6323_led, cdev);
	काष्ठा mt6323_leds *leds = led->parent;
	काष्ठा regmap *regmap = leds->hw->regmap;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	status = MT6323_ISINK_CH_EN(led->id);
	ret = regmap_update_bits(regmap, MT6323_ISINK_EN_CTRL,
				 MT6323_ISINK_CH_EN_MASK(led->id), ~status);
	अगर (ret < 0)
		वापस ret;

	usleep_range(100, 300);
	ret = regmap_update_bits(regmap, MT6323_TOP_CKPDN2,
				 MT6323_RG_ISINK_CK_PDN_MASK(led->id),
				 MT6323_RG_ISINK_CK_PDN(led->id));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल क्रमागत led_brightness
mt6323_get_led_hw_brightness(काष्ठा led_classdev *cdev)
अणु
	काष्ठा mt6323_led *led = container_of(cdev, काष्ठा mt6323_led, cdev);
	काष्ठा mt6323_leds *leds = led->parent;
	काष्ठा regmap *regmap = leds->hw->regmap;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, MT6323_TOP_CKPDN2, &status);
	अगर (ret < 0)
		वापस ret;

	अगर (status & MT6323_RG_ISINK_CK_PDN_MASK(led->id))
		वापस 0;

	ret = regmap_पढ़ो(regmap, MT6323_ISINK_EN_CTRL, &status);
	अगर (ret < 0)
		वापस ret;

	अगर (!(status & MT6323_ISINK_CH_EN(led->id)))
		वापस 0;

	ret = regmap_पढ़ो(regmap, MT6323_ISINK_CON2(led->id), &status);
	अगर (ret < 0)
		वापस ret;

	वापस  ((status & MT6323_ISINK_CH_STEP_MASK)
		  >> MT6323_ISINK_CH_STEP_SHIFT) + 1;
पूर्ण

अटल पूर्णांक mt6323_led_hw_on(काष्ठा led_classdev *cdev,
			    क्रमागत led_brightness brightness)
अणु
	काष्ठा mt6323_led *led = container_of(cdev, काष्ठा mt6323_led, cdev);
	काष्ठा mt6323_leds *leds = led->parent;
	काष्ठा regmap *regmap = leds->hw->regmap;
	अचिन्हित पूर्णांक status;
	पूर्णांक ret;

	/*
	 * Setup required घड़ी source, enable the corresponding
	 * घड़ी and channel and let work with continuous blink as
	 * the शेष.
	 */
	ret = regmap_update_bits(regmap, MT6323_TOP_CKCON1,
				 MT6323_RG_ISINK_CK_SEL_MASK(led->id), 0);
	अगर (ret < 0)
		वापस ret;

	status = MT6323_RG_ISINK_CK_PDN(led->id);
	ret = regmap_update_bits(regmap, MT6323_TOP_CKPDN2,
				 MT6323_RG_ISINK_CK_PDN_MASK(led->id),
				 ~status);
	अगर (ret < 0)
		वापस ret;

	usleep_range(100, 300);

	ret = regmap_update_bits(regmap, MT6323_ISINK_EN_CTRL,
				 MT6323_ISINK_CH_EN_MASK(led->id),
				 MT6323_ISINK_CH_EN(led->id));
	अगर (ret < 0)
		वापस ret;

	ret = mt6323_led_hw_brightness(cdev, brightness);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(regmap, MT6323_ISINK_CON0(led->id),
				 MT6323_ISINK_DIM_DUTY_MASK,
				 MT6323_ISINK_DIM_DUTY(31));
	अगर (ret < 0)
		वापस ret;

	ret = regmap_update_bits(regmap, MT6323_ISINK_CON1(led->id),
				 MT6323_ISINK_DIM_FSEL_MASK,
				 MT6323_ISINK_DIM_FSEL(1000));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक mt6323_led_set_blink(काष्ठा led_classdev *cdev,
				अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा mt6323_led *led = container_of(cdev, काष्ठा mt6323_led, cdev);
	काष्ठा mt6323_leds *leds = led->parent;
	काष्ठा regmap *regmap = leds->hw->regmap;
	अचिन्हित दीर्घ period;
	u8 duty_hw;
	पूर्णांक ret;

	/*
	 * LED subप्रणाली requires a शेष user
	 * मित्रly blink pattern क्रम the LED so using
	 * 1Hz duty cycle 50% here अगर without specअगरic
	 * value delay_on and delay off being asचिन्हित.
	 */
	अगर (!*delay_on && !*delay_off) अणु
		*delay_on = 500;
		*delay_off = 500;
	पूर्ण

	/*
	 * Units are in ms, अगर over the hardware able
	 * to support, fallback पूर्णांकo software blink
	 */
	period = *delay_on + *delay_off;

	अगर (period > MT6323_MAX_PERIOD)
		वापस -EINVAL;

	/*
	 * Calculate duty_hw based on the percentage of period during
	 * which the led is ON.
	 */
	duty_hw = MT6323_CAL_HW_DUTY(*delay_on, period);

	/* hardware करोesn't support zero duty cycle. */
	अगर (!duty_hw)
		वापस -EINVAL;

	mutex_lock(&leds->lock);
	/*
	 * Set max_brightness as the software blink behavior
	 * when no blink brightness.
	 */
	अगर (!led->current_brightness) अणु
		ret = mt6323_led_hw_on(cdev, cdev->max_brightness);
		अगर (ret < 0)
			जाओ out;
		led->current_brightness = cdev->max_brightness;
	पूर्ण

	ret = regmap_update_bits(regmap, MT6323_ISINK_CON0(led->id),
				 MT6323_ISINK_DIM_DUTY_MASK,
				 MT6323_ISINK_DIM_DUTY(duty_hw - 1));
	अगर (ret < 0)
		जाओ out;

	ret = regmap_update_bits(regmap, MT6323_ISINK_CON1(led->id),
				 MT6323_ISINK_DIM_FSEL_MASK,
				 MT6323_ISINK_DIM_FSEL(period - 1));
out:
	mutex_unlock(&leds->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mt6323_led_set_brightness(काष्ठा led_classdev *cdev,
				     क्रमागत led_brightness brightness)
अणु
	काष्ठा mt6323_led *led = container_of(cdev, काष्ठा mt6323_led, cdev);
	काष्ठा mt6323_leds *leds = led->parent;
	पूर्णांक ret;

	mutex_lock(&leds->lock);

	अगर (!led->current_brightness && brightness) अणु
		ret = mt6323_led_hw_on(cdev, brightness);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अगर (brightness) अणु
		ret = mt6323_led_hw_brightness(cdev, brightness);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = mt6323_led_hw_off(cdev);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	led->current_brightness = brightness;
out:
	mutex_unlock(&leds->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mt6323_led_set_dt_शेष(काष्ठा led_classdev *cdev,
				     काष्ठा device_node *np)
अणु
	काष्ठा mt6323_led *led = container_of(cdev, काष्ठा mt6323_led, cdev);
	स्थिर अक्षर *state;
	पूर्णांक ret = 0;

	state = of_get_property(np, "default-state", शून्य);
	अगर (state) अणु
		अगर (!म_भेद(state, "keep")) अणु
			ret = mt6323_get_led_hw_brightness(cdev);
			अगर (ret < 0)
				वापस ret;
			led->current_brightness = ret;
			ret = 0;
		पूर्ण अन्यथा अगर (!म_भेद(state, "on")) अणु
			ret =
			mt6323_led_set_brightness(cdev, cdev->max_brightness);
		पूर्ण अन्यथा  अणु
			ret = mt6323_led_set_brightness(cdev, LED_OFF);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mt6323_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(dev);
	काष्ठा device_node *child;
	काष्ठा mt6397_chip *hw = dev_get_drvdata(dev->parent);
	काष्ठा mt6323_leds *leds;
	काष्ठा mt6323_led *led;
	पूर्णांक ret;
	अचिन्हित पूर्णांक status;
	u32 reg;

	leds = devm_kzalloc(dev, माप(*leds), GFP_KERNEL);
	अगर (!leds)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, leds);
	leds->dev = dev;

	/*
	 * leds->hw poपूर्णांकs to the underlying bus क्रम the रेजिस्टर
	 * controlled.
	 */
	leds->hw = hw;
	mutex_init(&leds->lock);

	status = MT6323_RG_DRV_32K_CK_PDN;
	ret = regmap_update_bits(leds->hw->regmap, MT6323_TOP_CKPDN0,
				 MT6323_RG_DRV_32K_CK_PDN_MASK, ~status);
	अगर (ret < 0) अणु
		dev_err(leds->dev,
			"Failed to update MT6323_TOP_CKPDN0 Register\n");
		वापस ret;
	पूर्ण

	क्रम_each_available_child_of_node(np, child) अणु
		काष्ठा led_init_data init_data = अणुपूर्ण;

		ret = of_property_पढ़ो_u32(child, "reg", &reg);
		अगर (ret) अणु
			dev_err(dev, "Failed to read led 'reg' property\n");
			जाओ put_child_node;
		पूर्ण

		अगर (reg >= MT6323_MAX_LEDS || leds->led[reg]) अणु
			dev_err(dev, "Invalid led reg %u\n", reg);
			ret = -EINVAL;
			जाओ put_child_node;
		पूर्ण

		led = devm_kzalloc(dev, माप(*led), GFP_KERNEL);
		अगर (!led) अणु
			ret = -ENOMEM;
			जाओ put_child_node;
		पूर्ण

		leds->led[reg] = led;
		leds->led[reg]->id = reg;
		leds->led[reg]->cdev.max_brightness = MT6323_MAX_BRIGHTNESS;
		leds->led[reg]->cdev.brightness_set_blocking =
					mt6323_led_set_brightness;
		leds->led[reg]->cdev.blink_set = mt6323_led_set_blink;
		leds->led[reg]->cdev.brightness_get =
					mt6323_get_led_hw_brightness;
		leds->led[reg]->parent = leds;

		ret = mt6323_led_set_dt_शेष(&leds->led[reg]->cdev, child);
		अगर (ret < 0) अणु
			dev_err(leds->dev,
				"Failed to LED set default from devicetree\n");
			जाओ put_child_node;
		पूर्ण

		init_data.fwnode = of_fwnode_handle(child);

		ret = devm_led_classdev_रेजिस्टर_ext(dev, &leds->led[reg]->cdev,
						     &init_data);
		अगर (ret) अणु
			dev_err(dev, "Failed to register LED: %d\n", ret);
			जाओ put_child_node;
		पूर्ण
	पूर्ण

	वापस 0;

put_child_node:
	of_node_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक mt6323_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mt6323_leds *leds = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	/* Turn the LEDs off on driver removal. */
	क्रम (i = 0 ; leds->led[i] ; i++)
		mt6323_led_hw_off(&leds->led[i]->cdev);

	regmap_update_bits(leds->hw->regmap, MT6323_TOP_CKPDN0,
			   MT6323_RG_DRV_32K_CK_PDN_MASK,
			   MT6323_RG_DRV_32K_CK_PDN);

	mutex_destroy(&leds->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt6323_led_dt_match[] = अणु
	अणु .compatible = "mediatek,mt6323-led" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt6323_led_dt_match);

अटल काष्ठा platक्रमm_driver mt6323_led_driver = अणु
	.probe		= mt6323_led_probe,
	.हटाओ		= mt6323_led_हटाओ,
	.driver		= अणु
		.name	= "mt6323-led",
		.of_match_table = mt6323_led_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mt6323_led_driver);

MODULE_DESCRIPTION("LED driver for Mediatek MT6323 PMIC");
MODULE_AUTHOR("Sean Wang <sean.wang@mediatek.com>");
MODULE_LICENSE("GPL");
