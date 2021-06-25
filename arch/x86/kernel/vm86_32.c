<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1994  Linus Torvalds
 *
 *  29 dec 2001 - Fixed oopses caused by unchecked access to the vm86
 *                stack - Manfred Spraul <manfred@colorfullअगरe.com>
 *
 *  22 mar 2002 - Manfred detected the stackfaults, but didn't handle
 *                them correctly. Now the emulation will be in a
 *                consistent state after stackfaults - Kasper Dupont
 *                <kasperd@daimi.au.dk>
 *
 *  22 mar 2002 - Added missing clear_IF in set_vflags_* Kasper Dupont
 *                <kasperd@daimi.au.dk>
 *
 *  ?? ??? 2002 - Fixed premature वापसs from handle_vm86_fault
 *                caused by Kasper Dupont's changes - Stas Sergeev
 *
 *   4 apr 2002 - Fixed CHECK_IF_IN_TRAP broken by Stas' changes.
 *                Kasper Dupont <kasperd@daimi.au.dk>
 *
 *   9 apr 2002 - Changed syntax of macros in handle_vm86_fault.
 *                Kasper Dupont <kasperd@daimi.au.dk>
 *
 *   9 apr 2002 - Changed stack access macros to jump to a label
 *                instead of वापसing to userspace. This simplअगरies
 *                करो_पूर्णांक, and is needed by handle_vm6_fault. Kasper
 *                Dupont <kasperd@daimi.au.dk>
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/audit.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/slab.h>
#समावेश <linux/security.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/vm86.h>
#समावेश <यंत्र/चयन_to.h>

/*
 * Known problems:
 *
 * Interrupt handling is not guaranteed:
 * - a real x86 will disable all पूर्णांकerrupts क्रम one inकाष्ठाion
 *   after a "mov ss,xx" to make stack handling atomic even without
 *   the 'lss' instruction. We can't guarantee this in v86 mode,
 *   as the next inकाष्ठाion might result in a page fault or similar.
 * - a real x86 will have पूर्णांकerrupts disabled क्रम one inकाष्ठाion
 *   past the 'sti' that enables them. We don't bother with all the
 *   details yet.
 *
 * Let's hope these problems करो not actually matter क्रम anything.
 */


/*
 * 8- and 16-bit रेजिस्टर defines..
 */
#घोषणा AL(regs)	(((अचिन्हित अक्षर *)&((regs)->pt.ax))[0])
#घोषणा AH(regs)	(((अचिन्हित अक्षर *)&((regs)->pt.ax))[1])
#घोषणा IP(regs)	(*(अचिन्हित लघु *)&((regs)->pt.ip))
#घोषणा SP(regs)	(*(अचिन्हित लघु *)&((regs)->pt.sp))

/*
 * भव flags (16 and 32-bit versions)
 */
#घोषणा VFLAGS	(*(अचिन्हित लघु *)&(current->thपढ़ो.vm86->veflags))
#घोषणा VEFLAGS	(current->thपढ़ो.vm86->veflags)

#घोषणा set_flags(X, new, mask) \
((X) = ((X) & ~(mask)) | ((new) & (mask)))

#घोषणा SAFE_MASK	(0xDD5)
#घोषणा RETURN_MASK	(0xDFF)

व्योम save_v86_state(काष्ठा kernel_vm86_regs *regs, पूर्णांक retval)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा vm86plus_काष्ठा __user *user;
	काष्ठा vm86 *vm86 = current->thपढ़ो.vm86;

	/*
	 * This माला_लो called from entry.S with पूर्णांकerrupts disabled, but
	 * from process context. Enable पूर्णांकerrupts here, beक्रमe trying
	 * to access user space.
	 */
	local_irq_enable();

	अगर (!vm86 || !vm86->user_vm86) अणु
		pr_alert("no user_vm86: BAD\n");
		करो_निकास(संक_अंश);
	पूर्ण
	set_flags(regs->pt.flags, VEFLAGS, X86_EFLAGS_VIF | vm86->veflags_mask);
	user = vm86->user_vm86;

	अगर (!user_access_begin(user, vm86->vm86plus.is_vm86pus ?
		       माप(काष्ठा vm86plus_काष्ठा) :
		       माप(काष्ठा vm86_काष्ठा)))
		जाओ Efault;

	unsafe_put_user(regs->pt.bx, &user->regs.ebx, Efault_end);
	unsafe_put_user(regs->pt.cx, &user->regs.ecx, Efault_end);
	unsafe_put_user(regs->pt.dx, &user->regs.edx, Efault_end);
	unsafe_put_user(regs->pt.si, &user->regs.esi, Efault_end);
	unsafe_put_user(regs->pt.di, &user->regs.edi, Efault_end);
	unsafe_put_user(regs->pt.bp, &user->regs.ebp, Efault_end);
	unsafe_put_user(regs->pt.ax, &user->regs.eax, Efault_end);
	unsafe_put_user(regs->pt.ip, &user->regs.eip, Efault_end);
	unsafe_put_user(regs->pt.cs, &user->regs.cs, Efault_end);
	unsafe_put_user(regs->pt.flags, &user->regs.eflags, Efault_end);
	unsafe_put_user(regs->pt.sp, &user->regs.esp, Efault_end);
	unsafe_put_user(regs->pt.ss, &user->regs.ss, Efault_end);
	unsafe_put_user(regs->es, &user->regs.es, Efault_end);
	unsafe_put_user(regs->ds, &user->regs.ds, Efault_end);
	unsafe_put_user(regs->fs, &user->regs.fs, Efault_end);
	unsafe_put_user(regs->gs, &user->regs.gs, Efault_end);

	/*
	 * Don't ग_लिखो screen_biपंचांगap in हाल some user had a value there
	 * and expected it to reमुख्य unchanged.
	 */

	user_access_end();

	preempt_disable();
	tsk->thपढ़ो.sp0 = vm86->saved_sp0;
	tsk->thपढ़ो.sysenter_cs = __KERNEL_CS;
	update_task_stack(tsk);
	refresh_sysenter_cs(&tsk->thपढ़ो);
	vm86->saved_sp0 = 0;
	preempt_enable();

	स_नकल(&regs->pt, &vm86->regs32, माप(काष्ठा pt_regs));

	lazy_load_gs(vm86->regs32.gs);

	regs->pt.ax = retval;
	वापस;

Efault_end:
	user_access_end();
Efault:
	pr_alert("could not access userspace vm86 info\n");
	करो_निकास(संक_अंश);
पूर्ण

अटल पूर्णांक करो_vm86_irq_handling(पूर्णांक subfunction, पूर्णांक irqnumber);
अटल दीर्घ करो_sys_vm86(काष्ठा vm86plus_काष्ठा __user *user_vm86, bool plus);

SYSCALL_DEFINE1(vm86old, काष्ठा vm86_काष्ठा __user *, user_vm86)
अणु
	वापस करो_sys_vm86((काष्ठा vm86plus_काष्ठा __user *) user_vm86, false);
पूर्ण


SYSCALL_DEFINE2(vm86, अचिन्हित दीर्घ, cmd, अचिन्हित दीर्घ, arg)
अणु
	चयन (cmd) अणु
	हाल VM86_REQUEST_IRQ:
	हाल VM86_FREE_IRQ:
	हाल VM86_GET_IRQ_BITS:
	हाल VM86_GET_AND_RESET_IRQ:
		वापस करो_vm86_irq_handling(cmd, (पूर्णांक)arg);
	हाल VM86_PLUS_INSTALL_CHECK:
		/*
		 * NOTE: on old vm86 stuff this will वापस the error
		 *  from access_ok(), because the subfunction is
		 *  पूर्णांकerpreted as (invalid) address to vm86_काष्ठा.
		 *  So the installation check works.
		 */
		वापस 0;
	पूर्ण

	/* we come here only क्रम functions VM86_ENTER, VM86_ENTER_NO_BYPASS */
	वापस करो_sys_vm86((काष्ठा vm86plus_काष्ठा __user *) arg, true);
पूर्ण


अटल दीर्घ करो_sys_vm86(काष्ठा vm86plus_काष्ठा __user *user_vm86, bool plus)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा vm86 *vm86 = tsk->thपढ़ो.vm86;
	काष्ठा kernel_vm86_regs vm86regs;
	काष्ठा pt_regs *regs = current_pt_regs();
	अचिन्हित दीर्घ err = 0;
	काष्ठा vm86_काष्ठा v;

	err = security_mmap_addr(0);
	अगर (err) अणु
		/*
		 * vm86 cannot भवize the address space, so vm86 users
		 * need to manage the low 1MB themselves using mmap.  Given
		 * that BIOS places important data in the first page, vm86
		 * is essentially useless अगर mmap_min_addr != 0.  DOSEMU,
		 * क्रम example, won't even bother trying to use vm86 अगर it
		 * can't map a page at भव address 0.
		 *
		 * To reduce the available kernel attack surface, simply
		 * disallow vm86(old) क्रम users who cannot mmap at va 0.
		 *
		 * The implementation of security_mmap_addr will allow
		 * suitably privileged users to map va 0 even अगर
		 * vm.mmap_min_addr is set above 0, and we want this
		 * behavior क्रम vm86 as well, as it ensures that legacy
		 * tools like vbetool will not fail just because of
		 * vm.mmap_min_addr.
		 */
		pr_info_once("Denied a call to vm86(old) from %s[%d] (uid: %d).  Set the vm.mmap_min_addr sysctl to 0 and/or adjust LSM mmap_min_addr policy to enable vm86 if you are using a vm86-based DOS emulator.\n",
			     current->comm, task_pid_nr(current),
			     from_kuid_munged(&init_user_ns, current_uid()));
		वापस -EPERM;
	पूर्ण

	अगर (!vm86) अणु
		अगर (!(vm86 = kzalloc(माप(*vm86), GFP_KERNEL)))
			वापस -ENOMEM;
		tsk->thपढ़ो.vm86 = vm86;
	पूर्ण
	अगर (vm86->saved_sp0)
		वापस -EPERM;

	अगर (copy_from_user(&v, user_vm86,
			दुरत्व(काष्ठा vm86_काष्ठा, पूर्णांक_revectored)))
		वापस -EFAULT;


	/* VM86_SCREEN_BITMAP had numerous bugs and appears to have no users. */
	अगर (v.flags & VM86_SCREEN_BITMAP) अणु
		अक्षर comm[TASK_COMM_LEN];

		pr_info_once("vm86: '%s' uses VM86_SCREEN_BITMAP, which is no longer supported\n", get_task_comm(comm, current));
		वापस -EINVAL;
	पूर्ण

	स_रखो(&vm86regs, 0, माप(vm86regs));

	vm86regs.pt.bx = v.regs.ebx;
	vm86regs.pt.cx = v.regs.ecx;
	vm86regs.pt.dx = v.regs.edx;
	vm86regs.pt.si = v.regs.esi;
	vm86regs.pt.di = v.regs.edi;
	vm86regs.pt.bp = v.regs.ebp;
	vm86regs.pt.ax = v.regs.eax;
	vm86regs.pt.ip = v.regs.eip;
	vm86regs.pt.cs = v.regs.cs;
	vm86regs.pt.flags = v.regs.eflags;
	vm86regs.pt.sp = v.regs.esp;
	vm86regs.pt.ss = v.regs.ss;
	vm86regs.es = v.regs.es;
	vm86regs.ds = v.regs.ds;
	vm86regs.fs = v.regs.fs;
	vm86regs.gs = v.regs.gs;

	vm86->flags = v.flags;
	vm86->cpu_type = v.cpu_type;

	अगर (copy_from_user(&vm86->पूर्णांक_revectored,
			   &user_vm86->पूर्णांक_revectored,
			   माप(काष्ठा revectored_काष्ठा)))
		वापस -EFAULT;
	अगर (copy_from_user(&vm86->पूर्णांक21_revectored,
			   &user_vm86->पूर्णांक21_revectored,
			   माप(काष्ठा revectored_काष्ठा)))
		वापस -EFAULT;
	अगर (plus) अणु
		अगर (copy_from_user(&vm86->vm86plus, &user_vm86->vm86plus,
				   माप(काष्ठा vm86plus_info_काष्ठा)))
			वापस -EFAULT;
		vm86->vm86plus.is_vm86pus = 1;
	पूर्ण अन्यथा
		स_रखो(&vm86->vm86plus, 0,
		       माप(काष्ठा vm86plus_info_काष्ठा));

	स_नकल(&vm86->regs32, regs, माप(काष्ठा pt_regs));
	vm86->user_vm86 = user_vm86;

/*
 * The flags रेजिस्टर is also special: we cannot trust that the user
 * has set it up safely, so this makes sure पूर्णांकerrupt etc flags are
 * inherited from रक्षित mode.
 */
	VEFLAGS = vm86regs.pt.flags;
	vm86regs.pt.flags &= SAFE_MASK;
	vm86regs.pt.flags |= regs->flags & ~SAFE_MASK;
	vm86regs.pt.flags |= X86_VM_MASK;

	vm86regs.pt.orig_ax = regs->orig_ax;

	चयन (vm86->cpu_type) अणु
	हाल CPU_286:
		vm86->veflags_mask = 0;
		अवरोध;
	हाल CPU_386:
		vm86->veflags_mask = X86_EFLAGS_NT | X86_EFLAGS_IOPL;
		अवरोध;
	हाल CPU_486:
		vm86->veflags_mask = X86_EFLAGS_AC | X86_EFLAGS_NT | X86_EFLAGS_IOPL;
		अवरोध;
	शेष:
		vm86->veflags_mask = X86_EFLAGS_ID | X86_EFLAGS_AC | X86_EFLAGS_NT | X86_EFLAGS_IOPL;
		अवरोध;
	पूर्ण

/*
 * Save old state
 */
	vm86->saved_sp0 = tsk->thपढ़ो.sp0;
	lazy_save_gs(vm86->regs32.gs);

	/* make room क्रम real-mode segments */
	preempt_disable();
	tsk->thपढ़ो.sp0 += 16;

	अगर (boot_cpu_has(X86_FEATURE_SEP)) अणु
		tsk->thपढ़ो.sysenter_cs = 0;
		refresh_sysenter_cs(&tsk->thपढ़ो);
	पूर्ण

	update_task_stack(tsk);
	preempt_enable();

	स_नकल((काष्ठा kernel_vm86_regs *)regs, &vm86regs, माप(vm86regs));
	वापस regs->ax;
पूर्ण

अटल अंतरभूत व्योम set_IF(काष्ठा kernel_vm86_regs *regs)
अणु
	VEFLAGS |= X86_EFLAGS_VIF;
पूर्ण

अटल अंतरभूत व्योम clear_IF(काष्ठा kernel_vm86_regs *regs)
अणु
	VEFLAGS &= ~X86_EFLAGS_VIF;
पूर्ण

अटल अंतरभूत व्योम clear_TF(काष्ठा kernel_vm86_regs *regs)
अणु
	regs->pt.flags &= ~X86_EFLAGS_TF;
पूर्ण

अटल अंतरभूत व्योम clear_AC(काष्ठा kernel_vm86_regs *regs)
अणु
	regs->pt.flags &= ~X86_EFLAGS_AC;
पूर्ण

/*
 * It is correct to call set_IF(regs) from the set_vflags_*
 * functions. However someone क्रमgot to call clear_IF(regs)
 * in the opposite हाल.
 * After the command sequence CLI PUSHF STI POPF you should
 * end up with पूर्णांकerrupts disabled, but you ended up with
 * पूर्णांकerrupts enabled.
 *  ( I was testing my own changes, but the only bug I
 *    could find was in a function I had not changed. )
 * [KD]
 */

अटल अंतरभूत व्योम set_vflags_दीर्घ(अचिन्हित दीर्घ flags, काष्ठा kernel_vm86_regs *regs)
अणु
	set_flags(VEFLAGS, flags, current->thपढ़ो.vm86->veflags_mask);
	set_flags(regs->pt.flags, flags, SAFE_MASK);
	अगर (flags & X86_EFLAGS_IF)
		set_IF(regs);
	अन्यथा
		clear_IF(regs);
पूर्ण

अटल अंतरभूत व्योम set_vflags_लघु(अचिन्हित लघु flags, काष्ठा kernel_vm86_regs *regs)
अणु
	set_flags(VFLAGS, flags, current->thपढ़ो.vm86->veflags_mask);
	set_flags(regs->pt.flags, flags, SAFE_MASK);
	अगर (flags & X86_EFLAGS_IF)
		set_IF(regs);
	अन्यथा
		clear_IF(regs);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ get_vflags(काष्ठा kernel_vm86_regs *regs)
अणु
	अचिन्हित दीर्घ flags = regs->pt.flags & RETURN_MASK;

	अगर (VEFLAGS & X86_EFLAGS_VIF)
		flags |= X86_EFLAGS_IF;
	flags |= X86_EFLAGS_IOPL;
	वापस flags | (VEFLAGS & current->thपढ़ो.vm86->veflags_mask);
पूर्ण

अटल अंतरभूत पूर्णांक is_revectored(पूर्णांक nr, काष्ठा revectored_काष्ठा *biपंचांगap)
अणु
	वापस test_bit(nr, biपंचांगap->__map);
पूर्ण

#घोषणा val_byte(val, n) (((__u8 *)&val)[n])

#घोषणा pushb(base, ptr, val, err_label) \
	करो अणु \
		__u8 __val = val; \
		ptr--; \
		अगर (put_user(__val, base + ptr) < 0) \
			जाओ err_label; \
	पूर्ण जबतक (0)

#घोषणा pushw(base, ptr, val, err_label) \
	करो अणु \
		__u16 __val = val; \
		ptr--; \
		अगर (put_user(val_byte(__val, 1), base + ptr) < 0) \
			जाओ err_label; \
		ptr--; \
		अगर (put_user(val_byte(__val, 0), base + ptr) < 0) \
			जाओ err_label; \
	पूर्ण जबतक (0)

#घोषणा pushl(base, ptr, val, err_label) \
	करो अणु \
		__u32 __val = val; \
		ptr--; \
		अगर (put_user(val_byte(__val, 3), base + ptr) < 0) \
			जाओ err_label; \
		ptr--; \
		अगर (put_user(val_byte(__val, 2), base + ptr) < 0) \
			जाओ err_label; \
		ptr--; \
		अगर (put_user(val_byte(__val, 1), base + ptr) < 0) \
			जाओ err_label; \
		ptr--; \
		अगर (put_user(val_byte(__val, 0), base + ptr) < 0) \
			जाओ err_label; \
	पूर्ण जबतक (0)

#घोषणा popb(base, ptr, err_label) \
	(अणु \
		__u8 __res; \
		अगर (get_user(__res, base + ptr) < 0) \
			जाओ err_label; \
		ptr++; \
		__res; \
	पूर्ण)

#घोषणा popw(base, ptr, err_label) \
	(अणु \
		__u16 __res; \
		अगर (get_user(val_byte(__res, 0), base + ptr) < 0) \
			जाओ err_label; \
		ptr++; \
		अगर (get_user(val_byte(__res, 1), base + ptr) < 0) \
			जाओ err_label; \
		ptr++; \
		__res; \
	पूर्ण)

#घोषणा popl(base, ptr, err_label) \
	(अणु \
		__u32 __res; \
		अगर (get_user(val_byte(__res, 0), base + ptr) < 0) \
			जाओ err_label; \
		ptr++; \
		अगर (get_user(val_byte(__res, 1), base + ptr) < 0) \
			जाओ err_label; \
		ptr++; \
		अगर (get_user(val_byte(__res, 2), base + ptr) < 0) \
			जाओ err_label; \
		ptr++; \
		अगर (get_user(val_byte(__res, 3), base + ptr) < 0) \
			जाओ err_label; \
		ptr++; \
		__res; \
	पूर्ण)

/* There are so many possible reasons क्रम this function to वापस
 * VM86_INTx, so adding another करोesn't bother me. We can expect
 * userspace programs to be able to handle it. (Getting a problem
 * in userspace is always better than an Oops anyway.) [KD]
 */
अटल व्योम करो_पूर्णांक(काष्ठा kernel_vm86_regs *regs, पूर्णांक i,
    अचिन्हित अक्षर __user *ssp, अचिन्हित लघु sp)
अणु
	अचिन्हित दीर्घ __user *पूर्णांकr_ptr;
	अचिन्हित दीर्घ segoffs;
	काष्ठा vm86 *vm86 = current->thपढ़ो.vm86;

	अगर (regs->pt.cs == BIOSSEG)
		जाओ cannot_handle;
	अगर (is_revectored(i, &vm86->पूर्णांक_revectored))
		जाओ cannot_handle;
	अगर (i == 0x21 && is_revectored(AH(regs), &vm86->पूर्णांक21_revectored))
		जाओ cannot_handle;
	पूर्णांकr_ptr = (अचिन्हित दीर्घ __user *) (i << 2);
	अगर (get_user(segoffs, पूर्णांकr_ptr))
		जाओ cannot_handle;
	अगर ((segoffs >> 16) == BIOSSEG)
		जाओ cannot_handle;
	pushw(ssp, sp, get_vflags(regs), cannot_handle);
	pushw(ssp, sp, regs->pt.cs, cannot_handle);
	pushw(ssp, sp, IP(regs), cannot_handle);
	regs->pt.cs = segoffs >> 16;
	SP(regs) -= 6;
	IP(regs) = segoffs & 0xffff;
	clear_TF(regs);
	clear_IF(regs);
	clear_AC(regs);
	वापस;

cannot_handle:
	save_v86_state(regs, VM86_INTx + (i << 8));
पूर्ण

पूर्णांक handle_vm86_trap(काष्ठा kernel_vm86_regs *regs, दीर्घ error_code, पूर्णांक trapno)
अणु
	काष्ठा vm86 *vm86 = current->thपढ़ो.vm86;

	अगर (vm86->vm86plus.is_vm86pus) अणु
		अगर ((trapno == 3) || (trapno == 1)) अणु
			save_v86_state(regs, VM86_TRAP + (trapno << 8));
			वापस 0;
		पूर्ण
		करो_पूर्णांक(regs, trapno, (अचिन्हित अक्षर __user *) (regs->pt.ss << 4), SP(regs));
		वापस 0;
	पूर्ण
	अगर (trapno != 1)
		वापस 1; /* we let this handle by the calling routine */
	current->thपढ़ो.trap_nr = trapno;
	current->thपढ़ो.error_code = error_code;
	क्रमce_sig(SIGTRAP);
	वापस 0;
पूर्ण

व्योम handle_vm86_fault(काष्ठा kernel_vm86_regs *regs, दीर्घ error_code)
अणु
	अचिन्हित अक्षर opcode;
	अचिन्हित अक्षर __user *csp;
	अचिन्हित अक्षर __user *ssp;
	अचिन्हित लघु ip, sp, orig_flags;
	पूर्णांक data32, pref_करोne;
	काष्ठा vm86plus_info_काष्ठा *vmpi = &current->thपढ़ो.vm86->vm86plus;

#घोषणा CHECK_IF_IN_TRAP \
	अगर (vmpi->vm86dbg_active && vmpi->vm86dbg_TFpendig) \
		newflags |= X86_EFLAGS_TF

	orig_flags = *(अचिन्हित लघु *)&regs->pt.flags;

	csp = (अचिन्हित अक्षर __user *) (regs->pt.cs << 4);
	ssp = (अचिन्हित अक्षर __user *) (regs->pt.ss << 4);
	sp = SP(regs);
	ip = IP(regs);

	data32 = 0;
	pref_करोne = 0;
	करो अणु
		चयन (opcode = popb(csp, ip, simulate_sigsegv)) अणु
		हाल 0x66:      /* 32-bit data */     data32 = 1; अवरोध;
		हाल 0x67:      /* 32-bit address */  अवरोध;
		हाल 0x2e:      /* CS */              अवरोध;
		हाल 0x3e:      /* DS */              अवरोध;
		हाल 0x26:      /* ES */              अवरोध;
		हाल 0x36:      /* SS */              अवरोध;
		हाल 0x65:      /* GS */              अवरोध;
		हाल 0x64:      /* FS */              अवरोध;
		हाल 0xf2:      /* repnz */       अवरोध;
		हाल 0xf3:      /* rep */             अवरोध;
		शेष: pref_करोne = 1;
		पूर्ण
	पूर्ण जबतक (!pref_करोne);

	चयन (opcode) अणु

	/* pushf */
	हाल 0x9c:
		अगर (data32) अणु
			pushl(ssp, sp, get_vflags(regs), simulate_sigsegv);
			SP(regs) -= 4;
		पूर्ण अन्यथा अणु
			pushw(ssp, sp, get_vflags(regs), simulate_sigsegv);
			SP(regs) -= 2;
		पूर्ण
		IP(regs) = ip;
		जाओ vm86_fault_वापस;

	/* popf */
	हाल 0x9d:
		अणु
		अचिन्हित दीर्घ newflags;
		अगर (data32) अणु
			newflags = popl(ssp, sp, simulate_sigsegv);
			SP(regs) += 4;
		पूर्ण अन्यथा अणु
			newflags = popw(ssp, sp, simulate_sigsegv);
			SP(regs) += 2;
		पूर्ण
		IP(regs) = ip;
		CHECK_IF_IN_TRAP;
		अगर (data32)
			set_vflags_दीर्घ(newflags, regs);
		अन्यथा
			set_vflags_लघु(newflags, regs);

		जाओ check_vip;
		पूर्ण

	/* पूर्णांक xx */
	हाल 0xcd: अणु
		पूर्णांक पूर्णांकno = popb(csp, ip, simulate_sigsegv);
		IP(regs) = ip;
		अगर (vmpi->vm86dbg_active) अणु
			अगर ((1 << (पूर्णांकno & 7)) & vmpi->vm86dbg_पूर्णांकxxtab[पूर्णांकno >> 3]) अणु
				save_v86_state(regs, VM86_INTx + (पूर्णांकno << 8));
				वापस;
			पूर्ण
		पूर्ण
		करो_पूर्णांक(regs, पूर्णांकno, ssp, sp);
		वापस;
	पूर्ण

	/* iret */
	हाल 0xcf:
		अणु
		अचिन्हित दीर्घ newip;
		अचिन्हित दीर्घ newcs;
		अचिन्हित दीर्घ newflags;
		अगर (data32) अणु
			newip = popl(ssp, sp, simulate_sigsegv);
			newcs = popl(ssp, sp, simulate_sigsegv);
			newflags = popl(ssp, sp, simulate_sigsegv);
			SP(regs) += 12;
		पूर्ण अन्यथा अणु
			newip = popw(ssp, sp, simulate_sigsegv);
			newcs = popw(ssp, sp, simulate_sigsegv);
			newflags = popw(ssp, sp, simulate_sigsegv);
			SP(regs) += 6;
		पूर्ण
		IP(regs) = newip;
		regs->pt.cs = newcs;
		CHECK_IF_IN_TRAP;
		अगर (data32) अणु
			set_vflags_दीर्घ(newflags, regs);
		पूर्ण अन्यथा अणु
			set_vflags_लघु(newflags, regs);
		पूर्ण
		जाओ check_vip;
		पूर्ण

	/* cli */
	हाल 0xfa:
		IP(regs) = ip;
		clear_IF(regs);
		जाओ vm86_fault_वापस;

	/* sti */
	/*
	 * Damn. This is incorrect: the 'sti' inकाष्ठाion should actually
	 * enable पूर्णांकerrupts after the /next/ inकाष्ठाion. Not good.
	 *
	 * Probably needs some horsing around with the TF flag. Aiee..
	 */
	हाल 0xfb:
		IP(regs) = ip;
		set_IF(regs);
		जाओ check_vip;

	शेष:
		save_v86_state(regs, VM86_UNKNOWN);
	पूर्ण

	वापस;

check_vip:
	अगर ((VEFLAGS & (X86_EFLAGS_VIP | X86_EFLAGS_VIF)) ==
	    (X86_EFLAGS_VIP | X86_EFLAGS_VIF)) अणु
		save_v86_state(regs, VM86_STI);
		वापस;
	पूर्ण

vm86_fault_वापस:
	अगर (vmpi->क्रमce_वापस_क्रम_pic  && (VEFLAGS & (X86_EFLAGS_IF | X86_EFLAGS_VIF))) अणु
		save_v86_state(regs, VM86_PICRETURN);
		वापस;
	पूर्ण
	अगर (orig_flags & X86_EFLAGS_TF)
		handle_vm86_trap(regs, 0, X86_TRAP_DB);
	वापस;

simulate_sigsegv:
	/* FIXME: After a दीर्घ discussion with Stas we finally
	 *        agreed, that this is wrong. Here we should
	 *        really send a संक_अंश to the user program.
	 *        But how करो we create the correct context? We
	 *        are inside a general protection fault handler
	 *        and has just वापसed from a page fault handler.
	 *        The correct context क्रम the संकेत handler
	 *        should be a mixture of the two, but how करो we
	 *        get the inक्रमmation? [KD]
	 */
	save_v86_state(regs, VM86_UNKNOWN);
पूर्ण

/* ---------------- vm86 special IRQ passing stuff ----------------- */

#घोषणा VM86_IRQNAME		"vm86irq"

अटल काष्ठा vm86_irqs अणु
	काष्ठा task_काष्ठा *tsk;
	पूर्णांक sig;
पूर्ण vm86_irqs[16];

अटल DEFINE_SPINLOCK(irqbits_lock);
अटल पूर्णांक irqbits;

#घोषणा ALLOWED_SIGS (1 /* 0 = करोn't send a संकेत */ \
	| (1 << SIGUSR1) | (1 << SIGUSR2) | (1 << SIGIO)  | (1 << SIGURG) \
	| (1 << SIGUNUSED))

अटल irqवापस_t irq_handler(पूर्णांक पूर्णांकno, व्योम *dev_id)
अणु
	पूर्णांक irq_bit;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&irqbits_lock, flags);
	irq_bit = 1 << पूर्णांकno;
	अगर ((irqbits & irq_bit) || !vm86_irqs[पूर्णांकno].tsk)
		जाओ out;
	irqbits |= irq_bit;
	अगर (vm86_irqs[पूर्णांकno].sig)
		send_sig(vm86_irqs[पूर्णांकno].sig, vm86_irqs[पूर्णांकno].tsk, 1);
	/*
	 * IRQ will be re-enabled when user asks क्रम the irq (whether
	 * polling or as a result of the संकेत)
	 */
	disable_irq_nosync(पूर्णांकno);
	spin_unlock_irqrestore(&irqbits_lock, flags);
	वापस IRQ_HANDLED;

out:
	spin_unlock_irqrestore(&irqbits_lock, flags);
	वापस IRQ_NONE;
पूर्ण

अटल अंतरभूत व्योम मुक्त_vm86_irq(पूर्णांक irqnumber)
अणु
	अचिन्हित दीर्घ flags;

	मुक्त_irq(irqnumber, शून्य);
	vm86_irqs[irqnumber].tsk = शून्य;

	spin_lock_irqsave(&irqbits_lock, flags);
	irqbits &= ~(1 << irqnumber);
	spin_unlock_irqrestore(&irqbits_lock, flags);
पूर्ण

व्योम release_vm86_irqs(काष्ठा task_काष्ठा *task)
अणु
	पूर्णांक i;
	क्रम (i = FIRST_VM86_IRQ ; i <= LAST_VM86_IRQ; i++)
	    अगर (vm86_irqs[i].tsk == task)
		मुक्त_vm86_irq(i);
पूर्ण

अटल अंतरभूत पूर्णांक get_and_reset_irq(पूर्णांक irqnumber)
अणु
	पूर्णांक bit;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (invalid_vm86_irq(irqnumber)) वापस 0;
	अगर (vm86_irqs[irqnumber].tsk != current) वापस 0;
	spin_lock_irqsave(&irqbits_lock, flags);
	bit = irqbits & (1 << irqnumber);
	irqbits &= ~bit;
	अगर (bit) अणु
		enable_irq(irqnumber);
		ret = 1;
	पूर्ण

	spin_unlock_irqrestore(&irqbits_lock, flags);
	वापस ret;
पूर्ण


अटल पूर्णांक करो_vm86_irq_handling(पूर्णांक subfunction, पूर्णांक irqnumber)
अणु
	पूर्णांक ret;
	चयन (subfunction) अणु
		हाल VM86_GET_AND_RESET_IRQ: अणु
			वापस get_and_reset_irq(irqnumber);
		पूर्ण
		हाल VM86_GET_IRQ_BITS: अणु
			वापस irqbits;
		पूर्ण
		हाल VM86_REQUEST_IRQ: अणु
			पूर्णांक sig = irqnumber >> 8;
			पूर्णांक irq = irqnumber & 255;
			अगर (!capable(CAP_SYS_ADMIN)) वापस -EPERM;
			अगर (!((1 << sig) & ALLOWED_SIGS)) वापस -EPERM;
			अगर (invalid_vm86_irq(irq)) वापस -EPERM;
			अगर (vm86_irqs[irq].tsk) वापस -EPERM;
			ret = request_irq(irq, &irq_handler, 0, VM86_IRQNAME, शून्य);
			अगर (ret) वापस ret;
			vm86_irqs[irq].sig = sig;
			vm86_irqs[irq].tsk = current;
			वापस irq;
		पूर्ण
		हाल  VM86_FREE_IRQ: अणु
			अगर (invalid_vm86_irq(irqnumber)) वापस -EPERM;
			अगर (!vm86_irqs[irqnumber].tsk) वापस 0;
			अगर (vm86_irqs[irqnumber].tsk != current) वापस -EPERM;
			मुक्त_vm86_irq(irqnumber);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

