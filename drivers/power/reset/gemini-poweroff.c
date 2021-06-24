<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Gemini घातer management controller
 * Copyright (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 *
 * Inspired by code from the SL3516 board support by Jason Lee
 * Inspired by code from Janos Laube <janos.dev@gmail.com>
 */
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>

#घोषणा GEMINI_PWC_ID		0x00010500
#घोषणा	GEMINI_PWC_IDREG	0x00
#घोषणा	GEMINI_PWC_CTRLREG	0x04
#घोषणा	GEMINI_PWC_STATREG	0x08

#घोषणा GEMINI_CTRL_SHUTDOWN	BIT(0)
#घोषणा GEMINI_CTRL_ENABLE	BIT(1)
#घोषणा GEMINI_CTRL_IRQ_CLR	BIT(2)

#घोषणा GEMINI_STAT_CIR		BIT(4)
#घोषणा	GEMINI_STAT_RTC		BIT(5)
#घोषणा	GEMINI_STAT_POWERBUTTON	BIT(6)

काष्ठा gemini_घातercon अणु
        काष्ठा device           *dev;
        व्योम __iomem            *base;
पूर्ण;

अटल irqवापस_t gemini_घातerbutton_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gemini_घातercon *gpw = data;
	u32 val;

	/* ACK the IRQ */
	val = पढ़ोl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_IRQ_CLR;
	ग_लिखोl(val, gpw->base + GEMINI_PWC_CTRLREG);

	val = पढ़ोl(gpw->base + GEMINI_PWC_STATREG);
	val &= 0x70U;
	चयन (val) अणु
	हाल GEMINI_STAT_CIR:
		/*
		 * We करो not yet have a driver क्रम the infrared
		 * controller so it can cause spurious घातeroff
		 * events. Ignore those क्रम now.
		 */
		dev_info(gpw->dev, "infrared poweroff - ignored\n");
		अवरोध;
	हाल GEMINI_STAT_RTC:
		dev_info(gpw->dev, "RTC poweroff\n");
		orderly_घातeroff(true);
		अवरोध;
	हाल GEMINI_STAT_POWERBUTTON:
		dev_info(gpw->dev, "poweroff button pressed\n");
		orderly_घातeroff(true);
		अवरोध;
	शेष:
		dev_info(gpw->dev, "other power management IRQ\n");
		अवरोध;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* This callback needs this अटल local as it has व्योम as argument */
अटल काष्ठा gemini_घातercon *gpw_घातeroff;

अटल व्योम gemini_घातeroff(व्योम)
अणु
	काष्ठा gemini_घातercon *gpw = gpw_घातeroff;
	u32 val;

	dev_crit(gpw->dev, "Gemini power off\n");
	val = पढ़ोl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_ENABLE | GEMINI_CTRL_IRQ_CLR;
	ग_लिखोl(val, gpw->base + GEMINI_PWC_CTRLREG);

	val &= ~GEMINI_CTRL_ENABLE;
	val |= GEMINI_CTRL_SHUTDOWN;
	ग_लिखोl(val, gpw->base + GEMINI_PWC_CTRLREG);
पूर्ण

अटल पूर्णांक gemini_घातeroff_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;
	काष्ठा gemini_घातercon *gpw;
	u32 val;
	पूर्णांक irq;
	पूर्णांक ret;

	gpw = devm_kzalloc(dev, माप(*gpw), GFP_KERNEL);
	अगर (!gpw)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	gpw->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(gpw->base))
		वापस PTR_ERR(gpw->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!irq)
		वापस -EINVAL;

	gpw->dev = dev;

	val = पढ़ोl(gpw->base + GEMINI_PWC_IDREG);
	val &= 0xFFFFFF00U;
	अगर (val != GEMINI_PWC_ID) अणु
		dev_err(dev, "wrong power controller ID: %08x\n",
			val);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Enable the घातer controller. This is crucial on Gemini
	 * प्रणालीs: अगर this is not करोne, pressing the घातer button
	 * will result in unconditional घातeroff without any warning.
	 * This makes the kernel handle the घातeroff.
	 */
	val = पढ़ोl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_ENABLE;
	ग_लिखोl(val, gpw->base + GEMINI_PWC_CTRLREG);

	/* Clear the IRQ */
	val = पढ़ोl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_IRQ_CLR;
	ग_लिखोl(val, gpw->base + GEMINI_PWC_CTRLREG);

	/* Wait क्रम this to clear */
	val = पढ़ोl(gpw->base + GEMINI_PWC_STATREG);
	जबतक (val & 0x70U)
		val = पढ़ोl(gpw->base + GEMINI_PWC_STATREG);

	/* Clear the IRQ again */
	val = पढ़ोl(gpw->base + GEMINI_PWC_CTRLREG);
	val |= GEMINI_CTRL_IRQ_CLR;
	ग_लिखोl(val, gpw->base + GEMINI_PWC_CTRLREG);

	ret = devm_request_irq(dev, irq, gemini_घातerbutton_पूर्णांकerrupt, 0,
			       "poweroff", gpw);
	अगर (ret)
		वापस ret;

	pm_घातer_off = gemini_घातeroff;
	gpw_घातeroff = gpw;

	dev_info(dev, "Gemini poweroff driver registered\n");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gemini_घातeroff_of_match[] = अणु
	अणु
		.compatible = "cortina,gemini-power-controller",
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver gemini_घातeroff_driver = अणु
	.probe = gemini_घातeroff_probe,
	.driver = अणु
		.name = "gemini-poweroff",
		.of_match_table = gemini_घातeroff_of_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(gemini_घातeroff_driver);
