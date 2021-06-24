<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Thermal device driver क्रम DA9062 and DA9061
 * Copyright (C) 2017  Dialog Semiconductor
 */

/* When over-temperature is reached, an पूर्णांकerrupt from the device will be
 * triggered. Following this event the पूर्णांकerrupt will be disabled and
 * periodic transmission of uevents (HOT trip poपूर्णांक) should define the
 * first level of temperature supervision. It is expected that any final
 * implementation of the thermal driver will include a .notअगरy() function
 * to implement these uevents to userspace.
 *
 * These uevents are पूर्णांकended to indicate non-invasive temperature control
 * of the प्रणाली, where the necessary measures क्रम cooling are the
 * responsibility of the host software. Once the temperature falls again,
 * the IRQ is re-enabled so the start of a new over-temperature event can
 * be detected without स्थिरant software monitoring.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/thermal.h>
#समावेश <linux/workqueue.h>

#समावेश <linux/mfd/da9062/core.h>
#समावेश <linux/mfd/da9062/रेजिस्टरs.h>

/* Minimum, maximum and शेष polling millisecond periods are provided
 * here as an example. It is expected that any final implementation to also
 * include a modअगरication of these settings to match the required
 * application.
 */
#घोषणा DA9062_DEFAULT_POLLING_MS_PERIOD	3000
#घोषणा DA9062_MAX_POLLING_MS_PERIOD		10000
#घोषणा DA9062_MIN_POLLING_MS_PERIOD		1000

#घोषणा DA9062_MILLI_CELSIUS(t)			((t) * 1000)

काष्ठा da9062_thermal_config अणु
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा da9062_thermal अणु
	काष्ठा da9062 *hw;
	काष्ठा delayed_work work;
	काष्ठा thermal_zone_device *zone;
	काष्ठा mutex lock; /* protection क्रम da9062_thermal temperature */
	पूर्णांक temperature;
	पूर्णांक irq;
	स्थिर काष्ठा da9062_thermal_config *config;
	काष्ठा device *dev;
पूर्ण;

अटल व्योम da9062_thermal_poll_on(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा da9062_thermal *thermal = container_of(work,
						काष्ठा da9062_thermal,
						work.work);
	अचिन्हित दीर्घ delay;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* clear E_TEMP */
	ret = regmap_ग_लिखो(thermal->hw->regmap,
			   DA9062AA_EVENT_B,
			   DA9062AA_E_TEMP_MASK);
	अगर (ret < 0) अणु
		dev_err(thermal->dev,
			"Cannot clear the TJUNC temperature status\n");
		जाओ err_enable_irq;
	पूर्ण

	/* Now पढ़ो E_TEMP again: it is acting like a status bit.
	 * If over-temperature, then this status will be true.
	 * If not over-temperature, this status will be false.
	 */
	ret = regmap_पढ़ो(thermal->hw->regmap,
			  DA9062AA_EVENT_B,
			  &val);
	अगर (ret < 0) अणु
		dev_err(thermal->dev,
			"Cannot check the TJUNC temperature status\n");
		जाओ err_enable_irq;
	पूर्ण

	अगर (val & DA9062AA_E_TEMP_MASK) अणु
		mutex_lock(&thermal->lock);
		thermal->temperature = DA9062_MILLI_CELSIUS(125);
		mutex_unlock(&thermal->lock);
		thermal_zone_device_update(thermal->zone,
					   THERMAL_EVENT_UNSPECIFIED);

		delay = thermal->zone->passive_delay_jअगरfies;
		queue_delayed_work(प्रणाली_मुक्तzable_wq, &thermal->work, delay);
		वापस;
	पूर्ण

	mutex_lock(&thermal->lock);
	thermal->temperature = DA9062_MILLI_CELSIUS(0);
	mutex_unlock(&thermal->lock);
	thermal_zone_device_update(thermal->zone,
				   THERMAL_EVENT_UNSPECIFIED);

err_enable_irq:
	enable_irq(thermal->irq);
पूर्ण

अटल irqवापस_t da9062_thermal_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा da9062_thermal *thermal = data;

	disable_irq_nosync(thermal->irq);
	queue_delayed_work(प्रणाली_मुक्तzable_wq, &thermal->work, 0);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक da9062_thermal_get_trip_type(काष्ठा thermal_zone_device *z,
					पूर्णांक trip,
					क्रमागत thermal_trip_type *type)
अणु
	काष्ठा da9062_thermal *thermal = z->devdata;

	चयन (trip) अणु
	हाल 0:
		*type = THERMAL_TRIP_HOT;
		अवरोध;
	शेष:
		dev_err(thermal->dev,
			"Driver does not support more than 1 trip-wire\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da9062_thermal_get_trip_temp(काष्ठा thermal_zone_device *z,
					पूर्णांक trip,
					पूर्णांक *temp)
अणु
	काष्ठा da9062_thermal *thermal = z->devdata;

	चयन (trip) अणु
	हाल 0:
		*temp = DA9062_MILLI_CELSIUS(125);
		अवरोध;
	शेष:
		dev_err(thermal->dev,
			"Driver does not support more than 1 trip-wire\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक da9062_thermal_get_temp(काष्ठा thermal_zone_device *z,
				   पूर्णांक *temp)
अणु
	काष्ठा da9062_thermal *thermal = z->devdata;

	mutex_lock(&thermal->lock);
	*temp = thermal->temperature;
	mutex_unlock(&thermal->lock);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops da9062_thermal_ops = अणु
	.get_temp	= da9062_thermal_get_temp,
	.get_trip_type	= da9062_thermal_get_trip_type,
	.get_trip_temp	= da9062_thermal_get_trip_temp,
पूर्ण;

अटल स्थिर काष्ठा da9062_thermal_config da9062_config = अणु
	.name = "da9062-thermal",
पूर्ण;

अटल स्थिर काष्ठा of_device_id da9062_compatible_reg_id_table[] = अणु
	अणु .compatible = "dlg,da9062-thermal", .data = &da9062_config पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, da9062_compatible_reg_id_table);

अटल पूर्णांक da9062_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा da9062 *chip = dev_get_drvdata(pdev->dev.parent);
	काष्ठा da9062_thermal *thermal;
	अचिन्हित पूर्णांक pp_पंचांगp = DA9062_DEFAULT_POLLING_MS_PERIOD;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret = 0;

	match = of_match_node(da9062_compatible_reg_id_table,
			      pdev->dev.of_node);
	अगर (!match)
		वापस -ENXIO;

	अगर (pdev->dev.of_node) अणु
		अगर (!of_property_पढ़ो_u32(pdev->dev.of_node,
					  "polling-delay-passive",
					  &pp_पंचांगp)) अणु
			अगर (pp_पंचांगp < DA9062_MIN_POLLING_MS_PERIOD ||
			    pp_पंचांगp > DA9062_MAX_POLLING_MS_PERIOD) अणु
				dev_warn(&pdev->dev,
					 "Out-of-range polling period %d ms\n",
					 pp_पंचांगp);
				pp_पंचांगp = DA9062_DEFAULT_POLLING_MS_PERIOD;
			पूर्ण
		पूर्ण
	पूर्ण

	thermal = devm_kzalloc(&pdev->dev, माप(काष्ठा da9062_thermal),
			       GFP_KERNEL);
	अगर (!thermal) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	thermal->config = match->data;
	thermal->hw = chip;
	thermal->dev = &pdev->dev;

	INIT_DELAYED_WORK(&thermal->work, da9062_thermal_poll_on);
	mutex_init(&thermal->lock);

	thermal->zone = thermal_zone_device_रेजिस्टर(thermal->config->name,
					1, 0, thermal,
					&da9062_thermal_ops, शून्य, pp_पंचांगp,
					0);
	अगर (IS_ERR(thermal->zone)) अणु
		dev_err(&pdev->dev, "Cannot register thermal zone device\n");
		ret = PTR_ERR(thermal->zone);
		जाओ err;
	पूर्ण
	ret = thermal_zone_device_enable(thermal->zone);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot enable thermal zone device\n");
		जाओ err_zone;
	पूर्ण

	dev_dbg(&pdev->dev,
		"TJUNC temperature polling period set at %d ms\n",
		jअगरfies_to_msecs(thermal->zone->passive_delay_jअगरfies));

	ret = platक्रमm_get_irq_byname(pdev, "THERMAL");
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to get platform IRQ.\n");
		जाओ err_zone;
	पूर्ण
	thermal->irq = ret;

	ret = request_thपढ़ोed_irq(thermal->irq, शून्य,
				   da9062_thermal_irq_handler,
				   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				   "THERMAL", thermal);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to request thermal device IRQ.\n");
		जाओ err_zone;
	पूर्ण

	platक्रमm_set_drvdata(pdev, thermal);
	वापस 0;

err_zone:
	thermal_zone_device_unरेजिस्टर(thermal->zone);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक da9062_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा	da9062_thermal *thermal = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(thermal->irq, thermal);
	cancel_delayed_work_sync(&thermal->work);
	thermal_zone_device_unरेजिस्टर(thermal->zone);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver da9062_thermal_driver = अणु
	.probe	= da9062_thermal_probe,
	.हटाओ	= da9062_thermal_हटाओ,
	.driver	= अणु
		.name	= "da9062-thermal",
		.of_match_table = da9062_compatible_reg_id_table,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(da9062_thermal_driver);

MODULE_AUTHOR("Steve Twiss");
MODULE_DESCRIPTION("Thermal TJUNC device driver for Dialog DA9062 and DA9061");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:da9062-thermal");
