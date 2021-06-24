<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// S3C64xx specअगरic support क्रम pinctrl-samsung driver.
//
// Copyright (c) 2013 Tomasz Figa <tomasz.figa@gmail.com>
//
// Based on pinctrl-exynos.c, please see the file क्रम original copyrights.
//
// This file contains the Samsung S3C64xx specअगरic inक्रमmation required by the
// the Samsung pinctrl/gpiolib driver. It also includes the implementation of
// बाह्यal gpio and wakeup पूर्णांकerrupt support.

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#समावेश "pinctrl-samsung.h"

#घोषणा NUM_EINT0		28
#घोषणा NUM_EINT0_IRQ		4
#घोषणा Eपूर्णांक_उच्च_PER_REG	16
#घोषणा Eपूर्णांक_उच्च_PER_GROUP	16

/* External GPIO and wakeup पूर्णांकerrupt related definitions */
#घोषणा SVC_GROUP_SHIFT		4
#घोषणा SVC_GROUP_MASK		0xf
#घोषणा SVC_NUM_MASK		0xf
#घोषणा SVC_GROUP(x)		((x >> SVC_GROUP_SHIFT) & \
						SVC_GROUP_MASK)

#घोषणा EINT12CON_REG		0x200
#घोषणा EINT12MASK_REG		0x240
#घोषणा EINT12PEND_REG		0x260

#घोषणा EINT_OFFS(i)		((i) % (2 * Eपूर्णांक_उच्च_PER_GROUP))
#घोषणा EINT_GROUP(i)		((i) / Eपूर्णांक_उच्च_PER_GROUP)
#घोषणा EINT_REG(g)		(4 * ((g) / 2))

#घोषणा EINTCON_REG(i)		(EINT12CON_REG + EINT_REG(EINT_GROUP(i)))
#घोषणा EINTMASK_REG(i)		(EINT12MASK_REG + EINT_REG(EINT_GROUP(i)))
#घोषणा EINTPEND_REG(i)		(EINT12PEND_REG + EINT_REG(EINT_GROUP(i)))

#घोषणा SERVICE_REG		0x284
#घोषणा SERVICEPEND_REG		0x288

#घोषणा EINT0CON0_REG		0x900
#घोषणा EINT0MASK_REG		0x920
#घोषणा EINT0PEND_REG		0x924

/* S3C64xx specअगरic बाह्यal पूर्णांकerrupt trigger types */
#घोषणा EINT_LEVEL_LOW		0
#घोषणा EINT_LEVEL_HIGH		1
#घोषणा EINT_EDGE_FALLING	2
#घोषणा EINT_EDGE_RISING	4
#घोषणा EINT_EDGE_BOTH		6
#घोषणा EINT_CON_MASK		0xF
#घोषणा EINT_CON_LEN		4

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_4bit_off = अणु
	.fld_width = अणु 4, 1, 2, 0, 2, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, 0, 0x0c, 0x10, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_4bit_alive = अणु
	.fld_width = अणु 4, 1, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_4bit2_off = अणु
	.fld_width = अणु 4, 1, 2, 0, 2, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x08, 0x0c, 0, 0x10, 0x14, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_4bit2_alive = अणु
	.fld_width = अणु 4, 1, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x08, 0x0c, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_2bit_off = अणु
	.fld_width = अणु 2, 1, 2, 0, 2, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, 0, 0x0c, 0x10, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_2bit_alive = अणु
	.fld_width = अणु 2, 1, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, पूर्ण,
पूर्ण;

#घोषणा PIN_BANK_4BIT(pins, reg, id)			\
	अणु						\
		.type		= &bank_type_4bit_off,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_4BIT_EINTG(pins, reg, id, eoffs)	\
	अणु						\
		.type		= &bank_type_4bit_off,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_GPIO,	\
		.eपूर्णांक_func	= 7,			\
		.eपूर्णांक_mask	= (1 << (pins)) - 1,	\
		.eपूर्णांक_offset	= eoffs,		\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_4BIT_EINTW(pins, reg, id, eoffs, emask) \
	अणु						\
		.type		= &bank_type_4bit_alive,\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_WKUP,	\
		.eपूर्णांक_func	= 3,			\
		.eपूर्णांक_mask	= emask,		\
		.eपूर्णांक_offset	= eoffs,		\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_4BIT2_EINTG(pins, reg, id, eoffs)	\
	अणु						\
		.type		= &bank_type_4bit2_off,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_GPIO,	\
		.eपूर्णांक_func	= 7,			\
		.eपूर्णांक_mask	= (1 << (pins)) - 1,	\
		.eपूर्णांक_offset	= eoffs,		\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_4BIT2_EINTW(pins, reg, id, eoffs, emask) \
	अणु						\
		.type		= &bank_type_4bit2_alive,\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_WKUP,	\
		.eपूर्णांक_func	= 3,			\
		.eपूर्णांक_mask	= emask,		\
		.eपूर्णांक_offset	= eoffs,		\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_4BIT2_ALIVE(pins, reg, id)		\
	अणु						\
		.type		= &bank_type_4bit2_alive,\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_2BIT(pins, reg, id)			\
	अणु						\
		.type		= &bank_type_2bit_off,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_2BIT_EINTG(pins, reg, id, eoffs, emask) \
	अणु						\
		.type		= &bank_type_2bit_off,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_GPIO,	\
		.eपूर्णांक_func	= 3,			\
		.eपूर्णांक_mask	= emask,		\
		.eपूर्णांक_offset	= eoffs,		\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_2BIT_EINTW(pins, reg, id, eoffs)	\
	अणु						\
		.type		= &bank_type_2bit_alive,\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_WKUP,	\
		.eपूर्णांक_func	= 2,			\
		.eपूर्णांक_mask	= (1 << (pins)) - 1,	\
		.eपूर्णांक_offset	= eoffs,		\
		.name		= id			\
	पूर्ण

/**
 * काष्ठा s3c64xx_eपूर्णांक0_data - EINT0 common data
 * @drvdata: pin controller driver data
 * @करोमुख्यs: IRQ करोमुख्यs of particular EINT0 पूर्णांकerrupts
 * @pins: pin offsets inside of banks of particular EINT0 पूर्णांकerrupts
 */
काष्ठा s3c64xx_eपूर्णांक0_data अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	काष्ठा irq_करोमुख्य *करोमुख्यs[NUM_EINT0];
	u8 pins[NUM_EINT0];
पूर्ण;

/**
 * काष्ठा s3c64xx_eपूर्णांक0_करोमुख्य_data - EINT0 per-करोमुख्य data
 * @bank: pin bank related to the करोमुख्य
 * @eपूर्णांकs: EINT0 पूर्णांकerrupts related to the करोमुख्य
 */
काष्ठा s3c64xx_eपूर्णांक0_करोमुख्य_data अणु
	काष्ठा samsung_pin_bank *bank;
	u8 eपूर्णांकs[];
पूर्ण;

/**
 * काष्ठा s3c64xx_eपूर्णांक_gpio_data - GPIO EINT data
 * @drvdata: pin controller driver data
 * @करोमुख्यs: array of करोमुख्यs related to EINT पूर्णांकerrupt groups
 */
काष्ठा s3c64xx_eपूर्णांक_gpio_data अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	काष्ठा irq_करोमुख्य *करोमुख्यs[];
पूर्ण;

/*
 * Common functions क्रम S3C64xx EINT configuration
 */

अटल पूर्णांक s3c64xx_irq_get_trigger(अचिन्हित पूर्णांक type)
अणु
	पूर्णांक trigger;

	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		trigger = EINT_EDGE_RISING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_FALLING:
		trigger = EINT_EDGE_FALLING;
		अवरोध;
	हाल IRQ_TYPE_EDGE_BOTH:
		trigger = EINT_EDGE_BOTH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_HIGH:
		trigger = EINT_LEVEL_HIGH;
		अवरोध;
	हाल IRQ_TYPE_LEVEL_LOW:
		trigger = EINT_LEVEL_LOW;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस trigger;
पूर्ण

अटल व्योम s3c64xx_irq_set_handler(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	/* Edge- and level-triggered पूर्णांकerrupts need dअगरferent handlers */
	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_level_irq);
पूर्ण

अटल व्योम s3c64xx_irq_set_function(काष्ठा samsung_pinctrl_drv_data *d,
					काष्ठा samsung_pin_bank *bank, पूर्णांक pin)
अणु
	स्थिर काष्ठा samsung_pin_bank_type *bank_type = bank->type;
	अचिन्हित दीर्घ flags;
	व्योम __iomem *reg;
	u8 shअगरt;
	u32 mask;
	u32 val;

	/* Make sure that pin is configured as पूर्णांकerrupt */
	reg = d->virt_base + bank->pctl_offset;
	shअगरt = pin;
	अगर (bank_type->fld_width[PINCFG_TYPE_FUNC] * shअगरt >= 32) अणु
		/* 4-bit bank type with 2 con regs */
		reg += 4;
		shअगरt -= 8;
	पूर्ण

	shअगरt = shअगरt * bank_type->fld_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fld_width[PINCFG_TYPE_FUNC]) - 1;

	raw_spin_lock_irqsave(&bank->slock, flags);

	val = पढ़ोl(reg);
	val &= ~(mask << shअगरt);
	val |= bank->eपूर्णांक_func << shअगरt;
	ग_लिखोl(val, reg);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
पूर्ण

/*
 * Functions क्रम EINT GPIO configuration (EINT groups 1-9)
 */

अटल अंतरभूत व्योम s3c64xx_gpio_irq_set_mask(काष्ठा irq_data *irqd, bool mask)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	अचिन्हित अक्षर index = EINT_OFFS(bank->eपूर्णांक_offset) + irqd->hwirq;
	व्योम __iomem *reg = d->virt_base + EINTMASK_REG(bank->eपूर्णांक_offset);
	u32 val;

	val = पढ़ोl(reg);
	अगर (mask)
		val |= 1 << index;
	अन्यथा
		val &= ~(1 << index);
	ग_लिखोl(val, reg);
पूर्ण

अटल व्योम s3c64xx_gpio_irq_unmask(काष्ठा irq_data *irqd)
अणु
	s3c64xx_gpio_irq_set_mask(irqd, false);
पूर्ण

अटल व्योम s3c64xx_gpio_irq_mask(काष्ठा irq_data *irqd)
अणु
	s3c64xx_gpio_irq_set_mask(irqd, true);
पूर्ण

अटल व्योम s3c64xx_gpio_irq_ack(काष्ठा irq_data *irqd)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	अचिन्हित अक्षर index = EINT_OFFS(bank->eपूर्णांक_offset) + irqd->hwirq;
	व्योम __iomem *reg = d->virt_base + EINTPEND_REG(bank->eपूर्णांक_offset);

	ग_लिखोl(1 << index, reg);
पूर्ण

अटल पूर्णांक s3c64xx_gpio_irq_set_type(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक type)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(irqd);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	व्योम __iomem *reg;
	पूर्णांक trigger;
	u8 shअगरt;
	u32 val;

	trigger = s3c64xx_irq_get_trigger(type);
	अगर (trigger < 0) अणु
		pr_err("unsupported external interrupt type\n");
		वापस -EINVAL;
	पूर्ण

	s3c64xx_irq_set_handler(irqd, type);

	/* Set up पूर्णांकerrupt trigger */
	reg = d->virt_base + EINTCON_REG(bank->eपूर्णांक_offset);
	shअगरt = EINT_OFFS(bank->eपूर्णांक_offset) + irqd->hwirq;
	shअगरt = 4 * (shअगरt / 4); /* 4 EINTs per trigger selector */

	val = पढ़ोl(reg);
	val &= ~(EINT_CON_MASK << shअगरt);
	val |= trigger << shअगरt;
	ग_लिखोl(val, reg);

	s3c64xx_irq_set_function(d, bank, irqd->hwirq);

	वापस 0;
पूर्ण

/*
 * irq_chip क्रम gpio पूर्णांकerrupts.
 */
अटल काष्ठा irq_chip s3c64xx_gpio_irq_chip = अणु
	.name		= "GPIO",
	.irq_unmask	= s3c64xx_gpio_irq_unmask,
	.irq_mask	= s3c64xx_gpio_irq_mask,
	.irq_ack	= s3c64xx_gpio_irq_ack,
	.irq_set_type	= s3c64xx_gpio_irq_set_type,
पूर्ण;

अटल पूर्णांक s3c64xx_gpio_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
					irq_hw_number_t hw)
अणु
	काष्ठा samsung_pin_bank *bank = h->host_data;

	अगर (!(bank->eपूर्णांक_mask & (1 << hw)))
		वापस -EINVAL;

	irq_set_chip_and_handler(virq,
				&s3c64xx_gpio_irq_chip, handle_level_irq);
	irq_set_chip_data(virq, bank);

	वापस 0;
पूर्ण

/*
 * irq करोमुख्य callbacks क्रम बाह्यal gpio पूर्णांकerrupt controller.
 */
अटल स्थिर काष्ठा irq_करोमुख्य_ops s3c64xx_gpio_irqd_ops = अणु
	.map	= s3c64xx_gpio_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल व्योम s3c64xx_eपूर्णांक_gpio_irq(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा s3c64xx_eपूर्णांक_gpio_data *data = irq_desc_get_handler_data(desc);
	काष्ठा samsung_pinctrl_drv_data *drvdata = data->drvdata;

	chained_irq_enter(chip, desc);

	करो अणु
		अचिन्हित पूर्णांक svc;
		अचिन्हित पूर्णांक group;
		अचिन्हित पूर्णांक pin;
		अचिन्हित पूर्णांक virq;

		svc = पढ़ोl(drvdata->virt_base + SERVICE_REG);
		group = SVC_GROUP(svc);
		pin = svc & SVC_NUM_MASK;

		अगर (!group)
			अवरोध;

		/* Group 1 is used क्रम two pin banks */
		अगर (group == 1) अणु
			अगर (pin < 8)
				group = 0;
			अन्यथा
				pin -= 8;
		पूर्ण

		virq = irq_linear_revmap(data->करोमुख्यs[group], pin);
		/*
		 * Something must be really wrong अगर an unmapped EINT
		 * was unmasked...
		 */
		BUG_ON(!virq);

		generic_handle_irq(virq);
	पूर्ण जबतक (1);

	chained_irq_निकास(chip, desc);
पूर्ण

/**
 * s3c64xx_eपूर्णांक_gpio_init() - setup handling of बाह्यal gpio पूर्णांकerrupts.
 * @d: driver data of samsung pinctrl driver.
 */
अटल पूर्णांक s3c64xx_eपूर्णांक_gpio_init(काष्ठा samsung_pinctrl_drv_data *d)
अणु
	काष्ठा s3c64xx_eपूर्णांक_gpio_data *data;
	काष्ठा samsung_pin_bank *bank;
	काष्ठा device *dev = d->dev;
	अचिन्हित पूर्णांक nr_करोमुख्यs;
	अचिन्हित पूर्णांक i;

	अगर (!d->irq) अणु
		dev_err(dev, "irq number not available\n");
		वापस -EINVAL;
	पूर्ण

	nr_करोमुख्यs = 0;
	bank = d->pin_banks;
	क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
		अचिन्हित पूर्णांक nr_eपूर्णांकs;
		अचिन्हित पूर्णांक mask;

		अगर (bank->eपूर्णांक_type != EINT_TYPE_GPIO)
			जारी;

		mask = bank->eपूर्णांक_mask;
		nr_eपूर्णांकs = fls(mask);

		bank->irq_करोमुख्य = irq_करोमुख्य_add_linear(bank->of_node,
					nr_eपूर्णांकs, &s3c64xx_gpio_irqd_ops, bank);
		अगर (!bank->irq_करोमुख्य) अणु
			dev_err(dev, "gpio irq domain add failed\n");
			वापस -ENXIO;
		पूर्ण

		++nr_करोमुख्यs;
	पूर्ण

	data = devm_kzalloc(dev, काष्ठा_size(data, करोमुख्यs, nr_करोमुख्यs),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	data->drvdata = d;

	bank = d->pin_banks;
	nr_करोमुख्यs = 0;
	क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
		अगर (bank->eपूर्णांक_type != EINT_TYPE_GPIO)
			जारी;

		data->करोमुख्यs[nr_करोमुख्यs++] = bank->irq_करोमुख्य;
	पूर्ण

	irq_set_chained_handler_and_data(d->irq, s3c64xx_eपूर्णांक_gpio_irq, data);

	वापस 0;
पूर्ण

/*
 * Functions क्रम configuration of EINT0 wake-up पूर्णांकerrupts
 */

अटल अंतरभूत व्योम s3c64xx_eपूर्णांक0_irq_set_mask(काष्ठा irq_data *irqd, bool mask)
अणु
	काष्ठा s3c64xx_eपूर्णांक0_करोमुख्य_data *ddata =
					irq_data_get_irq_chip_data(irqd);
	काष्ठा samsung_pinctrl_drv_data *d = ddata->bank->drvdata;
	u32 val;

	val = पढ़ोl(d->virt_base + EINT0MASK_REG);
	अगर (mask)
		val |= 1 << ddata->eपूर्णांकs[irqd->hwirq];
	अन्यथा
		val &= ~(1 << ddata->eपूर्णांकs[irqd->hwirq]);
	ग_लिखोl(val, d->virt_base + EINT0MASK_REG);
पूर्ण

अटल व्योम s3c64xx_eपूर्णांक0_irq_unmask(काष्ठा irq_data *irqd)
अणु
	s3c64xx_eपूर्णांक0_irq_set_mask(irqd, false);
पूर्ण

अटल व्योम s3c64xx_eपूर्णांक0_irq_mask(काष्ठा irq_data *irqd)
अणु
	s3c64xx_eपूर्णांक0_irq_set_mask(irqd, true);
पूर्ण

अटल व्योम s3c64xx_eपूर्णांक0_irq_ack(काष्ठा irq_data *irqd)
अणु
	काष्ठा s3c64xx_eपूर्णांक0_करोमुख्य_data *ddata =
					irq_data_get_irq_chip_data(irqd);
	काष्ठा samsung_pinctrl_drv_data *d = ddata->bank->drvdata;

	ग_लिखोl(1 << ddata->eपूर्णांकs[irqd->hwirq],
					d->virt_base + EINT0PEND_REG);
पूर्ण

अटल पूर्णांक s3c64xx_eपूर्णांक0_irq_set_type(काष्ठा irq_data *irqd, अचिन्हित पूर्णांक type)
अणु
	काष्ठा s3c64xx_eपूर्णांक0_करोमुख्य_data *ddata =
					irq_data_get_irq_chip_data(irqd);
	काष्ठा samsung_pin_bank *bank = ddata->bank;
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	व्योम __iomem *reg;
	पूर्णांक trigger;
	u8 shअगरt;
	u32 val;

	trigger = s3c64xx_irq_get_trigger(type);
	अगर (trigger < 0) अणु
		pr_err("unsupported external interrupt type\n");
		वापस -EINVAL;
	पूर्ण

	s3c64xx_irq_set_handler(irqd, type);

	/* Set up पूर्णांकerrupt trigger */
	reg = d->virt_base + EINT0CON0_REG;
	shअगरt = ddata->eपूर्णांकs[irqd->hwirq];
	अगर (shअगरt >= Eपूर्णांक_उच्च_PER_REG) अणु
		reg += 4;
		shअगरt -= Eपूर्णांक_उच्च_PER_REG;
	पूर्ण
	shअगरt = EINT_CON_LEN * (shअगरt / 2);

	val = पढ़ोl(reg);
	val &= ~(EINT_CON_MASK << shअगरt);
	val |= trigger << shअगरt;
	ग_लिखोl(val, reg);

	s3c64xx_irq_set_function(d, bank, irqd->hwirq);

	वापस 0;
पूर्ण

/*
 * irq_chip क्रम wakeup पूर्णांकerrupts
 */
अटल काष्ठा irq_chip s3c64xx_eपूर्णांक0_irq_chip = अणु
	.name		= "EINT0",
	.irq_unmask	= s3c64xx_eपूर्णांक0_irq_unmask,
	.irq_mask	= s3c64xx_eपूर्णांक0_irq_mask,
	.irq_ack	= s3c64xx_eपूर्णांक0_irq_ack,
	.irq_set_type	= s3c64xx_eपूर्णांक0_irq_set_type,
पूर्ण;

अटल अंतरभूत व्योम s3c64xx_irq_demux_eपूर्णांक(काष्ठा irq_desc *desc, u32 range)
अणु
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा s3c64xx_eपूर्णांक0_data *data = irq_desc_get_handler_data(desc);
	काष्ठा samsung_pinctrl_drv_data *drvdata = data->drvdata;
	अचिन्हित पूर्णांक pend, mask;

	chained_irq_enter(chip, desc);

	pend = पढ़ोl(drvdata->virt_base + EINT0PEND_REG);
	mask = पढ़ोl(drvdata->virt_base + EINT0MASK_REG);

	pend = pend & range & ~mask;
	pend &= range;

	जबतक (pend) अणु
		अचिन्हित पूर्णांक virq, irq;

		irq = fls(pend) - 1;
		pend &= ~(1 << irq);
		virq = irq_linear_revmap(data->करोमुख्यs[irq], data->pins[irq]);
		/*
		 * Something must be really wrong अगर an unmapped EINT
		 * was unmasked...
		 */
		BUG_ON(!virq);

		generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम s3c64xx_demux_eपूर्णांक0_3(काष्ठा irq_desc *desc)
अणु
	s3c64xx_irq_demux_eपूर्णांक(desc, 0xf);
पूर्ण

अटल व्योम s3c64xx_demux_eपूर्णांक4_11(काष्ठा irq_desc *desc)
अणु
	s3c64xx_irq_demux_eपूर्णांक(desc, 0xff0);
पूर्ण

अटल व्योम s3c64xx_demux_eपूर्णांक12_19(काष्ठा irq_desc *desc)
अणु
	s3c64xx_irq_demux_eपूर्णांक(desc, 0xff000);
पूर्ण

अटल व्योम s3c64xx_demux_eपूर्णांक20_27(काष्ठा irq_desc *desc)
अणु
	s3c64xx_irq_demux_eपूर्णांक(desc, 0xff00000);
पूर्ण

अटल irq_flow_handler_t s3c64xx_eपूर्णांक0_handlers[NUM_EINT0_IRQ] = अणु
	s3c64xx_demux_eपूर्णांक0_3,
	s3c64xx_demux_eपूर्णांक4_11,
	s3c64xx_demux_eपूर्णांक12_19,
	s3c64xx_demux_eपूर्णांक20_27,
पूर्ण;

अटल पूर्णांक s3c64xx_eपूर्णांक0_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
					irq_hw_number_t hw)
अणु
	काष्ठा s3c64xx_eपूर्णांक0_करोमुख्य_data *ddata = h->host_data;
	काष्ठा samsung_pin_bank *bank = ddata->bank;

	अगर (!(bank->eपूर्णांक_mask & (1 << hw)))
		वापस -EINVAL;

	irq_set_chip_and_handler(virq,
				&s3c64xx_eपूर्णांक0_irq_chip, handle_level_irq);
	irq_set_chip_data(virq, ddata);

	वापस 0;
पूर्ण

/*
 * irq करोमुख्य callbacks क्रम बाह्यal wakeup पूर्णांकerrupt controller.
 */
अटल स्थिर काष्ठा irq_करोमुख्य_ops s3c64xx_eपूर्णांक0_irqd_ops = अणु
	.map	= s3c64xx_eपूर्णांक0_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

/* list of बाह्यal wakeup controllers supported */
अटल स्थिर काष्ठा of_device_id s3c64xx_eपूर्णांक0_irq_ids[] = अणु
	अणु .compatible = "samsung,s3c64xx-wakeup-eint", पूर्ण,
	अणु पूर्ण
पूर्ण;

/**
 * s3c64xx_eपूर्णांक_eपूर्णांक0_init() - setup handling of बाह्यal wakeup पूर्णांकerrupts.
 * @d: driver data of samsung pinctrl driver.
 */
अटल पूर्णांक s3c64xx_eपूर्णांक_eपूर्णांक0_init(काष्ठा samsung_pinctrl_drv_data *d)
अणु
	काष्ठा device *dev = d->dev;
	काष्ठा device_node *eपूर्णांक0_np = शून्य;
	काष्ठा device_node *np;
	काष्ठा samsung_pin_bank *bank;
	काष्ठा s3c64xx_eपूर्णांक0_data *data;
	अचिन्हित पूर्णांक i;

	क्रम_each_child_of_node(dev->of_node, np) अणु
		अगर (of_match_node(s3c64xx_eपूर्णांक0_irq_ids, np)) अणु
			eपूर्णांक0_np = np;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!eपूर्णांक0_np)
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data) अणु
		of_node_put(eपूर्णांक0_np);
		वापस -ENOMEM;
	पूर्ण
	data->drvdata = d;

	क्रम (i = 0; i < NUM_EINT0_IRQ; ++i) अणु
		अचिन्हित पूर्णांक irq;

		irq = irq_of_parse_and_map(eपूर्णांक0_np, i);
		अगर (!irq) अणु
			dev_err(dev, "failed to get wakeup EINT IRQ %d\n", i);
			of_node_put(eपूर्णांक0_np);
			वापस -ENXIO;
		पूर्ण

		irq_set_chained_handler_and_data(irq,
						 s3c64xx_eपूर्णांक0_handlers[i],
						 data);
	पूर्ण
	of_node_put(eपूर्णांक0_np);

	bank = d->pin_banks;
	क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
		काष्ठा s3c64xx_eपूर्णांक0_करोमुख्य_data *ddata;
		अचिन्हित पूर्णांक nr_eपूर्णांकs;
		अचिन्हित पूर्णांक mask;
		अचिन्हित पूर्णांक irq;
		अचिन्हित पूर्णांक pin;

		अगर (bank->eपूर्णांक_type != EINT_TYPE_WKUP)
			जारी;

		mask = bank->eपूर्णांक_mask;
		nr_eपूर्णांकs = fls(mask);

		ddata = devm_kzalloc(dev,
				माप(*ddata) + nr_eपूर्णांकs, GFP_KERNEL);
		अगर (!ddata)
			वापस -ENOMEM;
		ddata->bank = bank;

		bank->irq_करोमुख्य = irq_करोमुख्य_add_linear(bank->of_node,
				nr_eपूर्णांकs, &s3c64xx_eपूर्णांक0_irqd_ops, ddata);
		अगर (!bank->irq_करोमुख्य) अणु
			dev_err(dev, "wkup irq domain add failed\n");
			वापस -ENXIO;
		पूर्ण

		irq = bank->eपूर्णांक_offset;
		mask = bank->eपूर्णांक_mask;
		क्रम (pin = 0; mask; ++pin, mask >>= 1) अणु
			अगर (!(mask & 1))
				जारी;
			data->करोमुख्यs[irq] = bank->irq_करोमुख्य;
			data->pins[irq] = pin;
			ddata->eपूर्णांकs[pin] = irq;
			++irq;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* pin banks of s3c64xx pin-controller 0 */
अटल स्थिर काष्ठा samsung_pin_bank_data s3c64xx_pin_banks0[] __initस्थिर = अणु
	PIN_BANK_4BIT_EINTG(8, 0x000, "gpa", 0),
	PIN_BANK_4BIT_EINTG(7, 0x020, "gpb", 8),
	PIN_BANK_4BIT_EINTG(8, 0x040, "gpc", 16),
	PIN_BANK_4BIT_EINTG(5, 0x060, "gpd", 32),
	PIN_BANK_4BIT(5, 0x080, "gpe"),
	PIN_BANK_2BIT_EINTG(16, 0x0a0, "gpf", 48, 0x3fff),
	PIN_BANK_4BIT_EINTG(7, 0x0c0, "gpg", 64),
	PIN_BANK_4BIT2_EINTG(10, 0x0e0, "gph", 80),
	PIN_BANK_2BIT(16, 0x100, "gpi"),
	PIN_BANK_2BIT(12, 0x120, "gpj"),
	PIN_BANK_4BIT2_ALIVE(16, 0x800, "gpk"),
	PIN_BANK_4BIT2_EINTW(15, 0x810, "gpl", 16, 0x7f00),
	PIN_BANK_4BIT_EINTW(6, 0x820, "gpm", 23, 0x1f),
	PIN_BANK_2BIT_EINTW(16, 0x830, "gpn", 0),
	PIN_BANK_2BIT_EINTG(16, 0x140, "gpo", 96, 0xffff),
	PIN_BANK_2BIT_EINTG(15, 0x160, "gpp", 112, 0x7fff),
	PIN_BANK_2BIT_EINTG(9, 0x180, "gpq", 128, 0x1ff),
पूर्ण;

/*
 * Samsung pinctrl driver data क्रम S3C64xx SoC. S3C64xx SoC includes
 * one gpio/pin-mux/pinconfig controller.
 */
अटल स्थिर काष्ठा samsung_pin_ctrl s3c64xx_pin_ctrl[] __initस्थिर = अणु
	अणु
		/* pin-controller instance 1 data */
		.pin_banks	= s3c64xx_pin_banks0,
		.nr_banks	= ARRAY_SIZE(s3c64xx_pin_banks0),
		.eपूर्णांक_gpio_init = s3c64xx_eपूर्णांक_gpio_init,
		.eपूर्णांक_wkup_init = s3c64xx_eपूर्णांक_eपूर्णांक0_init,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_pinctrl_of_match_data s3c64xx_of_data __initस्थिर = अणु
	.ctrl		= s3c64xx_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s3c64xx_pin_ctrl),
पूर्ण;
