<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RTC client/driver क्रम the Maxim/Dallas DS3232/DS3234 Real-Time Clock
 *
 * Copyright (C) 2009-2011 Freescale Semiconductor.
 * Author: Jack Lan <jack.lan@मुक्तscale.com>
 * Copyright (C) 2008 MIMOMax Wireless Ltd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>
#समावेश <linux/regmap.h>
#समावेश <linux/hwmon.h>

#घोषणा DS3232_REG_SECONDS      0x00
#घोषणा DS3232_REG_MINUTES      0x01
#घोषणा DS3232_REG_HOURS        0x02
#घोषणा DS3232_REG_AMPM         0x02
#घोषणा DS3232_REG_DAY          0x03
#घोषणा DS3232_REG_DATE         0x04
#घोषणा DS3232_REG_MONTH        0x05
#घोषणा DS3232_REG_CENTURY      0x05
#घोषणा DS3232_REG_YEAR         0x06
#घोषणा DS3232_REG_ALARM1       0x07       /* Alarm 1 BASE */
#घोषणा DS3232_REG_ALARM2       0x0B       /* Alarm 2 BASE */
#घोषणा DS3232_REG_CR           0x0E       /* Control रेजिस्टर */
#       define DS3232_REG_CR_nEOSC   0x80
#       define DS3232_REG_CR_INTCN   0x04
#       define DS3232_REG_CR_A2IE    0x02
#       define DS3232_REG_CR_A1IE    0x01

#घोषणा DS3232_REG_SR           0x0F       /* control/status रेजिस्टर */
#       define DS3232_REG_SR_OSF     0x80
#       define DS3232_REG_SR_BSY     0x04
#       define DS3232_REG_SR_A2F     0x02
#       define DS3232_REG_SR_A1F     0x01

#घोषणा DS3232_REG_TEMPERATURE	0x11
#घोषणा DS3232_REG_SRAM_START   0x14
#घोषणा DS3232_REG_SRAM_END     0xFF

#घोषणा DS3232_REG_SRAM_SIZE    236

काष्ठा ds3232 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	पूर्णांक irq;
	काष्ठा rtc_device *rtc;

	bool suspended;
पूर्ण;

अटल पूर्णांक ds3232_check_rtc_status(काष्ठा device *dev)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	पूर्णांक ret = 0;
	पूर्णांक control, stat;

	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_SR, &stat);
	अगर (ret)
		वापस ret;

	अगर (stat & DS3232_REG_SR_OSF)
		dev_warn(dev,
				"oscillator discontinuity flagged, "
				"time unreliable\n");

	stat &= ~(DS3232_REG_SR_OSF | DS3232_REG_SR_A1F | DS3232_REG_SR_A2F);

	ret = regmap_ग_लिखो(ds3232->regmap, DS3232_REG_SR, stat);
	अगर (ret)
		वापस ret;

	/* If the alarm is pending, clear it beक्रमe requesting
	 * the पूर्णांकerrupt, so an पूर्णांकerrupt event isn't reported
	 * beक्रमe everything is initialized.
	 */

	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_CR, &control);
	अगर (ret)
		वापस ret;

	control &= ~(DS3232_REG_CR_A1IE | DS3232_REG_CR_A2IE);
	control |= DS3232_REG_CR_INTCN;

	वापस regmap_ग_लिखो(ds3232->regmap, DS3232_REG_CR, control);
पूर्ण

अटल पूर्णांक ds3232_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	पूर्णांक ret;
	u8 buf[7];
	अचिन्हित पूर्णांक year, month, day, hour, minute, second;
	अचिन्हित पूर्णांक week, twelve_hr, am_pm;
	अचिन्हित पूर्णांक century, add_century = 0;

	ret = regmap_bulk_पढ़ो(ds3232->regmap, DS3232_REG_SECONDS, buf, 7);
	अगर (ret)
		वापस ret;

	second = buf[0];
	minute = buf[1];
	hour = buf[2];
	week = buf[3];
	day = buf[4];
	month = buf[5];
	year = buf[6];

	/* Extract additional inक्रमmation क्रम AM/PM and century */

	twelve_hr = hour & 0x40;
	am_pm = hour & 0x20;
	century = month & 0x80;

	/* Write to rtc_समय काष्ठाure */

	समय->पंचांग_sec = bcd2bin(second);
	समय->पंचांग_min = bcd2bin(minute);
	अगर (twelve_hr) अणु
		/* Convert to 24 hr */
		अगर (am_pm)
			समय->पंचांग_hour = bcd2bin(hour & 0x1F) + 12;
		अन्यथा
			समय->पंचांग_hour = bcd2bin(hour & 0x1F);
	पूर्ण अन्यथा अणु
		समय->पंचांग_hour = bcd2bin(hour);
	पूर्ण

	/* Day of the week in linux range is 0~6 जबतक 1~7 in RTC chip */
	समय->पंचांग_wday = bcd2bin(week) - 1;
	समय->पंचांग_mday = bcd2bin(day);
	/* linux पंचांग_mon range:0~11, जबतक month range is 1~12 in RTC chip */
	समय->पंचांग_mon = bcd2bin(month & 0x7F) - 1;
	अगर (century)
		add_century = 100;

	समय->पंचांग_year = bcd2bin(year) + add_century;

	वापस 0;
पूर्ण

अटल पूर्णांक ds3232_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *समय)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	u8 buf[7];

	/* Extract समय from rtc_समय and load पूर्णांकo ds3232*/

	buf[0] = bin2bcd(समय->पंचांग_sec);
	buf[1] = bin2bcd(समय->पंचांग_min);
	buf[2] = bin2bcd(समय->पंचांग_hour);
	/* Day of the week in linux range is 0~6 जबतक 1~7 in RTC chip */
	buf[3] = bin2bcd(समय->पंचांग_wday + 1);
	buf[4] = bin2bcd(समय->पंचांग_mday); /* Date */
	/* linux पंचांग_mon range:0~11, जबतक month range is 1~12 in RTC chip */
	buf[5] = bin2bcd(समय->पंचांग_mon + 1);
	अगर (समय->पंचांग_year >= 100) अणु
		buf[5] |= 0x80;
		buf[6] = bin2bcd(समय->पंचांग_year - 100);
	पूर्ण अन्यथा अणु
		buf[6] = bin2bcd(समय->पंचांग_year);
	पूर्ण

	वापस regmap_bulk_ग_लिखो(ds3232->regmap, DS3232_REG_SECONDS, buf, 7);
पूर्ण

/*
 * DS3232 has two alarm, we only use alarm1
 * According to linux specअगरication, only support one-shot alarm
 * no periodic alarm mode
 */
अटल पूर्णांक ds3232_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	पूर्णांक control, stat;
	पूर्णांक ret;
	u8 buf[4];

	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_SR, &stat);
	अगर (ret)
		जाओ out;
	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_CR, &control);
	अगर (ret)
		जाओ out;
	ret = regmap_bulk_पढ़ो(ds3232->regmap, DS3232_REG_ALARM1, buf, 4);
	अगर (ret)
		जाओ out;

	alarm->समय.पंचांग_sec = bcd2bin(buf[0] & 0x7F);
	alarm->समय.पंचांग_min = bcd2bin(buf[1] & 0x7F);
	alarm->समय.पंचांग_hour = bcd2bin(buf[2] & 0x7F);
	alarm->समय.पंचांग_mday = bcd2bin(buf[3] & 0x7F);

	alarm->enabled = !!(control & DS3232_REG_CR_A1IE);
	alarm->pending = !!(stat & DS3232_REG_SR_A1F);

	ret = 0;
out:
	वापस ret;
पूर्ण

/*
 * linux rtc-module करोes not support wday alarm
 * and only 24h समय mode supported indeed
 */
अटल पूर्णांक ds3232_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	पूर्णांक control, stat;
	पूर्णांक ret;
	u8 buf[4];

	अगर (ds3232->irq <= 0)
		वापस -EINVAL;

	buf[0] = bin2bcd(alarm->समय.पंचांग_sec);
	buf[1] = bin2bcd(alarm->समय.पंचांग_min);
	buf[2] = bin2bcd(alarm->समय.पंचांग_hour);
	buf[3] = bin2bcd(alarm->समय.पंचांग_mday);

	/* clear alarm पूर्णांकerrupt enable bit */
	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_CR, &control);
	अगर (ret)
		जाओ out;
	control &= ~(DS3232_REG_CR_A1IE | DS3232_REG_CR_A2IE);
	ret = regmap_ग_लिखो(ds3232->regmap, DS3232_REG_CR, control);
	अगर (ret)
		जाओ out;

	/* clear any pending alarm flag */
	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_SR, &stat);
	अगर (ret)
		जाओ out;
	stat &= ~(DS3232_REG_SR_A1F | DS3232_REG_SR_A2F);
	ret = regmap_ग_लिखो(ds3232->regmap, DS3232_REG_SR, stat);
	अगर (ret)
		जाओ out;

	ret = regmap_bulk_ग_लिखो(ds3232->regmap, DS3232_REG_ALARM1, buf, 4);
	अगर (ret)
		जाओ out;

	अगर (alarm->enabled) अणु
		control |= DS3232_REG_CR_A1IE;
		ret = regmap_ग_लिखो(ds3232->regmap, DS3232_REG_CR, control);
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ds3232_update_alarm(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	पूर्णांक control;
	पूर्णांक ret;

	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_CR, &control);
	अगर (ret)
		वापस ret;

	अगर (enabled)
		/* enable alarm1 पूर्णांकerrupt */
		control |= DS3232_REG_CR_A1IE;
	अन्यथा
		/* disable alarm1 पूर्णांकerrupt */
		control &= ~(DS3232_REG_CR_A1IE);
	ret = regmap_ग_लिखो(ds3232->regmap, DS3232_REG_CR, control);

	वापस ret;
पूर्ण

/*
 * Temperature sensor support क्रम ds3232/ds3234 devices.
 * A user-initiated temperature conversion is not started by this function,
 * so the temperature is updated once every 64 seconds.
 */
अटल पूर्णांक ds3232_hwmon_पढ़ो_temp(काष्ठा device *dev, दीर्घ पूर्णांक *mC)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	u8 temp_buf[2];
	s16 temp;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(ds3232->regmap, DS3232_REG_TEMPERATURE, temp_buf,
			       माप(temp_buf));
	अगर (ret < 0)
		वापस ret;

	/*
	 * Temperature is represented as a 10-bit code with a resolution of
	 * 0.25 degree celsius and encoded in two's complement क्रमmat.
	 */
	temp = (temp_buf[0] << 8) | temp_buf[1];
	temp >>= 6;
	*mC = temp * 250;

	वापस 0;
पूर्ण

अटल umode_t ds3232_hwmon_is_visible(स्थिर व्योम *data,
				       क्रमागत hwmon_sensor_types type,
				       u32 attr, पूर्णांक channel)
अणु
	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक ds3232_hwmon_पढ़ो(काष्ठा device *dev,
			     क्रमागत hwmon_sensor_types type,
			     u32 attr, पूर्णांक channel, दीर्घ *temp)
अणु
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		err = ds3232_hwmon_पढ़ो_temp(dev, temp);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल u32 ds3232_hwmon_chip_config[] = अणु
	HWMON_C_REGISTER_TZ,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info ds3232_hwmon_chip = अणु
	.type = hwmon_chip,
	.config = ds3232_hwmon_chip_config,
पूर्ण;

अटल u32 ds3232_hwmon_temp_config[] = अणु
	HWMON_T_INPUT,
	0
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info ds3232_hwmon_temp = अणु
	.type = hwmon_temp,
	.config = ds3232_hwmon_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *ds3232_hwmon_info[] = अणु
	&ds3232_hwmon_chip,
	&ds3232_hwmon_temp,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops ds3232_hwmon_hwmon_ops = अणु
	.is_visible = ds3232_hwmon_is_visible,
	.पढ़ो = ds3232_hwmon_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ds3232_hwmon_chip_info = अणु
	.ops = &ds3232_hwmon_hwmon_ops,
	.info = ds3232_hwmon_info,
पूर्ण;

अटल व्योम ds3232_hwmon_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	काष्ठा device *hwmon_dev;

	अगर (!IS_ENABLED(CONFIG_RTC_DRV_DS3232_HWMON))
		वापस;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, name, ds3232,
							&ds3232_hwmon_chip_info,
							शून्य);
	अगर (IS_ERR(hwmon_dev)) अणु
		dev_err(dev, "unable to register hwmon device %ld\n",
			PTR_ERR(hwmon_dev));
	पूर्ण
पूर्ण

अटल पूर्णांक ds3232_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);

	अगर (ds3232->irq <= 0)
		वापस -EINVAL;

	वापस ds3232_update_alarm(dev, enabled);
पूर्ण

अटल irqवापस_t ds3232_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा device *dev = dev_id;
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);
	पूर्णांक ret;
	पूर्णांक stat, control;

	rtc_lock(ds3232->rtc);

	ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_SR, &stat);
	अगर (ret)
		जाओ unlock;

	अगर (stat & DS3232_REG_SR_A1F) अणु
		ret = regmap_पढ़ो(ds3232->regmap, DS3232_REG_CR, &control);
		अगर (ret) अणु
			dev_warn(ds3232->dev,
				 "Read Control Register error %d\n", ret);
		पूर्ण अन्यथा अणु
			/* disable alarm1 पूर्णांकerrupt */
			control &= ~(DS3232_REG_CR_A1IE);
			ret = regmap_ग_लिखो(ds3232->regmap, DS3232_REG_CR,
					   control);
			अगर (ret) अणु
				dev_warn(ds3232->dev,
					 "Write Control Register error %d\n",
					 ret);
				जाओ unlock;
			पूर्ण

			/* clear the alarm pend flag */
			stat &= ~DS3232_REG_SR_A1F;
			ret = regmap_ग_लिखो(ds3232->regmap, DS3232_REG_SR, stat);
			अगर (ret) अणु
				dev_warn(ds3232->dev,
					 "Write Status Register error %d\n",
					 ret);
				जाओ unlock;
			पूर्ण

			rtc_update_irq(ds3232->rtc, 1, RTC_AF | RTC_IRQF);
		पूर्ण
	पूर्ण

unlock:
	rtc_unlock(ds3232->rtc);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds3232_rtc_ops = अणु
	.पढ़ो_समय = ds3232_पढ़ो_समय,
	.set_समय = ds3232_set_समय,
	.पढ़ो_alarm = ds3232_पढ़ो_alarm,
	.set_alarm = ds3232_set_alarm,
	.alarm_irq_enable = ds3232_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक ds3232_nvmem_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा regmap *ds3232_regmap = (काष्ठा regmap *)priv;

	वापस regmap_bulk_पढ़ो(ds3232_regmap, DS3232_REG_SRAM_START + offset,
				val, bytes);
पूर्ण

अटल पूर्णांक ds3232_nvmem_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा regmap *ds3232_regmap = (काष्ठा regmap *)priv;

	वापस regmap_bulk_ग_लिखो(ds3232_regmap, DS3232_REG_SRAM_START + offset,
				 val, bytes);
पूर्ण

अटल पूर्णांक ds3232_probe(काष्ठा device *dev, काष्ठा regmap *regmap, पूर्णांक irq,
			स्थिर अक्षर *name)
अणु
	काष्ठा ds3232 *ds3232;
	पूर्णांक ret;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "ds3232_sram",
		.stride = 1,
		.size = DS3232_REG_SRAM_SIZE,
		.word_size = 1,
		.reg_पढ़ो = ds3232_nvmem_पढ़ो,
		.reg_ग_लिखो = ds3232_nvmem_ग_लिखो,
		.priv = regmap,
		.type = NVMEM_TYPE_BATTERY_BACKED
	पूर्ण;

	ds3232 = devm_kzalloc(dev, माप(*ds3232), GFP_KERNEL);
	अगर (!ds3232)
		वापस -ENOMEM;

	ds3232->regmap = regmap;
	ds3232->irq = irq;
	ds3232->dev = dev;
	dev_set_drvdata(dev, ds3232);

	ret = ds3232_check_rtc_status(dev);
	अगर (ret)
		वापस ret;

	अगर (ds3232->irq > 0)
		device_init_wakeup(dev, 1);

	ds3232_hwmon_रेजिस्टर(dev, name);

	ds3232->rtc = devm_rtc_device_रेजिस्टर(dev, name, &ds3232_rtc_ops,
						THIS_MODULE);
	अगर (IS_ERR(ds3232->rtc))
		वापस PTR_ERR(ds3232->rtc);

	ret = devm_rtc_nvmem_रेजिस्टर(ds3232->rtc, &nvmem_cfg);
	अगर(ret)
		वापस ret;

	अगर (ds3232->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, ds3232->irq, शून्य,
						ds3232_irq,
						IRQF_SHARED | IRQF_ONESHOT,
						name, dev);
		अगर (ret) अणु
			device_set_wakeup_capable(dev, 0);
			ds3232->irq = 0;
			dev_err(dev, "unable to request IRQ\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ds3232_suspend(काष्ठा device *dev)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev)) अणु
		अगर (enable_irq_wake(ds3232->irq))
			dev_warn_once(dev, "Cannot set wakeup source\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds3232_resume(काष्ठा device *dev)
अणु
	काष्ठा ds3232 *ds3232 = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(ds3232->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops ds3232_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(ds3232_suspend, ds3232_resume)
पूर्ण;

#अगर IS_ENABLED(CONFIG_I2C)

अटल पूर्णांक ds3232_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	अटल स्थिर काष्ठा regmap_config config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = DS3232_REG_SRAM_END,
	पूर्ण;

	regmap = devm_regmap_init_i2c(client, &config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "%s: regmap allocation failed: %ld\n",
			__func__, PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस ds3232_probe(&client->dev, regmap, client->irq, client->name);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ds3232_id[] = अणु
	अणु "ds3232", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds3232_id);

अटल स्थिर  __maybe_unused काष्ठा of_device_id ds3232_of_match[] = अणु
	अणु .compatible = "dallas,ds3232" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds3232_of_match);

अटल काष्ठा i2c_driver ds3232_driver = अणु
	.driver = अणु
		.name = "rtc-ds3232",
		.of_match_table = of_match_ptr(ds3232_of_match),
		.pm	= &ds3232_pm_ops,
	पूर्ण,
	.probe = ds3232_i2c_probe,
	.id_table = ds3232_id,
पूर्ण;

अटल पूर्णांक ds3232_रेजिस्टर_driver(व्योम)
अणु
	वापस i2c_add_driver(&ds3232_driver);
पूर्ण

अटल व्योम ds3232_unरेजिस्टर_driver(व्योम)
अणु
	i2c_del_driver(&ds3232_driver);
पूर्ण

#अन्यथा

अटल पूर्णांक ds3232_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम ds3232_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SPI_MASTER)

अटल पूर्णांक ds3234_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक res;
	अचिन्हित पूर्णांक पंचांगp;
	अटल स्थिर काष्ठा regmap_config config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = DS3232_REG_SRAM_END,
		.ग_लिखो_flag_mask = 0x80,
	पूर्ण;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "%s: regmap allocation failed: %ld\n",
			__func__, PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	res = regmap_पढ़ो(regmap, DS3232_REG_SECONDS, &पंचांगp);
	अगर (res)
		वापस res;

	/* Control settings
	 *
	 * CONTROL_REG
	 * BIT 7	6	5	4	3	2	1	0
	 *     EOSC	BBSQW	CONV	RS2	RS1	INTCN	A2IE	A1IE
	 *
	 *     0	0	0	1	1	1	0	0
	 *
	 * CONTROL_STAT_REG
	 * BIT 7	6	5	4	3	2	1	0
	 *     OSF	BB32kHz	CRATE1	CRATE0	EN32kHz	BSY	A2F	A1F
	 *
	 *     1	0	0	0	1	0	0	0
	 */
	res = regmap_पढ़ो(regmap, DS3232_REG_CR, &पंचांगp);
	अगर (res)
		वापस res;
	res = regmap_ग_लिखो(regmap, DS3232_REG_CR, पंचांगp & 0x1c);
	अगर (res)
		वापस res;

	res = regmap_पढ़ो(regmap, DS3232_REG_SR, &पंचांगp);
	अगर (res)
		वापस res;
	res = regmap_ग_लिखो(regmap, DS3232_REG_SR, पंचांगp & 0x88);
	अगर (res)
		वापस res;

	/* Prपूर्णांक our settings */
	res = regmap_पढ़ो(regmap, DS3232_REG_CR, &पंचांगp);
	अगर (res)
		वापस res;
	dev_info(&spi->dev, "Control Reg: 0x%02x\n", पंचांगp);

	res = regmap_पढ़ो(regmap, DS3232_REG_SR, &पंचांगp);
	अगर (res)
		वापस res;
	dev_info(&spi->dev, "Ctrl/Stat Reg: 0x%02x\n", पंचांगp);

	वापस ds3232_probe(&spi->dev, regmap, spi->irq, "ds3234");
पूर्ण

अटल काष्ठा spi_driver ds3234_driver = अणु
	.driver = अणु
		.name	 = "ds3234",
	पूर्ण,
	.probe	 = ds3234_probe,
पूर्ण;

अटल पूर्णांक ds3234_रेजिस्टर_driver(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&ds3234_driver);
पूर्ण

अटल व्योम ds3234_unरेजिस्टर_driver(व्योम)
अणु
	spi_unरेजिस्टर_driver(&ds3234_driver);
पूर्ण

#अन्यथा

अटल पूर्णांक ds3234_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम ds3234_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init ds323x_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ds3232_रेजिस्टर_driver();
	अगर (ret) अणु
		pr_err("Failed to register ds3232 driver: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ds3234_रेजिस्टर_driver();
	अगर (ret) अणु
		pr_err("Failed to register ds3234 driver: %d\n", ret);
		ds3232_unरेजिस्टर_driver();
	पूर्ण

	वापस ret;
पूर्ण
module_init(ds323x_init)

अटल व्योम __निकास ds323x_निकास(व्योम)
अणु
	ds3234_unरेजिस्टर_driver();
	ds3232_unरेजिस्टर_driver();
पूर्ण
module_निकास(ds323x_निकास)

MODULE_AUTHOR("Srikanth Srinivasan <srikanth.srinivasan@freescale.com>");
MODULE_AUTHOR("Dennis Aberilla <denzzzhome@yahoo.com>");
MODULE_DESCRIPTION("Maxim/Dallas DS3232/DS3234 RTC Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("spi:ds3234");
