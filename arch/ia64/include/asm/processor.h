<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_IA64_PROCESSOR_H
#घोषणा _ASM_IA64_PROCESSOR_H

/*
 * Copyright (C) 1998-2004 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *	Stephane Eranian <eranian@hpl.hp.com>
 * Copyright (C) 1999 Asit Mallick <asit.k.mallick@पूर्णांकel.com>
 * Copyright (C) 1999 Don Dugger <करोn.dugger@पूर्णांकel.com>
 *
 * 11/24/98	S.Eranian	added ia64_set_iva()
 * 12/03/99	D. Mosberger	implement thपढ़ो_saved_pc() via kernel unwind API
 * 06/16/00	A. Mallick	added csd/ssd/tssd क्रम ia32 support
 */


#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/kregs.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/ustack.h>

#घोषणा IA64_NUM_PHYS_STACK_REG	96
#घोषणा IA64_NUM_DBG_REGS	8

#घोषणा DEFAULT_MAP_BASE	__IA64_UL_CONST(0x2000000000000000)
#घोषणा DEFAULT_TASK_SIZE	__IA64_UL_CONST(0xa000000000000000)

/*
 * TASK_SIZE really is a mis-named.  It really is the maximum user
 * space address (plus one).  On IA-64, there are five regions of 2TB
 * each (assuming 8KB page size), क्रम a total of 8TB of user भव
 * address space.
 */
#घोषणा TASK_SIZE       	DEFAULT_TASK_SIZE

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE	(current->thपढ़ो.map_base)

#घोषणा IA64_THREAD_FPH_VALID	(__IA64_UL(1) << 0)	/* भग्नing-poपूर्णांक high state valid? */
#घोषणा IA64_THREAD_DBG_VALID	(__IA64_UL(1) << 1)	/* debug रेजिस्टरs valid? */
#घोषणा IA64_THREAD_PM_VALID	(__IA64_UL(1) << 2)	/* perक्रमmance रेजिस्टरs valid? */
#घोषणा IA64_THREAD_UAC_NOPRINT	(__IA64_UL(1) << 3)	/* करोn't log unaligned accesses */
#घोषणा IA64_THREAD_UAC_SIGBUS	(__IA64_UL(1) << 4)	/* generate SIGBUS on unaligned acc. */
#घोषणा IA64_THREAD_MIGRATION	(__IA64_UL(1) << 5)	/* require migration
							   sync at ctx sw */
#घोषणा IA64_THREAD_FPEMU_NOPRINT (__IA64_UL(1) << 6)	/* करोn't log any fpswa faults */
#घोषणा IA64_THREAD_FPEMU_संक_भ_त्रुटि  (__IA64_UL(1) << 7)	/* send a संक_भ_त्रुटि क्रम fpswa faults */

#घोषणा IA64_THREAD_UAC_SHIFT	3
#घोषणा IA64_THREAD_UAC_MASK	(IA64_THREAD_UAC_NOPRINT | IA64_THREAD_UAC_SIGBUS)
#घोषणा IA64_THREAD_FPEMU_SHIFT	6
#घोषणा IA64_THREAD_FPEMU_MASK	(IA64_THREAD_FPEMU_NOPRINT | IA64_THREAD_FPEMU_संक_भ_त्रुटि)


/*
 * This shअगरt should be large enough to be able to represent 1000000000/itc_freq with good
 * accuracy जबतक being small enough to fit 10*1000000000<<IA64_NSEC_PER_CYC_SHIFT in 64 bits
 * (this will give enough slack to represent 10 seconds worth of समय as a scaled number).
 */
#घोषणा IA64_NSEC_PER_CYC_SHIFT	30

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/cache.h>
#समावेश <linux/compiler.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>

#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/rse.h>
#समावेश <यंत्र/unwind.h>
#समावेश <linux/atomic.h>
#अगर_घोषित CONFIG_NUMA
#समावेश <यंत्र/nodedata.h>
#पूर्ण_अगर

/* like above but expressed as bitfields क्रम more efficient access: */
काष्ठा ia64_psr अणु
	__u64 reserved0 : 1;
	__u64 be : 1;
	__u64 up : 1;
	__u64 ac : 1;
	__u64 mfl : 1;
	__u64 mfh : 1;
	__u64 reserved1 : 7;
	__u64 ic : 1;
	__u64 i : 1;
	__u64 pk : 1;
	__u64 reserved2 : 1;
	__u64 dt : 1;
	__u64 dfl : 1;
	__u64 dfh : 1;
	__u64 sp : 1;
	__u64 pp : 1;
	__u64 di : 1;
	__u64 si : 1;
	__u64 db : 1;
	__u64 lp : 1;
	__u64 tb : 1;
	__u64 rt : 1;
	__u64 reserved3 : 4;
	__u64 cpl : 2;
	__u64 is : 1;
	__u64 mc : 1;
	__u64 it : 1;
	__u64 id : 1;
	__u64 da : 1;
	__u64 dd : 1;
	__u64 ss : 1;
	__u64 ri : 2;
	__u64 ed : 1;
	__u64 bn : 1;
	__u64 reserved4 : 19;
पूर्ण;

जोड़ ia64_isr अणु
	__u64  val;
	काष्ठा अणु
		__u64 code : 16;
		__u64 vector : 8;
		__u64 reserved1 : 8;
		__u64 x : 1;
		__u64 w : 1;
		__u64 r : 1;
		__u64 na : 1;
		__u64 sp : 1;
		__u64 rs : 1;
		__u64 ir : 1;
		__u64 ni : 1;
		__u64 so : 1;
		__u64 ei : 2;
		__u64 ed : 1;
		__u64 reserved2 : 20;
	पूर्ण;
पूर्ण;

जोड़ ia64_lid अणु
	__u64 val;
	काष्ठा अणु
		__u64  rv  : 16;
		__u64  eid : 8;
		__u64  id  : 8;
		__u64  ig  : 32;
	पूर्ण;
पूर्ण;

जोड़ ia64_tpr अणु
	__u64 val;
	काष्ठा अणु
		__u64 ig0 : 4;
		__u64 mic : 4;
		__u64 rsv : 8;
		__u64 mmi : 1;
		__u64 ig1 : 47;
	पूर्ण;
पूर्ण;

जोड़ ia64_itir अणु
	__u64 val;
	काष्ठा अणु
		__u64 rv3  :  2; /* 0-1 */
		__u64 ps   :  6; /* 2-7 */
		__u64 key  : 24; /* 8-31 */
		__u64 rv4  : 32; /* 32-63 */
	पूर्ण;
पूर्ण;

जोड़  ia64_rr अणु
	__u64 val;
	काष्ठा अणु
		__u64  ve	:  1;  /* enable hw walker */
		__u64  reserved0:  1;  /* reserved */
		__u64  ps	:  6;  /* log page size */
		__u64  rid	: 24;  /* region id */
		__u64  reserved1: 32;  /* reserved */
	पूर्ण;
पूर्ण;

/*
 * CPU type, hardware bug flags, and per-CPU state.  Frequently used
 * state comes earlier:
 */
काष्ठा cpuinfo_ia64 अणु
	अचिन्हित पूर्णांक softirq_pending;
	अचिन्हित दीर्घ iपंचांग_delta;	/* # of घड़ी cycles between घड़ी ticks */
	अचिन्हित दीर्घ iपंचांग_next;		/* पूर्णांकerval समयr mask value to use क्रम next घड़ी tick */
	अचिन्हित दीर्घ nsec_per_cyc;	/* (1000000000<<IA64_NSEC_PER_CYC_SHIFT)/itc_freq */
	अचिन्हित दीर्घ unimpl_va_mask;	/* mask of unimplemented भव address bits (from PAL) */
	अचिन्हित दीर्घ unimpl_pa_mask;	/* mask of unimplemented physical address bits (from PAL) */
	अचिन्हित दीर्घ itc_freq;		/* frequency of ITC counter */
	अचिन्हित दीर्घ proc_freq;	/* frequency of processor */
	अचिन्हित दीर्घ cyc_per_usec;	/* itc_freq/1000000 */
	अचिन्हित दीर्घ ptce_base;
	अचिन्हित पूर्णांक ptce_count[2];
	अचिन्हित पूर्णांक ptce_stride[2];
	काष्ठा task_काष्ठा *ksoftirqd;	/* kernel softirq daemon क्रम this CPU */

#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ loops_per_jअगरfy;
	पूर्णांक cpu;
	अचिन्हित पूर्णांक socket_id;	/* physical processor socket id */
	अचिन्हित लघु core_id;	/* core id */
	अचिन्हित लघु thपढ़ो_id; /* thपढ़ो id */
	अचिन्हित लघु num_log;	/* Total number of logical processors on
				 * this socket that were successfully booted */
	अचिन्हित अक्षर cores_per_socket;	/* Cores per processor socket */
	अचिन्हित अक्षर thपढ़ोs_per_core;	/* Thपढ़ोs per core */
#पूर्ण_अगर

	/* CPUID-derived inक्रमmation: */
	अचिन्हित दीर्घ ppn;
	अचिन्हित दीर्घ features;
	अचिन्हित अक्षर number;
	अचिन्हित अक्षर revision;
	अचिन्हित अक्षर model;
	अचिन्हित अक्षर family;
	अचिन्हित अक्षर archrev;
	अक्षर venकरोr[16];
	अक्षर *model_name;

#अगर_घोषित CONFIG_NUMA
	काष्ठा ia64_node_data *node_data;
#पूर्ण_अगर
पूर्ण;

DECLARE_PER_CPU(काष्ठा cpuinfo_ia64, ia64_cpu_info);

/*
 * The "local" data variable.  It refers to the per-CPU data of the currently executing
 * CPU, much like "current" poपूर्णांकs to the per-task data of the currently executing task.
 * Do not use the address of local_cpu_data, since it will be dअगरferent from
 * cpu_data(smp_processor_id())!
 */
#घोषणा local_cpu_data		(&__ia64_per_cpu_var(ia64_cpu_info))
#घोषणा cpu_data(cpu)		(&per_cpu(ia64_cpu_info, cpu))

बाह्य व्योम prपूर्णांक_cpu_info (काष्ठा cpuinfo_ia64 *);

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

#घोषणा SET_UNALIGN_CTL(task,value)								\
(अणु												\
	(task)->thपढ़ो.flags = (((task)->thपढ़ो.flags & ~IA64_THREAD_UAC_MASK)			\
				| (((value) << IA64_THREAD_UAC_SHIFT) & IA64_THREAD_UAC_MASK));	\
	0;											\
पूर्ण)
#घोषणा GET_UNALIGN_CTL(task,addr)								\
(अणु												\
	put_user(((task)->thपढ़ो.flags & IA64_THREAD_UAC_MASK) >> IA64_THREAD_UAC_SHIFT,	\
		 (पूर्णांक __user *) (addr));							\
पूर्ण)

#घोषणा SET_FPEMU_CTL(task,value)								\
(अणु												\
	(task)->thपढ़ो.flags = (((task)->thपढ़ो.flags & ~IA64_THREAD_FPEMU_MASK)		\
			  | (((value) << IA64_THREAD_FPEMU_SHIFT) & IA64_THREAD_FPEMU_MASK));	\
	0;											\
पूर्ण)
#घोषणा GET_FPEMU_CTL(task,addr)								\
(अणु												\
	put_user(((task)->thपढ़ो.flags & IA64_THREAD_FPEMU_MASK) >> IA64_THREAD_FPEMU_SHIFT,	\
		 (पूर्णांक __user *) (addr));							\
पूर्ण)

काष्ठा thपढ़ो_काष्ठा अणु
	__u32 flags;			/* various thपढ़ो flags (see IA64_THREAD_*) */
	/* writing on_ustack is perक्रमmance-critical, so it's worth spending 8 bits on it... */
	__u8 on_ustack;			/* executing on user-stacks? */
	__u8 pad[3];
	__u64 ksp;			/* kernel stack poपूर्णांकer */
	__u64 map_base;			/* base address क्रम get_unmapped_area() */
	__u64 rbs_bot;			/* the base address क्रम the RBS */
	पूर्णांक last_fph_cpu;		/* CPU that may hold the contents of f32-f127 */
	अचिन्हित दीर्घ dbr[IA64_NUM_DBG_REGS];
	अचिन्हित दीर्घ ibr[IA64_NUM_DBG_REGS];
	काष्ठा ia64_fpreg fph[96];	/* saved/loaded on demand */
पूर्ण;

#घोषणा INIT_THREAD अणु						\
	.flags =	0,					\
	.on_ustack =	0,					\
	.ksp =		0,					\
	.map_base =	DEFAULT_MAP_BASE,			\
	.rbs_bot =	STACK_TOP - DEFAULT_USER_STACK_SIZE,	\
	.last_fph_cpu =  -1,					\
	.dbr =		अणु0, पूर्ण,					\
	.ibr =		अणु0, पूर्ण,					\
	.fph =		अणुअणुअणुअणु0पूर्णपूर्णपूर्ण, पूर्ण				\
पूर्ण

#घोषणा start_thपढ़ो(regs,new_ip,new_sp) करो अणु							\
	regs->cr_ipsr = ((regs->cr_ipsr | (IA64_PSR_BITS_TO_SET | IA64_PSR_CPL))		\
			 & ~(IA64_PSR_BITS_TO_CLEAR | IA64_PSR_RI | IA64_PSR_IS));		\
	regs->cr_iip = new_ip;									\
	regs->ar_rsc = 0xf;		/* eager mode, privilege level 3 */			\
	regs->ar_rnat = 0;									\
	regs->ar_bspstore = current->thपढ़ो.rbs_bot;						\
	regs->ar_fpsr = FPSR_DEFAULT;								\
	regs->loadrs = 0;									\
	regs->r8 = get_dumpable(current->mm);	/* set "don't zap registers" flag */		\
	regs->r12 = new_sp - 16;	/* allocate 16 byte scratch area */			\
	अगर (unlikely(get_dumpable(current->mm) != SUID_DUMP_USER)) अणु	\
		/*										\
		 * Zap scratch regs to aव्योम leaking bits between processes with dअगरferent	\
		 * uid/privileges.								\
		 */										\
		regs->ar_pfs = 0; regs->b0 = 0; regs->pr = 0;					\
		regs->r1 = 0; regs->r9  = 0; regs->r11 = 0; regs->r13 = 0; regs->r15 = 0;	\
	पूर्ण											\
पूर्ण जबतक (0)

/* Forward declarations, a strange C thing... */
काष्ठा mm_काष्ठा;
काष्ठा task_काष्ठा;

/*
 * Free all resources held by a thपढ़ो. This is called after the
 * parent of DEAD_TASK has collected the निकास status of the task via
 * रुको().
 */
#घोषणा release_thपढ़ो(dead_task)

/* Get रुको channel क्रम task P.  */
बाह्य अचिन्हित दीर्घ get_wchan (काष्ठा task_काष्ठा *p);

/* Return inकाष्ठाion poपूर्णांकer of blocked task TSK.  */
#घोषणा KSTK_EIP(tsk)					\
  (अणु							\
	काष्ठा pt_regs *_regs = task_pt_regs(tsk);	\
	_regs->cr_iip + ia64_psr(_regs)->ri;		\
  पूर्ण)

/* Return stack poपूर्णांकer of blocked task TSK.  */
#घोषणा KSTK_ESP(tsk)  ((tsk)->thपढ़ो.ksp)

बाह्य व्योम ia64_getreg_unknown_kr (व्योम);
बाह्य व्योम ia64_setreg_unknown_kr (व्योम);

#घोषणा ia64_get_kr(regnum)					\
(अणु								\
	अचिन्हित दीर्घ r = 0;					\
								\
	चयन (regnum) अणु					\
	    हाल 0: r = ia64_getreg(_IA64_REG_AR_KR0); अवरोध;	\
	    हाल 1: r = ia64_getreg(_IA64_REG_AR_KR1); अवरोध;	\
	    हाल 2: r = ia64_getreg(_IA64_REG_AR_KR2); अवरोध;	\
	    हाल 3: r = ia64_getreg(_IA64_REG_AR_KR3); अवरोध;	\
	    हाल 4: r = ia64_getreg(_IA64_REG_AR_KR4); अवरोध;	\
	    हाल 5: r = ia64_getreg(_IA64_REG_AR_KR5); अवरोध;	\
	    हाल 6: r = ia64_getreg(_IA64_REG_AR_KR6); अवरोध;	\
	    हाल 7: r = ia64_getreg(_IA64_REG_AR_KR7); अवरोध;	\
	    शेष: ia64_getreg_unknown_kr(); अवरोध;		\
	पूर्ण							\
	r;							\
पूर्ण)

#घोषणा ia64_set_kr(regnum, r) 					\
(अणु								\
	चयन (regnum) अणु					\
	    हाल 0: ia64_setreg(_IA64_REG_AR_KR0, r); अवरोध;	\
	    हाल 1: ia64_setreg(_IA64_REG_AR_KR1, r); अवरोध;	\
	    हाल 2: ia64_setreg(_IA64_REG_AR_KR2, r); अवरोध;	\
	    हाल 3: ia64_setreg(_IA64_REG_AR_KR3, r); अवरोध;	\
	    हाल 4: ia64_setreg(_IA64_REG_AR_KR4, r); अवरोध;	\
	    हाल 5: ia64_setreg(_IA64_REG_AR_KR5, r); अवरोध;	\
	    हाल 6: ia64_setreg(_IA64_REG_AR_KR6, r); अवरोध;	\
	    हाल 7: ia64_setreg(_IA64_REG_AR_KR7, r); अवरोध;	\
	    शेष: ia64_setreg_unknown_kr(); अवरोध;		\
	पूर्ण							\
पूर्ण)

/*
 * The following three macros can't be inline functions because we don't have काष्ठा
 * task_काष्ठा at this poपूर्णांक.
 */

/*
 * Return TRUE अगर task T owns the fph partition of the CPU we're running on.
 * Must be called from code that has preemption disabled.
 */
#घोषणा ia64_is_local_fpu_owner(t)								\
(अणु												\
	काष्ठा task_काष्ठा *__ia64_islfo_task = (t);						\
	(__ia64_islfo_task->thपढ़ो.last_fph_cpu == smp_processor_id()				\
	 && __ia64_islfo_task == (काष्ठा task_काष्ठा *) ia64_get_kr(IA64_KR_FPU_OWNER));	\
पूर्ण)

/*
 * Mark task T as owning the fph partition of the CPU we're running on.
 * Must be called from code that has preemption disabled.
 */
#घोषणा ia64_set_local_fpu_owner(t) करो अणु						\
	काष्ठा task_काष्ठा *__ia64_slfo_task = (t);					\
	__ia64_slfo_task->thपढ़ो.last_fph_cpu = smp_processor_id();			\
	ia64_set_kr(IA64_KR_FPU_OWNER, (अचिन्हित दीर्घ) __ia64_slfo_task);		\
पूर्ण जबतक (0)

/* Mark the fph partition of task T as being invalid on all CPUs.  */
#घोषणा ia64_drop_fpu(t)	((t)->thपढ़ो.last_fph_cpu = -1)

बाह्य व्योम __ia64_init_fpu (व्योम);
बाह्य व्योम __ia64_save_fpu (काष्ठा ia64_fpreg *fph);
बाह्य व्योम __ia64_load_fpu (काष्ठा ia64_fpreg *fph);
बाह्य व्योम ia64_save_debug_regs (अचिन्हित दीर्घ *save_area);
बाह्य व्योम ia64_load_debug_regs (अचिन्हित दीर्घ *save_area);

#घोषणा ia64_fph_enable()	करो अणु ia64_rsm(IA64_PSR_DFH); ia64_srlz_d(); पूर्ण जबतक (0)
#घोषणा ia64_fph_disable()	करो अणु ia64_ssm(IA64_PSR_DFH); ia64_srlz_d(); पूर्ण जबतक (0)

/* load fp 0.0 पूर्णांकo fph */
अटल अंतरभूत व्योम
ia64_init_fpu (व्योम) अणु
	ia64_fph_enable();
	__ia64_init_fpu();
	ia64_fph_disable();
पूर्ण

/* save f32-f127 at FPH */
अटल अंतरभूत व्योम
ia64_save_fpu (काष्ठा ia64_fpreg *fph) अणु
	ia64_fph_enable();
	__ia64_save_fpu(fph);
	ia64_fph_disable();
पूर्ण

/* load f32-f127 from FPH */
अटल अंतरभूत व्योम
ia64_load_fpu (काष्ठा ia64_fpreg *fph) अणु
	ia64_fph_enable();
	__ia64_load_fpu(fph);
	ia64_fph_disable();
पूर्ण

अटल अंतरभूत __u64
ia64_clear_ic (व्योम)
अणु
	__u64 psr;
	psr = ia64_getreg(_IA64_REG_PSR);
	ia64_stop();
	ia64_rsm(IA64_PSR_I | IA64_PSR_IC);
	ia64_srlz_i();
	वापस psr;
पूर्ण

/*
 * Restore the psr.
 */
अटल अंतरभूत व्योम
ia64_set_psr (__u64 psr)
अणु
	ia64_stop();
	ia64_setreg(_IA64_REG_PSR_L, psr);
	ia64_srlz_i();
पूर्ण

/*
 * Insert a translation पूर्णांकo an inकाष्ठाion and/or data translation
 * रेजिस्टर.
 */
अटल अंतरभूत व्योम
ia64_itr (__u64 target_mask, __u64 tr_num,
	  __u64 vmaddr, __u64 pte,
	  __u64 log_page_size)
अणु
	ia64_setreg(_IA64_REG_CR_ITIR, (log_page_size << 2));
	ia64_setreg(_IA64_REG_CR_IFA, vmaddr);
	ia64_stop();
	अगर (target_mask & 0x1)
		ia64_itri(tr_num, pte);
	अगर (target_mask & 0x2)
		ia64_itrd(tr_num, pte);
पूर्ण

/*
 * Insert a translation पूर्णांकo the inकाष्ठाion and/or data translation
 * cache.
 */
अटल अंतरभूत व्योम
ia64_itc (__u64 target_mask, __u64 vmaddr, __u64 pte,
	  __u64 log_page_size)
अणु
	ia64_setreg(_IA64_REG_CR_ITIR, (log_page_size << 2));
	ia64_setreg(_IA64_REG_CR_IFA, vmaddr);
	ia64_stop();
	/* as per EAS2.6, itc must be the last inकाष्ठाion in an inकाष्ठाion group */
	अगर (target_mask & 0x1)
		ia64_itci(pte);
	अगर (target_mask & 0x2)
		ia64_itcd(pte);
पूर्ण

/*
 * Purge a range of addresses from inकाष्ठाion and/or data translation
 * रेजिस्टर(s).
 */
अटल अंतरभूत व्योम
ia64_ptr (__u64 target_mask, __u64 vmaddr, __u64 log_size)
अणु
	अगर (target_mask & 0x1)
		ia64_ptri(vmaddr, (log_size << 2));
	अगर (target_mask & 0x2)
		ia64_ptrd(vmaddr, (log_size << 2));
पूर्ण

/* Set the पूर्णांकerrupt vector address.  The address must be suitably aligned (32KB).  */
अटल अंतरभूत व्योम
ia64_set_iva (व्योम *ivt_addr)
अणु
	ia64_setreg(_IA64_REG_CR_IVA, (__u64) ivt_addr);
	ia64_srlz_i();
पूर्ण

/* Set the page table address and control bits.  */
अटल अंतरभूत व्योम
ia64_set_pta (__u64 pta)
अणु
	/* Note: srlz.i implies srlz.d */
	ia64_setreg(_IA64_REG_CR_PTA, pta);
	ia64_srlz_i();
पूर्ण

अटल अंतरभूत व्योम
ia64_eoi (व्योम)
अणु
	ia64_setreg(_IA64_REG_CR_EOI, 0);
	ia64_srlz_d();
पूर्ण

#घोषणा cpu_relax()	ia64_hपूर्णांक(ia64_hपूर्णांक_छोड़ो)

अटल अंतरभूत पूर्णांक
ia64_get_irr(अचिन्हित पूर्णांक vector)
अणु
	अचिन्हित पूर्णांक reg = vector / 64;
	अचिन्हित पूर्णांक bit = vector % 64;
	u64 irr;

	चयन (reg) अणु
	हाल 0: irr = ia64_getreg(_IA64_REG_CR_IRR0); अवरोध;
	हाल 1: irr = ia64_getreg(_IA64_REG_CR_IRR1); अवरोध;
	हाल 2: irr = ia64_getreg(_IA64_REG_CR_IRR2); अवरोध;
	हाल 3: irr = ia64_getreg(_IA64_REG_CR_IRR3); अवरोध;
	पूर्ण

	वापस test_bit(bit, &irr);
पूर्ण

अटल अंतरभूत व्योम
ia64_set_lrr0 (अचिन्हित दीर्घ val)
अणु
	ia64_setreg(_IA64_REG_CR_LRR0, val);
	ia64_srlz_d();
पूर्ण

अटल अंतरभूत व्योम
ia64_set_lrr1 (अचिन्हित दीर्घ val)
अणु
	ia64_setreg(_IA64_REG_CR_LRR1, val);
	ia64_srlz_d();
पूर्ण


/*
 * Given the address to which a spill occurred, वापस the unat bit
 * number that corresponds to this address.
 */
अटल अंतरभूत __u64
ia64_unat_pos (व्योम *spill_addr)
अणु
	वापस ((__u64) spill_addr >> 3) & 0x3f;
पूर्ण

/*
 * Set the NaT bit of an पूर्णांकeger रेजिस्टर which was spilled at address
 * SPILL_ADDR.  UNAT is the mask to be updated.
 */
अटल अंतरभूत व्योम
ia64_set_unat (__u64 *unat, व्योम *spill_addr, अचिन्हित दीर्घ nat)
अणु
	__u64 bit = ia64_unat_pos(spill_addr);
	__u64 mask = 1UL << bit;

	*unat = (*unat & ~mask) | (nat << bit);
पूर्ण

अटल अंतरभूत __u64
ia64_get_ivr (व्योम)
अणु
	__u64 r;
	ia64_srlz_d();
	r = ia64_getreg(_IA64_REG_CR_IVR);
	ia64_srlz_d();
	वापस r;
पूर्ण

अटल अंतरभूत व्योम
ia64_set_dbr (__u64 regnum, __u64 value)
अणु
	__ia64_set_dbr(regnum, value);
#अगर_घोषित CONFIG_ITANIUM
	ia64_srlz_d();
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत __u64
ia64_get_dbr (__u64 regnum)
अणु
	__u64 retval;

	retval = __ia64_get_dbr(regnum);
#अगर_घोषित CONFIG_ITANIUM
	ia64_srlz_d();
#पूर्ण_अगर
	वापस retval;
पूर्ण

अटल अंतरभूत __u64
ia64_rotr (__u64 w, __u64 n)
अणु
	वापस (w >> n) | (w << (64 - n));
पूर्ण

#घोषणा ia64_rotl(w,n)	ia64_rotr((w), (64) - (n))

/*
 * Take a mapped kernel address and वापस the equivalent address
 * in the region 7 identity mapped भव area.
 */
अटल अंतरभूत व्योम *
ia64_imva (व्योम *addr)
अणु
	व्योम *result;
	result = (व्योम *) ia64_tpa(addr);
	वापस __va(result);
पूर्ण

#घोषणा ARCH_HAS_PREFETCH
#घोषणा ARCH_HAS_PREFETCHW
#घोषणा ARCH_HAS_SPINLOCK_PREFETCH
#घोषणा PREFETCH_STRIDE			L1_CACHE_BYTES

अटल अंतरभूत व्योम
prefetch (स्थिर व्योम *x)
अणु
	 ia64_lfetch(ia64_lfhपूर्णांक_none, x);
पूर्ण

अटल अंतरभूत व्योम
prefetchw (स्थिर व्योम *x)
अणु
	ia64_lfetch_excl(ia64_lfhपूर्णांक_none, x);
पूर्ण

#घोषणा spin_lock_prefetch(x)	prefetchw(x)

बाह्य अचिन्हित दीर्घ boot_option_idle_override;

क्रमागत idle_boot_override अणुIDLE_NO_OVERRIDE=0, IDLE_HALT, IDLE_FORCE_MWAIT,
			 IDLE_NOMWAIT, IDLE_POLLपूर्ण;

व्योम शेष_idle(व्योम);

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_IA64_PROCESSOR_H */
