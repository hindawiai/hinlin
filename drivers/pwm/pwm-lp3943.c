<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI/National Semiconductor LP3943 PWM driver
 *
 * Copyright 2013 Texas Instruments
 *
 * Author: Milo Kim <milo.kim@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/lp3943.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा LP3943_MAX_DUTY			255
#घोषणा LP3943_MIN_PERIOD		6250
#घोषणा LP3943_MAX_PERIOD		1600000

काष्ठा lp3943_pwm अणु
	काष्ठा pwm_chip chip;
	काष्ठा lp3943 *lp3943;
	काष्ठा lp3943_platक्रमm_data *pdata;
पूर्ण;

अटल अंतरभूत काष्ठा lp3943_pwm *to_lp3943_pwm(काष्ठा pwm_chip *_chip)
अणु
	वापस container_of(_chip, काष्ठा lp3943_pwm, chip);
पूर्ण

अटल काष्ठा lp3943_pwm_map *
lp3943_pwm_request_map(काष्ठा lp3943_pwm *lp3943_pwm, पूर्णांक hwpwm)
अणु
	काष्ठा lp3943_platक्रमm_data *pdata = lp3943_pwm->pdata;
	काष्ठा lp3943 *lp3943 = lp3943_pwm->lp3943;
	काष्ठा lp3943_pwm_map *pwm_map;
	पूर्णांक i, offset;

	pwm_map = kzalloc(माप(*pwm_map), GFP_KERNEL);
	अगर (!pwm_map)
		वापस ERR_PTR(-ENOMEM);

	pwm_map->output = pdata->pwms[hwpwm]->output;
	pwm_map->num_outमाला_दो = pdata->pwms[hwpwm]->num_outमाला_दो;

	क्रम (i = 0; i < pwm_map->num_outमाला_दो; i++) अणु
		offset = pwm_map->output[i];

		/* Return an error अगर the pin is alपढ़ोy asचिन्हित */
		अगर (test_and_set_bit(offset, &lp3943->pin_used)) अणु
			kमुक्त(pwm_map);
			वापस ERR_PTR(-EBUSY);
		पूर्ण
	पूर्ण

	वापस pwm_map;
पूर्ण

अटल पूर्णांक lp3943_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lp3943_pwm *lp3943_pwm = to_lp3943_pwm(chip);
	काष्ठा lp3943_pwm_map *pwm_map;

	pwm_map = lp3943_pwm_request_map(lp3943_pwm, pwm->hwpwm);
	अगर (IS_ERR(pwm_map))
		वापस PTR_ERR(pwm_map);

	वापस pwm_set_chip_data(pwm, pwm_map);
पूर्ण

अटल व्योम lp3943_pwm_मुक्त_map(काष्ठा lp3943_pwm *lp3943_pwm,
				काष्ठा lp3943_pwm_map *pwm_map)
अणु
	काष्ठा lp3943 *lp3943 = lp3943_pwm->lp3943;
	पूर्णांक i, offset;

	क्रम (i = 0; i < pwm_map->num_outमाला_दो; i++) अणु
		offset = pwm_map->output[i];
		clear_bit(offset, &lp3943->pin_used);
	पूर्ण

	kमुक्त(pwm_map);
पूर्ण

अटल व्योम lp3943_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lp3943_pwm *lp3943_pwm = to_lp3943_pwm(chip);
	काष्ठा lp3943_pwm_map *pwm_map = pwm_get_chip_data(pwm);

	lp3943_pwm_मुक्त_map(lp3943_pwm, pwm_map);
पूर्ण

अटल पूर्णांक lp3943_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			     पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा lp3943_pwm *lp3943_pwm = to_lp3943_pwm(chip);
	काष्ठा lp3943 *lp3943 = lp3943_pwm->lp3943;
	u8 val, reg_duty, reg_prescale;
	पूर्णांक err;

	/*
	 * How to configure the LP3943 PWMs
	 *
	 * 1) Period = 6250 ~ 1600000
	 * 2) Prescale = period / 6250 -1
	 * 3) Duty = input duty
	 *
	 * Prescale and duty are रेजिस्टर values
	 */

	अगर (pwm->hwpwm == 0) अणु
		reg_prescale = LP3943_REG_PRESCALE0;
		reg_duty     = LP3943_REG_PWM0;
	पूर्ण अन्यथा अणु
		reg_prescale = LP3943_REG_PRESCALE1;
		reg_duty     = LP3943_REG_PWM1;
	पूर्ण

	period_ns = clamp(period_ns, LP3943_MIN_PERIOD, LP3943_MAX_PERIOD);
	val       = (u8)(period_ns / LP3943_MIN_PERIOD - 1);

	err = lp3943_ग_लिखो_byte(lp3943, reg_prescale, val);
	अगर (err)
		वापस err;

	val = (u8)(duty_ns * LP3943_MAX_DUTY / period_ns);

	वापस lp3943_ग_लिखो_byte(lp3943, reg_duty, val);
पूर्ण

अटल पूर्णांक lp3943_pwm_set_mode(काष्ठा lp3943_pwm *lp3943_pwm,
			       काष्ठा lp3943_pwm_map *pwm_map,
			       u8 val)
अणु
	काष्ठा lp3943 *lp3943 = lp3943_pwm->lp3943;
	स्थिर काष्ठा lp3943_reg_cfg *mux = lp3943->mux_cfg;
	पूर्णांक i, index, err;

	क्रम (i = 0; i < pwm_map->num_outमाला_दो; i++) अणु
		index = pwm_map->output[i];
		err = lp3943_update_bits(lp3943, mux[index].reg,
					 mux[index].mask,
					 val << mux[index].shअगरt);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक lp3943_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lp3943_pwm *lp3943_pwm = to_lp3943_pwm(chip);
	काष्ठा lp3943_pwm_map *pwm_map = pwm_get_chip_data(pwm);
	u8 val;

	अगर (pwm->hwpwm == 0)
		val = LP3943_DIM_PWM0;
	अन्यथा
		val = LP3943_DIM_PWM1;

	/*
	 * Each PWM generator is set to control any of outमाला_दो of LP3943.
	 * To enable/disable the PWM, these output pins should be configured.
	 */

	वापस lp3943_pwm_set_mode(lp3943_pwm, pwm_map, val);
पूर्ण

अटल व्योम lp3943_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा lp3943_pwm *lp3943_pwm = to_lp3943_pwm(chip);
	काष्ठा lp3943_pwm_map *pwm_map = pwm_get_chip_data(pwm);

	/*
	 * LP3943 outमाला_दो are खोलो-drain, so the pin should be configured
	 * when the PWM is disabled.
	 */

	lp3943_pwm_set_mode(lp3943_pwm, pwm_map, LP3943_GPIO_OUT_HIGH);
पूर्ण

अटल स्थिर काष्ठा pwm_ops lp3943_pwm_ops = अणु
	.request	= lp3943_pwm_request,
	.मुक्त		= lp3943_pwm_मुक्त,
	.config		= lp3943_pwm_config,
	.enable		= lp3943_pwm_enable,
	.disable	= lp3943_pwm_disable,
	.owner		= THIS_MODULE,
पूर्ण;

अटल पूर्णांक lp3943_pwm_parse_dt(काष्ठा device *dev,
			       काष्ठा lp3943_pwm *lp3943_pwm)
अणु
	अटल स्थिर अक्षर * स्थिर name[] = अणु "ti,pwm0", "ti,pwm1", पूर्ण;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा lp3943_platक्रमm_data *pdata;
	काष्ठा lp3943_pwm_map *pwm_map;
	क्रमागत lp3943_pwm_output *output;
	पूर्णांक i, err, proplen, count = 0;
	u32 num_outमाला_दो;

	अगर (!node)
		वापस -EINVAL;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	/*
	 * Read the output map configuration from the device tree.
	 * Each of the two PWM generators can drive zero or more outमाला_दो.
	 */

	क्रम (i = 0; i < LP3943_NUM_PWMS; i++) अणु
		अगर (!of_get_property(node, name[i], &proplen))
			जारी;

		num_outमाला_दो = proplen / माप(u32);
		अगर (num_outमाला_दो == 0)
			जारी;

		output = devm_kसुस्मृति(dev, num_outमाला_दो, माप(*output),
				      GFP_KERNEL);
		अगर (!output)
			वापस -ENOMEM;

		err = of_property_पढ़ो_u32_array(node, name[i], output,
						 num_outमाला_दो);
		अगर (err)
			वापस err;

		pwm_map = devm_kzalloc(dev, माप(*pwm_map), GFP_KERNEL);
		अगर (!pwm_map)
			वापस -ENOMEM;

		pwm_map->output = output;
		pwm_map->num_outमाला_दो = num_outमाला_दो;
		pdata->pwms[i] = pwm_map;

		count++;
	पूर्ण

	अगर (count == 0)
		वापस -ENODATA;

	lp3943_pwm->pdata = pdata;
	वापस 0;
पूर्ण

अटल पूर्णांक lp3943_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp3943 *lp3943 = dev_get_drvdata(pdev->dev.parent);
	काष्ठा lp3943_pwm *lp3943_pwm;
	पूर्णांक ret;

	lp3943_pwm = devm_kzalloc(&pdev->dev, माप(*lp3943_pwm), GFP_KERNEL);
	अगर (!lp3943_pwm)
		वापस -ENOMEM;

	lp3943_pwm->pdata = lp3943->pdata;
	अगर (!lp3943_pwm->pdata) अणु
		अगर (IS_ENABLED(CONFIG_OF))
			ret = lp3943_pwm_parse_dt(&pdev->dev, lp3943_pwm);
		अन्यथा
			ret = -ENODEV;

		अगर (ret)
			वापस ret;
	पूर्ण

	lp3943_pwm->lp3943 = lp3943;
	lp3943_pwm->chip.dev = &pdev->dev;
	lp3943_pwm->chip.ops = &lp3943_pwm_ops;
	lp3943_pwm->chip.npwm = LP3943_NUM_PWMS;

	platक्रमm_set_drvdata(pdev, lp3943_pwm);

	वापस pwmchip_add(&lp3943_pwm->chip);
पूर्ण

अटल पूर्णांक lp3943_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा lp3943_pwm *lp3943_pwm = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&lp3943_pwm->chip);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id lp3943_pwm_of_match[] = अणु
	अणु .compatible = "ti,lp3943-pwm", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, lp3943_pwm_of_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver lp3943_pwm_driver = अणु
	.probe = lp3943_pwm_probe,
	.हटाओ = lp3943_pwm_हटाओ,
	.driver = अणु
		.name = "lp3943-pwm",
		.of_match_table = of_match_ptr(lp3943_pwm_of_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(lp3943_pwm_driver);

MODULE_DESCRIPTION("LP3943 PWM driver");
MODULE_ALIAS("platform:lp3943-pwm");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL");
