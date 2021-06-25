<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hibernation support क्रम x86-64
 *
 * Copyright (c) 2007 Rafael J. Wysocki <rjw@sisk.pl>
 * Copyright (c) 2002 Pavel Machek <pavel@ucw.cz>
 * Copyright (c) 2001 Patrick Mochel <mochel@osdl.org>
 */

#समावेश <linux/gfp.h>
#समावेश <linux/smp.h>
#समावेश <linux/suspend.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/pgtable.h>

#समावेश <crypto/hash.h>

#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/init.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mtrr.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/tlbflush.h>

अटल पूर्णांक set_up_temporary_text_mapping(pgd_t *pgd)
अणु
	pmd_t *pmd;
	pud_t *pud;
	p4d_t *p4d = शून्य;
	pgprot_t pgtable_prot = __pgprot(_KERNPG_TABLE);
	pgprot_t pmd_text_prot = __pgprot(__PAGE_KERNEL_LARGE_EXEC);

	/* Filter out unsupported __PAGE_KERNEL* bits: */
	pgprot_val(pmd_text_prot) &= __शेष_kernel_pte_mask;
	pgprot_val(pgtable_prot)  &= __शेष_kernel_pte_mask;

	/*
	 * The new mapping only has to cover the page containing the image
	 * kernel's entry poपूर्णांक (jump_address_phys), because the चयन over to
	 * it is carried out by relocated code running from a page allocated
	 * specअगरically क्रम this purpose and covered by the identity mapping, so
	 * the temporary kernel text mapping is only needed क्रम the final jump.
	 * Moreover, in that mapping the भव address of the image kernel's
	 * entry poपूर्णांक must be the same as its भव address in the image
	 * kernel (restore_jump_address), so the image kernel's
	 * restore_रेजिस्टरs() code करोesn't find itself in a dअगरferent area of
	 * the भव address space after चयनing over to the original page
	 * tables used by the image kernel.
	 */

	अगर (pgtable_l5_enabled()) अणु
		p4d = (p4d_t *)get_safe_page(GFP_ATOMIC);
		अगर (!p4d)
			वापस -ENOMEM;
	पूर्ण

	pud = (pud_t *)get_safe_page(GFP_ATOMIC);
	अगर (!pud)
		वापस -ENOMEM;

	pmd = (pmd_t *)get_safe_page(GFP_ATOMIC);
	अगर (!pmd)
		वापस -ENOMEM;

	set_pmd(pmd + pmd_index(restore_jump_address),
		__pmd((jump_address_phys & PMD_MASK) | pgprot_val(pmd_text_prot)));
	set_pud(pud + pud_index(restore_jump_address),
		__pud(__pa(pmd) | pgprot_val(pgtable_prot)));
	अगर (p4d) अणु
		p4d_t new_p4d = __p4d(__pa(pud) | pgprot_val(pgtable_prot));
		pgd_t new_pgd = __pgd(__pa(p4d) | pgprot_val(pgtable_prot));

		set_p4d(p4d + p4d_index(restore_jump_address), new_p4d);
		set_pgd(pgd + pgd_index(restore_jump_address), new_pgd);
	पूर्ण अन्यथा अणु
		/* No p4d क्रम 4-level paging: poपूर्णांक the pgd to the pud page table */
		pgd_t new_pgd = __pgd(__pa(pud) | pgprot_val(pgtable_prot));
		set_pgd(pgd + pgd_index(restore_jump_address), new_pgd);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *alloc_pgt_page(व्योम *context)
अणु
	वापस (व्योम *)get_safe_page(GFP_ATOMIC);
पूर्ण

अटल पूर्णांक set_up_temporary_mappings(व्योम)
अणु
	काष्ठा x86_mapping_info info = अणु
		.alloc_pgt_page	= alloc_pgt_page,
		.page_flag	= __PAGE_KERNEL_LARGE_EXEC,
		.offset		= __PAGE_OFFSET,
	पूर्ण;
	अचिन्हित दीर्घ mstart, mend;
	pgd_t *pgd;
	पूर्णांक result;
	पूर्णांक i;

	pgd = (pgd_t *)get_safe_page(GFP_ATOMIC);
	अगर (!pgd)
		वापस -ENOMEM;

	/* Prepare a temporary mapping क्रम the kernel text */
	result = set_up_temporary_text_mapping(pgd);
	अगर (result)
		वापस result;

	/* Set up the direct mapping from scratch */
	क्रम (i = 0; i < nr_pfn_mapped; i++) अणु
		mstart = pfn_mapped[i].start << PAGE_SHIFT;
		mend   = pfn_mapped[i].end << PAGE_SHIFT;

		result = kernel_ident_mapping_init(&info, pgd, mstart, mend);
		अगर (result)
			वापस result;
	पूर्ण

	temp_pgt = __pa(pgd);
	वापस 0;
पूर्ण

यंत्रlinkage पूर्णांक swsusp_arch_resume(व्योम)
अणु
	पूर्णांक error;

	/* We have got enough memory and from now on we cannot recover */
	error = set_up_temporary_mappings();
	अगर (error)
		वापस error;

	error = relocate_restore_code();
	अगर (error)
		वापस error;

	restore_image();
	वापस 0;
पूर्ण
