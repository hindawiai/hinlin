<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the SGS-Thomson M48T35 Timekeeper RAM chip
 *
 * Copyright (C) 2000 Silicon Graphics, Inc.
 * Written by Ulf Carlsson (ulfc@engr.sgi.com)
 *
 * Copyright (C) 2008 Thomas Bogenकरोerfer
 *
 * Based on code written by Paul Gorपंचांगaker.
 */

#समावेश <linux/module.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcd.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>

काष्ठा m48t35_rtc अणु
	u8	pad[0x7ff8];    /* starts at 0x7ff8 */
#अगर_घोषित CONFIG_SGI_IP27
	u8	hour;
	u8	min;
	u8	sec;
	u8	control;
	u8	year;
	u8	month;
	u8	date;
	u8	day;
#अन्यथा
	u8	control;
	u8	sec;
	u8	min;
	u8	hour;
	u8	day;
	u8	date;
	u8	month;
	u8	year;
#पूर्ण_अगर
पूर्ण;

#घोषणा M48T35_RTC_SET		0x80
#घोषणा M48T35_RTC_READ		0x40

काष्ठा m48t35_priv अणु
	काष्ठा rtc_device *rtc;
	काष्ठा m48t35_rtc __iomem *reg;
	माप_प्रकार size;
	अचिन्हित दीर्घ baseaddr;
	spinlock_t lock;
पूर्ण;

अटल पूर्णांक m48t35_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा m48t35_priv *priv = dev_get_drvdata(dev);
	u8 control;

	/*
	 * Only the values that we पढ़ो from the RTC are set. We leave
	 * पंचांग_wday, पंचांग_yday and पंचांग_isdst untouched. Even though the
	 * RTC has RTC_DAY_OF_WEEK, we ignore it, as it is only updated
	 * by the RTC when initially set to a non-zero value.
	 */
	spin_lock_irq(&priv->lock);
	control = पढ़ोb(&priv->reg->control);
	ग_लिखोb(control | M48T35_RTC_READ, &priv->reg->control);
	पंचांग->पंचांग_sec = पढ़ोb(&priv->reg->sec);
	पंचांग->पंचांग_min = पढ़ोb(&priv->reg->min);
	पंचांग->पंचांग_hour = पढ़ोb(&priv->reg->hour);
	पंचांग->पंचांग_mday = पढ़ोb(&priv->reg->date);
	पंचांग->पंचांग_mon = पढ़ोb(&priv->reg->month);
	पंचांग->पंचांग_year = पढ़ोb(&priv->reg->year);
	ग_लिखोb(control, &priv->reg->control);
	spin_unlock_irq(&priv->lock);

	पंचांग->पंचांग_sec = bcd2bin(पंचांग->पंचांग_sec);
	पंचांग->पंचांग_min = bcd2bin(पंचांग->पंचांग_min);
	पंचांग->पंचांग_hour = bcd2bin(पंचांग->पंचांग_hour);
	पंचांग->पंचांग_mday = bcd2bin(पंचांग->पंचांग_mday);
	पंचांग->पंचांग_mon = bcd2bin(पंचांग->पंचांग_mon);
	पंचांग->पंचांग_year = bcd2bin(पंचांग->पंचांग_year);

	/*
	 * Account क्रम dअगरferences between how the RTC uses the values
	 * and how they are defined in a काष्ठा rtc_समय;
	 */
	पंचांग->पंचांग_year += 70;
	अगर (पंचांग->पंचांग_year <= 69)
		पंचांग->पंचांग_year += 100;

	पंचांग->पंचांग_mon--;
	वापस 0;
पूर्ण

अटल पूर्णांक m48t35_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा m48t35_priv *priv = dev_get_drvdata(dev);
	अचिन्हित अक्षर mon, day, hrs, min, sec;
	अचिन्हित पूर्णांक yrs;
	u8 control;

	yrs = पंचांग->पंचांग_year + 1900;
	mon = पंचांग->पंचांग_mon + 1;   /* पंचांग_mon starts at zero */
	day = पंचांग->पंचांग_mday;
	hrs = पंचांग->पंचांग_hour;
	min = पंचांग->पंचांग_min;
	sec = पंचांग->पंचांग_sec;

	अगर (yrs < 1970)
		वापस -EINVAL;

	yrs -= 1970;
	अगर (yrs > 255)    /* They are अचिन्हित */
		वापस -EINVAL;

	अगर (yrs > 169)
		वापस -EINVAL;

	अगर (yrs >= 100)
		yrs -= 100;

	sec = bin2bcd(sec);
	min = bin2bcd(min);
	hrs = bin2bcd(hrs);
	day = bin2bcd(day);
	mon = bin2bcd(mon);
	yrs = bin2bcd(yrs);

	spin_lock_irq(&priv->lock);
	control = पढ़ोb(&priv->reg->control);
	ग_लिखोb(control | M48T35_RTC_SET, &priv->reg->control);
	ग_लिखोb(yrs, &priv->reg->year);
	ग_लिखोb(mon, &priv->reg->month);
	ग_लिखोb(day, &priv->reg->date);
	ग_लिखोb(hrs, &priv->reg->hour);
	ग_लिखोb(min, &priv->reg->min);
	ग_लिखोb(sec, &priv->reg->sec);
	ग_लिखोb(control, &priv->reg->control);
	spin_unlock_irq(&priv->lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops m48t35_ops = अणु
	.पढ़ो_समय	= m48t35_पढ़ो_समय,
	.set_समय	= m48t35_set_समय,
पूर्ण;

अटल पूर्णांक m48t35_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा m48t35_priv *priv;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	priv = devm_kzalloc(&pdev->dev, माप(काष्ठा m48t35_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->size = resource_size(res);
	अगर (!devm_request_mem_region(&pdev->dev, res->start, priv->size,
				     pdev->name))
		वापस -EBUSY;

	priv->baseaddr = res->start;
	priv->reg = devm_ioremap(&pdev->dev, priv->baseaddr, priv->size);
	अगर (!priv->reg)
		वापस -ENOMEM;

	spin_lock_init(&priv->lock);

	platक्रमm_set_drvdata(pdev, priv);

	priv->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "m48t35",
				  &m48t35_ops, THIS_MODULE);
	वापस PTR_ERR_OR_ZERO(priv->rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver m48t35_platक्रमm_driver = अणु
	.driver		= अणु
		.name	= "rtc-m48t35",
	पूर्ण,
	.probe		= m48t35_probe,
पूर्ण;

module_platक्रमm_driver(m48t35_platक्रमm_driver);

MODULE_AUTHOR("Thomas Bogendoerfer <tsbogend@alpha.franken.de>");
MODULE_DESCRIPTION("M48T35 RTC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:rtc-m48t35");
