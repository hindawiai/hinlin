<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Spin and पढ़ो/ग_लिखो lock operations.
 *
 * Copyright (C) 2001-2004 Paul Mackerras <paulus@au.ibm.com>, IBM
 * Copyright (C) 2001 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 * Copyright (C) 2002 Dave Engebretsen <engebret@us.ibm.com>, IBM
 *   Rework to support भव processors
 */

#समावेश <linux/kernel.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/smp.h>

/* रुकोing क्रम a spinlock... */
#अगर defined(CONFIG_PPC_SPLPAR)
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/smp.h>

व्योम splpar_spin_yield(arch_spinlock_t *lock)
अणु
	अचिन्हित पूर्णांक lock_value, holder_cpu, yield_count;

	lock_value = lock->slock;
	अगर (lock_value == 0)
		वापस;
	holder_cpu = lock_value & 0xffff;
	BUG_ON(holder_cpu >= NR_CPUS);

	yield_count = yield_count_of(holder_cpu);
	अगर ((yield_count & 1) == 0)
		वापस;		/* भव cpu is currently running */
	rmb();
	अगर (lock->slock != lock_value)
		वापस;		/* something has changed */
	yield_to_preempted(holder_cpu, yield_count);
पूर्ण
EXPORT_SYMBOL_GPL(splpar_spin_yield);

/*
 * Waiting क्रम a पढ़ो lock or a ग_लिखो lock on a rwlock...
 * This turns out to be the same क्रम पढ़ो and ग_लिखो locks, since
 * we only know the holder अगर it is ग_लिखो-locked.
 */
व्योम splpar_rw_yield(arch_rwlock_t *rw)
अणु
	पूर्णांक lock_value;
	अचिन्हित पूर्णांक holder_cpu, yield_count;

	lock_value = rw->lock;
	अगर (lock_value >= 0)
		वापस;		/* no ग_लिखो lock at present */
	holder_cpu = lock_value & 0xffff;
	BUG_ON(holder_cpu >= NR_CPUS);

	yield_count = yield_count_of(holder_cpu);
	अगर ((yield_count & 1) == 0)
		वापस;		/* भव cpu is currently running */
	rmb();
	अगर (rw->lock != lock_value)
		वापस;		/* something has changed */
	yield_to_preempted(holder_cpu, yield_count);
पूर्ण
#पूर्ण_अगर
