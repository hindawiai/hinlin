<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP855x Backlight Driver
 *
 *			Copyright (C) 2011 Texas Instruments
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/lp855x.h>
#समावेश <linux/pwm.h>
#समावेश <linux/regulator/consumer.h>

/* LP8550/1/2/3/6 Registers */
#घोषणा LP855X_BRIGHTNESS_CTRL		0x00
#घोषणा LP855X_DEVICE_CTRL		0x01
#घोषणा LP855X_EEPROM_START		0xA0
#घोषणा LP855X_EEPROM_END		0xA7
#घोषणा LP8556_EPROM_START		0xA0
#घोषणा LP8556_EPROM_END		0xAF

/* LP8555/7 Registers */
#घोषणा LP8557_BL_CMD			0x00
#घोषणा LP8557_BL_MASK			0x01
#घोषणा LP8557_BL_ON			0x01
#घोषणा LP8557_BL_OFF			0x00
#घोषणा LP8557_BRIGHTNESS_CTRL		0x04
#घोषणा LP8557_CONFIG			0x10
#घोषणा LP8555_EPROM_START		0x10
#घोषणा LP8555_EPROM_END		0x7A
#घोषणा LP8557_EPROM_START		0x10
#घोषणा LP8557_EPROM_END		0x1E

#घोषणा DEFAULT_BL_NAME		"lcd-backlight"
#घोषणा MAX_BRIGHTNESS		255

क्रमागत lp855x_brightness_ctrl_mode अणु
	PWM_BASED = 1,
	REGISTER_BASED,
पूर्ण;

काष्ठा lp855x;

/*
 * काष्ठा lp855x_device_config
 * @pre_init_device: init device function call beक्रमe updating the brightness
 * @reg_brightness: रेजिस्टर address क्रम brigthenss control
 * @reg_devicectrl: रेजिस्टर address क्रम device control
 * @post_init_device: late init device function call
 */
काष्ठा lp855x_device_config अणु
	पूर्णांक (*pre_init_device)(काष्ठा lp855x *);
	u8 reg_brightness;
	u8 reg_devicectrl;
	पूर्णांक (*post_init_device)(काष्ठा lp855x *);
पूर्ण;

काष्ठा lp855x अणु
	स्थिर अक्षर *chipname;
	क्रमागत lp855x_chip_id chip_id;
	क्रमागत lp855x_brightness_ctrl_mode mode;
	काष्ठा lp855x_device_config *cfg;
	काष्ठा i2c_client *client;
	काष्ठा backlight_device *bl;
	काष्ठा device *dev;
	काष्ठा lp855x_platक्रमm_data *pdata;
	काष्ठा pwm_device *pwm;
	काष्ठा regulator *supply;	/* regulator क्रम VDD input */
	काष्ठा regulator *enable;	/* regulator क्रम EN/VDDIO input */
पूर्ण;

अटल पूर्णांक lp855x_ग_लिखो_byte(काष्ठा lp855x *lp, u8 reg, u8 data)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(lp->client, reg, data);
पूर्ण

अटल पूर्णांक lp855x_update_bit(काष्ठा lp855x *lp, u8 reg, u8 mask, u8 data)
अणु
	पूर्णांक ret;
	u8 पंचांगp;

	ret = i2c_smbus_पढ़ो_byte_data(lp->client, reg);
	अगर (ret < 0) अणु
		dev_err(lp->dev, "failed to read 0x%.2x\n", reg);
		वापस ret;
	पूर्ण

	पंचांगp = (u8)ret;
	पंचांगp &= ~mask;
	पंचांगp |= data & mask;

	वापस lp855x_ग_लिखो_byte(lp, reg, पंचांगp);
पूर्ण

अटल bool lp855x_is_valid_rom_area(काष्ठा lp855x *lp, u8 addr)
अणु
	u8 start, end;

	चयन (lp->chip_id) अणु
	हाल LP8550:
	हाल LP8551:
	हाल LP8552:
	हाल LP8553:
		start = LP855X_EEPROM_START;
		end = LP855X_EEPROM_END;
		अवरोध;
	हाल LP8556:
		start = LP8556_EPROM_START;
		end = LP8556_EPROM_END;
		अवरोध;
	हाल LP8555:
		start = LP8555_EPROM_START;
		end = LP8555_EPROM_END;
		अवरोध;
	हाल LP8557:
		start = LP8557_EPROM_START;
		end = LP8557_EPROM_END;
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस addr >= start && addr <= end;
पूर्ण

अटल पूर्णांक lp8557_bl_off(काष्ठा lp855x *lp)
अणु
	/* BL_ON = 0 beक्रमe updating EPROM settings */
	वापस lp855x_update_bit(lp, LP8557_BL_CMD, LP8557_BL_MASK,
				LP8557_BL_OFF);
पूर्ण

अटल पूर्णांक lp8557_bl_on(काष्ठा lp855x *lp)
अणु
	/* BL_ON = 1 after updating EPROM settings */
	वापस lp855x_update_bit(lp, LP8557_BL_CMD, LP8557_BL_MASK,
				LP8557_BL_ON);
पूर्ण

अटल काष्ठा lp855x_device_config lp855x_dev_cfg = अणु
	.reg_brightness = LP855X_BRIGHTNESS_CTRL,
	.reg_devicectrl = LP855X_DEVICE_CTRL,
पूर्ण;

अटल काष्ठा lp855x_device_config lp8557_dev_cfg = अणु
	.reg_brightness = LP8557_BRIGHTNESS_CTRL,
	.reg_devicectrl = LP8557_CONFIG,
	.pre_init_device = lp8557_bl_off,
	.post_init_device = lp8557_bl_on,
पूर्ण;

/*
 * Device specअगरic configuration flow
 *
 *    a) pre_init_device(optional)
 *    b) update the brightness रेजिस्टर
 *    c) update device control रेजिस्टर
 *    d) update ROM area(optional)
 *    e) post_init_device(optional)
 *
 */
अटल पूर्णांक lp855x_configure(काष्ठा lp855x *lp)
अणु
	u8 val, addr;
	पूर्णांक i, ret;
	काष्ठा lp855x_platक्रमm_data *pd = lp->pdata;

	चयन (lp->chip_id) अणु
	हाल LP8550:
	हाल LP8551:
	हाल LP8552:
	हाल LP8553:
	हाल LP8556:
		lp->cfg = &lp855x_dev_cfg;
		अवरोध;
	हाल LP8555:
	हाल LP8557:
		lp->cfg = &lp8557_dev_cfg;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (lp->cfg->pre_init_device) अणु
		ret = lp->cfg->pre_init_device(lp);
		अगर (ret) अणु
			dev_err(lp->dev, "pre init device err: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण

	val = pd->initial_brightness;
	ret = lp855x_ग_लिखो_byte(lp, lp->cfg->reg_brightness, val);
	अगर (ret)
		जाओ err;

	val = pd->device_control;
	ret = lp855x_ग_लिखो_byte(lp, lp->cfg->reg_devicectrl, val);
	अगर (ret)
		जाओ err;

	अगर (pd->size_program > 0) अणु
		क्रम (i = 0; i < pd->size_program; i++) अणु
			addr = pd->rom_data[i].addr;
			val = pd->rom_data[i].val;
			अगर (!lp855x_is_valid_rom_area(lp, addr))
				जारी;

			ret = lp855x_ग_लिखो_byte(lp, addr, val);
			अगर (ret)
				जाओ err;
		पूर्ण
	पूर्ण

	अगर (lp->cfg->post_init_device) अणु
		ret = lp->cfg->post_init_device(lp);
		अगर (ret) अणु
			dev_err(lp->dev, "post init device err: %d\n", ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	वापस ret;
पूर्ण

अटल व्योम lp855x_pwm_ctrl(काष्ठा lp855x *lp, पूर्णांक br, पूर्णांक max_br)
अणु
	अचिन्हित पूर्णांक period = lp->pdata->period_ns;
	अचिन्हित पूर्णांक duty = br * period / max_br;
	काष्ठा pwm_device *pwm;

	/* request pwm device with the consumer name */
	अगर (!lp->pwm) अणु
		pwm = devm_pwm_get(lp->dev, lp->chipname);
		अगर (IS_ERR(pwm))
			वापस;

		lp->pwm = pwm;

		/*
		 * FIXME: pwm_apply_args() should be हटाओd when चयनing to
		 * the atomic PWM API.
		 */
		pwm_apply_args(pwm);
	पूर्ण

	pwm_config(lp->pwm, duty, period);
	अगर (duty)
		pwm_enable(lp->pwm);
	अन्यथा
		pwm_disable(lp->pwm);
पूर्ण

अटल पूर्णांक lp855x_bl_update_status(काष्ठा backlight_device *bl)
अणु
	काष्ठा lp855x *lp = bl_get_data(bl);
	पूर्णांक brightness = bl->props.brightness;

	अगर (bl->props.state & (BL_CORE_SUSPENDED | BL_CORE_FBBLANK))
		brightness = 0;

	अगर (lp->mode == PWM_BASED)
		lp855x_pwm_ctrl(lp, brightness, bl->props.max_brightness);
	अन्यथा अगर (lp->mode == REGISTER_BASED)
		lp855x_ग_लिखो_byte(lp, lp->cfg->reg_brightness, (u8)brightness);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops lp855x_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = lp855x_bl_update_status,
पूर्ण;

अटल पूर्णांक lp855x_backlight_रेजिस्टर(काष्ठा lp855x *lp)
अणु
	काष्ठा backlight_device *bl;
	काष्ठा backlight_properties props;
	काष्ठा lp855x_platक्रमm_data *pdata = lp->pdata;
	स्थिर अक्षर *name = pdata->name ? : DEFAULT_BL_NAME;

	स_रखो(&props, 0, माप(props));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = MAX_BRIGHTNESS;

	अगर (pdata->initial_brightness > props.max_brightness)
		pdata->initial_brightness = props.max_brightness;

	props.brightness = pdata->initial_brightness;

	bl = devm_backlight_device_रेजिस्टर(lp->dev, name, lp->dev, lp,
				       &lp855x_bl_ops, &props);
	अगर (IS_ERR(bl))
		वापस PTR_ERR(bl);

	lp->bl = bl;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार lp855x_get_chip_id(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lp855x *lp = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", lp->chipname);
पूर्ण

अटल sमाप_प्रकार lp855x_get_bl_ctl_mode(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा lp855x *lp = dev_get_drvdata(dev);
	अक्षर *strmode = शून्य;

	अगर (lp->mode == PWM_BASED)
		strmode = "pwm based";
	अन्यथा अगर (lp->mode == REGISTER_BASED)
		strmode = "register based";

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", strmode);
पूर्ण

अटल DEVICE_ATTR(chip_id, S_IRUGO, lp855x_get_chip_id, शून्य);
अटल DEVICE_ATTR(bl_ctl_mode, S_IRUGO, lp855x_get_bl_ctl_mode, शून्य);

अटल काष्ठा attribute *lp855x_attributes[] = अणु
	&dev_attr_chip_id.attr,
	&dev_attr_bl_ctl_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lp855x_attr_group = अणु
	.attrs = lp855x_attributes,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल पूर्णांक lp855x_parse_dt(काष्ठा lp855x *lp)
अणु
	काष्ठा device *dev = lp->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा lp855x_platक्रमm_data *pdata;
	पूर्णांक rom_length;

	अगर (!node) अणु
		dev_err(dev, "no platform data\n");
		वापस -EINVAL;
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	of_property_पढ़ो_string(node, "bl-name", &pdata->name);
	of_property_पढ़ो_u8(node, "dev-ctrl", &pdata->device_control);
	of_property_पढ़ो_u8(node, "init-brt", &pdata->initial_brightness);
	of_property_पढ़ो_u32(node, "pwm-period", &pdata->period_ns);

	/* Fill ROM platक्रमm data अगर defined */
	rom_length = of_get_child_count(node);
	अगर (rom_length > 0) अणु
		काष्ठा lp855x_rom_data *rom;
		काष्ठा device_node *child;
		पूर्णांक i = 0;

		rom = devm_kसुस्मृति(dev, rom_length, माप(*rom), GFP_KERNEL);
		अगर (!rom)
			वापस -ENOMEM;

		क्रम_each_child_of_node(node, child) अणु
			of_property_पढ़ो_u8(child, "rom-addr", &rom[i].addr);
			of_property_पढ़ो_u8(child, "rom-val", &rom[i].val);
			i++;
		पूर्ण

		pdata->size_program = rom_length;
		pdata->rom_data = &rom[0];
	पूर्ण

	lp->pdata = pdata;

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक lp855x_parse_dt(काष्ठा lp855x *lp)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक lp855x_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lp855x *lp;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(cl->adapter, I2C_FUNC_SMBUS_I2C_BLOCK))
		वापस -EIO;

	lp = devm_kzalloc(&cl->dev, माप(काष्ठा lp855x), GFP_KERNEL);
	अगर (!lp)
		वापस -ENOMEM;

	lp->client = cl;
	lp->dev = &cl->dev;
	lp->chipname = id->name;
	lp->chip_id = id->driver_data;
	lp->pdata = dev_get_platdata(&cl->dev);

	अगर (!lp->pdata) अणु
		ret = lp855x_parse_dt(lp);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (lp->pdata->period_ns > 0)
		lp->mode = PWM_BASED;
	अन्यथा
		lp->mode = REGISTER_BASED;

	lp->supply = devm_regulator_get(lp->dev, "power");
	अगर (IS_ERR(lp->supply)) अणु
		अगर (PTR_ERR(lp->supply) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		lp->supply = शून्य;
	पूर्ण

	lp->enable = devm_regulator_get_optional(lp->dev, "enable");
	अगर (IS_ERR(lp->enable)) अणु
		ret = PTR_ERR(lp->enable);
		अगर (ret == -ENODEV) अणु
			lp->enable = शून्य;
		पूर्ण अन्यथा अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(lp->dev, "error getting enable regulator: %d\n",
					ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (lp->supply) अणु
		ret = regulator_enable(lp->supply);
		अगर (ret < 0) अणु
			dev_err(&cl->dev, "failed to enable supply: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (lp->enable) अणु
		ret = regulator_enable(lp->enable);
		अगर (ret < 0) अणु
			dev_err(lp->dev, "failed to enable vddio: %d\n", ret);
			जाओ disable_supply;
		पूर्ण

		/*
		 * LP8555 datasheet says t_RESPONSE (समय between VDDIO and
		 * I2C) is 1ms.
		 */
		usleep_range(1000, 2000);
	पूर्ण

	i2c_set_clientdata(cl, lp);

	ret = lp855x_configure(lp);
	अगर (ret) अणु
		dev_err(lp->dev, "device config err: %d", ret);
		जाओ disable_vddio;
	पूर्ण

	ret = lp855x_backlight_रेजिस्टर(lp);
	अगर (ret) अणु
		dev_err(lp->dev,
			"failed to register backlight. err: %d\n", ret);
		जाओ disable_vddio;
	पूर्ण

	ret = sysfs_create_group(&lp->dev->kobj, &lp855x_attr_group);
	अगर (ret) अणु
		dev_err(lp->dev, "failed to register sysfs. err: %d\n", ret);
		जाओ disable_vddio;
	पूर्ण

	backlight_update_status(lp->bl);

	वापस 0;

disable_vddio:
	अगर (lp->enable)
		regulator_disable(lp->enable);
disable_supply:
	अगर (lp->supply)
		regulator_disable(lp->supply);

	वापस ret;
पूर्ण

अटल पूर्णांक lp855x_हटाओ(काष्ठा i2c_client *cl)
अणु
	काष्ठा lp855x *lp = i2c_get_clientdata(cl);

	lp->bl->props.brightness = 0;
	backlight_update_status(lp->bl);
	अगर (lp->enable)
		regulator_disable(lp->enable);
	अगर (lp->supply)
		regulator_disable(lp->supply);
	sysfs_हटाओ_group(&lp->dev->kobj, &lp855x_attr_group);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id lp855x_dt_ids[] = अणु
	अणु .compatible = "ti,lp8550", पूर्ण,
	अणु .compatible = "ti,lp8551", पूर्ण,
	अणु .compatible = "ti,lp8552", पूर्ण,
	अणु .compatible = "ti,lp8553", पूर्ण,
	अणु .compatible = "ti,lp8555", पूर्ण,
	अणु .compatible = "ti,lp8556", पूर्ण,
	अणु .compatible = "ti,lp8557", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lp855x_dt_ids);

अटल स्थिर काष्ठा i2c_device_id lp855x_ids[] = अणु
	अणु"lp8550", LP8550पूर्ण,
	अणु"lp8551", LP8551पूर्ण,
	अणु"lp8552", LP8552पूर्ण,
	अणु"lp8553", LP8553पूर्ण,
	अणु"lp8555", LP8555पूर्ण,
	अणु"lp8556", LP8556पूर्ण,
	अणु"lp8557", LP8557पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp855x_ids);

अटल काष्ठा i2c_driver lp855x_driver = अणु
	.driver = अणु
		   .name = "lp855x",
		   .of_match_table = of_match_ptr(lp855x_dt_ids),
		   पूर्ण,
	.probe = lp855x_probe,
	.हटाओ = lp855x_हटाओ,
	.id_table = lp855x_ids,
पूर्ण;

module_i2c_driver(lp855x_driver);

MODULE_DESCRIPTION("Texas Instruments LP855x Backlight driver");
MODULE_AUTHOR("Milo Kim <milo.kim@ti.com>");
MODULE_LICENSE("GPL");
