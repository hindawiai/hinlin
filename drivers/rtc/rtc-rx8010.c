<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the Epson RTC module RX-8010 SJ
 *
 * Copyright(C) Timesys Corporation 2015
 * Copyright(C) General Electric Company 2015
 */

#समावेश <linux/bcd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>

#घोषणा RX8010_SEC		0x10
#घोषणा RX8010_MIN		0x11
#घोषणा RX8010_HOUR		0x12
#घोषणा RX8010_WDAY		0x13
#घोषणा RX8010_MDAY		0x14
#घोषणा RX8010_MONTH		0x15
#घोषणा RX8010_YEAR		0x16
#घोषणा RX8010_RESV17		0x17
#घोषणा RX8010_ALMIN		0x18
#घोषणा RX8010_ALHOUR		0x19
#घोषणा RX8010_ALWDAY		0x1A
#घोषणा RX8010_TCOUNT0		0x1B
#घोषणा RX8010_TCOUNT1		0x1C
#घोषणा RX8010_EXT		0x1D
#घोषणा RX8010_FLAG		0x1E
#घोषणा RX8010_CTRL		0x1F
/* 0x20 to 0x2F are user रेजिस्टरs */
#घोषणा RX8010_RESV30		0x30
#घोषणा RX8010_RESV31		0x31
#घोषणा RX8010_IRQ		0x32

#घोषणा RX8010_EXT_WADA		BIT(3)

#घोषणा RX8010_FLAG_VLF		BIT(1)
#घोषणा RX8010_FLAG_AF		BIT(3)
#घोषणा RX8010_FLAG_TF		BIT(4)
#घोषणा RX8010_FLAG_UF		BIT(5)

#घोषणा RX8010_CTRL_AIE		BIT(3)
#घोषणा RX8010_CTRL_UIE		BIT(5)
#घोषणा RX8010_CTRL_STOP	BIT(6)
#घोषणा RX8010_CTRL_TEST	BIT(7)

#घोषणा RX8010_ALARM_AE		BIT(7)

अटल स्थिर काष्ठा i2c_device_id rx8010_id[] = अणु
	अणु "rx8010", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rx8010_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id rx8010_of_match[] = अणु
	अणु .compatible = "epson,rx8010" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rx8010_of_match);

काष्ठा rx8010_data अणु
	काष्ठा regmap *regs;
	काष्ठा rtc_device *rtc;
	u8 ctrlreg;
पूर्ण;

अटल irqवापस_t rx8010_irq_1_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *client = dev_id;
	काष्ठा rx8010_data *rx8010 = i2c_get_clientdata(client);
	पूर्णांक flagreg, err;

	rtc_lock(rx8010->rtc);

	err = regmap_पढ़ो(rx8010->regs, RX8010_FLAG, &flagreg);
	अगर (err) अणु
		rtc_unlock(rx8010->rtc);
		वापस IRQ_NONE;
	पूर्ण

	अगर (flagreg & RX8010_FLAG_VLF)
		dev_warn(&client->dev, "Frequency stop detected\n");

	अगर (flagreg & RX8010_FLAG_TF) अणु
		flagreg &= ~RX8010_FLAG_TF;
		rtc_update_irq(rx8010->rtc, 1, RTC_PF | RTC_IRQF);
	पूर्ण

	अगर (flagreg & RX8010_FLAG_AF) अणु
		flagreg &= ~RX8010_FLAG_AF;
		rtc_update_irq(rx8010->rtc, 1, RTC_AF | RTC_IRQF);
	पूर्ण

	अगर (flagreg & RX8010_FLAG_UF) अणु
		flagreg &= ~RX8010_FLAG_UF;
		rtc_update_irq(rx8010->rtc, 1, RTC_UF | RTC_IRQF);
	पूर्ण

	err = regmap_ग_लिखो(rx8010->regs, RX8010_FLAG, flagreg);
	rtc_unlock(rx8010->rtc);
	वापस err ? IRQ_NONE : IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rx8010_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा rx8010_data *rx8010 = dev_get_drvdata(dev);
	u8 date[RX8010_YEAR - RX8010_SEC + 1];
	पूर्णांक flagreg, err;

	err = regmap_पढ़ो(rx8010->regs, RX8010_FLAG, &flagreg);
	अगर (err)
		वापस err;

	अगर (flagreg & RX8010_FLAG_VLF) अणु
		dev_warn(dev, "Frequency stop detected\n");
		वापस -EINVAL;
	पूर्ण

	err = regmap_bulk_पढ़ो(rx8010->regs, RX8010_SEC, date, माप(date));
	अगर (err)
		वापस err;

	dt->पंचांग_sec = bcd2bin(date[RX8010_SEC - RX8010_SEC] & 0x7f);
	dt->पंचांग_min = bcd2bin(date[RX8010_MIN - RX8010_SEC] & 0x7f);
	dt->पंचांग_hour = bcd2bin(date[RX8010_HOUR - RX8010_SEC] & 0x3f);
	dt->पंचांग_mday = bcd2bin(date[RX8010_MDAY - RX8010_SEC] & 0x3f);
	dt->पंचांग_mon = bcd2bin(date[RX8010_MONTH - RX8010_SEC] & 0x1f) - 1;
	dt->पंचांग_year = bcd2bin(date[RX8010_YEAR - RX8010_SEC]) + 100;
	dt->पंचांग_wday = ffs(date[RX8010_WDAY - RX8010_SEC] & 0x7f);

	वापस 0;
पूर्ण

अटल पूर्णांक rx8010_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *dt)
अणु
	काष्ठा rx8010_data *rx8010 = dev_get_drvdata(dev);
	u8 date[RX8010_YEAR - RX8010_SEC + 1];
	पूर्णांक err;

	/* set STOP bit beक्रमe changing घड़ी/calendar */
	err = regmap_set_bits(rx8010->regs, RX8010_CTRL, RX8010_CTRL_STOP);
	अगर (err)
		वापस err;

	date[RX8010_SEC - RX8010_SEC] = bin2bcd(dt->पंचांग_sec);
	date[RX8010_MIN - RX8010_SEC] = bin2bcd(dt->पंचांग_min);
	date[RX8010_HOUR - RX8010_SEC] = bin2bcd(dt->पंचांग_hour);
	date[RX8010_MDAY - RX8010_SEC] = bin2bcd(dt->पंचांग_mday);
	date[RX8010_MONTH - RX8010_SEC] = bin2bcd(dt->पंचांग_mon + 1);
	date[RX8010_YEAR - RX8010_SEC] = bin2bcd(dt->पंचांग_year - 100);
	date[RX8010_WDAY - RX8010_SEC] = bin2bcd(1 << dt->पंचांग_wday);

	err = regmap_bulk_ग_लिखो(rx8010->regs, RX8010_SEC, date, माप(date));
	अगर (err)
		वापस err;

	/* clear STOP bit after changing घड़ी/calendar */
	err = regmap_clear_bits(rx8010->regs, RX8010_CTRL, RX8010_CTRL_STOP);
	अगर (err)
		वापस err;

	err = regmap_clear_bits(rx8010->regs, RX8010_FLAG, RX8010_FLAG_VLF);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक rx8010_init(काष्ठा device *dev)
अणु
	काष्ठा rx8010_data *rx8010 = dev_get_drvdata(dev);
	u8 ctrl[2];
	पूर्णांक need_clear = 0, err;

	/* Initialize reserved रेजिस्टरs as specअगरied in datasheet */
	err = regmap_ग_लिखो(rx8010->regs, RX8010_RESV17, 0xD8);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(rx8010->regs, RX8010_RESV30, 0x00);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(rx8010->regs, RX8010_RESV31, 0x08);
	अगर (err)
		वापस err;

	err = regmap_ग_लिखो(rx8010->regs, RX8010_IRQ, 0x00);
	अगर (err)
		वापस err;

	err = regmap_bulk_पढ़ो(rx8010->regs, RX8010_FLAG, ctrl, 2);
	अगर (err)
		वापस err;

	अगर (ctrl[0] & RX8010_FLAG_VLF)
		dev_warn(dev, "Frequency stop was detected\n");

	अगर (ctrl[0] & RX8010_FLAG_AF) अणु
		dev_warn(dev, "Alarm was detected\n");
		need_clear = 1;
	पूर्ण

	अगर (ctrl[0] & RX8010_FLAG_TF)
		need_clear = 1;

	अगर (ctrl[0] & RX8010_FLAG_UF)
		need_clear = 1;

	अगर (need_clear) अणु
		ctrl[0] &= ~(RX8010_FLAG_AF | RX8010_FLAG_TF | RX8010_FLAG_UF);
		err = regmap_ग_लिखो(rx8010->regs, RX8010_FLAG, ctrl[0]);
		अगर (err)
			वापस err;
	पूर्ण

	rx8010->ctrlreg = (ctrl[1] & ~RX8010_CTRL_TEST);

	वापस 0;
पूर्ण

अटल पूर्णांक rx8010_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा rx8010_data *rx8010 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	पूर्णांक flagreg, err;

	err = regmap_bulk_पढ़ो(rx8010->regs, RX8010_ALMIN, alarmvals, 3);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(rx8010->regs, RX8010_FLAG, &flagreg);
	अगर (err)
		वापस err;

	t->समय.पंचांग_sec = 0;
	t->समय.पंचांग_min = bcd2bin(alarmvals[0] & 0x7f);
	t->समय.पंचांग_hour = bcd2bin(alarmvals[1] & 0x3f);

	अगर (!(alarmvals[2] & RX8010_ALARM_AE))
		t->समय.पंचांग_mday = bcd2bin(alarmvals[2] & 0x7f);

	t->enabled = !!(rx8010->ctrlreg & RX8010_CTRL_AIE);
	t->pending = (flagreg & RX8010_FLAG_AF) && t->enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक rx8010_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *t)
अणु
	काष्ठा rx8010_data *rx8010 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	पूर्णांक err;

	अगर (rx8010->ctrlreg & (RX8010_CTRL_AIE | RX8010_CTRL_UIE)) अणु
		rx8010->ctrlreg &= ~(RX8010_CTRL_AIE | RX8010_CTRL_UIE);
		err = regmap_ग_लिखो(rx8010->regs, RX8010_CTRL, rx8010->ctrlreg);
		अगर (err)
			वापस err;
	पूर्ण

	err = regmap_clear_bits(rx8010->regs, RX8010_FLAG, RX8010_FLAG_AF);
	अगर (err)
		वापस err;

	alarmvals[0] = bin2bcd(t->समय.पंचांग_min);
	alarmvals[1] = bin2bcd(t->समय.पंचांग_hour);
	alarmvals[2] = bin2bcd(t->समय.पंचांग_mday);

	err = regmap_bulk_ग_लिखो(rx8010->regs, RX8010_ALMIN, alarmvals, 2);
	अगर (err)
		वापस err;

	err = regmap_clear_bits(rx8010->regs, RX8010_EXT, RX8010_EXT_WADA);
	अगर (err)
		वापस err;

	अगर (alarmvals[2] == 0)
		alarmvals[2] |= RX8010_ALARM_AE;

	err = regmap_ग_लिखो(rx8010->regs, RX8010_ALWDAY, alarmvals[2]);
	अगर (err)
		वापस err;

	अगर (t->enabled) अणु
		अगर (rx8010->rtc->uie_rtस_समयr.enabled)
			rx8010->ctrlreg |= RX8010_CTRL_UIE;
		अगर (rx8010->rtc->aie_समयr.enabled)
			rx8010->ctrlreg |=
				(RX8010_CTRL_AIE | RX8010_CTRL_UIE);

		err = regmap_ग_लिखो(rx8010->regs, RX8010_CTRL, rx8010->ctrlreg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rx8010_alarm_irq_enable(काष्ठा device *dev,
				   अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा rx8010_data *rx8010 = dev_get_drvdata(dev);
	पूर्णांक err;
	u8 ctrl;

	ctrl = rx8010->ctrlreg;

	अगर (enabled) अणु
		अगर (rx8010->rtc->uie_rtस_समयr.enabled)
			ctrl |= RX8010_CTRL_UIE;
		अगर (rx8010->rtc->aie_समयr.enabled)
			ctrl |= (RX8010_CTRL_AIE | RX8010_CTRL_UIE);
	पूर्ण अन्यथा अणु
		अगर (!rx8010->rtc->uie_rtस_समयr.enabled)
			ctrl &= ~RX8010_CTRL_UIE;
		अगर (!rx8010->rtc->aie_समयr.enabled)
			ctrl &= ~RX8010_CTRL_AIE;
	पूर्ण

	err = regmap_clear_bits(rx8010->regs, RX8010_FLAG, RX8010_FLAG_AF);
	अगर (err)
		वापस err;

	अगर (ctrl != rx8010->ctrlreg) अणु
		rx8010->ctrlreg = ctrl;
		err = regmap_ग_लिखो(rx8010->regs, RX8010_CTRL, rx8010->ctrlreg);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rx8010_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा rx8010_data *rx8010 = dev_get_drvdata(dev);
	पूर्णांक पंचांगp, flagreg, err;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		err = regmap_पढ़ो(rx8010->regs, RX8010_FLAG, &flagreg);
		अगर (err)
			वापस err;

		पंचांगp = flagreg & RX8010_FLAG_VLF ? RTC_VL_DATA_INVALID : 0;
		वापस put_user(पंचांगp, (अचिन्हित पूर्णांक __user *)arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rx8010_rtc_ops = अणु
	.पढ़ो_समय = rx8010_get_समय,
	.set_समय = rx8010_set_समय,
	.ioctl = rx8010_ioctl,
	.पढ़ो_alarm = rx8010_पढ़ो_alarm,
	.set_alarm = rx8010_set_alarm,
	.alarm_irq_enable = rx8010_alarm_irq_enable,
पूर्ण;

अटल स्थिर काष्ठा regmap_config rx8010_regmap_config = अणु
	.name = "rx8010-rtc",
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक rx8010_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा rx8010_data *rx8010;
	पूर्णांक err = 0;

	rx8010 = devm_kzalloc(dev, माप(*rx8010), GFP_KERNEL);
	अगर (!rx8010)
		वापस -ENOMEM;

	i2c_set_clientdata(client, rx8010);

	rx8010->regs = devm_regmap_init_i2c(client, &rx8010_regmap_config);
	अगर (IS_ERR(rx8010->regs))
		वापस PTR_ERR(rx8010->regs);

	err = rx8010_init(dev);
	अगर (err)
		वापस err;

	rx8010->rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(rx8010->rtc))
		वापस PTR_ERR(rx8010->rtc);

	अगर (client->irq > 0) अणु
		dev_info(dev, "IRQ %d supplied\n", client->irq);
		err = devm_request_thपढ़ोed_irq(dev, client->irq, शून्य,
						rx8010_irq_1_handler,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"rx8010", client);
		अगर (err) अणु
			dev_err(dev, "unable to request IRQ\n");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_bit(RTC_FEATURE_ALARM, rx8010->rtc->features);
	पूर्ण

	rx8010->rtc->ops = &rx8010_rtc_ops;
	rx8010->rtc->max_user_freq = 1;
	rx8010->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rx8010->rtc->range_max = RTC_TIMESTAMP_END_2099;

	वापस devm_rtc_रेजिस्टर_device(rx8010->rtc);
पूर्ण

अटल काष्ठा i2c_driver rx8010_driver = अणु
	.driver = अणु
		.name = "rtc-rx8010",
		.of_match_table = of_match_ptr(rx8010_of_match),
	पूर्ण,
	.probe_new	= rx8010_probe,
	.id_table	= rx8010_id,
पूर्ण;

module_i2c_driver(rx8010_driver);

MODULE_AUTHOR("Akshay Bhat <akshay.bhat@timesys.com>");
MODULE_DESCRIPTION("Epson RX8010SJ RTC driver");
MODULE_LICENSE("GPL v2");
