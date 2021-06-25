<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An I2C and SPI driver क्रम the NXP PCF2127/29 RTC
 * Copyright 2013 Til-Technologies
 *
 * Author: Renaud Cerrato <r.cerrato@til-technologies.fr>
 *
 * Watchकरोg and tamper functions
 * Author: Bruno Thomsen <bruno.thomsen@gmail.com>
 *
 * based on the other drivers in this same directory.
 *
 * Datasheet: http://cache.nxp.com/करोcuments/data_sheet/PCF2127.pdf
 */

#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/bcd.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/regmap.h>
#समावेश <linux/watchकरोg.h>

/* Control रेजिस्टर 1 */
#घोषणा PCF2127_REG_CTRL1		0x00
#घोषणा PCF2127_BIT_CTRL1_POR_OVRD		BIT(3)
#घोषणा PCF2127_BIT_CTRL1_TSF1			BIT(4)
/* Control रेजिस्टर 2 */
#घोषणा PCF2127_REG_CTRL2		0x01
#घोषणा PCF2127_BIT_CTRL2_AIE			BIT(1)
#घोषणा PCF2127_BIT_CTRL2_TSIE			BIT(2)
#घोषणा PCF2127_BIT_CTRL2_AF			BIT(4)
#घोषणा PCF2127_BIT_CTRL2_TSF2			BIT(5)
#घोषणा PCF2127_BIT_CTRL2_WDTF			BIT(6)
/* Control रेजिस्टर 3 */
#घोषणा PCF2127_REG_CTRL3		0x02
#घोषणा PCF2127_BIT_CTRL3_BLIE			BIT(0)
#घोषणा PCF2127_BIT_CTRL3_BIE			BIT(1)
#घोषणा PCF2127_BIT_CTRL3_BLF			BIT(2)
#घोषणा PCF2127_BIT_CTRL3_BF			BIT(3)
#घोषणा PCF2127_BIT_CTRL3_BTSE			BIT(4)
/* Time and date रेजिस्टरs */
#घोषणा PCF2127_REG_SC			0x03
#घोषणा PCF2127_BIT_SC_OSF			BIT(7)
#घोषणा PCF2127_REG_MN			0x04
#घोषणा PCF2127_REG_HR			0x05
#घोषणा PCF2127_REG_DM			0x06
#घोषणा PCF2127_REG_DW			0x07
#घोषणा PCF2127_REG_MO			0x08
#घोषणा PCF2127_REG_YR			0x09
/* Alarm रेजिस्टरs */
#घोषणा PCF2127_REG_ALARM_SC		0x0A
#घोषणा PCF2127_REG_ALARM_MN		0x0B
#घोषणा PCF2127_REG_ALARM_HR		0x0C
#घोषणा PCF2127_REG_ALARM_DM		0x0D
#घोषणा PCF2127_REG_ALARM_DW		0x0E
#घोषणा PCF2127_BIT_ALARM_AE			BIT(7)
/* CLKOUT control रेजिस्टर */
#घोषणा PCF2127_REG_CLKOUT		0x0f
#घोषणा PCF2127_BIT_CLKOUT_OTPR			BIT(5)
/* Watchकरोg रेजिस्टरs */
#घोषणा PCF2127_REG_WD_CTL		0x10
#घोषणा PCF2127_BIT_WD_CTL_TF0			BIT(0)
#घोषणा PCF2127_BIT_WD_CTL_TF1			BIT(1)
#घोषणा PCF2127_BIT_WD_CTL_CD0			BIT(6)
#घोषणा PCF2127_BIT_WD_CTL_CD1			BIT(7)
#घोषणा PCF2127_REG_WD_VAL		0x11
/* Tamper बारtamp रेजिस्टरs */
#घोषणा PCF2127_REG_TS_CTRL		0x12
#घोषणा PCF2127_BIT_TS_CTRL_TSOFF		BIT(6)
#घोषणा PCF2127_BIT_TS_CTRL_TSM			BIT(7)
#घोषणा PCF2127_REG_TS_SC		0x13
#घोषणा PCF2127_REG_TS_MN		0x14
#घोषणा PCF2127_REG_TS_HR		0x15
#घोषणा PCF2127_REG_TS_DM		0x16
#घोषणा PCF2127_REG_TS_MO		0x17
#घोषणा PCF2127_REG_TS_YR		0x18
/*
 * RAM रेजिस्टरs
 * PCF2127 has 512 bytes general-purpose अटल RAM (SRAM) that is
 * battery backed and can survive a घातer outage.
 * PCF2129 करोesn't have this feature.
 */
#घोषणा PCF2127_REG_RAM_ADDR_MSB	0x1A
#घोषणा PCF2127_REG_RAM_WRT_CMD		0x1C
#घोषणा PCF2127_REG_RAM_RD_CMD		0x1D

/* Watchकरोg समयr value स्थिरants */
#घोषणा PCF2127_WD_VAL_STOP		0
#घोषणा PCF2127_WD_VAL_MIN		2
#घोषणा PCF2127_WD_VAL_MAX		255
#घोषणा PCF2127_WD_VAL_DEFAULT		60

काष्ठा pcf2127 अणु
	काष्ठा rtc_device *rtc;
	काष्ठा watchकरोg_device wdd;
	काष्ठा regmap *regmap;
पूर्ण;

/*
 * In the routines that deal directly with the pcf2127 hardware, we use
 * rtc_समय -- month 0-11, hour 0-23, yr = calendar year-epoch.
 */
अटल पूर्णांक pcf2127_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[10];
	पूर्णांक ret;

	/*
	 * Aव्योम पढ़ोing CTRL2 रेजिस्टर as it causes WD_VAL रेजिस्टर
	 * value to reset to 0 which means watchकरोg is stopped.
	 */
	ret = regmap_bulk_पढ़ो(pcf2127->regmap, PCF2127_REG_CTRL3,
			       (buf + PCF2127_REG_CTRL3),
			       ARRAY_SIZE(buf) - PCF2127_REG_CTRL3);
	अगर (ret) अणु
		dev_err(dev, "%s: read error\n", __func__);
		वापस ret;
	पूर्ण

	अगर (buf[PCF2127_REG_CTRL3] & PCF2127_BIT_CTRL3_BLF)
		dev_info(dev,
			"low voltage detected, check/replace RTC battery.\n");

	/* Clock पूर्णांकegrity is not guaranteed when OSF flag is set. */
	अगर (buf[PCF2127_REG_SC] & PCF2127_BIT_SC_OSF) अणु
		/*
		 * no need clear the flag here,
		 * it will be cleared once the new date is saved
		 */
		dev_warn(dev,
			 "oscillator stop detected, date/time is not reliable\n");
		वापस -EINVAL;
	पूर्ण

	dev_dbg(dev,
		"%s: raw data is cr3=%02x, sec=%02x, min=%02x, hr=%02x, "
		"mday=%02x, wday=%02x, mon=%02x, year=%02x\n",
		__func__, buf[PCF2127_REG_CTRL3], buf[PCF2127_REG_SC],
		buf[PCF2127_REG_MN], buf[PCF2127_REG_HR],
		buf[PCF2127_REG_DM], buf[PCF2127_REG_DW],
		buf[PCF2127_REG_MO], buf[PCF2127_REG_YR]);

	पंचांग->पंचांग_sec = bcd2bin(buf[PCF2127_REG_SC] & 0x7F);
	पंचांग->पंचांग_min = bcd2bin(buf[PCF2127_REG_MN] & 0x7F);
	पंचांग->पंचांग_hour = bcd2bin(buf[PCF2127_REG_HR] & 0x3F); /* rtc hr 0-23 */
	पंचांग->पंचांग_mday = bcd2bin(buf[PCF2127_REG_DM] & 0x3F);
	पंचांग->पंचांग_wday = buf[PCF2127_REG_DW] & 0x07;
	पंचांग->पंचांग_mon = bcd2bin(buf[PCF2127_REG_MO] & 0x1F) - 1; /* rtc mn 1-12 */
	पंचांग->पंचांग_year = bcd2bin(buf[PCF2127_REG_YR]);
	पंचांग->पंचांग_year += 100;

	dev_dbg(dev, "%s: tm is secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2127_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev);
	अचिन्हित अक्षर buf[7];
	पूर्णांक i = 0, err;

	dev_dbg(dev, "%s: secs=%d, mins=%d, hours=%d, "
		"mday=%d, mon=%d, year=%d, wday=%d\n",
		__func__,
		पंचांग->पंचांग_sec, पंचांग->पंचांग_min, पंचांग->पंचांग_hour,
		पंचांग->पंचांग_mday, पंचांग->पंचांग_mon, पंचांग->पंचांग_year, पंचांग->पंचांग_wday);

	/* hours, minutes and seconds */
	buf[i++] = bin2bcd(पंचांग->पंचांग_sec);	/* this will also clear OSF flag */
	buf[i++] = bin2bcd(पंचांग->पंचांग_min);
	buf[i++] = bin2bcd(पंचांग->पंचांग_hour);
	buf[i++] = bin2bcd(पंचांग->पंचांग_mday);
	buf[i++] = पंचांग->पंचांग_wday & 0x07;

	/* month, 1 - 12 */
	buf[i++] = bin2bcd(पंचांग->पंचांग_mon + 1);

	/* year */
	buf[i++] = bin2bcd(पंचांग->पंचांग_year - 100);

	/* ग_लिखो रेजिस्टर's data */
	err = regmap_bulk_ग_लिखो(pcf2127->regmap, PCF2127_REG_SC, buf, i);
	अगर (err) अणु
		dev_err(dev,
			"%s: err=%d", __func__, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2127_rtc_ioctl(काष्ठा device *dev,
				अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev);
	पूर्णांक val, touser = 0;
	पूर्णांक ret;

	चयन (cmd) अणु
	हाल RTC_VL_READ:
		ret = regmap_पढ़ो(pcf2127->regmap, PCF2127_REG_CTRL3, &val);
		अगर (ret)
			वापस ret;

		अगर (val & PCF2127_BIT_CTRL3_BLF)
			touser |= RTC_VL_BACKUP_LOW;

		अगर (val & PCF2127_BIT_CTRL3_BF)
			touser |= RTC_VL_BACKUP_SWITCH;

		वापस put_user(touser, (अचिन्हित पूर्णांक __user *)arg);

	हाल RTC_VL_CLR:
		वापस regmap_update_bits(pcf2127->regmap, PCF2127_REG_CTRL3,
					  PCF2127_BIT_CTRL3_BF, 0);

	शेष:
		वापस -ENOIOCTLCMD;
	पूर्ण
पूर्ण

अटल पूर्णांक pcf2127_nvmem_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक offset,
			      व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा pcf2127 *pcf2127 = priv;
	पूर्णांक ret;
	अचिन्हित अक्षर offरखो_बफ[] = अणु offset >> 8, offset पूर्ण;

	ret = regmap_bulk_ग_लिखो(pcf2127->regmap, PCF2127_REG_RAM_ADDR_MSB,
				offरखो_बफ, 2);
	अगर (ret)
		वापस ret;

	वापस regmap_bulk_पढ़ो(pcf2127->regmap, PCF2127_REG_RAM_RD_CMD,
				val, bytes);
पूर्ण

अटल पूर्णांक pcf2127_nvmem_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक offset,
			       व्योम *val, माप_प्रकार bytes)
अणु
	काष्ठा pcf2127 *pcf2127 = priv;
	पूर्णांक ret;
	अचिन्हित अक्षर offरखो_बफ[] = अणु offset >> 8, offset पूर्ण;

	ret = regmap_bulk_ग_लिखो(pcf2127->regmap, PCF2127_REG_RAM_ADDR_MSB,
				offरखो_बफ, 2);
	अगर (ret)
		वापस ret;

	वापस regmap_bulk_ग_लिखो(pcf2127->regmap, PCF2127_REG_RAM_WRT_CMD,
				 val, bytes);
पूर्ण

/* watchकरोg driver */

अटल पूर्णांक pcf2127_wdt_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pcf2127 *pcf2127 = watchकरोg_get_drvdata(wdd);

	वापस regmap_ग_लिखो(pcf2127->regmap, PCF2127_REG_WD_VAL, wdd->समयout);
पूर्ण

/*
 * Restart watchकरोg समयr अगर feature is active.
 *
 * Note: Reading CTRL2 रेजिस्टर causes watchकरोg to stop which is unक्रमtunate,
 * since रेजिस्टर also contain control/status flags क्रम other features.
 * Always call this function after पढ़ोing CTRL2 रेजिस्टर.
 */
अटल पूर्णांक pcf2127_wdt_active_ping(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक ret = 0;

	अगर (watchकरोg_active(wdd)) अणु
		ret = pcf2127_wdt_ping(wdd);
		अगर (ret)
			dev_err(wdd->parent,
				"%s: watchdog restart failed, ret=%d\n",
				__func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pcf2127_wdt_start(काष्ठा watchकरोg_device *wdd)
अणु
	वापस pcf2127_wdt_ping(wdd);
पूर्ण

अटल पूर्णांक pcf2127_wdt_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा pcf2127 *pcf2127 = watchकरोg_get_drvdata(wdd);

	वापस regmap_ग_लिखो(pcf2127->regmap, PCF2127_REG_WD_VAL,
			    PCF2127_WD_VAL_STOP);
पूर्ण

अटल पूर्णांक pcf2127_wdt_set_समयout(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित पूर्णांक new_समयout)
अणु
	dev_dbg(wdd->parent, "new watchdog timeout: %is (old: %is)\n",
		new_समयout, wdd->समयout);

	wdd->समयout = new_समयout;

	वापस pcf2127_wdt_active_ping(wdd);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info pcf2127_wdt_info = अणु
	.identity = "NXP PCF2127/PCF2129 Watchdog",
	.options = WDIOF_KEEPALIVEPING | WDIOF_SETTIMEOUT,
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops pcf2127_watchकरोg_ops = अणु
	.owner = THIS_MODULE,
	.start = pcf2127_wdt_start,
	.stop = pcf2127_wdt_stop,
	.ping = pcf2127_wdt_ping,
	.set_समयout = pcf2127_wdt_set_समयout,
पूर्ण;

अटल पूर्णांक pcf2127_watchकरोg_init(काष्ठा device *dev, काष्ठा pcf2127 *pcf2127)
अणु
	u32 wdd_समयout;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_WATCHDOG) ||
	    !device_property_पढ़ो_bool(dev, "reset-source"))
		वापस 0;

	pcf2127->wdd.parent = dev;
	pcf2127->wdd.info = &pcf2127_wdt_info;
	pcf2127->wdd.ops = &pcf2127_watchकरोg_ops;
	pcf2127->wdd.min_समयout = PCF2127_WD_VAL_MIN;
	pcf2127->wdd.max_समयout = PCF2127_WD_VAL_MAX;
	pcf2127->wdd.समयout = PCF2127_WD_VAL_DEFAULT;
	pcf2127->wdd.min_hw_heartbeat_ms = 500;
	pcf2127->wdd.status = WATCHDOG_NOWAYOUT_INIT_STATUS;

	watchकरोg_set_drvdata(&pcf2127->wdd, pcf2127);

	/* Test अगर watchकरोg समयr is started by bootloader */
	ret = regmap_पढ़ो(pcf2127->regmap, PCF2127_REG_WD_VAL, &wdd_समयout);
	अगर (ret)
		वापस ret;

	अगर (wdd_समयout)
		set_bit(WDOG_HW_RUNNING, &pcf2127->wdd.status);

	वापस devm_watchकरोg_रेजिस्टर_device(dev, &pcf2127->wdd);
पूर्ण

/* Alarm */
अटल पूर्णांक pcf2127_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक buf[5], ctrl2;
	पूर्णांक ret;

	ret = regmap_पढ़ो(pcf2127->regmap, PCF2127_REG_CTRL2, &ctrl2);
	अगर (ret)
		वापस ret;

	ret = pcf2127_wdt_active_ping(&pcf2127->wdd);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(pcf2127->regmap, PCF2127_REG_ALARM_SC, buf,
			       माप(buf));
	अगर (ret)
		वापस ret;

	alrm->enabled = ctrl2 & PCF2127_BIT_CTRL2_AIE;
	alrm->pending = ctrl2 & PCF2127_BIT_CTRL2_AF;

	alrm->समय.पंचांग_sec = bcd2bin(buf[0] & 0x7F);
	alrm->समय.पंचांग_min = bcd2bin(buf[1] & 0x7F);
	alrm->समय.पंचांग_hour = bcd2bin(buf[2] & 0x3F);
	alrm->समय.पंचांग_mday = bcd2bin(buf[3] & 0x3F);

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2127_rtc_alarm_irq_enable(काष्ठा device *dev, u32 enable)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_CTRL2,
				 PCF2127_BIT_CTRL2_AIE,
				 enable ? PCF2127_BIT_CTRL2_AIE : 0);
	अगर (ret)
		वापस ret;

	वापस pcf2127_wdt_active_ping(&pcf2127->wdd);
पूर्ण

अटल पूर्णांक pcf2127_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev);
	uपूर्णांक8_t buf[5];
	पूर्णांक ret;

	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_CTRL2,
				 PCF2127_BIT_CTRL2_AF, 0);
	अगर (ret)
		वापस ret;

	ret = pcf2127_wdt_active_ping(&pcf2127->wdd);
	अगर (ret)
		वापस ret;

	buf[0] = bin2bcd(alrm->समय.पंचांग_sec);
	buf[1] = bin2bcd(alrm->समय.पंचांग_min);
	buf[2] = bin2bcd(alrm->समय.पंचांग_hour);
	buf[3] = bin2bcd(alrm->समय.पंचांग_mday);
	buf[4] = PCF2127_BIT_ALARM_AE; /* Do not match on week day */

	ret = regmap_bulk_ग_लिखो(pcf2127->regmap, PCF2127_REG_ALARM_SC, buf,
				माप(buf));
	अगर (ret)
		वापस ret;

	वापस pcf2127_rtc_alarm_irq_enable(dev, alrm->enabled);
पूर्ण

अटल irqवापस_t pcf2127_rtc_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक ctrl2 = 0;
	पूर्णांक ret = 0;

	ret = regmap_पढ़ो(pcf2127->regmap, PCF2127_REG_CTRL2, &ctrl2);
	अगर (ret)
		वापस IRQ_NONE;

	अगर (!(ctrl2 & PCF2127_BIT_CTRL2_AF))
		वापस IRQ_NONE;

	regmap_ग_लिखो(pcf2127->regmap, PCF2127_REG_CTRL2,
		     ctrl2 & ~(PCF2127_BIT_CTRL2_AF | PCF2127_BIT_CTRL2_WDTF));

	rtc_update_irq(pcf2127->rtc, 1, RTC_IRQF | RTC_AF);

	pcf2127_wdt_active_ping(&pcf2127->wdd);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops pcf2127_rtc_ops = अणु
	.ioctl            = pcf2127_rtc_ioctl,
	.पढ़ो_समय        = pcf2127_rtc_पढ़ो_समय,
	.set_समय         = pcf2127_rtc_set_समय,
	.पढ़ो_alarm       = pcf2127_rtc_पढ़ो_alarm,
	.set_alarm        = pcf2127_rtc_set_alarm,
	.alarm_irq_enable = pcf2127_rtc_alarm_irq_enable,
पूर्ण;

/* sysfs पूर्णांकerface */

अटल sमाप_प्रकार बारtamp0_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev->parent);
	पूर्णांक ret;

	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_CTRL1,
				 PCF2127_BIT_CTRL1_TSF1, 0);
	अगर (ret) अणु
		dev_err(dev, "%s: update ctrl1 ret=%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_CTRL2,
				 PCF2127_BIT_CTRL2_TSF2, 0);
	अगर (ret) अणु
		dev_err(dev, "%s: update ctrl2 ret=%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	ret = pcf2127_wdt_active_ping(&pcf2127->wdd);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण;

अटल sमाप_प्रकार बारtamp0_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा pcf2127 *pcf2127 = dev_get_drvdata(dev->parent);
	काष्ठा rtc_समय पंचांग;
	पूर्णांक ret;
	अचिन्हित अक्षर data[25];

	ret = regmap_bulk_पढ़ो(pcf2127->regmap, PCF2127_REG_CTRL1, data,
			       माप(data));
	अगर (ret) अणु
		dev_err(dev, "%s: read error ret=%d\n", __func__, ret);
		वापस ret;
	पूर्ण

	dev_dbg(dev,
		"%s: raw data is cr1=%02x, cr2=%02x, cr3=%02x, ts_sc=%02x, "
		"ts_mn=%02x, ts_hr=%02x, ts_dm=%02x, ts_mo=%02x, ts_yr=%02x\n",
		__func__, data[PCF2127_REG_CTRL1], data[PCF2127_REG_CTRL2],
		data[PCF2127_REG_CTRL3], data[PCF2127_REG_TS_SC],
		data[PCF2127_REG_TS_MN], data[PCF2127_REG_TS_HR],
		data[PCF2127_REG_TS_DM], data[PCF2127_REG_TS_MO],
		data[PCF2127_REG_TS_YR]);

	ret = pcf2127_wdt_active_ping(&pcf2127->wdd);
	अगर (ret)
		वापस ret;

	अगर (!(data[PCF2127_REG_CTRL1] & PCF2127_BIT_CTRL1_TSF1) &&
	    !(data[PCF2127_REG_CTRL2] & PCF2127_BIT_CTRL2_TSF2))
		वापस 0;

	पंचांग.पंचांग_sec = bcd2bin(data[PCF2127_REG_TS_SC] & 0x7F);
	पंचांग.पंचांग_min = bcd2bin(data[PCF2127_REG_TS_MN] & 0x7F);
	पंचांग.पंचांग_hour = bcd2bin(data[PCF2127_REG_TS_HR] & 0x3F);
	पंचांग.पंचांग_mday = bcd2bin(data[PCF2127_REG_TS_DM] & 0x3F);
	/* TS_MO रेजिस्टर (month) value range: 1-12 */
	पंचांग.पंचांग_mon = bcd2bin(data[PCF2127_REG_TS_MO] & 0x1F) - 1;
	पंचांग.पंचांग_year = bcd2bin(data[PCF2127_REG_TS_YR]);
	अगर (पंचांग.पंचांग_year < 70)
		पंचांग.पंचांग_year += 100; /* assume we are in 1970...2069 */

	ret = rtc_valid_पंचांग(&पंचांग);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%llu\n",
		       (अचिन्हित दीर्घ दीर्घ)rtc_पंचांग_to_समय64(&पंचांग));
पूर्ण;

अटल DEVICE_ATTR_RW(बारtamp0);

अटल काष्ठा attribute *pcf2127_attrs[] = अणु
	&dev_attr_बारtamp0.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pcf2127_attr_group = अणु
	.attrs	= pcf2127_attrs,
पूर्ण;

अटल पूर्णांक pcf2127_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
			 पूर्णांक alarm_irq, स्थिर अक्षर *name, bool is_pcf2127)
अणु
	काष्ठा pcf2127 *pcf2127;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक val;

	dev_dbg(dev, "%s\n", __func__);

	pcf2127 = devm_kzalloc(dev, माप(*pcf2127), GFP_KERNEL);
	अगर (!pcf2127)
		वापस -ENOMEM;

	pcf2127->regmap = regmap;

	dev_set_drvdata(dev, pcf2127);

	pcf2127->rtc = devm_rtc_allocate_device(dev);
	अगर (IS_ERR(pcf2127->rtc))
		वापस PTR_ERR(pcf2127->rtc);

	pcf2127->rtc->ops = &pcf2127_rtc_ops;
	pcf2127->rtc->range_min = RTC_TIMESTAMP_BEGIN_2000;
	pcf2127->rtc->range_max = RTC_TIMESTAMP_END_2099;
	pcf2127->rtc->set_start_समय = true; /* Sets actual start to 1970 */
	pcf2127->rtc->uie_unsupported = 1;
	clear_bit(RTC_FEATURE_ALARM, pcf2127->rtc->features);

	अगर (alarm_irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, alarm_irq, शून्य,
						pcf2127_rtc_irq,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						dev_name(dev), dev);
		अगर (ret) अणु
			dev_err(dev, "failed to request alarm irq\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (alarm_irq > 0 || device_property_पढ़ो_bool(dev, "wakeup-source")) अणु
		device_init_wakeup(dev, true);
		set_bit(RTC_FEATURE_ALARM, pcf2127->rtc->features);
	पूर्ण

	अगर (is_pcf2127) अणु
		काष्ठा nvmem_config nvmem_cfg = अणु
			.priv = pcf2127,
			.reg_पढ़ो = pcf2127_nvmem_पढ़ो,
			.reg_ग_लिखो = pcf2127_nvmem_ग_लिखो,
			.size = 512,
		पूर्ण;

		ret = devm_rtc_nvmem_रेजिस्टर(pcf2127->rtc, &nvmem_cfg);
	पूर्ण

	/*
	 * The "Power-On Reset Override" facility prevents the RTC to करो a reset
	 * after घातer on. For normal operation the PORO must be disabled.
	 */
	regmap_clear_bits(pcf2127->regmap, PCF2127_REG_CTRL1,
				PCF2127_BIT_CTRL1_POR_OVRD);

	ret = regmap_पढ़ो(pcf2127->regmap, PCF2127_REG_CLKOUT, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (!(val & PCF2127_BIT_CLKOUT_OTPR)) अणु
		ret = regmap_set_bits(pcf2127->regmap, PCF2127_REG_CLKOUT,
				      PCF2127_BIT_CLKOUT_OTPR);
		अगर (ret < 0)
			वापस ret;

		msleep(100);
	पूर्ण

	/*
	 * Watchकरोg समयr enabled and reset pin /RST activated when समयd out.
	 * Select 1Hz घड़ी source क्रम watchकरोg समयr.
	 * Note: Countकरोwn समयr disabled and not available.
	 * For pca2129, pcf2129, only bit[7] is क्रम Symbol WD_CD
	 * of रेजिस्टर watchdg_tim_ctl. The bit[6] is labeled
	 * as T. Bits labeled as T must always be written with
	 * logic 0.
	 */
	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_WD_CTL,
				 PCF2127_BIT_WD_CTL_CD1 |
				 PCF2127_BIT_WD_CTL_CD0 |
				 PCF2127_BIT_WD_CTL_TF1 |
				 PCF2127_BIT_WD_CTL_TF0,
				 PCF2127_BIT_WD_CTL_CD1 |
				 (is_pcf2127 ? PCF2127_BIT_WD_CTL_CD0 : 0) |
				 PCF2127_BIT_WD_CTL_TF1);
	अगर (ret) अणु
		dev_err(dev, "%s: watchdog config (wd_ctl) failed\n", __func__);
		वापस ret;
	पूर्ण

	pcf2127_watchकरोg_init(dev, pcf2127);

	/*
	 * Disable battery low/चयन-over बारtamp and पूर्णांकerrupts.
	 * Clear battery पूर्णांकerrupt flags which can block new trigger events.
	 * Note: This is the शेष chip behaviour but added to ensure
	 * correct tamper बारtamp and पूर्णांकerrupt function.
	 */
	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_CTRL3,
				 PCF2127_BIT_CTRL3_BTSE |
				 PCF2127_BIT_CTRL3_BIE |
				 PCF2127_BIT_CTRL3_BLIE, 0);
	अगर (ret) अणु
		dev_err(dev, "%s: interrupt config (ctrl3) failed\n",
			__func__);
		वापस ret;
	पूर्ण

	/*
	 * Enable बारtamp function and store बारtamp of first trigger
	 * event until TSF1 and TFS2 पूर्णांकerrupt flags are cleared.
	 */
	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_TS_CTRL,
				 PCF2127_BIT_TS_CTRL_TSOFF |
				 PCF2127_BIT_TS_CTRL_TSM,
				 PCF2127_BIT_TS_CTRL_TSM);
	अगर (ret) अणु
		dev_err(dev, "%s: tamper detection config (ts_ctrl) failed\n",
			__func__);
		वापस ret;
	पूर्ण

	/*
	 * Enable पूर्णांकerrupt generation when TSF1 or TSF2 बारtamp flags
	 * are set. Interrupt संकेत is an खोलो-drain output and can be
	 * left भग्नing अगर unused.
	 */
	ret = regmap_update_bits(pcf2127->regmap, PCF2127_REG_CTRL2,
				 PCF2127_BIT_CTRL2_TSIE,
				 PCF2127_BIT_CTRL2_TSIE);
	अगर (ret) अणु
		dev_err(dev, "%s: tamper detection config (ctrl2) failed\n",
			__func__);
		वापस ret;
	पूर्ण

	ret = rtc_add_group(pcf2127->rtc, &pcf2127_attr_group);
	अगर (ret) अणु
		dev_err(dev, "%s: tamper sysfs registering failed\n",
			__func__);
		वापस ret;
	पूर्ण

	वापस devm_rtc_रेजिस्टर_device(pcf2127->rtc);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id pcf2127_of_match[] = अणु
	अणु .compatible = "nxp,pcf2127" पूर्ण,
	अणु .compatible = "nxp,pcf2129" पूर्ण,
	अणु .compatible = "nxp,pca2129" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcf2127_of_match);
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C)

अटल पूर्णांक pcf2127_i2c_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	ret = i2c_master_send(client, data, count);
	अगर (ret != count)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2127_i2c_gather_ग_लिखो(व्योम *context,
				स्थिर व्योम *reg, माप_प्रकार reg_size,
				स्थिर व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;
	व्योम *buf;

	अगर (WARN_ON(reg_size != 1))
		वापस -EINVAL;

	buf = kदो_स्मृति(val_size + 1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	स_नकल(buf, reg, 1);
	स_नकल(buf + 1, val, val_size);

	ret = i2c_master_send(client, buf, val_size + 1);

	kमुक्त(buf);

	अगर (ret != val_size + 1)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक pcf2127_i2c_पढ़ो(व्योम *context, स्थिर व्योम *reg, माप_प्रकार reg_size,
				व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;

	अगर (WARN_ON(reg_size != 1))
		वापस -EINVAL;

	ret = i2c_master_send(client, reg, 1);
	अगर (ret != 1)
		वापस ret < 0 ? ret : -EIO;

	ret = i2c_master_recv(client, val, val_size);
	अगर (ret != val_size)
		वापस ret < 0 ? ret : -EIO;

	वापस 0;
पूर्ण

/*
 * The reason we need this custom regmap_bus instead of using regmap_init_i2c()
 * is that the STOP condition is required between set रेजिस्टर address and
 * पढ़ो रेजिस्टर data when पढ़ोing from रेजिस्टरs.
 */
अटल स्थिर काष्ठा regmap_bus pcf2127_i2c_regmap = अणु
	.ग_लिखो = pcf2127_i2c_ग_लिखो,
	.gather_ग_लिखो = pcf2127_i2c_gather_ग_लिखो,
	.पढ़ो = pcf2127_i2c_पढ़ो,
पूर्ण;

अटल काष्ठा i2c_driver pcf2127_i2c_driver;

अटल पूर्णांक pcf2127_i2c_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;
	अटल स्थिर काष्ठा regmap_config config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.max_रेजिस्टर = 0x1d,
	पूर्ण;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENODEV;

	regmap = devm_regmap_init(&client->dev, &pcf2127_i2c_regmap,
					&client->dev, &config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "%s: regmap allocation failed: %ld\n",
			__func__, PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस pcf2127_probe(&client->dev, regmap, client->irq,
			     pcf2127_i2c_driver.driver.name, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pcf2127_i2c_id[] = अणु
	अणु "pcf2127", 1 पूर्ण,
	अणु "pcf2129", 0 पूर्ण,
	अणु "pca2129", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pcf2127_i2c_id);

अटल काष्ठा i2c_driver pcf2127_i2c_driver = अणु
	.driver		= अणु
		.name	= "rtc-pcf2127-i2c",
		.of_match_table = of_match_ptr(pcf2127_of_match),
	पूर्ण,
	.probe		= pcf2127_i2c_probe,
	.id_table	= pcf2127_i2c_id,
पूर्ण;

अटल पूर्णांक pcf2127_i2c_रेजिस्टर_driver(व्योम)
अणु
	वापस i2c_add_driver(&pcf2127_i2c_driver);
पूर्ण

अटल व्योम pcf2127_i2c_unरेजिस्टर_driver(व्योम)
अणु
	i2c_del_driver(&pcf2127_i2c_driver);
पूर्ण

#अन्यथा

अटल पूर्णांक pcf2127_i2c_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम pcf2127_i2c_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_SPI_MASTER)

अटल काष्ठा spi_driver pcf2127_spi_driver;

अटल पूर्णांक pcf2127_spi_probe(काष्ठा spi_device *spi)
अणु
	अटल स्थिर काष्ठा regmap_config config = अणु
		.reg_bits = 8,
		.val_bits = 8,
		.पढ़ो_flag_mask = 0xa0,
		.ग_लिखो_flag_mask = 0x20,
		.max_रेजिस्टर = 0x1d,
	पूर्ण;
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "%s: regmap allocation failed: %ld\n",
			__func__, PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस pcf2127_probe(&spi->dev, regmap, spi->irq,
			     pcf2127_spi_driver.driver.name,
			     spi_get_device_id(spi)->driver_data);
पूर्ण

अटल स्थिर काष्ठा spi_device_id pcf2127_spi_id[] = अणु
	अणु "pcf2127", 1 पूर्ण,
	अणु "pcf2129", 0 पूर्ण,
	अणु "pca2129", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, pcf2127_spi_id);

अटल काष्ठा spi_driver pcf2127_spi_driver = अणु
	.driver		= अणु
		.name	= "rtc-pcf2127-spi",
		.of_match_table = of_match_ptr(pcf2127_of_match),
	पूर्ण,
	.probe		= pcf2127_spi_probe,
	.id_table	= pcf2127_spi_id,
पूर्ण;

अटल पूर्णांक pcf2127_spi_रेजिस्टर_driver(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&pcf2127_spi_driver);
पूर्ण

अटल व्योम pcf2127_spi_unरेजिस्टर_driver(व्योम)
अणु
	spi_unरेजिस्टर_driver(&pcf2127_spi_driver);
पूर्ण

#अन्यथा

अटल पूर्णांक pcf2127_spi_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल व्योम pcf2127_spi_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init pcf2127_init(व्योम)
अणु
	पूर्णांक ret;

	ret = pcf2127_i2c_रेजिस्टर_driver();
	अगर (ret) अणु
		pr_err("Failed to register pcf2127 i2c driver: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = pcf2127_spi_रेजिस्टर_driver();
	अगर (ret) अणु
		pr_err("Failed to register pcf2127 spi driver: %d\n", ret);
		pcf2127_i2c_unरेजिस्टर_driver();
	पूर्ण

	वापस ret;
पूर्ण
module_init(pcf2127_init)

अटल व्योम __निकास pcf2127_निकास(व्योम)
अणु
	pcf2127_spi_unरेजिस्टर_driver();
	pcf2127_i2c_unरेजिस्टर_driver();
पूर्ण
module_निकास(pcf2127_निकास)

MODULE_AUTHOR("Renaud Cerrato <r.cerrato@til-technologies.fr>");
MODULE_DESCRIPTION("NXP PCF2127/29 RTC driver");
MODULE_LICENSE("GPL v2");
