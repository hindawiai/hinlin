<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/parisc/traps.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 1999, 2000  Philipp Rumpf <prumpf@tux.org>
 */

/*
 * 'Traps.c' handles hardware traps and faults after we have saved some
 * state in 'asm.s'.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/console.h>
#समावेश <linux/bug.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/kdebug.h>

#समावेश <यंत्र/assembly.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/atomic.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/pdc.h>
#समावेश <यंत्र/pdc_chassis.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/kgdb.h>
#समावेश <linux/kprobes.h>

#समावेश "../math-emu/math-emu.h"	/* क्रम handle_fpe() */

अटल व्योम parisc_show_stack(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl);

अटल पूर्णांक prपूर्णांकbinary(अक्षर *buf, अचिन्हित दीर्घ x, पूर्णांक nbits)
अणु
	अचिन्हित दीर्घ mask = 1UL << (nbits - 1);
	जबतक (mask != 0) अणु
		*buf++ = (mask & x ? '1' : '0');
		mask >>= 1;
	पूर्ण
	*buf = '\0';

	वापस nbits;
पूर्ण

#अगर_घोषित CONFIG_64BIT
#घोषणा RFMT "%016lx"
#अन्यथा
#घोषणा RFMT "%08lx"
#पूर्ण_अगर
#घोषणा FFMT "%016llx"	/* fpregs are 64-bit always */

#घोषणा PRINTREGS(lvl,r,f,fmt,x)	\
	prपूर्णांकk("%s%s%02d-%02d  " fmt " " fmt " " fmt " " fmt "\n",	\
		lvl, f, (x), (x+3), (r)[(x)+0], (r)[(x)+1],		\
		(r)[(x)+2], (r)[(x)+3])

अटल व्योम prपूर्णांक_gr(स्थिर अक्षर *level, काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	अक्षर buf[64];

	prपूर्णांकk("%s\n", level);
	prपूर्णांकk("%s     YZrvWESTHLNXBCVMcbcbcbcbOGFRQPDI\n", level);
	prपूर्णांकbinary(buf, regs->gr[0], 32);
	prपूर्णांकk("%sPSW: %s %s\n", level, buf, prपूर्णांक_taपूर्णांकed());

	क्रम (i = 0; i < 32; i += 4)
		PRINTREGS(level, regs->gr, "r", RFMT, i);
पूर्ण

अटल व्योम prपूर्णांक_fr(स्थिर अक्षर *level, काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	अक्षर buf[64];
	काष्ठा अणु u32 sw[2]; पूर्ण s;

	/* FR are 64bit everywhere. Need to use यंत्र to get the content
	 * of fpsr/fper1, and we assume that we won't have a FP Identअगरy
	 * in our way, otherwise we're screwed.
	 * The fldd is used to restore the T-bit अगर there was one, as the
	 * store clears it anyway.
	 * PA2.0 book says "thou shall not use fstw on FPSR/FPERs" - T-Bone */
	यंत्र अस्थिर ("fstd %%fr0,0(%1)	\n\t"
		      "fldd 0(%1),%%fr0	\n\t"
		      : "=m" (s) : "r" (&s) : "r0");

	prपूर्णांकk("%s\n", level);
	prपूर्णांकk("%s      VZOUICununcqcqcqcqcqcrmunTDVZOUI\n", level);
	prपूर्णांकbinary(buf, s.sw[0], 32);
	prपूर्णांकk("%sFPSR: %s\n", level, buf);
	prपूर्णांकk("%sFPER1: %08x\n", level, s.sw[1]);

	/* here we'll print fr0 again, tho it'll be meaningless */
	क्रम (i = 0; i < 32; i += 4)
		PRINTREGS(level, regs->fr, "fr", FFMT, i);
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, user;
	स्थिर अक्षर *level;
	अचिन्हित दीर्घ cr30, cr31;

	user = user_mode(regs);
	level = user ? KERN_DEBUG : KERN_CRIT;

	show_regs_prपूर्णांक_info(level);

	prपूर्णांक_gr(level, regs);

	क्रम (i = 0; i < 8; i += 4)
		PRINTREGS(level, regs->sr, "sr", RFMT, i);

	अगर (user)
		prपूर्णांक_fr(level, regs);

	cr30 = mfctl(30);
	cr31 = mfctl(31);
	prपूर्णांकk("%s\n", level);
	prपूर्णांकk("%sIASQ: " RFMT " " RFMT " IAOQ: " RFMT " " RFMT "\n",
	       level, regs->iasq[0], regs->iasq[1], regs->iaoq[0], regs->iaoq[1]);
	prपूर्णांकk("%s IIR: %08lx    ISR: " RFMT "  IOR: " RFMT "\n",
	       level, regs->iir, regs->isr, regs->ior);
	prपूर्णांकk("%s CPU: %8d   CR30: " RFMT " CR31: " RFMT "\n",
	       level, current_thपढ़ो_info()->cpu, cr30, cr31);
	prपूर्णांकk("%s ORIG_R28: " RFMT "\n", level, regs->orig_r28);

	अगर (user) अणु
		prपूर्णांकk("%s IAOQ[0]: " RFMT "\n", level, regs->iaoq[0]);
		prपूर्णांकk("%s IAOQ[1]: " RFMT "\n", level, regs->iaoq[1]);
		prपूर्णांकk("%s RP(r2): " RFMT "\n", level, regs->gr[2]);
	पूर्ण अन्यथा अणु
		prपूर्णांकk("%s IAOQ[0]: %pS\n", level, (व्योम *) regs->iaoq[0]);
		prपूर्णांकk("%s IAOQ[1]: %pS\n", level, (व्योम *) regs->iaoq[1]);
		prपूर्णांकk("%s RP(r2): %pS\n", level, (व्योम *) regs->gr[2]);

		parisc_show_stack(current, regs, KERN_DEFAULT);
	पूर्ण
पूर्ण

अटल DEFINE_RATELIMIT_STATE(_hppa_rs,
	DEFAULT_RATELIMIT_INTERVAL, DEFAULT_RATELIMIT_BURST);

#घोषणा parisc_prपूर्णांकk_ratelimited(critical, regs, fmt, ...)	अणु	      \
	अगर ((critical || show_unhandled_संकेतs) && __ratelimit(&_hppa_rs)) अणु \
		prपूर्णांकk(fmt, ##__VA_ARGS__);				      \
		show_regs(regs);					      \
	पूर्ण								      \
पूर्ण


अटल व्योम करो_show_stack(काष्ठा unwind_frame_info *info, स्थिर अक्षर *loglvl)
अणु
	पूर्णांक i = 1;

	prपूर्णांकk("%sBacktrace:\n", loglvl);
	जबतक (i <= MAX_UNWIND_ENTRIES) अणु
		अगर (unwind_once(info) < 0 || info->ip == 0)
			अवरोध;

		अगर (__kernel_text_address(info->ip)) अणु
			prपूर्णांकk("%s [<" RFMT ">] %pS\n",
				loglvl, info->ip, (व्योम *) info->ip);
			i++;
		पूर्ण
	पूर्ण
	prपूर्णांकk("%s\n", loglvl);
पूर्ण

अटल व्योम parisc_show_stack(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl)
अणु
	काष्ठा unwind_frame_info info;

	unwind_frame_init_task(&info, task, regs);

	करो_show_stack(&info, loglvl);
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *t, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	parisc_show_stack(t, शून्य, loglvl);
पूर्ण

पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ iaoq)
अणु
	वापस 1;
पूर्ण

व्योम die_अगर_kernel(अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अगर (user_mode(regs)) अणु
		अगर (err == 0)
			वापस; /* STFU */

		parisc_prपूर्णांकk_ratelimited(1, regs,
			KERN_CRIT "%s (pid %d): %s (code %ld) at " RFMT "\n",
			current->comm, task_pid_nr(current), str, err, regs->iaoq[0]);

		वापस;
	पूर्ण

	bust_spinlocks(1);

	oops_enter();

	/* Amuse the user in a SPARC fashion */
	अगर (err) prपूर्णांकk(KERN_CRIT
			"      _______________________________ \n"
			"     < Your System ate a SPARC! Gah! >\n"
			"      ------------------------------- \n"
			"             \\   ^__^\न"
			"                 (__)\\       )\\/\\\n"
			"                  U  ||----w |\n"
			"                     ||     ||\n");
	
	/* unlock the pdc lock अगर necessary */
	pdc_emergency_unlock();

	/* maybe the kernel hasn't booted very far yet and hasn't been able 
	 * to initialize the serial or STI console. In that हाल we should 
	 * re-enable the pdc console, so that the user will be able to 
	 * identअगरy the problem. */
	अगर (!console_drivers)
		pdc_console_restart();
	
	अगर (err)
		prपूर्णांकk(KERN_CRIT "%s (pid %d): %s (code %ld)\n",
			current->comm, task_pid_nr(current), str, err);

	/* Wot's wrong wif bein' racy? */
	अगर (current->thपढ़ो.flags & PARISC_KERNEL_DEATH) अणु
		prपूर्णांकk(KERN_CRIT "%s() recursion detected.\n", __func__);
		local_irq_enable();
		जबतक (1);
	पूर्ण
	current->thपढ़ो.flags |= PARISC_KERNEL_DEATH;

	show_regs(regs);
	dump_stack();
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);

	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");

	अगर (panic_on_oops)
		panic("Fatal exception");

	oops_निकास();
	करो_निकास(संक_अंश);
पूर्ण

/* gdb uses अवरोध 4,8 */
#घोषणा GDB_BREAK_INSN 0x10004
अटल व्योम handle_gdb_अवरोध(काष्ठा pt_regs *regs, पूर्णांक wot)
अणु
	क्रमce_sig_fault(SIGTRAP, wot,
			(व्योम __user *) (regs->iaoq[0] & ~3));
पूर्ण

अटल व्योम handle_अवरोध(काष्ठा pt_regs *regs)
अणु
	अचिन्हित iir = regs->iir;

	अगर (unlikely(iir == PARISC_BUG_BREAK_INSN && !user_mode(regs))) अणु
		/* check अगर a BUG() or WARN() trapped here.  */
		क्रमागत bug_trap_type tt;
		tt = report_bug(regs->iaoq[0] & ~3, regs);
		अगर (tt == BUG_TRAP_TYPE_WARN) अणु
			regs->iaoq[0] += 4;
			regs->iaoq[1] += 4;
			वापस; /* वापस to next inकाष्ठाion when WARN_ON().  */
		पूर्ण
		die_अगर_kernel("Unknown kernel breakpoint", regs,
			(tt == BUG_TRAP_TYPE_NONE) ? 9 : 0);
	पूर्ण

#अगर_घोषित CONFIG_KPROBES
	अगर (unlikely(iir == PARISC_KPROBES_BREAK_INSN)) अणु
		parisc_kprobe_अवरोध_handler(regs);
		वापस;
	पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_KGDB
	अगर (unlikely(iir == PARISC_KGDB_COMPILED_BREAK_INSN ||
		iir == PARISC_KGDB_BREAK_INSN)) अणु
		kgdb_handle_exception(9, SIGTRAP, 0, regs);
		वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (unlikely(iir != GDB_BREAK_INSN))
		parisc_prपूर्णांकk_ratelimited(0, regs,
			KERN_DEBUG "break %d,%d: pid=%d command='%s'\n",
			iir & 31, (iir>>13) & ((1<<13)-1),
			task_pid_nr(current), current->comm);

	/* send standard GDB संकेत */
	handle_gdb_अवरोध(regs, TRAP_BRKPT);
पूर्ण

अटल व्योम शेष_trap(पूर्णांक code, काष्ठा pt_regs *regs)
अणु
	prपूर्णांकk(KERN_ERR "Trap %d on CPU %d\n", code, smp_processor_id());
	show_regs(regs);
पूर्ण

व्योम (*cpu_lpmc) (पूर्णांक code, काष्ठा pt_regs *regs) __पढ़ो_mostly = शेष_trap;


व्योम transfer_pim_to_trap_frame(काष्ठा pt_regs *regs)
अणु
    रेजिस्टर पूर्णांक i;
    बाह्य अचिन्हित पूर्णांक hpmc_pim_data[];
    काष्ठा pdc_hpmc_pim_11 *pim_narrow;
    काष्ठा pdc_hpmc_pim_20 *pim_wide;

    अगर (boot_cpu_data.cpu_type >= pcxu) अणु

	pim_wide = (काष्ठा pdc_hpmc_pim_20 *)hpmc_pim_data;

	/*
	 * Note: The following code will probably generate a
	 * bunch of truncation error warnings from the compiler.
	 * Could be handled with an अगरdef, but perhaps there
	 * is a better way.
	 */

	regs->gr[0] = pim_wide->cr[22];

	क्रम (i = 1; i < 32; i++)
	    regs->gr[i] = pim_wide->gr[i];

	क्रम (i = 0; i < 32; i++)
	    regs->fr[i] = pim_wide->fr[i];

	क्रम (i = 0; i < 8; i++)
	    regs->sr[i] = pim_wide->sr[i];

	regs->iasq[0] = pim_wide->cr[17];
	regs->iasq[1] = pim_wide->iasq_back;
	regs->iaoq[0] = pim_wide->cr[18];
	regs->iaoq[1] = pim_wide->iaoq_back;

	regs->sar  = pim_wide->cr[11];
	regs->iir  = pim_wide->cr[19];
	regs->isr  = pim_wide->cr[20];
	regs->ior  = pim_wide->cr[21];
    पूर्ण
    अन्यथा अणु
	pim_narrow = (काष्ठा pdc_hpmc_pim_11 *)hpmc_pim_data;

	regs->gr[0] = pim_narrow->cr[22];

	क्रम (i = 1; i < 32; i++)
	    regs->gr[i] = pim_narrow->gr[i];

	क्रम (i = 0; i < 32; i++)
	    regs->fr[i] = pim_narrow->fr[i];

	क्रम (i = 0; i < 8; i++)
	    regs->sr[i] = pim_narrow->sr[i];

	regs->iasq[0] = pim_narrow->cr[17];
	regs->iasq[1] = pim_narrow->iasq_back;
	regs->iaoq[0] = pim_narrow->cr[18];
	regs->iaoq[1] = pim_narrow->iaoq_back;

	regs->sar  = pim_narrow->cr[11];
	regs->iir  = pim_narrow->cr[19];
	regs->isr  = pim_narrow->cr[20];
	regs->ior  = pim_narrow->cr[21];
    पूर्ण

    /*
     * The following fields only have meaning अगर we came through
     * another path. So just zero them here.
     */

    regs->ksp = 0;
    regs->kpc = 0;
    regs->orig_r28 = 0;
पूर्ण


/*
 * This routine is called as a last resort when everything अन्यथा
 * has gone clearly wrong. We get called क्रम faults in kernel space,
 * and HPMC's.
 */
व्योम parisc_terminate(अक्षर *msg, काष्ठा pt_regs *regs, पूर्णांक code, अचिन्हित दीर्घ offset)
अणु
	अटल DEFINE_SPINLOCK(terminate_lock);

	(व्योम)notअगरy_die(DIE_OOPS, msg, regs, 0, code, SIGTRAP);
	bust_spinlocks(1);

	set_eiem(0);
	local_irq_disable();
	spin_lock(&terminate_lock);

	/* unlock the pdc lock अगर necessary */
	pdc_emergency_unlock();

	/* restart pdc console अगर necessary */
	अगर (!console_drivers)
		pdc_console_restart();

	/* Not all paths will gutter the processor... */
	चयन(code)अणु

	हाल 1:
		transfer_pim_to_trap_frame(regs);
		अवरोध;

	शेष:
		अवरोध;

	पूर्ण
	    
	अणु
		/* show_stack(शून्य, (अचिन्हित दीर्घ *)regs->gr[30]); */
		काष्ठा unwind_frame_info info;
		unwind_frame_init(&info, current, regs);
		करो_show_stack(&info, KERN_CRIT);
	पूर्ण

	prपूर्णांकk("\n");
	pr_crit("%s: Code=%d (%s) at addr " RFMT "\n",
		msg, code, trap_name(code), offset);
	show_regs(regs);

	spin_unlock(&terminate_lock);

	/* put soft घातer button back under hardware control;
	 * अगर the user had pressed it once at any समय, the 
	 * प्रणाली will shut करोwn immediately right here. */
	pdc_soft_घातer_button(0);
	
	/* Call kernel panic() so reboot समयouts work properly 
	 * FIXME: This function should be on the list of
	 * panic notअगरiers, and we should call panic
	 * directly from the location that we wish. 
	 * e.g. We should not call panic from
	 * parisc_terminate, but rather the oter way around.
	 * This hack works, prपूर्णांकs the panic message twice,
	 * and it enables reboot समयrs!
	 */
	panic(msg);
पूर्ण

व्योम notrace handle_पूर्णांकerruption(पूर्णांक code, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ fault_address = 0;
	अचिन्हित दीर्घ fault_space = 0;
	पूर्णांक si_code;

	अगर (code == 1)
	    pdc_console_restart();  /* चयन back to pdc अगर HPMC */
	अन्यथा
	    local_irq_enable();

	/* Security check:
	 * If the priority level is still user, and the
	 * faulting space is not equal to the active space
	 * then the user is attempting something in a space
	 * that करोes not beदीर्घ to them. Kill the process.
	 *
	 * This is normally the situation when the user
	 * attempts to jump पूर्णांकo the kernel space at the
	 * wrong offset, be it at the gateway page or a
	 * अक्रमom location.
	 *
	 * We cannot normally संकेत the process because it
	 * could *be* on the gateway page, and processes
	 * executing on the gateway page can't have संकेतs
	 * delivered.
	 * 
	 * We merely पढ़ोjust the address पूर्णांकo the users
	 * space, at a destination address of zero, and
	 * allow processing to जारी.
	 */
	अगर (((अचिन्हित दीर्घ)regs->iaoq[0] & 3) &&
	    ((अचिन्हित दीर्घ)regs->iasq[0] != (अचिन्हित दीर्घ)regs->sr[7])) अणु 
		/* Kill the user process later */
		regs->iaoq[0] = 0 | 3;
		regs->iaoq[1] = regs->iaoq[0] + 4;
		regs->iasq[0] = regs->iasq[1] = regs->sr[7];
		regs->gr[0] &= ~PSW_B;
		वापस;
	पूर्ण
	
#अगर 0
	prपूर्णांकk(KERN_CRIT "Interruption # %d\n", code);
#पूर्ण_अगर

	चयन(code) अणु

	हाल  1:
		/* High-priority machine check (HPMC) */
		
		/* set up a new led state on प्रणालीs shipped with a LED State panel */
		pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_HPMC);

		parisc_terminate("High Priority Machine Check (HPMC)",
				regs, code, 0);
		/* NOT REACHED */
		
	हाल  2:
		/* Power failure पूर्णांकerrupt */
		prपूर्णांकk(KERN_CRIT "Power failure interrupt !\n");
		वापस;

	हाल  3:
		/* Recovery counter trap */
		regs->gr[0] &= ~PSW_R;

#अगर_घोषित CONFIG_KPROBES
		अगर (parisc_kprobe_ss_handler(regs))
			वापस;
#पूर्ण_अगर

#अगर_घोषित CONFIG_KGDB
		अगर (kgdb_single_step) अणु
			kgdb_handle_exception(0, SIGTRAP, 0, regs);
			वापस;
		पूर्ण
#पूर्ण_अगर

		अगर (user_space(regs))
			handle_gdb_अवरोध(regs, TRAP_TRACE);
		/* अन्यथा this must be the start of a syscall - just let it run */
		वापस;

	हाल  5:
		/* Low-priority machine check */
		pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_LPMC);
		
		flush_cache_all();
		flush_tlb_all();
		cpu_lpmc(5, regs);
		वापस;

	हाल  PARISC_ITLB_TRAP:
		/* Inकाष्ठाion TLB miss fault/Inकाष्ठाion page fault */
		fault_address = regs->iaoq[0];
		fault_space   = regs->iasq[0];
		अवरोध;

	हाल  8:
		/* Illegal inकाष्ठाion trap */
		die_अगर_kernel("Illegal instruction", regs, code);
		si_code = ILL_ILLOPC;
		जाओ give_sigill;

	हाल  9:
		/* Break inकाष्ठाion trap */
		handle_अवरोध(regs);
		वापस;

	हाल 10:
		/* Privileged operation trap */
		die_अगर_kernel("Privileged operation", regs, code);
		si_code = ILL_PRVOPC;
		जाओ give_sigill;

	हाल 11:
		/* Privileged रेजिस्टर trap */
		अगर ((regs->iir & 0xffdfffe0) == 0x034008a0) अणु

			/* This is a MFCTL cr26/cr27 to gr inकाष्ठाion.
			 * PCXS traps on this, so we need to emulate it.
			 */

			अगर (regs->iir & 0x00200000)
				regs->gr[regs->iir & 0x1f] = mfctl(27);
			अन्यथा
				regs->gr[regs->iir & 0x1f] = mfctl(26);

			regs->iaoq[0] = regs->iaoq[1];
			regs->iaoq[1] += 4;
			regs->iasq[0] = regs->iasq[1];
			वापस;
		पूर्ण

		die_अगर_kernel("Privileged register usage", regs, code);
		si_code = ILL_PRVREG;
	give_sigill:
		क्रमce_sig_fault(संक_अवैध, si_code,
				(व्योम __user *) regs->iaoq[0]);
		वापस;

	हाल 12:
		/* Overflow Trap, let the userland संकेत handler करो the cleanup */
		क्रमce_sig_fault(संक_भ_त्रुटि, FPE_INTOVF,
				(व्योम __user *) regs->iaoq[0]);
		वापस;
		
	हाल 13:
		/* Conditional Trap
		   The condition succeeds in an inकाष्ठाion which traps
		   on condition  */
		अगर(user_mode(regs))अणु
			/* Let userspace app figure it out from the insn poपूर्णांकed
			 * to by si_addr.
			 */
			क्रमce_sig_fault(संक_भ_त्रुटि, FPE_CONDTRAP,
					(व्योम __user *) regs->iaoq[0]);
			वापस;
		पूर्ण 
		/* The kernel करोesn't want to handle condition codes */
		अवरोध;
		
	हाल 14:
		/* Assist Exception Trap, i.e. भग्नing poपूर्णांक exception. */
		die_अगर_kernel("Floating point exception", regs, 0); /* quiet */
		__inc_irq_stat(irq_fpassist_count);
		handle_fpe(regs);
		वापस;

	हाल 15:
		/* Data TLB miss fault/Data page fault */
		fallthrough;
	हाल 16:
		/* Non-access inकाष्ठाion TLB miss fault */
		/* The inकाष्ठाion TLB entry needed क्रम the target address of the FIC
		   is असलent, and hardware can't find it, so we get to cleanup */
		fallthrough;
	हाल 17:
		/* Non-access data TLB miss fault/Non-access data page fault */
		/* FIXME: 
			 Still need to add slow path emulation code here!
			 If the insn used a non-shaकरोw रेजिस्टर, then the tlb
			 handlers could not have their side-effect (e.g. probe
			 writing to a target रेजिस्टर) emulated since rfir would
			 erase the changes to said रेजिस्टर. Instead we have to
			 setup everything, call this function we are in, and emulate
			 by hand. Technically we need to emulate:
			 fdc,fdce,pdc,"fic,4f",prober,probeir,probew, probeiw
		*/
		fault_address = regs->ior;
		fault_space = regs->isr;
		अवरोध;

	हाल 18:
		/* PCXS only -- later cpu's split this पूर्णांकo types 26,27 & 28 */
		/* Check क्रम unaligned access */
		अगर (check_unaligned(regs)) अणु
			handle_unaligned(regs);
			वापस;
		पूर्ण
		fallthrough;
	हाल 26: 
		/* PCXL: Data memory access rights trap */
		fault_address = regs->ior;
		fault_space   = regs->isr;
		अवरोध;

	हाल 19:
		/* Data memory अवरोध trap */
		regs->gr[0] |= PSW_X; /* So we can single-step over the trap */
		fallthrough;
	हाल 21:
		/* Page reference trap */
		handle_gdb_अवरोध(regs, TRAP_HWBKPT);
		वापस;

	हाल 25:
		/* Taken branch trap */
		regs->gr[0] &= ~PSW_T;
		अगर (user_space(regs))
			handle_gdb_अवरोध(regs, TRAP_BRANCH);
		/* अन्यथा this must be the start of a syscall - just let it
		 * run.
		 */
		वापस;

	हाल  7:  
		/* Inकाष्ठाion access rights */
		/* PCXL: Inकाष्ठाion memory protection trap */

		/*
		 * This could be caused by either: 1) a process attempting
		 * to execute within a vma that करोes not have execute
		 * permission, or 2) an access rights violation caused by a
		 * flush only translation set up by ptep_get_and_clear().
		 * So we check the vma permissions to dअगरferentiate the two.
		 * If the vma indicates we have execute permission, then
		 * the cause is the latter one. In this हाल, we need to
		 * call करो_page_fault() to fix the problem.
		 */

		अगर (user_mode(regs)) अणु
			काष्ठा vm_area_काष्ठा *vma;

			mmap_पढ़ो_lock(current->mm);
			vma = find_vma(current->mm,regs->iaoq[0]);
			अगर (vma && (regs->iaoq[0] >= vma->vm_start)
				&& (vma->vm_flags & VM_EXEC)) अणु

				fault_address = regs->iaoq[0];
				fault_space = regs->iasq[0];

				mmap_पढ़ो_unlock(current->mm);
				अवरोध; /* call करो_page_fault() */
			पूर्ण
			mmap_पढ़ो_unlock(current->mm);
		पूर्ण
		fallthrough;
	हाल 27: 
		/* Data memory protection ID trap */
		अगर (code == 27 && !user_mode(regs) &&
			fixup_exception(regs))
			वापस;

		die_अगर_kernel("Protection id trap", regs, code);
		क्रमce_sig_fault(संक_अंश, SEGV_MAPERR,
				(code == 7)?
				((व्योम __user *) regs->iaoq[0]) :
				((व्योम __user *) regs->ior));
		वापस;

	हाल 28: 
		/* Unaligned data reference trap */
		handle_unaligned(regs);
		वापस;

	शेष:
		अगर (user_mode(regs)) अणु
			parisc_prपूर्णांकk_ratelimited(0, regs, KERN_DEBUG
				"handle_interruption() pid=%d command='%s'\n",
				task_pid_nr(current), current->comm);
			/* SIGBUS, क्रम lack of a better one. */
			क्रमce_sig_fault(SIGBUS, BUS_OBJERR,
					(व्योम __user *)regs->ior);
			वापस;
		पूर्ण
		pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_PANIC);
		
		parisc_terminate("Unexpected interruption", regs, code, 0);
		/* NOT REACHED */
	पूर्ण

	अगर (user_mode(regs)) अणु
	    अगर ((fault_space >> SPACEID_SHIFT) != (regs->sr[7] >> SPACEID_SHIFT)) अणु
		parisc_prपूर्णांकk_ratelimited(0, regs, KERN_DEBUG
				"User fault %d on space 0x%08lx, pid=%d command='%s'\n",
				code, fault_space,
				task_pid_nr(current), current->comm);
		क्रमce_sig_fault(संक_अंश, SEGV_MAPERR,
				(व्योम __user *)regs->ior);
		वापस;
	    पूर्ण
	पूर्ण
	अन्यथा अणु

	    /*
	     * The kernel should never fault on its own address space,
	     * unless pagefault_disable() was called beक्रमe.
	     */

	    अगर (fault_space == 0 && !faulthandler_disabled())
	    अणु
		/* Clean up and वापस अगर in exception table. */
		अगर (fixup_exception(regs))
			वापस;
		pdc_chassis_send_status(PDC_CHASSIS_सूचीECT_PANIC);
		parisc_terminate("Kernel Fault", regs, code, fault_address);
	    पूर्ण
	पूर्ण

	करो_page_fault(regs, code, fault_address);
पूर्ण


व्योम __init initialize_ivt(स्थिर व्योम *iva)
अणु
	बाह्य स्थिर u32 os_hpmc[];

	पूर्णांक i;
	u32 check = 0;
	u32 *ivap;
	u32 *hpmcp;
	u32 instr;

	अगर (म_भेद((स्थिर अक्षर *)iva, "cows can fly"))
		panic("IVT invalid");

	ivap = (u32 *)iva;

	क्रम (i = 0; i < 8; i++)
	    *ivap++ = 0;

	/*
	 * Use PDC_INSTR firmware function to get inकाष्ठाion that invokes
	 * PDCE_CHECK in HPMC handler.  See programming note at page 1-31 of
	 * the PA 1.1 Firmware Architecture करोcument.
	 */
	अगर (pdc_instr(&instr) == PDC_OK)
		ivap[0] = instr;

	/*
	 * Rules क्रम the checksum of the HPMC handler:
	 * 1. The IVA करोes not poपूर्णांक to PDC/PDH space (ie: the OS has installed
	 *    its own IVA).
	 * 2. The word at IVA + 32 is nonzero.
	 * 3. If Length (IVA + 60) is not zero, then Length (IVA + 60) and
	 *    Address (IVA + 56) are word-aligned.
	 * 4. The checksum of the 8 words starting at IVA + 32 plus the sum of
	 *    the Length/4 words starting at Address is zero.
	 */

	/* Setup IVA and compute checksum क्रम HPMC handler */
	ivap[6] = (u32)__pa(os_hpmc);

	hpmcp = (u32 *)os_hpmc;

	क्रम (i=0; i<8; i++)
	    check += ivap[i];

	ivap[5] = -check;
	pr_debug("initialize_ivt: IVA[6] = 0x%08x\n", ivap[6]);
पूर्ण
	

/* early_trap_init() is called beक्रमe we set up kernel mappings and
 * ग_लिखो-protect the kernel */
व्योम  __init early_trap_init(व्योम)
अणु
	बाह्य स्थिर व्योम fault_vector_20;

#अगर_अघोषित CONFIG_64BIT
	बाह्य स्थिर व्योम fault_vector_11;
	initialize_ivt(&fault_vector_11);
#पूर्ण_अगर

	initialize_ivt(&fault_vector_20);
पूर्ण

व्योम __init trap_init(व्योम)
अणु
पूर्ण
