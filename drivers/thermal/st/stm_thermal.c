<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2018 - All Rights Reserved
 * Author: David Hernandez Sanchez <david.hernandezsanchez@st.com> क्रम
 * STMicroelectronics.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/thermal.h>

#समावेश "../thermal_core.h"
#समावेश "../thermal_hwmon.h"

/* DTS रेजिस्टर offsets */
#घोषणा DTS_CFGR1_OFFSET	0x0
#घोषणा DTS_T0VALR1_OFFSET	0x8
#घोषणा DTS_RAMPVALR_OFFSET	0X10
#घोषणा DTS_ITR1_OFFSET		0x14
#घोषणा DTS_DR_OFFSET		0x1C
#घोषणा DTS_SR_OFFSET		0x20
#घोषणा DTS_ITENR_OFFSET	0x24
#घोषणा DTS_ICIFR_OFFSET	0x28

/* DTS_CFGR1 रेजिस्टर mask definitions */
#घोषणा HSREF_CLK_DIV_MASK	GENMASK(30, 24)
#घोषणा TS1_SMP_TIME_MASK	GENMASK(19, 16)
#घोषणा TS1_INTRIG_SEL_MASK	GENMASK(11, 8)

/* DTS_T0VALR1 रेजिस्टर mask definitions */
#घोषणा TS1_T0_MASK		GENMASK(17, 16)
#घोषणा TS1_FMT0_MASK		GENMASK(15, 0)

/* DTS_RAMPVALR रेजिस्टर mask definitions */
#घोषणा TS1_RAMP_COEFF_MASK	GENMASK(15, 0)

/* DTS_ITR1 रेजिस्टर mask definitions */
#घोषणा TS1_HITTHD_MASK		GENMASK(31, 16)
#घोषणा TS1_LITTHD_MASK		GENMASK(15, 0)

/* DTS_DR रेजिस्टर mask definitions */
#घोषणा TS1_MFREQ_MASK		GENMASK(15, 0)

/* DTS_ITENR रेजिस्टर mask definitions */
#घोषणा ITENR_MASK		(GENMASK(2, 0) | GENMASK(6, 4))

/* DTS_ICIFR रेजिस्टर mask definitions */
#घोषणा ICIFR_MASK		(GENMASK(2, 0) | GENMASK(6, 4))

/* Less signअगरicant bit position definitions */
#घोषणा TS1_T0_POS		16
#घोषणा TS1_HITTHD_POS		16
#घोषणा TS1_LITTHD_POS		0
#घोषणा HSREF_CLK_DIV_POS	24

/* DTS_CFGR1 bit definitions */
#घोषणा TS1_EN			BIT(0)
#घोषणा TS1_START		BIT(4)
#घोषणा REFCLK_SEL		BIT(20)
#घोषणा REFCLK_LSE		REFCLK_SEL
#घोषणा Q_MEAS_OPT		BIT(21)
#घोषणा CALIBRATION_CONTROL	Q_MEAS_OPT

/* DTS_SR bit definitions */
#घोषणा TS_RDY			BIT(15)
/* Bit definitions below are common क्रम DTS_SR, DTS_ITENR and DTS_CIFR */
#घोषणा HIGH_THRESHOLD		BIT(2)
#घोषणा LOW_THRESHOLD		BIT(1)

/* Constants */
#घोषणा ADJUST			100
#घोषणा ONE_MHZ			1000000
#घोषणा POLL_TIMEOUT		5000
#घोषणा STARTUP_TIME		40
#घोषणा TS1_T0_VAL0		30000  /* 30 celsius */
#घोषणा TS1_T0_VAL1		130000 /* 130 celsius */
#घोषणा NO_HW_TRIG		0
#घोषणा SAMPLING_TIME		15

काष्ठा sपंचांग_thermal_sensor अणु
	काष्ठा device *dev;
	काष्ठा thermal_zone_device *th_dev;
	क्रमागत thermal_device_mode mode;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक low_temp_enabled;
	अचिन्हित पूर्णांक high_temp_enabled;
	पूर्णांक irq;
	व्योम __iomem *base;
	पूर्णांक t0, fmt0, ramp_coeff;
पूर्ण;

अटल पूर्णांक sपंचांग_enable_irq(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	u32 value;

	dev_dbg(sensor->dev, "low:%d high:%d\n", sensor->low_temp_enabled,
		sensor->high_temp_enabled);

	/* Disable IT generation क्रम low and high thresholds */
	value = पढ़ोl_relaxed(sensor->base + DTS_ITENR_OFFSET);
	value &= ~(LOW_THRESHOLD | HIGH_THRESHOLD);

	अगर (sensor->low_temp_enabled)
		value |= HIGH_THRESHOLD;

	अगर (sensor->high_temp_enabled)
		value |= LOW_THRESHOLD;

	/* Enable पूर्णांकerrupts */
	ग_लिखोl_relaxed(value, sensor->base + DTS_ITENR_OFFSET);

	वापस 0;
पूर्ण

अटल irqवापस_t sपंचांग_thermal_irq_handler(पूर्णांक irq, व्योम *sdata)
अणु
	काष्ठा sपंचांग_thermal_sensor *sensor = sdata;

	dev_dbg(sensor->dev, "sr:%d\n",
		पढ़ोl_relaxed(sensor->base + DTS_SR_OFFSET));

	thermal_zone_device_update(sensor->th_dev, THERMAL_EVENT_UNSPECIFIED);

	sपंचांग_enable_irq(sensor);

	/* Acknoledge all DTS irqs */
	ग_लिखोl_relaxed(ICIFR_MASK, sensor->base + DTS_ICIFR_OFFSET);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक sपंचांग_sensor_घातer_on(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	पूर्णांक ret;
	u32 value;

	/* Enable sensor */
	value = पढ़ोl_relaxed(sensor->base + DTS_CFGR1_OFFSET);
	value |= TS1_EN;
	ग_लिखोl_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	/*
	 * The DTS block can be enabled by setting TSx_EN bit in
	 * DTS_CFGRx रेजिस्टर. It requires a startup समय of
	 * 40Nञs. Use 5 ms as arbitrary समयout.
	 */
	ret = पढ़ोl_poll_समयout(sensor->base + DTS_SR_OFFSET,
				 value, (value & TS_RDY),
				 STARTUP_TIME, POLL_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* Start continuous measuring */
	value = पढ़ोl_relaxed(sensor->base +
			      DTS_CFGR1_OFFSET);
	value |= TS1_START;
	ग_लिखोl_relaxed(value, sensor->base +
		       DTS_CFGR1_OFFSET);

	sensor->mode = THERMAL_DEVICE_ENABLED;

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग_sensor_घातer_off(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	u32 value;

	sensor->mode = THERMAL_DEVICE_DISABLED;

	/* Stop measuring */
	value = पढ़ोl_relaxed(sensor->base + DTS_CFGR1_OFFSET);
	value &= ~TS1_START;
	ग_लिखोl_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	/* Ensure stop is taken पूर्णांकo account */
	usleep_range(STARTUP_TIME, POLL_TIMEOUT);

	/* Disable sensor */
	value = पढ़ोl_relaxed(sensor->base + DTS_CFGR1_OFFSET);
	value &= ~TS1_EN;
	ग_लिखोl_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	/* Ensure disable is taken पूर्णांकo account */
	वापस पढ़ोl_poll_समयout(sensor->base + DTS_SR_OFFSET, value,
				  !(value & TS_RDY),
				  STARTUP_TIME, POLL_TIMEOUT);
पूर्ण

अटल पूर्णांक sपंचांग_thermal_calibration(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	u32 value, clk_freq;
	u32 prescaler;

	/* Figure out prescaler value क्रम PCLK during calibration */
	clk_freq = clk_get_rate(sensor->clk);
	अगर (!clk_freq)
		वापस -EINVAL;

	prescaler = 0;
	clk_freq /= ONE_MHZ;
	अगर (clk_freq) अणु
		जबतक (prescaler <= clk_freq)
			prescaler++;
	पूर्ण

	value = पढ़ोl_relaxed(sensor->base + DTS_CFGR1_OFFSET);

	/* Clear prescaler */
	value &= ~HSREF_CLK_DIV_MASK;

	/* Set prescaler. pclk_freq/prescaler < 1MHz */
	value |= (prescaler << HSREF_CLK_DIV_POS);

	/* Select PCLK as reference घड़ी */
	value &= ~REFCLK_SEL;

	/* Set maximal sampling समय क्रम better precision */
	value |= TS1_SMP_TIME_MASK;

	/* Measure with calibration */
	value &= ~CALIBRATION_CONTROL;

	/* select trigger */
	value &= ~TS1_INTRIG_SEL_MASK;
	value |= NO_HW_TRIG;

	ग_लिखोl_relaxed(value, sensor->base + DTS_CFGR1_OFFSET);

	वापस 0;
पूर्ण

/* Fill in DTS काष्ठाure with factory sensor values */
अटल पूर्णांक sपंचांग_thermal_पढ़ो_factory_settings(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	/* Retrieve engineering calibration temperature */
	sensor->t0 = पढ़ोl_relaxed(sensor->base + DTS_T0VALR1_OFFSET) &
					TS1_T0_MASK;
	अगर (!sensor->t0)
		sensor->t0 = TS1_T0_VAL0;
	अन्यथा
		sensor->t0 = TS1_T0_VAL1;

	/* Retrieve fmt0 and put it on Hz */
	sensor->fmt0 = ADJUST * (पढ़ोl_relaxed(sensor->base +
				 DTS_T0VALR1_OFFSET) & TS1_FMT0_MASK);

	/* Retrieve ramp coefficient */
	sensor->ramp_coeff = पढ़ोl_relaxed(sensor->base + DTS_RAMPVALR_OFFSET) &
					   TS1_RAMP_COEFF_MASK;

	अगर (!sensor->fmt0 || !sensor->ramp_coeff) अणु
		dev_err(sensor->dev, "%s: wrong setting\n", __func__);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(sensor->dev, "%s: T0 = %doC, FMT0 = %dHz, RAMP_COEFF = %dHz/oC",
		__func__, sensor->t0, sensor->fmt0, sensor->ramp_coeff);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग_thermal_calculate_threshold(काष्ठा sपंचांग_thermal_sensor *sensor,
					   पूर्णांक temp, u32 *th)
अणु
	पूर्णांक freqM;

	/* Figure out the CLK_PTAT frequency क्रम a given temperature */
	freqM = ((temp - sensor->t0) * sensor->ramp_coeff) / 1000 +
		sensor->fmt0;

	/* Figure out the threshold sample number */
	*th = clk_get_rate(sensor->clk) * SAMPLING_TIME / freqM;
	अगर (!*th)
		वापस -EINVAL;

	dev_dbg(sensor->dev, "freqM=%d Hz, threshold=0x%x", freqM, *th);

	वापस 0;
पूर्ण

/* Disable temperature पूर्णांकerrupt */
अटल पूर्णांक sपंचांग_disable_irq(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	u32 value;

	/* Disable IT generation */
	value = पढ़ोl_relaxed(sensor->base + DTS_ITENR_OFFSET);
	value &= ~ITENR_MASK;
	ग_लिखोl_relaxed(value, sensor->base + DTS_ITENR_OFFSET);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग_thermal_set_trips(व्योम *data, पूर्णांक low, पूर्णांक high)
अणु
	काष्ठा sपंचांग_thermal_sensor *sensor = data;
	u32 itr1, th;
	पूर्णांक ret;

	dev_dbg(sensor->dev, "set trips %d <--> %d\n", low, high);

	/* Erase threshold content */
	itr1 = पढ़ोl_relaxed(sensor->base + DTS_ITR1_OFFSET);
	itr1 &= ~(TS1_LITTHD_MASK | TS1_HITTHD_MASK);

	/*
	 * Disable low-temp अगर "low" is too small. As per thermal framework
	 * API, we use -पूर्णांक_उच्च rather than पूर्णांक_न्यून.
	 */

	अगर (low > -पूर्णांक_उच्च) अणु
		sensor->low_temp_enabled = 1;
		/* add 0.5 of hysteresis due to measurement error */
		ret = sपंचांग_thermal_calculate_threshold(sensor, low - 500, &th);
		अगर (ret)
			वापस ret;

		itr1 |= (TS1_HITTHD_MASK  & (th << TS1_HITTHD_POS));
	पूर्ण अन्यथा अणु
		sensor->low_temp_enabled = 0;
	पूर्ण

	/* Disable high-temp अगर "high" is too big. */
	अगर (high < पूर्णांक_उच्च) अणु
		sensor->high_temp_enabled = 1;
		ret = sपंचांग_thermal_calculate_threshold(sensor, high, &th);
		अगर (ret)
			वापस ret;

		itr1 |= (TS1_LITTHD_MASK  & (th << TS1_LITTHD_POS));
	पूर्ण अन्यथा अणु
		sensor->high_temp_enabled = 0;
	पूर्ण

	/* Write new threshod values*/
	ग_लिखोl_relaxed(itr1, sensor->base + DTS_ITR1_OFFSET);

	वापस 0;
पूर्ण

/* Callback to get temperature from HW */
अटल पूर्णांक sपंचांग_thermal_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा sपंचांग_thermal_sensor *sensor = data;
	u32 periods;
	पूर्णांक freqM, ret;

	अगर (sensor->mode != THERMAL_DEVICE_ENABLED)
		वापस -EAGAIN;

	/* Retrieve the number of periods sampled */
	ret = पढ़ोl_relaxed_poll_समयout(sensor->base + DTS_DR_OFFSET, periods,
					 (periods & TS1_MFREQ_MASK),
					 STARTUP_TIME, POLL_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* Figure out the CLK_PTAT frequency */
	freqM = (clk_get_rate(sensor->clk) * SAMPLING_TIME) / periods;
	अगर (!freqM)
		वापस -EINVAL;

	/* Figure out the temperature in mili celsius */
	*temp = (freqM - sensor->fmt0) * 1000 / sensor->ramp_coeff + sensor->t0;

	वापस 0;
पूर्ण

/* Registers DTS irq to be visible by GIC */
अटल पूर्णांक sपंचांग_रेजिस्टर_irq(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	काष्ठा device *dev = sensor->dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret;

	sensor->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sensor->irq < 0)
		वापस sensor->irq;

	ret = devm_request_thपढ़ोed_irq(dev, sensor->irq,
					शून्य,
					sपंचांग_thermal_irq_handler,
					IRQF_ONESHOT,
					dev->driver->name, sensor);
	अगर (ret) अणु
		dev_err(dev, "%s: Failed to register IRQ %d\n", __func__,
			sensor->irq);
		वापस ret;
	पूर्ण

	dev_dbg(dev, "%s: thermal IRQ registered", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग_thermal_sensor_off(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	पूर्णांक ret;

	sपंचांग_disable_irq(sensor);

	ret = sपंचांग_sensor_घातer_off(sensor);
	अगर (ret)
		वापस ret;

	clk_disable_unprepare(sensor->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग_thermal_prepare(काष्ठा sपंचांग_thermal_sensor *sensor)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(sensor->clk);
	अगर (ret)
		वापस ret;

	ret = sपंचांग_thermal_पढ़ो_factory_settings(sensor);
	अगर (ret)
		जाओ thermal_unprepare;

	ret = sपंचांग_thermal_calibration(sensor);
	अगर (ret)
		जाओ thermal_unprepare;

	वापस 0;

thermal_unprepare:
	clk_disable_unprepare(sensor->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग_thermal_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग_thermal_sensor *sensor = dev_get_drvdata(dev);

	वापस sपंचांग_thermal_sensor_off(sensor);
पूर्ण

अटल पूर्णांक sपंचांग_thermal_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा sपंचांग_thermal_sensor *sensor = dev_get_drvdata(dev);

	ret = sपंचांग_thermal_prepare(sensor);
	अगर (ret)
		वापस ret;

	ret = sपंचांग_sensor_घातer_on(sensor);
	अगर (ret)
		वापस ret;

	thermal_zone_device_update(sensor->th_dev, THERMAL_EVENT_UNSPECIFIED);
	sपंचांग_enable_irq(sensor);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(sपंचांग_thermal_pm_ops,
			 sपंचांग_thermal_suspend, sपंचांग_thermal_resume);

अटल स्थिर काष्ठा thermal_zone_of_device_ops sपंचांग_tz_ops = अणु
	.get_temp	= sपंचांग_thermal_get_temp,
	.set_trips	= sपंचांग_thermal_set_trips,
पूर्ण;

अटल स्थिर काष्ठा of_device_id sपंचांग_thermal_of_match[] = अणु
		अणु .compatible = "st,stm32-thermal"पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग_thermal_of_match);

अटल पूर्णांक sपंचांग_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग_thermal_sensor *sensor;
	काष्ठा resource *res;
	व्योम __iomem *base;
	पूर्णांक ret;

	अगर (!pdev->dev.of_node) अणु
		dev_err(&pdev->dev, "%s: device tree node not found\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	sensor = devm_kzalloc(&pdev->dev, माप(*sensor), GFP_KERNEL);
	अगर (!sensor)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, sensor);

	sensor->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/* Populate sensor */
	sensor->base = base;

	sensor->clk = devm_clk_get(&pdev->dev, "pclk");
	अगर (IS_ERR(sensor->clk)) अणु
		dev_err(&pdev->dev, "%s: failed to fetch PCLK clock\n",
			__func__);
		वापस PTR_ERR(sensor->clk);
	पूर्ण

	sपंचांग_disable_irq(sensor);

	/* Clear irq flags */
	ग_लिखोl_relaxed(ICIFR_MASK, sensor->base + DTS_ICIFR_OFFSET);

	/* Configure and enable HW sensor */
	ret = sपंचांग_thermal_prepare(sensor);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error prepare sensor: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = sपंचांग_sensor_घातer_on(sensor);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error power on sensor: %d\n", ret);
		वापस ret;
	पूर्ण

	sensor->th_dev = devm_thermal_zone_of_sensor_रेजिस्टर(&pdev->dev, 0,
							      sensor,
							      &sपंचांग_tz_ops);

	अगर (IS_ERR(sensor->th_dev)) अणु
		dev_err(&pdev->dev, "%s: thermal zone sensor registering KO\n",
			__func__);
		ret = PTR_ERR(sensor->th_dev);
		वापस ret;
	पूर्ण

	/* Register IRQ पूर्णांकo GIC */
	ret = sपंचांग_रेजिस्टर_irq(sensor);
	अगर (ret)
		जाओ err_tz;

	sपंचांग_enable_irq(sensor);

	/*
	 * Thermal_zone करोesn't enable hwmon as शेष,
	 * enable it here
	 */
	sensor->th_dev->tzp->no_hwmon = false;
	ret = thermal_add_hwmon_sysfs(sensor->th_dev);
	अगर (ret)
		जाओ err_tz;

	dev_info(&pdev->dev, "%s: Driver initialized successfully\n",
		 __func__);

	वापस 0;

err_tz:
	thermal_zone_of_sensor_unरेजिस्टर(&pdev->dev, sensor->th_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग_thermal_sensor *sensor = platक्रमm_get_drvdata(pdev);

	sपंचांग_thermal_sensor_off(sensor);
	thermal_हटाओ_hwmon_sysfs(sensor->th_dev);
	thermal_zone_of_sensor_unरेजिस्टर(&pdev->dev, sensor->th_dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांग_thermal_driver = अणु
	.driver = अणु
		.name	= "stm_thermal",
		.pm     = &sपंचांग_thermal_pm_ops,
		.of_match_table = sपंचांग_thermal_of_match,
	पूर्ण,
	.probe		= sपंचांग_thermal_probe,
	.हटाओ		= sपंचांग_thermal_हटाओ,
पूर्ण;
module_platक्रमm_driver(sपंचांग_thermal_driver);

MODULE_DESCRIPTION("STMicroelectronics STM32 Thermal Sensor Driver");
MODULE_AUTHOR("David Hernandez Sanchez <david.hernandezsanchez@st.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:stm_thermal");
