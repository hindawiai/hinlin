<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * lp5523.c - LP5523, LP55231 LED Driver
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
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/leds-lp55xx.h>
#समावेश <linux/slab.h>

#समावेश "leds-lp55xx-common.h"

#घोषणा LP5523_PROGRAM_LENGTH		32	/* bytes */
/* Memory is used like this:
 * 0x00 engine 1 program
 * 0x10 engine 2 program
 * 0x20 engine 3 program
 * 0x30 engine 1 muxing info
 * 0x40 engine 2 muxing info
 * 0x50 engine 3 muxing info
 */
#घोषणा LP5523_MAX_LEDS			9

/* Registers */
#घोषणा LP5523_REG_ENABLE		0x00
#घोषणा LP5523_REG_OP_MODE		0x01
#घोषणा LP5523_REG_ENABLE_LEDS_MSB	0x04
#घोषणा LP5523_REG_ENABLE_LEDS_LSB	0x05
#घोषणा LP5523_REG_LED_CTRL_BASE	0x06
#घोषणा LP5523_REG_LED_PWM_BASE		0x16
#घोषणा LP5523_REG_LED_CURRENT_BASE	0x26
#घोषणा LP5523_REG_CONFIG		0x36
#घोषणा LP5523_REG_STATUS		0x3A
#घोषणा LP5523_REG_RESET		0x3D
#घोषणा LP5523_REG_LED_TEST_CTRL	0x41
#घोषणा LP5523_REG_LED_TEST_ADC		0x42
#घोषणा LP5523_REG_MASTER_FADER_BASE	0x48
#घोषणा LP5523_REG_CH1_PROG_START	0x4C
#घोषणा LP5523_REG_CH2_PROG_START	0x4D
#घोषणा LP5523_REG_CH3_PROG_START	0x4E
#घोषणा LP5523_REG_PROG_PAGE_SEL	0x4F
#घोषणा LP5523_REG_PROG_MEM		0x50

/* Bit description in रेजिस्टरs */
#घोषणा LP5523_ENABLE			0x40
#घोषणा LP5523_AUTO_INC			0x40
#घोषणा LP5523_PWR_SAVE			0x20
#घोषणा LP5523_PWM_PWR_SAVE		0x04
#घोषणा LP5523_CP_AUTO			0x18
#घोषणा LP5523_AUTO_CLK			0x02

#घोषणा LP5523_EN_LEDTEST		0x80
#घोषणा LP5523_LEDTEST_DONE		0x80
#घोषणा LP5523_RESET			0xFF
#घोषणा LP5523_ADC_SHORTCIRC_LIM	80
#घोषणा LP5523_EXT_CLK_USED		0x08
#घोषणा LP5523_ENG_STATUS_MASK		0x07

#घोषणा LP5523_FADER_MAPPING_MASK	0xC0
#घोषणा LP5523_FADER_MAPPING_SHIFT	6

/* Memory Page Selection */
#घोषणा LP5523_PAGE_ENG1		0
#घोषणा LP5523_PAGE_ENG2		1
#घोषणा LP5523_PAGE_ENG3		2
#घोषणा LP5523_PAGE_MUX1		3
#घोषणा LP5523_PAGE_MUX2		4
#घोषणा LP5523_PAGE_MUX3		5

/* Program Memory Operations */
#घोषणा LP5523_MODE_ENG1_M		0x30	/* Operation Mode Register */
#घोषणा LP5523_MODE_ENG2_M		0x0C
#घोषणा LP5523_MODE_ENG3_M		0x03
#घोषणा LP5523_LOAD_ENG1		0x10
#घोषणा LP5523_LOAD_ENG2		0x04
#घोषणा LP5523_LOAD_ENG3		0x01

#घोषणा LP5523_ENG1_IS_LOADING(mode)	\
	((mode & LP5523_MODE_ENG1_M) == LP5523_LOAD_ENG1)
#घोषणा LP5523_ENG2_IS_LOADING(mode)	\
	((mode & LP5523_MODE_ENG2_M) == LP5523_LOAD_ENG2)
#घोषणा LP5523_ENG3_IS_LOADING(mode)	\
	((mode & LP5523_MODE_ENG3_M) == LP5523_LOAD_ENG3)

#घोषणा LP5523_EXEC_ENG1_M		0x30	/* Enable Register */
#घोषणा LP5523_EXEC_ENG2_M		0x0C
#घोषणा LP5523_EXEC_ENG3_M		0x03
#घोषणा LP5523_EXEC_M			0x3F
#घोषणा LP5523_RUN_ENG1			0x20
#घोषणा LP5523_RUN_ENG2			0x08
#घोषणा LP5523_RUN_ENG3			0x02

#घोषणा LED_ACTIVE(mux, led)		(!!(mux & (0x0001 << led)))

क्रमागत lp5523_chip_id अणु
	LP5523,
	LP55231,
पूर्ण;

अटल पूर्णांक lp5523_init_program_engine(काष्ठा lp55xx_chip *chip);

अटल अंतरभूत व्योम lp5523_रुको_opmode_करोne(व्योम)
अणु
	usleep_range(1000, 2000);
पूर्ण

अटल व्योम lp5523_set_led_current(काष्ठा lp55xx_led *led, u8 led_current)
अणु
	led->led_current = led_current;
	lp55xx_ग_लिखो(led->chip, LP5523_REG_LED_CURRENT_BASE + led->chan_nr,
		led_current);
पूर्ण

अटल पूर्णांक lp5523_post_init_device(काष्ठा lp55xx_chip *chip)
अणु
	पूर्णांक ret;

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_ENABLE, LP5523_ENABLE);
	अगर (ret)
		वापस ret;

	/* Chip startup समय is 500 us, 1 - 2 ms gives some margin */
	usleep_range(1000, 2000);

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_CONFIG,
			    LP5523_AUTO_INC | LP5523_PWR_SAVE |
			    LP5523_CP_AUTO | LP5523_AUTO_CLK |
			    LP5523_PWM_PWR_SAVE);
	अगर (ret)
		वापस ret;

	/* turn on all leds */
	ret = lp55xx_ग_लिखो(chip, LP5523_REG_ENABLE_LEDS_MSB, 0x01);
	अगर (ret)
		वापस ret;

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_ENABLE_LEDS_LSB, 0xff);
	अगर (ret)
		वापस ret;

	वापस lp5523_init_program_engine(chip);
पूर्ण

अटल व्योम lp5523_load_engine(काष्ठा lp55xx_chip *chip)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	अटल स्थिर u8 mask[] = अणु
		[LP55XX_ENGINE_1] = LP5523_MODE_ENG1_M,
		[LP55XX_ENGINE_2] = LP5523_MODE_ENG2_M,
		[LP55XX_ENGINE_3] = LP5523_MODE_ENG3_M,
	पूर्ण;

	अटल स्थिर u8 val[] = अणु
		[LP55XX_ENGINE_1] = LP5523_LOAD_ENG1,
		[LP55XX_ENGINE_2] = LP5523_LOAD_ENG2,
		[LP55XX_ENGINE_3] = LP5523_LOAD_ENG3,
	पूर्ण;

	lp55xx_update_bits(chip, LP5523_REG_OP_MODE, mask[idx], val[idx]);

	lp5523_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5523_load_engine_and_select_page(काष्ठा lp55xx_chip *chip)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	अटल स्थिर u8 page_sel[] = अणु
		[LP55XX_ENGINE_1] = LP5523_PAGE_ENG1,
		[LP55XX_ENGINE_2] = LP5523_PAGE_ENG2,
		[LP55XX_ENGINE_3] = LP5523_PAGE_ENG3,
	पूर्ण;

	lp5523_load_engine(chip);

	lp55xx_ग_लिखो(chip, LP5523_REG_PROG_PAGE_SEL, page_sel[idx]);
पूर्ण

अटल व्योम lp5523_stop_all_engines(काष्ठा lp55xx_chip *chip)
अणु
	lp55xx_ग_लिखो(chip, LP5523_REG_OP_MODE, 0);
	lp5523_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5523_stop_engine(काष्ठा lp55xx_chip *chip)
अणु
	क्रमागत lp55xx_engine_index idx = chip->engine_idx;
	अटल स्थिर u8 mask[] = अणु
		[LP55XX_ENGINE_1] = LP5523_MODE_ENG1_M,
		[LP55XX_ENGINE_2] = LP5523_MODE_ENG2_M,
		[LP55XX_ENGINE_3] = LP5523_MODE_ENG3_M,
	पूर्ण;

	lp55xx_update_bits(chip, LP5523_REG_OP_MODE, mask[idx], 0);

	lp5523_रुको_opmode_करोne();
पूर्ण

अटल व्योम lp5523_turn_off_channels(काष्ठा lp55xx_chip *chip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LP5523_MAX_LEDS; i++)
		lp55xx_ग_लिखो(chip, LP5523_REG_LED_PWM_BASE + i, 0);
पूर्ण

अटल व्योम lp5523_run_engine(काष्ठा lp55xx_chip *chip, bool start)
अणु
	पूर्णांक ret;
	u8 mode;
	u8 exec;

	/* stop engine */
	अगर (!start) अणु
		lp5523_stop_engine(chip);
		lp5523_turn_off_channels(chip);
		वापस;
	पूर्ण

	/*
	 * To run the engine,
	 * operation mode and enable रेजिस्टर should updated at the same समय
	 */

	ret = lp55xx_पढ़ो(chip, LP5523_REG_OP_MODE, &mode);
	अगर (ret)
		वापस;

	ret = lp55xx_पढ़ो(chip, LP5523_REG_ENABLE, &exec);
	अगर (ret)
		वापस;

	/* change operation mode to RUN only when each engine is loading */
	अगर (LP5523_ENG1_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5523_MODE_ENG1_M) | LP5523_RUN_ENG1;
		exec = (exec & ~LP5523_EXEC_ENG1_M) | LP5523_RUN_ENG1;
	पूर्ण

	अगर (LP5523_ENG2_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5523_MODE_ENG2_M) | LP5523_RUN_ENG2;
		exec = (exec & ~LP5523_EXEC_ENG2_M) | LP5523_RUN_ENG2;
	पूर्ण

	अगर (LP5523_ENG3_IS_LOADING(mode)) अणु
		mode = (mode & ~LP5523_MODE_ENG3_M) | LP5523_RUN_ENG3;
		exec = (exec & ~LP5523_EXEC_ENG3_M) | LP5523_RUN_ENG3;
	पूर्ण

	lp55xx_ग_लिखो(chip, LP5523_REG_OP_MODE, mode);
	lp5523_रुको_opmode_करोne();

	lp55xx_update_bits(chip, LP5523_REG_ENABLE, LP5523_EXEC_M, exec);
पूर्ण

अटल पूर्णांक lp5523_init_program_engine(काष्ठा lp55xx_chip *chip)
अणु
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक ret;
	u8 status;
	/* one pattern per engine setting LED MUX start and stop addresses */
	अटल स्थिर u8 pattern[][LP5523_PROGRAM_LENGTH] =  अणु
		अणु 0x9c, 0x30, 0x9c, 0xb0, 0x9d, 0x80, 0xd8, 0x00, 0पूर्ण,
		अणु 0x9c, 0x40, 0x9c, 0xc0, 0x9d, 0x80, 0xd8, 0x00, 0पूर्ण,
		अणु 0x9c, 0x50, 0x9c, 0xd0, 0x9d, 0x80, 0xd8, 0x00, 0पूर्ण,
	पूर्ण;

	/* hardcode 32 bytes of memory क्रम each engine from program memory */
	ret = lp55xx_ग_लिखो(chip, LP5523_REG_CH1_PROG_START, 0x00);
	अगर (ret)
		वापस ret;

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_CH2_PROG_START, 0x10);
	अगर (ret)
		वापस ret;

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_CH3_PROG_START, 0x20);
	अगर (ret)
		वापस ret;

	/* ग_लिखो LED MUX address space क्रम each engine */
	क्रम (i = LP55XX_ENGINE_1; i <= LP55XX_ENGINE_3; i++) अणु
		chip->engine_idx = i;
		lp5523_load_engine_and_select_page(chip);

		क्रम (j = 0; j < LP5523_PROGRAM_LENGTH; j++) अणु
			ret = lp55xx_ग_लिखो(chip, LP5523_REG_PROG_MEM + j,
					pattern[i - 1][j]);
			अगर (ret)
				जाओ out;
		पूर्ण
	पूर्ण

	lp5523_run_engine(chip, true);

	/* Let the programs run क्रम couple of ms and check the engine status */
	usleep_range(3000, 6000);
	ret = lp55xx_पढ़ो(chip, LP5523_REG_STATUS, &status);
	अगर (ret)
		जाओ out;
	status &= LP5523_ENG_STATUS_MASK;

	अगर (status != LP5523_ENG_STATUS_MASK) अणु
		dev_err(&chip->cl->dev,
			"could not configure LED engine, status = 0x%.2x\n",
			status);
		ret = -1;
	पूर्ण

out:
	lp5523_stop_all_engines(chip);
	वापस ret;
पूर्ण

अटल पूर्णांक lp5523_update_program_memory(काष्ठा lp55xx_chip *chip,
					स्थिर u8 *data, माप_प्रकार size)
अणु
	u8 pattern[LP5523_PROGRAM_LENGTH] = अणु0पूर्ण;
	अचिन्हित पूर्णांक cmd;
	अक्षर c[3];
	पूर्णांक nrअक्षरs;
	पूर्णांक ret;
	पूर्णांक offset = 0;
	पूर्णांक i = 0;

	जबतक ((offset < size - 1) && (i < LP5523_PROGRAM_LENGTH)) अणु
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

	क्रम (i = 0; i < LP5523_PROGRAM_LENGTH; i++) अणु
		ret = lp55xx_ग_लिखो(chip, LP5523_REG_PROG_MEM + i, pattern[i]);
		अगर (ret)
			वापस -EINVAL;
	पूर्ण

	वापस size;

err:
	dev_err(&chip->cl->dev, "wrong pattern format\n");
	वापस -EINVAL;
पूर्ण

अटल व्योम lp5523_firmware_loaded(काष्ठा lp55xx_chip *chip)
अणु
	स्थिर काष्ठा firmware *fw = chip->fw;

	अगर (fw->size > LP5523_PROGRAM_LENGTH) अणु
		dev_err(&chip->cl->dev, "firmware data size overflow: %zu\n",
			fw->size);
		वापस;
	पूर्ण

	/*
	 * Program memory sequence
	 *  1) set engine mode to "LOAD"
	 *  2) ग_लिखो firmware data पूर्णांकo program memory
	 */

	lp5523_load_engine_and_select_page(chip);
	lp5523_update_program_memory(chip, fw->data, fw->size);
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
		lp5523_run_engine(chip, true);
		engine->mode = LP55XX_ENGINE_RUN;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "load", 4)) अणु
		lp5523_stop_engine(chip);
		lp5523_load_engine(chip);
		engine->mode = LP55XX_ENGINE_LOAD;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "disabled", 8)) अणु
		lp5523_stop_engine(chip);
		engine->mode = LP55XX_ENGINE_DISABLED;
	पूर्ण

	mutex_unlock(&chip->lock);

	वापस len;
पूर्ण
store_mode(1)
store_mode(2)
store_mode(3)

अटल पूर्णांक lp5523_mux_parse(स्थिर अक्षर *buf, u16 *mux, माप_प्रकार len)
अणु
	u16 पंचांगp_mux = 0;
	पूर्णांक i;

	len = min_t(पूर्णांक, len, LP5523_MAX_LEDS);

	क्रम (i = 0; i < len; i++) अणु
		चयन (buf[i]) अणु
		हाल '1':
			पंचांगp_mux |= (1 << i);
			अवरोध;
		हाल '0':
			अवरोध;
		हाल '\n':
			i = len;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण
	*mux = पंचांगp_mux;

	वापस 0;
पूर्ण

अटल व्योम lp5523_mux_to_array(u16 led_mux, अक्षर *array)
अणु
	पूर्णांक i, pos = 0;

	क्रम (i = 0; i < LP5523_MAX_LEDS; i++)
		pos += प्र_लिखो(array + pos, "%x", LED_ACTIVE(led_mux, i));

	array[pos] = '\0';
पूर्ण

अटल sमाप_प्रकार show_engine_leds(काष्ठा device *dev,
			    काष्ठा device_attribute *attr,
			    अक्षर *buf, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	अक्षर mux[LP5523_MAX_LEDS + 1];

	lp5523_mux_to_array(chip->engines[nr - 1].led_mux, mux);

	वापस प्र_लिखो(buf, "%s\n", mux);
पूर्ण
show_leds(1)
show_leds(2)
show_leds(3)

अटल पूर्णांक lp5523_load_mux(काष्ठा lp55xx_chip *chip, u16 mux, पूर्णांक nr)
अणु
	काष्ठा lp55xx_engine *engine = &chip->engines[nr - 1];
	पूर्णांक ret;
	अटल स्थिर u8 mux_page[] = अणु
		[LP55XX_ENGINE_1] = LP5523_PAGE_MUX1,
		[LP55XX_ENGINE_2] = LP5523_PAGE_MUX2,
		[LP55XX_ENGINE_3] = LP5523_PAGE_MUX3,
	पूर्ण;

	lp5523_load_engine(chip);

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_PROG_PAGE_SEL, mux_page[nr]);
	अगर (ret)
		वापस ret;

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_PROG_MEM, (u8)(mux >> 8));
	अगर (ret)
		वापस ret;

	ret = lp55xx_ग_लिखो(chip, LP5523_REG_PROG_MEM + 1, (u8)(mux));
	अगर (ret)
		वापस ret;

	engine->led_mux = mux;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार store_engine_leds(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	काष्ठा lp55xx_engine *engine = &chip->engines[nr - 1];
	u16 mux = 0;
	sमाप_प्रकार ret;

	अगर (lp5523_mux_parse(buf, &mux, len))
		वापस -EINVAL;

	mutex_lock(&chip->lock);

	chip->engine_idx = nr;
	ret = -EINVAL;

	अगर (engine->mode != LP55XX_ENGINE_LOAD)
		जाओ leave;

	अगर (lp5523_load_mux(chip, mux, nr))
		जाओ leave;

	ret = len;
leave:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण
store_leds(1)
store_leds(2)
store_leds(3)

अटल sमाप_प्रकार store_engine_load(काष्ठा device *dev,
			     काष्ठा device_attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार len, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	chip->engine_idx = nr;
	lp5523_load_engine_and_select_page(chip);
	ret = lp5523_update_program_memory(chip, buf, len);

	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण
store_load(1)
store_load(2)
store_load(3)

अटल sमाप_प्रकार lp5523_selftest(काष्ठा device *dev,
			       काष्ठा device_attribute *attr,
			       अक्षर *buf)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	काष्ठा lp55xx_platक्रमm_data *pdata = chip->pdata;
	पूर्णांक i, ret, pos = 0;
	u8 status, adc, vdd;

	mutex_lock(&chip->lock);

	ret = lp55xx_पढ़ो(chip, LP5523_REG_STATUS, &status);
	अगर (ret < 0)
		जाओ fail;

	/* Check that ext घड़ी is really in use अगर requested */
	अगर (pdata->घड़ी_mode == LP55XX_CLOCK_EXT) अणु
		अगर  ((status & LP5523_EXT_CLK_USED) == 0)
			जाओ fail;
	पूर्ण

	/* Measure VDD (i.e. VBAT) first (channel 16 corresponds to VDD) */
	lp55xx_ग_लिखो(chip, LP5523_REG_LED_TEST_CTRL, LP5523_EN_LEDTEST | 16);
	usleep_range(3000, 6000); /* ADC conversion समय is typically 2.7 ms */
	ret = lp55xx_पढ़ो(chip, LP5523_REG_STATUS, &status);
	अगर (ret < 0)
		जाओ fail;

	अगर (!(status & LP5523_LEDTEST_DONE))
		usleep_range(3000, 6000); /* Was not पढ़ोy. Wait little bit */

	ret = lp55xx_पढ़ो(chip, LP5523_REG_LED_TEST_ADC, &vdd);
	अगर (ret < 0)
		जाओ fail;

	vdd--;	/* There may be some fluctuation in measurement */

	क्रम (i = 0; i < LP5523_MAX_LEDS; i++) अणु
		/* Skip non-existing channels */
		अगर (pdata->led_config[i].led_current == 0)
			जारी;

		/* Set शेष current */
		lp55xx_ग_लिखो(chip, LP5523_REG_LED_CURRENT_BASE + i,
			pdata->led_config[i].led_current);

		lp55xx_ग_लिखो(chip, LP5523_REG_LED_PWM_BASE + i, 0xff);
		/* let current stabilize 2 - 4ms beक्रमe measurements start */
		usleep_range(2000, 4000);
		lp55xx_ग_लिखो(chip, LP5523_REG_LED_TEST_CTRL,
			     LP5523_EN_LEDTEST | i);
		/* ADC conversion समय is 2.7 ms typically */
		usleep_range(3000, 6000);
		ret = lp55xx_पढ़ो(chip, LP5523_REG_STATUS, &status);
		अगर (ret < 0)
			जाओ fail;

		अगर (!(status & LP5523_LEDTEST_DONE))
			usleep_range(3000, 6000);/* Was not पढ़ोy. Wait. */

		ret = lp55xx_पढ़ो(chip, LP5523_REG_LED_TEST_ADC, &adc);
		अगर (ret < 0)
			जाओ fail;

		अगर (adc >= vdd || adc < LP5523_ADC_SHORTCIRC_LIM)
			pos += प्र_लिखो(buf + pos, "LED %d FAIL\n", i);

		lp55xx_ग_लिखो(chip, LP5523_REG_LED_PWM_BASE + i, 0x00);

		/* Restore current */
		lp55xx_ग_लिखो(chip, LP5523_REG_LED_CURRENT_BASE + i,
			led->led_current);
		led++;
	पूर्ण
	अगर (pos == 0)
		pos = प्र_लिखो(buf, "OK\n");
	जाओ release_lock;
fail:
	pos = प्र_लिखो(buf, "FAIL\n");

release_lock:
	mutex_unlock(&chip->lock);

	वापस pos;
पूर्ण

#घोषणा show_fader(nr)						\
अटल sमाप_प्रकार show_master_fader##nr(काष्ठा device *dev,	\
			    काष्ठा device_attribute *attr,	\
			    अक्षर *buf)				\
अणु								\
	वापस show_master_fader(dev, attr, buf, nr);		\
पूर्ण

#घोषणा store_fader(nr)						\
अटल sमाप_प्रकार store_master_fader##nr(काष्ठा device *dev,	\
			     काष्ठा device_attribute *attr,	\
			     स्थिर अक्षर *buf, माप_प्रकार len)	\
अणु								\
	वापस store_master_fader(dev, attr, buf, len, nr);	\
पूर्ण

अटल sमाप_प्रकार show_master_fader(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;
	u8 val;

	mutex_lock(&chip->lock);
	ret = lp55xx_पढ़ो(chip, LP5523_REG_MASTER_FADER_BASE + nr - 1, &val);
	mutex_unlock(&chip->lock);

	अगर (ret == 0)
		ret = प्र_लिखो(buf, "%u\n", val);

	वापस ret;
पूर्ण
show_fader(1)
show_fader(2)
show_fader(3)

अटल sमाप_प्रकार store_master_fader(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार len, पूर्णांक nr)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 0, &val))
		वापस -EINVAL;

	अगर (val > 0xff)
		वापस -EINVAL;

	mutex_lock(&chip->lock);
	ret = lp55xx_ग_लिखो(chip, LP5523_REG_MASTER_FADER_BASE + nr - 1,
			   (u8)val);
	mutex_unlock(&chip->lock);

	अगर (ret == 0)
		ret = len;

	वापस ret;
पूर्ण
store_fader(1)
store_fader(2)
store_fader(3)

अटल sमाप_प्रकार show_master_fader_leds(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक i, ret, pos = 0;
	u8 val;

	mutex_lock(&chip->lock);

	क्रम (i = 0; i < LP5523_MAX_LEDS; i++) अणु
		ret = lp55xx_पढ़ो(chip, LP5523_REG_LED_CTRL_BASE + i, &val);
		अगर (ret)
			जाओ leave;

		val = (val & LP5523_FADER_MAPPING_MASK)
			>> LP5523_FADER_MAPPING_SHIFT;
		अगर (val > 3) अणु
			ret = -EINVAL;
			जाओ leave;
		पूर्ण
		buf[pos++] = val + '0';
	पूर्ण
	buf[pos++] = '\n';
	ret = pos;
leave:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार store_master_fader_leds(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक i, n, ret;
	u8 val;

	n = min_t(पूर्णांक, len, LP5523_MAX_LEDS);

	mutex_lock(&chip->lock);

	क्रम (i = 0; i < n; i++) अणु
		अगर (buf[i] >= '0' && buf[i] <= '3') अणु
			val = (buf[i] - '0') << LP5523_FADER_MAPPING_SHIFT;
			ret = lp55xx_update_bits(chip,
						 LP5523_REG_LED_CTRL_BASE + i,
						 LP5523_FADER_MAPPING_MASK,
						 val);
			अगर (ret)
				जाओ leave;
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ leave;
		पूर्ण
	पूर्ण
	ret = len;
leave:
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lp5523_multicolor_brightness(काष्ठा lp55xx_led *led)
अणु
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&chip->lock);
	क्रम (i = 0; i < led->mc_cdev.num_colors; i++) अणु
		ret = lp55xx_ग_लिखो(chip,
				   LP5523_REG_LED_PWM_BASE +
				   led->mc_cdev.subled_info[i].channel,
				   led->mc_cdev.subled_info[i].brightness);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक lp5523_led_brightness(काष्ठा lp55xx_led *led)
अणु
	काष्ठा lp55xx_chip *chip = led->chip;
	पूर्णांक ret;

	mutex_lock(&chip->lock);
	ret = lp55xx_ग_लिखो(chip, LP5523_REG_LED_PWM_BASE + led->chan_nr,
		     led->brightness);
	mutex_unlock(&chip->lock);
	वापस ret;
पूर्ण

अटल LP55XX_DEV_ATTR_RW(engine1_mode, show_engine1_mode, store_engine1_mode);
अटल LP55XX_DEV_ATTR_RW(engine2_mode, show_engine2_mode, store_engine2_mode);
अटल LP55XX_DEV_ATTR_RW(engine3_mode, show_engine3_mode, store_engine3_mode);
अटल LP55XX_DEV_ATTR_RW(engine1_leds, show_engine1_leds, store_engine1_leds);
अटल LP55XX_DEV_ATTR_RW(engine2_leds, show_engine2_leds, store_engine2_leds);
अटल LP55XX_DEV_ATTR_RW(engine3_leds, show_engine3_leds, store_engine3_leds);
अटल LP55XX_DEV_ATTR_WO(engine1_load, store_engine1_load);
अटल LP55XX_DEV_ATTR_WO(engine2_load, store_engine2_load);
अटल LP55XX_DEV_ATTR_WO(engine3_load, store_engine3_load);
अटल LP55XX_DEV_ATTR_RO(selftest, lp5523_selftest);
अटल LP55XX_DEV_ATTR_RW(master_fader1, show_master_fader1,
			  store_master_fader1);
अटल LP55XX_DEV_ATTR_RW(master_fader2, show_master_fader2,
			  store_master_fader2);
अटल LP55XX_DEV_ATTR_RW(master_fader3, show_master_fader3,
			  store_master_fader3);
अटल LP55XX_DEV_ATTR_RW(master_fader_leds, show_master_fader_leds,
			  store_master_fader_leds);

अटल काष्ठा attribute *lp5523_attributes[] = अणु
	&dev_attr_engine1_mode.attr,
	&dev_attr_engine2_mode.attr,
	&dev_attr_engine3_mode.attr,
	&dev_attr_engine1_load.attr,
	&dev_attr_engine2_load.attr,
	&dev_attr_engine3_load.attr,
	&dev_attr_engine1_leds.attr,
	&dev_attr_engine2_leds.attr,
	&dev_attr_engine3_leds.attr,
	&dev_attr_selftest.attr,
	&dev_attr_master_fader1.attr,
	&dev_attr_master_fader2.attr,
	&dev_attr_master_fader3.attr,
	&dev_attr_master_fader_leds.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group lp5523_group = अणु
	.attrs = lp5523_attributes,
पूर्ण;

/* Chip specअगरic configurations */
अटल काष्ठा lp55xx_device_config lp5523_cfg = अणु
	.reset = अणु
		.addr = LP5523_REG_RESET,
		.val  = LP5523_RESET,
	पूर्ण,
	.enable = अणु
		.addr = LP5523_REG_ENABLE,
		.val  = LP5523_ENABLE,
	पूर्ण,
	.max_channel  = LP5523_MAX_LEDS,
	.post_init_device   = lp5523_post_init_device,
	.brightness_fn      = lp5523_led_brightness,
	.multicolor_brightness_fn = lp5523_multicolor_brightness,
	.set_led_current    = lp5523_set_led_current,
	.firmware_cb        = lp5523_firmware_loaded,
	.run_engine         = lp5523_run_engine,
	.dev_attr_group     = &lp5523_group,
पूर्ण;

अटल पूर्णांक lp5523_probe(काष्ठा i2c_client *client,
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

	chip->cfg = &lp5523_cfg;

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

अटल पूर्णांक lp5523_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा lp55xx_led *led = i2c_get_clientdata(client);
	काष्ठा lp55xx_chip *chip = led->chip;

	lp5523_stop_all_engines(chip);
	lp55xx_unरेजिस्टर_sysfs(chip);
	lp55xx_deinit_device(chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id lp5523_id[] = अणु
	अणु "lp5523",  LP5523 पूर्ण,
	अणु "lp55231", LP55231 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, lp5523_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id of_lp5523_leds_match[] = अणु
	अणु .compatible = "national,lp5523", पूर्ण,
	अणु .compatible = "ti,lp55231", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, of_lp5523_leds_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver lp5523_driver = अणु
	.driver = अणु
		.name	= "lp5523x",
		.of_match_table = of_match_ptr(of_lp5523_leds_match),
	पूर्ण,
	.probe		= lp5523_probe,
	.हटाओ		= lp5523_हटाओ,
	.id_table	= lp5523_id,
पूर्ण;

module_i2c_driver(lp5523_driver);

MODULE_AUTHOR("Mathias Nyman <mathias.nyman@nokia.com>");
MODULE_AUTHOR("Milo Kim <milo.kim@ti.com>");
MODULE_DESCRIPTION("LP5523 LED engine");
MODULE_LICENSE("GPL");
