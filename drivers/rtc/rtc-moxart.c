<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MOXA ART RTC driver.
 *
 * Copyright (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmail.com>
 *
 * Based on code from
 * Moxa Technology Co., Ltd. <www.moxa.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#घोषणा GPIO_RTC_RESERVED			0x0C
#घोषणा GPIO_RTC_DATA_SET			0x10
#घोषणा GPIO_RTC_DATA_CLEAR			0x14
#घोषणा GPIO_RTC_PIN_PULL_ENABLE		0x18
#घोषणा GPIO_RTC_PIN_PULL_TYPE			0x1C
#घोषणा GPIO_RTC_INT_ENABLE			0x20
#घोषणा GPIO_RTC_INT_RAW_STATE			0x24
#घोषणा GPIO_RTC_INT_MASKED_STATE		0x28
#घोषणा GPIO_RTC_INT_MASK			0x2C
#घोषणा GPIO_RTC_INT_CLEAR			0x30
#घोषणा GPIO_RTC_INT_TRIGGER			0x34
#घोषणा GPIO_RTC_INT_BOTH			0x38
#घोषणा GPIO_RTC_INT_RISE_NEG			0x3C
#घोषणा GPIO_RTC_BOUNCE_ENABLE			0x40
#घोषणा GPIO_RTC_BOUNCE_PRE_SCALE		0x44
#घोषणा GPIO_RTC_PROTECT_W			0x8E
#घोषणा GPIO_RTC_PROTECT_R			0x8F
#घोषणा GPIO_RTC_YEAR_W				0x8C
#घोषणा GPIO_RTC_YEAR_R				0x8D
#घोषणा GPIO_RTC_DAY_W				0x8A
#घोषणा GPIO_RTC_DAY_R				0x8B
#घोषणा GPIO_RTC_MONTH_W			0x88
#घोषणा GPIO_RTC_MONTH_R			0x89
#घोषणा GPIO_RTC_DATE_W				0x86
#घोषणा GPIO_RTC_DATE_R				0x87
#घोषणा GPIO_RTC_HOURS_W			0x84
#घोषणा GPIO_RTC_HOURS_R			0x85
#घोषणा GPIO_RTC_MINUTES_W			0x82
#घोषणा GPIO_RTC_MINUTES_R			0x83
#घोषणा GPIO_RTC_SECONDS_W			0x80
#घोषणा GPIO_RTC_SECONDS_R			0x81
#घोषणा GPIO_RTC_DELAY_TIME			8

काष्ठा moxart_rtc अणु
	काष्ठा rtc_device *rtc;
	spinlock_t rtc_lock;
	पूर्णांक gpio_data, gpio_sclk, gpio_reset;
पूर्ण;

अटल पूर्णांक day_of_year[12] =	अणु 0, 31, 59, 90, 120, 151, 181,
				  212, 243, 273, 304, 334 पूर्ण;

अटल व्योम moxart_rtc_ग_लिखो_byte(काष्ठा device *dev, u8 data)
अणु
	काष्ठा moxart_rtc *moxart_rtc = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++, data >>= 1) अणु
		gpio_set_value(moxart_rtc->gpio_sclk, 0);
		gpio_set_value(moxart_rtc->gpio_data, ((data & 1) == 1));
		udelay(GPIO_RTC_DELAY_TIME);
		gpio_set_value(moxart_rtc->gpio_sclk, 1);
		udelay(GPIO_RTC_DELAY_TIME);
	पूर्ण
पूर्ण

अटल u8 moxart_rtc_पढ़ो_byte(काष्ठा device *dev)
अणु
	काष्ठा moxart_rtc *moxart_rtc = dev_get_drvdata(dev);
	पूर्णांक i;
	u8 data = 0;

	क्रम (i = 0; i < 8; i++) अणु
		gpio_set_value(moxart_rtc->gpio_sclk, 0);
		udelay(GPIO_RTC_DELAY_TIME);
		gpio_set_value(moxart_rtc->gpio_sclk, 1);
		udelay(GPIO_RTC_DELAY_TIME);
		अगर (gpio_get_value(moxart_rtc->gpio_data))
			data |= (1 << i);
		udelay(GPIO_RTC_DELAY_TIME);
	पूर्ण
	वापस data;
पूर्ण

अटल u8 moxart_rtc_पढ़ो_रेजिस्टर(काष्ठा device *dev, u8 cmd)
अणु
	काष्ठा moxart_rtc *moxart_rtc = dev_get_drvdata(dev);
	u8 data;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	gpio_direction_output(moxart_rtc->gpio_data, 0);
	gpio_set_value(moxart_rtc->gpio_reset, 1);
	udelay(GPIO_RTC_DELAY_TIME);
	moxart_rtc_ग_लिखो_byte(dev, cmd);
	gpio_direction_input(moxart_rtc->gpio_data);
	udelay(GPIO_RTC_DELAY_TIME);
	data = moxart_rtc_पढ़ो_byte(dev);
	gpio_set_value(moxart_rtc->gpio_sclk, 0);
	gpio_set_value(moxart_rtc->gpio_reset, 0);
	udelay(GPIO_RTC_DELAY_TIME);

	local_irq_restore(flags);

	वापस data;
पूर्ण

अटल व्योम moxart_rtc_ग_लिखो_रेजिस्टर(काष्ठा device *dev, u8 cmd, u8 data)
अणु
	काष्ठा moxart_rtc *moxart_rtc = dev_get_drvdata(dev);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	gpio_direction_output(moxart_rtc->gpio_data, 0);
	gpio_set_value(moxart_rtc->gpio_reset, 1);
	udelay(GPIO_RTC_DELAY_TIME);
	moxart_rtc_ग_लिखो_byte(dev, cmd);
	moxart_rtc_ग_लिखो_byte(dev, data);
	gpio_set_value(moxart_rtc->gpio_sclk, 0);
	gpio_set_value(moxart_rtc->gpio_reset, 0);
	udelay(GPIO_RTC_DELAY_TIME);

	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक moxart_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा moxart_rtc *moxart_rtc = dev_get_drvdata(dev);

	spin_lock_irq(&moxart_rtc->rtc_lock);

	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_PROTECT_W, 0);
	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_YEAR_W,
				  (((पंचांग->पंचांग_year - 100) / 10) << 4) |
				  ((पंचांग->पंचांग_year - 100) % 10));

	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_MONTH_W,
				  (((पंचांग->पंचांग_mon + 1) / 10) << 4) |
				  ((पंचांग->पंचांग_mon + 1) % 10));

	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_DATE_W,
				  ((पंचांग->पंचांग_mday / 10) << 4) |
				  (पंचांग->पंचांग_mday % 10));

	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_HOURS_W,
				  ((पंचांग->पंचांग_hour / 10) << 4) |
				  (पंचांग->पंचांग_hour % 10));

	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_MINUTES_W,
				  ((पंचांग->पंचांग_min / 10) << 4) |
				  (पंचांग->पंचांग_min % 10));

	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_SECONDS_W,
				  ((पंचांग->पंचांग_sec / 10) << 4) |
				  (पंचांग->पंचांग_sec % 10));

	moxart_rtc_ग_लिखो_रेजिस्टर(dev, GPIO_RTC_PROTECT_W, 0x80);

	spin_unlock_irq(&moxart_rtc->rtc_lock);

	dev_dbg(dev, "%s: success tm_year=%d tm_mon=%d\n"
		"tm_mday=%d tm_hour=%d tm_min=%d tm_sec=%d\n",
		__func__, पंचांग->पंचांग_year, पंचांग->पंचांग_mon, पंचांग->पंचांग_mday,
		पंचांग->पंचांग_hour, पंचांग->पंचांग_min, पंचांग->पंचांग_sec);

	वापस 0;
पूर्ण

अटल पूर्णांक moxart_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा moxart_rtc *moxart_rtc = dev_get_drvdata(dev);
	अचिन्हित अक्षर v;

	spin_lock_irq(&moxart_rtc->rtc_lock);

	v = moxart_rtc_पढ़ो_रेजिस्टर(dev, GPIO_RTC_SECONDS_R);
	पंचांग->पंचांग_sec = (((v & 0x70) >> 4) * 10) + (v & 0x0F);

	v = moxart_rtc_पढ़ो_रेजिस्टर(dev, GPIO_RTC_MINUTES_R);
	पंचांग->पंचांग_min = (((v & 0x70) >> 4) * 10) + (v & 0x0F);

	v = moxart_rtc_पढ़ो_रेजिस्टर(dev, GPIO_RTC_HOURS_R);
	अगर (v & 0x80) अणु /* 12-hour mode */
		पंचांग->पंचांग_hour = (((v & 0x10) >> 4) * 10) + (v & 0x0F);
		अगर (v & 0x20) अणु /* PM mode */
			पंचांग->पंचांग_hour += 12;
			अगर (पंचांग->पंचांग_hour >= 24)
				पंचांग->पंचांग_hour = 0;
		पूर्ण
	पूर्ण अन्यथा अणु /* 24-hour mode */
		पंचांग->पंचांग_hour = (((v & 0x30) >> 4) * 10) + (v & 0x0F);
	पूर्ण

	v = moxart_rtc_पढ़ो_रेजिस्टर(dev, GPIO_RTC_DATE_R);
	पंचांग->पंचांग_mday = (((v & 0x30) >> 4) * 10) + (v & 0x0F);

	v = moxart_rtc_पढ़ो_रेजिस्टर(dev, GPIO_RTC_MONTH_R);
	पंचांग->पंचांग_mon = (((v & 0x10) >> 4) * 10) + (v & 0x0F);
	पंचांग->पंचांग_mon--;

	v = moxart_rtc_पढ़ो_रेजिस्टर(dev, GPIO_RTC_YEAR_R);
	पंचांग->पंचांग_year = (((v & 0xF0) >> 4) * 10) + (v & 0x0F);
	पंचांग->पंचांग_year += 100;
	अगर (पंचांग->पंचांग_year <= 69)
		पंचांग->पंचांग_year += 100;

	v = moxart_rtc_पढ़ो_रेजिस्टर(dev, GPIO_RTC_DAY_R);
	पंचांग->पंचांग_wday = (v & 0x0f) - 1;
	पंचांग->पंचांग_yday = day_of_year[पंचांग->पंचांग_mon];
	पंचांग->पंचांग_yday += (पंचांग->पंचांग_mday - 1);
	अगर (पंचांग->पंचांग_mon >= 2) अणु
		अगर (!(पंचांग->पंचांग_year % 4) && (पंचांग->पंचांग_year % 100))
			पंचांग->पंचांग_yday++;
	पूर्ण

	पंचांग->पंचांग_isdst = 0;

	spin_unlock_irq(&moxart_rtc->rtc_lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops moxart_rtc_ops = अणु
	.पढ़ो_समय	= moxart_rtc_पढ़ो_समय,
	.set_समय	= moxart_rtc_set_समय,
पूर्ण;

अटल पूर्णांक moxart_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा moxart_rtc *moxart_rtc;
	पूर्णांक ret = 0;

	moxart_rtc = devm_kzalloc(&pdev->dev, माप(*moxart_rtc), GFP_KERNEL);
	अगर (!moxart_rtc)
		वापस -ENOMEM;

	moxart_rtc->gpio_data = of_get_named_gpio(pdev->dev.of_node,
						  "gpio-rtc-data", 0);
	अगर (!gpio_is_valid(moxart_rtc->gpio_data)) अणु
		dev_err(&pdev->dev, "invalid gpio (data): %d\n",
			moxart_rtc->gpio_data);
		वापस moxart_rtc->gpio_data;
	पूर्ण

	moxart_rtc->gpio_sclk = of_get_named_gpio(pdev->dev.of_node,
						  "gpio-rtc-sclk", 0);
	अगर (!gpio_is_valid(moxart_rtc->gpio_sclk)) अणु
		dev_err(&pdev->dev, "invalid gpio (sclk): %d\n",
			moxart_rtc->gpio_sclk);
		वापस moxart_rtc->gpio_sclk;
	पूर्ण

	moxart_rtc->gpio_reset = of_get_named_gpio(pdev->dev.of_node,
						   "gpio-rtc-reset", 0);
	अगर (!gpio_is_valid(moxart_rtc->gpio_reset)) अणु
		dev_err(&pdev->dev, "invalid gpio (reset): %d\n",
			moxart_rtc->gpio_reset);
		वापस moxart_rtc->gpio_reset;
	पूर्ण

	spin_lock_init(&moxart_rtc->rtc_lock);
	platक्रमm_set_drvdata(pdev, moxart_rtc);

	ret = devm_gpio_request(&pdev->dev, moxart_rtc->gpio_data, "rtc_data");
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get rtc_data gpio\n");
		वापस ret;
	पूर्ण

	ret = devm_gpio_request_one(&pdev->dev, moxart_rtc->gpio_sclk,
				    GPIOF_सूची_OUT, "rtc_sclk");
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get rtc_sclk gpio\n");
		वापस ret;
	पूर्ण

	ret = devm_gpio_request_one(&pdev->dev, moxart_rtc->gpio_reset,
				    GPIOF_सूची_OUT, "rtc_reset");
	अगर (ret) अणु
		dev_err(&pdev->dev, "can't get rtc_reset gpio\n");
		वापस ret;
	पूर्ण

	moxart_rtc->rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, pdev->name,
						   &moxart_rtc_ops,
						   THIS_MODULE);
	अगर (IS_ERR(moxart_rtc->rtc)) अणु
		dev_err(&pdev->dev, "devm_rtc_device_register failed\n");
		वापस PTR_ERR(moxart_rtc->rtc);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id moxart_rtc_match[] = अणु
	अणु .compatible = "moxa,moxart-rtc" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, moxart_rtc_match);

अटल काष्ठा platक्रमm_driver moxart_rtc_driver = अणु
	.probe	= moxart_rtc_probe,
	.driver	= अणु
		.name		= "moxart-rtc",
		.of_match_table	= moxart_rtc_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(moxart_rtc_driver);

MODULE_DESCRIPTION("MOXART RTC driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonas Jensen <jonas.jensen@gmail.com>");
