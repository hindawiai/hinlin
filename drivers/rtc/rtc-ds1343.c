<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* rtc-ds1343.c
 *
 * Driver क्रम Dallas Semiconductor DS1343 Low Current, SPI Compatible
 * Real Time Clock
 *
 * Author : Raghavendra Chandra Ganiga <ravi23ganiga@gmail.com>
 *	    Ankur Srivastava <sankurece@gmail.com> : DS1343 Nvram Support
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/bcd.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_wakeirq.h>
#समावेश <linux/slab.h>

#घोषणा DALLAS_MAXIM_DS1343	0
#घोषणा DALLAS_MAXIM_DS1344	1

/* RTC DS1343 Registers */
#घोषणा DS1343_SECONDS_REG	0x00
#घोषणा DS1343_MINUTES_REG	0x01
#घोषणा DS1343_HOURS_REG	0x02
#घोषणा DS1343_DAY_REG		0x03
#घोषणा DS1343_DATE_REG		0x04
#घोषणा DS1343_MONTH_REG	0x05
#घोषणा DS1343_YEAR_REG		0x06
#घोषणा DS1343_ALM0_SEC_REG	0x07
#घोषणा DS1343_ALM0_MIN_REG	0x08
#घोषणा DS1343_ALM0_HOUR_REG	0x09
#घोषणा DS1343_ALM0_DAY_REG	0x0A
#घोषणा DS1343_ALM1_SEC_REG	0x0B
#घोषणा DS1343_ALM1_MIN_REG	0x0C
#घोषणा DS1343_ALM1_HOUR_REG	0x0D
#घोषणा DS1343_ALM1_DAY_REG	0x0E
#घोषणा DS1343_CONTROL_REG	0x0F
#घोषणा DS1343_STATUS_REG	0x10
#घोषणा DS1343_TRICKLE_REG	0x11
#घोषणा DS1343_NVRAM		0x20

#घोषणा DS1343_NVRAM_LEN	96

/* DS1343 Control Registers bits */
#घोषणा DS1343_EOSC		0x80
#घोषणा DS1343_DOSF		0x20
#घोषणा DS1343_EGFIL		0x10
#घोषणा DS1343_SQW		0x08
#घोषणा DS1343_INTCN		0x04
#घोषणा DS1343_A1IE		0x02
#घोषणा DS1343_A0IE		0x01

/* DS1343 Status Registers bits */
#घोषणा DS1343_OSF		0x80
#घोषणा DS1343_IRQF1		0x02
#घोषणा DS1343_IRQF0		0x01

/* DS1343 Trickle Charger Registers bits */
#घोषणा DS1343_TRICKLE_MAGIC	0xa0
#घोषणा DS1343_TRICKLE_DS1	0x08
#घोषणा DS1343_TRICKLE_1K	0x01
#घोषणा DS1343_TRICKLE_2K	0x02
#घोषणा DS1343_TRICKLE_4K	0x03

अटल स्थिर काष्ठा spi_device_id ds1343_id[] = अणु
	अणु "ds1343", DALLAS_MAXIM_DS1343 पूर्ण,
	अणु "ds1344", DALLAS_MAXIM_DS1344 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ds1343_id);

काष्ठा ds1343_priv अणु
	काष्ठा rtc_device *rtc;
	काष्ठा regmap *map;
	पूर्णांक irq;
पूर्ण;

अटल sमाप_प्रकार ds1343_show_glitchfilter(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev->parent);
	पूर्णांक glitch_filt_status, data;
	पूर्णांक res;

	res = regmap_पढ़ो(priv->map, DS1343_CONTROL_REG, &data);
	अगर (res)
		वापस res;

	glitch_filt_status = !!(data & DS1343_EGFIL);

	अगर (glitch_filt_status)
		वापस प्र_लिखो(buf, "enabled\n");
	अन्यथा
		वापस प्र_लिखो(buf, "disabled\n");
पूर्ण

अटल sमाप_प्रकार ds1343_store_glitchfilter(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev->parent);
	पूर्णांक data = 0;
	पूर्णांक res;

	अगर (म_भेदन(buf, "enabled", 7) == 0)
		data = DS1343_EGFIL;
	अन्यथा अगर (म_भेदन(buf, "disabled", 8))
		वापस -EINVAL;

	res = regmap_update_bits(priv->map, DS1343_CONTROL_REG,
				 DS1343_EGFIL, data);
	अगर (res)
		वापस res;

	वापस count;
पूर्ण

अटल DEVICE_ATTR(glitch_filter, S_IRUGO | S_IWUSR, ds1343_show_glitchfilter,
			ds1343_store_glitchfilter);

अटल पूर्णांक ds1343_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा ds1343_priv *ds1343 = priv;

	वापस regmap_bulk_ग_लिखो(ds1343->map, DS1343_NVRAM + off, val, bytes);
पूर्ण

अटल पूर्णांक ds1343_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा ds1343_priv *ds1343 = priv;

	वापस regmap_bulk_पढ़ो(ds1343->map, DS1343_NVRAM + off, val, bytes);
पूर्ण

अटल sमाप_प्रकार ds1343_show_trickleअक्षरger(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev->parent);
	पूर्णांक res, data;
	अक्षर *diodes = "disabled", *resistors = " ";

	res = regmap_पढ़ो(priv->map, DS1343_TRICKLE_REG, &data);
	अगर (res)
		वापस res;

	अगर ((data & 0xf0) == DS1343_TRICKLE_MAGIC) अणु
		चयन (data & 0x0c) अणु
		हाल DS1343_TRICKLE_DS1:
			diodes = "one diode,";
			अवरोध;

		शेष:
			diodes = "no diode,";
			अवरोध;
		पूर्ण

		चयन (data & 0x03) अणु
		हाल DS1343_TRICKLE_1K:
			resistors = "1k Ohm";
			अवरोध;

		हाल DS1343_TRICKLE_2K:
			resistors = "2k Ohm";
			अवरोध;

		हाल DS1343_TRICKLE_4K:
			resistors = "4k Ohm";
			अवरोध;

		शेष:
			diodes = "disabled";
			अवरोध;
		पूर्ण
	पूर्ण

	वापस प्र_लिखो(buf, "%s %s\n", diodes, resistors);
पूर्ण

अटल DEVICE_ATTR(trickle_अक्षरger, S_IRUGO, ds1343_show_trickleअक्षरger, शून्य);

अटल काष्ठा attribute *ds1343_attrs[] = अणु
	&dev_attr_glitch_filter.attr,
	&dev_attr_trickle_अक्षरger.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ds1343_attr_group = अणु
	.attrs  = ds1343_attrs,
पूर्ण;

अटल पूर्णांक ds1343_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[7];
	पूर्णांक res;

	res = regmap_bulk_पढ़ो(priv->map, DS1343_SECONDS_REG, buf, 7);
	अगर (res)
		वापस res;

	dt->पंचांग_sec	= bcd2bin(buf[0]);
	dt->पंचांग_min	= bcd2bin(buf[1]);
	dt->पंचांग_hour	= bcd2bin(buf[2] & 0x3F);
	dt->पंचांग_wday	= bcd2bin(buf[3]) - 1;
	dt->पंचांग_mday	= bcd2bin(buf[4]);
	dt->पंचांग_mon	= bcd2bin(buf[5] & 0x1F) - 1;
	dt->पंचांग_year	= bcd2bin(buf[6]) + 100; /* year offset from 1900 */

	वापस 0;
पूर्ण

अटल पूर्णांक ds1343_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev);
	u8 buf[7];

	buf[0] = bin2bcd(dt->पंचांग_sec);
	buf[1] = bin2bcd(dt->पंचांग_min);
	buf[2] = bin2bcd(dt->पंचांग_hour) & 0x3F;
	buf[3] = bin2bcd(dt->पंचांग_wday + 1);
	buf[4] = bin2bcd(dt->पंचांग_mday);
	buf[5] = bin2bcd(dt->पंचांग_mon + 1);
	buf[6] = bin2bcd(dt->पंचांग_year - 100);

	वापस regmap_bulk_ग_लिखो(priv->map, DS1343_SECONDS_REG,
				 buf, माप(buf));
पूर्ण

अटल पूर्णांक ds1343_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[4];
	अचिन्हित पूर्णांक val;
	पूर्णांक res;

	अगर (priv->irq <= 0)
		वापस -EINVAL;

	res = regmap_पढ़ो(priv->map, DS1343_STATUS_REG, &val);
	अगर (res)
		वापस res;

	alarm->pending = !!(val & DS1343_IRQF0);

	res = regmap_पढ़ो(priv->map, DS1343_CONTROL_REG, &val);
	अगर (res)
		वापस res;
	alarm->enabled = !!(val & DS1343_A0IE);

	res = regmap_bulk_पढ़ो(priv->map, DS1343_ALM0_SEC_REG, buf, 4);
	अगर (res)
		वापस res;

	alarm->समय.पंचांग_sec = bcd2bin(buf[0]) & 0x7f;
	alarm->समय.पंचांग_min = bcd2bin(buf[1]) & 0x7f;
	alarm->समय.पंचांग_hour = bcd2bin(buf[2]) & 0x3f;
	alarm->समय.पंचांग_mday = bcd2bin(buf[3]) & 0x3f;

	वापस 0;
पूर्ण

अटल पूर्णांक ds1343_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alarm)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[4];
	पूर्णांक res = 0;

	अगर (priv->irq <= 0)
		वापस -EINVAL;

	res = regmap_update_bits(priv->map, DS1343_CONTROL_REG, DS1343_A0IE, 0);
	अगर (res)
		वापस res;

	buf[0] = bin2bcd(alarm->समय.पंचांग_sec);
	buf[1] = bin2bcd(alarm->समय.पंचांग_min);
	buf[2] = bin2bcd(alarm->समय.पंचांग_hour);
	buf[3] = bin2bcd(alarm->समय.पंचांग_mday);

	res = regmap_bulk_ग_लिखो(priv->map, DS1343_ALM0_SEC_REG, buf, 4);
	अगर (res)
		वापस res;

	अगर (alarm->enabled)
		res = regmap_update_bits(priv->map, DS1343_CONTROL_REG,
					 DS1343_A0IE, DS1343_A0IE);

	वापस res;
पूर्ण

अटल पूर्णांक ds1343_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा ds1343_priv *priv = dev_get_drvdata(dev);

	अगर (priv->irq <= 0)
		वापस -EINVAL;

	वापस regmap_update_bits(priv->map, DS1343_CONTROL_REG,
				  DS1343_A0IE, enabled ? DS1343_A0IE : 0);
पूर्ण

अटल irqवापस_t ds1343_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ds1343_priv *priv = dev_id;
	अचिन्हित पूर्णांक stat;
	पूर्णांक res = 0;

	rtc_lock(priv->rtc);

	res = regmap_पढ़ो(priv->map, DS1343_STATUS_REG, &stat);
	अगर (res)
		जाओ out;

	अगर (stat & DS1343_IRQF0) अणु
		stat &= ~DS1343_IRQF0;
		regmap_ग_लिखो(priv->map, DS1343_STATUS_REG, stat);

		rtc_update_irq(priv->rtc, 1, RTC_AF | RTC_IRQF);

		regmap_update_bits(priv->map, DS1343_CONTROL_REG,
				   DS1343_A0IE, 0);
	पूर्ण

out:
	rtc_unlock(priv->rtc);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1343_rtc_ops = अणु
	.पढ़ो_समय	= ds1343_पढ़ो_समय,
	.set_समय	= ds1343_set_समय,
	.पढ़ो_alarm	= ds1343_पढ़ो_alarm,
	.set_alarm	= ds1343_set_alarm,
	.alarm_irq_enable = ds1343_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक ds1343_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ds1343_priv *priv;
	काष्ठा regmap_config config = अणु .reg_bits = 8, .val_bits = 8,
					.ग_लिखो_flag_mask = 0x80, पूर्ण;
	अचिन्हित पूर्णांक data;
	पूर्णांक res;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "ds1343-",
		.word_size = 1,
		.stride = 1,
		.size = DS1343_NVRAM_LEN,
		.reg_पढ़ो = ds1343_nvram_पढ़ो,
		.reg_ग_लिखो = ds1343_nvram_ग_लिखो,
	पूर्ण;

	priv = devm_kzalloc(&spi->dev, माप(काष्ठा ds1343_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* RTC DS1347 works in spi mode 3 and
	 * its chip select is active high. Active high should be defined as
	 * "inverse polarity" as GPIO-based chip selects can be logically
	 * active high but inverted by the GPIO library.
	 */
	spi->mode |= SPI_MODE_3;
	spi->mode ^= SPI_CS_HIGH;
	spi->bits_per_word = 8;
	res = spi_setup(spi);
	अगर (res)
		वापस res;

	spi_set_drvdata(spi, priv);

	priv->map = devm_regmap_init_spi(spi, &config);

	अगर (IS_ERR(priv->map)) अणु
		dev_err(&spi->dev, "spi regmap init failed for rtc ds1343\n");
		वापस PTR_ERR(priv->map);
	पूर्ण

	res = regmap_पढ़ो(priv->map, DS1343_SECONDS_REG, &data);
	अगर (res)
		वापस res;

	regmap_पढ़ो(priv->map, DS1343_CONTROL_REG, &data);
	data |= DS1343_INTCN;
	data &= ~(DS1343_EOSC | DS1343_A1IE | DS1343_A0IE);
	regmap_ग_लिखो(priv->map, DS1343_CONTROL_REG, data);

	regmap_पढ़ो(priv->map, DS1343_STATUS_REG, &data);
	data &= ~(DS1343_OSF | DS1343_IRQF1 | DS1343_IRQF0);
	regmap_ग_लिखो(priv->map, DS1343_STATUS_REG, data);

	priv->rtc = devm_rtc_allocate_device(&spi->dev);
	अगर (IS_ERR(priv->rtc))
		वापस PTR_ERR(priv->rtc);

	priv->rtc->ops = &ds1343_rtc_ops;
	priv->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	priv->rtc->range_max = RTC_TIMESTAMP_END_2099;

	res = rtc_add_group(priv->rtc, &ds1343_attr_group);
	अगर (res)
		dev_err(&spi->dev,
			"unable to create sysfs entries for rtc ds1343\n");

	res = devm_rtc_रेजिस्टर_device(priv->rtc);
	अगर (res)
		वापस res;

	nvmem_cfg.priv = priv;
	devm_rtc_nvmem_रेजिस्टर(priv->rtc, &nvmem_cfg);

	priv->irq = spi->irq;

	अगर (priv->irq >= 0) अणु
		res = devm_request_thपढ़ोed_irq(&spi->dev, spi->irq, शून्य,
						ds1343_thपढ़ो, IRQF_ONESHOT,
						"ds1343", priv);
		अगर (res) अणु
			priv->irq = -1;
			dev_err(&spi->dev,
				"unable to request irq for rtc ds1343\n");
		पूर्ण अन्यथा अणु
			device_init_wakeup(&spi->dev, true);
			dev_pm_set_wake_irq(&spi->dev, spi->irq);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ds1343_हटाओ(काष्ठा spi_device *spi)
अणु
	dev_pm_clear_wake_irq(&spi->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक ds1343_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	अगर (spi->irq >= 0 && device_may_wakeup(dev))
		enable_irq_wake(spi->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1343_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	अगर (spi->irq >= 0 && device_may_wakeup(dev))
		disable_irq_wake(spi->irq);

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ds1343_pm, ds1343_suspend, ds1343_resume);

अटल काष्ठा spi_driver ds1343_driver = अणु
	.driver = अणु
		.name = "ds1343",
		.pm = &ds1343_pm,
	पूर्ण,
	.probe = ds1343_probe,
	.हटाओ = ds1343_हटाओ,
	.id_table = ds1343_id,
पूर्ण;

module_spi_driver(ds1343_driver);

MODULE_DESCRIPTION("DS1343 RTC SPI Driver");
MODULE_AUTHOR("Raghavendra Chandra Ganiga <ravi23ganiga@gmail.com>,"
		"Ankur Srivastava <sankurece@gmail.com>");
MODULE_LICENSE("GPL v2");
