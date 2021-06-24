<शैली गुरु>
/*
 * Realtek RTD129x RTC
 *
 * Copyright (c) 2017 Andreas Fथअrber
 *
 * SPDX-License-Identअगरier: GPL-2.0+
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/spinlock.h>

#घोषणा RTD_RTCSEC		0x00
#घोषणा RTD_RTCMIN		0x04
#घोषणा RTD_RTCHR		0x08
#घोषणा RTD_RTCDATE1		0x0c
#घोषणा RTD_RTCDATE2		0x10
#घोषणा RTD_RTCACR		0x28
#घोषणा RTD_RTCEN		0x2c
#घोषणा RTD_RTCCR		0x30

#घोषणा RTD_RTCSEC_RTCSEC_MASK		0x7f

#घोषणा RTD_RTCMIN_RTCMIN_MASK		0x3f

#घोषणा RTD_RTCHR_RTCHR_MASK		0x1f

#घोषणा RTD_RTCDATE1_RTCDATE1_MASK	0xff

#घोषणा RTD_RTCDATE2_RTCDATE2_MASK	0x7f

#घोषणा RTD_RTCACR_RTCPWR		BIT(7)

#घोषणा RTD_RTCEN_RTCEN_MASK		0xff

#घोषणा RTD_RTCCR_RTCRST		BIT(6)

काष्ठा rtd119x_rtc अणु
	व्योम __iomem *base;
	काष्ठा clk *clk;
	काष्ठा rtc_device *rtcdev;
	अचिन्हित पूर्णांक base_year;
पूर्ण;

अटल अंतरभूत पूर्णांक rtd119x_rtc_days_in_year(पूर्णांक year)
अणु
	वापस 365 + (is_leap_year(year) ? 1 : 0);
पूर्ण

अटल व्योम rtd119x_rtc_reset(काष्ठा device *dev)
अणु
	काष्ठा rtd119x_rtc *data = dev_get_drvdata(dev);
	u32 val;

	val = पढ़ोl_relaxed(data->base + RTD_RTCCR);
	val |= RTD_RTCCR_RTCRST;
	ग_लिखोl_relaxed(val, data->base + RTD_RTCCR);

	val &= ~RTD_RTCCR_RTCRST;
	ग_लिखोl(val, data->base + RTD_RTCCR);
पूर्ण

अटल व्योम rtd119x_rtc_set_enabled(काष्ठा device *dev, bool enable)
अणु
	काष्ठा rtd119x_rtc *data = dev_get_drvdata(dev);
	u32 val;

	val = पढ़ोl_relaxed(data->base + RTD_RTCEN);
	अगर (enable) अणु
		अगर ((val & RTD_RTCEN_RTCEN_MASK) == 0x5a)
			वापस;
		ग_लिखोl_relaxed(0x5a, data->base + RTD_RTCEN);
	पूर्ण अन्यथा अणु
		ग_लिखोl_relaxed(0, data->base + RTD_RTCEN);
	पूर्ण
पूर्ण

अटल पूर्णांक rtd119x_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtd119x_rtc *data = dev_get_drvdata(dev);
	s32 day;
	u32 sec;
	अचिन्हित पूर्णांक year;
	पूर्णांक tries = 0;

	जबतक (true) अणु
		पंचांग->पंचांग_sec = (पढ़ोl_relaxed(data->base + RTD_RTCSEC) & RTD_RTCSEC_RTCSEC_MASK) >> 1;
		पंचांग->पंचांग_min  = पढ़ोl_relaxed(data->base + RTD_RTCMIN) & RTD_RTCMIN_RTCMIN_MASK;
		पंचांग->पंचांग_hour = पढ़ोl_relaxed(data->base + RTD_RTCHR) & RTD_RTCHR_RTCHR_MASK;
		day  =  पढ़ोl_relaxed(data->base + RTD_RTCDATE1) & RTD_RTCDATE1_RTCDATE1_MASK;
		day |= (पढ़ोl_relaxed(data->base + RTD_RTCDATE2) & RTD_RTCDATE2_RTCDATE2_MASK) << 8;
		sec  = (पढ़ोl_relaxed(data->base + RTD_RTCSEC) & RTD_RTCSEC_RTCSEC_MASK) >> 1;
		tries++;

		अगर (sec == पंचांग->पंचांग_sec)
			अवरोध;

		अगर (tries >= 3)
			वापस -EINVAL;
	पूर्ण
	अगर (tries > 1)
		dev_dbg(dev, "%s: needed %i tries\n", __func__, tries);

	year = data->base_year;
	जबतक (day >= rtd119x_rtc_days_in_year(year)) अणु
		day -= rtd119x_rtc_days_in_year(year);
		year++;
	पूर्ण
	पंचांग->पंचांग_year = year - 1900;
	पंचांग->पंचांग_yday = day;

	पंचांग->पंचांग_mon = 0;
	जबतक (day >= rtc_month_days(पंचांग->पंचांग_mon, year)) अणु
		day -= rtc_month_days(पंचांग->पंचांग_mon, year);
		पंचांग->पंचांग_mon++;
	पूर्ण
	पंचांग->पंचांग_mday = day + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक rtd119x_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा rtd119x_rtc *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक day;
	पूर्णांक i;

	अगर (1900 + पंचांग->पंचांग_year < data->base_year)
		वापस -EINVAL;

	day = 0;
	क्रम (i = data->base_year; i < 1900 + पंचांग->पंचांग_year; i++)
		day += rtd119x_rtc_days_in_year(i);

	day += पंचांग->पंचांग_yday;
	अगर (day > 0x7fff)
		वापस -EINVAL;

	rtd119x_rtc_set_enabled(dev, false);

	ग_लिखोl_relaxed((पंचांग->पंचांग_sec << 1) & RTD_RTCSEC_RTCSEC_MASK, data->base + RTD_RTCSEC);
	ग_लिखोl_relaxed(पंचांग->पंचांग_min & RTD_RTCMIN_RTCMIN_MASK, data->base + RTD_RTCMIN);
	ग_लिखोl_relaxed(पंचांग->पंचांग_hour & RTD_RTCHR_RTCHR_MASK, data->base + RTD_RTCHR);
	ग_लिखोl_relaxed(day & RTD_RTCDATE1_RTCDATE1_MASK, data->base + RTD_RTCDATE1);
	ग_लिखोl_relaxed((day >> 8) & RTD_RTCDATE2_RTCDATE2_MASK, data->base + RTD_RTCDATE2);

	rtd119x_rtc_set_enabled(dev, true);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rtd119x_rtc_ops = अणु
	.पढ़ो_समय	= rtd119x_rtc_पढ़ो_समय,
	.set_समय	= rtd119x_rtc_set_समय,
पूर्ण;

अटल स्थिर काष्ठा of_device_id rtd119x_rtc_dt_ids[] = अणु
	 अणु .compatible = "realtek,rtd1295-rtc" पूर्ण,
	 अणु पूर्ण
पूर्ण;

अटल पूर्णांक rtd119x_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtd119x_rtc *data;
	u32 val;
	पूर्णांक ret;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, data);
	data->base_year = 2014;

	data->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(data->base))
		वापस PTR_ERR(data->base);

	data->clk = of_clk_get(pdev->dev.of_node, 0);
	अगर (IS_ERR(data->clk))
		वापस PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	अगर (ret) अणु
		clk_put(data->clk);
		वापस ret;
	पूर्ण

	val = पढ़ोl_relaxed(data->base + RTD_RTCACR);
	अगर (!(val & RTD_RTCACR_RTCPWR)) अणु
		ग_लिखोl_relaxed(RTD_RTCACR_RTCPWR, data->base + RTD_RTCACR);

		rtd119x_rtc_reset(&pdev->dev);

		ग_लिखोl_relaxed(0, data->base + RTD_RTCMIN);
		ग_लिखोl_relaxed(0, data->base + RTD_RTCHR);
		ग_लिखोl_relaxed(0, data->base + RTD_RTCDATE1);
		ग_लिखोl_relaxed(0, data->base + RTD_RTCDATE2);
	पूर्ण

	rtd119x_rtc_set_enabled(&pdev->dev, true);

	data->rtcdev = devm_rtc_device_रेजिस्टर(&pdev->dev, "rtc",
						&rtd119x_rtc_ops, THIS_MODULE);
	अगर (IS_ERR(data->rtcdev)) अणु
		dev_err(&pdev->dev, "failed to register rtc device");
		clk_disable_unprepare(data->clk);
		clk_put(data->clk);
		वापस PTR_ERR(data->rtcdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rtd119x_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtd119x_rtc *data = platक्रमm_get_drvdata(pdev);

	rtd119x_rtc_set_enabled(&pdev->dev, false);

	clk_disable_unprepare(data->clk);
	clk_put(data->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver rtd119x_rtc_driver = अणु
	.probe = rtd119x_rtc_probe,
	.हटाओ = rtd119x_rtc_हटाओ,
	.driver = अणु
		.name = "rtd1295-rtc",
		.of_match_table	= rtd119x_rtc_dt_ids,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(rtd119x_rtc_driver);
