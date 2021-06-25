<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LP5562 LED driver
 *
 * Copyright (C) 2013 Texas Instruments
 *
 * Author: Milo(Woogyom) Kim <milo.kim@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/leds-lp55xx.h>
#समावेश <linux/slab.h>

#समावेश "leds-lp55xx-common.h"

#घोषणा LP5562_PROGRAM_LENGTH		32
#घोषणा LP5562_MAX_LEDS			4

/* ENABLE Register 00h */
#घोषणा LP5562_REG_ENABLE		0x00
#घोषणा LP5562_EXEC_ENG1_M		0x30
#घोषणा LP5562_EXEC_ENG2_M		0x0C
#घोषणा LP5562_EXEC_ENG3_M		0x03
#घोषणा LP5562_EXEC_M			0x3F
#घोषणा LP5562_MASTER_ENABLE		0x40	/* Chip master enable */
#घोषणा LP5562_LOGARITHMIC_PWM		0x80	/* Logarithmic PWM adjusपंचांगent */
#घोषणा LP5562_EXEC_RUN			0x2A
#घोषणा LP5562_ENABLE_DEFAULT	\
	(LP5562_MASTER_ENABLE | LP5562_LOGARITHMIC_PWM)
#घोषणा LP5562_ENABLE_RUN_PROGRAM	\
	(LP5562_ENABLE_DEFAULT | LP5562_EXEC_RUN)

/* OPMODE Register 01h */
#घोषणा LP5562_REG_OP_MODE		0x01
#घोषणा LP5562_MODE_ENG1_M		0x30
#घोषणा LP5562_MODE_ENG2_M		0x0C
#घोषणा LP5562_MODE_ENG3_M		0x03
#घोषणा LP5562_LOAD_ENG1		0x10
#घोषणा LP5562_LOAD_ENG2		0x04
#घोषणा LP5562_LOAD_ENG3		0x01
#घोषणा LP5562_RUN_ENG1			0x20
#घोषणा LP5562_RUN_ENG2			0x08
#घोषणा LP5562_RUN_ENG3			0x02
#घोषणा LP5562_ENG1_IS_LOADING(mode)	\
	((mode & LP5562_MODE_ENG1_M) == LP5562_LOAD_ENG1)
#घोषणा LP5562_ENG2_IS_LOADING(mode)	\
	((mode & LP5562_MODE_ENG2_M) == LP5562_LOAD_ENG2)
#घोषणा LP5562_ENG3_IS_LOADING(mode)	\
	((mode & LP5562_MODE_ENG3_M) == LP5562_LOAD_ENG3)

/* BRIGHTNESS Registers */
#घोषणा LP5562_REG_R_PWM		0x04
#घोषणा LP5562_REG_G_PWM		0x03
#घोषणा LP5562_REG_B_PWM		0x02
#घोषणा LP5562_REG_W_PWM		0x0E

/* CURRENT Registers */
#घोषणा LP5562_REG_R_CURRENT		0x07
#घोषणा LP5562_REG_G_CURRENT		0x06
#घोषणा LP5562_REG_B_CURRENT		0x05
#घोषणा LP5562_REG_W_CURRENT		0x0F

/* CONFIG Register 08h */
#घोषणा LP5562_REG_CONFIG		0x08
#घोषणा LP5562_PWM_HF			0x40
#घोषणा LP5562_PWRSAVE_EN		0x20
#घोषणा LP5562_CLK_INT			0x01	/* Internal घड़ी */
#घोषणा LP5562_DEFAULT_CFG		(LP5562_PWM_HF | LP5562_PWRSAVE_EN)

/* RESET Register 0Dh */
#घोषणा LP5562_REG_RESET		0x0D
#घोषणा LP5562_RESET			0xFF

/* PROGRAM ENGINE Registers */
#घोषणा LP5562_REG_PROG_MEM_ENG1	0x10
#घोषणा LP5562_REG_PROG_MEM_ENG2	0x30
#घोषणा LP5562_REG_PROG_MEM_ENG3	0x50

/* LEDMAP Register 70h */
#घोषणा LP5562_REG_ENG_SEL		0x70
#घोषणा LP5562_ENG_SEL_PWM		0
#घोषणा LP5562_ENG_FOR_RGB_M		0x3F
#घोषणा LP5562_ENG_SEL_RGB		0x1B	/* R:ENG1, G:ENG2, B:ENG3 */
#घोषणा LP5562_ENG_FOR_W_M		0xC0
#घोषणा LP5562_ENG1_FOR_W		0x40	/* W:ENG1 */
#घोषणा LP5562_ENG2_FOR_W		0x80	/* W:ENG2 */
#घोषणा LP5562_ENG3_FOR_W		0xC0	/* W:ENG3 */

/* Program Commands */
#घोषणा LP5562_CMD_DISABLE		0x00
#घोषणा LP5562_CMD_LOAD			0x15
#घोषणा LP5562_CMD_RUN			0x2A
#घोषणा LP5562_CMD_सूचीECT		0x3F
#घोषणा LP5562_PATTERN_OFF		0

अटल अंतरभूत व्योम lp5562_रुको_opmode_करोne(व्योम)
अणु
	/* operation mode change needs to be दीर्घer than 153 us */
	usleep_range(200, 300);
पूर्ण

अटल अंतरभूत व्योम lp5562_रुको_enable_करोne(व्योम)
अणु
	/* it takes more 488 us to update ENABLE रेजिस्टर */
	usleep_range(500, 600);
पूर्ण

अटल व्योम lp5562_set_led_current(काष्ठा lp55xx_led *led, u8 led_current)
अणु
	अटल स्थिर u8 addr[] = अणु
		LP5562_REG_R_CURRENT,
		LP5562_REG_G_CURRENT,
		LP5562_REG_B_CURRENT,
		LP5562_REG_W_CURRENT,
	पूर्ण;

	led->led_current = led_current;
	lp55xx_ग_लिखो(led->chip, addr[led->chan_nr], led_current);
पूर्ण

अटल व्योम lp5562_load_engine(काष्ठा lp55xx_chip *chip)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	अटल स्थिर u8 mask[] = अणु
		[LP55XX_ENGINE_1] = LP5562_MODE_ENG1_M,
		[LP55XX_ENGINE_2] = LP5562_MODE_ENG2_M,
		[LP55XX_ENGINE_3] = LP5562_MODE_ENG3_M,
	पूर्ण;

	अटल स्थिर u8 val[] = अणु
		[LP55XX_ENGINE_1] = LP5562_LOAD_ENG1,
		[LP55XX_ENGINE_2] = LP5562_LOAD_ENG2,
		[LP55XX_ENGINE_3] = LP5562_LOAD_ENG3,
	पूर्ण;

	lp55xx_update_bits(chip, LP5562_REG_OP_MODE, mask[idx], val[idx]);

	lp5562_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5562_stop_engine(काष्ठा lp55xx_chip *chip)
अणु
	lp55xx_ग_लिखो(chip, LP5562_REG_OP_MODE, LP5562_CMD_DISABLE);
	lp5562_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5562_run_engine(काष्ठा lp55xx_chip *chip, bool start)
अणु
	पूर्णांक ret;
	u8 mode;
	u8 exec;

	/* stop engine */
	अगर (!start) अणु
		lp55xx_ग_लिखो(chip, LP5562_REG_ENABLE, LP5562_ENABLE_DEFAULT);
		lp5562_रुको_enable_करोne();
		lp5562_stop_engine(chip);
		lp55xx_ग_लिखो(chip, LP5562_REG_ENG_SEL, LP5562_ENG_SEL_PWM);
		lp55xx_ग_लिखो(chip, LP5562_REG_OP_MODE, LP5562_CMD_सूचीECT);
		lp5562_रुको_opmode_करोne();
		वापस;
	पूर्ण

	/*
	 * To run the engine,
	 * operation mode and enable रेजिस्टर should updated at the same समय
	 */

	ret = lp55xx_पढ़ो(chip, LP5562_REG_OP_MODE, &mode);
	अगर (ret)
		वापस;

	ret = lp55xx_पढ़ो(chip, LP5562_REG_ENABLE, &exec);
	अगर (ret)
		वापस;

	/* change operation mode to RUN only when each engine is loading */
	अगर (LP5562_ENG1_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5562_MODE_ENG1_M) | LP5562_RUN_ENG1;
		exec = (exec & ~LP5562_EXEC_ENG1_M) | LP5562_RUN_ENG1;
	पूर्ण

	अगर (LP5562_ENG2_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5562_MODE_ENG2_M) | LP5562_RUN_ENG2;
		exec = (exec & ~LP5562_EXEC_ENG2_M) | LP5562_RUN_ENG2;
	पूर्ण

	अगर (LP5562_ENG3_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5562_MODE_ENG3_M) | LP5562_RUN_ENG3;
		exec = (exec & ~LP5562_EXEC_ENG3_M) | LP5562_RUN_ENG3;
	पूर्ण

	lp55xx_ग_लिखो(chip, LP5562_REG_OP_MODE, mode);
	lp5562_रुको_opmode_करोne();

	lp55xx_update_bits(chip, LP5562_REG_ENABLE, LP5562_EXEC_M, exec);
	lp5562_रुको_enable_करोne();
पूर्ण

अटल पूर्णांक lp5562_update_firmware(काष्ठा lp55xx_chip *chip,
					स्थिर u8 *data, माप_प्रकार size)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	u8 pattern[LP5562_PROGRAM_LENGTH] = अणु0पूर्ण;
	अटल स्थिर u8 addr[] = अणु
		[LP55XX_ENGINE_1] = LP5562_REG_PROG_MEM_ENG1,
		[LP55XX_ENGINE_2] = LP5562_REG_PROG_MEM_ENG2,
		[LP55XX_ENGINE_3] = LP5562_REG_PROG_MEM_ENG3,
	पूर्ण;
	अचिन्हित cmd;
	अक्षर c[3];
	पूर्णांक program_size;
	पूर्णांक nrअक्षरs;
	पूर्णांक offset = 0;
	पूर्णांक ret;
	पूर्णांक i;

	/* clear program memory beक्रमe updating */
	क्रम (i = 0; i < LP5562_PROGRAM_LENGTH; i++)
		lp55xx_ग_लिखो(chip, addr[idx] + i, 0);

	i = 0;
	जबतक ((offset < size - 1) && (i < LP5562_PROGRAM_LENGTH)) अणु
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

	program_size = i;
	क्रम (i = 0; i < program_size; i++)
		lp55xx_ग_लिखो(chip, addr[idx] + i, pattern[i]);

	वापस 0;

err:
	dev_err(&chip->cl->dev, "wrong pattern format\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम lp5562_firmware_loaded(काष्ठा lp55xx_chip *chip)
अणु
	स्थिर काष्ठा firmware *fw = chip->fw;

	/*
	 * the firmware is encoded in ascii hex अक्षरacter, with 2 अक्षरs
	 * per byte
	 */
	अगर (fw->size > (LP5562_PROGRAM_LENGTH * 2)) अणु
		dev_err(&chip->cl->dev, "firmware data size overflow: %zu\n",
			fw->size);
		वापस;
	पूर्ण

	/*
	 * Program memory sequence
	 *  1) set engine mode to "LOAD"
	 *  2) ग_लिखो firmware data पूर्णांकo program memory
	 */

	lp5562_load_engine(chip);
	lp5562_update_firmware(chip, fw->data, fw->size);
पूर्ण

अटल पूर्णांक lp5562_post_init_device(काष्ठा lp55xx_chip *chip)
अणु
	पूर्णांक ret;
	u8 cfg = LP5562_DEFAULT_CFG;

	/* Set all PWMs to direct control mode */
	ret = lp55xx_ग_लिखो(chip, LP5562_REG_OP_MODE, LP5562_CMD_सूचीECT);
	अगर (ret)
		वापस ret;

	lp5562_रुको_opmode_करोne();

	/* Update configuration क्रम the घड़ी setting */
	अगर (!lp55xx_is_extclk_used(chip))
		cfg |= LP5562_CLK_INT;

	ret = lp55xx_ग_लिखो(chip, LP5562_REG_CONFIG, cfg);
	अगर (ret)
		वापस ret;

	/* Initialize all channels PWM to zero -> leds off */
	lp55xx_ग_लिखो(chip, LP5562_REG_R_PWM, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_G_PWM, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_B_PWM, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_W_PWM, 0);

	/* Set LED map as रेजिस्टर PWM by शेष */
	lp55xx_ग_लिखो(chip, LP5562_REG_ENG_SEL, LP5562_ENG_SEL_PWM);

	वापस 0;
पूर्ण

अटल पूर्णांक lp5562_led_brightness(काष्ठा lp55xx_led *led)
अणु
	काष्ठा lp55xx_chip *chip = led->chip;
	अटल स्थिर u8 addr[] = अणु
		LP5562_REG_R_PWM,
		LP5562_REG_G_PWM,
		LP5562_REG_B_PWM,
		LP5562_REG_W_PWM,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lp55xx_ग_लिखो(chip, addr[led->chan_nr], led->brightness);
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल व्योम lp5562_ग_लिखो_program_memory(काष्ठा lp55xx_chip *chip,
					u8 base, स्थिर u8 *rgb, पूर्णांक size)
अणु
	पूर्णांक i;

	अगर (!rgb || size <= 0)
		वापस;

	क्रम (i = 0; i < size; i++)
		lp55xx_ग_लिखो(chip, base + i, *(rgb + i));

	lp55xx_ग_लिखो(chip, base + i, 0);
	lp55xx_ग_लिखो(chip, base + i + 1, 0);
पूर्ण

/* check the size of program count */
अटल अंतरभूत bool _is_pc_overflow(काष्ठा lp55xx_predef_pattern *ptn)
अणु
	वापस ptn->size_r >= LP5562_PROGRAM_LENGTH ||
	       ptn->size_g >= LP5562_PROGRAM_LENGTH ||
	       ptn->size_b >= LP5562_PROGRAM_LENGTH;
पूर्ण

अटल पूर्णांक lp5562_run_predef_led_pattern(काष्ठा lp55xx_chip *chip, पूर्णांक mode)
अणु
	काष्ठा lp55xx_predef_pattern *ptn;
	पूर्णांक i;

	अगर (mode == LP5562_PATTERN_OFF) अणु
		lp5562_run_engine(chip, false);
		वापस 0;
	पूर्ण

	ptn = chip->pdata->patterns + (mode - 1);
	अगर (!ptn || _is_pc_overflow(ptn)) अणु
		dev_err(&chip->cl->dev, "invalid pattern data\n");
		वापस -EINVAL;
	पूर्ण

	lp5562_stop_engine(chip);

	/* Set LED map as RGB */
	lp55xx_ग_लिखो(chip, LP5562_REG_ENG_SEL, LP5562_ENG_SEL_RGB);

	/* Load engines */
	क्रम (i = LP55XX_ENGINE_1; i <= LP55XX_ENGINE_3; i++) अणु
		chip->engine_idx = i;
		lp5562_load_engine(chip);
	पूर्ण

	/* Clear program रेजिस्टरs */
	lp55xx_ग_लिखो(chip, LP5562_REG_PROG_MEM_ENG1, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_PROG_MEM_ENG1 + 1, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_PROG_MEM_ENG2, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_PROG_MEM_ENG2 + 1, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_PROG_MEM_ENG3, 0);
	lp55xx_ग_लिखो(chip, LP5562_REG_PROG_MEM_ENG3 + 1, 0);

	/* Program engines */
	lp5562_ग_लिखो_program_memory(chip, LP5562_REG_PROG_MEM_ENG1,
				ptn->r, ptn->size_r);
	lp5562_ग_लिखो_program_memory(chip, LP5562_REG_PROG_MEM_ENG2,
				ptn->g, ptn->size_g);
	lp5562_ग_लिखो_program_memory(chip, LP5562_REG_PROG_MEM_ENG3,
				ptn->b, ptn->size_b);

	/* Run engines */
	lp5562_run_engine(chip, true);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार lp5562_store_pattern(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	काष्ठा lp55xx_predef_pattern *ptn = chip->pdata->patterns;
	पूर्णांक num_patterns = chip->pdata->num_patterns;
	अचिन्हित दीर्घ mode;
	पूर्णांक ret;

	ret = kम_से_अदीर्घ(buf, 0, &mode);
	अगर (ret)
		वापस ret;

	अगर (mode > num_patterns || !ptn)
		वापस -EINVAL;

	mutex_lock(&chip->lock);
	ret = lp5562_run_predef_led_pattern(chip, mode);
	mutex_unlock(&chip->lock);

	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

अटल sमाप_प्रकार lp5562_store_engine_mux(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	u8 mask;
	u8 val;

	/* LED map
	 * R ... Engine 1 (fixed)
	 * G ... Engine 2 (fixed)
	 * B ... Engine 3 (fixed)
	 * W ... Engine 1 or 2 or 3
	 */

	अगर (sysfs_streq(buf, "RGB")) अणु
		mask = LP5562_ENG_FOR_RGB_M;
		val = LP5562_ENG_SEL_RGB;
	पूर्ण अन्यथा अगर (sysfs_streq(buf, "W")) अणु
		क्रमागत lp55xx_engine_index idx = chip->engine_idx;

		mask = LP5562_ENG_FOR_W_M;
		चयन (idx) अणु
		हाल LP55XX_ENGINE_1:
			val = LP5562_ENG1_FOR_W;
			अवरोध;
		हाल LP55XX_ENGINE_2:
			val = LP5562_ENG2_FOR_W;
			अवरोध;
		हाल LP55XX_ENGINE_3:
			val = LP5562_ENG3_FOR_W;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

	पूर्ण अन्यथा अणु
		dev_err(dev, "choose RGB or W\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&chip->lock);
	lp55xx_update_bits(chip, LP5562_REG_ENG_SEL, mask, val);
	mutex_unlock(&chip->lock);

	वापस len;
पूर्ण

अटल LP55XX_DEV_ATTR_WO(led_pattern, lp5562_store_pattern);
अटल LP55XX_DEV_ATTR_WO(engine_mux, lp5562_store_engine_mux);

अटल काष्ठा attribute *lp5562_attributes[] = अणु
	&dev_attr_led_pattern.attr,
	&dev_attr_engine_mux.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lp5562_group = अणु
	.attrs = lp5562_attributes,
पूर्ण;

/* Chip specअगरic configurations */
अटल काष्ठा lp55xx_device_config lp5562_cfg = अणु
	.max_channel  = LP5562_MAX_LEDS,
	.reset = अणु
		.addr = LP5562_REG_RESET,
		.val  = LP5562_RESET,
	पूर्ण,
	.enable = अणु
		.addr = LP5562_REG_ENABLE,
		.val  = LP5562_ENABLE_DEFAULT,
	पूर्ण,
	.post_init_device   = lp5562_post_init_device,
	.set_led_current    = lp5562_set_led_current,
	.brightness_fn      = lp5562_led_brightness,
	.run_engine         = lp5562_run_engine,
	.firmware_cb        = lp5562_firmware_loaded,
	.dev_attr_group     = &lp5562_group,
पूर्ण;

अटल पूर्णांक lp5562_probe(काष्ठा i2c_client *client,
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

	chip->cfg = &lp5562_cfg;

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

अटल पूर्णांक lp5562_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(client);
	काष्ठा lp55xx_chip *chip = led->chip;

	lp5562_stop_engine(chip);

	lp55xx_unरेजिस्टर_sysfs(chip);
	lp55xx_deinit_device(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp5562_id[] = अणु
	अणु "lp5562", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, lp5562_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_lp5562_leds_match[] = अणु
	अणु .compatible = "ti,lp5562", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_lp5562_leds_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver lp5562_driver = अणु
	.driver = अणु
		.name	= "lp5562",
		.of_match_table = of_match_ptr(of_lp5562_leds_match),
	पूर्ण,
	.probe		= lp5562_probe,
	.हटाओ		= lp5562_हटाओ,
	.id_table	= lp5562_id,
पूर्ण;

module_i2c_driver(lp5562_driver);

MODULE_DESCRIPTION("Texas Instruments LP5562 LED Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
