<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  prepare to run common code
 *
 *  Copyright (C) 2000 Andrea Arcangeli <andrea@suse.de> SuSE
 */

#घोषणा DISABLE_BRANCH_PROFILING

/* cpu_feature_enabled() cannot be used this early */
#घोषणा USE_EARLY_PGTABLE_L5

#समावेश <linux/init.h>
#समावेश <linux/linkage.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/percpu.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/kdebug.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <यंत्र/bootparam_utils.h>
#समावेश <यंत्र/microcode.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/realmode.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/trapnr.h>
#समावेश <यंत्र/sev.h>

/*
 * Manage page tables very early on.
 */
बाह्य pmd_t early_dynamic_pgts[EARLY_DYNAMIC_PAGE_TABLES][PTRS_PER_PMD];
अटल अचिन्हित पूर्णांक __initdata next_early_pgt;
pmdval_t early_pmd_flags = __PAGE_KERNEL_LARGE & ~(_PAGE_GLOBAL | _PAGE_NX);

#अगर_घोषित CONFIG_X86_5LEVEL
अचिन्हित पूर्णांक __pgtable_l5_enabled __ro_after_init;
अचिन्हित पूर्णांक pgdir_shअगरt __ro_after_init = 39;
EXPORT_SYMBOL(pgdir_shअगरt);
अचिन्हित पूर्णांक ptrs_per_p4d __ro_after_init = 1;
EXPORT_SYMBOL(ptrs_per_p4d);
#पूर्ण_अगर

#अगर_घोषित CONFIG_DYNAMIC_MEMORY_LAYOUT
अचिन्हित दीर्घ page_offset_base __ro_after_init = __PAGE_OFFSET_BASE_L4;
EXPORT_SYMBOL(page_offset_base);
अचिन्हित दीर्घ vदो_स्मृति_base __ro_after_init = __VMALLOC_BASE_L4;
EXPORT_SYMBOL(vदो_स्मृति_base);
अचिन्हित दीर्घ vmemmap_base __ro_after_init = __VMEMMAP_BASE_L4;
EXPORT_SYMBOL(vmemmap_base);
#पूर्ण_अगर

/*
 * GDT used on the boot CPU beक्रमe चयनing to भव addresses.
 */
अटल काष्ठा desc_काष्ठा startup_gdt[GDT_ENTRIES] = अणु
	[GDT_ENTRY_KERNEL32_CS]         = GDT_ENTRY_INIT(0xc09b, 0, 0xfffff),
	[GDT_ENTRY_KERNEL_CS]           = GDT_ENTRY_INIT(0xa09b, 0, 0xfffff),
	[GDT_ENTRY_KERNEL_DS]           = GDT_ENTRY_INIT(0xc093, 0, 0xfffff),
पूर्ण;

/*
 * Address needs to be set at runसमय because it references the startup_gdt
 * जबतक the kernel still uses a direct mapping.
 */
अटल काष्ठा desc_ptr startup_gdt_descr = अणु
	.size = माप(startup_gdt),
	.address = 0,
पूर्ण;

#घोषणा __head	__section(".head.text")

अटल व्योम __head *fixup_poपूर्णांकer(व्योम *ptr, अचिन्हित दीर्घ physaddr)
अणु
	वापस ptr - (व्योम *)_text + (व्योम *)physaddr;
पूर्ण

अटल अचिन्हित दीर्घ __head *fixup_दीर्घ(व्योम *ptr, अचिन्हित दीर्घ physaddr)
अणु
	वापस fixup_poपूर्णांकer(ptr, physaddr);
पूर्ण

#अगर_घोषित CONFIG_X86_5LEVEL
अटल अचिन्हित पूर्णांक __head *fixup_पूर्णांक(व्योम *ptr, अचिन्हित दीर्घ physaddr)
अणु
	वापस fixup_poपूर्णांकer(ptr, physaddr);
पूर्ण

अटल bool __head check_la57_support(अचिन्हित दीर्घ physaddr)
अणु
	/*
	 * 5-level paging is detected and enabled at kernel decompression
	 * stage. Only check अगर it has been enabled there.
	 */
	अगर (!(native_पढ़ो_cr4() & X86_CR4_LA57))
		वापस false;

	*fixup_पूर्णांक(&__pgtable_l5_enabled, physaddr) = 1;
	*fixup_पूर्णांक(&pgdir_shअगरt, physaddr) = 48;
	*fixup_पूर्णांक(&ptrs_per_p4d, physaddr) = 512;
	*fixup_दीर्घ(&page_offset_base, physaddr) = __PAGE_OFFSET_BASE_L5;
	*fixup_दीर्घ(&vदो_स्मृति_base, physaddr) = __VMALLOC_BASE_L5;
	*fixup_दीर्घ(&vmemmap_base, physaddr) = __VMEMMAP_BASE_L5;

	वापस true;
पूर्ण
#अन्यथा
अटल bool __head check_la57_support(अचिन्हित दीर्घ physaddr)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

/* Code in __startup_64() can be relocated during execution, but the compiler
 * करोesn't have to generate PC-relative relocations when accessing globals from
 * that function. Clang actually करोes not generate them, which leads to
 * boot-समय crashes. To work around this problem, every global poपूर्णांकer must
 * be adjusted using fixup_poपूर्णांकer().
 */
अचिन्हित दीर्घ __head __startup_64(अचिन्हित दीर्घ physaddr,
				  काष्ठा boot_params *bp)
अणु
	अचिन्हित दीर्घ vaddr, vaddr_end;
	अचिन्हित दीर्घ load_delta, *p;
	अचिन्हित दीर्घ pgtable_flags;
	pgdval_t *pgd;
	p4dval_t *p4d;
	pudval_t *pud;
	pmdval_t *pmd, pmd_entry;
	pteval_t *mask_ptr;
	bool la57;
	पूर्णांक i;
	अचिन्हित पूर्णांक *next_pgt_ptr;

	la57 = check_la57_support(physaddr);

	/* Is the address too large? */
	अगर (physaddr >> MAX_PHYSMEM_BITS)
		क्रम (;;);

	/*
	 * Compute the delta between the address I am compiled to run at
	 * and the address I am actually running at.
	 */
	load_delta = physaddr - (अचिन्हित दीर्घ)(_text - __START_KERNEL_map);

	/* Is the address not 2M aligned? */
	अगर (load_delta & ~PMD_PAGE_MASK)
		क्रम (;;);

	/* Activate Secure Memory Encryption (SME) अगर supported and enabled */
	sme_enable(bp);

	/* Include the SME encryption mask in the fixup value */
	load_delta += sme_get_me_mask();

	/* Fixup the physical addresses in the page table */

	pgd = fixup_poपूर्णांकer(&early_top_pgt, physaddr);
	p = pgd + pgd_index(__START_KERNEL_map);
	अगर (la57)
		*p = (अचिन्हित दीर्घ)level4_kernel_pgt;
	अन्यथा
		*p = (अचिन्हित दीर्घ)level3_kernel_pgt;
	*p += _PAGE_TABLE_NOENC - __START_KERNEL_map + load_delta;

	अगर (la57) अणु
		p4d = fixup_poपूर्णांकer(&level4_kernel_pgt, physaddr);
		p4d[511] += load_delta;
	पूर्ण

	pud = fixup_poपूर्णांकer(&level3_kernel_pgt, physaddr);
	pud[510] += load_delta;
	pud[511] += load_delta;

	pmd = fixup_poपूर्णांकer(level2_fixmap_pgt, physaddr);
	क्रम (i = FIXMAP_PMD_TOP; i > FIXMAP_PMD_TOP - FIXMAP_PMD_NUM; i--)
		pmd[i] += load_delta;

	/*
	 * Set up the identity mapping क्रम the चयनover.  These
	 * entries should *NOT* have the global bit set!  This also
	 * creates a bunch of nonsense entries but that is fine --
	 * it aव्योमs problems around wraparound.
	 */

	next_pgt_ptr = fixup_poपूर्णांकer(&next_early_pgt, physaddr);
	pud = fixup_poपूर्णांकer(early_dynamic_pgts[(*next_pgt_ptr)++], physaddr);
	pmd = fixup_poपूर्णांकer(early_dynamic_pgts[(*next_pgt_ptr)++], physaddr);

	pgtable_flags = _KERNPG_TABLE_NOENC + sme_get_me_mask();

	अगर (la57) अणु
		p4d = fixup_poपूर्णांकer(early_dynamic_pgts[(*next_pgt_ptr)++],
				    physaddr);

		i = (physaddr >> PGसूची_SHIFT) % PTRS_PER_PGD;
		pgd[i + 0] = (pgdval_t)p4d + pgtable_flags;
		pgd[i + 1] = (pgdval_t)p4d + pgtable_flags;

		i = physaddr >> P4D_SHIFT;
		p4d[(i + 0) % PTRS_PER_P4D] = (pgdval_t)pud + pgtable_flags;
		p4d[(i + 1) % PTRS_PER_P4D] = (pgdval_t)pud + pgtable_flags;
	पूर्ण अन्यथा अणु
		i = (physaddr >> PGसूची_SHIFT) % PTRS_PER_PGD;
		pgd[i + 0] = (pgdval_t)pud + pgtable_flags;
		pgd[i + 1] = (pgdval_t)pud + pgtable_flags;
	पूर्ण

	i = physaddr >> PUD_SHIFT;
	pud[(i + 0) % PTRS_PER_PUD] = (pudval_t)pmd + pgtable_flags;
	pud[(i + 1) % PTRS_PER_PUD] = (pudval_t)pmd + pgtable_flags;

	pmd_entry = __PAGE_KERNEL_LARGE_EXEC & ~_PAGE_GLOBAL;
	/* Filter out unsupported __PAGE_KERNEL_* bits: */
	mask_ptr = fixup_poपूर्णांकer(&__supported_pte_mask, physaddr);
	pmd_entry &= *mask_ptr;
	pmd_entry += sme_get_me_mask();
	pmd_entry +=  physaddr;

	क्रम (i = 0; i < DIV_ROUND_UP(_end - _text, PMD_SIZE); i++) अणु
		पूर्णांक idx = i + (physaddr >> PMD_SHIFT);

		pmd[idx % PTRS_PER_PMD] = pmd_entry + i * PMD_SIZE;
	पूर्ण

	/*
	 * Fixup the kernel text+data भव addresses. Note that
	 * we might ग_लिखो invalid pmds, when the kernel is relocated
	 * cleanup_highmap() fixes this up aदीर्घ with the mappings
	 * beyond _end.
	 *
	 * Only the region occupied by the kernel image has so far
	 * been checked against the table of usable memory regions
	 * provided by the firmware, so invalidate pages outside that
	 * region. A page table entry that maps to a reserved area of
	 * memory would allow processor speculation पूर्णांकo that area,
	 * and on some hardware (particularly the UV platक्रमm) even
	 * speculative access to some reserved areas is caught as an
	 * error, causing the BIOS to halt the प्रणाली.
	 */

	pmd = fixup_poपूर्णांकer(level2_kernel_pgt, physaddr);

	/* invalidate pages beक्रमe the kernel image */
	क्रम (i = 0; i < pmd_index((अचिन्हित दीर्घ)_text); i++)
		pmd[i] &= ~_PAGE_PRESENT;

	/* fixup pages that are part of the kernel image */
	क्रम (; i <= pmd_index((अचिन्हित दीर्घ)_end); i++)
		अगर (pmd[i] & _PAGE_PRESENT)
			pmd[i] += load_delta;

	/* invalidate pages after the kernel image */
	क्रम (; i < PTRS_PER_PMD; i++)
		pmd[i] &= ~_PAGE_PRESENT;

	/*
	 * Fixup phys_base - हटाओ the memory encryption mask to obtain
	 * the true physical address.
	 */
	*fixup_दीर्घ(&phys_base, physaddr) += load_delta - sme_get_me_mask();

	/* Encrypt the kernel and related (अगर SME is active) */
	sme_encrypt_kernel(bp);

	/*
	 * Clear the memory encryption mask from the .bss..decrypted section.
	 * The bss section will be स_रखो to zero later in the initialization so
	 * there is no need to zero it after changing the memory encryption
	 * attribute.
	 */
	अगर (mem_encrypt_active()) अणु
		vaddr = (अचिन्हित दीर्घ)__start_bss_decrypted;
		vaddr_end = (अचिन्हित दीर्घ)__end_bss_decrypted;
		क्रम (; vaddr < vaddr_end; vaddr += PMD_SIZE) अणु
			i = pmd_index(vaddr);
			pmd[i] -= sme_get_me_mask();
		पूर्ण
	पूर्ण

	/*
	 * Return the SME encryption mask (अगर SME is active) to be used as a
	 * modअगरier क्रम the initial pgdir entry programmed पूर्णांकo CR3.
	 */
	वापस sme_get_me_mask();
पूर्ण

अचिन्हित दीर्घ __startup_secondary_64(व्योम)
अणु
	/*
	 * Return the SME encryption mask (अगर SME is active) to be used as a
	 * modअगरier क्रम the initial pgdir entry programmed पूर्णांकo CR3.
	 */
	वापस sme_get_me_mask();
पूर्ण

/* Wipe all early page tables except क्रम the kernel symbol map */
अटल व्योम __init reset_early_page_tables(व्योम)
अणु
	स_रखो(early_top_pgt, 0, माप(pgd_t)*(PTRS_PER_PGD-1));
	next_early_pgt = 0;
	ग_लिखो_cr3(__sme_pa_nodebug(early_top_pgt));
पूर्ण

/* Create a new PMD entry */
bool __init __early_make_pgtable(अचिन्हित दीर्घ address, pmdval_t pmd)
अणु
	अचिन्हित दीर्घ physaddr = address - __PAGE_OFFSET;
	pgdval_t pgd, *pgd_p;
	p4dval_t p4d, *p4d_p;
	pudval_t pud, *pud_p;
	pmdval_t *pmd_p;

	/* Invalid address or early pgt is करोne ?  */
	अगर (physaddr >= MAXMEM || पढ़ो_cr3_pa() != __pa_nodebug(early_top_pgt))
		वापस false;

again:
	pgd_p = &early_top_pgt[pgd_index(address)].pgd;
	pgd = *pgd_p;

	/*
	 * The use of __START_KERNEL_map rather than __PAGE_OFFSET here is
	 * critical -- __PAGE_OFFSET would poपूर्णांक us back पूर्णांकo the dynamic
	 * range and we might end up looping क्रमever...
	 */
	अगर (!pgtable_l5_enabled())
		p4d_p = pgd_p;
	अन्यथा अगर (pgd)
		p4d_p = (p4dval_t *)((pgd & PTE_PFN_MASK) + __START_KERNEL_map - phys_base);
	अन्यथा अणु
		अगर (next_early_pgt >= EARLY_DYNAMIC_PAGE_TABLES) अणु
			reset_early_page_tables();
			जाओ again;
		पूर्ण

		p4d_p = (p4dval_t *)early_dynamic_pgts[next_early_pgt++];
		स_रखो(p4d_p, 0, माप(*p4d_p) * PTRS_PER_P4D);
		*pgd_p = (pgdval_t)p4d_p - __START_KERNEL_map + phys_base + _KERNPG_TABLE;
	पूर्ण
	p4d_p += p4d_index(address);
	p4d = *p4d_p;

	अगर (p4d)
		pud_p = (pudval_t *)((p4d & PTE_PFN_MASK) + __START_KERNEL_map - phys_base);
	अन्यथा अणु
		अगर (next_early_pgt >= EARLY_DYNAMIC_PAGE_TABLES) अणु
			reset_early_page_tables();
			जाओ again;
		पूर्ण

		pud_p = (pudval_t *)early_dynamic_pgts[next_early_pgt++];
		स_रखो(pud_p, 0, माप(*pud_p) * PTRS_PER_PUD);
		*p4d_p = (p4dval_t)pud_p - __START_KERNEL_map + phys_base + _KERNPG_TABLE;
	पूर्ण
	pud_p += pud_index(address);
	pud = *pud_p;

	अगर (pud)
		pmd_p = (pmdval_t *)((pud & PTE_PFN_MASK) + __START_KERNEL_map - phys_base);
	अन्यथा अणु
		अगर (next_early_pgt >= EARLY_DYNAMIC_PAGE_TABLES) अणु
			reset_early_page_tables();
			जाओ again;
		पूर्ण

		pmd_p = (pmdval_t *)early_dynamic_pgts[next_early_pgt++];
		स_रखो(pmd_p, 0, माप(*pmd_p) * PTRS_PER_PMD);
		*pud_p = (pudval_t)pmd_p - __START_KERNEL_map + phys_base + _KERNPG_TABLE;
	पूर्ण
	pmd_p[pmd_index(address)] = pmd;

	वापस true;
पूर्ण

अटल bool __init early_make_pgtable(अचिन्हित दीर्घ address)
अणु
	अचिन्हित दीर्घ physaddr = address - __PAGE_OFFSET;
	pmdval_t pmd;

	pmd = (physaddr & PMD_MASK) + early_pmd_flags;

	वापस __early_make_pgtable(address, pmd);
पूर्ण

व्योम __init करो_early_exception(काष्ठा pt_regs *regs, पूर्णांक trapnr)
अणु
	अगर (trapnr == X86_TRAP_PF &&
	    early_make_pgtable(native_पढ़ो_cr2()))
		वापस;

	अगर (IS_ENABLED(CONFIG_AMD_MEM_ENCRYPT) &&
	    trapnr == X86_TRAP_VC && handle_vc_boot_ghcb(regs))
		वापस;

	early_fixup_exception(regs, trapnr);
पूर्ण

/* Don't add a prपूर्णांकk in there. prपूर्णांकk relies on the PDA which is not initialized 
   yet. */
अटल व्योम __init clear_bss(व्योम)
अणु
	स_रखो(__bss_start, 0,
	       (अचिन्हित दीर्घ) __bss_stop - (अचिन्हित दीर्घ) __bss_start);
पूर्ण

अटल अचिन्हित दीर्घ get_cmd_line_ptr(व्योम)
अणु
	अचिन्हित दीर्घ cmd_line_ptr = boot_params.hdr.cmd_line_ptr;

	cmd_line_ptr |= (u64)boot_params.ext_cmd_line_ptr << 32;

	वापस cmd_line_ptr;
पूर्ण

अटल व्योम __init copy_bootdata(अक्षर *real_mode_data)
अणु
	अक्षर * command_line;
	अचिन्हित दीर्घ cmd_line_ptr;

	/*
	 * If SME is active, this will create decrypted mappings of the
	 * boot data in advance of the copy operations.
	 */
	sme_map_bootdata(real_mode_data);

	स_नकल(&boot_params, real_mode_data, माप(boot_params));
	sanitize_boot_params(&boot_params);
	cmd_line_ptr = get_cmd_line_ptr();
	अगर (cmd_line_ptr) अणु
		command_line = __va(cmd_line_ptr);
		स_नकल(boot_command_line, command_line, COMMAND_LINE_SIZE);
	पूर्ण

	/*
	 * The old boot data is no दीर्घer needed and won't be reserved,
	 * मुक्तing up that memory क्रम use by the प्रणाली. If SME is active,
	 * we need to हटाओ the mappings that were created so that the
	 * memory करोesn't reमुख्य mapped as decrypted.
	 */
	sme_unmap_bootdata(real_mode_data);
पूर्ण

यंत्रlinkage __visible व्योम __init x86_64_start_kernel(अक्षर * real_mode_data)
अणु
	/*
	 * Build-समय sanity checks on the kernel image and module
	 * area mappings. (these are purely build-समय and produce no code)
	 */
	BUILD_BUG_ON(MODULES_VADDR < __START_KERNEL_map);
	BUILD_BUG_ON(MODULES_VADDR - __START_KERNEL_map < KERNEL_IMAGE_SIZE);
	BUILD_BUG_ON(MODULES_LEN + KERNEL_IMAGE_SIZE > 2*PUD_SIZE);
	BUILD_BUG_ON((__START_KERNEL_map & ~PMD_MASK) != 0);
	BUILD_BUG_ON((MODULES_VADDR & ~PMD_MASK) != 0);
	BUILD_BUG_ON(!(MODULES_VADDR > __START_KERNEL));
	MAYBE_BUILD_BUG_ON(!(((MODULES_END - 1) & PGसूची_MASK) ==
				(__START_KERNEL & PGसूची_MASK)));
	BUILD_BUG_ON(__fix_to_virt(__end_of_fixed_addresses) <= MODULES_END);

	cr4_init_shaकरोw();

	/* Kill off the identity-map trampoline */
	reset_early_page_tables();

	clear_bss();

	clear_page(init_top_pgt);

	/*
	 * SME support may update early_pmd_flags to include the memory
	 * encryption mask, so it needs to be called beक्रमe anything
	 * that may generate a page fault.
	 */
	sme_early_init();

	kasan_early_init();

	idt_setup_early_handler();

	copy_bootdata(__va(real_mode_data));

	/*
	 * Load microcode early on BSP.
	 */
	load_ucode_bsp();

	/* set init_top_pgt kernel high mapping*/
	init_top_pgt[511] = early_top_pgt[511];

	x86_64_start_reservations(real_mode_data);
पूर्ण

व्योम __init x86_64_start_reservations(अक्षर *real_mode_data)
अणु
	/* version is always not zero अगर it is copied */
	अगर (!boot_params.hdr.version)
		copy_bootdata(__va(real_mode_data));

	x86_early_init_platक्रमm_quirks();

	चयन (boot_params.hdr.hardware_subarch) अणु
	हाल X86_SUBARCH_INTEL_MID:
		x86_पूर्णांकel_mid_early_setup();
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	start_kernel();
पूर्ण

/*
 * Data काष्ठाures and code used क्रम IDT setup in head_64.S. The bringup-IDT is
 * used until the idt_table takes over. On the boot CPU this happens in
 * x86_64_start_kernel(), on secondary CPUs in start_secondary(). In both हालs
 * this happens in the functions called from head_64.S.
 *
 * The idt_table can't be used that early because all the code modअगरying it is
 * in idt.c and can be instrumented by tracing or KASAN, which both करोn't work
 * during early CPU bringup. Also the idt_table has the runसमय vectors
 * configured which require certain CPU state to be setup alपढ़ोy (like TSS),
 * which also hasn't happened yet in early CPU bringup.
 */
अटल gate_desc bringup_idt_table[NUM_EXCEPTION_VECTORS] __page_aligned_data;

अटल काष्ठा desc_ptr bringup_idt_descr = अणु
	.size		= (NUM_EXCEPTION_VECTORS * माप(gate_desc)) - 1,
	.address	= 0, /* Set at runसमय */
पूर्ण;

अटल व्योम set_bringup_idt_handler(gate_desc *idt, पूर्णांक n, व्योम *handler)
अणु
#अगर_घोषित CONFIG_AMD_MEM_ENCRYPT
	काष्ठा idt_data data;
	gate_desc desc;

	init_idt_data(&data, n, handler);
	idt_init_desc(&desc, &data);
	native_ग_लिखो_idt_entry(idt, n, &desc);
#पूर्ण_अगर
पूर्ण

/* This runs जबतक still in the direct mapping */
अटल व्योम startup_64_load_idt(अचिन्हित दीर्घ physbase)
अणु
	काष्ठा desc_ptr *desc = fixup_poपूर्णांकer(&bringup_idt_descr, physbase);
	gate_desc *idt = fixup_poपूर्णांकer(bringup_idt_table, physbase);


	अगर (IS_ENABLED(CONFIG_AMD_MEM_ENCRYPT)) अणु
		व्योम *handler;

		/* VMM Communication Exception */
		handler = fixup_poपूर्णांकer(vc_no_ghcb, physbase);
		set_bringup_idt_handler(idt, X86_TRAP_VC, handler);
	पूर्ण

	desc->address = (अचिन्हित दीर्घ)idt;
	native_load_idt(desc);
पूर्ण

/* This is used when running on kernel addresses */
व्योम early_setup_idt(व्योम)
अणु
	/* VMM Communication Exception */
	अगर (IS_ENABLED(CONFIG_AMD_MEM_ENCRYPT))
		set_bringup_idt_handler(bringup_idt_table, X86_TRAP_VC, vc_boot_ghcb);

	bringup_idt_descr.address = (अचिन्हित दीर्घ)bringup_idt_table;
	native_load_idt(&bringup_idt_descr);
पूर्ण

/*
 * Setup boot CPU state needed beक्रमe kernel चयनes to भव addresses.
 */
व्योम __head startup_64_setup_env(अचिन्हित दीर्घ physbase)
अणु
	/* Load GDT */
	startup_gdt_descr.address = (अचिन्हित दीर्घ)fixup_poपूर्णांकer(startup_gdt, physbase);
	native_load_gdt(&startup_gdt_descr);

	/* New GDT is live - reload data segment रेजिस्टरs */
	यंत्र अस्थिर("movl %%eax, %%ds\n"
		     "movl %%eax, %%ss\n"
		     "movl %%eax, %%es\n" : : "a"(__KERNEL_DS) : "memory");

	startup_64_load_idt(physbase);
पूर्ण
