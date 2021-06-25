<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 - 1999, 2000, 01, 06 Ralf Baechle
 * Copyright (C) 1995, 1996 Paul M. Antoine
 * Copyright (C) 1998 Ulf Carlsson
 * Copyright (C) 1999 Silicon Graphics, Inc.
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 2002, 2003, 2004, 2005, 2007  Maciej W. Rozycki
 * Copyright (C) 2000, 2001, 2012 MIPS Technologies, Inc.  All rights reserved.
 * Copyright (C) 2014, Imagination Technologies Ltd.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/compiler.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/kexec.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/extable.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/memblock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/kdb.h>
#समावेश <linux/irq.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/अवरोध.h>
#समावेश <यंत्र/cop2.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/dsp.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/fpu_emulator.h>
#समावेश <यंत्र/idle.h>
#समावेश <यंत्र/isa-rev.h>
#समावेश <यंत्र/mips-cps.h>
#समावेश <यंत्र/mips-r2-to-r6-emul.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mipsmtregs.h>
#समावेश <यंत्र/module.h>
#समावेश <यंत्र/msa.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/tlbdebug.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/watch.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/tlbex.h>
#समावेश <यंत्र/uयंत्र.h>

#समावेश <यंत्र/mach-loongson64/cpucfg-emul.h>

#समावेश "access-helper.h"

बाह्य व्योम check_रुको(व्योम);
बाह्य यंत्रlinkage व्योम rollback_handle_पूर्णांक(व्योम);
बाह्य यंत्रlinkage व्योम handle_पूर्णांक(व्योम);
बाह्य यंत्रlinkage व्योम handle_adel(व्योम);
बाह्य यंत्रlinkage व्योम handle_ades(व्योम);
बाह्य यंत्रlinkage व्योम handle_ibe(व्योम);
बाह्य यंत्रlinkage व्योम handle_dbe(व्योम);
बाह्य यंत्रlinkage व्योम handle_sys(व्योम);
बाह्य यंत्रlinkage व्योम handle_bp(व्योम);
बाह्य यंत्रlinkage व्योम handle_ri(व्योम);
बाह्य यंत्रlinkage व्योम handle_ri_rdhwr_tlbp(व्योम);
बाह्य यंत्रlinkage व्योम handle_ri_rdhwr(व्योम);
बाह्य यंत्रlinkage व्योम handle_cpu(व्योम);
बाह्य यंत्रlinkage व्योम handle_ov(व्योम);
बाह्य यंत्रlinkage व्योम handle_tr(व्योम);
बाह्य यंत्रlinkage व्योम handle_msa_fpe(व्योम);
बाह्य यंत्रlinkage व्योम handle_fpe(व्योम);
बाह्य यंत्रlinkage व्योम handle_ftlb(व्योम);
बाह्य यंत्रlinkage व्योम handle_gsexc(व्योम);
बाह्य यंत्रlinkage व्योम handle_msa(व्योम);
बाह्य यंत्रlinkage व्योम handle_mdmx(व्योम);
बाह्य यंत्रlinkage व्योम handle_watch(व्योम);
बाह्य यंत्रlinkage व्योम handle_mt(व्योम);
बाह्य यंत्रlinkage व्योम handle_dsp(व्योम);
बाह्य यंत्रlinkage व्योम handle_mcheck(व्योम);
बाह्य यंत्रlinkage व्योम handle_reserved(व्योम);
बाह्य व्योम tlb_करो_page_fault_0(व्योम);

व्योम (*board_be_init)(व्योम);
पूर्णांक (*board_be_handler)(काष्ठा pt_regs *regs, पूर्णांक is_fixup);
व्योम (*board_nmi_handler_setup)(व्योम);
व्योम (*board_ejtag_handler_setup)(व्योम);
व्योम (*board_bind_eic_पूर्णांकerrupt)(पूर्णांक irq, पूर्णांक regset);
व्योम (*board_ebase_setup)(व्योम);
व्योम(*board_cache_error_setup)(व्योम);

अटल व्योम show_raw_backtrace(अचिन्हित दीर्घ reg29, स्थिर अक्षर *loglvl,
			       bool user)
अणु
	अचिन्हित दीर्घ *sp = (अचिन्हित दीर्घ *)(reg29 & ~3);
	अचिन्हित दीर्घ addr;

	prपूर्णांकk("%sCall Trace:", loglvl);
#अगर_घोषित CONFIG_KALLSYMS
	prपूर्णांकk("%s\n", loglvl);
#पूर्ण_अगर
	जबतक (!kstack_end(sp)) अणु
		अगर (__get_addr(&addr, sp++, user)) अणु
			prपूर्णांकk("%s (Bad stack address)", loglvl);
			अवरोध;
		पूर्ण
		अगर (__kernel_text_address(addr))
			prपूर्णांक_ip_sym(loglvl, addr);
	पूर्ण
	prपूर्णांकk("%s\n", loglvl);
पूर्ण

#अगर_घोषित CONFIG_KALLSYMS
पूर्णांक raw_show_trace;
अटल पूर्णांक __init set_raw_show_trace(अक्षर *str)
अणु
	raw_show_trace = 1;
	वापस 1;
पूर्ण
__setup("raw_show_trace", set_raw_show_trace);
#पूर्ण_अगर

अटल व्योम show_backtrace(काष्ठा task_काष्ठा *task, स्थिर काष्ठा pt_regs *regs,
			   स्थिर अक्षर *loglvl, bool user)
अणु
	अचिन्हित दीर्घ sp = regs->regs[29];
	अचिन्हित दीर्घ ra = regs->regs[31];
	अचिन्हित दीर्घ pc = regs->cp0_epc;

	अगर (!task)
		task = current;

	अगर (raw_show_trace || user_mode(regs) || !__kernel_text_address(pc)) अणु
		show_raw_backtrace(sp, loglvl, user);
		वापस;
	पूर्ण
	prपूर्णांकk("%sCall Trace:\n", loglvl);
	करो अणु
		prपूर्णांक_ip_sym(loglvl, pc);
		pc = unwind_stack(task, &sp, pc, &ra);
	पूर्ण जबतक (pc);
	pr_cont("\n");
पूर्ण

/*
 * This routine abuses get_user()/put_user() to reference poपूर्णांकers
 * with at least a bit of error checking ...
 */
अटल व्योम show_stacktrace(काष्ठा task_काष्ठा *task,
	स्थिर काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl, bool user)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ stackdata;
	पूर्णांक i;
	अचिन्हित दीर्घ *sp = (अचिन्हित दीर्घ *)regs->regs[29];

	prपूर्णांकk("%sStack :", loglvl);
	i = 0;
	जबतक ((अचिन्हित दीर्घ) sp & (PAGE_SIZE - 1)) अणु
		अगर (i && ((i % (64 / field)) == 0)) अणु
			pr_cont("\n");
			prपूर्णांकk("%s       ", loglvl);
		पूर्ण
		अगर (i > 39) अणु
			pr_cont(" ...");
			अवरोध;
		पूर्ण

		अगर (__get_addr(&stackdata, sp++, user)) अणु
			pr_cont(" (Bad stack address)");
			अवरोध;
		पूर्ण

		pr_cont(" %0*lx", field, stackdata);
		i++;
	पूर्ण
	pr_cont("\n");
	show_backtrace(task, regs, loglvl, user);
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	काष्ठा pt_regs regs;

	regs.cp0_status = KSU_KERNEL;
	अगर (sp) अणु
		regs.regs[29] = (अचिन्हित दीर्घ)sp;
		regs.regs[31] = 0;
		regs.cp0_epc = 0;
	पूर्ण अन्यथा अणु
		अगर (task && task != current) अणु
			regs.regs[29] = task->thपढ़ो.reg29;
			regs.regs[31] = 0;
			regs.cp0_epc = task->thपढ़ो.reg31;
		पूर्ण अन्यथा अणु
			prepare_frametrace(&regs);
		पूर्ण
	पूर्ण
	show_stacktrace(task, &regs, loglvl, false);
पूर्ण

अटल व्योम show_code(व्योम *pc, bool user)
अणु
	दीर्घ i;
	अचिन्हित लघु *pc16 = शून्य;

	prपूर्णांकk("Code:");

	अगर ((अचिन्हित दीर्घ)pc & 1)
		pc16 = (u16 *)((अचिन्हित दीर्घ)pc & ~1);

	क्रम(i = -3 ; i < 6 ; i++) अणु
		अगर (pc16) अणु
			u16 insn16;

			अगर (__get_inst16(&insn16, pc16 + i, user))
				जाओ bad_address;

			pr_cont("%c%04x%c", (i?' ':'<'), insn16, (i?' ':'>'));
		पूर्ण अन्यथा अणु
			u32 insn32;

			अगर (__get_inst32(&insn32, (u32 *)pc + i, user))
				जाओ bad_address;

			pr_cont("%c%08x%c", (i?' ':'<'), insn32, (i?' ':'>'));
		पूर्ण
	पूर्ण
	pr_cont("\n");
	वापस;

bad_address:
	pr_cont(" (Bad address in epc)\n\n");
पूर्ण

अटल व्योम __show_regs(स्थिर काष्ठा pt_regs *regs)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	अचिन्हित पूर्णांक cause = regs->cp0_cause;
	अचिन्हित पूर्णांक exccode;
	पूर्णांक i;

	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	/*
	 * Saved मुख्य processor रेजिस्टरs
	 */
	क्रम (i = 0; i < 32; ) अणु
		अगर ((i % 4) == 0)
			prपूर्णांकk("$%2d   :", i);
		अगर (i == 0)
			pr_cont(" %0*lx", field, 0UL);
		अन्यथा अगर (i == 26 || i == 27)
			pr_cont(" %*s", field, "");
		अन्यथा
			pr_cont(" %0*lx", field, regs->regs[i]);

		i++;
		अगर ((i % 4) == 0)
			pr_cont("\n");
	पूर्ण

#अगर_घोषित CONFIG_CPU_HAS_SMARTMIPS
	prपूर्णांकk("Acx    : %0*lx\n", field, regs->acx);
#पूर्ण_अगर
	अगर (MIPS_ISA_REV < 6) अणु
		prपूर्णांकk("Hi    : %0*lx\n", field, regs->hi);
		prपूर्णांकk("Lo    : %0*lx\n", field, regs->lo);
	पूर्ण

	/*
	 * Saved cp0 रेजिस्टरs
	 */
	prपूर्णांकk("epc   : %0*lx %pS\n", field, regs->cp0_epc,
	       (व्योम *) regs->cp0_epc);
	prपूर्णांकk("ra    : %0*lx %pS\n", field, regs->regs[31],
	       (व्योम *) regs->regs[31]);

	prपूर्णांकk("Status: %08x	", (uपूर्णांक32_t) regs->cp0_status);

	अगर (cpu_has_3kex) अणु
		अगर (regs->cp0_status & ST0_KUO)
			pr_cont("KUo ");
		अगर (regs->cp0_status & ST0_IEO)
			pr_cont("IEo ");
		अगर (regs->cp0_status & ST0_KUP)
			pr_cont("KUp ");
		अगर (regs->cp0_status & ST0_IEP)
			pr_cont("IEp ");
		अगर (regs->cp0_status & ST0_KUC)
			pr_cont("KUc ");
		अगर (regs->cp0_status & ST0_IEC)
			pr_cont("IEc ");
	पूर्ण अन्यथा अगर (cpu_has_4kex) अणु
		अगर (regs->cp0_status & ST0_KX)
			pr_cont("KX ");
		अगर (regs->cp0_status & ST0_SX)
			pr_cont("SX ");
		अगर (regs->cp0_status & ST0_UX)
			pr_cont("UX ");
		चयन (regs->cp0_status & ST0_KSU) अणु
		हाल KSU_USER:
			pr_cont("USER ");
			अवरोध;
		हाल KSU_SUPERVISOR:
			pr_cont("SUPERVISOR ");
			अवरोध;
		हाल KSU_KERNEL:
			pr_cont("KERNEL ");
			अवरोध;
		शेष:
			pr_cont("BAD_MODE ");
			अवरोध;
		पूर्ण
		अगर (regs->cp0_status & ST0_ERL)
			pr_cont("ERL ");
		अगर (regs->cp0_status & ST0_EXL)
			pr_cont("EXL ");
		अगर (regs->cp0_status & ST0_IE)
			pr_cont("IE ");
	पूर्ण
	pr_cont("\n");

	exccode = (cause & CAUSEF_EXCCODE) >> CAUSEB_EXCCODE;
	prपूर्णांकk("Cause : %08x (ExcCode %02x)\n", cause, exccode);

	अगर (1 <= exccode && exccode <= 5)
		prपूर्णांकk("BadVA : %0*lx\n", field, regs->cp0_badvaddr);

	prपूर्णांकk("PrId  : %08x (%s)\n", पढ़ो_c0_prid(),
	       cpu_name_string());
पूर्ण

/*
 * FIXME: really the generic show_regs should take a स्थिर poपूर्णांकer argument.
 */
व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	__show_regs(regs);
	dump_stack();
पूर्ण

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);

	__show_regs(regs);
	prपूर्णांक_modules();
	prपूर्णांकk("Process %s (pid: %d, threadinfo=%p, task=%p, tls=%0*lx)\n",
	       current->comm, current->pid, current_thपढ़ो_info(), current,
	      field, current_thपढ़ो_info()->tp_value);
	अगर (cpu_has_userlocal) अणु
		अचिन्हित दीर्घ tls;

		tls = पढ़ो_c0_userlocal();
		अगर (tls != current_thपढ़ो_info()->tp_value)
			prपूर्णांकk("*HwTLS: %0*lx\n", field, tls);
	पूर्ण

	show_stacktrace(current, regs, KERN_DEFAULT, user_mode(regs));
	show_code((व्योम *)regs->cp0_epc, user_mode(regs));
	prपूर्णांकk("\n");
पूर्ण

अटल DEFINE_RAW_SPINLOCK(die_lock);

व्योम __noवापस die(स्थिर अक्षर *str, काष्ठा pt_regs *regs)
अणु
	अटल पूर्णांक die_counter;
	पूर्णांक sig = संक_अंश;

	oops_enter();

	अगर (notअगरy_die(DIE_OOPS, str, regs, 0, current->thपढ़ो.trap_nr,
		       संक_अंश) == NOTIFY_STOP)
		sig = 0;

	console_verbose();
	raw_spin_lock_irq(&die_lock);
	bust_spinlocks(1);

	prपूर्णांकk("%s[#%d]:\n", str, ++die_counter);
	show_रेजिस्टरs(regs);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	raw_spin_unlock_irq(&die_lock);

	oops_निकास();

	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");

	अगर (panic_on_oops)
		panic("Fatal exception");

	अगर (regs && kexec_should_crash(current))
		crash_kexec(regs);

	करो_निकास(sig);
पूर्ण

बाह्य काष्ठा exception_table_entry __start___dbe_table[];
बाह्य काष्ठा exception_table_entry __stop___dbe_table[];

__यंत्र__(
"	.section	__dbe_table, \"a\"\n"
"	.previous			\n");

/* Given an address, look क्रम it in the exception tables. */
अटल स्थिर काष्ठा exception_table_entry *search_dbe_tables(अचिन्हित दीर्घ addr)
अणु
	स्थिर काष्ठा exception_table_entry *e;

	e = search_extable(__start___dbe_table,
			   __stop___dbe_table - __start___dbe_table, addr);
	अगर (!e)
		e = search_module_dbetables(addr);
	वापस e;
पूर्ण

यंत्रlinkage व्योम करो_be(काष्ठा pt_regs *regs)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	स्थिर काष्ठा exception_table_entry *fixup = शून्य;
	पूर्णांक data = regs->cp0_cause & 4;
	पूर्णांक action = MIPS_BE_FATAL;
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	/* XXX For now.	 Fixme, this searches the wrong table ...  */
	अगर (data && !user_mode(regs))
		fixup = search_dbe_tables(exception_epc(regs));

	अगर (fixup)
		action = MIPS_BE_FIXUP;

	अगर (board_be_handler)
		action = board_be_handler(regs, fixup != शून्य);
	अन्यथा
		mips_cm_error_report();

	चयन (action) अणु
	हाल MIPS_BE_DISCARD:
		जाओ out;
	हाल MIPS_BE_FIXUP:
		अगर (fixup) अणु
			regs->cp0_epc = fixup->nextinsn;
			जाओ out;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Assume it would be too dangerous to जारी ...
	 */
	prपूर्णांकk(KERN_ALERT "%s bus error, epc == %0*lx, ra == %0*lx\n",
	       data ? "Data" : "Instruction",
	       field, regs->cp0_epc, field, regs->regs[31]);
	अगर (notअगरy_die(DIE_OOPS, "bus error", regs, 0, current->thपढ़ो.trap_nr,
		       SIGBUS) == NOTIFY_STOP)
		जाओ out;

	die_अगर_kernel("Oops", regs);
	क्रमce_sig(SIGBUS);

out:
	exception_निकास(prev_state);
पूर्ण

/*
 * ll/sc, rdhwr, sync emulation
 */

#घोषणा OPCODE 0xfc000000
#घोषणा BASE   0x03e00000
#घोषणा RT     0x001f0000
#घोषणा OFFSET 0x0000ffff
#घोषणा LL     0xc0000000
#घोषणा SC     0xe0000000
#घोषणा SPEC0  0x00000000
#घोषणा SPEC3  0x7c000000
#घोषणा RD     0x0000f800
#घोषणा FUNC   0x0000003f
#घोषणा SYNC   0x0000000f
#घोषणा RDHWR  0x0000003b

/*  microMIPS definitions   */
#घोषणा MM_POOL32A_FUNC 0xfc00ffff
#घोषणा MM_RDHWR        0x00006b3c
#घोषणा MM_RS           0x001f0000
#घोषणा MM_RT           0x03e00000

/*
 * The ll_bit is cleared by r*_चयन.S
 */

अचिन्हित पूर्णांक ll_bit;
काष्ठा task_काष्ठा *ll_task;

अटल अंतरभूत पूर्णांक simulate_ll(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित दीर्घ value, __user *vaddr;
	दीर्घ offset;

	/*
	 * analyse the ll inकाष्ठाion that just caused a ri exception
	 * and put the referenced address to addr.
	 */

	/* sign extend offset */
	offset = opcode & OFFSET;
	offset <<= 16;
	offset >>= 16;

	vaddr = (अचिन्हित दीर्घ __user *)
		((अचिन्हित दीर्घ)(regs->regs[(opcode & BASE) >> 21]) + offset);

	अगर ((अचिन्हित दीर्घ)vaddr & 3)
		वापस SIGBUS;
	अगर (get_user(value, vaddr))
		वापस संक_अंश;

	preempt_disable();

	अगर (ll_task == शून्य || ll_task == current) अणु
		ll_bit = 1;
	पूर्ण अन्यथा अणु
		ll_bit = 0;
	पूर्ण
	ll_task = current;

	preempt_enable();

	regs->regs[(opcode & RT) >> 16] = value;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक simulate_sc(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode)
अणु
	अचिन्हित दीर्घ __user *vaddr;
	अचिन्हित दीर्घ reg;
	दीर्घ offset;

	/*
	 * analyse the sc inकाष्ठाion that just caused a ri exception
	 * and put the referenced address to addr.
	 */

	/* sign extend offset */
	offset = opcode & OFFSET;
	offset <<= 16;
	offset >>= 16;

	vaddr = (अचिन्हित दीर्घ __user *)
		((अचिन्हित दीर्घ)(regs->regs[(opcode & BASE) >> 21]) + offset);
	reg = (opcode & RT) >> 16;

	अगर ((अचिन्हित दीर्घ)vaddr & 3)
		वापस SIGBUS;

	preempt_disable();

	अगर (ll_bit == 0 || ll_task != current) अणु
		regs->regs[reg] = 0;
		preempt_enable();
		वापस 0;
	पूर्ण

	preempt_enable();

	अगर (put_user(regs->regs[reg], vaddr))
		वापस संक_अंश;

	regs->regs[reg] = 1;

	वापस 0;
पूर्ण

/*
 * ll uses the opcode of lwc0 and sc uses the opcode of swc0.  That is both
 * opcodes are supposed to result in coprocessor unusable exceptions अगर
 * executed on ll/sc-less processors.  That's the theory.  In practice a
 * few processors such as NEC's VR4100 throw reserved inकाष्ठाion exceptions
 * instead, so we're करोing the emulation thing in both exception handlers.
 */
अटल पूर्णांक simulate_llsc(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode)
अणु
	अगर ((opcode & OPCODE) == LL) अणु
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
				1, regs, 0);
		वापस simulate_ll(regs, opcode);
	पूर्ण
	अगर ((opcode & OPCODE) == SC) अणु
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
				1, regs, 0);
		वापस simulate_sc(regs, opcode);
	पूर्ण

	वापस -1;			/* Must be something अन्यथा ... */
पूर्ण

/*
 * Simulate trapping 'rdhwr' inकाष्ठाions to provide user accessible
 * रेजिस्टरs not implemented in hardware.
 */
अटल पूर्णांक simulate_rdhwr(काष्ठा pt_regs *regs, पूर्णांक rd, पूर्णांक rt)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(current);

	perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
			1, regs, 0);
	चयन (rd) अणु
	हाल MIPS_HWR_CPUNUM:		/* CPU number */
		regs->regs[rt] = smp_processor_id();
		वापस 0;
	हाल MIPS_HWR_SYNCISTEP:	/* SYNCI length */
		regs->regs[rt] = min(current_cpu_data.dcache.linesz,
				     current_cpu_data.icache.linesz);
		वापस 0;
	हाल MIPS_HWR_CC:		/* Read count रेजिस्टर */
		regs->regs[rt] = पढ़ो_c0_count();
		वापस 0;
	हाल MIPS_HWR_CCRES:		/* Count रेजिस्टर resolution */
		चयन (current_cpu_type()) अणु
		हाल CPU_20KC:
		हाल CPU_25KF:
			regs->regs[rt] = 1;
			अवरोध;
		शेष:
			regs->regs[rt] = 2;
		पूर्ण
		वापस 0;
	हाल MIPS_HWR_ULR:		/* Read UserLocal रेजिस्टर */
		regs->regs[rt] = ti->tp_value;
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण
पूर्ण

अटल पूर्णांक simulate_rdhwr_normal(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode)
अणु
	अगर ((opcode & OPCODE) == SPEC3 && (opcode & FUNC) == RDHWR) अणु
		पूर्णांक rd = (opcode & RD) >> 11;
		पूर्णांक rt = (opcode & RT) >> 16;

		simulate_rdhwr(regs, rd, rt);
		वापस 0;
	पूर्ण

	/* Not ours.  */
	वापस -1;
पूर्ण

अटल पूर्णांक simulate_rdhwr_mm(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode)
अणु
	अगर ((opcode & MM_POOL32A_FUNC) == MM_RDHWR) अणु
		पूर्णांक rd = (opcode & MM_RS) >> 16;
		पूर्णांक rt = (opcode & MM_RT) >> 21;
		simulate_rdhwr(regs, rd, rt);
		वापस 0;
	पूर्ण

	/* Not ours.  */
	वापस -1;
पूर्ण

अटल पूर्णांक simulate_sync(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode)
अणु
	अगर ((opcode & OPCODE) == SPEC0 && (opcode & FUNC) == SYNC) अणु
		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS,
				1, regs, 0);
		वापस 0;
	पूर्ण

	वापस -1;			/* Must be something अन्यथा ... */
पूर्ण

/*
 * Loongson-3 CSR inकाष्ठाions emulation
 */

#अगर_घोषित CONFIG_CPU_LOONGSON3_CPUCFG_EMULATION

#घोषणा LWC2             0xc8000000
#घोषणा RS               BASE
#घोषणा CSR_OPCODE2      0x00000118
#घोषणा CSR_OPCODE2_MASK 0x000007ff
#घोषणा CSR_FUNC_MASK    RT
#घोषणा CSR_FUNC_CPUCFG  0x8

अटल पूर्णांक simulate_loongson3_cpucfg(काष्ठा pt_regs *regs,
				     अचिन्हित पूर्णांक opcode)
अणु
	पूर्णांक op = opcode & OPCODE;
	पूर्णांक op2 = opcode & CSR_OPCODE2_MASK;
	पूर्णांक csr_func = (opcode & CSR_FUNC_MASK) >> 16;

	अगर (op == LWC2 && op2 == CSR_OPCODE2 && csr_func == CSR_FUNC_CPUCFG) अणु
		पूर्णांक rd = (opcode & RD) >> 11;
		पूर्णांक rs = (opcode & RS) >> 21;
		__u64 sel = regs->regs[rs];

		perf_sw_event(PERF_COUNT_SW_EMULATION_FAULTS, 1, regs, 0);

		/* Do not emulate on unsupported core models. */
		preempt_disable();
		अगर (!loongson3_cpucfg_emulation_enabled(&current_cpu_data)) अणु
			preempt_enable();
			वापस -1;
		पूर्ण
		regs->regs[rd] = loongson3_cpucfg_पढ़ो_synthesized(
			&current_cpu_data, sel);
		preempt_enable();
		वापस 0;
	पूर्ण

	/* Not ours.  */
	वापस -1;
पूर्ण
#पूर्ण_अगर /* CONFIG_CPU_LOONGSON3_CPUCFG_EMULATION */

यंत्रlinkage व्योम करो_ov(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	die_अगर_kernel("Integer overflow", regs);

	क्रमce_sig_fault(संक_भ_त्रुटि, FPE_INTOVF, (व्योम __user *)regs->cp0_epc);
	exception_निकास(prev_state);
पूर्ण

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

/*
 * Send संक_भ_त्रुटि according to FCSR Cause bits, which must have alपढ़ोy
 * been masked against Enable bits.  This is impotant as Inexact can
 * happen together with Overflow or Underflow, and `ptrace' can set
 * any bits.
 */
व्योम क्रमce_fcr31_sig(अचिन्हित दीर्घ fcr31, व्योम __user *fault_addr,
		     काष्ठा task_काष्ठा *tsk)
अणु
	पूर्णांक si_code = FPE_FLTUNK;

	अगर (fcr31 & FPU_CSR_INV_X)
		si_code = FPE_FLTINV;
	अन्यथा अगर (fcr31 & FPU_CSR_DIV_X)
		si_code = FPE_FLTDIV;
	अन्यथा अगर (fcr31 & FPU_CSR_OVF_X)
		si_code = FPE_FLTOVF;
	अन्यथा अगर (fcr31 & FPU_CSR_UDF_X)
		si_code = FPE_FLTUND;
	अन्यथा अगर (fcr31 & FPU_CSR_INE_X)
		si_code = FPE_FLTRES;

	क्रमce_sig_fault_to_task(संक_भ_त्रुटि, si_code, fault_addr, tsk);
पूर्ण

पूर्णांक process_fpemu_वापस(पूर्णांक sig, व्योम __user *fault_addr, अचिन्हित दीर्घ fcr31)
अणु
	पूर्णांक si_code;
	काष्ठा vm_area_काष्ठा *vma;

	चयन (sig) अणु
	हाल 0:
		वापस 0;

	हाल संक_भ_त्रुटि:
		क्रमce_fcr31_sig(fcr31, fault_addr, current);
		वापस 1;

	हाल SIGBUS:
		क्रमce_sig_fault(SIGBUS, BUS_ADRERR, fault_addr);
		वापस 1;

	हाल संक_अंश:
		mmap_पढ़ो_lock(current->mm);
		vma = find_vma(current->mm, (अचिन्हित दीर्घ)fault_addr);
		अगर (vma && (vma->vm_start <= (अचिन्हित दीर्घ)fault_addr))
			si_code = SEGV_ACCERR;
		अन्यथा
			si_code = SEGV_MAPERR;
		mmap_पढ़ो_unlock(current->mm);
		क्रमce_sig_fault(संक_अंश, si_code, fault_addr);
		वापस 1;

	शेष:
		क्रमce_sig(sig);
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक simulate_fp(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode,
		       अचिन्हित दीर्घ old_epc, अचिन्हित दीर्घ old_ra)
अणु
	जोड़ mips_inकाष्ठाion inst = अणु .word = opcode पूर्ण;
	व्योम __user *fault_addr;
	अचिन्हित दीर्घ fcr31;
	पूर्णांक sig;

	/* If it's obviously not an FP inकाष्ठाion, skip it */
	चयन (inst.i_क्रमmat.opcode) अणु
	हाल cop1_op:
	हाल cop1x_op:
	हाल lwc1_op:
	हाल ldc1_op:
	हाल swc1_op:
	हाल sdc1_op:
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	/*
	 * करो_ri skipped over the inकाष्ठाion via compute_वापस_epc, unकरो
	 * that क्रम the FPU emulator.
	 */
	regs->cp0_epc = old_epc;
	regs->regs[31] = old_ra;

	/* Run the emulator */
	sig = fpu_emulator_cop1Handler(regs, &current->thपढ़ो.fpu, 1,
				       &fault_addr);

	/*
	 * We can't allow the emulated inकाष्ठाion to leave any
	 * enabled Cause bits set in $fcr31.
	 */
	fcr31 = mask_fcr31_x(current->thपढ़ो.fpu.fcr31);
	current->thपढ़ो.fpu.fcr31 &= ~fcr31;

	/* Restore the hardware रेजिस्टर state */
	own_fpu(1);

	/* Send a संकेत अगर required.  */
	process_fpemu_वापस(sig, fault_addr, fcr31);

	वापस 0;
पूर्ण

/*
 * XXX Delayed fp exceptions when करोing a lazy ctx चयन XXX
 */
यंत्रlinkage व्योम करो_fpe(काष्ठा pt_regs *regs, अचिन्हित दीर्घ fcr31)
अणु
	क्रमागत ctx_state prev_state;
	व्योम __user *fault_addr;
	पूर्णांक sig;

	prev_state = exception_enter();
	अगर (notअगरy_die(DIE_FP, "FP exception", regs, 0, current->thपढ़ो.trap_nr,
		       संक_भ_त्रुटि) == NOTIFY_STOP)
		जाओ out;

	/* Clear FCSR.Cause beक्रमe enabling पूर्णांकerrupts */
	ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS, fcr31 & ~mask_fcr31_x(fcr31));
	local_irq_enable();

	die_अगर_kernel("FP exception in kernel code", regs);

	अगर (fcr31 & FPU_CSR_UNI_X) अणु
		/*
		 * Unimplemented operation exception.  If we've got the full
		 * software emulator on-board, let's use it...
		 *
		 * Force FPU to dump state पूर्णांकo task/thपढ़ो context.  We're
		 * moving a lot of data here क्रम what is probably a single
		 * inकाष्ठाion, but the alternative is to pre-decode the FP
		 * रेजिस्टर opeअक्रमs beक्रमe invoking the emulator, which seems
		 * a bit extreme क्रम what should be an infrequent event.
		 */

		/* Run the emulator */
		sig = fpu_emulator_cop1Handler(regs, &current->thपढ़ो.fpu, 1,
					       &fault_addr);

		/*
		 * We can't allow the emulated inकाष्ठाion to leave any
		 * enabled Cause bits set in $fcr31.
		 */
		fcr31 = mask_fcr31_x(current->thपढ़ो.fpu.fcr31);
		current->thपढ़ो.fpu.fcr31 &= ~fcr31;

		/* Restore the hardware रेजिस्टर state */
		own_fpu(1);	/* Using the FPU again.	 */
	पूर्ण अन्यथा अणु
		sig = संक_भ_त्रुटि;
		fault_addr = (व्योम __user *) regs->cp0_epc;
	पूर्ण

	/* Send a संकेत अगर required.  */
	process_fpemu_वापस(sig, fault_addr, fcr31);

out:
	exception_निकास(prev_state);
पूर्ण

/*
 * MIPS MT processors may have fewer FPU contexts than CPU thपढ़ोs. If we've
 * emulated more than some threshold number of inकाष्ठाions, क्रमce migration to
 * a "CPU" that has FP support.
 */
अटल व्योम mt_ase_fp_affinity(व्योम)
अणु
#अगर_घोषित CONFIG_MIPS_MT_FPAFF
	अगर (mt_fpemul_threshold > 0 &&
	     ((current->thपढ़ो.emulated_fp++ > mt_fpemul_threshold))) अणु
		/*
		 * If there's no FPU present, or अगर the application has alपढ़ोy
		 * restricted the allowed set to exclude any CPUs with FPUs,
		 * we'll skip the procedure.
		 */
		अगर (cpumask_पूर्णांकersects(&current->cpus_mask, &mt_fpu_cpumask)) अणु
			cpumask_t पंचांगask;

			current->thपढ़ो.user_cpus_allowed
				= current->cpus_mask;
			cpumask_and(&पंचांगask, &current->cpus_mask,
				    &mt_fpu_cpumask);
			set_cpus_allowed_ptr(current, &पंचांगask);
			set_thपढ़ो_flag(TIF_FPUBOUND);
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */
पूर्ण

#अन्यथा /* !CONFIG_MIPS_FP_SUPPORT */

अटल पूर्णांक simulate_fp(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक opcode,
		       अचिन्हित दीर्घ old_epc, अचिन्हित दीर्घ old_ra)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर /* !CONFIG_MIPS_FP_SUPPORT */

व्योम करो_trap_or_bp(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक code, पूर्णांक si_code,
	स्थिर अक्षर *str)
अणु
	अक्षर b[40];

#अगर_घोषित CONFIG_KGDB_LOW_LEVEL_TRAP
	अगर (kgdb_ll_trap(DIE_TRAP, str, regs, code, current->thपढ़ो.trap_nr,
			 SIGTRAP) == NOTIFY_STOP)
		वापस;
#पूर्ण_अगर /* CONFIG_KGDB_LOW_LEVEL_TRAP */

	अगर (notअगरy_die(DIE_TRAP, str, regs, code, current->thपढ़ो.trap_nr,
		       SIGTRAP) == NOTIFY_STOP)
		वापस;

	/*
	 * A लघु test says that IRIX 5.3 sends SIGTRAP क्रम all trap
	 * insns, even क्रम trap and अवरोध codes that indicate arithmetic
	 * failures.  Weird ...
	 * But should we जारी the brokenness???  --macro
	 */
	चयन (code) अणु
	हाल BRK_OVERFLOW:
	हाल BRK_DIVZERO:
		scnम_लिखो(b, माप(b), "%s instruction in kernel code", str);
		die_अगर_kernel(b, regs);
		क्रमce_sig_fault(संक_भ_त्रुटि,
				code == BRK_DIVZERO ? FPE_INTDIV : FPE_INTOVF,
				(व्योम __user *) regs->cp0_epc);
		अवरोध;
	हाल BRK_BUG:
		die_अगर_kernel("Kernel bug detected", regs);
		क्रमce_sig(SIGTRAP);
		अवरोध;
	हाल BRK_MEMU:
		/*
		 * This अवरोधpoपूर्णांक code is used by the FPU emulator to retake
		 * control of the CPU after executing the inकाष्ठाion from the
		 * delay slot of an emulated branch.
		 *
		 * Terminate अगर exception was recognized as a delay slot वापस
		 * otherwise handle as normal.
		 */
		अगर (करो_dsemulret(regs))
			वापस;

		die_अगर_kernel("Math emu break/trap", regs);
		क्रमce_sig(SIGTRAP);
		अवरोध;
	शेष:
		scnम_लिखो(b, माप(b), "%s instruction in kernel code", str);
		die_अगर_kernel(b, regs);
		अगर (si_code) अणु
			क्रमce_sig_fault(SIGTRAP, si_code, शून्य);
		पूर्ण अन्यथा अणु
			क्रमce_sig(SIGTRAP);
		पूर्ण
	पूर्ण
पूर्ण

यंत्रlinkage व्योम करो_bp(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ epc = msk_isa16_mode(exception_epc(regs));
	अचिन्हित पूर्णांक opcode, bcode;
	क्रमागत ctx_state prev_state;
	bool user = user_mode(regs);

	prev_state = exception_enter();
	current->thपढ़ो.trap_nr = (regs->cp0_cause >> 2) & 0x1f;
	अगर (get_isa16_mode(regs->cp0_epc)) अणु
		u16 instr[2];

		अगर (__get_inst16(&instr[0], (u16 *)epc, user))
			जाओ out_sigsegv;

		अगर (!cpu_has_mmips) अणु
			/* MIPS16e mode */
			bcode = (instr[0] >> 5) & 0x3f;
		पूर्ण अन्यथा अगर (mm_insn_16bit(instr[0])) अणु
			/* 16-bit microMIPS BREAK */
			bcode = instr[0] & 0xf;
		पूर्ण अन्यथा अणु
			/* 32-bit microMIPS BREAK */
			अगर (__get_inst16(&instr[1], (u16 *)(epc + 2), user))
				जाओ out_sigsegv;
			opcode = (instr[0] << 16) | instr[1];
			bcode = (opcode >> 6) & ((1 << 20) - 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (__get_inst32(&opcode, (u32 *)epc, user))
			जाओ out_sigsegv;
		bcode = (opcode >> 6) & ((1 << 20) - 1);
	पूर्ण

	/*
	 * There is the ancient bug in the MIPS assemblers that the अवरोध
	 * code starts left to bit 16 instead to bit 6 in the opcode.
	 * Gas is bug-compatible, but not always, grrr...
	 * We handle both हालs with a simple heuristics.  --macro
	 */
	अगर (bcode >= (1 << 10))
		bcode = ((bcode & ((1 << 10) - 1)) << 10) | (bcode >> 10);

	/*
	 * notअगरy the kprobe handlers, अगर inकाष्ठाion is likely to
	 * pertain to them.
	 */
	चयन (bcode) अणु
	हाल BRK_UPROBE:
		अगर (notअगरy_die(DIE_UPROBE, "uprobe", regs, bcode,
			       current->thपढ़ो.trap_nr, SIGTRAP) == NOTIFY_STOP)
			जाओ out;
		अन्यथा
			अवरोध;
	हाल BRK_UPROBE_XOL:
		अगर (notअगरy_die(DIE_UPROBE_XOL, "uprobe_xol", regs, bcode,
			       current->thपढ़ो.trap_nr, SIGTRAP) == NOTIFY_STOP)
			जाओ out;
		अन्यथा
			अवरोध;
	हाल BRK_KPROBE_BP:
		अगर (notअगरy_die(DIE_BREAK, "debug", regs, bcode,
			       current->thपढ़ो.trap_nr, SIGTRAP) == NOTIFY_STOP)
			जाओ out;
		अन्यथा
			अवरोध;
	हाल BRK_KPROBE_SSTEPBP:
		अगर (notअगरy_die(DIE_SSTEPBP, "single_step", regs, bcode,
			       current->thपढ़ो.trap_nr, SIGTRAP) == NOTIFY_STOP)
			जाओ out;
		अन्यथा
			अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	करो_trap_or_bp(regs, bcode, TRAP_BRKPT, "Break");

out:
	exception_निकास(prev_state);
	वापस;

out_sigsegv:
	क्रमce_sig(संक_अंश);
	जाओ out;
पूर्ण

यंत्रlinkage व्योम करो_tr(काष्ठा pt_regs *regs)
अणु
	u32 opcode, tcode = 0;
	क्रमागत ctx_state prev_state;
	u16 instr[2];
	bool user = user_mode(regs);
	अचिन्हित दीर्घ epc = msk_isa16_mode(exception_epc(regs));

	prev_state = exception_enter();
	current->thपढ़ो.trap_nr = (regs->cp0_cause >> 2) & 0x1f;
	अगर (get_isa16_mode(regs->cp0_epc)) अणु
		अगर (__get_inst16(&instr[0], (u16 *)(epc + 0), user) ||
		    __get_inst16(&instr[1], (u16 *)(epc + 2), user))
			जाओ out_sigsegv;
		opcode = (instr[0] << 16) | instr[1];
		/* Immediate versions करोn't provide a code.  */
		अगर (!(opcode & OPCODE))
			tcode = (opcode >> 12) & ((1 << 4) - 1);
	पूर्ण अन्यथा अणु
		अगर (__get_inst32(&opcode, (u32 *)epc, user))
			जाओ out_sigsegv;
		/* Immediate versions करोn't provide a code.  */
		अगर (!(opcode & OPCODE))
			tcode = (opcode >> 6) & ((1 << 10) - 1);
	पूर्ण

	करो_trap_or_bp(regs, tcode, 0, "Trap");

out:
	exception_निकास(prev_state);
	वापस;

out_sigsegv:
	क्रमce_sig(संक_अंश);
	जाओ out;
पूर्ण

यंत्रlinkage व्योम करो_ri(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक __user *epc = (अचिन्हित पूर्णांक __user *)exception_epc(regs);
	अचिन्हित दीर्घ old_epc = regs->cp0_epc;
	अचिन्हित दीर्घ old31 = regs->regs[31];
	क्रमागत ctx_state prev_state;
	अचिन्हित पूर्णांक opcode = 0;
	पूर्णांक status = -1;

	/*
	 * Aव्योम any kernel code. Just emulate the R2 inकाष्ठाion
	 * as quickly as possible.
	 */
	अगर (mipsr2_emulation && cpu_has_mips_r6 &&
	    likely(user_mode(regs)) &&
	    likely(get_user(opcode, epc) >= 0)) अणु
		अचिन्हित दीर्घ fcr31 = 0;

		status = mipsr2_decoder(regs, opcode, &fcr31);
		चयन (status) अणु
		हाल 0:
		हाल SIGEMT:
			वापस;
		हाल संक_अवैध:
			जाओ no_r2_instr;
		शेष:
			process_fpemu_वापस(status,
					     &current->thपढ़ो.cp0_baduaddr,
					     fcr31);
			वापस;
		पूर्ण
	पूर्ण

no_r2_instr:

	prev_state = exception_enter();
	current->thपढ़ो.trap_nr = (regs->cp0_cause >> 2) & 0x1f;

	अगर (notअगरy_die(DIE_RI, "RI Fault", regs, 0, current->thपढ़ो.trap_nr,
		       संक_अवैध) == NOTIFY_STOP)
		जाओ out;

	die_अगर_kernel("Reserved instruction in kernel code", regs);

	अगर (unlikely(compute_वापस_epc(regs) < 0))
		जाओ out;

	अगर (!get_isa16_mode(regs->cp0_epc)) अणु
		अगर (unlikely(get_user(opcode, epc) < 0))
			status = संक_अंश;

		अगर (!cpu_has_llsc && status < 0)
			status = simulate_llsc(regs, opcode);

		अगर (status < 0)
			status = simulate_rdhwr_normal(regs, opcode);

		अगर (status < 0)
			status = simulate_sync(regs, opcode);

		अगर (status < 0)
			status = simulate_fp(regs, opcode, old_epc, old31);

#अगर_घोषित CONFIG_CPU_LOONGSON3_CPUCFG_EMULATION
		अगर (status < 0)
			status = simulate_loongson3_cpucfg(regs, opcode);
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (cpu_has_mmips) अणु
		अचिन्हित लघु mmop[2] = अणु 0 पूर्ण;

		अगर (unlikely(get_user(mmop[0], (u16 __user *)epc + 0) < 0))
			status = संक_अंश;
		अगर (unlikely(get_user(mmop[1], (u16 __user *)epc + 1) < 0))
			status = संक_अंश;
		opcode = mmop[0];
		opcode = (opcode << 16) | mmop[1];

		अगर (status < 0)
			status = simulate_rdhwr_mm(regs, opcode);
	पूर्ण

	अगर (status < 0)
		status = संक_अवैध;

	अगर (unlikely(status > 0)) अणु
		regs->cp0_epc = old_epc;		/* Unकरो skip-over.  */
		regs->regs[31] = old31;
		क्रमce_sig(status);
	पूर्ण

out:
	exception_निकास(prev_state);
पूर्ण

/*
 * No lock; only written during early bootup by CPU 0.
 */
अटल RAW_NOTIFIER_HEAD(cu2_chain);

पूर्णांक __ref रेजिस्टर_cu2_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस raw_notअगरier_chain_रेजिस्टर(&cu2_chain, nb);
पूर्ण

पूर्णांक cu2_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस raw_notअगरier_call_chain(&cu2_chain, val, v);
पूर्ण

अटल पूर्णांक शेष_cu2_call(काष्ठा notअगरier_block *nfb, अचिन्हित दीर्घ action,
	व्योम *data)
अणु
	काष्ठा pt_regs *regs = data;

	die_अगर_kernel("COP2: Unhandled kernel unaligned access or invalid "
			      "instruction", regs);
	क्रमce_sig(संक_अवैध);

	वापस NOTIFY_OK;
पूर्ण

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT

अटल पूर्णांक enable_restore_fp_context(पूर्णांक msa)
अणु
	पूर्णांक err, was_fpu_owner, prior_msa;
	bool first_fp;

	/* Initialize context अगर it hasn't been used alपढ़ोy */
	first_fp = init_fp_ctx(current);

	अगर (first_fp) अणु
		preempt_disable();
		err = own_fpu_inatomic(1);
		अगर (msa && !err) अणु
			enable_msa();
			/*
			 * with MSA enabled, userspace can see MSACSR
			 * and MSA regs, but the values in them are from
			 * other task beक्रमe current task, restore them
			 * from saved fp/msa context
			 */
			ग_लिखो_msa_csr(current->thपढ़ो.fpu.msacsr);
			/*
			 * own_fpu_inatomic(1) just restore low 64bit,
			 * fix the high 64bit
			 */
			init_msa_upper();
			set_thपढ़ो_flag(TIF_USEDMSA);
			set_thपढ़ो_flag(TIF_MSA_CTX_LIVE);
		पूर्ण
		preempt_enable();
		वापस err;
	पूर्ण

	/*
	 * This task has क्रमmerly used the FP context.
	 *
	 * If this thपढ़ो has no live MSA vector context then we can simply
	 * restore the scalar FP context. If it has live MSA vector context
	 * (that is, it has or may have used MSA since last perक्रमming a
	 * function call) then we'll need to restore the vector context. This
	 * applies even अगर we're currently only executing a scalar FP
	 * inकाष्ठाion. This is because अगर we were to later execute an MSA
	 * inकाष्ठाion then we'd either have to:
	 *
	 *  - Restore the vector context & clobber any रेजिस्टरs modअगरied by
	 *    scalar FP inकाष्ठाions between now & then.
	 *
	 * or
	 *
	 *  - Not restore the vector context & lose the most signअगरicant bits
	 *    of all vector रेजिस्टरs.
	 *
	 * Neither of those options is acceptable. We cannot restore the least
	 * signअगरicant bits of the रेजिस्टरs now & only restore the most
	 * signअगरicant bits later because the most signअगरicant bits of any
	 * vector रेजिस्टरs whose aliased FP रेजिस्टर is modअगरied now will have
	 * been zeroed. We'd have no way to know that when restoring the vector
	 * context & thus may load an outdated value क्रम the most signअगरicant
	 * bits of a vector रेजिस्टर.
	 */
	अगर (!msa && !thपढ़ो_msa_context_live())
		वापस own_fpu(1);

	/*
	 * This task is using or has previously used MSA. Thus we require
	 * that Status.FR == 1.
	 */
	preempt_disable();
	was_fpu_owner = is_fpu_owner();
	err = own_fpu_inatomic(0);
	अगर (err)
		जाओ out;

	enable_msa();
	ग_लिखो_msa_csr(current->thपढ़ो.fpu.msacsr);
	set_thपढ़ो_flag(TIF_USEDMSA);

	/*
	 * If this is the first समय that the task is using MSA and it has
	 * previously used scalar FP in this समय slice then we alपढ़ोy nave
	 * FP context which we shouldn't clobber. We करो however need to clear
	 * the upper 64b of each vector रेजिस्टर so that this task has no
	 * opportunity to see data left behind by another.
	 */
	prior_msa = test_and_set_thपढ़ो_flag(TIF_MSA_CTX_LIVE);
	अगर (!prior_msa && was_fpu_owner) अणु
		init_msa_upper();

		जाओ out;
	पूर्ण

	अगर (!prior_msa) अणु
		/*
		 * Restore the least signअगरicant 64b of each vector रेजिस्टर
		 * from the existing scalar FP context.
		 */
		_restore_fp(current);

		/*
		 * The task has not क्रमmerly used MSA, so clear the upper 64b
		 * of each vector रेजिस्टर such that it cannot see data left
		 * behind by another task.
		 */
		init_msa_upper();
	पूर्ण अन्यथा अणु
		/* We need to restore the vector context. */
		restore_msa(current);

		/* Restore the scalar FP control & status रेजिस्टर */
		अगर (!was_fpu_owner)
			ग_लिखो_32bit_cp1_रेजिस्टर(CP1_STATUS,
						 current->thपढ़ो.fpu.fcr31);
	पूर्ण

out:
	preempt_enable();

	वापस 0;
पूर्ण

#अन्यथा /* !CONFIG_MIPS_FP_SUPPORT */

अटल पूर्णांक enable_restore_fp_context(पूर्णांक msa)
अणु
	वापस संक_अवैध;
पूर्ण

#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */

यंत्रlinkage व्योम करो_cpu(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state;
	अचिन्हित पूर्णांक __user *epc;
	अचिन्हित दीर्घ old_epc, old31;
	अचिन्हित पूर्णांक opcode;
	अचिन्हित पूर्णांक cpid;
	पूर्णांक status;

	prev_state = exception_enter();
	cpid = (regs->cp0_cause >> CAUSEB_CE) & 3;

	अगर (cpid != 2)
		die_अगर_kernel("do_cpu invoked from kernel context!", regs);

	चयन (cpid) अणु
	हाल 0:
		epc = (अचिन्हित पूर्णांक __user *)exception_epc(regs);
		old_epc = regs->cp0_epc;
		old31 = regs->regs[31];
		opcode = 0;
		status = -1;

		अगर (unlikely(compute_वापस_epc(regs) < 0))
			अवरोध;

		अगर (!get_isa16_mode(regs->cp0_epc)) अणु
			अगर (unlikely(get_user(opcode, epc) < 0))
				status = संक_अंश;

			अगर (!cpu_has_llsc && status < 0)
				status = simulate_llsc(regs, opcode);
		पूर्ण

		अगर (status < 0)
			status = संक_अवैध;

		अगर (unlikely(status > 0)) अणु
			regs->cp0_epc = old_epc;	/* Unकरो skip-over.  */
			regs->regs[31] = old31;
			क्रमce_sig(status);
		पूर्ण

		अवरोध;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	हाल 3:
		/*
		 * The COP3 opcode space and consequently the CP0.Status.CU3
		 * bit and the CP0.Cause.CE=3 encoding have been हटाओd as
		 * of the MIPS III ISA.  From the MIPS IV and MIPS32r2 ISAs
		 * up the space has been reused क्रम COP1X inकाष्ठाions, that
		 * are enabled by the CP0.Status.CU1 bit and consequently
		 * use the CP0.Cause.CE=1 encoding क्रम Coprocessor Unusable
		 * exceptions.  Some FPU-less processors that implement one
		 * of these ISAs however use this code erroneously क्रम COP1X
		 * inकाष्ठाions.  Thereक्रमe we redirect this trap to the FP
		 * emulator too.
		 */
		अगर (raw_cpu_has_fpu || !cpu_has_mips_4_5_64_r2_r6) अणु
			क्रमce_sig(संक_अवैध);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 1: अणु
		व्योम __user *fault_addr;
		अचिन्हित दीर्घ fcr31;
		पूर्णांक err, sig;

		err = enable_restore_fp_context(0);

		अगर (raw_cpu_has_fpu && !err)
			अवरोध;

		sig = fpu_emulator_cop1Handler(regs, &current->thपढ़ो.fpu, 0,
					       &fault_addr);

		/*
		 * We can't allow the emulated inकाष्ठाion to leave
		 * any enabled Cause bits set in $fcr31.
		 */
		fcr31 = mask_fcr31_x(current->thपढ़ो.fpu.fcr31);
		current->thपढ़ो.fpu.fcr31 &= ~fcr31;

		/* Send a संकेत अगर required.  */
		अगर (!process_fpemu_वापस(sig, fault_addr, fcr31) && !err)
			mt_ase_fp_affinity();

		अवरोध;
	पूर्ण
#अन्यथा /* CONFIG_MIPS_FP_SUPPORT */
	हाल 1:
	हाल 3:
		क्रमce_sig(संक_अवैध);
		अवरोध;
#पूर्ण_अगर /* CONFIG_MIPS_FP_SUPPORT */

	हाल 2:
		raw_notअगरier_call_chain(&cu2_chain, CU2_EXCEPTION, regs);
		अवरोध;
	पूर्ण

	exception_निकास(prev_state);
पूर्ण

यंत्रlinkage व्योम करो_msa_fpe(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक msacsr)
अणु
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	current->thपढ़ो.trap_nr = (regs->cp0_cause >> 2) & 0x1f;
	अगर (notअगरy_die(DIE_MSAFP, "MSA FP exception", regs, 0,
		       current->thपढ़ो.trap_nr, संक_भ_त्रुटि) == NOTIFY_STOP)
		जाओ out;

	/* Clear MSACSR.Cause beक्रमe enabling पूर्णांकerrupts */
	ग_लिखो_msa_csr(msacsr & ~MSA_CSR_CAUSEF);
	local_irq_enable();

	die_अगर_kernel("do_msa_fpe invoked from kernel context!", regs);
	क्रमce_sig(संक_भ_त्रुटि);
out:
	exception_निकास(prev_state);
पूर्ण

यंत्रlinkage व्योम करो_msa(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state;
	पूर्णांक err;

	prev_state = exception_enter();

	अगर (!cpu_has_msa || test_thपढ़ो_flag(TIF_32BIT_FPREGS)) अणु
		क्रमce_sig(संक_अवैध);
		जाओ out;
	पूर्ण

	die_अगर_kernel("do_msa invoked from kernel context!", regs);

	err = enable_restore_fp_context(1);
	अगर (err)
		क्रमce_sig(संक_अवैध);
out:
	exception_निकास(prev_state);
पूर्ण

यंत्रlinkage व्योम करो_mdmx(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	क्रमce_sig(संक_अवैध);
	exception_निकास(prev_state);
पूर्ण

/*
 * Called with पूर्णांकerrupts disabled.
 */
यंत्रlinkage व्योम करो_watch(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	/*
	 * Clear WP (bit 22) bit of cause रेजिस्टर so we करोn't loop
	 * क्रमever.
	 */
	clear_c0_cause(CAUSEF_WP);

	/*
	 * If the current thपढ़ो has the watch रेजिस्टरs loaded, save
	 * their values and send SIGTRAP.  Otherwise another thपढ़ो
	 * left the रेजिस्टरs set, clear them and जारी.
	 */
	अगर (test_tsk_thपढ़ो_flag(current, TIF_LOAD_WATCH)) अणु
		mips_पढ़ो_watch_रेजिस्टरs();
		local_irq_enable();
		क्रमce_sig_fault(SIGTRAP, TRAP_HWBKPT, शून्य);
	पूर्ण अन्यथा अणु
		mips_clear_watch_रेजिस्टरs();
		local_irq_enable();
	पूर्ण
	exception_निकास(prev_state);
पूर्ण

यंत्रlinkage व्योम करो_mcheck(काष्ठा pt_regs *regs)
अणु
	पूर्णांक multi_match = regs->cp0_status & ST0_TS;
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();
	show_regs(regs);

	अगर (multi_match) अणु
		dump_tlb_regs();
		pr_info("\n");
		dump_tlb_all();
	पूर्ण

	show_code((व्योम *)regs->cp0_epc, user_mode(regs));

	/*
	 * Some chips may have other causes of machine check (e.g. SB1
	 * graduation समयr)
	 */
	panic("Caught Machine Check exception - %scaused by multiple "
	      "matching entries in the TLB.",
	      (multi_match) ? "" : "not ");
पूर्ण

यंत्रlinkage व्योम करो_mt(काष्ठा pt_regs *regs)
अणु
	पूर्णांक subcode;

	subcode = (पढ़ो_vpe_c0_vpecontrol() & VPECONTROL_EXCPT)
			>> VPECONTROL_EXCPT_SHIFT;
	चयन (subcode) अणु
	हाल 0:
		prपूर्णांकk(KERN_DEBUG "Thread Underflow\n");
		अवरोध;
	हाल 1:
		prपूर्णांकk(KERN_DEBUG "Thread Overflow\n");
		अवरोध;
	हाल 2:
		prपूर्णांकk(KERN_DEBUG "Invalid YIELD Qualifier\n");
		अवरोध;
	हाल 3:
		prपूर्णांकk(KERN_DEBUG "Gating Storage Exception\n");
		अवरोध;
	हाल 4:
		prपूर्णांकk(KERN_DEBUG "YIELD Scheduler Exception\n");
		अवरोध;
	हाल 5:
		prपूर्णांकk(KERN_DEBUG "Gating Storage Scheduler Exception\n");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_DEBUG "*** UNKNOWN THREAD EXCEPTION %d ***\n",
			subcode);
		अवरोध;
	पूर्ण
	die_अगर_kernel("MIPS MT Thread exception in kernel", regs);

	क्रमce_sig(संक_अवैध);
पूर्ण


यंत्रlinkage व्योम करो_dsp(काष्ठा pt_regs *regs)
अणु
	अगर (cpu_has_dsp)
		panic("Unexpected DSP exception");

	क्रमce_sig(संक_अवैध);
पूर्ण

यंत्रlinkage व्योम करो_reserved(काष्ठा pt_regs *regs)
अणु
	/*
	 * Game over - no way to handle this अगर it ever occurs.	 Most probably
	 * caused by a new unknown cpu type or after another deadly
	 * hard/software error.
	 */
	show_regs(regs);
	panic("Caught reserved exception %ld - should not happen.",
	      (regs->cp0_cause & 0x7f) >> 2);
पूर्ण

अटल पूर्णांक __initdata l1parity = 1;
अटल पूर्णांक __init nol1parity(अक्षर *s)
अणु
	l1parity = 0;
	वापस 1;
पूर्ण
__setup("nol1par", nol1parity);
अटल पूर्णांक __initdata l2parity = 1;
अटल पूर्णांक __init nol2parity(अक्षर *s)
अणु
	l2parity = 0;
	वापस 1;
पूर्ण
__setup("nol2par", nol2parity);

/*
 * Some MIPS CPUs can enable/disable क्रम cache parity detection, but करो
 * it dअगरferent ways.
 */
अटल अंतरभूत __init व्योम parity_protection_init(व्योम)
अणु
#घोषणा ERRCTL_PE	0x80000000
#घोषणा ERRCTL_L2P	0x00800000

	अगर (mips_cm_revision() >= CM_REV_CM3) अणु
		uदीर्घ gcr_ectl, cp0_ectl;

		/*
		 * With CM3 प्रणालीs we need to ensure that the L1 & L2
		 * parity enables are set to the same value, since this
		 * is presumed by the hardware engineers.
		 *
		 * If the user disabled either of L1 or L2 ECC checking,
		 * disable both.
		 */
		l1parity &= l2parity;
		l2parity &= l1parity;

		/* Probe L1 ECC support */
		cp0_ectl = पढ़ो_c0_ecc();
		ग_लिखो_c0_ecc(cp0_ectl | ERRCTL_PE);
		back_to_back_c0_hazard();
		cp0_ectl = पढ़ो_c0_ecc();

		/* Probe L2 ECC support */
		gcr_ectl = पढ़ो_gcr_err_control();

		अगर (!(gcr_ectl & CM_GCR_ERR_CONTROL_L2_ECC_SUPPORT) ||
		    !(cp0_ectl & ERRCTL_PE)) अणु
			/*
			 * One of L1 or L2 ECC checking isn't supported,
			 * so we cannot enable either.
			 */
			l1parity = l2parity = 0;
		पूर्ण

		/* Configure L1 ECC checking */
		अगर (l1parity)
			cp0_ectl |= ERRCTL_PE;
		अन्यथा
			cp0_ectl &= ~ERRCTL_PE;
		ग_लिखो_c0_ecc(cp0_ectl);
		back_to_back_c0_hazard();
		WARN_ON(!!(पढ़ो_c0_ecc() & ERRCTL_PE) != l1parity);

		/* Configure L2 ECC checking */
		अगर (l2parity)
			gcr_ectl |= CM_GCR_ERR_CONTROL_L2_ECC_EN;
		अन्यथा
			gcr_ectl &= ~CM_GCR_ERR_CONTROL_L2_ECC_EN;
		ग_लिखो_gcr_err_control(gcr_ectl);
		gcr_ectl = पढ़ो_gcr_err_control();
		gcr_ectl &= CM_GCR_ERR_CONTROL_L2_ECC_EN;
		WARN_ON(!!gcr_ectl != l2parity);

		pr_info("Cache parity protection %sabled\n",
			l1parity ? "en" : "dis");
		वापस;
	पूर्ण

	चयन (current_cpu_type()) अणु
	हाल CPU_24K:
	हाल CPU_34K:
	हाल CPU_74K:
	हाल CPU_1004K:
	हाल CPU_1074K:
	हाल CPU_INTERAPTIV:
	हाल CPU_PROAPTIV:
	हाल CPU_P5600:
	हाल CPU_QEMU_GENERIC:
	हाल CPU_P6600:
		अणु
			अचिन्हित दीर्घ errctl;
			अचिन्हित पूर्णांक l1parity_present, l2parity_present;

			errctl = पढ़ो_c0_ecc();
			errctl &= ~(ERRCTL_PE|ERRCTL_L2P);

			/* probe L1 parity support */
			ग_लिखो_c0_ecc(errctl | ERRCTL_PE);
			back_to_back_c0_hazard();
			l1parity_present = (पढ़ो_c0_ecc() & ERRCTL_PE);

			/* probe L2 parity support */
			ग_लिखो_c0_ecc(errctl|ERRCTL_L2P);
			back_to_back_c0_hazard();
			l2parity_present = (पढ़ो_c0_ecc() & ERRCTL_L2P);

			अगर (l1parity_present && l2parity_present) अणु
				अगर (l1parity)
					errctl |= ERRCTL_PE;
				अगर (l1parity ^ l2parity)
					errctl |= ERRCTL_L2P;
			पूर्ण अन्यथा अगर (l1parity_present) अणु
				अगर (l1parity)
					errctl |= ERRCTL_PE;
			पूर्ण अन्यथा अगर (l2parity_present) अणु
				अगर (l2parity)
					errctl |= ERRCTL_L2P;
			पूर्ण अन्यथा अणु
				/* No parity available */
			पूर्ण

			prपूर्णांकk(KERN_INFO "Writing ErrCtl register=%08lx\n", errctl);

			ग_लिखो_c0_ecc(errctl);
			back_to_back_c0_hazard();
			errctl = पढ़ो_c0_ecc();
			prपूर्णांकk(KERN_INFO "Readback ErrCtl register=%08lx\n", errctl);

			अगर (l1parity_present)
				prपूर्णांकk(KERN_INFO "Cache parity protection %sabled\n",
				       (errctl & ERRCTL_PE) ? "en" : "dis");

			अगर (l2parity_present) अणु
				अगर (l1parity_present && l1parity)
					errctl ^= ERRCTL_L2P;
				prपूर्णांकk(KERN_INFO "L2 cache parity protection %sabled\n",
				       (errctl & ERRCTL_L2P) ? "en" : "dis");
			पूर्ण
		पूर्ण
		अवरोध;

	हाल CPU_5KC:
	हाल CPU_5KE:
	हाल CPU_LOONGSON32:
		ग_लिखो_c0_ecc(0x80000000);
		back_to_back_c0_hazard();
		/* Set the PE bit (bit 31) in the c0_errctl रेजिस्टर. */
		prपूर्णांकk(KERN_INFO "Cache parity protection %sabled\n",
		       (पढ़ो_c0_ecc() & 0x80000000) ? "en" : "dis");
		अवरोध;
	हाल CPU_20KC:
	हाल CPU_25KF:
		/* Clear the DE bit (bit 16) in the c0_status रेजिस्टर. */
		prपूर्णांकk(KERN_INFO "Enable cache parity protection for "
		       "MIPS 20KC/25KF CPUs.\n");
		clear_c0_status(ST0_DE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

यंत्रlinkage व्योम cache_parity_error(व्योम)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	अचिन्हित पूर्णांक reg_val;

	/* For the moment, report the problem and hang. */
	prपूर्णांकk("Cache error exception:\n");
	prपूर्णांकk("cp0_errorepc == %0*lx\n", field, पढ़ो_c0_errorepc());
	reg_val = पढ़ो_c0_cacheerr();
	prपूर्णांकk("c0_cacheerr == %08x\n", reg_val);

	prपूर्णांकk("Decoded c0_cacheerr: %s cache fault in %s reference.\n",
	       reg_val & (1<<30) ? "secondary" : "primary",
	       reg_val & (1<<31) ? "data" : "insn");
	अगर ((cpu_has_mips_r2_r6) &&
	    ((current_cpu_data.processor_id & 0xff0000) == PRID_COMP_MIPS)) अणु
		pr_err("Error bits: %s%s%s%s%s%s%s%s\n",
			reg_val & (1<<29) ? "ED " : "",
			reg_val & (1<<28) ? "ET " : "",
			reg_val & (1<<27) ? "ES " : "",
			reg_val & (1<<26) ? "EE " : "",
			reg_val & (1<<25) ? "EB " : "",
			reg_val & (1<<24) ? "EI " : "",
			reg_val & (1<<23) ? "E1 " : "",
			reg_val & (1<<22) ? "E0 " : "");
	पूर्ण अन्यथा अणु
		pr_err("Error bits: %s%s%s%s%s%s%s\n",
			reg_val & (1<<29) ? "ED " : "",
			reg_val & (1<<28) ? "ET " : "",
			reg_val & (1<<26) ? "EE " : "",
			reg_val & (1<<25) ? "EB " : "",
			reg_val & (1<<24) ? "EI " : "",
			reg_val & (1<<23) ? "E1 " : "",
			reg_val & (1<<22) ? "E0 " : "");
	पूर्ण
	prपूर्णांकk("IDX: 0x%08x\n", reg_val & ((1<<22)-1));

#अगर defined(CONFIG_CPU_MIPS32) || defined(CONFIG_CPU_MIPS64)
	अगर (reg_val & (1<<22))
		prपूर्णांकk("DErrAddr0: 0x%0*lx\n", field, पढ़ो_c0_derraddr0());

	अगर (reg_val & (1<<23))
		prपूर्णांकk("DErrAddr1: 0x%0*lx\n", field, पढ़ो_c0_derraddr1());
#पूर्ण_अगर

	panic("Can't handle the cache error!");
पूर्ण

यंत्रlinkage व्योम करो_ftlb(व्योम)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	अचिन्हित पूर्णांक reg_val;

	/* For the moment, report the problem and hang. */
	अगर ((cpu_has_mips_r2_r6) &&
	    (((current_cpu_data.processor_id & 0xff0000) == PRID_COMP_MIPS) ||
	    ((current_cpu_data.processor_id & 0xff0000) == PRID_COMP_LOONGSON))) अणु
		pr_err("FTLB error exception, cp0_ecc=0x%08x:\n",
		       पढ़ो_c0_ecc());
		pr_err("cp0_errorepc == %0*lx\n", field, पढ़ो_c0_errorepc());
		reg_val = पढ़ो_c0_cacheerr();
		pr_err("c0_cacheerr == %08x\n", reg_val);

		अगर ((reg_val & 0xc0000000) == 0xc0000000) अणु
			pr_err("Decoded c0_cacheerr: FTLB parity error\n");
		पूर्ण अन्यथा अणु
			pr_err("Decoded c0_cacheerr: %s cache fault in %s reference.\n",
			       reg_val & (1<<30) ? "secondary" : "primary",
			       reg_val & (1<<31) ? "data" : "insn");
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("FTLB error exception\n");
	पूर्ण
	/* Just prपूर्णांक the cacheerr bits क्रम now */
	cache_parity_error();
पूर्ण

यंत्रlinkage व्योम करो_gsexc(काष्ठा pt_regs *regs, u32 diag1)
अणु
	u32 exccode = (diag1 & LOONGSON_DIAG1_EXCCODE) >>
			LOONGSON_DIAG1_EXCCODE_SHIFT;
	क्रमागत ctx_state prev_state;

	prev_state = exception_enter();

	चयन (exccode) अणु
	हाल 0x08:
		/* Unकरोcumented exception, will trigger on certain
		 * also-unकरोcumented inकाष्ठाions accessible from userspace.
		 * Processor state is not otherwise corrupted, but currently
		 * we करोn't know how to proceed. Maybe there is some
		 * unकरोcumented control flag to enable the inकाष्ठाions?
		 */
		क्रमce_sig(संक_अवैध);
		अवरोध;

	शेष:
		/* None of the other exceptions, करोcumented or not, have
		 * further details given; none are encountered in the wild
		 * either. Panic in हाल some of them turn out to be fatal.
		 */
		show_regs(regs);
		panic("Unhandled Loongson exception - GSCause = %08x", diag1);
	पूर्ण

	exception_निकास(prev_state);
पूर्ण

/*
 * SDBBP EJTAG debug exception handler.
 * We skip the inकाष्ठाion and वापस to the next inकाष्ठाion.
 */
व्योम ejtag_exception_handler(काष्ठा pt_regs *regs)
अणु
	स्थिर पूर्णांक field = 2 * माप(अचिन्हित दीर्घ);
	अचिन्हित दीर्घ depc, old_epc, old_ra;
	अचिन्हित पूर्णांक debug;

	prपूर्णांकk(KERN_DEBUG "SDBBP EJTAG debug exception - not handled yet, just ignored!\n");
	depc = पढ़ो_c0_depc();
	debug = पढ़ो_c0_debug();
	prपूर्णांकk(KERN_DEBUG "c0_depc = %0*lx, DEBUG = %08x\n", field, depc, debug);
	अगर (debug & 0x80000000) अणु
		/*
		 * In branch delay slot.
		 * We cheat a little bit here and use EPC to calculate the
		 * debug वापस address (DEPC). EPC is restored after the
		 * calculation.
		 */
		old_epc = regs->cp0_epc;
		old_ra = regs->regs[31];
		regs->cp0_epc = depc;
		compute_वापस_epc(regs);
		depc = regs->cp0_epc;
		regs->cp0_epc = old_epc;
		regs->regs[31] = old_ra;
	पूर्ण अन्यथा
		depc += 4;
	ग_लिखो_c0_depc(depc);

#अगर 0
	prपूर्णांकk(KERN_DEBUG "\n\n----- Enable EJTAG single stepping ----\n\n");
	ग_लिखो_c0_debug(debug | 0x100);
#पूर्ण_अगर
पूर्ण

/*
 * NMI exception handler.
 * No lock; only written during early bootup by CPU 0.
 */
अटल RAW_NOTIFIER_HEAD(nmi_chain);

पूर्णांक रेजिस्टर_nmi_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस raw_notअगरier_chain_रेजिस्टर(&nmi_chain, nb);
पूर्ण

व्योम __noवापस nmi_exception_handler(काष्ठा pt_regs *regs)
अणु
	अक्षर str[100];

	nmi_enter();
	raw_notअगरier_call_chain(&nmi_chain, 0, regs);
	bust_spinlocks(1);
	snम_लिखो(str, 100, "CPU%d NMI taken, CP0_EPC=%lx\n",
		 smp_processor_id(), regs->cp0_epc);
	regs->cp0_epc = पढ़ो_c0_errorepc();
	die(str, regs);
	nmi_निकास();
पूर्ण

अचिन्हित दीर्घ ebase;
EXPORT_SYMBOL_GPL(ebase);
अचिन्हित दीर्घ exception_handlers[32];
अचिन्हित दीर्घ vi_handlers[64];

व्योम reserve_exception_space(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	memblock_reserve(addr, size);
पूर्ण

व्योम __init *set_except_vector(पूर्णांक n, व्योम *addr)
अणु
	अचिन्हित दीर्घ handler = (अचिन्हित दीर्घ) addr;
	अचिन्हित दीर्घ old_handler;

#अगर_घोषित CONFIG_CPU_MICROMIPS
	/*
	 * Only the TLB handlers are cache aligned with an even
	 * address. All other handlers are on an odd address and
	 * require no modअगरication. Otherwise, MIPS32 mode will
	 * be entered when handling any TLB exceptions. That
	 * would be bad...since we must stay in microMIPS mode.
	 */
	अगर (!(handler & 0x1))
		handler |= 1;
#पूर्ण_अगर
	old_handler = xchg(&exception_handlers[n], handler);

	अगर (n == 0 && cpu_has_भागec) अणु
#अगर_घोषित CONFIG_CPU_MICROMIPS
		अचिन्हित दीर्घ jump_mask = ~((1 << 27) - 1);
#अन्यथा
		अचिन्हित दीर्घ jump_mask = ~((1 << 28) - 1);
#पूर्ण_अगर
		u32 *buf = (u32 *)(ebase + 0x200);
		अचिन्हित पूर्णांक k0 = 26;
		अगर ((handler & jump_mask) == ((ebase + 0x200) & jump_mask)) अणु
			uयंत्र_i_j(&buf, handler & ~jump_mask);
			uयंत्र_i_nop(&buf);
		पूर्ण अन्यथा अणु
			UASM_i_LA(&buf, k0, handler);
			uयंत्र_i_jr(&buf, k0);
			uयंत्र_i_nop(&buf);
		पूर्ण
		local_flush_icache_range(ebase + 0x200, (अचिन्हित दीर्घ)buf);
	पूर्ण
	वापस (व्योम *)old_handler;
पूर्ण

अटल व्योम करो_शेष_vi(व्योम)
अणु
	show_regs(get_irq_regs());
	panic("Caught unexpected vectored interrupt.");
पूर्ण

अटल व्योम *set_vi_srs_handler(पूर्णांक n, vi_handler_t addr, पूर्णांक srs)
अणु
	अचिन्हित दीर्घ handler;
	अचिन्हित दीर्घ old_handler = vi_handlers[n];
	पूर्णांक srssets = current_cpu_data.srsets;
	u16 *h;
	अचिन्हित अक्षर *b;

	BUG_ON(!cpu_has_veic && !cpu_has_vपूर्णांक);

	अगर (addr == शून्य) अणु
		handler = (अचिन्हित दीर्घ) करो_शेष_vi;
		srs = 0;
	पूर्ण अन्यथा
		handler = (अचिन्हित दीर्घ) addr;
	vi_handlers[n] = handler;

	b = (अचिन्हित अक्षर *)(ebase + 0x200 + n*VECTORSPACING);

	अगर (srs >= srssets)
		panic("Shadow register set %d not supported", srs);

	अगर (cpu_has_veic) अणु
		अगर (board_bind_eic_पूर्णांकerrupt)
			board_bind_eic_पूर्णांकerrupt(n, srs);
	पूर्ण अन्यथा अगर (cpu_has_vपूर्णांक) अणु
		/* SRSMap is only defined अगर shaकरोw sets are implemented */
		अगर (srssets > 1)
			change_c0_srsmap(0xf << n*4, srs << n*4);
	पूर्ण

	अगर (srs == 0) अणु
		/*
		 * If no shaकरोw set is selected then use the शेष handler
		 * that करोes normal रेजिस्टर saving and standard पूर्णांकerrupt निकास
		 */
		बाह्य अक्षर except_vec_vi, except_vec_vi_lui;
		बाह्य अक्षर except_vec_vi_ori, except_vec_vi_end;
		बाह्य अक्षर rollback_except_vec_vi;
		अक्षर *vec_start = using_rollback_handler() ?
			&rollback_except_vec_vi : &except_vec_vi;
#अगर defined(CONFIG_CPU_MICROMIPS) || defined(CONFIG_CPU_BIG_ENDIAN)
		स्थिर पूर्णांक lui_offset = &except_vec_vi_lui - vec_start + 2;
		स्थिर पूर्णांक ori_offset = &except_vec_vi_ori - vec_start + 2;
#अन्यथा
		स्थिर पूर्णांक lui_offset = &except_vec_vi_lui - vec_start;
		स्थिर पूर्णांक ori_offset = &except_vec_vi_ori - vec_start;
#पूर्ण_अगर
		स्थिर पूर्णांक handler_len = &except_vec_vi_end - vec_start;

		अगर (handler_len > VECTORSPACING) अणु
			/*
			 * Sigh... panicing won't help as the console
			 * is probably not configured :(
			 */
			panic("VECTORSPACING too small");
		पूर्ण

		set_handler(((अचिन्हित दीर्घ)b - ebase), vec_start,
#अगर_घोषित CONFIG_CPU_MICROMIPS
				(handler_len - 1));
#अन्यथा
				handler_len);
#पूर्ण_अगर
		h = (u16 *)(b + lui_offset);
		*h = (handler >> 16) & 0xffff;
		h = (u16 *)(b + ori_offset);
		*h = (handler & 0xffff);
		local_flush_icache_range((अचिन्हित दीर्घ)b,
					 (अचिन्हित दीर्घ)(b+handler_len));
	पूर्ण
	अन्यथा अणु
		/*
		 * In other हालs jump directly to the पूर्णांकerrupt handler. It
		 * is the handler's responsibility to save रेजिस्टरs अगर required
		 * (eg hi/lo) and वापस from the exception using "eret".
		 */
		u32 insn;

		h = (u16 *)b;
		/* j handler */
#अगर_घोषित CONFIG_CPU_MICROMIPS
		insn = 0xd4000000 | (((u32)handler & 0x07ffffff) >> 1);
#अन्यथा
		insn = 0x08000000 | (((u32)handler & 0x0fffffff) >> 2);
#पूर्ण_अगर
		h[0] = (insn >> 16) & 0xffff;
		h[1] = insn & 0xffff;
		h[2] = 0;
		h[3] = 0;
		local_flush_icache_range((अचिन्हित दीर्घ)b,
					 (अचिन्हित दीर्घ)(b+8));
	पूर्ण

	वापस (व्योम *)old_handler;
पूर्ण

व्योम *set_vi_handler(पूर्णांक n, vi_handler_t addr)
अणु
	वापस set_vi_srs_handler(n, addr, 0);
पूर्ण

बाह्य व्योम tlb_init(व्योम);

/*
 * Timer पूर्णांकerrupt
 */
पूर्णांक cp0_compare_irq;
EXPORT_SYMBOL_GPL(cp0_compare_irq);
पूर्णांक cp0_compare_irq_shअगरt;

/*
 * Perक्रमmance counter IRQ or -1 अगर shared with समयr
 */
पूर्णांक cp0_perfcount_irq;
EXPORT_SYMBOL_GPL(cp0_perfcount_irq);

/*
 * Fast debug channel IRQ or -1 अगर not present
 */
पूर्णांक cp0_fdc_irq;
EXPORT_SYMBOL_GPL(cp0_fdc_irq);

अटल पूर्णांक noulri;

अटल पूर्णांक __init ulri_disable(अक्षर *s)
अणु
	pr_info("Disabling ulri\n");
	noulri = 1;

	वापस 1;
पूर्ण
__setup("noulri", ulri_disable);

/* configure STATUS रेजिस्टर */
अटल व्योम configure_status(व्योम)
अणु
	/*
	 * Disable coprocessors and select 32-bit or 64-bit addressing
	 * and the 16/32 or 32/32 FPR रेजिस्टर model.  Reset the BEV
	 * flag that some firmware may have left set and the TS bit (क्रम
	 * IP27).  Set XX क्रम ISA IV code to work.
	 */
	अचिन्हित पूर्णांक status_set = ST0_KERNEL_CUMASK;
#अगर_घोषित CONFIG_64BIT
	status_set |= ST0_FR|ST0_KX|ST0_SX|ST0_UX;
#पूर्ण_अगर
	अगर (current_cpu_data.isa_level & MIPS_CPU_ISA_IV)
		status_set |= ST0_XX;
	अगर (cpu_has_dsp)
		status_set |= ST0_MX;

	change_c0_status(ST0_CU|ST0_MX|ST0_RE|ST0_FR|ST0_BEV|ST0_TS|ST0_KX|ST0_SX|ST0_UX,
			 status_set);
	back_to_back_c0_hazard();
पूर्ण

अचिन्हित पूर्णांक hwrena;
EXPORT_SYMBOL_GPL(hwrena);

/* configure HWRENA रेजिस्टर */
अटल व्योम configure_hwrena(व्योम)
अणु
	hwrena = cpu_hwrena_impl_bits;

	अगर (cpu_has_mips_r2_r6)
		hwrena |= MIPS_HWRENA_CPUNUM |
			  MIPS_HWRENA_SYNCISTEP |
			  MIPS_HWRENA_CC |
			  MIPS_HWRENA_CCRES;

	अगर (!noulri && cpu_has_userlocal)
		hwrena |= MIPS_HWRENA_ULR;

	अगर (hwrena)
		ग_लिखो_c0_hwrena(hwrena);
पूर्ण

अटल व्योम configure_exception_vector(व्योम)
अणु
	अगर (cpu_has_mips_r2_r6) अणु
		अचिन्हित दीर्घ sr = set_c0_status(ST0_BEV);
		/* If available, use WG to set top bits of EBASE */
		अगर (cpu_has_ebase_wg) अणु
#अगर_घोषित CONFIG_64BIT
			ग_लिखो_c0_ebase_64(ebase | MIPS_EBASE_WG);
#अन्यथा
			ग_लिखो_c0_ebase(ebase | MIPS_EBASE_WG);
#पूर्ण_अगर
		पूर्ण
		ग_लिखो_c0_ebase(ebase);
		ग_लिखो_c0_status(sr);
	पूर्ण
	अगर (cpu_has_veic || cpu_has_vपूर्णांक) अणु
		/* Setting vector spacing enables EI/VI mode  */
		change_c0_पूर्णांकctl(0x3e0, VECTORSPACING);
	पूर्ण
	अगर (cpu_has_भागec) अणु
		अगर (cpu_has_mipsmt) अणु
			अचिन्हित पूर्णांक vpflags = dvpe();
			set_c0_cause(CAUSEF_IV);
			evpe(vpflags);
		पूर्ण अन्यथा
			set_c0_cause(CAUSEF_IV);
	पूर्ण
पूर्ण

व्योम per_cpu_trap_init(bool is_boot_cpu)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	configure_status();
	configure_hwrena();

	configure_exception_vector();

	/*
	 * Beक्रमe R2 both पूर्णांकerrupt numbers were fixed to 7, so on R2 only:
	 *
	 *  o पढ़ो IntCtl.IPTI to determine the समयr पूर्णांकerrupt
	 *  o पढ़ो IntCtl.IPPCI to determine the perक्रमmance counter पूर्णांकerrupt
	 *  o पढ़ो IntCtl.IPFDC to determine the fast debug channel पूर्णांकerrupt
	 */
	अगर (cpu_has_mips_r2_r6) अणु
		cp0_compare_irq_shअगरt = CAUSEB_TI - CAUSEB_IP;
		cp0_compare_irq = (पढ़ो_c0_पूर्णांकctl() >> INTCTLB_IPTI) & 7;
		cp0_perfcount_irq = (पढ़ो_c0_पूर्णांकctl() >> INTCTLB_IPPCI) & 7;
		cp0_fdc_irq = (पढ़ो_c0_पूर्णांकctl() >> INTCTLB_IPFDC) & 7;
		अगर (!cp0_fdc_irq)
			cp0_fdc_irq = -1;

	पूर्ण अन्यथा अणु
		cp0_compare_irq = CP0_LEGACY_COMPARE_IRQ;
		cp0_compare_irq_shअगरt = CP0_LEGACY_PERFCNT_IRQ;
		cp0_perfcount_irq = -1;
		cp0_fdc_irq = -1;
	पूर्ण

	अगर (cpu_has_mmid)
		cpu_data[cpu].asid_cache = 0;
	अन्यथा अगर (!cpu_data[cpu].asid_cache)
		cpu_data[cpu].asid_cache = asid_first_version(cpu);

	mmgrab(&init_mm);
	current->active_mm = &init_mm;
	BUG_ON(current->mm);
	enter_lazy_tlb(&init_mm, current);

	/* Boot CPU's cache setup in setup_arch(). */
	अगर (!is_boot_cpu)
		cpu_cache_init();
	tlb_init();
	TLBMISS_HANDLER_SETUP();
पूर्ण

/* Install CPU exception handler */
व्योम set_handler(अचिन्हित दीर्घ offset, व्योम *addr, अचिन्हित दीर्घ size)
अणु
#अगर_घोषित CONFIG_CPU_MICROMIPS
	स_नकल((व्योम *)(ebase + offset), ((अचिन्हित अक्षर *)addr - 1), size);
#अन्यथा
	स_नकल((व्योम *)(ebase + offset), addr, size);
#पूर्ण_अगर
	local_flush_icache_range(ebase + offset, ebase + offset + size);
पूर्ण

अटल स्थिर अक्षर panic_null_cerr[] =
	"Trying to set NULL cache error exception handler\n";

/*
 * Install uncached CPU exception handler.
 * This is suitable only क्रम the cache error exception which is the only
 * exception handler that is being run uncached.
 */
व्योम set_uncached_handler(अचिन्हित दीर्घ offset, व्योम *addr,
	अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ uncached_ebase = CKSEG1ADDR(ebase);

	अगर (!addr)
		panic(panic_null_cerr);

	स_नकल((व्योम *)(uncached_ebase + offset), addr, size);
पूर्ण

अटल पूर्णांक __initdata rdhwr_noopt;
अटल पूर्णांक __init set_rdhwr_noopt(अक्षर *str)
अणु
	rdhwr_noopt = 1;
	वापस 1;
पूर्ण

__setup("rdhwr_noopt", set_rdhwr_noopt);

व्योम __init trap_init(व्योम)
अणु
	बाह्य अक्षर except_vec3_generic;
	बाह्य अक्षर except_vec4;
	बाह्य अक्षर except_vec3_r4000;
	अचिन्हित दीर्घ i, vec_size;
	phys_addr_t ebase_pa;

	check_रुको();

	अगर (!cpu_has_mips_r2_r6) अणु
		ebase = CAC_BASE;
		vec_size = 0x400;
	पूर्ण अन्यथा अणु
		अगर (cpu_has_veic || cpu_has_vपूर्णांक)
			vec_size = 0x200 + VECTORSPACING*64;
		अन्यथा
			vec_size = PAGE_SIZE;

		ebase_pa = memblock_phys_alloc(vec_size, 1 << fls(vec_size));
		अगर (!ebase_pa)
			panic("%s: Failed to allocate %lu bytes align=0x%x\n",
			      __func__, vec_size, 1 << fls(vec_size));

		/*
		 * Try to ensure ebase resides in KSeg0 अगर possible.
		 *
		 * It shouldn't generally be in XKPhys on MIPS64 to aव्योम
		 * hitting a poorly defined exception base क्रम Cache Errors.
		 * The allocation is likely to be in the low 512MB of physical,
		 * in which हाल we should be able to convert to KSeg0.
		 *
		 * EVA is special though as it allows segments to be rearranged
		 * and to become uncached during cache error handling.
		 */
		अगर (!IS_ENABLED(CONFIG_EVA) && !WARN_ON(ebase_pa >= 0x20000000))
			ebase = CKSEG0ADDR(ebase_pa);
		अन्यथा
			ebase = (अचिन्हित दीर्घ)phys_to_virt(ebase_pa);
	पूर्ण

	अगर (cpu_has_mmips) अणु
		अचिन्हित पूर्णांक config3 = पढ़ो_c0_config3();

		अगर (IS_ENABLED(CONFIG_CPU_MICROMIPS))
			ग_लिखो_c0_config3(config3 | MIPS_CONF3_ISA_OE);
		अन्यथा
			ग_लिखो_c0_config3(config3 & ~MIPS_CONF3_ISA_OE);
	पूर्ण

	अगर (board_ebase_setup)
		board_ebase_setup();
	per_cpu_trap_init(true);
	memblock_set_bottom_up(false);

	/*
	 * Copy the generic exception handlers to their final destination.
	 * This will be overridden later as suitable क्रम a particular
	 * configuration.
	 */
	set_handler(0x180, &except_vec3_generic, 0x80);

	/*
	 * Setup शेष vectors
	 */
	क्रम (i = 0; i <= 31; i++)
		set_except_vector(i, handle_reserved);

	/*
	 * Copy the EJTAG debug exception vector handler code to it's final
	 * destination.
	 */
	अगर (cpu_has_ejtag && board_ejtag_handler_setup)
		board_ejtag_handler_setup();

	/*
	 * Only some CPUs have the watch exceptions.
	 */
	अगर (cpu_has_watch)
		set_except_vector(EXCCODE_WATCH, handle_watch);

	/*
	 * Initialise पूर्णांकerrupt handlers
	 */
	अगर (cpu_has_veic || cpu_has_vपूर्णांक) अणु
		पूर्णांक nvec = cpu_has_veic ? 64 : 8;
		क्रम (i = 0; i < nvec; i++)
			set_vi_handler(i, शून्य);
	पूर्ण
	अन्यथा अगर (cpu_has_भागec)
		set_handler(0x200, &except_vec4, 0x8);

	/*
	 * Some CPUs can enable/disable क्रम cache parity detection, but करोes
	 * it dअगरferent ways.
	 */
	parity_protection_init();

	/*
	 * The Data Bus Errors / Inकाष्ठाion Bus Errors are संकेतed
	 * by बाह्यal hardware.  Thereक्रमe these two exceptions
	 * may have board specअगरic handlers.
	 */
	अगर (board_be_init)
		board_be_init();

	set_except_vector(EXCCODE_INT, using_rollback_handler() ?
					rollback_handle_पूर्णांक : handle_पूर्णांक);
	set_except_vector(EXCCODE_MOD, handle_tlbm);
	set_except_vector(EXCCODE_TLBL, handle_tlbl);
	set_except_vector(EXCCODE_TLBS, handle_tlbs);

	set_except_vector(EXCCODE_ADEL, handle_adel);
	set_except_vector(EXCCODE_ADES, handle_ades);

	set_except_vector(EXCCODE_IBE, handle_ibe);
	set_except_vector(EXCCODE_DBE, handle_dbe);

	set_except_vector(EXCCODE_SYS, handle_sys);
	set_except_vector(EXCCODE_BP, handle_bp);

	अगर (rdhwr_noopt)
		set_except_vector(EXCCODE_RI, handle_ri);
	अन्यथा अणु
		अगर (cpu_has_vtag_icache)
			set_except_vector(EXCCODE_RI, handle_ri_rdhwr_tlbp);
		अन्यथा अगर (current_cpu_type() == CPU_LOONGSON64)
			set_except_vector(EXCCODE_RI, handle_ri_rdhwr_tlbp);
		अन्यथा
			set_except_vector(EXCCODE_RI, handle_ri_rdhwr);
	पूर्ण

	set_except_vector(EXCCODE_CPU, handle_cpu);
	set_except_vector(EXCCODE_OV, handle_ov);
	set_except_vector(EXCCODE_TR, handle_tr);
	set_except_vector(EXCCODE_MSAFPE, handle_msa_fpe);

	अगर (board_nmi_handler_setup)
		board_nmi_handler_setup();

	अगर (cpu_has_fpu && !cpu_has_nofpuex)
		set_except_vector(EXCCODE_FPE, handle_fpe);

	अगर (cpu_has_ftlbparex)
		set_except_vector(MIPS_EXCCODE_TLBPAR, handle_ftlb);

	अगर (cpu_has_gsexcex)
		set_except_vector(LOONGSON_EXCCODE_GSEXC, handle_gsexc);

	अगर (cpu_has_rixiex) अणु
		set_except_vector(EXCCODE_TLBRI, tlb_करो_page_fault_0);
		set_except_vector(EXCCODE_TLBXI, tlb_करो_page_fault_0);
	पूर्ण

	set_except_vector(EXCCODE_MSADIS, handle_msa);
	set_except_vector(EXCCODE_MDMX, handle_mdmx);

	अगर (cpu_has_mcheck)
		set_except_vector(EXCCODE_MCHECK, handle_mcheck);

	अगर (cpu_has_mipsmt)
		set_except_vector(EXCCODE_THREAD, handle_mt);

	set_except_vector(EXCCODE_DSPDIS, handle_dsp);

	अगर (board_cache_error_setup)
		board_cache_error_setup();

	अगर (cpu_has_vce)
		/* Special exception: R4[04]00 uses also the भागec space. */
		set_handler(0x180, &except_vec3_r4000, 0x100);
	अन्यथा अगर (cpu_has_4kex)
		set_handler(0x180, &except_vec3_generic, 0x80);
	अन्यथा
		set_handler(0x080, &except_vec3_generic, 0x80);

	local_flush_icache_range(ebase, ebase + vec_size);

	sort_extable(__start___dbe_table, __stop___dbe_table);

	cu2_notअगरier(शेष_cu2_call, 0x80000000);	/* Run last  */
पूर्ण

अटल पूर्णांक trap_pm_notअगरier(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ cmd,
			    व्योम *v)
अणु
	चयन (cmd) अणु
	हाल CPU_PM_ENTER_FAILED:
	हाल CPU_PM_EXIT:
		configure_status();
		configure_hwrena();
		configure_exception_vector();

		/* Restore रेजिस्टर with CPU number क्रम TLB handlers */
		TLBMISS_HANDLER_RESTORE();

		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block trap_pm_notअगरier_block = अणु
	.notअगरier_call = trap_pm_notअगरier,
पूर्ण;

अटल पूर्णांक __init trap_pm_init(व्योम)
अणु
	वापस cpu_pm_रेजिस्टर_notअगरier(&trap_pm_notअगरier_block);
पूर्ण
arch_initcall(trap_pm_init);
