<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/alpha/mm/init.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 */

/* 2.3.x zone allocator, 1999 Andrea Arcangeli <andrea@suse.de> */

#समावेश <linux/pagemap.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h> /* max_low_pfn */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/gfp.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/console.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>

बाह्य व्योम die_अगर_kernel(अक्षर *,काष्ठा pt_regs *,दीर्घ);

अटल काष्ठा pcb_काष्ठा original_pcb;

pgd_t *
pgd_alloc(काष्ठा mm_काष्ठा *mm)
अणु
	pgd_t *ret, *init;

	ret = (pgd_t *)__get_मुक्त_page(GFP_KERNEL | __GFP_ZERO);
	init = pgd_offset(&init_mm, 0UL);
	अगर (ret) अणु
#अगर_घोषित CONFIG_ALPHA_LARGE_VMALLOC
		स_नकल (ret + USER_PTRS_PER_PGD, init + USER_PTRS_PER_PGD,
			(PTRS_PER_PGD - USER_PTRS_PER_PGD - 1)*माप(pgd_t));
#अन्यथा
		pgd_val(ret[PTRS_PER_PGD-2]) = pgd_val(init[PTRS_PER_PGD-2]);
#पूर्ण_अगर

		/* The last PGD entry is the VPTB self-map.  */
		pgd_val(ret[PTRS_PER_PGD-1])
		  = pte_val(mk_pte(virt_to_page(ret), PAGE_KERNEL));
	पूर्ण
	वापस ret;
पूर्ण


/*
 * BAD_PAGE is the page that is used क्रम page faults when linux
 * is out-of-memory. Older versions of linux just did a
 * करो_निकास(), but using this instead means there is less risk
 * क्रम a process dying in kernel mode, possibly leaving an inode
 * unused etc..
 *
 * BAD_PAGETABLE is the accompanying page-table: it is initialized
 * to poपूर्णांक to BAD_PAGE entries.
 *
 * ZERO_PAGE is a special page that is used क्रम zero-initialized
 * data and COW.
 */
pmd_t *
__bad_pagetable(व्योम)
अणु
	स_रखो((व्योम *) EMPTY_PGT, 0, PAGE_SIZE);
	वापस (pmd_t *) EMPTY_PGT;
पूर्ण

pte_t
__bad_page(व्योम)
अणु
	स_रखो((व्योम *) EMPTY_PGE, 0, PAGE_SIZE);
	वापस pte_सूची_गढ़ोty(mk_pte(virt_to_page(EMPTY_PGE), PAGE_SHARED));
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ
load_PCB(काष्ठा pcb_काष्ठा *pcb)
अणु
	रेजिस्टर अचिन्हित दीर्घ sp __यंत्र__("$30");
	pcb->ksp = sp;
	वापस __reload_thपढ़ो(pcb);
पूर्ण

/* Set up initial PCB, VPTB, and other such nicities.  */

अटल अंतरभूत व्योम
चयन_to_प्रणाली_map(व्योम)
अणु
	अचिन्हित दीर्घ newptbr;
	अचिन्हित दीर्घ original_pcb_ptr;

	/* Initialize the kernel's page tables.  Linux माला_दो the vptb in
	   the last slot of the L1 page table.  */
	स_रखो(swapper_pg_dir, 0, PAGE_SIZE);
	newptbr = ((अचिन्हित दीर्घ) swapper_pg_dir - PAGE_OFFSET) >> PAGE_SHIFT;
	pgd_val(swapper_pg_dir[1023]) =
		(newptbr << 32) | pgprot_val(PAGE_KERNEL);

	/* Set the vptb.  This is often करोne by the bootloader, but 
	   shouldn't be required.  */
	अगर (hwrpb->vptb != 0xfffffffe00000000UL) अणु
		wrvptptr(0xfffffffe00000000UL);
		hwrpb->vptb = 0xfffffffe00000000UL;
		hwrpb_update_checksum(hwrpb);
	पूर्ण

	/* Also set up the real kernel PCB जबतक we're at it.  */
	init_thपढ़ो_info.pcb.ptbr = newptbr;
	init_thपढ़ो_info.pcb.flags = 1;	/* set FEN, clear everything अन्यथा */
	original_pcb_ptr = load_PCB(&init_thपढ़ो_info.pcb);
	tbia();

	/* Save off the contents of the original PCB so that we can
	   restore the original console's page tables क्रम a clean reboot.

	   Note that the PCB is supposed to be a physical address, but
	   since KSEG values also happen to work, folks get confused.
	   Check this here.  */

	अगर (original_pcb_ptr < PAGE_OFFSET) अणु
		original_pcb_ptr = (अचिन्हित दीर्घ)
			phys_to_virt(original_pcb_ptr);
	पूर्ण
	original_pcb = *(काष्ठा pcb_काष्ठा *) original_pcb_ptr;
पूर्ण

पूर्णांक callback_init_करोne;

व्योम * __init
callback_init(व्योम * kernel_end)
अणु
	काष्ठा crb_काष्ठा * crb;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	व्योम *two_pages;

	/* Starting at the HWRPB, locate the CRB. */
	crb = (काष्ठा crb_काष्ठा *)((अक्षर *)hwrpb + hwrpb->crb_offset);

	अगर (alpha_using_srm) अणु
		/* Tell the console whither it is to be remapped. */
		अगर (srm_fixup(VMALLOC_START, (अचिन्हित दीर्घ)hwrpb))
			__halt();		/* "We're boned."  --Bender */

		/* Edit the procedure descriptors क्रम DISPATCH and FIXUP. */
		crb->dispatch_va = (काष्ठा procdesc_काष्ठा *)
			(VMALLOC_START + (अचिन्हित दीर्घ)crb->dispatch_va
			 - crb->map[0].va);
		crb->fixup_va = (काष्ठा procdesc_काष्ठा *)
			(VMALLOC_START + (अचिन्हित दीर्घ)crb->fixup_va
			 - crb->map[0].va);
	पूर्ण

	चयन_to_प्रणाली_map();

	/* Allocate one PGD and one PMD.  In the हाल of SRM, we'll need
	   these to actually remap the console.  There is an assumption
	   here that only one of each is needed, and this allows क्रम 8MB.
	   On प्रणालीs with larger consoles, additional pages will be
	   allocated as needed during the mapping process.

	   In the हाल of not SRM, but not CONFIG_ALPHA_LARGE_VMALLOC,
	   we need to allocate the PGD we use क्रम vदो_स्मृति beक्रमe we start
	   विभाजनing other tasks.  */

	two_pages = (व्योम *)
	  (((अचिन्हित दीर्घ)kernel_end + ~PAGE_MASK) & PAGE_MASK);
	kernel_end = two_pages + 2*PAGE_SIZE;
	स_रखो(two_pages, 0, 2*PAGE_SIZE);

	pgd = pgd_offset_k(VMALLOC_START);
	p4d = p4d_offset(pgd, VMALLOC_START);
	pud = pud_offset(p4d, VMALLOC_START);
	pud_set(pud, (pmd_t *)two_pages);
	pmd = pmd_offset(pud, VMALLOC_START);
	pmd_set(pmd, (pte_t *)(two_pages + PAGE_SIZE));

	अगर (alpha_using_srm) अणु
		अटल काष्ठा vm_काष्ठा console_remap_vm;
		अचिन्हित दीर्घ nr_pages = 0;
		अचिन्हित दीर्घ vaddr;
		अचिन्हित दीर्घ i, j;

		/* calculate needed size */
		क्रम (i = 0; i < crb->map_entries; ++i)
			nr_pages += crb->map[i].count;

		/* रेजिस्टर the vm area */
		console_remap_vm.flags = VM_ALLOC;
		console_remap_vm.size = nr_pages << PAGE_SHIFT;
		vm_area_रेजिस्टर_early(&console_remap_vm, PAGE_SIZE);

		vaddr = (अचिन्हित दीर्घ)console_remap_vm.addr;

		/* Set up the third level PTEs and update the भव
		   addresses of the CRB entries.  */
		क्रम (i = 0; i < crb->map_entries; ++i) अणु
			अचिन्हित दीर्घ pfn = crb->map[i].pa >> PAGE_SHIFT;
			crb->map[i].va = vaddr;
			क्रम (j = 0; j < crb->map[i].count; ++j) अणु
				/* Newer consoles (especially on larger
				   प्रणालीs) may require more pages of
				   PTEs. Grab additional pages as needed. */
				अगर (pmd != pmd_offset(pud, vaddr)) अणु
					स_रखो(kernel_end, 0, PAGE_SIZE);
					pmd = pmd_offset(pud, vaddr);
					pmd_set(pmd, (pte_t *)kernel_end);
					kernel_end += PAGE_SIZE;
				पूर्ण
				set_pte(pte_offset_kernel(pmd, vaddr),
					pfn_pte(pfn, PAGE_KERNEL));
				pfn++;
				vaddr += PAGE_SIZE;
			पूर्ण
		पूर्ण
	पूर्ण

	callback_init_करोne = 1;
	वापस kernel_end;
पूर्ण


#अगर_अघोषित CONFIG_DISCONTIGMEM
/*
 * paging_init() sets up the memory map.
 */
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु0, पूर्ण;
	अचिन्हित दीर्घ dma_pfn;

	dma_pfn = virt_to_phys((अक्षर *)MAX_DMA_ADDRESS) >> PAGE_SHIFT;
	max_pfn = max_low_pfn;

	max_zone_pfn[ZONE_DMA] = dma_pfn;
	max_zone_pfn[ZONE_NORMAL] = max_pfn;

	/* Initialize mem_map[].  */
	मुक्त_area_init(max_zone_pfn);

	/* Initialize the kernel's ZERO_PGE. */
	स_रखो((व्योम *)ZERO_PGE, 0, PAGE_SIZE);
पूर्ण
#पूर्ण_अगर /* CONFIG_DISCONTIGMEM */

#अगर defined(CONFIG_ALPHA_GENERIC) || defined(CONFIG_ALPHA_SRM)
व्योम
srm_paging_stop (व्योम)
अणु
	/* Move the vptb back to where the SRM console expects it.  */
	swapper_pg_dir[1] = swapper_pg_dir[1023];
	tbia();
	wrvptptr(0x200000000UL);
	hwrpb->vptb = 0x200000000UL;
	hwrpb_update_checksum(hwrpb);

	/* Reload the page tables that the console had in use.  */
	load_PCB(&original_pcb);
	tbia();
पूर्ण
#पूर्ण_अगर

व्योम __init
mem_init(व्योम)
अणु
	set_max_mapnr(max_low_pfn);
	high_memory = (व्योम *) __va(max_low_pfn * PAGE_SIZE);
	memblock_मुक्त_all();
पूर्ण
