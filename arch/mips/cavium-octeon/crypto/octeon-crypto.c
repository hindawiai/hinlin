<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2004-2012 Cavium Networks
 */

#समावेश <यंत्र/cop2.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched/task_stack.h>

#समावेश "octeon-crypto.h"

/**
 * Enable access to Octeon's COP2 crypto hardware क्रम kernel use. Wrap any
 * crypto operations in calls to octeon_crypto_enable/disable in order to make
 * sure the state of COP2 isn't corrupted अगर userspace is also perक्रमming
 * hardware crypto operations. Allocate the state parameter on the stack.
 * Returns with preemption disabled.
 *
 * @state: Poपूर्णांकer to state काष्ठाure to store current COP2 state in.
 *
 * Returns: Flags to be passed to octeon_crypto_disable()
 */
अचिन्हित दीर्घ octeon_crypto_enable(काष्ठा octeon_cop2_state *state)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ flags;

	preempt_disable();
	local_irq_save(flags);
	status = पढ़ो_c0_status();
	ग_लिखो_c0_status(status | ST0_CU2);
	अगर (KSTK_STATUS(current) & ST0_CU2) अणु
		octeon_cop2_save(&(current->thपढ़ो.cp2));
		KSTK_STATUS(current) &= ~ST0_CU2;
		status &= ~ST0_CU2;
	पूर्ण अन्यथा अगर (status & ST0_CU2) अणु
		octeon_cop2_save(state);
	पूर्ण
	local_irq_restore(flags);
	वापस status & ST0_CU2;
पूर्ण
EXPORT_SYMBOL_GPL(octeon_crypto_enable);

/**
 * Disable access to Octeon's COP2 crypto hardware in the kernel. This must be
 * called after an octeon_crypto_enable() beक्रमe any context चयन or वापस to
 * userspace.
 *
 * @state:	Poपूर्णांकer to COP2 state to restore
 * @flags:	Return value from octeon_crypto_enable()
 */
व्योम octeon_crypto_disable(काष्ठा octeon_cop2_state *state,
			   अचिन्हित दीर्घ crypto_flags)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर (crypto_flags & ST0_CU2)
		octeon_cop2_restore(state);
	अन्यथा
		ग_लिखो_c0_status(पढ़ो_c0_status() & ~ST0_CU2);
	local_irq_restore(flags);
	preempt_enable();
पूर्ण
EXPORT_SYMBOL_GPL(octeon_crypto_disable);
