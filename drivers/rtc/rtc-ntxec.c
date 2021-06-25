<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * The Netronix embedded controller is a microcontroller found in some
 * e-book पढ़ोers deचिन्हित by the original design manufacturer Netronix, Inc.
 * It contains RTC, battery monitoring, प्रणाली घातer management, and PWM
 * functionality.
 *
 * This driver implements access to the RTC समय and date.
 *
 * Copyright 2020 Jonathan Neuschथअfer <j.neuschaefer@gmx.net>
 */

#समावेश <linux/mfd/ntxec.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/types.h>

काष्ठा ntxec_rtc अणु
	काष्ठा device *dev;
	काष्ठा ntxec *ec;
पूर्ण;

#घोषणा NTXEC_REG_WRITE_YEAR	0x10
#घोषणा NTXEC_REG_WRITE_MONTH	0x11
#घोषणा NTXEC_REG_WRITE_DAY	0x12
#घोषणा NTXEC_REG_WRITE_HOUR	0x13
#घोषणा NTXEC_REG_WRITE_MINUTE	0x14
#घोषणा NTXEC_REG_WRITE_SECOND	0x15

#घोषणा NTXEC_REG_READ_YEAR_MONTH	0x20
#घोषणा NTXEC_REG_READ_MDAY_HOUR	0x21
#घोषणा NTXEC_REG_READ_MINUTE_SECOND	0x23

अटल पूर्णांक ntxec_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ntxec_rtc *rtc = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक value;
	पूर्णांक res;

retry:
	res = regmap_पढ़ो(rtc->ec->regmap, NTXEC_REG_READ_MINUTE_SECOND, &value);
	अगर (res < 0)
		वापस res;

	पंचांग->पंचांग_min = value >> 8;
	पंचांग->पंचांग_sec = value & 0xff;

	res = regmap_पढ़ो(rtc->ec->regmap, NTXEC_REG_READ_MDAY_HOUR, &value);
	अगर (res < 0)
		वापस res;

	पंचांग->पंचांग_mday = value >> 8;
	पंचांग->पंचांग_hour = value & 0xff;

	res = regmap_पढ़ो(rtc->ec->regmap, NTXEC_REG_READ_YEAR_MONTH, &value);
	अगर (res < 0)
		वापस res;

	पंचांग->पंचांग_year = (value >> 8) + 100;
	पंचांग->पंचांग_mon = (value & 0xff) - 1;

	/*
	 * Read the minutes/seconds field again. If it changed since the first
	 * पढ़ो, we can't assume that the values पढ़ो so far are consistent,
	 * and should start from the beginning.
	 */
	res = regmap_पढ़ो(rtc->ec->regmap, NTXEC_REG_READ_MINUTE_SECOND, &value);
	अगर (res < 0)
		वापस res;

	अगर (पंचांग->पंचांग_min != value >> 8 || पंचांग->पंचांग_sec != (value & 0xff))
		जाओ retry;

	वापस 0;
पूर्ण

अटल पूर्णांक ntxec_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा ntxec_rtc *rtc = dev_get_drvdata(dev);

	/*
	 * To aव्योम समय overflows जबतक we're writing the full date/समय,
	 * set the seconds field to zero beक्रमe करोing anything अन्यथा. For the
	 * next 59 seconds (plus however दीर्घ it takes until the RTC's next
	 * update of the second field), the seconds field will not overflow
	 * पूर्णांकo the other fields.
	 */
	काष्ठा reg_sequence regs[] = अणु
		अणु NTXEC_REG_WRITE_SECOND, ntxec_reg8(0) पूर्ण,
		अणु NTXEC_REG_WRITE_YEAR, ntxec_reg8(पंचांग->पंचांग_year - 100) पूर्ण,
		अणु NTXEC_REG_WRITE_MONTH, ntxec_reg8(पंचांग->पंचांग_mon + 1) पूर्ण,
		अणु NTXEC_REG_WRITE_DAY, ntxec_reg8(पंचांग->पंचांग_mday) पूर्ण,
		अणु NTXEC_REG_WRITE_HOUR, ntxec_reg8(पंचांग->पंचांग_hour) पूर्ण,
		अणु NTXEC_REG_WRITE_MINUTE, ntxec_reg8(पंचांग->पंचांग_min) पूर्ण,
		अणु NTXEC_REG_WRITE_SECOND, ntxec_reg8(पंचांग->पंचांग_sec) पूर्ण,
	पूर्ण;

	वापस regmap_multi_reg_ग_लिखो(rtc->ec->regmap, regs, ARRAY_SIZE(regs));
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops ntxec_rtc_ops = अणु
	.पढ़ो_समय = ntxec_पढ़ो_समय,
	.set_समय = ntxec_set_समय,
पूर्ण;

अटल पूर्णांक ntxec_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *dev;
	काष्ठा ntxec_rtc *rtc;

	pdev->dev.of_node = pdev->dev.parent->of_node;

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->dev = &pdev->dev;
	rtc->ec = dev_get_drvdata(pdev->dev.parent);
	platक्रमm_set_drvdata(pdev, rtc);

	dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(dev))
		वापस PTR_ERR(dev);

	dev->ops = &ntxec_rtc_ops;
	dev->range_min = RTC_TIMESTAMP_BEGIN_2000;
	dev->range_max = 9025257599LL; /* 2255-12-31 23:59:59 */

	वापस devm_rtc_रेजिस्टर_device(dev);
पूर्ण

अटल काष्ठा platक्रमm_driver ntxec_rtc_driver = अणु
	.driver = अणु
		.name = "ntxec-rtc",
	पूर्ण,
	.probe = ntxec_rtc_probe,
पूर्ण;
module_platक्रमm_driver(ntxec_rtc_driver);

MODULE_AUTHOR("Jonathan Neuschथअfer <j.neuschaefer@gmx.net>");
MODULE_DESCRIPTION("RTC driver for Netronix EC");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ntxec-rtc");
