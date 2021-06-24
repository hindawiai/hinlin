<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LP5521 LED chip driver.
 *
 * Copyright (C) 2010 Nokia Corporation
 * Copyright (C) 2012 Texas Instruments
 *
 * Contact: Samu Onkalo <samu.p.onkalo@nokia.com>
 *          Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_data/leds-lp55xx.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश "leds-lp55xx-common.h"

#घोषणा LP5521_PROGRAM_LENGTH		32
#घोषणा LP5521_MAX_LEDS			3
#घोषणा LP5521_CMD_सूचीECT		0x3F

/* Registers */
#घोषणा LP5521_REG_ENABLE		0x00
#घोषणा LP5521_REG_OP_MODE		0x01
#घोषणा LP5521_REG_R_PWM		0x02
#घोषणा LP5521_REG_G_PWM		0x03
#घोषणा LP5521_REG_B_PWM		0x04
#घोषणा LP5521_REG_R_CURRENT		0x05
#घोषणा LP5521_REG_G_CURRENT		0x06
#घोषणा LP5521_REG_B_CURRENT		0x07
#घोषणा LP5521_REG_CONFIG		0x08
#घोषणा LP5521_REG_STATUS		0x0C
#घोषणा LP5521_REG_RESET		0x0D
#घोषणा LP5521_REG_R_PROG_MEM		0x10
#घोषणा LP5521_REG_G_PROG_MEM		0x30
#घोषणा LP5521_REG_B_PROG_MEM		0x50

/* Base रेजिस्टर to set LED current */
#घोषणा LP5521_REG_LED_CURRENT_BASE	LP5521_REG_R_CURRENT
/* Base रेजिस्टर to set the brightness */
#घोषणा LP5521_REG_LED_PWM_BASE		LP5521_REG_R_PWM

/* Bits in ENABLE रेजिस्टर */
#घोषणा LP5521_MASTER_ENABLE		0x40	/* Chip master enable */
#घोषणा LP5521_LOGARITHMIC_PWM		0x80	/* Logarithmic PWM adjusपंचांगent */
#घोषणा LP5521_EXEC_RUN			0x2A
#घोषणा LP5521_ENABLE_DEFAULT	\
	(LP5521_MASTER_ENABLE | LP5521_LOGARITHMIC_PWM)
#घोषणा LP5521_ENABLE_RUN_PROGRAM	\
	(LP5521_ENABLE_DEFAULT | LP5521_EXEC_RUN)

/* CONFIG रेजिस्टर */
#घोषणा LP5521_PWM_HF			0x40	/* PWM: 0 = 256Hz, 1 = 558Hz */
#घोषणा LP5521_PWRSAVE_EN		0x20	/* 1 = Power save mode */
#घोषणा LP5521_CP_MODE_OFF		0	/* Charge pump (CP) off */
#घोषणा LP5521_CP_MODE_BYPASS		8	/* CP क्रमced to bypass mode */
#घोषणा LP5521_CP_MODE_1X5		0x10	/* CP क्रमced to 1.5x mode */
#घोषणा LP5521_CP_MODE_AUTO		0x18	/* Automatic mode selection */
#घोषणा LP5521_R_TO_BATT		0x04	/* R out: 0 = CP, 1 = Vbat */
#घोषणा LP5521_CLK_INT			0x01	/* Internal घड़ी */
#घोषणा LP5521_DEFAULT_CFG		\
	(LP5521_PWM_HF | LP5521_PWRSAVE_EN | LP5521_CP_MODE_AUTO)

/* Status */
#घोषणा LP5521_EXT_CLK_USED		0x08

/* शेष R channel current रेजिस्टर value */
#घोषणा LP5521_REG_R_CURR_DEFAULT	0xAF

/* Reset रेजिस्टर value */
#घोषणा LP5521_RESET			0xFF

/* Program Memory Operations */
#घोषणा LP5521_MODE_R_M			0x30	/* Operation Mode Register */
#घोषणा LP5521_MODE_G_M			0x0C
#घोषणा LP5521_MODE_B_M			0x03
#घोषणा LP5521_LOAD_R			0x10
#घोषणा LP5521_LOAD_G			0x04
#घोषणा LP5521_LOAD_B			0x01

#घोषणा LP5521_R_IS_LOADING(mode)	\
	((mode & LP5521_MODE_R_M) == LP5521_LOAD_R)
#घोषणा LP5521_G_IS_LOADING(mode)	\
	((mode & LP5521_MODE_G_M) == LP5521_LOAD_G)
#घोषणा LP5521_B_IS_LOADING(mode)	\
	((mode & LP5521_MODE_B_M) == LP5521_LOAD_B)

#घोषणा LP5521_EXEC_R_M			0x30	/* Enable Register */
#घोषणा LP5521_EXEC_G_M			0x0C
#घोषणा LP5521_EXEC_B_M			0x03
#घोषणा LP5521_EXEC_M			0x3F
#घोषणा LP5521_RUN_R			0x20
#घोषणा LP5521_RUN_G			0x08
#घोषणा LP5521_RUN_B			0x02

अटल अंतरभूत व्योम lp5521_रुको_opmode_करोne(व्योम)
अणु
	/* operation mode change needs to be दीर्घer than 153 us */
	usleep_range(200, 300);
पूर्ण

अटल अंतरभूत व्योम lp5521_रुको_enable_करोne(व्योम)
अणु
	/* it takes more 488 us to update ENABLE रेजिस्टर */
	usleep_range(500, 600);
पूर्ण

अटल व्योम lp5521_set_led_current(काष्ठा lp55xx_led *led, u8 led_current)
अणु
	led->led_current = led_current;
	lp55xx_ग_लिखो(led->chip, LP5521_REG_LED_CURRENT_BASE + led->chan_nr,
		led_current);
पूर्ण

अटल व्योम lp5521_load_engine(काष्ठा lp55xx_chip *chip)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	अटल स्थिर u8 mask[] = अणु
		[LP55XX_ENGINE_1] = LP5521_MODE_R_M,
		[LP55XX_ENGINE_2] = LP5521_MODE_G_M,
		[LP55XX_ENGINE_3] = LP5521_MODE_B_M,
	पूर्ण;

	अटल स्थिर u8 val[] = अणु
		[LP55XX_ENGINE_1] = LP5521_LOAD_R,
		[LP55XX_ENGINE_2] = LP5521_LOAD_G,
		[LP55XX_ENGINE_3] = LP5521_LOAD_B,
	पूर्ण;

	lp55xx_update_bits(chip, LP5521_REG_OP_MODE, mask[idx], val[idx]);

	lp5521_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5521_stop_all_engines(काष्ठा lp55xx_chip *chip)
अणु
	lp55xx_ग_लिखो(chip, LP5521_REG_OP_MODE, 0);
	lp5521_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5521_stop_engine(काष्ठा lp55xx_chip *chip)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	अटल स्थिर u8 mask[] = अणु
		[LP55XX_ENGINE_1] = LP5521_MODE_R_M,
		[LP55XX_ENGINE_2] = LP5521_MODE_G_M,
		[LP55XX_ENGINE_3] = LP5521_MODE_B_M,
	पूर्ण;

	lp55xx_update_bits(chip, LP5521_REG_OP_MODE, mask[idx], 0);

	lp5521_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5521_run_engine(काष्ठा lp55xx_chip *chip, bool start)
अणु
	पूर्णांक ret;
	u8 mode;
	u8 exec;

	/* stop engine */
	अगर (!start) अणु
		lp5521_stop_engine(chip);
		lp55xx_ग_लिखो(chip, LP5521_REG_OP_MODE, LP5521_CMD_सूचीECT);
		lp5521_रुको_opmode_करोne();
		वापस;
	पूर्ण

	/*
	 * To run the engine,
	 * operation mode and enable रेजिस्टर should updated at the same समय
	 */

	ret = lp55xx_पढ़ो(chip, LP5521_REG_OP_MODE, &mode);
	अगर (ret)
		वापस;

	ret = lp55xx_पढ़ो(chip, LP5521_REG_ENABLE, &exec);
	अगर (ret)
		वापस;

	/* change operation mode to RUN only when each engine is loading */
	अगर (LP5521_R_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5521_MODE_R_M) | LP5521_RUN_R;
		exec = (exec & ~LP5521_EXEC_R_M) | LP5521_RUN_R;
	पूर्ण

	अगर (LP5521_G_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5521_MODE_G_M) | LP5521_RUN_G;
		exec = (exec & ~LP5521_EXEC_G_M) | LP5521_RUN_G;
	पूर्ण

	अगर (LP5521_B_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5521_MODE_B_M) | LP5521_RUN_B;
		exec = (exec & ~LP5521_EXEC_B_M) | LP5521_RUN_B;
	पूर्ण

	lp55xx_ग_लिखो(chip, LP5521_REG_OP_MODE, mode);
	lp5521_रुको_opmode_करोne();

	lp55xx_update_bits(chip, LP5521_REG_ENABLE, LP5521_EXEC_M, exec);
	lp5521_रुको_enable_करोne();
पूर्ण

अटल पूर्णांक lp5521_update_program_memory(काष्ठा lp55xx_chip *chip,
					स्थिर u8 *data, माप_प्रकार size)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	u8 pattern[LP5521_PROGRAM_LENGTH] = अणु0पूर्ण;
	अटल स्थिर u8 addr[] = अणु
		[LP55XX_ENGINE_1] = LP5521_REG_R_PROG_MEM,
		[LP55XX_ENGINE_2] = LP5521_REG_G_PROG_MEM,
		[LP55XX_ENGINE_3] = LP5521_REG_B_PROG_MEM,
	पूर्ण;
	अचिन्हित cmd;
	अक्षर c[3];
	पूर्णांक nrअक्षरs;
	पूर्णांक ret;
	पूर्णांक offset = 0;
	पूर्णांक i = 0;

	जबतक ((offset < size - 1) && (i < LP5521_PROGRAM_LENGTH)) अणु
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

	क्रम (i = 0; i < LP5521_PROGRAM_LENGTH; i++) अणु
		ret = lp55xx_ग_लिखो(chip, addr[idx] + i, pattern[i]);
		अगर (ret)
			वापस -EINVAL;
	पूर्ण

	वापस size;

err:
	dev_err(&chip->cl->dev, "wrong pattern format\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम lp5521_firmware_loaded(काष्ठा lp55xx_chip *chip)
अणु
	स्थिर काष्ठा firmware *fw = chip->fw;

	अगर (fw->size > LP5521_PROGRAM_LENGTH) अणु
		dev_err(&chip->cl->dev, "firmware data size overflow: %zu\n",
			fw->size);
		वापस;
	पूर्ण

	/*
	 * Program memory sequence
	 *  1) set engine mode to "LOAD"
	 *  2) ग_लिखो firmware data पूर्णांकo program memory
	 */

	lp5521_load_engine(chip);
	lp5521_update_program_memory(chip, fw->data, fw->size);
पूर्ण

अटल पूर्णांक lp5521_post_init_device(काष्ठा lp55xx_chip *chip)
अणु
	पूर्णांक ret;
	u8 val;

	/*
	 * Make sure that the chip is reset by पढ़ोing back the r channel
	 * current reg. This is dummy पढ़ो is required on some platक्रमms -
	 * otherwise further access to the R G B channels in the
	 * LP5521_REG_ENABLE रेजिस्टर will not have any effect - strange!
	 */
	ret = lp55xx_पढ़ो(chip, LP5521_REG_R_CURRENT, &val);
	अगर (ret) अणु
		dev_err(&chip->cl->dev, "error in resetting chip\n");
		वापस ret;
	पूर्ण
	अगर (val != LP5521_REG_R_CURR_DEFAULT) अणु
		dev_err(&chip->cl->dev,
			"unexpected data in register (expected 0x%x got 0x%x)\n",
			LP5521_REG_R_CURR_DEFAULT, val);
		ret = -EINVAL;
		वापस ret;
	पूर्ण
	usleep_range(10000, 20000);

	/* Set all PWMs to direct control mode */
	ret = lp55xx_ग_लिखो(chip, LP5521_REG_OP_MODE, LP5521_CMD_सूचीECT);

	/* Update configuration क्रम the घड़ी setting */
	val = LP5521_DEFAULT_CFG;
	अगर (!lp55xx_is_extclk_used(chip))
		val |= LP5521_CLK_INT;

	ret = lp55xx_ग_लिखो(chip, LP5521_REG_CONFIG, val);
	अगर (ret)
		वापस ret;

	/* Initialize all channels PWM to zero -> leds off */
	lp55xx_ग_लिखो(chip, LP5521_REG_R_PWM, 0);
	lp55xx_ग_लिखो(chip, LP5521_REG_G_PWM, 0);
	lp55xx_ग_लिखो(chip, LP5521_REG_B_PWM, 0);

	/* Set engines are set to run state when OP_MODE enables engines */
	ret = lp55xx_ग_लिखो(chip, LP5521_REG_ENABLE, LP5521_ENABLE_RUN_PROGRAM);
	अगर (ret)
		वापस ret;

	lp5521_रुको_enable_करोne();

	वापस 0;
पूर्ण

अटल पूर्णांक lp5521_run_selftest(काष्ठा lp55xx_chip *chip, अक्षर *buf)
अणु
	काष्ठा lp55xx_platक्रमm_data *pdata = chip->pdata;
	पूर्णांक ret;
	u8 status;

	ret = lp55xx_पढ़ो(chip, LP5521_REG_STATUS, &status);
	अगर (ret < 0)
		वापस ret;

	अगर (pdata->घड़ी_mode != LP55XX_CLOCK_EXT)
		वापस 0;

	/* Check that ext घड़ी is really in use अगर requested */
	अगर  ((status & LP5521_EXT_CLK_USED) == 0)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक lp5521_multicolor_brightness(काष्ठा lp55xx_led *led)
अणु
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&chip->lock);
	क्रम (i = 0; i < led->mc_cdev.num_colors; i++) अणु
		ret = lp55xx_ग_लिखो(chip,
				   LP5521_REG_LED_PWM_BASE +
				   led->mc_cdev.subled_info[i].channel,
				   led->mc_cdev.subled_info[i].brightness);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lp5521_led_brightness(काष्ठा lp55xx_led *led)
अणु
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lp55xx_ग_लिखो(chip, LP5521_REG_LED_PWM_BASE + led->chan_nr,
		led->brightness);
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_engine_mode(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	क्रमागत lp55xx_engine_mode mode = chip->engines[nr - 1].mode;

	चयन (mode) अणु
	हाल LP55XX_ENGINE_RUN:
		वापस प्र_लिखो(buf, "run\n");
	हाल LP55XX_ENGINE_LOAD:
		वापस प्र_लिखो(buf, "load\n");
	हाल LP55XX_ENGINE_DISABLED:
	शेष:
		वापस प्र_लिखो(buf, "disabled\n");
	पूर्ण
पूर्ण
show_mode(1)
show_mode(2)
show_mode(3)

अटल sमाप_प्रकार store_engine_mode(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार len, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	काष्ठा lp55xx_engine *engine = &chip->engines[nr - 1];

	mutex_lock(&chip->lock);

	chip->engine_idx = nr;

	अगर (!म_भेदन(buf, "run", 3)) अणु
		lp5521_run_engine(chip, true);
		engine->mode = LP55XX_ENGINE_RUN;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "load", 4)) अणु
		lp5521_stop_engine(chip);
		lp5521_load_engine(chip);
		engine->mode = LP55XX_ENGINE_LOAD;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "disabled", 8)) अणु
		lp5521_stop_engine(chip);
		engine->mode = LP55XX_ENGINE_DISABLED;
	पूर्ण

	mutex_unlock(&chip->lock);

	वापस len;
पूर्ण
store_mode(1)
store_mode(2)
store_mode(3)

अटल sमाप_प्रकार store_engine_load(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	chip->engine_idx = nr;
	lp5521_load_engine(chip);
	ret = lp5521_update_program_memory(chip, buf, len);

	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण
store_load(1)
store_load(2)
store_load(3)

अटल sमाप_प्रकार lp5521_selftest(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lp5521_run_selftest(chip, buf);
	mutex_unlock(&chip->lock);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%s\n", ret ? "FAIL" : "OK");
पूर्ण

/* device attributes */
अटल LP55XX_DEV_ATTR_RW(engine1_mode, show_engine1_mode, store_engine1_mode);
अटल LP55XX_DEV_ATTR_RW(engine2_mode, show_engine2_mode, store_engine2_mode);
अटल LP55XX_DEV_ATTR_RW(engine3_mode, show_engine3_mode, store_engine3_mode);
अटल LP55XX_DEV_ATTR_WO(engine1_load, store_engine1_load);
अटल LP55XX_DEV_ATTR_WO(engine2_load, store_engine2_load);
अटल LP55XX_DEV_ATTR_WO(engine3_load, store_engine3_load);
अटल LP55XX_DEV_ATTR_RO(selftest, lp5521_selftest);

अटल काष्ठा attribute *lp5521_attributes[] = अणु
	&dev_attr_engine1_mode.attr,
	&dev_attr_engine2_mode.attr,
	&dev_attr_engine3_mode.attr,
	&dev_attr_engine1_load.attr,
	&dev_attr_engine2_load.attr,
	&dev_attr_engine3_load.attr,
	&dev_attr_selftest.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group lp5521_group = अणु
	.attrs = lp5521_attributes,
पूर्ण;

/* Chip specअगरic configurations */
अटल काष्ठा lp55xx_device_config lp5521_cfg = अणु
	.reset = अणु
		.addr = LP5521_REG_RESET,
		.val  = LP5521_RESET,
	पूर्ण,
	.enable = अणु
		.addr = LP5521_REG_ENABLE,
		.val  = LP5521_ENABLE_DEFAULT,
	पूर्ण,
	.max_channel  = LP5521_MAX_LEDS,
	.post_init_device   = lp5521_post_init_device,
	.brightness_fn      = lp5521_led_brightness,
	.multicolor_brightness_fn = lp5521_multicolor_brightness,
	.set_led_current    = lp5521_set_led_current,
	.firmware_cb        = lp5521_firmware_loaded,
	.run_engine         = lp5521_run_engine,
	.dev_attr_group     = &lp5521_group,
पूर्ण;

अटल पूर्णांक lp5521_probe(काष्ठा i2c_client *client,
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

	chip->cfg = &lp5521_cfg;

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

	dev_info(&client->dev, "%s programmable led chip found\n", id->name);

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

अटल पूर्णांक lp5521_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(client);
	काष्ठा lp55xx_chip *chip = led->chip;

	lp5521_stop_all_engines(chip);
	lp55xx_unरेजिस्टर_sysfs(chip);
	lp55xx_deinit_device(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp5521_id[] = अणु
	अणु "lp5521", 0 पूर्ण, /* Three channel chip */
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp5521_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_lp5521_leds_match[] = अणु
	अणु .compatible = "national,lp5521", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_lp5521_leds_match);
#पूर्ण_अगर
अटल काष्ठा i2c_driver lp5521_driver = अणु
	.driver = अणु
		.name	= "lp5521",
		.of_match_table = of_match_ptr(of_lp5521_leds_match),
	पूर्ण,
	.probe		= lp5521_probe,
	.हटाओ		= lp5521_हटाओ,
	.id_table	= lp5521_id,
पूर्ण;

module_i2c_driver(lp5521_driver);

MODULE_AUTHOR("Mathias Nyman, Yuri Zaporozhets, Samu Onkalo");
MODULE_AUTHOR("Milo Kim <milo.kim@ti.com>");
MODULE_DESCRIPTION("LP5521 LED engine");
MODULE_LICENSE("GPL v2");
