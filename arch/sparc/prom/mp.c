<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * mp.c:  OpenBoot Prom Multiprocessor support routines.  Don't call
 *        these on a UP or अन्यथा you will halt and catch fire. ;)
 *
 * Copyright (C) 1995 David S. Miller (davem@caip.rutgers.edu)
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/खोलोprom.h>
#समावेश <यंत्र/oplib.h>

बाह्य व्योम restore_current(व्योम);

/* Start cpu with prom-tree node 'cpunode' using context described
 * by 'ctable_reg' in context 'ctx' at program counter 'pc'.
 *
 * XXX Have to look पूर्णांकo what the वापस values mean. XXX
 */
पूर्णांक
prom_startcpu(पूर्णांक cpunode, काष्ठा linux_prom_रेजिस्टरs *ctable_reg, पूर्णांक ctx, अक्षर *pc)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&prom_lock, flags);
	चयन(prom_vers) अणु
	हाल PROM_V0:
	हाल PROM_V2:
	शेष:
		ret = -1;
		अवरोध;
	हाल PROM_V3:
		ret = (*(romvec->v3_cpustart))(cpunode, (पूर्णांक) ctable_reg, ctx, pc);
		अवरोध;
	पूर्ण
	restore_current();
	spin_unlock_irqrestore(&prom_lock, flags);

	वापस ret;
पूर्ण
