<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Low-level task चयनing. This is based on inक्रमmation published in
 * the Processor Abstraction Layer and the System Abstraction Layer
 * manual.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 */
#अगर_अघोषित _ASM_IA64_SWITCH_TO_H
#घोषणा _ASM_IA64_SWITCH_TO_H

#समावेश <linux/percpu.h>

काष्ठा task_काष्ठा;

/*
 * Context चयन from one thपढ़ो to another.  If the two thपढ़ोs have
 * dअगरferent address spaces, schedule() has alपढ़ोy taken care of
 * चयनing to the new address space by calling चयन_mm().
 *
 * Disabling access to the fph partition and the debug-रेजिस्टर
 * context चयन MUST be करोne beक्रमe calling ia64_चयन_to() since a
 * newly created thपढ़ो वापसs directly to
 * ia64_ret_from_syscall_clear_r8.
 */
बाह्य काष्ठा task_काष्ठा *ia64_चयन_to (व्योम *next_task);

बाह्य व्योम ia64_save_extra (काष्ठा task_काष्ठा *task);
बाह्य व्योम ia64_load_extra (काष्ठा task_काष्ठा *task);

#घोषणा IA64_HAS_EXTRA_STATE(t)							\
	((t)->thपढ़ो.flags & (IA64_THREAD_DBG_VALID|IA64_THREAD_PM_VALID))

#घोषणा __चयन_to(prev,next,last) करो अणु							 \
	अगर (IA64_HAS_EXTRA_STATE(prev))								 \
		ia64_save_extra(prev);								 \
	अगर (IA64_HAS_EXTRA_STATE(next))								 \
		ia64_load_extra(next);								 \
	ia64_psr(task_pt_regs(next))->dfh = !ia64_is_local_fpu_owner(next);			 \
	(last) = ia64_चयन_to((next));							 \
पूर्ण जबतक (0)

#अगर_घोषित CONFIG_SMP
/*
 * In the SMP हाल, we save the fph state when context-चयनing away from a thपढ़ो that
 * modअगरied fph.  This way, when the thपढ़ो माला_लो scheduled on another CPU, the CPU can
 * pick up the state from task->thपढ़ो.fph, aव्योमing the complication of having to fetch
 * the latest fph state from another CPU.  In other words: eager save, lazy restore.
 */
# define चयन_to(prev,next,last) करो अणु						\
	अगर (ia64_psr(task_pt_regs(prev))->mfh && ia64_is_local_fpu_owner(prev)) अणु				\
		ia64_psr(task_pt_regs(prev))->mfh = 0;			\
		(prev)->thपढ़ो.flags |= IA64_THREAD_FPH_VALID;			\
		__ia64_save_fpu((prev)->thपढ़ो.fph);				\
	पूर्ण									\
	__चयन_to(prev, next, last);						\
	/* "next" in old context is "current" in new context */			\
	अगर (unlikely((current->thपढ़ो.flags & IA64_THREAD_MIGRATION) &&	       \
		     (task_cpu(current) !=				       \
		      		      task_thपढ़ो_info(current)->last_cpu))) अणु \
		task_thपढ़ो_info(current)->last_cpu = task_cpu(current);       \
	पूर्ण								       \
पूर्ण जबतक (0)
#अन्यथा
# define चयन_to(prev,next,last)	__चयन_to(prev, next, last)
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_IA64_SWITCH_TO_H */
