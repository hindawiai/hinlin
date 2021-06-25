<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Interrupt support क्रम Cirrus Logic Madera codecs
 *
 * Copyright (C) 2015-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip/irq-madera.h>
#समावेश <linux/mfd/madera/core.h>
#समावेश <linux/mfd/madera/pdata.h>
#समावेश <linux/mfd/madera/रेजिस्टरs.h>

#घोषणा MADERA_IRQ(_irq, _reg)					\
	[MADERA_IRQ_ ## _irq] = अणु				\
		.reg_offset = (_reg) - MADERA_IRQ1_STATUS_2,	\
		.mask = MADERA_ ## _irq ## _EINT1		\
	पूर्ण

/* Mappings are the same क्रम all Madera codecs */
अटल स्थिर काष्ठा regmap_irq madera_irqs[MADERA_NUM_IRQ] = अणु
	MADERA_IRQ(FLL1_LOCK,		MADERA_IRQ1_STATUS_2),
	MADERA_IRQ(FLL2_LOCK,		MADERA_IRQ1_STATUS_2),
	MADERA_IRQ(FLL3_LOCK,		MADERA_IRQ1_STATUS_2),
	MADERA_IRQ(FLLAO_LOCK,		MADERA_IRQ1_STATUS_2),

	MADERA_IRQ(MICDET1,		MADERA_IRQ1_STATUS_6),
	MADERA_IRQ(MICDET2,		MADERA_IRQ1_STATUS_6),
	MADERA_IRQ(HPDET,		MADERA_IRQ1_STATUS_6),

	MADERA_IRQ(MICD_CLAMP_RISE,	MADERA_IRQ1_STATUS_7),
	MADERA_IRQ(MICD_CLAMP_FALL,	MADERA_IRQ1_STATUS_7),
	MADERA_IRQ(JD1_RISE,		MADERA_IRQ1_STATUS_7),
	MADERA_IRQ(JD1_FALL,		MADERA_IRQ1_STATUS_7),

	MADERA_IRQ(ASRC2_IN1_LOCK,	MADERA_IRQ1_STATUS_9),
	MADERA_IRQ(ASRC2_IN2_LOCK,	MADERA_IRQ1_STATUS_9),
	MADERA_IRQ(ASRC1_IN1_LOCK,	MADERA_IRQ1_STATUS_9),
	MADERA_IRQ(ASRC1_IN2_LOCK,	MADERA_IRQ1_STATUS_9),
	MADERA_IRQ(DRC2_SIG_DET,	MADERA_IRQ1_STATUS_9),
	MADERA_IRQ(DRC1_SIG_DET,	MADERA_IRQ1_STATUS_9),

	MADERA_IRQ(DSP_IRQ1,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ2,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ3,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ4,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ5,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ6,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ7,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ8,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ9,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ10,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ11,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ12,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ13,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ14,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ15,		MADERA_IRQ1_STATUS_11),
	MADERA_IRQ(DSP_IRQ16,		MADERA_IRQ1_STATUS_11),

	MADERA_IRQ(HP3R_SC,		MADERA_IRQ1_STATUS_12),
	MADERA_IRQ(HP3L_SC,		MADERA_IRQ1_STATUS_12),
	MADERA_IRQ(HP2R_SC,		MADERA_IRQ1_STATUS_12),
	MADERA_IRQ(HP2L_SC,		MADERA_IRQ1_STATUS_12),
	MADERA_IRQ(HP1R_SC,		MADERA_IRQ1_STATUS_12),
	MADERA_IRQ(HP1L_SC,		MADERA_IRQ1_STATUS_12),

	MADERA_IRQ(SPK_OVERHEAT_WARN,	MADERA_IRQ1_STATUS_15),
	MADERA_IRQ(SPK_OVERHEAT,	MADERA_IRQ1_STATUS_15),

	MADERA_IRQ(DSP1_BUS_ERR,	MADERA_IRQ1_STATUS_33),
	MADERA_IRQ(DSP2_BUS_ERR,	MADERA_IRQ1_STATUS_33),
	MADERA_IRQ(DSP3_BUS_ERR,	MADERA_IRQ1_STATUS_33),
	MADERA_IRQ(DSP4_BUS_ERR,	MADERA_IRQ1_STATUS_33),
	MADERA_IRQ(DSP5_BUS_ERR,	MADERA_IRQ1_STATUS_33),
	MADERA_IRQ(DSP6_BUS_ERR,	MADERA_IRQ1_STATUS_33),
	MADERA_IRQ(DSP7_BUS_ERR,	MADERA_IRQ1_STATUS_33),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip madera_irq_chip = अणु
	.name		= "madera IRQ",
	.status_base	= MADERA_IRQ1_STATUS_2,
	.mask_base	= MADERA_IRQ1_MASK_2,
	.ack_base	= MADERA_IRQ1_STATUS_2,
	.runसमय_pm	= true,
	.num_regs	= 32,
	.irqs		= madera_irqs,
	.num_irqs	= ARRAY_SIZE(madera_irqs),
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक madera_suspend(काष्ठा device *dev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(dev->parent);

	dev_dbg(madera->irq_dev, "Suspend, disabling IRQ\n");

	/*
	 * A runसमय resume would be needed to access the chip पूर्णांकerrupt
	 * controller but runसमय pm करोesn't function during suspend.
	 * Temporarily disable पूर्णांकerrupts until we reach suspend_noirq state.
	 */
	disable_irq(madera->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(dev->parent);

	dev_dbg(madera->irq_dev, "No IRQ suspend, reenabling IRQ\n");

	/* Re-enable पूर्णांकerrupts to service wakeup पूर्णांकerrupts from the chip */
	enable_irq(madera->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(dev->parent);

	dev_dbg(madera->irq_dev, "No IRQ resume, disabling IRQ\n");

	/*
	 * We can't handle पूर्णांकerrupts until runसमय pm is available again.
	 * Disable them temporarily.
	 */
	disable_irq(madera->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक madera_resume(काष्ठा device *dev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(dev->parent);

	dev_dbg(madera->irq_dev, "Resume, reenabling IRQ\n");

	/* Interrupts can now be handled */
	enable_irq(madera->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops madera_irq_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(madera_suspend, madera_resume)
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(madera_suspend_noirq,
				      madera_resume_noirq)
पूर्ण;

अटल पूर्णांक madera_irq_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);
	काष्ठा irq_data *irq_data;
	अचिन्हित पूर्णांक irq_flags = 0;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "probe\n");

	/*
	 * Read the flags from the पूर्णांकerrupt controller अगर not specअगरied
	 * by pdata
	 */
	irq_flags = madera->pdata.irq_flags;
	अगर (!irq_flags) अणु
		irq_data = irq_get_irq_data(madera->irq);
		अगर (!irq_data) अणु
			dev_err(&pdev->dev, "Invalid IRQ: %d\n", madera->irq);
			वापस -EINVAL;
		पूर्ण

		irq_flags = irqd_get_trigger_type(irq_data);

		/* Codec शेषs to trigger low, use this अगर no flags given */
		अगर (irq_flags == IRQ_TYPE_NONE)
			irq_flags = IRQF_TRIGGER_LOW;
	पूर्ण

	अगर (irq_flags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)) अणु
		dev_err(&pdev->dev, "Host interrupt not level-triggered\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * The silicon always starts at active-low, check अगर we need to
	 * चयन to active-high.
	 */
	अगर (irq_flags & IRQF_TRIGGER_HIGH) अणु
		ret = regmap_update_bits(madera->regmap, MADERA_IRQ1_CTRL,
					 MADERA_IRQ_POL_MASK, 0);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"Failed to set IRQ polarity: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * NOTE: regmap रेजिस्टरs this against the OF node of the parent of
	 * the regmap - that is, against the mfd driver
	 */
	ret = regmap_add_irq_chip(madera->regmap, madera->irq, IRQF_ONESHOT, 0,
				  &madera_irq_chip, &madera->irq_data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "add_irq_chip failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Save dev in parent MFD काष्ठा so it is accessible to siblings */
	madera->irq_dev = &pdev->dev;

	वापस 0;
पूर्ण

अटल पूर्णांक madera_irq_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा madera *madera = dev_get_drvdata(pdev->dev.parent);

	/*
	 * The IRQ is disabled by the parent MFD driver beक्रमe
	 * it starts cleaning up all child drivers
	 */
	madera->irq_dev = शून्य;
	regmap_del_irq_chip(madera->irq, madera->irq_data);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver madera_irq_driver = अणु
	.probe	= &madera_irq_probe,
	.हटाओ = &madera_irq_हटाओ,
	.driver = अणु
		.name	= "madera-irq",
		.pm	= &madera_irq_pm_ops,
	पूर्ण
पूर्ण;
module_platक्रमm_driver(madera_irq_driver);

MODULE_SOFTDEP("pre: madera");
MODULE_DESCRIPTION("Madera IRQ driver");
MODULE_AUTHOR("Richard Fitzgerald <rf@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
