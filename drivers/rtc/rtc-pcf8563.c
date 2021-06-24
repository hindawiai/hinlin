<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An I2C driver क्रम the Philips PCF8563 RTC
 * Copyright 2005-06 Tower Technologies
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 * Maपूर्णांकainers: http://www.nslu2-linux.org/
 *
 * based on the other drivers in this same directory.
 *
 * http://www.semiconductors.philips.com/acrobat/datasheets/PCF8563-04.pdf
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/i2c.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/err.h>

#घोषणा PCF8563_REG_ST1		0x00 /* status */
#घोषणा PCF8563_REG_ST2		0x01
#घोषणा PCF8563_BIT_AIE		BIT(1)
#घोषणा PCF8563_BIT_AF		BIT(3)
#घोषणा PCF8563_BITS_ST2_N	(7 << 5)

#घोषणा PCF8563_REG_SC		0x02 /* dateसमय */
#घोषणा PCF8563_REG_MN		0x03
#घोषणा PCF8563_REG_HR		0x04
#घोषणा PCF8563_REG_DM		0x05
#घोषणा PCF8563_REG_DW		0x06
#घोषणा PCF8563_REG_MO		0x07
#घोषणा PCF8563_REG_YR		0x08

#घोषणा PCF8563_REG_AMN		0x09 /* alarm */

#घोषणा PCF8563_REG_CLKO		0x0D /* घड़ी out */
#घोषणा PCF8563_REG_CLKO_FE		0x80 /* घड़ी out enabled */
#घोषणा PCF8563_REG_CLKO_F_MASK		0x03 /* frequenc mask */
#घोषणा PCF8563_REG_CLKO_F_32768HZ	0x00
#घोषणा PCF8563_REG_CLKO_F_1024HZ	0x01
#घोषणा PCF8563_REG_CLKO_F_32HZ		0x02
#घोषणा PCF8563_REG_CLKO_F_1HZ		0x03

#घोषणा PCF8563_REG_TMRC	0x0E /* समयr control */
#घोषणा PCF8563_TMRC_ENABLE	BIT(7)
#घोषणा PCF8563_TMRC_4096	0
#घोषणा PCF8563_TMRC_64		1
#घोषणा PCF8563_TMRC_1		2
#घोषणा PCF8563_TMRC_1_60	3
#घोषणा PCF8563_TMRC_MASK	3

#घोषणा PCF8563_REG_TMR		0x0F /* समयr */

#घोषणा PCF8563_SC_LV		0x80 /* low voltage */
#घोषणा PCF8563_MO_C		0x80 /* century */

अटल काष्ठा i2c_driver pcf8563_driver;

काष्ठा pcf8563 अणु
	काष्ठा rtc_device *rtc;
	/*
	 * The meaning of MO_C bit varies by the chip type.
	 * From PCF8563 datasheet: this bit is toggled when the years
	 * रेजिस्टर overflows from 99 to 00
	 *   0 indicates the century is 20xx
	 *   1 indicates the century is 19xx
	 * From RTC8564 datasheet: this bit indicates change of
	 * century. When the year digit data overflows from 99 to 00,
	 * this bit is set. By presetting it to 0 जबतक still in the
	 * 20th century, it will be set in year 2000, ...
	 * There seems no reliable way to know how the प्रणाली use this
	 * bit.  So let's करो it heuristically, assuming we are live in
	 * 1970...2069.
	 */
	पूर्णांक c_polarity;	/* 0: MO_C=1 means 19xx, otherwise MO_C=1 means 20xx */

	काष्ठा i2c_client *client;
#अगर_घोषित CONFIG_COMMON_CLK
	काष्ठा clk_hw		clkout_hw;
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक pcf8563_पढ़ो_block_data(काष्ठा i2c_client *client, अचिन्हित अक्षर reg,
				   अचिन्हित अक्षर length, अचिन्हित अक्षर *buf)
अणु
	काष्ठा i2c_msg msgs[] = अणु
		अणु/* setup पढ़ो ptr */
			.addr = client->addr,
			.len = 1,
			.buf = &reg,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = length,
			.buf = buf
		पूर्ण,
	पूर्ण;

	अगर ((i2c_transfer(client->adapter, msgs, 2)) != 2) अणु
		dev_err(&client->dev, "%s: read error\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8563_ग_लिखो_block_data(काष्ठा i2c_client *client,
				   अचिन्हित अक्षर reg, अचिन्हित अक्षर length,
				   अचिन्हित अक्षर *buf)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < length; i++) अणु
		अचिन्हित अक्षर data[2] = अणु reg + i, buf[i] पूर्ण;

		err = i2c_master_send(client, data, माप(data));
		अगर (err != माप(data)) अणु
			dev_err(&client->dev,
				"%s: err=%d addr=%02x, data=%02x\n",
				__func__, err, data[0], data[1]);
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8563_set_alarm_mode(काष्ठा i2c_client *client, bool on)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक err;

	err = pcf8563_पढ़ो_block_data(client, PCF8563_REG_ST2, 1, &buf);
	अगर (err < 0)
		वापस err;

	अगर (on)
		buf |= PCF8563_BIT_AIE;
	अन्यथा
		buf &= ~PCF8563_BIT_AIE;

	buf &= ~(PCF8563_BIT_AF | PCF8563_BITS_ST2_N);

	err = pcf8563_ग_लिखो_block_data(client, PCF8563_REG_ST2, 1, &buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "%s: write error\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8563_get_alarm_mode(काष्ठा i2c_client *client, अचिन्हित अक्षर *en,
				  अचिन्हित अक्षर *pen)
अणु
	अचिन्हित अक्षर buf;
	पूर्णांक err;

	err = pcf8563_पढ़ो_block_data(client, PCF8563_REG_ST2, 1, &buf);
	अगर (err)
		वापस err;

	अगर (en)
		*en = !!(buf & PCF8563_BIT_AIE);
	अगर (pen)
		*pen = !!(buf & PCF8563_BIT_AF);

	वापस 0;
पूर्ण

अटल irqवापस_t pcf8563_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pcf8563 *pcf8563 = i2c_get_clientdata(dev_id);
	पूर्णांक err;
	अक्षर pending;

	err = pcf8563_get_alarm_mode(pcf8563->client, शून्य, &pending);
	अगर (err)
		वापस IRQ_NONE;

	अगर (pending) अणु
		rtc_update_irq(pcf8563->rtc, 1, RTC_IRQF | RTC_AF);
		pcf8563_set_alarm_mode(pcf8563->client, 1);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/*
 * In the routines that deal directly with the pcf8563 hardware, we use
 * rtc_समय -- month 0-11, hour 0-23, yr = calendar year-epoch.
 */
अटल पूर्णांक pcf8563_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pcf8563 *pcf8563 = i2c_get_clientdata(client);
	अचिन्हित अक्षर buf[9];
	पूर्णांक err;

	err = pcf8563_पढ़ो_block_data(client, PCF8563_REG_ST1, 9, buf);
	अगर (err)
		वापस err;

	अगर (buf[PCF8563_REG_SC] & PCF8563_SC_LV) अणु
		dev_err(&client->dev,
			"low voltage detected, date/time is not reliable.\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&client->dev,
		"%s: raw data is st1=%02x, st2=%02x, sec=%02x, min=%02x, hr=%02x, "
		"mday=%02x, wday=%02x, mon=%02x, year=%02x\n",
		__func__,
		buf[0], buf[1], buf[2], buf[3],
		buf[4], buf[5], buf[6], buf[7],
		buf[8]);


	पंचांग->पंचांग_sec = bcd2bin(buf[PCF8563_REG_SC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(buf[PCF8563_REG_MN] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(buf[PCF8563_REG_HR] & 0x3F); /* rtc hr 0-23 */
	पंचांग->पंचांग_mday = bcd2bin(buf[PCF8563_REG_DM] & 0x3F);
	पंचांग->पंचांग_wday = buf[PCF8563_REG_DW] & 0x07;
	पंचांग->पंचांग_mon = bcd2bin(buf[PCF8563_REG_MO] & 0x1F) - 1; /* rtc mn 1-12 */
	पंचांग->पंचांग_year = bcd2bin(buf[PCF8563_REG_YR]) + 100;
	/* detect the polarity heuristically. see note above. */
	pcf8563->c_polarity = (buf[PCF8563_REG_MO] & PCF8563_MO_C) ?
		(पंचांग->पंचांग_year >= 100) : (पंचांग->पंचांग_year < 100);

	dev_dbg(&client->dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8563_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा pcf8563 *pcf8563 = i2c_get_clientdata(client);
	अचिन्हित अक्षर buf[9];

	dev_dbg(&client->dev, "%s: secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	/* hours, minutes and seconds */
	buf[PCF8563_REG_SC] = bin2bcd(पंचांग->पंचांग_sec);
	buf[PCF8563_REG_MN] = bin2bcd(पंचांग->पंचांग_min);
	buf[PCF8563_REG_HR] = bin2bcd(पंचांग->पंचांग_hour);

	buf[PCF8563_REG_DM] = bin2bcd(पंचांग->पंचांग_mday);

	/* month, 1 - 12 */
	buf[PCF8563_REG_MO] = bin2bcd(पंचांग->पंचांग_mon + 1);

	/* year and century */
	buf[PCF8563_REG_YR] = bin2bcd(पंचांग->पंचांग_year - 100);
	अगर (pcf8563->c_polarity ? (पंचांग->पंचांग_year >= 100) : (पंचांग->पंचांग_year < 100))
		buf[PCF8563_REG_MO] |= PCF8563_MO_C;

	buf[PCF8563_REG_DW] = पंचांग->पंचांग_wday & 0x07;

	वापस pcf8563_ग_लिखो_block_data(client, PCF8563_REG_SC,
				9 - PCF8563_REG_SC, buf + PCF8563_REG_SC);
पूर्ण

अटल पूर्णांक pcf8563_rtc_ioctl(काष्ठा device *dev, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		ret = i2c_smbus_पढ़ो_byte_data(client, PCF8563_REG_SC);
		अगर (ret < 0)
			वापस ret;

		वापस put_user(ret & PCF8563_SC_LV ? RTC_VL_DATA_INVALID : 0,
				(अचिन्हित पूर्णांक __user *)arg);
	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक pcf8563_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर buf[4];
	पूर्णांक err;

	err = pcf8563_पढ़ो_block_data(client, PCF8563_REG_AMN, 4, buf);
	अगर (err)
		वापस err;

	dev_dbg(&client->dev,
		"%s: raw data is min=%02x, hr=%02x, mday=%02x, wday=%02x\n",
		__func__, buf[0], buf[1], buf[2], buf[3]);

	पंचांग->समय.पंचांग_sec = 0;
	पंचांग->समय.पंचांग_min = bcd2bin(buf[0] & 0x7F);
	पंचांग->समय.पंचांग_hour = bcd2bin(buf[1] & 0x3F);
	पंचांग->समय.पंचांग_mday = bcd2bin(buf[2] & 0x3F);
	पंचांग->समय.पंचांग_wday = bcd2bin(buf[3] & 0x7);

	err = pcf8563_get_alarm_mode(client, &पंचांग->enabled, &पंचांग->pending);
	अगर (err < 0)
		वापस err;

	dev_dbg(&client->dev, "%s: tm is mins=%d, hours=%d, mday=%d, wday=%d,"
		" enabled=%d, pending=%d\n", __func__, पंचांग->समय.पंचांग_min,
		पंचांग->समय.पंचांग_hour, पंचांग->समय.पंचांग_mday, पंचांग->समय.पंचांग_wday,
		पंचांग->enabled, पंचांग->pending);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8563_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *पंचांग)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर buf[4];
	पूर्णांक err;

	/* The alarm has no seconds, round up to nearest minute */
	अगर (पंचांग->समय.पंचांग_sec) अणु
		समय64_t alarm_समय = rtc_पंचांग_to_समय64(&पंचांग->समय);

		alarm_समय += 60 - पंचांग->समय.पंचांग_sec;
		rtc_समय64_to_पंचांग(alarm_समय, &पंचांग->समय);
	पूर्ण

	dev_dbg(dev, "%s, min=%d hour=%d wday=%d mday=%d "
		"enabled=%d pending=%d\n", __func__,
		पंचांग->समय.पंचांग_min, पंचांग->समय.पंचांग_hour, पंचांग->समय.पंचांग_wday,
		पंचांग->समय.पंचांग_mday, पंचांग->enabled, पंचांग->pending);

	buf[0] = bin2bcd(पंचांग->समय.पंचांग_min);
	buf[1] = bin2bcd(पंचांग->समय.पंचांग_hour);
	buf[2] = bin2bcd(पंचांग->समय.पंचांग_mday);
	buf[3] = पंचांग->समय.पंचांग_wday & 0x07;

	err = pcf8563_ग_लिखो_block_data(client, PCF8563_REG_AMN, 4, buf);
	अगर (err)
		वापस err;

	वापस pcf8563_set_alarm_mode(client, !!पंचांग->enabled);
पूर्ण

अटल पूर्णांक pcf8563_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	dev_dbg(dev, "%s: en=%d\n", __func__, enabled);
	वापस pcf8563_set_alarm_mode(to_i2c_client(dev), !!enabled);
पूर्ण

#अगर_घोषित CONFIG_COMMON_CLK
/*
 * Handling of the clkout
 */

#घोषणा clkout_hw_to_pcf8563(_hw) container_of(_hw, काष्ठा pcf8563, clkout_hw)

अटल स्थिर पूर्णांक clkout_rates[] = अणु
	32768,
	1024,
	32,
	1,
पूर्ण;

अटल अचिन्हित दीर्घ pcf8563_clkout_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pcf8563 *pcf8563 = clkout_hw_to_pcf8563(hw);
	काष्ठा i2c_client *client = pcf8563->client;
	अचिन्हित अक्षर buf;
	पूर्णांक ret = pcf8563_पढ़ो_block_data(client, PCF8563_REG_CLKO, 1, &buf);

	अगर (ret < 0)
		वापस 0;

	buf &= PCF8563_REG_CLKO_F_MASK;
	वापस clkout_rates[buf];
पूर्ण

अटल दीर्घ pcf8563_clkout_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				      अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(clkout_rates); i++)
		अगर (clkout_rates[i] <= rate)
			वापस clkout_rates[i];

	वापस 0;
पूर्ण

अटल पूर्णांक pcf8563_clkout_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				   अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा pcf8563 *pcf8563 = clkout_hw_to_pcf8563(hw);
	काष्ठा i2c_client *client = pcf8563->client;
	अचिन्हित अक्षर buf;
	पूर्णांक ret = pcf8563_पढ़ो_block_data(client, PCF8563_REG_CLKO, 1, &buf);
	पूर्णांक i;

	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(clkout_rates); i++)
		अगर (clkout_rates[i] == rate) अणु
			buf &= ~PCF8563_REG_CLKO_F_MASK;
			buf |= i;
			ret = pcf8563_ग_लिखो_block_data(client,
						       PCF8563_REG_CLKO, 1,
						       &buf);
			वापस ret;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक pcf8563_clkout_control(काष्ठा clk_hw *hw, bool enable)
अणु
	काष्ठा pcf8563 *pcf8563 = clkout_hw_to_pcf8563(hw);
	काष्ठा i2c_client *client = pcf8563->client;
	अचिन्हित अक्षर buf;
	पूर्णांक ret = pcf8563_पढ़ो_block_data(client, PCF8563_REG_CLKO, 1, &buf);

	अगर (ret < 0)
		वापस ret;

	अगर (enable)
		buf |= PCF8563_REG_CLKO_FE;
	अन्यथा
		buf &= ~PCF8563_REG_CLKO_FE;

	ret = pcf8563_ग_लिखो_block_data(client, PCF8563_REG_CLKO, 1, &buf);
	वापस ret;
पूर्ण

अटल पूर्णांक pcf8563_clkout_prepare(काष्ठा clk_hw *hw)
अणु
	वापस pcf8563_clkout_control(hw, 1);
पूर्ण

अटल व्योम pcf8563_clkout_unprepare(काष्ठा clk_hw *hw)
अणु
	pcf8563_clkout_control(hw, 0);
पूर्ण

अटल पूर्णांक pcf8563_clkout_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा pcf8563 *pcf8563 = clkout_hw_to_pcf8563(hw);
	काष्ठा i2c_client *client = pcf8563->client;
	अचिन्हित अक्षर buf;
	पूर्णांक ret = pcf8563_पढ़ो_block_data(client, PCF8563_REG_CLKO, 1, &buf);

	अगर (ret < 0)
		वापस ret;

	वापस !!(buf & PCF8563_REG_CLKO_FE);
पूर्ण

अटल स्थिर काष्ठा clk_ops pcf8563_clkout_ops = अणु
	.prepare = pcf8563_clkout_prepare,
	.unprepare = pcf8563_clkout_unprepare,
	.is_prepared = pcf8563_clkout_is_prepared,
	.recalc_rate = pcf8563_clkout_recalc_rate,
	.round_rate = pcf8563_clkout_round_rate,
	.set_rate = pcf8563_clkout_set_rate,
पूर्ण;

अटल काष्ठा clk *pcf8563_clkout_रेजिस्टर_clk(काष्ठा pcf8563 *pcf8563)
अणु
	काष्ठा i2c_client *client = pcf8563->client;
	काष्ठा device_node *node = client->dev.of_node;
	काष्ठा clk *clk;
	काष्ठा clk_init_data init;
	पूर्णांक ret;
	अचिन्हित अक्षर buf;

	/* disable the clkout output */
	buf = 0;
	ret = pcf8563_ग_लिखो_block_data(client, PCF8563_REG_CLKO, 1, &buf);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	init.name = "pcf8563-clkout";
	init.ops = &pcf8563_clkout_ops;
	init.flags = 0;
	init.parent_names = शून्य;
	init.num_parents = 0;
	pcf8563->clkout_hw.init = &init;

	/* optional override of the घड़ीname */
	of_property_पढ़ो_string(node, "clock-output-names", &init.name);

	/* रेजिस्टर the घड़ी */
	clk = devm_clk_रेजिस्टर(&client->dev, &pcf8563->clkout_hw);

	अगर (!IS_ERR(clk))
		of_clk_add_provider(node, of_clk_src_simple_get, clk);

	वापस clk;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा rtc_class_ops pcf8563_rtc_ops = अणु
	.ioctl		= pcf8563_rtc_ioctl,
	.पढ़ो_समय	= pcf8563_rtc_पढ़ो_समय,
	.set_समय	= pcf8563_rtc_set_समय,
	.पढ़ो_alarm	= pcf8563_rtc_पढ़ो_alarm,
	.set_alarm	= pcf8563_rtc_set_alarm,
	.alarm_irq_enable = pcf8563_irq_enable,
पूर्ण;

अटल पूर्णांक pcf8563_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा pcf8563 *pcf8563;
	पूर्णांक err;
	अचिन्हित अक्षर buf;

	dev_dbg(&client->dev, "%s\n", __func__);

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	pcf8563 = devm_kzalloc(&client->dev, माप(काष्ठा pcf8563),
				GFP_KERNEL);
	अगर (!pcf8563)
		वापस -ENOMEM;

	i2c_set_clientdata(client, pcf8563);
	pcf8563->client = client;
	device_set_wakeup_capable(&client->dev, 1);

	/* Set समयr to lowest frequency to save घातer (ref Haoyu datasheet) */
	buf = PCF8563_TMRC_1_60;
	err = pcf8563_ग_लिखो_block_data(client, PCF8563_REG_TMRC, 1, &buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "%s: write error\n", __func__);
		वापस err;
	पूर्ण

	/* Clear flags and disable पूर्णांकerrupts */
	buf = 0;
	err = pcf8563_ग_लिखो_block_data(client, PCF8563_REG_ST2, 1, &buf);
	अगर (err < 0) अणु
		dev_err(&client->dev, "%s: write error\n", __func__);
		वापस err;
	पूर्ण

	pcf8563->rtc = devm_rtc_allocate_device(&client->dev);
	अगर (IS_ERR(pcf8563->rtc))
		वापस PTR_ERR(pcf8563->rtc);

	pcf8563->rtc->ops = &pcf8563_rtc_ops;
	/* the pcf8563 alarm only supports a minute accuracy */
	pcf8563->rtc->uie_unsupported = 1;
	pcf8563->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	pcf8563->rtc->range_max = RTC_TIMESTAMP_END_2099;
	pcf8563->rtc->set_start_समय = true;

	अगर (client->irq > 0) अणु
		err = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
				शून्य, pcf8563_irq,
				IRQF_SHARED | IRQF_ONESHOT | IRQF_TRIGGER_LOW,
				pcf8563_driver.driver.name, client);
		अगर (err) अणु
			dev_err(&client->dev, "unable to request IRQ %d\n",
								client->irq);
			वापस err;
		पूर्ण
	पूर्ण

	err = devm_rtc_रेजिस्टर_device(pcf8563->rtc);
	अगर (err)
		वापस err;

#अगर_घोषित CONFIG_COMMON_CLK
	/* रेजिस्टर clk in common clk framework */
	pcf8563_clkout_रेजिस्टर_clk(pcf8563);
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcf8563_id[] = अणु
	अणु "pcf8563", 0 पूर्ण,
	अणु "rtc8564", 0 पूर्ण,
	अणु "pca8565", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf8563_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcf8563_of_match[] = अणु
	अणु .compatible = "nxp,pcf8563" पूर्ण,
	अणु .compatible = "epson,rtc8564" पूर्ण,
	अणु .compatible = "microcrystal,rv8564" पूर्ण,
	अणु .compatible = "nxp,pca8565" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcf8563_of_match);
#पूर्ण_अगर

अटल काष्ठा i2c_driver pcf8563_driver = अणु
	.driver		= अणु
		.name	= "rtc-pcf8563",
		.of_match_table = of_match_ptr(pcf8563_of_match),
	पूर्ण,
	.probe		= pcf8563_probe,
	.id_table	= pcf8563_id,
पूर्ण;

module_i2c_driver(pcf8563_driver);

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("Philips PCF8563/Epson RTC8564 RTC driver");
MODULE_LICENSE("GPL");
