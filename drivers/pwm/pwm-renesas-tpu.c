<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R-Mobile TPU PWM driver
 *
 * Copyright (C) 2012 Renesas Solutions Corp.
 */

#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pwm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#घोषणा TPU_CHANNEL_MAX		4

#घोषणा TPU_TSTR		0x00	/* Timer start रेजिस्टर (shared) */

#घोषणा TPU_TCRn		0x00	/* Timer control रेजिस्टर */
#घोषणा TPU_TCR_CCLR_NONE	(0 << 5)
#घोषणा TPU_TCR_CCLR_TGRA	(1 << 5)
#घोषणा TPU_TCR_CCLR_TGRB	(2 << 5)
#घोषणा TPU_TCR_CCLR_TGRC	(5 << 5)
#घोषणा TPU_TCR_CCLR_TGRD	(6 << 5)
#घोषणा TPU_TCR_CKEG_RISING	(0 << 3)
#घोषणा TPU_TCR_CKEG_FALLING	(1 << 3)
#घोषणा TPU_TCR_CKEG_BOTH	(2 << 3)
#घोषणा TPU_TMDRn		0x04	/* Timer mode रेजिस्टर */
#घोषणा TPU_TMDR_BFWT		(1 << 6)
#घोषणा TPU_TMDR_BFB		(1 << 5)
#घोषणा TPU_TMDR_BFA		(1 << 4)
#घोषणा TPU_TMDR_MD_NORMAL	(0 << 0)
#घोषणा TPU_TMDR_MD_PWM		(2 << 0)
#घोषणा TPU_TIORn		0x08	/* Timer I/O control रेजिस्टर */
#घोषणा TPU_TIOR_IOA_0		(0 << 0)
#घोषणा TPU_TIOR_IOA_0_CLR	(1 << 0)
#घोषणा TPU_TIOR_IOA_0_SET	(2 << 0)
#घोषणा TPU_TIOR_IOA_0_TOGGLE	(3 << 0)
#घोषणा TPU_TIOR_IOA_1		(4 << 0)
#घोषणा TPU_TIOR_IOA_1_CLR	(5 << 0)
#घोषणा TPU_TIOR_IOA_1_SET	(6 << 0)
#घोषणा TPU_TIOR_IOA_1_TOGGLE	(7 << 0)
#घोषणा TPU_TIERn		0x0c	/* Timer पूर्णांकerrupt enable रेजिस्टर */
#घोषणा TPU_TSRn		0x10	/* Timer status रेजिस्टर */
#घोषणा TPU_TCNTn		0x14	/* Timer counter */
#घोषणा TPU_TGRAn		0x18	/* Timer general रेजिस्टर A */
#घोषणा TPU_TGRBn		0x1c	/* Timer general रेजिस्टर B */
#घोषणा TPU_TGRCn		0x20	/* Timer general रेजिस्टर C */
#घोषणा TPU_TGRDn		0x24	/* Timer general रेजिस्टर D */

#घोषणा TPU_CHANNEL_OFFSET	0x10
#घोषणा TPU_CHANNEL_SIZE	0x40

क्रमागत tpu_pin_state अणु
	TPU_PIN_INACTIVE,		/* Pin is driven inactive */
	TPU_PIN_PWM,			/* Pin is driven by PWM */
	TPU_PIN_ACTIVE,			/* Pin is driven active */
पूर्ण;

काष्ठा tpu_device;

काष्ठा tpu_pwm_device अणु
	bool समयr_on;			/* Whether the समयr is running */

	काष्ठा tpu_device *tpu;
	अचिन्हित पूर्णांक channel;		/* Channel number in the TPU */

	क्रमागत pwm_polarity polarity;
	अचिन्हित पूर्णांक prescaler;
	u16 period;
	u16 duty;
पूर्ण;

काष्ठा tpu_device अणु
	काष्ठा platक्रमm_device *pdev;
	काष्ठा pwm_chip chip;
	spinlock_t lock;

	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा to_tpu_device(c)	container_of(c, काष्ठा tpu_device, chip)

अटल व्योम tpu_pwm_ग_लिखो(काष्ठा tpu_pwm_device *pwm, पूर्णांक reg_nr, u16 value)
अणु
	व्योम __iomem *base = pwm->tpu->base + TPU_CHANNEL_OFFSET
			   + pwm->channel * TPU_CHANNEL_SIZE;

	ioग_लिखो16(value, base + reg_nr);
पूर्ण

अटल व्योम tpu_pwm_set_pin(काष्ठा tpu_pwm_device *pwm,
			    क्रमागत tpu_pin_state state)
अणु
	अटल स्थिर अक्षर * स्थिर states[] = अणु "inactive", "PWM", "active" पूर्ण;

	dev_dbg(&pwm->tpu->pdev->dev, "%u: configuring pin as %s\n",
		pwm->channel, states[state]);

	चयन (state) अणु
	हाल TPU_PIN_INACTIVE:
		tpu_pwm_ग_लिखो(pwm, TPU_TIORn,
			      pwm->polarity == PWM_POLARITY_INVERSED ?
			      TPU_TIOR_IOA_1 : TPU_TIOR_IOA_0);
		अवरोध;
	हाल TPU_PIN_PWM:
		tpu_pwm_ग_लिखो(pwm, TPU_TIORn,
			      pwm->polarity == PWM_POLARITY_INVERSED ?
			      TPU_TIOR_IOA_0_SET : TPU_TIOR_IOA_1_CLR);
		अवरोध;
	हाल TPU_PIN_ACTIVE:
		tpu_pwm_ग_लिखो(pwm, TPU_TIORn,
			      pwm->polarity == PWM_POLARITY_INVERSED ?
			      TPU_TIOR_IOA_0 : TPU_TIOR_IOA_1);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम tpu_pwm_start_stop(काष्ठा tpu_pwm_device *pwm, पूर्णांक start)
अणु
	अचिन्हित दीर्घ flags;
	u16 value;

	spin_lock_irqsave(&pwm->tpu->lock, flags);
	value = ioपढ़ो16(pwm->tpu->base + TPU_TSTR);

	अगर (start)
		value |= 1 << pwm->channel;
	अन्यथा
		value &= ~(1 << pwm->channel);

	ioग_लिखो16(value, pwm->tpu->base + TPU_TSTR);
	spin_unlock_irqrestore(&pwm->tpu->lock, flags);
पूर्ण

अटल पूर्णांक tpu_pwm_समयr_start(काष्ठा tpu_pwm_device *pwm)
अणु
	पूर्णांक ret;

	अगर (!pwm->समयr_on) अणु
		/* Wake up device and enable घड़ी. */
		pm_runसमय_get_sync(&pwm->tpu->pdev->dev);
		ret = clk_prepare_enable(pwm->tpu->clk);
		अगर (ret) अणु
			dev_err(&pwm->tpu->pdev->dev, "cannot enable clock\n");
			वापस ret;
		पूर्ण
		pwm->समयr_on = true;
	पूर्ण

	/*
	 * Make sure the channel is stopped, as we need to reconfigure it
	 * completely. First drive the pin to the inactive state to aव्योम
	 * glitches.
	 */
	tpu_pwm_set_pin(pwm, TPU_PIN_INACTIVE);
	tpu_pwm_start_stop(pwm, false);

	/*
	 * - Clear TCNT on TGRB match
	 * - Count on rising edge
	 * - Set prescaler
	 * - Output 0 until TGRA, output 1 until TGRB (active low polarity)
	 * - Output 1 until TGRA, output 0 until TGRB (active high polarity
	 * - PWM mode
	 */
	tpu_pwm_ग_लिखो(pwm, TPU_TCRn, TPU_TCR_CCLR_TGRB | TPU_TCR_CKEG_RISING |
		      pwm->prescaler);
	tpu_pwm_ग_लिखो(pwm, TPU_TMDRn, TPU_TMDR_MD_PWM);
	tpu_pwm_set_pin(pwm, TPU_PIN_PWM);
	tpu_pwm_ग_लिखो(pwm, TPU_TGRAn, pwm->duty);
	tpu_pwm_ग_लिखो(pwm, TPU_TGRBn, pwm->period);

	dev_dbg(&pwm->tpu->pdev->dev, "%u: TGRA 0x%04x TGRB 0x%04x\n",
		pwm->channel, pwm->duty, pwm->period);

	/* Start the channel. */
	tpu_pwm_start_stop(pwm, true);

	वापस 0;
पूर्ण

अटल व्योम tpu_pwm_समयr_stop(काष्ठा tpu_pwm_device *pwm)
अणु
	अगर (!pwm->समयr_on)
		वापस;

	/* Disable channel. */
	tpu_pwm_start_stop(pwm, false);

	/* Stop घड़ी and mark device as idle. */
	clk_disable_unprepare(pwm->tpu->clk);
	pm_runसमय_put(&pwm->tpu->pdev->dev);

	pwm->समयr_on = false;
पूर्ण

/* -----------------------------------------------------------------------------
 * PWM API
 */

अटल पूर्णांक tpu_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *_pwm)
अणु
	काष्ठा tpu_device *tpu = to_tpu_device(chip);
	काष्ठा tpu_pwm_device *pwm;

	अगर (_pwm->hwpwm >= TPU_CHANNEL_MAX)
		वापस -EINVAL;

	pwm = kzalloc(माप(*pwm), GFP_KERNEL);
	अगर (pwm == शून्य)
		वापस -ENOMEM;

	pwm->tpu = tpu;
	pwm->channel = _pwm->hwpwm;
	pwm->polarity = PWM_POLARITY_NORMAL;
	pwm->prescaler = 0;
	pwm->period = 0;
	pwm->duty = 0;

	pwm->समयr_on = false;

	pwm_set_chip_data(_pwm, pwm);

	वापस 0;
पूर्ण

अटल व्योम tpu_pwm_मुक्त(काष्ठा pwm_chip *chip, काष्ठा pwm_device *_pwm)
अणु
	काष्ठा tpu_pwm_device *pwm = pwm_get_chip_data(_pwm);

	tpu_pwm_समयr_stop(pwm);
	kमुक्त(pwm);
पूर्ण

अटल पूर्णांक tpu_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *_pwm,
			  पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	अटल स्थिर अचिन्हित पूर्णांक prescalers[] = अणु 1, 4, 16, 64 पूर्ण;
	काष्ठा tpu_pwm_device *pwm = pwm_get_chip_data(_pwm);
	काष्ठा tpu_device *tpu = to_tpu_device(chip);
	अचिन्हित पूर्णांक prescaler;
	bool duty_only = false;
	u32 clk_rate;
	u32 period;
	u32 duty;
	पूर्णांक ret;

	/*
	 * Pick a prescaler to aव्योम overflowing the counter.
	 * TODO: Pick the highest acceptable prescaler.
	 */
	clk_rate = clk_get_rate(tpu->clk);

	क्रम (prescaler = 0; prescaler < ARRAY_SIZE(prescalers); ++prescaler) अणु
		period = clk_rate / prescalers[prescaler]
		       / (NSEC_PER_SEC / period_ns);
		अगर (period <= 0xffff)
			अवरोध;
	पूर्ण

	अगर (prescaler == ARRAY_SIZE(prescalers) || period == 0) अणु
		dev_err(&tpu->pdev->dev, "clock rate mismatch\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (duty_ns) अणु
		duty = clk_rate / prescalers[prescaler]
		     / (NSEC_PER_SEC / duty_ns);
		अगर (duty > period)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		duty = 0;
	पूर्ण

	dev_dbg(&tpu->pdev->dev,
		"rate %u, prescaler %u, period %u, duty %u\n",
		clk_rate, prescalers[prescaler], period, duty);

	अगर (pwm->prescaler == prescaler && pwm->period == period)
		duty_only = true;

	pwm->prescaler = prescaler;
	pwm->period = period;
	pwm->duty = duty;

	/* If the channel is disabled we're करोne. */
	अगर (!pwm_is_enabled(_pwm))
		वापस 0;

	अगर (duty_only && pwm->समयr_on) अणु
		/*
		 * If only the duty cycle changed and the समयr is alपढ़ोy
		 * running, there's no need to reconfigure it completely, Just
		 * modअगरy the duty cycle.
		 */
		tpu_pwm_ग_लिखो(pwm, TPU_TGRAn, pwm->duty);
		dev_dbg(&tpu->pdev->dev, "%u: TGRA 0x%04x\n", pwm->channel,
			pwm->duty);
	पूर्ण अन्यथा अणु
		/* Otherwise perक्रमm a full reconfiguration. */
		ret = tpu_pwm_समयr_start(pwm);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (duty == 0 || duty == period) अणु
		/*
		 * To aव्योम running the समयr when not strictly required, handle
		 * 0% and 100% duty cycles as fixed levels and stop the समयr.
		 */
		tpu_pwm_set_pin(pwm, duty ? TPU_PIN_ACTIVE : TPU_PIN_INACTIVE);
		tpu_pwm_समयr_stop(pwm);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tpu_pwm_set_polarity(काष्ठा pwm_chip *chip, काष्ठा pwm_device *_pwm,
				क्रमागत pwm_polarity polarity)
अणु
	काष्ठा tpu_pwm_device *pwm = pwm_get_chip_data(_pwm);

	pwm->polarity = polarity;

	वापस 0;
पूर्ण

अटल पूर्णांक tpu_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *_pwm)
अणु
	काष्ठा tpu_pwm_device *pwm = pwm_get_chip_data(_pwm);
	पूर्णांक ret;

	ret = tpu_pwm_समयr_start(pwm);
	अगर (ret < 0)
		वापस ret;

	/*
	 * To aव्योम running the समयr when not strictly required, handle 0% and
	 * 100% duty cycles as fixed levels and stop the समयr.
	 */
	अगर (pwm->duty == 0 || pwm->duty == pwm->period) अणु
		tpu_pwm_set_pin(pwm, pwm->duty ?
				TPU_PIN_ACTIVE : TPU_PIN_INACTIVE);
		tpu_pwm_समयr_stop(pwm);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम tpu_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *_pwm)
अणु
	काष्ठा tpu_pwm_device *pwm = pwm_get_chip_data(_pwm);

	/* The समयr must be running to modअगरy the pin output configuration. */
	tpu_pwm_समयr_start(pwm);
	tpu_pwm_set_pin(pwm, TPU_PIN_INACTIVE);
	tpu_pwm_समयr_stop(pwm);
पूर्ण

अटल स्थिर काष्ठा pwm_ops tpu_pwm_ops = अणु
	.request = tpu_pwm_request,
	.मुक्त = tpu_pwm_मुक्त,
	.config = tpu_pwm_config,
	.set_polarity = tpu_pwm_set_polarity,
	.enable = tpu_pwm_enable,
	.disable = tpu_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

/* -----------------------------------------------------------------------------
 * Probe and हटाओ
 */

अटल पूर्णांक tpu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpu_device *tpu;
	पूर्णांक ret;

	tpu = devm_kzalloc(&pdev->dev, माप(*tpu), GFP_KERNEL);
	अगर (tpu == शून्य)
		वापस -ENOMEM;

	spin_lock_init(&tpu->lock);
	tpu->pdev = pdev;

	/* Map memory, get घड़ी and pin control. */
	tpu->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(tpu->base))
		वापस PTR_ERR(tpu->base);

	tpu->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(tpu->clk)) अणु
		dev_err(&pdev->dev, "cannot get clock\n");
		वापस PTR_ERR(tpu->clk);
	पूर्ण

	/* Initialize and रेजिस्टर the device. */
	platक्रमm_set_drvdata(pdev, tpu);

	tpu->chip.dev = &pdev->dev;
	tpu->chip.ops = &tpu_pwm_ops;
	tpu->chip.of_xlate = of_pwm_xlate_with_flags;
	tpu->chip.of_pwm_n_cells = 3;
	tpu->chip.npwm = TPU_CHANNEL_MAX;

	pm_runसमय_enable(&pdev->dev);

	ret = pwmchip_add(&tpu->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to register PWM chip\n");
		pm_runसमय_disable(&pdev->dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tpu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tpu_device *tpu = platक्रमm_get_drvdata(pdev);
	पूर्णांक ret;

	ret = pwmchip_हटाओ(&tpu->chip);

	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id tpu_of_table[] = अणु
	अणु .compatible = "renesas,tpu-r8a73a4", पूर्ण,
	अणु .compatible = "renesas,tpu-r8a7740", पूर्ण,
	अणु .compatible = "renesas,tpu-r8a7790", पूर्ण,
	अणु .compatible = "renesas,tpu", पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, tpu_of_table);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver tpu_driver = अणु
	.probe		= tpu_probe,
	.हटाओ		= tpu_हटाओ,
	.driver		= अणु
		.name	= "renesas-tpu-pwm",
		.of_match_table = of_match_ptr(tpu_of_table),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(tpu_driver);

MODULE_AUTHOR("Laurent Pinchart <laurent.pinchart@ideasonboard.com>");
MODULE_DESCRIPTION("Renesas TPU PWM Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:renesas-tpu-pwm");
