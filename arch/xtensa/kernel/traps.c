<शैली गुरु>
/*
 * arch/xtensa/kernel/traps.c
 *
 * Exception handling.
 *
 * Derived from code with the following copyrights:
 * Copyright (C) 1994 - 1999 by Ralf Baechle
 * Modअगरied क्रम R3000 by Paul M. Antoine, 1995, 1996
 * Complete output from die() by Ulf Carlsson, 1998
 * Copyright (C) 1999 Silicon Graphics, Inc.
 *
 * Essentially rewritten क्रम the Xtensa architecture port.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 *
 * Joe Taylor	<joe@tensilica.com, joetylr@yahoo.com>
 * Chris Zankel	<chris@zankel.net>
 * Marc Gauthier<marc@tensilica.com, marc@alumni.uwaterloo.ca>
 * Kevin Chea
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/delay.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/समयx.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>

/*
 * Machine specअगरic पूर्णांकerrupt handlers
 */

बाह्य व्योम kernel_exception(व्योम);
बाह्य व्योम user_exception(व्योम);

बाह्य व्योम fast_illegal_inकाष्ठाion_user(व्योम);
बाह्य व्योम fast_syscall_user(व्योम);
बाह्य व्योम fast_alloca(व्योम);
बाह्य व्योम fast_unaligned(व्योम);
बाह्य व्योम fast_second_level_miss(व्योम);
बाह्य व्योम fast_store_prohibited(व्योम);
बाह्य व्योम fast_coprocessor(व्योम);

बाह्य व्योम करो_illegal_inकाष्ठाion (काष्ठा pt_regs*);
बाह्य व्योम करो_पूर्णांकerrupt (काष्ठा pt_regs*);
बाह्य व्योम करो_nmi(काष्ठा pt_regs *);
बाह्य व्योम करो_unaligned_user (काष्ठा pt_regs*);
बाह्य व्योम करो_multihit (काष्ठा pt_regs*, अचिन्हित दीर्घ);
बाह्य व्योम करो_page_fault (काष्ठा pt_regs*, अचिन्हित दीर्घ);
बाह्य व्योम करो_debug (काष्ठा pt_regs*);
बाह्य व्योम प्रणाली_call (काष्ठा pt_regs*);

/*
 * The vector table must be preceded by a save area (which
 * implies it must be in RAM, unless one places RAM immediately
 * beक्रमe a ROM and माला_दो the vector at the start of the ROM (!))
 */

#घोषणा KRNL		0x01
#घोषणा USER		0x02

#घोषणा COPROCESSOR(x)							\
अणु EXCCAUSE_COPROCESSOR ## x ## _DISABLED, USER, fast_coprocessor पूर्ण

प्रकार काष्ठा अणु
	पूर्णांक cause;
	पूर्णांक fast;
	व्योम* handler;
पूर्ण dispatch_init_table_t;

अटल dispatch_init_table_t __initdata dispatch_init_table[] = अणु

#अगर_घोषित CONFIG_USER_ABI_CALL0_PROBE
अणु EXCCAUSE_ILLEGAL_INSTRUCTION,	USER,	   fast_illegal_inकाष्ठाion_user पूर्ण,
#पूर्ण_अगर
अणु EXCCAUSE_ILLEGAL_INSTRUCTION,	0,	   करो_illegal_inकाष्ठाionपूर्ण,
अणु EXCCAUSE_SYSTEM_CALL,		USER,	   fast_syscall_user पूर्ण,
अणु EXCCAUSE_SYSTEM_CALL,		0,	   प्रणाली_call पूर्ण,
/* EXCCAUSE_INSTRUCTION_FETCH unhandled */
/* EXCCAUSE_LOAD_STORE_ERROR unhandled*/
अणु EXCCAUSE_LEVEL1_INTERRUPT,	0,	   करो_पूर्णांकerrupt पूर्ण,
अणु EXCCAUSE_ALLOCA,		USER|KRNL, fast_alloca पूर्ण,
/* EXCCAUSE_INTEGER_DIVIDE_BY_ZERO unhandled */
/* EXCCAUSE_PRIVILEGED unhandled */
#अगर XCHAL_UNALIGNED_LOAD_EXCEPTION || XCHAL_UNALIGNED_STORE_EXCEPTION
#अगर_घोषित CONFIG_XTENSA_UNALIGNED_USER
अणु EXCCAUSE_UNALIGNED,		USER,	   fast_unaligned पूर्ण,
#पूर्ण_अगर
अणु EXCCAUSE_UNALIGNED,		0,	   करो_unaligned_user पूर्ण,
अणु EXCCAUSE_UNALIGNED,		KRNL,	   fast_unaligned पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_MMU
अणु EXCCAUSE_ITLB_MISS,		0,	   करो_page_fault पूर्ण,
अणु EXCCAUSE_ITLB_MISS,		USER|KRNL, fast_second_level_missपूर्ण,
अणु EXCCAUSE_ITLB_MULTIHIT,		0,	   करो_multihit पूर्ण,
अणु EXCCAUSE_ITLB_PRIVILEGE,	0,	   करो_page_fault पूर्ण,
/* EXCCAUSE_SIZE_RESTRICTION unhandled */
अणु EXCCAUSE_FETCH_CACHE_ATTRIBUTE,	0,	   करो_page_fault पूर्ण,
अणु EXCCAUSE_DTLB_MISS,		USER|KRNL, fast_second_level_missपूर्ण,
अणु EXCCAUSE_DTLB_MISS,		0,	   करो_page_fault पूर्ण,
अणु EXCCAUSE_DTLB_MULTIHIT,		0,	   करो_multihit पूर्ण,
अणु EXCCAUSE_DTLB_PRIVILEGE,	0,	   करो_page_fault पूर्ण,
/* EXCCAUSE_DTLB_SIZE_RESTRICTION unhandled */
अणु EXCCAUSE_STORE_CACHE_ATTRIBUTE,	USER|KRNL, fast_store_prohibited पूर्ण,
अणु EXCCAUSE_STORE_CACHE_ATTRIBUTE,	0,	   करो_page_fault पूर्ण,
अणु EXCCAUSE_LOAD_CACHE_ATTRIBUTE,	0,	   करो_page_fault पूर्ण,
#पूर्ण_अगर /* CONFIG_MMU */
/* XCCHAL_EXCCAUSE_FLOATING_POINT unhandled */
#अगर XTENSA_HAVE_COPROCESSOR(0)
COPROCESSOR(0),
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSOR(1)
COPROCESSOR(1),
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSOR(2)
COPROCESSOR(2),
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSOR(3)
COPROCESSOR(3),
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSOR(4)
COPROCESSOR(4),
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSOR(5)
COPROCESSOR(5),
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSOR(6)
COPROCESSOR(6),
#पूर्ण_अगर
#अगर XTENSA_HAVE_COPROCESSOR(7)
COPROCESSOR(7),
#पूर्ण_अगर
#अगर XTENSA_FAKE_NMI
अणु EXCCAUSE_MAPPED_NMI,			0,		करो_nmi पूर्ण,
#पूर्ण_अगर
अणु EXCCAUSE_MAPPED_DEBUG,		0,		करो_debug पूर्ण,
अणु -1, -1, 0 पूर्ण

पूर्ण;

/* The exception table <exc_table> serves two functions:
 * 1. it contains three dispatch tables (fast_user, fast_kernel, शेष-c)
 * 2. it is a temporary memory buffer क्रम the exception handlers.
 */

DEFINE_PER_CPU(काष्ठा exc_table, exc_table);
DEFINE_PER_CPU(काष्ठा debug_table, debug_table);

व्योम die(स्थिर अक्षर*, काष्ठा pt_regs*, दीर्घ);

अटल अंतरभूत व्योम
__die_अगर_kernel(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अगर (!user_mode(regs))
		die(str, regs, err);
पूर्ण

/*
 * Unhandled Exceptions. Kill user task or panic अगर in kernel space.
 */

व्योम करो_unhandled(काष्ठा pt_regs *regs, अचिन्हित दीर्घ exccause)
अणु
	__die_अगर_kernel("Caught unhandled exception - should not happen",
			regs, SIGKILL);

	/* If in user mode, send संक_अवैध संकेत to current process */
	pr_info_ratelimited("Caught unhandled exception in '%s' "
			    "(pid = %d, pc = %#010lx) - should not happen\n"
			    "\tEXCCAUSE is %ld\n",
			    current->comm, task_pid_nr(current), regs->pc,
			    exccause);
	क्रमce_sig(संक_अवैध);
पूर्ण

/*
 * Multi-hit exception. This अगर fatal!
 */

व्योम करो_multihit(काष्ठा pt_regs *regs, अचिन्हित दीर्घ exccause)
अणु
	die("Caught multihit exception", regs, SIGKILL);
पूर्ण

/*
 * IRQ handler.
 */

बाह्य व्योम करो_IRQ(पूर्णांक, काष्ठा pt_regs *);

#अगर XTENSA_FAKE_NMI

#घोषणा IS_POW2(v) (((v) & ((v) - 1)) == 0)

#अगर !(PROFILING_INTLEVEL == XCHAL_EXCM_LEVEL && \
      IS_POW2(XTENSA_INTLEVEL_MASK(PROFILING_INTLEVEL)))
#warning "Fake NMI is requested for PMM, but there are other IRQs at or above its level."
#warning "Fake NMI will be used, but there will be a bugcheck if one of those IRQs fire."

अटल अंतरभूत व्योम check_valid_nmi(व्योम)
अणु
	अचिन्हित पूर्णांकपढ़ो = xtensa_get_sr(पूर्णांकerrupt);
	अचिन्हित पूर्णांकenable = xtensa_get_sr(पूर्णांकenable);

	BUG_ON(पूर्णांकपढ़ो & पूर्णांकenable &
	       ~(XTENSA_INTLEVEL_ANDBELOW_MASK(PROFILING_INTLEVEL) ^
		 XTENSA_INTLEVEL_MASK(PROFILING_INTLEVEL) ^
		 BIT(XCHAL_PROFILING_INTERRUPT)));
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम check_valid_nmi(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

irqवापस_t xtensa_pmu_irq_handler(पूर्णांक irq, व्योम *dev_id);

DEFINE_PER_CPU(अचिन्हित दीर्घ, nmi_count);

व्योम करो_nmi(काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *old_regs;

	अगर ((regs->ps & PS_INTLEVEL_MASK) < LOCKLEVEL)
		trace_hardirqs_off();

	old_regs = set_irq_regs(regs);
	nmi_enter();
	++*this_cpu_ptr(&nmi_count);
	check_valid_nmi();
	xtensa_pmu_irq_handler(0, शून्य);
	nmi_निकास();
	set_irq_regs(old_regs);
पूर्ण
#पूर्ण_अगर

व्योम करो_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	अटल स्थिर अचिन्हित पूर्णांक_level_mask[] = अणु
		0,
		XCHAL_INTLEVEL1_MASK,
		XCHAL_INTLEVEL2_MASK,
		XCHAL_INTLEVEL3_MASK,
		XCHAL_INTLEVEL4_MASK,
		XCHAL_INTLEVEL5_MASK,
		XCHAL_INTLEVEL6_MASK,
		XCHAL_INTLEVEL7_MASK,
	पूर्ण;
	काष्ठा pt_regs *old_regs;

	trace_hardirqs_off();

	old_regs = set_irq_regs(regs);
	irq_enter();

	क्रम (;;) अणु
		अचिन्हित पूर्णांकपढ़ो = xtensa_get_sr(पूर्णांकerrupt);
		अचिन्हित पूर्णांकenable = xtensa_get_sr(पूर्णांकenable);
		अचिन्हित पूर्णांक_at_level = पूर्णांकपढ़ो & पूर्णांकenable;
		अचिन्हित level;

		क्रम (level = LOCKLEVEL; level > 0; --level) अणु
			अगर (पूर्णांक_at_level & पूर्णांक_level_mask[level]) अणु
				पूर्णांक_at_level &= पूर्णांक_level_mask[level];
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (level == 0)
			अवरोध;

		करो_IRQ(__ffs(पूर्णांक_at_level), regs);
	पूर्ण

	irq_निकास();
	set_irq_regs(old_regs);
पूर्ण

/*
 * Illegal inकाष्ठाion. Fatal अगर in kernel space.
 */

व्योम
करो_illegal_inकाष्ठाion(काष्ठा pt_regs *regs)
अणु
	__die_अगर_kernel("Illegal instruction in kernel", regs, SIGKILL);

	/* If in user mode, send संक_अवैध संकेत to current process. */

	pr_info_ratelimited("Illegal Instruction in '%s' (pid = %d, pc = %#010lx)\n",
			    current->comm, task_pid_nr(current), regs->pc);
	क्रमce_sig(संक_अवैध);
पूर्ण


/*
 * Handle unaligned memory accesses from user space. Kill task.
 *
 * If CONFIG_UNALIGNED_USER is not set, we करोn't allow unaligned memory
 * accesses causes from user space.
 */

#अगर XCHAL_UNALIGNED_LOAD_EXCEPTION || XCHAL_UNALIGNED_STORE_EXCEPTION
व्योम
करो_unaligned_user (काष्ठा pt_regs *regs)
अणु
	__die_अगर_kernel("Unhandled unaligned exception in kernel",
			regs, SIGKILL);

	current->thपढ़ो.bad_vaddr = regs->excvaddr;
	current->thपढ़ो.error_code = -3;
	pr_info_ratelimited("Unaligned memory access to %08lx in '%s' "
			    "(pid = %d, pc = %#010lx)\n",
			    regs->excvaddr, current->comm,
			    task_pid_nr(current), regs->pc);
	क्रमce_sig_fault(SIGBUS, BUS_ADRALN, (व्योम *) regs->excvaddr);
पूर्ण
#पूर्ण_अगर

/* Handle debug events.
 * When CONFIG_HAVE_HW_BREAKPOINT is on this handler is called with
 * preemption disabled to aव्योम rescheduling and keep mapping of hardware
 * अवरोधpoपूर्णांक काष्ठाures to debug रेजिस्टरs पूर्णांकact, so that
 * DEBUGCAUSE.DBNUM could be used in हाल of data अवरोधpoपूर्णांक hit.
 */
व्योम
करो_debug(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	पूर्णांक ret = check_hw_अवरोधpoपूर्णांक(regs);

	preempt_enable();
	अगर (ret == 0)
		वापस;
#पूर्ण_अगर
	__die_अगर_kernel("Breakpoint in kernel", regs, SIGKILL);

	/* If in user mode, send SIGTRAP संकेत to current process */

	क्रमce_sig(SIGTRAP);
पूर्ण


#घोषणा set_handler(type, cause, handler)				\
	करो अणु								\
		अचिन्हित पूर्णांक cpu;					\
									\
		क्रम_each_possible_cpu(cpu)				\
			per_cpu(exc_table, cpu).type[cause] = (handler);\
	पूर्ण जबतक (0)

/* Set exception C handler - क्रम temporary use when probing exceptions */

व्योम * __init trap_set_handler(पूर्णांक cause, व्योम *handler)
अणु
	व्योम *previous = per_cpu(exc_table, 0).शेष_handler[cause];

	set_handler(शेष_handler, cause, handler);
	वापस previous;
पूर्ण


अटल व्योम trap_init_excsave(व्योम)
अणु
	अचिन्हित दीर्घ excsave1 = (अचिन्हित दीर्घ)this_cpu_ptr(&exc_table);
	__यंत्र__ __अस्थिर__("wsr  %0, excsave1\n" : : "a" (excsave1));
पूर्ण

अटल व्योम trap_init_debug(व्योम)
अणु
	अचिन्हित दीर्घ debugsave = (अचिन्हित दीर्घ)this_cpu_ptr(&debug_table);

	this_cpu_ptr(&debug_table)->debug_exception = debug_exception;
	__यंत्र__ __अस्थिर__("wsr %0, excsave" __stringअगरy(XCHAL_DEBUGLEVEL)
			     :: "a"(debugsave));
पूर्ण

/*
 * Initialize dispatch tables.
 *
 * The exception vectors are stored compressed the __init section in the
 * dispatch_init_table. This function initializes the following three tables
 * from that compressed table:
 * - fast user		first dispatch table क्रम user exceptions
 * - fast kernel	first dispatch table क्रम kernel exceptions
 * - शेष C-handler	C-handler called by the शेष fast handler.
 *
 * See vectors.S क्रम more details.
 */

व्योम __init trap_init(व्योम)
अणु
	पूर्णांक i;

	/* Setup शेष vectors. */

	क्रम (i = 0; i < EXCCAUSE_N; i++) अणु
		set_handler(fast_user_handler, i, user_exception);
		set_handler(fast_kernel_handler, i, kernel_exception);
		set_handler(शेष_handler, i, करो_unhandled);
	पूर्ण

	/* Setup specअगरic handlers. */

	क्रम(i = 0; dispatch_init_table[i].cause >= 0; i++) अणु
		पूर्णांक fast = dispatch_init_table[i].fast;
		पूर्णांक cause = dispatch_init_table[i].cause;
		व्योम *handler = dispatch_init_table[i].handler;

		अगर (fast == 0)
			set_handler(शेष_handler, cause, handler);
		अगर ((fast & USER) != 0)
			set_handler(fast_user_handler, cause, handler);
		अगर ((fast & KRNL) != 0)
			set_handler(fast_kernel_handler, cause, handler);
	पूर्ण

	/* Initialize EXCSAVE_1 to hold the address of the exception table. */
	trap_init_excsave();
	trap_init_debug();
पूर्ण

#अगर_घोषित CONFIG_SMP
व्योम secondary_trap_init(व्योम)
अणु
	trap_init_excsave();
	trap_init_debug();
पूर्ण
#पूर्ण_अगर

/*
 * This function dumps the current valid winकरोw frame and other base रेजिस्टरs.
 */

व्योम show_regs(काष्ठा pt_regs * regs)
अणु
	पूर्णांक i, wmask;

	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	wmask = regs->wmask & ~1;

	क्रम (i = 0; i < 16; i++) अणु
		अगर ((i % 8) == 0)
			pr_info("a%02d:", i);
		pr_cont(" %08lx", regs->areg[i]);
	पूर्ण
	pr_cont("\n");
	pr_info("pc: %08lx, ps: %08lx, depc: %08lx, excvaddr: %08lx\n",
		regs->pc, regs->ps, regs->depc, regs->excvaddr);
	pr_info("lbeg: %08lx, lend: %08lx lcount: %08lx, sar: %08lx\n",
		regs->lbeg, regs->lend, regs->lcount, regs->sar);
	अगर (user_mode(regs))
		pr_cont("wb: %08lx, ws: %08lx, wmask: %08lx, syscall: %ld\n",
			regs->winकरोwbase, regs->winकरोwstart, regs->wmask,
			regs->syscall);
पूर्ण

अटल पूर्णांक show_trace_cb(काष्ठा stackframe *frame, व्योम *data)
अणु
	स्थिर अक्षर *loglvl = data;

	अगर (kernel_text_address(frame->pc))
		prपूर्णांकk("%s [<%08lx>] %pB\n",
			loglvl, frame->pc, (व्योम *)frame->pc);
	वापस 0;
पूर्ण

अटल व्योम show_trace(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp,
		       स्थिर अक्षर *loglvl)
अणु
	अगर (!sp)
		sp = stack_poपूर्णांकer(task);

	prपूर्णांकk("%sCall Trace:\n", loglvl);
	walk_stackframe(sp, show_trace_cb, (व्योम *)loglvl);
पूर्ण

#घोषणा STACK_DUMP_ENTRY_SIZE 4
#घोषणा STACK_DUMP_LINE_SIZE 32
अटल माप_प्रकार kstack_depth_to_prपूर्णांक = CONFIG_PRINT_STACK_DEPTH;

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	माप_प्रकार len;

	अगर (!sp)
		sp = stack_poपूर्णांकer(task);

	len = min((-(माप_प्रकार)sp) & (THREAD_SIZE - STACK_DUMP_ENTRY_SIZE),
		  kstack_depth_to_prपूर्णांक * STACK_DUMP_ENTRY_SIZE);

	prपूर्णांकk("%sStack:\n", loglvl);
	prपूर्णांक_hex_dump(loglvl, " ", DUMP_PREFIX_NONE,
		       STACK_DUMP_LINE_SIZE, STACK_DUMP_ENTRY_SIZE,
		       sp, len, false);
	show_trace(task, sp, loglvl);
पूर्ण

DEFINE_SPINLOCK(die_lock);

व्योम die(स्थिर अक्षर * str, काष्ठा pt_regs * regs, दीर्घ err)
अणु
	अटल पूर्णांक die_counter;
	स्थिर अक्षर *pr = "";

	अगर (IS_ENABLED(CONFIG_PREEMPTION))
		pr = IS_ENABLED(CONFIG_PREEMPT_RT) ? " PREEMPT_RT" : " PREEMPT";

	console_verbose();
	spin_lock_irq(&die_lock);

	pr_info("%s: sig: %ld [#%d]%s\n", str, err, ++die_counter, pr);
	show_regs(regs);
	अगर (!user_mode(regs))
		show_stack(शून्य, (अचिन्हित दीर्घ *)regs->areg[1], KERN_INFO);

	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die_lock);

	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");

	अगर (panic_on_oops)
		panic("Fatal exception");

	करो_निकास(err);
पूर्ण
