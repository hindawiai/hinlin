<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Simple driver क्रम Texas Instruments LM3642 LED Flash driver chip
* Copyright (C) 2012 Texas Instruments
*/
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/fs.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_data/leds-lm3642.h>

#घोषणा	REG_FILT_TIME			(0x0)
#घोषणा	REG_IVFM_MODE			(0x1)
#घोषणा	REG_TORCH_TIME			(0x6)
#घोषणा	REG_FLASH			(0x8)
#घोषणा	REG_I_CTRL			(0x9)
#घोषणा	REG_ENABLE			(0xA)
#घोषणा	REG_FLAG			(0xB)
#घोषणा	REG_MAX				(0xB)

#घोषणा	UVLO_EN_SHIFT			(7)
#घोषणा	IVM_D_TH_SHIFT			(2)
#घोषणा	TORCH_RAMP_UP_TIME_SHIFT	(3)
#घोषणा	TORCH_RAMP_DN_TIME_SHIFT	(0)
#घोषणा	INDUCTOR_I_LIMIT_SHIFT		(6)
#घोषणा	FLASH_RAMP_TIME_SHIFT		(3)
#घोषणा	FLASH_TOUT_TIME_SHIFT		(0)
#घोषणा	TORCH_I_SHIFT			(4)
#घोषणा	FLASH_I_SHIFT			(0)
#घोषणा	IVFM_SHIFT			(7)
#घोषणा	TX_PIN_EN_SHIFT			(6)
#घोषणा	STROBE_PIN_EN_SHIFT		(5)
#घोषणा	TORCH_PIN_EN_SHIFT		(4)
#घोषणा	MODE_BITS_SHIFT			(0)

#घोषणा	UVLO_EN_MASK			(0x1)
#घोषणा	IVM_D_TH_MASK			(0x7)
#घोषणा	TORCH_RAMP_UP_TIME_MASK		(0x7)
#घोषणा	TORCH_RAMP_DN_TIME_MASK		(0x7)
#घोषणा	INDUCTOR_I_LIMIT_MASK		(0x1)
#घोषणा	FLASH_RAMP_TIME_MASK		(0x7)
#घोषणा	FLASH_TOUT_TIME_MASK		(0x7)
#घोषणा	TORCH_I_MASK			(0x7)
#घोषणा	FLASH_I_MASK			(0xF)
#घोषणा	IVFM_MASK			(0x1)
#घोषणा	TX_PIN_EN_MASK			(0x1)
#घोषणा	STROBE_PIN_EN_MASK		(0x1)
#घोषणा	TORCH_PIN_EN_MASK		(0x1)
#घोषणा	MODE_BITS_MASK			(0x73)
#घोषणा EX_PIN_CONTROL_MASK		(0x71)
#घोषणा EX_PIN_ENABLE_MASK		(0x70)

क्रमागत lm3642_mode अणु
	MODES_STASNDBY = 0,
	MODES_INDIC,
	MODES_TORCH,
	MODES_FLASH
पूर्ण;

काष्ठा lm3642_chip_data अणु
	काष्ठा device *dev;

	काष्ठा led_classdev cdev_flash;
	काष्ठा led_classdev cdev_torch;
	काष्ठा led_classdev cdev_indicator;

	u8 br_flash;
	u8 br_torch;
	u8 br_indicator;

	क्रमागत lm3642_torch_pin_enable torch_pin;
	क्रमागत lm3642_strobe_pin_enable strobe_pin;
	क्रमागत lm3642_tx_pin_enable tx_pin;

	काष्ठा lm3642_platक्रमm_data *pdata;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;

	अचिन्हित पूर्णांक last_flag;
पूर्ण;

/* chip initialize */
अटल पूर्णांक lm3642_chip_init(काष्ठा lm3642_chip_data *chip)
अणु
	पूर्णांक ret;
	काष्ठा lm3642_platक्रमm_data *pdata = chip->pdata;

	/* set enable रेजिस्टर */
	ret = regmap_update_bits(chip->regmap, REG_ENABLE, EX_PIN_ENABLE_MASK,
				 pdata->tx_pin);
	अगर (ret < 0)
		dev_err(chip->dev, "Failed to update REG_ENABLE Register\n");
	वापस ret;
पूर्ण

/* chip control */
अटल पूर्णांक lm3642_control(काष्ठा lm3642_chip_data *chip,
			  u8 brightness, क्रमागत lm3642_mode opmode)
अणु
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, REG_FLAG, &chip->last_flag);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to read REG_FLAG Register\n");
		वापस ret;
	पूर्ण

	अगर (chip->last_flag)
		dev_info(chip->dev, "Last FLAG is 0x%x\n", chip->last_flag);

	/* brightness 0 means off-state */
	अगर (!brightness)
		opmode = MODES_STASNDBY;

	चयन (opmode) अणु
	हाल MODES_TORCH:
		ret = regmap_update_bits(chip->regmap, REG_I_CTRL,
					 TORCH_I_MASK << TORCH_I_SHIFT,
					 (brightness - 1) << TORCH_I_SHIFT);

		अगर (chip->torch_pin)
			opmode |= (TORCH_PIN_EN_MASK << TORCH_PIN_EN_SHIFT);
		अवरोध;

	हाल MODES_FLASH:
		ret = regmap_update_bits(chip->regmap, REG_I_CTRL,
					 FLASH_I_MASK << FLASH_I_SHIFT,
					 (brightness - 1) << FLASH_I_SHIFT);

		अगर (chip->strobe_pin)
			opmode |= (STROBE_PIN_EN_MASK << STROBE_PIN_EN_SHIFT);
		अवरोध;

	हाल MODES_INDIC:
		ret = regmap_update_bits(chip->regmap, REG_I_CTRL,
					 TORCH_I_MASK << TORCH_I_SHIFT,
					 (brightness - 1) << TORCH_I_SHIFT);
		अवरोध;

	हाल MODES_STASNDBY:

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(chip->dev, "Failed to write REG_I_CTRL Register\n");
		वापस ret;
	पूर्ण

	अगर (chip->tx_pin)
		opmode |= (TX_PIN_EN_MASK << TX_PIN_EN_SHIFT);

	ret = regmap_update_bits(chip->regmap, REG_ENABLE,
				 MODE_BITS_MASK << MODE_BITS_SHIFT,
				 opmode << MODE_BITS_SHIFT);
	वापस ret;
पूर्ण

/* torch */

/* torch pin config क्रम lm3642 */
अटल sमाप_प्रकार torch_pin_store(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार ret;
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3642_chip_data *chip =
	    container_of(led_cdev, काष्ठा lm3642_chip_data, cdev_indicator);
	अचिन्हित पूर्णांक state;

	ret = kstrtouपूर्णांक(buf, 10, &state);
	अगर (ret)
		वापस ret;
	अगर (state != 0)
		state = 0x01 << TORCH_PIN_EN_SHIFT;

	chip->torch_pin = state;
	ret = regmap_update_bits(chip->regmap, REG_ENABLE,
				 TORCH_PIN_EN_MASK << TORCH_PIN_EN_SHIFT,
				 state);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s:i2c access fail to register\n", __func__);
		वापस ret;
	पूर्ण

	वापस size;
पूर्ण

अटल DEVICE_ATTR_WO(torch_pin);

अटल पूर्णांक lm3642_torch_brightness_set(काष्ठा led_classdev *cdev,
					क्रमागत led_brightness brightness)
अणु
	काष्ठा lm3642_chip_data *chip =
	    container_of(cdev, काष्ठा lm3642_chip_data, cdev_torch);
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	chip->br_torch = brightness;
	ret = lm3642_control(chip, chip->br_torch, MODES_TORCH);
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

/* flash */

/* strobe pin config क्रम lm3642*/
अटल sमाप_प्रकार strobe_pin_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार ret;
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm3642_chip_data *chip =
	    container_of(led_cdev, काष्ठा lm3642_chip_data, cdev_indicator);
	अचिन्हित पूर्णांक state;

	ret = kstrtouपूर्णांक(buf, 10, &state);
	अगर (ret)
		वापस ret;
	अगर (state != 0)
		state = 0x01 << STROBE_PIN_EN_SHIFT;

	chip->strobe_pin = state;
	ret = regmap_update_bits(chip->regmap, REG_ENABLE,
				 STROBE_PIN_EN_MASK << STROBE_PIN_EN_SHIFT,
				 state);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "%s:i2c access fail to register\n", __func__);
		वापस ret;
	पूर्ण

	वापस size;
पूर्ण

अटल DEVICE_ATTR_WO(strobe_pin);

अटल पूर्णांक lm3642_strobe_brightness_set(काष्ठा led_classdev *cdev,
					 क्रमागत led_brightness brightness)
अणु
	काष्ठा lm3642_chip_data *chip =
	    container_of(cdev, काष्ठा lm3642_chip_data, cdev_flash);
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	chip->br_flash = brightness;
	ret = lm3642_control(chip, chip->br_flash, MODES_FLASH);
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

/* indicator */
अटल पूर्णांक lm3642_indicator_brightness_set(काष्ठा led_classdev *cdev,
					    क्रमागत led_brightness brightness)
अणु
	काष्ठा lm3642_chip_data *chip =
	    container_of(cdev, काष्ठा lm3642_chip_data, cdev_indicator);
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	chip->br_indicator = brightness;
	ret = lm3642_control(chip, chip->br_indicator, MODES_INDIC);
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा regmap_config lm3642_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = REG_MAX,
पूर्ण;

अटल काष्ठा attribute *lm3642_flash_attrs[] = अणु
	&dev_attr_strobe_pin.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm3642_flash);

अटल काष्ठा attribute *lm3642_torch_attrs[] = अणु
	&dev_attr_torch_pin.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm3642_torch);

अटल पूर्णांक lm3642_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm3642_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा lm3642_chip_data *chip;

	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) अणु
		dev_err(&client->dev, "i2c functionality check fail.\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (pdata == शून्य) अणु
		dev_err(&client->dev, "needs Platform Data.\n");
		वापस -ENODATA;
	पूर्ण

	chip = devm_kzalloc(&client->dev,
			    माप(काष्ठा lm3642_chip_data), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = &client->dev;
	chip->pdata = pdata;

	chip->tx_pin = pdata->tx_pin;
	chip->torch_pin = pdata->torch_pin;
	chip->strobe_pin = pdata->strobe_pin;

	chip->regmap = devm_regmap_init_i2c(client, &lm3642_regmap);
	अगर (IS_ERR(chip->regmap)) अणु
		err = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			err);
		वापस err;
	पूर्ण

	mutex_init(&chip->lock);
	i2c_set_clientdata(client, chip);

	err = lm3642_chip_init(chip);
	अगर (err < 0)
		जाओ err_out;

	/* flash */
	chip->cdev_flash.name = "flash";
	chip->cdev_flash.max_brightness = 16;
	chip->cdev_flash.brightness_set_blocking = lm3642_strobe_brightness_set;
	chip->cdev_flash.शेष_trigger = "flash";
	chip->cdev_flash.groups = lm3642_flash_groups;
	err = led_classdev_रेजिस्टर(&client->dev, &chip->cdev_flash);
	अगर (err < 0) अणु
		dev_err(chip->dev, "failed to register flash\n");
		जाओ err_out;
	पूर्ण

	/* torch */
	chip->cdev_torch.name = "torch";
	chip->cdev_torch.max_brightness = 8;
	chip->cdev_torch.brightness_set_blocking = lm3642_torch_brightness_set;
	chip->cdev_torch.शेष_trigger = "torch";
	chip->cdev_torch.groups = lm3642_torch_groups;
	err = led_classdev_रेजिस्टर(&client->dev, &chip->cdev_torch);
	अगर (err < 0) अणु
		dev_err(chip->dev, "failed to register torch\n");
		जाओ err_create_torch_file;
	पूर्ण

	/* indicator */
	chip->cdev_indicator.name = "indicator";
	chip->cdev_indicator.max_brightness = 8;
	chip->cdev_indicator.brightness_set_blocking =
						lm3642_indicator_brightness_set;
	err = led_classdev_रेजिस्टर(&client->dev, &chip->cdev_indicator);
	अगर (err < 0) अणु
		dev_err(chip->dev, "failed to register indicator\n");
		जाओ err_create_indicator_file;
	पूर्ण

	dev_info(&client->dev, "LM3642 is initialized\n");
	वापस 0;

err_create_indicator_file:
	led_classdev_unरेजिस्टर(&chip->cdev_torch);
err_create_torch_file:
	led_classdev_unरेजिस्टर(&chip->cdev_flash);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक lm3642_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm3642_chip_data *chip = i2c_get_clientdata(client);

	led_classdev_unरेजिस्टर(&chip->cdev_indicator);
	led_classdev_unरेजिस्टर(&chip->cdev_torch);
	led_classdev_unरेजिस्टर(&chip->cdev_flash);
	regmap_ग_लिखो(chip->regmap, REG_ENABLE, 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm3642_id[] = अणु
	अणुLM3642_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lm3642_id);

अटल काष्ठा i2c_driver lm3642_i2c_driver = अणु
	.driver = अणु
		   .name = LM3642_NAME,
		   .pm = शून्य,
		   पूर्ण,
	.probe = lm3642_probe,
	.हटाओ = lm3642_हटाओ,
	.id_table = lm3642_id,
पूर्ण;

module_i2c_driver(lm3642_i2c_driver);

MODULE_DESCRIPTION("Texas Instruments Flash Lighting driver for LM3642");
MODULE_AUTHOR("Daniel Jeong <daniel.jeong@ti.com>");
MODULE_AUTHOR("G.Shark Jeong <gshark.jeong@gmail.com>");
MODULE_LICENSE("GPL v2");
