<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
* Simple driver क्रम Texas Instruments LM355x LED Flash driver chip
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
#समावेश <linux/platक्रमm_data/leds-lm355x.h>

क्रमागत lm355x_type अणु
	CHIP_LM3554 = 0,
	CHIP_LM3556,
पूर्ण;

क्रमागत lm355x_regs अणु
	REG_FLAG = 0,
	REG_TORCH_CFG,
	REG_TORCH_CTRL,
	REG_STROBE_CFG,
	REG_FLASH_CTRL,
	REG_INDI_CFG,
	REG_INDI_CTRL,
	REG_OPMODE,
	REG_MAX,
पूर्ण;

/* operation mode */
क्रमागत lm355x_mode अणु
	MODE_SHDN = 0,
	MODE_INDIC,
	MODE_TORCH,
	MODE_FLASH
पूर्ण;

/* रेजिस्टर map info. */
काष्ठा lm355x_reg_data अणु
	u8 regno;
	u8 mask;
	u8 shअगरt;
पूर्ण;

काष्ठा lm355x_chip_data अणु
	काष्ठा device *dev;
	क्रमागत lm355x_type type;

	काष्ठा led_classdev cdev_flash;
	काष्ठा led_classdev cdev_torch;
	काष्ठा led_classdev cdev_indicator;

	काष्ठा lm355x_platक्रमm_data *pdata;
	काष्ठा regmap *regmap;
	काष्ठा mutex lock;

	अचिन्हित पूर्णांक last_flag;
	काष्ठा lm355x_reg_data *regs;
पूर्ण;

/* specअगरic indicator function क्रम lm3556 */
क्रमागत lm3556_indic_pulse_समय अणु
	PULSE_TIME_0_MS = 0,
	PULSE_TIME_32_MS,
	PULSE_TIME_64_MS,
	PULSE_TIME_92_MS,
	PULSE_TIME_128_MS,
	PULSE_TIME_160_MS,
	PULSE_TIME_196_MS,
	PULSE_TIME_224_MS,
	PULSE_TIME_256_MS,
	PULSE_TIME_288_MS,
	PULSE_TIME_320_MS,
	PULSE_TIME_352_MS,
	PULSE_TIME_384_MS,
	PULSE_TIME_416_MS,
	PULSE_TIME_448_MS,
	PULSE_TIME_480_MS,
पूर्ण;

क्रमागत lm3556_indic_n_blank अणु
	INDIC_N_BLANK_0 = 0,
	INDIC_N_BLANK_1,
	INDIC_N_BLANK_2,
	INDIC_N_BLANK_3,
	INDIC_N_BLANK_4,
	INDIC_N_BLANK_5,
	INDIC_N_BLANK_6,
	INDIC_N_BLANK_7,
	INDIC_N_BLANK_8,
	INDIC_N_BLANK_9,
	INDIC_N_BLANK_10,
	INDIC_N_BLANK_11,
	INDIC_N_BLANK_12,
	INDIC_N_BLANK_13,
	INDIC_N_BLANK_14,
	INDIC_N_BLANK_15,
पूर्ण;

क्रमागत lm3556_indic_period अणु
	INDIC_PERIOD_0 = 0,
	INDIC_PERIOD_1,
	INDIC_PERIOD_2,
	INDIC_PERIOD_3,
	INDIC_PERIOD_4,
	INDIC_PERIOD_5,
	INDIC_PERIOD_6,
	INDIC_PERIOD_7,
पूर्ण;

#घोषणा INDIC_PATTERN_SIZE 4

काष्ठा indicator अणु
	u8 blinking;
	u8 period_cnt;
पूर्ण;

/* indicator pattern data only क्रम lm3556 */
अटल काष्ठा indicator indicator_pattern[INDIC_PATTERN_SIZE] = अणु
	[0] = अणु(INDIC_N_BLANK_1 << 4) | PULSE_TIME_32_MS, INDIC_PERIOD_1पूर्ण,
	[1] = अणु(INDIC_N_BLANK_15 << 4) | PULSE_TIME_32_MS, INDIC_PERIOD_2पूर्ण,
	[2] = अणु(INDIC_N_BLANK_10 << 4) | PULSE_TIME_32_MS, INDIC_PERIOD_4पूर्ण,
	[3] = अणु(INDIC_N_BLANK_5 << 4) | PULSE_TIME_32_MS, INDIC_PERIOD_7पूर्ण,
पूर्ण;

अटल काष्ठा lm355x_reg_data lm3554_regs[REG_MAX] = अणु
	[REG_FLAG] = अणु0xD0, 0xBF, 0पूर्ण,
	[REG_TORCH_CFG] = अणु0xE0, 0x80, 7पूर्ण,
	[REG_TORCH_CTRL] = अणु0xA0, 0x38, 3पूर्ण,
	[REG_STROBE_CFG] = अणु0xE0, 0x04, 2पूर्ण,
	[REG_FLASH_CTRL] = अणु0xB0, 0x78, 3पूर्ण,
	[REG_INDI_CFG] = अणु0xE0, 0x08, 3पूर्ण,
	[REG_INDI_CTRL] = अणु0xA0, 0xC0, 6पूर्ण,
	[REG_OPMODE] = अणु0xA0, 0x03, 0पूर्ण,
पूर्ण;

अटल काष्ठा lm355x_reg_data lm3556_regs[REG_MAX] = अणु
	[REG_FLAG] = अणु0x0B, 0xFF, 0पूर्ण,
	[REG_TORCH_CFG] = अणु0x0A, 0x10, 4पूर्ण,
	[REG_TORCH_CTRL] = अणु0x09, 0x70, 4पूर्ण,
	[REG_STROBE_CFG] = अणु0x0A, 0x20, 5पूर्ण,
	[REG_FLASH_CTRL] = अणु0x09, 0x0F, 0पूर्ण,
	[REG_INDI_CFG] = अणु0xFF, 0xFF, 0पूर्ण,
	[REG_INDI_CTRL] = अणु0x09, 0x70, 4पूर्ण,
	[REG_OPMODE] = अणु0x0A, 0x03, 0पूर्ण,
पूर्ण;

अटल अक्षर lm355x_name[][I2C_NAME_SIZE] = अणु
	[CHIP_LM3554] = LM3554_NAME,
	[CHIP_LM3556] = LM3556_NAME,
पूर्ण;

/* chip initialize */
अटल पूर्णांक lm355x_chip_init(काष्ठा lm355x_chip_data *chip)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	काष्ठा lm355x_platक्रमm_data *pdata = chip->pdata;

	/* input and output pins configuration */
	चयन (chip->type) अणु
	हाल CHIP_LM3554:
		reg_val = (u32)pdata->pin_tx2 | (u32)pdata->ntc_pin;
		ret = regmap_update_bits(chip->regmap, 0xE0, 0x28, reg_val);
		अगर (ret < 0)
			जाओ out;
		reg_val = (u32)pdata->pass_mode;
		ret = regmap_update_bits(chip->regmap, 0xA0, 0x04, reg_val);
		अगर (ret < 0)
			जाओ out;
		अवरोध;

	हाल CHIP_LM3556:
		reg_val = (u32)pdata->pin_tx2 | (u32)pdata->ntc_pin |
		          (u32)pdata->pass_mode;
		ret = regmap_update_bits(chip->regmap, 0x0A, 0xC4, reg_val);
		अगर (ret < 0)
			जाओ out;
		अवरोध;
	शेष:
		वापस -ENODATA;
	पूर्ण

	वापस ret;
out:
	dev_err(chip->dev, "%s:i2c access fail to register\n", __func__);
	वापस ret;
पूर्ण

/* chip control */
अटल पूर्णांक lm355x_control(काष्ठा lm355x_chip_data *chip,
			   u8 brightness, क्रमागत lm355x_mode opmode)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg_val;
	काष्ठा lm355x_platक्रमm_data *pdata = chip->pdata;
	काष्ठा lm355x_reg_data *preg = chip->regs;

	ret = regmap_पढ़ो(chip->regmap, preg[REG_FLAG].regno, &chip->last_flag);
	अगर (ret < 0)
		जाओ out;
	अगर (chip->last_flag & preg[REG_FLAG].mask)
		dev_info(chip->dev, "%s Last FLAG is 0x%x\n",
			 lm355x_name[chip->type],
			 chip->last_flag & preg[REG_FLAG].mask);
	/* brightness 0 means shutकरोwn */
	अगर (!brightness)
		opmode = MODE_SHDN;

	चयन (opmode) अणु
	हाल MODE_TORCH:
		ret =
		    regmap_update_bits(chip->regmap, preg[REG_TORCH_CTRL].regno,
				       preg[REG_TORCH_CTRL].mask,
				       (brightness - 1)
				       << preg[REG_TORCH_CTRL].shअगरt);
		अगर (ret < 0)
			जाओ out;

		अगर (pdata->pin_tx1 != LM355x_PIN_TORCH_DISABLE) अणु
			ret =
			    regmap_update_bits(chip->regmap,
					       preg[REG_TORCH_CFG].regno,
					       preg[REG_TORCH_CFG].mask,
					       0x01 <<
					       preg[REG_TORCH_CFG].shअगरt);
			अगर (ret < 0)
				जाओ out;
			opmode = MODE_SHDN;
			dev_info(chip->dev,
				 "torch brt is set - ext. torch pin mode\n");
		पूर्ण
		अवरोध;

	हाल MODE_FLASH:

		ret =
		    regmap_update_bits(chip->regmap, preg[REG_FLASH_CTRL].regno,
				       preg[REG_FLASH_CTRL].mask,
				       (brightness - 1)
				       << preg[REG_FLASH_CTRL].shअगरt);
		अगर (ret < 0)
			जाओ out;

		अगर (pdata->pin_strobe != LM355x_PIN_STROBE_DISABLE) अणु
			अगर (chip->type == CHIP_LM3554)
				reg_val = 0x00;
			अन्यथा
				reg_val = 0x01;
			ret =
			    regmap_update_bits(chip->regmap,
					       preg[REG_STROBE_CFG].regno,
					       preg[REG_STROBE_CFG].mask,
					       reg_val <<
					       preg[REG_STROBE_CFG].shअगरt);
			अगर (ret < 0)
				जाओ out;
			opmode = MODE_SHDN;
			dev_info(chip->dev,
				 "flash brt is set - ext. strobe pin mode\n");
		पूर्ण
		अवरोध;

	हाल MODE_INDIC:
		ret =
		    regmap_update_bits(chip->regmap, preg[REG_INDI_CTRL].regno,
				       preg[REG_INDI_CTRL].mask,
				       (brightness - 1)
				       << preg[REG_INDI_CTRL].shअगरt);
		अगर (ret < 0)
			जाओ out;

		अगर (pdata->pin_tx2 != LM355x_PIN_TX_DISABLE) अणु
			ret =
			    regmap_update_bits(chip->regmap,
					       preg[REG_INDI_CFG].regno,
					       preg[REG_INDI_CFG].mask,
					       0x01 <<
					       preg[REG_INDI_CFG].shअगरt);
			अगर (ret < 0)
				जाओ out;
			opmode = MODE_SHDN;
		पूर्ण
		अवरोध;
	हाल MODE_SHDN:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* operation mode control */
	ret = regmap_update_bits(chip->regmap, preg[REG_OPMODE].regno,
				 preg[REG_OPMODE].mask,
				 opmode << preg[REG_OPMODE].shअगरt);
	अगर (ret < 0)
		जाओ out;
	वापस ret;
out:
	dev_err(chip->dev, "%s:i2c access fail to register\n", __func__);
	वापस ret;
पूर्ण

/* torch */

अटल पूर्णांक lm355x_torch_brightness_set(काष्ठा led_classdev *cdev,
					क्रमागत led_brightness brightness)
अणु
	काष्ठा lm355x_chip_data *chip =
	    container_of(cdev, काष्ठा lm355x_chip_data, cdev_torch);
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lm355x_control(chip, brightness, MODE_TORCH);
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

/* flash */

अटल पूर्णांक lm355x_strobe_brightness_set(काष्ठा led_classdev *cdev,
					 क्रमागत led_brightness brightness)
अणु
	काष्ठा lm355x_chip_data *chip =
	    container_of(cdev, काष्ठा lm355x_chip_data, cdev_flash);
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lm355x_control(chip, brightness, MODE_FLASH);
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

/* indicator */

अटल पूर्णांक lm355x_indicator_brightness_set(काष्ठा led_classdev *cdev,
					    क्रमागत led_brightness brightness)
अणु
	काष्ठा lm355x_chip_data *chip =
	    container_of(cdev, काष्ठा lm355x_chip_data, cdev_indicator);
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lm355x_control(chip, brightness, MODE_INDIC);
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

/* indicator pattern only क्रम lm3556*/
अटल sमाप_प्रकार pattern_store(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	sमाप_प्रकार ret;
	काष्ठा led_classdev *led_cdev = dev_get_drvdata(dev);
	काष्ठा lm355x_chip_data *chip =
	    container_of(led_cdev, काष्ठा lm355x_chip_data, cdev_indicator);
	अचिन्हित पूर्णांक state;

	ret = kstrtouपूर्णांक(buf, 10, &state);
	अगर (ret)
		जाओ out;
	अगर (state > INDIC_PATTERN_SIZE - 1)
		state = INDIC_PATTERN_SIZE - 1;

	ret = regmap_ग_लिखो(chip->regmap, 0x04,
			   indicator_pattern[state].blinking);
	अगर (ret < 0)
		जाओ out;

	ret = regmap_ग_लिखो(chip->regmap, 0x05,
			   indicator_pattern[state].period_cnt);
	अगर (ret < 0)
		जाओ out;

	वापस size;
out:
	dev_err(chip->dev, "%s:i2c access fail to register\n", __func__);
	वापस ret;
पूर्ण

अटल DEVICE_ATTR_WO(pattern);

अटल काष्ठा attribute *lm355x_indicator_attrs[] = अणु
	&dev_attr_pattern.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(lm355x_indicator);

अटल स्थिर काष्ठा regmap_config lm355x_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = 0xFF,
पूर्ण;

/* module initialize */
अटल पूर्णांक lm355x_probe(काष्ठा i2c_client *client,
				  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा lm355x_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा lm355x_chip_data *chip;

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
			    माप(काष्ठा lm355x_chip_data), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->dev = &client->dev;
	chip->type = id->driver_data;
	चयन (id->driver_data) अणु
	हाल CHIP_LM3554:
		chip->regs = lm3554_regs;
		अवरोध;
	हाल CHIP_LM3556:
		chip->regs = lm3556_regs;
		अवरोध;
	शेष:
		वापस -ENOSYS;
	पूर्ण
	chip->pdata = pdata;

	chip->regmap = devm_regmap_init_i2c(client, &lm355x_regmap);
	अगर (IS_ERR(chip->regmap)) अणु
		err = PTR_ERR(chip->regmap);
		dev_err(&client->dev,
			"Failed to allocate register map: %d\n", err);
		वापस err;
	पूर्ण

	mutex_init(&chip->lock);
	i2c_set_clientdata(client, chip);

	err = lm355x_chip_init(chip);
	अगर (err < 0)
		जाओ err_out;

	/* flash */
	chip->cdev_flash.name = "flash";
	chip->cdev_flash.max_brightness = 16;
	chip->cdev_flash.brightness_set_blocking = lm355x_strobe_brightness_set;
	chip->cdev_flash.शेष_trigger = "flash";
	err = led_classdev_रेजिस्टर(&client->dev, &chip->cdev_flash);
	अगर (err < 0)
		जाओ err_out;
	/* torch */
	chip->cdev_torch.name = "torch";
	chip->cdev_torch.max_brightness = 8;
	chip->cdev_torch.brightness_set_blocking = lm355x_torch_brightness_set;
	chip->cdev_torch.शेष_trigger = "torch";
	err = led_classdev_रेजिस्टर(&client->dev, &chip->cdev_torch);
	अगर (err < 0)
		जाओ err_create_torch_file;
	/* indicator */
	chip->cdev_indicator.name = "indicator";
	अगर (id->driver_data == CHIP_LM3554)
		chip->cdev_indicator.max_brightness = 4;
	अन्यथा
		chip->cdev_indicator.max_brightness = 8;
	chip->cdev_indicator.brightness_set_blocking =
					lm355x_indicator_brightness_set;
	/* indicator pattern control only क्रम LM3556 */
	अगर (id->driver_data == CHIP_LM3556)
		chip->cdev_indicator.groups = lm355x_indicator_groups;
	err = led_classdev_रेजिस्टर(&client->dev, &chip->cdev_indicator);
	अगर (err < 0)
		जाओ err_create_indicator_file;

	dev_info(&client->dev, "%s is initialized\n",
		 lm355x_name[id->driver_data]);
	वापस 0;

err_create_indicator_file:
	led_classdev_unरेजिस्टर(&chip->cdev_torch);
err_create_torch_file:
	led_classdev_unरेजिस्टर(&chip->cdev_flash);
err_out:
	वापस err;
पूर्ण

अटल पूर्णांक lm355x_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lm355x_chip_data *chip = i2c_get_clientdata(client);
	काष्ठा lm355x_reg_data *preg = chip->regs;

	regmap_ग_लिखो(chip->regmap, preg[REG_OPMODE].regno, 0);
	led_classdev_unरेजिस्टर(&chip->cdev_indicator);
	led_classdev_unरेजिस्टर(&chip->cdev_torch);
	led_classdev_unरेजिस्टर(&chip->cdev_flash);
	dev_info(&client->dev, "%s is removed\n", lm355x_name[chip->type]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lm355x_id[] = अणु
	अणुLM3554_NAME, CHIP_LM3554पूर्ण,
	अणुLM3556_NAME, CHIP_LM3556पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lm355x_id);

अटल काष्ठा i2c_driver lm355x_i2c_driver = अणु
	.driver = अणु
		   .name = LM355x_NAME,
		   .pm = शून्य,
		   पूर्ण,
	.probe = lm355x_probe,
	.हटाओ = lm355x_हटाओ,
	.id_table = lm355x_id,
पूर्ण;

module_i2c_driver(lm355x_i2c_driver);

MODULE_DESCRIPTION("Texas Instruments Flash Lighting driver for LM355x");
MODULE_AUTHOR("Daniel Jeong <daniel.jeong@ti.com>");
MODULE_AUTHOR("G.Shark Jeong <gshark.jeong@gmail.com>");
MODULE_LICENSE("GPL v2");
