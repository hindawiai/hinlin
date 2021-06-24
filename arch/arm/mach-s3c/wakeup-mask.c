<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2010 Ben Dooks <ben-linux@fluff.org>
//
// Support क्रम wakeup mask पूर्णांकerrupts on newer SoCs

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>

#समावेश "wakeup-mask.h"
#समावेश "pm.h"

व्योम samsung_sync_wakemask(व्योम __iomem *reg,
			   स्थिर काष्ठा samsung_wakeup_mask *mask, पूर्णांक nr_mask)
अणु
	काष्ठा irq_data *data;
	u32 val;

	val = __raw_पढ़ोl(reg);

	क्रम (; nr_mask > 0; nr_mask--, mask++) अणु
		अगर (mask->irq == NO_WAKEUP_IRQ) अणु
			val |= mask->bit;
			जारी;
		पूर्ण

		data = irq_get_irq_data(mask->irq);

		/* bit of a liberty to पढ़ो this directly from irq_data. */
		अगर (irqd_is_wakeup_set(data))
			val &= ~mask->bit;
		अन्यथा
			val |= mask->bit;
	पूर्ण

	prपूर्णांकk(KERN_INFO "wakemask %08x => %08x\n", __raw_पढ़ोl(reg), val);
	__raw_ग_लिखोl(val, reg);
पूर्ण
