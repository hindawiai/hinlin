<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com),
 *               Martin Schwidefsky (schwidefsky@de.ibm.com)
 *
 *  Derived from "include/asm-i386/processor.h"
 *    Copyright (C) 1994, Linus Torvalds
 */

#अगर_अघोषित __ASM_S390_PROCESSOR_H
#घोषणा __ASM_S390_PROCESSOR_H

#समावेश <linux/bits.h>

#घोषणा CIF_NOHZ_DELAY		2	/* delay HZ disable क्रम a tick */
#घोषणा CIF_FPU			3	/* restore FPU रेजिस्टरs */
#घोषणा CIF_ENABLED_WAIT	5	/* in enabled रुको state */
#घोषणा CIF_MCCK_GUEST		6	/* machine check happening in guest */
#घोषणा CIF_DEDICATED_CPU	7	/* this CPU is dedicated */

#घोषणा _CIF_NOHZ_DELAY		BIT(CIF_NOHZ_DELAY)
#घोषणा _CIF_FPU		BIT(CIF_FPU)
#घोषणा _CIF_ENABLED_WAIT	BIT(CIF_ENABLED_WAIT)
#घोषणा _CIF_MCCK_GUEST		BIT(CIF_MCCK_GUEST)
#घोषणा _CIF_DEDICATED_CPU	BIT(CIF_DEDICATED_CPU)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/cpumask.h>
#समावेश <linux/linkage.h>
#समावेश <linux/irqflags.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/runसमय_instr.h>
#समावेश <यंत्र/fpu/types.h>
#समावेश <यंत्र/fpu/पूर्णांकernal.h>
#समावेश <यंत्र/irqflags.h>

प्रकार दीर्घ (*sys_call_ptr_t)(काष्ठा pt_regs *regs);

अटल अंतरभूत व्योम set_cpu_flag(पूर्णांक flag)
अणु
	S390_lowcore.cpu_flags |= (1UL << flag);
पूर्ण

अटल अंतरभूत व्योम clear_cpu_flag(पूर्णांक flag)
अणु
	S390_lowcore.cpu_flags &= ~(1UL << flag);
पूर्ण

अटल अंतरभूत पूर्णांक test_cpu_flag(पूर्णांक flag)
अणु
	वापस !!(S390_lowcore.cpu_flags & (1UL << flag));
पूर्ण

/*
 * Test CIF flag of another CPU. The caller needs to ensure that
 * CPU hotplug can not happen, e.g. by disabling preemption.
 */
अटल अंतरभूत पूर्णांक test_cpu_flag_of(पूर्णांक flag, पूर्णांक cpu)
अणु
	काष्ठा lowcore *lc = lowcore_ptr[cpu];
	वापस !!(lc->cpu_flags & (1UL << flag));
पूर्ण

#घोषणा arch_needs_cpu() test_cpu_flag(CIF_NOHZ_DELAY)

अटल अंतरभूत व्योम get_cpu_id(काष्ठा cpuid *ptr)
अणु
	यंत्र अस्थिर("stidp %0" : "=Q" (*ptr));
पूर्ण

व्योम s390_adjust_jअगरfies(व्योम);
व्योम s390_update_cpu_mhz(व्योम);
व्योम cpu_detect_mhz_feature(व्योम);

बाह्य स्थिर काष्ठा seq_operations cpuinfo_op;
बाह्य व्योम execve_tail(व्योम);
बाह्य व्योम __bpon(व्योम);

/*
 * User space process size: 2GB क्रम 31 bit, 4TB or 8PT क्रम 64 bit.
 */

#घोषणा TASK_SIZE_OF(tsk)	(test_tsk_thपढ़ो_flag(tsk, TIF_31BIT) ? \
					_REGION3_SIZE : TASK_SIZE_MAX)
#घोषणा TASK_UNMAPPED_BASE	(test_thपढ़ो_flag(TIF_31BIT) ? \
					(_REGION3_SIZE >> 1) : (_REGION2_SIZE >> 1))
#घोषणा TASK_SIZE		TASK_SIZE_OF(current)
#घोषणा TASK_SIZE_MAX		(-PAGE_SIZE)

#घोषणा STACK_TOP		(test_thपढ़ो_flag(TIF_31BIT) ? \
					_REGION3_SIZE : _REGION2_SIZE)
#घोषणा STACK_TOP_MAX		_REGION2_SIZE

#घोषणा HAVE_ARCH_PICK_MMAP_LAYOUT

/*
 * Thपढ़ो काष्ठाure
 */
काष्ठा thपढ़ो_काष्ठा अणु
	अचिन्हित पूर्णांक  acrs[NUM_ACRS];
	अचिन्हित दीर्घ ksp;			/* kernel stack poपूर्णांकer */
	अचिन्हित दीर्घ user_समयr;		/* task cpuसमय in user space */
	अचिन्हित दीर्घ guest_समयr;		/* task cpuसमय in kvm guest */
	अचिन्हित दीर्घ प्रणाली_समयr;		/* task cpuसमय in kernel space */
	अचिन्हित दीर्घ hardirq_समयr;		/* task cpuसमय in hardirq context */
	अचिन्हित दीर्घ softirq_समयr;		/* task cpuसमय in softirq context */
	स्थिर sys_call_ptr_t *sys_call_table;	/* प्रणाली call table address */
	अचिन्हित दीर्घ gmap_addr;		/* address of last gmap fault. */
	अचिन्हित पूर्णांक gmap_ग_लिखो_flag;		/* gmap fault ग_लिखो indication */
	अचिन्हित पूर्णांक gmap_पूर्णांक_code;		/* पूर्णांक code of last gmap fault */
	अचिन्हित पूर्णांक gmap_pfault;		/* संकेत of a pending guest pfault */

	/* Per-thपढ़ो inक्रमmation related to debugging */
	काष्ठा per_regs per_user;		/* User specअगरied PER रेजिस्टरs */
	काष्ठा per_event per_event;		/* Cause of the last PER trap */
	अचिन्हित दीर्घ per_flags;		/* Flags to control debug behavior */
	अचिन्हित पूर्णांक प्रणाली_call;		/* प्रणाली call number in संकेत */
	अचिन्हित दीर्घ last_अवरोध;		/* last अवरोधing-event-address. */
	/* pfault_रुको is used to block the process on a pfault event */
	अचिन्हित दीर्घ pfault_रुको;
	काष्ठा list_head list;
	/* cpu runसमय instrumentation */
	काष्ठा runसमय_instr_cb *ri_cb;
	काष्ठा gs_cb *gs_cb;			/* Current guarded storage cb */
	काष्ठा gs_cb *gs_bc_cb;			/* Broadcast guarded storage cb */
	अचिन्हित अक्षर trap_tdb[256];		/* Transaction पात diagnose block */
	/*
	 * Warning: 'fpu' is dynamically-sized. It *MUST* be at
	 * the end.
	 */
	काष्ठा fpu fpu;			/* FP and VX रेजिस्टर save area */
पूर्ण;

/* Flag to disable transactions. */
#घोषणा PER_FLAG_NO_TE			1UL
/* Flag to enable अक्रमom transaction पातs. */
#घोषणा PER_FLAG_TE_ABORT_RAND		2UL
/* Flag to specअगरy अक्रमom transaction पात mode:
 * - पात each transaction at a अक्रमom inकाष्ठाion beक्रमe TEND अगर set.
 * - पात अक्रमom transactions at a अक्रमom inकाष्ठाion अगर cleared.
 */
#घोषणा PER_FLAG_TE_ABORT_RAND_TEND	4UL

प्रकार काष्ठा thपढ़ो_काष्ठा thपढ़ो_काष्ठा;

#घोषणा ARCH_MIN_TASKALIGN	8

#घोषणा INIT_THREAD अणु							\
	.ksp = माप(init_stack) + (अचिन्हित दीर्घ) &init_stack,	\
	.fpu.regs = (व्योम *) init_task.thपढ़ो.fpu.fprs,			\
	.last_अवरोध = 1,						\
पूर्ण

/*
 * Do necessary setup to start up a new thपढ़ो.
 */
#घोषणा start_thपढ़ो(regs, new_psw, new_stackp) करो अणु			\
	regs->psw.mask	= PSW_USER_BITS | PSW_MASK_EA | PSW_MASK_BA;	\
	regs->psw.addr	= new_psw;					\
	regs->gprs[15]	= new_stackp;					\
	execve_tail();							\
पूर्ण जबतक (0)

#घोषणा start_thपढ़ो31(regs, new_psw, new_stackp) करो अणु			\
	regs->psw.mask	= PSW_USER_BITS | PSW_MASK_BA;			\
	regs->psw.addr	= new_psw;					\
	regs->gprs[15]	= new_stackp;					\
	execve_tail();							\
पूर्ण जबतक (0)

/* Forward declaration, a strange C thing */
काष्ठा task_काष्ठा;
काष्ठा mm_काष्ठा;
काष्ठा seq_file;
काष्ठा pt_regs;

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs);
व्योम show_cacheinfo(काष्ठा seq_file *m);

/* Free all resources held by a thपढ़ो. */
अटल अंतरभूत व्योम release_thपढ़ो(काष्ठा task_काष्ठा *tsk) अणु पूर्ण

/* Free guarded storage control block */
व्योम guarded_storage_release(काष्ठा task_काष्ठा *tsk);
व्योम gs_load_bc_cb(काष्ठा pt_regs *regs);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);
#घोषणा task_pt_regs(tsk) ((काष्ठा pt_regs *) \
        (task_stack_page(tsk) + THREAD_SIZE) - 1)
#घोषणा KSTK_EIP(tsk)	(task_pt_regs(tsk)->psw.addr)
#घोषणा KSTK_ESP(tsk)	(task_pt_regs(tsk)->gprs[15])

/* Has task runसमय instrumentation enabled ? */
#घोषणा is_ri_task(tsk) (!!(tsk)->thपढ़ो.ri_cb)

अटल __always_अंतरभूत अचिन्हित दीर्घ current_stack_poपूर्णांकer(व्योम)
अणु
	अचिन्हित दीर्घ sp;

	यंत्र अस्थिर("la %0,0(15)" : "=a" (sp));
	वापस sp;
पूर्ण

अटल __no_kasan_or_अंतरभूत अचिन्हित लघु stap(व्योम)
अणु
	अचिन्हित लघु cpu_address;

	यंत्र अस्थिर("stap %0" : "=Q" (cpu_address));
	वापस cpu_address;
पूर्ण

#घोषणा cpu_relax() barrier()

#घोषणा ECAG_CACHE_ATTRIBUTE	0
#घोषणा ECAG_CPU_ATTRIBUTE	1

अटल अंतरभूत अचिन्हित दीर्घ __ecag(अचिन्हित पूर्णांक asi, अचिन्हित अक्षर parm)
अणु
	अचिन्हित दीर्घ val;

	यंत्र अस्थिर(".insn	rsy,0xeb000000004c,%0,0,0(%1)" /* ecag */
		     : "=d" (val) : "a" (asi << 8 | parm));
	वापस val;
पूर्ण

अटल अंतरभूत व्योम psw_set_key(अचिन्हित पूर्णांक key)
अणु
	यंत्र अस्थिर("spka 0(%0)" : : "d" (key));
पूर्ण

/*
 * Set PSW to specअगरied value.
 */
अटल अंतरभूत व्योम __load_psw(psw_t psw)
अणु
	यंत्र अस्थिर("lpswe %0" : : "Q" (psw) : "cc");
पूर्ण

/*
 * Set PSW mask to specअगरied value, जबतक leaving the
 * PSW addr poपूर्णांकing to the next inकाष्ठाion.
 */
अटल __no_kasan_or_अंतरभूत व्योम __load_psw_mask(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ addr;
	psw_t psw;

	psw.mask = mask;

	यंत्र अस्थिर(
		"	larl	%0,1f\n"
		"	stg	%0,%1\n"
		"	lpswe	%2\n"
		"1:"
		: "=&d" (addr), "=Q" (psw.addr) : "Q" (psw) : "memory", "cc");
पूर्ण

/*
 * Extract current PSW mask
 */
अटल अंतरभूत अचिन्हित दीर्घ __extract_psw(व्योम)
अणु
	अचिन्हित पूर्णांक reg1, reg2;

	यंत्र अस्थिर("epsw %0,%1" : "=d" (reg1), "=a" (reg2));
	वापस (((अचिन्हित दीर्घ) reg1) << 32) | ((अचिन्हित दीर्घ) reg2);
पूर्ण

अटल अंतरभूत व्योम local_mcck_enable(व्योम)
अणु
	__load_psw_mask(__extract_psw() | PSW_MASK_MCHECK);
पूर्ण

अटल अंतरभूत व्योम local_mcck_disable(व्योम)
अणु
	__load_psw_mask(__extract_psw() & ~PSW_MASK_MCHECK);
पूर्ण

/*
 * Rewind PSW inकाष्ठाion address by specअगरied number of bytes.
 */
अटल अंतरभूत अचिन्हित दीर्घ __शुरुआत_psw(psw_t psw, अचिन्हित दीर्घ ilc)
अणु
	अचिन्हित दीर्घ mask;

	mask = (psw.mask & PSW_MASK_EA) ? -1UL :
	       (psw.mask & PSW_MASK_BA) ? (1UL << 31) - 1 :
					  (1UL << 24) - 1;
	वापस (psw.addr - ilc) & mask;
पूर्ण

/*
 * Function to drop a processor पूर्णांकo disabled रुको state
 */
अटल __always_अंतरभूत व्योम __noवापस disabled_रुको(व्योम)
अणु
	psw_t psw;

	psw.mask = PSW_MASK_BASE | PSW_MASK_WAIT | PSW_MASK_BA | PSW_MASK_EA;
	psw.addr = _THIS_IP_;
	__load_psw(psw);
	जबतक (1);
पूर्ण

/*
 * Basic Program Check Handler.
 */
बाह्य व्योम s390_base_pgm_handler(व्योम);
बाह्य व्योम (*s390_base_pgm_handler_fn)(व्योम);

#घोषणा ARCH_LOW_ADDRESS_LIMIT	0x7fffffffUL

बाह्य पूर्णांक स_नकल_real(व्योम *, व्योम *, माप_प्रकार);
बाह्य व्योम स_नकल_असलolute(व्योम *, व्योम *, माप_प्रकार);

#घोषणा mem_assign_असलolute(dest, val) करो अणु			\
	__typeof__(dest) __पंचांगp = (val);				\
								\
	BUILD_BUG_ON(माप(__पंचांगp) != माप(val));		\
	स_नकल_असलolute(&(dest), &__पंचांगp, माप(__पंचांगp));	\
पूर्ण जबतक (0)

बाह्य पूर्णांक s390_isolate_bp(व्योम);
बाह्य पूर्णांक s390_isolate_bp_guest(व्योम);

अटल __always_अंतरभूत bool regs_irqs_disabled(काष्ठा pt_regs *regs)
अणु
	वापस arch_irqs_disabled_flags(regs->psw.mask);
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_S390_PROCESSOR_H */
