<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * An rtc driver क्रम the Dallas DS1742
 *
 * Copyright (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 *
 * Copyright (C) 2006 Torsten Ertbjerg Rयंत्रussen <tr@newtec.dk>
 *  - nvram size determined from resource
 *  - this ds1742 driver now supports ds1743.
 */

#समावेश <linux/bcd.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/rtc.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>

#घोषणा RTC_SIZE		8

#घोषणा RTC_CONTROL		0
#घोषणा RTC_CENTURY		0
#घोषणा RTC_SECONDS		1
#घोषणा RTC_MINUTES		2
#घोषणा RTC_HOURS		3
#घोषणा RTC_DAY			4
#घोषणा RTC_DATE		5
#घोषणा RTC_MONTH		6
#घोषणा RTC_YEAR		7

#घोषणा RTC_CENTURY_MASK	0x3f
#घोषणा RTC_SECONDS_MASK	0x7f
#घोषणा RTC_DAY_MASK		0x07

/* Bits in the Control/Century रेजिस्टर */
#घोषणा RTC_WRITE		0x80
#घोषणा RTC_READ		0x40

/* Bits in the Seconds रेजिस्टर */
#घोषणा RTC_STOP		0x80

/* Bits in the Day रेजिस्टर */
#घोषणा RTC_BATT_FLAG		0x80

काष्ठा rtc_plat_data अणु
	व्योम __iomem *ioaddr_nvram;
	व्योम __iomem *ioaddr_rtc;
	अचिन्हित दीर्घ last_jअगरfies;
पूर्ण;

अटल पूर्णांक ds1742_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr_rtc;
	u8 century;

	century = bin2bcd((पंचांग->पंचांग_year + 1900) / 100);

	ग_लिखोb(RTC_WRITE, ioaddr + RTC_CONTROL);

	ग_लिखोb(bin2bcd(पंचांग->पंचांग_year % 100), ioaddr + RTC_YEAR);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mon + 1), ioaddr + RTC_MONTH);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_wday) & RTC_DAY_MASK, ioaddr + RTC_DAY);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_mday), ioaddr + RTC_DATE);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_hour), ioaddr + RTC_HOURS);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_min), ioaddr + RTC_MINUTES);
	ग_लिखोb(bin2bcd(पंचांग->पंचांग_sec) & RTC_SECONDS_MASK, ioaddr + RTC_SECONDS);

	/* RTC_CENTURY and RTC_CONTROL share same रेजिस्टर */
	ग_लिखोb(RTC_WRITE | (century & RTC_CENTURY_MASK), ioaddr + RTC_CENTURY);
	ग_लिखोb(century & RTC_CENTURY_MASK, ioaddr + RTC_CONTROL);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1742_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtc_plat_data *pdata = dev_get_drvdata(dev);
	व्योम __iomem *ioaddr = pdata->ioaddr_rtc;
	अचिन्हित पूर्णांक year, month, day, hour, minute, second, week;
	अचिन्हित पूर्णांक century;

	/* give enough समय to update RTC in हाल of continuous पढ़ो */
	अगर (pdata->last_jअगरfies == jअगरfies)
		msleep(1);
	pdata->last_jअगरfies = jअगरfies;
	ग_लिखोb(RTC_READ, ioaddr + RTC_CONTROL);
	second = पढ़ोb(ioaddr + RTC_SECONDS) & RTC_SECONDS_MASK;
	minute = पढ़ोb(ioaddr + RTC_MINUTES);
	hour = पढ़ोb(ioaddr + RTC_HOURS);
	day = पढ़ोb(ioaddr + RTC_DATE);
	week = पढ़ोb(ioaddr + RTC_DAY) & RTC_DAY_MASK;
	month = पढ़ोb(ioaddr + RTC_MONTH);
	year = पढ़ोb(ioaddr + RTC_YEAR);
	century = पढ़ोb(ioaddr + RTC_CENTURY) & RTC_CENTURY_MASK;
	ग_लिखोb(0, ioaddr + RTC_CONTROL);
	पंचांग->पंचांग_sec = bcd2bin(second);
	पंचांग->पंचांग_min = bcd2bin(minute);
	पंचांग->पंचांग_hour = bcd2bin(hour);
	पंचांग->पंचांग_mday = bcd2bin(day);
	पंचांग->पंचांग_wday = bcd2bin(week);
	पंचांग->पंचांग_mon = bcd2bin(month) - 1;
	/* year is 1900 + पंचांग->पंचांग_year */
	पंचांग->पंचांग_year = bcd2bin(year) + bcd2bin(century) * 100 - 1900;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1742_rtc_ops = अणु
	.पढ़ो_समय	= ds1742_rtc_पढ़ो_समय,
	.set_समय	= ds1742_rtc_set_समय,
पूर्ण;

अटल पूर्णांक ds1742_nvram_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
			     माप_प्रकार bytes)
अणु
	काष्ठा rtc_plat_data *pdata = priv;
	व्योम __iomem *ioaddr = pdata->ioaddr_nvram;
	u8 *buf = val;

	क्रम (; bytes; bytes--)
		*buf++ = पढ़ोb(ioaddr + pos++);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1742_nvram_ग_लिखो(व्योम *priv, अचिन्हित पूर्णांक pos, व्योम *val,
			      माप_प्रकार bytes)
अणु
	काष्ठा rtc_plat_data *pdata = priv;
	व्योम __iomem *ioaddr = pdata->ioaddr_nvram;
	u8 *buf = val;

	क्रम (; bytes; bytes--)
		ग_लिखोb(*buf++, ioaddr + pos++);
	वापस 0;
पूर्ण

अटल पूर्णांक ds1742_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक cen, sec;
	काष्ठा rtc_plat_data *pdata;
	व्योम __iomem *ioaddr;
	पूर्णांक ret = 0;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.name = "ds1742_nvram",
		.reg_पढ़ो = ds1742_nvram_पढ़ो,
		.reg_ग_लिखो = ds1742_nvram_ग_लिखो,
	पूर्ण;


	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ioaddr = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ioaddr))
		वापस PTR_ERR(ioaddr);

	pdata->ioaddr_nvram = ioaddr;
	pdata->ioaddr_rtc = ioaddr + resource_size(res) - RTC_SIZE;

	nvmem_cfg.size = resource_size(res) - RTC_SIZE;
	nvmem_cfg.priv = pdata;

	/* turn RTC on अगर it was not on */
	ioaddr = pdata->ioaddr_rtc;
	sec = पढ़ोb(ioaddr + RTC_SECONDS);
	अगर (sec & RTC_STOP) अणु
		sec &= RTC_SECONDS_MASK;
		cen = पढ़ोb(ioaddr + RTC_CENTURY) & RTC_CENTURY_MASK;
		ग_लिखोb(RTC_WRITE, ioaddr + RTC_CONTROL);
		ग_लिखोb(sec, ioaddr + RTC_SECONDS);
		ग_लिखोb(cen & RTC_CENTURY_MASK, ioaddr + RTC_CONTROL);
	पूर्ण
	अगर (!(पढ़ोb(ioaddr + RTC_DAY) & RTC_BATT_FLAG))
		dev_warn(&pdev->dev, "voltage-low detected.\n");

	pdata->last_jअगरfies = jअगरfies;
	platक्रमm_set_drvdata(pdev, pdata);

	rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc))
		वापस PTR_ERR(rtc);

	rtc->ops = &ds1742_rtc_ops;

	ret = devm_rtc_रेजिस्टर_device(rtc);
	अगर (ret)
		वापस ret;

	devm_rtc_nvmem_रेजिस्टर(rtc, &nvmem_cfg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused ds1742_rtc_of_match[] = अणु
	अणु .compatible = "maxim,ds1742", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1742_rtc_of_match);

अटल काष्ठा platक्रमm_driver ds1742_rtc_driver = अणु
	.probe		= ds1742_rtc_probe,
	.driver		= अणु
		.name	= "rtc-ds1742",
		.of_match_table = of_match_ptr(ds1742_rtc_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ds1742_rtc_driver);

MODULE_AUTHOR("Atsushi Nemoto <anemo@mba.ocn.ne.jp>");
MODULE_DESCRIPTION("Dallas DS1742 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-ds1742");
