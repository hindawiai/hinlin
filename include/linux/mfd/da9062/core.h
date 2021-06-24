<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015-2017  Dialog Semiconductor
 */

#अगर_अघोषित __MFD_DA9062_CORE_H__
#घोषणा __MFD_DA9062_CORE_H__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/da9062/रेजिस्टरs.h>

क्रमागत da9062_compatible_types अणु
	COMPAT_TYPE_DA9061 = 1,
	COMPAT_TYPE_DA9062,
पूर्ण;

क्रमागत da9061_irqs अणु
	/* IRQ A */
	DA9061_IRQ_ONKEY,
	DA9061_IRQ_WDG_WARN,
	DA9061_IRQ_SEQ_RDY,
	/* IRQ B*/
	DA9061_IRQ_TEMP,
	DA9061_IRQ_LDO_LIM,
	DA9061_IRQ_DVC_RDY,
	DA9061_IRQ_VDD_WARN,
	/* IRQ C */
	DA9061_IRQ_GPI0,
	DA9061_IRQ_GPI1,
	DA9061_IRQ_GPI2,
	DA9061_IRQ_GPI3,
	DA9061_IRQ_GPI4,

	DA9061_NUM_IRQ,
पूर्ण;

क्रमागत da9062_irqs अणु
	/* IRQ A */
	DA9062_IRQ_ONKEY,
	DA9062_IRQ_ALARM,
	DA9062_IRQ_TICK,
	DA9062_IRQ_WDG_WARN,
	DA9062_IRQ_SEQ_RDY,
	/* IRQ B*/
	DA9062_IRQ_TEMP,
	DA9062_IRQ_LDO_LIM,
	DA9062_IRQ_DVC_RDY,
	DA9062_IRQ_VDD_WARN,
	/* IRQ C */
	DA9062_IRQ_GPI0,
	DA9062_IRQ_GPI1,
	DA9062_IRQ_GPI2,
	DA9062_IRQ_GPI3,
	DA9062_IRQ_GPI4,

	DA9062_NUM_IRQ,
पूर्ण;

काष्ठा da9062 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा regmap_irq_chip_data *regmap_irq;
	क्रमागत da9062_compatible_types chip_type;
पूर्ण;

#पूर्ण_अगर /* __MFD_DA9062_CORE_H__ */
