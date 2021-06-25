<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * RTC driver क्रम the Micro Crystal RV8803
 *
 * Copyright (C) 2015 Micro Crystal SA
 * Alexandre Belloni <alexandre.belloni@bootlin.com>
 *
 */

#समावेश <linux/bcd.h>
#समावेश <linux/bitops.h>
#समावेश <linux/log2.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/rtc.h>

#घोषणा RV8803_I2C_TRY_COUNT		4

#घोषणा RV8803_SEC			0x00
#घोषणा RV8803_MIN			0x01
#घोषणा RV8803_HOUR			0x02
#घोषणा RV8803_WEEK			0x03
#घोषणा RV8803_DAY			0x04
#घोषणा RV8803_MONTH			0x05
#घोषणा RV8803_YEAR			0x06
#घोषणा RV8803_RAM			0x07
#घोषणा RV8803_ALARM_MIN		0x08
#घोषणा RV8803_ALARM_HOUR		0x09
#घोषणा RV8803_ALARM_WEEK_OR_DAY	0x0A
#घोषणा RV8803_EXT			0x0D
#घोषणा RV8803_FLAG			0x0E
#घोषणा RV8803_CTRL			0x0F

#घोषणा RV8803_EXT_WADA			BIT(6)

#घोषणा RV8803_FLAG_V1F			BIT(0)
#घोषणा RV8803_FLAG_V2F			BIT(1)
#घोषणा RV8803_FLAG_AF			BIT(3)
#घोषणा RV8803_FLAG_TF			BIT(4)
#घोषणा RV8803_FLAG_UF			BIT(5)

#घोषणा RV8803_CTRL_RESET		BIT(0)

#घोषणा RV8803_CTRL_EIE			BIT(2)
#घोषणा RV8803_CTRL_AIE			BIT(3)
#घोषणा RV8803_CTRL_TIE			BIT(4)
#घोषणा RV8803_CTRL_UIE			BIT(5)

#घोषणा RX8900_BACKUP_CTRL		0x18
#घोषणा RX8900_FLAG_SWOFF		BIT(2)
#घोषणा RX8900_FLAG_VDETOFF		BIT(3)

क्रमागत rv8803_type अणु
	rv_8803,
	rx_8900
पूर्ण;

काष्ठा rv8803_data अणु
	काष्ठा i2c_client *client;
	काष्ठा rtc_device *rtc;
	काष्ठा mutex flags_lock;
	u8 ctrl;
	क्रमागत rv8803_type type;
पूर्ण;

अटल पूर्णांक rv8803_पढ़ो_reg(स्थिर काष्ठा i2c_client *client, u8 reg)
अणु
	पूर्णांक try = RV8803_I2C_TRY_COUNT;
	s32 ret;

	/*
	 * There is a 61तगs winकरोw during which the RTC करोes not acknowledge I2C
	 * transfers. In that हाल, ensure that there are multiple attempts.
	 */
	करो
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	जबतक ((ret == -ENXIO || ret == -EIO) && --try);
	अगर (ret < 0)
		dev_err(&client->dev, "Unable to read register 0x%02x\n", reg);

	वापस ret;
पूर्ण

अटल पूर्णांक rv8803_पढ़ो_regs(स्थिर काष्ठा i2c_client *client,
			    u8 reg, u8 count, u8 *values)
अणु
	पूर्णांक try = RV8803_I2C_TRY_COUNT;
	s32 ret;

	करो
		ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg, count, values);
	जबतक ((ret == -ENXIO || ret == -EIO) && --try);
	अगर (ret != count) अणु
		dev_err(&client->dev,
			"Unable to read registers 0x%02x..0x%02x\n",
			reg, reg + count - 1);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv8803_ग_लिखो_reg(स्थिर काष्ठा i2c_client *client, u8 reg, u8 value)
अणु
	पूर्णांक try = RV8803_I2C_TRY_COUNT;
	s32 ret;

	करो
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg, value);
	जबतक ((ret == -ENXIO || ret == -EIO) && --try);
	अगर (ret)
		dev_err(&client->dev, "Unable to write register 0x%02x\n", reg);

	वापस ret;
पूर्ण

अटल पूर्णांक rv8803_ग_लिखो_regs(स्थिर काष्ठा i2c_client *client,
			     u8 reg, u8 count, स्थिर u8 *values)
अणु
	पूर्णांक try = RV8803_I2C_TRY_COUNT;
	s32 ret;

	करो
		ret = i2c_smbus_ग_लिखो_i2c_block_data(client, reg, count,
						     values);
	जबतक ((ret == -ENXIO || ret == -EIO) && --try);
	अगर (ret)
		dev_err(&client->dev,
			"Unable to write registers 0x%02x..0x%02x\n",
			reg, reg + count - 1);

	वापस ret;
पूर्ण

अटल irqवापस_t rv8803_handle_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा i2c_client *client = dev_id;
	काष्ठा rv8803_data *rv8803 = i2c_get_clientdata(client);
	अचिन्हित दीर्घ events = 0;
	पूर्णांक flags;

	mutex_lock(&rv8803->flags_lock);

	flags = rv8803_पढ़ो_reg(client, RV8803_FLAG);
	अगर (flags <= 0) अणु
		mutex_unlock(&rv8803->flags_lock);
		वापस IRQ_NONE;
	पूर्ण

	अगर (flags & RV8803_FLAG_V1F)
		dev_warn(&client->dev, "Voltage low, temperature compensation stopped.\n");

	अगर (flags & RV8803_FLAG_V2F)
		dev_warn(&client->dev, "Voltage low, data loss detected.\n");

	अगर (flags & RV8803_FLAG_TF) अणु
		flags &= ~RV8803_FLAG_TF;
		rv8803->ctrl &= ~RV8803_CTRL_TIE;
		events |= RTC_PF;
	पूर्ण

	अगर (flags & RV8803_FLAG_AF) अणु
		flags &= ~RV8803_FLAG_AF;
		rv8803->ctrl &= ~RV8803_CTRL_AIE;
		events |= RTC_AF;
	पूर्ण

	अगर (flags & RV8803_FLAG_UF) अणु
		flags &= ~RV8803_FLAG_UF;
		rv8803->ctrl &= ~RV8803_CTRL_UIE;
		events |= RTC_UF;
	पूर्ण

	अगर (events) अणु
		rtc_update_irq(rv8803->rtc, 1, events);
		rv8803_ग_लिखो_reg(client, RV8803_FLAG, flags);
		rv8803_ग_लिखो_reg(rv8803->client, RV8803_CTRL, rv8803->ctrl);
	पूर्ण

	mutex_unlock(&rv8803->flags_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rv8803_get_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv8803_data *rv8803 = dev_get_drvdata(dev);
	u8 date1[7];
	u8 date2[7];
	u8 *date = date1;
	पूर्णांक ret, flags;

	flags = rv8803_पढ़ो_reg(rv8803->client, RV8803_FLAG);
	अगर (flags < 0)
		वापस flags;

	अगर (flags & RV8803_FLAG_V2F) अणु
		dev_warn(dev, "Voltage low, data is invalid.\n");
		वापस -EINVAL;
	पूर्ण

	ret = rv8803_पढ़ो_regs(rv8803->client, RV8803_SEC, 7, date);
	अगर (ret)
		वापस ret;

	अगर ((date1[RV8803_SEC] & 0x7f) == bin2bcd(59)) अणु
		ret = rv8803_पढ़ो_regs(rv8803->client, RV8803_SEC, 7, date2);
		अगर (ret)
			वापस ret;

		अगर ((date2[RV8803_SEC] & 0x7f) != bin2bcd(59))
			date = date2;
	पूर्ण

	पंचांग->पंचांग_sec  = bcd2bin(date[RV8803_SEC] & 0x7f);
	पंचांग->पंचांग_min  = bcd2bin(date[RV8803_MIN] & 0x7f);
	पंचांग->पंचांग_hour = bcd2bin(date[RV8803_HOUR] & 0x3f);
	पंचांग->पंचांग_wday = ilog2(date[RV8803_WEEK] & 0x7f);
	पंचांग->पंचांग_mday = bcd2bin(date[RV8803_DAY] & 0x3f);
	पंचांग->पंचांग_mon  = bcd2bin(date[RV8803_MONTH] & 0x1f) - 1;
	पंचांग->पंचांग_year = bcd2bin(date[RV8803_YEAR]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक rv8803_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rv8803_data *rv8803 = dev_get_drvdata(dev);
	u8 date[7];
	पूर्णांक ctrl, flags, ret;

	ctrl = rv8803_पढ़ो_reg(rv8803->client, RV8803_CTRL);
	अगर (ctrl < 0)
		वापस ctrl;

	/* Stop the घड़ी */
	ret = rv8803_ग_लिखो_reg(rv8803->client, RV8803_CTRL,
			       ctrl | RV8803_CTRL_RESET);
	अगर (ret)
		वापस ret;

	date[RV8803_SEC]   = bin2bcd(पंचांग->पंचांग_sec);
	date[RV8803_MIN]   = bin2bcd(पंचांग->पंचांग_min);
	date[RV8803_HOUR]  = bin2bcd(पंचांग->पंचांग_hour);
	date[RV8803_WEEK]  = 1 << (पंचांग->पंचांग_wday);
	date[RV8803_DAY]   = bin2bcd(पंचांग->पंचांग_mday);
	date[RV8803_MONTH] = bin2bcd(पंचांग->पंचांग_mon + 1);
	date[RV8803_YEAR]  = bin2bcd(पंचांग->पंचांग_year - 100);

	ret = rv8803_ग_लिखो_regs(rv8803->client, RV8803_SEC, 7, date);
	अगर (ret)
		वापस ret;

	/* Restart the घड़ी */
	ret = rv8803_ग_लिखो_reg(rv8803->client, RV8803_CTRL,
			       ctrl & ~RV8803_CTRL_RESET);
	अगर (ret)
		वापस ret;

	mutex_lock(&rv8803->flags_lock);

	flags = rv8803_पढ़ो_reg(rv8803->client, RV8803_FLAG);
	अगर (flags < 0) अणु
		mutex_unlock(&rv8803->flags_lock);
		वापस flags;
	पूर्ण

	ret = rv8803_ग_लिखो_reg(rv8803->client, RV8803_FLAG,
			       flags & ~(RV8803_FLAG_V1F | RV8803_FLAG_V2F));

	mutex_unlock(&rv8803->flags_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rv8803_get_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा rv8803_data *rv8803 = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = rv8803->client;
	u8 alarmvals[3];
	पूर्णांक flags, ret;

	ret = rv8803_पढ़ो_regs(client, RV8803_ALARM_MIN, 3, alarmvals);
	अगर (ret)
		वापस ret;

	flags = rv8803_पढ़ो_reg(client, RV8803_FLAG);
	अगर (flags < 0)
		वापस flags;

	alrm->समय.पंचांग_sec  = 0;
	alrm->समय.पंचांग_min  = bcd2bin(alarmvals[0] & 0x7f);
	alrm->समय.पंचांग_hour = bcd2bin(alarmvals[1] & 0x3f);
	alrm->समय.पंचांग_mday = bcd2bin(alarmvals[2] & 0x3f);

	alrm->enabled = !!(rv8803->ctrl & RV8803_CTRL_AIE);
	alrm->pending = (flags & RV8803_FLAG_AF) && alrm->enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक rv8803_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rv8803_data *rv8803 = dev_get_drvdata(dev);
	u8 alarmvals[3];
	u8 ctrl[2];
	पूर्णांक ret, err;

	/* The alarm has no seconds, round up to nearest minute */
	अगर (alrm->समय.पंचांग_sec) अणु
		समय64_t alarm_समय = rtc_पंचांग_to_समय64(&alrm->समय);

		alarm_समय += 60 - alrm->समय.पंचांग_sec;
		rtc_समय64_to_पंचांग(alarm_समय, &alrm->समय);
	पूर्ण

	mutex_lock(&rv8803->flags_lock);

	ret = rv8803_पढ़ो_regs(client, RV8803_FLAG, 2, ctrl);
	अगर (ret) अणु
		mutex_unlock(&rv8803->flags_lock);
		वापस ret;
	पूर्ण

	alarmvals[0] = bin2bcd(alrm->समय.पंचांग_min);
	alarmvals[1] = bin2bcd(alrm->समय.पंचांग_hour);
	alarmvals[2] = bin2bcd(alrm->समय.पंचांग_mday);

	अगर (rv8803->ctrl & (RV8803_CTRL_AIE | RV8803_CTRL_UIE)) अणु
		rv8803->ctrl &= ~(RV8803_CTRL_AIE | RV8803_CTRL_UIE);
		err = rv8803_ग_लिखो_reg(rv8803->client, RV8803_CTRL,
				       rv8803->ctrl);
		अगर (err) अणु
			mutex_unlock(&rv8803->flags_lock);
			वापस err;
		पूर्ण
	पूर्ण

	ctrl[1] &= ~RV8803_FLAG_AF;
	err = rv8803_ग_लिखो_reg(rv8803->client, RV8803_FLAG, ctrl[1]);
	mutex_unlock(&rv8803->flags_lock);
	अगर (err)
		वापस err;

	err = rv8803_ग_लिखो_regs(rv8803->client, RV8803_ALARM_MIN, 3, alarmvals);
	अगर (err)
		वापस err;

	अगर (alrm->enabled) अणु
		अगर (rv8803->rtc->uie_rtस_समयr.enabled)
			rv8803->ctrl |= RV8803_CTRL_UIE;
		अगर (rv8803->rtc->aie_समयr.enabled)
			rv8803->ctrl |= RV8803_CTRL_AIE;

		err = rv8803_ग_लिखो_reg(rv8803->client, RV8803_CTRL,
				       rv8803->ctrl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv8803_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rv8803_data *rv8803 = dev_get_drvdata(dev);
	पूर्णांक ctrl, flags, err;

	ctrl = rv8803->ctrl;

	अगर (enabled) अणु
		अगर (rv8803->rtc->uie_rtस_समयr.enabled)
			ctrl |= RV8803_CTRL_UIE;
		अगर (rv8803->rtc->aie_समयr.enabled)
			ctrl |= RV8803_CTRL_AIE;
	पूर्ण अन्यथा अणु
		अगर (!rv8803->rtc->uie_rtस_समयr.enabled)
			ctrl &= ~RV8803_CTRL_UIE;
		अगर (!rv8803->rtc->aie_समयr.enabled)
			ctrl &= ~RV8803_CTRL_AIE;
	पूर्ण

	mutex_lock(&rv8803->flags_lock);
	flags = rv8803_पढ़ो_reg(client, RV8803_FLAG);
	अगर (flags < 0) अणु
		mutex_unlock(&rv8803->flags_lock);
		वापस flags;
	पूर्ण
	flags &= ~(RV8803_FLAG_AF | RV8803_FLAG_UF);
	err = rv8803_ग_लिखो_reg(client, RV8803_FLAG, flags);
	mutex_unlock(&rv8803->flags_lock);
	अगर (err)
		वापस err;

	अगर (ctrl != rv8803->ctrl) अणु
		rv8803->ctrl = ctrl;
		err = rv8803_ग_लिखो_reg(client, RV8803_CTRL, rv8803->ctrl);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rv8803_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rv8803_data *rv8803 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक vl = 0;
	पूर्णांक flags, ret = 0;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		flags = rv8803_पढ़ो_reg(client, RV8803_FLAG);
		अगर (flags < 0)
			वापस flags;

		अगर (flags & RV8803_FLAG_V1F) अणु
			dev_warn(&client->dev, "Voltage low, temperature compensation stopped.\n");
			vl = RTC_VL_ACCURACY_LOW;
		पूर्ण

		अगर (flags & RV8803_FLAG_V2F)
			vl |= RTC_VL_DATA_INVALID;

		वापस put_user(vl, (अचिन्हित पूर्णांक __user *)arg);

	हाल RTC_VL_CLR:
		mutex_lock(&rv8803->flags_lock);
		flags = rv8803_पढ़ो_reg(client, RV8803_FLAG);
		अगर (flags < 0) अणु
			mutex_unlock(&rv8803->flags_lock);
			वापस flags;
		पूर्ण

		flags &= ~RV8803_FLAG_V1F;
		ret = rv8803_ग_लिखो_reg(client, RV8803_FLAG, flags);
		mutex_unlock(&rv8803->flags_lock);
		अगर (ret)
			वापस ret;

		वापस 0;

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक rv8803_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset, व्योम *val,
			      माप_प्रकार bytes)
अणु
	वापस rv8803_ग_लिखो_reg(priv, RV8803_RAM, *(u8 *)val);
पूर्ण

अटल पूर्णांक rv8803_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset,
			     व्योम *val, माप_प्रकार bytes)
अणु
	पूर्णांक ret;

	ret = rv8803_पढ़ो_reg(priv, RV8803_RAM);
	अगर (ret < 0)
		वापस ret;

	*(u8 *)val = ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rv8803_rtc_ops = अणु
	.पढ़ो_समय = rv8803_get_समय,
	.set_समय = rv8803_set_समय,
	.ioctl = rv8803_ioctl,
	.पढ़ो_alarm = rv8803_get_alarm,
	.set_alarm = rv8803_set_alarm,
	.alarm_irq_enable = rv8803_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक rx8900_trickle_अक्षरger_init(काष्ठा rv8803_data *rv8803)
अणु
	काष्ठा i2c_client *client = rv8803->client;
	काष्ठा device_node *node = client->dev.of_node;
	पूर्णांक err;
	u8 flags;

	अगर (!node)
		वापस 0;

	अगर (rv8803->type != rx_8900)
		वापस 0;

	err = i2c_smbus_पढ़ो_byte_data(rv8803->client, RX8900_BACKUP_CTRL);
	अगर (err < 0)
		वापस err;

	flags = ~(RX8900_FLAG_VDETOFF | RX8900_FLAG_SWOFF) & (u8)err;

	अगर (of_property_पढ़ो_bool(node, "epson,vdet-disable"))
		flags |= RX8900_FLAG_VDETOFF;

	अगर (of_property_पढ़ो_bool(node, "trickle-diode-disable"))
		flags |= RX8900_FLAG_SWOFF;

	वापस i2c_smbus_ग_लिखो_byte_data(rv8803->client, RX8900_BACKUP_CTRL,
					 flags);
पूर्ण

अटल पूर्णांक rv8803_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा rv8803_data *rv8803;
	पूर्णांक err, flags;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "rv8803_nvram",
		.word_size = 1,
		.stride = 1,
		.size = 1,
		.reg_पढ़ो = rv8803_nvram_पढ़ो,
		.reg_ग_लिखो = rv8803_nvram_ग_लिखो,
		.priv = client,
	पूर्ण;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_I2C_BLOCK)) अणु
		dev_err(&adapter->dev, "doesn't support I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_I2C_BLOCK\n");
		वापस -EIO;
	पूर्ण

	rv8803 = devm_kzalloc(&client->dev, माप(काष्ठा rv8803_data),
			      GFP_KERNEL);
	अगर (!rv8803)
		वापस -ENOMEM;

	mutex_init(&rv8803->flags_lock);
	rv8803->client = client;
	अगर (client->dev.of_node)
		rv8803->type = (क्रमागत rv8803_type)
			of_device_get_match_data(&client->dev);
	अन्यथा
		rv8803->type = id->driver_data;
	i2c_set_clientdata(client, rv8803);

	flags = rv8803_पढ़ो_reg(client, RV8803_FLAG);
	अगर (flags < 0)
		वापस flags;

	अगर (flags & RV8803_FLAG_V1F)
		dev_warn(&client->dev, "Voltage low, temperature compensation stopped.\n");

	अगर (flags & RV8803_FLAG_V2F)
		dev_warn(&client->dev, "Voltage low, data loss detected.\n");

	अगर (flags & RV8803_FLAG_AF)
		dev_warn(&client->dev, "An alarm maybe have been missed.\n");

	rv8803->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(rv8803->rtc))
		वापस PTR_ERR(rv8803->rtc);

	अगर (client->irq > 0) अणु
		err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, rv8803_handle_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"rv8803", client);
		अगर (err) अणु
			dev_warn(&client->dev, "unable to request IRQ, alarms disabled\n");
			client->irq = 0;
		पूर्ण
	पूर्ण
	अगर (!client->irq)
		clear_bit(RTC_FEATURE_ALARM, rv8803->rtc->features);

	err = rv8803_ग_लिखो_reg(rv8803->client, RV8803_EXT, RV8803_EXT_WADA);
	अगर (err)
		वापस err;

	err = rx8900_trickle_अक्षरger_init(rv8803);
	अगर (err) अणु
		dev_err(&client->dev, "failed to init charger\n");
		वापस err;
	पूर्ण

	rv8803->rtc->ops = &rv8803_rtc_ops;
	rv8803->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rv8803->rtc->range_max = RTC_TIMESTAMP_END_2099;
	err = devm_rtc_रेजिस्टर_device(rv8803->rtc);
	अगर (err)
		वापस err;

	devm_rtc_nvmem_रेजिस्टर(rv8803->rtc, &nvmem_cfg);

	rv8803->rtc->max_user_freq = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id rv8803_id[] = अणु
	अणु "rv8803", rv_8803 पूर्ण,
	अणु "rx8803", rv_8803 पूर्ण,
	अणु "rx8900", rx_8900 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, rv8803_id);

अटल स्थिर __maybe_unused काष्ठा of_device_id rv8803_of_match[] = अणु
	अणु
		.compatible = "microcrystal,rv8803",
		.data = (व्योम *)rv_8803
	पूर्ण,
	अणु
		.compatible = "epson,rx8803",
		.data = (व्योम *)rv_8803
	पूर्ण,
	अणु
		.compatible = "epson,rx8900",
		.data = (व्योम *)rx_8900
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rv8803_of_match);

अटल काष्ठा i2c_driver rv8803_driver = अणु
	.driver = अणु
		.name = "rtc-rv8803",
		.of_match_table = of_match_ptr(rv8803_of_match),
	पूर्ण,
	.probe		= rv8803_probe,
	.id_table	= rv8803_id,
पूर्ण;
module_i2c_driver(rv8803_driver);

MODULE_AUTHOR("Alexandre Belloni <alexandre.belloni@bootlin.com>");
MODULE_DESCRIPTION("Micro Crystal RV8803 RTC driver");
MODULE_LICENSE("GPL v2");
