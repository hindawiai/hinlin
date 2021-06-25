<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Simple driver क्रम Texas Instruments LM3639 Backlight + Flash LED driver chip
* Copyright (C) 2012 Texas Instruments
*/
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_data/lm3639_bl.h>

#घोषणा REG_DEV_ID	0x00
#घोषणा REG_CHECKSUM	0x01
#घोषणा REG_BL_CONF_1	0x02
#घोषणा REG_BL_CONF_2	0x03
#घोषणा REG_BL_CONF_3	0x04
#घोषणा REG_BL_CONF_4	0x05
#घोषणा REG_FL_CONF_1	0x06
#घोषणा REG_FL_CONF_2	0x07
#घोषणा REG_FL_CONF_3	0x08
#घोषणा REG_IO_CTRL	0x09
#घोषणा REG_ENABLE	0x0A
#घोषणा REG_FLAG	0x0B
#घोषणा REG_MAX		REG_FLAG

काष्ठा lm3639_chip_data अणु
	काष्ठा device *dev;
	काष्ठा lm3639_platक्रमm_data *pdata;

	काष्ठा backlight_device *bled;
	काष्ठा led_classdev cdev_flash;
	काष्ठा led_classdev cdev_torch;
	काष्ठा regmap *regmap;

	अचिन्हित पूर्णांक bled_mode;
	अचिन्हित पूर्णांक bled_map;
	अचिन्हित पूर्णांक last_flag;
पूर्ण;

/* initialize chip */
अटल पूर्णांक lm3639_chip_init(काष्ठा lm3639_chip_data *pchip)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	काष्ठा lm3639_platक्रमm_data *pdata = pchip->pdata;

	/* input pins config. */
	ret =
	    regmap_update_bits(pchip->regmap, REG_BL_CONF_1, 0x08,
			       pdata->pin_pwm);
	अगर (ret < 0)
		जाओ out;

	reg_val = (pdata->pin_pwm & 0x40) | pdata->pin_strobe | pdata->pin_tx;
	ret = regmap_update_bits(pchip->regmap, REG_IO_CTRL, 0x7C, reg_val);
	अगर (ret < 0)
		जाओ out;

	/* init brightness */
	ret = regmap_ग_लिखो(pchip->regmap, REG_BL_CONF_4, pdata->init_brt_led);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_ग_लिखो(pchip->regmap, REG_BL_CONF_3, pdata->init_brt_led);
	अगर (ret < 0)
		जाओ out;

	/* output pins config. */
	अगर (!pdata->init_brt_led) अणु
		reg_val = pdata->fled_pins;
		reg_val |= pdata->bled_pins;
	पूर्ण अन्यथा अणु
		reg_val = pdata->fled_pins;
		reg_val |= pdata->bled_pins | 0x01;
	पूर्ण

	ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x79, reg_val);
	अगर (ret < 0)
		जाओ out;

	वापस ret;
out:
	dev_err(pchip->dev, "i2c failed to access register\n");
	वापस ret;
पूर्ण

/* update and get brightness */
अटल पूर्णांक lm3639_bled_update_status(काष्ठा backlight_device *bl)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	काष्ठा lm3639_chip_data *pchip = bl_get_data(bl);
	काष्ठा lm3639_platक्रमm_data *pdata = pchip->pdata;

	ret = regmap_पढ़ो(pchip->regmap, REG_FLAG, &reg_val);
	अगर (ret < 0)
		जाओ out;

	अगर (reg_val != 0)
		dev_info(pchip->dev, "last flag is 0x%x\n", reg_val);

	/* pwm control */
	अगर (pdata->pin_pwm) अणु
		अगर (pdata->pwm_set_पूर्णांकensity)
			pdata->pwm_set_पूर्णांकensity(bl->props.brightness,
						 pdata->max_brt_led);
		अन्यथा
			dev_err(pchip->dev,
				"No pwm control func. in plat-data\n");
		वापस bl->props.brightness;
	पूर्ण

	/* i2c control and set brigtness */
	ret = regmap_ग_लिखो(pchip->regmap, REG_BL_CONF_4, bl->props.brightness);
	अगर (ret < 0)
		जाओ out;
	ret = regmap_ग_लिखो(pchip->regmap, REG_BL_CONF_3, bl->props.brightness);
	अगर (ret < 0)
		जाओ out;

	अगर (!bl->props.brightness)
		ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x01, 0x00);
	अन्यथा
		ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x01, 0x01);
	अगर (ret < 0)
		जाओ out;

	वापस bl->props.brightness;
out:
	dev_err(pchip->dev, "i2c failed to access registers\n");
	वापस bl->props.brightness;
पूर्ण

अटल पूर्णांक lm3639_bled_get_brightness(काष्ठा backlight_device *bl)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	काष्ठा lm3639_chip_data *pchip = bl_get_data(bl);
	काष्ठा lm3639_platक्रमm_data *pdata = pchip->pdata;

	अगर (pdata->pin_pwm) अणु
		अगर (pdata->pwm_get_पूर्णांकensity)
			bl->props.brightness = pdata->pwm_get_पूर्णांकensity();
		अन्यथा
			dev_err(pchip->dev,
				"No pwm control func. in plat-data\n");
		वापस bl->props.brightness;
	पूर्ण

	ret = regmap_पढ़ो(pchip->regmap, REG_BL_CONF_1, &reg_val);
	अगर (ret < 0)
		जाओ out;
	अगर (reg_val & 0x10)
		ret = regmap_पढ़ो(pchip->regmap, REG_BL_CONF_4, &reg_val);
	अन्यथा
		ret = regmap_पढ़ो(pchip->regmap, REG_BL_CONF_3, &reg_val);
	अगर (ret < 0)
		जाओ out;
	bl->props.brightness = reg_val;

	वापस bl->props.brightness;
out:
	dev_err(pchip->dev, "i2c failed to access register\n");
	वापस bl->props.brightness;
पूर्ण

अटल स्थिर काष्ठा backlight_ops lm3639_bled_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status = lm3639_bled_update_status,
	.get_brightness = lm3639_bled_get_brightness,
पूर्ण;

/* backlight mapping mode */
अटल sमाप_प्रकार lm3639_bled_mode_store(काष्ठा device *dev,
				      काष्ठा device_attribute *devAttr,
				      स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार ret;
	काष्ठा lm3639_chip_data *pchip = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक state;

	ret = kstrtouपूर्णांक(buf, 10, &state);
	अगर (ret)
		जाओ out_input;

	अगर (!state)
		ret =
		    regmap_update_bits(pchip->regmap, REG_BL_CONF_1, 0x10,
				       0x00);
	अन्यथा
		ret =
		    regmap_update_bits(pchip->regmap, REG_BL_CONF_1, 0x10,
				       0x10);

	अगर (ret < 0)
		जाओ out;

	वापस size;

out:
	dev_err(pchip->dev, "%s:i2c access fail to register\n", __func__);
	वापस ret;

out_input:
	dev_err(pchip->dev, "%s:input conversion fail\n", __func__);
	वापस ret;

पूर्ण

अटल DEVICE_ATTR(bled_mode, S_IWUSR, शून्य, lm3639_bled_mode_store);

/* torch */
अटल व्योम lm3639_torch_brightness_set(काष्ठा led_classdev *cdev,
					क्रमागत led_brightness brightness)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	काष्ठा lm3639_chip_data *pchip;

	pchip = container_of(cdev, काष्ठा lm3639_chip_data, cdev_torch);

	ret = regmap_पढ़ो(pchip->regmap, REG_FLAG, &reg_val);
	अगर (ret < 0)
		जाओ out;
	अगर (reg_val != 0)
		dev_info(pchip->dev, "last flag is 0x%x\n", reg_val);

	/* brightness 0 means off state */
	अगर (!brightness) अणु
		ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x06, 0x00);
		अगर (ret < 0)
			जाओ out;
		वापस;
	पूर्ण

	ret = regmap_update_bits(pchip->regmap,
				 REG_FL_CONF_1, 0x70, (brightness - 1) << 4);
	अगर (ret < 0)
		जाओ out;
	ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x06, 0x02);
	अगर (ret < 0)
		जाओ out;

	वापस;
out:
	dev_err(pchip->dev, "i2c failed to access register\n");
पूर्ण

/* flash */
अटल व्योम lm3639_flash_brightness_set(काष्ठा led_classdev *cdev,
					क्रमागत led_brightness brightness)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	काष्ठा lm3639_chip_data *pchip;

	pchip = container_of(cdev, काष्ठा lm3639_chip_data, cdev_flash);

	ret = regmap_पढ़ो(pchip->regmap, REG_FLAG, &reg_val);
	अगर (ret < 0)
		जाओ out;
	अगर (reg_val != 0)
		dev_info(pchip->dev, "last flag is 0x%x\n", reg_val);

	/* torch off beक्रमe flash control */
	ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x06, 0x00);
	अगर (ret < 0)
		जाओ out;

	/* brightness 0 means off state */
	अगर (!brightness)
		वापस;

	ret = regmap_update_bits(pchip->regmap,
				 REG_FL_CONF_1, 0x0F, brightness - 1);
	अगर (ret < 0)
		जाओ out;
	ret = regmap_update_bits(pchip->regmap, REG_ENABLE, 0x06, 0x06);
	अगर (ret < 0)
		जाओ out;

	वापस;
out:
	dev_err(pchip->dev, "i2c failed to access register\n");
पूर्ण

अटल स्थिर काष्ठा regmap_config lm3639_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = REG_MAX,
पूर्ण;

अटल पूर्णांक lm3639_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा lm3639_chip_data *pchip;
	काष्ठा lm3639_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा backlight_properties props;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "i2c functionality check fail.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "Needs Platform Data.\n");
		वापस -ENODATA;
	पूर्ण

	pchip = devm_kzalloc(&client->dev,
			     माप(काष्ठा lm3639_chip_data), GFP_KERNEL);
	अगर (!pchip)
		वापस -ENOMEM;

	pchip->pdata = pdata;
	pchip->dev = &client->dev;

	pchip->regmap = devm_regmap_init_i2c(client, &lm3639_regmap);
	अगर (IS_ERR(pchip->regmap)) अणु
		ret = PTR_ERR(pchip->regmap);
		dev_err(&client->dev, "fail : allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण
	i2c_set_clientdata(client, pchip);

	/* chip initialize */
	ret = lm3639_chip_init(pchip);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "fail : chip init\n");
		जाओ err_out;
	पूर्ण

	/* backlight */
	props.type = BACKLIGHT_RAW;
	props.brightness = pdata->init_brt_led;
	props.max_brightness = pdata->max_brt_led;
	pchip->bled =
	    devm_backlight_device_रेजिस्टर(pchip->dev, "lm3639_bled",
					   pchip->dev, pchip, &lm3639_bled_ops,
					   &props);
	अगर (IS_ERR(pchip->bled)) अणु
		dev_err(&client->dev, "fail : backlight register\n");
		ret = PTR_ERR(pchip->bled);
		जाओ err_out;
	पूर्ण

	ret = device_create_file(&(pchip->bled->dev), &dev_attr_bled_mode);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed : add sysfs entries\n");
		जाओ err_out;
	पूर्ण

	/* flash */
	pchip->cdev_flash.name = "lm3639_flash";
	pchip->cdev_flash.max_brightness = 16;
	pchip->cdev_flash.brightness_set = lm3639_flash_brightness_set;
	ret = led_classdev_रेजिस्टर((काष्ठा device *)
				    &client->dev, &pchip->cdev_flash);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "fail : flash register\n");
		जाओ err_flash;
	पूर्ण

	/* torch */
	pchip->cdev_torch.name = "lm3639_torch";
	pchip->cdev_torch.max_brightness = 8;
	pchip->cdev_torch.brightness_set = lm3639_torch_brightness_set;
	ret = led_classdev_रेजिस्टर((काष्ठा device *)
				    &client->dev, &pchip->cdev_torch);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "fail : torch register\n");
		जाओ err_torch;
	पूर्ण

	वापस 0;

err_torch:
	led_classdev_unरेजिस्टर(&pchip->cdev_flash);
err_flash:
	device_हटाओ_file(&(pchip->bled->dev), &dev_attr_bled_mode);
err_out:
	वापस ret;
पूर्ण

अटल पूर्णांक lm3639_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3639_chip_data *pchip = i2c_get_clientdata(client);

	regmap_ग_लिखो(pchip->regmap, REG_ENABLE, 0x00);

	led_classdev_unरेजिस्टर(&pchip->cdev_torch);
	led_classdev_unरेजिस्टर(&pchip->cdev_flash);
	अगर (pchip->bled)
		device_हटाओ_file(&(pchip->bled->dev), &dev_attr_bled_mode);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3639_id[] = अणु
	अणुLM3639_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lm3639_id);
अटल काष्ठा i2c_driver lm3639_i2c_driver = अणु
	.driver = अणु
		   .name = LM3639_NAME,
		   पूर्ण,
	.probe = lm3639_probe,
	.हटाओ = lm3639_हटाओ,
	.id_table = lm3639_id,
पूर्ण;

module_i2c_driver(lm3639_i2c_driver);

MODULE_DESCRIPTION("Texas Instruments Backlight+Flash LED driver for LM3639");
MODULE_AUTHOR("Daniel Jeong <gshark.jeong@gmail.com>");
MODULE_AUTHOR("Ldd Mlp <ldd-mlp@list.ti.com>");
MODULE_LICENSE("GPL v2");
