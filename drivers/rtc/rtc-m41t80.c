<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C client/driver क्रम the ST M41T80 family of i2c rtc chips.
 *
 * Author: Alexander Bigga <ab@mycable.de>
 *
 * Based on m41t00.c by Mark A. Greer <mgreer@mvista.com>
 *
 * 2006 (c) mycable GmbH
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bcd.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/माला.स>
#अगर_घोषित CONFIG_RTC_DRV_M41T80_WDT
#समावेश <linux/fs.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/reboot.h>
#समावेश <linux/watchकरोg.h>
#पूर्ण_अगर

#घोषणा M41T80_REG_SSEC		0x00
#घोषणा M41T80_REG_SEC		0x01
#घोषणा M41T80_REG_MIN		0x02
#घोषणा M41T80_REG_HOUR		0x03
#घोषणा M41T80_REG_WDAY		0x04
#घोषणा M41T80_REG_DAY		0x05
#घोषणा M41T80_REG_MON		0x06
#घोषणा M41T80_REG_YEAR		0x07
#घोषणा M41T80_REG_ALARM_MON	0x0a
#घोषणा M41T80_REG_ALARM_DAY	0x0b
#घोषणा M41T80_REG_ALARM_HOUR	0x0c
#घोषणा M41T80_REG_ALARM_MIN	0x0d
#घोषणा M41T80_REG_ALARM_SEC	0x0e
#घोषणा M41T80_REG_FLAGS	0x0f
#घोषणा M41T80_REG_SQW		0x13

#घोषणा M41T80_DATETIME_REG_SIZE	(M41T80_REG_YEAR + 1)
#घोषणा M41T80_ALARM_REG_SIZE	\
	(M41T80_REG_ALARM_SEC + 1 - M41T80_REG_ALARM_MON)

#घोषणा M41T80_SQW_MAX_FREQ	32768

#घोषणा M41T80_SEC_ST		BIT(7)	/* ST: Stop Bit */
#घोषणा M41T80_ALMON_AFE	BIT(7)	/* AFE: AF Enable Bit */
#घोषणा M41T80_ALMON_SQWE	BIT(6)	/* SQWE: SQW Enable Bit */
#घोषणा M41T80_ALHOUR_HT	BIT(6)	/* HT: Halt Update Bit */
#घोषणा M41T80_FLAGS_OF		BIT(2)	/* OF: Oscillator Failure Bit */
#घोषणा M41T80_FLAGS_AF		BIT(6)	/* AF: Alarm Flag Bit */
#घोषणा M41T80_FLAGS_BATT_LOW	BIT(4)	/* BL: Battery Low Bit */
#घोषणा M41T80_WATCHDOG_RB2	BIT(7)	/* RB: Watchकरोg resolution */
#घोषणा M41T80_WATCHDOG_RB1	BIT(1)	/* RB: Watchकरोg resolution */
#घोषणा M41T80_WATCHDOG_RB0	BIT(0)	/* RB: Watchकरोg resolution */

#घोषणा M41T80_FEATURE_HT	BIT(0)	/* Halt feature */
#घोषणा M41T80_FEATURE_BL	BIT(1)	/* Battery low indicator */
#घोषणा M41T80_FEATURE_SQ	BIT(2)	/* Squarewave feature */
#घोषणा M41T80_FEATURE_WD	BIT(3)	/* Extra watchकरोg resolution */
#घोषणा M41T80_FEATURE_SQ_ALT	BIT(4)	/* RSx bits are in reg 4 */

अटल स्थिर काष्ठा i2c_device_id m41t80_id[] = अणु
	अणु "m41t62", M41T80_FEATURE_SQ | M41T80_FEATURE_SQ_ALT पूर्ण,
	अणु "m41t65", M41T80_FEATURE_HT | M41T80_FEATURE_WD पूर्ण,
	अणु "m41t80", M41T80_FEATURE_SQ पूर्ण,
	अणु "m41t81", M41T80_FEATURE_HT | M41T80_FEATURE_SQपूर्ण,
	अणु "m41t81s", M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ पूर्ण,
	अणु "m41t82", M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ पूर्ण,
	अणु "m41t83", M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ पूर्ण,
	अणु "m41st84", M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ पूर्ण,
	अणु "m41st85", M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ पूर्ण,
	अणु "m41st87", M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ पूर्ण,
	अणु "rv4162", M41T80_FEATURE_SQ | M41T80_FEATURE_WD | M41T80_FEATURE_SQ_ALT पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, m41t80_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id m41t80_of_match[] = अणु
	अणु
		.compatible = "st,m41t62",
		.data = (व्योम *)(M41T80_FEATURE_SQ | M41T80_FEATURE_SQ_ALT)
	पूर्ण,
	अणु
		.compatible = "st,m41t65",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_WD)
	पूर्ण,
	अणु
		.compatible = "st,m41t80",
		.data = (व्योम *)(M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "st,m41t81",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "st,m41t81s",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "st,m41t82",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "st,m41t83",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "st,m41t84",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "st,m41t85",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "st,m41t87",
		.data = (व्योम *)(M41T80_FEATURE_HT | M41T80_FEATURE_BL | M41T80_FEATURE_SQ)
	पूर्ण,
	अणु
		.compatible = "microcrystal,rv4162",
		.data = (व्योम *)(M41T80_FEATURE_SQ | M41T80_FEATURE_WD | M41T80_FEATURE_SQ_ALT)
	पूर्ण,
	/* DT compatibility only, करो not use compatibles below: */
	अणु
		.compatible = "st,rv4162",
		.data = (व्योम *)(M41T80_FEATURE_SQ | M41T80_FEATURE_WD | M41T80_FEATURE_SQ_ALT)
	पूर्ण,
	अणु
		.compatible = "rv4162",
		.data = (व्योम *)(M41T80_FEATURE_SQ | M41T80_FEATURE_WD | M41T80_FEATURE_SQ_ALT)
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, m41t80_of_match);

काष्ठा m41t80_data अणु
	अचिन्हित दीर्घ features;
	काष्ठा i2c_client *client;
	काष्ठा rtc_device *rtc;
#अगर_घोषित CONFIG_COMMON_CLK
	काष्ठा clk_hw sqw;
	अचिन्हित दीर्घ freq;
	अचिन्हित पूर्णांक sqwe;
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t m41t80_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *client = dev_id;
	काष्ठा m41t80_data *m41t80 = i2c_get_clientdata(client);
	अचिन्हित दीर्घ events = 0;
	पूर्णांक flags, flags_afe;

	rtc_lock(m41t80->rtc);

	flags_afe = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_ALARM_MON);
	अगर (flags_afe < 0) अणु
		rtc_unlock(m41t80->rtc);
		वापस IRQ_NONE;
	पूर्ण

	flags = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_FLAGS);
	अगर (flags <= 0) अणु
		rtc_unlock(m41t80->rtc);
		वापस IRQ_NONE;
	पूर्ण

	अगर (flags & M41T80_FLAGS_AF) अणु
		flags &= ~M41T80_FLAGS_AF;
		flags_afe &= ~M41T80_ALMON_AFE;
		events |= RTC_AF;
	पूर्ण

	अगर (events) अणु
		rtc_update_irq(m41t80->rtc, 1, events);
		i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_FLAGS, flags);
		i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_ALARM_MON,
					  flags_afe);
	पूर्ण

	rtc_unlock(m41t80->rtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक m41t80_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर buf[8];
	पूर्णांक err, flags;

	flags = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_FLAGS);
	अगर (flags < 0)
		वापस flags;

	अगर (flags & M41T80_FLAGS_OF) अणु
		dev_err(&client->dev, "Oscillator failure, data is invalid.\n");
		वापस -EINVAL;
	पूर्ण

	err = i2c_smbus_पढ़ो_i2c_block_data(client, M41T80_REG_SSEC,
					    माप(buf), buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to read date\n");
		वापस err;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(buf[M41T80_REG_SEC] & 0x7f);
	पंचांग->पंचांग_min = bcd2bin(buf[M41T80_REG_MIN] & 0x7f);
	पंचांग->पंचांग_hour = bcd2bin(buf[M41T80_REG_HOUR] & 0x3f);
	पंचांग->पंचांग_mday = bcd2bin(buf[M41T80_REG_DAY] & 0x3f);
	पंचांग->पंचांग_wday = buf[M41T80_REG_WDAY] & 0x07;
	पंचांग->पंचांग_mon = bcd2bin(buf[M41T80_REG_MON] & 0x1f) - 1;

	/* assume 20YY not 19YY, and ignore the Century Bit */
	पंचांग->पंचांग_year = bcd2bin(buf[M41T80_REG_YEAR]) + 100;
	वापस 0;
पूर्ण

अटल पूर्णांक m41t80_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा m41t80_data *clientdata = i2c_get_clientdata(client);
	अचिन्हित अक्षर buf[8];
	पूर्णांक err, flags;

	buf[M41T80_REG_SSEC] = 0;
	buf[M41T80_REG_SEC] = bin2bcd(पंचांग->पंचांग_sec);
	buf[M41T80_REG_MIN] = bin2bcd(पंचांग->पंचांग_min);
	buf[M41T80_REG_HOUR] = bin2bcd(पंचांग->पंचांग_hour);
	buf[M41T80_REG_DAY] = bin2bcd(पंचांग->पंचांग_mday);
	buf[M41T80_REG_MON] = bin2bcd(पंचांग->पंचांग_mon + 1);
	buf[M41T80_REG_YEAR] = bin2bcd(पंचांग->पंचांग_year - 100);
	buf[M41T80_REG_WDAY] = पंचांग->पंचांग_wday;

	/* If the square wave output is controlled in the weekday रेजिस्टर */
	अगर (clientdata->features & M41T80_FEATURE_SQ_ALT) अणु
		पूर्णांक val;

		val = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_WDAY);
		अगर (val < 0)
			वापस val;

		buf[M41T80_REG_WDAY] |= (val & 0xf0);
	पूर्ण

	err = i2c_smbus_ग_लिखो_i2c_block_data(client, M41T80_REG_SSEC,
					     माप(buf), buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to write to date registers\n");
		वापस err;
	पूर्ण

	/* Clear the OF bit of Flags Register */
	flags = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_FLAGS);
	अगर (flags < 0)
		वापस flags;

	err = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_FLAGS,
					flags & ~M41T80_FLAGS_OF);
	अगर (err < 0) अणु
		dev_err(&client->dev, "Unable to write flags register\n");
		वापस err;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक m41t80_rtc_proc(काष्ठा device *dev, काष्ठा seq_file *seq)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा m41t80_data *clientdata = i2c_get_clientdata(client);
	पूर्णांक reg;

	अगर (clientdata->features & M41T80_FEATURE_BL) अणु
		reg = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_FLAGS);
		अगर (reg < 0)
			वापस reg;
		seq_म_लिखो(seq, "battery\t\t: %s\n",
			   (reg & M41T80_FLAGS_BATT_LOW) ? "exhausted" : "ok");
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक m41t80_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक flags, retval;

	flags = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_ALARM_MON);
	अगर (flags < 0)
		वापस flags;

	अगर (enabled)
		flags |= M41T80_ALMON_AFE;
	अन्यथा
		flags &= ~M41T80_ALMON_AFE;

	retval = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_ALARM_MON, flags);
	अगर (retval < 0) अणु
		dev_err(dev, "Unable to enable alarm IRQ %d\n", retval);
		वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक m41t80_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 alarmvals[5];
	पूर्णांक ret, err;

	alarmvals[0] = bin2bcd(alrm->समय.पंचांग_mon + 1);
	alarmvals[1] = bin2bcd(alrm->समय.पंचांग_mday);
	alarmvals[2] = bin2bcd(alrm->समय.पंचांग_hour);
	alarmvals[3] = bin2bcd(alrm->समय.पंचांग_min);
	alarmvals[4] = bin2bcd(alrm->समय.पंचांग_sec);

	/* Clear AF and AFE flags */
	ret = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_ALARM_MON);
	अगर (ret < 0)
		वापस ret;
	err = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_ALARM_MON,
					ret & ~(M41T80_ALMON_AFE));
	अगर (err < 0) अणु
		dev_err(dev, "Unable to clear AFE bit\n");
		वापस err;
	पूर्ण

	/* Keep SQWE bit value */
	alarmvals[0] |= (ret & M41T80_ALMON_SQWE);

	ret = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_FLAGS);
	अगर (ret < 0)
		वापस ret;

	err = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_FLAGS,
					ret & ~(M41T80_FLAGS_AF));
	अगर (err < 0) अणु
		dev_err(dev, "Unable to clear AF bit\n");
		वापस err;
	पूर्ण

	/* Write the alarm */
	err = i2c_smbus_ग_लिखो_i2c_block_data(client, M41T80_REG_ALARM_MON,
					     5, alarmvals);
	अगर (err)
		वापस err;

	/* Enable the alarm पूर्णांकerrupt */
	अगर (alrm->enabled) अणु
		alarmvals[0] |= M41T80_ALMON_AFE;
		err = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_ALARM_MON,
						alarmvals[0]);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक m41t80_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 alarmvals[5];
	पूर्णांक flags, ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, M41T80_REG_ALARM_MON,
					    5, alarmvals);
	अगर (ret != 5)
		वापस ret < 0 ? ret : -EIO;

	flags = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_FLAGS);
	अगर (flags < 0)
		वापस flags;

	alrm->समय.पंचांग_sec  = bcd2bin(alarmvals[4] & 0x7f);
	alrm->समय.पंचांग_min  = bcd2bin(alarmvals[3] & 0x7f);
	alrm->समय.पंचांग_hour = bcd2bin(alarmvals[2] & 0x3f);
	alrm->समय.पंचांग_mday = bcd2bin(alarmvals[1] & 0x3f);
	alrm->समय.पंचांग_mon  = bcd2bin(alarmvals[0] & 0x3f) - 1;

	alrm->enabled = !!(alarmvals[0] & M41T80_ALMON_AFE);
	alrm->pending = (flags & M41T80_FLAGS_AF) && alrm->enabled;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops m41t80_rtc_ops = अणु
	.पढ़ो_समय = m41t80_rtc_पढ़ो_समय,
	.set_समय = m41t80_rtc_set_समय,
	.proc = m41t80_rtc_proc,
	.पढ़ो_alarm = m41t80_पढ़ो_alarm,
	.set_alarm = m41t80_set_alarm,
	.alarm_irq_enable = m41t80_alarm_irq_enable,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक m41t80_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (client->irq >= 0 && device_may_wakeup(dev))
		enable_irq_wake(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक m41t80_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (client->irq >= 0 && device_may_wakeup(dev))
		disable_irq_wake(client->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(m41t80_pm, m41t80_suspend, m41t80_resume);

#अगर_घोषित CONFIG_COMMON_CLK
#घोषणा sqw_to_m41t80_data(_hw) container_of(_hw, काष्ठा m41t80_data, sqw)

अटल अचिन्हित दीर्घ m41t80_decode_freq(पूर्णांक setting)
अणु
	वापस (setting == 0) ? 0 : (setting == 1) ? M41T80_SQW_MAX_FREQ :
		M41T80_SQW_MAX_FREQ >> setting;
पूर्ण

अटल अचिन्हित दीर्घ m41t80_get_freq(काष्ठा m41t80_data *m41t80)
अणु
	काष्ठा i2c_client *client = m41t80->client;
	पूर्णांक reg_sqw = (m41t80->features & M41T80_FEATURE_SQ_ALT) ?
		M41T80_REG_WDAY : M41T80_REG_SQW;
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, reg_sqw);

	अगर (ret < 0)
		वापस 0;
	वापस m41t80_decode_freq(ret >> 4);
पूर्ण

अटल अचिन्हित दीर्घ m41t80_sqw_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	वापस sqw_to_m41t80_data(hw)->freq;
पूर्ण

अटल दीर्घ m41t80_sqw_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	अगर (rate >= M41T80_SQW_MAX_FREQ)
		वापस M41T80_SQW_MAX_FREQ;
	अगर (rate >= M41T80_SQW_MAX_FREQ / 4)
		वापस M41T80_SQW_MAX_FREQ / 4;
	अगर (!rate)
		वापस 0;
	वापस 1 << ilog2(rate);
पूर्ण

अटल पूर्णांक m41t80_sqw_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा m41t80_data *m41t80 = sqw_to_m41t80_data(hw);
	काष्ठा i2c_client *client = m41t80->client;
	पूर्णांक reg_sqw = (m41t80->features & M41T80_FEATURE_SQ_ALT) ?
		M41T80_REG_WDAY : M41T80_REG_SQW;
	पूर्णांक reg, ret, val = 0;

	अगर (rate >= M41T80_SQW_MAX_FREQ)
		val = 1;
	अन्यथा अगर (rate >= M41T80_SQW_MAX_FREQ / 4)
		val = 2;
	अन्यथा अगर (rate)
		val = 15 - ilog2(rate);

	reg = i2c_smbus_पढ़ो_byte_data(client, reg_sqw);
	अगर (reg < 0)
		वापस reg;

	reg = (reg & 0x0f) | (val << 4);

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg_sqw, reg);
	अगर (!ret)
		m41t80->freq = m41t80_decode_freq(val);
	वापस ret;
पूर्ण

अटल पूर्णांक m41t80_sqw_control(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा m41t80_data *m41t80 = sqw_to_m41t80_data(hw);
	काष्ठा i2c_client *client = m41t80->client;
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_ALARM_MON);

	अगर (ret < 0)
		वापस ret;

	अगर (enable)
		ret |= M41T80_ALMON_SQWE;
	अन्यथा
		ret &= ~M41T80_ALMON_SQWE;

	ret = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_ALARM_MON, ret);
	अगर (!ret)
		m41t80->sqwe = enable;
	वापस ret;
पूर्ण

अटल पूर्णांक m41t80_sqw_prepare(काष्ठा clk_hw *hw)
अणु
	वापस m41t80_sqw_control(hw, 1);
पूर्ण

अटल व्योम m41t80_sqw_unprepare(काष्ठा clk_hw *hw)
अणु
	m41t80_sqw_control(hw, 0);
पूर्ण

अटल पूर्णांक m41t80_sqw_is_prepared(काष्ठा clk_hw *hw)
अणु
	वापस sqw_to_m41t80_data(hw)->sqwe;
पूर्ण

अटल स्थिर काष्ठा clk_ops m41t80_sqw_ops = अणु
	.prepare = m41t80_sqw_prepare,
	.unprepare = m41t80_sqw_unprepare,
	.is_prepared = m41t80_sqw_is_prepared,
	.recalc_rate = m41t80_sqw_recalc_rate,
	.round_rate = m41t80_sqw_round_rate,
	.set_rate = m41t80_sqw_set_rate,
पूर्ण;

अटल काष्ठा clk *m41t80_sqw_रेजिस्टर_clk(काष्ठा m41t80_data *m41t80)
अणु
	काष्ठा i2c_client *client = m41t80->client;
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	/* First disable the घड़ी */
	ret = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_ALARM_MON);
	अगर (ret < 0)
		वापस ERR_PTR(ret);
	ret = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_ALARM_MON,
					ret & ~(M41T80_ALMON_SQWE));
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	init.name = "m41t80-sqw";
	init.ops = &m41t80_sqw_ops;
	init.flags = 0;
	init.parent_names = शून्य;
	init.num_parents = 0;
	m41t80->sqw.init = &init;
	m41t80->freq = m41t80_get_freq(m41t80);

	/* optional override of the घड़ीname */
	of_property_पढ़ो_string(node, "clock-output-names", &init.name);

	/* रेजिस्टर the घड़ी */
	clk = clk_रेजिस्टर(&client->dev, &m41t80->sqw);
	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस clk;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_RTC_DRV_M41T80_WDT
/*
 *****************************************************************************
 *
 * Watchकरोg Driver
 *
 *****************************************************************************
 */
अटल DEFINE_MUTEX(m41t80_rtc_mutex);
अटल काष्ठा i2c_client *save_client;

/* Default margin */
#घोषणा WD_TIMO 60		/* 1..31 seconds */

अटल पूर्णांक wdt_margin = WD_TIMO;
module_param(wdt_margin, पूर्णांक, 0);
MODULE_PARM_DESC(wdt_margin, "Watchdog timeout in seconds (default 60s)");

अटल अचिन्हित दीर्घ wdt_is_खोलो;
अटल पूर्णांक boot_flag;

/**
 *	wdt_ping:
 *
 *	Reload counter one with the watchकरोg समयout. We करोn't bother reloading
 *	the cascade counter.
 */
अटल व्योम wdt_ping(व्योम)
अणु
	अचिन्हित अक्षर i2c_data[2];
	काष्ठा i2c_msg msgs1[1] = अणु
		अणु
			.addr	= save_client->addr,
			.flags	= 0,
			.len	= 2,
			.buf	= i2c_data,
		पूर्ण,
	पूर्ण;
	काष्ठा m41t80_data *clientdata = i2c_get_clientdata(save_client);

	i2c_data[0] = 0x09;		/* watchकरोg रेजिस्टर */

	अगर (wdt_margin > 31)
		i2c_data[1] = (wdt_margin & 0xFC) | 0x83; /* resolution = 4s */
	अन्यथा
		/*
		 * WDS = 1 (0x80), mulitplier = WD_TIMO, resolution = 1s (0x02)
		 */
		i2c_data[1] = wdt_margin << 2 | 0x82;

	/*
	 * M41T65 has three bits क्रम watchकरोg resolution.  Don't set bit 7, as
	 * that would be an invalid resolution.
	 */
	अगर (clientdata->features & M41T80_FEATURE_WD)
		i2c_data[1] &= ~M41T80_WATCHDOG_RB2;

	i2c_transfer(save_client->adapter, msgs1, 1);
पूर्ण

/**
 *	wdt_disable:
 *
 *	disables watchकरोg.
 */
अटल व्योम wdt_disable(व्योम)
अणु
	अचिन्हित अक्षर i2c_data[2], i2c_buf[0x10];
	काष्ठा i2c_msg msgs0[2] = अणु
		अणु
			.addr	= save_client->addr,
			.flags	= 0,
			.len	= 1,
			.buf	= i2c_data,
		पूर्ण,
		अणु
			.addr	= save_client->addr,
			.flags	= I2C_M_RD,
			.len	= 1,
			.buf	= i2c_buf,
		पूर्ण,
	पूर्ण;
	काष्ठा i2c_msg msgs1[1] = अणु
		अणु
			.addr	= save_client->addr,
			.flags	= 0,
			.len	= 2,
			.buf	= i2c_data,
		पूर्ण,
	पूर्ण;

	i2c_data[0] = 0x09;
	i2c_transfer(save_client->adapter, msgs0, 2);

	i2c_data[0] = 0x09;
	i2c_data[1] = 0x00;
	i2c_transfer(save_client->adapter, msgs1, 1);
पूर्ण

/**
 *	wdt_ग_लिखो:
 *	@file: file handle to the watchकरोg
 *	@buf: buffer to ग_लिखो (unused as data करोes not matter here
 *	@count: count of bytes
 *	@ppos: poपूर्णांकer to the position to ग_लिखो. No seeks allowed
 *
 *	A ग_लिखो to a watchकरोg device is defined as a keepalive संकेत. Any
 *	ग_लिखो of data will करो, as we we करोn't define content meaning.
 */
अटल sमाप_प्रकार wdt_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	अगर (count) अणु
		wdt_ping();
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार wdt_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

/**
 *	wdt_ioctl:
 *	@file: file handle to the device
 *	@cmd: watchकरोg command
 *	@arg: argument poपूर्णांकer
 *
 *	The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *	according to their available features. We only actually usefully support
 *	querying capabilities and current status.
 */
अटल पूर्णांक wdt_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
		     अचिन्हित दीर्घ arg)
अणु
	पूर्णांक new_margin, rv;
	अटल काष्ठा watchकरोg_info ident = अणु
		.options = WDIOF_POWERUNDER | WDIOF_KEEPALIVEPING |
			WDIOF_SETTIMEOUT,
		.firmware_version = 1,
		.identity = "M41T80 WTD"
	पूर्ण;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		वापस copy_to_user((काष्ठा watchकरोg_info __user *)arg, &ident,
				    माप(ident)) ? -EFAULT : 0;

	हाल WDIOC_GETSTATUS:
	हाल WDIOC_GETBOOTSTATUS:
		वापस put_user(boot_flag, (पूर्णांक __user *)arg);
	हाल WDIOC_KEEPALIVE:
		wdt_ping();
		वापस 0;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(new_margin, (पूर्णांक __user *)arg))
			वापस -EFAULT;
		/* Arbitrary, can't find the card's limits */
		अगर (new_margin < 1 || new_margin > 124)
			वापस -EINVAL;
		wdt_margin = new_margin;
		wdt_ping();
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		वापस put_user(wdt_margin, (पूर्णांक __user *)arg);

	हाल WDIOC_SETOPTIONS:
		अगर (copy_from_user(&rv, (पूर्णांक __user *)arg, माप(पूर्णांक)))
			वापस -EFAULT;

		अगर (rv & WDIOS_DISABLECARD) अणु
			pr_info("disable watchdog\n");
			wdt_disable();
		पूर्ण

		अगर (rv & WDIOS_ENABLECARD) अणु
			pr_info("enable watchdog\n");
			wdt_ping();
		पूर्ण

		वापस -EINVAL;
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल दीर्घ wdt_unlocked_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&m41t80_rtc_mutex);
	ret = wdt_ioctl(file, cmd, arg);
	mutex_unlock(&m41t80_rtc_mutex);

	वापस ret;
पूर्ण

/**
 *	wdt_खोलो:
 *	@inode: inode of device
 *	@file: file handle to device
 *
 */
अटल पूर्णांक wdt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (iminor(inode) == WATCHDOG_MINOR) अणु
		mutex_lock(&m41t80_rtc_mutex);
		अगर (test_and_set_bit(0, &wdt_is_खोलो)) अणु
			mutex_unlock(&m41t80_rtc_mutex);
			वापस -EBUSY;
		पूर्ण
		/*
		 *	Activate
		 */
		wdt_is_खोलो = 1;
		mutex_unlock(&m41t80_rtc_mutex);
		वापस stream_खोलो(inode, file);
	पूर्ण
	वापस -ENODEV;
पूर्ण

/**
 *	wdt_बंद:
 *	@inode: inode to board
 *	@file: file handle to board
 *
 */
अटल पूर्णांक wdt_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (iminor(inode) == WATCHDOG_MINOR)
		clear_bit(0, &wdt_is_खोलो);
	वापस 0;
पूर्ण

/**
 *	notअगरy_sys:
 *	@this: our notअगरier block
 *	@code: the event being reported
 *	@unused: unused
 *
 *	Our notअगरier is called on प्रणाली shutकरोwns. We want to turn the card
 *	off at reboot otherwise the machine will reboot again during memory
 *	test or worse yet during the following fsck. This would suck, in fact
 *	trust me - अगर it happens it करोes suck.
 */
अटल पूर्णांक wdt_notअगरy_sys(काष्ठा notअगरier_block *this, अचिन्हित दीर्घ code,
			  व्योम *unused)
अणु
	अगर (code == SYS_DOWN || code == SYS_HALT)
		/* Disable Watchकरोg */
		wdt_disable();
	वापस NOTIFY_DONE;
पूर्ण

अटल स्थिर काष्ठा file_operations wdt_fops = अणु
	.owner	= THIS_MODULE,
	.पढ़ो	= wdt_पढ़ो,
	.unlocked_ioctl = wdt_unlocked_ioctl,
	.compat_ioctl = compat_ptr_ioctl,
	.ग_लिखो	= wdt_ग_लिखो,
	.खोलो	= wdt_खोलो,
	.release = wdt_release,
	.llseek = no_llseek,
पूर्ण;

अटल काष्ठा miscdevice wdt_dev = अणु
	.minor = WATCHDOG_MINOR,
	.name = "watchdog",
	.fops = &wdt_fops,
पूर्ण;

/*
 *	The WDT card needs to learn about soft shutकरोwns in order to
 *	turn the समयbomb रेजिस्टरs off.
 */
अटल काष्ठा notअगरier_block wdt_notअगरier = अणु
	.notअगरier_call = wdt_notअगरy_sys,
पूर्ण;
#पूर्ण_अगर /* CONFIG_RTC_DRV_M41T80_WDT */

/*
 *****************************************************************************
 *
 *	Driver Interface
 *
 *****************************************************************************
 */

अटल पूर्णांक m41t80_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक rc = 0;
	काष्ठा rtc_समय पंचांग;
	काष्ठा m41t80_data *m41t80_data = शून्य;
	bool wakeup_source = false;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_I2C_BLOCK |
				     I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(&adapter->dev, "doesn't support I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BLOCK\n");
		वापस -ENODEV;
	पूर्ण

	m41t80_data = devm_kzalloc(&client->dev, माप(*m41t80_data),
				   GFP_KERNEL);
	अगर (!m41t80_data)
		वापस -ENOMEM;

	m41t80_data->client = client;
	अगर (client->dev.of_node)
		m41t80_data->features = (अचिन्हित दीर्घ)
			of_device_get_match_data(&client->dev);
	अन्यथा
		m41t80_data->features = id->driver_data;
	i2c_set_clientdata(client, m41t80_data);

	m41t80_data->rtc =  devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(m41t80_data->rtc))
		वापस PTR_ERR(m41t80_data->rtc);

#अगर_घोषित CONFIG_OF
	wakeup_source = of_property_पढ़ो_bool(client->dev.of_node,
					      "wakeup-source");
#पूर्ण_अगर
	अगर (client->irq > 0) अणु
		rc = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					       शून्य, m41t80_handle_irq,
					       IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					       "m41t80", client);
		अगर (rc) अणु
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
			wakeup_source = false;
		पूर्ण
	पूर्ण
	अगर (client->irq > 0 || wakeup_source)
		device_init_wakeup(&client->dev, true);
	अन्यथा
		clear_bit(RTC_FEATURE_ALARM, m41t80_data->rtc->features);

	m41t80_data->rtc->ops = &m41t80_rtc_ops;
	m41t80_data->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	m41t80_data->rtc->range_max = RTC_TIMESTAMP_END_2099;

	अगर (client->irq <= 0) अणु
		/* We cannot support UIE mode अगर we करो not have an IRQ line */
		m41t80_data->rtc->uie_unsupported = 1;
	पूर्ण

	/* Make sure HT (Halt Update) bit is cleared */
	rc = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_ALARM_HOUR);

	अगर (rc >= 0 && rc & M41T80_ALHOUR_HT) अणु
		अगर (m41t80_data->features & M41T80_FEATURE_HT) अणु
			m41t80_rtc_पढ़ो_समय(&client->dev, &पंचांग);
			dev_info(&client->dev, "HT bit was set!\n");
			dev_info(&client->dev, "Power Down at %ptR\n", &पंचांग);
		पूर्ण
		rc = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_ALARM_HOUR,
					       rc & ~M41T80_ALHOUR_HT);
	पूर्ण

	अगर (rc < 0) अणु
		dev_err(&client->dev, "Can't clear HT bit\n");
		वापस rc;
	पूर्ण

	/* Make sure ST (stop) bit is cleared */
	rc = i2c_smbus_पढ़ो_byte_data(client, M41T80_REG_SEC);

	अगर (rc >= 0 && rc & M41T80_SEC_ST)
		rc = i2c_smbus_ग_लिखो_byte_data(client, M41T80_REG_SEC,
					       rc & ~M41T80_SEC_ST);
	अगर (rc < 0) अणु
		dev_err(&client->dev, "Can't clear ST bit\n");
		वापस rc;
	पूर्ण

#अगर_घोषित CONFIG_RTC_DRV_M41T80_WDT
	अगर (m41t80_data->features & M41T80_FEATURE_HT) अणु
		save_client = client;
		rc = misc_रेजिस्टर(&wdt_dev);
		अगर (rc)
			वापस rc;
		rc = रेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
		अगर (rc) अणु
			misc_deरेजिस्टर(&wdt_dev);
			वापस rc;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMMON_CLK
	अगर (m41t80_data->features & M41T80_FEATURE_SQ)
		m41t80_sqw_रेजिस्टर_clk(m41t80_data);
#पूर्ण_अगर

	rc = devm_rtc_रेजिस्टर_device(m41t80_data->rtc);
	अगर (rc)
		वापस rc;

	वापस 0;
पूर्ण

अटल पूर्णांक m41t80_हटाओ(काष्ठा i2c_client *client)
अणु
#अगर_घोषित CONFIG_RTC_DRV_M41T80_WDT
	काष्ठा m41t80_data *clientdata = i2c_get_clientdata(client);

	अगर (clientdata->features & M41T80_FEATURE_HT) अणु
		misc_deरेजिस्टर(&wdt_dev);
		unरेजिस्टर_reboot_notअगरier(&wdt_notअगरier);
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver m41t80_driver = अणु
	.driver = अणु
		.name = "rtc-m41t80",
		.of_match_table = of_match_ptr(m41t80_of_match),
		.pm = &m41t80_pm,
	पूर्ण,
	.probe = m41t80_probe,
	.हटाओ = m41t80_हटाओ,
	.id_table = m41t80_id,
पूर्ण;

module_i2c_driver(m41t80_driver);

MODULE_AUTHOR("Alexander Bigga <ab@mycable.de>");
MODULE_DESCRIPTION("ST Microelectronics M41T80 series RTC I2C Client Driver");
MODULE_LICENSE("GPL");
