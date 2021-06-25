<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Backlight driver क्रम the Kinetic KTD253
 * Based on code and know-how from the Samsung GT-S7710
 * Gareth Phillips <gareth.phillips@samsung.com>
 */
#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>

/* Current ratio is n/32 from 1/32 to 32/32 */
#घोषणा KTD253_MIN_RATIO 1
#घोषणा KTD253_MAX_RATIO 32
#घोषणा KTD253_DEFAULT_RATIO 13

#घोषणा KTD253_T_LOW_NS (200 + 10) /* Additional 10ns as safety factor */
#घोषणा KTD253_T_HIGH_NS (200 + 10) /* Additional 10ns as safety factor */
#घोषणा KTD253_T_OFF_MS 3

काष्ठा ktd253_backlight अणु
	काष्ठा device *dev;
	काष्ठा backlight_device *bl;
	काष्ठा gpio_desc *gpiod;
	u16 ratio;
पूर्ण;

अटल पूर्णांक ktd253_backlight_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा ktd253_backlight *ktd253 = bl_get_data(bl);
	पूर्णांक brightness = backlight_get_brightness(bl);
	u16 target_ratio;
	u16 current_ratio = ktd253->ratio;
	अचिन्हित दीर्घ flags;

	dev_dbg(ktd253->dev, "new brightness/ratio: %d/32\n", brightness);

	target_ratio = brightness;

	अगर (target_ratio == current_ratio)
		/* This is alपढ़ोy right */
		वापस 0;

	अगर (target_ratio == 0) अणु
		gpiod_set_value_cansleep(ktd253->gpiod, 0);
		/*
		 * We need to keep the GPIO low क्रम at least this दीर्घ
		 * to actually चयन the KTD253 off.
		 */
		msleep(KTD253_T_OFF_MS);
		ktd253->ratio = 0;
		वापस 0;
	पूर्ण

	अगर (current_ratio == 0) अणु
		gpiod_set_value_cansleep(ktd253->gpiod, 1);
		ndelay(KTD253_T_HIGH_NS);
		/* We always fall back to this when we घातer on */
		current_ratio = KTD253_MAX_RATIO;
	पूर्ण

	/*
	 * WARNING:
	 * The loop to set the correct current level is perक्रमmed
	 * with पूर्णांकerrupts disabled as it is timing critical.
	 * The maximum number of cycles of the loop is 32
	 * so the समय taken will be (T_LOW_NS + T_HIGH_NS + loop_समय) * 32,
	 */
	local_irq_save(flags);
	जबतक (current_ratio != target_ratio) अणु
		/*
		 * These GPIO operations असलolutely can NOT sleep so no
		 * _cansleep suffixes, and no using GPIO expanders on
		 * slow buses क्रम this!
		 */
		gpiod_set_value(ktd253->gpiod, 0);
		ndelay(KTD253_T_LOW_NS);
		gpiod_set_value(ktd253->gpiod, 1);
		ndelay(KTD253_T_HIGH_NS);
		/* After 1/32 we loop back to 32/32 */
		अगर (current_ratio == KTD253_MIN_RATIO)
			current_ratio = KTD253_MAX_RATIO;
		अन्यथा
			current_ratio--;
	पूर्ण
	local_irq_restore(flags);
	ktd253->ratio = current_ratio;

	dev_dbg(ktd253->dev, "new ratio set to %d/32\n", target_ratio);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops ktd253_backlight_ops = अणु
	.options	= BL_CORE_SUSPENDRESUME,
	.update_status	= ktd253_backlight_update_status,
पूर्ण;

अटल पूर्णांक ktd253_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा backlight_device *bl;
	काष्ठा ktd253_backlight *ktd253;
	u32 max_brightness;
	u32 brightness;
	पूर्णांक ret;

	ktd253 = devm_kzalloc(dev, माप(*ktd253), GFP_KERNEL);
	अगर (!ktd253)
		वापस -ENOMEM;
	ktd253->dev = dev;

	ret = device_property_पढ़ो_u32(dev, "max-brightness", &max_brightness);
	अगर (ret)
		max_brightness = KTD253_MAX_RATIO;
	अगर (max_brightness > KTD253_MAX_RATIO) अणु
		/* Clamp brightness to hardware max */
		dev_err(dev, "illegal max brightness specified\n");
		max_brightness = KTD253_MAX_RATIO;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "default-brightness", &brightness);
	अगर (ret)
		brightness = KTD253_DEFAULT_RATIO;
	अगर (brightness > max_brightness) अणु
		/* Clamp शेष brightness to max brightness */
		dev_err(dev, "default brightness exceeds max brightness\n");
		brightness = max_brightness;
	पूर्ण

	ktd253->gpiod = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	अगर (IS_ERR(ktd253->gpiod)) अणु
		ret = PTR_ERR(ktd253->gpiod);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "gpio line missing or invalid.\n");
		वापस ret;
	पूर्ण
	gpiod_set_consumer_name(ktd253->gpiod, dev_name(dev));
	/* Bring backlight to a known off state */
	msleep(KTD253_T_OFF_MS);

	bl = devm_backlight_device_रेजिस्टर(dev, dev_name(dev), dev, ktd253,
					    &ktd253_backlight_ops, शून्य);
	अगर (IS_ERR(bl)) अणु
		dev_err(dev, "failed to register backlight\n");
		वापस PTR_ERR(bl);
	पूर्ण
	bl->props.max_brightness = max_brightness;
	/* When we just enable the GPIO line we set max brightness */
	अगर (brightness) अणु
		bl->props.brightness = brightness;
		bl->props.घातer = FB_BLANK_UNBLANK;
	पूर्ण अन्यथा अणु
		bl->props.brightness = 0;
		bl->props.घातer = FB_BLANK_POWERDOWN;
	पूर्ण

	ktd253->bl = bl;
	platक्रमm_set_drvdata(pdev, bl);
	backlight_update_status(bl);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ktd253_backlight_of_match[] = अणु
	अणु .compatible = "kinetic,ktd253" पूर्ण,
	अणु .compatible = "kinetic,ktd259" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ktd253_backlight_of_match);

अटल काष्ठा platक्रमm_driver ktd253_backlight_driver = अणु
	.driver = अणु
		.name = "ktd253-backlight",
		.of_match_table = ktd253_backlight_of_match,
	पूर्ण,
	.probe		= ktd253_backlight_probe,
पूर्ण;
module_platक्रमm_driver(ktd253_backlight_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("Kinetic KTD253 Backlight Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ktd253-backlight");
