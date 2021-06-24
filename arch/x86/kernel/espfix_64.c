<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2014 Intel Corporation; author: H. Peter Anvin
 *
 * ----------------------------------------------------------------------- */

/*
 * The IRET inकाष्ठाion, when वापसing to a 16-bit segment, only
 * restores the bottom 16 bits of the user space stack poपूर्णांकer.  This
 * causes some 16-bit software to अवरोध, but it also leaks kernel state
 * to user space.
 *
 * This works around this by creating percpu "ministacks", each of which
 * is mapped 2^16 बार 64K apart.  When we detect that the वापस SS is
 * on the LDT, we copy the IRET frame to the ministack and use the
 * relevant alias to वापस to userspace.  The ministacks are mapped
 * पढ़ोonly, so अगर the IRET fault we promote #GP to #DF which is an IST
 * vector and thus has its own stack; we then करो the fixup in the #DF
 * handler.
 *
 * This file sets up the ministacks and the related page tables.  The
 * actual ministack invocation is in entry_64.S.
 */

#समावेश <linux/init.h>
#समावेश <linux/init_task.h>
#समावेश <linux/kernel.h>
#समावेश <linux/percpu.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/espfix.h>

/*
 * Note: we only need 6*8 = 48 bytes क्रम the espfix stack, but round
 * it up to a cache line to aव्योम unnecessary sharing.
 */
#घोषणा ESPFIX_STACK_SIZE	(8*8UL)
#घोषणा ESPFIX_STACKS_PER_PAGE	(PAGE_SIZE/ESPFIX_STACK_SIZE)

/* There is address space क्रम how many espfix pages? */
#घोषणा ESPFIX_PAGE_SPACE	(1UL << (P4D_SHIFT-PAGE_SHIFT-16))

#घोषणा ESPFIX_MAX_CPUS		(ESPFIX_STACKS_PER_PAGE * ESPFIX_PAGE_SPACE)
#अगर CONFIG_NR_CPUS > ESPFIX_MAX_CPUS
# error "Need more virtual address space for the ESPFIX hack"
#पूर्ण_अगर

#घोषणा PGALLOC_GFP (GFP_KERNEL | __GFP_ZERO)

/* This contains the *bottom* address of the espfix stack */
DEFINE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ, espfix_stack);
DEFINE_PER_CPU_READ_MOSTLY(अचिन्हित दीर्घ, espfix_waddr);

/* Initialization mutex - should this be a spinlock? */
अटल DEFINE_MUTEX(espfix_init_mutex);

/* Page allocation biपंचांगap - each page serves ESPFIX_STACKS_PER_PAGE CPUs */
#घोषणा ESPFIX_MAX_PAGES  DIV_ROUND_UP(CONFIG_NR_CPUS, ESPFIX_STACKS_PER_PAGE)
अटल व्योम *espfix_pages[ESPFIX_MAX_PAGES];

अटल __page_aligned_bss pud_t espfix_pud_page[PTRS_PER_PUD]
	__aligned(PAGE_SIZE);

अटल अचिन्हित पूर्णांक page_अक्रमom, slot_अक्रमom;

/*
 * This वापसs the bottom address of the espfix stack क्रम a specअगरic CPU.
 * The math allows क्रम a non-घातer-of-two ESPFIX_STACK_SIZE, in which हाल
 * we have to account क्रम some amount of padding at the end of each page.
 */
अटल अंतरभूत अचिन्हित दीर्घ espfix_base_addr(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ page, slot;
	अचिन्हित दीर्घ addr;

	page = (cpu / ESPFIX_STACKS_PER_PAGE) ^ page_अक्रमom;
	slot = (cpu + slot_अक्रमom) % ESPFIX_STACKS_PER_PAGE;
	addr = (page << PAGE_SHIFT) + (slot * ESPFIX_STACK_SIZE);
	addr = (addr & 0xffffUL) | ((addr & ~0xffffUL) << 16);
	addr += ESPFIX_BASE_ADDR;
	वापस addr;
पूर्ण

#घोषणा PTE_STRIDE        (65536/PAGE_SIZE)
#घोषणा ESPFIX_PTE_CLONES (PTRS_PER_PTE/PTE_STRIDE)
#घोषणा ESPFIX_PMD_CLONES PTRS_PER_PMD
#घोषणा ESPFIX_PUD_CLONES (65536/(ESPFIX_PTE_CLONES*ESPFIX_PMD_CLONES))

#घोषणा PGTABLE_PROT	  ((_KERNPG_TABLE & ~_PAGE_RW) | _PAGE_NX)

अटल व्योम init_espfix_अक्रमom(व्योम)
अणु
	अचिन्हित दीर्घ अक्रम;

	/*
	 * This is run beक्रमe the entropy pools are initialized,
	 * but this is hopefully better than nothing.
	 */
	अगर (!arch_get_अक्रमom_दीर्घ(&अक्रम)) अणु
		/* The स्थिरant is an arbitrary large prime */
		अक्रम = rdtsc();
		अक्रम *= 0xc345c6b72fd16123UL;
	पूर्ण

	slot_अक्रमom = अक्रम % ESPFIX_STACKS_PER_PAGE;
	page_अक्रमom = (अक्रम / ESPFIX_STACKS_PER_PAGE)
		& (ESPFIX_PAGE_SPACE - 1);
पूर्ण

व्योम __init init_espfix_bsp(व्योम)
अणु
	pgd_t *pgd;
	p4d_t *p4d;

	/* Install the espfix pud पूर्णांकo the kernel page directory */
	pgd = &init_top_pgt[pgd_index(ESPFIX_BASE_ADDR)];
	p4d = p4d_alloc(&init_mm, pgd, ESPFIX_BASE_ADDR);
	p4d_populate(&init_mm, p4d, espfix_pud_page);

	/* Ranकरोmize the locations */
	init_espfix_अक्रमom();

	/* The rest is the same as क्रम any other processor */
	init_espfix_ap(0);
पूर्ण

व्योम init_espfix_ap(पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक page;
	अचिन्हित दीर्घ addr;
	pud_t pud, *pud_p;
	pmd_t pmd, *pmd_p;
	pte_t pte, *pte_p;
	पूर्णांक n, node;
	व्योम *stack_page;
	pteval_t ptemask;

	/* We only have to करो this once... */
	अगर (likely(per_cpu(espfix_stack, cpu)))
		वापस;		/* Alपढ़ोy initialized */

	addr = espfix_base_addr(cpu);
	page = cpu/ESPFIX_STACKS_PER_PAGE;

	/* Did another CPU alपढ़ोy set this up? */
	stack_page = READ_ONCE(espfix_pages[page]);
	अगर (likely(stack_page))
		जाओ करोne;

	mutex_lock(&espfix_init_mutex);

	/* Did we race on the lock? */
	stack_page = READ_ONCE(espfix_pages[page]);
	अगर (stack_page)
		जाओ unlock_करोne;

	node = cpu_to_node(cpu);
	ptemask = __supported_pte_mask;

	pud_p = &espfix_pud_page[pud_index(addr)];
	pud = *pud_p;
	अगर (!pud_present(pud)) अणु
		काष्ठा page *page = alloc_pages_node(node, PGALLOC_GFP, 0);

		pmd_p = (pmd_t *)page_address(page);
		pud = __pud(__pa(pmd_p) | (PGTABLE_PROT & ptemask));
		paravirt_alloc_pmd(&init_mm, __pa(pmd_p) >> PAGE_SHIFT);
		क्रम (n = 0; n < ESPFIX_PUD_CLONES; n++)
			set_pud(&pud_p[n], pud);
	पूर्ण

	pmd_p = pmd_offset(&pud, addr);
	pmd = *pmd_p;
	अगर (!pmd_present(pmd)) अणु
		काष्ठा page *page = alloc_pages_node(node, PGALLOC_GFP, 0);

		pte_p = (pte_t *)page_address(page);
		pmd = __pmd(__pa(pte_p) | (PGTABLE_PROT & ptemask));
		paravirt_alloc_pte(&init_mm, __pa(pte_p) >> PAGE_SHIFT);
		क्रम (n = 0; n < ESPFIX_PMD_CLONES; n++)
			set_pmd(&pmd_p[n], pmd);
	पूर्ण

	pte_p = pte_offset_kernel(&pmd, addr);
	stack_page = page_address(alloc_pages_node(node, GFP_KERNEL, 0));
	/*
	 * __PAGE_KERNEL_* includes _PAGE_GLOBAL, which we want since
	 * this is mapped to userspace.
	 */
	pte = __pte(__pa(stack_page) | ((__PAGE_KERNEL_RO | _PAGE_ENC) & ptemask));
	क्रम (n = 0; n < ESPFIX_PTE_CLONES; n++)
		set_pte(&pte_p[n*PTE_STRIDE], pte);

	/* Job is करोne क्रम this CPU and any CPU which shares this page */
	WRITE_ONCE(espfix_pages[page], stack_page);

unlock_करोne:
	mutex_unlock(&espfix_init_mutex);
करोne:
	per_cpu(espfix_stack, cpu) = addr;
	per_cpu(espfix_waddr, cpu) = (अचिन्हित दीर्घ)stack_page
				      + (addr & ~PAGE_MASK);
पूर्ण
