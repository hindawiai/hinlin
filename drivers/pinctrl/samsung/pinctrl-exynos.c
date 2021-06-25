<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Exynos specअगरic support क्रम Samsung pinctrl/gpiolib driver with eपूर्णांक support.
//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//		http://www.samsung.com
// Copyright (c) 2012 Linaro Ltd
//		http://www.linaro.org
//
// Author: Thomas Abraham <thomas.ab@samsung.com>
//
// This file contains the Samsung Exynos specअगरic inक्रमmation required by the
// the Samsung pinctrl/gpiolib driver. It also includes the implementation of
// बाह्यal gpio and wakeup पूर्णांकerrupt support.

#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/regmap.h>
#समावेश <linux/err.h>
#समावेश <linux/soc/samsung/exynos-pmu.h>
#समावेश <linux/soc/samsung/exynos-regs-pmu.h>

#समावेश <dt-bindings/pinctrl/samsung.h>

#समावेश "pinctrl-samsung.h"
#समावेश "pinctrl-exynos.h"

काष्ठा exynos_irq_chip अणु
	काष्ठा irq_chip chip;

	u32 eपूर्णांक_con;
	u32 eपूर्णांक_mask;
	u32 eपूर्णांक_pend;
	u32 *eपूर्णांक_wake_mask_value;
	u32 eपूर्णांक_wake_mask_reg;
	व्योम (*set_eपूर्णांक_wakeup_mask)(काष्ठा samsung_pinctrl_drv_data *drvdata,
				     काष्ठा exynos_irq_chip *irq_chip);
पूर्ण;

अटल अंतरभूत काष्ठा exynos_irq_chip *to_exynos_irq_chip(काष्ठा irq_chip *chip)
अणु
	वापस container_of(chip, काष्ठा exynos_irq_chip, chip);
पूर्ण

अटल व्योम exynos_irq_mask(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(irqd);
	काष्ठा exynos_irq_chip *our_chip = to_exynos_irq_chip(chip);
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	अचिन्हित दीर्घ reg_mask = our_chip->eपूर्णांक_mask + bank->eपूर्णांक_offset;
	अचिन्हित पूर्णांक mask;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&bank->slock, flags);

	mask = पढ़ोl(bank->eपूर्णांक_base + reg_mask);
	mask |= 1 << irqd->hwirq;
	ग_लिखोl(mask, bank->eपूर्णांक_base + reg_mask);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
पूर्ण

अटल व्योम exynos_irq_ack(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(irqd);
	काष्ठा exynos_irq_chip *our_chip = to_exynos_irq_chip(chip);
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	अचिन्हित दीर्घ reg_pend = our_chip->eपूर्णांक_pend + bank->eपूर्णांक_offset;

	ग_लिखोl(1 << irqd->hwirq, bank->eपूर्णांक_base + reg_pend);
पूर्ण

अटल व्योम exynos_irq_unmask(काष्ठा irq_data *irqd)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(irqd);
	काष्ठा exynos_irq_chip *our_chip = to_exynos_irq_chip(chip);
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	अचिन्हित दीर्घ reg_mask = our_chip->eपूर्णांक_mask + bank->eपूर्णांक_offset;
	अचिन्हित पूर्णांक mask;
	अचिन्हित दीर्घ flags;

	/*
	 * Ack level पूर्णांकerrupts right beक्रमe unmask
	 *
	 * If we करोn't do this we'll get a द्विगुन-पूर्णांकerrupt.  Level triggered
	 * पूर्णांकerrupts must not fire an पूर्णांकerrupt अगर the level is not
	 * _currently_ active, even अगर it was active जबतक the पूर्णांकerrupt was
	 * masked.
	 */
	अगर (irqd_get_trigger_type(irqd) & IRQ_TYPE_LEVEL_MASK)
		exynos_irq_ack(irqd);

	raw_spin_lock_irqsave(&bank->slock, flags);

	mask = पढ़ोl(bank->eपूर्णांक_base + reg_mask);
	mask &= ~(1 << irqd->hwirq);
	ग_लिखोl(mask, bank->eपूर्णांक_base + reg_mask);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
पूर्ण

अटल पूर्णांक exynos_irq_set_type(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक type)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(irqd);
	काष्ठा exynos_irq_chip *our_chip = to_exynos_irq_chip(chip);
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	अचिन्हित पूर्णांक shअगरt = EXYNOS_EINT_CON_LEN * irqd->hwirq;
	अचिन्हित पूर्णांक con, trig_type;
	अचिन्हित दीर्घ reg_con = our_chip->eपूर्णांक_con + bank->eपूर्णांक_offset;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		trig_type = EXYNOS_EINT_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		trig_type = EXYNOS_EINT_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		trig_type = EXYNOS_EINT_EDGE_BOTH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		trig_type = EXYNOS_EINT_LEVEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		trig_type = EXYNOS_EINT_LEVEL_LOW;
		अवरोध;
	शेष:
		pr_err("unsupported external interrupt type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(irqd, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(irqd, handle_level_irq);

	con = पढ़ोl(bank->eपूर्णांक_base + reg_con);
	con &= ~(EXYNOS_EINT_CON_MASK << shअगरt);
	con |= trig_type << shअगरt;
	ग_लिखोl(con, bank->eपूर्णांक_base + reg_con);

	वापस 0;
पूर्ण

अटल पूर्णांक exynos_irq_request_resources(काष्ठा irq_data *irqd)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	स्थिर काष्ठा samsung_pin_bank_type *bank_type = bank->type;
	अचिन्हित दीर्घ reg_con, flags;
	अचिन्हित पूर्णांक shअगरt, mask, con;
	पूर्णांक ret;

	ret = gpiochip_lock_as_irq(&bank->gpio_chip, irqd->hwirq);
	अगर (ret) अणु
		dev_err(bank->gpio_chip.parent,
			"unable to lock pin %s-%lu IRQ\n",
			bank->name, irqd->hwirq);
		वापस ret;
	पूर्ण

	reg_con = bank->pctl_offset + bank_type->reg_offset[PINCFG_TYPE_FUNC];
	shअगरt = irqd->hwirq * bank_type->fld_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fld_width[PINCFG_TYPE_FUNC]) - 1;

	raw_spin_lock_irqsave(&bank->slock, flags);

	con = पढ़ोl(bank->pctl_base + reg_con);
	con &= ~(mask << shअगरt);
	con |= EXYNOS_PIN_FUNC_EINT << shअगरt;
	ग_लिखोl(con, bank->pctl_base + reg_con);

	raw_spin_unlock_irqrestore(&bank->slock, flags);

	वापस 0;
पूर्ण

अटल व्योम exynos_irq_release_resources(काष्ठा irq_data *irqd)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	स्थिर काष्ठा samsung_pin_bank_type *bank_type = bank->type;
	अचिन्हित दीर्घ reg_con, flags;
	अचिन्हित पूर्णांक shअगरt, mask, con;

	reg_con = bank->pctl_offset + bank_type->reg_offset[PINCFG_TYPE_FUNC];
	shअगरt = irqd->hwirq * bank_type->fld_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fld_width[PINCFG_TYPE_FUNC]) - 1;

	raw_spin_lock_irqsave(&bank->slock, flags);

	con = पढ़ोl(bank->pctl_base + reg_con);
	con &= ~(mask << shअगरt);
	con |= EXYNOS_PIN_FUNC_INPUT << shअगरt;
	ग_लिखोl(con, bank->pctl_base + reg_con);

	raw_spin_unlock_irqrestore(&bank->slock, flags);

	gpiochip_unlock_as_irq(&bank->gpio_chip, irqd->hwirq);
पूर्ण

/*
 * irq_chip क्रम gpio पूर्णांकerrupts.
 */
अटल स्थिर काष्ठा exynos_irq_chip exynos_gpio_irq_chip __initस्थिर = अणु
	.chip = अणु
		.name = "exynos_gpio_irq_chip",
		.irq_unmask = exynos_irq_unmask,
		.irq_mask = exynos_irq_mask,
		.irq_ack = exynos_irq_ack,
		.irq_set_type = exynos_irq_set_type,
		.irq_request_resources = exynos_irq_request_resources,
		.irq_release_resources = exynos_irq_release_resources,
	पूर्ण,
	.eपूर्णांक_con = EXYNOS_GPIO_ECON_OFFSET,
	.eपूर्णांक_mask = EXYNOS_GPIO_EMASK_OFFSET,
	.eपूर्णांक_pend = EXYNOS_GPIO_EPEND_OFFSET,
	/* eपूर्णांक_wake_mask_value not used */
पूर्ण;

अटल पूर्णांक exynos_eपूर्णांक_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
					irq_hw_number_t hw)
अणु
	काष्ठा samsung_pin_bank *b = h->host_data;

	irq_set_chip_data(virq, b);
	irq_set_chip_and_handler(virq, &b->irq_chip->chip,
					handle_level_irq);
	वापस 0;
पूर्ण

/*
 * irq करोमुख्य callbacks क्रम बाह्यal gpio and wakeup पूर्णांकerrupt controllers.
 */
अटल स्थिर काष्ठा irq_करोमुख्य_ops exynos_eपूर्णांक_irqd_ops = अणु
	.map	= exynos_eपूर्णांक_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल irqवापस_t exynos_eपूर्णांक_gpio_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा samsung_pinctrl_drv_data *d = data;
	काष्ठा samsung_pin_bank *bank = d->pin_banks;
	अचिन्हित पूर्णांक svc, group, pin, virq;

	svc = पढ़ोl(bank->eपूर्णांक_base + EXYNOS_SVC_OFFSET);
	group = EXYNOS_SVC_GROUP(svc);
	pin = svc & EXYNOS_SVC_NUM_MASK;

	अगर (!group)
		वापस IRQ_HANDLED;
	bank += (group - 1);

	virq = irq_linear_revmap(bank->irq_करोमुख्य, pin);
	अगर (!virq)
		वापस IRQ_NONE;
	generic_handle_irq(virq);
	वापस IRQ_HANDLED;
पूर्ण

काष्ठा exynos_eपूर्णांक_gpio_save अणु
	u32 eपूर्णांक_con;
	u32 eपूर्णांक_fltcon0;
	u32 eपूर्णांक_fltcon1;
	u32 eपूर्णांक_mask;
पूर्ण;

/*
 * exynos_eपूर्णांक_gpio_init() - setup handling of बाह्यal gpio पूर्णांकerrupts.
 * @d: driver data of samsung pinctrl driver.
 */
__init पूर्णांक exynos_eपूर्णांक_gpio_init(काष्ठा samsung_pinctrl_drv_data *d)
अणु
	काष्ठा samsung_pin_bank *bank;
	काष्ठा device *dev = d->dev;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!d->irq) अणु
		dev_err(dev, "irq number not available\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_irq(dev, d->irq, exynos_eपूर्णांक_gpio_irq,
					0, dev_name(dev), d);
	अगर (ret) अणु
		dev_err(dev, "irq request failed\n");
		वापस -ENXIO;
	पूर्ण

	bank = d->pin_banks;
	क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
		अगर (bank->eपूर्णांक_type != EINT_TYPE_GPIO)
			जारी;

		bank->irq_chip = devm_kmemdup(dev, &exynos_gpio_irq_chip,
					   माप(*bank->irq_chip), GFP_KERNEL);
		अगर (!bank->irq_chip) अणु
			ret = -ENOMEM;
			जाओ err_करोमुख्यs;
		पूर्ण
		bank->irq_chip->chip.name = bank->name;

		bank->irq_करोमुख्य = irq_करोमुख्य_add_linear(bank->of_node,
				bank->nr_pins, &exynos_eपूर्णांक_irqd_ops, bank);
		अगर (!bank->irq_करोमुख्य) अणु
			dev_err(dev, "gpio irq domain add failed\n");
			ret = -ENXIO;
			जाओ err_करोमुख्यs;
		पूर्ण

		bank->soc_priv = devm_kzalloc(d->dev,
			माप(काष्ठा exynos_eपूर्णांक_gpio_save), GFP_KERNEL);
		अगर (!bank->soc_priv) अणु
			irq_करोमुख्य_हटाओ(bank->irq_करोमुख्य);
			ret = -ENOMEM;
			जाओ err_करोमुख्यs;
		पूर्ण

	पूर्ण

	वापस 0;

err_करोमुख्यs:
	क्रम (--i, --bank; i >= 0; --i, --bank) अणु
		अगर (bank->eपूर्णांक_type != EINT_TYPE_GPIO)
			जारी;
		irq_करोमुख्य_हटाओ(bank->irq_करोमुख्य);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक exynos_wkup_irq_set_wake(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक on)
अणु
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(irqd);
	काष्ठा exynos_irq_chip *our_chip = to_exynos_irq_chip(chip);
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	अचिन्हित दीर्घ bit = 1UL << (2 * bank->eपूर्णांक_offset + irqd->hwirq);

	pr_info("wake %s for irq %d\n", on ? "enabled" : "disabled", irqd->irq);

	अगर (!on)
		*our_chip->eपूर्णांक_wake_mask_value |= bit;
	अन्यथा
		*our_chip->eपूर्णांक_wake_mask_value &= ~bit;

	वापस 0;
पूर्ण

अटल व्योम
exynos_pinctrl_set_eपूर्णांक_wakeup_mask(काष्ठा samsung_pinctrl_drv_data *drvdata,
				    काष्ठा exynos_irq_chip *irq_chip)
अणु
	काष्ठा regmap *pmu_regs;

	अगर (!drvdata->retention_ctrl || !drvdata->retention_ctrl->priv) अणु
		dev_warn(drvdata->dev,
			 "No retention data configured bank with external wakeup interrupt. Wake-up mask will not be set.\n");
		वापस;
	पूर्ण

	pmu_regs = drvdata->retention_ctrl->priv;
	dev_info(drvdata->dev,
		 "Setting external wakeup interrupt mask: 0x%x\n",
		 *irq_chip->eपूर्णांक_wake_mask_value);

	regmap_ग_लिखो(pmu_regs, irq_chip->eपूर्णांक_wake_mask_reg,
		     *irq_chip->eपूर्णांक_wake_mask_value);
पूर्ण

अटल व्योम
s5pv210_pinctrl_set_eपूर्णांक_wakeup_mask(काष्ठा samsung_pinctrl_drv_data *drvdata,
				    काष्ठा exynos_irq_chip *irq_chip)

अणु
	व्योम __iomem *clk_base;

	अगर (!drvdata->retention_ctrl || !drvdata->retention_ctrl->priv) अणु
		dev_warn(drvdata->dev,
			 "No retention data configured bank with external wakeup interrupt. Wake-up mask will not be set.\n");
		वापस;
	पूर्ण


	clk_base = (व्योम __iomem *) drvdata->retention_ctrl->priv;

	__raw_ग_लिखोl(*irq_chip->eपूर्णांक_wake_mask_value,
		     clk_base + irq_chip->eपूर्णांक_wake_mask_reg);
पूर्ण

अटल u32 eपूर्णांक_wake_mask_value = EXYNOS_EINT_WAKEUP_MASK_DISABLED;
/*
 * irq_chip क्रम wakeup पूर्णांकerrupts
 */
अटल स्थिर काष्ठा exynos_irq_chip s5pv210_wkup_irq_chip __initस्थिर = अणु
	.chip = अणु
		.name = "s5pv210_wkup_irq_chip",
		.irq_unmask = exynos_irq_unmask,
		.irq_mask = exynos_irq_mask,
		.irq_ack = exynos_irq_ack,
		.irq_set_type = exynos_irq_set_type,
		.irq_set_wake = exynos_wkup_irq_set_wake,
		.irq_request_resources = exynos_irq_request_resources,
		.irq_release_resources = exynos_irq_release_resources,
	पूर्ण,
	.eपूर्णांक_con = EXYNOS_WKUP_ECON_OFFSET,
	.eपूर्णांक_mask = EXYNOS_WKUP_EMASK_OFFSET,
	.eपूर्णांक_pend = EXYNOS_WKUP_EPEND_OFFSET,
	.eपूर्णांक_wake_mask_value = &eपूर्णांक_wake_mask_value,
	/* Only dअगरferences with exynos4210_wkup_irq_chip: */
	.eपूर्णांक_wake_mask_reg = S5PV210_EINT_WAKEUP_MASK,
	.set_eपूर्णांक_wakeup_mask = s5pv210_pinctrl_set_eपूर्णांक_wakeup_mask,
पूर्ण;

अटल स्थिर काष्ठा exynos_irq_chip exynos4210_wkup_irq_chip __initस्थिर = अणु
	.chip = अणु
		.name = "exynos4210_wkup_irq_chip",
		.irq_unmask = exynos_irq_unmask,
		.irq_mask = exynos_irq_mask,
		.irq_ack = exynos_irq_ack,
		.irq_set_type = exynos_irq_set_type,
		.irq_set_wake = exynos_wkup_irq_set_wake,
		.irq_request_resources = exynos_irq_request_resources,
		.irq_release_resources = exynos_irq_release_resources,
	पूर्ण,
	.eपूर्णांक_con = EXYNOS_WKUP_ECON_OFFSET,
	.eपूर्णांक_mask = EXYNOS_WKUP_EMASK_OFFSET,
	.eपूर्णांक_pend = EXYNOS_WKUP_EPEND_OFFSET,
	.eपूर्णांक_wake_mask_value = &eपूर्णांक_wake_mask_value,
	.eपूर्णांक_wake_mask_reg = EXYNOS_EINT_WAKEUP_MASK,
	.set_eपूर्णांक_wakeup_mask = exynos_pinctrl_set_eपूर्णांक_wakeup_mask,
पूर्ण;

अटल स्थिर काष्ठा exynos_irq_chip exynos7_wkup_irq_chip __initस्थिर = अणु
	.chip = अणु
		.name = "exynos7_wkup_irq_chip",
		.irq_unmask = exynos_irq_unmask,
		.irq_mask = exynos_irq_mask,
		.irq_ack = exynos_irq_ack,
		.irq_set_type = exynos_irq_set_type,
		.irq_set_wake = exynos_wkup_irq_set_wake,
		.irq_request_resources = exynos_irq_request_resources,
		.irq_release_resources = exynos_irq_release_resources,
	पूर्ण,
	.eपूर्णांक_con = EXYNOS7_WKUP_ECON_OFFSET,
	.eपूर्णांक_mask = EXYNOS7_WKUP_EMASK_OFFSET,
	.eपूर्णांक_pend = EXYNOS7_WKUP_EPEND_OFFSET,
	.eपूर्णांक_wake_mask_value = &eपूर्णांक_wake_mask_value,
	.eपूर्णांक_wake_mask_reg = EXYNOS5433_EINT_WAKEUP_MASK,
	.set_eपूर्णांक_wakeup_mask = exynos_pinctrl_set_eपूर्णांक_wakeup_mask,
पूर्ण;

/* list of बाह्यal wakeup controllers supported */
अटल स्थिर काष्ठा of_device_id exynos_wkup_irq_ids[] = अणु
	अणु .compatible = "samsung,s5pv210-wakeup-eint",
			.data = &s5pv210_wkup_irq_chip पूर्ण,
	अणु .compatible = "samsung,exynos4210-wakeup-eint",
			.data = &exynos4210_wkup_irq_chip पूर्ण,
	अणु .compatible = "samsung,exynos7-wakeup-eint",
			.data = &exynos7_wkup_irq_chip पूर्ण,
	अणु पूर्ण
पूर्ण;

/* पूर्णांकerrupt handler क्रम wakeup पूर्णांकerrupts 0..15 */
अटल व्योम exynos_irq_eपूर्णांक0_15(काष्ठा irq_desc *desc)
अणु
	काष्ठा exynos_weपूर्णांक_data *eपूर्णांकd = irq_desc_get_handler_data(desc);
	काष्ठा samsung_pin_bank *bank = eपूर्णांकd->bank;
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	पूर्णांक eपूर्णांक_irq;

	chained_irq_enter(chip, desc);

	eपूर्णांक_irq = irq_linear_revmap(bank->irq_करोमुख्य, eपूर्णांकd->irq);
	generic_handle_irq(eपूर्णांक_irq);

	chained_irq_निकास(chip, desc);
पूर्ण

अटल अंतरभूत व्योम exynos_irq_demux_eपूर्णांक(अचिन्हित पूर्णांक pend,
						काष्ठा irq_करोमुख्य *करोमुख्य)
अणु
	अचिन्हित पूर्णांक irq;

	जबतक (pend) अणु
		irq = fls(pend) - 1;
		generic_handle_irq(irq_find_mapping(करोमुख्य, irq));
		pend &= ~(1 << irq);
	पूर्ण
पूर्ण

/* पूर्णांकerrupt handler क्रम wakeup पूर्णांकerrupt 16 */
अटल व्योम exynos_irq_demux_eपूर्णांक16_31(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा exynos_muxed_weपूर्णांक_data *eपूर्णांकd = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक pend;
	अचिन्हित पूर्णांक mask;
	पूर्णांक i;

	chained_irq_enter(chip, desc);

	क्रम (i = 0; i < eपूर्णांकd->nr_banks; ++i) अणु
		काष्ठा samsung_pin_bank *b = eपूर्णांकd->banks[i];
		pend = पढ़ोl(b->eपूर्णांक_base + b->irq_chip->eपूर्णांक_pend
				+ b->eपूर्णांक_offset);
		mask = पढ़ोl(b->eपूर्णांक_base + b->irq_chip->eपूर्णांक_mask
				+ b->eपूर्णांक_offset);
		exynos_irq_demux_eपूर्णांक(pend & ~mask, b->irq_करोमुख्य);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

/*
 * exynos_eपूर्णांक_wkup_init() - setup handling of बाह्यal wakeup पूर्णांकerrupts.
 * @d: driver data of samsung pinctrl driver.
 */
__init पूर्णांक exynos_eपूर्णांक_wkup_init(काष्ठा samsung_pinctrl_drv_data *d)
अणु
	काष्ठा device *dev = d->dev;
	काष्ठा device_node *wkup_np = शून्य;
	काष्ठा device_node *np;
	काष्ठा samsung_pin_bank *bank;
	काष्ठा exynos_weपूर्णांक_data *weपूर्णांक_data;
	काष्ठा exynos_muxed_weपूर्णांक_data *muxed_data;
	स्थिर काष्ठा exynos_irq_chip *irq_chip;
	अचिन्हित पूर्णांक muxed_banks = 0;
	अचिन्हित पूर्णांक i;
	पूर्णांक idx, irq;

	क्रम_each_child_of_node(dev->of_node, np) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(exynos_wkup_irq_ids, np);
		अगर (match) अणु
			irq_chip = match->data;
			wkup_np = np;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!wkup_np)
		वापस -ENODEV;

	bank = d->pin_banks;
	क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
		अगर (bank->eपूर्णांक_type != EINT_TYPE_WKUP)
			जारी;

		bank->irq_chip = devm_kmemdup(dev, irq_chip, माप(*irq_chip),
					      GFP_KERNEL);
		अगर (!bank->irq_chip) अणु
			of_node_put(wkup_np);
			वापस -ENOMEM;
		पूर्ण
		bank->irq_chip->chip.name = bank->name;

		bank->irq_करोमुख्य = irq_करोमुख्य_add_linear(bank->of_node,
				bank->nr_pins, &exynos_eपूर्णांक_irqd_ops, bank);
		अगर (!bank->irq_करोमुख्य) अणु
			dev_err(dev, "wkup irq domain add failed\n");
			of_node_put(wkup_np);
			वापस -ENXIO;
		पूर्ण

		अगर (!of_find_property(bank->of_node, "interrupts", शून्य)) अणु
			bank->eपूर्णांक_type = EINT_TYPE_WKUP_MUX;
			++muxed_banks;
			जारी;
		पूर्ण

		weपूर्णांक_data = devm_kसुस्मृति(dev,
					  bank->nr_pins, माप(*weपूर्णांक_data),
					  GFP_KERNEL);
		अगर (!weपूर्णांक_data) अणु
			of_node_put(wkup_np);
			वापस -ENOMEM;
		पूर्ण

		क्रम (idx = 0; idx < bank->nr_pins; ++idx) अणु
			irq = irq_of_parse_and_map(bank->of_node, idx);
			अगर (!irq) अणु
				dev_err(dev, "irq number for eint-%s-%d not found\n",
							bank->name, idx);
				जारी;
			पूर्ण
			weपूर्णांक_data[idx].irq = idx;
			weपूर्णांक_data[idx].bank = bank;
			irq_set_chained_handler_and_data(irq,
							 exynos_irq_eपूर्णांक0_15,
							 &weपूर्णांक_data[idx]);
		पूर्ण
	पूर्ण

	अगर (!muxed_banks) अणु
		of_node_put(wkup_np);
		वापस 0;
	पूर्ण

	irq = irq_of_parse_and_map(wkup_np, 0);
	of_node_put(wkup_np);
	अगर (!irq) अणु
		dev_err(dev, "irq number for muxed EINTs not found\n");
		वापस 0;
	पूर्ण

	muxed_data = devm_kzalloc(dev, माप(*muxed_data)
		+ muxed_banks*माप(काष्ठा samsung_pin_bank *), GFP_KERNEL);
	अगर (!muxed_data)
		वापस -ENOMEM;

	irq_set_chained_handler_and_data(irq, exynos_irq_demux_eपूर्णांक16_31,
					 muxed_data);

	bank = d->pin_banks;
	idx = 0;
	क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
		अगर (bank->eपूर्णांक_type != EINT_TYPE_WKUP_MUX)
			जारी;

		muxed_data->banks[idx++] = bank;
	पूर्ण
	muxed_data->nr_banks = muxed_banks;

	वापस 0;
पूर्ण

अटल व्योम exynos_pinctrl_suspend_bank(
				काष्ठा samsung_pinctrl_drv_data *drvdata,
				काष्ठा samsung_pin_bank *bank)
अणु
	काष्ठा exynos_eपूर्णांक_gpio_save *save = bank->soc_priv;
	व्योम __iomem *regs = bank->eपूर्णांक_base;

	save->eपूर्णांक_con = पढ़ोl(regs + EXYNOS_GPIO_ECON_OFFSET
						+ bank->eपूर्णांक_offset);
	save->eपूर्णांक_fltcon0 = पढ़ोl(regs + EXYNOS_GPIO_EFLTCON_OFFSET
						+ 2 * bank->eपूर्णांक_offset);
	save->eपूर्णांक_fltcon1 = पढ़ोl(regs + EXYNOS_GPIO_EFLTCON_OFFSET
						+ 2 * bank->eपूर्णांक_offset + 4);
	save->eपूर्णांक_mask = पढ़ोl(regs + bank->irq_chip->eपूर्णांक_mask
						+ bank->eपूर्णांक_offset);

	pr_debug("%s: save     con %#010x\n", bank->name, save->eपूर्णांक_con);
	pr_debug("%s: save fltcon0 %#010x\n", bank->name, save->eपूर्णांक_fltcon0);
	pr_debug("%s: save fltcon1 %#010x\n", bank->name, save->eपूर्णांक_fltcon1);
	pr_debug("%s: save    mask %#010x\n", bank->name, save->eपूर्णांक_mask);
पूर्ण

व्योम exynos_pinctrl_suspend(काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	काष्ठा samsung_pin_bank *bank = drvdata->pin_banks;
	काष्ठा exynos_irq_chip *irq_chip = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < drvdata->nr_banks; ++i, ++bank) अणु
		अगर (bank->eपूर्णांक_type == EINT_TYPE_GPIO)
			exynos_pinctrl_suspend_bank(drvdata, bank);
		अन्यथा अगर (bank->eपूर्णांक_type == EINT_TYPE_WKUP) अणु
			अगर (!irq_chip) अणु
				irq_chip = bank->irq_chip;
				irq_chip->set_eपूर्णांक_wakeup_mask(drvdata,
							       irq_chip);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम exynos_pinctrl_resume_bank(
				काष्ठा samsung_pinctrl_drv_data *drvdata,
				काष्ठा samsung_pin_bank *bank)
अणु
	काष्ठा exynos_eपूर्णांक_gpio_save *save = bank->soc_priv;
	व्योम __iomem *regs = bank->eपूर्णांक_base;

	pr_debug("%s:     con %#010x => %#010x\n", bank->name,
			पढ़ोl(regs + EXYNOS_GPIO_ECON_OFFSET
			+ bank->eपूर्णांक_offset), save->eपूर्णांक_con);
	pr_debug("%s: fltcon0 %#010x => %#010x\n", bank->name,
			पढ़ोl(regs + EXYNOS_GPIO_EFLTCON_OFFSET
			+ 2 * bank->eपूर्णांक_offset), save->eपूर्णांक_fltcon0);
	pr_debug("%s: fltcon1 %#010x => %#010x\n", bank->name,
			पढ़ोl(regs + EXYNOS_GPIO_EFLTCON_OFFSET
			+ 2 * bank->eपूर्णांक_offset + 4), save->eपूर्णांक_fltcon1);
	pr_debug("%s:    mask %#010x => %#010x\n", bank->name,
			पढ़ोl(regs + bank->irq_chip->eपूर्णांक_mask
			+ bank->eपूर्णांक_offset), save->eपूर्णांक_mask);

	ग_लिखोl(save->eपूर्णांक_con, regs + EXYNOS_GPIO_ECON_OFFSET
						+ bank->eपूर्णांक_offset);
	ग_लिखोl(save->eपूर्णांक_fltcon0, regs + EXYNOS_GPIO_EFLTCON_OFFSET
						+ 2 * bank->eपूर्णांक_offset);
	ग_लिखोl(save->eपूर्णांक_fltcon1, regs + EXYNOS_GPIO_EFLTCON_OFFSET
						+ 2 * bank->eपूर्णांक_offset + 4);
	ग_लिखोl(save->eपूर्णांक_mask, regs + bank->irq_chip->eपूर्णांक_mask
						+ bank->eपूर्णांक_offset);
पूर्ण

व्योम exynos_pinctrl_resume(काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	काष्ठा samsung_pin_bank *bank = drvdata->pin_banks;
	पूर्णांक i;

	क्रम (i = 0; i < drvdata->nr_banks; ++i, ++bank)
		अगर (bank->eपूर्णांक_type == EINT_TYPE_GPIO)
			exynos_pinctrl_resume_bank(drvdata, bank);
पूर्ण

अटल व्योम exynos_retention_enable(काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	अगर (drvdata->retention_ctrl->refcnt)
		atomic_inc(drvdata->retention_ctrl->refcnt);
पूर्ण

अटल व्योम exynos_retention_disable(काष्ठा samsung_pinctrl_drv_data *drvdata)
अणु
	काष्ठा samsung_retention_ctrl *ctrl = drvdata->retention_ctrl;
	काष्ठा regmap *pmu_regs = ctrl->priv;
	पूर्णांक i;

	अगर (ctrl->refcnt && !atomic_dec_and_test(ctrl->refcnt))
		वापस;

	क्रम (i = 0; i < ctrl->nr_regs; i++)
		regmap_ग_लिखो(pmu_regs, ctrl->regs[i], ctrl->value);
पूर्ण

काष्ठा samsung_retention_ctrl *
exynos_retention_init(काष्ठा samsung_pinctrl_drv_data *drvdata,
		      स्थिर काष्ठा samsung_retention_data *data)
अणु
	काष्ठा samsung_retention_ctrl *ctrl;
	काष्ठा regmap *pmu_regs;
	पूर्णांक i;

	ctrl = devm_kzalloc(drvdata->dev, माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस ERR_PTR(-ENOMEM);

	pmu_regs = exynos_get_pmu_regmap();
	अगर (IS_ERR(pmu_regs))
		वापस ERR_CAST(pmu_regs);

	ctrl->priv = pmu_regs;
	ctrl->regs = data->regs;
	ctrl->nr_regs = data->nr_regs;
	ctrl->value = data->value;
	ctrl->refcnt = data->refcnt;
	ctrl->enable = exynos_retention_enable;
	ctrl->disable = exynos_retention_disable;

	/* Ensure that retention is disabled on driver init */
	क्रम (i = 0; i < ctrl->nr_regs; i++)
		regmap_ग_लिखो(pmu_regs, ctrl->regs[i], ctrl->value);

	वापस ctrl;
पूर्ण
