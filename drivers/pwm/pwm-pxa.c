<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/pwm/pwm-pxa.c
 *
 * simple driver क्रम PWM (Pulse Width Modulator) controller
 *
 * 2008-02-13	initial version
 *		eric miao <eric.miao@marvell.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/pwm.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/भाग64.h>

#घोषणा HAS_SECONDARY_PWM	0x10

अटल स्थिर काष्ठा platक्रमm_device_id pwm_id_table[] = अणु
	/*   PWM    has_secondary_pwm? */
	अणु "pxa25x-pwm", 0 पूर्ण,
	अणु "pxa27x-pwm", HAS_SECONDARY_PWM पूर्ण,
	अणु "pxa168-pwm", 0 पूर्ण,
	अणु "pxa910-pwm", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, pwm_id_table);

/* PWM रेजिस्टरs and bits definitions */
#घोषणा PWMCR		(0x00)
#घोषणा PWMDCR		(0x04)
#घोषणा PWMPCR		(0x08)

#घोषणा PWMCR_SD	(1 << 6)
#घोषणा PWMDCR_FD	(1 << 10)

काष्ठा pxa_pwm_chip अणु
	काष्ठा pwm_chip	chip;
	काष्ठा device	*dev;

	काष्ठा clk	*clk;
	व्योम __iomem	*mmio_base;
पूर्ण;

अटल अंतरभूत काष्ठा pxa_pwm_chip *to_pxa_pwm_chip(काष्ठा pwm_chip *chip)
अणु
	वापस container_of(chip, काष्ठा pxa_pwm_chip, chip);
पूर्ण

/*
 * period_ns = 10^9 * (PRESCALE + 1) * (PV + 1) / PWM_CLK_RATE
 * duty_ns   = 10^9 * (PRESCALE + 1) * DC / PWM_CLK_RATE
 */
अटल पूर्णांक pxa_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
			  पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा pxa_pwm_chip *pc = to_pxa_pwm_chip(chip);
	अचिन्हित दीर्घ दीर्घ c;
	अचिन्हित दीर्घ period_cycles, prescale, pv, dc;
	अचिन्हित दीर्घ offset;
	पूर्णांक rc;

	offset = pwm->hwpwm ? 0x10 : 0;

	c = clk_get_rate(pc->clk);
	c = c * period_ns;
	करो_भाग(c, 1000000000);
	period_cycles = c;

	अगर (period_cycles < 1)
		period_cycles = 1;
	prescale = (period_cycles - 1) / 1024;
	pv = period_cycles / (prescale + 1) - 1;

	अगर (prescale > 63)
		वापस -EINVAL;

	अगर (duty_ns == period_ns)
		dc = PWMDCR_FD;
	अन्यथा
		dc = (pv + 1) * duty_ns / period_ns;

	/* NOTE: the घड़ी to PWM has to be enabled first
	 * beक्रमe writing to the रेजिस्टरs
	 */
	rc = clk_prepare_enable(pc->clk);
	अगर (rc < 0)
		वापस rc;

	ग_लिखोl(prescale, pc->mmio_base + offset + PWMCR);
	ग_लिखोl(dc, pc->mmio_base + offset + PWMDCR);
	ग_लिखोl(pv, pc->mmio_base + offset + PWMPCR);

	clk_disable_unprepare(pc->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक pxa_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pxa_pwm_chip *pc = to_pxa_pwm_chip(chip);

	वापस clk_prepare_enable(pc->clk);
पूर्ण

अटल व्योम pxa_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा pxa_pwm_chip *pc = to_pxa_pwm_chip(chip);

	clk_disable_unprepare(pc->clk);
पूर्ण

अटल स्थिर काष्ठा pwm_ops pxa_pwm_ops = अणु
	.config = pxa_pwm_config,
	.enable = pxa_pwm_enable,
	.disable = pxa_pwm_disable,
	.owner = THIS_MODULE,
पूर्ण;

#अगर_घोषित CONFIG_OF
/*
 * Device tree users must create one device instance क्रम each PWM channel.
 * Hence we dispense with the HAS_SECONDARY_PWM and "tell" the original driver
 * code that this is a single channel pxa25x-pwm.  Currently all devices are
 * supported identically.
 */
अटल स्थिर काष्ठा of_device_id pwm_of_match[] = अणु
	अणु .compatible = "marvell,pxa250-pwm", .data = &pwm_id_table[0]पूर्ण,
	अणु .compatible = "marvell,pxa270-pwm", .data = &pwm_id_table[0]पूर्ण,
	अणु .compatible = "marvell,pxa168-pwm", .data = &pwm_id_table[0]पूर्ण,
	अणु .compatible = "marvell,pxa910-pwm", .data = &pwm_id_table[0]पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pwm_of_match);
#अन्यथा
#घोषणा pwm_of_match शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा platक्रमm_device_id *pxa_pwm_get_id_dt(काष्ठा device *dev)
अणु
	स्थिर काष्ठा of_device_id *id = of_match_device(pwm_of_match, dev);

	वापस id ? id->data : शून्य;
पूर्ण

अटल काष्ठा pwm_device *
pxa_pwm_of_xlate(काष्ठा pwm_chip *pc, स्थिर काष्ठा of_phandle_args *args)
अणु
	काष्ठा pwm_device *pwm;

	pwm = pwm_request_from_chip(pc, 0, शून्य);
	अगर (IS_ERR(pwm))
		वापस pwm;

	pwm->args.period = args->args[0];

	वापस pwm;
पूर्ण

अटल पूर्णांक pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *id = platक्रमm_get_device_id(pdev);
	काष्ठा pxa_pwm_chip *pwm;
	पूर्णांक ret = 0;

	अगर (IS_ENABLED(CONFIG_OF) && id == शून्य)
		id = pxa_pwm_get_id_dt(&pdev->dev);

	अगर (id == शून्य)
		वापस -EINVAL;

	pwm = devm_kzalloc(&pdev->dev, माप(*pwm), GFP_KERNEL);
	अगर (pwm == शून्य)
		वापस -ENOMEM;

	pwm->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pwm->clk))
		वापस PTR_ERR(pwm->clk);

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &pxa_pwm_ops;
	pwm->chip.npwm = (id->driver_data & HAS_SECONDARY_PWM) ? 2 : 1;

	अगर (IS_ENABLED(CONFIG_OF)) अणु
		pwm->chip.of_xlate = pxa_pwm_of_xlate;
		pwm->chip.of_pwm_n_cells = 1;
	पूर्ण

	pwm->mmio_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(pwm->mmio_base))
		वापस PTR_ERR(pwm->mmio_base);

	ret = pwmchip_add(&pwm->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, pwm);
	वापस 0;
पूर्ण

अटल पूर्णांक pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa_pwm_chip *chip;

	chip = platक्रमm_get_drvdata(pdev);
	अगर (chip == शून्य)
		वापस -ENODEV;

	वापस pwmchip_हटाओ(&chip->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver pwm_driver = अणु
	.driver		= अणु
		.name	= "pxa25x-pwm",
		.of_match_table = pwm_of_match,
	पूर्ण,
	.probe		= pwm_probe,
	.हटाओ		= pwm_हटाओ,
	.id_table	= pwm_id_table,
पूर्ण;

module_platक्रमm_driver(pwm_driver);

MODULE_LICENSE("GPL v2");
