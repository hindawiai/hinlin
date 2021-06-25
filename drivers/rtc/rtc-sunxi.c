<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * An RTC driver क्रम Allwinner A10/A20
 *
 * Copyright (c) 2013, Carlo Caione <carlo.caione@gmail.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/types.h>

#घोषणा SUNXI_LOSC_CTRL				0x0000
#घोषणा SUNXI_LOSC_CTRL_RTC_HMS_ACC		BIT(8)
#घोषणा SUNXI_LOSC_CTRL_RTC_YMD_ACC		BIT(7)

#घोषणा SUNXI_RTC_YMD				0x0004

#घोषणा SUNXI_RTC_HMS				0x0008

#घोषणा SUNXI_ALRM_DHMS				0x000c

#घोषणा SUNXI_ALRM_EN				0x0014
#घोषणा SUNXI_ALRM_EN_CNT_EN			BIT(8)

#घोषणा SUNXI_ALRM_IRQ_EN			0x0018
#घोषणा SUNXI_ALRM_IRQ_EN_CNT_IRQ_EN		BIT(0)

#घोषणा SUNXI_ALRM_IRQ_STA			0x001c
#घोषणा SUNXI_ALRM_IRQ_STA_CNT_IRQ_PEND		BIT(0)

#घोषणा SUNXI_MASK_DH				0x0000001f
#घोषणा SUNXI_MASK_SM				0x0000003f
#घोषणा SUNXI_MASK_M				0x0000000f
#घोषणा SUNXI_MASK_LY				0x00000001
#घोषणा SUNXI_MASK_D				0x00000ffe
#घोषणा SUNXI_MASK_M				0x0000000f

#घोषणा SUNXI_GET(x, mask, shअगरt)		(((x) & ((mask) << (shअगरt))) \
							>> (shअगरt))

#घोषणा SUNXI_SET(x, mask, shअगरt)		(((x) & (mask)) << (shअगरt))

/*
 * Get date values
 */
#घोषणा SUNXI_DATE_GET_DAY_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_DH, 0)
#घोषणा SUNXI_DATE_GET_MON_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_M, 8)
#घोषणा SUNXI_DATE_GET_YEAR_VALUE(x, mask)	SUNXI_GET(x, mask, 16)

/*
 * Get समय values
 */
#घोषणा SUNXI_TIME_GET_SEC_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 0)
#घोषणा SUNXI_TIME_GET_MIN_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 8)
#घोषणा SUNXI_TIME_GET_HOUR_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_DH, 16)

/*
 * Get alarm values
 */
#घोषणा SUNXI_ALRM_GET_SEC_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 0)
#घोषणा SUNXI_ALRM_GET_MIN_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_SM, 8)
#घोषणा SUNXI_ALRM_GET_HOUR_VALUE(x)		SUNXI_GET(x, SUNXI_MASK_DH, 16)

/*
 * Set date values
 */
#घोषणा SUNXI_DATE_SET_DAY_VALUE(x)		SUNXI_DATE_GET_DAY_VALUE(x)
#घोषणा SUNXI_DATE_SET_MON_VALUE(x)		SUNXI_SET(x, SUNXI_MASK_M, 8)
#घोषणा SUNXI_DATE_SET_YEAR_VALUE(x, mask)	SUNXI_SET(x, mask, 16)
#घोषणा SUNXI_LEAP_SET_VALUE(x, shअगरt)		SUNXI_SET(x, SUNXI_MASK_LY, shअगरt)

/*
 * Set समय values
 */
#घोषणा SUNXI_TIME_SET_SEC_VALUE(x)		SUNXI_TIME_GET_SEC_VALUE(x)
#घोषणा SUNXI_TIME_SET_MIN_VALUE(x)		SUNXI_SET(x, SUNXI_MASK_SM, 8)
#घोषणा SUNXI_TIME_SET_HOUR_VALUE(x)		SUNXI_SET(x, SUNXI_MASK_DH, 16)

/*
 * Set alarm values
 */
#घोषणा SUNXI_ALRM_SET_SEC_VALUE(x)		SUNXI_ALRM_GET_SEC_VALUE(x)
#घोषणा SUNXI_ALRM_SET_MIN_VALUE(x)		SUNXI_SET(x, SUNXI_MASK_SM, 8)
#घोषणा SUNXI_ALRM_SET_HOUR_VALUE(x)		SUNXI_SET(x, SUNXI_MASK_DH, 16)
#घोषणा SUNXI_ALRM_SET_DAY_VALUE(x)		SUNXI_SET(x, SUNXI_MASK_D, 21)

/*
 * Time unit conversions
 */
#घोषणा SEC_IN_MIN				60
#घोषणा SEC_IN_HOUR				(60 * SEC_IN_MIN)
#घोषणा SEC_IN_DAY				(24 * SEC_IN_HOUR)

/*
 * The year parameter passed to the driver is usually an offset relative to
 * the year 1900. This macro is used to convert this offset to another one
 * relative to the minimum year allowed by the hardware.
 */
#घोषणा SUNXI_YEAR_OFF(x)			((x)->min - 1900)

/*
 * min and max year are arbitrary set considering the limited range of the
 * hardware रेजिस्टर field
 */
काष्ठा sunxi_rtc_data_year अणु
	अचिन्हित पूर्णांक min;		/* min year allowed */
	अचिन्हित पूर्णांक max;		/* max year allowed */
	अचिन्हित पूर्णांक mask;		/* mask क्रम the year field */
	अचिन्हित अक्षर leap_shअगरt;	/* bit shअगरt to get the leap year */
पूर्ण;

अटल स्थिर काष्ठा sunxi_rtc_data_year data_year_param[] = अणु
	[0] = अणु
		.min		= 2010,
		.max		= 2073,
		.mask		= 0x3f,
		.leap_shअगरt	= 22,
	पूर्ण,
	[1] = अणु
		.min		= 1970,
		.max		= 2225,
		.mask		= 0xff,
		.leap_shअगरt	= 24,
	पूर्ण,
पूर्ण;

काष्ठा sunxi_rtc_dev अणु
	काष्ठा rtc_device *rtc;
	काष्ठा device *dev;
	स्थिर काष्ठा sunxi_rtc_data_year *data_year;
	व्योम __iomem *base;
	पूर्णांक irq;
पूर्ण;

अटल irqवापस_t sunxi_rtc_alarmirq(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा sunxi_rtc_dev *chip = (काष्ठा sunxi_rtc_dev *) id;
	u32 val;

	val = पढ़ोl(chip->base + SUNXI_ALRM_IRQ_STA);

	अगर (val & SUNXI_ALRM_IRQ_STA_CNT_IRQ_PEND) अणु
		val |= SUNXI_ALRM_IRQ_STA_CNT_IRQ_PEND;
		ग_लिखोl(val, chip->base + SUNXI_ALRM_IRQ_STA);

		rtc_update_irq(chip->rtc, 1, RTC_AF | RTC_IRQF);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल व्योम sunxi_rtc_setaie(अचिन्हित पूर्णांक to, काष्ठा sunxi_rtc_dev *chip)
अणु
	u32 alrm_val = 0;
	u32 alrm_irq_val = 0;

	अगर (to) अणु
		alrm_val = पढ़ोl(chip->base + SUNXI_ALRM_EN);
		alrm_val |= SUNXI_ALRM_EN_CNT_EN;

		alrm_irq_val = पढ़ोl(chip->base + SUNXI_ALRM_IRQ_EN);
		alrm_irq_val |= SUNXI_ALRM_IRQ_EN_CNT_IRQ_EN;
	पूर्ण अन्यथा अणु
		ग_लिखोl(SUNXI_ALRM_IRQ_STA_CNT_IRQ_PEND,
				chip->base + SUNXI_ALRM_IRQ_STA);
	पूर्ण

	ग_लिखोl(alrm_val, chip->base + SUNXI_ALRM_EN);
	ग_लिखोl(alrm_irq_val, chip->base + SUNXI_ALRM_IRQ_EN);
पूर्ण

अटल पूर्णांक sunxi_rtc_getalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alrm_पंचांग = &wkalrm->समय;
	u32 alrm;
	u32 alrm_en;
	u32 date;

	alrm = पढ़ोl(chip->base + SUNXI_ALRM_DHMS);
	date = पढ़ोl(chip->base + SUNXI_RTC_YMD);

	alrm_पंचांग->पंचांग_sec = SUNXI_ALRM_GET_SEC_VALUE(alrm);
	alrm_पंचांग->पंचांग_min = SUNXI_ALRM_GET_MIN_VALUE(alrm);
	alrm_पंचांग->पंचांग_hour = SUNXI_ALRM_GET_HOUR_VALUE(alrm);

	alrm_पंचांग->पंचांग_mday = SUNXI_DATE_GET_DAY_VALUE(date);
	alrm_पंचांग->पंचांग_mon = SUNXI_DATE_GET_MON_VALUE(date);
	alrm_पंचांग->पंचांग_year = SUNXI_DATE_GET_YEAR_VALUE(date,
			chip->data_year->mask);

	alrm_पंचांग->पंचांग_mon -= 1;

	/*
	 * चयन from (data_year->min)-relative offset to
	 * a (1900)-relative one
	 */
	alrm_पंचांग->पंचांग_year += SUNXI_YEAR_OFF(chip->data_year);

	alrm_en = पढ़ोl(chip->base + SUNXI_ALRM_IRQ_EN);
	अगर (alrm_en & SUNXI_ALRM_EN_CNT_EN)
		wkalrm->enabled = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_rtc_समय_लो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	u32 date, समय;

	/*
	 * पढ़ो again in हाल it changes
	 */
	करो अणु
		date = पढ़ोl(chip->base + SUNXI_RTC_YMD);
		समय = पढ़ोl(chip->base + SUNXI_RTC_HMS);
	पूर्ण जबतक ((date != पढ़ोl(chip->base + SUNXI_RTC_YMD)) ||
		 (समय != पढ़ोl(chip->base + SUNXI_RTC_HMS)));

	rtc_पंचांग->पंचांग_sec  = SUNXI_TIME_GET_SEC_VALUE(समय);
	rtc_पंचांग->पंचांग_min  = SUNXI_TIME_GET_MIN_VALUE(समय);
	rtc_पंचांग->पंचांग_hour = SUNXI_TIME_GET_HOUR_VALUE(समय);

	rtc_पंचांग->पंचांग_mday = SUNXI_DATE_GET_DAY_VALUE(date);
	rtc_पंचांग->पंचांग_mon  = SUNXI_DATE_GET_MON_VALUE(date);
	rtc_पंचांग->पंचांग_year = SUNXI_DATE_GET_YEAR_VALUE(date,
					chip->data_year->mask);

	rtc_पंचांग->पंचांग_mon  -= 1;

	/*
	 * चयन from (data_year->min)-relative offset to
	 * a (1900)-relative one
	 */
	rtc_पंचांग->पंचांग_year += SUNXI_YEAR_OFF(chip->data_year);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_rtc_setalarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *wkalrm)
अणु
	काष्ठा sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	काष्ठा rtc_समय *alrm_पंचांग = &wkalrm->समय;
	काष्ठा rtc_समय पंचांग_now;
	u32 alrm;
	समय64_t dअगरf;
	अचिन्हित दीर्घ समय_gap;
	अचिन्हित दीर्घ समय_gap_day;
	अचिन्हित दीर्घ समय_gap_hour;
	अचिन्हित दीर्घ समय_gap_min;
	पूर्णांक ret;

	ret = sunxi_rtc_समय_लो(dev, &पंचांग_now);
	अगर (ret < 0) अणु
		dev_err(dev, "Error in getting time\n");
		वापस -EINVAL;
	पूर्ण

	dअगरf = rtc_पंचांग_sub(alrm_पंचांग, &पंचांग_now);
	अगर (dअगरf <= 0) अणु
		dev_err(dev, "Date to set in the past\n");
		वापस -EINVAL;
	पूर्ण

	अगर (dअगरf > 255 * SEC_IN_DAY) अणु
		dev_err(dev, "Day must be in the range 0 - 255\n");
		वापस -EINVAL;
	पूर्ण

	समय_gap = dअगरf;
	समय_gap_day = समय_gap / SEC_IN_DAY;
	समय_gap -= समय_gap_day * SEC_IN_DAY;
	समय_gap_hour = समय_gap / SEC_IN_HOUR;
	समय_gap -= समय_gap_hour * SEC_IN_HOUR;
	समय_gap_min = समय_gap / SEC_IN_MIN;
	समय_gap -= समय_gap_min * SEC_IN_MIN;

	sunxi_rtc_setaie(0, chip);
	ग_लिखोl(0, chip->base + SUNXI_ALRM_DHMS);
	usleep_range(100, 300);

	alrm = SUNXI_ALRM_SET_SEC_VALUE(समय_gap) |
		SUNXI_ALRM_SET_MIN_VALUE(समय_gap_min) |
		SUNXI_ALRM_SET_HOUR_VALUE(समय_gap_hour) |
		SUNXI_ALRM_SET_DAY_VALUE(समय_gap_day);
	ग_लिखोl(alrm, chip->base + SUNXI_ALRM_DHMS);

	ग_लिखोl(0, chip->base + SUNXI_ALRM_IRQ_EN);
	ग_लिखोl(SUNXI_ALRM_IRQ_EN_CNT_IRQ_EN, chip->base + SUNXI_ALRM_IRQ_EN);

	sunxi_rtc_setaie(wkalrm->enabled, chip);

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_rtc_रुको(काष्ठा sunxi_rtc_dev *chip, पूर्णांक offset,
			  अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक ms_समयout)
अणु
	स्थिर अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(ms_समयout);
	u32 reg;

	करो अणु
		reg = पढ़ोl(chip->base + offset);
		reg &= mask;

		अगर (reg == mask)
			वापस 0;

	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक sunxi_rtc_समय_रखो(काष्ठा device *dev, काष्ठा rtc_समय *rtc_पंचांग)
अणु
	काष्ठा sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	u32 date = 0;
	u32 समय = 0;
	अचिन्हित पूर्णांक year;

	/*
	 * the input rtc_पंचांग->पंचांग_year is the offset relative to 1900. We use
	 * the SUNXI_YEAR_OFF macro to rebase it with respect to the min year
	 * allowed by the hardware
	 */

	year = rtc_पंचांग->पंचांग_year + 1900;
	अगर (year < chip->data_year->min || year > chip->data_year->max) अणु
		dev_err(dev, "rtc only supports year in range %u - %u\n",
			chip->data_year->min, chip->data_year->max);
		वापस -EINVAL;
	पूर्ण

	rtc_पंचांग->पंचांग_year -= SUNXI_YEAR_OFF(chip->data_year);
	rtc_पंचांग->पंचांग_mon += 1;

	date = SUNXI_DATE_SET_DAY_VALUE(rtc_पंचांग->पंचांग_mday) |
		SUNXI_DATE_SET_MON_VALUE(rtc_पंचांग->पंचांग_mon)  |
		SUNXI_DATE_SET_YEAR_VALUE(rtc_पंचांग->पंचांग_year,
				chip->data_year->mask);

	अगर (is_leap_year(year))
		date |= SUNXI_LEAP_SET_VALUE(1, chip->data_year->leap_shअगरt);

	समय = SUNXI_TIME_SET_SEC_VALUE(rtc_पंचांग->पंचांग_sec)  |
		SUNXI_TIME_SET_MIN_VALUE(rtc_पंचांग->पंचांग_min)  |
		SUNXI_TIME_SET_HOUR_VALUE(rtc_पंचांग->पंचांग_hour);

	ग_लिखोl(0, chip->base + SUNXI_RTC_HMS);
	ग_लिखोl(0, chip->base + SUNXI_RTC_YMD);

	ग_लिखोl(समय, chip->base + SUNXI_RTC_HMS);

	/*
	 * After writing the RTC HH-MM-SS रेजिस्टर, the
	 * SUNXI_LOSC_CTRL_RTC_HMS_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	अगर (sunxi_rtc_रुको(chip, SUNXI_LOSC_CTRL,
				SUNXI_LOSC_CTRL_RTC_HMS_ACC, 50)) अणु
		dev_err(dev, "Failed to set rtc time.\n");
		वापस -1;
	पूर्ण

	ग_लिखोl(date, chip->base + SUNXI_RTC_YMD);

	/*
	 * After writing the RTC YY-MM-DD रेजिस्टर, the
	 * SUNXI_LOSC_CTRL_RTC_YMD_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	अगर (sunxi_rtc_रुको(chip, SUNXI_LOSC_CTRL,
				SUNXI_LOSC_CTRL_RTC_YMD_ACC, 50)) अणु
		dev_err(dev, "Failed to set rtc time.\n");
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sunxi_rtc_alarm_irq_enable(काष्ठा device *dev, अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा sunxi_rtc_dev *chip = dev_get_drvdata(dev);

	अगर (!enabled)
		sunxi_rtc_setaie(enabled, chip);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops sunxi_rtc_ops = अणु
	.पढ़ो_समय		= sunxi_rtc_समय_लो,
	.set_समय		= sunxi_rtc_समय_रखो,
	.पढ़ो_alarm		= sunxi_rtc_getalarm,
	.set_alarm		= sunxi_rtc_setalarm,
	.alarm_irq_enable	= sunxi_rtc_alarm_irq_enable
पूर्ण;

अटल स्थिर काष्ठा of_device_id sunxi_rtc_dt_ids[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-rtc", .data = &data_year_param[0] पूर्ण,
	अणु .compatible = "allwinner,sun7i-a20-rtc", .data = &data_year_param[1] पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sunxi_rtc_dt_ids);

अटल पूर्णांक sunxi_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sunxi_rtc_dev *chip;
	पूर्णांक ret;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, chip);
	chip->dev = &pdev->dev;

	chip->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(chip->rtc))
		वापस PTR_ERR(chip->rtc);

	chip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->base))
		वापस PTR_ERR(chip->base);

	chip->irq = platक्रमm_get_irq(pdev, 0);
	अगर (chip->irq < 0)
		वापस chip->irq;
	ret = devm_request_irq(&pdev->dev, chip->irq, sunxi_rtc_alarmirq,
			0, dev_name(&pdev->dev), chip);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not request IRQ\n");
		वापस ret;
	पूर्ण

	chip->data_year = of_device_get_match_data(&pdev->dev);
	अगर (!chip->data_year) अणु
		dev_err(&pdev->dev, "Unable to setup RTC data\n");
		वापस -ENODEV;
	पूर्ण

	/* clear the alarm count value */
	ग_लिखोl(0, chip->base + SUNXI_ALRM_DHMS);

	/* disable alarm, not generate irq pending */
	ग_लिखोl(0, chip->base + SUNXI_ALRM_EN);

	/* disable alarm week/cnt irq, unset to cpu */
	ग_लिखोl(0, chip->base + SUNXI_ALRM_IRQ_EN);

	/* clear alarm week/cnt irq pending */
	ग_लिखोl(SUNXI_ALRM_IRQ_STA_CNT_IRQ_PEND, chip->base +
			SUNXI_ALRM_IRQ_STA);

	chip->rtc->ops = &sunxi_rtc_ops;

	वापस devm_rtc_रेजिस्टर_device(chip->rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver sunxi_rtc_driver = अणु
	.probe		= sunxi_rtc_probe,
	.driver		= अणु
		.name		= "sunxi-rtc",
		.of_match_table = sunxi_rtc_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(sunxi_rtc_driver);

MODULE_DESCRIPTION("sunxi RTC driver");
MODULE_AUTHOR("Carlo Caione <carlo.caione@gmail.com>");
MODULE_LICENSE("GPL");
