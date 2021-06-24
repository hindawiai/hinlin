<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/input.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा VIB_MAX_LEVEL_mV	(3100)
#घोषणा VIB_MIN_LEVEL_mV	(1200)
#घोषणा VIB_MAX_LEVELS		(VIB_MAX_LEVEL_mV - VIB_MIN_LEVEL_mV)

#घोषणा MAX_FF_SPEED		0xff

काष्ठा pm8xxx_regs अणु
	अचिन्हित पूर्णांक enable_addr;
	अचिन्हित पूर्णांक enable_mask;

	अचिन्हित पूर्णांक drv_addr;
	अचिन्हित पूर्णांक drv_mask;
	अचिन्हित पूर्णांक drv_shअगरt;
	अचिन्हित पूर्णांक drv_en_manual_mask;
पूर्ण;

अटल स्थिर काष्ठा pm8xxx_regs pm8058_regs = अणु
	.drv_addr = 0x4A,
	.drv_mask = 0xf8,
	.drv_shअगरt = 3,
	.drv_en_manual_mask = 0xfc,
पूर्ण;

अटल काष्ठा pm8xxx_regs pm8916_regs = अणु
	.enable_addr = 0xc046,
	.enable_mask = BIT(7),
	.drv_addr = 0xc041,
	.drv_mask = 0x1F,
	.drv_shअगरt = 0,
	.drv_en_manual_mask = 0,
पूर्ण;

/**
 * काष्ठा pm8xxx_vib - काष्ठाure to hold vibrator data
 * @vib_input_dev: input device supporting क्रमce feedback
 * @work: work काष्ठाure to set the vibration parameters
 * @regmap: regmap क्रम रेजिस्टर पढ़ो/ग_लिखो
 * @regs: रेजिस्टरs' info
 * @speed: speed of vibration set from userland
 * @active: state of vibrator
 * @level: level of vibration to set in the chip
 * @reg_vib_drv: regs->drv_addr रेजिस्टर value
 */
काष्ठा pm8xxx_vib अणु
	काष्ठा input_dev *vib_input_dev;
	काष्ठा work_काष्ठा work;
	काष्ठा regmap *regmap;
	स्थिर काष्ठा pm8xxx_regs *regs;
	पूर्णांक speed;
	पूर्णांक level;
	bool active;
	u8  reg_vib_drv;
पूर्ण;

/**
 * pm8xxx_vib_set - handler to start/stop vibration
 * @vib: poपूर्णांकer to vibrator काष्ठाure
 * @on: state to set
 */
अटल पूर्णांक pm8xxx_vib_set(काष्ठा pm8xxx_vib *vib, bool on)
अणु
	पूर्णांक rc;
	अचिन्हित पूर्णांक val = vib->reg_vib_drv;
	स्थिर काष्ठा pm8xxx_regs *regs = vib->regs;

	अगर (on)
		val |= (vib->level << regs->drv_shअगरt) & regs->drv_mask;
	अन्यथा
		val &= ~regs->drv_mask;

	rc = regmap_ग_लिखो(vib->regmap, regs->drv_addr, val);
	अगर (rc < 0)
		वापस rc;

	vib->reg_vib_drv = val;

	अगर (regs->enable_mask)
		rc = regmap_update_bits(vib->regmap, regs->enable_addr,
					regs->enable_mask, on ? ~0 : 0);

	वापस rc;
पूर्ण

/**
 * pm8xxx_work_handler - worker to set vibration level
 * @work: poपूर्णांकer to work_काष्ठा
 */
अटल व्योम pm8xxx_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा pm8xxx_vib *vib = container_of(work, काष्ठा pm8xxx_vib, work);
	स्थिर काष्ठा pm8xxx_regs *regs = vib->regs;
	पूर्णांक rc;
	अचिन्हित पूर्णांक val;

	rc = regmap_पढ़ो(vib->regmap, regs->drv_addr, &val);
	अगर (rc < 0)
		वापस;

	/*
	 * pmic vibrator supports voltage ranges from 1.2 to 3.1V, so
	 * scale the level to fit पूर्णांकo these ranges.
	 */
	अगर (vib->speed) अणु
		vib->active = true;
		vib->level = ((VIB_MAX_LEVELS * vib->speed) / MAX_FF_SPEED) +
						VIB_MIN_LEVEL_mV;
		vib->level /= 100;
	पूर्ण अन्यथा अणु
		vib->active = false;
		vib->level = VIB_MIN_LEVEL_mV / 100;
	पूर्ण

	pm8xxx_vib_set(vib, vib->active);
पूर्ण

/**
 * pm8xxx_vib_बंद - callback of input बंद callback
 * @dev: input device poपूर्णांकer
 *
 * Turns off the vibrator.
 */
अटल व्योम pm8xxx_vib_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pm8xxx_vib *vib = input_get_drvdata(dev);

	cancel_work_sync(&vib->work);
	अगर (vib->active)
		pm8xxx_vib_set(vib, false);
पूर्ण

/**
 * pm8xxx_vib_play_effect - function to handle vib effects.
 * @dev: input device poपूर्णांकer
 * @data: data of effect
 * @effect: effect to play
 *
 * Currently this driver supports only rumble effects.
 */
अटल पूर्णांक pm8xxx_vib_play_effect(काष्ठा input_dev *dev, व्योम *data,
				  काष्ठा ff_effect *effect)
अणु
	काष्ठा pm8xxx_vib *vib = input_get_drvdata(dev);

	vib->speed = effect->u.rumble.strong_magnitude >> 8;
	अगर (!vib->speed)
		vib->speed = effect->u.rumble.weak_magnitude >> 9;

	schedule_work(&vib->work);

	वापस 0;
पूर्ण

अटल पूर्णांक pm8xxx_vib_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pm8xxx_vib *vib;
	काष्ठा input_dev *input_dev;
	पूर्णांक error;
	अचिन्हित पूर्णांक val;
	स्थिर काष्ठा pm8xxx_regs *regs;

	vib = devm_kzalloc(&pdev->dev, माप(*vib), GFP_KERNEL);
	अगर (!vib)
		वापस -ENOMEM;

	vib->regmap = dev_get_regmap(pdev->dev.parent, शून्य);
	अगर (!vib->regmap)
		वापस -ENODEV;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev)
		वापस -ENOMEM;

	INIT_WORK(&vib->work, pm8xxx_work_handler);
	vib->vib_input_dev = input_dev;

	regs = of_device_get_match_data(&pdev->dev);

	/* operate in manual mode */
	error = regmap_पढ़ो(vib->regmap, regs->drv_addr, &val);
	अगर (error < 0)
		वापस error;

	val &= regs->drv_en_manual_mask;
	error = regmap_ग_लिखो(vib->regmap, regs->drv_addr, val);
	अगर (error < 0)
		वापस error;

	vib->regs = regs;
	vib->reg_vib_drv = val;

	input_dev->name = "pm8xxx_vib_ffmemless";
	input_dev->id.version = 1;
	input_dev->बंद = pm8xxx_vib_बंद;
	input_set_drvdata(input_dev, vib);
	input_set_capability(vib->vib_input_dev, EV_FF, FF_RUMBLE);

	error = input_ff_create_memless(input_dev, शून्य,
					pm8xxx_vib_play_effect);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"couldn't register vibrator as FF device\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "couldn't register input device\n");
		वापस error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, vib);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused pm8xxx_vib_suspend(काष्ठा device *dev)
अणु
	काष्ठा pm8xxx_vib *vib = dev_get_drvdata(dev);

	/* Turn off the vibrator */
	pm8xxx_vib_set(vib, false);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(pm8xxx_vib_pm_ops, pm8xxx_vib_suspend, शून्य);

अटल स्थिर काष्ठा of_device_id pm8xxx_vib_id_table[] = अणु
	अणु .compatible = "qcom,pm8058-vib", .data = &pm8058_regs पूर्ण,
	अणु .compatible = "qcom,pm8921-vib", .data = &pm8058_regs पूर्ण,
	अणु .compatible = "qcom,pm8916-vib", .data = &pm8916_regs पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pm8xxx_vib_id_table);

अटल काष्ठा platक्रमm_driver pm8xxx_vib_driver = अणु
	.probe		= pm8xxx_vib_probe,
	.driver		= अणु
		.name	= "pm8xxx-vib",
		.pm	= &pm8xxx_vib_pm_ops,
		.of_match_table = pm8xxx_vib_id_table,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(pm8xxx_vib_driver);

MODULE_ALIAS("platform:pm8xxx_vib");
MODULE_DESCRIPTION("PMIC8xxx vibrator driver based on ff-memless framework");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Amy Maloche <amaloche@codeaurora.org>");
