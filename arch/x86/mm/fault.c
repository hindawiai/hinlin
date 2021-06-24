<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1995  Linus Torvalds
 *  Copyright (C) 2001, 2002 Andi Kleen, SuSE Lअसल.
 *  Copyright (C) 2008-2009, Red Hat Inc., Ingo Molnar
 */
#समावेश <linux/sched.h>		/* test_thपढ़ो_flag(), ...	*/
#समावेश <linux/sched/task_stack.h>	/* task_stack_*(), ...		*/
#समावेश <linux/kdebug.h>		/* oops_begin/end, ...		*/
#समावेश <linux/extable.h>		/* search_exception_tables	*/
#समावेश <linux/memblock.h>		/* max_low_pfn			*/
#समावेश <linux/kfence.h>		/* kfence_handle_page_fault	*/
#समावेश <linux/kprobes.h>		/* NOKPROBE_SYMBOL, ...		*/
#समावेश <linux/mmiotrace.h>		/* kmmio_handler, ...		*/
#समावेश <linux/perf_event.h>		/* perf_sw_event		*/
#समावेश <linux/hugetlb.h>		/* hstate_index_to_shअगरt	*/
#समावेश <linux/prefetch.h>		/* prefetchw			*/
#समावेश <linux/context_tracking.h>	/* exception_enter(), ...	*/
#समावेश <linux/uaccess.h>		/* faulthandler_disabled()	*/
#समावेश <linux/efi.h>			/* efi_crash_gracefully_on_page_fault()*/
#समावेश <linux/mm_types.h>

#समावेश <यंत्र/cpufeature.h>		/* boot_cpu_has, ...		*/
#समावेश <यंत्र/traps.h>			/* करोtraplinkage, ...		*/
#समावेश <यंत्र/fixmap.h>			/* VSYSCALL_ADDR		*/
#समावेश <यंत्र/vsyscall.h>		/* emulate_vsyscall		*/
#समावेश <यंत्र/vm86.h>			/* काष्ठा vm86			*/
#समावेश <यंत्र/mmu_context.h>		/* vma_pkey()			*/
#समावेश <यंत्र/efi.h>			/* efi_crash_gracefully_on_page_fault()*/
#समावेश <यंत्र/desc.h>			/* store_idt(), ...		*/
#समावेश <यंत्र/cpu_entry_area.h>		/* exception stack		*/
#समावेश <यंत्र/pgtable_areas.h>		/* VMALLOC_START, ...		*/
#समावेश <यंत्र/kvm_para.h>		/* kvm_handle_async_pf		*/
#समावेश <यंत्र/vdso.h>			/* fixup_vdso_exception()	*/

#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/trace/exceptions.h>

/*
 * Returns 0 अगर mmiotrace is disabled, or अगर the fault is not
 * handled by mmiotrace:
 */
अटल nokprobe_अंतरभूत पूर्णांक
kmmio_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr)
अणु
	अगर (unlikely(is_kmmio_active()))
		अगर (kmmio_handler(regs, addr) == 1)
			वापस -1;
	वापस 0;
पूर्ण

/*
 * Prefetch quirks:
 *
 * 32-bit mode:
 *
 *   Someबार AMD Athlon/Opteron CPUs report invalid exceptions on prefetch.
 *   Check that here and ignore it.  This is AMD erratum #91.
 *
 * 64-bit mode:
 *
 *   Someबार the CPU reports invalid exceptions on prefetch.
 *   Check that here and ignore it.
 *
 * Opcode checker based on code by Riअक्षरd Brunner.
 */
अटल अंतरभूत पूर्णांक
check_prefetch_opcode(काष्ठा pt_regs *regs, अचिन्हित अक्षर *instr,
		      अचिन्हित अक्षर opcode, पूर्णांक *prefetch)
अणु
	अचिन्हित अक्षर instr_hi = opcode & 0xf0;
	अचिन्हित अक्षर instr_lo = opcode & 0x0f;

	चयन (instr_hi) अणु
	हाल 0x20:
	हाल 0x30:
		/*
		 * Values 0x26,0x2E,0x36,0x3E are valid x86 prefixes.
		 * In X86_64 दीर्घ mode, the CPU will संकेत invalid
		 * opcode अगर some of these prefixes are present so
		 * X86_64 will never get here anyway
		 */
		वापस ((instr_lo & 7) == 0x6);
#अगर_घोषित CONFIG_X86_64
	हाल 0x40:
		/*
		 * In 64-bit mode 0x40..0x4F are valid REX prefixes
		 */
		वापस (!user_mode(regs) || user_64bit_mode(regs));
#पूर्ण_अगर
	हाल 0x60:
		/* 0x64 thru 0x67 are valid prefixes in all modes. */
		वापस (instr_lo & 0xC) == 0x4;
	हाल 0xF0:
		/* 0xF0, 0xF2, 0xF3 are valid prefixes in all modes. */
		वापस !instr_lo || (instr_lo>>1) == 1;
	हाल 0x00:
		/* Prefetch inकाष्ठाion is 0x0F0D or 0x0F18 */
		अगर (get_kernel_nofault(opcode, instr))
			वापस 0;

		*prefetch = (instr_lo == 0xF) &&
			(opcode == 0x0D || opcode == 0x18);
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool is_amd_k8_pre_npt(व्योम)
अणु
	काष्ठा cpuinfo_x86 *c = &boot_cpu_data;

	वापस unlikely(IS_ENABLED(CONFIG_CPU_SUP_AMD) &&
			c->x86_venकरोr == X86_VENDOR_AMD &&
			c->x86 == 0xf && c->x86_model < 0x40);
पूर्ण

अटल पूर्णांक
is_prefetch(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर *max_instr;
	अचिन्हित अक्षर *instr;
	पूर्णांक prefetch = 0;

	/* Erratum #91 affects AMD K8, pre-NPT CPUs */
	अगर (!is_amd_k8_pre_npt())
		वापस 0;

	/*
	 * If it was a exec (inकाष्ठाion fetch) fault on NX page, then
	 * करो not ignore the fault:
	 */
	अगर (error_code & X86_PF_INSTR)
		वापस 0;

	instr = (व्योम *)convert_ip_to_linear(current, regs);
	max_instr = instr + 15;

	/*
	 * This code has historically always bailed out अगर IP poपूर्णांकs to a
	 * not-present page (e.g. due to a race).  No one has ever
	 * complained about this.
	 */
	pagefault_disable();

	जबतक (instr < max_instr) अणु
		अचिन्हित अक्षर opcode;

		अगर (user_mode(regs)) अणु
			अगर (get_user(opcode, instr))
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (get_kernel_nofault(opcode, instr))
				अवरोध;
		पूर्ण

		instr++;

		अगर (!check_prefetch_opcode(regs, instr, opcode, &prefetch))
			अवरोध;
	पूर्ण

	pagefault_enable();
	वापस prefetch;
पूर्ण

DEFINE_SPINLOCK(pgd_lock);
LIST_HEAD(pgd_list);

#अगर_घोषित CONFIG_X86_32
अटल अंतरभूत pmd_t *vदो_स्मृति_sync_one(pgd_t *pgd, अचिन्हित दीर्घ address)
अणु
	अचिन्हित index = pgd_index(address);
	pgd_t *pgd_k;
	p4d_t *p4d, *p4d_k;
	pud_t *pud, *pud_k;
	pmd_t *pmd, *pmd_k;

	pgd += index;
	pgd_k = init_mm.pgd + index;

	अगर (!pgd_present(*pgd_k))
		वापस शून्य;

	/*
	 * set_pgd(pgd, *pgd_k); here would be useless on PAE
	 * and redundant with the set_pmd() on non-PAE. As would
	 * set_p4d/set_pud.
	 */
	p4d = p4d_offset(pgd, address);
	p4d_k = p4d_offset(pgd_k, address);
	अगर (!p4d_present(*p4d_k))
		वापस शून्य;

	pud = pud_offset(p4d, address);
	pud_k = pud_offset(p4d_k, address);
	अगर (!pud_present(*pud_k))
		वापस शून्य;

	pmd = pmd_offset(pud, address);
	pmd_k = pmd_offset(pud_k, address);

	अगर (pmd_present(*pmd) != pmd_present(*pmd_k))
		set_pmd(pmd, *pmd_k);

	अगर (!pmd_present(*pmd_k))
		वापस शून्य;
	अन्यथा
		BUG_ON(pmd_pfn(*pmd) != pmd_pfn(*pmd_k));

	वापस pmd_k;
पूर्ण

/*
 *   Handle a fault on the vदो_स्मृति or module mapping area
 *
 *   This is needed because there is a race condition between the समय
 *   when the vदो_स्मृति mapping code updates the PMD to the poपूर्णांक in समय
 *   where it synchronizes this update with the other page-tables in the
 *   प्रणाली.
 *
 *   In this race winकरोw another thपढ़ो/CPU can map an area on the same
 *   PMD, finds it alपढ़ोy present and करोes not synchronize it with the
 *   rest of the प्रणाली yet. As a result v[mz]alloc might वापस areas
 *   which are not mapped in every page-table in the प्रणाली, causing an
 *   unhandled page-fault when they are accessed.
 */
अटल noअंतरभूत पूर्णांक vदो_स्मृति_fault(अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ pgd_paddr;
	pmd_t *pmd_k;
	pte_t *pte_k;

	/* Make sure we are in vदो_स्मृति area: */
	अगर (!(address >= VMALLOC_START && address < VMALLOC_END))
		वापस -1;

	/*
	 * Synchronize this task's top level page-table
	 * with the 'reference' page table.
	 *
	 * Do _not_ use "current" here. We might be inside
	 * an पूर्णांकerrupt in the middle of a task चयन..
	 */
	pgd_paddr = पढ़ो_cr3_pa();
	pmd_k = vदो_स्मृति_sync_one(__va(pgd_paddr), address);
	अगर (!pmd_k)
		वापस -1;

	अगर (pmd_large(*pmd_k))
		वापस 0;

	pte_k = pte_offset_kernel(pmd_k, address);
	अगर (!pte_present(*pte_k))
		वापस -1;

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(vदो_स्मृति_fault);

व्योम arch_sync_kernel_mappings(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = start & PMD_MASK;
	     addr >= TASK_SIZE_MAX && addr < VMALLOC_END;
	     addr += PMD_SIZE) अणु
		काष्ठा page *page;

		spin_lock(&pgd_lock);
		list_क्रम_each_entry(page, &pgd_list, lru) अणु
			spinlock_t *pgt_lock;

			/* the pgt_lock only क्रम Xen */
			pgt_lock = &pgd_page_get_mm(page)->page_table_lock;

			spin_lock(pgt_lock);
			vदो_स्मृति_sync_one(page_address(page), addr);
			spin_unlock(pgt_lock);
		पूर्ण
		spin_unlock(&pgd_lock);
	पूर्ण
पूर्ण

अटल bool low_pfn(अचिन्हित दीर्घ pfn)
अणु
	वापस pfn < max_low_pfn;
पूर्ण

अटल व्योम dump_pagetable(अचिन्हित दीर्घ address)
अणु
	pgd_t *base = __va(पढ़ो_cr3_pa());
	pgd_t *pgd = &base[pgd_index(address)];
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

#अगर_घोषित CONFIG_X86_PAE
	pr_info("*pdpt = %016Lx ", pgd_val(*pgd));
	अगर (!low_pfn(pgd_val(*pgd) >> PAGE_SHIFT) || !pgd_present(*pgd))
		जाओ out;
#घोषणा pr_pde pr_cont
#अन्यथा
#घोषणा pr_pde pr_info
#पूर्ण_अगर
	p4d = p4d_offset(pgd, address);
	pud = pud_offset(p4d, address);
	pmd = pmd_offset(pud, address);
	pr_pde("*pde = %0*Lx ", माप(*pmd) * 2, (u64)pmd_val(*pmd));
#अघोषित pr_pde

	/*
	 * We must not directly access the pte in the highpte
	 * हाल अगर the page table is located in highmem.
	 * And let's rather not kmap-atomic the pte, just in हाल
	 * it's allocated alपढ़ोy:
	 */
	अगर (!low_pfn(pmd_pfn(*pmd)) || !pmd_present(*pmd) || pmd_large(*pmd))
		जाओ out;

	pte = pte_offset_kernel(pmd, address);
	pr_cont("*pte = %0*Lx ", माप(*pte) * 2, (u64)pte_val(*pte));
out:
	pr_cont("\n");
पूर्ण

#अन्यथा /* CONFIG_X86_64: */

#अगर_घोषित CONFIG_CPU_SUP_AMD
अटल स्थिर अक्षर errata93_warning[] =
KERN_ERR 
"******* Your BIOS seems to not contain a fix for K8 errata #93\n"
"******* Working around it, but it may cause SEGVs or burn power.\n"
"******* Please consider a BIOS update.\n"
"******* Disabling USB legacy in the BIOS may also help.\n";
#पूर्ण_अगर

अटल पूर्णांक bad_address(व्योम *p)
अणु
	अचिन्हित दीर्घ dummy;

	वापस get_kernel_nofault(dummy, (अचिन्हित दीर्घ *)p);
पूर्ण

अटल व्योम dump_pagetable(अचिन्हित दीर्घ address)
अणु
	pgd_t *base = __va(पढ़ो_cr3_pa());
	pgd_t *pgd = base + pgd_index(address);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	अगर (bad_address(pgd))
		जाओ bad;

	pr_info("PGD %lx ", pgd_val(*pgd));

	अगर (!pgd_present(*pgd))
		जाओ out;

	p4d = p4d_offset(pgd, address);
	अगर (bad_address(p4d))
		जाओ bad;

	pr_cont("P4D %lx ", p4d_val(*p4d));
	अगर (!p4d_present(*p4d) || p4d_large(*p4d))
		जाओ out;

	pud = pud_offset(p4d, address);
	अगर (bad_address(pud))
		जाओ bad;

	pr_cont("PUD %lx ", pud_val(*pud));
	अगर (!pud_present(*pud) || pud_large(*pud))
		जाओ out;

	pmd = pmd_offset(pud, address);
	अगर (bad_address(pmd))
		जाओ bad;

	pr_cont("PMD %lx ", pmd_val(*pmd));
	अगर (!pmd_present(*pmd) || pmd_large(*pmd))
		जाओ out;

	pte = pte_offset_kernel(pmd, address);
	अगर (bad_address(pte))
		जाओ bad;

	pr_cont("PTE %lx", pte_val(*pte));
out:
	pr_cont("\n");
	वापस;
bad:
	pr_info("BAD\n");
पूर्ण

#पूर्ण_अगर /* CONFIG_X86_64 */

/*
 * Workaround क्रम K8 erratum #93 & buggy BIOS.
 *
 * BIOS SMM functions are required to use a specअगरic workaround
 * to aव्योम corruption of the 64bit RIP रेजिस्टर on C stepping K8.
 *
 * A lot of BIOS that didn't get tested properly miss this.
 *
 * The OS sees this as a page fault with the upper 32bits of RIP cleared.
 * Try to work around it here.
 *
 * Note we only handle faults in kernel here.
 * Does nothing on 32-bit.
 */
अटल पूर्णांक is_errata93(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
#अगर defined(CONFIG_X86_64) && defined(CONFIG_CPU_SUP_AMD)
	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD
	    || boot_cpu_data.x86 != 0xf)
		वापस 0;

	अगर (user_mode(regs))
		वापस 0;

	अगर (address != regs->ip)
		वापस 0;

	अगर ((address >> 32) != 0)
		वापस 0;

	address |= 0xffffffffUL << 32;
	अगर ((address >= (u64)_stext && address <= (u64)_etext) ||
	    (address >= MODULES_VADDR && address <= MODULES_END)) अणु
		prपूर्णांकk_once(errata93_warning);
		regs->ip = address;
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Work around K8 erratum #100 K8 in compat mode occasionally jumps
 * to illegal addresses >4GB.
 *
 * We catch this in the page fault handler because these addresses
 * are not reachable. Just detect this हाल and वापस.  Any code
 * segment in LDT is compatibility mode.
 */
अटल पूर्णांक is_errata100(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address)
अणु
#अगर_घोषित CONFIG_X86_64
	अगर ((regs->cs == __USER32_CS || (regs->cs & (1<<2))) && (address >> 32))
		वापस 1;
#पूर्ण_अगर
	वापस 0;
पूर्ण

/* Pentium F0 0F C7 C8 bug workaround: */
अटल पूर्णांक is_f00f_bug(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		       अचिन्हित दीर्घ address)
अणु
#अगर_घोषित CONFIG_X86_F00F_BUG
	अगर (boot_cpu_has_bug(X86_BUG_F00F) && !(error_code & X86_PF_USER) &&
	    idt_is_f00f_address(address)) अणु
		handle_invalid_op(regs);
		वापस 1;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम show_ldttss(स्थिर काष्ठा desc_ptr *gdt, स्थिर अक्षर *name, u16 index)
अणु
	u32 offset = (index >> 3) * माप(काष्ठा desc_काष्ठा);
	अचिन्हित दीर्घ addr;
	काष्ठा ldttss_desc desc;

	अगर (index == 0) अणु
		pr_alert("%s: NULL\n", name);
		वापस;
	पूर्ण

	अगर (offset + माप(काष्ठा ldttss_desc) >= gdt->size) अणु
		pr_alert("%s: 0x%hx -- out of bounds\n", name, index);
		वापस;
	पूर्ण

	अगर (copy_from_kernel_nofault(&desc, (व्योम *)(gdt->address + offset),
			      माप(काष्ठा ldttss_desc))) अणु
		pr_alert("%s: 0x%hx -- GDT entry is not readable\n",
			 name, index);
		वापस;
	पूर्ण

	addr = desc.base0 | (desc.base1 << 16) | ((अचिन्हित दीर्घ)desc.base2 << 24);
#अगर_घोषित CONFIG_X86_64
	addr |= ((u64)desc.base3 << 32);
#पूर्ण_अगर
	pr_alert("%s: 0x%hx -- base=0x%lx limit=0x%x\n",
		 name, index, addr, (desc.limit0 | (desc.limit1 << 16)));
पूर्ण

अटल व्योम
show_fault_oops(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ address)
अणु
	अगर (!oops_may_prपूर्णांक())
		वापस;

	अगर (error_code & X86_PF_INSTR) अणु
		अचिन्हित पूर्णांक level;
		pgd_t *pgd;
		pte_t *pte;

		pgd = __va(पढ़ो_cr3_pa());
		pgd += pgd_index(address);

		pte = lookup_address_in_pgd(pgd, address, &level);

		अगर (pte && pte_present(*pte) && !pte_exec(*pte))
			pr_crit("kernel tried to execute NX-protected page - exploit attempt? (uid: %d)\n",
				from_kuid(&init_user_ns, current_uid()));
		अगर (pte && pte_present(*pte) && pte_exec(*pte) &&
				(pgd_flags(*pgd) & _PAGE_USER) &&
				(__पढ़ो_cr4() & X86_CR4_SMEP))
			pr_crit("unable to execute userspace code (SMEP?) (uid: %d)\n",
				from_kuid(&init_user_ns, current_uid()));
	पूर्ण

	अगर (address < PAGE_SIZE && !user_mode(regs))
		pr_alert("BUG: kernel NULL pointer dereference, address: %px\n",
			(व्योम *)address);
	अन्यथा
		pr_alert("BUG: unable to handle page fault for address: %px\n",
			(व्योम *)address);

	pr_alert("#PF: %s %s in %s mode\n",
		 (error_code & X86_PF_USER)  ? "user" : "supervisor",
		 (error_code & X86_PF_INSTR) ? "instruction fetch" :
		 (error_code & X86_PF_WRITE) ? "write access" :
					       "read access",
			     user_mode(regs) ? "user" : "kernel");
	pr_alert("#PF: error_code(0x%04lx) - %s\n", error_code,
		 !(error_code & X86_PF_PROT) ? "not-present page" :
		 (error_code & X86_PF_RSVD)  ? "reserved bit violation" :
		 (error_code & X86_PF_PK)    ? "protection keys violation" :
					       "permissions violation");

	अगर (!(error_code & X86_PF_USER) && user_mode(regs)) अणु
		काष्ठा desc_ptr idt, gdt;
		u16 ldtr, tr;

		/*
		 * This can happen क्रम quite a few reasons.  The more obvious
		 * ones are faults accessing the GDT, or LDT.  Perhaps
		 * surprisingly, अगर the CPU tries to deliver a benign or
		 * contributory exception from user code and माला_लो a page fault
		 * during delivery, the page fault can be delivered as though
		 * it originated directly from user code.  This could happen
		 * due to wrong permissions on the IDT, GDT, LDT, TSS, or
		 * kernel or IST stack.
		 */
		store_idt(&idt);

		/* Usable even on Xen PV -- it's just slow. */
		native_store_gdt(&gdt);

		pr_alert("IDT: 0x%lx (limit=0x%hx) GDT: 0x%lx (limit=0x%hx)\n",
			 idt.address, idt.size, gdt.address, gdt.size);

		store_ldt(ldtr);
		show_ldttss(&gdt, "LDTR", ldtr);

		store_tr(tr);
		show_ldttss(&gdt, "TR", tr);
	पूर्ण

	dump_pagetable(address);
पूर्ण

अटल noअंतरभूत व्योम
pgtable_bad(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
	    अचिन्हित दीर्घ address)
अणु
	काष्ठा task_काष्ठा *tsk;
	अचिन्हित दीर्घ flags;
	पूर्णांक sig;

	flags = oops_begin();
	tsk = current;
	sig = SIGKILL;

	prपूर्णांकk(KERN_ALERT "%s: Corrupted page table at address %lx\n",
	       tsk->comm, address);
	dump_pagetable(address);

	अगर (__die("Bad pagetable", regs, error_code))
		sig = 0;

	oops_end(flags, regs, sig);
पूर्ण

अटल व्योम sanitize_error_code(अचिन्हित दीर्घ address,
				अचिन्हित दीर्घ *error_code)
अणु
	/*
	 * To aव्योम leaking inक्रमmation about the kernel page
	 * table layout, pretend that user-mode accesses to
	 * kernel addresses are always protection faults.
	 *
	 * NB: This means that failed vsyscalls with vsyscall=none
	 * will have the PROT bit.  This करोesn't leak any
	 * inक्रमmation and करोes not appear to cause any problems.
	 */
	अगर (address >= TASK_SIZE_MAX)
		*error_code |= X86_PF_PROT;
पूर्ण

अटल व्योम set_संकेत_archinfo(अचिन्हित दीर्घ address,
				अचिन्हित दीर्घ error_code)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	tsk->thपढ़ो.trap_nr = X86_TRAP_PF;
	tsk->thपढ़ो.error_code = error_code | X86_PF_USER;
	tsk->thपढ़ो.cr2 = address;
पूर्ण

अटल noअंतरभूत व्योम
page_fault_oops(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक sig;

	अगर (user_mode(regs)) अणु
		/*
		 * Implicit kernel access from user mode?  Skip the stack
		 * overflow and EFI special हालs.
		 */
		जाओ oops;
	पूर्ण

#अगर_घोषित CONFIG_VMAP_STACK
	/*
	 * Stack overflow?  During boot, we can fault near the initial
	 * stack in the direct map, but that's not an overflow -- check
	 * that we're in vदो_स्मृति space to aव्योम this.
	 */
	अगर (is_vदो_स्मृति_addr((व्योम *)address) &&
	    (((अचिन्हित दीर्घ)current->stack - 1 - address < PAGE_SIZE) ||
	     address - ((अचिन्हित दीर्घ)current->stack + THREAD_SIZE) < PAGE_SIZE)) अणु
		अचिन्हित दीर्घ stack = __this_cpu_ist_top_va(DF) - माप(व्योम *);
		/*
		 * We're likely to be running with very little stack space
		 * left.  It's plausible that we'd hit this condition but
		 * द्विगुन-fault even beक्रमe we get this far, in which हाल
		 * we're fine: the द्विगुन-fault handler will deal with it.
		 *
		 * We करोn't want to make it all the way पूर्णांकo the oops code
		 * and then द्विगुन-fault, though, because we're likely to
		 * अवरोध the console driver and lose most of the stack dump.
		 */
		यंत्र अस्थिर ("movq %[stack], %%rsp\n\t"
			      "call handle_stack_overflow\n\t"
			      "1: jmp 1b"
			      : ASM_CALL_CONSTRAINT
			      : "D" ("kernel stack overflow (page fault)"),
				"S" (regs), "d" (address),
				[stack] "rm" (stack));
		unreachable();
	पूर्ण
#पूर्ण_अगर

	/*
	 * Buggy firmware could access regions which might page fault.  If
	 * this happens, EFI has a special OOPS path that will try to
	 * aव्योम hanging the प्रणाली.
	 */
	अगर (IS_ENABLED(CONFIG_EFI))
		efi_crash_gracefully_on_page_fault(address);

	/* Only not-present faults should be handled by KFENCE. */
	अगर (!(error_code & X86_PF_PROT) &&
	    kfence_handle_page_fault(address, error_code & X86_PF_WRITE, regs))
		वापस;

oops:
	/*
	 * Oops. The kernel tried to access some bad page. We'll have to
	 * terminate things with extreme prejudice:
	 */
	flags = oops_begin();

	show_fault_oops(regs, error_code, address);

	अगर (task_stack_end_corrupted(current))
		prपूर्णांकk(KERN_EMERG "Thread overran stack, or stack corrupted\n");

	sig = SIGKILL;
	अगर (__die("Oops", regs, error_code))
		sig = 0;

	/* Executive summary in हाल the body of the oops scrolled away */
	prपूर्णांकk(KERN_DEFAULT "CR2: %016lx\n", address);

	oops_end(flags, regs, sig);
पूर्ण

अटल noअंतरभूत व्योम
kernelmode_fixup_or_oops(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
			 अचिन्हित दीर्घ address, पूर्णांक संकेत, पूर्णांक si_code)
अणु
	WARN_ON_ONCE(user_mode(regs));

	/* Are we prepared to handle this kernel fault? */
	अगर (fixup_exception(regs, X86_TRAP_PF, error_code, address)) अणु
		/*
		 * Any पूर्णांकerrupt that takes a fault माला_लो the fixup. This makes
		 * the below recursive fault logic only apply to a faults from
		 * task context.
		 */
		अगर (in_पूर्णांकerrupt())
			वापस;

		/*
		 * Per the above we're !in_पूर्णांकerrupt(), aka. task context.
		 *
		 * In this हाल we need to make sure we're not recursively
		 * faulting through the emulate_vsyscall() logic.
		 */
		अगर (current->thपढ़ो.sig_on_uaccess_err && संकेत) अणु
			sanitize_error_code(address, &error_code);

			set_संकेत_archinfo(address, error_code);

			/* XXX: hwpoison faults will set the wrong code. */
			क्रमce_sig_fault(संकेत, si_code, (व्योम __user *)address);
		पूर्ण

		/*
		 * Barring that, we can करो the fixup and be happy.
		 */
		वापस;
	पूर्ण

	/*
	 * AMD erratum #91 manअगरests as a spurious page fault on a PREFETCH
	 * inकाष्ठाion.
	 */
	अगर (is_prefetch(regs, error_code, address))
		वापस;

	page_fault_oops(regs, error_code, address);
पूर्ण

/*
 * Prपूर्णांक out info about fatal segfaults, अगर the show_unhandled_संकेतs
 * sysctl is set:
 */
अटल अंतरभूत व्योम
show_संकेत_msg(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		अचिन्हित दीर्घ address, काष्ठा task_काष्ठा *tsk)
अणु
	स्थिर अक्षर *loglvl = task_pid_nr(tsk) > 1 ? KERN_INFO : KERN_EMERG;

	अगर (!unhandled_संकेत(tsk, संक_अंश))
		वापस;

	अगर (!prपूर्णांकk_ratelimit())
		वापस;

	prपूर्णांकk("%s%s[%d]: segfault at %lx ip %px sp %px error %lx",
		loglvl, tsk->comm, task_pid_nr(tsk), address,
		(व्योम *)regs->ip, (व्योम *)regs->sp, error_code);

	prपूर्णांक_vma_addr(KERN_CONT " in ", regs->ip);

	prपूर्णांकk(KERN_CONT "\n");

	show_opcodes(regs, loglvl);
पूर्ण

/*
 * The (legacy) vsyscall page is the दीर्घ page in the kernel portion
 * of the address space that has user-accessible permissions.
 */
अटल bool is_vsyscall_vaddr(अचिन्हित दीर्घ vaddr)
अणु
	वापस unlikely((vaddr & PAGE_MASK) == VSYSCALL_ADDR);
पूर्ण

अटल व्योम
__bad_area_nosemaphore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		       अचिन्हित दीर्घ address, u32 pkey, पूर्णांक si_code)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	अगर (!user_mode(regs)) अणु
		kernelmode_fixup_or_oops(regs, error_code, address, pkey, si_code);
		वापस;
	पूर्ण

	अगर (!(error_code & X86_PF_USER)) अणु
		/* Implicit user access to kernel memory -- just oops */
		page_fault_oops(regs, error_code, address);
		वापस;
	पूर्ण

	/*
	 * User mode accesses just cause a संक_अंश.
	 * It's possible to have पूर्णांकerrupts off here:
	 */
	local_irq_enable();

	/*
	 * Valid to करो another page fault here because this one came
	 * from user space:
	 */
	अगर (is_prefetch(regs, error_code, address))
		वापस;

	अगर (is_errata100(regs, address))
		वापस;

	sanitize_error_code(address, &error_code);

	अगर (fixup_vdso_exception(regs, X86_TRAP_PF, error_code, address))
		वापस;

	अगर (likely(show_unhandled_संकेतs))
		show_संकेत_msg(regs, error_code, address, tsk);

	set_संकेत_archinfo(address, error_code);

	अगर (si_code == SEGV_PKUERR)
		क्रमce_sig_pkuerr((व्योम __user *)address, pkey);
	अन्यथा
		क्रमce_sig_fault(संक_अंश, si_code, (व्योम __user *)address);

	local_irq_disable();
पूर्ण

अटल noअंतरभूत व्योम
bad_area_nosemaphore(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		     अचिन्हित दीर्घ address)
अणु
	__bad_area_nosemaphore(regs, error_code, address, 0, SEGV_MAPERR);
पूर्ण

अटल व्योम
__bad_area(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
	   अचिन्हित दीर्घ address, u32 pkey, पूर्णांक si_code)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	/*
	 * Something tried to access memory that isn't in our memory map..
	 * Fix it, but check अगर it's kernel or user first..
	 */
	mmap_पढ़ो_unlock(mm);

	__bad_area_nosemaphore(regs, error_code, address, pkey, si_code);
पूर्ण

अटल noअंतरभूत व्योम
bad_area(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ address)
अणु
	__bad_area(regs, error_code, address, 0, SEGV_MAPERR);
पूर्ण

अटल अंतरभूत bool bad_area_access_from_pkeys(अचिन्हित दीर्घ error_code,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	/* This code is always called on the current mm */
	bool क्रमeign = false;

	अगर (!boot_cpu_has(X86_FEATURE_OSPKE))
		वापस false;
	अगर (error_code & X86_PF_PK)
		वापस true;
	/* this checks permission keys on the VMA: */
	अगर (!arch_vma_access_permitted(vma, (error_code & X86_PF_WRITE),
				       (error_code & X86_PF_INSTR), क्रमeign))
		वापस true;
	वापस false;
पूर्ण

अटल noअंतरभूत व्योम
bad_area_access_error(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
		      अचिन्हित दीर्घ address, काष्ठा vm_area_काष्ठा *vma)
अणु
	/*
	 * This OSPKE check is not strictly necessary at runसमय.
	 * But, करोing it this way allows compiler optimizations
	 * अगर pkeys are compiled out.
	 */
	अगर (bad_area_access_from_pkeys(error_code, vma)) अणु
		/*
		 * A protection key fault means that the PKRU value did not allow
		 * access to some PTE.  Userspace can figure out what PKRU was
		 * from the XSAVE state.  This function captures the pkey from
		 * the vma and passes it to userspace so userspace can discover
		 * which protection key was set on the PTE.
		 *
		 * If we get here, we know that the hardware संकेतed a X86_PF_PK
		 * fault and that there was a VMA once we got in the fault
		 * handler.  It करोes *not* guarantee that the VMA we find here
		 * was the one that we faulted on.
		 *
		 * 1. T1   : mprotect_key(foo, PAGE_SIZE, pkey=4);
		 * 2. T1   : set PKRU to deny access to pkey=4, touches page
		 * 3. T1   : faults...
		 * 4.    T2: mprotect_key(foo, PAGE_SIZE, pkey=5);
		 * 5. T1   : enters fault handler, takes mmap_lock, etc...
		 * 6. T1   : reaches here, sees vma_pkey(vma)=5, when we really
		 *	     faulted on a pte with its pkey=4.
		 */
		u32 pkey = vma_pkey(vma);

		__bad_area(regs, error_code, address, pkey, SEGV_PKUERR);
	पूर्ण अन्यथा अणु
		__bad_area(regs, error_code, address, 0, SEGV_ACCERR);
	पूर्ण
पूर्ण

अटल व्योम
करो_sigbus(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ address,
	  vm_fault_t fault)
अणु
	/* Kernel mode? Handle exceptions or die: */
	अगर (!user_mode(regs)) अणु
		kernelmode_fixup_or_oops(regs, error_code, address, SIGBUS, BUS_ADRERR);
		वापस;
	पूर्ण

	/* User-space => ok to करो another page fault: */
	अगर (is_prefetch(regs, error_code, address))
		वापस;

	sanitize_error_code(address, &error_code);

	अगर (fixup_vdso_exception(regs, X86_TRAP_PF, error_code, address))
		वापस;

	set_संकेत_archinfo(address, error_code);

#अगर_घोषित CONFIG_MEMORY_FAILURE
	अगर (fault & (VM_FAULT_HWPOISON|VM_FAULT_HWPOISON_LARGE)) अणु
		काष्ठा task_काष्ठा *tsk = current;
		अचिन्हित lsb = 0;

		pr_err(
	"MCE: Killing %s:%d due to hardware memory corruption fault at %lx\n",
			tsk->comm, tsk->pid, address);
		अगर (fault & VM_FAULT_HWPOISON_LARGE)
			lsb = hstate_index_to_shअगरt(VM_FAULT_GET_HINDEX(fault));
		अगर (fault & VM_FAULT_HWPOISON)
			lsb = PAGE_SHIFT;
		क्रमce_sig_mceerr(BUS_MCEERR_AR, (व्योम __user *)address, lsb);
		वापस;
	पूर्ण
#पूर्ण_अगर
	क्रमce_sig_fault(SIGBUS, BUS_ADRERR, (व्योम __user *)address);
पूर्ण

अटल पूर्णांक spurious_kernel_fault_check(अचिन्हित दीर्घ error_code, pte_t *pte)
अणु
	अगर ((error_code & X86_PF_WRITE) && !pte_ग_लिखो(*pte))
		वापस 0;

	अगर ((error_code & X86_PF_INSTR) && !pte_exec(*pte))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Handle a spurious fault caused by a stale TLB entry.
 *
 * This allows us to lazily refresh the TLB when increasing the
 * permissions of a kernel page (RO -> RW or NX -> X).  Doing it
 * eagerly is very expensive since that implies करोing a full
 * cross-processor TLB flush, even अगर no stale TLB entries exist
 * on other processors.
 *
 * Spurious faults may only occur अगर the TLB contains an entry with
 * fewer permission than the page table entry.  Non-present (P = 0)
 * and reserved bit (R = 1) faults are never spurious.
 *
 * There are no security implications to leaving a stale TLB when
 * increasing the permissions on a page.
 *
 * Returns non-zero अगर a spurious fault was handled, zero otherwise.
 *
 * See Intel Developer's Manual Vol 3 Section 4.10.4.3, bullet 3
 * (Optional Invalidation).
 */
अटल noअंतरभूत पूर्णांक
spurious_kernel_fault(अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	पूर्णांक ret;

	/*
	 * Only ग_लिखोs to RO or inकाष्ठाion fetches from NX may cause
	 * spurious faults.
	 *
	 * These could be from user or supervisor accesses but the TLB
	 * is only lazily flushed after a kernel mapping protection
	 * change, so user accesses are not expected to cause spurious
	 * faults.
	 */
	अगर (error_code != (X86_PF_WRITE | X86_PF_PROT) &&
	    error_code != (X86_PF_INSTR | X86_PF_PROT))
		वापस 0;

	pgd = init_mm.pgd + pgd_index(address);
	अगर (!pgd_present(*pgd))
		वापस 0;

	p4d = p4d_offset(pgd, address);
	अगर (!p4d_present(*p4d))
		वापस 0;

	अगर (p4d_large(*p4d))
		वापस spurious_kernel_fault_check(error_code, (pte_t *) p4d);

	pud = pud_offset(p4d, address);
	अगर (!pud_present(*pud))
		वापस 0;

	अगर (pud_large(*pud))
		वापस spurious_kernel_fault_check(error_code, (pte_t *) pud);

	pmd = pmd_offset(pud, address);
	अगर (!pmd_present(*pmd))
		वापस 0;

	अगर (pmd_large(*pmd))
		वापस spurious_kernel_fault_check(error_code, (pte_t *) pmd);

	pte = pte_offset_kernel(pmd, address);
	अगर (!pte_present(*pte))
		वापस 0;

	ret = spurious_kernel_fault_check(error_code, pte);
	अगर (!ret)
		वापस 0;

	/*
	 * Make sure we have permissions in PMD.
	 * If not, then there's a bug in the page tables:
	 */
	ret = spurious_kernel_fault_check(error_code, (pte_t *) pmd);
	WARN_ONCE(!ret, "PMD has incorrect permission bits\n");

	वापस ret;
पूर्ण
NOKPROBE_SYMBOL(spurious_kernel_fault);

पूर्णांक show_unhandled_संकेतs = 1;

अटल अंतरभूत पूर्णांक
access_error(अचिन्हित दीर्घ error_code, काष्ठा vm_area_काष्ठा *vma)
अणु
	/* This is only called क्रम the current mm, so: */
	bool क्रमeign = false;

	/*
	 * Read or ग_लिखो was blocked by protection keys.  This is
	 * always an unconditional error and can never result in
	 * a follow-up action to resolve the fault, like a COW.
	 */
	अगर (error_code & X86_PF_PK)
		वापस 1;

	/*
	 * SGX hardware blocked the access.  This usually happens
	 * when the enclave memory contents have been destroyed, like
	 * after a suspend/resume cycle. In any हाल, the kernel can't
	 * fix the cause of the fault.  Handle the fault as an access
	 * error even in हालs where no actual access violation
	 * occurred.  This allows userspace to rebuild the enclave in
	 * response to the संकेत.
	 */
	अगर (unlikely(error_code & X86_PF_SGX))
		वापस 1;

	/*
	 * Make sure to check the VMA so that we करो not perक्रमm
	 * faults just to hit a X86_PF_PK as soon as we fill in a
	 * page.
	 */
	अगर (!arch_vma_access_permitted(vma, (error_code & X86_PF_WRITE),
				       (error_code & X86_PF_INSTR), क्रमeign))
		वापस 1;

	अगर (error_code & X86_PF_WRITE) अणु
		/* ग_लिखो, present and ग_लिखो, not present: */
		अगर (unlikely(!(vma->vm_flags & VM_WRITE)))
			वापस 1;
		वापस 0;
	पूर्ण

	/* पढ़ो, present: */
	अगर (unlikely(error_code & X86_PF_PROT))
		वापस 1;

	/* पढ़ो, not present: */
	अगर (unlikely(!vma_is_accessible(vma)))
		वापस 1;

	वापस 0;
पूर्ण

bool fault_in_kernel_space(अचिन्हित दीर्घ address)
अणु
	/*
	 * On 64-bit प्रणालीs, the vsyscall page is at an address above
	 * TASK_SIZE_MAX, but is not considered part of the kernel
	 * address space.
	 */
	अगर (IS_ENABLED(CONFIG_X86_64) && is_vsyscall_vaddr(address))
		वापस false;

	वापस address >= TASK_SIZE_MAX;
पूर्ण

/*
 * Called क्रम all faults where 'address' is part of the kernel address
 * space.  Might get called क्रम faults that originate from *code* that
 * ran in userspace or the kernel.
 */
अटल व्योम
करो_kern_addr_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ hw_error_code,
		   अचिन्हित दीर्घ address)
अणु
	/*
	 * Protection keys exceptions only happen on user pages.  We
	 * have no user pages in the kernel portion of the address
	 * space, so करो not expect them here.
	 */
	WARN_ON_ONCE(hw_error_code & X86_PF_PK);

#अगर_घोषित CONFIG_X86_32
	/*
	 * We can fault-in kernel-space भव memory on-demand. The
	 * 'reference' page table is init_mm.pgd.
	 *
	 * NOTE! We MUST NOT take any locks क्रम this हाल. We may
	 * be in an पूर्णांकerrupt or a critical region, and should
	 * only copy the inक्रमmation from the master page table,
	 * nothing more.
	 *
	 * Beक्रमe करोing this on-demand faulting, ensure that the
	 * fault is not any of the following:
	 * 1. A fault on a PTE with a reserved bit set.
	 * 2. A fault caused by a user-mode access.  (Do not demand-
	 *    fault kernel memory due to user-mode accesses).
	 * 3. A fault caused by a page-level protection violation.
	 *    (A demand fault would be on a non-present page which
	 *     would have X86_PF_PROT==0).
	 *
	 * This is only needed to बंद a race condition on x86-32 in
	 * the vदो_स्मृति mapping/unmapping code. See the comment above
	 * vदो_स्मृति_fault() क्रम details. On x86-64 the race करोes not
	 * exist as the vदो_स्मृति mappings करोn't need to be synchronized
	 * there.
	 */
	अगर (!(hw_error_code & (X86_PF_RSVD | X86_PF_USER | X86_PF_PROT))) अणु
		अगर (vदो_स्मृति_fault(address) >= 0)
			वापस;
	पूर्ण
#पूर्ण_अगर

	अगर (is_f00f_bug(regs, hw_error_code, address))
		वापस;

	/* Was the fault spurious, caused by lazy TLB invalidation? */
	अगर (spurious_kernel_fault(hw_error_code, address))
		वापस;

	/* kprobes करोn't want to hook the spurious faults: */
	अगर (kprobe_page_fault(regs, X86_TRAP_PF))
		वापस;

	/*
	 * Note, despite being a "bad area", there are quite a few
	 * acceptable reasons to get here, such as erratum fixups
	 * and handling kernel code that can fault, like get_user().
	 *
	 * Don't take the mm semaphore here. If we fixup a prefetch
	 * fault we could otherwise deadlock:
	 */
	bad_area_nosemaphore(regs, hw_error_code, address);
पूर्ण
NOKPROBE_SYMBOL(करो_kern_addr_fault);

/*
 * Handle faults in the user portion of the address space.  Nothing in here
 * should check X86_PF_USER without a specअगरic justअगरication: क्रम almost
 * all purposes, we should treat a normal kernel access to user memory
 * (e.g. get_user(), put_user(), etc.) the same as the WRUSS inकाष्ठाion.
 * The one exception is AC flag handling, which is, per the x86
 * architecture, special क्रम WRUSS.
 */
अटल अंतरभूत
व्योम करो_user_addr_fault(काष्ठा pt_regs *regs,
			अचिन्हित दीर्घ error_code,
			अचिन्हित दीर्घ address)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा task_काष्ठा *tsk;
	काष्ठा mm_काष्ठा *mm;
	vm_fault_t fault;
	अचिन्हित पूर्णांक flags = FAULT_FLAG_DEFAULT;

	tsk = current;
	mm = tsk->mm;

	अगर (unlikely((error_code & (X86_PF_USER | X86_PF_INSTR)) == X86_PF_INSTR)) अणु
		/*
		 * Whoops, this is kernel mode code trying to execute from
		 * user memory.  Unless this is AMD erratum #93, which
		 * corrupts RIP such that it looks like a user address,
		 * this is unrecoverable.  Don't even try to look up the
		 * VMA or look क्रम extable entries.
		 */
		अगर (is_errata93(regs, address))
			वापस;

		page_fault_oops(regs, error_code, address);
		वापस;
	पूर्ण

	/* kprobes करोn't want to hook the spurious faults: */
	अगर (unlikely(kprobe_page_fault(regs, X86_TRAP_PF)))
		वापस;

	/*
	 * Reserved bits are never expected to be set on
	 * entries in the user portion of the page tables.
	 */
	अगर (unlikely(error_code & X86_PF_RSVD))
		pgtable_bad(regs, error_code, address);

	/*
	 * If SMAP is on, check क्रम invalid kernel (supervisor) access to user
	 * pages in the user address space.  The odd हाल here is WRUSS,
	 * which, according to the preliminary करोcumentation, करोes not respect
	 * SMAP and will have the USER bit set so, in all हालs, SMAP
	 * enक्रमcement appears to be consistent with the USER bit.
	 */
	अगर (unlikely(cpu_feature_enabled(X86_FEATURE_SMAP) &&
		     !(error_code & X86_PF_USER) &&
		     !(regs->flags & X86_EFLAGS_AC))) अणु
		/*
		 * No extable entry here.  This was a kernel access to an
		 * invalid poपूर्णांकer.  get_kernel_nofault() will not get here.
		 */
		page_fault_oops(regs, error_code, address);
		वापस;
	पूर्ण

	/*
	 * If we're in an पूर्णांकerrupt, have no user context or are running
	 * in a region with pagefaults disabled then we must not take the fault
	 */
	अगर (unlikely(faulthandler_disabled() || !mm)) अणु
		bad_area_nosemaphore(regs, error_code, address);
		वापस;
	पूर्ण

	/*
	 * It's safe to allow irq's after cr2 has been saved and the
	 * vदो_स्मृति fault has been handled.
	 *
	 * User-mode रेजिस्टरs count as a user access even क्रम any
	 * potential प्रणाली fault or CPU buglet:
	 */
	अगर (user_mode(regs)) अणु
		local_irq_enable();
		flags |= FAULT_FLAG_USER;
	पूर्ण अन्यथा अणु
		अगर (regs->flags & X86_EFLAGS_IF)
			local_irq_enable();
	पूर्ण

	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, regs, address);

	अगर (error_code & X86_PF_WRITE)
		flags |= FAULT_FLAG_WRITE;
	अगर (error_code & X86_PF_INSTR)
		flags |= FAULT_FLAG_INSTRUCTION;

#अगर_घोषित CONFIG_X86_64
	/*
	 * Faults in the vsyscall page might need emulation.  The
	 * vsyscall page is at a high address (>PAGE_OFFSET), but is
	 * considered to be part of the user address space.
	 *
	 * The vsyscall page करोes not have a "real" VMA, so करो this
	 * emulation beक्रमe we go searching क्रम VMAs.
	 *
	 * PKRU never rejects inकाष्ठाion fetches, so we करोn't need
	 * to consider the PF_PK bit.
	 */
	अगर (is_vsyscall_vaddr(address)) अणु
		अगर (emulate_vsyscall(error_code, regs, address))
			वापस;
	पूर्ण
#पूर्ण_अगर

	/*
	 * Kernel-mode access to the user address space should only occur
	 * on well-defined single inकाष्ठाions listed in the exception
	 * tables.  But, an erroneous kernel fault occurring outside one of
	 * those areas which also holds mmap_lock might deadlock attempting
	 * to validate the fault against the address space.
	 *
	 * Only करो the expensive exception table search when we might be at
	 * risk of a deadlock.  This happens अगर we
	 * 1. Failed to acquire mmap_lock, and
	 * 2. The access did not originate in userspace.
	 */
	अगर (unlikely(!mmap_पढ़ो_trylock(mm))) अणु
		अगर (!user_mode(regs) && !search_exception_tables(regs->ip)) अणु
			/*
			 * Fault from code in kernel from
			 * which we करो not expect faults.
			 */
			bad_area_nosemaphore(regs, error_code, address);
			वापस;
		पूर्ण
retry:
		mmap_पढ़ो_lock(mm);
	पूर्ण अन्यथा अणु
		/*
		 * The above करोwn_पढ़ो_trylock() might have succeeded in
		 * which हाल we'll have missed the might_sleep() from
		 * करोwn_पढ़ो():
		 */
		might_sleep();
	पूर्ण

	vma = find_vma(mm, address);
	अगर (unlikely(!vma)) अणु
		bad_area(regs, error_code, address);
		वापस;
	पूर्ण
	अगर (likely(vma->vm_start <= address))
		जाओ good_area;
	अगर (unlikely(!(vma->vm_flags & VM_GROWSDOWN))) अणु
		bad_area(regs, error_code, address);
		वापस;
	पूर्ण
	अगर (unlikely(expand_stack(vma, address))) अणु
		bad_area(regs, error_code, address);
		वापस;
	पूर्ण

	/*
	 * Ok, we have a good vm_area क्रम this memory access, so
	 * we can handle it..
	 */
good_area:
	अगर (unlikely(access_error(error_code, vma))) अणु
		bad_area_access_error(regs, error_code, address, vma);
		वापस;
	पूर्ण

	/*
	 * If क्रम any reason at all we couldn't handle the fault,
	 * make sure we निकास gracefully rather than endlessly reकरो
	 * the fault.  Since we never set FAULT_FLAG_RETRY_NOWAIT, अगर
	 * we get VM_FAULT_RETRY back, the mmap_lock has been unlocked.
	 *
	 * Note that handle_userfault() may also release and reacquire mmap_lock
	 * (and not वापस with VM_FAULT_RETRY), when वापसing to userland to
	 * repeat the page fault later with a VM_FAULT_NOPAGE retval
	 * (potentially after handling any pending संकेत during the वापस to
	 * userland). The वापस to userland is identअगरied whenever
	 * FAULT_FLAG_USER|FAULT_FLAG_KILLABLE are both set in flags.
	 */
	fault = handle_mm_fault(vma, address, flags, regs);

	अगर (fault_संकेत_pending(fault, regs)) अणु
		/*
		 * Quick path to respond to संकेतs.  The core mm code
		 * has unlocked the mm क्रम us अगर we get here.
		 */
		अगर (!user_mode(regs))
			kernelmode_fixup_or_oops(regs, error_code, address,
						 SIGBUS, BUS_ADRERR);
		वापस;
	पूर्ण

	/*
	 * If we need to retry the mmap_lock has alपढ़ोy been released,
	 * and अगर there is a fatal संकेत pending there is no guarantee
	 * that we made any progress. Handle this हाल first.
	 */
	अगर (unlikely((fault & VM_FAULT_RETRY) &&
		     (flags & FAULT_FLAG_ALLOW_RETRY))) अणु
		flags |= FAULT_FLAG_TRIED;
		जाओ retry;
	पूर्ण

	mmap_पढ़ो_unlock(mm);
	अगर (likely(!(fault & VM_FAULT_ERROR)))
		वापस;

	अगर (fatal_संकेत_pending(current) && !user_mode(regs)) अणु
		kernelmode_fixup_or_oops(regs, error_code, address, 0, 0);
		वापस;
	पूर्ण

	अगर (fault & VM_FAULT_OOM) अणु
		/* Kernel mode? Handle exceptions or die: */
		अगर (!user_mode(regs)) अणु
			kernelmode_fixup_or_oops(regs, error_code, address,
						 संक_अंश, SEGV_MAPERR);
			वापस;
		पूर्ण

		/*
		 * We ran out of memory, call the OOM समाप्तer, and वापस the
		 * userspace (which will retry the fault, or समाप्त us अगर we got
		 * oom-समाप्तed):
		 */
		pagefault_out_of_memory();
	पूर्ण अन्यथा अणु
		अगर (fault & (VM_FAULT_SIGBUS|VM_FAULT_HWPOISON|
			     VM_FAULT_HWPOISON_LARGE))
			करो_sigbus(regs, error_code, address, fault);
		अन्यथा अगर (fault & VM_FAULT_संक_अंश)
			bad_area_nosemaphore(regs, error_code, address);
		अन्यथा
			BUG();
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(करो_user_addr_fault);

अटल __always_अंतरभूत व्योम
trace_page_fault_entries(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
			 अचिन्हित दीर्घ address)
अणु
	अगर (!trace_pagefault_enabled())
		वापस;

	अगर (user_mode(regs))
		trace_page_fault_user(address, regs, error_code);
	अन्यथा
		trace_page_fault_kernel(address, regs, error_code);
पूर्ण

अटल __always_अंतरभूत व्योम
handle_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code,
			      अचिन्हित दीर्घ address)
अणु
	trace_page_fault_entries(regs, error_code, address);

	अगर (unlikely(kmmio_fault(regs, address)))
		वापस;

	/* Was the fault on kernel-controlled part of the address space? */
	अगर (unlikely(fault_in_kernel_space(address))) अणु
		करो_kern_addr_fault(regs, error_code, address);
	पूर्ण अन्यथा अणु
		करो_user_addr_fault(regs, error_code, address);
		/*
		 * User address page fault handling might have reenabled
		 * पूर्णांकerrupts. Fixing up all potential निकास poपूर्णांकs of
		 * करो_user_addr_fault() and its leaf functions is just not
		 * करोable w/o creating an unholy mess or turning the code
		 * upside करोwn.
		 */
		local_irq_disable();
	पूर्ण
पूर्ण

DEFINE_IDTENTRY_RAW_ERRORCODE(exc_page_fault)
अणु
	अचिन्हित दीर्घ address = पढ़ो_cr2();
	irqentry_state_t state;

	prefetchw(&current->mm->mmap_lock);

	/*
	 * KVM uses #PF vector to deliver 'page not present' events to guests
	 * (asynchronous page fault mechanism). The event happens when a
	 * userspace task is trying to access some valid (from guest's poपूर्णांक of
	 * view) memory which is not currently mapped by the host (e.g. the
	 * memory is swapped out). Note, the corresponding "page ready" event
	 * which is injected when the memory becomes available, is delivered via
	 * an पूर्णांकerrupt mechanism and not a #PF exception
	 * (see arch/x86/kernel/kvm.c: sysvec_kvm_asyncpf_पूर्णांकerrupt()).
	 *
	 * We are relying on the पूर्णांकerrupted context being sane (valid RSP,
	 * relevant locks not held, etc.), which is fine as दीर्घ as the
	 * पूर्णांकerrupted context had IF=1.  We are also relying on the KVM
	 * async pf type field and CR2 being पढ़ो consistently instead of
	 * getting values from real and async page faults mixed up.
	 *
	 * Fingers crossed.
	 *
	 * The async #PF handling code takes care of idtentry handling
	 * itself.
	 */
	अगर (kvm_handle_async_pf(regs, (u32)address))
		वापस;

	/*
	 * Entry handling क्रम valid #PF from kernel mode is slightly
	 * dअगरferent: RCU is alपढ़ोy watching and rcu_irq_enter() must not
	 * be invoked because a kernel fault on a user space address might
	 * sleep.
	 *
	 * In हाल the fault hit a RCU idle region the conditional entry
	 * code reenabled RCU to aव्योम subsequent wreckage which helps
	 * debuggability.
	 */
	state = irqentry_enter(regs);

	instrumentation_begin();
	handle_page_fault(regs, error_code, address);
	instrumentation_end();

	irqentry_निकास(regs, state);
पूर्ण
