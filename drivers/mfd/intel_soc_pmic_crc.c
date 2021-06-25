<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Device access क्रम Crystal Cove PMIC
 *
 * Copyright (C) 2013, 2014 Intel Corporation. All rights reserved.
 *
 * Author: Yang, Bin <bin.yang@पूर्णांकel.com>
 * Author: Zhu, Lejun <lejun.zhu@linux.पूर्णांकel.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/पूर्णांकel_soc_pmic.h>

#समावेश "intel_soc_pmic_core.h"

#घोषणा CRYSTAL_COVE_MAX_REGISTER	0xC6

#घोषणा CRYSTAL_COVE_REG_IRQLVL1	0x02
#घोषणा CRYSTAL_COVE_REG_MIRQLVL1	0x0E

#घोषणा CRYSTAL_COVE_IRQ_PWRSRC		0
#घोषणा CRYSTAL_COVE_IRQ_THRM		1
#घोषणा CRYSTAL_COVE_IRQ_BCU		2
#घोषणा CRYSTAL_COVE_IRQ_ADC		3
#घोषणा CRYSTAL_COVE_IRQ_CHGR		4
#घोषणा CRYSTAL_COVE_IRQ_GPIO		5
#घोषणा CRYSTAL_COVE_IRQ_VHDMIOCP	6

अटल स्थिर काष्ठा resource gpio_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(CRYSTAL_COVE_IRQ_GPIO, "GPIO"),
पूर्ण;

अटल स्थिर काष्ठा resource pwrsrc_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(CRYSTAL_COVE_IRQ_PWRSRC, "PWRSRC"),
पूर्ण;

अटल स्थिर काष्ठा resource adc_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(CRYSTAL_COVE_IRQ_ADC, "ADC"),
पूर्ण;

अटल स्थिर काष्ठा resource thermal_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(CRYSTAL_COVE_IRQ_THRM, "THERMAL"),
पूर्ण;

अटल स्थिर काष्ठा resource bcu_resources[] = अणु
	DEFINE_RES_IRQ_NAMED(CRYSTAL_COVE_IRQ_BCU, "BCU"),
पूर्ण;

अटल काष्ठा mfd_cell crystal_cove_byt_dev[] = अणु
	अणु
		.name = "crystal_cove_pwrsrc",
		.num_resources = ARRAY_SIZE(pwrsrc_resources),
		.resources = pwrsrc_resources,
	पूर्ण,
	अणु
		.name = "crystal_cove_adc",
		.num_resources = ARRAY_SIZE(adc_resources),
		.resources = adc_resources,
	पूर्ण,
	अणु
		.name = "crystal_cove_thermal",
		.num_resources = ARRAY_SIZE(thermal_resources),
		.resources = thermal_resources,
	पूर्ण,
	अणु
		.name = "crystal_cove_bcu",
		.num_resources = ARRAY_SIZE(bcu_resources),
		.resources = bcu_resources,
	पूर्ण,
	अणु
		.name = "crystal_cove_gpio",
		.num_resources = ARRAY_SIZE(gpio_resources),
		.resources = gpio_resources,
	पूर्ण,
	अणु
		.name = "byt_crystal_cove_pmic",
	पूर्ण,
	अणु
		.name = "crystal_cove_pwm",
	पूर्ण,
पूर्ण;

अटल काष्ठा mfd_cell crystal_cove_cht_dev[] = अणु
	अणु
		.name = "crystal_cove_gpio",
		.num_resources = ARRAY_SIZE(gpio_resources),
		.resources = gpio_resources,
	पूर्ण,
	अणु
		.name = "cht_crystal_cove_pmic",
	पूर्ण,
	अणु
		.name = "crystal_cove_pwm",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config crystal_cove_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CRYSTAL_COVE_MAX_REGISTER,
	.cache_type = REGCACHE_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq crystal_cove_irqs[] = अणु
	REGMAP_IRQ_REG(CRYSTAL_COVE_IRQ_PWRSRC, 0, BIT(CRYSTAL_COVE_IRQ_PWRSRC)),
	REGMAP_IRQ_REG(CRYSTAL_COVE_IRQ_THRM, 0, BIT(CRYSTAL_COVE_IRQ_THRM)),
	REGMAP_IRQ_REG(CRYSTAL_COVE_IRQ_BCU, 0, BIT(CRYSTAL_COVE_IRQ_BCU)),
	REGMAP_IRQ_REG(CRYSTAL_COVE_IRQ_ADC, 0, BIT(CRYSTAL_COVE_IRQ_ADC)),
	REGMAP_IRQ_REG(CRYSTAL_COVE_IRQ_CHGR, 0, BIT(CRYSTAL_COVE_IRQ_CHGR)),
	REGMAP_IRQ_REG(CRYSTAL_COVE_IRQ_GPIO, 0, BIT(CRYSTAL_COVE_IRQ_GPIO)),
	REGMAP_IRQ_REG(CRYSTAL_COVE_IRQ_VHDMIOCP, 0, BIT(CRYSTAL_COVE_IRQ_VHDMIOCP)),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip crystal_cove_irq_chip = अणु
	.name = "Crystal Cove",
	.irqs = crystal_cove_irqs,
	.num_irqs = ARRAY_SIZE(crystal_cove_irqs),
	.num_regs = 1,
	.status_base = CRYSTAL_COVE_REG_IRQLVL1,
	.mask_base = CRYSTAL_COVE_REG_MIRQLVL1,
पूर्ण;

काष्ठा पूर्णांकel_soc_pmic_config पूर्णांकel_soc_pmic_config_byt_crc = अणु
	.irq_flags = IRQF_TRIGGER_RISING,
	.cell_dev = crystal_cove_byt_dev,
	.n_cell_devs = ARRAY_SIZE(crystal_cove_byt_dev),
	.regmap_config = &crystal_cove_regmap_config,
	.irq_chip = &crystal_cove_irq_chip,
पूर्ण;

काष्ठा पूर्णांकel_soc_pmic_config पूर्णांकel_soc_pmic_config_cht_crc = अणु
	.irq_flags = IRQF_TRIGGER_RISING,
	.cell_dev = crystal_cove_cht_dev,
	.n_cell_devs = ARRAY_SIZE(crystal_cove_cht_dev),
	.regmap_config = &crystal_cove_regmap_config,
	.irq_chip = &crystal_cove_irq_chip,
पूर्ण;
