<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// S3C24XX specअगरic support क्रम Samsung pinctrl/gpiolib driver.
//
// Copyright (c) 2013 Heiko Stuebner <heiko@sntech.de>
//
// This file contains the SamsungS3C24XX specअगरic inक्रमmation required by the
// Samsung pinctrl/gpiolib driver. It also includes the implementation of
// बाह्यal gpio and wakeup पूर्णांकerrupt support.

#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/irq.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/irqchip/chained_irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>

#समावेश "pinctrl-samsung.h"

#घोषणा NUM_EINT	24
#घोषणा NUM_EINT_IRQ	6
#घोषणा Eपूर्णांक_उच्च_PER_GROUP	8

#घोषणा EINTPEND_REG	0xa8
#घोषणा EINTMASK_REG	0xa4

#घोषणा EINT_GROUP(i)		((पूर्णांक)((i) / Eपूर्णांक_उच्च_PER_GROUP))
#घोषणा EINT_REG(i)		((EINT_GROUP(i) * 4) + 0x88)
#घोषणा EINT_OFFS(i)		((i) % Eपूर्णांक_उच्च_PER_GROUP * 4)

#घोषणा EINT_LEVEL_LOW		0
#घोषणा EINT_LEVEL_HIGH		1
#घोषणा EINT_EDGE_FALLING	2
#घोषणा EINT_EDGE_RISING	4
#घोषणा EINT_EDGE_BOTH		6
#घोषणा EINT_MASK		0xf

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_1bit = अणु
	.fld_width = अणु 1, 1, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_type bank_type_2bit = अणु
	.fld_width = अणु 2, 1, 2, पूर्ण,
	.reg_offset = अणु 0x00, 0x04, 0x08, पूर्ण,
पूर्ण;

#घोषणा PIN_BANK_A(pins, reg, id)		\
	अणु						\
		.type		= &bank_type_1bit,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_2BIT(pins, reg, id)		\
	अणु						\
		.type		= &bank_type_2bit,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_NONE,	\
		.name		= id			\
	पूर्ण

#घोषणा PIN_BANK_2BIT_EINTW(pins, reg, id, eoffs, emask)\
	अणु						\
		.type		= &bank_type_2bit,	\
		.pctl_offset	= reg,			\
		.nr_pins	= pins,			\
		.eपूर्णांक_type	= EINT_TYPE_WKUP,	\
		.eपूर्णांक_func	= 2,			\
		.eपूर्णांक_mask	= emask,		\
		.eपूर्णांक_offset	= eoffs,		\
		.name		= id			\
	पूर्ण

/**
 * काष्ठा s3c24xx_eपूर्णांक_data - EINT common data
 * @drvdata: pin controller driver data
 * @करोमुख्यs: IRQ करोमुख्यs of particular EINT पूर्णांकerrupts
 * @parents: mapped parent irqs in the मुख्य पूर्णांकerrupt controller
 */
काष्ठा s3c24xx_eपूर्णांक_data अणु
	काष्ठा samsung_pinctrl_drv_data *drvdata;
	काष्ठा irq_करोमुख्य *करोमुख्यs[NUM_EINT];
	पूर्णांक parents[NUM_EINT_IRQ];
पूर्ण;

/**
 * काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data - per irq-करोमुख्य data
 * @bank: pin bank related to the करोमुख्य
 * @eपूर्णांक_data: common data
 * @eपूर्णांक0_3_parent_only: live eपूर्णांकs 0-3 only in the मुख्य पूर्णांकc
 */
काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data अणु
	काष्ठा samsung_pin_bank *bank;
	काष्ठा s3c24xx_eपूर्णांक_data *eपूर्णांक_data;
	bool eपूर्णांक0_3_parent_only;
पूर्ण;

अटल पूर्णांक s3c24xx_eपूर्णांक_get_trigger(अचिन्हित पूर्णांक type)
अणु
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_RISING:
		वापस EINT_EDGE_RISING;
	हाल IRQ_TYPE_EDGE_FALLING:
		वापस EINT_EDGE_FALLING;
	हाल IRQ_TYPE_EDGE_BOTH:
		वापस EINT_EDGE_BOTH;
	हाल IRQ_TYPE_LEVEL_HIGH:
		वापस EINT_LEVEL_HIGH;
	हाल IRQ_TYPE_LEVEL_LOW:
		वापस EINT_LEVEL_LOW;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम s3c24xx_eपूर्णांक_set_handler(काष्ठा irq_data *d, अचिन्हित पूर्णांक type)
अणु
	/* Edge- and level-triggered पूर्णांकerrupts need dअगरferent handlers */
	अगर (type & IRQ_TYPE_EDGE_BOTH)
		irq_set_handler_locked(d, handle_edge_irq);
	अन्यथा
		irq_set_handler_locked(d, handle_level_irq);
पूर्ण

अटल व्योम s3c24xx_eपूर्णांक_set_function(काष्ठा samsung_pinctrl_drv_data *d,
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
	shअगरt = pin * bank_type->fld_width[PINCFG_TYPE_FUNC];
	mask = (1 << bank_type->fld_width[PINCFG_TYPE_FUNC]) - 1;

	raw_spin_lock_irqsave(&bank->slock, flags);

	val = पढ़ोl(reg);
	val &= ~(mask << shअगरt);
	val |= bank->eपूर्णांक_func << shअगरt;
	ग_लिखोl(val, reg);

	raw_spin_unlock_irqrestore(&bank->slock, flags);
पूर्ण

अटल पूर्णांक s3c24xx_eपूर्णांक_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	पूर्णांक index = bank->eपूर्णांक_offset + data->hwirq;
	व्योम __iomem *reg;
	पूर्णांक trigger;
	u8 shअगरt;
	u32 val;

	trigger = s3c24xx_eपूर्णांक_get_trigger(type);
	अगर (trigger < 0) अणु
		dev_err(d->dev, "unsupported external interrupt type\n");
		वापस -EINVAL;
	पूर्ण

	s3c24xx_eपूर्णांक_set_handler(data, type);

	/* Set up पूर्णांकerrupt trigger */
	reg = d->virt_base + EINT_REG(index);
	shअगरt = EINT_OFFS(index);

	val = पढ़ोl(reg);
	val &= ~(EINT_MASK << shअगरt);
	val |= trigger << shअगरt;
	ग_लिखोl(val, reg);

	s3c24xx_eपूर्णांक_set_function(d, bank, data->hwirq);

	वापस 0;
पूर्ण

/* Handling of EINTs 0-3 on all except S3C2412 and S3C2413 */

अटल व्योम s3c2410_eपूर्णांक0_3_ack(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data *ddata = bank->irq_करोमुख्य->host_data;
	काष्ठा s3c24xx_eपूर्णांक_data *eपूर्णांक_data = ddata->eपूर्णांक_data;
	पूर्णांक parent_irq = eपूर्णांक_data->parents[data->hwirq];
	काष्ठा irq_chip *parent_chip = irq_get_chip(parent_irq);

	parent_chip->irq_ack(irq_get_irq_data(parent_irq));
पूर्ण

अटल व्योम s3c2410_eपूर्णांक0_3_mask(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data *ddata = bank->irq_करोमुख्य->host_data;
	काष्ठा s3c24xx_eपूर्णांक_data *eपूर्णांक_data = ddata->eपूर्णांक_data;
	पूर्णांक parent_irq = eपूर्णांक_data->parents[data->hwirq];
	काष्ठा irq_chip *parent_chip = irq_get_chip(parent_irq);

	parent_chip->irq_mask(irq_get_irq_data(parent_irq));
पूर्ण

अटल व्योम s3c2410_eपूर्णांक0_3_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data *ddata = bank->irq_करोमुख्य->host_data;
	काष्ठा s3c24xx_eपूर्णांक_data *eपूर्णांक_data = ddata->eपूर्णांक_data;
	पूर्णांक parent_irq = eपूर्णांक_data->parents[data->hwirq];
	काष्ठा irq_chip *parent_chip = irq_get_chip(parent_irq);

	parent_chip->irq_unmask(irq_get_irq_data(parent_irq));
पूर्ण

अटल काष्ठा irq_chip s3c2410_eपूर्णांक0_3_chip = अणु
	.name		= "s3c2410-eint0_3",
	.irq_ack	= s3c2410_eपूर्णांक0_3_ack,
	.irq_mask	= s3c2410_eपूर्णांक0_3_mask,
	.irq_unmask	= s3c2410_eपूर्णांक0_3_unmask,
	.irq_set_type	= s3c24xx_eपूर्णांक_type,
पूर्ण;

अटल व्योम s3c2410_demux_eपूर्णांक0_3(काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा s3c24xx_eपूर्णांक_data *eपूर्णांक_data = irq_desc_get_handler_data(desc);
	अचिन्हित पूर्णांक virq;

	/* the first 4 eपूर्णांकs have a simple 1 to 1 mapping */
	virq = irq_linear_revmap(eपूर्णांक_data->करोमुख्यs[data->hwirq], data->hwirq);
	/* Something must be really wrong अगर an unmapped EINT is unmasked */
	BUG_ON(!virq);

	generic_handle_irq(virq);
पूर्ण

/* Handling of EINTs 0-3 on S3C2412 and S3C2413 */

अटल व्योम s3c2412_eपूर्णांक0_3_ack(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;

	अचिन्हित दीर्घ bitval = 1UL << data->hwirq;
	ग_लिखोl(bitval, d->virt_base + EINTPEND_REG);
पूर्ण

अटल व्योम s3c2412_eपूर्णांक0_3_mask(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	अचिन्हित दीर्घ mask;

	mask = पढ़ोl(d->virt_base + EINTMASK_REG);
	mask |= (1UL << data->hwirq);
	ग_लिखोl(mask, d->virt_base + EINTMASK_REG);
पूर्ण

अटल व्योम s3c2412_eपूर्णांक0_3_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	अचिन्हित दीर्घ mask;

	mask = पढ़ोl(d->virt_base + EINTMASK_REG);
	mask &= ~(1UL << data->hwirq);
	ग_लिखोl(mask, d->virt_base + EINTMASK_REG);
पूर्ण

अटल काष्ठा irq_chip s3c2412_eपूर्णांक0_3_chip = अणु
	.name		= "s3c2412-eint0_3",
	.irq_ack	= s3c2412_eपूर्णांक0_3_ack,
	.irq_mask	= s3c2412_eपूर्णांक0_3_mask,
	.irq_unmask	= s3c2412_eपूर्णांक0_3_unmask,
	.irq_set_type	= s3c24xx_eपूर्णांक_type,
पूर्ण;

अटल व्योम s3c2412_demux_eपूर्णांक0_3(काष्ठा irq_desc *desc)
अणु
	काष्ठा s3c24xx_eपूर्णांक_data *eपूर्णांक_data = irq_desc_get_handler_data(desc);
	काष्ठा irq_data *data = irq_desc_get_irq_data(desc);
	काष्ठा irq_chip *chip = irq_data_get_irq_chip(data);
	अचिन्हित पूर्णांक virq;

	chained_irq_enter(chip, desc);

	/* the first 4 eपूर्णांकs have a simple 1 to 1 mapping */
	virq = irq_linear_revmap(eपूर्णांक_data->करोमुख्यs[data->hwirq], data->hwirq);
	/* Something must be really wrong अगर an unmapped EINT is unmasked */
	BUG_ON(!virq);

	generic_handle_irq(virq);

	chained_irq_निकास(chip, desc);
पूर्ण

/* Handling of all other eपूर्णांकs */

अटल व्योम s3c24xx_eपूर्णांक_ack(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	अचिन्हित अक्षर index = bank->eपूर्णांक_offset + data->hwirq;

	ग_लिखोl(1UL << index, d->virt_base + EINTPEND_REG);
पूर्ण

अटल व्योम s3c24xx_eपूर्णांक_mask(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	अचिन्हित अक्षर index = bank->eपूर्णांक_offset + data->hwirq;
	अचिन्हित दीर्घ mask;

	mask = पढ़ोl(d->virt_base + EINTMASK_REG);
	mask |= (1UL << index);
	ग_लिखोl(mask, d->virt_base + EINTMASK_REG);
पूर्ण

अटल व्योम s3c24xx_eपूर्णांक_unmask(काष्ठा irq_data *data)
अणु
	काष्ठा samsung_pin_bank *bank = irq_data_get_irq_chip_data(data);
	काष्ठा samsung_pinctrl_drv_data *d = bank->drvdata;
	अचिन्हित अक्षर index = bank->eपूर्णांक_offset + data->hwirq;
	अचिन्हित दीर्घ mask;

	mask = पढ़ोl(d->virt_base + EINTMASK_REG);
	mask &= ~(1UL << index);
	ग_लिखोl(mask, d->virt_base + EINTMASK_REG);
पूर्ण

अटल काष्ठा irq_chip s3c24xx_eपूर्णांक_chip = अणु
	.name		= "s3c-eint",
	.irq_ack	= s3c24xx_eपूर्णांक_ack,
	.irq_mask	= s3c24xx_eपूर्णांक_mask,
	.irq_unmask	= s3c24xx_eपूर्णांक_unmask,
	.irq_set_type	= s3c24xx_eपूर्णांक_type,
पूर्ण;

अटल अंतरभूत व्योम s3c24xx_demux_eपूर्णांक(काष्ठा irq_desc *desc,
				      u32 offset, u32 range)
अणु
	काष्ठा s3c24xx_eपूर्णांक_data *data = irq_desc_get_handler_data(desc);
	काष्ठा irq_chip *chip = irq_desc_get_chip(desc);
	काष्ठा samsung_pinctrl_drv_data *d = data->drvdata;
	अचिन्हित पूर्णांक pend, mask;

	chained_irq_enter(chip, desc);

	pend = पढ़ोl(d->virt_base + EINTPEND_REG);
	mask = पढ़ोl(d->virt_base + EINTMASK_REG);

	pend &= ~mask;
	pend &= range;

	जबतक (pend) अणु
		अचिन्हित पूर्णांक virq, irq;

		irq = __ffs(pend);
		pend &= ~(1 << irq);
		virq = irq_linear_revmap(data->करोमुख्यs[irq], irq - offset);
		/* Something is really wrong अगर an unmapped EINT is unmasked */
		BUG_ON(!virq);

		generic_handle_irq(virq);
	पूर्ण

	chained_irq_निकास(chip, desc);
पूर्ण

अटल व्योम s3c24xx_demux_eपूर्णांक4_7(काष्ठा irq_desc *desc)
अणु
	s3c24xx_demux_eपूर्णांक(desc, 0, 0xf0);
पूर्ण

अटल व्योम s3c24xx_demux_eपूर्णांक8_23(काष्ठा irq_desc *desc)
अणु
	s3c24xx_demux_eपूर्णांक(desc, 8, 0xffff00);
पूर्ण

अटल irq_flow_handler_t s3c2410_eपूर्णांक_handlers[NUM_EINT_IRQ] = अणु
	s3c2410_demux_eपूर्णांक0_3,
	s3c2410_demux_eपूर्णांक0_3,
	s3c2410_demux_eपूर्णांक0_3,
	s3c2410_demux_eपूर्णांक0_3,
	s3c24xx_demux_eपूर्णांक4_7,
	s3c24xx_demux_eपूर्णांक8_23,
पूर्ण;

अटल irq_flow_handler_t s3c2412_eपूर्णांक_handlers[NUM_EINT_IRQ] = अणु
	s3c2412_demux_eपूर्णांक0_3,
	s3c2412_demux_eपूर्णांक0_3,
	s3c2412_demux_eपूर्णांक0_3,
	s3c2412_demux_eपूर्णांक0_3,
	s3c24xx_demux_eपूर्णांक4_7,
	s3c24xx_demux_eपूर्णांक8_23,
पूर्ण;

अटल पूर्णांक s3c24xx_gpf_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
					irq_hw_number_t hw)
अणु
	काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data *ddata = h->host_data;
	काष्ठा samsung_pin_bank *bank = ddata->bank;

	अगर (!(bank->eपूर्णांक_mask & (1 << (bank->eपूर्णांक_offset + hw))))
		वापस -EINVAL;

	अगर (hw <= 3) अणु
		अगर (ddata->eपूर्णांक0_3_parent_only)
			irq_set_chip_and_handler(virq, &s3c2410_eपूर्णांक0_3_chip,
						 handle_edge_irq);
		अन्यथा
			irq_set_chip_and_handler(virq, &s3c2412_eपूर्णांक0_3_chip,
						 handle_edge_irq);
	पूर्ण अन्यथा अणु
		irq_set_chip_and_handler(virq, &s3c24xx_eपूर्णांक_chip,
					 handle_edge_irq);
	पूर्ण
	irq_set_chip_data(virq, bank);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops s3c24xx_gpf_irq_ops = अणु
	.map	= s3c24xx_gpf_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल पूर्णांक s3c24xx_gpg_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
					irq_hw_number_t hw)
अणु
	काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data *ddata = h->host_data;
	काष्ठा samsung_pin_bank *bank = ddata->bank;

	अगर (!(bank->eपूर्णांक_mask & (1 << (bank->eपूर्णांक_offset + hw))))
		वापस -EINVAL;

	irq_set_chip_and_handler(virq, &s3c24xx_eपूर्णांक_chip, handle_edge_irq);
	irq_set_chip_data(virq, bank);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops s3c24xx_gpg_irq_ops = अणु
	.map	= s3c24xx_gpg_irq_map,
	.xlate	= irq_करोमुख्य_xlate_twocell,
पूर्ण;

अटल स्थिर काष्ठा of_device_id s3c24xx_eपूर्णांक_irq_ids[] = अणु
	अणु .compatible = "samsung,s3c2410-wakeup-eint", .data = (व्योम *)1 पूर्ण,
	अणु .compatible = "samsung,s3c2412-wakeup-eint", .data = (व्योम *)0 पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक s3c24xx_eपूर्णांक_init(काष्ठा samsung_pinctrl_drv_data *d)
अणु
	काष्ठा device *dev = d->dev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *eपूर्णांक_np = शून्य;
	काष्ठा device_node *np;
	काष्ठा samsung_pin_bank *bank;
	काष्ठा s3c24xx_eपूर्णांक_data *eपूर्णांक_data;
	स्थिर काष्ठा irq_करोमुख्य_ops *ops;
	अचिन्हित पूर्णांक i;
	bool eपूर्णांक0_3_parent_only;
	irq_flow_handler_t *handlers;

	क्रम_each_child_of_node(dev->of_node, np) अणु
		match = of_match_node(s3c24xx_eपूर्णांक_irq_ids, np);
		अगर (match) अणु
			eपूर्णांक_np = np;
			eपूर्णांक0_3_parent_only = (bool)match->data;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!eपूर्णांक_np)
		वापस -ENODEV;

	eपूर्णांक_data = devm_kzalloc(dev, माप(*eपूर्णांक_data), GFP_KERNEL);
	अगर (!eपूर्णांक_data) अणु
		of_node_put(eपूर्णांक_np);
		वापस -ENOMEM;
	पूर्ण

	eपूर्णांक_data->drvdata = d;

	handlers = eपूर्णांक0_3_parent_only ? s3c2410_eपूर्णांक_handlers
				       : s3c2412_eपूर्णांक_handlers;
	क्रम (i = 0; i < NUM_EINT_IRQ; ++i) अणु
		अचिन्हित पूर्णांक irq;

		irq = irq_of_parse_and_map(eपूर्णांक_np, i);
		अगर (!irq) अणु
			dev_err(dev, "failed to get wakeup EINT IRQ %d\n", i);
			of_node_put(eपूर्णांक_np);
			वापस -ENXIO;
		पूर्ण

		eपूर्णांक_data->parents[i] = irq;
		irq_set_chained_handler_and_data(irq, handlers[i], eपूर्णांक_data);
	पूर्ण
	of_node_put(eपूर्णांक_np);

	bank = d->pin_banks;
	क्रम (i = 0; i < d->nr_banks; ++i, ++bank) अणु
		काष्ठा s3c24xx_eपूर्णांक_करोमुख्य_data *ddata;
		अचिन्हित पूर्णांक mask;
		अचिन्हित पूर्णांक irq;
		अचिन्हित पूर्णांक pin;

		अगर (bank->eपूर्णांक_type != EINT_TYPE_WKUP)
			जारी;

		ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
		अगर (!ddata)
			वापस -ENOMEM;

		ddata->bank = bank;
		ddata->eपूर्णांक_data = eपूर्णांक_data;
		ddata->eपूर्णांक0_3_parent_only = eपूर्णांक0_3_parent_only;

		ops = (bank->eपूर्णांक_offset == 0) ? &s3c24xx_gpf_irq_ops
					       : &s3c24xx_gpg_irq_ops;

		bank->irq_करोमुख्य = irq_करोमुख्य_add_linear(bank->of_node,
				bank->nr_pins, ops, ddata);
		अगर (!bank->irq_करोमुख्य) अणु
			dev_err(dev, "wkup irq domain add failed\n");
			वापस -ENXIO;
		पूर्ण

		irq = bank->eपूर्णांक_offset;
		mask = bank->eपूर्णांक_mask;
		क्रम (pin = 0; mask; ++pin, mask >>= 1) अणु
			अगर (irq >= NUM_EINT)
				अवरोध;
			अगर (!(mask & 1))
				जारी;
			eपूर्णांक_data->करोमुख्यs[irq] = bank->irq_करोमुख्य;
			++irq;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा samsung_pin_bank_data s3c2412_pin_banks[] __initस्थिर = अणु
	PIN_BANK_A(23, 0x000, "gpa"),
	PIN_BANK_2BIT(11, 0x010, "gpb"),
	PIN_BANK_2BIT(16, 0x020, "gpc"),
	PIN_BANK_2BIT(16, 0x030, "gpd"),
	PIN_BANK_2BIT(16, 0x040, "gpe"),
	PIN_BANK_2BIT_EINTW(8, 0x050, "gpf", 0, 0xff),
	PIN_BANK_2BIT_EINTW(16, 0x060, "gpg", 8, 0xffff00),
	PIN_BANK_2BIT(11, 0x070, "gph"),
	PIN_BANK_2BIT(13, 0x080, "gpj"),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_ctrl s3c2412_pin_ctrl[] __initस्थिर = अणु
	अणु
		.pin_banks	= s3c2412_pin_banks,
		.nr_banks	= ARRAY_SIZE(s3c2412_pin_banks),
		.eपूर्णांक_wkup_init = s3c24xx_eपूर्णांक_init,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2412_of_data __initस्थिर = अणु
	.ctrl		= s3c2412_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s3c2412_pin_ctrl),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_data s3c2416_pin_banks[] __initस्थिर = अणु
	PIN_BANK_A(27, 0x000, "gpa"),
	PIN_BANK_2BIT(11, 0x010, "gpb"),
	PIN_BANK_2BIT(16, 0x020, "gpc"),
	PIN_BANK_2BIT(16, 0x030, "gpd"),
	PIN_BANK_2BIT(16, 0x040, "gpe"),
	PIN_BANK_2BIT_EINTW(8, 0x050, "gpf", 0, 0xff),
	PIN_BANK_2BIT_EINTW(8, 0x060, "gpg", 8, 0xff00),
	PIN_BANK_2BIT(15, 0x070, "gph"),
	PIN_BANK_2BIT(16, 0x0e0, "gpk"),
	PIN_BANK_2BIT(14, 0x0f0, "gpl"),
	PIN_BANK_2BIT(2, 0x100, "gpm"),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_ctrl s3c2416_pin_ctrl[] __initस्थिर = अणु
	अणु
		.pin_banks	= s3c2416_pin_banks,
		.nr_banks	= ARRAY_SIZE(s3c2416_pin_banks),
		.eपूर्णांक_wkup_init = s3c24xx_eपूर्णांक_init,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2416_of_data __initस्थिर = अणु
	.ctrl		= s3c2416_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s3c2416_pin_ctrl),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_data s3c2440_pin_banks[] __initस्थिर = अणु
	PIN_BANK_A(25, 0x000, "gpa"),
	PIN_BANK_2BIT(11, 0x010, "gpb"),
	PIN_BANK_2BIT(16, 0x020, "gpc"),
	PIN_BANK_2BIT(16, 0x030, "gpd"),
	PIN_BANK_2BIT(16, 0x040, "gpe"),
	PIN_BANK_2BIT_EINTW(8, 0x050, "gpf", 0, 0xff),
	PIN_BANK_2BIT_EINTW(16, 0x060, "gpg", 8, 0xffff00),
	PIN_BANK_2BIT(11, 0x070, "gph"),
	PIN_BANK_2BIT(13, 0x0d0, "gpj"),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_ctrl s3c2440_pin_ctrl[] __initस्थिर = अणु
	अणु
		.pin_banks	= s3c2440_pin_banks,
		.nr_banks	= ARRAY_SIZE(s3c2440_pin_banks),
		.eपूर्णांक_wkup_init = s3c24xx_eपूर्णांक_init,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2440_of_data __initस्थिर = अणु
	.ctrl		= s3c2440_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s3c2440_pin_ctrl),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_bank_data s3c2450_pin_banks[] __initस्थिर = अणु
	PIN_BANK_A(28, 0x000, "gpa"),
	PIN_BANK_2BIT(11, 0x010, "gpb"),
	PIN_BANK_2BIT(16, 0x020, "gpc"),
	PIN_BANK_2BIT(16, 0x030, "gpd"),
	PIN_BANK_2BIT(16, 0x040, "gpe"),
	PIN_BANK_2BIT_EINTW(8, 0x050, "gpf", 0, 0xff),
	PIN_BANK_2BIT_EINTW(16, 0x060, "gpg", 8, 0xffff00),
	PIN_BANK_2BIT(15, 0x070, "gph"),
	PIN_BANK_2BIT(16, 0x0d0, "gpj"),
	PIN_BANK_2BIT(16, 0x0e0, "gpk"),
	PIN_BANK_2BIT(15, 0x0f0, "gpl"),
	PIN_BANK_2BIT(2, 0x100, "gpm"),
पूर्ण;

अटल स्थिर काष्ठा samsung_pin_ctrl s3c2450_pin_ctrl[] __initस्थिर = अणु
	अणु
		.pin_banks	= s3c2450_pin_banks,
		.nr_banks	= ARRAY_SIZE(s3c2450_pin_banks),
		.eपूर्णांक_wkup_init = s3c24xx_eपूर्णांक_init,
	पूर्ण,
पूर्ण;

स्थिर काष्ठा samsung_pinctrl_of_match_data s3c2450_of_data __initस्थिर = अणु
	.ctrl		= s3c2450_pin_ctrl,
	.num_ctrl	= ARRAY_SIZE(s3c2450_pin_ctrl),
पूर्ण;
