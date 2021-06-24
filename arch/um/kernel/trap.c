<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2000 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 */

#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/hardirq.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/debug.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <arch.h>
#समावेश <as-layout.h>
#समावेश <kern_util.h>
#समावेश <os.h>
#समावेश <skas.h>

/*
 * Note this is स्थिरrained to वापस 0, -EFAULT, -EACCES, -ENOMEM by
 * segv().
 */
पूर्णांक handle_page_fault(अचिन्हित दीर्घ address, अचिन्हित दीर्घ ip,
		      पूर्णांक is_ग_लिखो, पूर्णांक is_user, पूर्णांक *code_out)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक err = -EFAULT;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	*code_out = SEGV_MAPERR;

	/*
	 * If the fault was with pagefaults disabled, करोn't take the fault, just
	 * fail.
	 */
	अगर (faulthandler_disabled())
		जाओ out_nosemaphore;

	अगर (is_user)
		flags |= FAULT_FLAG_USER;
retry:
	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, address);
	अगर (!vma)
		जाओ out;
	अन्यथा अगर (vma->vm_start <= address)
		जाओ good_area;
	अन्यथा अगर (!(vma->vm_flags & VM_GROWSDOWN))
		जाओ out;
	अन्यथा अगर (is_user && !ARCH_IS_STACKGROW(address))
		जाओ out;
	अन्यथा अगर (expand_stack(vma, address))
		जाओ out;

good_area:
	*code_out = SEGV_ACCERR;
	अगर (is_ग_लिखो) अणु
		अगर (!(vma->vm_flags & VM_WRITE))
			जाओ out;
		flags |= FAULT_FLAG_WRITE;
	पूर्ण अन्यथा अणु
		/* Don't require VM_READ|VM_EXEC क्रम ग_लिखो faults! */
		अगर (!(vma->vm_flags & (VM_READ | VM_EXEC)))
			जाओ out;
	पूर्ण

	करो अणु
		vm_fault_t fault;

		fault = handle_mm_fault(vma, address, flags, शून्य);

		अगर ((fault & VM_FAULT_RETRY) && fatal_संकेत_pending(current))
			जाओ out_nosemaphore;

		अगर (unlikely(fault & VM_FAULT_ERROR)) अणु
			अगर (fault & VM_FAULT_OOM) अणु
				जाओ out_of_memory;
			पूर्ण अन्यथा अगर (fault & VM_FAULT_संक_अंश) अणु
				जाओ out;
			पूर्ण अन्यथा अगर (fault & VM_FAULT_SIGBUS) अणु
				err = -EACCES;
				जाओ out;
			पूर्ण
			BUG();
		पूर्ण
		अगर (flags & FAULT_FLAG_ALLOW_RETRY) अणु
			अगर (fault & VM_FAULT_RETRY) अणु
				flags |= FAULT_FLAG_TRIED;

				जाओ retry;
			पूर्ण
		पूर्ण

		pmd = pmd_off(mm, address);
		pte = pte_offset_kernel(pmd, address);
	पूर्ण जबतक (!pte_present(*pte));
	err = 0;
	/*
	 * The below warning was added in place of
	 *	pte_mkyoung(); अगर (is_ग_लिखो) pte_सूची_गढ़ोty();
	 * If it's triggered, we'd see normally a hang here (a clean pte is
	 * marked पढ़ो-only to emulate the dirty bit).
	 * However, the generic code can mark a PTE writable but clean on a
	 * concurrent पढ़ो fault, triggering this harmlessly. So comment it out.
	 */
#अगर 0
	WARN_ON(!pte_young(*pte) || (is_ग_लिखो && !pte_dirty(*pte)));
#पूर्ण_अगर
	flush_tlb_page(vma, address);
out:
	mmap_पढ़ो_unlock(mm);
out_nosemaphore:
	वापस err;

out_of_memory:
	/*
	 * We ran out of memory, call the OOM समाप्तer, and वापस the userspace
	 * (which will retry the fault, or समाप्त us अगर we got oom-समाप्तed).
	 */
	mmap_पढ़ो_unlock(mm);
	अगर (!is_user)
		जाओ out_nosemaphore;
	pagefault_out_of_memory();
	वापस 0;
पूर्ण
EXPORT_SYMBOL(handle_page_fault);

अटल व्योम show_segv_info(काष्ठा uml_pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;
	काष्ठा faultinfo *fi = UPT_FAULTINFO(regs);

	अगर (!unhandled_संकेत(tsk, संक_अंश))
		वापस;

	अगर (!prपूर्णांकk_ratelimit())
		वापस;

	prपूर्णांकk("%s%s[%d]: segfault at %lx ip %px sp %px error %x",
		task_pid_nr(tsk) > 1 ? KERN_INFO : KERN_EMERG,
		tsk->comm, task_pid_nr(tsk), FAULT_ADDRESS(*fi),
		(व्योम *)UPT_IP(regs), (व्योम *)UPT_SP(regs),
		fi->error_code);

	prपूर्णांक_vma_addr(KERN_CONT " in ", UPT_IP(regs));
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

अटल व्योम bad_segv(काष्ठा faultinfo fi, अचिन्हित दीर्घ ip)
अणु
	current->thपढ़ो.arch.faultinfo = fi;
	क्रमce_sig_fault(संक_अंश, SEGV_ACCERR, (व्योम __user *) FAULT_ADDRESS(fi));
पूर्ण

व्योम fatal_sigsegv(व्योम)
अणु
	क्रमce_sigsegv(संक_अंश);
	करो_संकेत(&current->thपढ़ो.regs);
	/*
	 * This is to tell gcc that we're not वापसing - करो_संकेत
	 * can, in general, वापस, but in this हाल, it's not, since
	 * we just got a fatal संक_अंश queued.
	 */
	os_dump_core();
पूर्ण

/**
 * segv_handler() - the संक_अंश handler
 * @sig:	the संकेत number
 * @unused_si:	the संकेत info काष्ठा; unused in this handler
 * @regs:	the ptrace रेजिस्टर inक्रमmation
 *
 * The handler first extracts the faultinfo from the UML ptrace regs काष्ठा.
 * If the userfault did not happen in an UML userspace process, bad_segv is called.
 * Otherwise the संकेत did happen in a cloned userspace process, handle it.
 */
व्योम segv_handler(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs)
अणु
	काष्ठा faultinfo * fi = UPT_FAULTINFO(regs);

	अगर (UPT_IS_USER(regs) && !SEGV_IS_FIXABLE(fi)) अणु
		show_segv_info(regs);
		bad_segv(*fi, UPT_IP(regs));
		वापस;
	पूर्ण
	segv(*fi, UPT_IP(regs), UPT_IS_USER(regs), regs);
पूर्ण

/*
 * We give a *copy* of the faultinfo in the regs to segv.
 * This must be करोne, since nesting SEGVs could overग_लिखो
 * the info in the regs. A poपूर्णांकer to the info then would
 * give us bad data!
 */
अचिन्हित दीर्घ segv(काष्ठा faultinfo fi, अचिन्हित दीर्घ ip, पूर्णांक is_user,
		   काष्ठा uml_pt_regs *regs)
अणु
	लाँघ_बफ *catcher;
	पूर्णांक si_code;
	पूर्णांक err;
	पूर्णांक is_ग_लिखो = FAULT_WRITE(fi);
	अचिन्हित दीर्घ address = FAULT_ADDRESS(fi);

	अगर (!is_user && regs)
		current->thपढ़ो.segv_regs = container_of(regs, काष्ठा pt_regs, regs);

	अगर (!is_user && (address >= start_vm) && (address < end_vm)) अणु
		flush_tlb_kernel_vm();
		जाओ out;
	पूर्ण
	अन्यथा अगर (current->mm == शून्य) अणु
		show_regs(container_of(regs, काष्ठा pt_regs, regs));
		panic("Segfault with no mm");
	पूर्ण
	अन्यथा अगर (!is_user && address > PAGE_SIZE && address < TASK_SIZE) अणु
		show_regs(container_of(regs, काष्ठा pt_regs, regs));
		panic("Kernel tried to access user memory at addr 0x%lx, ip 0x%lx",
		       address, ip);
	पूर्ण

	अगर (SEGV_IS_FIXABLE(&fi))
		err = handle_page_fault(address, ip, is_ग_लिखो, is_user,
					&si_code);
	अन्यथा अणु
		err = -EFAULT;
		/*
		 * A thपढ़ो accessed शून्य, we get a fault, but CR2 is invalid.
		 * This code is used in __करो_copy_from_user() of TT mode.
		 * XXX tt mode is gone, so maybe this isn't needed any more
		 */
		address = 0;
	पूर्ण

	catcher = current->thपढ़ो.fault_catcher;
	अगर (!err)
		जाओ out;
	अन्यथा अगर (catcher != शून्य) अणु
		current->thपढ़ो.fault_addr = (व्योम *) address;
		UML_LONGJMP(catcher, 1);
	पूर्ण
	अन्यथा अगर (current->thपढ़ो.fault_addr != शून्य)
		panic("fault_addr set but no fault catcher");
	अन्यथा अगर (!is_user && arch_fixup(ip, regs))
		जाओ out;

	अगर (!is_user) अणु
		show_regs(container_of(regs, काष्ठा pt_regs, regs));
		panic("Kernel mode fault at addr 0x%lx, ip 0x%lx",
		      address, ip);
	पूर्ण

	show_segv_info(regs);

	अगर (err == -EACCES) अणु
		current->thपढ़ो.arch.faultinfo = fi;
		क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)address);
	पूर्ण अन्यथा अणु
		BUG_ON(err != -EFAULT);
		current->thपढ़ो.arch.faultinfo = fi;
		क्रमce_sig_fault(संक_अंश, si_code, (व्योम __user *) address);
	पूर्ण

out:
	अगर (regs)
		current->thपढ़ो.segv_regs = शून्य;

	वापस 0;
पूर्ण

व्योम relay_संकेत(पूर्णांक sig, काष्ठा siginfo *si, काष्ठा uml_pt_regs *regs)
अणु
	पूर्णांक code, err;
	अगर (!UPT_IS_USER(regs)) अणु
		अगर (sig == SIGBUS)
			prपूर्णांकk(KERN_ERR "Bus error - the host /dev/shm or /tmp "
			       "mount likely just ran out of space\n");
		panic("Kernel mode signal %d", sig);
	पूर्ण

	arch_examine_संकेत(sig, regs);

	/* Is the संकेत layout क्रम the संकेत known?
	 * Signal data must be scrubbed to prevent inक्रमmation leaks.
	 */
	code = si->si_code;
	err = si->si_त्रुटि_सं;
	अगर ((err == 0) && (siginfo_layout(sig, code) == SIL_FAULT)) अणु
		काष्ठा faultinfo *fi = UPT_FAULTINFO(regs);
		current->thपढ़ो.arch.faultinfo = *fi;
		क्रमce_sig_fault(sig, code, (व्योम __user *)FAULT_ADDRESS(*fi));
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "Attempted to relay unknown signal %d (si_code = %d) with errno %d\n",
		       sig, code, err);
		क्रमce_sig(sig);
	पूर्ण
पूर्ण

व्योम bus_handler(पूर्णांक sig, काष्ठा siginfo *si, काष्ठा uml_pt_regs *regs)
अणु
	अगर (current->thपढ़ो.fault_catcher != शून्य)
		UML_LONGJMP(current->thपढ़ो.fault_catcher, 1);
	अन्यथा
		relay_संकेत(sig, si, regs);
पूर्ण

व्योम winch(पूर्णांक sig, काष्ठा siginfo *unused_si, काष्ठा uml_pt_regs *regs)
अणु
	करो_IRQ(WINCH_IRQ, regs);
पूर्ण

व्योम trap_init(व्योम)
अणु
पूर्ण
