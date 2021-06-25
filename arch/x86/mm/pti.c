<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright(c) 2017 Intel Corporation. All rights reserved.
 *
 * This code is based in part on work published here:
 *
 *	https://github.com/IAIK/KAISER
 *
 * The original work was written by and and चिन्हित off by क्रम the Linux
 * kernel by:
 *
 *   Signed-off-by: Riअक्षरd Fellner <riअक्षरd.fellner@student.tugraz.at>
 *   Signed-off-by: Moritz Lipp <moritz.lipp@iaik.tugraz.at>
 *   Signed-off-by: Daniel Gruss <daniel.gruss@iaik.tugraz.at>
 *   Signed-off-by: Michael Schwarz <michael.schwarz@iaik.tugraz.at>
 *
 * Major changes to the original code by: Dave Hansen <dave.hansen@पूर्णांकel.com>
 * Mostly rewritten by Thomas Gleixner <tglx@linutronix.de> and
 *		       Andy Lutomirsky <luto@amacapital.net>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/vsyscall.h>
#समावेश <यंत्र/cmdline.h>
#समावेश <यंत्र/pti.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/set_memory.h>

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)     "Kernel/User page tables isolation: " fmt

/* Backporting helper */
#अगर_अघोषित __GFP_NOTRACK
#घोषणा __GFP_NOTRACK	0
#पूर्ण_अगर

/*
 * Define the page-table levels we clone क्रम user-space on 32
 * and 64 bit.
 */
#अगर_घोषित CONFIG_X86_64
#घोषणा	PTI_LEVEL_KERNEL_IMAGE	PTI_CLONE_PMD
#अन्यथा
#घोषणा	PTI_LEVEL_KERNEL_IMAGE	PTI_CLONE_PTE
#पूर्ण_अगर

अटल व्योम __init pti_prपूर्णांक_अगर_insecure(स्थिर अक्षर *reason)
अणु
	अगर (boot_cpu_has_bug(X86_BUG_CPU_MELTDOWN))
		pr_info("%s\n", reason);
पूर्ण

अटल व्योम __init pti_prपूर्णांक_अगर_secure(स्थिर अक्षर *reason)
अणु
	अगर (!boot_cpu_has_bug(X86_BUG_CPU_MELTDOWN))
		pr_info("%s\n", reason);
पूर्ण

अटल क्रमागत pti_mode अणु
	PTI_AUTO = 0,
	PTI_FORCE_OFF,
	PTI_FORCE_ON
पूर्ण pti_mode;

व्योम __init pti_check_bootसमय_disable(व्योम)
अणु
	अक्षर arg[5];
	पूर्णांक ret;

	/* Assume mode is स्वतः unless overridden. */
	pti_mode = PTI_AUTO;

	अगर (hypervisor_is_type(X86_HYPER_XEN_PV)) अणु
		pti_mode = PTI_FORCE_OFF;
		pti_prपूर्णांक_अगर_insecure("disabled on XEN PV.");
		वापस;
	पूर्ण

	ret = cmdline_find_option(boot_command_line, "pti", arg, माप(arg));
	अगर (ret > 0)  अणु
		अगर (ret == 3 && !म_भेदन(arg, "off", 3)) अणु
			pti_mode = PTI_FORCE_OFF;
			pti_prपूर्णांक_अगर_insecure("disabled on command line.");
			वापस;
		पूर्ण
		अगर (ret == 2 && !म_भेदन(arg, "on", 2)) अणु
			pti_mode = PTI_FORCE_ON;
			pti_prपूर्णांक_अगर_secure("force enabled on command line.");
			जाओ enable;
		पूर्ण
		अगर (ret == 4 && !म_भेदन(arg, "auto", 4)) अणु
			pti_mode = PTI_AUTO;
			जाओ स्वतःsel;
		पूर्ण
	पूर्ण

	अगर (cmdline_find_option_bool(boot_command_line, "nopti") ||
	    cpu_mitigations_off()) अणु
		pti_mode = PTI_FORCE_OFF;
		pti_prपूर्णांक_अगर_insecure("disabled on command line.");
		वापस;
	पूर्ण

स्वतःsel:
	अगर (!boot_cpu_has_bug(X86_BUG_CPU_MELTDOWN))
		वापस;
enable:
	setup_क्रमce_cpu_cap(X86_FEATURE_PTI);
पूर्ण

pgd_t __pti_set_user_pgtbl(pgd_t *pgdp, pgd_t pgd)
अणु
	/*
	 * Changes to the high (kernel) portion of the kernelmode page
	 * tables are not स्वतःmatically propagated to the usermode tables.
	 *
	 * Users should keep in mind that, unlike the kernelmode tables,
	 * there is no vदो_स्मृति_fault equivalent क्रम the usermode tables.
	 * Top-level entries added to init_mm's usermode pgd after boot
	 * will not be स्वतःmatically propagated to other mms.
	 */
	अगर (!pgdp_maps_userspace(pgdp))
		वापस pgd;

	/*
	 * The user page tables get the full PGD, accessible from
	 * userspace:
	 */
	kernel_to_user_pgdp(pgdp)->pgd = pgd.pgd;

	/*
	 * If this is normal user memory, make it NX in the kernel
	 * pagetables so that, अगर we somehow screw up and वापस to
	 * usermode with the kernel CR3 loaded, we'll get a page fault
	 * instead of allowing user code to execute with the wrong CR3.
	 *
	 * As exceptions, we करोn't set NX अगर:
	 *  - _PAGE_USER is not set.  This could be an executable
	 *     EFI runसमय mapping or something similar, and the kernel
	 *     may execute from it
	 *  - we करोn't have NX support
	 *  - we're clearing the PGD (i.e. the new pgd is not present).
	 */
	अगर ((pgd.pgd & (_PAGE_USER|_PAGE_PRESENT)) == (_PAGE_USER|_PAGE_PRESENT) &&
	    (__supported_pte_mask & _PAGE_NX))
		pgd.pgd |= _PAGE_NX;

	/* वापस the copy of the PGD we want the kernel to use: */
	वापस pgd;
पूर्ण

/*
 * Walk the user copy of the page tables (optionally) trying to allocate
 * page table pages on the way करोwn.
 *
 * Returns a poपूर्णांकer to a P4D on success, or शून्य on failure.
 */
अटल p4d_t *pti_user_pagetable_walk_p4d(अचिन्हित दीर्घ address)
अणु
	pgd_t *pgd = kernel_to_user_pgdp(pgd_offset_k(address));
	gfp_t gfp = (GFP_KERNEL | __GFP_NOTRACK | __GFP_ZERO);

	अगर (address < PAGE_OFFSET) अणु
		WARN_ONCE(1, "attempt to walk user address\n");
		वापस शून्य;
	पूर्ण

	अगर (pgd_none(*pgd)) अणु
		अचिन्हित दीर्घ new_p4d_page = __get_मुक्त_page(gfp);
		अगर (WARN_ON_ONCE(!new_p4d_page))
			वापस शून्य;

		set_pgd(pgd, __pgd(_KERNPG_TABLE | __pa(new_p4d_page)));
	पूर्ण
	BUILD_BUG_ON(pgd_large(*pgd) != 0);

	वापस p4d_offset(pgd, address);
पूर्ण

/*
 * Walk the user copy of the page tables (optionally) trying to allocate
 * page table pages on the way करोwn.
 *
 * Returns a poपूर्णांकer to a PMD on success, or शून्य on failure.
 */
अटल pmd_t *pti_user_pagetable_walk_pmd(अचिन्हित दीर्घ address)
अणु
	gfp_t gfp = (GFP_KERNEL | __GFP_NOTRACK | __GFP_ZERO);
	p4d_t *p4d;
	pud_t *pud;

	p4d = pti_user_pagetable_walk_p4d(address);
	अगर (!p4d)
		वापस शून्य;

	BUILD_BUG_ON(p4d_large(*p4d) != 0);
	अगर (p4d_none(*p4d)) अणु
		अचिन्हित दीर्घ new_pud_page = __get_मुक्त_page(gfp);
		अगर (WARN_ON_ONCE(!new_pud_page))
			वापस शून्य;

		set_p4d(p4d, __p4d(_KERNPG_TABLE | __pa(new_pud_page)));
	पूर्ण

	pud = pud_offset(p4d, address);
	/* The user page tables करो not use large mappings: */
	अगर (pud_large(*pud)) अणु
		WARN_ON(1);
		वापस शून्य;
	पूर्ण
	अगर (pud_none(*pud)) अणु
		अचिन्हित दीर्घ new_pmd_page = __get_मुक्त_page(gfp);
		अगर (WARN_ON_ONCE(!new_pmd_page))
			वापस शून्य;

		set_pud(pud, __pud(_KERNPG_TABLE | __pa(new_pmd_page)));
	पूर्ण

	वापस pmd_offset(pud, address);
पूर्ण

/*
 * Walk the shaकरोw copy of the page tables (optionally) trying to allocate
 * page table pages on the way करोwn.  Does not support large pages.
 *
 * Note: this is only used when mapping *new* kernel data पूर्णांकo the
 * user/shaकरोw page tables.  It is never used क्रम userspace data.
 *
 * Returns a poपूर्णांकer to a PTE on success, or शून्य on failure.
 */
अटल pte_t *pti_user_pagetable_walk_pte(अचिन्हित दीर्घ address)
अणु
	gfp_t gfp = (GFP_KERNEL | __GFP_NOTRACK | __GFP_ZERO);
	pmd_t *pmd;
	pte_t *pte;

	pmd = pti_user_pagetable_walk_pmd(address);
	अगर (!pmd)
		वापस शून्य;

	/* We can't करो anything sensible अगर we hit a large mapping. */
	अगर (pmd_large(*pmd)) अणु
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	अगर (pmd_none(*pmd)) अणु
		अचिन्हित दीर्घ new_pte_page = __get_मुक्त_page(gfp);
		अगर (!new_pte_page)
			वापस शून्य;

		set_pmd(pmd, __pmd(_KERNPG_TABLE | __pa(new_pte_page)));
	पूर्ण

	pte = pte_offset_kernel(pmd, address);
	अगर (pte_flags(*pte) & _PAGE_USER) अणु
		WARN_ONCE(1, "attempt to walk to user pte\n");
		वापस शून्य;
	पूर्ण
	वापस pte;
पूर्ण

#अगर_घोषित CONFIG_X86_VSYSCALL_EMULATION
अटल व्योम __init pti_setup_vsyscall(व्योम)
अणु
	pte_t *pte, *target_pte;
	अचिन्हित पूर्णांक level;

	pte = lookup_address(VSYSCALL_ADDR, &level);
	अगर (!pte || WARN_ON(level != PG_LEVEL_4K) || pte_none(*pte))
		वापस;

	target_pte = pti_user_pagetable_walk_pte(VSYSCALL_ADDR);
	अगर (WARN_ON(!target_pte))
		वापस;

	*target_pte = *pte;
	set_vsyscall_pgtable_user_bits(kernel_to_user_pgdp(swapper_pg_dir));
पूर्ण
#अन्यथा
अटल व्योम __init pti_setup_vsyscall(व्योम) अणु पूर्ण
#पूर्ण_अगर

क्रमागत pti_clone_level अणु
	PTI_CLONE_PMD,
	PTI_CLONE_PTE,
पूर्ण;

अटल व्योम
pti_clone_pgtable(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		  क्रमागत pti_clone_level level)
अणु
	अचिन्हित दीर्घ addr;

	/*
	 * Clone the populated PMDs which cover start to end. These PMD areas
	 * can have holes.
	 */
	क्रम (addr = start; addr < end;) अणु
		pte_t *pte, *target_pte;
		pmd_t *pmd, *target_pmd;
		pgd_t *pgd;
		p4d_t *p4d;
		pud_t *pud;

		/* Overflow check */
		अगर (addr < start)
			अवरोध;

		pgd = pgd_offset_k(addr);
		अगर (WARN_ON(pgd_none(*pgd)))
			वापस;
		p4d = p4d_offset(pgd, addr);
		अगर (WARN_ON(p4d_none(*p4d)))
			वापस;

		pud = pud_offset(p4d, addr);
		अगर (pud_none(*pud)) अणु
			WARN_ON_ONCE(addr & ~PUD_MASK);
			addr = round_up(addr + 1, PUD_SIZE);
			जारी;
		पूर्ण

		pmd = pmd_offset(pud, addr);
		अगर (pmd_none(*pmd)) अणु
			WARN_ON_ONCE(addr & ~PMD_MASK);
			addr = round_up(addr + 1, PMD_SIZE);
			जारी;
		पूर्ण

		अगर (pmd_large(*pmd) || level == PTI_CLONE_PMD) अणु
			target_pmd = pti_user_pagetable_walk_pmd(addr);
			अगर (WARN_ON(!target_pmd))
				वापस;

			/*
			 * Only clone present PMDs.  This ensures only setting
			 * _PAGE_GLOBAL on present PMDs.  This should only be
			 * called on well-known addresses anyway, so a non-
			 * present PMD would be a surprise.
			 */
			अगर (WARN_ON(!(pmd_flags(*pmd) & _PAGE_PRESENT)))
				वापस;

			/*
			 * Setting 'target_pmd' below creates a mapping in both
			 * the user and kernel page tables.  It is effectively
			 * global, so set it as global in both copies.  Note:
			 * the X86_FEATURE_PGE check is not _required_ because
			 * the CPU ignores _PAGE_GLOBAL when PGE is not
			 * supported.  The check keeps consistency with
			 * code that only set this bit when supported.
			 */
			अगर (boot_cpu_has(X86_FEATURE_PGE))
				*pmd = pmd_set_flags(*pmd, _PAGE_GLOBAL);

			/*
			 * Copy the PMD.  That is, the kernelmode and usermode
			 * tables will share the last-level page tables of this
			 * address range
			 */
			*target_pmd = *pmd;

			addr += PMD_SIZE;

		पूर्ण अन्यथा अगर (level == PTI_CLONE_PTE) अणु

			/* Walk the page-table करोwn to the pte level */
			pte = pte_offset_kernel(pmd, addr);
			अगर (pte_none(*pte)) अणु
				addr += PAGE_SIZE;
				जारी;
			पूर्ण

			/* Only clone present PTEs */
			अगर (WARN_ON(!(pte_flags(*pte) & _PAGE_PRESENT)))
				वापस;

			/* Allocate PTE in the user page-table */
			target_pte = pti_user_pagetable_walk_pte(addr);
			अगर (WARN_ON(!target_pte))
				वापस;

			/* Set GLOBAL bit in both PTEs */
			अगर (boot_cpu_has(X86_FEATURE_PGE))
				*pte = pte_set_flags(*pte, _PAGE_GLOBAL);

			/* Clone the PTE */
			*target_pte = *pte;

			addr += PAGE_SIZE;

		पूर्ण अन्यथा अणु
			BUG();
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_64
/*
 * Clone a single p4d (i.e. a top-level entry on 4-level प्रणालीs and a
 * next-level entry on 5-level प्रणालीs.
 */
अटल व्योम __init pti_clone_p4d(अचिन्हित दीर्घ addr)
अणु
	p4d_t *kernel_p4d, *user_p4d;
	pgd_t *kernel_pgd;

	user_p4d = pti_user_pagetable_walk_p4d(addr);
	अगर (!user_p4d)
		वापस;

	kernel_pgd = pgd_offset_k(addr);
	kernel_p4d = p4d_offset(kernel_pgd, addr);
	*user_p4d = *kernel_p4d;
पूर्ण

/*
 * Clone the CPU_ENTRY_AREA and associated data पूर्णांकo the user space visible
 * page table.
 */
अटल व्योम __init pti_clone_user_shared(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	pti_clone_p4d(CPU_ENTRY_AREA_BASE);

	क्रम_each_possible_cpu(cpu) अणु
		/*
		 * The SYSCALL64 entry code needs one word of scratch space
		 * in which to spill a रेजिस्टर.  It lives in the sp2 slot
		 * of the CPU's TSS.
		 *
		 * This is करोne क्रम all possible CPUs during boot to ensure
		 * that it's propagated to all mms.
		 */

		अचिन्हित दीर्घ va = (अचिन्हित दीर्घ)&per_cpu(cpu_tss_rw, cpu);
		phys_addr_t pa = per_cpu_ptr_to_phys((व्योम *)va);
		pte_t *target_pte;

		target_pte = pti_user_pagetable_walk_pte(va);
		अगर (WARN_ON(!target_pte))
			वापस;

		*target_pte = pfn_pte(pa >> PAGE_SHIFT, PAGE_KERNEL);
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_X86_64 */

/*
 * On 32 bit PAE प्रणालीs with 1GB of Kernel address space there is only
 * one pgd/p4d क्रम the whole kernel. Cloning that would map the whole
 * address space पूर्णांकo the user page-tables, making PTI useless. So clone
 * the page-table on the PMD level to prevent that.
 */
अटल व्योम __init pti_clone_user_shared(व्योम)
अणु
	अचिन्हित दीर्घ start, end;

	start = CPU_ENTRY_AREA_BASE;
	end   = start + (PAGE_SIZE * CPU_ENTRY_AREA_PAGES);

	pti_clone_pgtable(start, end, PTI_CLONE_PMD);
पूर्ण
#पूर्ण_अगर /* CONFIG_X86_64 */

/*
 * Clone the ESPFIX P4D पूर्णांकo the user space visible page table
 */
अटल व्योम __init pti_setup_espfix64(व्योम)
अणु
#अगर_घोषित CONFIG_X86_ESPFIX64
	pti_clone_p4d(ESPFIX_BASE_ADDR);
#पूर्ण_अगर
पूर्ण

/*
 * Clone the populated PMDs of the entry text and क्रमce it RO.
 */
अटल व्योम pti_clone_entry_text(व्योम)
अणु
	pti_clone_pgtable((अचिन्हित दीर्घ) __entry_text_start,
			  (अचिन्हित दीर्घ) __entry_text_end,
			  PTI_CLONE_PMD);
पूर्ण

/*
 * Global pages and PCIDs are both ways to make kernel TLB entries
 * live दीर्घer, reduce TLB misses and improve kernel perक्रमmance.
 * But, leaving all kernel text Global makes it potentially accessible
 * to Meltकरोwn-style attacks which make it trivial to find gadमाला_लो or
 * defeat KASLR.
 *
 * Only use global pages when it is really worth it.
 */
अटल अंतरभूत bool pti_kernel_image_global_ok(व्योम)
अणु
	/*
	 * Systems with PCIDs get little benefit from global
	 * kernel text and are not worth the करोwnsides.
	 */
	अगर (cpu_feature_enabled(X86_FEATURE_PCID))
		वापस false;

	/*
	 * Only करो global kernel image क्रम pti=स्वतः.  Do the most
	 * secure thing (not global) अगर pti=on specअगरied.
	 */
	अगर (pti_mode != PTI_AUTO)
		वापस false;

	/*
	 * K8 may not tolerate the cleared _PAGE_RW on the userspace
	 * global kernel image pages.  Do the safe thing (disable
	 * global kernel image).  This is unlikely to ever be
	 * noticed because PTI is disabled by शेष on AMD CPUs.
	 */
	अगर (boot_cpu_has(X86_FEATURE_K8))
		वापस false;

	/*
	 * RANDSTRUCT derives its hardening benefits from the
	 * attacker's lack of knowledge about the layout of kernel
	 * data काष्ठाures.  Keep the kernel image non-global in
	 * हालs where RANDSTRUCT is in use to help keep the layout a
	 * secret.
	 */
	अगर (IS_ENABLED(CONFIG_GCC_PLUGIN_RANDSTRUCT))
		वापस false;

	वापस true;
पूर्ण

/*
 * For some configurations, map all of kernel text पूर्णांकo the user page
 * tables.  This reduces TLB misses, especially on non-PCID प्रणालीs.
 */
अटल व्योम pti_clone_kernel_text(व्योम)
अणु
	/*
	 * rodata is part of the kernel image and is normally
	 * पढ़ोable on the fileप्रणाली or on the web.  But, करो not
	 * clone the areas past rodata, they might contain secrets.
	 */
	अचिन्हित दीर्घ start = PFN_ALIGN(_text);
	अचिन्हित दीर्घ end_clone  = (अचिन्हित दीर्घ)__end_rodata_aligned;
	अचिन्हित दीर्घ end_global = PFN_ALIGN((अचिन्हित दीर्घ)_etext);

	अगर (!pti_kernel_image_global_ok())
		वापस;

	pr_debug("mapping partial kernel image into user address space\n");

	/*
	 * Note that this will unकरो _some_ of the work that
	 * pti_set_kernel_image_nonglobal() did to clear the
	 * global bit.
	 */
	pti_clone_pgtable(start, end_clone, PTI_LEVEL_KERNEL_IMAGE);

	/*
	 * pti_clone_pgtable() will set the global bit in any PMDs
	 * that it clones, but we also need to get any PTEs in
	 * the last level क्रम areas that are not huge-page-aligned.
	 */

	/* Set the global bit क्रम normal non-__init kernel text: */
	set_memory_global(start, (end_global - start) >> PAGE_SHIFT);
पूर्ण

अटल व्योम pti_set_kernel_image_nonglobal(व्योम)
अणु
	/*
	 * The identity map is created with PMDs, regardless of the
	 * actual length of the kernel.  We need to clear
	 * _PAGE_GLOBAL up to a PMD boundary, not just to the end
	 * of the image.
	 */
	अचिन्हित दीर्घ start = PFN_ALIGN(_text);
	अचिन्हित दीर्घ end = ALIGN((अचिन्हित दीर्घ)_end, PMD_PAGE_SIZE);

	/*
	 * This clears _PAGE_GLOBAL from the entire kernel image.
	 * pti_clone_kernel_text() map put _PAGE_GLOBAL back क्रम
	 * areas that are mapped to userspace.
	 */
	set_memory_nonglobal(start, (end - start) >> PAGE_SHIFT);
पूर्ण

/*
 * Initialize kernel page table isolation
 */
व्योम __init pti_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_PTI))
		वापस;

	pr_info("enabled\n");

#अगर_घोषित CONFIG_X86_32
	/*
	 * We check क्रम X86_FEATURE_PCID here. But the init-code will
	 * clear the feature flag on 32 bit because the feature is not
	 * supported on 32 bit anyway. To prपूर्णांक the warning we need to
	 * check with cpuid directly again.
	 */
	अगर (cpuid_ecx(0x1) & BIT(17)) अणु
		/* Use prपूर्णांकk to work around pr_fmt() */
		prपूर्णांकk(KERN_WARNING "\n");
		prपूर्णांकk(KERN_WARNING "************************************************************\n");
		prपूर्णांकk(KERN_WARNING "** WARNING! WARNING! WARNING! WARNING! WARNING! WARNING!  **\n");
		prपूर्णांकk(KERN_WARNING "**                                                        **\n");
		prपूर्णांकk(KERN_WARNING "** You are using 32-bit PTI on a 64-bit PCID-capable CPU. **\n");
		prपूर्णांकk(KERN_WARNING "** Your performance will increase dramatically if you     **\n");
		prपूर्णांकk(KERN_WARNING "** switch to a 64-bit kernel!                             **\n");
		prपूर्णांकk(KERN_WARNING "**                                                        **\n");
		prपूर्णांकk(KERN_WARNING "** WARNING! WARNING! WARNING! WARNING! WARNING! WARNING!  **\n");
		prपूर्णांकk(KERN_WARNING "************************************************************\n");
	पूर्ण
#पूर्ण_अगर

	pti_clone_user_shared();

	/* Unकरो all global bits from the init pagetables in head_64.S: */
	pti_set_kernel_image_nonglobal();
	/* Replace some of the global bits just क्रम shared entry text: */
	pti_clone_entry_text();
	pti_setup_espfix64();
	pti_setup_vsyscall();
पूर्ण

/*
 * Finalize the kernel mappings in the userspace page-table. Some of the
 * mappings क्रम the kernel image might have changed since pti_init()
 * cloned them. This is because parts of the kernel image have been
 * mapped RO and/or NX.  These changes need to be cloned again to the
 * userspace page-table.
 */
व्योम pti_finalize(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_PTI))
		वापस;
	/*
	 * We need to clone everything (again) that maps parts of the
	 * kernel image.
	 */
	pti_clone_entry_text();
	pti_clone_kernel_text();

	debug_checkwx_user();
पूर्ण
