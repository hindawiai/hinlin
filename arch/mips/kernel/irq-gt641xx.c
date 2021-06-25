<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  GT641xx IRQ routines.
 *
 *  Copyright (C) 2007	Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/gt64120.h>

#घोषणा GT641XX_IRQ_TO_BIT(irq) (1U << (irq - GT641XX_IRQ_BASE))

अटल DEFINE_RAW_SPINLOCK(gt641xx_irq_lock);

अटल व्योम ack_gt641xx_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 cause;

	raw_spin_lock_irqsave(&gt641xx_irq_lock, flags);
	cause = GT_READ(GT_INTRCAUSE_OFS);
	cause &= ~GT641XX_IRQ_TO_BIT(d->irq);
	GT_WRITE(GT_INTRCAUSE_OFS, cause);
	raw_spin_unlock_irqrestore(&gt641xx_irq_lock, flags);
पूर्ण

अटल व्योम mask_gt641xx_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask;

	raw_spin_lock_irqsave(&gt641xx_irq_lock, flags);
	mask = GT_READ(GT_INTRMASK_OFS);
	mask &= ~GT641XX_IRQ_TO_BIT(d->irq);
	GT_WRITE(GT_INTRMASK_OFS, mask);
	raw_spin_unlock_irqrestore(&gt641xx_irq_lock, flags);
पूर्ण

अटल व्योम mask_ack_gt641xx_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 cause, mask;

	raw_spin_lock_irqsave(&gt641xx_irq_lock, flags);
	mask = GT_READ(GT_INTRMASK_OFS);
	mask &= ~GT641XX_IRQ_TO_BIT(d->irq);
	GT_WRITE(GT_INTRMASK_OFS, mask);

	cause = GT_READ(GT_INTRCAUSE_OFS);
	cause &= ~GT641XX_IRQ_TO_BIT(d->irq);
	GT_WRITE(GT_INTRCAUSE_OFS, cause);
	raw_spin_unlock_irqrestore(&gt641xx_irq_lock, flags);
पूर्ण

अटल व्योम unmask_gt641xx_irq(काष्ठा irq_data *d)
अणु
	अचिन्हित दीर्घ flags;
	u32 mask;

	raw_spin_lock_irqsave(&gt641xx_irq_lock, flags);
	mask = GT_READ(GT_INTRMASK_OFS);
	mask |= GT641XX_IRQ_TO_BIT(d->irq);
	GT_WRITE(GT_INTRMASK_OFS, mask);
	raw_spin_unlock_irqrestore(&gt641xx_irq_lock, flags);
पूर्ण

अटल काष्ठा irq_chip gt641xx_irq_chip = अणु
	.name		= "GT641xx",
	.irq_ack	= ack_gt641xx_irq,
	.irq_mask	= mask_gt641xx_irq,
	.irq_mask_ack	= mask_ack_gt641xx_irq,
	.irq_unmask	= unmask_gt641xx_irq,
पूर्ण;

व्योम gt641xx_irq_dispatch(व्योम)
अणु
	u32 cause, mask;
	पूर्णांक i;

	cause = GT_READ(GT_INTRCAUSE_OFS);
	mask = GT_READ(GT_INTRMASK_OFS);
	cause &= mask;

	/*
	 * bit0 : logical or of all the पूर्णांकerrupt bits.
	 * bit30: logical or of bits[29:26,20:1].
	 * bit31: logical or of bits[25:1].
	 */
	क्रम (i = 1; i < 30; i++) अणु
		अगर (cause & (1U << i)) अणु
			करो_IRQ(GT641XX_IRQ_BASE + i);
			वापस;
		पूर्ण
	पूर्ण

	atomic_inc(&irq_err_count);
पूर्ण

व्योम __init gt641xx_irq_init(व्योम)
अणु
	पूर्णांक i;

	GT_WRITE(GT_INTRMASK_OFS, 0);
	GT_WRITE(GT_INTRCAUSE_OFS, 0);

	/*
	 * bit0 : logical or of all the पूर्णांकerrupt bits.
	 * bit30: logical or of bits[29:26,20:1].
	 * bit31: logical or of bits[25:1].
	 */
	क्रम (i = 1; i < 30; i++)
		irq_set_chip_and_handler(GT641XX_IRQ_BASE + i,
					 &gt641xx_irq_chip, handle_level_irq);
पूर्ण
