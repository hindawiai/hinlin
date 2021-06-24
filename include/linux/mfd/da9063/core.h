<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Definitions क्रम DA9063 MFD driver
 *
 * Copyright 2012 Dialog Semiconductor Ltd.
 *
 * Author: Michal Hajduk, Dialog Semiconductor
 * Author: Krystian Garbaciak, Dialog Semiconductor
 */

#अगर_अघोषित __MFD_DA9063_CORE_H__
#घोषणा __MFD_DA9063_CORE_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/da9063/रेजिस्टरs.h>

/* DA9063 modules */
#घोषणा DA9063_DRVNAME_CORE		"da9063-core"
#घोषणा DA9063_DRVNAME_REGULATORS	"da9063-regulators"
#घोषणा DA9063_DRVNAME_LEDS		"da9063-leds"
#घोषणा DA9063_DRVNAME_WATCHDOG		"da9063-watchdog"
#घोषणा DA9063_DRVNAME_HWMON		"da9063-hwmon"
#घोषणा DA9063_DRVNAME_ONKEY		"da9063-onkey"
#घोषणा DA9063_DRVNAME_RTC		"da9063-rtc"
#घोषणा DA9063_DRVNAME_VIBRATION	"da9063-vibration"

#घोषणा PMIC_CHIP_ID_DA9063		0x61

क्रमागत da9063_type अणु
	PMIC_TYPE_DA9063 = 0,
	PMIC_TYPE_DA9063L,
पूर्ण;

क्रमागत da9063_variant_codes अणु
	PMIC_DA9063_AD = 0x3,
	PMIC_DA9063_BB = 0x5,
	PMIC_DA9063_CA = 0x6,
	PMIC_DA9063_DA = 0x7,
पूर्ण;

/* Interrupts */
क्रमागत da9063_irqs अणु
	DA9063_IRQ_ONKEY = 0,
	DA9063_IRQ_ALARM,
	DA9063_IRQ_TICK,
	DA9063_IRQ_ADC_RDY,
	DA9063_IRQ_SEQ_RDY,
	DA9063_IRQ_WAKE,
	DA9063_IRQ_TEMP,
	DA9063_IRQ_COMP_1V2,
	DA9063_IRQ_LDO_LIM,
	DA9063_IRQ_REG_UVOV,
	DA9063_IRQ_DVC_RDY,
	DA9063_IRQ_VDD_MON,
	DA9063_IRQ_WARN,
	DA9063_IRQ_GPI0,
	DA9063_IRQ_GPI1,
	DA9063_IRQ_GPI2,
	DA9063_IRQ_GPI3,
	DA9063_IRQ_GPI4,
	DA9063_IRQ_GPI5,
	DA9063_IRQ_GPI6,
	DA9063_IRQ_GPI7,
	DA9063_IRQ_GPI8,
	DA9063_IRQ_GPI9,
	DA9063_IRQ_GPI10,
	DA9063_IRQ_GPI11,
	DA9063_IRQ_GPI12,
	DA9063_IRQ_GPI13,
	DA9063_IRQ_GPI14,
	DA9063_IRQ_GPI15,
पूर्ण;

काष्ठा da9063 अणु
	/* Device */
	काष्ठा device	*dev;
	क्रमागत da9063_type type;
	अचिन्हित अक्षर	variant_code;
	अचिन्हित पूर्णांक	flags;

	/* Control पूर्णांकerface */
	काष्ठा regmap	*regmap;

	/* Interrupts */
	पूर्णांक		chip_irq;
	अचिन्हित पूर्णांक	irq_base;
	काष्ठा regmap_irq_chip_data *regmap_irq;
पूर्ण;

पूर्णांक da9063_device_init(काष्ठा da9063 *da9063, अचिन्हित पूर्णांक irq);
पूर्णांक da9063_irq_init(काष्ठा da9063 *da9063);

#पूर्ण_अगर /* __MFD_DA9063_CORE_H__ */
