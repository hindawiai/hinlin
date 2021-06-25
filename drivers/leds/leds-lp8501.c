<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LP8501 9 channel LED Driver
 *
 * Copyright (C) 2013 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/leds-lp55xx.h>
#समावेश <linux/slab.h>

#समावेश "leds-lp55xx-common.h"

#घोषणा LP8501_PROGRAM_LENGTH		32
#घोषणा LP8501_MAX_LEDS			9

/* Registers */
#घोषणा LP8501_REG_ENABLE		0x00
#घोषणा LP8501_ENABLE			BIT(6)
#घोषणा LP8501_EXEC_M			0x3F
#घोषणा LP8501_EXEC_ENG1_M		0x30
#घोषणा LP8501_EXEC_ENG2_M		0x0C
#घोषणा LP8501_EXEC_ENG3_M		0x03
#घोषणा LP8501_RUN_ENG1			0x20
#घोषणा LP8501_RUN_ENG2			0x08
#घोषणा LP8501_RUN_ENG3			0x02

#घोषणा LP8501_REG_OP_MODE		0x01
#घोषणा LP8501_MODE_ENG1_M		0x30
#घोषणा LP8501_MODE_ENG2_M		0x0C
#घोषणा LP8501_MODE_ENG3_M		0x03
#घोषणा LP8501_LOAD_ENG1		0x10
#घोषणा LP8501_LOAD_ENG2		0x04
#घोषणा LP8501_LOAD_ENG3		0x01

#घोषणा LP8501_REG_PWR_CONFIG		0x05
#घोषणा LP8501_PWR_CONFIG_M		0x03

#घोषणा LP8501_REG_LED_PWM_BASE		0x16

#घोषणा LP8501_REG_LED_CURRENT_BASE	0x26

#घोषणा LP8501_REG_CONFIG		0x36
#घोषणा LP8501_PWM_PSAVE		BIT(7)
#घोषणा LP8501_AUTO_INC			BIT(6)
#घोषणा LP8501_PWR_SAVE			BIT(5)
#घोषणा LP8501_CP_AUTO			0x18
#घोषणा LP8501_INT_CLK			BIT(0)
#घोषणा LP8501_DEFAULT_CFG	\
	(LP8501_PWM_PSAVE | LP8501_AUTO_INC | LP8501_PWR_SAVE | LP8501_CP_AUTO)

#घोषणा LP8501_REG_RESET		0x3D
#घोषणा LP8501_RESET			0xFF

#घोषणा LP8501_REG_PROG_PAGE_SEL	0x4F
#घोषणा LP8501_PAGE_ENG1		0
#घोषणा LP8501_PAGE_ENG2		1
#घोषणा LP8501_PAGE_ENG3		2

#घोषणा LP8501_REG_PROG_MEM		0x50

#घोषणा LP8501_ENG1_IS_LOADING(mode)	\
	((mode & LP8501_MODE_ENG1_M) == LP8501_LOAD_ENG1)
#घोषणा LP8501_ENG2_IS_LOADING(mode)	\
	((mode & LP8501_MODE_ENG2_M) == LP8501_LOAD_ENG2)
#घोषणा LP8501_ENG3_IS_LOADING(mode)	\
	((mode & LP8501_MODE_ENG3_M) == LP8501_LOAD_ENG3)

अटल अंतरभूत व्योम lp8501_रुको_opmode_करोne(व्योम)
अणु
	usleep_range(1000, 2000);
पूर्ण

अटल व्योम lp8501_set_led_current(काष्ठा lp55xx_led *led, u8 led_current)
अणु
	led->led_current = led_current;
	lp55xx_ग_लिखो(led->chip, LP8501_REG_LED_CURRENT_BASE + led->chan_nr,
		led_current);
पूर्ण

अटल पूर्णांक lp8501_post_init_device(काष्ठा lp55xx_chip *chip)
अणु
	पूर्णांक ret;
	u8 val = LP8501_DEFAULT_CFG;

	ret = lp55xx_ग_लिखो(chip, LP8501_REG_ENABLE, LP8501_ENABLE);
	अगर (ret)
		वापस ret;

	/* Chip startup समय is 500 us, 1 - 2 ms gives some margin */
	usleep_range(1000, 2000);

	अगर (chip->pdata->घड़ी_mode != LP55XX_CLOCK_EXT)
		val |= LP8501_INT_CLK;

	ret = lp55xx_ग_लिखो(chip, LP8501_REG_CONFIG, val);
	अगर (ret)
		वापस ret;

	/* Power selection क्रम each output */
	वापस lp55xx_update_bits(chip, LP8501_REG_PWR_CONFIG,
				LP8501_PWR_CONFIG_M, chip->pdata->pwr_sel);
पूर्ण

अटल व्योम lp8501_load_engine(काष्ठा lp55xx_chip *chip)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	अटल स्थिर u8 mask[] = अणु
		[LP55XX_ENGINE_1] = LP8501_MODE_ENG1_M,
		[LP55XX_ENGINE_2] = LP8501_MODE_ENG2_M,
		[LP55XX_ENGINE_3] = LP8501_MODE_ENG3_M,
	पूर्ण;

	अटल स्थिर u8 val[] = अणु
		[LP55XX_ENGINE_1] = LP8501_LOAD_ENG1,
		[LP55XX_ENGINE_2] = LP8501_LOAD_ENG2,
		[LP55XX_ENGINE_3] = LP8501_LOAD_ENG3,
	पूर्ण;

	अटल स्थिर u8 page_sel[] = अणु
		[LP55XX_ENGINE_1] = LP8501_PAGE_ENG1,
		[LP55XX_ENGINE_2] = LP8501_PAGE_ENG2,
		[LP55XX_ENGINE_3] = LP8501_PAGE_ENG3,
	पूर्ण;

	lp55xx_update_bits(chip, LP8501_REG_OP_MODE, mask[idx], val[idx]);

	lp8501_रुको_opmode_करोne();

	lp55xx_ग_लिखो(chip, LP8501_REG_PROG_PAGE_SEL, page_sel[idx]);
पूर्ण

अटल व्योम lp8501_stop_engine(काष्ठा lp55xx_chip *chip)
अणु
	lp55xx_ग_लिखो(chip, LP8501_REG_OP_MODE, 0);
	lp8501_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp8501_turn_off_channels(काष्ठा lp55xx_chip *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LP8501_MAX_LEDS; i++)
		lp55xx_ग_लिखो(chip, LP8501_REG_LED_PWM_BASE + i, 0);
पूर्ण

अटल व्योम lp8501_run_engine(काष्ठा lp55xx_chip *chip, bool start)
अणु
	पूर्णांक ret;
	u8 mode;
	u8 exec;

	/* stop engine */
	अगर (!start) अणु
		lp8501_stop_engine(chip);
		lp8501_turn_off_channels(chip);
		वापस;
	पूर्ण

	/*
	 * To run the engine,
	 * operation mode and enable रेजिस्टर should updated at the same समय
	 */

	ret = lp55xx_पढ़ो(chip, LP8501_REG_OP_MODE, &mode);
	अगर (ret)
		वापस;

	ret = lp55xx_पढ़ो(chip, LP8501_REG_ENABLE, &exec);
	अगर (ret)
		वापस;

	/* change operation mode to RUN only when each engine is loading */
	अगर (LP8501_ENG1_IS_LOADING(mode)) अणु
		mode = (mode & ~LP8501_MODE_ENG1_M) | LP8501_RUN_ENG1;
		exec = (exec & ~LP8501_EXEC_ENG1_M) | LP8501_RUN_ENG1;
	पूर्ण

	अगर (LP8501_ENG2_IS_LOADING(mode)) अणु
		mode = (mode & ~LP8501_MODE_ENG2_M) | LP8501_RUN_ENG2;
		exec = (exec & ~LP8501_EXEC_ENG2_M) | LP8501_RUN_ENG2;
	पूर्ण

	अगर (LP8501_ENG3_IS_LOADING(mode)) अणु
		mode = (mode & ~LP8501_MODE_ENG3_M) | LP8501_RUN_ENG3;
		exec = (exec & ~LP8501_EXEC_ENG3_M) | LP8501_RUN_ENG3;
	पूर्ण

	lp55xx_ग_लिखो(chip, LP8501_REG_OP_MODE, mode);
	lp8501_रुको_opmode_करोne();

	lp55xx_update_bits(chip, LP8501_REG_ENABLE, LP8501_EXEC_M, exec);
पूर्ण

अटल पूर्णांक lp8501_update_program_memory(काष्ठा lp55xx_chip *chip,
					स्थिर u8 *data, माप_प्रकार size)
अणु
	u8 pattern[LP8501_PROGRAM_LENGTH] = अणु0पूर्ण;
	अचिन्हित cmd;
	अक्षर c[3];
	पूर्णांक update_size;
	पूर्णांक nrअक्षरs;
	पूर्णांक offset = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/* clear program memory beक्रमe updating */
	क्रम (i = 0; i < LP8501_PROGRAM_LENGTH; i++)
		lp55xx_ग_लिखो(chip, LP8501_REG_PROG_MEM + i, 0);

	i = 0;
	जबतक ((offset < size - 1) && (i < LP8501_PROGRAM_LENGTH)) अणु
		/* separate माला_पूछोs because length is working only क्रम %s */
		ret = माला_पूछो(data + offset, "%2s%n ", c, &nrअक्षरs);
		अगर (ret != 1)
			जाओ err;

		ret = माला_पूछो(c, "%2x", &cmd);
		अगर (ret != 1)
			जाओ err;

		pattern[i] = (u8)cmd;
		offset += nrअक्षरs;
		i++;
	पूर्ण

	/* Each inकाष्ठाion is 16bit दीर्घ. Check that length is even */
	अगर (i % 2)
		जाओ err;

	update_size = i;
	क्रम (i = 0; i < update_size; i++)
		lp55xx_ग_लिखो(chip, LP8501_REG_PROG_MEM + i, pattern[i]);

	वापस 0;

err:
	dev_err(&chip->cl->dev, "wrong pattern format\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम lp8501_firmware_loaded(काष्ठा lp55xx_chip *chip)
अणु
	स्थिर काष्ठा firmware *fw = chip->fw;

	अगर (fw->size > LP8501_PROGRAM_LENGTH) अणु
		dev_err(&chip->cl->dev, "firmware data size overflow: %zu\n",
			fw->size);
		वापस;
	पूर्ण

	/*
	 * Program memory sequence
	 *  1) set engine mode to "LOAD"
	 *  2) ग_लिखो firmware data पूर्णांकo program memory
	 */

	lp8501_load_engine(chip);
	lp8501_update_program_memory(chip, fw->data, fw->size);
पूर्ण

अटल पूर्णांक lp8501_led_brightness(काष्ठा lp55xx_led *led)
अणु
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lp55xx_ग_लिखो(chip, LP8501_REG_LED_PWM_BASE + led->chan_nr,
		     led->brightness);
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

/* Chip specअगरic configurations */
अटल काष्ठा lp55xx_device_config lp8501_cfg = अणु
	.reset = अणु
		.addr = LP8501_REG_RESET,
		.val  = LP8501_RESET,
	पूर्ण,
	.enable = अणु
		.addr = LP8501_REG_ENABLE,
		.val  = LP8501_ENABLE,
	पूर्ण,
	.max_channel  = LP8501_MAX_LEDS,
	.post_init_device   = lp8501_post_init_device,
	.brightness_fn      = lp8501_led_brightness,
	.set_led_current    = lp8501_set_led_current,
	.firmware_cb        = lp8501_firmware_loaded,
	.run_engine         = lp8501_run_engine,
पूर्ण;

अटल पूर्णांक lp8501_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा lp55xx_chip *chip;
	काष्ठा lp55xx_led *led;
	काष्ठा lp55xx_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा device_node *np = dev_of_node(&client->dev);

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->cfg = &lp8501_cfg;

	अगर (!pdata) अणु
		अगर (np) अणु
			pdata = lp55xx_of_populate_pdata(&client->dev, np,
							 chip);
			अगर (IS_ERR(pdata))
				वापस PTR_ERR(pdata);
		पूर्ण अन्यथा अणु
			dev_err(&client->dev, "no platform data\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	led = devm_kसुस्मृति(&client->dev,
			pdata->num_channels, माप(*led), GFP_KERNEL);
	अगर (!led)
		वापस -ENOMEM;

	chip->cl = client;
	chip->pdata = pdata;

	mutex_init(&chip->lock);

	i2c_set_clientdata(client, led);

	ret = lp55xx_init_device(chip);
	अगर (ret)
		जाओ err_init;

	dev_info(&client->dev, "%s Programmable led chip found\n", id->name);

	ret = lp55xx_रेजिस्टर_leds(led, chip);
	अगर (ret)
		जाओ err_out;

	ret = lp55xx_रेजिस्टर_sysfs(chip);
	अगर (ret) अणु
		dev_err(&client->dev, "registering sysfs failed\n");
		जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	lp55xx_deinit_device(chip);
err_init:
	वापस ret;
पूर्ण

अटल पूर्णांक lp8501_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(client);
	काष्ठा lp55xx_chip *chip = led->chip;

	lp8501_stop_engine(chip);
	lp55xx_unरेजिस्टर_sysfs(chip);
	lp55xx_deinit_device(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp8501_id[] = अणु
	अणु "lp8501",  0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp8501_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_lp8501_leds_match[] = अणु
	अणु .compatible = "ti,lp8501", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_lp8501_leds_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver lp8501_driver = अणु
	.driver = अणु
		.name	= "lp8501",
		.of_match_table = of_match_ptr(of_lp8501_leds_match),
	पूर्ण,
	.probe		= lp8501_probe,
	.हटाओ		= lp8501_हटाओ,
	.id_table	= lp8501_id,
पूर्ण;

module_i2c_driver(lp8501_driver);

MODULE_DESCRIPTION("Texas Instruments LP8501 LED driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
