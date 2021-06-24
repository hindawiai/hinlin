<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Dallas DS1216 RTC driver
 *
 * Copyright (c) 2007 Thomas Bogenकरोerfer
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcd.h>
#समावेश <linux/slab.h>

काष्ठा ds1216_regs अणु
	u8 tsec;
	u8 sec;
	u8 min;
	u8 hour;
	u8 wday;
	u8 mday;
	u8 month;
	u8 year;
पूर्ण;

#घोषणा DS1216_HOUR_1224	(1 << 7)
#घोषणा DS1216_HOUR_AMPM	(1 << 5)

काष्ठा ds1216_priv अणु
	काष्ठा rtc_device *rtc;
	व्योम __iomem *ioaddr;
पूर्ण;

अटल स्थिर u8 magic[] = अणु
	0xc5, 0x3a, 0xa3, 0x5c, 0xc5, 0x3a, 0xa3, 0x5c
पूर्ण;

/*
 * Read the 64 bit we'd like to have - It a series
 * of 64 bits showing up in the LSB of the base रेजिस्टर.
 *
 */
अटल व्योम ds1216_पढ़ो(u8 __iomem *ioaddr, u8 *buf)
अणु
	अचिन्हित अक्षर c;
	पूर्णांक i, j;

	क्रम (i = 0; i < 8; i++) अणु
		c = 0;
		क्रम (j = 0; j < 8; j++)
			c |= (पढ़ोb(ioaddr) & 0x1) << j;
		buf[i] = c;
	पूर्ण
पूर्ण

अटल व्योम ds1216_ग_लिखो(u8 __iomem *ioaddr, स्थिर u8 *buf)
अणु
	अचिन्हित अक्षर c;
	पूर्णांक i, j;

	क्रम (i = 0; i < 8; i++) अणु
		c = buf[i];
		क्रम (j = 0; j < 8; j++) अणु
			ग_लिखोb(c, ioaddr);
			c = c >> 1;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ds1216_चयन_ds_to_घड़ी(u8 __iomem *ioaddr)
अणु
	/* Reset magic poपूर्णांकer */
	पढ़ोb(ioaddr);
	/* Write 64 bit magic to DS1216 */
	ds1216_ग_लिखो(ioaddr, magic);
पूर्ण

अटल पूर्णांक ds1216_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ds1216_priv *priv = dev_get_drvdata(dev);
	काष्ठा ds1216_regs regs;

	ds1216_चयन_ds_to_घड़ी(priv->ioaddr);
	ds1216_पढ़ो(priv->ioaddr, (u8 *)&regs);

	पंचांग->पंचांग_sec = bcd2bin(regs.sec);
	पंचांग->पंचांग_min = bcd2bin(regs.min);
	अगर (regs.hour & DS1216_HOUR_1224) अणु
		/* AM/PM mode */
		पंचांग->पंचांग_hour = bcd2bin(regs.hour & 0x1f);
		अगर (regs.hour & DS1216_HOUR_AMPM)
			पंचांग->पंचांग_hour += 12;
	पूर्ण अन्यथा
		पंचांग->पंचांग_hour = bcd2bin(regs.hour & 0x3f);
	पंचांग->पंचांग_wday = (regs.wday & 7) - 1;
	पंचांग->पंचांग_mday = bcd2bin(regs.mday & 0x3f);
	पंचांग->पंचांग_mon = bcd2bin(regs.month & 0x1f);
	पंचांग->पंचांग_year = bcd2bin(regs.year);
	अगर (पंचांग->पंचांग_year < 70)
		पंचांग->पंचांग_year += 100;

	वापस 0;
पूर्ण

अटल पूर्णांक ds1216_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ds1216_priv *priv = dev_get_drvdata(dev);
	काष्ठा ds1216_regs regs;

	ds1216_चयन_ds_to_घड़ी(priv->ioaddr);
	ds1216_पढ़ो(priv->ioaddr, (u8 *)&regs);

	regs.tsec = 0; /* clear 0.1 and 0.01 seconds */
	regs.sec = bin2bcd(पंचांग->पंचांग_sec);
	regs.min = bin2bcd(पंचांग->पंचांग_min);
	regs.hour &= DS1216_HOUR_1224;
	अगर (regs.hour && पंचांग->पंचांग_hour > 12) अणु
		regs.hour |= DS1216_HOUR_AMPM;
		पंचांग->पंचांग_hour -= 12;
	पूर्ण
	regs.hour |= bin2bcd(पंचांग->पंचांग_hour);
	regs.wday &= ~7;
	regs.wday |= पंचांग->पंचांग_wday;
	regs.mday = bin2bcd(पंचांग->पंचांग_mday);
	regs.month = bin2bcd(पंचांग->पंचांग_mon);
	regs.year = bin2bcd(पंचांग->पंचांग_year % 100);

	ds1216_चयन_ds_to_घड़ी(priv->ioaddr);
	ds1216_ग_लिखो(priv->ioaddr, (u8 *)&regs);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ds1216_rtc_ops = अणु
	.पढ़ो_समय	= ds1216_rtc_पढ़ो_समय,
	.set_समय	= ds1216_rtc_set_समय,
पूर्ण;

अटल पूर्णांक __init ds1216_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ds1216_priv *priv;
	u8 dummy[8];

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	priv->ioaddr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->ioaddr))
		वापस PTR_ERR(priv->ioaddr);

	priv->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "ds1216",
					&ds1216_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(priv->rtc))
		वापस PTR_ERR(priv->rtc);

	/* dummy पढ़ो to get घड़ी पूर्णांकo a known state */
	ds1216_पढ़ो(priv->ioaddr, dummy);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ds1216_rtc_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "rtc-ds1216",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(ds1216_rtc_platक्रमm_driver, ds1216_rtc_probe);

MODULE_AUTHOR("Thomas Bogendoerfer <tsbogend@alpha.franken.de>");
MODULE_DESCRIPTION("DS1216 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-ds1216");
