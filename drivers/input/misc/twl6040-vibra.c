<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * twl6040-vibra.c - TWL6040 Vibrator driver
 *
 * Author:      Jorge Eduarकरो Candelaria <jorge.candelaria@ti.com>
 * Author:      Misael Lopez Cruz <misael.lopez@ti.com>
 *
 * Copyright:   (C) 2011 Texas Instruments, Inc.
 *
 * Based on twl4030-vibra.c by Henrik Saari <henrik.saari@nokia.com>
 *				Felipe Balbi <felipe.balbi@nokia.com>
 *				Jari Vanhala <ext-javi.vanhala@nokia.com>
 */
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/twl6040.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा EFFECT_सूची_180_DEG	0x8000

/* Recommended modulation index 85% */
#घोषणा TWL6040_VIBRA_MOD	85

#घोषणा TWL6040_NUM_SUPPLIES 2

काष्ठा vibra_info अणु
	काष्ठा device *dev;
	काष्ठा input_dev *input_dev;
	काष्ठा work_काष्ठा play_work;

	पूर्णांक irq;

	bool enabled;
	पूर्णांक weak_speed;
	पूर्णांक strong_speed;
	पूर्णांक direction;

	अचिन्हित पूर्णांक vibldrv_res;
	अचिन्हित पूर्णांक vibrdrv_res;
	अचिन्हित पूर्णांक viblmotor_res;
	अचिन्हित पूर्णांक vibrmotor_res;

	काष्ठा regulator_bulk_data supplies[TWL6040_NUM_SUPPLIES];

	काष्ठा twl6040 *twl6040;
पूर्ण;

अटल irqवापस_t twl6040_vib_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vibra_info *info = data;
	काष्ठा twl6040 *twl6040 = info->twl6040;
	u8 status;

	status = twl6040_reg_पढ़ो(twl6040, TWL6040_REG_STATUS);
	अगर (status & TWL6040_VIBLOCDET) अणु
		dev_warn(info->dev, "Left Vibrator overcurrent detected\n");
		twl6040_clear_bits(twl6040, TWL6040_REG_VIBCTLL,
				   TWL6040_VIBENA);
	पूर्ण
	अगर (status & TWL6040_VIBROCDET) अणु
		dev_warn(info->dev, "Right Vibrator overcurrent detected\n");
		twl6040_clear_bits(twl6040, TWL6040_REG_VIBCTLR,
				   TWL6040_VIBENA);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम twl6040_vibra_enable(काष्ठा vibra_info *info)
अणु
	काष्ठा twl6040 *twl6040 = info->twl6040;
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(info->supplies), info->supplies);
	अगर (ret) अणु
		dev_err(info->dev, "failed to enable regulators %d\n", ret);
		वापस;
	पूर्ण

	twl6040_घातer(info->twl6040, 1);
	अगर (twl6040_get_revid(twl6040) <= TWL6040_REV_ES1_1) अणु
		/*
		 * ERRATA: Disable overcurrent protection क्रम at least
		 * 3ms when enabling vibrator drivers to aव्योम false
		 * overcurrent detection
		 */
		twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBCTLL,
				  TWL6040_VIBENA | TWL6040_VIBCTRL);
		twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBCTLR,
				  TWL6040_VIBENA | TWL6040_VIBCTRL);
		usleep_range(3000, 3500);
	पूर्ण

	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBCTLL,
			  TWL6040_VIBENA);
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBCTLR,
			  TWL6040_VIBENA);

	info->enabled = true;
पूर्ण

अटल व्योम twl6040_vibra_disable(काष्ठा vibra_info *info)
अणु
	काष्ठा twl6040 *twl6040 = info->twl6040;

	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBCTLL, 0x00);
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBCTLR, 0x00);
	twl6040_घातer(info->twl6040, 0);

	regulator_bulk_disable(ARRAY_SIZE(info->supplies), info->supplies);

	info->enabled = false;
पूर्ण

अटल u8 twl6040_vibra_code(पूर्णांक vddvib, पूर्णांक vibdrv_res, पूर्णांक motor_res,
			     पूर्णांक speed, पूर्णांक direction)
अणु
	पूर्णांक vpk, max_code;
	u8 vibdat;

	/* output swing */
	vpk = (vddvib * motor_res * TWL6040_VIBRA_MOD) /
		(100 * (vibdrv_res + motor_res));

	/* 50mV per VIBDAT code step */
	max_code = vpk / 50;
	अगर (max_code > TWL6040_VIBDAT_MAX)
		max_code = TWL6040_VIBDAT_MAX;

	/* scale speed to max allowed code */
	vibdat = (u8)((speed * max_code) / अच_लघु_उच्च);

	/* 2's complement क्रम direction > 180 degrees */
	vibdat *= direction;

	वापस vibdat;
पूर्ण

अटल व्योम twl6040_vibra_set_effect(काष्ठा vibra_info *info)
अणु
	काष्ठा twl6040 *twl6040 = info->twl6040;
	u8 vibdatl, vibdatr;
	पूर्णांक volt;

	/* weak motor */
	volt = regulator_get_voltage(info->supplies[0].consumer) / 1000;
	vibdatl = twl6040_vibra_code(volt, info->vibldrv_res,
				     info->viblmotor_res,
				     info->weak_speed, info->direction);

	/* strong motor */
	volt = regulator_get_voltage(info->supplies[1].consumer) / 1000;
	vibdatr = twl6040_vibra_code(volt, info->vibrdrv_res,
				     info->vibrmotor_res,
				     info->strong_speed, info->direction);

	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBDATL, vibdatl);
	twl6040_reg_ग_लिखो(twl6040, TWL6040_REG_VIBDATR, vibdatr);
पूर्ण

अटल व्योम vibra_play_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vibra_info *info = container_of(work,
				काष्ठा vibra_info, play_work);
	पूर्णांक ret;

	/* Do not allow effect, जबतक the routing is set to use audio */
	ret = twl6040_get_vibralr_status(info->twl6040);
	अगर (ret & TWL6040_VIBSEL) अणु
		dev_info(info->dev, "Vibra is configured for audio\n");
		वापस;
	पूर्ण

	अगर (info->weak_speed || info->strong_speed) अणु
		अगर (!info->enabled)
			twl6040_vibra_enable(info);

		twl6040_vibra_set_effect(info);
	पूर्ण अन्यथा अगर (info->enabled)
		twl6040_vibra_disable(info);

पूर्ण

अटल पूर्णांक vibra_play(काष्ठा input_dev *input, व्योम *data,
		      काष्ठा ff_effect *effect)
अणु
	काष्ठा vibra_info *info = input_get_drvdata(input);

	info->weak_speed = effect->u.rumble.weak_magnitude;
	info->strong_speed = effect->u.rumble.strong_magnitude;
	info->direction = effect->direction < EFFECT_सूची_180_DEG ? 1 : -1;

	schedule_work(&info->play_work);

	वापस 0;
पूर्ण

अटल व्योम twl6040_vibra_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा vibra_info *info = input_get_drvdata(input);

	cancel_work_sync(&info->play_work);

	अगर (info->enabled)
		twl6040_vibra_disable(info);
पूर्ण

अटल पूर्णांक __maybe_unused twl6040_vibra_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा vibra_info *info = platक्रमm_get_drvdata(pdev);

	cancel_work_sync(&info->play_work);

	अगर (info->enabled)
		twl6040_vibra_disable(info);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(twl6040_vibra_pm_ops, twl6040_vibra_suspend, शून्य);

अटल पूर्णांक twl6040_vibra_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *twl6040_core_dev = pdev->dev.parent;
	काष्ठा device_node *twl6040_core_node;
	काष्ठा vibra_info *info;
	पूर्णांक vddvibl_uV = 0;
	पूर्णांक vddvibr_uV = 0;
	पूर्णांक error;

	twl6040_core_node = of_get_child_by_name(twl6040_core_dev->of_node,
						 "vibra");
	अगर (!twl6040_core_node) अणु
		dev_err(&pdev->dev, "parent of node is missing?\n");
		वापस -EINVAL;
	पूर्ण

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info) अणु
		of_node_put(twl6040_core_node);
		dev_err(&pdev->dev, "couldn't allocate memory\n");
		वापस -ENOMEM;
	पूर्ण

	info->dev = &pdev->dev;

	info->twl6040 = dev_get_drvdata(pdev->dev.parent);

	of_property_पढ़ो_u32(twl6040_core_node, "ti,vibldrv-res",
			     &info->vibldrv_res);
	of_property_पढ़ो_u32(twl6040_core_node, "ti,vibrdrv-res",
			     &info->vibrdrv_res);
	of_property_पढ़ो_u32(twl6040_core_node, "ti,viblmotor-res",
			     &info->viblmotor_res);
	of_property_पढ़ो_u32(twl6040_core_node, "ti,vibrmotor-res",
			     &info->vibrmotor_res);
	of_property_पढ़ो_u32(twl6040_core_node, "ti,vddvibl-uV", &vddvibl_uV);
	of_property_पढ़ो_u32(twl6040_core_node, "ti,vddvibr-uV", &vddvibr_uV);

	of_node_put(twl6040_core_node);

	अगर ((!info->vibldrv_res && !info->viblmotor_res) ||
	    (!info->vibrdrv_res && !info->vibrmotor_res)) अणु
		dev_err(info->dev, "invalid vibra driver/motor resistance\n");
		वापस -EINVAL;
	पूर्ण

	info->irq = platक्रमm_get_irq(pdev, 0);
	अगर (info->irq < 0)
		वापस -EINVAL;

	error = devm_request_thपढ़ोed_irq(&pdev->dev, info->irq, शून्य,
					  twl6040_vib_irq_handler,
					  IRQF_ONESHOT,
					  "twl6040_irq_vib", info);
	अगर (error) अणु
		dev_err(info->dev, "VIB IRQ request failed: %d\n", error);
		वापस error;
	पूर्ण

	info->supplies[0].supply = "vddvibl";
	info->supplies[1].supply = "vddvibr";
	/*
	 * When booted with Device tree the regulators are attached to the
	 * parent device (twl6040 MFD core)
	 */
	error = devm_regulator_bulk_get(twl6040_core_dev,
					ARRAY_SIZE(info->supplies),
					info->supplies);
	अगर (error) अणु
		dev_err(info->dev, "couldn't get regulators %d\n", error);
		वापस error;
	पूर्ण

	अगर (vddvibl_uV) अणु
		error = regulator_set_voltage(info->supplies[0].consumer,
					      vddvibl_uV, vddvibl_uV);
		अगर (error) अणु
			dev_err(info->dev, "failed to set VDDVIBL volt %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	अगर (vddvibr_uV) अणु
		error = regulator_set_voltage(info->supplies[1].consumer,
					      vddvibr_uV, vddvibr_uV);
		अगर (error) अणु
			dev_err(info->dev, "failed to set VDDVIBR volt %d\n",
				error);
			वापस error;
		पूर्ण
	पूर्ण

	INIT_WORK(&info->play_work, vibra_play_work);

	info->input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!info->input_dev) अणु
		dev_err(info->dev, "couldn't allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_set_drvdata(info->input_dev, info);

	info->input_dev->name = "twl6040:vibrator";
	info->input_dev->id.version = 1;
	info->input_dev->बंद = twl6040_vibra_बंद;
	__set_bit(FF_RUMBLE, info->input_dev->ffbit);

	error = input_ff_create_memless(info->input_dev, शून्य, vibra_play);
	अगर (error) अणु
		dev_err(info->dev, "couldn't register vibrator to FF\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(info->input_dev);
	अगर (error) अणु
		dev_err(info->dev, "couldn't register input device\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver twl6040_vibra_driver = अणु
	.probe		= twl6040_vibra_probe,
	.driver		= अणु
		.name	= "twl6040-vibra",
		.pm	= &twl6040_vibra_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(twl6040_vibra_driver);

MODULE_ALIAS("platform:twl6040-vibra");
MODULE_DESCRIPTION("TWL6040 Vibra driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jorge Eduardo Candelaria <jorge.candelaria@ti.com>");
MODULE_AUTHOR("Misael Lopez Cruz <misael.lopez@ti.com>");
