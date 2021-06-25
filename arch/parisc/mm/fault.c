<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 *
 * Copyright (C) 1995, 1996, 1997, 1998 by Ralf Baechle
 * Copyright 1999 SuSE GmbH (Philipp Rumpf, prumpf@tux.org)
 * Copyright 1999 Hewlett Packard Co.
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/extable.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/perf_event.h>

#समावेश <यंत्र/traps.h>

/* Various important other fields */
#घोषणा bit22set(x)		(x & 0x00000200)
#घोषणा bits23_25set(x)		(x & 0x000001c0)
#घोषणा isGraphicsFlushRead(x)	((x & 0xfc003fdf) == 0x04001a80)
				/* extended opcode is 0x6a */

#घोषणा BITSSET		0x1c0	/* क्रम identअगरying LDCW */


पूर्णांक show_unhandled_संकेतs = 1;

/*
 * parisc_acctyp(अचिन्हित पूर्णांक inst) --
 *    Given a PA-RISC memory access inकाष्ठाion, determine अगर the
 *    the inकाष्ठाion would perक्रमm a memory पढ़ो or memory ग_लिखो
 *    operation.
 *
 *    This function assumes that the given inकाष्ठाion is a memory access
 *    inकाष्ठाion (i.e. you should really only call it अगर you know that
 *    the inकाष्ठाion has generated some sort of a memory access fault).
 *
 * Returns:
 *   VM_READ  अगर पढ़ो operation
 *   VM_WRITE अगर ग_लिखो operation
 *   VM_EXEC  अगर execute operation
 */
अटल अचिन्हित दीर्घ
parisc_acctyp(अचिन्हित दीर्घ code, अचिन्हित पूर्णांक inst)
अणु
	अगर (code == 6 || code == 16)
	    वापस VM_EXEC;

	चयन (inst & 0xf0000000) अणु
	हाल 0x40000000: /* load */
	हाल 0x50000000: /* new load */
		वापस VM_READ;

	हाल 0x60000000: /* store */
	हाल 0x70000000: /* new store */
		वापस VM_WRITE;

	हाल 0x20000000: /* coproc */
	हाल 0x30000000: /* coproc2 */
		अगर (bit22set(inst))
			वापस VM_WRITE;
		fallthrough;

	हाल 0x0: /* indexed/memory management */
		अगर (bit22set(inst)) अणु
			/*
			 * Check क्रम the 'Graphics Flush Read' inकाष्ठाion.
			 * It resembles an FDC inकाष्ठाion, except क्रम bits
			 * 20 and 21. Any combination other than zero will
			 * utilize the block mover functionality on some
			 * older PA-RISC platक्रमms.  The हाल where a block
			 * move is perक्रमmed from VM to graphics IO space
			 * should be treated as a READ.
			 *
			 * The signअगरicance of bits 20,21 in the FDC
			 * inकाष्ठाion is:
			 *
			 *   00  Flush data cache (normal inकाष्ठाion behavior)
			 *   01  Graphics flush ग_लिखो  (IO space -> VM)
			 *   10  Graphics flush पढ़ो   (VM -> IO space)
			 *   11  Graphics flush पढ़ो/ग_लिखो (VM <-> IO space)
			 */
			अगर (isGraphicsFlushRead(inst))
				वापस VM_READ;
			वापस VM_WRITE;
		पूर्ण अन्यथा अणु
			/*
			 * Check क्रम LDCWX and LDCWS (semaphore inकाष्ठाions).
			 * If bits 23 through 25 are all 1's it is one of
			 * the above two inकाष्ठाions and is a ग_लिखो.
			 *
			 * Note: With the limited bits we are looking at,
			 * this will also catch PROBEW and PROBEWI. However,
			 * these should never get in here because they करोn't
			 * generate exceptions of the type:
			 *   Data TLB miss fault/data page fault
			 *   Data memory protection trap
			 */
			अगर (bits23_25set(inst) == BITSSET)
				वापस VM_WRITE;
		पूर्ण
		वापस VM_READ; /* Default */
	पूर्ण
	वापस VM_READ; /* Default */
पूर्ण

#अघोषित bit22set
#अघोषित bits23_25set
#अघोषित isGraphicsFlushRead
#अघोषित BITSSET


#अगर 0
/* This is the treewalk to find a vma which is the highest that has
 * a start < addr.  We're using find_vma_prev instead right now, but
 * we might want to use this at some poपूर्णांक in the future.  Probably
 * not, but I want it committed to CVS so I करोn't lose it :-)
 */
			जबतक (tree != vm_avl_empty) अणु
				अगर (tree->vm_start > addr) अणु
					tree = tree->vm_avl_left;
				पूर्ण अन्यथा अणु
					prev = tree;
					अगर (prev->vm_next == शून्य)
						अवरोध;
					अगर (prev->vm_next->vm_start > addr)
						अवरोध;
					tree = tree->vm_avl_right;
				पूर्ण
			पूर्ण
#पूर्ण_अगर

पूर्णांक fixup_exception(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा exception_table_entry *fix;

	fix = search_exception_tables(regs->iaoq[0]);
	अगर (fix) अणु
		/*
		 * Fix up get_user() and put_user().
		 * ASM_EXCEPTIONTABLE_ENTRY_EFAULT() sets the least-signअगरicant
		 * bit in the relative address of the fixup routine to indicate
		 * that %r8 should be loaded with -EFAULT to report a userspace
		 * access error.
		 */
		अगर (fix->fixup & 1) अणु
			regs->gr[8] = -EFAULT;

			/* zero target रेजिस्टर क्रम get_user() */
			अगर (parisc_acctyp(0, regs->iir) == VM_READ) अणु
				पूर्णांक treg = regs->iir & 0x1f;
				BUG_ON(treg == 0);
				regs->gr[treg] = 0;
			पूर्ण
		पूर्ण

		regs->iaoq[0] = (अचिन्हित दीर्घ)&fix->fixup + fix->fixup;
		regs->iaoq[0] &= ~3;
		/*
		 * NOTE: In some हालs the faulting inकाष्ठाion
		 * may be in the delay slot of a branch. We
		 * करोn't want to take the branch, so we don't
		 * increment iaoq[1], instead we set it to be
		 * iaoq[0]+4, and clear the B bit in the PSW
		 */
		regs->iaoq[1] = regs->iaoq[0] + 4;
		regs->gr[0] &= ~PSW_B; /* IPSW in gr[0] */

		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * parisc hardware trap list
 *
 * Documented in section 3 "Addressing and Access Control" of the
 * "PA-RISC 1.1 Architecture and Instruction Set Reference Manual"
 * https://parisc.wiki.kernel.org/index.php/File:Pa11_acd.pdf
 *
 * For implementation see handle_पूर्णांकerruption() in traps.c
 */
अटल स्थिर अक्षर * स्थिर trap_description[] = अणु
	[1] "High-priority machine check (HPMC)",
	[2] "Power failure interrupt",
	[3] "Recovery counter trap",
	[5] "Low-priority machine check",
	[6] "Instruction TLB miss fault",
	[7] "Instruction access rights / protection trap",
	[8] "Illegal instruction trap",
	[9] "Break instruction trap",
	[10] "Privileged operation trap",
	[11] "Privileged register trap",
	[12] "Overflow trap",
	[13] "Conditional trap",
	[14] "FP Assist Exception trap",
	[15] "Data TLB miss fault",
	[16] "Non-access ITLB miss fault",
	[17] "Non-access DTLB miss fault",
	[18] "Data memory protection/unaligned access trap",
	[19] "Data memory break trap",
	[20] "TLB dirty bit trap",
	[21] "Page reference trap",
	[22] "Assist emulation trap",
	[25] "Taken branch trap",
	[26] "Data memory access rights trap",
	[27] "Data memory protection ID trap",
	[28] "Unaligned data reference trap",
पूर्ण;

स्थिर अक्षर *trap_name(अचिन्हित दीर्घ code)
अणु
	स्थिर अक्षर *t = शून्य;

	अगर (code < ARRAY_SIZE(trap_description))
		t = trap_description[code];

	वापस t ? t : "Unknown trap";
पूर्ण

/*
 * Prपूर्णांक out info about fatal segfaults, अगर the show_unhandled_संकेतs
 * sysctl is set:
 */
अटल अंतरभूत व्योम
show_संकेत_msg(काष्ठा pt_regs *regs, अचिन्हित दीर्घ code,
		अचिन्हित दीर्घ address, काष्ठा task_काष्ठा *tsk,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (!unhandled_संकेत(tsk, संक_अंश))
		वापस;

	अगर (!prपूर्णांकk_ratelimit())
		वापस;

	pr_warn("\n");
	pr_warn("do_page_fault() command='%s' type=%lu address=0x%08lx",
	    tsk->comm, code, address);
	prपूर्णांक_vma_addr(KERN_CONT " in ", regs->iaoq[0]);

	pr_cont("\ntrap #%lu: %s%c", code, trap_name(code),
		vma ? ',':'\n');

	अगर (vma)
		pr_cont(" vm_start = 0x%08lx, vm_end = 0x%08lx\n",
			vma->vm_start, vma->vm_end);

	show_regs(regs);
पूर्ण

व्योम करो_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ code,
			      अचिन्हित दीर्घ address)
अणु
	काष्ठा vm_area_काष्ठा *vma, *prev_vma;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ acc_type;
	vm_fault_t fault = 0;
	अचिन्हित पूर्णांक flags;

	अगर (faulthandler_disabled())
		जाओ no_context;

	tsk = current;
	mm = tsk->mm;
	अगर (!mm)
		जाओ no_context;

	flags = FAULT_FLAG_DEFAULT;
	अगर (user_mode(regs))
		flags |= FAULT_FLAG_USER;

	acc_type = parisc_acctyp(code, regs->iir);
	अगर (acc_type & VM_WRITE)
		flags |= FAULT_FLAG_WRITE;
	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);
retry:
	mmap_पढ़ो_lock(mm);
	vma = find_vma_prev(mm, address, &prev_vma);
	अगर (!vma || address < vma->vm_start)
		जाओ check_expansion;
/*
 * Ok, we have a good vm_area क्रम this memory access. We still need to
 * check the access permissions.
 */

good_area:

	अगर ((vma->vm_flags & acc_type) != acc_type)
		जाओ bad_area;

	/*
	 * If क्रम any reason at all we couldn't handle the fault, make
	 * sure we निकास gracefully rather than endlessly reकरो the
	 * fault.
	 */

	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs))
		वापस;

	अगर (unlikely(fault & VM_FAULT_ERROR)) अणु
		/*
		 * We hit a shared mapping outside of the file, or some
		 * other thing happened to us that made us unable to
		 * handle the page fault gracefully.
		 */
		अगर (fault & VM_FAULT_OOM)
			जाओ out_of_memory;
		अन्यथा अगर (fault & VM_FAULT_संक_अंश)
			जाओ bad_area;
		अन्यथा अगर (fault & (VM_FAULT_SIGBUS|VM_FAULT_HWPOISON|
				  VM_FAULT_HWPOISON_LARGE))
			जाओ bad_area;
		BUG();
	पूर्ण
	अगर (flags & FAULT_FLAG_ALLOW_RETRY) अणु
		अगर (fault & VM_FAULT_RETRY) अणु
			/*
			 * No need to mmap_पढ़ो_unlock(mm) as we would
			 * have alपढ़ोy released it in __lock_page_or_retry
			 * in mm/filemap.c.
			 */
			flags |= FAULT_FLAG_TRIED;
			जाओ retry;
		पूर्ण
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	वापस;

check_expansion:
	vma = prev_vma;
	अगर (vma && (expand_stack(vma, address) == 0))
		जाओ good_area;

/*
 * Something tried to access memory that isn't in our memory map..
 */
bad_area:
	mmap_पढ़ो_unlock(mm);

	अगर (user_mode(regs)) अणु
		पूर्णांक signo, si_code;

		चयन (code) अणु
		हाल 15:	/* Data TLB miss fault/Data page fault */
			/* send संक_अंश when outside of vma */
			अगर (!vma ||
			    address < vma->vm_start || address >= vma->vm_end) अणु
				signo = संक_अंश;
				si_code = SEGV_MAPERR;
				अवरोध;
			पूर्ण

			/* send संक_अंश क्रम wrong permissions */
			अगर ((vma->vm_flags & acc_type) != acc_type) अणु
				signo = संक_अंश;
				si_code = SEGV_ACCERR;
				अवरोध;
			पूर्ण

			/* probably address is outside of mapped file */
			fallthrough;
		हाल 17:	/* NA data TLB miss / page fault */
		हाल 18:	/* Unaligned access - PCXS only */
			signo = SIGBUS;
			si_code = (code == 18) ? BUS_ADRALN : BUS_ADRERR;
			अवरोध;
		हाल 16:	/* Non-access inकाष्ठाion TLB miss fault */
		हाल 26:	/* PCXL: Data memory access rights trap */
		शेष:
			signo = संक_अंश;
			si_code = (code == 26) ? SEGV_ACCERR : SEGV_MAPERR;
			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_MEMORY_FAILURE
		अगर (fault & (VM_FAULT_HWPOISON|VM_FAULT_HWPOISON_LARGE)) अणु
			अचिन्हित पूर्णांक lsb = 0;
			prपूर्णांकk(KERN_ERR
	"MCE: Killing %s:%d due to hardware memory corruption fault at %08lx\n",
			tsk->comm, tsk->pid, address);
			/*
			 * Either small page or large page may be poisoned.
			 * In other words, VM_FAULT_HWPOISON_LARGE and
			 * VM_FAULT_HWPOISON are mutually exclusive.
			 */
			अगर (fault & VM_FAULT_HWPOISON_LARGE)
				lsb = hstate_index_to_shअगरt(VM_FAULT_GET_HINDEX(fault));
			अन्यथा अगर (fault & VM_FAULT_HWPOISON)
				lsb = PAGE_SHIFT;

			क्रमce_sig_mceerr(BUS_MCEERR_AR, (व्योम __user *) address,
					 lsb);
			वापस;
		पूर्ण
#पूर्ण_अगर
		show_संकेत_msg(regs, code, address, tsk, vma);

		क्रमce_sig_fault(signo, si_code, (व्योम __user *) address);
		वापस;
	पूर्ण

no_context:

	अगर (!user_mode(regs) && fixup_exception(regs)) अणु
		वापस;
	पूर्ण

	parisc_terminate("Bad Address (null pointer deref?)", regs, code, address);

  out_of_memory:
	mmap_पढ़ो_unlock(mm);
	अगर (!user_mode(regs))
		जाओ no_context;
	pagefault_out_of_memory();
पूर्ण
