<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/pwm/pwm-vt8500.c
 *
 * Copyright (C) 2012 Tony Prisk <linux@prisktech.co.nz>
 * Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/pwm.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>

#समावेश <यंत्र/भाग64.h>

#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_address.h>

/*
 * SoC architecture allocates रेजिस्टर space क्रम 4 PWMs but only
 * 2 are currently implemented.
 */
#घोषणा VT8500_NR_PWMS	2

#घोषणा REG_CTRL(pwm)		(((pwm) << 4) + 0x00)
#घोषणा REG_SCALAR(pwm)		(((pwm) << 4) + 0x04)
#घोषणा REG_PERIOD(pwm)		(((pwm) << 4) + 0x08)
#घोषणा REG_DUTY(pwm)		(((pwm) << 4) + 0x0C)
#घोषणा REG_STATUS		0x40

#घोषणा CTRL_ENABLE		BIT(0)
#घोषणा CTRL_INVERT		BIT(1)
#घोषणा CTRL_AUTOLOAD		BIT(2)
#घोषणा CTRL_STOP_IMM		BIT(3)
#घोषणा CTRL_LOAD_PRESCALE	BIT(4)
#घोषणा CTRL_LOAD_PERIOD	BIT(5)

#घोषणा STATUS_CTRL_UPDATE	BIT(0)
#घोषणा STATUS_SCALAR_UPDATE	BIT(1)
#घोषणा STATUS_PERIOD_UPDATE	BIT(2)
#घोषणा STATUS_DUTY_UPDATE	BIT(3)
#घोषणा STATUS_ALL_UPDATE	0x0F

काष्ठा vt8500_chip अणु
	काष्ठा pwm_chip chip;
	व्योम __iomem *base;
	काष्ठा clk *clk;
पूर्ण;

#घोषणा to_vt8500_chip(chip)	container_of(chip, काष्ठा vt8500_chip, chip)

#घोषणा msecs_to_loops(t) (loops_per_jअगरfy / 1000 * HZ * t)
अटल अंतरभूत व्योम pwm_busy_रुको(काष्ठा vt8500_chip *vt8500, पूर्णांक nr, u8 biपंचांगask)
अणु
	पूर्णांक loops = msecs_to_loops(10);
	u32 mask = biपंचांगask << (nr << 8);

	जबतक ((पढ़ोl(vt8500->base + REG_STATUS) & mask) && --loops)
		cpu_relax();

	अगर (unlikely(!loops))
		dev_warn(vt8500->chip.dev, "Waiting for status bits 0x%x to clear timed out\n",
			 mask);
पूर्ण

अटल पूर्णांक vt8500_pwm_config(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm,
		पूर्णांक duty_ns, पूर्णांक period_ns)
अणु
	काष्ठा vt8500_chip *vt8500 = to_vt8500_chip(chip);
	अचिन्हित दीर्घ दीर्घ c;
	अचिन्हित दीर्घ period_cycles, prescale, pv, dc;
	पूर्णांक err;
	u32 val;

	err = clk_enable(vt8500->clk);
	अगर (err < 0) अणु
		dev_err(chip->dev, "failed to enable clock\n");
		वापस err;
	पूर्ण

	c = clk_get_rate(vt8500->clk);
	c = c * period_ns;
	करो_भाग(c, 1000000000);
	period_cycles = c;

	अगर (period_cycles < 1)
		period_cycles = 1;
	prescale = (period_cycles - 1) / 4096;
	pv = period_cycles / (prescale + 1) - 1;
	अगर (pv > 4095)
		pv = 4095;

	अगर (prescale > 1023) अणु
		clk_disable(vt8500->clk);
		वापस -EINVAL;
	पूर्ण

	c = (अचिन्हित दीर्घ दीर्घ)pv * duty_ns;
	करो_भाग(c, period_ns);
	dc = c;

	ग_लिखोl(prescale, vt8500->base + REG_SCALAR(pwm->hwpwm));
	pwm_busy_रुको(vt8500, pwm->hwpwm, STATUS_SCALAR_UPDATE);

	ग_लिखोl(pv, vt8500->base + REG_PERIOD(pwm->hwpwm));
	pwm_busy_रुको(vt8500, pwm->hwpwm, STATUS_PERIOD_UPDATE);

	ग_लिखोl(dc, vt8500->base + REG_DUTY(pwm->hwpwm));
	pwm_busy_रुको(vt8500, pwm->hwpwm, STATUS_DUTY_UPDATE);

	val = पढ़ोl(vt8500->base + REG_CTRL(pwm->hwpwm));
	val |= CTRL_AUTOLOAD;
	ग_लिखोl(val, vt8500->base + REG_CTRL(pwm->hwpwm));
	pwm_busy_रुको(vt8500, pwm->hwpwm, STATUS_CTRL_UPDATE);

	clk_disable(vt8500->clk);
	वापस 0;
पूर्ण

अटल पूर्णांक vt8500_pwm_enable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा vt8500_chip *vt8500 = to_vt8500_chip(chip);
	पूर्णांक err;
	u32 val;

	err = clk_enable(vt8500->clk);
	अगर (err < 0) अणु
		dev_err(chip->dev, "failed to enable clock\n");
		वापस err;
	पूर्ण

	val = पढ़ोl(vt8500->base + REG_CTRL(pwm->hwpwm));
	val |= CTRL_ENABLE;
	ग_लिखोl(val, vt8500->base + REG_CTRL(pwm->hwpwm));
	pwm_busy_रुको(vt8500, pwm->hwpwm, STATUS_CTRL_UPDATE);

	वापस 0;
पूर्ण

अटल व्योम vt8500_pwm_disable(काष्ठा pwm_chip *chip, काष्ठा pwm_device *pwm)
अणु
	काष्ठा vt8500_chip *vt8500 = to_vt8500_chip(chip);
	u32 val;

	val = पढ़ोl(vt8500->base + REG_CTRL(pwm->hwpwm));
	val &= ~CTRL_ENABLE;
	ग_लिखोl(val, vt8500->base + REG_CTRL(pwm->hwpwm));
	pwm_busy_रुको(vt8500, pwm->hwpwm, STATUS_CTRL_UPDATE);

	clk_disable(vt8500->clk);
पूर्ण

अटल पूर्णांक vt8500_pwm_set_polarity(काष्ठा pwm_chip *chip,
				   काष्ठा pwm_device *pwm,
				   क्रमागत pwm_polarity polarity)
अणु
	काष्ठा vt8500_chip *vt8500 = to_vt8500_chip(chip);
	u32 val;

	val = पढ़ोl(vt8500->base + REG_CTRL(pwm->hwpwm));

	अगर (polarity == PWM_POLARITY_INVERSED)
		val |= CTRL_INVERT;
	अन्यथा
		val &= ~CTRL_INVERT;

	ग_लिखोl(val, vt8500->base + REG_CTRL(pwm->hwpwm));
	pwm_busy_रुको(vt8500, pwm->hwpwm, STATUS_CTRL_UPDATE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा pwm_ops vt8500_pwm_ops = अणु
	.enable = vt8500_pwm_enable,
	.disable = vt8500_pwm_disable,
	.config = vt8500_pwm_config,
	.set_polarity = vt8500_pwm_set_polarity,
	.owner = THIS_MODULE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vt8500_pwm_dt_ids[] = अणु
	अणु .compatible = "via,vt8500-pwm", पूर्ण,
	अणु /* Sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vt8500_pwm_dt_ids);

अटल पूर्णांक vt8500_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8500_chip *chip;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (!np) अणु
		dev_err(&pdev->dev, "invalid devicetree node\n");
		वापस -EINVAL;
	पूर्ण

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;

	chip->chip.dev = &pdev->dev;
	chip->chip.ops = &vt8500_pwm_ops;
	chip->chip.of_xlate = of_pwm_xlate_with_flags;
	chip->chip.of_pwm_n_cells = 3;
	chip->chip.npwm = VT8500_NR_PWMS;

	chip->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(chip->clk)) अणु
		dev_err(&pdev->dev, "clock source not specified\n");
		वापस PTR_ERR(chip->clk);
	पूर्ण

	chip->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(chip->base))
		वापस PTR_ERR(chip->base);

	ret = clk_prepare(chip->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to prepare clock\n");
		वापस ret;
	पूर्ण

	ret = pwmchip_add(&chip->chip);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to add PWM chip\n");
		clk_unprepare(chip->clk);
		वापस ret;
	पूर्ण

	platक्रमm_set_drvdata(pdev, chip);
	वापस ret;
पूर्ण

अटल पूर्णांक vt8500_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा vt8500_chip *chip;

	chip = platक्रमm_get_drvdata(pdev);
	अगर (chip == शून्य)
		वापस -ENODEV;

	clk_unprepare(chip->clk);

	वापस pwmchip_हटाओ(&chip->chip);
पूर्ण

अटल काष्ठा platक्रमm_driver vt8500_pwm_driver = अणु
	.probe		= vt8500_pwm_probe,
	.हटाओ		= vt8500_pwm_हटाओ,
	.driver		= अणु
		.name	= "vt8500-pwm",
		.of_match_table = vt8500_pwm_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(vt8500_pwm_driver);

MODULE_DESCRIPTION("VT8500 PWM Driver");
MODULE_AUTHOR("Tony Prisk <linux@prisktech.co.nz>");
MODULE_LICENSE("GPL v2");
