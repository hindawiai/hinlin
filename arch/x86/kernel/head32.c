<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/i386/kernel/head32.c -- prepare to run common code
 *
 *  Copyright (C) 2000 Andrea Arcangeli <andrea@suse.de> SuSE
 *  Copyright (C) 2007 Eric Biederman <ebiederm@xmission.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/start_kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/desc.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/bootparam_utils.h>

अटल व्योम __init i386_शेष_early_setup(व्योम)
अणु
	/* Initialize 32bit specअगरic setup functions */
	x86_init.resources.reserve_resources = i386_reserve_resources;
	x86_init.mpparse.setup_ioapic_ids = setup_ioapic_ids_from_mpc;
पूर्ण

यंत्रlinkage __visible व्योम __init i386_start_kernel(व्योम)
अणु
	/* Make sure IDT is set up beक्रमe any exception happens */
	idt_setup_early_handler();

	cr4_init_shaकरोw();

	sanitize_boot_params(&boot_params);

	x86_early_init_platक्रमm_quirks();

	/* Call the subarch specअगरic early setup function */
	चयन (boot_params.hdr.hardware_subarch) अणु
	हाल X86_SUBARCH_INTEL_MID:
		x86_पूर्णांकel_mid_early_setup();
		अवरोध;
	हाल X86_SUBARCH_CE4100:
		x86_ce4100_early_setup();
		अवरोध;
	शेष:
		i386_शेष_early_setup();
		अवरोध;
	पूर्ण

	start_kernel();
पूर्ण

/*
 * Initialize page tables.  This creates a PDE and a set of page
 * tables, which are located immediately beyond __brk_base.  The variable
 * _brk_end is set up to poपूर्णांक to the first "safe" location.
 * Mappings are created both at भव address 0 (identity mapping)
 * and PAGE_OFFSET क्रम up to _end.
 *
 * In PAE mode initial_page_table is अटलally defined to contain
 * enough entries to cover the VMSPLIT option (that is the top 1, 2 or 3
 * entries). The identity mapping is handled by poपूर्णांकing two PGD entries
 * to the first kernel PMD. Note the upper half of each PMD or PTE are
 * always zero at this stage.
 */
व्योम __init mk_early_pgtbl_32(व्योम)
अणु
#अगर_घोषित __pa
#अघोषित __pa
#पूर्ण_अगर
#घोषणा __pa(x)  ((अचिन्हित दीर्घ)(x) - PAGE_OFFSET)
	pte_t pte, *ptep;
	पूर्णांक i;
	अचिन्हित दीर्घ *ptr;
	/* Enough space to fit pagetables क्रम the low memory linear map */
	स्थिर अचिन्हित दीर्घ limit = __pa(_end) +
		(PAGE_TABLE_SIZE(LOWMEM_PAGES) << PAGE_SHIFT);
#अगर_घोषित CONFIG_X86_PAE
	pmd_t pl2, *pl2p = (pmd_t *)__pa(initial_pg_pmd);
#घोषणा SET_PL2(pl2, val)    अणु (pl2).pmd = (val); पूर्ण
#अन्यथा
	pgd_t pl2, *pl2p = (pgd_t *)__pa(initial_page_table);
#घोषणा SET_PL2(pl2, val)   अणु (pl2).pgd = (val); पूर्ण
#पूर्ण_अगर

	ptep = (pte_t *)__pa(__brk_base);
	pte.pte = PTE_IDENT_ATTR;

	जबतक ((pte.pte & PTE_PFN_MASK) < limit) अणु

		SET_PL2(pl2, (अचिन्हित दीर्घ)ptep | PDE_IDENT_ATTR);
		*pl2p = pl2;
#अगर_अघोषित CONFIG_X86_PAE
		/* Kernel PDE entry */
		*(pl2p +  ((PAGE_OFFSET >> PGसूची_SHIFT))) = pl2;
#पूर्ण_अगर
		क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
			*ptep = pte;
			pte.pte += PAGE_SIZE;
			ptep++;
		पूर्ण

		pl2p++;
	पूर्ण

	ptr = (अचिन्हित दीर्घ *)__pa(&max_pfn_mapped);
	/* Can't use pte_pfn() since it's a call with CONFIG_PARAVIRT */
	*ptr = (pte.pte & PTE_PFN_MASK) >> PAGE_SHIFT;

	ptr = (अचिन्हित दीर्घ *)__pa(&_brk_end);
	*ptr = (अचिन्हित दीर्घ)ptep + PAGE_OFFSET;
पूर्ण

