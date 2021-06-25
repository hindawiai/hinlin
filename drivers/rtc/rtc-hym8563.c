<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Haoyu HYM8563 RTC driver
 *
 * Copyright (C) 2013 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * based on rtc-HYM8563
 * Copyright (C) 2010 ROCKCHIP, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>

#घोषणा HYM8563_CTL1		0x00
#घोषणा HYM8563_CTL1_TEST	BIT(7)
#घोषणा HYM8563_CTL1_STOP	BIT(5)
#घोषणा HYM8563_CTL1_TESTC	BIT(3)

#घोषणा HYM8563_CTL2		0x01
#घोषणा HYM8563_CTL2_TI_TP	BIT(4)
#घोषणा HYM8563_CTL2_AF		BIT(3)
#घोषणा HYM8563_CTL2_TF		BIT(2)
#घोषणा HYM8563_CTL2_AIE	BIT(1)
#घोषणा HYM8563_CTL2_TIE	BIT(0)

#घोषणा HYM8563_SEC		0x02
#घोषणा HYM8563_SEC_VL		BIT(7)
#घोषणा HYM8563_SEC_MASK	0x7f

#घोषणा HYM8563_MIN		0x03
#घोषणा HYM8563_MIN_MASK	0x7f

#घोषणा HYM8563_HOUR		0x04
#घोषणा HYM8563_HOUR_MASK	0x3f

#घोषणा HYM8563_DAY		0x05
#घोषणा HYM8563_DAY_MASK	0x3f

#घोषणा HYM8563_WEEKDAY		0x06
#घोषणा HYM8563_WEEKDAY_MASK	0x07

#घोषणा HYM8563_MONTH		0x07
#घोषणा HYM8563_MONTH_CENTURY	BIT(7)
#घोषणा HYM8563_MONTH_MASK	0x1f

#घोषणा HYM8563_YEAR		0x08

#घोषणा HYM8563_ALM_MIN		0x09
#घोषणा HYM8563_ALM_HOUR	0x0a
#घोषणा HYM8563_ALM_DAY		0x0b
#घोषणा HYM8563_ALM_WEEK	0x0c

/* Each alarm check can be disabled by setting this bit in the रेजिस्टर */
#घोषणा HYM8563_ALM_BIT_DISABLE	BIT(7)

#घोषणा HYM8563_CLKOUT		0x0d
#घोषणा HYM8563_CLKOUT_ENABLE	BIT(7)
#घोषणा HYM8563_CLKOUT_32768	0
#घोषणा HYM8563_CLKOUT_1024	1
#घोषणा HYM8563_CLKOUT_32	2
#घोषणा HYM8563_CLKOUT_1	3
#घोषणा HYM8563_CLKOUT_MASK	3

#घोषणा HYM8563_TMR_CTL		0x0e
#घोषणा HYM8563_TMR_CTL_ENABLE	BIT(7)
#घोषणा HYM8563_TMR_CTL_4096	0
#घोषणा HYM8563_TMR_CTL_64	1
#घोषणा HYM8563_TMR_CTL_1	2
#घोषणा HYM8563_TMR_CTL_1_60	3
#घोषणा HYM8563_TMR_CTL_MASK	3

#घोषणा HYM8563_TMR_CNT		0x0f

काष्ठा hym8563 अणु
	काष्ठा i2c_client	*client;
	काष्ठा rtc_device	*rtc;
#अगर_घोषित CONFIG_COMMON_CLK
	काष्ठा clk_hw		clkout_hw;
#पूर्ण_अगर
पूर्ण;

/*
 * RTC handling
 */

अटल पूर्णांक hym8563_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 buf[7];
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, HYM8563_SEC, 7, buf);
	अगर (ret < 0)
		वापस ret;

	अगर (buf[0] & HYM8563_SEC_VL) अणु
		dev_warn(&client->dev,
			 "no valid clock/calendar values available\n");
		वापस -EINVAL;
	पूर्ण

	पंचांग->पंचांग_sec = bcd2bin(buf[0] & HYM8563_SEC_MASK);
	पंचांग->पंचांग_min = bcd2bin(buf[1] & HYM8563_MIN_MASK);
	पंचांग->पंचांग_hour = bcd2bin(buf[2] & HYM8563_HOUR_MASK);
	पंचांग->पंचांग_mday = bcd2bin(buf[3] & HYM8563_DAY_MASK);
	पंचांग->पंचांग_wday = bcd2bin(buf[4] & HYM8563_WEEKDAY_MASK); /* 0 = Sun */
	पंचांग->पंचांग_mon = bcd2bin(buf[5] & HYM8563_MONTH_MASK) - 1; /* 0 = Jan */
	पंचांग->पंचांग_year = bcd2bin(buf[6]) + 100;

	वापस 0;
पूर्ण

अटल पूर्णांक hym8563_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	u8 buf[7];
	पूर्णांक ret;

	/* Years >= 2100 are to far in the future, 19XX is to early */
	अगर (पंचांग->पंचांग_year < 100 || पंचांग->पंचांग_year >= 200)
		वापस -EINVAL;

	buf[0] = bin2bcd(पंचांग->पंचांग_sec);
	buf[1] = bin2bcd(पंचांग->पंचांग_min);
	buf[2] = bin2bcd(पंचांग->पंचांग_hour);
	buf[3] = bin2bcd(पंचांग->पंचांग_mday);
	buf[4] = bin2bcd(पंचांग->पंचांग_wday);
	buf[5] = bin2bcd(पंचांग->पंचांग_mon + 1);

	/*
	 * While the HYM8563 has a century flag in the month रेजिस्टर,
	 * it करोes not seem to carry it over a subsequent ग_लिखो/पढ़ो.
	 * So we'll limit ourself to 100 years, starting at 2000 क्रम now.
	 */
	buf[6] = bin2bcd(पंचांग->पंचांग_year - 100);

	/*
	 * CTL1 only contains TEST-mode bits apart from stop,
	 * so no need to पढ़ो the value first
	 */
	ret = i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CTL1,
						HYM8563_CTL1_STOP);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(client, HYM8563_SEC, 7, buf);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CTL1, 0);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक hym8563_rtc_alarm_irq_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक data;

	data = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CTL2);
	अगर (data < 0)
		वापस data;

	अगर (enabled)
		data |= HYM8563_CTL2_AIE;
	अन्यथा
		data &= ~HYM8563_CTL2_AIE;

	वापस i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CTL2, data);
पूर्ण;

अटल पूर्णांक hym8563_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rtc_समय *alm_पंचांग = &alm->समय;
	u8 buf[4];
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, HYM8563_ALM_MIN, 4, buf);
	अगर (ret < 0)
		वापस ret;

	/* The alarm only has a minute accuracy */
	alm_पंचांग->पंचांग_sec = 0;

	alm_पंचांग->पंचांग_min = (buf[0] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[0] & HYM8563_MIN_MASK);
	alm_पंचांग->पंचांग_hour = (buf[1] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[1] & HYM8563_HOUR_MASK);
	alm_पंचांग->पंचांग_mday = (buf[2] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[2] & HYM8563_DAY_MASK);
	alm_पंचांग->पंचांग_wday = (buf[3] & HYM8563_ALM_BIT_DISABLE) ?
					-1 :
					bcd2bin(buf[3] & HYM8563_WEEKDAY_MASK);

	ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CTL2);
	अगर (ret < 0)
		वापस ret;

	अगर (ret & HYM8563_CTL2_AIE)
		alm->enabled = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक hym8563_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alm)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा rtc_समय *alm_पंचांग = &alm->समय;
	u8 buf[4];
	पूर्णांक ret;

	/*
	 * The alarm has no seconds so deal with it
	 */
	अगर (alm_पंचांग->पंचांग_sec) अणु
		alm_पंचांग->पंचांग_sec = 0;
		alm_पंचांग->पंचांग_min++;
		अगर (alm_पंचांग->पंचांग_min >= 60) अणु
			alm_पंचांग->पंचांग_min = 0;
			alm_पंचांग->पंचांग_hour++;
			अगर (alm_पंचांग->पंचांग_hour >= 24) अणु
				alm_पंचांग->पंचांग_hour = 0;
				alm_पंचांग->पंचांग_mday++;
				अगर (alm_पंचांग->पंचांग_mday > 31)
					alm_पंचांग->पंचांग_mday = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CTL2);
	अगर (ret < 0)
		वापस ret;

	ret &= ~HYM8563_CTL2_AIE;

	ret = i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CTL2, ret);
	अगर (ret < 0)
		वापस ret;

	buf[0] = (alm_पंचांग->पंचांग_min < 60 && alm_पंचांग->पंचांग_min >= 0) ?
			bin2bcd(alm_पंचांग->पंचांग_min) : HYM8563_ALM_BIT_DISABLE;

	buf[1] = (alm_पंचांग->पंचांग_hour < 24 && alm_पंचांग->पंचांग_hour >= 0) ?
			bin2bcd(alm_पंचांग->पंचांग_hour) : HYM8563_ALM_BIT_DISABLE;

	buf[2] = (alm_पंचांग->पंचांग_mday <= 31 && alm_पंचांग->पंचांग_mday >= 1) ?
			bin2bcd(alm_पंचांग->पंचांग_mday) : HYM8563_ALM_BIT_DISABLE;

	buf[3] = (alm_पंचांग->पंचांग_wday < 7 && alm_पंचांग->पंचांग_wday >= 0) ?
			bin2bcd(alm_पंचांग->पंचांग_wday) : HYM8563_ALM_BIT_DISABLE;

	ret = i2c_smbus_ग_लिखो_i2c_block_data(client, HYM8563_ALM_MIN, 4, buf);
	अगर (ret < 0)
		वापस ret;

	वापस hym8563_rtc_alarm_irq_enable(dev, alm->enabled);
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops hym8563_rtc_ops = अणु
	.पढ़ो_समय		= hym8563_rtc_पढ़ो_समय,
	.set_समय		= hym8563_rtc_set_समय,
	.alarm_irq_enable	= hym8563_rtc_alarm_irq_enable,
	.पढ़ो_alarm		= hym8563_rtc_पढ़ो_alarm,
	.set_alarm		= hym8563_rtc_set_alarm,
पूर्ण;

/*
 * Handling of the clkout
 */

#अगर_घोषित CONFIG_COMMON_CLK
#घोषणा clkout_hw_to_hym8563(_hw) container_of(_hw, काष्ठा hym8563, clkout_hw)

अटल पूर्णांक clkout_rates[] = अणु
	32768,
	1024,
	32,
	1,
पूर्ण;

अटल अचिन्हित दीर्घ hym8563_clkout_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hym8563 *hym8563 = clkout_hw_to_hym8563(hw);
	काष्ठा i2c_client *client = hym8563->client;
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CLKOUT);

	अगर (ret < 0)
		वापस 0;

	ret &= HYM8563_CLKOUT_MASK;
	वापस clkout_rates[ret];
पूर्ण

अटल दीर्घ hym8563_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(clkout_rates); i++)
		अगर (clkout_rates[i] <= rate)
			वापस clkout_rates[i];

	वापस 0;
पूर्ण

अटल पूर्णांक hym8563_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा hym8563 *hym8563 = clkout_hw_to_hym8563(hw);
	काष्ठा i2c_client *client = hym8563->client;
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CLKOUT);
	पूर्णांक i;

	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(clkout_rates); i++)
		अगर (clkout_rates[i] == rate) अणु
			ret &= ~HYM8563_CLKOUT_MASK;
			ret |= i;
			वापस i2c_smbus_ग_लिखो_byte_data(client,
							 HYM8563_CLKOUT, ret);
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hym8563_clkout_control(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा hym8563 *hym8563 = clkout_hw_to_hym8563(hw);
	काष्ठा i2c_client *client = hym8563->client;
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CLKOUT);

	अगर (ret < 0)
		वापस ret;

	अगर (enable)
		ret |= HYM8563_CLKOUT_ENABLE;
	अन्यथा
		ret &= ~HYM8563_CLKOUT_ENABLE;

	वापस i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CLKOUT, ret);
पूर्ण

अटल पूर्णांक hym8563_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	वापस hym8563_clkout_control(hw, 1);
पूर्ण

अटल व्योम hym8563_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	hym8563_clkout_control(hw, 0);
पूर्ण

अटल पूर्णांक hym8563_clkout_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा hym8563 *hym8563 = clkout_hw_to_hym8563(hw);
	काष्ठा i2c_client *client = hym8563->client;
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CLKOUT);

	अगर (ret < 0)
		वापस ret;

	वापस !!(ret & HYM8563_CLKOUT_ENABLE);
पूर्ण

अटल स्थिर काष्ठा clk_ops hym8563_clkout_ops = अणु
	.prepare = hym8563_clkout_prepare,
	.unprepare = hym8563_clkout_unprepare,
	.is_prepared = hym8563_clkout_is_prepared,
	.recalc_rate = hym8563_clkout_recalc_rate,
	.round_rate = hym8563_clkout_round_rate,
	.set_rate = hym8563_clkout_set_rate,
पूर्ण;

अटल काष्ठा clk *hym8563_clkout_रेजिस्टर_clk(काष्ठा hym8563 *hym8563)
अणु
	काष्ठा i2c_client *client = hym8563->client;
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CLKOUT,
						0);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	init.name = "hym8563-clkout";
	init.ops = &hym8563_clkout_ops;
	init.flags = 0;
	init.parent_names = शून्य;
	init.num_parents = 0;
	hym8563->clkout_hw.init = &init;

	/* optional override of the घड़ीname */
	of_property_पढ़ो_string(node, "clock-output-names", &init.name);

	/* रेजिस्टर the घड़ी */
	clk = clk_रेजिस्टर(&client->dev, &hym8563->clkout_hw);

	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस clk;
पूर्ण
#पूर्ण_अगर

/*
 * The alarm पूर्णांकerrupt is implemented as a level-low पूर्णांकerrupt in the
 * hym8563, जबतक the समयr पूर्णांकerrupt uses a falling edge.
 * We करोn't use the समयr at all, so the पूर्णांकerrupt is requested to
 * use the level-low trigger.
 */
अटल irqवापस_t hym8563_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा hym8563 *hym8563 = (काष्ठा hym8563 *)dev_id;
	काष्ठा i2c_client *client = hym8563->client;
	पूर्णांक data, ret;

	rtc_lock(hym8563->rtc);

	/* Clear the alarm flag */

	data = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CTL2);
	अगर (data < 0) अणु
		dev_err(&client->dev, "%s: error reading i2c data %d\n",
			__func__, data);
		जाओ out;
	पूर्ण

	data &= ~HYM8563_CTL2_AF;

	ret = i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CTL2, data);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "%s: error writing i2c data %d\n",
			__func__, ret);
	पूर्ण

out:
	rtc_unlock(hym8563->rtc);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक hym8563_init_device(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	/* Clear stop flag अगर present */
	ret = i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CTL1, 0);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_CTL2);
	अगर (ret < 0)
		वापस ret;

	/* Disable alarm and समयr पूर्णांकerrupts */
	ret &= ~HYM8563_CTL2_AIE;
	ret &= ~HYM8563_CTL2_TIE;

	/* Clear any pending alarm and समयr flags */
	अगर (ret & HYM8563_CTL2_AF)
		ret &= ~HYM8563_CTL2_AF;

	अगर (ret & HYM8563_CTL2_TF)
		ret &= ~HYM8563_CTL2_TF;

	ret &= ~HYM8563_CTL2_TI_TP;

	वापस i2c_smbus_ग_लिखो_byte_data(client, HYM8563_CTL2, ret);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक hym8563_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	अगर (device_may_wakeup(dev)) अणु
		ret = enable_irq_wake(client->irq);
		अगर (ret) अणु
			dev_err(dev, "enable_irq_wake failed, %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hym8563_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	अगर (device_may_wakeup(dev))
		disable_irq_wake(client->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(hym8563_pm_ops, hym8563_suspend, hym8563_resume);

अटल पूर्णांक hym8563_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा hym8563 *hym8563;
	पूर्णांक ret;

	hym8563 = devm_kzalloc(&client->dev, माप(*hym8563), GFP_KERNEL);
	अगर (!hym8563)
		वापस -ENOMEM;

	hym8563->client = client;
	i2c_set_clientdata(client, hym8563);

	ret = hym8563_init_device(client);
	अगर (ret) अणु
		dev_err(&client->dev, "could not init device, %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, hym8563_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						client->name, hym8563);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "irq %d request failed, %d\n",
				client->irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (client->irq > 0 ||
	    device_property_पढ़ो_bool(&client->dev, "wakeup-source")) अणु
		device_init_wakeup(&client->dev, true);
	पूर्ण

	/* check state of calendar inक्रमmation */
	ret = i2c_smbus_पढ़ो_byte_data(client, HYM8563_SEC);
	अगर (ret < 0)
		वापस ret;

	dev_dbg(&client->dev, "rtc information is %s\n",
		(ret & HYM8563_SEC_VL) ? "invalid" : "valid");

	hym8563->rtc = devm_rtc_device_रेजिस्टर(&client->dev, client->name,
						&hym8563_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(hym8563->rtc))
		वापस PTR_ERR(hym8563->rtc);

	/* the hym8563 alarm only supports a minute accuracy */
	hym8563->rtc->uie_unsupported = 1;

#अगर_घोषित CONFIG_COMMON_CLK
	hym8563_clkout_रेजिस्टर_clk(hym8563);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hym8563_id[] = अणु
	अणु "hym8563", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, hym8563_id);

अटल स्थिर काष्ठा of_device_id hym8563_dt_idtable[] = अणु
	अणु .compatible = "haoyu,hym8563" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, hym8563_dt_idtable);

अटल काष्ठा i2c_driver hym8563_driver = अणु
	.driver		= अणु
		.name	= "rtc-hym8563",
		.pm	= &hym8563_pm_ops,
		.of_match_table	= hym8563_dt_idtable,
	पूर्ण,
	.probe		= hym8563_probe,
	.id_table	= hym8563_id,
पूर्ण;

module_i2c_driver(hym8563_driver);

MODULE_AUTHOR("Heiko Stuebner <heiko@sntech.de>");
MODULE_DESCRIPTION("HYM8563 RTC driver");
MODULE_LICENSE("GPL");
