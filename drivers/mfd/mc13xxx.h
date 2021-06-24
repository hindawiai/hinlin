<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2012 Creative Product Design
 * Marc Reilly <marc@cpdesign.com.au>
 */
#अगर_अघोषित __DRIVERS_MFD_MC13XXX_H
#घोषणा __DRIVERS_MFD_MC13XXX_H

#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>
#समावेश <linux/mfd/mc13xxx.h>

#घोषणा MC13XXX_NUMREGS		0x3f
#घोषणा MC13XXX_IRQ_REG_CNT	2
#घोषणा MC13XXX_IRQ_PER_REG	24

काष्ठा mc13xxx;

काष्ठा mc13xxx_variant अणु
	स्थिर अक्षर *name;
	व्योम (*prपूर्णांक_revision)(काष्ठा mc13xxx *mc13xxx, u32 revision);
पूर्ण;

बाह्य काष्ठा mc13xxx_variant
		mc13xxx_variant_mc13783,
		mc13xxx_variant_mc13892,
		mc13xxx_variant_mc34708;

काष्ठा mc13xxx अणु
	काष्ठा regmap *regmap;

	काष्ठा device *dev;
	स्थिर काष्ठा mc13xxx_variant *variant;

	काष्ठा regmap_irq irqs[MC13XXX_IRQ_PER_REG * MC13XXX_IRQ_REG_CNT];
	काष्ठा regmap_irq_chip irq_chip;
	काष्ठा regmap_irq_chip_data *irq_data;

	काष्ठा mutex lock;
	पूर्णांक irq;
	पूर्णांक flags;

	पूर्णांक adcflags;
पूर्ण;

पूर्णांक mc13xxx_common_init(काष्ठा device *dev);
पूर्णांक mc13xxx_common_निकास(काष्ठा device *dev);

#पूर्ण_अगर /* __DRIVERS_MFD_MC13XXX_H */
