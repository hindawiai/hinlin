<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/bug.h>
#समावेश <linux/export.h>
#समावेश <linux/irqflags.h>

noinstr व्योम warn_bogus_irq_restore(व्योम)
अणु
	instrumentation_begin();
	WARN_ONCE(1, "raw_local_irq_restore() called with IRQs enabled\n");
	instrumentation_end();
पूर्ण
EXPORT_SYMBOL(warn_bogus_irq_restore);
