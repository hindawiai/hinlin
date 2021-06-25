<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * g762 - Driver क्रम the Global Mixed-mode Technology Inc. fan speed
 *        PWM controller chips from G762 family, i.e. G762 and G763
 *
 * Copyright (C) 2013, Arnaud EBALARD <arno@natisbad.org>
 *
 * This work is based on a basic version क्रम 2.6.31 kernel developed
 * by Olivier Mouchet क्रम LaCie. Updates and correction have been
 * perक्रमmed to run on recent kernels. Additional features, like the
 * ability to configure various अक्षरacteristics via .dts file or
 * board init file have been added. Detailed datasheet on which this
 * development is based is available here:
 *
 *  http://natisbad.org/NAS/refs/GMT_EDS-762_763-080710-0.2.pdf
 *
 * Headers from previous developments have been kept below:
 *
 * Copyright (c) 2009 LaCie
 *
 * Author: Olivier Mouchet <olivier.mouchet@gmail.com>
 *
 * based on g760a code written by Herbert Valerio Riedel <hvr@gnu.org>
 * Copyright (C) 2007  Herbert Valerio Riedel <hvr@gnu.org>
 *
 * g762: minimal datasheet available at:
 *       http://www.gmt.com.tw/product/datasheet/EDS-762_3.pdf
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_data/g762.h>

#घोषणा DRVNAME "g762"

अटल स्थिर काष्ठा i2c_device_id g762_id[] = अणु
	अणु "g762", 0 पूर्ण,
	अणु "g763", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, g762_id);

क्रमागत g762_regs अणु
	G762_REG_SET_CNT  = 0x00,
	G762_REG_ACT_CNT  = 0x01,
	G762_REG_FAN_STA  = 0x02,
	G762_REG_SET_OUT  = 0x03,
	G762_REG_FAN_CMD1 = 0x04,
	G762_REG_FAN_CMD2 = 0x05,
पूर्ण;

/* Config रेजिस्टर bits */
#घोषणा G762_REG_FAN_CMD1_DET_FAN_FAIL  0x80 /* enable fan_fail संकेत */
#घोषणा G762_REG_FAN_CMD1_DET_FAN_OOC   0x40 /* enable fan_out_of_control */
#घोषणा G762_REG_FAN_CMD1_OUT_MODE      0x20 /* out mode: PWM or DC */
#घोषणा G762_REG_FAN_CMD1_FAN_MODE      0x10 /* fan mode: बंदd/खोलो-loop */
#घोषणा G762_REG_FAN_CMD1_CLK_DIV_ID1   0x08 /* घड़ी भागisor value */
#घोषणा G762_REG_FAN_CMD1_CLK_DIV_ID0   0x04
#घोषणा G762_REG_FAN_CMD1_PWM_POLARITY  0x02 /* PWM polarity */
#घोषणा G762_REG_FAN_CMD1_PULSE_PER_REV 0x01 /* pulse per fan revolution */

#घोषणा G762_REG_FAN_CMD2_GEAR_MODE_1   0x08 /* fan gear mode */
#घोषणा G762_REG_FAN_CMD2_GEAR_MODE_0   0x04
#घोषणा G762_REG_FAN_CMD2_FAN_STARTV_1  0x02 /* fan startup voltage */
#घोषणा G762_REG_FAN_CMD2_FAN_STARTV_0  0x01

#घोषणा G762_REG_FAN_STA_FAIL           0x02 /* fan fail */
#घोषणा G762_REG_FAN_STA_OOC            0x01 /* fan out of control */

/* Config रेजिस्टर values */
#घोषणा G762_OUT_MODE_PWM            1
#घोषणा G762_OUT_MODE_DC             0

#घोषणा G762_FAN_MODE_CLOSED_LOOP    2
#घोषणा G762_FAN_MODE_OPEN_LOOP      1

#घोषणा G762_PWM_POLARITY_NEGATIVE   1
#घोषणा G762_PWM_POLARITY_POSITIVE   0

/* Register data is पढ़ो (and cached) at most once per second. */
#घोषणा G762_UPDATE_INTERVAL    HZ

/*
 * Extract pulse count per fan revolution value (2 or 4) from given
 * FAN_CMD1 रेजिस्टर value.
 */
#घोषणा G762_PULSE_FROM_REG(reg) \
	((((reg) & G762_REG_FAN_CMD1_PULSE_PER_REV) + 1) << 1)

/*
 * Extract fan घड़ी भागisor (1, 2, 4 or 8) from given FAN_CMD1
 * रेजिस्टर value.
 */
#घोषणा G762_CLKDIV_FROM_REG(reg) \
	(1 << (((reg) & (G762_REG_FAN_CMD1_CLK_DIV_ID0 |	\
			 G762_REG_FAN_CMD1_CLK_DIV_ID1)) >> 2))

/*
 * Extract fan gear mode multiplier value (0, 2 or 4) from given
 * FAN_CMD2 रेजिस्टर value.
 */
#घोषणा G762_GEARMULT_FROM_REG(reg) \
	(1 << (((reg) & (G762_REG_FAN_CMD2_GEAR_MODE_0 |	\
			 G762_REG_FAN_CMD2_GEAR_MODE_1)) >> 2))

काष्ठा g762_data अणु
	काष्ठा i2c_client *client;
	काष्ठा clk *clk;

	/* update mutex */
	काष्ठा mutex update_lock;

	/* board specअगरic parameters. */
	u32 clk_freq;

	/* g762 रेजिस्टर cache */
	bool valid;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	u8 set_cnt;  /* controls fan rotation speed in बंदd-loop mode */
	u8 act_cnt;  /* provides access to current fan RPM value */
	u8 fan_sta;  /* bit 0: set when actual fan speed is more than
		      *        25% outside requested fan speed
		      * bit 1: set when no transition occurs on fan
		      *        pin क्रम 0.7s
		      */
	u8 set_out;  /* controls fan rotation speed in खोलो-loop mode */
	u8 fan_cmd1; /*   0: FG_PLS_ID0 FG pulses count per revolution
		      *      0: 2 counts per revolution
		      *      1: 4 counts per revolution
		      *   1: PWM_POLARITY 1: negative_duty
		      *                   0: positive_duty
		      * 2,3: [FG_CLOCK_ID0, FG_CLK_ID1]
		      *         00: Divide fan घड़ी by 1
		      *         01: Divide fan घड़ी by 2
		      *         10: Divide fan घड़ी by 4
		      *         11: Divide fan घड़ी by 8
		      *   4: FAN_MODE 1:बंदd-loop, 0:खोलो-loop
		      *   5: OUT_MODE 1:PWM, 0:DC
		      *   6: DET_FAN_OOC enable "fan ooc" status
		      *   7: DET_FAN_FAIL enable "fan fail" status
		      */
	u8 fan_cmd2; /* 0,1: FAN_STARTV 0,1,2,3 -> 0,32,64,96 dac_code
		      * 2,3: FG_GEAR_MODE
		      *         00: multiplier = 1
		      *         01: multiplier = 2
		      *         10: multiplier = 4
		      *   4: Mask ALERT# (g763 only)
		      */
पूर्ण;

/*
 * Convert count value from fan controller रेजिस्टर (FAN_SET_CNT) पूर्णांकo fan
 * speed RPM value. Note that the datasheet करोcuments a basic क्रमmula;
 * influence of additional parameters (fan घड़ी भागisor, fan gear mode)
 * have been infered from examples in the datasheet and tests.
 */
अटल अंतरभूत अचिन्हित पूर्णांक rpm_from_cnt(u8 cnt, u32 clk_freq, u16 p,
					u8 clk_भाग, u8 gear_mult)
अणु
	अगर (cnt == 0xff)  /* setting cnt to 255 stops the fan */
		वापस 0;

	वापस (clk_freq * 30 * gear_mult) / ((cnt ? cnt : 1) * p * clk_भाग);
पूर्ण

/*
 * Convert fan RPM value from sysfs पूर्णांकo count value क्रम fan controller
 * रेजिस्टर (FAN_SET_CNT).
 */
अटल अंतरभूत अचिन्हित अक्षर cnt_from_rpm(अचिन्हित दीर्घ rpm, u32 clk_freq, u16 p,
					 u8 clk_भाग, u8 gear_mult)
अणु
	अचिन्हित दीर्घ f1 = clk_freq * 30 * gear_mult;
	अचिन्हित दीर्घ f2 = p * clk_भाग;

	अगर (!rpm)	/* to stop the fan, set cnt to 255 */
		वापस 0xff;

	rpm = clamp_val(rpm, f1 / (255 * f2), अच_दीर्घ_उच्च / f2);
	वापस DIV_ROUND_CLOSEST(f1, rpm * f2);
पूर्ण

/* helper to grab and cache data, at most one समय per second */
अटल काष्ठा g762_data *g762_update_client(काष्ठा device *dev)
अणु
	काष्ठा g762_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret = 0;

	mutex_lock(&data->update_lock);
	अगर (समय_beक्रमe(jअगरfies, data->last_updated + G762_UPDATE_INTERVAL) &&
	    likely(data->valid))
		जाओ out;

	ret = i2c_smbus_पढ़ो_byte_data(client, G762_REG_SET_CNT);
	अगर (ret < 0)
		जाओ out;
	data->set_cnt = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, G762_REG_ACT_CNT);
	अगर (ret < 0)
		जाओ out;
	data->act_cnt = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, G762_REG_FAN_STA);
	अगर (ret < 0)
		जाओ out;
	data->fan_sta = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, G762_REG_SET_OUT);
	अगर (ret < 0)
		जाओ out;
	data->set_out = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, G762_REG_FAN_CMD1);
	अगर (ret < 0)
		जाओ out;
	data->fan_cmd1 = ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, G762_REG_FAN_CMD2);
	अगर (ret < 0)
		जाओ out;
	data->fan_cmd2 = ret;

	data->last_updated = jअगरfies;
	data->valid = true;
 out:
	mutex_unlock(&data->update_lock);

	अगर (ret < 0) /* upon error, encode it in वापस value */
		data = ERR_PTR(ret);

	वापस data;
पूर्ण

/* helpers क्रम writing hardware parameters */

/*
 * Set input घड़ी frequency received on CLK pin of the chip. Accepted values
 * are between 0 and 0xffffff. If zero is given, then शेष frequency
 * (32,768Hz) is used. Note that घड़ी frequency is a अक्षरacteristic of the
 * प्रणाली but an पूर्णांकernal parameter, i.e. value is not passed to the device.
 */
अटल पूर्णांक करो_set_clk_freq(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = dev_get_drvdata(dev);

	अगर (val > 0xffffff)
		वापस -EINVAL;
	अगर (!val)
		val = 32768;

	data->clk_freq = val;

	वापस 0;
पूर्ण

/* Set pwm mode. Accepts either 0 (PWM mode) or 1 (DC mode) */
अटल पूर्णांक करो_set_pwm_mode(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल G762_OUT_MODE_PWM:
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_OUT_MODE;
		अवरोध;
	हाल G762_OUT_MODE_DC:
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_OUT_MODE;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD1,
					data->fan_cmd1);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/* Set fan घड़ी भागisor. Accepts either 1, 2, 4 or 8. */
अटल पूर्णांक करो_set_fan_भाग(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल 1:
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_CLK_DIV_ID0;
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_CLK_DIV_ID1;
		अवरोध;
	हाल 2:
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_CLK_DIV_ID0;
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_CLK_DIV_ID1;
		अवरोध;
	हाल 4:
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_CLK_DIV_ID0;
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_CLK_DIV_ID1;
		अवरोध;
	हाल 8:
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_CLK_DIV_ID0;
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_CLK_DIV_ID1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD1,
					data->fan_cmd1);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/* Set fan gear mode. Accepts either 0, 1 or 2. */
अटल पूर्णांक करो_set_fan_gear_mode(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल 0:
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_GEAR_MODE_0;
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_GEAR_MODE_1;
		अवरोध;
	हाल 1:
		data->fan_cmd2 |=  G762_REG_FAN_CMD2_GEAR_MODE_0;
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_GEAR_MODE_1;
		अवरोध;
	हाल 2:
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_GEAR_MODE_0;
		data->fan_cmd2 |=  G762_REG_FAN_CMD2_GEAR_MODE_1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD2,
					data->fan_cmd2);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/* Set number of fan pulses per revolution. Accepts either 2 or 4. */
अटल पूर्णांक करो_set_fan_pulses(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल 2:
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_PULSE_PER_REV;
		अवरोध;
	हाल 4:
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_PULSE_PER_REV;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD1,
					data->fan_cmd1);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/* Set fan mode. Accepts either 1 (खोलो-loop) or 2 (बंदd-loop). */
अटल पूर्णांक करो_set_pwm_enable(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल G762_FAN_MODE_CLOSED_LOOP:
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_FAN_MODE;
		अवरोध;
	हाल G762_FAN_MODE_OPEN_LOOP:
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_FAN_MODE;
		/*
		 * BUG FIX: अगर SET_CNT रेजिस्टर value is 255 then, क्रम some
		 * unknown reason, fan will not rotate as expected, no matter
		 * the value of SET_OUT (to be specअगरic, this seems to happen
		 * only in PWM mode). To workaround this bug, we give SET_CNT
		 * value of 254 अगर it is 255 when चयनing to खोलो-loop.
		 */
		अगर (data->set_cnt == 0xff)
			i2c_smbus_ग_लिखो_byte_data(data->client,
						  G762_REG_SET_CNT, 254);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD1,
					data->fan_cmd1);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/* Set PWM polarity. Accepts either 0 (positive duty) or 1 (negative duty) */
अटल पूर्णांक करो_set_pwm_polarity(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल G762_PWM_POLARITY_POSITIVE:
		data->fan_cmd1 &= ~G762_REG_FAN_CMD1_PWM_POLARITY;
		अवरोध;
	हाल G762_PWM_POLARITY_NEGATIVE:
		data->fan_cmd1 |=  G762_REG_FAN_CMD1_PWM_POLARITY;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD1,
					data->fan_cmd1);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/*
 * Set pwm value. Accepts values between 0 (stops the fan) and
 * 255 (full speed). This only makes sense in खोलो-loop mode.
 */
अटल पूर्णांक करो_set_pwm(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	अगर (val > 255)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	ret = i2c_smbus_ग_लिखो_byte_data(client, G762_REG_SET_OUT, val);
	data->valid = false;
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/*
 * Set fan RPM value. Can be called both in बंदd and खोलो-loop mode
 * but effect will only be seen after बंदd-loop mode is configured.
 */
अटल पूर्णांक करो_set_fan_target(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	data->set_cnt = cnt_from_rpm(val, data->clk_freq,
				     G762_PULSE_FROM_REG(data->fan_cmd1),
				     G762_CLKDIV_FROM_REG(data->fan_cmd1),
				     G762_GEARMULT_FROM_REG(data->fan_cmd2));
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_SET_CNT,
					data->set_cnt);
	data->valid = false;
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/* Set fan startup voltage. Accepted values are either 0, 1, 2 or 3. */
अटल पूर्णांक करो_set_fan_startv(काष्ठा device *dev, अचिन्हित दीर्घ val)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	पूर्णांक ret;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	चयन (val) अणु
	हाल 0:
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_FAN_STARTV_0;
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_FAN_STARTV_1;
		अवरोध;
	हाल 1:
		data->fan_cmd2 |=  G762_REG_FAN_CMD2_FAN_STARTV_0;
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_FAN_STARTV_1;
		अवरोध;
	हाल 2:
		data->fan_cmd2 &= ~G762_REG_FAN_CMD2_FAN_STARTV_0;
		data->fan_cmd2 |=  G762_REG_FAN_CMD2_FAN_STARTV_1;
		अवरोध;
	हाल 3:
		data->fan_cmd2 |=  G762_REG_FAN_CMD2_FAN_STARTV_0;
		data->fan_cmd2 |=  G762_REG_FAN_CMD2_FAN_STARTV_1;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD2,
					data->fan_cmd2);
	data->valid = false;
 out:
	mutex_unlock(&data->update_lock);

	वापस ret;
पूर्ण

/*
 * Helper to import hardware अक्षरacteristics from .dts file and push
 * those to the chip.
 */

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id g762_dt_match[] = अणु
	अणु .compatible = "gmt,g762" पूर्ण,
	अणु .compatible = "gmt,g763" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, g762_dt_match);

/*
 * Grab घड़ी (a required property), enable it, get (fixed) घड़ी frequency
 * and store it. Note: upon success, घड़ी has been prepared and enabled; it
 * must later be unprepared and disabled (e.g. during module unloading) by a
 * call to g762_of_घड़ी_disable(). Note that a reference to घड़ी is kept
 * in our निजी data काष्ठाure to be used in this function.
 */
अटल व्योम g762_of_घड़ी_disable(व्योम *data)
अणु
	काष्ठा g762_data *g762 = data;

	clk_disable_unprepare(g762->clk);
	clk_put(g762->clk);
पूर्ण

अटल पूर्णांक g762_of_घड़ी_enable(काष्ठा i2c_client *client)
अणु
	काष्ठा g762_data *data;
	अचिन्हित दीर्घ clk_freq;
	काष्ठा clk *clk;
	पूर्णांक ret;

	अगर (!client->dev.of_node)
		वापस 0;

	clk = of_clk_get(client->dev.of_node, 0);
	अगर (IS_ERR(clk)) अणु
		dev_err(&client->dev, "failed to get clock\n");
		वापस PTR_ERR(clk);
	पूर्ण

	ret = clk_prepare_enable(clk);
	अगर (ret) अणु
		dev_err(&client->dev, "failed to enable clock\n");
		जाओ clk_put;
	पूर्ण

	clk_freq = clk_get_rate(clk);
	ret = करो_set_clk_freq(&client->dev, clk_freq);
	अगर (ret) अणु
		dev_err(&client->dev, "invalid clock freq %lu\n", clk_freq);
		जाओ clk_unprep;
	पूर्ण

	data = i2c_get_clientdata(client);
	data->clk = clk;

	devm_add_action(&client->dev, g762_of_घड़ी_disable, data);
	वापस 0;

 clk_unprep:
	clk_disable_unprepare(clk);

 clk_put:
	clk_put(clk);

	वापस ret;
पूर्ण

अटल पूर्णांक g762_of_prop_import_one(काष्ठा i2c_client *client,
				   स्थिर अक्षर *pname,
				   पूर्णांक (*psetter)(काष्ठा device *dev,
						  अचिन्हित दीर्घ val))
अणु
	पूर्णांक ret;
	u32 pval;

	अगर (of_property_पढ़ो_u32(client->dev.of_node, pname, &pval))
		वापस 0;

	dev_dbg(&client->dev, "found %s (%d)\n", pname, pval);
	ret = (*psetter)(&client->dev, pval);
	अगर (ret)
		dev_err(&client->dev, "unable to set %s (%d)\n", pname, pval);

	वापस ret;
पूर्ण

अटल पूर्णांक g762_of_prop_import(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	अगर (!client->dev.of_node)
		वापस 0;

	ret = g762_of_prop_import_one(client, "fan_gear_mode",
				      करो_set_fan_gear_mode);
	अगर (ret)
		वापस ret;

	ret = g762_of_prop_import_one(client, "pwm_polarity",
				      करो_set_pwm_polarity);
	अगर (ret)
		वापस ret;

	वापस g762_of_prop_import_one(client, "fan_startv",
				       करो_set_fan_startv);
पूर्ण

#अन्यथा
अटल पूर्णांक g762_of_prop_import(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक g762_of_घड़ी_enable(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Helper to import hardware अक्षरacteristics from .dts file and push
 * those to the chip.
 */

अटल पूर्णांक g762_pdata_prop_import(काष्ठा i2c_client *client)
अणु
	काष्ठा g762_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	पूर्णांक ret;

	अगर (!pdata)
		वापस 0;

	ret = करो_set_fan_gear_mode(&client->dev, pdata->fan_gear_mode);
	अगर (ret)
		वापस ret;

	ret = करो_set_pwm_polarity(&client->dev, pdata->pwm_polarity);
	अगर (ret)
		वापस ret;

	ret = करो_set_fan_startv(&client->dev, pdata->fan_startv);
	अगर (ret)
		वापस ret;

	वापस करो_set_clk_freq(&client->dev, pdata->clk_freq);
पूर्ण

/*
 * sysfs attributes
 */

/*
 * Read function क्रम fan1_input sysfs file. Return current fan RPM value, or
 * 0 अगर fan is out of control.
 */
अटल sमाप_प्रकार fan1_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	अचिन्हित पूर्णांक rpm = 0;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	/* reverse logic: fan out of control reporting is enabled low */
	अगर (data->fan_sta & G762_REG_FAN_STA_OOC) अणु
		rpm = rpm_from_cnt(data->act_cnt, data->clk_freq,
				   G762_PULSE_FROM_REG(data->fan_cmd1),
				   G762_CLKDIV_FROM_REG(data->fan_cmd1),
				   G762_GEARMULT_FROM_REG(data->fan_cmd2));
	पूर्ण
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%u\n", rpm);
पूर्ण

/*
 * Read and ग_लिखो functions क्रम pwm1_mode sysfs file. Get and set fan speed
 * control mode i.e. PWM (1) or DC (0).
 */
अटल sमाप_प्रकार pwm1_mode_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			      अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n",
		       !!(data->fan_cmd1 & G762_REG_FAN_CMD1_OUT_MODE));
पूर्ण

अटल sमाप_प्रकार pwm1_mode_store(काष्ठा device *dev,
			       काष्ठा device_attribute *da, स्थिर अक्षर *buf,
			       माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	ret = करो_set_pwm_mode(dev, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/*
 * Read and ग_लिखो functions क्रम fan1_भाग sysfs file. Get and set fan
 * controller prescaler value
 */
अटल sमाप_प्रकार fan1_भाग_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			     अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", G762_CLKDIV_FROM_REG(data->fan_cmd1));
पूर्ण

अटल sमाप_प्रकार fan1_भाग_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	ret = करो_set_fan_भाग(dev, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/*
 * Read and ग_लिखो functions क्रम fan1_pulses sysfs file. Get and set number
 * of tachometer pulses per fan revolution.
 */
अटल sमाप_प्रकार fan1_pulses_show(काष्ठा device *dev,
				काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", G762_PULSE_FROM_REG(data->fan_cmd1));
पूर्ण

अटल sमाप_प्रकार fan1_pulses_store(काष्ठा device *dev,
				 काष्ठा device_attribute *da, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	ret = करो_set_fan_pulses(dev, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/*
 * Read and ग_लिखो functions क्रम pwm1_enable. Get and set fan speed control mode
 * (i.e. बंदd or खोलो-loop).
 *
 * Following करोcumentation about hwmon's sysfs पूर्णांकerface, a pwm1_enable node
 * should accept the following:
 *
 *  0 : no fan speed control (i.e. fan at full speed)
 *  1 : manual fan speed control enabled (use pwm[1-*]) (खोलो-loop)
 *  2+: स्वतःmatic fan speed control enabled (use fan[1-*]_target) (बंदd-loop)
 *
 * but we करो not accept 0 as this mode is not natively supported by the chip
 * and it is not emulated by g762 driver. -EINVAL is वापसed in this हाल.
 */
अटल sमाप_प्रकार pwm1_enable_show(काष्ठा device *dev,
				काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n",
		       (!!(data->fan_cmd1 & G762_REG_FAN_CMD1_FAN_MODE)) + 1);
पूर्ण

अटल sमाप_प्रकार pwm1_enable_store(काष्ठा device *dev,
				 काष्ठा device_attribute *da, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	ret = करो_set_pwm_enable(dev, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/*
 * Read and ग_लिखो functions क्रम pwm1 sysfs file. Get and set pwm value
 * (which affects fan speed) in खोलो-loop mode. 0 stops the fan and 255
 * makes it run at full speed.
 */
अटल sमाप_प्रकार pwm1_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			 अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->set_out);
पूर्ण

अटल sमाप_प्रकार pwm1_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	ret = करो_set_pwm(dev, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/*
 * Read and ग_लिखो function क्रम fan1_target sysfs file. Get/set the fan speed in
 * बंदd-loop mode. Speed is given as a RPM value; then the chip will regulate
 * the fan speed using pulses from fan tachometer.
 *
 * Refer to rpm_from_cnt() implementation above to get info about count number
 * calculation.
 *
 * Also note that due to rounding errors it is possible that you करोn't पढ़ो
 * back exactly the value you have set.
 */
अटल sमाप_प्रकार fan1_target_show(काष्ठा device *dev,
				काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);
	अचिन्हित पूर्णांक rpm;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	mutex_lock(&data->update_lock);
	rpm = rpm_from_cnt(data->set_cnt, data->clk_freq,
			   G762_PULSE_FROM_REG(data->fan_cmd1),
			   G762_CLKDIV_FROM_REG(data->fan_cmd1),
			   G762_GEARMULT_FROM_REG(data->fan_cmd2));
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%u\n", rpm);
पूर्ण

अटल sमाप_प्रकार fan1_target_store(काष्ठा device *dev,
				 काष्ठा device_attribute *da, स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	अचिन्हित दीर्घ val;
	पूर्णांक ret;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	ret = करो_set_fan_target(dev, val);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

/* पढ़ो function क्रम fan1_fault sysfs file. */
अटल sमाप_प्रकार fan1_fault_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			       अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%u\n", !!(data->fan_sta & G762_REG_FAN_STA_FAIL));
पूर्ण

/*
 * पढ़ो function क्रम fan1_alarm sysfs file. Note that OOC condition is
 * enabled low
 */
अटल sमाप_प्रकार fan1_alarm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%u\n", !(data->fan_sta & G762_REG_FAN_STA_OOC));
पूर्ण

अटल DEVICE_ATTR_RW(pwm1);
अटल DEVICE_ATTR_RW(pwm1_mode);
अटल DEVICE_ATTR_RW(pwm1_enable);
अटल DEVICE_ATTR_RO(fan1_input);
अटल DEVICE_ATTR_RO(fan1_alarm);
अटल DEVICE_ATTR_RO(fan1_fault);
अटल DEVICE_ATTR_RW(fan1_target);
अटल DEVICE_ATTR_RW(fan1_भाग);
अटल DEVICE_ATTR_RW(fan1_pulses);

/* Driver data */
अटल काष्ठा attribute *g762_attrs[] = अणु
	&dev_attr_fan1_input.attr,
	&dev_attr_fan1_alarm.attr,
	&dev_attr_fan1_fault.attr,
	&dev_attr_fan1_target.attr,
	&dev_attr_fan1_भाग.attr,
	&dev_attr_fan1_pulses.attr,
	&dev_attr_pwm1.attr,
	&dev_attr_pwm1_mode.attr,
	&dev_attr_pwm1_enable.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(g762);

/*
 * Enable both fan failure detection and fan out of control protection. The
 * function करोes not protect change/access to data काष्ठाure; it must thus
 * only be called during initialization.
 */
अटल अंतरभूत पूर्णांक g762_fan_init(काष्ठा device *dev)
अणु
	काष्ठा g762_data *data = g762_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	data->fan_cmd1 |= G762_REG_FAN_CMD1_DET_FAN_FAIL;
	data->fan_cmd1 |= G762_REG_FAN_CMD1_DET_FAN_OOC;
	data->valid = false;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, G762_REG_FAN_CMD1,
					 data->fan_cmd1);
पूर्ण

अटल पूर्णांक g762_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा g762_data *data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(काष्ठा g762_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;
	mutex_init(&data->update_lock);

	/* Enable fan failure detection and fan out of control protection */
	ret = g762_fan_init(dev);
	अगर (ret)
		वापस ret;

	/* Get configuration via DT ... */
	ret = g762_of_घड़ी_enable(client);
	अगर (ret)
		वापस ret;
	ret = g762_of_prop_import(client);
	अगर (ret)
		वापस ret;
	/* ... or platक्रमm_data */
	ret = g762_pdata_prop_import(client);
	अगर (ret)
		वापस ret;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							    data, g762_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा i2c_driver g762_driver = अणु
	.driver = अणु
		.name = DRVNAME,
		.of_match_table = of_match_ptr(g762_dt_match),
	पूर्ण,
	.probe_new = g762_probe,
	.id_table = g762_id,
पूर्ण;

module_i2c_driver(g762_driver);

MODULE_AUTHOR("Arnaud EBALARD <arno@natisbad.org>");
MODULE_DESCRIPTION("GMT G762/G763 driver");
MODULE_LICENSE("GPL");
