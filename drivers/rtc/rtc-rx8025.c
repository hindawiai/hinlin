<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Epson's RTC module RX-8025 SA/NB
 *
 * Copyright (C) 2009 Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 *
 * Copyright (C) 2005 by Digi International Inc.
 * All rights reserved.
 *
 * Modअगरied by fengjh at rising.com.cn
 * <lm-sensors@lm-sensors.org>
 * 2006.11
 *
 * Code cleanup by Sergei Poselenov, <sposelenov@emcraft.com>
 * Converted to new style by Wolfgang Gअक्रमegger <wg@gअक्रमegger.com>
 * Alarm and periodic पूर्णांकerrupt added by Dmitry Rakhchev <rda@emcraft.com>
 */
#समावेश <linux/bcd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>

/* Register definitions */
#घोषणा RX8025_REG_SEC		0x00
#घोषणा RX8025_REG_MIN		0x01
#घोषणा RX8025_REG_HOUR		0x02
#घोषणा RX8025_REG_WDAY		0x03
#घोषणा RX8025_REG_MDAY		0x04
#घोषणा RX8025_REG_MONTH	0x05
#घोषणा RX8025_REG_YEAR		0x06
#घोषणा RX8025_REG_DIGOFF	0x07
#घोषणा RX8025_REG_ALWMIN	0x08
#घोषणा RX8025_REG_ALWHOUR	0x09
#घोषणा RX8025_REG_ALWWDAY	0x0a
#घोषणा RX8025_REG_ALDMIN	0x0b
#घोषणा RX8025_REG_ALDHOUR	0x0c
/* 0x0d is reserved */
#घोषणा RX8025_REG_CTRL1	0x0e
#घोषणा RX8025_REG_CTRL2	0x0f

#घोषणा RX8025_BIT_CTRL1_CT	(7 << 0)
/* 1 Hz periodic level irq */
#घोषणा RX8025_BIT_CTRL1_CT_1HZ	4
#घोषणा RX8025_BIT_CTRL1_TEST	BIT(3)
#घोषणा RX8025_BIT_CTRL1_1224	BIT(5)
#घोषणा RX8025_BIT_CTRL1_DALE	BIT(6)
#घोषणा RX8025_BIT_CTRL1_WALE	BIT(7)

#घोषणा RX8025_BIT_CTRL2_DAFG	BIT(0)
#घोषणा RX8025_BIT_CTRL2_WAFG	BIT(1)
#घोषणा RX8025_BIT_CTRL2_CTFG	BIT(2)
#घोषणा RX8025_BIT_CTRL2_PON	BIT(4)
#घोषणा RX8025_BIT_CTRL2_XST	BIT(5)
#घोषणा RX8025_BIT_CTRL2_VDET	BIT(6)

/* Clock precision adjusपंचांगent */
#घोषणा RX8025_ADJ_RESOLUTION	3050 /* in ppb */
#घोषणा RX8025_ADJ_DATA_MAX	62
#घोषणा RX8025_ADJ_DATA_MIN	-62

अटल स्थिर काष्ठा i2c_device_id rx8025_id[] = अणु
	अणु "rx8025", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rx8025_id);

काष्ठा rx8025_data अणु
	काष्ठा rtc_device *rtc;
	u8 ctrl1;
पूर्ण;

अटल s32 rx8025_पढ़ो_reg(स्थिर काष्ठा i2c_client *client, u8 number)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, number << 4);
पूर्ण

अटल पूर्णांक rx8025_पढ़ो_regs(स्थिर काष्ठा i2c_client *client,
			    u8 number, u8 length, u8 *values)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_i2c_block_data(client, number << 4, length,
						values);
	अगर (ret != length)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल s32 rx8025_ग_लिखो_reg(स्थिर काष्ठा i2c_client *client, u8 number,
			    u8 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, number << 4, value);
पूर्ण

अटल s32 rx8025_ग_लिखो_regs(स्थिर काष्ठा i2c_client *client,
			     u8 number, u8 length, स्थिर u8 *values)
अणु
	वापस i2c_smbus_ग_लिखो_i2c_block_data(client, number << 4,
					      length, values);
पूर्ण

अटल पूर्णांक rx8025_check_validity(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ctrl2;

	ctrl2 = rx8025_पढ़ो_reg(client, RX8025_REG_CTRL2);
	अगर (ctrl2 < 0)
		वापस ctrl2;

	अगर (ctrl2 & RX8025_BIT_CTRL2_VDET)
		dev_warn(dev, "power voltage drop detected\n");

	अगर (ctrl2 & RX8025_BIT_CTRL2_PON) अणु
		dev_warn(dev, "power-on reset detected, date is invalid\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!(ctrl2 & RX8025_BIT_CTRL2_XST)) अणु
		dev_warn(dev, "crystal stopped, date is invalid\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rx8025_reset_validity(काष्ठा i2c_client *client)
अणु
	पूर्णांक ctrl2 = rx8025_पढ़ो_reg(client, RX8025_REG_CTRL2);

	अगर (ctrl2 < 0)
		वापस ctrl2;

	ctrl2 &= ~(RX8025_BIT_CTRL2_PON | RX8025_BIT_CTRL2_VDET);

	वापस rx8025_ग_लिखो_reg(client, RX8025_REG_CTRL2,
				ctrl2 | RX8025_BIT_CTRL2_XST);
पूर्ण

अटल irqवापस_t rx8025_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *client = dev_id;
	काष्ठा rx8025_data *rx8025 = i2c_get_clientdata(client);
	पूर्णांक status;

	rtc_lock(rx8025->rtc);
	status = rx8025_पढ़ो_reg(client, RX8025_REG_CTRL2);
	अगर (status < 0)
		जाओ out;

	अगर (!(status & RX8025_BIT_CTRL2_XST))
		dev_warn(&client->dev, "Oscillation stop was detected,"
			 "you may have to readjust the clock\n");

	अगर (status & RX8025_BIT_CTRL2_CTFG) अणु
		/* periodic */
		status &= ~RX8025_BIT_CTRL2_CTFG;
		rtc_update_irq(rx8025->rtc, 1, RTC_PF | RTC_IRQF);
	पूर्ण

	अगर (status & RX8025_BIT_CTRL2_DAFG) अणु
		/* alarm */
		status &= RX8025_BIT_CTRL2_DAFG;
		अगर (rx8025_ग_लिखो_reg(client, RX8025_REG_CTRL1,
				     rx8025->ctrl1 & ~RX8025_BIT_CTRL1_DALE))
			जाओ out;
		rtc_update_irq(rx8025->rtc, 1, RTC_AF | RTC_IRQF);
	पूर्ण

out:
	rtc_unlock(rx8025->rtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rx8025_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rx8025_data *rx8025 = dev_get_drvdata(dev);
	u8 date[7];
	पूर्णांक err;

	err = rx8025_check_validity(dev);
	अगर (err)
		वापस err;

	err = rx8025_पढ़ो_regs(client, RX8025_REG_SEC, 7, date);
	अगर (err)
		वापस err;

	dev_dbg(dev, "%s: read %7ph\n", __func__, date);

	dt->पंचांग_sec = bcd2bin(date[RX8025_REG_SEC] & 0x7f);
	dt->पंचांग_min = bcd2bin(date[RX8025_REG_MIN] & 0x7f);
	अगर (rx8025->ctrl1 & RX8025_BIT_CTRL1_1224)
		dt->पंचांग_hour = bcd2bin(date[RX8025_REG_HOUR] & 0x3f);
	अन्यथा
		dt->पंचांग_hour = bcd2bin(date[RX8025_REG_HOUR] & 0x1f) % 12
			+ (date[RX8025_REG_HOUR] & 0x20 ? 12 : 0);

	dt->पंचांग_mday = bcd2bin(date[RX8025_REG_MDAY] & 0x3f);
	dt->पंचांग_mon = bcd2bin(date[RX8025_REG_MONTH] & 0x1f) - 1;
	dt->पंचांग_year = bcd2bin(date[RX8025_REG_YEAR]) + 100;

	dev_dbg(dev, "%s: date %ptRr\n", __func__, dt);

	वापस 0;
पूर्ण

अटल पूर्णांक rx8025_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rx8025_data *rx8025 = dev_get_drvdata(dev);
	u8 date[7];
	पूर्णांक ret;

	अगर ((dt->पंचांग_year < 100) || (dt->पंचांग_year > 199))
		वापस -EINVAL;

	/*
	 * Here the पढ़ो-only bits are written as "0".  I'm not sure अगर that
	 * is sound.
	 */
	date[RX8025_REG_SEC] = bin2bcd(dt->पंचांग_sec);
	date[RX8025_REG_MIN] = bin2bcd(dt->पंचांग_min);
	अगर (rx8025->ctrl1 & RX8025_BIT_CTRL1_1224)
		date[RX8025_REG_HOUR] = bin2bcd(dt->पंचांग_hour);
	अन्यथा
		date[RX8025_REG_HOUR] = (dt->पंचांग_hour >= 12 ? 0x20 : 0)
			| bin2bcd((dt->पंचांग_hour + 11) % 12 + 1);

	date[RX8025_REG_WDAY] = bin2bcd(dt->पंचांग_wday);
	date[RX8025_REG_MDAY] = bin2bcd(dt->पंचांग_mday);
	date[RX8025_REG_MONTH] = bin2bcd(dt->पंचांग_mon + 1);
	date[RX8025_REG_YEAR] = bin2bcd(dt->पंचांग_year - 100);

	dev_dbg(dev, "%s: write %7ph\n", __func__, date);

	ret = rx8025_ग_लिखो_regs(client, RX8025_REG_SEC, 7, date);
	अगर (ret < 0)
		वापस ret;

	वापस rx8025_reset_validity(client);
पूर्ण

अटल पूर्णांक rx8025_init_client(काष्ठा i2c_client *client)
अणु
	काष्ठा rx8025_data *rx8025 = i2c_get_clientdata(client);
	u8 ctrl[2], ctrl2;
	पूर्णांक need_clear = 0;
	पूर्णांक err;

	err = rx8025_पढ़ो_regs(client, RX8025_REG_CTRL1, 2, ctrl);
	अगर (err)
		जाओ out;

	/* Keep test bit zero ! */
	rx8025->ctrl1 = ctrl[0] & ~RX8025_BIT_CTRL1_TEST;

	अगर (ctrl[1] & (RX8025_BIT_CTRL2_DAFG | RX8025_BIT_CTRL2_WAFG)) अणु
		dev_warn(&client->dev, "Alarm was detected\n");
		need_clear = 1;
	पूर्ण

	अगर (ctrl[1] & RX8025_BIT_CTRL2_CTFG)
		need_clear = 1;

	अगर (need_clear) अणु
		ctrl2 = ctrl[1];
		ctrl2 &= ~(RX8025_BIT_CTRL2_CTFG | RX8025_BIT_CTRL2_WAFG |
			   RX8025_BIT_CTRL2_DAFG);

		err = rx8025_ग_लिखो_reg(client, RX8025_REG_CTRL2, ctrl2);
	पूर्ण
out:
	वापस err;
पूर्ण

/* Alarm support */
अटल पूर्णांक rx8025_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rx8025_data *rx8025 = dev_get_drvdata(dev);
	u8 ald[2];
	पूर्णांक ctrl2, err;

	अगर (client->irq <= 0)
		वापस -EINVAL;

	err = rx8025_पढ़ो_regs(client, RX8025_REG_ALDMIN, 2, ald);
	अगर (err)
		वापस err;

	ctrl2 = rx8025_पढ़ो_reg(client, RX8025_REG_CTRL2);
	अगर (ctrl2 < 0)
		वापस ctrl2;

	dev_dbg(dev, "%s: read alarm 0x%02x 0x%02x ctrl2 %02x\n",
		__func__, ald[0], ald[1], ctrl2);

	/* Hardware alarms precision is 1 minute! */
	t->समय.पंचांग_sec = 0;
	t->समय.पंचांग_min = bcd2bin(ald[0] & 0x7f);
	अगर (rx8025->ctrl1 & RX8025_BIT_CTRL1_1224)
		t->समय.पंचांग_hour = bcd2bin(ald[1] & 0x3f);
	अन्यथा
		t->समय.पंचांग_hour = bcd2bin(ald[1] & 0x1f) % 12
			+ (ald[1] & 0x20 ? 12 : 0);

	dev_dbg(dev, "%s: date: %ptRr\n", __func__, &t->समय);
	t->enabled = !!(rx8025->ctrl1 & RX8025_BIT_CTRL1_DALE);
	t->pending = (ctrl2 & RX8025_BIT_CTRL2_DAFG) && t->enabled;

	वापस err;
पूर्ण

अटल पूर्णांक rx8025_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rx8025_data *rx8025 = dev_get_drvdata(dev);
	u8 ald[2];
	पूर्णांक err;

	अगर (client->irq <= 0)
		वापस -EINVAL;

	/*
	 * Hardware alarm precision is 1 minute!
	 * round up to nearest minute
	 */
	अगर (t->समय.पंचांग_sec) अणु
		समय64_t alarm_समय = rtc_पंचांग_to_समय64(&t->समय);

		alarm_समय += 60 - t->समय.पंचांग_sec;
		rtc_समय64_to_पंचांग(alarm_समय, &t->समय);
	पूर्ण

	ald[0] = bin2bcd(t->समय.पंचांग_min);
	अगर (rx8025->ctrl1 & RX8025_BIT_CTRL1_1224)
		ald[1] = bin2bcd(t->समय.पंचांग_hour);
	अन्यथा
		ald[1] = (t->समय.पंचांग_hour >= 12 ? 0x20 : 0)
			| bin2bcd((t->समय.पंचांग_hour + 11) % 12 + 1);

	dev_dbg(dev, "%s: write 0x%02x 0x%02x\n", __func__, ald[0], ald[1]);

	अगर (rx8025->ctrl1 & RX8025_BIT_CTRL1_DALE) अणु
		rx8025->ctrl1 &= ~RX8025_BIT_CTRL1_DALE;
		err = rx8025_ग_लिखो_reg(client, RX8025_REG_CTRL1,
				       rx8025->ctrl1);
		अगर (err)
			वापस err;
	पूर्ण
	err = rx8025_ग_लिखो_regs(client, RX8025_REG_ALDMIN, 2, ald);
	अगर (err)
		वापस err;

	अगर (t->enabled) अणु
		rx8025->ctrl1 |= RX8025_BIT_CTRL1_DALE;
		err = rx8025_ग_लिखो_reg(client, RX8025_REG_CTRL1,
				       rx8025->ctrl1);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rx8025_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rx8025_data *rx8025 = dev_get_drvdata(dev);
	u8 ctrl1;
	पूर्णांक err;

	ctrl1 = rx8025->ctrl1;
	अगर (enabled)
		ctrl1 |= RX8025_BIT_CTRL1_DALE;
	अन्यथा
		ctrl1 &= ~RX8025_BIT_CTRL1_DALE;

	अगर (ctrl1 != rx8025->ctrl1) अणु
		rx8025->ctrl1 = ctrl1;
		err = rx8025_ग_लिखो_reg(client, RX8025_REG_CTRL1,
				       rx8025->ctrl1);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rx8025_rtc_ops = अणु
	.पढ़ो_समय = rx8025_get_समय,
	.set_समय = rx8025_set_समय,
	.पढ़ो_alarm = rx8025_पढ़ो_alarm,
	.set_alarm = rx8025_set_alarm,
	.alarm_irq_enable = rx8025_alarm_irq_enable,
पूर्ण;

/*
 * Clock precision adjusपंचांगent support
 *
 * According to the RX8025 SA/NB application manual the frequency and
 * temperature अक्षरacteristics can be approximated using the following
 * equation:
 *
 *   df = a * (ut - t)**2
 *
 *   df: Frequency deviation in any temperature
 *   a : Coefficient = (-35 +-5) * 10**-9
 *   ut: Ultimate temperature in degree = +25 +-5 degree
 *   t : Any temperature in degree
 *
 * Note that the घड़ी adjusपंचांगent in ppb must be entered (which is
 * the negative value of the deviation).
 */
अटल पूर्णांक rx8025_get_घड़ी_adjust(काष्ठा device *dev, पूर्णांक *adj)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक digoff;

	digoff = rx8025_पढ़ो_reg(client, RX8025_REG_DIGOFF);
	अगर (digoff < 0)
		वापस digoff;

	*adj = digoff >= 64 ? digoff - 128 : digoff;
	अगर (*adj > 0)
		(*adj)--;
	*adj *= -RX8025_ADJ_RESOLUTION;

	वापस 0;
पूर्ण

अटल पूर्णांक rx8025_set_घड़ी_adjust(काष्ठा device *dev, पूर्णांक adj)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 digoff;
	पूर्णांक err;

	adj /= -RX8025_ADJ_RESOLUTION;
	अगर (adj > RX8025_ADJ_DATA_MAX)
		adj = RX8025_ADJ_DATA_MAX;
	अन्यथा अगर (adj < RX8025_ADJ_DATA_MIN)
		adj = RX8025_ADJ_DATA_MIN;
	अन्यथा अगर (adj > 0)
		adj++;
	अन्यथा अगर (adj < 0)
		adj += 128;
	digoff = adj;

	err = rx8025_ग_लिखो_reg(client, RX8025_REG_DIGOFF, digoff);
	अगर (err)
		वापस err;

	dev_dbg(dev, "%s: write 0x%02x\n", __func__, digoff);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार rx8025_sysfs_show_घड़ी_adjust(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	पूर्णांक err, adj;

	err = rx8025_get_घड़ी_adjust(dev, &adj);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", adj);
पूर्ण

अटल sमाप_प्रकार rx8025_sysfs_store_घड़ी_adjust(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक adj, err;

	अगर (माला_पूछो(buf, "%i", &adj) != 1)
		वापस -EINVAL;

	err = rx8025_set_घड़ी_adjust(dev, adj);

	वापस err ? err : count;
पूर्ण

अटल DEVICE_ATTR(घड़ी_adjust_ppb, S_IRUGO | S_IWUSR,
		   rx8025_sysfs_show_घड़ी_adjust,
		   rx8025_sysfs_store_घड़ी_adjust);

अटल पूर्णांक rx8025_sysfs_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस device_create_file(dev, &dev_attr_घड़ी_adjust_ppb);
पूर्ण

अटल व्योम rx8025_sysfs_unरेजिस्टर(काष्ठा device *dev)
अणु
	device_हटाओ_file(dev, &dev_attr_घड़ी_adjust_ppb);
पूर्ण

अटल पूर्णांक rx8025_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा rx8025_data *rx8025;
	पूर्णांक err = 0;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		dev_err(&adapter->dev,
			"doesn't support required functionality\n");
		वापस -EIO;
	पूर्ण

	rx8025 = devm_kzalloc(&client->dev, माप(*rx8025), GFP_KERNEL);
	अगर (!rx8025)
		वापस -ENOMEM;

	i2c_set_clientdata(client, rx8025);

	err = rx8025_init_client(client);
	अगर (err)
		वापस err;

	rx8025->rtc = devm_rtc_device_रेजिस्टर(&client->dev, client->name,
					  &rx8025_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(rx8025->rtc)) अणु
		dev_err(&client->dev, "unable to register the class device\n");
		वापस PTR_ERR(rx8025->rtc);
	पूर्ण

	अगर (client->irq > 0) अणु
		dev_info(&client->dev, "IRQ %d supplied\n", client->irq);
		err = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
						rx8025_handle_irq,
						IRQF_ONESHOT,
						"rx8025", client);
		अगर (err) अणु
			dev_err(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		पूर्ण
	पूर्ण

	rx8025->rtc->max_user_freq = 1;

	/* the rx8025 alarm only supports a minute accuracy */
	rx8025->rtc->uie_unsupported = 1;

	err = rx8025_sysfs_रेजिस्टर(&client->dev);
	वापस err;
पूर्ण

अटल पूर्णांक rx8025_हटाओ(काष्ठा i2c_client *client)
अणु
	rx8025_sysfs_unरेजिस्टर(&client->dev);
	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver rx8025_driver = अणु
	.driver = अणु
		.name = "rtc-rx8025",
	पूर्ण,
	.probe		= rx8025_probe,
	.हटाओ		= rx8025_हटाओ,
	.id_table	= rx8025_id,
पूर्ण;

module_i2c_driver(rx8025_driver);

MODULE_AUTHOR("Wolfgang Grandegger <wg@grandegger.com>");
MODULE_DESCRIPTION("RX-8025 SA/NB RTC driver");
MODULE_LICENSE("GPL");
