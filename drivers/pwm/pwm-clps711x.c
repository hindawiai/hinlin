<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Cirrus Logic CLPS711X PWM driver
 * Author: Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

काष्ठा clps711x_chip अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *pmpcon;
	काष्ठा clk *clk;
	spinlock_t lock;
पूर्ण;

अटल अंतरभूत काष्ठा clps711x_chip *to_clps711x_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा clps711x_chip, chip);
पूर्ण

अटल व्योम clps711x_pwm_update_val(काष्ठा clps711x_chip *priv, u32 n, u32 v)
अणु
	/* PWM0 - bits 4..7, PWM1 - bits 8..11 */
	u32 shअगरt = (n + 1) * 4;
	अचिन्हित दीर्घ flags;
	u32 पंचांगp;

	spin_lock_irqsave(&priv->lock, flags);

	पंचांगp = पढ़ोl(priv->pmpcon);
	पंचांगp &= ~(0xf << shअगरt);
	पंचांगp |= v << shअगरt;
	ग_लिखोl(पंचांगp, priv->pmpcon);

	spin_unlock_irqrestore(&priv->lock, flags);
पूर्ण

अटल अचिन्हित पूर्णांक clps711x_get_duty(काष्ठा pwm_device *pwm, अचिन्हित पूर्णांक v)
अणु
	/* Duty cycle 0..15 max */
	वापस DIV64_U64_ROUND_CLOSEST(v * 0xf, pwm->args.period);
पूर्ण

अटल पूर्णांक clps711x_pwm_request(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा clps711x_chip *priv = to_clps711x_chip(chip);
	अचिन्हित पूर्णांक freq = clk_get_rate(priv->clk);

	अगर (!freq)
		वापस -EINVAL;

	/* Store स्थिरant period value */
	pwm->args.period = DIV_ROUND_CLOSEST(NSEC_PER_SEC, freq);

	वापस 0;
पूर्ण

अटल पूर्णांक clps711x_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			       पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा clps711x_chip *priv = to_clps711x_chip(chip);
	अचिन्हित पूर्णांक duty;

	अगर (period_ns != pwm->args.period)
		वापस -EINVAL;

	duty = clps711x_get_duty(pwm, duty_ns);
	clps711x_pwm_update_val(priv, pwm->hwpwm, duty);

	वापस 0;
पूर्ण

अटल पूर्णांक clps711x_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा clps711x_chip *priv = to_clps711x_chip(chip);
	अचिन्हित पूर्णांक duty;

	duty = clps711x_get_duty(pwm, pwm_get_duty_cycle(pwm));
	clps711x_pwm_update_val(priv, pwm->hwpwm, duty);

	वापस 0;
पूर्ण

अटल व्योम clps711x_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा clps711x_chip *priv = to_clps711x_chip(chip);

	clps711x_pwm_update_val(priv, pwm->hwpwm, 0);
पूर्ण

अटल स्थिर काष्ठा pwm_ops clps711x_pwm_ops = अणु
	.request = clps711x_pwm_request,
	.config = clps711x_pwm_config,
	.enable = clps711x_pwm_enable,
	.disable = clps711x_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

अटल काष्ठा pwm_device *clps711x_pwm_xlate(काष्ठा pwm_chip *chip,
					     स्थिर काष्ठा of_phandle_args *args)
अणु
	अगर (args->args[0] >= chip->npwm)
		वापस ERR_PTR(-EINVAL);

	वापस pwm_request_from_chip(chip, args->args[0], शून्य);
पूर्ण

अटल पूर्णांक clps711x_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clps711x_chip *priv;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->pmpcon = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->pmpcon))
		वापस PTR_ERR(priv->pmpcon);

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	priv->chip.ops = &clps711x_pwm_ops;
	priv->chip.dev = &pdev->dev;
	priv->chip.npwm = 2;
	priv->chip.of_xlate = clps711x_pwm_xlate;
	priv->chip.of_pwm_n_cells = 1;

	spin_lock_init(&priv->lock);

	platक्रमm_set_drvdata(pdev, priv);

	वापस pwmchip_add(&priv->chip);
पूर्ण

अटल पूर्णांक clps711x_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clps711x_chip *priv = platक्रमm_get_drvdata(pdev);

	वापस pwmchip_हटाओ(&priv->chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id __maybe_unused clps711x_pwm_dt_ids[] = अणु
	अणु .compatible = "cirrus,ep7209-pwm", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clps711x_pwm_dt_ids);

अटल काष्ठा platक्रमm_driver clps711x_pwm_driver = अणु
	.driver = अणु
		.name = "clps711x-pwm",
		.of_match_table = of_match_ptr(clps711x_pwm_dt_ids),
	पूर्ण,
	.probe = clps711x_pwm_probe,
	.हटाओ = clps711x_pwm_हटाओ,
पूर्ण;
module_platक्रमm_driver(clps711x_pwm_driver);

MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("Cirrus Logic CLPS711X PWM driver");
MODULE_LICENSE("GPL");
