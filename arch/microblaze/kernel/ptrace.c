<शैली गुरु>
/*
 * `ptrace' प्रणाली call
 *
 * Copyright (C) 2008-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2004-2007 John Williams <john.williams@petalogix.com>
 *
 * derived from arch/v850/kernel/ptrace.c
 *
 * Copyright (C) 2002,03 NEC Electronics Corporation
 * Copyright (C) 2002,03 Miles Bader <miles@gnu.org>
 *
 * Derived from arch/mips/kernel/ptrace.c:
 *
 * Copyright (C) 1992 Ross Biro
 * Copyright (C) Linus Torvalds
 * Copyright (C) 1994, 95, 96, 97, 98, 2000 Ralf Baechle
 * Copyright (C) 1996 David S. Miller
 * Kevin D. Kissell, kevink@mips.com and Carsten Langgaard, carstenl@mips.com
 * Copyright (C) 1999 MIPS Technologies, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/elf.h>
#समावेश <linux/audit.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/tracehook.h>

#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/syscall.h>
#समावेश <linux/पन.स>

/* Returns the address where the रेजिस्टर at REG_OFFS in P is stashed away. */
अटल microblaze_reg_t *reg_save_addr(अचिन्हित reg_offs,
					काष्ठा task_काष्ठा *t)
अणु
	काष्ठा pt_regs *regs;

	/*
	 * Three basic हालs:
	 *
	 * (1)	A रेजिस्टर normally saved beक्रमe calling the scheduler, is
	 *	available in the kernel entry pt_regs काष्ठाure at the top
	 *	of the kernel stack. The kernel trap/irq निकास path takes
	 *	care to save/restore almost all रेजिस्टरs क्रम ptrace'd
	 *	processes.
	 *
	 * (2)	A call-clobbered रेजिस्टर, where the process P entered the
	 *	kernel via [syscall] trap, is not stored anywhere; that's
	 *	OK, because such रेजिस्टरs are not expected to be preserved
	 *	when the trap वापसs anyway (so we करोn't actually bother to
	 *	test क्रम this हाल).
	 *
	 * (3)	A few रेजिस्टरs not used at all by the kernel, and so
	 *	normally never saved except by context-चयनes, are in the
	 *	context चयन state.
	 */

	/* Register saved during kernel entry (or not available). */
	regs = task_pt_regs(t);

	वापस (microblaze_reg_t *)((अक्षर *)regs + reg_offs);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	पूर्णांक rval;
	अचिन्हित दीर्घ val = 0;

	चयन (request) अणु
	/* Read/ग_लिखो the word at location ADDR in the रेजिस्टरs. */
	हाल PTRACE_PEEKUSR:
	हाल PTRACE_POKEUSR:
		pr_debug("PEEKUSR/POKEUSR : 0x%08lx\n", addr);
		rval = 0;
		अगर (addr >= PT_SIZE && request == PTRACE_PEEKUSR) अणु
			/*
			 * Special requests that करोn't actually correspond
			 * to offsets in काष्ठा pt_regs.
			 */
			अगर (addr == PT_TEXT_ADDR) अणु
				val = child->mm->start_code;
			पूर्ण अन्यथा अगर (addr == PT_DATA_ADDR) अणु
				val = child->mm->start_data;
			पूर्ण अन्यथा अगर (addr == PT_TEXT_LEN) अणु
				val = child->mm->end_code
					- child->mm->start_code;
			पूर्ण अन्यथा अणु
				rval = -EIO;
			पूर्ण
		पूर्ण अन्यथा अगर (addr < PT_SIZE && (addr & 0x3) == 0) अणु
			microblaze_reg_t *reg_addr = reg_save_addr(addr, child);
			अगर (request == PTRACE_PEEKUSR)
				val = *reg_addr;
			अन्यथा अणु
#अगर 1
				*reg_addr = data;
#अन्यथा
				/* MS potential problem on WB प्रणाली
				 * Be aware that reg_addr is भव address
				 * virt_to_phys conversion is necessary.
				 * This could be sensible solution.
				 */
				u32 paddr = virt_to_phys((u32)reg_addr);
				invalidate_icache_range(paddr, paddr + 4);
				*reg_addr = data;
				flush_dcache_range(paddr, paddr + 4);
#पूर्ण_अगर
			पूर्ण
		पूर्ण अन्यथा
			rval = -EIO;

		अगर (rval == 0 && request == PTRACE_PEEKUSR)
			rval = put_user(val, (अचिन्हित दीर्घ __user *)data);
		अवरोध;
	शेष:
		rval = ptrace_request(child, request, addr, data);
	पूर्ण
	वापस rval;
पूर्ण

यंत्रlinkage अचिन्हित दीर्घ करो_syscall_trace_enter(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ ret = 0;

	secure_computing_strict(regs->r12);

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE) &&
	    tracehook_report_syscall_entry(regs))
		/*
		 * Tracing decided this syscall should not happen.
		 * We'll वापस a bogus call number to get an ENOSYS
		 * error, but leave the original number in regs->regs[0].
		 */
		ret = -1L;

	audit_syscall_entry(regs->r12, regs->r5, regs->r6, regs->r7, regs->r8);

	वापस ret ?: regs->r12;
पूर्ण

यंत्रlinkage व्योम करो_syscall_trace_leave(काष्ठा pt_regs *regs)
अणु
	पूर्णांक step;

	audit_syscall_निकास(regs);

	step = test_thपढ़ो_flag(TIF_SINGLESTEP);
	अगर (step || test_thपढ़ो_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_निकास(regs, step);
पूर्ण

व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* nothing to करो */
पूर्ण
