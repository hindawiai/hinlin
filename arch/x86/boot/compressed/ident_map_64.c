<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This code is used on x86_64 to create page table identity mappings on
 * demand by building up a new set of page tables (or appending to the
 * existing ones), and then चयनing over to them when पढ़ोy.
 *
 * Copyright (C) 2015-2016  Yinghai Lu
 * Copyright (C)      2016  Kees Cook
 */

/*
 * Since we're dealing with identity mappings, physical and भव
 * addresses are the same, so override these defines which are ultimately
 * used by the headers in misc.h.
 */
#घोषणा __pa(x)  ((अचिन्हित दीर्घ)(x))
#घोषणा __va(x)  ((व्योम *)((अचिन्हित दीर्घ)(x)))

/* No PAGE_TABLE_ISOLATION support needed either: */
#अघोषित CONFIG_PAGE_TABLE_ISOLATION

#समावेश "error.h"
#समावेश "misc.h"

/* These actually करो the work of building the kernel identity maps. */
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/cmpxchg.h>
#समावेश <यंत्र/trap_pf.h>
#समावेश <यंत्र/trapnr.h>
#समावेश <यंत्र/init.h>
/* Use the अटल base क्रम this part of the boot process */
#अघोषित __PAGE_OFFSET
#घोषणा __PAGE_OFFSET __PAGE_OFFSET_BASE
#समावेश "../../mm/ident_map.c"

#घोषणा _SETUP
#समावेश <यंत्र/setup.h>	/* For COMMAND_LINE_SIZE */
#अघोषित _SETUP

बाह्य अचिन्हित दीर्घ get_cmd_line_ptr(व्योम);

/* Used by PAGE_KERN* macros: */
pteval_t __शेष_kernel_pte_mask __पढ़ो_mostly = ~0;

/* Used to track our page table allocation area. */
काष्ठा alloc_pgt_data अणु
	अचिन्हित अक्षर *pgt_buf;
	अचिन्हित दीर्घ pgt_buf_size;
	अचिन्हित दीर्घ pgt_buf_offset;
पूर्ण;

/*
 * Allocates space क्रम a page table entry, using काष्ठा alloc_pgt_data
 * above. Besides the local callers, this is used as the allocation
 * callback in mapping_info below.
 */
अटल व्योम *alloc_pgt_page(व्योम *context)
अणु
	काष्ठा alloc_pgt_data *pages = (काष्ठा alloc_pgt_data *)context;
	अचिन्हित अक्षर *entry;

	/* Validate there is space available क्रम a new page. */
	अगर (pages->pgt_buf_offset >= pages->pgt_buf_size) अणु
		debug_माला_दोtr("out of pgt_buf in " __खाता__ "!?\n");
		debug_putaddr(pages->pgt_buf_offset);
		debug_putaddr(pages->pgt_buf_size);
		वापस शून्य;
	पूर्ण

	entry = pages->pgt_buf + pages->pgt_buf_offset;
	pages->pgt_buf_offset += PAGE_SIZE;

	वापस entry;
पूर्ण

/* Used to track our allocated page tables. */
अटल काष्ठा alloc_pgt_data pgt_data;

/* The top level page table entry poपूर्णांकer. */
अटल अचिन्हित दीर्घ top_level_pgt;

phys_addr_t physical_mask = (1ULL << __PHYSICAL_MASK_SHIFT) - 1;

/*
 * Mapping inक्रमmation काष्ठाure passed to kernel_ident_mapping_init().
 * Due to relocation, poपूर्णांकers must be asचिन्हित at run समय not build समय.
 */
अटल काष्ठा x86_mapping_info mapping_info;

/*
 * Adds the specअगरied range to the identity mappings.
 */
अटल व्योम add_identity_map(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	पूर्णांक ret;

	/* Align boundary to 2M. */
	start = round_करोwn(start, PMD_SIZE);
	end = round_up(end, PMD_SIZE);
	अगर (start >= end)
		वापस;

	/* Build the mapping. */
	ret = kernel_ident_mapping_init(&mapping_info, (pgd_t *)top_level_pgt, start, end);
	अगर (ret)
		error("Error: kernel_ident_mapping_init() failed\n");
पूर्ण

/* Locates and clears a region क्रम a new top level page table. */
व्योम initialize_identity_maps(व्योम *rmode)
अणु
	अचिन्हित दीर्घ cmdline;

	/* Exclude the encryption mask from __PHYSICAL_MASK */
	physical_mask &= ~sme_me_mask;

	/* Init mapping_info with run-समय function/buffer poपूर्णांकers. */
	mapping_info.alloc_pgt_page = alloc_pgt_page;
	mapping_info.context = &pgt_data;
	mapping_info.page_flag = __PAGE_KERNEL_LARGE_EXEC | sme_me_mask;
	mapping_info.kernpg_flag = _KERNPG_TABLE;

	/*
	 * It should be impossible क्रम this not to alपढ़ोy be true,
	 * but since calling this a second समय would शुरुआत the other
	 * counters, let's just make sure this is reset too.
	 */
	pgt_data.pgt_buf_offset = 0;

	/*
	 * If we came here via startup_32(), cr3 will be _pgtable alपढ़ोy
	 * and we must append to the existing area instead of entirely
	 * overwriting it.
	 *
	 * With 5-level paging, we use '_pgtable' to allocate the p4d page table,
	 * the top-level page table is allocated separately.
	 *
	 * p4d_offset(top_level_pgt, 0) would cover both the 4- and 5-level
	 * हालs. On 4-level paging it's equal to 'top_level_pgt'.
	 */
	top_level_pgt = पढ़ो_cr3_pa();
	अगर (p4d_offset((pgd_t *)top_level_pgt, 0) == (p4d_t *)_pgtable) अणु
		pgt_data.pgt_buf = _pgtable + BOOT_INIT_PGT_SIZE;
		pgt_data.pgt_buf_size = BOOT_PGT_SIZE - BOOT_INIT_PGT_SIZE;
		स_रखो(pgt_data.pgt_buf, 0, pgt_data.pgt_buf_size);
	पूर्ण अन्यथा अणु
		pgt_data.pgt_buf = _pgtable;
		pgt_data.pgt_buf_size = BOOT_PGT_SIZE;
		स_रखो(pgt_data.pgt_buf, 0, pgt_data.pgt_buf_size);
		top_level_pgt = (अचिन्हित दीर्घ)alloc_pgt_page(&pgt_data);
	पूर्ण

	/*
	 * New page-table is set up - map the kernel image, boot_params and the
	 * command line. The uncompressed kernel requires boot_params and the
	 * command line to be mapped in the identity mapping. Map them
	 * explicitly here in हाल the compressed kernel करोes not touch them,
	 * or करोes not touch all the pages covering them.
	 */
	add_identity_map((अचिन्हित दीर्घ)_head, (अचिन्हित दीर्घ)_end);
	boot_params = rmode;
	add_identity_map((अचिन्हित दीर्घ)boot_params, (अचिन्हित दीर्घ)(boot_params + 1));
	cmdline = get_cmd_line_ptr();
	add_identity_map(cmdline, cmdline + COMMAND_LINE_SIZE);

	/* Load the new page-table. */
	sev_verअगरy_cbit(top_level_pgt);
	ग_लिखो_cr3(top_level_pgt);
पूर्ण

अटल pte_t *split_large_pmd(काष्ठा x86_mapping_info *info,
			      pmd_t *pmdp, अचिन्हित दीर्घ __address)
अणु
	अचिन्हित दीर्घ page_flags;
	अचिन्हित दीर्घ address;
	pte_t *pte;
	pmd_t pmd;
	पूर्णांक i;

	pte = (pte_t *)info->alloc_pgt_page(info->context);
	अगर (!pte)
		वापस शून्य;

	address     = __address & PMD_MASK;
	/* No large page - clear PSE flag */
	page_flags  = info->page_flag & ~_PAGE_PSE;

	/* Populate the PTEs */
	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		set_pte(&pte[i], __pte(address | page_flags));
		address += PAGE_SIZE;
	पूर्ण

	/*
	 * Ideally we need to clear the large PMD first and करो a TLB
	 * flush beक्रमe we ग_लिखो the new PMD. But the 2M range of the
	 * PMD might contain the code we execute and/or the stack
	 * we are on, so we can't करो that. But that should be safe here
	 * because we are going from large to small mappings and we are
	 * also the only user of the page-table, so there is no chance
	 * of a TLB multihit.
	 */
	pmd = __pmd((अचिन्हित दीर्घ)pte | info->kernpg_flag);
	set_pmd(pmdp, pmd);
	/* Flush TLB to establish the new PMD */
	ग_लिखो_cr3(top_level_pgt);

	वापस pte + pte_index(__address);
पूर्ण

अटल व्योम clflush_page(अचिन्हित दीर्घ address)
अणु
	अचिन्हित पूर्णांक flush_size;
	अक्षर *cl, *start, *end;

	/*
	 * Hardcode cl-size to 64 - CPUID can't be used here because that might
	 * cause another #VC exception and the GHCB is not पढ़ोy to use yet.
	 */
	flush_size = 64;
	start      = (अक्षर *)(address & PAGE_MASK);
	end        = start + PAGE_SIZE;

	/*
	 * First make sure there are no pending ग_लिखोs on the cache-lines to
	 * flush.
	 */
	यंत्र अस्थिर("mfence" : : : "memory");

	क्रम (cl = start; cl != end; cl += flush_size)
		clflush(cl);
पूर्ण

अटल पूर्णांक set_clr_page_flags(काष्ठा x86_mapping_info *info,
			      अचिन्हित दीर्घ address,
			      pteval_t set, pteval_t clr)
अणु
	pgd_t *pgdp = (pgd_t *)top_level_pgt;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep, pte;

	/*
	 * First make sure there is a PMD mapping क्रम 'address'.
	 * It should alपढ़ोy exist, but keep things generic.
	 *
	 * To map the page just पढ़ो from it and fault it in अगर there is no
	 * mapping yet. add_identity_map() can't be called here because that
	 * would unconditionally map the address on PMD level, destroying any
	 * PTE-level mappings that might alपढ़ोy exist. Use assembly here so
	 * the access won't be optimized away.
	 */
	यंत्र अस्थिर("mov %[address], %%r9"
		     :: [address] "g" (*(अचिन्हित दीर्घ *)address)
		     : "r9", "memory");

	/*
	 * The page is mapped at least with PMD size - so skip checks and walk
	 * directly to the PMD.
	 */
	p4dp = p4d_offset(pgdp, address);
	pudp = pud_offset(p4dp, address);
	pmdp = pmd_offset(pudp, address);

	अगर (pmd_large(*pmdp))
		ptep = split_large_pmd(info, pmdp, address);
	अन्यथा
		ptep = pte_offset_kernel(pmdp, address);

	अगर (!ptep)
		वापस -ENOMEM;

	/*
	 * Changing encryption attributes of a page requires to flush it from
	 * the caches.
	 */
	अगर ((set | clr) & _PAGE_ENC)
		clflush_page(address);

	/* Update PTE */
	pte = *ptep;
	pte = pte_set_flags(pte, set);
	pte = pte_clear_flags(pte, clr);
	set_pte(ptep, pte);

	/* Flush TLB after changing encryption attribute */
	ग_लिखो_cr3(top_level_pgt);

	वापस 0;
पूर्ण

पूर्णांक set_page_decrypted(अचिन्हित दीर्घ address)
अणु
	वापस set_clr_page_flags(&mapping_info, address, 0, _PAGE_ENC);
पूर्ण

पूर्णांक set_page_encrypted(अचिन्हित दीर्घ address)
अणु
	वापस set_clr_page_flags(&mapping_info, address, _PAGE_ENC, 0);
पूर्ण

पूर्णांक set_page_non_present(अचिन्हित दीर्घ address)
अणु
	वापस set_clr_page_flags(&mapping_info, address, 0, _PAGE_PRESENT);
पूर्ण

अटल व्योम करो_pf_error(स्थिर अक्षर *msg, अचिन्हित दीर्घ error_code,
			अचिन्हित दीर्घ address, अचिन्हित दीर्घ ip)
अणु
	error_माला_दोtr(msg);

	error_माला_दोtr("\nError Code: ");
	error_puthex(error_code);
	error_माला_दोtr("\nCR2: 0x");
	error_puthex(address);
	error_माला_दोtr("\nRIP relative to _head: 0x");
	error_puthex(ip - (अचिन्हित दीर्घ)_head);
	error_माला_दोtr("\n");

	error("Stopping.\n");
पूर्ण

व्योम करो_boot_page_fault(काष्ठा pt_regs *regs, अचिन्हित दीर्घ error_code)
अणु
	अचिन्हित दीर्घ address = native_पढ़ो_cr2();
	अचिन्हित दीर्घ end;
	bool ghcb_fault;

	ghcb_fault = sev_es_check_ghcb_fault(address);

	address   &= PMD_MASK;
	end        = address + PMD_SIZE;

	/*
	 * Check क्रम unexpected error codes. Unexpected are:
	 *	- Faults on present pages
	 *	- User faults
	 *	- Reserved bits set
	 */
	अगर (error_code & (X86_PF_PROT | X86_PF_USER | X86_PF_RSVD))
		करो_pf_error("Unexpected page-fault:", error_code, address, regs->ip);
	अन्यथा अगर (ghcb_fault)
		करो_pf_error("Page-fault on GHCB page:", error_code, address, regs->ip);

	/*
	 * Error code is sane - now identity map the 2M region around
	 * the faulting address.
	 */
	add_identity_map(address, end);
पूर्ण
