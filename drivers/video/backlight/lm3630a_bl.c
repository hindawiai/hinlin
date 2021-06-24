<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Simple driver क्रम Texas Instruments LM3630A Backlight driver chip
* Copyright (C) 2012 Texas Instruments
*/
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pwm.h>
#समावेश <linux/platक्रमm_data/lm3630a_bl.h>

#घोषणा REG_CTRL	0x00
#घोषणा REG_BOOST	0x02
#घोषणा REG_CONFIG	0x01
#घोषणा REG_BRT_A	0x03
#घोषणा REG_BRT_B	0x04
#घोषणा REG_I_A		0x05
#घोषणा REG_I_B		0x06
#घोषणा REG_INT_STATUS	0x09
#घोषणा REG_INT_EN	0x0A
#घोषणा REG_FAULT	0x0B
#घोषणा REG_PWM_OUTLOW	0x12
#घोषणा REG_PWM_OUTHIGH	0x13
#घोषणा REG_FILTER_STRENGTH	0x50
#घोषणा REG_MAX		0x50

#घोषणा INT_DEBOUNCE_MSEC	10

#घोषणा LM3630A_BANK_0		0
#घोषणा LM3630A_BANK_1		1

#घोषणा LM3630A_NUM_SINKS	2
#घोषणा LM3630A_SINK_0		0
#घोषणा LM3630A_SINK_1		1

काष्ठा lm3630a_chip अणु
	काष्ठा device *dev;
	काष्ठा delayed_work work;

	पूर्णांक irq;
	काष्ठा workqueue_काष्ठा *irqthपढ़ो;
	काष्ठा lm3630a_platक्रमm_data *pdata;
	काष्ठा backlight_device *bleda;
	काष्ठा backlight_device *bledb;
	काष्ठा gpio_desc *enable_gpio;
	काष्ठा regmap *regmap;
	काष्ठा pwm_device *pwmd;
पूर्ण;

/* i2c access */
अटल पूर्णांक lm3630a_पढ़ो(काष्ठा lm3630a_chip *pchip, अचिन्हित पूर्णांक reg)
अणु
	पूर्णांक rval;
	अचिन्हित पूर्णांक reg_val;

	rval = regmap_पढ़ो(pchip->regmap, reg, &reg_val);
	अगर (rval < 0)
		वापस rval;
	वापस reg_val & 0xFF;
पूर्ण

अटल पूर्णांक lm3630a_ग_लिखो(काष्ठा lm3630a_chip *pchip,
			 अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक data)
अणु
	वापस regmap_ग_लिखो(pchip->regmap, reg, data);
पूर्ण

अटल पूर्णांक lm3630a_update(काष्ठा lm3630a_chip *pchip,
			  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
			  अचिन्हित पूर्णांक data)
अणु
	वापस regmap_update_bits(pchip->regmap, reg, mask, data);
पूर्ण

/* initialize chip */
अटल पूर्णांक lm3630a_chip_init(काष्ठा lm3630a_chip *pchip)
अणु
	पूर्णांक rval;
	काष्ठा lm3630a_platक्रमm_data *pdata = pchip->pdata;

	usleep_range(1000, 2000);
	/* set Filter Strength Register */
	rval = lm3630a_ग_लिखो(pchip, REG_FILTER_STRENGTH, 0x03);
	/* set Cofig. रेजिस्टर */
	rval |= lm3630a_update(pchip, REG_CONFIG, 0x07, pdata->pwm_ctrl);
	/* set boost control */
	rval |= lm3630a_ग_लिखो(pchip, REG_BOOST, 0x38);
	/* set current A */
	rval |= lm3630a_update(pchip, REG_I_A, 0x1F, 0x1F);
	/* set current B */
	rval |= lm3630a_ग_लिखो(pchip, REG_I_B, 0x1F);
	/* set control */
	rval |= lm3630a_update(pchip, REG_CTRL, 0x14, pdata->leda_ctrl);
	rval |= lm3630a_update(pchip, REG_CTRL, 0x0B, pdata->ledb_ctrl);
	usleep_range(1000, 2000);
	/* set brightness A and B */
	rval |= lm3630a_ग_लिखो(pchip, REG_BRT_A, pdata->leda_init_brt);
	rval |= lm3630a_ग_लिखो(pchip, REG_BRT_B, pdata->ledb_init_brt);

	अगर (rval < 0)
		dev_err(pchip->dev, "i2c failed to access register\n");
	वापस rval;
पूर्ण

/* पूर्णांकerrupt handling */
अटल व्योम lm3630a_delayed_func(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक rval;
	काष्ठा lm3630a_chip *pchip;

	pchip = container_of(work, काष्ठा lm3630a_chip, work.work);

	rval = lm3630a_पढ़ो(pchip, REG_INT_STATUS);
	अगर (rval < 0) अणु
		dev_err(pchip->dev,
			"i2c failed to access REG_INT_STATUS Register\n");
		वापस;
	पूर्ण

	dev_info(pchip->dev, "REG_INT_STATUS Register is 0x%x\n", rval);
पूर्ण

अटल irqवापस_t lm3630a_isr_func(पूर्णांक irq, व्योम *chip)
अणु
	पूर्णांक rval;
	काष्ठा lm3630a_chip *pchip = chip;
	अचिन्हित दीर्घ delay = msecs_to_jअगरfies(INT_DEBOUNCE_MSEC);

	queue_delayed_work(pchip->irqthपढ़ो, &pchip->work, delay);

	rval = lm3630a_update(pchip, REG_CTRL, 0x80, 0x00);
	अगर (rval < 0) अणु
		dev_err(pchip->dev, "i2c failed to access register\n");
		वापस IRQ_NONE;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक lm3630a_पूर्णांकr_config(काष्ठा lm3630a_chip *pchip)
अणु
	पूर्णांक rval;

	rval = lm3630a_ग_लिखो(pchip, REG_INT_EN, 0x87);
	अगर (rval < 0)
		वापस rval;

	INIT_DELAYED_WORK(&pchip->work, lm3630a_delayed_func);
	pchip->irqthपढ़ो = create_singlethपढ़ो_workqueue("lm3630a-irqthd");
	अगर (!pchip->irqthपढ़ो) अणु
		dev_err(pchip->dev, "create irq thread fail\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (request_thपढ़ोed_irq
	    (pchip->irq, शून्य, lm3630a_isr_func,
	     IRQF_TRIGGER_FALLING | IRQF_ONESHOT, "lm3630a_irq", pchip)) अणु
		dev_err(pchip->dev, "request threaded irq fail\n");
		destroy_workqueue(pchip->irqthपढ़ो);
		वापस -ENOMEM;
	पूर्ण
	वापस rval;
पूर्ण

अटल व्योम lm3630a_pwm_ctrl(काष्ठा lm3630a_chip *pchip, पूर्णांक br, पूर्णांक br_max)
अणु
	अचिन्हित पूर्णांक period = pchip->pdata->pwm_period;
	अचिन्हित पूर्णांक duty = br * period / br_max;

	pwm_config(pchip->pwmd, duty, period);
	अगर (duty)
		pwm_enable(pchip->pwmd);
	अन्यथा
		pwm_disable(pchip->pwmd);
पूर्ण

/* update and get brightness */
अटल पूर्णांक lm3630a_bank_a_update_status(काष्ठा backlight_device *bl)
अणु
	पूर्णांक ret;
	काष्ठा lm3630a_chip *pchip = bl_get_data(bl);
	क्रमागत lm3630a_pwm_ctrl pwm_ctrl = pchip->pdata->pwm_ctrl;

	/* pwm control */
	अगर ((pwm_ctrl & LM3630A_PWM_BANK_A) != 0) अणु
		lm3630a_pwm_ctrl(pchip, bl->props.brightness,
				 bl->props.max_brightness);
		वापस bl->props.brightness;
	पूर्ण

	/* disable sleep */
	ret = lm3630a_update(pchip, REG_CTRL, 0x80, 0x00);
	अगर (ret < 0)
		जाओ out_i2c_err;
	usleep_range(1000, 2000);
	/* minimum brightness is 0x04 */
	ret = lm3630a_ग_लिखो(pchip, REG_BRT_A, bl->props.brightness);
	अगर (bl->props.brightness < 0x4)
		ret |= lm3630a_update(pchip, REG_CTRL, LM3630A_LEDA_ENABLE, 0);
	अन्यथा
		ret |= lm3630a_update(pchip, REG_CTRL,
				      LM3630A_LEDA_ENABLE, LM3630A_LEDA_ENABLE);
	अगर (ret < 0)
		जाओ out_i2c_err;
	वापस 0;

out_i2c_err:
	dev_err(pchip->dev, "i2c failed to access\n");
	वापस bl->props.brightness;
पूर्ण

अटल पूर्णांक lm3630a_bank_a_get_brightness(काष्ठा backlight_device *bl)
अणु
	पूर्णांक brightness, rval;
	काष्ठा lm3630a_chip *pchip = bl_get_data(bl);
	क्रमागत lm3630a_pwm_ctrl pwm_ctrl = pchip->pdata->pwm_ctrl;

	अगर ((pwm_ctrl & LM3630A_PWM_BANK_A) != 0) अणु
		rval = lm3630a_पढ़ो(pchip, REG_PWM_OUTHIGH);
		अगर (rval < 0)
			जाओ out_i2c_err;
		brightness = (rval & 0x01) << 8;
		rval = lm3630a_पढ़ो(pchip, REG_PWM_OUTLOW);
		अगर (rval < 0)
			जाओ out_i2c_err;
		brightness |= rval;
		जाओ out;
	पूर्ण

	/* disable sleep */
	rval = lm3630a_update(pchip, REG_CTRL, 0x80, 0x00);
	अगर (rval < 0)
		जाओ out_i2c_err;
	usleep_range(1000, 2000);
	rval = lm3630a_पढ़ो(pchip, REG_BRT_A);
	अगर (rval < 0)
		जाओ out_i2c_err;
	brightness = rval;

out:
	bl->props.brightness = brightness;
	वापस bl->props.brightness;
out_i2c_err:
	dev_err(pchip->dev, "i2c failed to access register\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops lm3630a_bank_a_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = lm3630a_bank_a_update_status,
	.get_brightness = lm3630a_bank_a_get_brightness,
पूर्ण;

/* update and get brightness */
अटल पूर्णांक lm3630a_bank_b_update_status(काष्ठा backlight_device *bl)
अणु
	पूर्णांक ret;
	काष्ठा lm3630a_chip *pchip = bl_get_data(bl);
	क्रमागत lm3630a_pwm_ctrl pwm_ctrl = pchip->pdata->pwm_ctrl;

	/* pwm control */
	अगर ((pwm_ctrl & LM3630A_PWM_BANK_B) != 0) अणु
		lm3630a_pwm_ctrl(pchip, bl->props.brightness,
				 bl->props.max_brightness);
		वापस bl->props.brightness;
	पूर्ण

	/* disable sleep */
	ret = lm3630a_update(pchip, REG_CTRL, 0x80, 0x00);
	अगर (ret < 0)
		जाओ out_i2c_err;
	usleep_range(1000, 2000);
	/* minimum brightness is 0x04 */
	ret = lm3630a_ग_लिखो(pchip, REG_BRT_B, bl->props.brightness);
	अगर (bl->props.brightness < 0x4)
		ret |= lm3630a_update(pchip, REG_CTRL, LM3630A_LEDB_ENABLE, 0);
	अन्यथा
		ret |= lm3630a_update(pchip, REG_CTRL,
				      LM3630A_LEDB_ENABLE, LM3630A_LEDB_ENABLE);
	अगर (ret < 0)
		जाओ out_i2c_err;
	वापस 0;

out_i2c_err:
	dev_err(pchip->dev, "i2c failed to access REG_CTRL\n");
	वापस bl->props.brightness;
पूर्ण

अटल पूर्णांक lm3630a_bank_b_get_brightness(काष्ठा backlight_device *bl)
अणु
	पूर्णांक brightness, rval;
	काष्ठा lm3630a_chip *pchip = bl_get_data(bl);
	क्रमागत lm3630a_pwm_ctrl pwm_ctrl = pchip->pdata->pwm_ctrl;

	अगर ((pwm_ctrl & LM3630A_PWM_BANK_B) != 0) अणु
		rval = lm3630a_पढ़ो(pchip, REG_PWM_OUTHIGH);
		अगर (rval < 0)
			जाओ out_i2c_err;
		brightness = (rval & 0x01) << 8;
		rval = lm3630a_पढ़ो(pchip, REG_PWM_OUTLOW);
		अगर (rval < 0)
			जाओ out_i2c_err;
		brightness |= rval;
		जाओ out;
	पूर्ण

	/* disable sleep */
	rval = lm3630a_update(pchip, REG_CTRL, 0x80, 0x00);
	अगर (rval < 0)
		जाओ out_i2c_err;
	usleep_range(1000, 2000);
	rval = lm3630a_पढ़ो(pchip, REG_BRT_B);
	अगर (rval < 0)
		जाओ out_i2c_err;
	brightness = rval;

out:
	bl->props.brightness = brightness;
	वापस bl->props.brightness;
out_i2c_err:
	dev_err(pchip->dev, "i2c failed to access register\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops lm3630a_bank_b_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = lm3630a_bank_b_update_status,
	.get_brightness = lm3630a_bank_b_get_brightness,
पूर्ण;

अटल पूर्णांक lm3630a_backlight_रेजिस्टर(काष्ठा lm3630a_chip *pchip)
अणु
	काष्ठा lm3630a_platक्रमm_data *pdata = pchip->pdata;
	काष्ठा backlight_properties props;
	स्थिर अक्षर *label;

	props.type = BACKLIGHT_RAW;
	अगर (pdata->leda_ctrl != LM3630A_LEDA_DISABLE) अणु
		props.brightness = pdata->leda_init_brt;
		props.max_brightness = pdata->leda_max_brt;
		label = pdata->leda_label ? pdata->leda_label : "lm3630a_leda";
		pchip->bleda =
		    devm_backlight_device_रेजिस्टर(pchip->dev, label,
						   pchip->dev, pchip,
						   &lm3630a_bank_a_ops, &props);
		अगर (IS_ERR(pchip->bleda))
			वापस PTR_ERR(pchip->bleda);
	पूर्ण

	अगर ((pdata->ledb_ctrl != LM3630A_LEDB_DISABLE) &&
	    (pdata->ledb_ctrl != LM3630A_LEDB_ON_A)) अणु
		props.brightness = pdata->ledb_init_brt;
		props.max_brightness = pdata->ledb_max_brt;
		label = pdata->ledb_label ? pdata->ledb_label : "lm3630a_ledb";
		pchip->bledb =
		    devm_backlight_device_रेजिस्टर(pchip->dev, label,
						   pchip->dev, pchip,
						   &lm3630a_bank_b_ops, &props);
		अगर (IS_ERR(pchip->bledb))
			वापस PTR_ERR(pchip->bledb);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config lm3630a_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = REG_MAX,
पूर्ण;

अटल पूर्णांक lm3630a_parse_led_sources(काष्ठा fwnode_handle *node,
				     पूर्णांक शेष_led_sources)
अणु
	u32 sources[LM3630A_NUM_SINKS];
	पूर्णांक ret, num_sources, i;

	num_sources = fwnode_property_count_u32(node, "led-sources");
	अगर (num_sources < 0)
		वापस शेष_led_sources;
	अन्यथा अगर (num_sources > ARRAY_SIZE(sources))
		वापस -EINVAL;

	ret = fwnode_property_पढ़ो_u32_array(node, "led-sources", sources,
					     num_sources);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num_sources; i++) अणु
		अगर (sources[i] != LM3630A_SINK_0 && sources[i] != LM3630A_SINK_1)
			वापस -EINVAL;

		ret |= BIT(sources[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lm3630a_parse_bank(काष्ठा lm3630a_platक्रमm_data *pdata,
			      काष्ठा fwnode_handle *node, पूर्णांक *seen_led_sources)
अणु
	पूर्णांक led_sources, ret;
	स्थिर अक्षर *label;
	u32 bank, val;
	bool linear;

	ret = fwnode_property_पढ़ो_u32(node, "reg", &bank);
	अगर (ret)
		वापस ret;

	अगर (bank != LM3630A_BANK_0 && bank != LM3630A_BANK_1)
		वापस -EINVAL;

	led_sources = lm3630a_parse_led_sources(node, BIT(bank));
	अगर (led_sources < 0)
		वापस led_sources;

	अगर (*seen_led_sources & led_sources)
		वापस -EINVAL;

	*seen_led_sources |= led_sources;

	linear = fwnode_property_पढ़ो_bool(node,
					   "ti,linear-mapping-mode");
	अगर (bank) अणु
		अगर (led_sources & BIT(LM3630A_SINK_0) ||
		    !(led_sources & BIT(LM3630A_SINK_1)))
			वापस -EINVAL;

		pdata->ledb_ctrl = linear ?
			LM3630A_LEDB_ENABLE_LINEAR :
			LM3630A_LEDB_ENABLE;
	पूर्ण अन्यथा अणु
		अगर (!(led_sources & BIT(LM3630A_SINK_0)))
			वापस -EINVAL;

		pdata->leda_ctrl = linear ?
			LM3630A_LEDA_ENABLE_LINEAR :
			LM3630A_LEDA_ENABLE;

		अगर (led_sources & BIT(LM3630A_SINK_1))
			pdata->ledb_ctrl = LM3630A_LEDB_ON_A;
	पूर्ण

	ret = fwnode_property_पढ़ो_string(node, "label", &label);
	अगर (!ret) अणु
		अगर (bank)
			pdata->ledb_label = label;
		अन्यथा
			pdata->leda_label = label;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(node, "default-brightness",
				       &val);
	अगर (!ret) अणु
		अगर (bank)
			pdata->ledb_init_brt = val;
		अन्यथा
			pdata->leda_init_brt = val;
	पूर्ण

	ret = fwnode_property_पढ़ो_u32(node, "max-brightness", &val);
	अगर (!ret) अणु
		अगर (bank)
			pdata->ledb_max_brt = val;
		अन्यथा
			pdata->leda_max_brt = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lm3630a_parse_node(काष्ठा lm3630a_chip *pchip,
			      काष्ठा lm3630a_platक्रमm_data *pdata)
अणु
	पूर्णांक ret = -ENODEV, seen_led_sources = 0;
	काष्ठा fwnode_handle *node;

	device_क्रम_each_child_node(pchip->dev, node) अणु
		ret = lm3630a_parse_bank(pdata, node, &seen_led_sources);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lm3630a_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm3630a_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा lm3630a_chip *pchip;
	पूर्णांक rval;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "fail : i2c functionality check\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	pchip = devm_kzalloc(&client->dev, माप(काष्ठा lm3630a_chip),
			     GFP_KERNEL);
	अगर (!pchip)
		वापस -ENOMEM;
	pchip->dev = &client->dev;

	pchip->regmap = devm_regmap_init_i2c(client, &lm3630a_regmap);
	अगर (IS_ERR(pchip->regmap)) अणु
		rval = PTR_ERR(pchip->regmap);
		dev_err(&client->dev, "fail : allocate reg. map: %d\n", rval);
		वापस rval;
	पूर्ण

	i2c_set_clientdata(client, pchip);
	अगर (pdata == शून्य) अणु
		pdata = devm_kzalloc(pchip->dev,
				     माप(काष्ठा lm3630a_platक्रमm_data),
				     GFP_KERNEL);
		अगर (pdata == शून्य)
			वापस -ENOMEM;

		/* शेष values */
		pdata->leda_max_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->ledb_max_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->leda_init_brt = LM3630A_MAX_BRIGHTNESS;
		pdata->ledb_init_brt = LM3630A_MAX_BRIGHTNESS;

		rval = lm3630a_parse_node(pchip, pdata);
		अगर (rval) अणु
			dev_err(&client->dev, "fail : parse node\n");
			वापस rval;
		पूर्ण
	पूर्ण
	pchip->pdata = pdata;

	pchip->enable_gpio = devm_gpiod_get_optional(&client->dev, "enable",
						GPIOD_OUT_HIGH);
	अगर (IS_ERR(pchip->enable_gpio)) अणु
		rval = PTR_ERR(pchip->enable_gpio);
		वापस rval;
	पूर्ण

	/* chip initialize */
	rval = lm3630a_chip_init(pchip);
	अगर (rval < 0) अणु
		dev_err(&client->dev, "fail : init chip\n");
		वापस rval;
	पूर्ण
	/* backlight रेजिस्टर */
	rval = lm3630a_backlight_रेजिस्टर(pchip);
	अगर (rval < 0) अणु
		dev_err(&client->dev, "fail : backlight register.\n");
		वापस rval;
	पूर्ण
	/* pwm */
	अगर (pdata->pwm_ctrl != LM3630A_PWM_DISABLE) अणु
		pchip->pwmd = devm_pwm_get(pchip->dev, "lm3630a-pwm");
		अगर (IS_ERR(pchip->pwmd)) अणु
			dev_err(&client->dev, "fail : get pwm device\n");
			वापस PTR_ERR(pchip->pwmd);
		पूर्ण

		/*
		 * FIXME: pwm_apply_args() should be हटाओd when चयनing to
		 * the atomic PWM API.
		 */
		pwm_apply_args(pchip->pwmd);
	पूर्ण

	/* पूर्णांकerrupt enable  : irq 0 is not allowed */
	pchip->irq = client->irq;
	अगर (pchip->irq) अणु
		rval = lm3630a_पूर्णांकr_config(pchip);
		अगर (rval < 0)
			वापस rval;
	पूर्ण
	dev_info(&client->dev, "LM3630A backlight register OK.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक lm3630a_हटाओ(काष्ठा i2c_client *client)
अणु
	पूर्णांक rval;
	काष्ठा lm3630a_chip *pchip = i2c_get_clientdata(client);

	rval = lm3630a_ग_लिखो(pchip, REG_BRT_A, 0);
	अगर (rval < 0)
		dev_err(pchip->dev, "i2c failed to access register\n");

	rval = lm3630a_ग_लिखो(pchip, REG_BRT_B, 0);
	अगर (rval < 0)
		dev_err(pchip->dev, "i2c failed to access register\n");

	अगर (pchip->irq) अणु
		मुक्त_irq(pchip->irq, pchip);
		flush_workqueue(pchip->irqthपढ़ो);
		destroy_workqueue(pchip->irqthपढ़ो);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3630a_id[] = अणु
	अणुLM3630A_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lm3630a_id);

अटल स्थिर काष्ठा of_device_id lm3630a_match_table[] = अणु
	अणु .compatible = "ti,lm3630a", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, lm3630a_match_table);

अटल काष्ठा i2c_driver lm3630a_i2c_driver = अणु
	.driver = अणु
		   .name = LM3630A_NAME,
		   .of_match_table = lm3630a_match_table,
		   पूर्ण,
	.probe = lm3630a_probe,
	.हटाओ = lm3630a_हटाओ,
	.id_table = lm3630a_id,
पूर्ण;

module_i2c_driver(lm3630a_i2c_driver);

MODULE_DESCRIPTION("Texas Instruments Backlight driver for LM3630A");
MODULE_AUTHOR("Daniel Jeong <gshark.jeong@gmail.com>");
MODULE_AUTHOR("LDD MLP <ldd-mlp@list.ti.com>");
MODULE_LICENSE("GPL v2");
