<शैली गुरु>
/*
 * HW exception handling
 *
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2008 PetaLogix
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

/*
 * This file handles the architecture-dependent parts of hardware exceptions
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/kallsyms.h>

#समावेश <यंत्र/exceptions.h>
#समावेश <यंत्र/entry.h>		/* For KM CPU var */
#समावेश <linux/uaccess.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/cacheflush.h>

#घोषणा MICROBLAZE_ILL_OPCODE_EXCEPTION	0x02
#घोषणा MICROBLAZE_IBUS_EXCEPTION	0x03
#घोषणा MICROBLAZE_DBUS_EXCEPTION	0x04
#घोषणा MICROBLAZE_DIV_ZERO_EXCEPTION	0x05
#घोषणा MICROBLAZE_FPU_EXCEPTION	0x06
#घोषणा MICROBLAZE_PRIVILEGED_EXCEPTION	0x07

अटल DEFINE_SPINLOCK(die_lock);

व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *fp, दीर्घ err)
अणु
	console_verbose();
	spin_lock_irq(&die_lock);
	pr_warn("Oops: %s, sig: %ld\n", str, err);
	show_regs(fp);
	spin_unlock_irq(&die_lock);
	/* करो_निकास() should take care of panic'ing from an पूर्णांकerrupt
	 * context so we करोn't handle it here
	 */
	करो_निकास(err);
पूर्ण

/* क्रम user application debugging */
यंत्रlinkage व्योम sw_exception(काष्ठा pt_regs *regs)
अणु
	_exception(SIGTRAP, regs, TRAP_BRKPT, regs->r16);
	flush_dcache_range(regs->r16, regs->r16 + 0x4);
	flush_icache_range(regs->r16, regs->r16 + 0x4);
पूर्ण

व्योम _exception(पूर्णांक signr, काष्ठा pt_regs *regs, पूर्णांक code, अचिन्हित दीर्घ addr)
अणु
	अगर (kernel_mode(regs))
		die("Exception in kernel mode", regs, signr);

	क्रमce_sig_fault(signr, code, (व्योम __user *)addr);
पूर्ण

यंत्रlinkage व्योम full_exception(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक type,
							पूर्णांक fsr, पूर्णांक addr)
अणु
	addr = regs->pc;

#अगर 0
	pr_warn("Exception %02x in %s mode, FSR=%08x PC=%08x ESR=%08x\n",
			type, user_mode(regs) ? "user" : "kernel", fsr,
			(अचिन्हित पूर्णांक) regs->pc, (अचिन्हित पूर्णांक) regs->esr);
#पूर्ण_अगर

	चयन (type & 0x1F) अणु
	हाल MICROBLAZE_ILL_OPCODE_EXCEPTION:
		अगर (user_mode(regs)) अणु
			pr_debug("Illegal opcode exception in user mode\n");
			_exception(संक_अवैध, regs, ILL_ILLOPC, addr);
			वापस;
		पूर्ण
		pr_warn("Illegal opcode exception in kernel mode.\n");
		die("opcode exception", regs, SIGBUS);
		अवरोध;
	हाल MICROBLAZE_IBUS_EXCEPTION:
		अगर (user_mode(regs)) अणु
			pr_debug("Instruction bus error exception in user mode\n");
			_exception(SIGBUS, regs, BUS_ADRERR, addr);
			वापस;
		पूर्ण
		pr_warn("Instruction bus error exception in kernel mode.\n");
		die("bus exception", regs, SIGBUS);
		अवरोध;
	हाल MICROBLAZE_DBUS_EXCEPTION:
		अगर (user_mode(regs)) अणु
			pr_debug("Data bus error exception in user mode\n");
			_exception(SIGBUS, regs, BUS_ADRERR, addr);
			वापस;
		पूर्ण
		pr_warn("Data bus error exception in kernel mode.\n");
		die("bus exception", regs, SIGBUS);
		अवरोध;
	हाल MICROBLAZE_DIV_ZERO_EXCEPTION:
		अगर (user_mode(regs)) अणु
			pr_debug("Divide by zero exception in user mode\n");
			_exception(संक_भ_त्रुटि, regs, FPE_INTDIV, addr);
			वापस;
		पूर्ण
		pr_warn("Divide by zero exception in kernel mode.\n");
		die("Divide by zero exception", regs, SIGBUS);
		अवरोध;
	हाल MICROBLAZE_FPU_EXCEPTION:
		pr_debug("FPU exception\n");
		/* IEEE FP exception */
		/* I हटाओd fsr variable and use code var क्रम storing fsr */
		अगर (fsr & FSR_IO)
			fsr = FPE_FLTINV;
		अन्यथा अगर (fsr & FSR_OF)
			fsr = FPE_FLTOVF;
		अन्यथा अगर (fsr & FSR_UF)
			fsr = FPE_FLTUND;
		अन्यथा अगर (fsr & FSR_DZ)
			fsr = FPE_FLTDIV;
		अन्यथा अगर (fsr & FSR_DO)
			fsr = FPE_FLTRES;
		_exception(संक_भ_त्रुटि, regs, fsr, addr);
		अवरोध;
	हाल MICROBLAZE_PRIVILEGED_EXCEPTION:
		pr_debug("Privileged exception\n");
		_exception(संक_अवैध, regs, ILL_PRVOPC, addr);
		अवरोध;
	शेष:
	/* FIXME what to करो in unexpected exception */
		pr_warn("Unexpected exception %02x PC=%08x in %s mode\n",
			type, (अचिन्हित पूर्णांक) addr,
			kernel_mode(regs) ? "kernel" : "user");
	पूर्ण
	वापस;
पूर्ण
