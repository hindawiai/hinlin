<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8994-irq.c  --  Interrupt controller support क्रम Wolfson WM8994
 *
 * Copyright 2010 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/wm8994/core.h>
#समावेश <linux/mfd/wm8994/pdata.h>
#समावेश <linux/mfd/wm8994/रेजिस्टरs.h>

#समावेश <linux/delay.h>

अटल स्थिर काष्ठा regmap_irq wm8994_irqs[] = अणु
	[WM8994_IRQ_TEMP_SHUT] = अणु
		.reg_offset = 1,
		.mask = WM8994_TEMP_SHUT_EINT,
	पूर्ण,
	[WM8994_IRQ_MIC1_DET] = अणु
		.reg_offset = 1,
		.mask = WM8994_MIC1_DET_EINT,
	पूर्ण,
	[WM8994_IRQ_MIC1_SHRT] = अणु
		.reg_offset = 1,
		.mask = WM8994_MIC1_SHRT_EINT,
	पूर्ण,
	[WM8994_IRQ_MIC2_DET] = अणु
		.reg_offset = 1,
		.mask = WM8994_MIC2_DET_EINT,
	पूर्ण,
	[WM8994_IRQ_MIC2_SHRT] = अणु
		.reg_offset = 1,
		.mask = WM8994_MIC2_SHRT_EINT,
	पूर्ण,
	[WM8994_IRQ_FLL1_LOCK] = अणु
		.reg_offset = 1,
		.mask = WM8994_FLL1_LOCK_EINT,
	पूर्ण,
	[WM8994_IRQ_FLL2_LOCK] = अणु
		.reg_offset = 1,
		.mask = WM8994_FLL2_LOCK_EINT,
	पूर्ण,
	[WM8994_IRQ_SRC1_LOCK] = अणु
		.reg_offset = 1,
		.mask = WM8994_SRC1_LOCK_EINT,
	पूर्ण,
	[WM8994_IRQ_SRC2_LOCK] = अणु
		.reg_offset = 1,
		.mask = WM8994_SRC2_LOCK_EINT,
	पूर्ण,
	[WM8994_IRQ_AIF1DRC1_SIG_DET] = अणु
		.reg_offset = 1,
		.mask = WM8994_AIF1DRC1_SIG_DET,
	पूर्ण,
	[WM8994_IRQ_AIF1DRC2_SIG_DET] = अणु
		.reg_offset = 1,
		.mask = WM8994_AIF1DRC2_SIG_DET_EINT,
	पूर्ण,
	[WM8994_IRQ_AIF2DRC_SIG_DET] = अणु
		.reg_offset = 1,
		.mask = WM8994_AIF2DRC_SIG_DET_EINT,
	पूर्ण,
	[WM8994_IRQ_FIFOS_ERR] = अणु
		.reg_offset = 1,
		.mask = WM8994_FIFOS_ERR_EINT,
	पूर्ण,
	[WM8994_IRQ_WSEQ_DONE] = अणु
		.reg_offset = 1,
		.mask = WM8994_WSEQ_DONE_EINT,
	पूर्ण,
	[WM8994_IRQ_DCS_DONE] = अणु
		.reg_offset = 1,
		.mask = WM8994_DCS_DONE_EINT,
	पूर्ण,
	[WM8994_IRQ_TEMP_WARN] = अणु
		.reg_offset = 1,
		.mask = WM8994_TEMP_WARN_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(1)] = अणु
		.mask = WM8994_GP1_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(2)] = अणु
		.mask = WM8994_GP2_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(3)] = अणु
		.mask = WM8994_GP3_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(4)] = अणु
		.mask = WM8994_GP4_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(5)] = अणु
		.mask = WM8994_GP5_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(6)] = अणु
		.mask = WM8994_GP6_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(7)] = अणु
		.mask = WM8994_GP7_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(8)] = अणु
		.mask = WM8994_GP8_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(9)] = अणु
		.mask = WM8994_GP8_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(10)] = अणु
		.mask = WM8994_GP10_EINT,
	पूर्ण,
	[WM8994_IRQ_GPIO(11)] = अणु
		.mask = WM8994_GP11_EINT,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip wm8994_irq_chip = अणु
	.name = "wm8994",
	.irqs = wm8994_irqs,
	.num_irqs = ARRAY_SIZE(wm8994_irqs),

	.num_regs = 2,
	.status_base = WM8994_INTERRUPT_STATUS_1,
	.mask_base = WM8994_INTERRUPT_STATUS_1_MASK,
	.ack_base = WM8994_INTERRUPT_STATUS_1,
	.runसमय_pm = true,
पूर्ण;

अटल व्योम wm8994_edge_irq_enable(काष्ठा irq_data *data)
अणु
पूर्ण

अटल व्योम wm8994_edge_irq_disable(काष्ठा irq_data *data)
अणु
पूर्ण

अटल काष्ठा irq_chip wm8994_edge_irq_chip = अणु
	.name			= "wm8994_edge",
	.irq_disable		= wm8994_edge_irq_disable,
	.irq_enable		= wm8994_edge_irq_enable,
पूर्ण;

अटल irqवापस_t wm8994_edge_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm8994 *wm8994 = data;

	जबतक (gpio_get_value_cansleep(wm8994->pdata.irq_gpio))
		handle_nested_irq(irq_create_mapping(wm8994->edge_irq, 0));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wm8994_edge_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			       irq_hw_number_t hw)
अणु
	काष्ठा wm8994 *wm8994 = h->host_data;

	irq_set_chip_data(virq, wm8994);
	irq_set_chip_and_handler(virq, &wm8994_edge_irq_chip, handle_edge_irq);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops wm8994_edge_irq_ops = अणु
	.map	= wm8994_edge_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

पूर्णांक wm8994_irq_init(काष्ठा wm8994 *wm8994)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ irqflags;
	काष्ठा wm8994_pdata *pdata = &wm8994->pdata;

	अगर (!wm8994->irq) अणु
		dev_warn(wm8994->dev,
			 "No interrupt specified, no interrupts\n");
		wm8994->irq_base = 0;
		वापस 0;
	पूर्ण

	/* select user or शेष irq flags */
	irqflags = IRQF_TRIGGER_HIGH | IRQF_ONESHOT;
	अगर (pdata->irq_flags)
		irqflags = pdata->irq_flags;

	/* use a GPIO क्रम edge triggered controllers */
	अगर (irqflags & (IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING)) अणु
		अगर (gpio_to_irq(pdata->irq_gpio) != wm8994->irq) अणु
			dev_warn(wm8994->dev, "IRQ %d is not GPIO %d (%d)\n",
				 wm8994->irq, pdata->irq_gpio,
				 gpio_to_irq(pdata->irq_gpio));
			wm8994->irq = gpio_to_irq(pdata->irq_gpio);
		पूर्ण

		ret = devm_gpio_request_one(wm8994->dev, pdata->irq_gpio,
					    GPIOF_IN, "WM8994 IRQ");

		अगर (ret != 0) अणु
			dev_err(wm8994->dev, "Failed to get IRQ GPIO: %d\n",
				ret);
			वापस ret;
		पूर्ण

		wm8994->edge_irq = irq_करोमुख्य_add_linear(शून्य, 1,
							 &wm8994_edge_irq_ops,
							 wm8994);

		ret = regmap_add_irq_chip(wm8994->regmap,
					  irq_create_mapping(wm8994->edge_irq,
							     0),
					  IRQF_ONESHOT,
					  wm8994->irq_base, &wm8994_irq_chip,
					  &wm8994->irq_data);
		अगर (ret != 0) अणु
			dev_err(wm8994->dev, "Failed to get IRQ: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = request_thपढ़ोed_irq(wm8994->irq,
					   शून्य, wm8994_edge_irq,
					   irqflags,
					   "WM8994 edge", wm8994);
	पूर्ण अन्यथा अणु
		ret = regmap_add_irq_chip(wm8994->regmap, wm8994->irq,
					  irqflags,
					  wm8994->irq_base, &wm8994_irq_chip,
					  &wm8994->irq_data);
	पूर्ण

	अगर (ret != 0) अणु
		dev_err(wm8994->dev, "Failed to register IRQ chip: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable top level पूर्णांकerrupt अगर it was masked */
	wm8994_reg_ग_लिखो(wm8994, WM8994_INTERRUPT_CONTROL, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(wm8994_irq_init);

व्योम wm8994_irq_निकास(काष्ठा wm8994 *wm8994)
अणु
	regmap_del_irq_chip(wm8994->irq, wm8994->irq_data);
पूर्ण
EXPORT_SYMBOL(wm8994_irq_निकास);
