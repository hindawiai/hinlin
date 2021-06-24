<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2006 Linus Torvalds, Ingo Molnar
 * Copyright (C) 2005-2006, Thomas Gleixner
 *
 * This file contains the IRQ-resend code
 *
 * If the पूर्णांकerrupt is रुकोing to be processed, we try to re-run it.
 * We can't directly run it from here since the caller might be in an
 * पूर्णांकerrupt-रक्षित region. Not all irq controller chips can
 * retrigger पूर्णांकerrupts at the hardware level, so in those हालs
 * we allow the resending of IRQs via a tasklet.
 */

#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "internals.h"

#अगर_घोषित CONFIG_HARसूचीQS_SW_RESEND

/* Biपंचांगap to handle software resend of पूर्णांकerrupts: */
अटल DECLARE_BITMAP(irqs_resend, IRQ_BITMAP_BITS);

/*
 * Run software resends of IRQ's
 */
अटल व्योम resend_irqs(काष्ठा tasklet_काष्ठा *unused)
अणु
	काष्ठा irq_desc *desc;
	पूर्णांक irq;

	जबतक (!biपंचांगap_empty(irqs_resend, nr_irqs)) अणु
		irq = find_first_bit(irqs_resend, nr_irqs);
		clear_bit(irq, irqs_resend);
		desc = irq_to_desc(irq);
		अगर (!desc)
			जारी;
		local_irq_disable();
		desc->handle_irq(desc);
		local_irq_enable();
	पूर्ण
पूर्ण

/* Tasklet to handle resend: */
अटल DECLARE_TASKLET(resend_tasklet, resend_irqs);

अटल पूर्णांक irq_sw_resend(काष्ठा irq_desc *desc)
अणु
	अचिन्हित पूर्णांक irq = irq_desc_get_irq(desc);

	/*
	 * Validate whether this पूर्णांकerrupt can be safely injected from
	 * non पूर्णांकerrupt context
	 */
	अगर (handle_enक्रमce_irqctx(&desc->irq_data))
		वापस -EINVAL;

	/*
	 * If the पूर्णांकerrupt is running in the thपढ़ो context of the parent
	 * irq we need to be careful, because we cannot trigger it
	 * directly.
	 */
	अगर (irq_settings_is_nested_thपढ़ो(desc)) अणु
		/*
		 * If the parent_irq is valid, we retrigger the parent,
		 * otherwise we करो nothing.
		 */
		अगर (!desc->parent_irq)
			वापस -EINVAL;
		irq = desc->parent_irq;
	पूर्ण

	/* Set it pending and activate the softirq: */
	set_bit(irq, irqs_resend);
	tasklet_schedule(&resend_tasklet);
	वापस 0;
पूर्ण

#अन्यथा
अटल पूर्णांक irq_sw_resend(काष्ठा irq_desc *desc)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक try_retrigger(काष्ठा irq_desc *desc)
अणु
	अगर (desc->irq_data.chip->irq_retrigger)
		वापस desc->irq_data.chip->irq_retrigger(&desc->irq_data);

#अगर_घोषित CONFIG_IRQ_DOMAIN_HIERARCHY
	वापस irq_chip_retrigger_hierarchy(&desc->irq_data);
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/*
 * IRQ resend
 *
 * Is called with पूर्णांकerrupts disabled and desc->lock held.
 */
पूर्णांक check_irq_resend(काष्ठा irq_desc *desc, bool inject)
अणु
	पूर्णांक err = 0;

	/*
	 * We करो not resend level type पूर्णांकerrupts. Level type पूर्णांकerrupts
	 * are resent by hardware when they are still active. Clear the
	 * pending bit so suspend/resume करोes not get confused.
	 */
	अगर (irq_settings_is_level(desc)) अणु
		desc->istate &= ~IRQS_PENDING;
		वापस -EINVAL;
	पूर्ण

	अगर (desc->istate & IRQS_REPLAY)
		वापस -EBUSY;

	अगर (!(desc->istate & IRQS_PENDING) && !inject)
		वापस 0;

	desc->istate &= ~IRQS_PENDING;

	अगर (!try_retrigger(desc))
		err = irq_sw_resend(desc);

	/* If the retrigger was successful, mark it with the REPLAY bit */
	अगर (!err)
		desc->istate |= IRQS_REPLAY;
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IRQ_INJECTION
/**
 * irq_inject_पूर्णांकerrupt - Inject an पूर्णांकerrupt क्रम testing/error injection
 * @irq:	The पूर्णांकerrupt number
 *
 * This function must only be used क्रम debug and testing purposes!
 *
 * Especially on x86 this can cause a premature completion of an पूर्णांकerrupt
 * affinity change causing the पूर्णांकerrupt line to become stale. Very
 * unlikely, but possible.
 *
 * The injection can fail क्रम various reasons:
 * - Interrupt is not activated
 * - Interrupt is NMI type or currently replaying
 * - Interrupt is level type
 * - Interrupt करोes not support hardware retrigger and software resend is
 *   either not enabled or not possible क्रम the पूर्णांकerrupt.
 */
पूर्णांक irq_inject_पूर्णांकerrupt(अचिन्हित पूर्णांक irq)
अणु
	काष्ठा irq_desc *desc;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	/* Try the state injection hardware पूर्णांकerface first */
	अगर (!irq_set_irqchip_state(irq, IRQCHIP_STATE_PENDING, true))
		वापस 0;

	/* That failed, try via the resend mechanism */
	desc = irq_get_desc_buslock(irq, &flags, 0);
	अगर (!desc)
		वापस -EINVAL;

	/*
	 * Only try to inject when the पूर्णांकerrupt is:
	 *  - not NMI type
	 *  - activated
	 */
	अगर ((desc->istate & IRQS_NMI) || !irqd_is_activated(&desc->irq_data))
		err = -EINVAL;
	अन्यथा
		err = check_irq_resend(desc, true);

	irq_put_desc_busunlock(desc, flags);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(irq_inject_पूर्णांकerrupt);
#पूर्ण_अगर
