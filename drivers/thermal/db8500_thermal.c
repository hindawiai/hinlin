<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * db8500_thermal.c - DB8500 Thermal Management Implementation
 *
 * Copyright (C) 2012 ST-Ericsson
 * Copyright (C) 2012-2019 Linaro Ltd.
 *
 * Authors: Hongbo Zhang, Linus Walleij
 */

#समावेश <linux/cpu_cooling.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/dbx500-prcmu.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#घोषणा PRCMU_DEFAULT_MEASURE_TIME	0xFFF
#घोषणा PRCMU_DEFAULT_LOW_TEMP		0

/**
 * db8500_thermal_poपूर्णांकs - the पूर्णांकerpolation poपूर्णांकs that trigger
 * पूर्णांकerrupts
 */
अटल स्थिर अचिन्हित दीर्घ db8500_thermal_poपूर्णांकs[] = अणु
	15000,
	20000,
	25000,
	30000,
	35000,
	40000,
	45000,
	50000,
	55000,
	60000,
	65000,
	70000,
	75000,
	80000,
	/*
	 * This is where things start to get really bad क्रम the
	 * SoC and the thermal zones should be set up to trigger
	 * critical temperature at 85000 mC so we करोn't get above
	 * this poपूर्णांक.
	 */
	85000,
	90000,
	95000,
	100000,
पूर्ण;

काष्ठा db8500_thermal_zone अणु
	काष्ठा thermal_zone_device *tz;
	क्रमागत thermal_trend trend;
	अचिन्हित दीर्घ पूर्णांकerpolated_temp;
	अचिन्हित पूर्णांक cur_index;
पूर्ण;

/* Callback to get current temperature */
अटल पूर्णांक db8500_thermal_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा db8500_thermal_zone *th = data;

	/*
	 * TODO: There is no PRCMU पूर्णांकerface to get temperature data currently,
	 * so a pseuकरो temperature is वापसed , it works क्रम thermal framework
	 * and this will be fixed when the PRCMU पूर्णांकerface is available.
	 */
	*temp = th->पूर्णांकerpolated_temp;

	वापस 0;
पूर्ण

/* Callback to get temperature changing trend */
अटल पूर्णांक db8500_thermal_get_trend(व्योम *data, पूर्णांक trip, क्रमागत thermal_trend *trend)
अणु
	काष्ठा db8500_thermal_zone *th = data;

	*trend = th->trend;

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_of_device_ops thdev_ops = अणु
	.get_temp = db8500_thermal_get_temp,
	.get_trend = db8500_thermal_get_trend,
पूर्ण;

अटल व्योम db8500_thermal_update_config(काष्ठा db8500_thermal_zone *th,
					 अचिन्हित पूर्णांक idx,
					 क्रमागत thermal_trend trend,
					 अचिन्हित दीर्घ next_low,
					 अचिन्हित दीर्घ next_high)
अणु
	prcmu_stop_temp_sense();

	th->cur_index = idx;
	th->पूर्णांकerpolated_temp = (next_low + next_high)/2;
	th->trend = trend;

	/*
	 * The PRCMU accept असलolute temperatures in celsius so भागide
	 * करोwn the millicelsius with 1000
	 */
	prcmu_config_hoपंचांगon((u8)(next_low/1000), (u8)(next_high/1000));
	prcmu_start_temp_sense(PRCMU_DEFAULT_MEASURE_TIME);
पूर्ण

अटल irqवापस_t prcmu_low_irq_handler(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा db8500_thermal_zone *th = irq_data;
	अचिन्हित पूर्णांक idx = th->cur_index;
	अचिन्हित दीर्घ next_low, next_high;

	अगर (idx == 0)
		/* Meaningless क्रम thermal management, ignoring it */
		वापस IRQ_HANDLED;

	अगर (idx == 1) अणु
		next_high = db8500_thermal_poपूर्णांकs[0];
		next_low = PRCMU_DEFAULT_LOW_TEMP;
	पूर्ण अन्यथा अणु
		next_high = db8500_thermal_poपूर्णांकs[idx - 1];
		next_low = db8500_thermal_poपूर्णांकs[idx - 2];
	पूर्ण
	idx -= 1;

	db8500_thermal_update_config(th, idx, THERMAL_TREND_DROPPING,
				     next_low, next_high);
	dev_dbg(&th->tz->device,
		"PRCMU set max %ld, min %ld\n", next_high, next_low);

	thermal_zone_device_update(th->tz, THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t prcmu_high_irq_handler(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा db8500_thermal_zone *th = irq_data;
	अचिन्हित पूर्णांक idx = th->cur_index;
	अचिन्हित दीर्घ next_low, next_high;
	पूर्णांक num_poपूर्णांकs = ARRAY_SIZE(db8500_thermal_poपूर्णांकs);

	अगर (idx < num_poपूर्णांकs - 1) अणु
		next_high = db8500_thermal_poपूर्णांकs[idx+1];
		next_low = db8500_thermal_poपूर्णांकs[idx];
		idx += 1;

		db8500_thermal_update_config(th, idx, THERMAL_TREND_RAISING,
					     next_low, next_high);

		dev_dbg(&th->tz->device,
			"PRCMU set max %ld, min %ld\n", next_high, next_low);
	पूर्ण अन्यथा अगर (idx == num_poपूर्णांकs - 1)
		/* So we roof out 1 degree over the max poपूर्णांक */
		th->पूर्णांकerpolated_temp = db8500_thermal_poपूर्णांकs[idx] + 1;

	thermal_zone_device_update(th->tz, THERMAL_EVENT_UNSPECIFIED);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक db8500_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा db8500_thermal_zone *th = शून्य;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक low_irq, high_irq, ret = 0;

	th = devm_kzalloc(dev, माप(*th), GFP_KERNEL);
	अगर (!th)
		वापस -ENOMEM;

	low_irq = platक्रमm_get_irq_byname(pdev, "IRQ_HOTMON_LOW");
	अगर (low_irq < 0) अणु
		dev_err(dev, "Get IRQ_HOTMON_LOW failed\n");
		वापस low_irq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, low_irq, शून्य,
		prcmu_low_irq_handler, IRQF_NO_SUSPEND | IRQF_ONESHOT,
		"dbx500_temp_low", th);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to allocate temp low irq\n");
		वापस ret;
	पूर्ण

	high_irq = platक्रमm_get_irq_byname(pdev, "IRQ_HOTMON_HIGH");
	अगर (high_irq < 0) अणु
		dev_err(dev, "Get IRQ_HOTMON_HIGH failed\n");
		वापस high_irq;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, high_irq, शून्य,
		prcmu_high_irq_handler, IRQF_NO_SUSPEND | IRQF_ONESHOT,
		"dbx500_temp_high", th);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to allocate temp high irq\n");
		वापस ret;
	पूर्ण

	/* रेजिस्टर of thermal sensor and get info from DT */
	th->tz = devm_thermal_zone_of_sensor_रेजिस्टर(dev, 0, th, &thdev_ops);
	अगर (IS_ERR(th->tz)) अणु
		dev_err(dev, "register thermal zone sensor failed\n");
		वापस PTR_ERR(th->tz);
	पूर्ण
	dev_info(dev, "thermal zone sensor registered\n");

	/* Start measuring at the lowest poपूर्णांक */
	db8500_thermal_update_config(th, 0, THERMAL_TREND_STABLE,
				     PRCMU_DEFAULT_LOW_TEMP,
				     db8500_thermal_poपूर्णांकs[0]);

	platक्रमm_set_drvdata(pdev, th);

	वापस 0;
पूर्ण

अटल पूर्णांक db8500_thermal_suspend(काष्ठा platक्रमm_device *pdev,
		pm_message_t state)
अणु
	prcmu_stop_temp_sense();

	वापस 0;
पूर्ण

अटल पूर्णांक db8500_thermal_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा db8500_thermal_zone *th = platक्रमm_get_drvdata(pdev);

	/* Resume and start measuring at the lowest poपूर्णांक */
	db8500_thermal_update_config(th, 0, THERMAL_TREND_STABLE,
				     PRCMU_DEFAULT_LOW_TEMP,
				     db8500_thermal_poपूर्णांकs[0]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id db8500_thermal_match[] = अणु
	अणु .compatible = "stericsson,db8500-thermal" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, db8500_thermal_match);

अटल काष्ठा platक्रमm_driver db8500_thermal_driver = अणु
	.driver = अणु
		.name = "db8500-thermal",
		.of_match_table = of_match_ptr(db8500_thermal_match),
	पूर्ण,
	.probe = db8500_thermal_probe,
	.suspend = db8500_thermal_suspend,
	.resume = db8500_thermal_resume,
पूर्ण;

module_platक्रमm_driver(db8500_thermal_driver);

MODULE_AUTHOR("Hongbo Zhang <hongbo.zhang@stericsson.com>");
MODULE_DESCRIPTION("DB8500 thermal driver");
MODULE_LICENSE("GPL");
