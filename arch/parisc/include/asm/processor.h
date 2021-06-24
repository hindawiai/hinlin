<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/यंत्र-parisc/processor.h
 *
 * Copyright (C) 1994 Linus Torvalds
 * Copyright (C) 2001 Grant Grundler
 */

#अगर_अघोषित __ASM_PARISC_PROCESSOR_H
#घोषणा __ASM_PARISC_PROCESSOR_H

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/prefetch.h>
#समावेश <यंत्र/hardware.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/percpu.h>
#पूर्ण_अगर /* __ASSEMBLY__ */

#घोषणा HAVE_ARCH_PICK_MMAP_LAYOUT

#घोषणा TASK_SIZE_OF(tsk)       ((tsk)->thपढ़ो.task_size)
#घोषणा TASK_SIZE	        TASK_SIZE_OF(current)
#घोषणा TASK_UNMAPPED_BASE      (current->thपढ़ो.map_base)

#घोषणा DEFAULT_TASK_SIZE32	(0xFFF00000UL)
#घोषणा DEFAULT_MAP_BASE32	(0x40000000UL)

#अगर_घोषित CONFIG_64BIT
#घोषणा DEFAULT_TASK_SIZE       (MAX_ADDRESS-0xf000000)
#घोषणा DEFAULT_MAP_BASE        (0x200000000UL)
#अन्यथा
#घोषणा DEFAULT_TASK_SIZE	DEFAULT_TASK_SIZE32
#घोषणा DEFAULT_MAP_BASE	DEFAULT_MAP_BASE32
#पूर्ण_अगर

#अगर_घोषित __KERNEL__

/* XXX: STACK_TOP actually should be STACK_BOTTOM क्रम parisc.
 * prumpf */

#घोषणा STACK_TOP	TASK_SIZE
#घोषणा STACK_TOP_MAX	DEFAULT_TASK_SIZE

#पूर्ण_अगर

#अगर_अघोषित __ASSEMBLY__

अचिन्हित दीर्घ calc_max_stack_size(अचिन्हित दीर्घ stack_max);

/*
 * Data detected about CPUs at boot समय which is the same क्रम all CPU's.
 * HP boxes are SMP - ie identical processors.
 *
 * FIXME: some CPU rev info may be processor specअगरic...
 */
काष्ठा प्रणाली_cpuinfo_parisc अणु
	अचिन्हित पूर्णांक	cpu_count;
	अचिन्हित पूर्णांक	cpu_hz;
	अचिन्हित पूर्णांक	hversion;
	अचिन्हित पूर्णांक	sversion;
	क्रमागत cpu_type	cpu_type;

	काष्ठा अणु
		काष्ठा pdc_model model;
		अचिन्हित दीर्घ versions;
		अचिन्हित दीर्घ cpuid;
		अचिन्हित दीर्घ capabilities;
		अक्षर   sys_model_name[81]; /* PDC-ROM वापसes this model name */
	पूर्ण pdc;

	स्थिर अक्षर	*cpu_name;	/* e.g. "PA7300LC (PCX-L2)" */
	स्थिर अक्षर	*family_name;	/* e.g. "1.1e" */
पूर्ण;


/* Per CPU data काष्ठाure - ie varies per CPU.  */
काष्ठा cpuinfo_parisc अणु
	अचिन्हित दीर्घ it_value;     /* Interval Timer at last समयr Intr */
	अचिन्हित दीर्घ irq_count;    /* number of IRQ's since boot */
	अचिन्हित दीर्घ cpuid;        /* aka slot_number or set to NO_PROC_ID */
	अचिन्हित दीर्घ hpa;          /* Host Physical address */
	अचिन्हित दीर्घ txn_addr;     /* MMIO addr of EIR or id_eid */
#अगर_घोषित CONFIG_SMP
	अचिन्हित दीर्घ pending_ipi;  /* biपंचांगap of type ipi_message_type */
#पूर्ण_अगर
	अचिन्हित दीर्घ bh_count;     /* number of बार bh was invoked */
	अचिन्हित दीर्घ fp_rev;
	अचिन्हित दीर्घ fp_model;
	अचिन्हित दीर्घ cpu_num;      /* CPU number from PAT firmware */
	अचिन्हित दीर्घ cpu_loc;      /* CPU location from PAT firmware */
	अचिन्हित पूर्णांक state;
	काष्ठा parisc_device *dev;
पूर्ण;

बाह्य काष्ठा प्रणाली_cpuinfo_parisc boot_cpu_data;
DECLARE_PER_CPU(काष्ठा cpuinfo_parisc, cpu_data);

#घोषणा CPU_HVERSION ((boot_cpu_data.hversion >> 4) & 0x0FFF)

प्रकार काष्ठा अणु
	पूर्णांक seg;  
पूर्ण mm_segment_t;

#घोषणा ARCH_MIN_TASKALIGN	8

काष्ठा thपढ़ो_काष्ठा अणु
	काष्ठा pt_regs regs;
	अचिन्हित दीर्घ  task_size;
	अचिन्हित दीर्घ  map_base;
	अचिन्हित दीर्घ  flags;
पूर्ण; 

#घोषणा task_pt_regs(tsk) ((काष्ठा pt_regs *)&((tsk)->thपढ़ो.regs))

/* Thपढ़ो काष्ठा flags. */
#घोषणा PARISC_UAC_NOPRINT	(1UL << 0)	/* see prctl and unaligned.c */
#घोषणा PARISC_UAC_SIGBUS	(1UL << 1)
#घोषणा PARISC_KERNEL_DEATH	(1UL << 31)	/* see die_अगर_kernel()... */

#घोषणा PARISC_UAC_SHIFT	0
#घोषणा PARISC_UAC_MASK		(PARISC_UAC_NOPRINT|PARISC_UAC_SIGBUS)

#घोषणा SET_UNALIGN_CTL(task,value)                                       \
        (अणु                                                                \
        (task)->thपढ़ो.flags = (((task)->thपढ़ो.flags & ~PARISC_UAC_MASK) \
                                | (((value) << PARISC_UAC_SHIFT) &        \
                                   PARISC_UAC_MASK));                     \
        0;                                                                \
        पूर्ण)

#घोषणा GET_UNALIGN_CTL(task,addr)                                        \
        (अणु                                                                \
        put_user(((task)->thपढ़ो.flags & PARISC_UAC_MASK)                 \
                 >> PARISC_UAC_SHIFT, (पूर्णांक __user *) (addr));             \
        पूर्ण)

#घोषणा INIT_THREAD अणु \
	.regs = अणु	.gr	= अणु 0, पूर्ण, \
			.fr	= अणु 0, पूर्ण, \
			.sr	= अणु 0, पूर्ण, \
			.iasq	= अणु 0, पूर्ण, \
			.iaoq	= अणु 0, पूर्ण, \
			.cr27	= 0, \
		पूर्ण, \
	.task_size	= DEFAULT_TASK_SIZE, \
	.map_base	= DEFAULT_MAP_BASE, \
	.flags		= 0 \
	पूर्ण

काष्ठा task_काष्ठा;
व्योम show_trace(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *stack);

/*
 * Start user thपढ़ो in another space.
 *
 * Note that we set both the iaoq and r31 to the new pc. When
 * the kernel initially calls execve it will वापस through an
 * rfi path that will use the values in the iaoq. The execve
 * syscall path will वापस through the gateway page, and
 * that uses r31 to branch to.
 *
 * For ELF we clear r23, because the dynamic linker uses it to pass
 * the address of the finalizer function.
 *
 * We also initialize sr3 to an illegal value (illegal क्रम our
 * implementation, not क्रम the architecture).
 */
प्रकार अचिन्हित पूर्णांक elf_caddr_t;

/* The ELF abi wants things करोne a "wee bit" dअगरferently than
 * som करोes.  Supporting this behavior here aव्योमs
 * having our own version of create_elf_tables.
 *
 * Oh, and yes, that is not a typo, we are really passing argc in r25
 * and argv in r24 (rather than r26 and r25).  This is because that's
 * where __libc_start_मुख्य wants them.
 *
 * Duplicated from dl-machine.h क्रम the benefit of पढ़ोers:
 *
 *  Our initial stack layout is rather dअगरferent from everyone अन्यथा's
 *  due to the unique PA-RISC ABI.  As far as I know it looks like
 *  this:

   -----------------------------------  (user startup code creates this frame)
   |         32 bytes of magic       |
   |---------------------------------|
   | 32 bytes argument/sp save area  |
   |---------------------------------| (bprm->p)
   |	    ELF auxiliary info	     |
   |         (up to 28 words)        |
   |---------------------------------|
   |		   शून्य		     |
   |---------------------------------|
   |	   Environment poपूर्णांकers	     |
   |---------------------------------|
   |		   शून्य		     |
   |---------------------------------|
   |        Argument poपूर्णांकers        |
   |---------------------------------| <- argv
   |          argc (1 word)          |
   |---------------------------------| <- bprm->exec (HACK!)
   |         N bytes of slack        |
   |---------------------------------|
   |	filename passed to execve    |
   |---------------------------------| (mm->env_end)
   |           env strings           |
   |---------------------------------| (mm->env_start, mm->arg_end)
   |           arg strings           |
   |---------------------------------|
   | additional faked arg strings अगर |
   | we're invoked via binfmt_script |
   |---------------------------------| (mm->arg_start)
   stack base is at TASK_SIZE - rlim_max.

on करोwnward growing arches, it looks like this:
   stack base at TASK_SIZE
   | filename passed to execve
   | env strings
   | arg strings
   | faked arg strings
   | slack
   | ELF
   | envps
   | argvs
   | argc

 *  The pleasant part of this is that अगर we need to skip arguments we
 *  can just decrement argc and move argv, because the stack poपूर्णांकer
 *  is utterly unrelated to the location of the environment and
 *  argument vectors.
 *
 * Note that the S/390 people took the easy way out and hacked their
 * GCC to make the stack grow करोwnwards.
 *
 * Final Note: For entry from syscall, the W (wide) bit of the PSW
 * is stuffed पूर्णांकo the lowest bit of the user sp (%r30), so we fill
 * it in here from the current->personality
 */

#घोषणा USER_WIDE_MODE	(!is_32bit_task())

#घोषणा start_thपढ़ो(regs, new_pc, new_sp) करो अणु		\
	elf_addr_t *sp = (elf_addr_t *)new_sp;		\
	__u32 spaceid = (__u32)current->mm->context;	\
	elf_addr_t pc = (elf_addr_t)new_pc | 3;		\
	elf_caddr_t *argv = (elf_caddr_t *)bprm->exec + 1;	\
							\
	regs->iasq[0] = spaceid;			\
	regs->iasq[1] = spaceid;			\
	regs->iaoq[0] = pc;				\
	regs->iaoq[1] = pc + 4;                         \
	regs->sr[2] = LINUX_GATEWAY_SPACE;              \
	regs->sr[3] = 0xffff;				\
	regs->sr[4] = spaceid;				\
	regs->sr[5] = spaceid;				\
	regs->sr[6] = spaceid;				\
	regs->sr[7] = spaceid;				\
	regs->gr[ 0] = USER_PSW | (USER_WIDE_MODE ? PSW_W : 0); \
	regs->fr[ 0] = 0LL;                            	\
	regs->fr[ 1] = 0LL;                            	\
	regs->fr[ 2] = 0LL;                            	\
	regs->fr[ 3] = 0LL;                            	\
	regs->gr[30] = (((अचिन्हित दीर्घ)sp + 63) &~ 63) | (USER_WIDE_MODE ? 1 : 0); \
	regs->gr[31] = pc;				\
							\
	get_user(regs->gr[25], (argv - 1));		\
	regs->gr[24] = (दीर्घ) argv;			\
	regs->gr[23] = 0;				\
पूर्ण जबतक(0)

काष्ठा mm_काष्ठा;

/* Free all resources held by a thपढ़ो. */
बाह्य व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);

बाह्य अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा KSTK_EIP(tsk)	((tsk)->thपढ़ो.regs.iaoq[0])
#घोषणा KSTK_ESP(tsk)	((tsk)->thपढ़ो.regs.gr[30])

#घोषणा cpu_relax()	barrier()

/*
 * parisc_requires_coherency() is used to identअगरy the combined VIPT/PIPT
 * cached CPUs which require a guarantee of coherency (no inequivalent aliases
 * with dअगरferent data, whether clean or not) to operate
 */
#अगर_घोषित CONFIG_PA8X00
बाह्य पूर्णांक _parisc_requires_coherency;
#घोषणा parisc_requires_coherency()	_parisc_requires_coherency
#अन्यथा
#घोषणा parisc_requires_coherency()	(0)
#पूर्ण_अगर

बाह्य पूर्णांक running_on_qemu;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_PARISC_PROCESSOR_H */
