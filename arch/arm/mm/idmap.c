<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/प्रणाली_info.h>

/*
 * Note: accesses outside of the kernel image and the identity map area
 * are not supported on any CPU using the idmap tables as its current
 * page tables.
 */
pgd_t *idmap_pgd __ro_after_init;
दीर्घ दीर्घ arch_phys_to_idmap_offset __ro_after_init;

#अगर_घोषित CONFIG_ARM_LPAE
अटल व्योम idmap_add_pmd(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
	अचिन्हित दीर्घ prot)
अणु
	pmd_t *pmd;
	अचिन्हित दीर्घ next;

	अगर (pud_none_or_clear_bad(pud) || (pud_val(*pud) & L_PGD_SWAPPER)) अणु
		pmd = pmd_alloc_one(&init_mm, addr);
		अगर (!pmd) अणु
			pr_warn("Failed to allocate identity pmd.\n");
			वापस;
		पूर्ण
		/*
		 * Copy the original PMD to ensure that the PMD entries क्रम
		 * the kernel image are preserved.
		 */
		अगर (!pud_none(*pud))
			स_नकल(pmd, pmd_offset(pud, 0),
			       PTRS_PER_PMD * माप(pmd_t));
		pud_populate(&init_mm, pud, pmd);
		pmd += pmd_index(addr);
	पूर्ण अन्यथा
		pmd = pmd_offset(pud, addr);

	करो अणु
		next = pmd_addr_end(addr, end);
		*pmd = __pmd((addr & PMD_MASK) | prot);
		flush_pmd_entry(pmd);
	पूर्ण जबतक (pmd++, addr = next, addr != end);
पूर्ण
#अन्यथा	/* !CONFIG_ARM_LPAE */
अटल व्योम idmap_add_pmd(pud_t *pud, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
	अचिन्हित दीर्घ prot)
अणु
	pmd_t *pmd = pmd_offset(pud, addr);

	addr = (addr & PMD_MASK) | prot;
	pmd[0] = __pmd(addr);
	addr += SECTION_SIZE;
	pmd[1] = __pmd(addr);
	flush_pmd_entry(pmd);
पूर्ण
#पूर्ण_अगर	/* CONFIG_ARM_LPAE */

अटल व्योम idmap_add_pud(pgd_t *pgd, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
	अचिन्हित दीर्घ prot)
अणु
	p4d_t *p4d = p4d_offset(pgd, addr);
	pud_t *pud = pud_offset(p4d, addr);
	अचिन्हित दीर्घ next;

	करो अणु
		next = pud_addr_end(addr, end);
		idmap_add_pmd(pud, addr, next, prot);
	पूर्ण जबतक (pud++, addr = next, addr != end);
पूर्ण

अटल व्योम identity_mapping_add(pgd_t *pgd, स्थिर अक्षर *text_start,
				 स्थिर अक्षर *text_end, अचिन्हित दीर्घ prot)
अणु
	अचिन्हित दीर्घ addr, end;
	अचिन्हित दीर्घ next;

	addr = virt_to_idmap(text_start);
	end = virt_to_idmap(text_end);
	pr_info("Setting up static identity map for 0x%lx - 0x%lx\n", addr, end);

	prot |= PMD_TYPE_SECT | PMD_SECT_AP_WRITE | PMD_SECT_AF;

	अगर (cpu_architecture() <= CPU_ARCH_ARMv5TEJ && !cpu_is_xscale_family())
		prot |= PMD_BIT4;

	pgd += pgd_index(addr);
	करो अणु
		next = pgd_addr_end(addr, end);
		idmap_add_pud(pgd, addr, next, prot);
	पूर्ण जबतक (pgd++, addr = next, addr != end);
पूर्ण

बाह्य अक्षर  __idmap_text_start[], __idmap_text_end[];

अटल पूर्णांक __init init_अटल_idmap(व्योम)
अणु
	idmap_pgd = pgd_alloc(&init_mm);
	अगर (!idmap_pgd)
		वापस -ENOMEM;

	identity_mapping_add(idmap_pgd, __idmap_text_start,
			     __idmap_text_end, 0);

	/* Flush L1 क्रम the hardware to see this page table content */
	अगर (!(elf_hwcap & HWCAP_LPAE))
		flush_cache_louis();

	वापस 0;
पूर्ण
early_initcall(init_अटल_idmap);

/*
 * In order to soft-boot, we need to चयन to a 1:1 mapping क्रम the
 * cpu_reset functions. This will then ensure that we have predictable
 * results when turning off the mmu.
 */
व्योम setup_mm_क्रम_reboot(व्योम)
अणु
	/* Switch to the identity mapping. */
	cpu_चयन_mm(idmap_pgd, &init_mm);
	local_flush_bp_all();

#अगर_घोषित CONFIG_CPU_HAS_ASID
	/*
	 * We करोn't have a clean ASID क्रम the identity mapping, which
	 * may clash with भव addresses of the previous page tables
	 * and thereक्रमe potentially in the TLB.
	 */
	local_flush_tlb_all();
#पूर्ण_अगर
पूर्ण
