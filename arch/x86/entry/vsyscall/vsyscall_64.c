<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012-2014 Andy Lutomirski <luto@amacapital.net>
 *
 * Based on the original implementation which is:
 *  Copyright (C) 2001 Andrea Arcangeli <andrea@suse.de> SuSE
 *  Copyright 2003 Andi Kleen, SuSE Lअसल.
 *
 *  Parts of the original code have been moved to arch/x86/vdso/vma.c
 *
 * This file implements vsyscall emulation.  vsyscalls are a legacy ABI:
 * Userspace can request certain kernel services by calling fixed
 * addresses.  This concept is problematic:
 *
 * - It पूर्णांकerferes with ASLR.
 * - It's awkward to ग_लिखो code that lives in kernel addresses but is
 *   callable by userspace at fixed addresses.
 * - The whole concept is impossible क्रम 32-bit compat userspace.
 * - UML cannot easily भवize a vsyscall.
 *
 * As of mid-2014, I believe that there is no new userspace code that
 * will use a vsyscall अगर the vDSO is present.  I hope that there will
 * soon be no new userspace code that will ever use a vsyscall.
 *
 * The code in this file emulates vsyscalls when notअगरied of a page
 * fault to a vsyscall address.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/समयr.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mm_types.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/ratelimit.h>

#समावेश <यंत्र/vsyscall.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/paravirt.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश "vsyscall_trace.h"

अटल क्रमागत अणु EMULATE, XONLY, NONE पूर्ण vsyscall_mode __ro_after_init =
#अगर_घोषित CONFIG_LEGACY_VSYSCALL_NONE
	NONE;
#या_अगर defined(CONFIG_LEGACY_VSYSCALL_XONLY)
	XONLY;
#अन्यथा
	EMULATE;
#पूर्ण_अगर

अटल पूर्णांक __init vsyscall_setup(अक्षर *str)
अणु
	अगर (str) अणु
		अगर (!म_भेद("emulate", str))
			vsyscall_mode = EMULATE;
		अन्यथा अगर (!म_भेद("xonly", str))
			vsyscall_mode = XONLY;
		अन्यथा अगर (!म_भेद("none", str))
			vsyscall_mode = NONE;
		अन्यथा
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण
early_param("vsyscall", vsyscall_setup);

अटल व्योम warn_bad_vsyscall(स्थिर अक्षर *level, काष्ठा pt_regs *regs,
			      स्थिर अक्षर *message)
अणु
	अगर (!show_unhandled_संकेतs)
		वापस;

	prपूर्णांकk_ratelimited("%s%s[%d] %s ip:%lx cs:%lx sp:%lx ax:%lx si:%lx di:%lx\n",
			   level, current->comm, task_pid_nr(current),
			   message, regs->ip, regs->cs,
			   regs->sp, regs->ax, regs->si, regs->di);
पूर्ण

अटल पूर्णांक addr_to_vsyscall_nr(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक nr;

	अगर ((addr & ~0xC00UL) != VSYSCALL_ADDR)
		वापस -EINVAL;

	nr = (addr & 0xC00UL) >> 10;
	अगर (nr >= 3)
		वापस -EINVAL;

	वापस nr;
पूर्ण

अटल bool ग_लिखो_ok_or_segv(अचिन्हित दीर्घ ptr, माप_प्रकार size)
अणु
	/*
	 * XXX: अगर access_ok, get_user, and put_user handled
	 * sig_on_uaccess_err, this could go away.
	 */

	अगर (!access_ok((व्योम __user *)ptr, size)) अणु
		काष्ठा thपढ़ो_काष्ठा *thपढ़ो = &current->thपढ़ो;

		thपढ़ो->error_code	= X86_PF_USER | X86_PF_WRITE;
		thपढ़ो->cr2		= ptr;
		thपढ़ो->trap_nr		= X86_TRAP_PF;

		क्रमce_sig_fault(संक_अंश, SEGV_MAPERR, (व्योम __user *)ptr);
		वापस false;
	पूर्ण अन्यथा अणु
		वापस true;
	पूर्ण
पूर्ण

bool emulate_vsyscall(अचिन्हित दीर्घ error_code,
		      काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
	काष्ठा task_काष्ठा *tsk;
	अचिन्हित दीर्घ caller;
	पूर्णांक vsyscall_nr, syscall_nr, पंचांगp;
	पूर्णांक prev_sig_on_uaccess_err;
	दीर्घ ret;
	अचिन्हित दीर्घ orig_dx;

	/* Write faults or kernel-privilege faults never get fixed up. */
	अगर ((error_code & (X86_PF_WRITE | X86_PF_USER)) != X86_PF_USER)
		वापस false;

	अगर (!(error_code & X86_PF_INSTR)) अणु
		/* Failed vsyscall पढ़ो */
		अगर (vsyscall_mode == EMULATE)
			वापस false;

		/*
		 * User code tried and failed to पढ़ो the vsyscall page.
		 */
		warn_bad_vsyscall(KERN_INFO, regs, "vsyscall read attempt denied -- look up the vsyscall kernel parameter if you need a workaround");
		वापस false;
	पूर्ण

	/*
	 * No poपूर्णांक in checking CS -- the only way to get here is a user mode
	 * trap to a high address, which means that we're in 64-bit user code.
	 */

	WARN_ON_ONCE(address != regs->ip);

	अगर (vsyscall_mode == NONE) अणु
		warn_bad_vsyscall(KERN_INFO, regs,
				  "vsyscall attempted with vsyscall=none");
		वापस false;
	पूर्ण

	vsyscall_nr = addr_to_vsyscall_nr(address);

	trace_emulate_vsyscall(vsyscall_nr);

	अगर (vsyscall_nr < 0) अणु
		warn_bad_vsyscall(KERN_WARNING, regs,
				  "misaligned vsyscall (exploit attempt or buggy program) -- look up the vsyscall kernel parameter if you need a workaround");
		जाओ sigsegv;
	पूर्ण

	अगर (get_user(caller, (अचिन्हित दीर्घ __user *)regs->sp) != 0) अणु
		warn_bad_vsyscall(KERN_WARNING, regs,
				  "vsyscall with bad stack (exploit attempt?)");
		जाओ sigsegv;
	पूर्ण

	tsk = current;

	/*
	 * Check क्रम access_ok violations and find the syscall nr.
	 *
	 * शून्य is a valid user poपूर्णांकer (in the access_ok sense) on 32-bit and
	 * 64-bit, so we करोn't need to special-हाल it here.  For all the
	 * vsyscalls, शून्य means "don't write anything" not "ग_लिखो it at
	 * address 0".
	 */
	चयन (vsyscall_nr) अणु
	हाल 0:
		अगर (!ग_लिखो_ok_or_segv(regs->di, माप(काष्ठा __kernel_old_समयval)) ||
		    !ग_लिखो_ok_or_segv(regs->si, माप(काष्ठा समयzone))) अणु
			ret = -EFAULT;
			जाओ check_fault;
		पूर्ण

		syscall_nr = __NR_समय_लोofday;
		अवरोध;

	हाल 1:
		अगर (!ग_लिखो_ok_or_segv(regs->di, माप(__kernel_old_समय_प्रकार))) अणु
			ret = -EFAULT;
			जाओ check_fault;
		पूर्ण

		syscall_nr = __NR_समय;
		अवरोध;

	हाल 2:
		अगर (!ग_लिखो_ok_or_segv(regs->di, माप(अचिन्हित)) ||
		    !ग_लिखो_ok_or_segv(regs->si, माप(अचिन्हित))) अणु
			ret = -EFAULT;
			जाओ check_fault;
		पूर्ण

		syscall_nr = __NR_अ_लोpu;
		अवरोध;
	पूर्ण

	/*
	 * Handle seccomp.  regs->ip must be the original value.
	 * See seccomp_send_sigsys and Documentation/userspace-api/seccomp_filter.rst.
	 *
	 * We could optimize the seccomp disabled हाल, but perक्रमmance
	 * here करोesn't matter.
	 */
	regs->orig_ax = syscall_nr;
	regs->ax = -ENOSYS;
	पंचांगp = secure_computing();
	अगर ((!पंचांगp && regs->orig_ax != syscall_nr) || regs->ip != address) अणु
		warn_bad_vsyscall(KERN_DEBUG, regs,
				  "seccomp tried to change syscall nr or ip");
		करो_निकास(SIGSYS);
	पूर्ण
	regs->orig_ax = -1;
	अगर (पंचांगp)
		जाओ करो_ret;  /* skip requested */

	/*
	 * With a real vsyscall, page faults cause संक_अंश.  We want to
	 * preserve that behavior to make writing exploits harder.
	 */
	prev_sig_on_uaccess_err = current->thपढ़ो.sig_on_uaccess_err;
	current->thपढ़ो.sig_on_uaccess_err = 1;

	ret = -EFAULT;
	चयन (vsyscall_nr) अणु
	हाल 0:
		/* this decodes regs->di and regs->si on its own */
		ret = __x64_sys_समय_लोofday(regs);
		अवरोध;

	हाल 1:
		/* this decodes regs->di on its own */
		ret = __x64_sys_समय(regs);
		अवरोध;

	हाल 2:
		/* जबतक we could clobber regs->dx, we didn't in the past... */
		orig_dx = regs->dx;
		regs->dx = 0;
		/* this decodes regs->di, regs->si and regs->dx on its own */
		ret = __x64_sys_अ_लोpu(regs);
		regs->dx = orig_dx;
		अवरोध;
	पूर्ण

	current->thपढ़ो.sig_on_uaccess_err = prev_sig_on_uaccess_err;

check_fault:
	अगर (ret == -EFAULT) अणु
		/* Bad news -- userspace fed a bad poपूर्णांकer to a vsyscall. */
		warn_bad_vsyscall(KERN_INFO, regs,
				  "vsyscall fault (exploit attempt?)");

		/*
		 * If we failed to generate a संकेत क्रम any reason,
		 * generate one here.  (This should be impossible.)
		 */
		अगर (WARN_ON_ONCE(!sigismember(&tsk->pending.संकेत, SIGBUS) &&
				 !sigismember(&tsk->pending.संकेत, संक_अंश)))
			जाओ sigsegv;

		वापस true;  /* Don't emulate the ret. */
	पूर्ण

	regs->ax = ret;

करो_ret:
	/* Emulate a ret inकाष्ठाion. */
	regs->ip = caller;
	regs->sp += 8;
	वापस true;

sigsegv:
	क्रमce_sig(संक_अंश);
	वापस true;
पूर्ण

/*
 * A pseuकरो VMA to allow ptrace access क्रम the vsyscall page.  This only
 * covers the 64bit vsyscall page now. 32bit has a real VMA now and करोes
 * not need special handling anymore:
 */
अटल स्थिर अक्षर *gate_vma_name(काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस "[vsyscall]";
पूर्ण
अटल स्थिर काष्ठा vm_operations_काष्ठा gate_vma_ops = अणु
	.name = gate_vma_name,
पूर्ण;
अटल काष्ठा vm_area_काष्ठा gate_vma __ro_after_init = अणु
	.vm_start	= VSYSCALL_ADDR,
	.vm_end		= VSYSCALL_ADDR + PAGE_SIZE,
	.vm_page_prot	= PAGE_READONLY_EXEC,
	.vm_flags	= VM_READ | VM_EXEC,
	.vm_ops		= &gate_vma_ops,
पूर्ण;

काष्ठा vm_area_काष्ठा *get_gate_vma(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (!mm || !(mm->context.flags & MM_CONTEXT_HAS_VSYSCALL))
		वापस शून्य;
#पूर्ण_अगर
	अगर (vsyscall_mode == NONE)
		वापस शून्य;
	वापस &gate_vma;
पूर्ण

पूर्णांक in_gate_area(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	काष्ठा vm_area_काष्ठा *vma = get_gate_vma(mm);

	अगर (!vma)
		वापस 0;

	वापस (addr >= vma->vm_start) && (addr < vma->vm_end);
पूर्ण

/*
 * Use this when you have no reliable mm, typically from पूर्णांकerrupt
 * context. It is less reliable than using a task's mm and may give
 * false positives.
 */
पूर्णांक in_gate_area_no_mm(अचिन्हित दीर्घ addr)
अणु
	वापस vsyscall_mode != NONE && (addr & PAGE_MASK) == VSYSCALL_ADDR;
पूर्ण

/*
 * The VSYSCALL page is the only user-accessible page in the kernel address
 * range.  Normally, the kernel page tables can have _PAGE_USER clear, but
 * the tables covering VSYSCALL_ADDR need _PAGE_USER set अगर vsyscalls
 * are enabled.
 *
 * Some day we may create a "minimal" vsyscall mode in which we emulate
 * vsyscalls but leave the page not present.  If so, we skip calling
 * this.
 */
व्योम __init set_vsyscall_pgtable_user_bits(pgd_t *root)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset_pgd(root, VSYSCALL_ADDR);
	set_pgd(pgd, __pgd(pgd_val(*pgd) | _PAGE_USER));
	p4d = p4d_offset(pgd, VSYSCALL_ADDR);
#अगर CONFIG_PGTABLE_LEVELS >= 5
	set_p4d(p4d, __p4d(p4d_val(*p4d) | _PAGE_USER));
#पूर्ण_अगर
	pud = pud_offset(p4d, VSYSCALL_ADDR);
	set_pud(pud, __pud(pud_val(*pud) | _PAGE_USER));
	pmd = pmd_offset(pud, VSYSCALL_ADDR);
	set_pmd(pmd, __pmd(pmd_val(*pmd) | _PAGE_USER));
पूर्ण

व्योम __init map_vsyscall(व्योम)
अणु
	बाह्य अक्षर __vsyscall_page;
	अचिन्हित दीर्घ physaddr_vsyscall = __pa_symbol(&__vsyscall_page);

	/*
	 * For full emulation, the page needs to exist क्रम real.  In
	 * execute-only mode, there is no PTE at all backing the vsyscall
	 * page.
	 */
	अगर (vsyscall_mode == EMULATE) अणु
		__set_fixmap(VSYSCALL_PAGE, physaddr_vsyscall,
			     PAGE_KERNEL_VVAR);
		set_vsyscall_pgtable_user_bits(swapper_pg_dir);
	पूर्ण

	अगर (vsyscall_mode == XONLY)
		gate_vma.vm_flags = VM_EXEC;

	BUILD_BUG_ON((अचिन्हित दीर्घ)__fix_to_virt(VSYSCALL_PAGE) !=
		     (अचिन्हित दीर्घ)VSYSCALL_ADDR);
पूर्ण
