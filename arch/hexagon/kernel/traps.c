<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Kernel traps/events क्रम Hexagon processor
 *
 * Copyright (c) 2010-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/module.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/tracehook.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/vm_fault.h>
#समावेश <यंत्र/syscall.h>
#समावेश <यंत्र/रेजिस्टरs.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/sections.h>
#अगर_घोषित CONFIG_KGDB
# include <linux/kgdb.h>
#पूर्ण_अगर

#घोषणा TRAP_SYSCALL	1
#घोषणा TRAP_DEBUG	0xdb

व्योम __init trap_init(व्योम)
अणु
पूर्ण

#अगर_घोषित CONFIG_GENERIC_BUG
/* Maybe should resemble arch/sh/kernel/traps.c ?? */
पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ addr)
अणु
	वापस 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_GENERIC_BUG */

अटल स्थिर अक्षर *ex_name(पूर्णांक ex)
अणु
	चयन (ex) अणु
	हाल HVM_GE_C_XPROT:
	हाल HVM_GE_C_XUSER:
		वापस "Execute protection fault";
	हाल HVM_GE_C_RPROT:
	हाल HVM_GE_C_RUSER:
		वापस "Read protection fault";
	हाल HVM_GE_C_WPROT:
	हाल HVM_GE_C_WUSER:
		वापस "Write protection fault";
	हाल HVM_GE_C_XMAL:
		वापस "Misaligned instruction";
	हाल HVM_GE_C_WREG:
		वापस "Multiple writes to same register in packet";
	हाल HVM_GE_C_PCAL:
		वापस "Program counter values that are not properly aligned";
	हाल HVM_GE_C_RMAL:
		वापस "Misaligned data load";
	हाल HVM_GE_C_WMAL:
		वापस "Misaligned data store";
	हाल HVM_GE_C_INVI:
	हाल HVM_GE_C_PRIVI:
		वापस "Illegal instruction";
	हाल HVM_GE_C_BUS:
		वापस "Precise bus error";
	हाल HVM_GE_C_CACHE:
		वापस "Cache error";

	हाल 0xdb:
		वापस "Debugger trap";

	शेष:
		वापस "Unrecognized exception";
	पूर्ण
पूर्ण

अटल व्योम करो_show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *fp,
			  अचिन्हित दीर्घ ip, स्थिर अक्षर *loglvl)
अणु
	पूर्णांक kstack_depth_to_prपूर्णांक = 24;
	अचिन्हित दीर्घ offset, size;
	स्थिर अक्षर *name = शून्य;
	अचिन्हित दीर्घ *newfp;
	अचिन्हित दीर्घ low, high;
	अक्षर पंचांगpstr[128];
	अक्षर *modname;
	पूर्णांक i;

	अगर (task == शून्य)
		task = current;

	prपूर्णांकk("%sCPU#%d, %s/%d, Call Trace:\n", loglvl, raw_smp_processor_id(),
		task->comm, task_pid_nr(task));

	अगर (fp == शून्य) अणु
		अगर (task == current) अणु
			यंत्र("%0 = r30" : "=r" (fp));
		पूर्ण अन्यथा अणु
			fp = (अचिन्हित दीर्घ *)
			     ((काष्ठा hexagon_चयन_stack *)
			     task->thपढ़ो.चयन_sp)->fp;
		पूर्ण
	पूर्ण

	अगर ((((अचिन्हित दीर्घ) fp) & 0x3) || ((अचिन्हित दीर्घ) fp < 0x1000)) अणु
		prपूर्णांकk("%s-- Corrupt frame pointer %p\n", loglvl, fp);
		वापस;
	पूर्ण

	/* Saved link reg is one word above FP */
	अगर (!ip)
		ip = *(fp+1);

	/* Expect kernel stack to be in-bounds */
	low = (अचिन्हित दीर्घ)task_stack_page(task);
	high = low + THREAD_SIZE - 8;
	low += माप(काष्ठा thपढ़ो_info);

	क्रम (i = 0; i < kstack_depth_to_prपूर्णांक; i++) अणु

		name = kallsyms_lookup(ip, &size, &offset, &modname, पंचांगpstr);

		prपूर्णांकk("%s[%p] 0x%lx: %s + 0x%lx", loglvl, fp, ip, name, offset);
		अगर (((अचिन्हित दीर्घ) fp < low) || (high < (अचिन्हित दीर्घ) fp))
			prपूर्णांकk(KERN_CONT " (FP out of bounds!)");
		अगर (modname)
			prपूर्णांकk(KERN_CONT " [%s] ", modname);
		prपूर्णांकk(KERN_CONT "\n");

		newfp = (अचिन्हित दीर्घ *) *fp;

		अगर (((अचिन्हित दीर्घ) newfp) & 0x3) अणु
			prपूर्णांकk("%s-- Corrupt frame pointer %p\n", loglvl, newfp);
			अवरोध;
		पूर्ण

		/* Attempt to जारी past exception. */
		अगर (0 == newfp) अणु
			काष्ठा pt_regs *regs = (काष्ठा pt_regs *) (((व्योम *)fp)
						+ 8);

			अगर (regs->syscall_nr != -1) अणु
				prपूर्णांकk("%s-- trap0 -- syscall_nr: %ld", loglvl,
					regs->syscall_nr);
				prपूर्णांकk(KERN_CONT "  psp: %lx  elr: %lx\n",
					 pt_psp(regs), pt_elr(regs));
				अवरोध;
			पूर्ण अन्यथा अणु
				/* really want to see more ... */
				kstack_depth_to_prपूर्णांक += 6;
				prपूर्णांकk("%s-- %s (0x%lx)  badva: %lx\n", loglvl,
					ex_name(pt_cause(regs)), pt_cause(regs),
					pt_badva(regs));
			पूर्ण

			newfp = (अचिन्हित दीर्घ *) regs->r30;
			ip = pt_elr(regs);
		पूर्ण अन्यथा अणु
			ip = *(newfp + 1);
		पूर्ण

		/* If link reg is null, we are करोne. */
		अगर (ip == 0x0)
			अवरोध;

		/* If newfp isn't larger, we're tracing garbage. */
		अगर (newfp > fp)
			fp = newfp;
		अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *fp, स्थिर अक्षर *loglvl)
अणु
	/* Saved link reg is one word above FP */
	करो_show_stack(task, fp, 0, loglvl);
पूर्ण

पूर्णांक die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अटल काष्ठा अणु
		spinlock_t lock;
		पूर्णांक counter;
	पूर्ण die = अणु
		.lock = __SPIN_LOCK_UNLOCKED(die.lock),
		.counter = 0
	पूर्ण;

	console_verbose();
	oops_enter();

	spin_lock_irq(&die.lock);
	bust_spinlocks(1);
	prपूर्णांकk(KERN_EMERG "Oops: %s[#%d]:\n", str, ++die.counter);

	अगर (notअगरy_die(DIE_OOPS, str, regs, err, pt_cause(regs), संक_अंश) ==
	    NOTIFY_STOP)
		वापस 1;

	prपूर्णांक_modules();
	show_regs(regs);
	करो_show_stack(current, &regs->r30, pt_elr(regs), KERN_EMERG);

	bust_spinlocks(0);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);

	spin_unlock_irq(&die.lock);

	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");

	अगर (panic_on_oops)
		panic("Fatal exception");

	oops_निकास();
	करो_निकास(err);
	वापस 0;
पूर्ण

पूर्णांक die_अगर_kernel(अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अगर (!user_mode(regs))
		वापस die(str, regs, err);
	अन्यथा
		वापस 0;
पूर्ण

/*
 * It's not clear that misaligned fetches are ever recoverable.
 */
अटल व्योम misaligned_inकाष्ठाion(काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel("Misaligned Instruction", regs, 0);
	क्रमce_sig(SIGBUS);
पूर्ण

/*
 * Misaligned loads and stores, on the other hand, can be
 * emulated, and probably should be, some day.  But क्रम now
 * they will be considered fatal.
 */
अटल व्योम misaligned_data_load(काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel("Misaligned Data Load", regs, 0);
	क्रमce_sig(SIGBUS);
पूर्ण

अटल व्योम misaligned_data_store(काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel("Misaligned Data Store", regs, 0);
	क्रमce_sig(SIGBUS);
पूर्ण

अटल व्योम illegal_inकाष्ठाion(काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel("Illegal Instruction", regs, 0);
	क्रमce_sig(संक_अवैध);
पूर्ण

/*
 * Precise bus errors may be recoverable with a a retry,
 * but क्रम now, treat them as irrecoverable.
 */
अटल व्योम precise_bus_error(काष्ठा pt_regs *regs)
अणु
	die_अगर_kernel("Precise Bus Error", regs, 0);
	क्रमce_sig(SIGBUS);
पूर्ण

/*
 * If anything is to be करोne here other than panic,
 * it will probably be complex and migrate to another
 * source module.  For now, just die.
 */
अटल व्योम cache_error(काष्ठा pt_regs *regs)
अणु
	die("Cache Error", regs, 0);
पूर्ण

/*
 * General exception handler
 */
व्योम करो_genex(काष्ठा pt_regs *regs)
अणु
	/*
	 * Decode Cause and Dispatch
	 */
	चयन (pt_cause(regs)) अणु
	हाल HVM_GE_C_XPROT:
	हाल HVM_GE_C_XUSER:
		execute_protection_fault(regs);
		अवरोध;
	हाल HVM_GE_C_RPROT:
	हाल HVM_GE_C_RUSER:
		पढ़ो_protection_fault(regs);
		अवरोध;
	हाल HVM_GE_C_WPROT:
	हाल HVM_GE_C_WUSER:
		ग_लिखो_protection_fault(regs);
		अवरोध;
	हाल HVM_GE_C_XMAL:
		misaligned_inकाष्ठाion(regs);
		अवरोध;
	हाल HVM_GE_C_WREG:
		illegal_inकाष्ठाion(regs);
		अवरोध;
	हाल HVM_GE_C_PCAL:
		misaligned_inकाष्ठाion(regs);
		अवरोध;
	हाल HVM_GE_C_RMAL:
		misaligned_data_load(regs);
		अवरोध;
	हाल HVM_GE_C_WMAL:
		misaligned_data_store(regs);
		अवरोध;
	हाल HVM_GE_C_INVI:
	हाल HVM_GE_C_PRIVI:
		illegal_inकाष्ठाion(regs);
		अवरोध;
	हाल HVM_GE_C_BUS:
		precise_bus_error(regs);
		अवरोध;
	हाल HVM_GE_C_CACHE:
		cache_error(regs);
		अवरोध;
	शेष:
		/* Halt and catch fire */
		panic("Unrecognized exception 0x%lx\n", pt_cause(regs));
		अवरोध;
	पूर्ण
पूर्ण

/* Indirect प्रणाली call dispatch */
दीर्घ sys_syscall(व्योम)
अणु
	prपूर्णांकk(KERN_ERR "sys_syscall invoked!\n");
	वापस -ENOSYS;
पूर्ण

व्योम करो_trap0(काष्ठा pt_regs *regs)
अणु
	syscall_fn syscall;

	चयन (pt_cause(regs)) अणु
	हाल TRAP_SYSCALL:
		/* System call is trap0 #1 */

		/* allow strace to catch syscall args  */
		अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACE) &&
			tracehook_report_syscall_entry(regs)))
			वापस;  /*  वापस -ENOSYS somewhere?  */

		/* Interrupts should be re-enabled क्रम syscall processing */
		__vmsetie(VM_INT_ENABLE);

		/*
		 * System call number is in r6, arguments in r0..r5.
		 * Fortunately, no Linux syscall has more than 6 arguments,
		 * and Hexagon ABI passes first 6 arguments in रेजिस्टरs.
		 * 64-bit arguments are passed in odd/even रेजिस्टर pairs.
		 * Fortunately, we have no प्रणाली calls that take more
		 * than three arguments with more than one 64-bit value.
		 * Should that change, we'd need to redesign to copy
		 * between user and kernel stacks.
		 */
		regs->syscall_nr = regs->r06;

		/*
		 * GPR R0 carries the first parameter, and is also used
		 * to report the वापस value.  We need a backup of
		 * the user's value in हाल we need to करो a late restart
		 * of the प्रणाली call.
		 */
		regs->restart_r0 = regs->r00;

		अगर ((अचिन्हित दीर्घ) regs->syscall_nr >= __NR_syscalls) अणु
			regs->r00 = -1;
		पूर्ण अन्यथा अणु
			syscall = (syscall_fn)
				  (sys_call_table[regs->syscall_nr]);
			regs->r00 = syscall(regs->r00, regs->r01,
				   regs->r02, regs->r03,
				   regs->r04, regs->r05);
		पूर्ण

		/* allow strace to get the syscall वापस state  */
		अगर (unlikely(test_thपढ़ो_flag(TIF_SYSCALL_TRACE)))
			tracehook_report_syscall_निकास(regs, 0);

		अवरोध;
	हाल TRAP_DEBUG:
		/* Trap0 0xdb is debug अवरोधpoपूर्णांक */
		अगर (user_mode(regs)) अणु
			/*
			 * Some architecures add some per-thपढ़ो state
			 * to distinguish between अवरोधpoपूर्णांक traps and
			 * trace traps.  We may want to करो that, and
			 * set the si_code value appropriately, or we
			 * may want to use a dअगरferent trap0 flavor.
			 */
			क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT,
					(व्योम __user *) pt_elr(regs));
		पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_KGDB
			kgdb_handle_exception(pt_cause(regs), SIGTRAP,
					      TRAP_BRKPT, regs);
#पूर्ण_अगर
		पूर्ण
		अवरोध;
	पूर्ण
	/* Ignore other trap0 codes क्रम now, especially 0 (Angel calls) */
पूर्ण

/*
 * Machine check exception handler
 */
व्योम करो_machcheck(काष्ठा pt_regs *regs)
अणु
	/* Halt and catch fire */
	__vmstop();
पूर्ण

/*
 * Treat this like the old 0xdb trap.
 */

व्योम करो_debug_exception(काष्ठा pt_regs *regs)
अणु
	regs->hvmer.vmest &= ~HVM_VMEST_CAUSE_MSK;
	regs->hvmer.vmest |= (TRAP_DEBUG << HVM_VMEST_CAUSE_SFT);
	करो_trap0(regs);
पूर्ण
