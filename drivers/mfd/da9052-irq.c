<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DA9052 पूर्णांकerrupt support
 *
 * Author: Fabio Estevam <fabio.estevam@मुक्तscale.com>
 * Based on arizona-irq.c, which is:
 *
 * Copyright 2012 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <linux/mfd/da9052/da9052.h>
#समावेश <linux/mfd/da9052/reg.h>

#घोषणा DA9052_NUM_IRQ_REGS		4
#घोषणा DA9052_IRQ_MASK_POS_1		0x01
#घोषणा DA9052_IRQ_MASK_POS_2		0x02
#घोषणा DA9052_IRQ_MASK_POS_3		0x04
#घोषणा DA9052_IRQ_MASK_POS_4		0x08
#घोषणा DA9052_IRQ_MASK_POS_5		0x10
#घोषणा DA9052_IRQ_MASK_POS_6		0x20
#घोषणा DA9052_IRQ_MASK_POS_7		0x40
#घोषणा DA9052_IRQ_MASK_POS_8		0x80

अटल स्थिर काष्ठा regmap_irq da9052_irqs[] = अणु
	[DA9052_IRQ_DCIN] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_1,
	पूर्ण,
	[DA9052_IRQ_VBUS] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_2,
	पूर्ण,
	[DA9052_IRQ_DCINREM] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_3,
	पूर्ण,
	[DA9052_IRQ_VBUSREM] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_4,
	पूर्ण,
	[DA9052_IRQ_VDDLOW] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_5,
	पूर्ण,
	[DA9052_IRQ_ALARM] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_6,
	पूर्ण,
	[DA9052_IRQ_SEQRDY] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_7,
	पूर्ण,
	[DA9052_IRQ_COMP1V2] = अणु
		.reg_offset = 0,
		.mask = DA9052_IRQ_MASK_POS_8,
	पूर्ण,
	[DA9052_IRQ_NONKEY] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_1,
	पूर्ण,
	[DA9052_IRQ_IDFLOAT] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_2,
	पूर्ण,
	[DA9052_IRQ_IDGND] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_3,
	पूर्ण,
	[DA9052_IRQ_CHGEND] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_4,
	पूर्ण,
	[DA9052_IRQ_TBAT] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_5,
	पूर्ण,
	[DA9052_IRQ_ADC_EOM] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_6,
	पूर्ण,
	[DA9052_IRQ_PENDOWN] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_7,
	पूर्ण,
	[DA9052_IRQ_TSIREADY] = अणु
		.reg_offset = 1,
		.mask = DA9052_IRQ_MASK_POS_8,
	पूर्ण,
	[DA9052_IRQ_GPI0] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_1,
	पूर्ण,
	[DA9052_IRQ_GPI1] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_2,
	पूर्ण,
	[DA9052_IRQ_GPI2] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_3,
	पूर्ण,
	[DA9052_IRQ_GPI3] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_4,
	पूर्ण,
	[DA9052_IRQ_GPI4] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_5,
	पूर्ण,
	[DA9052_IRQ_GPI5] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_6,
	पूर्ण,
	[DA9052_IRQ_GPI6] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_7,
	पूर्ण,
	[DA9052_IRQ_GPI7] = अणु
		.reg_offset = 2,
		.mask = DA9052_IRQ_MASK_POS_8,
	पूर्ण,
	[DA9052_IRQ_GPI8] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_1,
	पूर्ण,
	[DA9052_IRQ_GPI9] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_2,
	पूर्ण,
	[DA9052_IRQ_GPI10] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_3,
	पूर्ण,
	[DA9052_IRQ_GPI11] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_4,
	पूर्ण,
	[DA9052_IRQ_GPI12] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_5,
	पूर्ण,
	[DA9052_IRQ_GPI13] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_6,
	पूर्ण,
	[DA9052_IRQ_GPI14] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_7,
	पूर्ण,
	[DA9052_IRQ_GPI15] = अणु
		.reg_offset = 3,
		.mask = DA9052_IRQ_MASK_POS_8,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip da9052_regmap_irq_chip = अणु
	.name = "da9052_irq",
	.status_base = DA9052_EVENT_A_REG,
	.mask_base = DA9052_IRQ_MASK_A_REG,
	.ack_base = DA9052_EVENT_A_REG,
	.num_regs = DA9052_NUM_IRQ_REGS,
	.irqs = da9052_irqs,
	.num_irqs = ARRAY_SIZE(da9052_irqs),
पूर्ण;

अटल पूर्णांक da9052_map_irq(काष्ठा da9052 *da9052, पूर्णांक irq)
अणु
	वापस regmap_irq_get_virq(da9052->irq_data, irq);
पूर्ण

पूर्णांक da9052_enable_irq(काष्ठा da9052 *da9052, पूर्णांक irq)
अणु
	irq = da9052_map_irq(da9052, irq);
	अगर (irq < 0)
		वापस irq;

	enable_irq(irq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(da9052_enable_irq);

पूर्णांक da9052_disable_irq(काष्ठा da9052 *da9052, पूर्णांक irq)
अणु
	irq = da9052_map_irq(da9052, irq);
	अगर (irq < 0)
		वापस irq;

	disable_irq(irq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(da9052_disable_irq);

पूर्णांक da9052_disable_irq_nosync(काष्ठा da9052 *da9052, पूर्णांक irq)
अणु
	irq = da9052_map_irq(da9052, irq);
	अगर (irq < 0)
		वापस irq;

	disable_irq_nosync(irq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(da9052_disable_irq_nosync);

पूर्णांक da9052_request_irq(काष्ठा da9052 *da9052, पूर्णांक irq, अक्षर *name,
			   irq_handler_t handler, व्योम *data)
अणु
	irq = da9052_map_irq(da9052, irq);
	अगर (irq < 0)
		वापस irq;

	वापस request_thपढ़ोed_irq(irq, शून्य, handler,
				     IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				     name, data);
पूर्ण
EXPORT_SYMBOL_GPL(da9052_request_irq);

व्योम da9052_मुक्त_irq(काष्ठा da9052 *da9052, पूर्णांक irq, व्योम *data)
अणु
	irq = da9052_map_irq(da9052, irq);
	अगर (irq < 0)
		वापस;

	मुक्त_irq(irq, data);
पूर्ण
EXPORT_SYMBOL_GPL(da9052_मुक्त_irq);

अटल irqवापस_t da9052_auxadc_irq(पूर्णांक irq, व्योम *irq_data)
अणु
	काष्ठा da9052 *da9052 = irq_data;

	complete(&da9052->करोne);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक da9052_irq_init(काष्ठा da9052 *da9052)
अणु
	पूर्णांक ret;

	ret = regmap_add_irq_chip(da9052->regmap, da9052->chip_irq,
				  IRQF_TRIGGER_LOW | IRQF_ONESHOT,
				  -1, &da9052_regmap_irq_chip,
				  &da9052->irq_data);
	अगर (ret < 0) अणु
		dev_err(da9052->dev, "regmap_add_irq_chip failed: %d\n", ret);
		जाओ regmap_err;
	पूर्ण

	enable_irq_wake(da9052->chip_irq);

	ret = da9052_request_irq(da9052, DA9052_IRQ_ADC_EOM, "adc-irq",
			    da9052_auxadc_irq, da9052);

	अगर (ret != 0) अणु
		dev_err(da9052->dev, "DA9052_IRQ_ADC_EOM failed: %d\n", ret);
		जाओ request_irq_err;
	पूर्ण

	वापस 0;

request_irq_err:
	regmap_del_irq_chip(da9052->chip_irq, da9052->irq_data);
regmap_err:
	वापस ret;

पूर्ण

पूर्णांक da9052_irq_निकास(काष्ठा da9052 *da9052)
अणु
	da9052_मुक्त_irq(da9052, DA9052_IRQ_ADC_EOM, da9052);
	regmap_del_irq_chip(da9052->chip_irq, da9052->irq_data);

	वापस 0;
पूर्ण
