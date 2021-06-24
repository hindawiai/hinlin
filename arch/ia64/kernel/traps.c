<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Architecture-specअगरic trap handling.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 *
 * 05/12/00 grao <goutham.rao@पूर्णांकel.com> : added isr in siginfo क्रम संक_भ_त्रुटि
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/tty.h>
#समावेश <linux/vt_kern.h>		/* For unblank_screen() */
#समावेश <linux/export.h>
#समावेश <linux/extable.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/delay.h>		/* क्रम ssleep() */
#समावेश <linux/kdebug.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/fpswa.h>
#समावेश <यंत्र/पूर्णांकrinsics.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/setup.h>

fpswa_पूर्णांकerface_t *fpswa_पूर्णांकerface;
EXPORT_SYMBOL(fpswa_पूर्णांकerface);

व्योम __init
trap_init (व्योम)
अणु
	अगर (ia64_boot_param->fpswa)
		/* FPSWA fixup: make the पूर्णांकerface poपूर्णांकer a kernel भव address: */
		fpswa_पूर्णांकerface = __va(ia64_boot_param->fpswa);
पूर्ण

पूर्णांक
die (स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अटल काष्ठा अणु
		spinlock_t lock;
		u32 lock_owner;
		पूर्णांक lock_owner_depth;
	पूर्ण die = अणु
		.lock =	__SPIN_LOCK_UNLOCKED(die.lock),
		.lock_owner = -1,
		.lock_owner_depth = 0
	पूर्ण;
	अटल पूर्णांक die_counter;
	पूर्णांक cpu = get_cpu();

	अगर (die.lock_owner != cpu) अणु
		console_verbose();
		spin_lock_irq(&die.lock);
		die.lock_owner = cpu;
		die.lock_owner_depth = 0;
		bust_spinlocks(1);
	पूर्ण
	put_cpu();

	अगर (++die.lock_owner_depth < 3) अणु
		prपूर्णांकk("%s[%d]: %s %ld [%d]\n",
		current->comm, task_pid_nr(current), str, err, ++die_counter);
		अगर (notअगरy_die(DIE_OOPS, str, regs, err, 255, संक_अंश)
	            != NOTIFY_STOP)
			show_regs(regs);
		अन्यथा
			regs = शून्य;
  	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "Recursive die() failure, output suppressed\n");

	bust_spinlocks(0);
	die.lock_owner = -1;
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die.lock);

	अगर (!regs)
		वापस 1;

	अगर (panic_on_oops)
		panic("Fatal exception");

  	करो_निकास(संक_अंश);
	वापस 0;
पूर्ण

पूर्णांक
die_अगर_kernel (अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अगर (!user_mode(regs))
		वापस die(str, regs, err);
	वापस 0;
पूर्ण

व्योम
__kprobes ia64_bad_अवरोध (अचिन्हित दीर्घ अवरोध_num, काष्ठा pt_regs *regs)
अणु
	पूर्णांक sig, code;

	चयन (अवरोध_num) अणु
	      हाल 0: /* unknown error (used by GCC क्रम __builtin_पात()) */
		अगर (notअगरy_die(DIE_BREAK, "break 0", regs, अवरोध_num, TRAP_BRKPT, SIGTRAP)
			       	== NOTIFY_STOP)
			वापस;
		अगर (die_अगर_kernel("bugcheck!", regs, अवरोध_num))
			वापस;
		sig = संक_अवैध; code = ILL_ILLOPC;
		अवरोध;

	      हाल 1: /* पूर्णांकeger भागide by zero */
		sig = संक_भ_त्रुटि; code = FPE_INTDIV;
		अवरोध;

	      हाल 2: /* पूर्णांकeger overflow */
		sig = संक_भ_त्रुटि; code = FPE_INTOVF;
		अवरोध;

	      हाल 3: /* range check/bounds check */
		sig = संक_भ_त्रुटि; code = FPE_FLTSUB;
		अवरोध;

	      हाल 4: /* null poपूर्णांकer dereference */
		sig = संक_अंश; code = SEGV_MAPERR;
		अवरोध;

	      हाल 5: /* misaligned data */
		sig = संक_अंश; code = BUS_ADRALN;
		अवरोध;

	      हाल 6: /* decimal overflow */
		sig = संक_भ_त्रुटि; code = __FPE_DECOVF;
		अवरोध;

	      हाल 7: /* decimal भागide by zero */
		sig = संक_भ_त्रुटि; code = __FPE_DECDIV;
		अवरोध;

	      हाल 8: /* packed decimal error */
		sig = संक_भ_त्रुटि; code = __FPE_DECERR;
		अवरोध;

	      हाल 9: /* invalid ASCII digit */
		sig = संक_भ_त्रुटि; code = __FPE_INVASC;
		अवरोध;

	      हाल 10: /* invalid decimal digit */
		sig = संक_भ_त्रुटि; code = __FPE_INVDEC;
		अवरोध;

	      हाल 11: /* paragraph stack overflow */
		sig = संक_अंश; code = __SEGV_PSTKOVF;
		अवरोध;

	      हाल 0x3f000 ... 0x3ffff:	/* bundle-update in progress */
		sig = संक_अवैध; code = __ILL_BNDMOD;
		अवरोध;

	      शेष:
		अगर ((अवरोध_num < 0x40000 || अवरोध_num > 0x100000)
		    && die_अगर_kernel("Bad break", regs, अवरोध_num))
			वापस;

		अगर (अवरोध_num < 0x80000) अणु
			sig = संक_अवैध; code = __ILL_BREAK;
		पूर्ण अन्यथा अणु
			अगर (notअगरy_die(DIE_BREAK, "bad break", regs, अवरोध_num, TRAP_BRKPT, SIGTRAP)
					== NOTIFY_STOP)
				वापस;
			sig = SIGTRAP; code = TRAP_BRKPT;
		पूर्ण
	पूर्ण
	क्रमce_sig_fault(sig, code,
			(व्योम __user *) (regs->cr_iip + ia64_psr(regs)->ri),
			अवरोध_num, 0 /* clear __ISR_VALID */, 0);
पूर्ण

/*
 * disabled_fph_fault() is called when a user-level process attempts to access f32..f127
 * and it करोesn't own the fp-high रेजिस्टर partition.  When this happens, we save the
 * current fph partition in the task_काष्ठा of the fpu-owner (अगर necessary) and then load
 * the fp-high partition of the current task (अगर necessary).  Note that the kernel has
 * access to fph by the समय we get here, as the IVT's "Disabled FP-Register" handler takes
 * care of clearing psr.dfh.
 */
अटल अंतरभूत व्योम
disabled_fph_fault (काष्ठा pt_regs *regs)
अणु
	काष्ठा ia64_psr *psr = ia64_psr(regs);

	/* first, grant user-level access to fph partition: */
	psr->dfh = 0;

	/*
	 * Make sure that no other task माला_लो in on this processor
	 * जबतक we're claiming the FPU
	 */
	preempt_disable();
#अगर_अघोषित CONFIG_SMP
	अणु
		काष्ठा task_काष्ठा *fpu_owner
			= (काष्ठा task_काष्ठा *)ia64_get_kr(IA64_KR_FPU_OWNER);

		अगर (ia64_is_local_fpu_owner(current)) अणु
			preempt_enable_no_resched();
			वापस;
		पूर्ण

		अगर (fpu_owner)
			ia64_flush_fph(fpu_owner);
	पूर्ण
#पूर्ण_अगर /* !CONFIG_SMP */
	ia64_set_local_fpu_owner(current);
	अगर ((current->thपढ़ो.flags & IA64_THREAD_FPH_VALID) != 0) अणु
		__ia64_load_fpu(current->thपढ़ो.fph);
		psr->mfh = 0;
	पूर्ण अन्यथा अणु
		__ia64_init_fpu();
		/*
		 * Set mfh because the state in thपढ़ो.fph करोes not match the state in
		 * the fph partition.
		 */
		psr->mfh = 1;
	पूर्ण
	preempt_enable_no_resched();
पूर्ण

अटल अंतरभूत पूर्णांक
fp_emulate (पूर्णांक fp_fault, व्योम *bundle, दीर्घ *ipsr, दीर्घ *fpsr, दीर्घ *isr, दीर्घ *pr, दीर्घ *अगरs,
	    काष्ठा pt_regs *regs)
अणु
	fp_state_t fp_state;
	fpswa_ret_t ret;

	अगर (!fpswa_पूर्णांकerface)
		वापस -1;

	स_रखो(&fp_state, 0, माप(fp_state_t));

	/*
	 * compute fp_state.  only FP रेजिस्टरs f6 - f11 are used by the
	 * kernel, so set those bits in the mask and set the low अस्थिर
	 * poपूर्णांकer to poपूर्णांक to these रेजिस्टरs.
	 */
	fp_state.biपंचांगask_low64 = 0xfc0;  /* bit6..bit11 */

	fp_state.fp_state_low_अस्थिर = (fp_state_low_अस्थिर_t *) &regs->f6;
	/*
	 * अचिन्हित दीर्घ (*EFI_FPSWA) (
	 *      अचिन्हित दीर्घ    trap_type,
	 *	व्योम             *Bundle,
	 *	अचिन्हित दीर्घ    *pipsr,
	 *	अचिन्हित दीर्घ    *pfsr,
	 *	अचिन्हित दीर्घ    *pisr,
	 *	अचिन्हित दीर्घ    *ppreds,
	 *	अचिन्हित दीर्घ    *pअगरs,
	 *	व्योम             *fp_state);
	 */
	ret = (*fpswa_पूर्णांकerface->fpswa)((अचिन्हित दीर्घ) fp_fault, bundle,
					(अचिन्हित दीर्घ *) ipsr, (अचिन्हित दीर्घ *) fpsr,
					(अचिन्हित दीर्घ *) isr, (अचिन्हित दीर्घ *) pr,
					(अचिन्हित दीर्घ *) अगरs, &fp_state);

	वापस ret.status;
पूर्ण

काष्ठा fpu_swa_msg अणु
	अचिन्हित दीर्घ count;
	अचिन्हित दीर्घ समय;
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा fpu_swa_msg, cpulast);
DECLARE_PER_CPU(काष्ठा fpu_swa_msg, cpulast);
अटल काष्ठा fpu_swa_msg last __cacheline_aligned;


/*
 * Handle भग्नing-poपूर्णांक assist faults and traps.
 */
अटल पूर्णांक
handle_fpu_swa (पूर्णांक fp_fault, काष्ठा pt_regs *regs, अचिन्हित दीर्घ isr)
अणु
	दीर्घ exception, bundle[2];
	अचिन्हित दीर्घ fault_ip;

	fault_ip = regs->cr_iip;
	अगर (!fp_fault && (ia64_psr(regs)->ri == 0))
		fault_ip -= 16;
	अगर (copy_from_user(bundle, (व्योम __user *) fault_ip, माप(bundle)))
		वापस -1;

	अगर (!(current->thपढ़ो.flags & IA64_THREAD_FPEMU_NOPRINT))  अणु
		अचिन्हित दीर्घ count, current_jअगरfies = jअगरfies;
		काष्ठा fpu_swa_msg *cp = this_cpu_ptr(&cpulast);

		अगर (unlikely(current_jअगरfies > cp->समय))
			cp->count = 0;
		अगर (unlikely(cp->count < 5)) अणु
			cp->count++;
			cp->समय = current_jअगरfies + 5 * HZ;

			/* minimize races by grabbing a copy of count BEFORE checking last.समय. */
			count = last.count;
			barrier();

			/*
			 * Lower 4 bits are used as a count. Upper bits are a sequence
			 * number that is updated when count is reset. The cmpxchg will
			 * fail is seqno has changed. This minimizes mutiple cpus
			 * resetting the count.
			 */
			अगर (current_jअगरfies > last.समय)
				(व्योम) cmpxchg_acq(&last.count, count, 16 + (count & ~15));

			/* used fetchadd to atomically update the count */
			अगर ((last.count & 15) < 5 && (ia64_fetchadd(1, &last.count, acq) & 15) < 5) अणु
				last.समय = current_jअगरfies + 5 * HZ;
				prपूर्णांकk(KERN_WARNING
		       			"%s(%d): floating-point assist fault at ip %016lx, isr %016lx\n",
		       			current->comm, task_pid_nr(current), regs->cr_iip + ia64_psr(regs)->ri, isr);
			पूर्ण
		पूर्ण
	पूर्ण

	exception = fp_emulate(fp_fault, bundle, &regs->cr_ipsr, &regs->ar_fpsr, &isr, &regs->pr,
			       &regs->cr_अगरs, regs);
	अगर (fp_fault) अणु
		अगर (exception == 0) अणु
			/* emulation was successful */
			ia64_increment_ip(regs);
		पूर्ण अन्यथा अगर (exception == -1) अणु
			prपूर्णांकk(KERN_ERR "handle_fpu_swa: fp_emulate() returned -1\n");
			वापस -1;
		पूर्ण अन्यथा अणु
			/* is next inकाष्ठाion a trap? */
			पूर्णांक si_code;

			अगर (exception & 2) अणु
				ia64_increment_ip(regs);
			पूर्ण
			si_code = FPE_FLTUNK;	/* शेष code */
			अगर (isr & 0x11) अणु
				si_code = FPE_FLTINV;
			पूर्ण अन्यथा अगर (isr & 0x22) अणु
				/* denormal opeअक्रम माला_लो the same si_code as underflow 
				* see arch/i386/kernel/traps.c:math_error()  */
				si_code = FPE_FLTUND;
			पूर्ण अन्यथा अगर (isr & 0x44) अणु
				si_code = FPE_FLTDIV;
			पूर्ण
			क्रमce_sig_fault(संक_भ_त्रुटि, si_code,
					(व्योम __user *) (regs->cr_iip + ia64_psr(regs)->ri),
					0, __ISR_VALID, isr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (exception == -1) अणु
			prपूर्णांकk(KERN_ERR "handle_fpu_swa: fp_emulate() returned -1\n");
			वापस -1;
		पूर्ण अन्यथा अगर (exception != 0) अणु
			/* उठाओ exception */
			पूर्णांक si_code;

			si_code = FPE_FLTUNK;	/* शेष code */
			अगर (isr & 0x880) अणु
				si_code = FPE_FLTOVF;
			पूर्ण अन्यथा अगर (isr & 0x1100) अणु
				si_code = FPE_FLTUND;
			पूर्ण अन्यथा अगर (isr & 0x2200) अणु
				si_code = FPE_FLTRES;
			पूर्ण
			क्रमce_sig_fault(संक_भ_त्रुटि, si_code,
					(व्योम __user *) (regs->cr_iip + ia64_psr(regs)->ri),
					0, __ISR_VALID, isr);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा illegal_op_वापस अणु
	अचिन्हित दीर्घ fkt, arg1, arg2, arg3;
पूर्ण;

काष्ठा illegal_op_वापस
ia64_illegal_op_fault (अचिन्हित दीर्घ ec, दीर्घ arg1, दीर्घ arg2, दीर्घ arg3,
		       दीर्घ arg4, दीर्घ arg5, दीर्घ arg6, दीर्घ arg7,
		       काष्ठा pt_regs regs)
अणु
	काष्ठा illegal_op_वापस rv;
	अक्षर buf[128];

#अगर_घोषित CONFIG_IA64_BRL_EMU
	अणु
		बाह्य काष्ठा illegal_op_वापस ia64_emulate_brl (काष्ठा pt_regs *, अचिन्हित दीर्घ);

		rv = ia64_emulate_brl(&regs, ec);
		अगर (rv.fkt != (अचिन्हित दीर्घ) -1)
			वापस rv;
	पूर्ण
#पूर्ण_अगर

	प्र_लिखो(buf, "IA-64 Illegal operation fault");
	rv.fkt = 0;
	अगर (die_अगर_kernel(buf, &regs, 0))
		वापस rv;

	क्रमce_sig_fault(संक_अवैध, ILL_ILLOPC,
			(व्योम __user *) (regs.cr_iip + ia64_psr(&regs)->ri),
			0, 0, 0);
	वापस rv;
पूर्ण

व्योम __kprobes
ia64_fault (अचिन्हित दीर्घ vector, अचिन्हित दीर्घ isr, अचिन्हित दीर्घ अगरa,
	    अचिन्हित दीर्घ iim, अचिन्हित दीर्घ itir, दीर्घ arg5, दीर्घ arg6,
	    दीर्घ arg7, काष्ठा pt_regs regs)
अणु
	अचिन्हित दीर्घ code, error = isr, iip;
	अक्षर buf[128];
	पूर्णांक result, sig, si_code;
	अटल स्थिर अक्षर *reason[] = अणु
		"IA-64 Illegal Operation fault",
		"IA-64 Privileged Operation fault",
		"IA-64 Privileged Register fault",
		"IA-64 Reserved Register/Field fault",
		"Disabled Instruction Set Transition fault",
		"Unknown fault 5", "Unknown fault 6", "Unknown fault 7", "Illegal Hazard fault",
		"Unknown fault 9", "Unknown fault 10", "Unknown fault 11", "Unknown fault 12",
		"Unknown fault 13", "Unknown fault 14", "Unknown fault 15"
	पूर्ण;

	अगर ((isr & IA64_ISR_NA) && ((isr & IA64_ISR_CODE_MASK) == IA64_ISR_CODE_LFETCH)) अणु
		/*
		 * This fault was due to lfetch.fault, set "ed" bit in the psr to cancel
		 * the lfetch.
		 */
		ia64_psr(&regs)->ed = 1;
		वापस;
	पूर्ण

	iip = regs.cr_iip + ia64_psr(&regs)->ri;

	चयन (vector) अणु
	      हाल 24: /* General Exception */
		code = (isr >> 4) & 0xf;
		प्र_लिखो(buf, "General Exception: %s%s", reason[code],
			(code == 3) ? ((isr & (1UL << 37))
				       ? " (RSE access)" : " (data access)") : "");
		अगर (code == 8) अणु
# अगरdef CONFIG_IA64_PRINT_HAZARDS
			prपूर्णांकk("%s[%d]: possible hazard @ ip=%016lx (pr = %016lx)\n",
			       current->comm, task_pid_nr(current),
			       regs.cr_iip + ia64_psr(&regs)->ri, regs.pr);
# endअगर
			वापस;
		पूर्ण
		अवरोध;

	      हाल 25: /* Disabled FP-Register */
		अगर (isr & 2) अणु
			disabled_fph_fault(&regs);
			वापस;
		पूर्ण
		प्र_लिखो(buf, "Disabled FPL fault---not supposed to happen!");
		अवरोध;

	      हाल 26: /* NaT Consumption */
		अगर (user_mode(&regs)) अणु
			व्योम __user *addr;

			अगर (((isr >> 4) & 0xf) == 2) अणु
				/* NaT page consumption */
				sig = संक_अंश;
				code = SEGV_ACCERR;
				addr = (व्योम __user *) अगरa;
			पूर्ण अन्यथा अणु
				/* रेजिस्टर NaT consumption */
				sig = संक_अवैध;
				code = ILL_ILLOPN;
				addr = (व्योम __user *) (regs.cr_iip
							+ ia64_psr(&regs)->ri);
			पूर्ण
			क्रमce_sig_fault(sig, code, addr,
					vector, __ISR_VALID, isr);
			वापस;
		पूर्ण अन्यथा अगर (ia64_करोne_with_exception(&regs))
			वापस;
		प्र_लिखो(buf, "NaT consumption");
		अवरोध;

	      हाल 31: /* Unsupported Data Reference */
		अगर (user_mode(&regs)) अणु
			क्रमce_sig_fault(संक_अवैध, ILL_ILLOPN, (व्योम __user *) iip,
					vector, __ISR_VALID, isr);
			वापस;
		पूर्ण
		प्र_लिखो(buf, "Unsupported data reference");
		अवरोध;

	      हाल 29: /* Debug */
	      हाल 35: /* Taken Branch Trap */
	      हाल 36: /* Single Step Trap */
		अगर (fsys_mode(current, &regs)) अणु
			बाह्य अक्षर __kernel_syscall_via_अवरोध[];
			/*
			 * Got a trap in fsys-mode: Taken Branch Trap
			 * and Single Step trap need special handling;
			 * Debug trap is ignored (we disable it here
			 * and re-enable it in the lower-privilege trap).
			 */
			अगर (unlikely(vector == 29)) अणु
				set_thपढ़ो_flag(TIF_DB_DISABLED);
				ia64_psr(&regs)->db = 0;
				ia64_psr(&regs)->lp = 1;
				वापस;
			पूर्ण
			/* re-करो the प्रणाली call via अवरोध 0x100000: */
			regs.cr_iip = (अचिन्हित दीर्घ) __kernel_syscall_via_अवरोध;
			ia64_psr(&regs)->ri = 0;
			ia64_psr(&regs)->cpl = 3;
			वापस;
		पूर्ण
		चयन (vector) अणु
		      शेष:
		      हाल 29:
			si_code = TRAP_HWBKPT;
#अगर_घोषित CONFIG_ITANIUM
			/*
			 * Erratum 10 (IFA may contain incorrect address) now has
			 * "NoFix" status.  There are no plans क्रम fixing this.
			 */
			अगर (ia64_psr(&regs)->is == 0)
			  अगरa = regs.cr_iip;
#पूर्ण_अगर
			अवरोध;
		      हाल 35: si_code = TRAP_BRANCH; अगरa = 0; अवरोध;
		      हाल 36: si_code = TRAP_TRACE; अगरa = 0; अवरोध;
		पूर्ण
		अगर (notअगरy_die(DIE_FAULT, "ia64_fault", &regs, vector, si_code, SIGTRAP)
			       	== NOTIFY_STOP)
			वापस;
		क्रमce_sig_fault(SIGTRAP, si_code, (व्योम __user *) अगरa,
				0, __ISR_VALID, isr);
		वापस;

	      हाल 32: /* fp fault */
	      हाल 33: /* fp trap */
		result = handle_fpu_swa((vector == 32) ? 1 : 0, &regs, isr);
		अगर ((result < 0) || (current->thपढ़ो.flags & IA64_THREAD_FPEMU_संक_भ_त्रुटि)) अणु
			क्रमce_sig_fault(संक_भ_त्रुटि, FPE_FLTINV, (व्योम __user *) iip,
					0, __ISR_VALID, isr);
		पूर्ण
		वापस;

	      हाल 34:
		अगर (isr & 0x2) अणु
			/* Lower-Privilege Transfer Trap */

			/* If we disabled debug traps during an fsyscall,
			 * re-enable them here.
			 */
			अगर (test_thपढ़ो_flag(TIF_DB_DISABLED)) अणु
				clear_thपढ़ो_flag(TIF_DB_DISABLED);
				ia64_psr(&regs)->db = 1;
			पूर्ण

			/*
			 * Just clear PSR.lp and then वापस immediately:
			 * all the पूर्णांकeresting work (e.g., संकेत delivery)
			 * is करोne in the kernel निकास path.
			 */
			ia64_psr(&regs)->lp = 0;
			वापस;
		पूर्ण अन्यथा अणु
			/* Unimplemented Instr. Address Trap */
			अगर (user_mode(&regs)) अणु
				क्रमce_sig_fault(संक_अवैध, ILL_BADIADDR,
						(व्योम __user *) iip,
						0, 0, 0);
				वापस;
			पूर्ण
			प्र_लिखो(buf, "Unimplemented Instruction Address fault");
		पूर्ण
		अवरोध;

	      हाल 45:
		prपूर्णांकk(KERN_ERR "Unexpected IA-32 exception (Trap 45)\n");
		prपूर्णांकk(KERN_ERR "  iip - 0x%lx, ifa - 0x%lx, isr - 0x%lx\n",
		       iip, अगरa, isr);
		क्रमce_sig(संक_अंश);
		वापस;

	      हाल 46:
		prपूर्णांकk(KERN_ERR "Unexpected IA-32 intercept trap (Trap 46)\n");
		prपूर्णांकk(KERN_ERR "  iip - 0x%lx, ifa - 0x%lx, isr - 0x%lx, iim - 0x%lx\n",
		       iip, अगरa, isr, iim);
		क्रमce_sig(संक_अंश);
		वापस;

	      हाल 47:
		प्र_लिखो(buf, "IA-32 Interruption Fault (int 0x%lx)", isr >> 16);
		अवरोध;

	      शेष:
		प्र_लिखो(buf, "Fault %lu", vector);
		अवरोध;
	पूर्ण
	अगर (!die_अगर_kernel(buf, &regs, error))
		क्रमce_sig(संक_अवैध);
पूर्ण
