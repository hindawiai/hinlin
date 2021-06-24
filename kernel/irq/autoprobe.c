<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 1992, 1998-2004 Linus Torvalds, Ingo Molnar
 *
 * This file contains the पूर्णांकerrupt probing code and driver APIs.
 */

#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/async.h>

#समावेश "internals.h"

/*
 * Autodetection depends on the fact that any पूर्णांकerrupt that
 * comes in on to an unasचिन्हित handler will get stuck with
 * "IRQS_WAITING" cleared and the पूर्णांकerrupt disabled.
 */
अटल DEFINE_MUTEX(probing_active);

/**
 *	probe_irq_on	- begin an पूर्णांकerrupt स्वतःdetect
 *
 *	Commence probing क्रम an पूर्णांकerrupt. The पूर्णांकerrupts are scanned
 *	and a mask of potential पूर्णांकerrupt lines is वापसed.
 *
 */
अचिन्हित दीर्घ probe_irq_on(व्योम)
अणु
	काष्ठा irq_desc *desc;
	अचिन्हित दीर्घ mask = 0;
	पूर्णांक i;

	/*
	 * quiesce the kernel, or at least the asynchronous portion
	 */
	async_synchronize_full();
	mutex_lock(&probing_active);
	/*
	 * something may have generated an irq दीर्घ ago and we want to
	 * flush such a दीर्घstanding irq beक्रमe considering it as spurious.
	 */
	क्रम_each_irq_desc_reverse(i, desc) अणु
		raw_spin_lock_irq(&desc->lock);
		अगर (!desc->action && irq_settings_can_probe(desc)) अणु
			/*
			 * Some chips need to know about probing in
			 * progress:
			 */
			अगर (desc->irq_data.chip->irq_set_type)
				desc->irq_data.chip->irq_set_type(&desc->irq_data,
							 IRQ_TYPE_PROBE);
			irq_activate_and_startup(desc, IRQ_NORESEND);
		पूर्ण
		raw_spin_unlock_irq(&desc->lock);
	पूर्ण

	/* Wait क्रम दीर्घstanding पूर्णांकerrupts to trigger. */
	msleep(20);

	/*
	 * enable any unasचिन्हित irqs
	 * (we must startup again here because अगर a दीर्घstanding irq
	 * happened in the previous stage, it may have masked itself)
	 */
	क्रम_each_irq_desc_reverse(i, desc) अणु
		raw_spin_lock_irq(&desc->lock);
		अगर (!desc->action && irq_settings_can_probe(desc)) अणु
			desc->istate |= IRQS_AUTODETECT | IRQS_WAITING;
			अगर (irq_activate_and_startup(desc, IRQ_NORESEND))
				desc->istate |= IRQS_PENDING;
		पूर्ण
		raw_spin_unlock_irq(&desc->lock);
	पूर्ण

	/*
	 * Wait क्रम spurious पूर्णांकerrupts to trigger
	 */
	msleep(100);

	/*
	 * Now filter out any obviously spurious पूर्णांकerrupts
	 */
	क्रम_each_irq_desc(i, desc) अणु
		raw_spin_lock_irq(&desc->lock);

		अगर (desc->istate & IRQS_AUTODETECT) अणु
			/* It triggered alपढ़ोy - consider it spurious. */
			अगर (!(desc->istate & IRQS_WAITING)) अणु
				desc->istate &= ~IRQS_AUTODETECT;
				irq_shutकरोwn_and_deactivate(desc);
			पूर्ण अन्यथा
				अगर (i < 32)
					mask |= 1 << i;
		पूर्ण
		raw_spin_unlock_irq(&desc->lock);
	पूर्ण

	वापस mask;
पूर्ण
EXPORT_SYMBOL(probe_irq_on);

/**
 *	probe_irq_mask - scan a biपंचांगap of पूर्णांकerrupt lines
 *	@val:	mask of पूर्णांकerrupts to consider
 *
 *	Scan the पूर्णांकerrupt lines and वापस a biपंचांगap of active
 *	स्वतःdetect पूर्णांकerrupts. The पूर्णांकerrupt probe logic state
 *	is then वापसed to its previous value.
 *
 *	Note: we need to scan all the irq's even though we will
 *	only वापस स्वतःdetect irq numbers - just so that we reset
 *	them all to a known state.
 */
अचिन्हित पूर्णांक probe_irq_mask(अचिन्हित दीर्घ val)
अणु
	अचिन्हित पूर्णांक mask = 0;
	काष्ठा irq_desc *desc;
	पूर्णांक i;

	क्रम_each_irq_desc(i, desc) अणु
		raw_spin_lock_irq(&desc->lock);
		अगर (desc->istate & IRQS_AUTODETECT) अणु
			अगर (i < 16 && !(desc->istate & IRQS_WAITING))
				mask |= 1 << i;

			desc->istate &= ~IRQS_AUTODETECT;
			irq_shutकरोwn_and_deactivate(desc);
		पूर्ण
		raw_spin_unlock_irq(&desc->lock);
	पूर्ण
	mutex_unlock(&probing_active);

	वापस mask & val;
पूर्ण
EXPORT_SYMBOL(probe_irq_mask);

/**
 *	probe_irq_off	- end an पूर्णांकerrupt स्वतःdetect
 *	@val: mask of potential पूर्णांकerrupts (unused)
 *
 *	Scans the unused पूर्णांकerrupt lines and वापसs the line which
 *	appears to have triggered the पूर्णांकerrupt. If no पूर्णांकerrupt was
 *	found then zero is वापसed. If more than one पूर्णांकerrupt is
 *	found then minus the first candidate is वापसed to indicate
 *	their is करोubt.
 *
 *	The पूर्णांकerrupt probe logic state is वापसed to its previous
 *	value.
 *
 *	BUGS: When used in a module (which arguably shouldn't happen)
 *	nothing prevents two IRQ probe callers from overlapping. The
 *	results of this are non-optimal.
 */
पूर्णांक probe_irq_off(अचिन्हित दीर्घ val)
अणु
	पूर्णांक i, irq_found = 0, nr_of_irqs = 0;
	काष्ठा irq_desc *desc;

	क्रम_each_irq_desc(i, desc) अणु
		raw_spin_lock_irq(&desc->lock);

		अगर (desc->istate & IRQS_AUTODETECT) अणु
			अगर (!(desc->istate & IRQS_WAITING)) अणु
				अगर (!nr_of_irqs)
					irq_found = i;
				nr_of_irqs++;
			पूर्ण
			desc->istate &= ~IRQS_AUTODETECT;
			irq_shutकरोwn_and_deactivate(desc);
		पूर्ण
		raw_spin_unlock_irq(&desc->lock);
	पूर्ण
	mutex_unlock(&probing_active);

	अगर (nr_of_irqs > 1)
		irq_found = -irq_found;

	वापस irq_found;
पूर्ण
EXPORT_SYMBOL(probe_irq_off);

