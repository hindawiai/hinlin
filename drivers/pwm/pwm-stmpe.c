<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2016 Linaro Ltd.
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/sपंचांगpe.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>

#घोषणा STMPE24XX_PWMCS		0x30
#घोषणा PWMCS_EN_PWM0		BIT(0)
#घोषणा PWMCS_EN_PWM1		BIT(1)
#घोषणा PWMCS_EN_PWM2		BIT(2)
#घोषणा STMPE24XX_PWMIC0	0x38
#घोषणा STMPE24XX_PWMIC1	0x39
#घोषणा STMPE24XX_PWMIC2	0x3a

#घोषणा STMPE_PWM_24XX_PINBASE	21

काष्ठा sपंचांगpe_pwm अणु
	काष्ठा sपंचांगpe *sपंचांगpe;
	काष्ठा pwm_chip chip;
	u8 last_duty;
पूर्ण;

अटल अंतरभूत काष्ठा sपंचांगpe_pwm *to_sपंचांगpe_pwm(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा sपंचांगpe_pwm, chip);
पूर्ण

अटल पूर्णांक sपंचांगpe_24xx_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा sपंचांगpe_pwm *sपंचांगpe_pwm = to_sपंचांगpe_pwm(chip);
	u8 value;
	पूर्णांक ret;

	ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe_pwm->sपंचांगpe, STMPE24XX_PWMCS);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "error reading PWM#%u control\n",
			pwm->hwpwm);
		वापस ret;
	पूर्ण

	value = ret | BIT(pwm->hwpwm);

	ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe_pwm->sपंचांगpe, STMPE24XX_PWMCS, value);
	अगर (ret) अणु
		dev_err(chip->dev, "error writing PWM#%u control\n",
			pwm->hwpwm);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांगpe_24xx_pwm_disable(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm)
अणु
	काष्ठा sपंचांगpe_pwm *sपंचांगpe_pwm = to_sपंचांगpe_pwm(chip);
	u8 value;
	पूर्णांक ret;

	ret = sपंचांगpe_reg_पढ़ो(sपंचांगpe_pwm->sपंचांगpe, STMPE24XX_PWMCS);
	अगर (ret < 0) अणु
		dev_err(chip->dev, "error reading PWM#%u control\n",
			pwm->hwpwm);
		वापस;
	पूर्ण

	value = ret & ~BIT(pwm->hwpwm);

	ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe_pwm->sपंचांगpe, STMPE24XX_PWMCS, value);
	अगर (ret) अणु
		dev_err(chip->dev, "error writing PWM#%u control\n",
			pwm->hwpwm);
		वापस;
	पूर्ण
पूर्ण

/* STMPE 24xx PWM inकाष्ठाions */
#घोषणा SMAX		0x007f
#घोषणा SMIN		0x00ff
#घोषणा GTS		0x0000
#घोषणा LOAD		BIT(14) /* Only available on 2403 */
#घोषणा RAMPUP		0x0000
#घोषणा RAMPDOWN	BIT(7)
#घोषणा PRESCALE_512	BIT(14)
#घोषणा STEPTIME_1	BIT(8)
#घोषणा BRANCH		(BIT(15) | BIT(13))

अटल पूर्णांक sपंचांगpe_24xx_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
				 पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा sपंचांगpe_pwm *sपंचांगpe_pwm = to_sपंचांगpe_pwm(chip);
	अचिन्हित पूर्णांक i, pin;
	u16 program[3] = अणु
		SMAX,
		GTS,
		GTS,
	पूर्ण;
	u8 offset;
	पूर्णांक ret;

	/* Make sure we are disabled */
	अगर (pwm_is_enabled(pwm)) अणु
		sपंचांगpe_24xx_pwm_disable(chip, pwm);
	पूर्ण अन्यथा अणु
		/* Connect the PWM to the pin */
		pin = pwm->hwpwm;

		/* On STMPE2401 and 2403 pins 21,22,23 are used */
		अगर (sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2401 ||
		    sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2403)
			pin += STMPE_PWM_24XX_PINBASE;

		ret = sपंचांगpe_set_altfunc(sपंचांगpe_pwm->sपंचांगpe, BIT(pin),
					STMPE_BLOCK_PWM);
		अगर (ret) अणु
			dev_err(chip->dev, "unable to connect PWM#%u to pin\n",
				pwm->hwpwm);
			वापस ret;
		पूर्ण
	पूर्ण

	/* STMPE24XX */
	चयन (pwm->hwpwm) अणु
	हाल 0:
		offset = STMPE24XX_PWMIC0;
		अवरोध;

	हाल 1:
		offset = STMPE24XX_PWMIC1;
		अवरोध;

	हाल 2:
		offset = STMPE24XX_PWMIC2;
		अवरोध;

	शेष:
		/* Should not happen as npwm is 3 */
		वापस -ENODEV;
	पूर्ण

	dev_dbg(chip->dev, "PWM#%u: config duty %d ns, period %d ns\n",
		pwm->hwpwm, duty_ns, period_ns);

	अगर (duty_ns == 0) अणु
		अगर (sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2401)
			program[0] = SMAX; /* off all the समय */

		अगर (sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2403)
			program[0] = LOAD | 0xff; /* LOAD 0xff */

		sपंचांगpe_pwm->last_duty = 0x00;
	पूर्ण अन्यथा अगर (duty_ns == period_ns) अणु
		अगर (sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2401)
			program[0] = SMIN; /* on all the समय */

		अगर (sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2403)
			program[0] = LOAD | 0x00; /* LOAD 0x00 */

		sपंचांगpe_pwm->last_duty = 0xff;
	पूर्ण अन्यथा अणु
		u8 value, last = sपंचांगpe_pwm->last_duty;
		अचिन्हित दीर्घ duty;

		/*
		 * Counter goes from 0x00 to 0xff repeatedly at 32768 Hz,
		 * (means a period of 30517 ns) then this is compared to the
		 * counter from the ramp, अगर this is >= PWM counter the output
		 * is high. With LOAD we can define how much of the cycle it
		 * is on.
		 *
		 * Prescale = 0 -> 2 kHz -> T = 1/f = 488281.25 ns
		 */

		/* Scale to 0..0xff */
		duty = duty_ns * 256;
		duty = DIV_ROUND_CLOSEST(duty, period_ns);
		value = duty;

		अगर (value == last) अणु
			/* Run the old program */
			अगर (pwm_is_enabled(pwm))
				sपंचांगpe_24xx_pwm_enable(chip, pwm);

			वापस 0;
		पूर्ण अन्यथा अगर (sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2403) अणु
			/* STMPE2403 can simply set the right PWM value */
			program[0] = LOAD | value;
			program[1] = 0x0000;
		पूर्ण अन्यथा अगर (sपंचांगpe_pwm->sपंचांगpe->partnum == STMPE2401) अणु
			/* STMPE2401 need a complex program */
			u16 incdec = 0x0000;

			अगर (last < value)
				/* Count up */
				incdec = RAMPUP | (value - last);
			अन्यथा
				/* Count करोwn */
				incdec = RAMPDOWN | (last - value);

			/* Step to desired value, smoothly */
			program[0] = PRESCALE_512 | STEPTIME_1 | incdec;

			/* Loop eternally to 0x00 */
			program[1] = BRANCH;
		पूर्ण

		dev_dbg(chip->dev,
			"PWM#%u: value = %02x, last_duty = %02x, program=%04x,%04x,%04x\n",
			pwm->hwpwm, value, last, program[0], program[1],
			program[2]);
		sपंचांगpe_pwm->last_duty = value;
	पूर्ण

	/*
	 * We can ग_लिखो programs of up to 64 16-bit words पूर्णांकo this channel.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(program); i++) अणु
		u8 value;

		value = (program[i] >> 8) & 0xff;

		ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe_pwm->sपंचांगpe, offset, value);
		अगर (ret) अणु
			dev_err(chip->dev, "error writing register %02x: %d\n",
				offset, ret);
			वापस ret;
		पूर्ण

		value = program[i] & 0xff;

		ret = sपंचांगpe_reg_ग_लिखो(sपंचांगpe_pwm->sपंचांगpe, offset, value);
		अगर (ret) अणु
			dev_err(chip->dev, "error writing register %02x: %d\n",
				offset, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* If we were enabled, re-enable this PWM */
	अगर (pwm_is_enabled(pwm))
		sपंचांगpe_24xx_pwm_enable(chip, pwm);

	/* Sleep क्रम 200ms so we're sure it will take effect */
	msleep(200);

	dev_dbg(chip->dev, "programmed PWM#%u, %u bytes\n", pwm->hwpwm, i);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops sपंचांगpe_24xx_pwm_ops = अणु
	.config = sपंचांगpe_24xx_pwm_config,
	.enable = sपंचांगpe_24xx_pwm_enable,
	.disable = sपंचांगpe_24xx_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक __init sपंचांगpe_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांगpe *sपंचांगpe = dev_get_drvdata(pdev->dev.parent);
	काष्ठा sपंचांगpe_pwm *pwm;
	पूर्णांक ret;

	pwm = devm_kzalloc(&pdev->dev, माप(*pwm), GFP_KERNEL);
	अगर (!pwm)
		वापस -ENOMEM;

	pwm->sपंचांगpe = sपंचांगpe;
	pwm->chip.dev = &pdev->dev;

	अगर (sपंचांगpe->partnum == STMPE2401 || sपंचांगpe->partnum == STMPE2403) अणु
		pwm->chip.ops = &sपंचांगpe_24xx_pwm_ops;
		pwm->chip.npwm = 3;
	पूर्ण अन्यथा अणु
		अगर (sपंचांगpe->partnum == STMPE1601)
			dev_err(&pdev->dev, "STMPE1601 not yet supported\n");
		अन्यथा
			dev_err(&pdev->dev, "Unknown STMPE PWM\n");

		वापस -ENODEV;
	पूर्ण

	ret = sपंचांगpe_enable(sपंचांगpe, STMPE_BLOCK_PWM);
	अगर (ret)
		वापस ret;

	ret = pwmchip_add(&pwm->chip);
	अगर (ret) अणु
		sपंचांगpe_disable(sपंचांगpe, STMPE_BLOCK_PWM);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwm);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sपंचांगpe_pwm_driver = अणु
	.driver = अणु
		.name = "stmpe-pwm",
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver_probe(sपंचांगpe_pwm_driver, sपंचांगpe_pwm_probe);
