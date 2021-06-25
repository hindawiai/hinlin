<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2008 Tensilica Inc.
 * Copyright (C) 2015 Cadence Design Systems Inc.
 */

#अगर_अघोषित _XTENSA_PROCESSOR_H
#घोषणा _XTENSA_PROCESSOR_H

#समावेश <यंत्र/core.h>

#समावेश <linux/compiler.h>
#समावेश <linux/stringअगरy.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/regs.h>

/* Assertions. */

#अगर (XCHAL_HAVE_WINDOWED != 1)
# error Linux requires the Xtensa Winकरोwed Registers Option.
#पूर्ण_अगर

/* Xtensa ABI requires stack alignment to be at least 16 */

#घोषणा STACK_ALIGN (XCHAL_DATA_WIDTH > 16 ? XCHAL_DATA_WIDTH : 16)

#घोषणा ARCH_SLAB_MINALIGN STACK_ALIGN

/*
 * User space process size: 1 GB.
 * Winकरोwed call ABI requires caller and callee to be located within the same
 * 1 GB region. The C compiler places trampoline code on the stack क्रम sources
 * that take the address of a nested C function (a feature used by glibc), so
 * the 1 GB requirement applies to the stack as well.
 */

#अगर_घोषित CONFIG_MMU
#घोषणा TASK_SIZE	__XTENSA_UL_CONST(0x40000000)
#अन्यथा
#घोषणा TASK_SIZE	__XTENSA_UL_CONST(0xffffffff)
#पूर्ण_अगर

#घोषणा STACK_TOP	TASK_SIZE
#घोषणा STACK_TOP_MAX	STACK_TOP

/*
 * General exception cause asचिन्हित to fake NMI. Fake NMI needs to be handled
 * dअगरferently from other पूर्णांकerrupts, but it uses common kernel entry/निकास
 * code.
 */

#घोषणा EXCCAUSE_MAPPED_NMI	62

/*
 * General exception cause asचिन्हित to debug exceptions. Debug exceptions go
 * to their own vector, rather than the general exception vectors (user,
 * kernel, द्विगुन); and their specअगरic causes are reported via DEBUGCAUSE
 * rather than EXCCAUSE.  However it is someबार convenient to redirect debug
 * exceptions to the general exception mechanism.  To करो this, an otherwise
 * unused EXCCAUSE value was asचिन्हित to debug exceptions क्रम this purpose.
 */

#घोषणा EXCCAUSE_MAPPED_DEBUG	63

/*
 * We use DEPC also as a flag to distinguish between द्विगुन and regular
 * exceptions. For perक्रमmance reasons, DEPC might contain the value of
 * EXCCAUSE क्रम regular exceptions, so we use this definition to mark a
 * valid द्विगुन exception address.
 * (Note: We use it in bgeui, so it should be 64, 128, or 256)
 */

#घोषणा VALID_DOUBLE_EXCEPTION_ADDRESS	64

#घोषणा XTENSA_INT_LEVEL(पूर्णांकno) _XTENSA_INT_LEVEL(पूर्णांकno)
#घोषणा _XTENSA_INT_LEVEL(पूर्णांकno) XCHAL_INT##पूर्णांकno##_LEVEL

#घोषणा XTENSA_INTLEVEL_MASK(level) _XTENSA_INTLEVEL_MASK(level)
#घोषणा _XTENSA_INTLEVEL_MASK(level) (XCHAL_INTLEVEL##level##_MASK)

#घोषणा XTENSA_INTLEVEL_ANDBELOW_MASK(l) _XTENSA_INTLEVEL_ANDBELOW_MASK(l)
#घोषणा _XTENSA_INTLEVEL_ANDBELOW_MASK(l) (XCHAL_INTLEVEL##l##_ANDBELOW_MASK)

#घोषणा PROFILING_INTLEVEL XTENSA_INT_LEVEL(XCHAL_PROFILING_INTERRUPT)

/* LOCKLEVEL defines the पूर्णांकerrupt level that masks all
 * general-purpose पूर्णांकerrupts.
 */
#अगर defined(CONFIG_XTENSA_FAKE_NMI) && defined(XCHAL_PROFILING_INTERRUPT)
#घोषणा LOCKLEVEL (PROFILING_INTLEVEL - 1)
#अन्यथा
#घोषणा LOCKLEVEL XCHAL_EXCM_LEVEL
#पूर्ण_अगर

#घोषणा TOPLEVEL XCHAL_EXCM_LEVEL
#घोषणा XTENSA_FAKE_NMI (LOCKLEVEL < TOPLEVEL)

/* WSBITS and WBBITS are the width of the WINDOWSTART and WINDOWBASE
 * रेजिस्टरs
 */
#घोषणा WSBITS  (XCHAL_NUM_AREGS / 4)      /* width of WINDOWSTART in bits */
#घोषणा WBBITS  (XCHAL_NUM_AREGS_LOG2 - 2) /* width of WINDOWBASE in bits */

#अगर_अघोषित __ASSEMBLY__

/* Build a valid वापस address क्रम the specअगरied call winsize.
 * winsize must be 1 (call4), 2 (call8), or 3 (call12)
 */
#घोषणा MAKE_RA_FOR_CALL(ra,ws)   (((ra) & 0x3fffffff) | (ws) << 30)

/* Convert वापस address to a valid pc
 * Note: We assume that the stack poपूर्णांकer is in the same 1GB ranges as the ra
 */
#घोषणा MAKE_PC_FROM_RA(ra,sp)    (((ra) & 0x3fffffff) | ((sp) & 0xc0000000))

/* Spill slot location क्रम the रेजिस्टर reg in the spill area under the stack
 * poपूर्णांकer sp. reg must be in the range [0..4).
 */
#घोषणा SPILL_SLOT(sp, reg) (*(((अचिन्हित दीर्घ *)(sp)) - 4 + (reg)))

/* Spill slot location क्रम the रेजिस्टर reg in the spill area under the stack
 * poपूर्णांकer sp क्रम the call8. reg must be in the range [4..8).
 */
#घोषणा SPILL_SLOT_CALL8(sp, reg) (*(((अचिन्हित दीर्घ *)(sp)) - 12 + (reg)))

/* Spill slot location क्रम the रेजिस्टर reg in the spill area under the stack
 * poपूर्णांकer sp क्रम the call12. reg must be in the range [4..12).
 */
#घोषणा SPILL_SLOT_CALL12(sp, reg) (*(((अचिन्हित दीर्घ *)(sp)) - 16 + (reg)))

प्रकार काष्ठा अणु
	अचिन्हित दीर्घ seg;
पूर्ण mm_segment_t;

काष्ठा thपढ़ो_काष्ठा अणु

	/* kernel's वापस address and stack poपूर्णांकer क्रम context चयनing */
	अचिन्हित दीर्घ ra; /* kernel's a0: वापस address and winकरोw call size */
	अचिन्हित दीर्घ sp; /* kernel's a1: stack poपूर्णांकer */

	mm_segment_t current_ds;    /* see uaccess.h क्रम example uses */

	/* काष्ठा xtensa_cpuinfo info; */

	अचिन्हित दीर्घ bad_vaddr; /* last user fault */
	अचिन्हित दीर्घ bad_uaddr; /* last kernel fault accessing user space */
	अचिन्हित दीर्घ error_code;
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	काष्ठा perf_event *ptrace_bp[XCHAL_NUM_IBREAK];
	काष्ठा perf_event *ptrace_wp[XCHAL_NUM_DBREAK];
#पूर्ण_अगर
	/* Make काष्ठाure 16 bytes aligned. */
	पूर्णांक align[0] __attribute__ ((aligned(16)));
पूर्ण;

/* This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE	(TASK_SIZE / 2)

#घोषणा INIT_THREAD  \
अणु									\
	ra:		0, 						\
	sp:		माप(init_stack) + (दीर्घ) &init_stack,	\
	current_ds:	अणु0पूर्ण,						\
	/*info:		अणु0पूर्ण, */						\
	bad_vaddr:	0,						\
	bad_uaddr:	0,						\
	error_code:	0,						\
पूर्ण


/*
 * Do necessary setup to start up a newly executed thपढ़ो.
 * Note: When winकरोwed ABI is used क्रम userspace we set-up ps
 *       as अगर we did a call4 to the new pc.
 *       set_thपढ़ो_state in संकेत.c depends on it.
 */
#अगर IS_ENABLED(CONFIG_USER_ABI_CALL0)
#घोषणा USER_PS_VALUE ((USER_RING << PS_RING_SHIFT) |			\
		       (1 << PS_UM_BIT) |				\
		       (1 << PS_EXCM_BIT))
#अन्यथा
#घोषणा USER_PS_VALUE (PS_WOE_MASK |					\
		       (1 << PS_CALLINC_SHIFT) |			\
		       (USER_RING << PS_RING_SHIFT) |			\
		       (1 << PS_UM_BIT) |				\
		       (1 << PS_EXCM_BIT))
#पूर्ण_अगर

/* Clearing a0 terminates the backtrace. */
#घोषणा start_thपढ़ो(regs, new_pc, new_sp) \
	करो अणु \
		अचिन्हित दीर्घ syscall = (regs)->syscall; \
		स_रखो((regs), 0, माप(*(regs))); \
		(regs)->pc = (new_pc); \
		(regs)->ps = USER_PS_VALUE; \
		(regs)->areg[1] = (new_sp); \
		(regs)->areg[0] = 0; \
		(regs)->wmask = 1; \
		(regs)->depc = 0; \
		(regs)->winकरोwbase = 0; \
		(regs)->winकरोwstart = 1; \
		(regs)->syscall = syscall; \
	पूर्ण जबतक (0)

/* Forward declaration */
काष्ठा task_काष्ठा;
काष्ठा mm_काष्ठा;

/* Free all resources held by a thपढ़ो. */
#घोषणा release_thपढ़ो(thपढ़ो) करो अणु पूर्ण जबतक(0)

बाह्य अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा KSTK_EIP(tsk)		(task_pt_regs(tsk)->pc)
#घोषणा KSTK_ESP(tsk)		(task_pt_regs(tsk)->areg[1])

#घोषणा cpu_relax()  barrier()

/* Special रेजिस्टर access. */

#घोषणा xtensa_set_sr(x, sr) \
	(अणु \
	 अचिन्हित पूर्णांक v = (अचिन्हित पूर्णांक)(x); \
	 __यंत्र__ __अस्थिर__ ("wsr %0, "__stringअगरy(sr) :: "a"(v)); \
	 पूर्ण)

#घोषणा xtensa_get_sr(sr) \
	(अणु \
	 अचिन्हित पूर्णांक v; \
	 __यंत्र__ __अस्थिर__ ("rsr %0, "__stringअगरy(sr) : "=a"(v)); \
	 v; \
	 पूर्ण)

#अगर XCHAL_HAVE_EXTERN_REGS

अटल अंतरभूत व्योम set_er(अचिन्हित दीर्घ value, अचिन्हित दीर्घ addr)
अणु
	यंत्र अस्थिर ("wer %0, %1" : : "a" (value), "a" (addr) : "memory");
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_er(अचिन्हित दीर्घ addr)
अणु
	रेजिस्टर अचिन्हित दीर्घ value;
	यंत्र अस्थिर ("rer %0, %1" : "=a" (value) : "a" (addr) : "memory");
	वापस value;
पूर्ण

#पूर्ण_अगर /* XCHAL_HAVE_EXTERN_REGS */

#पूर्ण_अगर	/* __ASSEMBLY__ */
#पूर्ण_अगर	/* _XTENSA_PROCESSOR_H */
