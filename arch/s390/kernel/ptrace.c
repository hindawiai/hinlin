<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Ptrace user space पूर्णांकerface.
 *
 *    Copyright IBM Corp. 1999, 2010
 *    Author(s): Denis Joseph Barrow
 *               Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#समावेश "asm/ptrace.h"
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/security.h>
#समावेश <linux/audit.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/elf.h>
#समावेश <linux/regset.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/seccomp.h>
#समावेश <linux/compat.h>
#समावेश <trace/syscall.h>
#समावेश <यंत्र/page.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/runसमय_instr.h>
#समावेश <यंत्र/facility.h>

#समावेश "entry.h"

#अगर_घोषित CONFIG_COMPAT
#समावेश "compat_ptrace.h"
#पूर्ण_अगर

व्योम update_cr_regs(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(task);
	काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &task->thपढ़ो;
	काष्ठा per_regs old, new;
	जोड़ ctlreg0 cr0_old, cr0_new;
	जोड़ ctlreg2 cr2_old, cr2_new;
	पूर्णांक cr0_changed, cr2_changed;

	__ctl_store(cr0_old.val, 0, 0);
	__ctl_store(cr2_old.val, 2, 2);
	cr0_new = cr0_old;
	cr2_new = cr2_old;
	/* Take care of the enable/disable of transactional execution. */
	अगर (MACHINE_HAS_TE) अणु
		/* Set or clear transaction execution TXC bit 8. */
		cr0_new.tcx = 1;
		अगर (task->thपढ़ो.per_flags & PER_FLAG_NO_TE)
			cr0_new.tcx = 0;
		/* Set or clear transaction execution TDC bits 62 and 63. */
		cr2_new.tdc = 0;
		अगर (task->thपढ़ो.per_flags & PER_FLAG_TE_ABORT_RAND) अणु
			अगर (task->thपढ़ो.per_flags & PER_FLAG_TE_ABORT_RAND_TEND)
				cr2_new.tdc = 1;
			अन्यथा
				cr2_new.tdc = 2;
		पूर्ण
	पूर्ण
	/* Take care of enable/disable of guarded storage. */
	अगर (MACHINE_HAS_GS) अणु
		cr2_new.gse = 0;
		अगर (task->thपढ़ो.gs_cb)
			cr2_new.gse = 1;
	पूर्ण
	/* Load control रेजिस्टर 0/2 अगरf changed */
	cr0_changed = cr0_new.val != cr0_old.val;
	cr2_changed = cr2_new.val != cr2_old.val;
	अगर (cr0_changed)
		__ctl_load(cr0_new.val, 0, 0);
	अगर (cr2_changed)
		__ctl_load(cr2_new.val, 2, 2);
	/* Copy user specअगरied PER रेजिस्टरs */
	new.control = thपढ़ो->per_user.control;
	new.start = thपढ़ो->per_user.start;
	new.end = thपढ़ो->per_user.end;

	/* merge TIF_SINGLE_STEP पूर्णांकo user specअगरied PER रेजिस्टरs. */
	अगर (test_tsk_thपढ़ो_flag(task, TIF_SINGLE_STEP) ||
	    test_tsk_thपढ़ो_flag(task, TIF_UPROBE_SINGLESTEP)) अणु
		अगर (test_tsk_thपढ़ो_flag(task, TIF_BLOCK_STEP))
			new.control |= PER_EVENT_BRANCH;
		अन्यथा
			new.control |= PER_EVENT_IFETCH;
		new.control |= PER_CONTROL_SUSPENSION;
		new.control |= PER_EVENT_TRANSACTION_END;
		अगर (test_tsk_thपढ़ो_flag(task, TIF_UPROBE_SINGLESTEP))
			new.control |= PER_EVENT_IFETCH;
		new.start = 0;
		new.end = -1UL;
	पूर्ण

	/* Take care of the PER enablement bit in the PSW. */
	अगर (!(new.control & PER_EVENT_MASK)) अणु
		regs->psw.mask &= ~PSW_MASK_PER;
		वापस;
	पूर्ण
	regs->psw.mask |= PSW_MASK_PER;
	__ctl_store(old, 9, 11);
	अगर (स_भेद(&new, &old, माप(काष्ठा per_regs)) != 0)
		__ctl_load(new, 9, 11);
पूर्ण

व्योम user_enable_single_step(काष्ठा task_काष्ठा *task)
अणु
	clear_tsk_thपढ़ो_flag(task, TIF_BLOCK_STEP);
	set_tsk_thपढ़ो_flag(task, TIF_SINGLE_STEP);
पूर्ण

व्योम user_disable_single_step(काष्ठा task_काष्ठा *task)
अणु
	clear_tsk_thपढ़ो_flag(task, TIF_BLOCK_STEP);
	clear_tsk_thपढ़ो_flag(task, TIF_SINGLE_STEP);
पूर्ण

व्योम user_enable_block_step(काष्ठा task_काष्ठा *task)
अणु
	set_tsk_thपढ़ो_flag(task, TIF_SINGLE_STEP);
	set_tsk_thपढ़ो_flag(task, TIF_BLOCK_STEP);
पूर्ण

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Clear all debugging related fields.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *task)
अणु
	स_रखो(&task->thपढ़ो.per_user, 0, माप(task->thपढ़ो.per_user));
	स_रखो(&task->thपढ़ो.per_event, 0, माप(task->thपढ़ो.per_event));
	clear_tsk_thपढ़ो_flag(task, TIF_SINGLE_STEP);
	clear_tsk_thपढ़ो_flag(task, TIF_PER_TRAP);
	task->thपढ़ो.per_flags = 0;
पूर्ण

#घोषणा __ADDR_MASK 7

अटल अंतरभूत अचिन्हित दीर्घ __peek_user_per(काष्ठा task_काष्ठा *child,
					    addr_t addr)
अणु
	काष्ठा per_काष्ठा_kernel *dummy = शून्य;

	अगर (addr == (addr_t) &dummy->cr9)
		/* Control bits of the active per set. */
		वापस test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			PER_EVENT_IFETCH : child->thपढ़ो.per_user.control;
	अन्यथा अगर (addr == (addr_t) &dummy->cr10)
		/* Start address of the active per set. */
		वापस test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			0 : child->thपढ़ो.per_user.start;
	अन्यथा अगर (addr == (addr_t) &dummy->cr11)
		/* End address of the active per set. */
		वापस test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			-1UL : child->thपढ़ो.per_user.end;
	अन्यथा अगर (addr == (addr_t) &dummy->bits)
		/* Single-step bit. */
		वापस test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			(1UL << (BITS_PER_LONG - 1)) : 0;
	अन्यथा अगर (addr == (addr_t) &dummy->starting_addr)
		/* Start address of the user specअगरied per set. */
		वापस child->thपढ़ो.per_user.start;
	अन्यथा अगर (addr == (addr_t) &dummy->ending_addr)
		/* End address of the user specअगरied per set. */
		वापस child->thपढ़ो.per_user.end;
	अन्यथा अगर (addr == (addr_t) &dummy->perc_aपंचांगid)
		/* PER code, ATMID and AI of the last PER trap */
		वापस (अचिन्हित दीर्घ)
			child->thपढ़ो.per_event.cause << (BITS_PER_LONG - 16);
	अन्यथा अगर (addr == (addr_t) &dummy->address)
		/* Address of the last PER trap */
		वापस child->thपढ़ो.per_event.address;
	अन्यथा अगर (addr == (addr_t) &dummy->access_id)
		/* Access id of the last PER trap */
		वापस (अचिन्हित दीर्घ)
			child->thपढ़ो.per_event.paid << (BITS_PER_LONG - 8);
	वापस 0;
पूर्ण

/*
 * Read the word at offset addr from the user area of a process. The
 * trouble here is that the inक्रमmation is littered over dअगरferent
 * locations. The process रेजिस्टरs are found on the kernel stack,
 * the भग्नing poपूर्णांक stuff and the trace settings are stored in
 * the task काष्ठाure. In addition the dअगरferent काष्ठाures in
 * काष्ठा user contain pad bytes that should be पढ़ो as zeroes.
 * Lovely...
 */
अटल अचिन्हित दीर्घ __peek_user(काष्ठा task_काष्ठा *child, addr_t addr)
अणु
	काष्ठा user *dummy = शून्य;
	addr_t offset, पंचांगp;

	अगर (addr < (addr_t) &dummy->regs.acrs) अणु
		/*
		 * psw and gprs are stored on the stack
		 */
		पंचांगp = *(addr_t *)((addr_t) &task_pt_regs(child)->psw + addr);
		अगर (addr == (addr_t) &dummy->regs.psw.mask) अणु
			/* Return a clean psw mask. */
			पंचांगp &= PSW_MASK_USER | PSW_MASK_RI;
			पंचांगp |= PSW_USER_BITS;
		पूर्ण

	पूर्ण अन्यथा अगर (addr < (addr_t) &dummy->regs.orig_gpr2) अणु
		/*
		 * access रेजिस्टरs are stored in the thपढ़ो काष्ठाure
		 */
		offset = addr - (addr_t) &dummy->regs.acrs;
		/*
		 * Very special हाल: old & broken 64 bit gdb पढ़ोing
		 * from acrs[15]. Result is a 64 bit value. Read the
		 * 32 bit acrs[15] value and shअगरt it by 32. Sick...
		 */
		अगर (addr == (addr_t) &dummy->regs.acrs[15])
			पंचांगp = ((अचिन्हित दीर्घ) child->thपढ़ो.acrs[15]) << 32;
		अन्यथा
			पंचांगp = *(addr_t *)((addr_t) &child->thपढ़ो.acrs + offset);

	पूर्ण अन्यथा अगर (addr == (addr_t) &dummy->regs.orig_gpr2) अणु
		/*
		 * orig_gpr2 is stored on the kernel stack
		 */
		पंचांगp = (addr_t) task_pt_regs(child)->orig_gpr2;

	पूर्ण अन्यथा अगर (addr < (addr_t) &dummy->regs.fp_regs) अणु
		/*
		 * prevent पढ़ोs of padding hole between
		 * orig_gpr2 and fp_regs on s390.
		 */
		पंचांगp = 0;

	पूर्ण अन्यथा अगर (addr == (addr_t) &dummy->regs.fp_regs.fpc) अणु
		/*
		 * भग्नing poपूर्णांक control reg. is in the thपढ़ो काष्ठाure
		 */
		पंचांगp = child->thपढ़ो.fpu.fpc;
		पंचांगp <<= BITS_PER_LONG - 32;

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy->regs.fp_regs + 1)) अणु
		/*
		 * भग्नing poपूर्णांक regs. are either in child->thपढ़ो.fpu
		 * or the child->thपढ़ो.fpu.vxrs array
		 */
		offset = addr - (addr_t) &dummy->regs.fp_regs.fprs;
		अगर (MACHINE_HAS_VX)
			पंचांगp = *(addr_t *)
			       ((addr_t) child->thपढ़ो.fpu.vxrs + 2*offset);
		अन्यथा
			पंचांगp = *(addr_t *)
			       ((addr_t) child->thपढ़ो.fpu.fprs + offset);

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy->regs.per_info + 1)) अणु
		/*
		 * Handle access to the per_info काष्ठाure.
		 */
		addr -= (addr_t) &dummy->regs.per_info;
		पंचांगp = __peek_user_per(child, addr);

	पूर्ण अन्यथा
		पंचांगp = 0;

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक
peek_user(काष्ठा task_काष्ठा *child, addr_t addr, addr_t data)
अणु
	addr_t पंचांगp, mask;

	/*
	 * Stupid gdb peeks/pokes the access रेजिस्टरs in 64 bit with
	 * an alignment of 4. Programmers from hell...
	 */
	mask = __ADDR_MASK;
	अगर (addr >= (addr_t) &((काष्ठा user *) शून्य)->regs.acrs &&
	    addr < (addr_t) &((काष्ठा user *) शून्य)->regs.orig_gpr2)
		mask = 3;
	अगर ((addr & mask) || addr > माप(काष्ठा user) - __ADDR_MASK)
		वापस -EIO;

	पंचांगp = __peek_user(child, addr);
	वापस put_user(पंचांगp, (addr_t __user *) data);
पूर्ण

अटल अंतरभूत व्योम __poke_user_per(काष्ठा task_काष्ठा *child,
				   addr_t addr, addr_t data)
अणु
	काष्ठा per_काष्ठा_kernel *dummy = शून्य;

	/*
	 * There are only three fields in the per_info काष्ठा that the
	 * debugger user can ग_लिखो to.
	 * 1) cr9: the debugger wants to set a new PER event mask
	 * 2) starting_addr: the debugger wants to set a new starting
	 *    address to use with the PER event mask.
	 * 3) ending_addr: the debugger wants to set a new ending
	 *    address to use with the PER event mask.
	 * The user specअगरied PER event mask and the start and end
	 * addresses are used only अगर single stepping is not in effect.
	 * Writes to any other field in per_info are ignored.
	 */
	अगर (addr == (addr_t) &dummy->cr9)
		/* PER event mask of the user specअगरied per set. */
		child->thपढ़ो.per_user.control =
			data & (PER_EVENT_MASK | PER_CONTROL_MASK);
	अन्यथा अगर (addr == (addr_t) &dummy->starting_addr)
		/* Starting address of the user specअगरied per set. */
		child->thपढ़ो.per_user.start = data;
	अन्यथा अगर (addr == (addr_t) &dummy->ending_addr)
		/* Ending address of the user specअगरied per set. */
		child->thपढ़ो.per_user.end = data;
पूर्ण

/*
 * Write a word to the user area of a process at location addr. This
 * operation करोes have an additional problem compared to peek_user.
 * Stores to the program status word and on the भग्नing poपूर्णांक
 * control रेजिस्टर needs to get checked क्रम validity.
 */
अटल पूर्णांक __poke_user(काष्ठा task_काष्ठा *child, addr_t addr, addr_t data)
अणु
	काष्ठा user *dummy = शून्य;
	addr_t offset;


	अगर (addr < (addr_t) &dummy->regs.acrs) अणु
		काष्ठा pt_regs *regs = task_pt_regs(child);
		/*
		 * psw and gprs are stored on the stack
		 */
		अगर (addr == (addr_t) &dummy->regs.psw.mask) अणु
			अचिन्हित दीर्घ mask = PSW_MASK_USER;

			mask |= is_ri_task(child) ? PSW_MASK_RI : 0;
			अगर ((data ^ PSW_USER_BITS) & ~mask)
				/* Invalid psw mask. */
				वापस -EINVAL;
			अगर ((data & PSW_MASK_ASC) == PSW_ASC_HOME)
				/* Invalid address-space-control bits */
				वापस -EINVAL;
			अगर ((data & PSW_MASK_EA) && !(data & PSW_MASK_BA))
				/* Invalid addressing mode bits */
				वापस -EINVAL;
		पूर्ण

		अगर (test_pt_regs_flag(regs, PIF_SYSCALL) &&
			addr == दुरत्व(काष्ठा user, regs.gprs[2])) अणु
			काष्ठा pt_regs *regs = task_pt_regs(child);

			regs->पूर्णांक_code = 0x20000 | (data & 0xffff);
		पूर्ण
		*(addr_t *)((addr_t) &regs->psw + addr) = data;
	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy->regs.orig_gpr2)) अणु
		/*
		 * access रेजिस्टरs are stored in the thपढ़ो काष्ठाure
		 */
		offset = addr - (addr_t) &dummy->regs.acrs;
		/*
		 * Very special हाल: old & broken 64 bit gdb writing
		 * to acrs[15] with a 64 bit value. Ignore the lower
		 * half of the value and ग_लिखो the upper 32 bit to
		 * acrs[15]. Sick...
		 */
		अगर (addr == (addr_t) &dummy->regs.acrs[15])
			child->thपढ़ो.acrs[15] = (अचिन्हित पूर्णांक) (data >> 32);
		अन्यथा
			*(addr_t *)((addr_t) &child->thपढ़ो.acrs + offset) = data;

	पूर्ण अन्यथा अगर (addr == (addr_t) &dummy->regs.orig_gpr2) अणु
		/*
		 * orig_gpr2 is stored on the kernel stack
		 */
		task_pt_regs(child)->orig_gpr2 = data;

	पूर्ण अन्यथा अगर (addr < (addr_t) &dummy->regs.fp_regs) अणु
		/*
		 * prevent ग_लिखोs of padding hole between
		 * orig_gpr2 and fp_regs on s390.
		 */
		वापस 0;

	पूर्ण अन्यथा अगर (addr == (addr_t) &dummy->regs.fp_regs.fpc) अणु
		/*
		 * भग्नing poपूर्णांक control reg. is in the thपढ़ो काष्ठाure
		 */
		अगर ((अचिन्हित पूर्णांक) data != 0 ||
		    test_fp_ctl(data >> (BITS_PER_LONG - 32)))
			वापस -EINVAL;
		child->thपढ़ो.fpu.fpc = data >> (BITS_PER_LONG - 32);

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy->regs.fp_regs + 1)) अणु
		/*
		 * भग्नing poपूर्णांक regs. are either in child->thपढ़ो.fpu
		 * or the child->thपढ़ो.fpu.vxrs array
		 */
		offset = addr - (addr_t) &dummy->regs.fp_regs.fprs;
		अगर (MACHINE_HAS_VX)
			*(addr_t *)((addr_t)
				child->thपढ़ो.fpu.vxrs + 2*offset) = data;
		अन्यथा
			*(addr_t *)((addr_t)
				child->thपढ़ो.fpu.fprs + offset) = data;

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy->regs.per_info + 1)) अणु
		/*
		 * Handle access to the per_info काष्ठाure.
		 */
		addr -= (addr_t) &dummy->regs.per_info;
		__poke_user_per(child, addr, data);

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक poke_user(काष्ठा task_काष्ठा *child, addr_t addr, addr_t data)
अणु
	addr_t mask;

	/*
	 * Stupid gdb peeks/pokes the access रेजिस्टरs in 64 bit with
	 * an alignment of 4. Programmers from hell indeed...
	 */
	mask = __ADDR_MASK;
	अगर (addr >= (addr_t) &((काष्ठा user *) शून्य)->regs.acrs &&
	    addr < (addr_t) &((काष्ठा user *) शून्य)->regs.orig_gpr2)
		mask = 3;
	अगर ((addr & mask) || addr > माप(काष्ठा user) - __ADDR_MASK)
		वापस -EIO;

	वापस __poke_user(child, addr, data);
पूर्ण

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	ptrace_area parea; 
	पूर्णांक copied, ret;

	चयन (request) अणु
	हाल PTRACE_PEEKUSR:
		/* पढ़ो the word at location addr in the USER area. */
		वापस peek_user(child, addr, data);

	हाल PTRACE_POKEUSR:
		/* ग_लिखो the word at location addr in the USER area */
		वापस poke_user(child, addr, data);

	हाल PTRACE_PEEKUSR_AREA:
	हाल PTRACE_POKEUSR_AREA:
		अगर (copy_from_user(&parea, (व्योम __क्रमce __user *) addr,
							माप(parea)))
			वापस -EFAULT;
		addr = parea.kernel_addr;
		data = parea.process_addr;
		copied = 0;
		जबतक (copied < parea.len) अणु
			अगर (request == PTRACE_PEEKUSR_AREA)
				ret = peek_user(child, addr, data);
			अन्यथा अणु
				addr_t uपंचांगp;
				अगर (get_user(uपंचांगp,
					     (addr_t __क्रमce __user *) data))
					वापस -EFAULT;
				ret = poke_user(child, addr, uपंचांगp);
			पूर्ण
			अगर (ret)
				वापस ret;
			addr += माप(अचिन्हित दीर्घ);
			data += माप(अचिन्हित दीर्घ);
			copied += माप(अचिन्हित दीर्घ);
		पूर्ण
		वापस 0;
	हाल PTRACE_GET_LAST_BREAK:
		put_user(child->thपढ़ो.last_अवरोध,
			 (अचिन्हित दीर्घ __user *) data);
		वापस 0;
	हाल PTRACE_ENABLE_TE:
		अगर (!MACHINE_HAS_TE)
			वापस -EIO;
		child->thपढ़ो.per_flags &= ~PER_FLAG_NO_TE;
		वापस 0;
	हाल PTRACE_DISABLE_TE:
		अगर (!MACHINE_HAS_TE)
			वापस -EIO;
		child->thपढ़ो.per_flags |= PER_FLAG_NO_TE;
		child->thपढ़ो.per_flags &= ~PER_FLAG_TE_ABORT_RAND;
		वापस 0;
	हाल PTRACE_TE_ABORT_RAND:
		अगर (!MACHINE_HAS_TE || (child->thपढ़ो.per_flags & PER_FLAG_NO_TE))
			वापस -EIO;
		चयन (data) अणु
		हाल 0UL:
			child->thपढ़ो.per_flags &= ~PER_FLAG_TE_ABORT_RAND;
			अवरोध;
		हाल 1UL:
			child->thपढ़ो.per_flags |= PER_FLAG_TE_ABORT_RAND;
			child->thपढ़ो.per_flags |= PER_FLAG_TE_ABORT_RAND_TEND;
			अवरोध;
		हाल 2UL:
			child->thपढ़ो.per_flags |= PER_FLAG_TE_ABORT_RAND;
			child->thपढ़ो.per_flags &= ~PER_FLAG_TE_ABORT_RAND_TEND;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	शेष:
		वापस ptrace_request(child, request, addr, data);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
/*
 * Now the fun part starts... a 31 bit program running in the
 * 31 bit emulation tracing another program. PTRACE_PEEKTEXT,
 * PTRACE_PEEKDATA, PTRACE_POKETEXT and PTRACE_POKEDATA are easy
 * to handle, the dअगरference to the 64 bit versions of the requests
 * is that the access is करोne in multiples of 4 byte instead of
 * 8 bytes (माप(अचिन्हित दीर्घ) on 31/64 bit).
 * The ugly part are PTRACE_PEEKUSR, PTRACE_PEEKUSR_AREA,
 * PTRACE_POKEUSR and PTRACE_POKEUSR_AREA. If the traced program
 * is a 31 bit program too, the content of काष्ठा user can be
 * emulated. A 31 bit program peeking पूर्णांकo the काष्ठा user of
 * a 64 bit program is a no-no.
 */

/*
 * Same as peek_user_per but क्रम a 31 bit program.
 */
अटल अंतरभूत __u32 __peek_user_per_compat(काष्ठा task_काष्ठा *child,
					   addr_t addr)
अणु
	काष्ठा compat_per_काष्ठा_kernel *dummy32 = शून्य;

	अगर (addr == (addr_t) &dummy32->cr9)
		/* Control bits of the active per set. */
		वापस (__u32) test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			PER_EVENT_IFETCH : child->thपढ़ो.per_user.control;
	अन्यथा अगर (addr == (addr_t) &dummy32->cr10)
		/* Start address of the active per set. */
		वापस (__u32) test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			0 : child->thपढ़ो.per_user.start;
	अन्यथा अगर (addr == (addr_t) &dummy32->cr11)
		/* End address of the active per set. */
		वापस test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			PSW32_ADDR_INSN : child->thपढ़ो.per_user.end;
	अन्यथा अगर (addr == (addr_t) &dummy32->bits)
		/* Single-step bit. */
		वापस (__u32) test_thपढ़ो_flag(TIF_SINGLE_STEP) ?
			0x80000000 : 0;
	अन्यथा अगर (addr == (addr_t) &dummy32->starting_addr)
		/* Start address of the user specअगरied per set. */
		वापस (__u32) child->thपढ़ो.per_user.start;
	अन्यथा अगर (addr == (addr_t) &dummy32->ending_addr)
		/* End address of the user specअगरied per set. */
		वापस (__u32) child->thपढ़ो.per_user.end;
	अन्यथा अगर (addr == (addr_t) &dummy32->perc_aपंचांगid)
		/* PER code, ATMID and AI of the last PER trap */
		वापस (__u32) child->thपढ़ो.per_event.cause << 16;
	अन्यथा अगर (addr == (addr_t) &dummy32->address)
		/* Address of the last PER trap */
		वापस (__u32) child->thपढ़ो.per_event.address;
	अन्यथा अगर (addr == (addr_t) &dummy32->access_id)
		/* Access id of the last PER trap */
		वापस (__u32) child->thपढ़ो.per_event.paid << 24;
	वापस 0;
पूर्ण

/*
 * Same as peek_user but क्रम a 31 bit program.
 */
अटल u32 __peek_user_compat(काष्ठा task_काष्ठा *child, addr_t addr)
अणु
	काष्ठा compat_user *dummy32 = शून्य;
	addr_t offset;
	__u32 पंचांगp;

	अगर (addr < (addr_t) &dummy32->regs.acrs) अणु
		काष्ठा pt_regs *regs = task_pt_regs(child);
		/*
		 * psw and gprs are stored on the stack
		 */
		अगर (addr == (addr_t) &dummy32->regs.psw.mask) अणु
			/* Fake a 31 bit psw mask. */
			पंचांगp = (__u32)(regs->psw.mask >> 32);
			पंचांगp &= PSW32_MASK_USER | PSW32_MASK_RI;
			पंचांगp |= PSW32_USER_BITS;
		पूर्ण अन्यथा अगर (addr == (addr_t) &dummy32->regs.psw.addr) अणु
			/* Fake a 31 bit psw address. */
			पंचांगp = (__u32) regs->psw.addr |
				(__u32)(regs->psw.mask & PSW_MASK_BA);
		पूर्ण अन्यथा अणु
			/* gpr 0-15 */
			पंचांगp = *(__u32 *)((addr_t) &regs->psw + addr*2 + 4);
		पूर्ण
	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy32->regs.orig_gpr2)) अणु
		/*
		 * access रेजिस्टरs are stored in the thपढ़ो काष्ठाure
		 */
		offset = addr - (addr_t) &dummy32->regs.acrs;
		पंचांगp = *(__u32*)((addr_t) &child->thपढ़ो.acrs + offset);

	पूर्ण अन्यथा अगर (addr == (addr_t) (&dummy32->regs.orig_gpr2)) अणु
		/*
		 * orig_gpr2 is stored on the kernel stack
		 */
		पंचांगp = *(__u32*)((addr_t) &task_pt_regs(child)->orig_gpr2 + 4);

	पूर्ण अन्यथा अगर (addr < (addr_t) &dummy32->regs.fp_regs) अणु
		/*
		 * prevent पढ़ोs of padding hole between
		 * orig_gpr2 and fp_regs on s390.
		 */
		पंचांगp = 0;

	पूर्ण अन्यथा अगर (addr == (addr_t) &dummy32->regs.fp_regs.fpc) अणु
		/*
		 * भग्नing poपूर्णांक control reg. is in the thपढ़ो काष्ठाure
		 */
		पंचांगp = child->thपढ़ो.fpu.fpc;

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy32->regs.fp_regs + 1)) अणु
		/*
		 * भग्नing poपूर्णांक regs. are either in child->thपढ़ो.fpu
		 * or the child->thपढ़ो.fpu.vxrs array
		 */
		offset = addr - (addr_t) &dummy32->regs.fp_regs.fprs;
		अगर (MACHINE_HAS_VX)
			पंचांगp = *(__u32 *)
			       ((addr_t) child->thपढ़ो.fpu.vxrs + 2*offset);
		अन्यथा
			पंचांगp = *(__u32 *)
			       ((addr_t) child->thपढ़ो.fpu.fprs + offset);

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy32->regs.per_info + 1)) अणु
		/*
		 * Handle access to the per_info काष्ठाure.
		 */
		addr -= (addr_t) &dummy32->regs.per_info;
		पंचांगp = __peek_user_per_compat(child, addr);

	पूर्ण अन्यथा
		पंचांगp = 0;

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक peek_user_compat(काष्ठा task_काष्ठा *child,
			    addr_t addr, addr_t data)
अणु
	__u32 पंचांगp;

	अगर (!is_compat_task() || (addr & 3) || addr > माप(काष्ठा user) - 3)
		वापस -EIO;

	पंचांगp = __peek_user_compat(child, addr);
	वापस put_user(पंचांगp, (__u32 __user *) data);
पूर्ण

/*
 * Same as poke_user_per but क्रम a 31 bit program.
 */
अटल अंतरभूत व्योम __poke_user_per_compat(काष्ठा task_काष्ठा *child,
					  addr_t addr, __u32 data)
अणु
	काष्ठा compat_per_काष्ठा_kernel *dummy32 = शून्य;

	अगर (addr == (addr_t) &dummy32->cr9)
		/* PER event mask of the user specअगरied per set. */
		child->thपढ़ो.per_user.control =
			data & (PER_EVENT_MASK | PER_CONTROL_MASK);
	अन्यथा अगर (addr == (addr_t) &dummy32->starting_addr)
		/* Starting address of the user specअगरied per set. */
		child->thपढ़ो.per_user.start = data;
	अन्यथा अगर (addr == (addr_t) &dummy32->ending_addr)
		/* Ending address of the user specअगरied per set. */
		child->thपढ़ो.per_user.end = data;
पूर्ण

/*
 * Same as poke_user but क्रम a 31 bit program.
 */
अटल पूर्णांक __poke_user_compat(काष्ठा task_काष्ठा *child,
			      addr_t addr, addr_t data)
अणु
	काष्ठा compat_user *dummy32 = शून्य;
	__u32 पंचांगp = (__u32) data;
	addr_t offset;

	अगर (addr < (addr_t) &dummy32->regs.acrs) अणु
		काष्ठा pt_regs *regs = task_pt_regs(child);
		/*
		 * psw, gprs, acrs and orig_gpr2 are stored on the stack
		 */
		अगर (addr == (addr_t) &dummy32->regs.psw.mask) अणु
			__u32 mask = PSW32_MASK_USER;

			mask |= is_ri_task(child) ? PSW32_MASK_RI : 0;
			/* Build a 64 bit psw mask from 31 bit mask. */
			अगर ((पंचांगp ^ PSW32_USER_BITS) & ~mask)
				/* Invalid psw mask. */
				वापस -EINVAL;
			अगर ((data & PSW32_MASK_ASC) == PSW32_ASC_HOME)
				/* Invalid address-space-control bits */
				वापस -EINVAL;
			regs->psw.mask = (regs->psw.mask & ~PSW_MASK_USER) |
				(regs->psw.mask & PSW_MASK_BA) |
				(__u64)(पंचांगp & mask) << 32;
		पूर्ण अन्यथा अगर (addr == (addr_t) &dummy32->regs.psw.addr) अणु
			/* Build a 64 bit psw address from 31 bit address. */
			regs->psw.addr = (__u64) पंचांगp & PSW32_ADDR_INSN;
			/* Transfer 31 bit amode bit to psw mask. */
			regs->psw.mask = (regs->psw.mask & ~PSW_MASK_BA) |
				(__u64)(पंचांगp & PSW32_ADDR_AMODE);
		पूर्ण अन्यथा अणु
			अगर (test_pt_regs_flag(regs, PIF_SYSCALL) &&
				addr == दुरत्व(काष्ठा compat_user, regs.gprs[2])) अणु
				काष्ठा pt_regs *regs = task_pt_regs(child);

				regs->पूर्णांक_code = 0x20000 | (data & 0xffff);
			पूर्ण
			/* gpr 0-15 */
			*(__u32*)((addr_t) &regs->psw + addr*2 + 4) = पंचांगp;
		पूर्ण
	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy32->regs.orig_gpr2)) अणु
		/*
		 * access रेजिस्टरs are stored in the thपढ़ो काष्ठाure
		 */
		offset = addr - (addr_t) &dummy32->regs.acrs;
		*(__u32*)((addr_t) &child->thपढ़ो.acrs + offset) = पंचांगp;

	पूर्ण अन्यथा अगर (addr == (addr_t) (&dummy32->regs.orig_gpr2)) अणु
		/*
		 * orig_gpr2 is stored on the kernel stack
		 */
		*(__u32*)((addr_t) &task_pt_regs(child)->orig_gpr2 + 4) = पंचांगp;

	पूर्ण अन्यथा अगर (addr < (addr_t) &dummy32->regs.fp_regs) अणु
		/*
		 * prevent ग_लिखोss of padding hole between
		 * orig_gpr2 and fp_regs on s390.
		 */
		वापस 0;

	पूर्ण अन्यथा अगर (addr == (addr_t) &dummy32->regs.fp_regs.fpc) अणु
		/*
		 * भग्नing poपूर्णांक control reg. is in the thपढ़ो काष्ठाure
		 */
		अगर (test_fp_ctl(पंचांगp))
			वापस -EINVAL;
		child->thपढ़ो.fpu.fpc = data;

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy32->regs.fp_regs + 1)) अणु
		/*
		 * भग्नing poपूर्णांक regs. are either in child->thपढ़ो.fpu
		 * or the child->thपढ़ो.fpu.vxrs array
		 */
		offset = addr - (addr_t) &dummy32->regs.fp_regs.fprs;
		अगर (MACHINE_HAS_VX)
			*(__u32 *)((addr_t)
				child->thपढ़ो.fpu.vxrs + 2*offset) = पंचांगp;
		अन्यथा
			*(__u32 *)((addr_t)
				child->thपढ़ो.fpu.fprs + offset) = पंचांगp;

	पूर्ण अन्यथा अगर (addr < (addr_t) (&dummy32->regs.per_info + 1)) अणु
		/*
		 * Handle access to the per_info काष्ठाure.
		 */
		addr -= (addr_t) &dummy32->regs.per_info;
		__poke_user_per_compat(child, addr, data);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक poke_user_compat(काष्ठा task_काष्ठा *child,
			    addr_t addr, addr_t data)
अणु
	अगर (!is_compat_task() || (addr & 3) ||
	    addr > माप(काष्ठा compat_user) - 3)
		वापस -EIO;

	वापस __poke_user_compat(child, addr, data);
पूर्ण

दीर्घ compat_arch_ptrace(काष्ठा task_काष्ठा *child, compat_दीर्घ_t request,
			compat_uदीर्घ_t caddr, compat_uदीर्घ_t cdata)
अणु
	अचिन्हित दीर्घ addr = caddr;
	अचिन्हित दीर्घ data = cdata;
	compat_ptrace_area parea;
	पूर्णांक copied, ret;

	चयन (request) अणु
	हाल PTRACE_PEEKUSR:
		/* पढ़ो the word at location addr in the USER area. */
		वापस peek_user_compat(child, addr, data);

	हाल PTRACE_POKEUSR:
		/* ग_लिखो the word at location addr in the USER area */
		वापस poke_user_compat(child, addr, data);

	हाल PTRACE_PEEKUSR_AREA:
	हाल PTRACE_POKEUSR_AREA:
		अगर (copy_from_user(&parea, (व्योम __क्रमce __user *) addr,
							माप(parea)))
			वापस -EFAULT;
		addr = parea.kernel_addr;
		data = parea.process_addr;
		copied = 0;
		जबतक (copied < parea.len) अणु
			अगर (request == PTRACE_PEEKUSR_AREA)
				ret = peek_user_compat(child, addr, data);
			अन्यथा अणु
				__u32 uपंचांगp;
				अगर (get_user(uपंचांगp,
					     (__u32 __क्रमce __user *) data))
					वापस -EFAULT;
				ret = poke_user_compat(child, addr, uपंचांगp);
			पूर्ण
			अगर (ret)
				वापस ret;
			addr += माप(अचिन्हित पूर्णांक);
			data += माप(अचिन्हित पूर्णांक);
			copied += माप(अचिन्हित पूर्णांक);
		पूर्ण
		वापस 0;
	हाल PTRACE_GET_LAST_BREAK:
		put_user(child->thपढ़ो.last_अवरोध,
			 (अचिन्हित पूर्णांक __user *) data);
		वापस 0;
	पूर्ण
	वापस compat_ptrace_request(child, request, addr, data);
पूर्ण
#पूर्ण_अगर

/*
 * user_regset definitions.
 */

अटल पूर्णांक s390_regs_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	अचिन्हित pos;
	अगर (target == current)
		save_access_regs(target->thपढ़ो.acrs);

	क्रम (pos = 0; pos < माप(s390_regs); pos += माप(दीर्घ))
		membuf_store(&to, __peek_user(target, pos));
	वापस 0;
पूर्ण

अटल पूर्णांक s390_regs_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक rc = 0;

	अगर (target == current)
		save_access_regs(target->thपढ़ो.acrs);

	अगर (kbuf) अणु
		स्थिर अचिन्हित दीर्घ *k = kbuf;
		जबतक (count > 0 && !rc) अणु
			rc = __poke_user(target, pos, *k++);
			count -= माप(*k);
			pos += माप(*k);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर अचिन्हित दीर्घ  __user *u = ubuf;
		जबतक (count > 0 && !rc) अणु
			अचिन्हित दीर्घ word;
			rc = __get_user(word, u++);
			अगर (rc)
				अवरोध;
			rc = __poke_user(target, pos, word);
			count -= माप(*u);
			pos += माप(*u);
		पूर्ण
	पूर्ण

	अगर (rc == 0 && target == current)
		restore_access_regs(target->thपढ़ो.acrs);

	वापस rc;
पूर्ण

अटल पूर्णांक s390_fpregs_get(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा user_regset *regset,
			   काष्ठा membuf to)
अणु
	_s390_fp_regs fp_regs;

	अगर (target == current)
		save_fpu_regs();

	fp_regs.fpc = target->thपढ़ो.fpu.fpc;
	fpregs_store(&fp_regs, &target->thपढ़ो.fpu);

	वापस membuf_ग_लिखो(&to, &fp_regs, माप(fp_regs));
पूर्ण

अटल पूर्णांक s390_fpregs_set(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा user_regset *regset, अचिन्हित पूर्णांक pos,
			   अचिन्हित पूर्णांक count, स्थिर व्योम *kbuf,
			   स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक rc = 0;
	freg_t fprs[__NUM_FPRS];

	अगर (target == current)
		save_fpu_regs();

	अगर (MACHINE_HAS_VX)
		convert_vx_to_fp(fprs, target->thपढ़ो.fpu.vxrs);
	अन्यथा
		स_नकल(&fprs, target->thपढ़ो.fpu.fprs, माप(fprs));

	/* If setting FPC, must validate it first. */
	अगर (count > 0 && pos < दुरत्व(s390_fp_regs, fprs)) अणु
		u32 ufpc[2] = अणु target->thपढ़ो.fpu.fpc, 0 पूर्ण;
		rc = user_regset_copyin(&pos, &count, &kbuf, &ubuf, &ufpc,
					0, दुरत्व(s390_fp_regs, fprs));
		अगर (rc)
			वापस rc;
		अगर (ufpc[1] != 0 || test_fp_ctl(ufpc[0]))
			वापस -EINVAL;
		target->thपढ़ो.fpu.fpc = ufpc[0];
	पूर्ण

	अगर (rc == 0 && count > 0)
		rc = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					fprs, दुरत्व(s390_fp_regs, fprs), -1);
	अगर (rc)
		वापस rc;

	अगर (MACHINE_HAS_VX)
		convert_fp_to_vx(target->thपढ़ो.fpu.vxrs, fprs);
	अन्यथा
		स_नकल(target->thपढ़ो.fpu.fprs, &fprs, माप(fprs));

	वापस rc;
पूर्ण

अटल पूर्णांक s390_last_अवरोध_get(काष्ठा task_काष्ठा *target,
			       स्थिर काष्ठा user_regset *regset,
			       काष्ठा membuf to)
अणु
	वापस membuf_store(&to, target->thपढ़ो.last_अवरोध);
पूर्ण

अटल पूर्णांक s390_last_अवरोध_set(काष्ठा task_काष्ठा *target,
			       स्थिर काष्ठा user_regset *regset,
			       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक s390_tdb_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(target);

	अगर (!(regs->पूर्णांक_code & 0x200))
		वापस -ENODATA;
	वापस membuf_ग_लिखो(&to, target->thपढ़ो.trap_tdb, 256);
पूर्ण

अटल पूर्णांक s390_tdb_set(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक s390_vxrs_low_get(काष्ठा task_काष्ठा *target,
			     स्थिर काष्ठा user_regset *regset,
			     काष्ठा membuf to)
अणु
	__u64 vxrs[__NUM_VXRS_LOW];
	पूर्णांक i;

	अगर (!MACHINE_HAS_VX)
		वापस -ENODEV;
	अगर (target == current)
		save_fpu_regs();
	क्रम (i = 0; i < __NUM_VXRS_LOW; i++)
		vxrs[i] = *((__u64 *)(target->thपढ़ो.fpu.vxrs + i) + 1);
	वापस membuf_ग_लिखो(&to, vxrs, माप(vxrs));
पूर्ण

अटल पूर्णांक s390_vxrs_low_set(काष्ठा task_काष्ठा *target,
			     स्थिर काष्ठा user_regset *regset,
			     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	__u64 vxrs[__NUM_VXRS_LOW];
	पूर्णांक i, rc;

	अगर (!MACHINE_HAS_VX)
		वापस -ENODEV;
	अगर (target == current)
		save_fpu_regs();

	क्रम (i = 0; i < __NUM_VXRS_LOW; i++)
		vxrs[i] = *((__u64 *)(target->thपढ़ो.fpu.vxrs + i) + 1);

	rc = user_regset_copyin(&pos, &count, &kbuf, &ubuf, vxrs, 0, -1);
	अगर (rc == 0)
		क्रम (i = 0; i < __NUM_VXRS_LOW; i++)
			*((__u64 *)(target->thपढ़ो.fpu.vxrs + i) + 1) = vxrs[i];

	वापस rc;
पूर्ण

अटल पूर्णांक s390_vxrs_high_get(काष्ठा task_काष्ठा *target,
			      स्थिर काष्ठा user_regset *regset,
			      काष्ठा membuf to)
अणु
	अगर (!MACHINE_HAS_VX)
		वापस -ENODEV;
	अगर (target == current)
		save_fpu_regs();
	वापस membuf_ग_लिखो(&to, target->thपढ़ो.fpu.vxrs + __NUM_VXRS_LOW,
			    __NUM_VXRS_HIGH * माप(__vector128));
पूर्ण

अटल पूर्णांक s390_vxrs_high_set(काष्ठा task_काष्ठा *target,
			      स्थिर काष्ठा user_regset *regset,
			      अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			      स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक rc;

	अगर (!MACHINE_HAS_VX)
		वापस -ENODEV;
	अगर (target == current)
		save_fpu_regs();

	rc = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				target->thपढ़ो.fpu.vxrs + __NUM_VXRS_LOW, 0, -1);
	वापस rc;
पूर्ण

अटल पूर्णांक s390_प्रणाली_call_get(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				काष्ठा membuf to)
अणु
	वापस membuf_store(&to, target->thपढ़ो.प्रणाली_call);
पूर्ण

अटल पूर्णांक s390_प्रणाली_call_set(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित पूर्णांक *data = &target->thपढ़ो.प्रणाली_call;
	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  data, 0, माप(अचिन्हित पूर्णांक));
पूर्ण

अटल पूर्णांक s390_gs_cb_get(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  काष्ठा membuf to)
अणु
	काष्ठा gs_cb *data = target->thपढ़ो.gs_cb;

	अगर (!MACHINE_HAS_GS)
		वापस -ENODEV;
	अगर (!data)
		वापस -ENODATA;
	अगर (target == current)
		save_gs_cb(data);
	वापस membuf_ग_लिखो(&to, data, माप(काष्ठा gs_cb));
पूर्ण

अटल पूर्णांक s390_gs_cb_set(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा gs_cb gs_cb = अणु पूर्ण, *data = शून्य;
	पूर्णांक rc;

	अगर (!MACHINE_HAS_GS)
		वापस -ENODEV;
	अगर (!target->thपढ़ो.gs_cb) अणु
		data = kzalloc(माप(*data), GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;
	पूर्ण
	अगर (!target->thपढ़ो.gs_cb)
		gs_cb.gsd = 25;
	अन्यथा अगर (target == current)
		save_gs_cb(&gs_cb);
	अन्यथा
		gs_cb = *target->thपढ़ो.gs_cb;
	rc = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				&gs_cb, 0, माप(gs_cb));
	अगर (rc) अणु
		kमुक्त(data);
		वापस -EFAULT;
	पूर्ण
	preempt_disable();
	अगर (!target->thपढ़ो.gs_cb)
		target->thपढ़ो.gs_cb = data;
	*target->thपढ़ो.gs_cb = gs_cb;
	अगर (target == current) अणु
		__ctl_set_bit(2, 4);
		restore_gs_cb(target->thपढ़ो.gs_cb);
	पूर्ण
	preempt_enable();
	वापस rc;
पूर्ण

अटल पूर्णांक s390_gs_bc_get(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  काष्ठा membuf to)
अणु
	काष्ठा gs_cb *data = target->thपढ़ो.gs_bc_cb;

	अगर (!MACHINE_HAS_GS)
		वापस -ENODEV;
	अगर (!data)
		वापस -ENODATA;
	वापस membuf_ग_लिखो(&to, data, माप(काष्ठा gs_cb));
पूर्ण

अटल पूर्णांक s390_gs_bc_set(काष्ठा task_काष्ठा *target,
			  स्थिर काष्ठा user_regset *regset,
			  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा gs_cb *data = target->thपढ़ो.gs_bc_cb;

	अगर (!MACHINE_HAS_GS)
		वापस -ENODEV;
	अगर (!data) अणु
		data = kzalloc(माप(*data), GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;
		target->thपढ़ो.gs_bc_cb = data;
	पूर्ण
	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				  data, 0, माप(काष्ठा gs_cb));
पूर्ण

अटल bool is_ri_cb_valid(काष्ठा runसमय_instr_cb *cb)
अणु
	वापस (cb->rca & 0x1f) == 0 &&
		(cb->roa & 0xfff) == 0 &&
		(cb->rla & 0xfff) == 0xfff &&
		cb->s == 1 &&
		cb->k == 1 &&
		cb->h == 0 &&
		cb->reserved1 == 0 &&
		cb->ps == 1 &&
		cb->qs == 0 &&
		cb->pc == 1 &&
		cb->qc == 0 &&
		cb->reserved2 == 0 &&
		cb->reserved3 == 0 &&
		cb->reserved4 == 0 &&
		cb->reserved5 == 0 &&
		cb->reserved6 == 0 &&
		cb->reserved7 == 0 &&
		cb->reserved8 == 0 &&
		cb->rla >= cb->roa &&
		cb->rca >= cb->roa &&
		cb->rca <= cb->rla+1 &&
		cb->m < 3;
पूर्ण

अटल पूर्णांक s390_runसमय_instr_get(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				काष्ठा membuf to)
अणु
	काष्ठा runसमय_instr_cb *data = target->thपढ़ो.ri_cb;

	अगर (!test_facility(64))
		वापस -ENODEV;
	अगर (!data)
		वापस -ENODATA;

	वापस membuf_ग_लिखो(&to, data, माप(काष्ठा runसमय_instr_cb));
पूर्ण

अटल पूर्णांक s390_runसमय_instr_set(काष्ठा task_काष्ठा *target,
				  स्थिर काष्ठा user_regset *regset,
				  अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				  स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा runसमय_instr_cb ri_cb = अणु पूर्ण, *data = शून्य;
	पूर्णांक rc;

	अगर (!test_facility(64))
		वापस -ENODEV;

	अगर (!target->thपढ़ो.ri_cb) अणु
		data = kzalloc(माप(*data), GFP_KERNEL);
		अगर (!data)
			वापस -ENOMEM;
	पूर्ण

	अगर (target->thपढ़ो.ri_cb) अणु
		अगर (target == current)
			store_runसमय_instr_cb(&ri_cb);
		अन्यथा
			ri_cb = *target->thपढ़ो.ri_cb;
	पूर्ण

	rc = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				&ri_cb, 0, माप(काष्ठा runसमय_instr_cb));
	अगर (rc) अणु
		kमुक्त(data);
		वापस -EFAULT;
	पूर्ण

	अगर (!is_ri_cb_valid(&ri_cb)) अणु
		kमुक्त(data);
		वापस -EINVAL;
	पूर्ण
	/*
	 * Override access key in any हाल, since user space should
	 * not be able to set it, nor should it care about it.
	 */
	ri_cb.key = PAGE_DEFAULT_KEY >> 4;
	preempt_disable();
	अगर (!target->thपढ़ो.ri_cb)
		target->thपढ़ो.ri_cb = data;
	*target->thपढ़ो.ri_cb = ri_cb;
	अगर (target == current)
		load_runसमय_instr_cb(target->thपढ़ो.ri_cb);
	preempt_enable();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा user_regset s390_regsets[] = अणु
	अणु
		.core_note_type = NT_PRSTATUS,
		.n = माप(s390_regs) / माप(दीर्घ),
		.size = माप(दीर्घ),
		.align = माप(दीर्घ),
		.regset_get = s390_regs_get,
		.set = s390_regs_set,
	पूर्ण,
	अणु
		.core_note_type = NT_PRFPREG,
		.n = माप(s390_fp_regs) / माप(दीर्घ),
		.size = माप(दीर्घ),
		.align = माप(दीर्घ),
		.regset_get = s390_fpregs_get,
		.set = s390_fpregs_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_SYSTEM_CALL,
		.n = 1,
		.size = माप(अचिन्हित पूर्णांक),
		.align = माप(अचिन्हित पूर्णांक),
		.regset_get = s390_प्रणाली_call_get,
		.set = s390_प्रणाली_call_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_LAST_BREAK,
		.n = 1,
		.size = माप(दीर्घ),
		.align = माप(दीर्घ),
		.regset_get = s390_last_अवरोध_get,
		.set = s390_last_अवरोध_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_TDB,
		.n = 1,
		.size = 256,
		.align = 1,
		.regset_get = s390_tdb_get,
		.set = s390_tdb_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_VXRS_LOW,
		.n = __NUM_VXRS_LOW,
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_vxrs_low_get,
		.set = s390_vxrs_low_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_VXRS_HIGH,
		.n = __NUM_VXRS_HIGH,
		.size = माप(__vector128),
		.align = माप(__vector128),
		.regset_get = s390_vxrs_high_get,
		.set = s390_vxrs_high_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_GS_CB,
		.n = माप(काष्ठा gs_cb) / माप(__u64),
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_gs_cb_get,
		.set = s390_gs_cb_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_GS_BC,
		.n = माप(काष्ठा gs_cb) / माप(__u64),
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_gs_bc_get,
		.set = s390_gs_bc_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_RI_CB,
		.n = माप(काष्ठा runसमय_instr_cb) / माप(__u64),
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_runसमय_instr_get,
		.set = s390_runसमय_instr_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_s390_view = अणु
	.name = "s390x",
	.e_machine = EM_S390,
	.regsets = s390_regsets,
	.n = ARRAY_SIZE(s390_regsets)
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक s390_compat_regs_get(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				काष्ठा membuf to)
अणु
	अचिन्हित n;

	अगर (target == current)
		save_access_regs(target->thपढ़ो.acrs);

	क्रम (n = 0; n < माप(s390_compat_regs); n += माप(compat_uदीर्घ_t))
		membuf_store(&to, __peek_user_compat(target, n));
	वापस 0;
पूर्ण

अटल पूर्णांक s390_compat_regs_set(काष्ठा task_काष्ठा *target,
				स्थिर काष्ठा user_regset *regset,
				अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	पूर्णांक rc = 0;

	अगर (target == current)
		save_access_regs(target->thपढ़ो.acrs);

	अगर (kbuf) अणु
		स्थिर compat_uदीर्घ_t *k = kbuf;
		जबतक (count > 0 && !rc) अणु
			rc = __poke_user_compat(target, pos, *k++);
			count -= माप(*k);
			pos += माप(*k);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर compat_uदीर्घ_t  __user *u = ubuf;
		जबतक (count > 0 && !rc) अणु
			compat_uदीर्घ_t word;
			rc = __get_user(word, u++);
			अगर (rc)
				अवरोध;
			rc = __poke_user_compat(target, pos, word);
			count -= माप(*u);
			pos += माप(*u);
		पूर्ण
	पूर्ण

	अगर (rc == 0 && target == current)
		restore_access_regs(target->thपढ़ो.acrs);

	वापस rc;
पूर्ण

अटल पूर्णांक s390_compat_regs_high_get(काष्ठा task_काष्ठा *target,
				     स्थिर काष्ठा user_regset *regset,
				     काष्ठा membuf to)
अणु
	compat_uदीर्घ_t *gprs_high;
	पूर्णांक i;

	gprs_high = (compat_uदीर्घ_t *)task_pt_regs(target)->gprs;
	क्रम (i = 0; i < NUM_GPRS; i++, gprs_high += 2)
		membuf_store(&to, *gprs_high);
	वापस 0;
पूर्ण

अटल पूर्णांक s390_compat_regs_high_set(काष्ठा task_काष्ठा *target,
				     स्थिर काष्ठा user_regset *regset,
				     अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				     स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	compat_uदीर्घ_t *gprs_high;
	पूर्णांक rc = 0;

	gprs_high = (compat_uदीर्घ_t *)
		&task_pt_regs(target)->gprs[pos / माप(compat_uदीर्घ_t)];
	अगर (kbuf) अणु
		स्थिर compat_uदीर्घ_t *k = kbuf;
		जबतक (count > 0) अणु
			*gprs_high = *k++;
			*gprs_high += 2;
			count -= माप(*k);
		पूर्ण
	पूर्ण अन्यथा अणु
		स्थिर compat_uदीर्घ_t  __user *u = ubuf;
		जबतक (count > 0 && !rc) अणु
			अचिन्हित दीर्घ word;
			rc = __get_user(word, u++);
			अगर (rc)
				अवरोध;
			*gprs_high = word;
			*gprs_high += 2;
			count -= माप(*u);
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक s390_compat_last_अवरोध_get(काष्ठा task_काष्ठा *target,
				      स्थिर काष्ठा user_regset *regset,
				      काष्ठा membuf to)
अणु
	compat_uदीर्घ_t last_अवरोध = target->thपढ़ो.last_अवरोध;

	वापस membuf_store(&to, (अचिन्हित दीर्घ)last_अवरोध);
पूर्ण

अटल पूर्णांक s390_compat_last_अवरोध_set(काष्ठा task_काष्ठा *target,
				      स्थिर काष्ठा user_regset *regset,
				      अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
				      स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा user_regset s390_compat_regsets[] = अणु
	अणु
		.core_note_type = NT_PRSTATUS,
		.n = माप(s390_compat_regs) / माप(compat_दीर्घ_t),
		.size = माप(compat_दीर्घ_t),
		.align = माप(compat_दीर्घ_t),
		.regset_get = s390_compat_regs_get,
		.set = s390_compat_regs_set,
	पूर्ण,
	अणु
		.core_note_type = NT_PRFPREG,
		.n = माप(s390_fp_regs) / माप(compat_दीर्घ_t),
		.size = माप(compat_दीर्घ_t),
		.align = माप(compat_दीर्घ_t),
		.regset_get = s390_fpregs_get,
		.set = s390_fpregs_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_SYSTEM_CALL,
		.n = 1,
		.size = माप(compat_uपूर्णांक_t),
		.align = माप(compat_uपूर्णांक_t),
		.regset_get = s390_प्रणाली_call_get,
		.set = s390_प्रणाली_call_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_LAST_BREAK,
		.n = 1,
		.size = माप(दीर्घ),
		.align = माप(दीर्घ),
		.regset_get = s390_compat_last_अवरोध_get,
		.set = s390_compat_last_अवरोध_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_TDB,
		.n = 1,
		.size = 256,
		.align = 1,
		.regset_get = s390_tdb_get,
		.set = s390_tdb_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_VXRS_LOW,
		.n = __NUM_VXRS_LOW,
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_vxrs_low_get,
		.set = s390_vxrs_low_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_VXRS_HIGH,
		.n = __NUM_VXRS_HIGH,
		.size = माप(__vector128),
		.align = माप(__vector128),
		.regset_get = s390_vxrs_high_get,
		.set = s390_vxrs_high_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_HIGH_GPRS,
		.n = माप(s390_compat_regs_high) / माप(compat_दीर्घ_t),
		.size = माप(compat_दीर्घ_t),
		.align = माप(compat_दीर्घ_t),
		.regset_get = s390_compat_regs_high_get,
		.set = s390_compat_regs_high_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_GS_CB,
		.n = माप(काष्ठा gs_cb) / माप(__u64),
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_gs_cb_get,
		.set = s390_gs_cb_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_GS_BC,
		.n = माप(काष्ठा gs_cb) / माप(__u64),
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_gs_bc_get,
		.set = s390_gs_bc_set,
	पूर्ण,
	अणु
		.core_note_type = NT_S390_RI_CB,
		.n = माप(काष्ठा runसमय_instr_cb) / माप(__u64),
		.size = माप(__u64),
		.align = माप(__u64),
		.regset_get = s390_runसमय_instr_get,
		.set = s390_runसमय_instr_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_s390_compat_view = अणु
	.name = "s390",
	.e_machine = EM_S390,
	.regsets = s390_compat_regsets,
	.n = ARRAY_SIZE(s390_compat_regsets)
पूर्ण;
#पूर्ण_अगर

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (test_tsk_thपढ़ो_flag(task, TIF_31BIT))
		वापस &user_s390_compat_view;
#पूर्ण_अगर
	वापस &user_s390_view;
पूर्ण

अटल स्थिर अक्षर *gpr_names[NUM_GPRS] = अणु
	"r0", "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",
	"r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15",
पूर्ण;

अचिन्हित दीर्घ regs_get_रेजिस्टर(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= NUM_GPRS)
		वापस 0;
	वापस regs->gprs[offset];
पूर्ण

पूर्णांक regs_query_रेजिस्टर_offset(स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ offset;

	अगर (!name || *name != 'r')
		वापस -EINVAL;
	अगर (kम_से_अदीर्घ(name + 1, 10, &offset))
		वापस -EINVAL;
	अगर (offset >= NUM_GPRS)
		वापस -EINVAL;
	वापस offset;
पूर्ण

स्थिर अक्षर *regs_query_रेजिस्टर_name(अचिन्हित पूर्णांक offset)
अणु
	अगर (offset >= NUM_GPRS)
		वापस शून्य;
	वापस gpr_names[offset];
पूर्ण

अटल पूर्णांक regs_within_kernel_stack(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ ksp = kernel_stack_poपूर्णांकer(regs);

	वापस (addr & ~(THREAD_SIZE - 1)) == (ksp & ~(THREAD_SIZE - 1));
पूर्ण

/**
 * regs_get_kernel_stack_nth() - get Nth entry of the stack
 * @regs:pt_regs which contains kernel stack poपूर्णांकer.
 * @n:stack entry number.
 *
 * regs_get_kernel_stack_nth() वापसs @n th entry of the kernel stack which
 * is specअगरined by @regs. If the @n th entry is NOT in the kernel stack,
 * this वापसs 0.
 */
अचिन्हित दीर्घ regs_get_kernel_stack_nth(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक n)
अणु
	अचिन्हित दीर्घ addr;

	addr = kernel_stack_poपूर्णांकer(regs) + n * माप(दीर्घ);
	अगर (!regs_within_kernel_stack(regs, addr))
		वापस 0;
	वापस *(अचिन्हित दीर्घ *)addr;
पूर्ण
