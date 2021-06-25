<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Avionic Design GmbH
 */

#समावेश <linux/bcd.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_wakeirq.h>

#घोषणा REG_CONTROL1 0x00
#घोषणा REG_CONTROL1_CAP_SEL BIT(7)
#घोषणा REG_CONTROL1_STOP    BIT(5)
#घोषणा REG_CONTROL1_AIE    BIT(1)

#घोषणा REG_CONTROL2 0x01
#घोषणा REG_CONTROL2_AF BIT(3)

#घोषणा REG_CONTROL3 0x02
#घोषणा REG_CONTROL3_PM_BLD BIT(7) /* battery low detection disabled */
#घोषणा REG_CONTROL3_PM_VDD BIT(6) /* चयन-over disabled */
#घोषणा REG_CONTROL3_PM_DSM BIT(5) /* direct चयनing mode */
#घोषणा REG_CONTROL3_PM_MASK 0xe0
#घोषणा REG_CONTROL3_BLF BIT(2) /* battery low bit, पढ़ो-only */

#घोषणा REG_SECONDS  0x03
#घोषणा REG_SECONDS_OS BIT(7)

#घोषणा REG_MINUTES  0x04
#घोषणा REG_HOURS    0x05
#घोषणा REG_DAYS     0x06
#घोषणा REG_WEEKDAYS 0x07
#घोषणा REG_MONTHS   0x08
#घोषणा REG_YEARS    0x09

#घोषणा REG_MINUTE_ALARM	0x0a
#घोषणा REG_HOUR_ALARM		0x0b
#घोषणा REG_DAY_ALARM		0x0c
#घोषणा REG_WEEKDAY_ALARM	0x0d
#घोषणा ALARM_DIS BIT(7)

#घोषणा REG_OFFSET   0x0e
#घोषणा REG_OFFSET_MODE BIT(7)

#घोषणा REG_TMR_CLKOUT_CTRL 0x0f

काष्ठा pcf8523 अणु
	काष्ठा rtc_device *rtc;
	काष्ठा i2c_client *client;
पूर्ण;

अटल पूर्णांक pcf8523_पढ़ो(काष्ठा i2c_client *client, u8 reg, u8 *valuep)
अणु
	काष्ठा i2c_msg msgs[2];
	u8 value = 0;
	पूर्णांक err;

	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = माप(reg);
	msgs[0].buf = &reg;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = माप(value);
	msgs[1].buf = &value;

	err = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (err < 0)
		वापस err;

	*valuep = value;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_ग_लिखो(काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	u8 buffer[2] = अणु reg, value पूर्ण;
	काष्ठा i2c_msg msg;
	पूर्णांक err;

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = माप(buffer);
	msg.buf = buffer;

	err = i2c_transfer(client->adapter, &msg, 1);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_voltage_low(काष्ठा i2c_client *client)
अणु
	u8 value;
	पूर्णांक err;

	err = pcf8523_पढ़ो(client, REG_CONTROL3, &value);
	अगर (err < 0)
		वापस err;

	वापस !!(value & REG_CONTROL3_BLF);
पूर्ण

अटल पूर्णांक pcf8523_load_capacitance(काष्ठा i2c_client *client)
अणु
	u32 load;
	u8 value;
	पूर्णांक err;

	err = pcf8523_पढ़ो(client, REG_CONTROL1, &value);
	अगर (err < 0)
		वापस err;

	load = 12500;
	of_property_पढ़ो_u32(client->dev.of_node, "quartz-load-femtofarads",
			     &load);

	चयन (load) अणु
	शेष:
		dev_warn(&client->dev, "Unknown quartz-load-femtofarads value: %d. Assuming 12500",
			 load);
		fallthrough;
	हाल 12500:
		value |= REG_CONTROL1_CAP_SEL;
		अवरोध;
	हाल 7000:
		value &= ~REG_CONTROL1_CAP_SEL;
		अवरोध;
	पूर्ण

	err = pcf8523_ग_लिखो(client, REG_CONTROL1, value);

	वापस err;
पूर्ण

अटल पूर्णांक pcf8523_set_pm(काष्ठा i2c_client *client, u8 pm)
अणु
	u8 value;
	पूर्णांक err;

	err = pcf8523_पढ़ो(client, REG_CONTROL3, &value);
	अगर (err < 0)
		वापस err;

	value = (value & ~REG_CONTROL3_PM_MASK) | pm;

	err = pcf8523_ग_लिखो(client, REG_CONTROL3, value);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल irqवापस_t pcf8523_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pcf8523 *pcf8523 = i2c_get_clientdata(dev_id);
	u8 value;
	पूर्णांक err;

	err = pcf8523_पढ़ो(pcf8523->client, REG_CONTROL2, &value);
	अगर (err < 0)
		वापस IRQ_HANDLED;

	अगर (value & REG_CONTROL2_AF) अणु
		value &= ~REG_CONTROL2_AF;
		pcf8523_ग_लिखो(pcf8523->client, REG_CONTROL2, value);
		rtc_update_irq(pcf8523->rtc, 1, RTC_IRQF | RTC_AF);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक pcf8523_stop_rtc(काष्ठा i2c_client *client)
अणु
	u8 value;
	पूर्णांक err;

	err = pcf8523_पढ़ो(client, REG_CONTROL1, &value);
	अगर (err < 0)
		वापस err;

	value |= REG_CONTROL1_STOP;

	err = pcf8523_ग_लिखो(client, REG_CONTROL1, value);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_start_rtc(काष्ठा i2c_client *client)
अणु
	u8 value;
	पूर्णांक err;

	err = pcf8523_पढ़ो(client, REG_CONTROL1, &value);
	अगर (err < 0)
		वापस err;

	value &= ~REG_CONTROL1_STOP;

	err = pcf8523_ग_लिखो(client, REG_CONTROL1, value);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 start = REG_SECONDS, regs[7];
	काष्ठा i2c_msg msgs[2];
	पूर्णांक err;

	err = pcf8523_voltage_low(client);
	अगर (err < 0) अणु
		वापस err;
	पूर्ण अन्यथा अगर (err > 0) अणु
		dev_err(dev, "low voltage detected, time is unreliable\n");
		वापस -EINVAL;
	पूर्ण

	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &start;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = माप(regs);
	msgs[1].buf = regs;

	err = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (err < 0)
		वापस err;

	अगर (regs[0] & REG_SECONDS_OS)
		वापस -EINVAL;

	पंचांग->पंचांग_sec = bcd2bin(regs[0] & 0x7f);
	पंचांग->पंचांग_min = bcd2bin(regs[1] & 0x7f);
	पंचांग->पंचांग_hour = bcd2bin(regs[2] & 0x3f);
	पंचांग->पंचांग_mday = bcd2bin(regs[3] & 0x3f);
	पंचांग->पंचांग_wday = regs[4] & 0x7;
	पंचांग->पंचांग_mon = bcd2bin(regs[5] & 0x1f) - 1;
	पंचांग->पंचांग_year = bcd2bin(regs[6]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_msg msg;
	u8 regs[8];
	पूर्णांक err;

	err = pcf8523_stop_rtc(client);
	अगर (err < 0)
		वापस err;

	regs[0] = REG_SECONDS;
	/* This will purposely overग_लिखो REG_SECONDS_OS */
	regs[1] = bin2bcd(पंचांग->पंचांग_sec);
	regs[2] = bin2bcd(पंचांग->पंचांग_min);
	regs[3] = bin2bcd(पंचांग->पंचांग_hour);
	regs[4] = bin2bcd(पंचांग->पंचांग_mday);
	regs[5] = पंचांग->पंचांग_wday;
	regs[6] = bin2bcd(पंचांग->पंचांग_mon + 1);
	regs[7] = bin2bcd(पंचांग->पंचांग_year - 100);

	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = माप(regs);
	msg.buf = regs;

	err = i2c_transfer(client->adapter, &msg, 1);
	अगर (err < 0) अणु
		/*
		 * If the समय cannot be set, restart the RTC anyway. Note
		 * that errors are ignored अगर the RTC cannot be started so
		 * that we have a chance to propagate the original error.
		 */
		pcf8523_start_rtc(client);
		वापस err;
	पूर्ण

	वापस pcf8523_start_rtc(client);
पूर्ण

अटल पूर्णांक pcf8523_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 start = REG_MINUTE_ALARM, regs[4];
	काष्ठा i2c_msg msgs[2];
	u8 value;
	पूर्णांक err;

	msgs[0].addr = client->addr;
	msgs[0].flags = 0;
	msgs[0].len = 1;
	msgs[0].buf = &start;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = माप(regs);
	msgs[1].buf = regs;

	err = i2c_transfer(client->adapter, msgs, ARRAY_SIZE(msgs));
	अगर (err < 0)
		वापस err;

	पंचांग->समय.पंचांग_sec = 0;
	पंचांग->समय.पंचांग_min = bcd2bin(regs[0] & 0x7F);
	पंचांग->समय.पंचांग_hour = bcd2bin(regs[1] & 0x3F);
	पंचांग->समय.पंचांग_mday = bcd2bin(regs[2] & 0x3F);
	पंचांग->समय.पंचांग_wday = bcd2bin(regs[3] & 0x7);

	err = pcf8523_पढ़ो(client, REG_CONTROL1, &value);
	अगर (err < 0)
		वापस err;
	पंचांग->enabled = !!(value & REG_CONTROL1_AIE);

	err = pcf8523_पढ़ो(client, REG_CONTROL2, &value);
	अगर (err < 0)
		वापस err;
	पंचांग->pending = !!(value & REG_CONTROL2_AF);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 value;
	पूर्णांक err;

	err = pcf8523_पढ़ो(client, REG_CONTROL1, &value);
	अगर (err < 0)
		वापस err;

	value &= REG_CONTROL1_AIE;

	अगर (enabled)
		value |= REG_CONTROL1_AIE;

	err = pcf8523_ग_लिखो(client, REG_CONTROL1, value);
	अगर (err < 0)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा i2c_msg msg;
	u8 regs[5];
	पूर्णांक err;

	err = pcf8523_irq_enable(dev, 0);
	अगर (err)
		वापस err;

	err = pcf8523_ग_लिखो(client, REG_CONTROL2, 0);
	अगर (err < 0)
		वापस err;

	/* The alarm has no seconds, round up to nearest minute */
	अगर (पंचांग->समय.पंचांग_sec) अणु
		समय64_t alarm_समय = rtc_पंचांग_to_समय64(&पंचांग->समय);

		alarm_समय += 60 - पंचांग->समय.पंचांग_sec;
		rtc_समय64_to_पंचांग(alarm_समय, &पंचांग->समय);
	पूर्ण

	regs[0] = REG_MINUTE_ALARM;
	regs[1] = bin2bcd(पंचांग->समय.पंचांग_min);
	regs[2] = bin2bcd(पंचांग->समय.पंचांग_hour);
	regs[3] = bin2bcd(पंचांग->समय.पंचांग_mday);
	regs[4] = ALARM_DIS;
	msg.addr = client->addr;
	msg.flags = 0;
	msg.len = माप(regs);
	msg.buf = regs;
	err = i2c_transfer(client->adapter, &msg, 1);
	अगर (err < 0)
		वापस err;

	अगर (पंचांग->enabled)
		वापस pcf8523_irq_enable(dev, पंचांग->enabled);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_RTC_INTF_DEV
अटल पूर्णांक pcf8523_rtc_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd,
			     अचिन्हित दीर्घ arg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित पूर्णांक flags = 0;
	u8 value;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		ret = pcf8523_voltage_low(client);
		अगर (ret < 0)
			वापस ret;
		अगर (ret)
			flags |= RTC_VL_BACKUP_LOW;

		ret = pcf8523_पढ़ो(client, REG_SECONDS, &value);
		अगर (ret < 0)
			वापस ret;

		अगर (value & REG_SECONDS_OS)
			flags |= RTC_VL_DATA_INVALID;

		वापस put_user(flags, (अचिन्हित पूर्णांक __user *)arg);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण
#अन्यथा
#घोषणा pcf8523_rtc_ioctl शून्य
#पूर्ण_अगर

अटल पूर्णांक pcf8523_rtc_पढ़ो_offset(काष्ठा device *dev, दीर्घ *offset)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक err;
	u8 value;
	s8 val;

	err = pcf8523_पढ़ो(client, REG_OFFSET, &value);
	अगर (err < 0)
		वापस err;

	/* sign extend the 7-bit offset value */
	val = value << 1;
	*offset = (value & REG_OFFSET_MODE ? 4069 : 4340) * (val >> 1);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8523_rtc_set_offset(काष्ठा device *dev, दीर्घ offset)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	दीर्घ reg_m0, reg_m1;
	u8 value;

	reg_m0 = clamp(DIV_ROUND_CLOSEST(offset, 4340), -64L, 63L);
	reg_m1 = clamp(DIV_ROUND_CLOSEST(offset, 4069), -64L, 63L);

	अगर (असल(reg_m0 * 4340 - offset) < असल(reg_m1 * 4069 - offset))
		value = reg_m0 & 0x7f;
	अन्यथा
		value = (reg_m1 & 0x7f) | REG_OFFSET_MODE;

	वापस pcf8523_ग_लिखो(client, REG_OFFSET, value);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pcf8523_rtc_ops = अणु
	.पढ़ो_समय = pcf8523_rtc_पढ़ो_समय,
	.set_समय = pcf8523_rtc_set_समय,
	.पढ़ो_alarm = pcf8523_rtc_पढ़ो_alarm,
	.set_alarm = pcf8523_rtc_set_alarm,
	.alarm_irq_enable = pcf8523_irq_enable,
	.ioctl = pcf8523_rtc_ioctl,
	.पढ़ो_offset = pcf8523_rtc_पढ़ो_offset,
	.set_offset = pcf8523_rtc_set_offset,
पूर्ण;

अटल पूर्णांक pcf8523_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pcf8523 *pcf8523;
	काष्ठा rtc_device *rtc;
	bool wakeup_source = false;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	pcf8523 = devm_kzalloc(&client->dev, माप(काष्ठा pcf8523), GFP_KERNEL);
	अगर (!pcf8523)
		वापस -ENOMEM;

	i2c_set_clientdata(client, pcf8523);
	pcf8523->client = client;

	err = pcf8523_load_capacitance(client);
	अगर (err < 0)
		dev_warn(&client->dev, "failed to set xtal load capacitance: %d",
			 err);

	err = pcf8523_set_pm(client, 0);
	अगर (err < 0)
		वापस err;

	rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	pcf8523->rtc = rtc;
	rtc->ops = &pcf8523_rtc_ops;
	rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->range_max = RTC_TIMESTAMP_END_2099;
	rtc->uie_unsupported = 1;

	अगर (client->irq > 0) अणु
		err = pcf8523_ग_लिखो(client, REG_TMR_CLKOUT_CTRL, 0x38);
		अगर (err < 0)
			वापस err;

		err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, pcf8523_irq,
						IRQF_SHARED | IRQF_ONESHOT | IRQF_TRIGGER_LOW,
						dev_name(&rtc->dev), client);
		अगर (err)
			वापस err;

		dev_pm_set_wake_irq(&client->dev, client->irq);
	पूर्ण

#अगर_घोषित CONFIG_OF
	wakeup_source = of_property_पढ़ो_bool(client->dev.of_node, "wakeup-source");
#पूर्ण_अगर
	अगर (client->irq > 0 || wakeup_source)
		device_init_wakeup(&client->dev, true);

	वापस devm_rtc_रेजिस्टर_device(rtc);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcf8523_id[] = अणु
	अणु "pcf8523", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf8523_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcf8523_of_match[] = अणु
	अणु .compatible = "nxp,pcf8523" पूर्ण,
	अणु .compatible = "microcrystal,rv8523" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcf8523_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver pcf8523_driver = अणु
	.driver = अणु
		.name = "rtc-pcf8523",
		.of_match_table = of_match_ptr(pcf8523_of_match),
	पूर्ण,
	.probe = pcf8523_probe,
	.id_table = pcf8523_id,
पूर्ण;
module_i2c_driver(pcf8523_driver);

MODULE_AUTHOR("Thierry Reding <thierry.reding@avionic-design.de>");
MODULE_DESCRIPTION("NXP PCF8523 RTC driver");
MODULE_LICENSE("GPL v2");
