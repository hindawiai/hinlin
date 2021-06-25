<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Spपढ़ोtrum Communications Inc.

#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

/* PMIC global control रेजिस्टर definition */
#घोषणा SC27XX_MODULE_EN0	0xc08
#घोषणा SC27XX_CLK_EN0		0xc18
#घोषणा SC27XX_RGB_CTRL		0xebc

#घोषणा SC27XX_BLTC_EN		BIT(9)
#घोषणा SC27XX_RTC_EN		BIT(7)
#घोषणा SC27XX_RGB_PD		BIT(0)

/* Breathing light controller रेजिस्टर definition */
#घोषणा SC27XX_LEDS_CTRL	0x00
#घोषणा SC27XX_LEDS_PRESCALE	0x04
#घोषणा SC27XX_LEDS_DUTY	0x08
#घोषणा SC27XX_LEDS_CURVE0	0x0c
#घोषणा SC27XX_LEDS_CURVE1	0x10

#घोषणा SC27XX_CTRL_SHIFT	4
#घोषणा SC27XX_LED_RUN		BIT(0)
#घोषणा SC27XX_LED_TYPE		BIT(1)

#घोषणा SC27XX_DUTY_SHIFT	8
#घोषणा SC27XX_DUTY_MASK	GENMASK(15, 0)
#घोषणा SC27XX_MOD_MASK		GENMASK(7, 0)

#घोषणा SC27XX_CURVE_SHIFT	8
#घोषणा SC27XX_CURVE_L_MASK	GENMASK(7, 0)
#घोषणा SC27XX_CURVE_H_MASK	GENMASK(15, 8)

#घोषणा SC27XX_LEDS_OFFSET	0x10
#घोषणा SC27XX_LEDS_MAX		3
#घोषणा SC27XX_LEDS_PATTERN_CNT	4
/* Stage duration step, in milliseconds */
#घोषणा SC27XX_LEDS_STEP	125
/* Minimum and maximum duration, in milliseconds */
#घोषणा SC27XX_DELTA_T_MIN	SC27XX_LEDS_STEP
#घोषणा SC27XX_DELTA_T_MAX	(SC27XX_LEDS_STEP * 255)

काष्ठा sc27xx_led अणु
	काष्ठा fwnode_handle *fwnode;
	काष्ठा led_classdev ldev;
	काष्ठा sc27xx_led_priv *priv;
	u8 line;
	bool active;
पूर्ण;

काष्ठा sc27xx_led_priv अणु
	काष्ठा sc27xx_led leds[SC27XX_LEDS_MAX];
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;
	u32 base;
पूर्ण;

#घोषणा to_sc27xx_led(ldev) \
	container_of(ldev, काष्ठा sc27xx_led, ldev)

अटल पूर्णांक sc27xx_led_init(काष्ठा regmap *regmap)
अणु
	पूर्णांक err;

	err = regmap_update_bits(regmap, SC27XX_MODULE_EN0, SC27XX_BLTC_EN,
				 SC27XX_BLTC_EN);
	अगर (err)
		वापस err;

	err = regmap_update_bits(regmap, SC27XX_CLK_EN0, SC27XX_RTC_EN,
				 SC27XX_RTC_EN);
	अगर (err)
		वापस err;

	वापस regmap_update_bits(regmap, SC27XX_RGB_CTRL, SC27XX_RGB_PD, 0);
पूर्ण

अटल u32 sc27xx_led_get_offset(काष्ठा sc27xx_led *leds)
अणु
	वापस leds->priv->base + SC27XX_LEDS_OFFSET * leds->line;
पूर्ण

अटल पूर्णांक sc27xx_led_enable(काष्ठा sc27xx_led *leds, क्रमागत led_brightness value)
अणु
	u32 base = sc27xx_led_get_offset(leds);
	u32 ctrl_base = leds->priv->base + SC27XX_LEDS_CTRL;
	u8 ctrl_shअगरt = SC27XX_CTRL_SHIFT * leds->line;
	काष्ठा regmap *regmap = leds->priv->regmap;
	पूर्णांक err;

	err = regmap_update_bits(regmap, base + SC27XX_LEDS_DUTY,
				 SC27XX_DUTY_MASK,
				 (value << SC27XX_DUTY_SHIFT) |
				 SC27XX_MOD_MASK);
	अगर (err)
		वापस err;

	वापस regmap_update_bits(regmap, ctrl_base,
			(SC27XX_LED_RUN | SC27XX_LED_TYPE) << ctrl_shअगरt,
			(SC27XX_LED_RUN | SC27XX_LED_TYPE) << ctrl_shअगरt);
पूर्ण

अटल पूर्णांक sc27xx_led_disable(काष्ठा sc27xx_led *leds)
अणु
	काष्ठा regmap *regmap = leds->priv->regmap;
	u32 ctrl_base = leds->priv->base + SC27XX_LEDS_CTRL;
	u8 ctrl_shअगरt = SC27XX_CTRL_SHIFT * leds->line;

	वापस regmap_update_bits(regmap, ctrl_base,
			(SC27XX_LED_RUN | SC27XX_LED_TYPE) << ctrl_shअगरt, 0);
पूर्ण

अटल पूर्णांक sc27xx_led_set(काष्ठा led_classdev *ldev, क्रमागत led_brightness value)
अणु
	काष्ठा sc27xx_led *leds = to_sc27xx_led(ldev);
	पूर्णांक err;

	mutex_lock(&leds->priv->lock);

	अगर (value == LED_OFF)
		err = sc27xx_led_disable(leds);
	अन्यथा
		err = sc27xx_led_enable(leds, value);

	mutex_unlock(&leds->priv->lock);

	वापस err;
पूर्ण

अटल व्योम sc27xx_led_clamp_align_delta_t(u32 *delta_t)
अणु
	u32 v, offset, t = *delta_t;

	v = t + SC27XX_LEDS_STEP / 2;
	v = clamp_t(u32, v, SC27XX_DELTA_T_MIN, SC27XX_DELTA_T_MAX);
	offset = v - SC27XX_DELTA_T_MIN;
	offset = SC27XX_LEDS_STEP * (offset / SC27XX_LEDS_STEP);

	*delta_t = SC27XX_DELTA_T_MIN + offset;
पूर्ण

अटल पूर्णांक sc27xx_led_pattern_clear(काष्ठा led_classdev *ldev)
अणु
	काष्ठा sc27xx_led *leds = to_sc27xx_led(ldev);
	काष्ठा regmap *regmap = leds->priv->regmap;
	u32 base = sc27xx_led_get_offset(leds);
	u32 ctrl_base = leds->priv->base + SC27XX_LEDS_CTRL;
	u8 ctrl_shअगरt = SC27XX_CTRL_SHIFT * leds->line;
	पूर्णांक err;

	mutex_lock(&leds->priv->lock);

	/* Reset the rise, high, fall and low समय to zero. */
	regmap_ग_लिखो(regmap, base + SC27XX_LEDS_CURVE0, 0);
	regmap_ग_लिखो(regmap, base + SC27XX_LEDS_CURVE1, 0);

	err = regmap_update_bits(regmap, ctrl_base,
			(SC27XX_LED_RUN | SC27XX_LED_TYPE) << ctrl_shअगरt, 0);

	ldev->brightness = LED_OFF;

	mutex_unlock(&leds->priv->lock);

	वापस err;
पूर्ण

अटल पूर्णांक sc27xx_led_pattern_set(काष्ठा led_classdev *ldev,
				  काष्ठा led_pattern *pattern,
				  u32 len, पूर्णांक repeat)
अणु
	काष्ठा sc27xx_led *leds = to_sc27xx_led(ldev);
	u32 base = sc27xx_led_get_offset(leds);
	u32 ctrl_base = leds->priv->base + SC27XX_LEDS_CTRL;
	u8 ctrl_shअगरt = SC27XX_CTRL_SHIFT * leds->line;
	काष्ठा regmap *regmap = leds->priv->regmap;
	पूर्णांक err;

	/*
	 * Must contain 4 tuples to configure the rise समय, high समय, fall
	 * समय and low समय to enable the breathing mode.
	 */
	अगर (len != SC27XX_LEDS_PATTERN_CNT)
		वापस -EINVAL;

	mutex_lock(&leds->priv->lock);

	sc27xx_led_clamp_align_delta_t(&pattern[0].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE0,
				 SC27XX_CURVE_L_MASK,
				 pattern[0].delta_t / SC27XX_LEDS_STEP);
	अगर (err)
		जाओ out;

	sc27xx_led_clamp_align_delta_t(&pattern[1].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE1,
				 SC27XX_CURVE_L_MASK,
				 pattern[1].delta_t / SC27XX_LEDS_STEP);
	अगर (err)
		जाओ out;

	sc27xx_led_clamp_align_delta_t(&pattern[2].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE0,
				 SC27XX_CURVE_H_MASK,
				 (pattern[2].delta_t / SC27XX_LEDS_STEP) <<
				 SC27XX_CURVE_SHIFT);
	अगर (err)
		जाओ out;

	sc27xx_led_clamp_align_delta_t(&pattern[3].delta_t);
	err = regmap_update_bits(regmap, base + SC27XX_LEDS_CURVE1,
				 SC27XX_CURVE_H_MASK,
				 (pattern[3].delta_t / SC27XX_LEDS_STEP) <<
				 SC27XX_CURVE_SHIFT);
	अगर (err)
		जाओ out;

	err = regmap_update_bits(regmap, base + SC27XX_LEDS_DUTY,
				 SC27XX_DUTY_MASK,
				 (pattern[1].brightness << SC27XX_DUTY_SHIFT) |
				 SC27XX_MOD_MASK);
	अगर (err)
		जाओ out;

	/* Enable the LED breathing mode */
	err = regmap_update_bits(regmap, ctrl_base,
				 SC27XX_LED_RUN << ctrl_shअगरt,
				 SC27XX_LED_RUN << ctrl_shअगरt);
	अगर (!err)
		ldev->brightness = pattern[1].brightness;

out:
	mutex_unlock(&leds->priv->lock);

	वापस err;
पूर्ण

अटल पूर्णांक sc27xx_led_रेजिस्टर(काष्ठा device *dev, काष्ठा sc27xx_led_priv *priv)
अणु
	पूर्णांक i, err;

	err = sc27xx_led_init(priv->regmap);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < SC27XX_LEDS_MAX; i++) अणु
		काष्ठा sc27xx_led *led = &priv->leds[i];
		काष्ठा led_init_data init_data = अणुपूर्ण;

		अगर (!led->active)
			जारी;

		led->line = i;
		led->priv = priv;
		led->ldev.brightness_set_blocking = sc27xx_led_set;
		led->ldev.pattern_set = sc27xx_led_pattern_set;
		led->ldev.pattern_clear = sc27xx_led_pattern_clear;
		led->ldev.शेष_trigger = "pattern";

		init_data.fwnode = led->fwnode;
		init_data.devicename = "sc27xx";
		init_data.शेष_label = ":";

		err = devm_led_classdev_रेजिस्टर_ext(dev, &led->ldev,
						     &init_data);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sc27xx_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev_of_node(dev), *child;
	काष्ठा sc27xx_led_priv *priv;
	u32 base, count, reg;
	पूर्णांक err;

	count = of_get_available_child_count(np);
	अगर (!count || count > SC27XX_LEDS_MAX)
		वापस -EINVAL;

	err = of_property_पढ़ो_u32(np, "reg", &base);
	अगर (err) अणु
		dev_err(dev, "fail to get reg of property\n");
		वापस err;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);
	mutex_init(&priv->lock);
	priv->base = base;
	priv->regmap = dev_get_regmap(dev->parent, शून्य);
	अगर (!priv->regmap) अणु
		err = -ENODEV;
		dev_err(dev, "failed to get regmap: %d\n", err);
		वापस err;
	पूर्ण

	क्रम_each_available_child_of_node(np, child) अणु
		err = of_property_पढ़ो_u32(child, "reg", &reg);
		अगर (err) अणु
			of_node_put(child);
			mutex_destroy(&priv->lock);
			वापस err;
		पूर्ण

		अगर (reg >= SC27XX_LEDS_MAX || priv->leds[reg].active) अणु
			of_node_put(child);
			mutex_destroy(&priv->lock);
			वापस -EINVAL;
		पूर्ण

		priv->leds[reg].fwnode = of_fwnode_handle(child);
		priv->leds[reg].active = true;
	पूर्ण

	err = sc27xx_led_रेजिस्टर(dev, priv);
	अगर (err)
		mutex_destroy(&priv->lock);

	वापस err;
पूर्ण

अटल पूर्णांक sc27xx_led_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sc27xx_led_priv *priv = platक्रमm_get_drvdata(pdev);

	mutex_destroy(&priv->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sc27xx_led_of_match[] = अणु
	अणु .compatible = "sprd,sc2731-bltc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sc27xx_led_of_match);

अटल काष्ठा platक्रमm_driver sc27xx_led_driver = अणु
	.driver = अणु
		.name = "sprd-bltc",
		.of_match_table = sc27xx_led_of_match,
	पूर्ण,
	.probe = sc27xx_led_probe,
	.हटाओ = sc27xx_led_हटाओ,
पूर्ण;

module_platक्रमm_driver(sc27xx_led_driver);

MODULE_DESCRIPTION("Spreadtrum SC27xx breathing light controller driver");
MODULE_AUTHOR("Xiaotong Lu <xiaotong.lu@spreadtrum.com>");
MODULE_AUTHOR("Baolin Wang <baolin.wang@linaro.org>");
MODULE_LICENSE("GPL v2");
