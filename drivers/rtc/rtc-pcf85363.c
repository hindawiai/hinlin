<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * drivers/rtc/rtc-pcf85363.c
 *
 * Driver क्रम NXP PCF85363 real-समय घड़ी.
 *
 * Copyright (C) 2017 Eric Nelson
 */
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtc.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bcd.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

/*
 * Date/Time रेजिस्टरs
 */
#घोषणा DT_100THS	0x00
#घोषणा DT_SECS		0x01
#घोषणा DT_MINUTES	0x02
#घोषणा DT_HOURS	0x03
#घोषणा DT_DAYS		0x04
#घोषणा DT_WEEKDAYS	0x05
#घोषणा DT_MONTHS	0x06
#घोषणा DT_YEARS	0x07

/*
 * Alarm रेजिस्टरs
 */
#घोषणा DT_SECOND_ALM1	0x08
#घोषणा DT_MINUTE_ALM1	0x09
#घोषणा DT_HOUR_ALM1	0x0a
#घोषणा DT_DAY_ALM1	0x0b
#घोषणा DT_MONTH_ALM1	0x0c
#घोषणा DT_MINUTE_ALM2	0x0d
#घोषणा DT_HOUR_ALM2	0x0e
#घोषणा DT_WEEKDAY_ALM2	0x0f
#घोषणा DT_ALARM_EN	0x10

/*
 * Time stamp रेजिस्टरs
 */
#घोषणा DT_TIMESTAMP1	0x11
#घोषणा DT_TIMESTAMP2	0x17
#घोषणा DT_TIMESTAMP3	0x1d
#घोषणा DT_TS_MODE	0x23

/*
 * control रेजिस्टरs
 */
#घोषणा CTRL_OFFSET	0x24
#घोषणा CTRL_OSCILLATOR	0x25
#घोषणा CTRL_BATTERY	0x26
#घोषणा CTRL_PIN_IO	0x27
#घोषणा CTRL_FUNCTION	0x28
#घोषणा CTRL_INTA_EN	0x29
#घोषणा CTRL_INTB_EN	0x2a
#घोषणा CTRL_FLAGS	0x2b
#घोषणा CTRL_RAMBYTE	0x2c
#घोषणा CTRL_WDOG	0x2d
#घोषणा CTRL_STOP_EN	0x2e
#घोषणा CTRL_RESETS	0x2f
#घोषणा CTRL_RAM	0x40

#घोषणा ALRM_SEC_A1E	BIT(0)
#घोषणा ALRM_MIN_A1E	BIT(1)
#घोषणा ALRM_HR_A1E	BIT(2)
#घोषणा ALRM_DAY_A1E	BIT(3)
#घोषणा ALRM_MON_A1E	BIT(4)
#घोषणा ALRM_MIN_A2E	BIT(5)
#घोषणा ALRM_HR_A2E	BIT(6)
#घोषणा ALRM_DAY_A2E	BIT(7)

#घोषणा INT_WDIE	BIT(0)
#घोषणा INT_BSIE	BIT(1)
#घोषणा INT_TSRIE	BIT(2)
#घोषणा INT_A2IE	BIT(3)
#घोषणा INT_A1IE	BIT(4)
#घोषणा INT_OIE		BIT(5)
#घोषणा INT_PIE		BIT(6)
#घोषणा INT_ILP		BIT(7)

#घोषणा FLAGS_TSR1F	BIT(0)
#घोषणा FLAGS_TSR2F	BIT(1)
#घोषणा FLAGS_TSR3F	BIT(2)
#घोषणा FLAGS_BSF	BIT(3)
#घोषणा FLAGS_WDF	BIT(4)
#घोषणा FLAGS_A1F	BIT(5)
#घोषणा FLAGS_A2F	BIT(6)
#घोषणा FLAGS_PIF	BIT(7)

#घोषणा PIN_IO_INTAPM	GENMASK(1, 0)
#घोषणा PIN_IO_INTA_CLK	0
#घोषणा PIN_IO_INTA_BAT	1
#घोषणा PIN_IO_INTA_OUT	2
#घोषणा PIN_IO_INTA_HIZ	3

#घोषणा STOP_EN_STOP	BIT(0)

#घोषणा RESET_CPR	0xa4

#घोषणा NVRAM_SIZE	0x40

काष्ठा pcf85363 अणु
	काष्ठा rtc_device	*rtc;
	काष्ठा regmap		*regmap;
पूर्ण;

काष्ठा pcf85x63_config अणु
	काष्ठा regmap_config regmap;
	अचिन्हित पूर्णांक num_nvram;
पूर्ण;

अटल पूर्णांक pcf85363_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf85363 *pcf85363 = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[DT_YEARS + 1];
	पूर्णांक ret, len = माप(buf);

	/* पढ़ो the RTC date and समय रेजिस्टरs all at once */
	ret = regmap_bulk_पढ़ो(pcf85363->regmap, DT_100THS, buf, len);
	अगर (ret) अणु
		dev_err(dev, "%s: error %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	पंचांग->पंचांग_year = bcd2bin(buf[DT_YEARS]);
	/* adjust क्रम 1900 base of rtc_समय */
	पंचांग->पंचांग_year += 100;

	पंचांग->पंचांग_wday = buf[DT_WEEKDAYS] & 7;
	buf[DT_SECS] &= 0x7F;
	पंचांग->पंचांग_sec = bcd2bin(buf[DT_SECS]);
	buf[DT_MINUTES] &= 0x7F;
	पंचांग->पंचांग_min = bcd2bin(buf[DT_MINUTES]);
	पंचांग->पंचांग_hour = bcd2bin(buf[DT_HOURS]);
	पंचांग->पंचांग_mday = bcd2bin(buf[DT_DAYS]);
	पंचांग->पंचांग_mon = bcd2bin(buf[DT_MONTHS]) - 1;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf85363_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf85363 *pcf85363 = dev_get_drvdata(dev);
	अचिन्हित अक्षर पंचांगp[11];
	अचिन्हित अक्षर *buf = &पंचांगp[2];
	पूर्णांक ret;

	पंचांगp[0] = STOP_EN_STOP;
	पंचांगp[1] = RESET_CPR;

	buf[DT_100THS] = 0;
	buf[DT_SECS] = bin2bcd(पंचांग->पंचांग_sec);
	buf[DT_MINUTES] = bin2bcd(पंचांग->पंचांग_min);
	buf[DT_HOURS] = bin2bcd(पंचांग->पंचांग_hour);
	buf[DT_DAYS] = bin2bcd(पंचांग->पंचांग_mday);
	buf[DT_WEEKDAYS] = पंचांग->पंचांग_wday;
	buf[DT_MONTHS] = bin2bcd(पंचांग->पंचांग_mon + 1);
	buf[DT_YEARS] = bin2bcd(पंचांग->पंचांग_year % 100);

	ret = regmap_bulk_ग_लिखो(pcf85363->regmap, CTRL_STOP_EN,
				पंचांगp, 2);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_ग_लिखो(pcf85363->regmap, DT_100THS,
				buf, माप(पंचांगp) - 2);
	अगर (ret)
		वापस ret;

	वापस regmap_ग_लिखो(pcf85363->regmap, CTRL_STOP_EN, 0);
पूर्ण

अटल पूर्णांक pcf85363_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcf85363 *pcf85363 = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[DT_MONTH_ALM1 - DT_SECOND_ALM1 + 1];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(pcf85363->regmap, DT_SECOND_ALM1, buf,
			       माप(buf));
	अगर (ret)
		वापस ret;

	alrm->समय.पंचांग_sec = bcd2bin(buf[0]);
	alrm->समय.पंचांग_min = bcd2bin(buf[1]);
	alrm->समय.पंचांग_hour = bcd2bin(buf[2]);
	alrm->समय.पंचांग_mday = bcd2bin(buf[3]);
	alrm->समय.पंचांग_mon = bcd2bin(buf[4]) - 1;

	ret = regmap_पढ़ो(pcf85363->regmap, CTRL_INTA_EN, &val);
	अगर (ret)
		वापस ret;

	alrm->enabled =  !!(val & INT_A1IE);

	वापस 0;
पूर्ण

अटल पूर्णांक _pcf85363_rtc_alarm_irq_enable(काष्ठा pcf85363 *pcf85363, अचिन्हित
					  पूर्णांक enabled)
अणु
	अचिन्हित पूर्णांक alarm_flags = ALRM_SEC_A1E | ALRM_MIN_A1E | ALRM_HR_A1E |
				   ALRM_DAY_A1E | ALRM_MON_A1E;
	पूर्णांक ret;

	ret = regmap_update_bits(pcf85363->regmap, DT_ALARM_EN, alarm_flags,
				 enabled ? alarm_flags : 0);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(pcf85363->regmap, CTRL_INTA_EN,
				 INT_A1IE, enabled ? INT_A1IE : 0);

	अगर (ret || enabled)
		वापस ret;

	/* clear current flags */
	वापस regmap_update_bits(pcf85363->regmap, CTRL_FLAGS, FLAGS_A1F, 0);
पूर्ण

अटल पूर्णांक pcf85363_rtc_alarm_irq_enable(काष्ठा device *dev,
					 अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा pcf85363 *pcf85363 = dev_get_drvdata(dev);

	वापस _pcf85363_rtc_alarm_irq_enable(pcf85363, enabled);
पूर्ण

अटल पूर्णांक pcf85363_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcf85363 *pcf85363 = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[DT_MONTH_ALM1 - DT_SECOND_ALM1 + 1];
	पूर्णांक ret;

	buf[0] = bin2bcd(alrm->समय.पंचांग_sec);
	buf[1] = bin2bcd(alrm->समय.पंचांग_min);
	buf[2] = bin2bcd(alrm->समय.पंचांग_hour);
	buf[3] = bin2bcd(alrm->समय.पंचांग_mday);
	buf[4] = bin2bcd(alrm->समय.पंचांग_mon + 1);

	/*
	 * Disable the alarm पूर्णांकerrupt beक्रमe changing the value to aव्योम
	 * spurious पूर्णांकerrupts
	 */
	ret = _pcf85363_rtc_alarm_irq_enable(pcf85363, 0);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_ग_लिखो(pcf85363->regmap, DT_SECOND_ALM1, buf,
				माप(buf));
	अगर (ret)
		वापस ret;

	वापस _pcf85363_rtc_alarm_irq_enable(pcf85363, alrm->enabled);
पूर्ण

अटल irqवापस_t pcf85363_rtc_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pcf85363 *pcf85363 = i2c_get_clientdata(dev_id);
	अचिन्हित पूर्णांक flags;
	पूर्णांक err;

	err = regmap_पढ़ो(pcf85363->regmap, CTRL_FLAGS, &flags);
	अगर (err)
		वापस IRQ_NONE;

	अगर (flags & FLAGS_A1F) अणु
		rtc_update_irq(pcf85363->rtc, 1, RTC_IRQF | RTC_AF);
		regmap_update_bits(pcf85363->regmap, CTRL_FLAGS, FLAGS_A1F, 0);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtc_ops = अणु
	.पढ़ो_समय	= pcf85363_rtc_पढ़ो_समय,
	.set_समय	= pcf85363_rtc_set_समय,
	.पढ़ो_alarm	= pcf85363_rtc_पढ़ो_alarm,
	.set_alarm	= pcf85363_rtc_set_alarm,
	.alarm_irq_enable = pcf85363_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक pcf85363_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			       माप_प्रकार bytes)
अणु
	काष्ठा pcf85363 *pcf85363 = priv;

	वापस regmap_bulk_पढ़ो(pcf85363->regmap, CTRL_RAM + offset,
				val, bytes);
पूर्ण

अटल पूर्णांक pcf85363_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
				माप_प्रकार bytes)
अणु
	काष्ठा pcf85363 *pcf85363 = priv;

	वापस regmap_bulk_ग_लिखो(pcf85363->regmap, CTRL_RAM + offset,
				 val, bytes);
पूर्ण

अटल पूर्णांक pcf85x63_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			       माप_प्रकार bytes)
अणु
	काष्ठा pcf85363 *pcf85363 = priv;
	अचिन्हित पूर्णांक पंचांगp_val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pcf85363->regmap, CTRL_RAMBYTE, &पंचांगp_val);
	(*(अचिन्हित अक्षर *) val) = (अचिन्हित अक्षर) पंचांगp_val;

	वापस ret;
पूर्ण

अटल पूर्णांक pcf85x63_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
				माप_प्रकार bytes)
अणु
	काष्ठा pcf85363 *pcf85363 = priv;
	अचिन्हित अक्षर पंचांगp_val;

	पंचांगp_val = *((अचिन्हित अक्षर *)val);
	वापस regmap_ग_लिखो(pcf85363->regmap, CTRL_RAMBYTE,
				(अचिन्हित पूर्णांक)पंचांगp_val);
पूर्ण

अटल स्थिर काष्ठा pcf85x63_config pcf_85263_config = अणु
	.regmap = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x2f,
	पूर्ण,
	.num_nvram = 1
पूर्ण;

अटल स्थिर काष्ठा pcf85x63_config pcf_85363_config = अणु
	.regmap = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x7f,
	पूर्ण,
	.num_nvram = 2
पूर्ण;

अटल पूर्णांक pcf85363_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pcf85363 *pcf85363;
	स्थिर काष्ठा pcf85x63_config *config = &pcf_85363_config;
	स्थिर व्योम *data = of_device_get_match_data(&client->dev);
	अटल काष्ठा nvmem_config nvmem_cfg[] = अणु
		अणु
			.name = "pcf85x63-",
			.word_size = 1,
			.stride = 1,
			.size = 1,
			.reg_पढ़ो = pcf85x63_nvram_पढ़ो,
			.reg_ग_लिखो = pcf85x63_nvram_ग_लिखो,
		पूर्ण, अणु
			.name = "pcf85363-",
			.word_size = 1,
			.stride = 1,
			.size = NVRAM_SIZE,
			.reg_पढ़ो = pcf85363_nvram_पढ़ो,
			.reg_ग_लिखो = pcf85363_nvram_ग_लिखो,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret, i;

	अगर (data)
		config = data;

	pcf85363 = devm_kzalloc(&client->dev, माप(काष्ठा pcf85363),
				GFP_KERNEL);
	अगर (!pcf85363)
		वापस -ENOMEM;

	pcf85363->regmap = devm_regmap_init_i2c(client, &config->regmap);
	अगर (IS_ERR(pcf85363->regmap)) अणु
		dev_err(&client->dev, "regmap allocation failed\n");
		वापस PTR_ERR(pcf85363->regmap);
	पूर्ण

	i2c_set_clientdata(client, pcf85363);

	pcf85363->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(pcf85363->rtc))
		वापस PTR_ERR(pcf85363->rtc);

	pcf85363->rtc->ops = &rtc_ops;
	pcf85363->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	pcf85363->rtc->range_max = RTC_TIMESTAMP_END_2099;
	clear_bit(RTC_FEATURE_ALARM, pcf85363->rtc->features);

	अगर (client->irq > 0) अणु
		regmap_ग_लिखो(pcf85363->regmap, CTRL_FLAGS, 0);
		regmap_update_bits(pcf85363->regmap, CTRL_PIN_IO,
				   PIN_IO_INTA_OUT, PIN_IO_INTAPM);
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, pcf85363_rtc_handle_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"pcf85363", client);
		अगर (ret)
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
		अन्यथा
			set_bit(RTC_FEATURE_ALARM, pcf85363->rtc->features);
	पूर्ण

	ret = devm_rtc_रेजिस्टर_device(pcf85363->rtc);

	क्रम (i = 0; i < config->num_nvram; i++) अणु
		nvmem_cfg[i].priv = pcf85363;
		devm_rtc_nvmem_रेजिस्टर(pcf85363->rtc, &nvmem_cfg[i]);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर __maybe_unused काष्ठा of_device_id dev_ids[] = अणु
	अणु .compatible = "nxp,pcf85263", .data = &pcf_85263_config पूर्ण,
	अणु .compatible = "nxp,pcf85363", .data = &pcf_85363_config पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dev_ids);

अटल काष्ठा i2c_driver pcf85363_driver = अणु
	.driver	= अणु
		.name	= "pcf85363",
		.of_match_table = of_match_ptr(dev_ids),
	पूर्ण,
	.probe	= pcf85363_probe,
पूर्ण;

module_i2c_driver(pcf85363_driver);

MODULE_AUTHOR("Eric Nelson");
MODULE_DESCRIPTION("pcf85263/pcf85363 I2C RTC driver");
MODULE_LICENSE("GPL");
