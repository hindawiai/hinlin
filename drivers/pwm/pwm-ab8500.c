<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Arun R Murthy <arun.murthy@stericsson.com>
 */
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/pwm.h>
#समावेश <linux/mfd/abx500.h>
#समावेश <linux/mfd/abx500/ab8500.h>
#समावेश <linux/module.h>

/*
 * PWM Out generators
 * Bank: 0x10
 */
#घोषणा AB8500_PWM_OUT_CTRL1_REG	0x60
#घोषणा AB8500_PWM_OUT_CTRL2_REG	0x61
#घोषणा AB8500_PWM_OUT_CTRL7_REG	0x66

काष्ठा ab8500_pwm_chip अणु
	काष्ठा pwm_chip chip;
पूर्ण;

अटल पूर्णांक ab8500_pwm_apply(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			    स्थिर काष्ठा pwm_state *state)
अणु
	पूर्णांक ret;
	u8 reg;
	अचिन्हित पूर्णांक higher_val, lower_val;

	अगर (state->polarity != PWM_POLARITY_NORMAL)
		वापस -EINVAL;

	अगर (!state->enabled) अणु
		ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(chip->dev,
					AB8500_MISC, AB8500_PWM_OUT_CTRL7_REG,
					1 << (chip->base - 1), 0);

		अगर (ret < 0)
			dev_err(chip->dev, "%s: Failed to disable PWM, Error %d\n",
								pwm->label, ret);
		वापस ret;
	पूर्ण

	/*
	 * get the first 8 bits that are be written to
	 * AB8500_PWM_OUT_CTRL1_REG[0:7]
	 */
	lower_val = state->duty_cycle & 0x00FF;
	/*
	 * get bits [9:10] that are to be written to
	 * AB8500_PWM_OUT_CTRL2_REG[0:1]
	 */
	higher_val = ((state->duty_cycle & 0x0300) >> 8);

	reg = AB8500_PWM_OUT_CTRL1_REG + ((chip->base - 1) * 2);

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(chip->dev, AB8500_MISC,
			reg, (u8)lower_val);
	अगर (ret < 0)
		वापस ret;

	ret = abx500_set_रेजिस्टर_पूर्णांकerruptible(chip->dev, AB8500_MISC,
			(reg + 1), (u8)higher_val);
	अगर (ret < 0)
		वापस ret;

	ret = abx500_mask_and_set_रेजिस्टर_पूर्णांकerruptible(chip->dev,
				AB8500_MISC, AB8500_PWM_OUT_CTRL7_REG,
				1 << (chip->base - 1), 1 << (chip->base - 1));
	अगर (ret < 0)
		dev_err(chip->dev, "%s: Failed to enable PWM, Error %d\n",
							pwm->label, ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा pwm_ops ab8500_pwm_ops = अणु
	.apply = ab8500_pwm_apply,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक ab8500_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500_pwm_chip *ab8500;
	पूर्णांक err;

	/*
	 * Nothing to be करोne in probe, this is required to get the
	 * device which is required क्रम ab8500 पढ़ो and ग_लिखो
	 */
	ab8500 = devm_kzalloc(&pdev->dev, माप(*ab8500), GFP_KERNEL);
	अगर (ab8500 == शून्य)
		वापस -ENOMEM;

	ab8500->chip.dev = &pdev->dev;
	ab8500->chip.ops = &ab8500_pwm_ops;
	ab8500->chip.npwm = 1;

	err = pwmchip_add(&ab8500->chip);
	अगर (err < 0)
		वापस dev_err_probe(&pdev->dev, err, "Failed to add pwm chip\n");

	dev_dbg(&pdev->dev, "pwm probe successful\n");
	platक्रमm_set_drvdata(pdev, ab8500);

	वापस 0;
पूर्ण

अटल पूर्णांक ab8500_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ab8500_pwm_chip *ab8500 = platक्रमm_get_drvdata(pdev);
	पूर्णांक err;

	err = pwmchip_हटाओ(&ab8500->chip);
	अगर (err < 0)
		वापस err;

	dev_dbg(&pdev->dev, "pwm driver removed\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ab8500_pwm_driver = अणु
	.driver = अणु
		.name = "ab8500-pwm",
	पूर्ण,
	.probe = ab8500_pwm_probe,
	.हटाओ = ab8500_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(ab8500_pwm_driver);

MODULE_AUTHOR("Arun MURTHY <arun.murthy@stericsson.com>");
MODULE_DESCRIPTION("AB8500 Pulse Width Modulation Driver");
MODULE_ALIAS("platform:ab8500-pwm");
MODULE_LICENSE("GPL v2");
