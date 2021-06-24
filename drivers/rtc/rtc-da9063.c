<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Real समय घड़ी device driver क्रम DA9063
 * Copyright (C) 2013-2015  Dialog Semiconductor Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

#समावेश <linux/mfd/da9062/रेजिस्टरs.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>
#समावेश <linux/mfd/da9063/core.h>

#घोषणा YEARS_TO_DA9063(year)		((year) - 100)
#घोषणा MONTHS_TO_DA9063(month)		((month) + 1)
#घोषणा YEARS_FROM_DA9063(year)		((year) + 100)
#घोषणा MONTHS_FROM_DA9063(month)	((month) - 1)

क्रमागत अणु
	RTC_SEC	= 0,
	RTC_MIN	= 1,
	RTC_HOUR = 2,
	RTC_DAY	= 3,
	RTC_MONTH = 4,
	RTC_YEAR = 5,
	RTC_DATA_LEN
पूर्ण;

काष्ठा da9063_compatible_rtc_regmap अणु
	/* REGS */
	पूर्णांक rtc_enable_reg;
	पूर्णांक rtc_enable_32k_crystal_reg;
	पूर्णांक rtc_alarm_secs_reg;
	पूर्णांक rtc_alarm_year_reg;
	पूर्णांक rtc_count_secs_reg;
	पूर्णांक rtc_count_year_reg;
	पूर्णांक rtc_event_reg;
	/* MASKS */
	पूर्णांक rtc_enable_mask;
	पूर्णांक rtc_crystal_mask;
	पूर्णांक rtc_event_alarm_mask;
	पूर्णांक rtc_alarm_on_mask;
	पूर्णांक rtc_alarm_status_mask;
	पूर्णांक rtc_tick_on_mask;
	पूर्णांक rtc_पढ़ोy_to_पढ़ो_mask;
	पूर्णांक rtc_count_sec_mask;
	पूर्णांक rtc_count_min_mask;
	पूर्णांक rtc_count_hour_mask;
	पूर्णांक rtc_count_day_mask;
	पूर्णांक rtc_count_month_mask;
	पूर्णांक rtc_count_year_mask;
	/* ALARM CONFIG */
	पूर्णांक rtc_data_start;
	पूर्णांक rtc_alarm_len;
पूर्ण;

काष्ठा da9063_compatible_rtc अणु
	काष्ठा rtc_device *rtc_dev;
	काष्ठा rtc_समय alarm_समय;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config;
	bool rtc_sync;
पूर्ण;

अटल स्थिर काष्ठा da9063_compatible_rtc_regmap da9063_ad_regs = अणु
	/* REGS */
	.rtc_enable_reg             = DA9063_REG_CONTROL_E,
	.rtc_alarm_secs_reg         = DA9063_AD_REG_ALARM_MI,
	.rtc_alarm_year_reg         = DA9063_AD_REG_ALARM_Y,
	.rtc_count_secs_reg         = DA9063_REG_COUNT_S,
	.rtc_count_year_reg         = DA9063_REG_COUNT_Y,
	.rtc_event_reg              = DA9063_REG_EVENT_A,
	/* MASKS */
	.rtc_enable_mask            = DA9063_RTC_EN,
	.rtc_crystal_mask           = DA9063_CRYSTAL,
	.rtc_enable_32k_crystal_reg = DA9063_REG_EN_32K,
	.rtc_event_alarm_mask       = DA9063_E_ALARM,
	.rtc_alarm_on_mask          = DA9063_ALARM_ON,
	.rtc_alarm_status_mask      = DA9063_ALARM_STATUS_ALARM |
				      DA9063_ALARM_STATUS_TICK,
	.rtc_tick_on_mask           = DA9063_TICK_ON,
	.rtc_पढ़ोy_to_पढ़ो_mask     = DA9063_RTC_READ,
	.rtc_count_sec_mask         = DA9063_COUNT_SEC_MASK,
	.rtc_count_min_mask         = DA9063_COUNT_MIN_MASK,
	.rtc_count_hour_mask        = DA9063_COUNT_HOUR_MASK,
	.rtc_count_day_mask         = DA9063_COUNT_DAY_MASK,
	.rtc_count_month_mask       = DA9063_COUNT_MONTH_MASK,
	.rtc_count_year_mask        = DA9063_COUNT_YEAR_MASK,
	/* ALARM CONFIG */
	.rtc_data_start             = RTC_MIN,
	.rtc_alarm_len              = RTC_DATA_LEN - 1,
पूर्ण;

अटल स्थिर काष्ठा da9063_compatible_rtc_regmap da9063_bb_regs = अणु
	/* REGS */
	.rtc_enable_reg             = DA9063_REG_CONTROL_E,
	.rtc_alarm_secs_reg         = DA9063_BB_REG_ALARM_S,
	.rtc_alarm_year_reg         = DA9063_BB_REG_ALARM_Y,
	.rtc_count_secs_reg         = DA9063_REG_COUNT_S,
	.rtc_count_year_reg         = DA9063_REG_COUNT_Y,
	.rtc_event_reg              = DA9063_REG_EVENT_A,
	/* MASKS */
	.rtc_enable_mask            = DA9063_RTC_EN,
	.rtc_crystal_mask           = DA9063_CRYSTAL,
	.rtc_enable_32k_crystal_reg = DA9063_REG_EN_32K,
	.rtc_event_alarm_mask       = DA9063_E_ALARM,
	.rtc_alarm_on_mask          = DA9063_ALARM_ON,
	.rtc_alarm_status_mask      = DA9063_ALARM_STATUS_ALARM |
				      DA9063_ALARM_STATUS_TICK,
	.rtc_tick_on_mask           = DA9063_TICK_ON,
	.rtc_पढ़ोy_to_पढ़ो_mask     = DA9063_RTC_READ,
	.rtc_count_sec_mask         = DA9063_COUNT_SEC_MASK,
	.rtc_count_min_mask         = DA9063_COUNT_MIN_MASK,
	.rtc_count_hour_mask        = DA9063_COUNT_HOUR_MASK,
	.rtc_count_day_mask         = DA9063_COUNT_DAY_MASK,
	.rtc_count_month_mask       = DA9063_COUNT_MONTH_MASK,
	.rtc_count_year_mask        = DA9063_COUNT_YEAR_MASK,
	/* ALARM CONFIG */
	.rtc_data_start             = RTC_SEC,
	.rtc_alarm_len              = RTC_DATA_LEN,
पूर्ण;

अटल स्थिर काष्ठा da9063_compatible_rtc_regmap da9062_aa_regs = अणु
	/* REGS */
	.rtc_enable_reg             = DA9062AA_CONTROL_E,
	.rtc_alarm_secs_reg         = DA9062AA_ALARM_S,
	.rtc_alarm_year_reg         = DA9062AA_ALARM_Y,
	.rtc_count_secs_reg         = DA9062AA_COUNT_S,
	.rtc_count_year_reg         = DA9062AA_COUNT_Y,
	.rtc_event_reg              = DA9062AA_EVENT_A,
	/* MASKS */
	.rtc_enable_mask            = DA9062AA_RTC_EN_MASK,
	.rtc_crystal_mask           = DA9062AA_CRYSTAL_MASK,
	.rtc_enable_32k_crystal_reg = DA9062AA_EN_32K,
	.rtc_event_alarm_mask       = DA9062AA_M_ALARM_MASK,
	.rtc_alarm_on_mask          = DA9062AA_ALARM_ON_MASK,
	.rtc_alarm_status_mask      = (0x02 << 6),
	.rtc_tick_on_mask           = DA9062AA_TICK_ON_MASK,
	.rtc_पढ़ोy_to_पढ़ो_mask     = DA9062AA_RTC_READ_MASK,
	.rtc_count_sec_mask         = DA9062AA_COUNT_SEC_MASK,
	.rtc_count_min_mask         = DA9062AA_COUNT_MIN_MASK,
	.rtc_count_hour_mask        = DA9062AA_COUNT_HOUR_MASK,
	.rtc_count_day_mask         = DA9062AA_COUNT_DAY_MASK,
	.rtc_count_month_mask       = DA9062AA_COUNT_MONTH_MASK,
	.rtc_count_year_mask        = DA9062AA_COUNT_YEAR_MASK,
	/* ALARM CONFIG */
	.rtc_data_start             = RTC_SEC,
	.rtc_alarm_len              = RTC_DATA_LEN,
पूर्ण;

अटल स्थिर काष्ठा of_device_id da9063_compatible_reg_id_table[] = अणु
	अणु .compatible = "dlg,da9063-rtc", .data = &da9063_bb_regs पूर्ण,
	अणु .compatible = "dlg,da9062-rtc", .data = &da9062_aa_regs पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, da9063_compatible_reg_id_table);

अटल व्योम da9063_data_to_पंचांग(u8 *data, काष्ठा rtc_समय *पंचांग,
			      काष्ठा da9063_compatible_rtc *rtc)
अणु
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;

	पंचांग->पंचांग_sec  = data[RTC_SEC]  & config->rtc_count_sec_mask;
	पंचांग->पंचांग_min  = data[RTC_MIN]  & config->rtc_count_min_mask;
	पंचांग->पंचांग_hour = data[RTC_HOUR] & config->rtc_count_hour_mask;
	पंचांग->पंचांग_mday = data[RTC_DAY]  & config->rtc_count_day_mask;
	पंचांग->पंचांग_mon  = MONTHS_FROM_DA9063(data[RTC_MONTH] &
					 config->rtc_count_month_mask);
	पंचांग->पंचांग_year = YEARS_FROM_DA9063(data[RTC_YEAR] &
					config->rtc_count_year_mask);
पूर्ण

अटल व्योम da9063_पंचांग_to_data(काष्ठा rtc_समय *पंचांग, u8 *data,
			      काष्ठा da9063_compatible_rtc *rtc)
अणु
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;

	data[RTC_SEC]   = पंचांग->पंचांग_sec & config->rtc_count_sec_mask;
	data[RTC_MIN]   = पंचांग->पंचांग_min & config->rtc_count_min_mask;
	data[RTC_HOUR]  = पंचांग->पंचांग_hour & config->rtc_count_hour_mask;
	data[RTC_DAY]   = पंचांग->पंचांग_mday & config->rtc_count_day_mask;
	data[RTC_MONTH] = MONTHS_TO_DA9063(पंचांग->पंचांग_mon) &
				config->rtc_count_month_mask;
	data[RTC_YEAR]  = YEARS_TO_DA9063(पंचांग->पंचांग_year) &
				config->rtc_count_year_mask;
पूर्ण

अटल पूर्णांक da9063_rtc_stop_alarm(काष्ठा device *dev)
अणु
	काष्ठा da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;

	वापस regmap_update_bits(rtc->regmap,
				  config->rtc_alarm_year_reg,
				  config->rtc_alarm_on_mask,
				  0);
पूर्ण

अटल पूर्णांक da9063_rtc_start_alarm(काष्ठा device *dev)
अणु
	काष्ठा da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;

	वापस regmap_update_bits(rtc->regmap,
				  config->rtc_alarm_year_reg,
				  config->rtc_alarm_on_mask,
				  config->rtc_alarm_on_mask);
पूर्ण

अटल पूर्णांक da9063_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;
	अचिन्हित दीर्घ पंचांग_secs;
	अचिन्हित दीर्घ al_secs;
	u8 data[RTC_DATA_LEN];
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(rtc->regmap,
			       config->rtc_count_secs_reg,
			       data, RTC_DATA_LEN);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read RTC time data: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!(data[RTC_SEC] & config->rtc_पढ़ोy_to_पढ़ो_mask)) अणु
		dev_dbg(dev, "RTC not yet ready to be read by the host\n");
		वापस -EINVAL;
	पूर्ण

	da9063_data_to_पंचांग(data, पंचांग, rtc);

	पंचांग_secs = rtc_पंचांग_to_समय64(पंचांग);
	al_secs = rtc_पंचांग_to_समय64(&rtc->alarm_समय);

	/* handle the rtc synchronisation delay */
	अगर (rtc->rtc_sync && al_secs - पंचांग_secs == 1)
		स_नकल(पंचांग, &rtc->alarm_समय, माप(काष्ठा rtc_समय));
	अन्यथा
		rtc->rtc_sync = false;

	वापस 0;
पूर्ण

अटल पूर्णांक da9063_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;
	u8 data[RTC_DATA_LEN];
	पूर्णांक ret;

	da9063_पंचांग_to_data(पंचांग, data, rtc);
	ret = regmap_bulk_ग_लिखो(rtc->regmap,
				config->rtc_count_secs_reg,
				data, RTC_DATA_LEN);
	अगर (ret < 0)
		dev_err(dev, "Failed to set RTC time data: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;
	u8 data[RTC_DATA_LEN];
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	data[RTC_SEC] = 0;
	ret = regmap_bulk_पढ़ो(rtc->regmap,
			       config->rtc_alarm_secs_reg,
			       &data[config->rtc_data_start],
			       config->rtc_alarm_len);
	अगर (ret < 0)
		वापस ret;

	da9063_data_to_पंचांग(data, &alrm->समय, rtc);

	alrm->enabled = !!(data[RTC_YEAR] & config->rtc_alarm_on_mask);

	ret = regmap_पढ़ो(rtc->regmap,
			  config->rtc_event_reg,
			  &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val & config->rtc_event_alarm_mask)
		alrm->pending = 1;
	अन्यथा
		alrm->pending = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक da9063_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा da9063_compatible_rtc *rtc = dev_get_drvdata(dev);
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;
	u8 data[RTC_DATA_LEN];
	पूर्णांक ret;

	da9063_पंचांग_to_data(&alrm->समय, data, rtc);

	ret = da9063_rtc_stop_alarm(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to stop alarm: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_bulk_ग_लिखो(rtc->regmap,
				config->rtc_alarm_secs_reg,
				&data[config->rtc_data_start],
				config->rtc_alarm_len);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to write alarm: %d\n", ret);
		वापस ret;
	पूर्ण

	da9063_data_to_पंचांग(data, &rtc->alarm_समय, rtc);

	अगर (alrm->enabled) अणु
		ret = da9063_rtc_start_alarm(dev);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to start alarm: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक da9063_rtc_alarm_irq_enable(काष्ठा device *dev,
				       अचिन्हित पूर्णांक enabled)
अणु
	अगर (enabled)
		वापस da9063_rtc_start_alarm(dev);
	अन्यथा
		वापस da9063_rtc_stop_alarm(dev);
पूर्ण

अटल irqवापस_t da9063_alarm_event(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9063_compatible_rtc *rtc = data;
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config = rtc->config;

	regmap_update_bits(rtc->regmap,
			   config->rtc_alarm_year_reg,
			   config->rtc_alarm_on_mask,
			   0);

	rtc->rtc_sync = true;
	rtc_update_irq(rtc->rtc_dev, 1, RTC_IRQF | RTC_AF);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops da9063_rtc_ops = अणु
	.पढ़ो_समय = da9063_rtc_पढ़ो_समय,
	.set_समय = da9063_rtc_set_समय,
	.पढ़ो_alarm = da9063_rtc_पढ़ो_alarm,
	.set_alarm = da9063_rtc_set_alarm,
	.alarm_irq_enable = da9063_rtc_alarm_irq_enable,
पूर्ण;

अटल पूर्णांक da9063_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9063_compatible_rtc *rtc;
	स्थिर काष्ठा da9063_compatible_rtc_regmap *config;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक irq_alarm;
	u8 data[RTC_DATA_LEN];
	पूर्णांक ret;

	अगर (!pdev->dev.of_node)
		वापस -ENXIO;

	match = of_match_node(da9063_compatible_reg_id_table,
			      pdev->dev.of_node);

	rtc = devm_kzalloc(&pdev->dev, माप(*rtc), GFP_KERNEL);
	अगर (!rtc)
		वापस -ENOMEM;

	rtc->config = match->data;
	अगर (of_device_is_compatible(pdev->dev.of_node, "dlg,da9063-rtc")) अणु
		काष्ठा da9063 *chip = dev_get_drvdata(pdev->dev.parent);

		अगर (chip->variant_code == PMIC_DA9063_AD)
			rtc->config = &da9063_ad_regs;
	पूर्ण

	rtc->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!rtc->regmap) अणु
		dev_warn(&pdev->dev, "Parent regmap unavailable.\n");
		वापस -ENXIO;
	पूर्ण

	config = rtc->config;
	ret = regmap_update_bits(rtc->regmap,
				 config->rtc_enable_reg,
				 config->rtc_enable_mask,
				 config->rtc_enable_mask);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to enable RTC\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(rtc->regmap,
				 config->rtc_enable_32k_crystal_reg,
				 config->rtc_crystal_mask,
				 config->rtc_crystal_mask);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to run 32kHz oscillator\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(rtc->regmap,
				 config->rtc_alarm_secs_reg,
				 config->rtc_alarm_status_mask,
				 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to access RTC alarm register\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(rtc->regmap,
				 config->rtc_alarm_secs_reg,
				 DA9063_ALARM_STATUS_ALARM,
				 DA9063_ALARM_STATUS_ALARM);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to access RTC alarm register\n");
		वापस ret;
	पूर्ण

	ret = regmap_update_bits(rtc->regmap,
				 config->rtc_alarm_year_reg,
				 config->rtc_tick_on_mask,
				 0);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to disable TICKs\n");
		वापस ret;
	पूर्ण

	data[RTC_SEC] = 0;
	ret = regmap_bulk_पढ़ो(rtc->regmap,
			       config->rtc_alarm_secs_reg,
			       &data[config->rtc_data_start],
			       config->rtc_alarm_len);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to read initial alarm data: %d\n",
			ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, rtc);

	rtc->rtc_dev = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(rtc->rtc_dev))
		वापस PTR_ERR(rtc->rtc_dev);

	rtc->rtc_dev->ops = &da9063_rtc_ops;
	rtc->rtc_dev->range_min = RTC_TIMESTAMP_BEGIN_2000;
	rtc->rtc_dev->range_max = RTC_TIMESTAMP_END_2063;

	da9063_data_to_पंचांग(data, &rtc->alarm_समय, rtc);
	rtc->rtc_sync = false;

	/*
	 * TODO: some models have alarms on a minute boundary but still support
	 * real hardware पूर्णांकerrupts. Add this once the core supports it.
	 */
	अगर (config->rtc_data_start != RTC_SEC)
		rtc->rtc_dev->uie_unsupported = 1;

	irq_alarm = platक्रमm_get_irq_byname(pdev, "ALARM");
	अगर (irq_alarm < 0)
		वापस irq_alarm;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, irq_alarm, शून्य,
					da9063_alarm_event,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"ALARM", rtc);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to request ALARM IRQ %d: %d\n",
			irq_alarm, ret);

	वापस devm_rtc_रेजिस्टर_device(rtc->rtc_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver da9063_rtc_driver = अणु
	.probe		= da9063_rtc_probe,
	.driver		= अणु
		.name	= DA9063_DRVNAME_RTC,
		.of_match_table = da9063_compatible_reg_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9063_rtc_driver);

MODULE_AUTHOR("S Twiss <stwiss.opensource@diasemi.com>");
MODULE_DESCRIPTION("Real time clock device driver for Dialog DA9063");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DA9063_DRVNAME_RTC);
