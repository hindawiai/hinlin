<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_PROCESSOR_H
#घोषणा __ASM_CSKY_PROCESSOR_H

#समावेश <linux/bitops.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/cache.h>
#समावेश <abi/reg_ops.h>
#समावेश <abi/regdef.h>
#समावेश <abi/चयन_context.h>
#अगर_घोषित CONFIG_CPU_HAS_FPU
#समावेश <abi/fpu.h>
#पूर्ण_अगर

काष्ठा cpuinfo_csky अणु
	अचिन्हित दीर्घ asid_cache;
पूर्ण __aligned(SMP_CACHE_BYTES);

बाह्य काष्ठा cpuinfo_csky cpu_data[];

/*
 * User space process size: 2GB. This is hardcoded पूर्णांकo a few places,
 * so करोn't change it unless you know what you are करोing.  TASK_SIZE
 * क्रम a 64 bit kernel expandable to 8192EB, of which the current CSKY
 * implementations will "only" be able to use 1TB ...
 */
#घोषणा TASK_SIZE	(PAGE_OFFSET - (PAGE_SIZE * 8))

#अगर_घोषित __KERNEL__
#घोषणा STACK_TOP       TASK_SIZE
#घोषणा STACK_TOP_MAX   STACK_TOP
#पूर्ण_अगर

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE      (TASK_SIZE / 3)

काष्ठा thपढ़ो_काष्ठा अणु
	अचिन्हित दीर्घ  sp;        /* kernel stack poपूर्णांकer */
	अचिन्हित दीर्घ  trap_no;   /* saved status रेजिस्टर */

	/* FPU regs */
	काष्ठा user_fp __aligned(16) user_fp;
पूर्ण;

#घोषणा INIT_THREAD  अणु \
	.sp = माप(init_stack) + (अचिन्हित दीर्घ) &init_stack, \
पूर्ण

/*
 * Do necessary setup to start up a newly executed thपढ़ो.
 *
 * pass the data segment पूर्णांकo user programs अगर it exists,
 * it can't hurt anything as far as I can tell
 */
#घोषणा start_thपढ़ो(_regs, _pc, _usp)					\
करो अणु									\
	set_fs(USER_DS); /* पढ़ोs from user space */			\
	(_regs)->pc = (_pc);						\
	(_regs)->regs[1] = 0; /* ABIV1 is R7, uClibc_मुख्य rtdl arg */	\
	(_regs)->regs[2] = 0;						\
	(_regs)->regs[3] = 0; /* ABIV2 is R7, use it? */		\
	(_regs)->sr &= ~PS_S;						\
	(_regs)->usp = (_usp);						\
पूर्ण जबतक (0)

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *dead_task)
अणु
पूर्ण

/* Prepare to copy thपढ़ो state - unlazy all lazy status */
#घोषणा prepare_to_copy(tsk)    करो अणु पूर्ण जबतक (0)

बाह्य पूर्णांक kernel_thपढ़ो(पूर्णांक (*fn)(व्योम *), व्योम *arg, अचिन्हित दीर्घ flags);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा KSTK_EIP(tsk)		(task_pt_regs(tsk)->pc)
#घोषणा KSTK_ESP(tsk)		(task_pt_regs(tsk)->usp)

#घोषणा task_pt_regs(p) \
	((काष्ठा pt_regs *)(THREAD_SIZE + task_stack_page(p)) - 1)

#घोषणा cpu_relax() barrier()

#पूर्ण_अगर /* __ASM_CSKY_PROCESSOR_H */
